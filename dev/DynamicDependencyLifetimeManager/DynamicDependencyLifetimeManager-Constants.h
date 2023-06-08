// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// Rely on _STRINGIZE(x) in yvals_core.h
#ifndef _STRINGIZE
#define _STRINGIZEX(x)  #x
#define _STRINGIZE(x)   _STRINGIZEX(x)
#endif

#define PR_DYNDEP_LIBID_UUID                        1BF712E5-41ED-46a5-8402-2D40725F691E

#define PR_DYNDEP_LIFETIMEMANAGER_CLSID_UUID        32E7CF70-038C-429a-BD49-88850F1B4A11
#define PR_DYNDEP_LIFETIMEMANAGER_CLSID_STRING      _STRINGIZE(PR_DYNDEP_LIFETIMEMANAGER_CLSID_UUID)
#define PR_DYNDEP_LIFETIMEMANAGER_CLSID_GUID        0x32e7cf70, 0x038c, 0x429a, { 0xbd, 0x49, 0x88, 0x85, 0x0f, 0x1b, 0x4a, 0x11 }

#if defined(WINDOWSAPPSDK_BUILD_PIPELINE) && (WINDOWSAPPSDK_BUILD_PIPELINE == 1)
#include "DynamicDependency-Override.h"
#endif
