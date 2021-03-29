// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "msixdynamicdependency.h"

#include "MddDetourPackageGraph.h"
#include "PackageDependencyManager.h"
#include "PackageGraphManager.h"

namespace MddCore
{
bool IsStaticPackageGraphEmpty()
{
    // Check the static package graph
    UINT32 n{};
    const auto rc{ GetCurrentStaticPackageInfo(PACKAGE_FILTER_HEAD | PACKAGE_FILTER_STATIC, &n, nullptr, nullptr) };
    if (rc == ERROR_SUCCESS)
    {
        // The package graph isn't empty but there's no static HEAD. Thus we have no static package graph
        return true;
    }
    (void) LOG_HR_IF_MSG(HRESULT_FROM_WIN32(rc), (rc != APPMODEL_ERROR_NO_PACKAGE) && (rc != ERROR_INSUFFICIENT_BUFFER), "GetCurrentStaticPackageInfo rc=%d", rc);
    return (rc == APPMODEL_ERROR_NO_PACKAGE);
}

bool IsPackagedProcess()
{
    UINT32 n{};
    const auto rc{ GetCurrentPackageFullName(&n, nullptr) };
    (void) LOG_HR_IF_MSG(HRESULT_FROM_WIN32(rc), (rc != APPMODEL_ERROR_NO_PACKAGE) && (rc != ERROR_INSUFFICIENT_BUFFER), "GetCurrentPackageFullName rc=%d", rc);
    return (rc == ERROR_INSUFFICIENT_BUFFER);
}

// Temporary check to prevent accidental misuse and false bug reports until we address Issue #567 https://github.com/microsoft/ProjectReunion/issues/567
bool IsElevated(HANDLE token = nullptr)
{
    wistd::unique_ptr<TOKEN_MANDATORY_LABEL> tokenMandatoryLabel{ wil::get_token_information_failfast<TOKEN_MANDATORY_LABEL>(!token ? GetCurrentThreadEffectiveToken() : token) };
    const DWORD integrityLevel{ *GetSidSubAuthority((*tokenMandatoryLabel).Label.Sid, static_cast<DWORD>(static_cast<UCHAR>(*GetSidSubAuthorityCount((*tokenMandatoryLabel).Label.Sid) - 1))) };
    return integrityLevel >= SECURITY_MANDATORY_HIGH_RID;
}

void FailFastIfElevated()
{
    FAIL_FAST_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), IsElevated() || IsElevated(GetCurrentProcessToken()), "DynamicDependencies doesn't support elevation. See Issue #567 https://github.com/microsoft/ProjectReunion/issues/567");
}
}

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
    // Dynamic Dependencies doesn't support elevation. See Issue #567 https://github.com/microsoft/ProjectReunion/issues/567
    MddCore::FailFastIfElevated();

    *packageDependencyId = nullptr;

    // Dynamic Dependencies requires a non-packaged process
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), MddCore::IsPackagedProcess());

    MddCore::PackageDependencyManager::CreatePackageDependency(user, packageFamilyName, minVersion, packageDependencyProcessorArchitectures, lifetimeKind, lifetimeArtifact, options, packageDependencyId);
    return S_OK;
}
CATCH_RETURN();

STDAPI_(void) MddDeletePackageDependency(
    _In_ PCWSTR packageDependencyId) noexcept try
{
    // Dynamic Dependencies doesn't support elevation. See Issue #567 https://github.com/microsoft/ProjectReunion/issues/567
    MddCore::FailFastIfElevated();

    // Dynamic Dependencies requires a non-packaged process
    THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), MddCore::IsPackagedProcess());

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
    // Dynamic Dependencies doesn't support elevation. See Issue #567 https://github.com/microsoft/ProjectReunion/issues/567
    MddCore::FailFastIfElevated();

    *packageDependencyContext = nullptr;
    if (packageFullName)
    {
        *packageFullName = nullptr;
    }

    // Dynamic Dependencies requires a non-packaged process
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), MddCore::IsPackagedProcess());

    RETURN_IF_FAILED(MddCore::PackageGraphManager::AddToPackageGraph(packageDependencyId, rank, options, packageDependencyContext, packageFullName));
    return S_OK;
}
CATCH_RETURN();

STDAPI_(void) MddRemovePackageDependency(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext) noexcept try
{
    // Dynamic Dependencies doesn't support elevation. See Issue #567 https://github.com/microsoft/ProjectReunion/issues/567
    MddCore::FailFastIfElevated();

    // Dynamic Dependencies requires a non-packaged process
    LOG_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), MddCore::IsPackagedProcess());

    MddCore::PackageGraphManager::RemoveFromPackageGraph(packageDependencyContext);
}
CATCH_LOG();

STDAPI MddGetResolvedPackageFullNameForPackageDependency(
    _In_ PCWSTR packageDependencyId,
    _Outptr_result_maybenull_ PWSTR* packageFullName) noexcept try
{
    // Dynamic Dependencies doesn't support elevation. See Issue #567 https://github.com/microsoft/ProjectReunion/issues/567
    MddCore::FailFastIfElevated();

    *packageFullName = nullptr;

    // Dynamic Dependencies requires a non-packaged process
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), MddCore::IsPackagedProcess());

    RETURN_HR_IF(E_INVALIDARG, !packageDependencyId || (packageDependencyId[0] == L'\0'));

    wil::unique_process_heap_string fullName;
    RETURN_IF_FAILED(MddCore::PackageGraphManager::ResolvePackageDependency(packageDependencyId, MddAddPackageDependencyOptions::None, fullName));

    *packageFullName = fullName.release();
    return S_OK;
}
CATCH_RETURN();

STDAPI MddGetIdForPackageDependencyContext(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext,
    _Outptr_result_maybenull_ PWSTR* packageDependencyId) noexcept try
{
    // Dynamic Dependencies doesn't support elevation. See Issue #567 https://github.com/microsoft/ProjectReunion/issues/567
    MddCore::FailFastIfElevated();

    *packageDependencyId = nullptr;

    // Dynamic Dependencies requires a non-packaged process
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), MddCore::IsPackagedProcess());

    RETURN_HR_IF(E_INVALIDARG, !packageDependencyContext);

    wil::unique_process_heap_string id;
    RETURN_IF_FAILED(MddCore::PackageGraphManager::GetPackageDependencyForContext(packageDependencyContext, id));

    *packageDependencyId = id.release();
    return S_OK;
}
CATCH_RETURN();
