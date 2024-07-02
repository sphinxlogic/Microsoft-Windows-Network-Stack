/*++

Copyright(c) 1998,99  Microsoft Corporation

Module Name:

    univ.c

Abstract:

    Windows Load Balancing Service (WLBS)
    Driver - global variables

Author:

    kyrilf

--*/


#include <stdlib.h>
#include <ndis.h>

#include "univ.h"
#include "wlbsparm.h"

#if defined (NLB_TCP_NOTIFICATION)
#include <ntddnlb.h>
#endif

/* GLOBALS */

/* The global teaming list spin lock. */
NDIS_SPIN_LOCK          univ_bda_teaming_lock;
WCHAR                   empty_str [] = L"";
UNIV_IOCTL_HDLR         univ_ioctl_hdlr = NULL;
PVOID                   univ_driver_ptr = NULL;
NDIS_HANDLE             univ_driver_handle = NULL;
NDIS_HANDLE             univ_wrapper_handle = NULL;
NDIS_HANDLE             univ_prot_handle = NULL;
NDIS_HANDLE             univ_ctxt_handle = NULL;
NDIS_SPIN_LOCK          univ_bind_lock;
ULONG                   univ_changing_ip = 0;
NDIS_HANDLE             univ_device_handle = NULL;
PDEVICE_OBJECT          univ_device_object = NULL;
ULONG                   univ_tcp_cleanup = TRUE;
#if defined (NLB_TCP_NOTIFICATION)
ULONG                   univ_notification = NLB_CONNECTION_CALLBACK_TCP;
PCALLBACK_OBJECT        univ_tcp_callback_object = NULL;
PVOID                   univ_tcp_callback_function = NULL;
PCALLBACK_OBJECT        univ_alternate_callback_object = NULL;
PVOID                   univ_alternate_callback_function = NULL;
#endif
NDIS_PHYSICAL_ADDRESS   univ_max_addr = NDIS_PHYSICAL_ADDRESS_CONST (-1,-1);
NDIS_MEDIUM             univ_medium_array [UNIV_NUM_MEDIUMS] = UNIV_MEDIUMS;
UNICODE_STRING          DriverEntryRegistryPath;
PWCHAR                  univ_reg_path = NULL;
ULONG                   univ_reg_path_len = 0;
NDIS_OID                univ_oids [UNIV_NUM_OIDS] =
                                       { OID_GEN_SUPPORTED_LIST,
                                         OID_GEN_HARDWARE_STATUS,
                                         OID_GEN_MEDIA_SUPPORTED,
                                         OID_GEN_MEDIA_IN_USE,
                                         OID_GEN_MAXIMUM_LOOKAHEAD,
                                         OID_GEN_MAXIMUM_FRAME_SIZE,
                                         OID_GEN_LINK_SPEED,
                                         OID_GEN_TRANSMIT_BUFFER_SPACE,
                                         OID_GEN_RECEIVE_BUFFER_SPACE,
                                         OID_GEN_TRANSMIT_BLOCK_SIZE,
                                         OID_GEN_RECEIVE_BLOCK_SIZE,
                                         OID_GEN_VENDOR_ID,
                                         OID_GEN_VENDOR_DESCRIPTION,
                                         OID_GEN_CURRENT_PACKET_FILTER,
                                         OID_GEN_CURRENT_LOOKAHEAD,
                                         OID_GEN_DRIVER_VERSION,
                                         OID_GEN_MAXIMUM_TOTAL_SIZE,
                                         OID_GEN_PROTOCOL_OPTIONS,
                                         OID_GEN_MAC_OPTIONS,
                                         OID_GEN_MEDIA_CONNECT_STATUS,
                                         OID_GEN_MAXIMUM_SEND_PACKETS,
                                         OID_GEN_VENDOR_DRIVER_VERSION,
                                         OID_GEN_XMIT_OK,
                                         OID_GEN_RCV_OK,
                                         OID_GEN_XMIT_ERROR,
                                         OID_GEN_RCV_ERROR,
                                         OID_GEN_RCV_NO_BUFFER,
                                         OID_GEN_DIRECTED_BYTES_XMIT,
                                         OID_GEN_DIRECTED_FRAMES_XMIT,
                                         OID_GEN_MULTICAST_BYTES_XMIT,
                                         OID_GEN_MULTICAST_FRAMES_XMIT,
                                         OID_GEN_BROADCAST_BYTES_XMIT,
                                         OID_GEN_BROADCAST_FRAMES_XMIT,
                                         OID_GEN_DIRECTED_BYTES_RCV,
                                         OID_GEN_DIRECTED_FRAMES_RCV,
                                         OID_GEN_MULTICAST_BYTES_RCV,
                                         OID_GEN_MULTICAST_FRAMES_RCV,
                                         OID_GEN_BROADCAST_BYTES_RCV,
                                         OID_GEN_BROADCAST_FRAMES_RCV,
                                         OID_GEN_RCV_CRC_ERROR,
                                         OID_GEN_TRANSMIT_QUEUE_LENGTH,
                                         OID_802_3_PERMANENT_ADDRESS,
                                         OID_802_3_CURRENT_ADDRESS,
                                         OID_802_3_MULTICAST_LIST,
                                         OID_802_3_MAXIMUM_LIST_SIZE,
                                         OID_802_3_MAC_OPTIONS,
                                         OID_802_3_RCV_ERROR_ALIGNMENT,
                                         OID_802_3_XMIT_ONE_COLLISION,
                                         OID_802_3_XMIT_MORE_COLLISIONS,
                                         OID_802_3_XMIT_DEFERRED,
                                         OID_802_3_XMIT_MAX_COLLISIONS,
                                         OID_802_3_RCV_OVERRUN,
                                         OID_802_3_XMIT_UNDERRUN,
                                         OID_802_3_XMIT_HEARTBEAT_FAILURE,
                                         OID_802_3_XMIT_TIMES_CRS_LOST,
                                         OID_802_3_XMIT_LATE_COLLISIONS };


