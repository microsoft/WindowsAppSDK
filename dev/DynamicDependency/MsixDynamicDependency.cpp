// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "msixdynamicdependency.h"

#include "PackageGraph.h"

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
    _In_ PCWSTR packageDependencyId,
    INT32 rank,
    MddAddPackageDependencyOptions options,
    _Out_ MDD_PACKAGEDEPENDENCY_CONTEXT* packageDependencyContext,
    _Outptr_opt_result_maybenull_ PWSTR* packageFullName)
{
    *packageDependencyContext = nullptr;
    if (packageFullName)
    {
        *packageFullName = nullptr;
    }

    auto lock(AcquirePackageGraphLock());

    wil::unique_process_heap_string fullName;
    RETURN_IF_FAILED(ResolvePackageDependency(packageDependencyId, options, fullName));
    MDD_PACKAGEDEPENDENCY_CONTEXT context{};
    RETURN_IF_FAILED(AddToPackageGraph(fullName.get(), rank, options, context));

    *packageDependencyContext = context;
    if (packageFullName)
    {
        *packageFullName = fullName.release();
    }

    RETURN_WIN32(ERROR_NOT_SUPPORTED);
}

STDAPI_(void) MddRemovePackageDependency(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext)
{
    (void)LOG_IF_FAILED(RemoveFromPackageGraph(packageDependencyContext));
}

STDAPI MddGetResolvedPackageFullNameForPackageDependency(
    _In_ PCWSTR packageDependencyId,
    _Outptr_result_maybenull_ PWSTR* packageFullName)
{
    *packageFullName = nullptr;

    wil::unique_process_heap_string fullName;
    RETURN_IF_FAILED(ResolvePackageDependency(packageDependencyId, fullName));

    *packageFullName = fullName.release();
    return S_OK;
}
