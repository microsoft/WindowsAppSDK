#pragma once

#include <Windows.h>
#include <stdint.h>

struct AppContainerAccess
{
    PCWSTR appContainerName;
    uint32_t accessMask;
};

STDAPI GetSecurityDescriptorForAppContainerNames(
    uint32_t countOfAppContainerNames,
    _In_reads_(countOfAppContainerNames)
    const AppContainerAccess* appAccess,
    uint32_t userAccessMask,
    _Outptr_
    PSECURITY_DESCRIPTOR* securityDescriptor
);
