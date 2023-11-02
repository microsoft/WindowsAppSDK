// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(MDDWIN11DYNAMICDEPENDENCY_H)
#define MDDWIN11DYNAMICDEPENDENCY_H

#include <MsixDynamicDependency.h>

#include <IsWindowsVersion.h>

namespace MddCore::Win11
{
    namespace details
    {
        __declspec(selectany) HMODULE g_dllApisetAppmodelRuntime_1_6{};
        __declspec(selectany) decltype(&::TryCreatePackageDependency) g_win11TryCreatePackageDependency{};
        __declspec(selectany) decltype(&::DeletePackageDependency) g_win11DeletePackageDependency{};
        __declspec(selectany) decltype(&::AddPackageDependency) g_win11AddPackageDependency{};
        __declspec(selectany) decltype(&::RemovePackageDependency) g_win11RemovePackageDependency{};
        __declspec(selectany) decltype(&::GetResolvedPackageFullNameForPackageDependency) g_win11GetResolvedPackageFullNameForPackageDependency{};
        __declspec(selectany) decltype(&::GetIdForPackageDependencyContext) g_win11GetIdForPackageDependencyContext{};
        __declspec(selectany) decltype(&::GetPackageGraphRevisionId) g_win11GetPackageGraphRevisionId{};

        //TODO:Resolve __declspec(selectany) HMODULE g_dllApisetAppmodelRuntime_1_7{};
        //TODO:Resolve __declspec(selectany) decltype(&::ResolvePackageFullNameForPackageDependency) g_win11ResolvePackageFullNameForPackageDependency{};

        __declspec(selectany) bool g_isSupported{ WindowsVersion::IsWindows11_22H2OrGreater() };

        constexpr PackageDependencyLifetimeKind ToLifetimeKind(MddPackageDependencyLifetimeKind lifetimeKind)
        {
            switch (lifetimeKind)
            {
                case MddPackageDependencyLifetimeKind::Process: return PackageDependencyLifetimeKind_Process;
                case MddPackageDependencyLifetimeKind::FilePath: return PackageDependencyLifetimeKind_FilePath;
                case MddPackageDependencyLifetimeKind::RegistryKey: return PackageDependencyLifetimeKind_RegistryKey;
                default: THROW_HR_MSG(E_UNEXPECTED, "Unknown MddPackageDependencyLifetimeKind (%d)", lifetimeKind);
            };
        }

#if defined(WINRT_Microsoft_Windows_ApplicationModel_DynamicDependency_H)
        constexpr PackageDependencyLifetimeKind ToLifetimeKind(winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind lifetimeKind)
        {
            switch (lifetimeKind)
            {
                case winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::Process: return PackageDependencyLifetimeKind_Process;
                case winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::FilePath: return PackageDependencyLifetimeKind_FilePath;
                case winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::RegistryKey: return PackageDependencyLifetimeKind_RegistryKey;
                default: THROW_HR_MSG(E_UNEXPECTED, "Unknown winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeKind (%d)", lifetimeKind);
            };
        }
#endif // defined(WINRT_Microsoft_Windows_ApplicationModel_DynamicDependency_H)
    }

#if defined(WINRT_Microsoft_Windows_ApplicationModel_DynamicDependency_H)
    inline winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContextId ToContextId(MDD_PACKAGEDEPENDENCY_CONTEXT context)
    {
        return winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContextId{ static_cast<uint64_t>(reinterpret_cast<INT_PTR>(context)) };
    }
#endif // defined(WINRT_Microsoft_Windows_ApplicationModel_DynamicDependency_H)

#if defined(WINRT_Microsoft_Windows_ApplicationModel_DynamicDependency_H)
    inline MDD_PACKAGEDEPENDENCY_CONTEXT ToContext(winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContextId contextId)
    {
        return reinterpret_cast<MDD_PACKAGEDEPENDENCY_CONTEXT>(static_cast<INT_PTR>(contextId.Id));
    }
#endif // defined(WINRT_Microsoft_Windows_ApplicationModel_DynamicDependency_H)