/* PROCEDURES */


VOID Univ_ndis_string_alloc (
    PNDIS_STRING            string,
    PCHAR                   src)
{
    PWCHAR                  tmp;


    /* allocate enough space for the string */

    string -> Length = strlen (src) * sizeof (WCHAR);
    string -> MaximumLength = string -> Length + sizeof (WCHAR);

    NdisAllocateMemoryWithTag (& (string -> Buffer), string -> MaximumLength,
                               UNIV_POOL_TAG);

    if (string -> Buffer == NULL)
    {
        string -> Length = 0;
        string -> MaximumLength = 0;
        return;
    }

    /* copy characters */

    tmp = string -> Buffer;

    while (* src != '\0')
    {
        * tmp = (WCHAR) (* src);
        src ++;
        tmp ++;
    }

    * tmp = UNICODE_NULL;

} /* end Univ_ndis_string_free */


VOID Univ_ndis_string_free (
    PNDIS_STRING            string)
{
    if (string -> Buffer == NULL)
        return;

    /* free memory */

    NdisFreeMemory (string -> Buffer, string -> MaximumLength, 0);
    string -> Length = 0;
    string -> MaximumLength = 0;

} /* end Univ_ndis_string_free */


VOID Univ_ansi_string_alloc (
    PANSI_STRING            string,
    PWCHAR                  src)
{
    PCHAR                   tmp;
    PWCHAR                  wtmp;
    USHORT                  len;


    /* compute length of the string in characters */

    wtmp = src;
    len = 0;

    while (* wtmp != UNICODE_NULL)
    {
        len ++;
        wtmp ++;
    }

    /* allocate enough space for the string */

    string -> Length = len;
    string -> MaximumLength = len + sizeof (CHAR);

    NdisAllocateMemoryWithTag (& (string -> Buffer), string -> MaximumLength,
                               UNIV_POOL_TAG);

    if (string -> Buffer == NULL)
    {
        string -> Length = 0;
        string -> MaximumLength = 0;
        return;
    }

    /* copy characters */

    tmp = string -> Buffer;

    while (* src != '\0')
    {
        * tmp = (CHAR) (* src);
        src ++;
        tmp ++;
    }

    * tmp = 0;

} /* end Univ_ansi_string_free */


VOID Univ_ansi_string_free (
    PANSI_STRING        string)
{
    if (string == NULL)
        return;

    /* free memory */

    NdisFreeMemory (string -> Buffer, string -> MaximumLength, 0);
    string -> Length = 0;
    string -> MaximumLength = 0;

} /* end Univ_ansi_string_free */


