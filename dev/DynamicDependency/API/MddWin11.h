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
        // GetCurrentPackageInfo3 is documented but not in appmodel.h
        // See https://learn.microsoft.com/windows/win32/appxpkg/appmodel/nf-appmodel-getcurrentpackageinfo3
        enum PackageInfo3Type
        {
            PackageInfo3Type_PackageInfoGeneration = 16,
        };
        //
        WINBASEAPI HRESULT WINAPI GetCurrentPackageInfo3(
            _In_ UINT32 flags,
            _In_ MddCore::Win11::details::PackageInfo3Type packageInfoType,
            _Inout_ UINT32* bufferLength,
            _Out_writes_bytes_opt_(*bufferLength) void* buffer,
            _Out_opt_ UINT32* count);

        __declspec(selectany) HMODULE g_dllApisetAppmodelRuntime_1_5{};
        __declspec(selectany) decltype(&::TryCreatePackageDependency) g_win11TryCreatePackageDependency{};
        __declspec(selectany) decltype(&::DeletePackageDependency) g_win11DeletePackageDependency{};
        __declspec(selectany) decltype(&::AddPackageDependency) g_win11AddPackageDependency{};
        __declspec(selectany) decltype(&::RemovePackageDependency) g_win11RemovePackageDependency{};
        __declspec(selectany) decltype(&::GetResolvedPackageFullNameForPackageDependency) g_win11GetResolvedPackageFullNameForPackageDependency{};
        __declspec(selectany) decltype(&::GetIdForPackageDependencyContext) g_win11GetIdForPackageDependencyContext{};
        __declspec(selectany) decltype(&MddCore::Win11::details::GetCurrentPackageInfo3) g_win11GetCurrentPackageInfo3{};

        __declspec(selectany) HMODULE g_dllApisetAppmodelRuntime_1_6{};
        __declspec(selectany) decltype(&::GetPackageGraphRevisionId) g_win11GetPackageGraphRevisionId{};

        __declspec(selectany) HMODULE g_dllApisetAppmodelRuntime_1_7{};
        //TODO:47775758 GetResolved2 __declspec(selectany) decltype(&::GetResolvedPackageFullNameForPackageDependency2) g_win11GetResolvedPackageFullNameForPackageDependency2{};

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

        inline HRESULT Load(PCWSTR moduleName, HMODULE& hmodule)
        {
            hmodule = LoadLibraryExW(moduleName, nullptr, 0);
            if (hmodule == nullptr)
            {
                const auto rc{ GetLastError() };
                RETURN_HR_IF_MSG(HRESULT_FROM_WIN32(rc), rc != ERROR_MOD_NOT_FOUND, "%ls", moduleName);
            }
            return S_OK;
        }
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
#if defined(TODO_WindowsAppSDKAggregator_Test_Failures)
        return MddCore::Win11::details::g_isSupported;
#else
        return false;
#endif
    }

    inline bool IsGetResolvedPackageFullNameForPackageDependency2Supported()
    {
        return IsSupported() && MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_7;
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

        const auto hr{ MddCore::Win11::details::g_win11TryCreatePackageDependency(user, packageFamilyName, win11MinVersion,
            win11PackageDependencyProcessorArchitectures, win11LifetimeKind, lifetimeArtifact,
            win11Options, packageDependencyId) };
        if (FAILED(hr))
        {
            if (hr == STATEREPOSITORY_E_DEPENDENCY_NOT_RESOLVED)
            {
                RETURN_HR_IF_MSG(E_INVALIDARG, ::VerifyPackageFamilyName(packageFamilyName) == HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER), "PackageFamilyName:%ls", packageFamilyName);
            }
            RETURN_HR_MSG(hr, "TryCreatePackageDependency(...packageFamilyName=%ls...)", packageFamilyName);
        }
        return S_OK;
    }

