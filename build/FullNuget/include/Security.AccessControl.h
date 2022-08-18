// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include <Windows.h>

struct AppContainerNameAndAccess
{
    PCWSTR appContainerName;
    UINT32 accessMask;
};

STDAPI GetSecurityDescriptorForAppContainerNames(
    UINT32 accessRequestCount,
    _In_reads_(accessRequestCount) const AppContainerNameAndAccess* accessRequests,
    _In_opt_ PSID principal,
    UINT32 principalAccessMask,
    _Outptr_ PSECURITY_DESCRIPTOR* securityDescriptor,
    _Out_opt_ UINT32* securityDescriptorSize
);
