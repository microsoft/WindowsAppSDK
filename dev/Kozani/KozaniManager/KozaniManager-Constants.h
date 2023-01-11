// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// Rely on _STRINGIZE(x) in yvals_core.h
#ifndef _STRINGIZE
#define _STRINGIZEX(x)  #x
#define _STRINGIZE(x)   _STRINGIZEX(x)
#endif

#define PR_KOZANIMANAGER_LIBID_UUID        a263ef01-804d-4c26-93e2-2884fea48e49

#define PR_KOZANIMANAGER_CLSID_UUID        c20b68c2-a449-423c-aaeb-e5713fe30887
#define PR_KOZANIMANAGER_CLSID_STRING      _STRINGIZE(PR_KOZANIMANAGER_CLSID_UUID)
#define PR_KOZANIMANAGER_CLSID_GUID        0xc20b68c2, 0xa449, 0x423c, { 0xaa, 0xeb, 0xe5, 0x71, 0x3f, 0xe3, 0x08, 0x87 }

#if defined(WINDOWSAPPSDK_BUILD_PIPELINE) && (WINDOWSAPPSDK_BUILD_PIPELINE == 1)
#include "KozaniManager-Override.h"
#endif
