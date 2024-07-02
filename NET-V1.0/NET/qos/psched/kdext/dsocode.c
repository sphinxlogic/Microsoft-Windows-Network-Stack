/****************************** Module Header ******************************\
* Module Name: dsocode.c
*
* Copyright (c) 1985-1999, Microsoft Corporation
*
* This file contains the dump structure offset (dso) extension. It is
*  included by $(ALT_PROJECT)\dsotable.c which is generated by structo.exe
*
* History:
* 06/17/96 GerardoB Created
* 10/06/98 Rajeshsu edited to use wdbgexts.h
\***************************************************************************/

#define DsoPrint(x) dprintf("%.*s", nIndent, "                      "); dprintf x

#define OFLAG(l)        (1L << ((DWORD)#@l - (DWORD)'a'))
#define EvalExp (PVOID)GetExpression

#define EXACT_MATCH 0xFFFF

int gnIndent = 0; // caller should set and restore this appropriately.

VOID moveBlock(
    PVOID pdst,
    PVOID src,
    DWORD size)
{
    BOOL fSuccess = TRUE;
    ULONG Result;
    
    try {
        if (!ReadMemory((DWORD_PTR)src, pdst, size, &Result)) {
            fSuccess = FALSE;
        }
    } except (EXCEPTION_EXECUTE_HANDLER) {
        //dprintf(pszMoveException, pszExtName);
        fSuccess = FALSE;
    }

    if (!fSuccess) {
        dprintf("moveBlock(%x, %x, %x) failed.\n", pdst, src, size);
    }
}


/***************************************************************************\
* dsoTerminateString
*
* This is used to "parse" the command line. It null-terminates a space
*  delimited string, returns its size and a pointer to the begining
*  of next string
*
* 06/17/96 Created Gerardob
\***************************************************************************/
LPSTR dsoTerminateString(LPSTR psz, PDWORD pdwSize)
{
    LPSTR pszWork = psz;

    while (*pszWork != 0) {
        if (*pszWork == ' ') {
            *pszWork++ = 0;
            break;
        }
        pszWork++;
    }

    *pdwSize = (DWORD)(pszWork - psz);
    if (*pszWork != 0) {
        (*pdwSize)--;
    }

    while ((*pszWork != 0) && (*pszWork == ' ')) {
        pszWork++;
    }

    return pszWork;
}
/***************************************************************************\
* dsoGetOffset
*
* If the highest order bit of psot->dwOffset is set, then the value is a
*  relative offset from the previous field; otherwise, it is the
*  actual field offset from the beginnig of the structure
*
* 06/20/96 Created Gerardob
\***************************************************************************/
UINT dsoGetOffset (PSTRUCTUREOFFSETSTABLE psot)
{
    if (!(psot->dwOffset & 0x80000000)) {
        return psot->dwOffset;
    } else {
        return ((psot->dwOffset & ~0x80000000) + dsoGetOffset(psot - 1));
    }
}
/***************************************************************************\
* dsoGetSize
*
* The field size is calculated by substracting its offset from the next
*  field's offset. If the struct has unions, several "fields" might have
*  the same offset, or a given table entry (i.e., a field) might have an
*  offset value greater than the offset value for the next entry (a union
*  of two structures).
*
* 06/26/96 Created Gerardob
\***************************************************************************/
UINT dsoGetSize (PSTRUCTUREOFFSETSTABLE psot, DWORD dwOffset)
{
    DWORD dwNextFieldOffset;

    do {
        psot++;
        dwNextFieldOffset = dsoGetOffset(psot);
    } while (dwNextFieldOffset <= dwOffset);

    return dwNextFieldOffset - dwOffset;
}
/***************************************************************************\
* dsoGetStruct
*
* 07/03/96 Created Gerardob
\***************************************************************************/
PSTRUCTURESTABLE dsoGetStruct (LPSTR pszStruct, DWORD dwSize)
{
    PSTRUCTURESTABLE pst = gst;

    /*
     * If dwSize is EXACT_MATCH, we try an exact
     * case sensitive match
     */
    if (dwSize == EXACT_MATCH) {
        while (pst->pszName != NULL) {
            if (!strcmp(pszStruct, pst->pszName)) {
                return pst;
            }
            pst++;
        }
        return NULL;
    }
    /*
     * Try an exact case insensitive match
     */
    while (pst->pszName != NULL) {
        if (!_stricmp(pszStruct, pst->pszName)) {
            return pst;
        }
        pst++;
    }

    /*
     * Partial prefix match
     */
    pst = gst;
    while (pst->pszName != NULL) {
        if (!_strnicmp(pszStruct, pst->pszName, dwSize)) {
            return pst;
        }
        pst++;
    }

    return NULL;

}
/***************************************************************************\
* dsoGetField
*
* 07/03/96 Created Gerardob
\***************************************************************************/
PSTRUCTUREOFFSETSTABLE dosGetField (PSTRUCTUREOFFSETSTABLE psot, LPSTR pszField, DWORD dwSize)
{
    PSTRUCTUREOFFSETSTABLE psotFirst = psot;

    /*
     * try an exact match
     */
    while (psot->pszField != NULL) {
        if (!_stricmp(pszField, psot->pszField)) {
            return psot;
        }
        psot++;
    }

    /*
     * Partial prefix match
     */
    psot = psotFirst;
    while (psot->pszField != NULL) {
        if (!_strnicmp(pszField, psot->pszField, dwSize)) {
            return psot;
        }
        psot++;
    }
    return NULL;

}
/***************************************************************************\
* Idso
*
* !dso StructName [FieldName] [Address]
*
* 06/17/96 Created Gerardob
* 05/12/97 MCostea Added bit field support
\***************************************************************************/

