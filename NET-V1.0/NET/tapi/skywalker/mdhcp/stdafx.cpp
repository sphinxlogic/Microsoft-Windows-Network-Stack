/*

Copyright (c) 1998-1999  Microsoft Corporation

Module Name:
    stdafx.cpp 

Abstract:
    source file that includes just the standard includes
    stdafx.pch will be the pre-compiled header
    stdafx.obj will contain the pre-compiled type information


Author:

*/

#include "stdafx.h"

#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#include <statreg.cpp>
#endif

#include <atlimpl.cpp>
