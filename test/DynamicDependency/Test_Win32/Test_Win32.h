// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

namespace Test::DynamicDependency
{
	class Test_Win32
	{
	public:
        BEGIN_TEST_CLASS(Test_Win32)
            //TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            //TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(Setup);
        TEST_CLASS_CLEANUP(Cleanup);

        TEST_METHOD(Create_Delete);

        TEST_METHOD(Delete_Null);
        TEST_METHOD(Delete_NotFound);

        TEST_METHOD(FullLifecycle_ProcessLifetime_Framework_WindowsAppRuntime);
        TEST_METHOD(FullLifecycle_ProcessLifetime_Frameworks_WindowsAppRuntime_MathAdd);
        TEST_METHOD(FullLifecycle_FilePathLifetime_Frameworks_WindowsAppRuntime_MathAdd);
        TEST_METHOD(FullLifecycle_RegistryLifetime_Frameworks_WindowsAppRuntime_MathAdd);

        TEST_METHOD(Add_Rank_A0_B10);
        TEST_METHOD(Add_Rank_B0prepend_A0);
        TEST_METHOD(Add_Rank_Bneg10_A0);

        TEST_METHOD(Create_FilePathLifetime_NoExist);
        TEST_METHOD(Create_RegistryLifetime_NoExist);
        TEST_METHOD(Create_DoNotVerifyDependencyResolution);

        TEST_METHOD(Create_Add_Architectures_Explicit);
        TEST_METHOD(Create_Add_Architectures_Current);

        TEST_METHOD(GetResolvedPackageFullName_Null);
        TEST_METHOD(GetResolvedPackageFullName_NotFound);

        TEST_METHOD(GetIdForPackageDependencyContext_Null);
        TEST_METHOD(GetIdForPackageDependencyContext);

        TEST_METHOD(WinRTReentrancy);

    private:
        static void VerifyPackageDependency(
            PCWSTR packageDependencyId,
            const HRESULT expectedHR,
            PCWSTR expectedPackageFullName = nullptr);

        static void VerifyPackageDependency(
            PCWSTR packageDependencyId,
            const HRESULT expectedHR,
            const std::wstring& expectedPackageFullName);

        static void VerifyPathEnvironmentVariable(PCWSTR path);

        static void VerifyPathEnvironmentVariable(PCWSTR path1, PCWSTR path);

        static void VerifyPathEnvironmentVariable(PCWSTR path1, PCWSTR path2, PCWSTR path);

        static void VerifyPathEnvironmentVariable(PCWSTR path1, PCWSTR path2, PCWSTR path3, PCWSTR path);

        static void VerifyPathEnvironmentVariable(const std::wstring& path1, PCWSTR path);

        static void VerifyPathEnvironmentVariable(const std::wstring& path1, const std::wstring& path2, PCWSTR path);

        static void VerifyPathEnvironmentVariable(const std::wstring& path1, const std::wstring& path2, const std::wstring& path3, PCWSTR path);

        static void VerifyPackageInPackageGraph(
            const std::wstring& packageFullName,
            const HRESULT expectedHR);

        static void VerifyPackageNotInPackageGraph(
            const std::wstring& packageFullName,
            const HRESULT expectedHR);

        static HRESULT GetCurrentPackageInfo(
            UINT32& packageInfoCount,
            const PACKAGE_INFO*& packageInfo,
            wil::unique_cotaskmem_ptr<BYTE[]>& buffer);

        static HRESULT GetCurrentPackageInfo(
            const UINT32 flags,
            const PackagePathType packagePathType,
            UINT32& packageInfoCount,
            const PACKAGE_INFO*& packageInfo,
            wil::unique_cotaskmem_ptr<BYTE[]>& buffer);

        static int FindPackageFullNameInPackageInfoArray(
            const std::wstring& packageFullName,
            const size_t packageInfoCount,
            const PACKAGE_INFO* packageInfo);

    private:
        // Overloads and conveniences for TryCreate to simplify test readability
        wil::unique_process_heap_string Mdd_TryCreate(
            PCWSTR packageFamilyName,
            const MddPackageDependencyLifetimeKind lifetimeKind = MddPackageDependencyLifetimeKind::Process,
            PCWSTR lifetimeArtifact = nullptr,
            MddCreatePackageDependencyOptions options = MddCreatePackageDependencyOptions::None);

        wil::unique_process_heap_string Mdd_TryCreate(
            const HRESULT expectedHR,
            PCWSTR packageFamilyName,
            const MddPackageDependencyLifetimeKind lifetimeKind = MddPackageDependencyLifetimeKind::Process,
            PCWSTR lifetimeArtifact = nullptr,
            MddCreatePackageDependencyOptions options = MddCreatePackageDependencyOptions::None);

