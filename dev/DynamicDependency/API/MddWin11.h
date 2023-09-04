// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(MDDWIN11DYNAMICDEPENDENCY_H)
#define MDDWIN11DYNAMICDEPENDENCY_H

#include <MsixDynamicDependency.h>
#include <winrt/Microsoft.Windows.ApplicationModel.DynamicDependency.h>

HRESULT WINAPI MddWin11Initialize() noexcept;

HRESULT WINAPI MddWin11Shutdown() noexcept;

namespace MddCore::Win11
{
bool IsSupported();

HRESULT TryCreatePackageDependency(
    PSID user,
    const winrt::hstring& packageFamilyName,
    const winrt::Windows::ApplicationModel::PackageVersion& minVersion,
    winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures packageDependencyProcessorArchitectures,
    winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& options,
    _Outptr_result_maybenull_ PWSTR* packageDependencyId);

HRESULT TryCreatePackageDependency(
    PSID user,
    _In_ PCWSTR packageFamilyName,
    PACKAGE_VERSION minVersion,
    MddPackageDependencyProcessorArchitectures packageDependencyProcessorArchitectures,
    MddPackageDependencyLifetimeKind lifetimeKind,
    PCWSTR lifetimeArtifact,
    MddCreatePackageDependencyOptions options,
    _Outptr_result_maybenull_ PWSTR* packageDependencyId);

void DeletePackageDependency(
    _In_ PCWSTR packageDependencyId);

HRESULT AddPackageDependency(
    const winrt::hstring& packageDependencyId,
    winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& options,
    _Out_ MDD_PACKAGEDEPENDENCY_CONTEXT* packageDependencyContext,
    _Outptr_opt_result_maybenull_ PWSTR* packageFullName);

HRESULT AddPackageDependency(
    _In_ PCWSTR packageDependencyId,
    std::int32_t rank,
    MddAddPackageDependencyOptions options,
    _Out_ MDD_PACKAGEDEPENDENCY_CONTEXT* packageDependencyContext,
    _Outptr_opt_result_maybenull_ PWSTR* packageFullName);

void RemovePackageDependency(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext);

HRESULT GetResolvedPackageFullNameForPackageDependency(
    _In_ PCWSTR packageDependencyId,
    _Outptr_result_maybenull_ PWSTR* packageFullName);

HRESULT GetIdForPackageDependencyContext(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext,
    _Outptr_result_maybenull_ PWSTR* packageDependencyId);

UINT32 GetPackageGraphRevisionId();
}

#endif // MDDWIN11DYNAMICDEPENDENCY_H
