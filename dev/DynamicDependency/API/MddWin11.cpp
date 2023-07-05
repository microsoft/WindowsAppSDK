// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <IsWindowsVersion.h>

#include "MddWin11.h"

namespace MddCore::Win11
{
decltype(&::TryCreatePackageDependency) g_win11TryCreatePackageDependency{};
decltype(&::DeletePackageDependency) g_win11DeletePackageDependency{};
decltype(&::AddPackageDependency) g_win11AddPackageDependency{};
decltype(&::RemovePackageDependency) g_win11RemovePackageDependency{};
decltype(&::GetResolvedPackageFullNameForPackageDependency) g_win11GetResolvedPackageFullNameForPackageDependency{};
decltype(&::GetIdForPackageDependencyContext) g_win11GetIdForPackageDependencyContext{};
decltype(&::GetPackageGraphRevisionId) g_win11GetPackageGraphRevisionId{};
}

bool MddCore::Win11::IsSupported()
{
    static bool s_isSupported{ WindowsVersion::IsWindows11_22H2OrGreater() };
    return s_isSupported;
}

HRESULT MddCore::Win11::Initialize()
{
    HMODULE dllApisetAppmodelRuntime_1_6{ LoadLibraryExW(L"api-ms-win-appmodel-runtime-l1-1-6.dll", nullptr, 0) };
    FAIL_FAST_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), dllApisetAppmodelRuntime_1_6);

    auto win11TryCreatePackageDependency{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_6, TryCreatePackageDependency) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), g_win11TryCreatePackageDependency);
    auto win11DeletePackageDependency{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_6, DeletePackageDependency) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), g_win11DeletePackageDependency);
    auto win11AddPackageDependency{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_6, AddPackageDependency) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), g_win11AddPackageDependency);
    auto win11RemovePackageDependency{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_6, RemovePackageDependency) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), g_win11RemovePackageDependency);
    auto win11GetResolvedPackageFullNameForPackageDependency{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_6, GetResolvedPackageFullNameForPackageDependency) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), g_win11GetResolvedPackageFullNameForPackageDependency);
    auto win11GetIdForPackageDependencyContext{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_6, GetIdForPackageDependencyContext) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), g_win11GetIdForPackageDependencyContext);
    auto win11GetPackageGraphRevisionId{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_6, GetPackageGraphRevisionId) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), g_win11GetPackageGraphRevisionId);

    g_win11TryCreatePackageDependency = win11TryCreatePackageDependency;
    g_win11DeletePackageDependency = win11DeletePackageDependency;
    g_win11AddPackageDependency = win11AddPackageDependency;
    g_win11RemovePackageDependency = win11RemovePackageDependency;
    g_win11GetResolvedPackageFullNameForPackageDependency = win11GetResolvedPackageFullNameForPackageDependency;
    g_win11GetIdForPackageDependencyContext = win11GetIdForPackageDependencyContext;
    g_win11GetPackageGraphRevisionId = win11GetPackageGraphRevisionId;
    return S_OK;
}

void MddCore::Win11::Shutdown()
{
    g_win11TryCreatePackageDependency = nullptr;
    g_win11DeletePackageDependency = nullptr;
    g_win11AddPackageDependency = nullptr;
    g_win11RemovePackageDependency = nullptr;
    g_win11GetResolvedPackageFullNameForPackageDependency = nullptr;
    g_win11GetIdForPackageDependencyContext = nullptr;
    g_win11GetPackageGraphRevisionId = nullptr;
}