ULONG   Univ_str_to_ulong (
    PULONG          retp,
    PWCHAR          start_ptr,
    PWCHAR *        end_ptr,
    ULONG           width,
    ULONG           base)
{
    PWCHAR          ptr;
    WCHAR           c;
    ULONG           number = 0;
    ULONG           val, pos = 0;


    /* check base */

    if (base != 2 && base != 8 && base != 10 && base != 16)
    {
        if (end_ptr != NULL)
            * end_ptr = start_ptr;

        return FALSE;
    }

    /* skip space */

    ptr = start_ptr;
    number = 0;

    while (* ptr == 0x20)
        ptr ++;

    /* extract digits and build the number */

    while (pos < width)
    {
        c = * ptr;

        if (0x30 <= c && c <= 0x39)
            val = c - 0x30;
        else if (0x41 <= c && c <= 0x46)
            val = c - 0x41 + 0xa;
        else if (0x61 <= c && c <= 0x66)
            val = c - 0x61 + 0xa;
        else
            break;

        if (val >= base)
            break;

        number = number * base + val;

        ptr ++;
        pos ++;
    }

    /* makre sure we extracted something */

    if (pos == 0)
    {
        ptr = start_ptr;
        * retp = 0;
        return FALSE;
    }

    /* return resulting number */

    if (end_ptr != NULL)
        * end_ptr = ptr;

    * retp = number;
    return TRUE;

} /* end Univ_str_to_ulong */


PWCHAR Univ_ulong_to_str (
    ULONG           val,
    PWCHAR          buf,
    ULONG           base)
{
    ULONG           dig;
    PWCHAR          p, sav;
    WCHAR           tmp;


    /* check base */

    if (base != 2 && base != 8 && base != 10 && base != 16)
    {
        buf [0] = 0;
        return buf;
    }

    /* extract digits from the number and output to string */

    p = buf;

    do
    {
        /* get next digit */

        dig = (ULONG) (val % base);
        val /= base;

        /* convert to ascii and store */

        if (dig > 9)
            * p = (CHAR) (dig - 10 + L'a');
        else
            * p = (CHAR) (dig + L'0');

        p ++;
    }
    while (val > 0);

    * p = 0;
    sav = p;

    /* swap the characters, since operation above creates inverted string */

    p --;

    do
    {
        tmp = * p;
        * p = * buf;
        * buf = tmp;
        p --; buf ++;
    }
    while (buf < p);       /* repeat until halfway */

    return sav;

} /* end Univ_ulong_to_str */

void Univ_ip_addr_ulong_to_str (
    ULONG           val,
    PWCHAR          buf)
{
    int             idx;
    PWCHAR          str_begin, str_end, cur_str;
    PUCHAR          ptr;
    WCHAR           tmp;
    UCHAR           cur_val;

    // Access the ip address in the dword as an array of bytes
    ptr = (PUCHAR)&val;

    cur_str = str_begin = buf;
    
    for (idx = 0 ; idx < 4 ; idx++) 
    {
        // Get current byte
        cur_val = *ptr++;

        // Convert current byte to string
        do
        {
            *cur_str = (cur_val % 10) + L'0';
            cur_val /= 10;
            cur_str++;
        }
        while (cur_val > 0);

        // Swap the characters, since operation above creates inverted string. 
        // There could atmost be three characters ("255" is the highest), 
        // so, it is enough if we swap once. In other words, a "if" will do 
        // in the place of a "while" in the below loop.
        str_end = cur_str - 1;
        if (str_begin < str_end)       
        {
            tmp        = *str_end;
            *str_end   = *str_begin;
            *str_begin = tmp;
        }

        *cur_str = L'.';

        // Position the destination string to fill in the next byte as a string
        str_begin = ++cur_str;
    }

    // Overwrite the last '.' with the Null terminator
    *(cur_str - 1) = UNICODE_NULL;

    return; 

} /* end Univ_ip_addr_ulong_to_str */

BOOL Univ_equal_unicode_string (PWSTR string1, PWSTR string2, ULONG length)
{
    /* Loop until "length" characters have been compared. */
    while (length > 0) {
        /* If the two characters are not equal, then check to see if they only
           differ by case - if so, its ok, if not, the strings are not equal. */
        if (*string1 != *string2) {
            /* Convert uppercase letters to a lowercase comparison: A - Z */
            if ((*string1 >= 65) && (*string1 <= 90)) {
                if (*string2 != (*string1 + 32)) return FALSE;
            /* Convert lowercase letters to an uppercase comparison: a - z */
            } else if ((*string1 >= 97) && (*string1 <= 122)) {
                if (*string2 != (*string1 - 32)) return FALSE;
            /* If the character is not a letter, then it must match exactly - fail. */
            } else {
                return FALSE;
            }
        }
        
        /* Increment the string pointers and decrement the 
           number of characters left to check. */
        string1++;
        string2++;
        length--;
    }
    
    /* If we got this far, the strings match. */
    return TRUE;
}
