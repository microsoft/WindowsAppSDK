// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>

#include <msixdynamicdependency.h>

STDAPI MddTryCreatePackageDependency(
    PSID /*user*/,
    _In_ PCWSTR /*packageFamilyName*/,
    PACKAGE_VERSION /*minVersion*/,
    MddPackageDependencyProcessorArchitectures /*packageDependencyProcessorArchitectures*/,
    MddPackageDependencyLifetimeKind /*lifetimeKind*/,
    PCWSTR /*lifetimeArtifact*/,
    MddCreatePackageDependencyOptions /*options*/,
    _Outptr_result_maybenull_ PWSTR* packageDependencyId)
{
    *packageDependencyId = nullptr;
    RETURN_WIN32(ERROR_NOT_SUPPORTED);
}

STDAPI_(void) MddDeletePackageDependency(
    _In_ PCWSTR /*packageDependencyId*/)
{
}

STDAPI MddAddPackageDependency(
    _In_ PCWSTR /*packageDependencyId*/,
    INT32 /*rank*/,
    MddAddPackageDependencyOptions /*options*/,
    _Out_ MDD_PACKAGEDEPENDENCY_CONTEXT* packageDependencyContext,
    _Outptr_opt_result_maybenull_ PWSTR* packageFullName)
{
    *packageDependencyContext = nullptr;
    if (packageFullName)
    {
        *packageFullName = nullptr;
    }
    RETURN_WIN32(ERROR_NOT_SUPPORTED);
}

STDAPI_(void) MddRemovePackageDependency(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT /*packageDependencyContext*/)
{
}

STDAPI MddGetResolvedPackageFullNameForPackageDependency(
    _In_ PCWSTR /*packageDependencyId*/,
    _Outptr_result_maybenull_ PWSTR* packageFullName)
{
    *packageFullName = nullptr;
    RETURN_WIN32(ERROR_NOT_SUPPORTED);
}
