// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// Rely on _STRINGIZE(x) in yvals_core.h
#ifndef _STRINGIZE
#define _STRINGIZEX(x)  #x
#define _STRINGIZE(x)   _STRINGIZEX(x)
#endif

#define PR_KOZANIMANAGER_LIBID_UUID        29acee21-e36b-4bd5-bf7d-ad54ba28c954

#define PR_KOZANIMANAGER_CLSID_UUID        b7034343-8d78-4d21-81ca-7a6c1c961c17
#define PR_KOZANIMANAGER_CLSID_STRING      _STRINGIZE(PR_KOZANIMANAGER_CLSID_UUID)
#define PR_KOZANIMANAGER_CLSID_GUID        0xb7034343, 0x8d78, 0x4d21, { 0x81, 0xca, 0x7a, 0x6c, 0x1c, 0x96, 0x1c, 0x17 }

#if defined(WINDOWSAPPSDK_BUILD_PIPELINE) && (WINDOWSAPPSDK_BUILD_PIPELINE == 1)
#include "KozaniManager-Override.h"
#endif