    inline bool IsSupported()
    {
        return MddCore::Win11::details::g_isSupported;
    }

    inline HRESULT TryCreatePackageDependency(
        PSID user,
        _In_ PCWSTR packageFamilyName,
        PACKAGE_VERSION minVersion,
        MddPackageDependencyProcessorArchitectures packageDependencyProcessorArchitectures,
        MddPackageDependencyLifetimeKind lifetimeKind,
        PCWSTR lifetimeArtifact,
        MddCreatePackageDependencyOptions options,
        _Outptr_result_maybenull_ PWSTR* packageDependencyId)
    {
        const ::AppModel::Identity::PackageVersion win11MinVersion{ minVersion };

        auto win11PackageDependencyProcessorArchitectures{ PackageDependencyProcessorArchitectures_None };
        WI_SetFlagIf(win11PackageDependencyProcessorArchitectures, PackageDependencyProcessorArchitectures_Neutral, WI_IsFlagSet(packageDependencyProcessorArchitectures, MddPackageDependencyProcessorArchitectures::Neutral));
        WI_SetFlagIf(win11PackageDependencyProcessorArchitectures, PackageDependencyProcessorArchitectures_X86, WI_IsFlagSet(packageDependencyProcessorArchitectures, MddPackageDependencyProcessorArchitectures::X86));
        WI_SetFlagIf(win11PackageDependencyProcessorArchitectures, PackageDependencyProcessorArchitectures_X64, WI_IsFlagSet(packageDependencyProcessorArchitectures, MddPackageDependencyProcessorArchitectures::X64));
        WI_SetFlagIf(win11PackageDependencyProcessorArchitectures, PackageDependencyProcessorArchitectures_Arm, WI_IsFlagSet(packageDependencyProcessorArchitectures, MddPackageDependencyProcessorArchitectures::Arm));
        WI_SetFlagIf(win11PackageDependencyProcessorArchitectures, PackageDependencyProcessorArchitectures_Arm64, WI_IsFlagSet(packageDependencyProcessorArchitectures, MddPackageDependencyProcessorArchitectures::Arm64));
        WI_SetFlagIf(win11PackageDependencyProcessorArchitectures, PackageDependencyProcessorArchitectures_X86A64, WI_IsFlagSet(packageDependencyProcessorArchitectures, MddPackageDependencyProcessorArchitectures::X86OnArm64));

        const auto win11LifetimeKind{ MddCore::Win11::details::ToLifetimeKind(lifetimeKind) };

        auto win11Options{ CreatePackageDependencyOptions_None };
        WI_SetFlagIf(win11Options, CreatePackageDependencyOptions_DoNotVerifyDependencyResolution, WI_IsFlagSet(options, MddCreatePackageDependencyOptions::DoNotVerifyDependencyResolution));
        WI_SetFlagIf(win11Options, CreatePackageDependencyOptions_ScopeIsSystem, WI_IsFlagSet(options, MddCreatePackageDependencyOptions::ScopeIsSystem));

        RETURN_IF_FAILED(MddCore::Win11::details::g_win11TryCreatePackageDependency(user, packageFamilyName, win11MinVersion,
            win11PackageDependencyProcessorArchitectures, win11LifetimeKind, lifetimeArtifact,
            win11Options, packageDependencyId));
        return S_OK;
    }

#if defined(WINRT_Microsoft_Windows_ApplicationModel_DynamicDependency_H)
//TODO reimplement over above
    inline HRESULT TryCreatePackageDependency(
        PSID user,
        const winrt::hstring& packageFamilyName,
        const winrt::Windows::ApplicationModel::PackageVersion& minVersion,
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures packageDependencyProcessorArchitectures,
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& options,
        _Outptr_result_maybenull_ PWSTR* packageDependencyId)
    {
        PCWSTR win11PackageFamilyName{ packageFamilyName.c_str() };

        const ::AppModel::Identity::PackageVersion minPackageVersion{ minVersion };
        const PACKAGE_VERSION win11MinVersion{ minPackageVersion };

        auto win11PackageDependencyProcessorArchitectures{ PackageDependencyProcessorArchitectures_None };
        WI_SetFlagIf(win11PackageDependencyProcessorArchitectures, PackageDependencyProcessorArchitectures_Neutral, WI_IsFlagSet(packageDependencyProcessorArchitectures, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::Neutral));
        WI_SetFlagIf(win11PackageDependencyProcessorArchitectures, PackageDependencyProcessorArchitectures_X86, WI_IsFlagSet(packageDependencyProcessorArchitectures, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::X86));
        WI_SetFlagIf(win11PackageDependencyProcessorArchitectures, PackageDependencyProcessorArchitectures_X64, WI_IsFlagSet(packageDependencyProcessorArchitectures, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::X64));
        WI_SetFlagIf(win11PackageDependencyProcessorArchitectures, PackageDependencyProcessorArchitectures_Arm, WI_IsFlagSet(packageDependencyProcessorArchitectures, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::Arm));
        WI_SetFlagIf(win11PackageDependencyProcessorArchitectures, PackageDependencyProcessorArchitectures_Arm64, WI_IsFlagSet(packageDependencyProcessorArchitectures, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::Arm64));
        WI_SetFlagIf(win11PackageDependencyProcessorArchitectures, PackageDependencyProcessorArchitectures_X86A64, WI_IsFlagSet(packageDependencyProcessorArchitectures, winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::X86OnArm64));

        const auto win11LifetimeKind{ MddCore::Win11::details::ToLifetimeKind(options.LifetimeArtifactKind()) };

        PCWSTR win11LifetimeArtifact{ options.LifetimeArtifact().c_str() };

        auto win11Options{ CreatePackageDependencyOptions_None };
        WI_SetFlagIf(win11Options, CreatePackageDependencyOptions_DoNotVerifyDependencyResolution, !options.VerifyDependencyResolution());
        //TODO CreatePackageDependencyOptions_ScopeIsSystem

        RETURN_IF_FAILED(MddCore::Win11::details::g_win11TryCreatePackageDependency(user, win11PackageFamilyName, win11MinVersion,
            win11PackageDependencyProcessorArchitectures, win11LifetimeKind, win11LifetimeArtifact,
            win11Options, packageDependencyId));
        return S_OK;
    }
#endif // defined(WINRT_Microsoft_Windows_ApplicationModel_DynamicDependency_H)

