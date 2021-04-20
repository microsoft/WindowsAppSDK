// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if defined(PROJECTREUNION_BUILD_PIPELINE) && (PROJECTREUNION_BUILD_PIPELINE == 1)
#include "DynamicDependencyLifetimeManager-Constants-Override.h"
#else
#define PR_DYNDEP_LIBID_UUID                        1BF712E5-41ED-46a5-8402-2D40725F691E
#define PR_DYNDEP_LIFETIMEMANAGER_CLSID_UUID        32E7CF70-038C-429a-BD49-88850F1B4A11
#define PR_DYNDEP_LIFETIMEMANAGER_CLSID_STRING      "32E7CF70-038C-429a-BD49-88850F1B4A11"
#define PR_DYNDEP_LIFETIMEMANAGER_CLSID_GUID        0x32e7cf70, 0x038c, 0x429a, { 0xbd, 0x49, 0x88, 0x85, 0x0f, 0x1b, 0x4a, 0x11 }
#endif
