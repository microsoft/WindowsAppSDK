// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// Rely on _STRINGIZE(x) in yvals_core.h
#ifndef _STRINGIZE
#define _STRINGIZEX(x)  #x
#define _STRINGIZE(x)   _STRINGIZEX(x)
#endif

#define PR_KOZANIREMOTEMANAGER_LIBID_UUID        55caef43-e183-4419-b43e-7244ddc29264

#define PR_KOZANIREMOTEMANAGER_CLSID_UUID        a55bcc68-d2d2-4135-9f56-79224326f7e8
#define PR_KOZANIREMOTEMANAGER_CLSID_STRING      _STRINGIZE(PR_KOZANIREMOTEMANAGER_CLSID_UUID)
#define PR_KOZANIREMOTEMANAGER_CLSID_GUID        0xa55bcc68, 0xd2d2, 0x4135, { 0x9f, 0x56, 0x79, 0x22, 0x43, 0x26, 0xf7, 0xe8 }

#if defined(WINDOWSAPPSDK_BUILD_PIPELINE) && (WINDOWSAPPSDK_BUILD_PIPELINE == 1)
#include "KozaniRemoteManager-Override.h"
#endif