    inline void DeletePackageDependency(
        const winrt::hstring& packageDependencyId)
    {
        DeletePackageDependency(packageDependencyId.c_str());
    }

    inline void DeletePackageDependency(
        _In_ PCWSTR packageDependencyId)
    {
        (void)LOG_IF_FAILED(MddCore::Win11::details::g_win11DeletePackageDependency(packageDependencyId));
    }

    inline HRESULT AddPackageDependency(
        _In_ PCWSTR packageDependencyId,
        std::int32_t rank,
        MddAddPackageDependencyOptions options,
        _Out_ MDD_PACKAGEDEPENDENCY_CONTEXT* packageDependencyContext,
        _Outptr_opt_result_maybenull_ PWSTR* packageFullName)
    {
        auto win11Options{ AddPackageDependencyOptions_None };
        WI_SetFlagIf(win11Options, AddPackageDependencyOptions_PrependIfRankCollision, WI_IsFlagSet(options, MddAddPackageDependencyOptions::PrependIfRankCollision));

        static_assert(sizeof(MDD_PACKAGEDEPENDENCY_CONTEXT) == sizeof(PACKAGEDEPENDENCY_CONTEXT));
        auto win11PackageDependencyContext{ reinterpret_cast<PACKAGEDEPENDENCY_CONTEXT*>(packageDependencyContext) };

        RETURN_IF_FAILED(MddCore::Win11::details::g_win11AddPackageDependency(packageDependencyId, rank, win11Options, win11PackageDependencyContext, packageFullName));
        return S_OK;
    }

#if defined(WINRT_Microsoft_Windows_ApplicationModel_DynamicDependency_H)
//TODO reimplement over above
    inline HRESULT AddPackageDependency(
        const winrt::hstring& packageDependencyId,
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& options,
        _Out_ MDD_PACKAGEDEPENDENCY_CONTEXT* packageDependencyContext,
        _Outptr_opt_result_maybenull_ PWSTR* packageFullName)
    {
        PCWSTR win11PackageDependencyId{ packageDependencyId.c_str() };

        const auto win11Rank{ options.Rank() };

        auto win11Options{ AddPackageDependencyOptions_None };
        WI_SetFlagIf(win11Options, AddPackageDependencyOptions_PrependIfRankCollision, options.PrependIfRankCollision());

        static_assert(sizeof(MDD_PACKAGEDEPENDENCY_CONTEXT) == sizeof(PACKAGEDEPENDENCY_CONTEXT));
        auto win11PackageDependencyContext{ reinterpret_cast<PACKAGEDEPENDENCY_CONTEXT*>(packageDependencyContext) };

        RETURN_IF_FAILED(MddCore::Win11::details::g_win11AddPackageDependency(win11PackageDependencyId, win11Rank, win11Options, win11PackageDependencyContext, packageFullName));
        return S_OK;
    }
#endif // defined(WINRT_Microsoft_Windows_ApplicationModel_DynamicDependency_H)