        wil::unique_process_heap_string Mdd_TryCreate(
            const HRESULT expectedHR,
            PCWSTR packageFamilyName,
            MddPackageDependencyProcessorArchitectures architectures,
            const MddPackageDependencyLifetimeKind lifetimeKind = MddPackageDependencyLifetimeKind::Process,
            PCWSTR lifetimeArtifact = nullptr,
            MddCreatePackageDependencyOptions options = MddCreatePackageDependencyOptions::None);

        wil::unique_process_heap_string Mdd_TryCreate_WindowsAppRuntimeFramework(
            const MddPackageDependencyLifetimeKind lifetimeKind = MddPackageDependencyLifetimeKind::Process,
            PCWSTR lifetimeArtifact = nullptr);

        wil::unique_process_heap_string Mdd_TryCreate_FrameworkMathAdd(
            MddCreatePackageDependencyOptions options);

        wil::unique_process_heap_string Mdd_TryCreate_FrameworkMathAdd(
            const MddPackageDependencyLifetimeKind lifetimeKind = MddPackageDependencyLifetimeKind::Process,
            PCWSTR lifetimeArtifact = nullptr);

        wil::unique_process_heap_string Mdd_TryCreate_FrameworkMathAdd(
            const MddPackageDependencyProcessorArchitectures architectures,
            const MddPackageDependencyLifetimeKind lifetimeKind = MddPackageDependencyLifetimeKind::Process,
            PCWSTR lifetimeArtifact = nullptr);

        wil::unique_process_heap_string Mdd_TryCreate_FrameworkMathAdd(
            const HRESULT expectedHR,
            const MddPackageDependencyLifetimeKind lifetimeKind = MddPackageDependencyLifetimeKind::Process,
            PCWSTR lifetimeArtifact = nullptr,
            MddCreatePackageDependencyOptions options = MddCreatePackageDependencyOptions::None);

        wil::unique_process_heap_string Mdd_TryCreate_FrameworkWidgets(
            MddCreatePackageDependencyOptions options);

        wil::unique_process_heap_string Mdd_TryCreate_FrameworkWidgets(
            const MddPackageDependencyLifetimeKind lifetimeKind = MddPackageDependencyLifetimeKind::Process,
            PCWSTR lifetimeArtifact = nullptr);

        wil::unique_process_heap_string Mdd_TryCreate_FrameworkWidgets(
            const MddPackageDependencyProcessorArchitectures architectures,
            const MddPackageDependencyLifetimeKind lifetimeKind = MddPackageDependencyLifetimeKind::Process,
            PCWSTR lifetimeArtifact = nullptr);

        wil::unique_process_heap_string Mdd_TryCreate_FrameworkWidgets(
            const HRESULT expectedHR,
            const MddPackageDependencyLifetimeKind lifetimeKind = MddPackageDependencyLifetimeKind::Process,
            PCWSTR lifetimeArtifact = nullptr,
            MddCreatePackageDependencyOptions options = MddCreatePackageDependencyOptions::None);

    private:
        // Overloads and conveniences for Add to simplify test readability
        MDD_PACKAGEDEPENDENCY_CONTEXT Mdd_Add(
            PCWSTR packageDependencyId);

        MDD_PACKAGEDEPENDENCY_CONTEXT Mdd_Add(
            const HRESULT expectedHR,
            PCWSTR packageDependencyId);

        MDD_PACKAGEDEPENDENCY_CONTEXT Mdd_Add(
            PCWSTR packageDependencyId,
            wil::unique_process_heap_string& packageFullName);

        MDD_PACKAGEDEPENDENCY_CONTEXT Mdd_Add(
            PCWSTR packageDependencyId,
            const INT32 rank,
            wil::unique_process_heap_string& packageFullName);

        MDD_PACKAGEDEPENDENCY_CONTEXT Mdd_Add(
            PCWSTR packageDependencyId,
            const INT32 rank,
            const MddAddPackageDependencyOptions options,
            wil::unique_process_heap_string& packageFullName);

        MDD_PACKAGEDEPENDENCY_CONTEXT Mdd_Add(
            const HRESULT expectedHR,
            PCWSTR packageDependencyId,
            const INT32 rank,
            const MddAddPackageDependencyOptions options,
            wil::unique_process_heap_string& packageFullName);

    private:
        static HANDLE File_CreateTemporary(
            const std::filesystem::path& filename);

