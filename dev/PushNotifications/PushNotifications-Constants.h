// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

// Rely on _STRINGIZE(x) in yvals_core.h
#ifndef _STRINGIZE
#define _STRINGIZEX(x)  #x
#define _STRINGIZE(x)   _STRINGIZEX(x)
#endif

#define PR_PUSHNOTIFICATIONS_CLSID_UUID             8FCFB82B-DB93-4E1D-9008-76D768CEB9EA
#define PR_PUSHNOTIFICATIONS_CLSID_UUID_STRING      _STRINGIZE(PR_PUSHNOTIFICATIONS_CLSID_UUID)

#if defined(PROJECTREUNION_BUILD_PIPELINE) && (PROJECTREUNION_BUILD_PIPELINE == 1)
#include "PushNotifications-Override.h"
#endif