HRESULT MddCore::Win11::TryCreatePackageDependency(
    PSID user,
    _In_ PCWSTR packageFamilyName,
    PACKAGE_VERSION minVersion,
    MddPackageDependencyProcessorArchitectures packageDependencyProcessorArchitectures,
    MddPackageDependencyLifetimeKind lifetimeKind,
    PCWSTR lifetimeArtifact,
    MddCreatePackageDependencyOptions options,
    _Outptr_result_maybenull_ PWSTR* packageDependencyId)
{
    static_assert(static_cast<int>(MddPackageDependencyProcessorArchitectures::None) == static_cast<int>(PackageDependencyProcessorArchitectures_None));
    static_assert(static_cast<int>(MddPackageDependencyProcessorArchitectures::Neutral) == static_cast<int>(PackageDependencyProcessorArchitectures_Neutral));
    static_assert(static_cast<int>(MddPackageDependencyProcessorArchitectures::X86) == static_cast<int>(PackageDependencyProcessorArchitectures_X86));
    static_assert(static_cast<int>(MddPackageDependencyProcessorArchitectures::X64) == static_cast<int>(PackageDependencyProcessorArchitectures_X64));
    static_assert(static_cast<int>(MddPackageDependencyProcessorArchitectures::Arm) == static_cast<int>(PackageDependencyProcessorArchitectures_Arm));
    static_assert(static_cast<int>(MddPackageDependencyProcessorArchitectures::Arm64) == static_cast<int>(PackageDependencyProcessorArchitectures_Arm64));
    static_assert(static_cast<int>(MddPackageDependencyProcessorArchitectures::X86OnArm64) == static_cast<int>(PackageDependencyProcessorArchitectures_X86A64));
    auto win11PackageDependencyProcessorArchitectures{ static_cast<::PackageDependencyProcessorArchitectures>(packageDependencyProcessorArchitectures) };

    static_assert(static_cast<int>(MddPackageDependencyLifetimeKind::Process) == static_cast<int>(PackageDependencyLifetimeKind_Process));
    static_assert(static_cast<int>(MddPackageDependencyLifetimeKind::FilePath) == static_cast<int>(PackageDependencyLifetimeKind_FilePath));
    static_assert(static_cast<int>(MddPackageDependencyLifetimeKind::RegistryKey) == static_cast<int>(PackageDependencyLifetimeKind_RegistryKey));
    auto win11LifetimeKind{ static_cast<::PackageDependencyLifetimeKind>(lifetimeKind) };

    static_assert(static_cast<int>(MddCreatePackageDependencyOptions::None) == static_cast<int>(CreatePackageDependencyOptions_None));
    static_assert(static_cast<int>(MddCreatePackageDependencyOptions::DoNotVerifyDependencyResolution) == static_cast<int>(CreatePackageDependencyOptions_DoNotVerifyDependencyResolution));
    static_assert(static_cast<int>(MddCreatePackageDependencyOptions::ScopeIsSystem) == static_cast<int>(CreatePackageDependencyOptions_ScopeIsSystem));
    auto win11Options{ static_cast<::CreatePackageDependencyOptions>(options) };

    RETURN_IF_FAILED(g_win11TryCreatePackageDependency(user, packageFamilyName, minVersion,
        win11PackageDependencyProcessorArchitectures, win11LifetimeKind, lifetimeArtifact,
        win11Options, packageDependencyId));
    return S_OK;
}

void MddCore::Win11::DeletePackageDependency(
    _In_ PCWSTR packageDependencyId)
{
    g_win11DeletePackageDependency(packageDependencyId);
}

HRESULT MddCore::Win11::AddPackageDependency(
    _In_ PCWSTR packageDependencyId,
    INT32 rank,
    MddAddPackageDependencyOptions options,
    _Out_ MDD_PACKAGEDEPENDENCY_CONTEXT* packageDependencyContext,
    _Outptr_opt_result_maybenull_ PWSTR* packageFullName)
{
    static_assert(static_cast<int>(MddAddPackageDependencyOptions::None) == static_cast<int>(AddPackageDependencyOptions_None));
    static_assert(static_cast<int>(MddAddPackageDependencyOptions::PrependIfRankCollision) == static_cast<int>(AddPackageDependencyOptions_PrependIfRankCollision));
    auto win11Options{ static_cast<::AddPackageDependencyOptions>(options) };

    static_assert(sizeof(MDD_PACKAGEDEPENDENCY_CONTEXT) == sizeof(PACKAGEDEPENDENCY_CONTEXT));
    auto win11PackageDependencyContext{ reinterpret_cast<PACKAGEDEPENDENCY_CONTEXT*>(packageDependencyContext) };

    RETURN_IF_FAILED(g_win11AddPackageDependency(packageDependencyId, rank, win11Options, win11PackageDependencyContext, packageFullName));
    return S_OK;
}

void MddCore::Win11::RemovePackageDependency(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext)
{
    static_assert(sizeof(MDD_PACKAGEDEPENDENCY_CONTEXT) == sizeof(PACKAGEDEPENDENCY_CONTEXT));
    auto win11PackageDependencyContext{ reinterpret_cast<PACKAGEDEPENDENCY_CONTEXT>(packageDependencyContext) };

    g_win11RemovePackageDependency(win11PackageDependencyContext);
}

HRESULT MddCore::Win11::GetResolvedPackageFullNameForPackageDependency(
    _In_ PCWSTR packageDependencyId,
    _Outptr_result_maybenull_ PWSTR* packageFullName)
{
    RETURN_IF_FAILED(g_win11GetResolvedPackageFullNameForPackageDependency(packageDependencyId, packageFullName));
    return S_OK;
}

HRESULT MddCore::Win11::GetIdForPackageDependencyContext(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext,
    _Outptr_result_maybenull_ PWSTR* packageDependencyId)
{
    static_assert(sizeof(MDD_PACKAGEDEPENDENCY_CONTEXT) == sizeof(PACKAGEDEPENDENCY_CONTEXT));
    auto win11PackageDependencyContext{ reinterpret_cast<PACKAGEDEPENDENCY_CONTEXT>(packageDependencyContext) };

    RETURN_IF_FAILED(g_win11GetIdForPackageDependencyContext(win11PackageDependencyContext, packageDependencyId));
    return S_OK;
}

UINT32 MddCore::Win11::GetPackageGraphRevisionId()
{
    return g_win11GetPackageGraphRevisionId();
}
