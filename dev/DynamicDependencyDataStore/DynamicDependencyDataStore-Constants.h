// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if defined(PROJECTREUNION_PIPELINE_BUILD) && (PROJECTREUNION_PIPELINE_BUILD == 1)
#include "DynamicDependencyDataStore-Constants-Override.h"
#else
#define PR_DYNDEP_LIBID_UUID                1BF712E5-41ED-46a5-8402-2D40725F691E
#define PR_DYNDEP_DATASTORE_CLSID_UUID      D1AD16C7-EC59-4765-BF95-9A243EB00507
#define PR_DYNDEP_DATASTORE_CLSID_STRING    "D1AD16C7-EC59-4765-BF95-9A243EB00507"
#endif