#if defined(WINRT_Microsoft_Windows_ApplicationModel_DynamicDependency_H)
    inline HRESULT _TryCreatePackageDependency(
        PSID user,
        const winrt::hstring& packageFamilyName,
        const winrt::Windows::ApplicationModel::PackageVersion& minVersion,
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures packageDependencyProcessorArchitectures,
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& options,
        const MddCreatePackageDependencyOptions initialOptions,
        _Outptr_result_maybenull_ PWSTR* packageDependencyId)
    {
        PCWSTR mddPackageFamilyName{ packageFamilyName.c_str() };

        const ::AppModel::Identity::PackageVersion minPackageVersion{ minVersion };
        const PACKAGE_VERSION mddMinVersion{ minPackageVersion };

        static_assert(static_cast<uint32_t>(PackageDependencyProcessorArchitectures_Neutral) == static_cast<uint32_t>(MddPackageDependencyProcessorArchitectures::Neutral));
        static_assert(static_cast<uint32_t>(PackageDependencyProcessorArchitectures_X86) == static_cast<uint32_t>(MddPackageDependencyProcessorArchitectures::X86));
        static_assert(static_cast<uint32_t>(PackageDependencyProcessorArchitectures_X64) == static_cast<uint32_t>(MddPackageDependencyProcessorArchitectures::X64));
        static_assert(static_cast<uint32_t>(PackageDependencyProcessorArchitectures_Arm) == static_cast<uint32_t>(MddPackageDependencyProcessorArchitectures::Arm));
        static_assert(static_cast<uint32_t>(PackageDependencyProcessorArchitectures_Arm64) == static_cast<uint32_t>(MddPackageDependencyProcessorArchitectures::Arm64));
        static_assert(static_cast<uint32_t>(PackageDependencyProcessorArchitectures_X86A64) == static_cast<uint32_t>(MddPackageDependencyProcessorArchitectures::X86OnArm64));
        const auto mddPackageDependencyProcessorArchitectures{ static_cast<MddPackageDependencyProcessorArchitectures>(packageDependencyProcessorArchitectures) };

        static_assert(static_cast<uint32_t>(MddPackageDependencyLifetimeKind::Process) == static_cast<uint32_t>(winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::Process));
        static_assert(static_cast<uint32_t>(MddPackageDependencyLifetimeKind::FilePath) == static_cast<uint32_t>(winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::FilePath));
        static_assert(static_cast<uint32_t>(MddPackageDependencyLifetimeKind::RegistryKey) == static_cast<uint32_t>(winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::RegistryKey));
        const auto mddLifetimeKind{ static_cast<MddPackageDependencyLifetimeKind>(options.LifetimeArtifactKind()) };

        PCWSTR mddLifetimeArtifact{ options.LifetimeArtifact().c_str() };

        auto mddOptions{ initialOptions };
        WI_SetFlagIf(mddOptions, MddCreatePackageDependencyOptions::DoNotVerifyDependencyResolution, !options.VerifyDependencyResolution());
        // NOTE: ScopeIsSystem is handled by the caller via initialOptions

        RETURN_IF_FAILED(TryCreatePackageDependency(user, mddPackageFamilyName, mddMinVersion,
            mddPackageDependencyProcessorArchitectures, mddLifetimeKind, mddLifetimeArtifact, mddOptions, packageDependencyId));
        return S_OK;
    }

    inline HRESULT TryCreatePackageDependency(
        PSID user,
        const winrt::hstring& packageFamilyName,
        const winrt::Windows::ApplicationModel::PackageVersion& minVersion,
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures packageDependencyProcessorArchitectures,
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& options,
        _Outptr_result_maybenull_ PWSTR* packageDependencyId)
    {
        RETURN_IF_FAILED(_TryCreatePackageDependency(user, packageFamilyName, minVersion,
            packageDependencyProcessorArchitectures, options,
            MddCreatePackageDependencyOptions::None, packageDependencyId));
        return S_OK;
    }

    inline HRESULT TryCreatePackageDependencyForSystem(
        PSID user,
        const winrt::hstring& packageFamilyName,
        const winrt::Windows::ApplicationModel::PackageVersion& minVersion,
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures packageDependencyProcessorArchitectures,
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions const& options,
        _Outptr_result_maybenull_ PWSTR* packageDependencyId)
    {
        RETURN_IF_FAILED(_TryCreatePackageDependency(user, packageFamilyName, minVersion,
            packageDependencyProcessorArchitectures, options,
            MddCreatePackageDependencyOptions::ScopeIsSystem, packageDependencyId));
        return S_OK;
    }