    inline void RemovePackageDependency(
        _In_ MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext)
    {
        static_assert(sizeof(MDD_PACKAGEDEPENDENCY_CONTEXT) == sizeof(PACKAGEDEPENDENCY_CONTEXT));
        auto win11PackageDependencyContext{ reinterpret_cast<PACKAGEDEPENDENCY_CONTEXT>(packageDependencyContext) };

        MddCore::Win11::details::g_win11RemovePackageDependency(win11PackageDependencyContext);
    }

#if defined(WINRT_Microsoft_Windows_ApplicationModel_DynamicDependency_H)
    inline void RemovePackageDependency(
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContextId packageDependencyContextId)
    {
        return RemovePackageDependency(MddCore::Win11::ToContext(packageDependencyContextId));
    }
#endif // defined(WINRT_Microsoft_Windows_ApplicationModel_DynamicDependency_H)

    inline HRESULT GetResolvedPackageFullNameForPackageDependency(
        _In_ PCWSTR packageDependencyId,
        _Outptr_result_maybenull_ PWSTR* packageFullName)
    {
        RETURN_IF_FAILED(MddCore::Win11::details::g_win11GetResolvedPackageFullNameForPackageDependency(packageDependencyId, packageFullName));
        return S_OK;
    }

    inline HRESULT ResolvePackageFullNameForPackageDependency(
        _In_ PCWSTR packageDependencyId,
        _Outptr_result_maybenull_ PWSTR* packageFullName)
    {
        //TODO:Resolve RETURN_IF_FAILED(MddCore::Win11::details::g_win11ResolvePackageFullNameForPackageDependency(packageDependencyId, packageFullName));
        //TODO:Resolve return S_OK;
        RETURN_HR(E_NOTIMPL);
    }

    inline HRESULT GetIdForPackageDependencyContext(
        _In_ MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext,
        _Outptr_result_maybenull_ PWSTR* packageDependencyId)
    {
        static_assert(sizeof(MDD_PACKAGEDEPENDENCY_CONTEXT) == sizeof(PACKAGEDEPENDENCY_CONTEXT));
        auto win11PackageDependencyContext{ reinterpret_cast<PACKAGEDEPENDENCY_CONTEXT>(packageDependencyContext) };

        RETURN_IF_FAILED(MddCore::Win11::details::g_win11GetIdForPackageDependencyContext(win11PackageDependencyContext, packageDependencyId));
        return S_OK;
    }

    inline UINT32 GetPackageGraphRevisionId()
    {
        return MddCore::Win11::details::g_win11GetPackageGraphRevisionId();
    }
}

