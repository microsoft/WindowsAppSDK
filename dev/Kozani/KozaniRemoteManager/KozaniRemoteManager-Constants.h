// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// Rely on _STRINGIZE(x) in yvals_core.h
#ifndef _STRINGIZE
#define _STRINGIZEX(x)  #x
#define _STRINGIZE(x)   _STRINGIZEX(x)
#endif

#define PR_KOZANIREMOTEMANAGER_LIBID_UUID        eace4145-0a4e-45af-a9da-f96e32cd935f

#define PR_KOZANIREMOTEMANAGER_CLSID_UUID        f30462b7-602b-4626-9f8b-dfc07317720f
#define PR_KOZANIREMOTEMANAGER_CLSID_STRING      _STRINGIZE(PR_KOZANIREMOTEMANAGER_CLSID_UUID)
#define PR_KOZANIREMOTEMANAGER_CLSID_GUID        0xf30462b7, 0x602b, 0x4626, { 0x9f, 0x8b, 0xdf, 0xc0, 0x73, 0x17, 0x72, 0x0f }

#if defined(WINDOWSAPPSDK_BUILD_PIPELINE) && (WINDOWSAPPSDK_BUILD_PIPELINE == 1)
#include "KozaniRemoteManager-Override.h"
#endif
