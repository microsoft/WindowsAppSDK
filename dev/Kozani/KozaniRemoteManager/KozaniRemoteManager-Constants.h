// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// Rely on _STRINGIZE(x) in yvals_core.h
#ifndef _STRINGIZE
#define _STRINGIZEX(x)  #x
#define _STRINGIZE(x)   _STRINGIZEX(x)
#endif

#define PR_KOZANIREMOTEMANAGER_LIBID_UUID        0f1e1fe3-65df-490a-be16-211c04a41e25

#define PR_KOZANIREMOTEMANAGER_CLSID_UUID        17b65d52-f4a5-4ea6-9e62-031168b05017
#define PR_KOZANIREMOTEMANAGER_CLSID_STRING      _STRINGIZE(PR_KOZANIREMOTEMANAGER_CLSID_UUID)
#define PR_KOZANIREMOTEMANAGER_CLSID_GUID        0x17b65d52, 0xf4a5, 0x4ea6, { 0x9e, 0x62, 0x03, 0x11, 0x68, 0xb0, 0x50, 0x17 }

#if defined(WINDOWSAPPSDK_BUILD_PIPELINE) && (WINDOWSAPPSDK_BUILD_PIPELINE == 1)
#include "KozaniRemoteManager-Override.h"
#endif