#endif // defined(WINRT_Microsoft_Windows_ApplicationModel_DynamicDependency_H)

    inline void DeletePackageDependency(
        _In_ PCWSTR packageDependencyId)
    {
        (void)LOG_IF_FAILED(MddCore::Win11::details::g_win11DeletePackageDependency(packageDependencyId));
    }

    inline void DeletePackageDependency(
        const winrt::hstring& packageDependencyId)
    {
        DeletePackageDependency(packageDependencyId.c_str());
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
    inline HRESULT AddPackageDependency(
        const winrt::hstring& packageDependencyId,
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions const& options,
        _Out_ MDD_PACKAGEDEPENDENCY_CONTEXT* packageDependencyContext,
        _Outptr_opt_result_maybenull_ PWSTR* packageFullName)
    {
        PCWSTR mddPackageDependencyId{ packageDependencyId.c_str() };

        const auto mddRank{ options.Rank() };

        auto mddOptions{ MddAddPackageDependencyOptions::None };
        WI_SetFlagIf(mddOptions, MddAddPackageDependencyOptions::PrependIfRankCollision, options.PrependIfRankCollision());

        RETURN_IF_FAILED(AddPackageDependency(mddPackageDependencyId, mddRank, mddOptions, packageDependencyContext, packageFullName));
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

    inline HRESULT GetResolvedPackageFullNameForPackageDependency2(
        _In_ PCWSTR /*packageDependencyId*/,
        _Outptr_result_maybenull_ PWSTR* /*packageFullName*/)
    {
        //TODO:47775758 GetResolved2 RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), g_win11GetResolvedPackageFullNameForPackageDependency2);
        //TODO:47775758 GetResolved2 RETURN_IF_FAILED(MddCore::Win11::details::g_win11GetResolvedPackageFullNameForPackageDependency2(packageDependencyId, packageFullName));
        //TODO:47775758 GetResolved2 return S_OK;
        RETURN_WIN32(ERROR_NOT_SUPPORTED);
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
        if (MddCore::Win11::details::g_win11GetPackageGraphRevisionId())
        {
            return MddCore::Win11::details::g_win11GetPackageGraphRevisionId();
        }
        else
        {
            UINT32 revisionId{};
            UINT32 bufferLength{ sizeof(revisionId) };
            const HRESULT hr{ MddCore::Win11::details::g_win11GetCurrentPackageInfo3(0, MddCore::Win11::details::PackageInfo3Type_PackageInfoGeneration, &bufferLength, &revisionId, nullptr) };
            if (hr == HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE))
            {
                // No package graph
                return 0;
            }
            LOG_IF_FAILED_MSG(hr, "GetCurrentPackageInfo3 failed!");
            return revisionId;
        }
    }
}

