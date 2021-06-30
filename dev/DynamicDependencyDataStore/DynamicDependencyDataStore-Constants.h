// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

// Rely on _STRINGIZE(x) in yvals_core.h
#ifndef _STRINGIZE
#define _STRINGIZEX(x)  #x
#define _STRINGIZE(x)   _STRINGIZEX(x)
#endif

#define PR_DYNDEP_LIBID_UUID                1BF712E5-41ED-46a5-8402-2D40725F691E

#define PR_DYNDEP_DATASTORE_CLSID_UUID      D1AD16C7-EC59-4765-BF95-9A243EB00507
#define PR_DYNDEP_DATASTORE_CLSID_STRING    _STRINGIZE(PR_DYNDEP_DATASTORE_CLSID_UUID)

#if defined(PROJECTREUNION_BUILD_PIPELINE) && (PROJECTREUNION_BUILD_PIPELINE == 1)
#include "DynamicDependency-Override.h"
#endif