#define NFIELDS 2  // per row.

BOOL Idso(DWORD opts, LPSTR pszCmdLine)
{
    BOOL fOneField = FALSE;
    DWORD dwValue, dwSize, dwBytesRead, dwOffset, dwOffsetNext, dwFieldsPerRow, dwMoveSize;
    DWORD dwBuffer [20];  /* Make sure it has an even number of elemnts and at least 4*/
    const DWORD *pcdwLimit = dwBuffer + (sizeof(dwBuffer) / sizeof(*dwBuffer));
    DWORD *pdwValue;
    LPSTR pszField, pszAddress;
    PBYTE pBufferOffset;
    PSTRUCTURESTABLE pst, pstNested;
    PSTRUCTUREOFFSETSTABLE psot;
    PVOID pAddress = NULL;

    int   cBFStart, cBFLength;   /* for printing bit field values: keeps count of field location */
    char* pTmp;
    DWORD dwMask;
    BOOL  fBF;
    int   cBF;                   /* no of dwords this set of bit-fields spread till now */
    int   cchName;               /* length of field name */
    int   nIndent = gnIndent;    /* amount to indent */

    UNREFERENCED_PARAMETER(opts);

    if (pszCmdLine == NULL) {
        return FALSE;
    }

    /*
     * Find the struct table
     */
    pszField = dsoTerminateString(pszCmdLine, &dwSize);
    pst = dsoGetStruct (pszCmdLine, dwSize);
    if (pst == NULL) {
        DsoPrint(("Structure not found: %s\n", pszCmdLine));
        return TRUE;
    }

    /*
     * Got a table
     */
    psot = pst->psot;

    /*
     * If there is another argument, let's assume a field name follows
     */
    if (*pszField != 0) {
        /*
         * Find the field
         */
        pszAddress = dsoTerminateString(pszField, &dwSize);
        psot = dosGetField (psot, pszField, dwSize);

        /*
         * If it didn't find the field and an address was provided, game over.
         * Otherwise, the second parameter might be the address
         */
        if (psot == NULL) {
            if (*pszAddress != 0) {
                DsoPrint(("Field not found: %s. Struct: %s\n", pszField, pst->pszName));
                return TRUE;
            } else {
                pszAddress = pszField;
                /*
                 * Reset psot since this argument was not a field
                 */
                psot = pst->psot;
            }
        } else {
            fOneField = TRUE;
        }
    
        /*
         * Get the pointer to the struct
         */
        if (*pszAddress != 0) {
            pAddress = EvalExp(pszAddress);
            if (pAddress == NULL) {
                /*
                 * EvalExp displayed the error message, so return silently
                 */
                return TRUE;
            }
        }

    } /* if (*pszField != 0) */


    /*
     * If a field name was specified, dump that field only
     * Otherwise, dump the whole table.
     */
    if (fOneField) {
        /*
         * If no address available, just display the field name and offset
         */
        dwOffset = dsoGetOffset(psot);

        DsoPrint(("Structure %s - Size: %#lx\n", pst->pszName, pst->dwSize));

        /*
         * Try to see if the fields are not nested structures
         */
        if (*psot->pszField >= 'A' && *psot->pszField <= 'Z') {
            /*
             * Probably the field is a nested structure
             */
            if (pstNested = dsoGetStruct (psot->pszField, EXACT_MATCH)) {
                DWORD dwNestedOffset = dsoGetOffset(psot);
                char cmdLine[80];
                DsoPrint(("\nNested at offset %03lx: ", dwNestedOffset));
                if (pAddress) {
                    sprintf(cmdLine, "%s %p", psot->pszField, (PBYTE)pAddress + dwNestedOffset);
                    pTmp = cmdLine;
                }
                else {
                    pTmp = psot->pszField;
                }
                return Idso(opts, pTmp);
            }
        }

        DsoPrint(("Field: %s - Offset: %#lx\n", psot->pszField, dwOffset));
        if (pAddress == NULL) {
            return TRUE;
        }

        /*
         * Printing field value
         */

        /*123456789 1*/
        DsoPrint(("Address   Value\n"));

        dwBytesRead = 0;
        dwSize = dsoGetSize(psot, dwOffset);
        /*
         * Print 4 DWORDS per row; one row per loop
         */

        do { /* while ((int)dwSize > 0) */

            /*
             * Read values for next row
             */
            if (4 * sizeof(DWORD) >= dwSize) {
                dwMoveSize = dwSize;
            } else {
                dwMoveSize = 4 * sizeof(DWORD);
            }
            moveBlock(dwBuffer, (PBYTE)pAddress + dwOffset + dwBytesRead, dwMoveSize);
            pBufferOffset = (PBYTE)dwBuffer;

            /*
             * Print the address
             */
            DsoPrint(("%p  ", (DWORD_PTR)((PBYTE)pAddress + dwOffset + dwBytesRead)));
            /*
             * Keep track of bytes read (dwBytesRead) and bytes
             *  remaining to be read (dwSize)
             */
            dwBytesRead += dwMoveSize;
            dwSize -= dwMoveSize;
            /*
             * Print the values, one dword at the time
             */
            while (dwMoveSize >= sizeof(DWORD)) {
                DsoPrint(("%08lx ", *((DWORD *)pBufferOffset)));
                pBufferOffset += sizeof(DWORD);
                dwMoveSize -= sizeof(DWORD);
            }
            /*
             * If less than a DWORD left, zero extend and print a DWORD
             */
            if (dwMoveSize > 0) {
                dwValue = 0;
                memcpy(&dwValue, pBufferOffset, dwMoveSize);
                DsoPrint(("%0*lx", dwMoveSize * 2, dwValue));
            }
            dprintf("\n");

        } while ((int)dwSize > 0);

        return TRUE;

    } /* if (fOneField) */


    /*
     * Printing all the fields.
     */
    if (pAddress != NULL) {
        DsoPrint(("Structure %s %#lx - Size: %#lx", pst->pszName, pAddress, pst->dwSize));
    } else {
        DsoPrint(("Structure %s - Size: %#lx", pst->pszName, pst->dwSize));
    }

    dwOffset = 0;
    pBufferOffset = NULL; /* Forces the local buffer to be loaded */
    dwFieldsPerRow = NFIELDS;
    cBFStart = 0;
    cBF = 0;

    /*
     * Loop through all fields in the table. Print one field per loop
     */

    while (psot->pszField != NULL) {

        /*
         * Print two fields per row
         */
        if (dwFieldsPerRow == NFIELDS) {
            dprintf("\n");
            dwFieldsPerRow = 1;
            cchName = 24 - gnIndent/NFIELDS;
            nIndent = gnIndent;
            // Print("cchName = %d\n", cchName);
        } else {
            dwFieldsPerRow++;
            cchName = 24 - (gnIndent + 1)/NFIELDS;
            nIndent = 0;
            // Print("cchName = %d\n", cchName);
        }

        /*
         * -v functionality
         * Try to see if the fields are not nested structures
         * The naming convention assigns Uppercase names for them
         */
        if (opts & OFLAG(v)) {
            if (*psot->pszField >= 'A' && *psot->pszField <= 'Z') {
                /*
                 * Probably the field is a nested structure
                 */
                if (pstNested = dsoGetStruct (psot->pszField, EXACT_MATCH)) {
                    DWORD dwNestedOffset = dsoGetOffset(psot);
                    char cmdLine[80];
                    DsoPrint(("\nNested at offset %03lx: ", dwNestedOffset));
                    if (pAddress) {
                        sprintf(cmdLine, "%s %p", psot->pszField, (PBYTE)pAddress + dwNestedOffset);
                        pTmp = cmdLine;
                    }
                    else {
                        pTmp = psot->pszField;
                    }
                    Idso(opts, pTmp);
                    dwOffsetNext = dsoGetOffset(psot + 1);
                    dwFieldsPerRow = 0;
                    goto Continue;
                }
            }
        }

        /*
         * If no address provided, Print field name(s) and offset(s) only
         */
        if (pAddress == NULL) {
            DsoPrint(("%03lx %-*.*s", dsoGetOffset(psot),
                      cchName, cchName, psot->pszField));
        } else {
            /*
             * Printing offsets and values.
             *
             * Get the size of the value and max it to one DWORD
             */
            dwOffsetNext = dsoGetOffset(psot + 1);
            if (dwOffsetNext > dwOffset) {
                dwSize = dwOffsetNext - dwOffset;
            } else {
                dwSize = dsoGetSize(psot, dwOffset);
            }
            if (dwSize > sizeof(DWORD)) {
                dwSize = sizeof(DWORD);
            }

            /*
             * Get a pointer to the value in the local buffer
             * If the value is not in the buffer, load it
             */
            pdwValue = (PDWORD)(pBufferOffset + dwOffset);
            if ((pdwValue < dwBuffer) || (pdwValue + dwSize > pcdwLimit)) {
                pBufferOffset = (PBYTE)dwBuffer - dwOffset;
                pdwValue = dwBuffer;

                if (sizeof(dwBuffer) >= pst->dwSize - dwOffset) {
                    dwMoveSize = pst->dwSize - dwOffset;
                } else {
                    dwMoveSize = sizeof(dwBuffer);
                }
                moveBlock((PBYTE)dwBuffer, (PBYTE)pAddress + dwOffset, dwMoveSize);

            }

            /*
             * Copy the value and print it
             */
            dwValue = 0; /* in case size < sizeof(DWORD) */
            memcpy(&dwValue, pdwValue, dwSize);

            /*
             * Deal with bit fields
             */
            fBF = FALSE;
            pTmp = psot->pszField;
            while (*pTmp) {
                if (*pTmp++ == ':') {

                    fBF = TRUE;
                    while ((*pTmp == ' ') || (*pTmp == '\t')) {     /* skip white spaces */
                        ++pTmp;
                    }
                    cBFLength = *(pTmp++) - '0';      /* now get the bit size, maybe 2 digits */
                    if ((*pTmp >= '0') && (*pTmp <= '9'))
                        cBFLength = cBFLength*10 + (*pTmp - '0');

                    if (cBFStart == 0) {
                        DsoPrint(("(%03lx) %08lx BIT FIELDS\n", dwOffset, dwValue));
                        dwFieldsPerRow = 1;
                    }
                    else if (cBFStart >= 8*sizeof(DWORD)) {   /* check for multi-dword fields */
                        cBF ++;
                        cBFStart %= 8*sizeof(DWORD);
                    }

                    dwMask = (1L << cBFLength) - 1;
                    dwMask <<= cBFStart;
                    /* print byte offset and the bit offset inside it */
                    DsoPrint(("(%03lx) (%d)   %-2x %-*.*s", dwOffset + cBF*sizeof(DWORD) + cBFStart/8, cBFStart & 7,
                           (dwMask & dwValue) >> cBFStart,
                            cchName, cchName, psot->pszField));
                    cBFStart += cBFLength;
                    cBFLength = 0;
                    break;
                }
            }
            if (!fBF) {
                int width = 8;
                if (dwSize == sizeof(BYTE)) {
                    dwValue &= 0xff;
                    width = 2;
                } else if (dwSize == sizeof(WORD)) {
                    dwValue &= 0xffff;
                    width = 4;
                }
                DsoPrint(("(%03lx) %*s%0*lx %-*.*s", dwOffset, 8 - width, "", width, dwValue,
                          cchName, cchName, psot->pszField));
                cBFStart = 0;
                cBF = 0;
            }

        } /* if (pAddress == NULL) */

Continue:
        dwOffset = dwOffsetNext;
        psot++;

    } /* while (psot->pszField != NULL) */

    dprintf("\n");

    return TRUE;
}

DECLARE_API( psdso )
{
    LPSTR pszCmdLine = (LPSTR)args;
    DWORD opts = 0;

    Idso(opts, pszCmdLine);
}
