// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// Rely on _STRINGIZE(x) in yvals_core.h
#ifndef _STRINGIZE
#define _STRINGIZEX(x)  #x
#define _STRINGIZE(x)   _STRINGIZEX(x)
#endif

#define PR_KOZANIMANAGER_LIBID_UUID        b3f7f4b4-6c5b-4c2e-bc92-bd29521c7834

#define PR_KOZANIMANAGER_CLSID_UUID        18ee7fea-022e-4bda-956a-232592c14988
#define PR_KOZANIMANAGER_CLSID_STRING      _STRINGIZE(PR_KOZANIMANAGER_CLSID_UUID)
#define PR_KOZANIMANAGER_CLSID_GUID        0x18ee7fea, 0x022e, 0x4bda, { 0x95, 0x6a, 0x23, 0x25, 0x92, 0xc1, 0x49, 0x88 }

#if defined(WINDOWSAPPSDK_BUILD_PIPELINE) && (WINDOWSAPPSDK_BUILD_PIPELINE == 1)
#include "KozaniManager-Override.h"
#endif
