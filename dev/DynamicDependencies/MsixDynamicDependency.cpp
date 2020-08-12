// Copyright (C) Microsoft. All rights reserved.

#include <pch.h>

#include <msixdynamicdependency.h>

STDAPI MddPinPackageDependency(
    PSID /*user*/,
    _In_ PCWSTR /*packageFamilyName*/,
    PACKAGE_VERSION /*minVersion*/,
    MddPackageDependencyProcessorArchitectures /*packageDependencyProcessorArchitectures*/,
    MddPinPackageDependencyLifetimeKind /*lifetimeKind*/,
    PCWSTR /*lifetimeArtifact*/,
    MddPinPackageDependencyFlags /*flags*/,
    _Outptr_result_maybenull_ PWSTR* packageDependencyId)
{
    *packageDependencyId = nullptr;
    RETURN_WIN32(ERROR_NOT_SUPPORTED);
}

STDAPI_(void) MddUnpinPackageDependency(
    _In_ PCWSTR /*packageDependencyId*/)
{
}

STDAPI MddAddPackageDependency(
    _In_ PCWSTR /*packageDependencyId*/,
    INT32 /*rank*/,
    MddAddPackageDependencyFlags /*flags*/,
    _Out_ MDD_PACKAGEDEPENDENCY_CONTEXT* packageDependencyContext,
    _Outptr_opt_result_maybenull_ PWSTR* packageFullName)
{
    *packageDependencyContext = nullptr;
    *packageFullName = nullptr;
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

STDAPI_(BOOL) MddArePackageDependencyIdsEquivalent(
    _In_ PCWSTR /*packageDependencyId1*/,
    _In_ PCWSTR /*packageDependencyId2*/)
{
    return FALSE;
}

STDAPI_(BOOL) MddArePackageDependencyContextsEquivalent(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT /*context1*/,
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT /*context2*/)
{
    return FALSE;
}
