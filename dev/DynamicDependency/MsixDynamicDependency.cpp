// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "msixdynamicdependency.h"

#include "PackageDependency.h"
#include "PackageDependencyManager.h"
#include "PackageGraph.h"

STDAPI MddTryCreatePackageDependency(
    PSID user,
    _In_ PCWSTR packageFamilyName,
    PACKAGE_VERSION minVersion,
    MddPackageDependencyProcessorArchitectures packageDependencyProcessorArchitectures,
    MddPackageDependencyLifetimeKind lifetimeKind,
    PCWSTR lifetimeArtifact,
    MddCreatePackageDependencyOptions options,
    _Outptr_result_maybenull_ PWSTR* packageDependencyId) noexcept try
{
    MddCore::PackageDependencyManager::CreatePackageDependency(user, packageFamilyName, minVersion, packageDependencyProcessorArchitectures, lifetimeKind, lifetimeArtifact, options, packageDependencyId);
    return S_OK;
}
CATCH_RETURN();

STDAPI_(void) MddDeletePackageDependency(
    _In_ PCWSTR packageDependencyId) noexcept
{
    MddCore::PackageDependencyManager::DeletePackageDependency(packageDependencyId);
}

STDAPI MddAddPackageDependency(
    _In_ PCWSTR packageDependencyId,
    INT32 rank,
    MddAddPackageDependencyOptions options,
    _Out_ MDD_PACKAGEDEPENDENCY_CONTEXT* packageDependencyContext,
    _Outptr_opt_result_maybenull_ PWSTR* packageFullName) noexcept try
{
    *packageDependencyContext = nullptr;
    if (packageFullName)
    {
        *packageFullName = nullptr;
    }

    auto lock(MddCore::AcquirePackageGraphLock());

    wil::unique_process_heap_string fullName;
    RETURN_IF_FAILED(MddCore::ResolvePackageDependency(packageDependencyId, options, fullName));
    MDD_PACKAGEDEPENDENCY_CONTEXT context{};
    RETURN_IF_FAILED(MddCore::AddToPackageGraph(fullName.get(), rank, options, context));

    *packageDependencyContext = context;
    if (packageFullName)
    {
        *packageFullName = fullName.release();
    }
    return S_OK;
}
CATCH_RETURN();

STDAPI_(void) MddRemovePackageDependency(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext) noexcept
{
    (void)LOG_IF_FAILED(MddCore::RemoveFromPackageGraph(packageDependencyContext));
}

STDAPI MddGetResolvedPackageFullNameForPackageDependency(
    _In_ PCWSTR packageDependencyId,
    _Outptr_result_maybenull_ PWSTR* packageFullName) noexcept try
{
    *packageFullName = nullptr;

    wil::unique_process_heap_string fullName;
    RETURN_IF_FAILED(MddCore::ResolvePackageDependency(packageDependencyId, fullName));

    *packageFullName = fullName.release();
    return S_OK;
}
CATCH_RETURN();
