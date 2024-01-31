// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "msixdynamicdependency.h"

#include "MddDetourPackageGraph.h"
#include "PackageDependencyManager.h"
#include "PackageGraphManager.h"

#include "MddWin11.h"

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
    *packageDependencyId = nullptr;

    // Use the Win11 APIs if available (instead of Detour'ing to our own implementation)
    if (MddCore::Win11::IsSupported())
    {
        RETURN_IF_FAILED(MddCore::Win11::TryCreatePackageDependency(user, packageFamilyName,
            minVersion, packageDependencyProcessorArchitectures, lifetimeKind, lifetimeArtifact,
            options, packageDependencyId));
        return S_OK;
    }

    // WinAppSDK's Dynamic Dependencies requires a non-packaged process
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), AppModel::Identity::IsPackagedProcess());

    MddCore::PackageDependencyManager::CreatePackageDependency(user, packageFamilyName, minVersion, packageDependencyProcessorArchitectures, lifetimeKind, lifetimeArtifact, options, packageDependencyId);
    return S_OK;
}
CATCH_RETURN();

STDAPI_(void) MddDeletePackageDependency(
    _In_ PCWSTR packageDependencyId) noexcept try
{
    // Use the Win11 APIs if available (instead of Detour'ing to our own implementation)
    if (MddCore::Win11::IsSupported())
    {
        MddCore::Win11::DeletePackageDependency(packageDependencyId);
        return;
    }

    // WinAppSDK's Dynamic Dependencies requires a non-packaged process
    THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), AppModel::Identity::IsPackagedProcess());

    MddCore::PackageDependencyManager::DeletePackageDependency(packageDependencyId);
}
CATCH_LOG();

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

    // Use the Win11 APIs if available (instead of Detour'ing to our own implementation)
    if (MddCore::Win11::IsSupported())
    {
        RETURN_IF_FAILED(MddCore::Win11::AddPackageDependency(packageDependencyId, rank, options, packageDependencyContext, packageFullName));
        return S_OK;
    }

    // WinAppSDK's Dynamic Dependencies requires a non-packaged process
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), AppModel::Identity::IsPackagedProcess());

    RETURN_IF_FAILED(MddCore::PackageGraphManager::AddToPackageGraph(packageDependencyId, rank, options, packageDependencyContext, packageFullName));
    return S_OK;
}
CATCH_RETURN();

STDAPI_(void) MddRemovePackageDependency(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext) noexcept try
{
    // Use the Win11 APIs if available (instead of Detour'ing to our own implementation)
    if (MddCore::Win11::IsSupported())
    {
        MddCore::Win11::RemovePackageDependency(packageDependencyContext);
        return;
    }

    // WinAppSDK's Dynamic Dependencies requires a non-packaged process
    LOG_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), AppModel::Identity::IsPackagedProcess());

    MddCore::PackageGraphManager::RemoveFromPackageGraph(packageDependencyContext);
}
CATCH_LOG();

STDAPI MddGetResolvedPackageFullNameForPackageDependency(
    _In_ PCWSTR packageDependencyId,
    _Outptr_result_maybenull_ PWSTR* packageFullName) noexcept try
{
    *packageFullName = nullptr;

    // Use the Win11 APIs if available (instead of Detour'ing to our own implementation)
    if (MddCore::Win11::IsSupported())
    {
        RETURN_IF_FAILED(MddCore::Win11::GetResolvedPackageFullNameForPackageDependency(packageDependencyId, packageFullName));
        return S_OK;
    }

    // WinAppSDK's Dynamic Dependencies requires a non-packaged process
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), AppModel::Identity::IsPackagedProcess());

    RETURN_HR_IF(E_INVALIDARG, !packageDependencyId || (packageDependencyId[0] == L'\0'));

    wil::unique_process_heap_string fullName;
    RETURN_IF_FAILED(MddCore::PackageGraphManager::GetResolvedPackageDependency(packageDependencyId, fullName));

    *packageFullName = fullName.release();
    return S_OK;
}
CATCH_RETURN();

STDAPI MddGetResolvedPackageFullNameForPackageDependency2(
    _In_ PCWSTR packageDependencyId,
    _Outptr_result_maybenull_ PWSTR* packageFullName) noexcept try
{
    *packageFullName = nullptr;

    // Use the Win11 APIs if available (instead of Detour'ing to our own implementation)
    if (MddCore::Win11::IsSupported())
    {
        RETURN_IF_FAILED(MddCore::Win11::GetResolvedPackageFullNameForPackageDependency2(packageDependencyId, packageFullName));
        return S_OK;
    }

    // WinAppSDK's Dynamic Dependencies requires a non-packaged process
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), AppModel::Identity::IsPackagedProcess());

    RETURN_HR_IF(E_INVALIDARG, !packageDependencyId || (packageDependencyId[0] == L'\0'));

    wil::unique_process_heap_string fullName;
    RETURN_IF_FAILED(MddCore::PackageGraphManager::GetResolvedPackageDependency2(packageDependencyId, fullName));

    *packageFullName = fullName.release();
    return S_OK;
}
CATCH_RETURN();

STDAPI MddGetIdForPackageDependencyContext(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext,
    _Outptr_result_maybenull_ PWSTR* packageDependencyId) noexcept try
{
    *packageDependencyId = nullptr;

    // Use the Win11 APIs if available (instead of Detour'ing to our own implementation)
    if (MddCore::Win11::IsSupported())
    {
        RETURN_IF_FAILED(MddCore::Win11::GetIdForPackageDependencyContext(packageDependencyContext, packageDependencyId));
        return S_OK;
    }

    // WinAppSDK's Dynamic Dependencies requires a non-packaged process
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), AppModel::Identity::IsPackagedProcess());

    RETURN_HR_IF(E_INVALIDARG, !packageDependencyContext);

    wil::unique_process_heap_string id;
    RETURN_IF_FAILED(MddCore::PackageGraphManager::GetPackageDependencyForContext(packageDependencyContext, id));

    *packageDependencyId = id.release();
    return S_OK;
}
CATCH_RETURN();

STDAPI_(UINT32) MddGetPackageGraphRevisionId() noexcept
{
    // Use the Win11 APIs if available (instead of Detour'ing to our own implementation)
    if (MddCore::Win11::IsSupported())
    {
        return MddCore::Win11::GetPackageGraphRevisionId();
    }

    return MddCore::PackageGraphManager::GetPackageGraphRevisionId();
}

STDAPI_(UINT32) MddGetGenerationId() noexcept
{
    return MddGetPackageGraphRevisionId();
}