    private:
        static HKEY Registry_CreateKey(
            const std::wstring& key);

        static void Registry_DeleteKey(
            const std::wstring& key);

        static HKEY Registry_Key_Parse(
            const std::wstring& key,
            PCWSTR& subkey);

        static HKEY Registry_Key_Parse(
            const std::wstring& key,
            size_t& offsetToSubkey);

    private:
        static std::wstring GetPathEnvironmentVariable();

        static std::wstring GetPathEnvironmentVariableMinusPathPrefix(
            PCWSTR pathPrefix);

        static std::wstring GetPathEnvironmentVariableMinusPathPrefix(
            const std::wstring& pathPrefix);

        static std::wstring GetPathEnvironmentVariableMinusWindowsAppRuntimeFramework();

    private:
        static MddPackageDependencyProcessorArchitectures GetCurrentArchitectureAsFilter();

    private:
        static void VerifyPackageGraphRevisionId(
            const UINT32 expectedPackageGraphRevisionId);

        static void VerifyGenerationId(
            const UINT32 expectedGenerationId);

    private:
        static wil::unique_hmodule m_bootstrapDll;
    };

	class Test_Win32_Elevated : Test_Win32
	{
	public:
        BEGIN_TEST_CLASS(Test_Win32_Elevated)
            //TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            //TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
            TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(Setup_Elevated)
        {
            return Setup();
        }
        TEST_CLASS_CLEANUP(Cleanup_Elevated)
        {
            return Cleanup();
        }

        TEST_METHOD(Create_Delete_Elevated)
        {
            Create_Delete();
        }

        TEST_METHOD(Delete_Null_Elevated)
        {
            Delete_Null();
        }
        TEST_METHOD(Delete_NotFound_Elevated)
        {
            Delete_NotFound();
        }

        TEST_METHOD(FullLifecycle_ProcessLifetime_Framework_WindowsAppRuntime_Elevated)
        {
            FullLifecycle_ProcessLifetime_Framework_WindowsAppRuntime();
        }
        TEST_METHOD(FullLifecycle_ProcessLifetime_Frameworks_WindowsAppRuntime_MathAdd_Elevated)
        {
            FullLifecycle_ProcessLifetime_Frameworks_WindowsAppRuntime_MathAdd();
        }
        TEST_METHOD(FullLifecycle_FilePathLifetime_Frameworks_WindowsAppRuntime_MathAdd_Elevated)
        {
            FullLifecycle_FilePathLifetime_Frameworks_WindowsAppRuntime_MathAdd();
        }
        TEST_METHOD(FullLifecycle_RegistryLifetime_Frameworks_WindowsAppRuntime_MathAdd_Elevated)
        {
            FullLifecycle_RegistryLifetime_Frameworks_WindowsAppRuntime_MathAdd();
        }

        TEST_METHOD(Add_Rank_A0_B10_Elevated)
        {
            Add_Rank_A0_B10();
        }
        TEST_METHOD(Add_Rank_B0prepend_A0_Elevated)
        {
            Add_Rank_B0prepend_A0();
        }
        TEST_METHOD(Add_Rank_Bneg10_A0_Elevated)
        {
            Add_Rank_Bneg10_A0();
        }

        TEST_METHOD(Create_FilePathLifetime_NoExist_Elevated)
        {
            Create_FilePathLifetime_NoExist();
        }
        TEST_METHOD(Create_RegistryLifetime_NoExist_Elevated)
        {
            Create_RegistryLifetime_NoExist();
        }
        TEST_METHOD(Create_DoNotVerifyDependencyResolution_Elevated)
        {
            Create_DoNotVerifyDependencyResolution();
        }

        TEST_METHOD(Create_Add_Architectures_Explicit_Elevated)
        {
            Create_Add_Architectures_Explicit();
        }
        TEST_METHOD(Create_Add_Architectures_Current_Elevated)
        {
            Create_Add_Architectures_Current();
        }

        TEST_METHOD(GetResolvedPackageFullName_Null_Elevated)
        {
            GetResolvedPackageFullName_Null();
        }
        TEST_METHOD(GetResolvedPackageFullName_NotFound_Elevated)
        {
            GetResolvedPackageFullName_NotFound();
        }

        TEST_METHOD(GetIdForPackageDependencyContext_Null_Elevated)
        {
            GetIdForPackageDependencyContext_Null();
        }
        TEST_METHOD(GetIdForPackageDependencyContext_Elevated)
        {
            GetIdForPackageDependencyContext();
        }

        TEST_METHOD(WinRTReentrancy_Elevated)
        {
            WinRTReentrancy();
        }
    };
}