inline HRESULT WINAPI MddWin11Initialize() noexcept
{
    if (!MddCore::Win11::IsSupported())
    {
        return S_OK;
    }

    //TODO:47775758 GetResolved2 auto win11GetResolvedPackageFullNameForPackageDependency2{ static_cast<decltype(&::GetResolvedPackageFullNameForPackageDependency2)>(nullptr) };
    HMODULE dllApisetAppmodelRuntime_1_7{};
    RETURN_IF_FAILED(MddCore::Win11::details::Load(L"api-ms-win-appmodel-runtime-l1-1-7.dll", dllApisetAppmodelRuntime_1_7));
    if (dllApisetAppmodelRuntime_1_7)
    {
        //TODO:47775758 GetResolved2 win11GetResolvedPackageFullNameForPackageDependency2 = GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_7, GetResolvedPackageFullNameForPackageDependency);
        //TODO:47775758 GetResolved2 RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), win11GetResolvedPackageFullNameForPackageDependency2);
    }

    auto win11GetPackageGraphRevisionId{ static_cast<decltype(&::GetPackageGraphRevisionId)>(nullptr) };
    HMODULE dllApisetAppmodelRuntime_1_6{};
    RETURN_IF_FAILED(MddCore::Win11::details::Load(L"api-ms-win-appmodel-runtime-l1-1-6.dll", dllApisetAppmodelRuntime_1_6));
    if (dllApisetAppmodelRuntime_1_6)
    {
        win11GetPackageGraphRevisionId = GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_6, GetPackageGraphRevisionId);
        RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), win11GetPackageGraphRevisionId);
    }

    HMODULE dllApisetAppmodelRuntime_1_5{ LoadLibraryExW(L"api-ms-win-appmodel-runtime-l1-1-5.dll", nullptr, 0) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), dllApisetAppmodelRuntime_1_5);
    auto win11TryCreatePackageDependency{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_5, TryCreatePackageDependency) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), win11TryCreatePackageDependency);
    auto win11DeletePackageDependency{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_5, DeletePackageDependency) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), win11DeletePackageDependency);
    auto win11AddPackageDependency{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_5, AddPackageDependency) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), win11AddPackageDependency);
    auto win11RemovePackageDependency{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_5, RemovePackageDependency) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), win11RemovePackageDependency);
    auto win11GetResolvedPackageFullNameForPackageDependency{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_5, GetResolvedPackageFullNameForPackageDependency) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), win11GetResolvedPackageFullNameForPackageDependency);
    auto win11GetIdForPackageDependencyContext{ GetProcAddressByFunctionDeclaration(dllApisetAppmodelRuntime_1_5, GetIdForPackageDependencyContext) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), win11GetIdForPackageDependencyContext);
    auto win11GetCurrentPackageInfo3{ reinterpret_cast<decltype(MddCore::Win11::details::g_win11GetCurrentPackageInfo3)>(GetProcAddress(dllApisetAppmodelRuntime_1_5, "GetCurrentPackageInfo3")) };
    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), win11GetCurrentPackageInfo3);

    // Success
    MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_7 = dllApisetAppmodelRuntime_1_7;
    //TODO:47775758 GetResolved2 MddCore::Win11::details::g_win11GetResolvedPackageFullNameForPackageDependency2 = win11GetResolvedPackageFullNameForPackageDependency2;
    //
    MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_6 = dllApisetAppmodelRuntime_1_6;
    MddCore::Win11::details::g_win11GetPackageGraphRevisionId = win11GetPackageGraphRevisionId;
    //
    MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_5 = dllApisetAppmodelRuntime_1_5;
    MddCore::Win11::details::g_win11TryCreatePackageDependency = win11TryCreatePackageDependency;
    MddCore::Win11::details::g_win11DeletePackageDependency = win11DeletePackageDependency;
    MddCore::Win11::details::g_win11AddPackageDependency = win11AddPackageDependency;
    MddCore::Win11::details::g_win11RemovePackageDependency = win11RemovePackageDependency;
    MddCore::Win11::details::g_win11GetResolvedPackageFullNameForPackageDependency = win11GetResolvedPackageFullNameForPackageDependency;
    MddCore::Win11::details::g_win11GetIdForPackageDependencyContext = win11GetIdForPackageDependencyContext;
    MddCore::Win11::details::g_win11GetCurrentPackageInfo3 = win11GetCurrentPackageInfo3;
    return S_OK;
}

inline HRESULT WINAPI MddWin11Shutdown() noexcept
{
    if (MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_7)
    {
        //TODO:47775758 GetResolved2 MddCore::Win11::details::g_win11GetResolvedPackageFullNameForPackageDependency2 = nullptr;
        FreeLibrary(MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_7);
        MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_7 = nullptr;
    }

    if (MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_6)
    {
        MddCore::Win11::details::g_win11GetPackageGraphRevisionId = nullptr;
        FreeLibrary(MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_6);
        MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_6 = nullptr;
    }

    if (MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_5)
    {
        MddCore::Win11::details::g_win11TryCreatePackageDependency = nullptr;
        MddCore::Win11::details::g_win11DeletePackageDependency = nullptr;
        MddCore::Win11::details::g_win11AddPackageDependency = nullptr;
        MddCore::Win11::details::g_win11RemovePackageDependency = nullptr;
        MddCore::Win11::details::g_win11GetResolvedPackageFullNameForPackageDependency = nullptr;
        MddCore::Win11::details::g_win11GetIdForPackageDependencyContext = nullptr;
        MddCore::Win11::details::g_win11GetCurrentPackageInfo3 = nullptr;
        FreeLibrary(MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_5);
        MddCore::Win11::details::g_dllApisetAppmodelRuntime_1_5 = nullptr;
    }
    return S_OK;
}

#endif // MDDWIN11DYNAMICDEPENDENCY_H