inline HRESULT WINAPI MddWin11Initialize() noexcept
{
    if (!MddCore::Win11::IsSupported())
    {
        return S_OK;
    }

    HMODULE dllApisetAppmodelRuntime_1_6{ LoadLibraryExW(L"api-ms-win-appmodel-runtime-l1-1-6.dll", nullptr, 0) };
    FAIL_FAST_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), dllApisetAppmodelRuntime_1_6);

    auto win11TryCreatePackageDependency{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_6, TryCreatePackageDependency) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), win11TryCreatePackageDependency);
    auto win11DeletePackageDependency{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_6, DeletePackageDependency) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), win11DeletePackageDependency);
    auto win11AddPackageDependency{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_6, AddPackageDependency) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), win11AddPackageDependency);
    auto win11RemovePackageDependency{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_6, RemovePackageDependency) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), win11RemovePackageDependency);
    auto win11GetResolvedPackageFullNameForPackageDependency{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_6, GetResolvedPackageFullNameForPackageDependency) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), win11GetResolvedPackageFullNameForPackageDependency);
    auto win11GetIdForPackageDependencyContext{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_6, GetIdForPackageDependencyContext) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), win11GetIdForPackageDependencyContext);
    auto win11GetPackageGraphRevisionId{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_6, GetPackageGraphRevisionId) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), win11GetPackageGraphRevisionId);
    //
    //TODO:Resolve HMODULE dllApisetAppmodelRuntime_1_7{ LoadLibraryExW(L"api-ms-win-appmodel-runtime-l1-1-7.dll", nullptr, 0) };
    //TODO:Resolve FAIL_FAST_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), dllApisetAppmodelRuntime_1_7);
    //TODO:Resolve
    //TODO:Resolve auto win11ResolvePackageFullNameForPackageDependency{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_7, ResolvePackageFullNameForPackageDependency) };
    //TODO:Resolve RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), win11ResolvePackageFullNameForPackageDependency);

    //TODO:Resolve MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_7 = dllApisetAppmodelRuntime_1_7;
    //TODO:Resolve MddCore::Win11::details::g_win11ResolvePackageFullNameForPackageDependency = win11ResolvePackageFullNameForPackageDependency;
    //
    MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_6 = dllApisetAppmodelRuntime_1_6;
    MddCore::Win11::details::g_win11TryCreatePackageDependency = win11TryCreatePackageDependency;
    MddCore::Win11::details::g_win11DeletePackageDependency = win11DeletePackageDependency;
    MddCore::Win11::details::g_win11AddPackageDependency = win11AddPackageDependency;
    MddCore::Win11::details::g_win11RemovePackageDependency = win11RemovePackageDependency;
    MddCore::Win11::details::g_win11GetResolvedPackageFullNameForPackageDependency = win11GetResolvedPackageFullNameForPackageDependency;
    MddCore::Win11::details::g_win11GetIdForPackageDependencyContext = win11GetIdForPackageDependencyContext;
    MddCore::Win11::details::g_win11GetPackageGraphRevisionId = win11GetPackageGraphRevisionId;
    return S_OK;
}

inline HRESULT WINAPI MddWin11Shutdown() noexcept
{
    //TODO:Resolve if (MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_7)
    //TODO:Resolve {
    //TODO:Resolve     MddCore::Win11::details::g_win11ResolvePackageFullNameForPackageDependency = nullptr;
    //TODO:Resolve     FreeLibrary(MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_7);
    //TODO:Resolve     MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_7 = nullptr;
    //TODO:Resolve }

    if (MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_6)
    {
        MddCore::Win11::details::g_win11TryCreatePackageDependency = nullptr;
        MddCore::Win11::details::g_win11DeletePackageDependency = nullptr;
        MddCore::Win11::details::g_win11AddPackageDependency = nullptr;
        MddCore::Win11::details::g_win11RemovePackageDependency = nullptr;
        MddCore::Win11::details::g_win11GetResolvedPackageFullNameForPackageDependency = nullptr;
        MddCore::Win11::details::g_win11GetIdForPackageDependencyContext = nullptr;
        MddCore::Win11::details::g_win11GetPackageGraphRevisionId = nullptr;
        FreeLibrary(MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_6);
        MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_6 = nullptr;
    }
    return S_OK;
}

#endif // MDDWIN11DYNAMICDEPENDENCY_H
