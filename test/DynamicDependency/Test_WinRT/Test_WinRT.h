// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

namespace Test::DynamicDependency
{
	TEST_CLASS(Test_WinRT)
	{
	public:
        TEST_CLASS_INITIALIZE(Setup);
        TEST_CLASS_CLEANUP(Cleanup);

        TEST_METHOD(Create_Delete);

        TEST_METHOD(GetFromId_Empty);
        TEST_METHOD(GetFromId_NotFound);

        TEST_METHOD(FullLifecycle_ProcessLifetime_Framework_ProjectReunion);
        TEST_METHOD(FullLifecycle_ProcessLifetime_Frameworks_ProjectReunion_MathAdd);
        TEST_METHOD(FullLifecycle_FilePathLifetime_Frameworks_ProjectReunion_MathAdd);
        TEST_METHOD(FullLifecycle_RegistryLifetime_Frameworks_ProjectReunion_MathAdd);

        TEST_METHOD(Add_Rank_A0_B10);
        TEST_METHOD(Add_Rank_B0prepend_A0);
        TEST_METHOD(Add_Rank_Bneg10_A0);

        TEST_METHOD(Create_FilePathLifetime_NoExist);
        TEST_METHOD(Create_RegistryLifetime_NoExist);
        TEST_METHOD(Create_DoNotVerifyDependencyResolution);

        TEST_METHOD(Create_Add_Architectures_Explicit);
        TEST_METHOD(Create_Add_Architectures_Current);

    private:
        static void VerifyPackageDependency(
            PCWSTR packageDependencyId,
            const HRESULT expectedHR,
            PCWSTR expectedPackageFullName = nullptr);

        static void VerifyPackageDependency(
            PCWSTR packageDependencyId,
            const HRESULT expectedHR,
            const std::wstring& expectedPackageFullName);

        void VerifyPackageDependency(
            const winrt::hstring& packageDependencyId,
            const HRESULT expectedHR);

        static void VerifyPackageDependency(
            const winrt::hstring& packageDependencyId,
            const HRESULT expectedHR,
            const winrt::hstring& expectedPackageFullName);

        static void VerifyPackageDependency(
            const winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependency& packageDependency,
            const HRESULT expectedHR);

        static void VerifyPackageDependency(
            const winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependency& packageDependency,
            const HRESULT expectedHR,
            const winrt::hstring& expectedPackageFullName);

        static void VerifyPathEnvironmentVariable(PCWSTR path);

        static void VerifyPathEnvironmentVariable(PCWSTR path1, PCWSTR path);

        static void VerifyPathEnvironmentVariable(PCWSTR path1, PCWSTR path2, PCWSTR path);

        static void VerifyPathEnvironmentVariable(PCWSTR path1, PCWSTR path2, PCWSTR path3, PCWSTR path);

        static void VerifyPathEnvironmentVariable(const std::wstring& path1, PCWSTR path);

        static void VerifyPathEnvironmentVariable(const std::wstring& path1, const std::wstring& path2, PCWSTR path);

        static void VerifyPathEnvironmentVariable(const std::wstring& path1, const std::wstring& path2, const std::wstring& path3, PCWSTR path);

        static void VerifyPathEnvironmentVariable(const winrt::hstring& path1, PCWSTR path);

        static void VerifyPathEnvironmentVariable(const winrt::hstring& path1, const winrt::hstring& path2, PCWSTR path);

        static void VerifyPathEnvironmentVariable(const winrt::hstring& path1, const winrt::hstring& path2, const winrt::hstring& path3, PCWSTR path);

        static void VerifyPackageInPackageGraph(
            const winrt::hstring& packageFullName,
            const HRESULT expectedHR);

        static void VerifyPackageNotInPackageGraph(
            const winrt::hstring& packageFullName,
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
            const winrt::hstring& packageFullName,
            const size_t packageInfoCount,
            const PACKAGE_INFO* packageInfo);

    private:
        // Overloads and conveniences for TryCreate to simplify test readability
        winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependency _Create(
            const winrt::hstring& packageFamilyName,
            const winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind lifetimeKind = winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::Process,
            PCWSTR lifetimeArtifact = nullptr);

        winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependency _Create(
            const HRESULT expectedHR,
            const winrt::hstring& packageFamilyName,
            const winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind lifetimeKind = winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::Process,
            PCWSTR lifetimeArtifact = nullptr);

        winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependency _Create(
            const HRESULT expectedHR,
            const winrt::hstring& packageFamilyName,
            const winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures architectures,
            const winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind lifetimeKind = winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::Process,
            PCWSTR lifetimeArtifact = nullptr);

        winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependency _Create(
            const HRESULT expectedHR,
    const winrt::hstring& packageFamilyName,
            winrt::Microsoft::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions& options);

        winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependency _Create_ProjectReunionFramework(
            const winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind lifetimeKind = winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::Process,
            PCWSTR lifetimeArtifact = nullptr);

        winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependency _Create_FrameworkMathAdd();

        winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependency _Create_FrameworkMathAdd(
            const winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind lifetimeKind,
            PCWSTR lifetimeArtifact = nullptr);

        winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependency _Create_FrameworkMathAdd(
            const winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures architectures,
            const winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind lifetimeKind = winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::Process,
            PCWSTR lifetimeArtifact = nullptr);

        winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependency _Create_FrameworkMathAdd(
            const HRESULT expectedHR,
            const winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind lifetimeKind = winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::Process,
            PCWSTR lifetimeArtifact = nullptr);

        winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependency _Create_FrameworkMathAdd(
            winrt::Microsoft::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions& options);

    private:
        // Overloads and conveniences for Add to simplify test readability
        winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyContext _Add(
            winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependency packageDependency);

        winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyContext _Add(
            const HRESULT expectedHR,
            winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependency packageDependency);

        winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyContext _Add(
            winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependency packageDependency,
            const INT32 rank);

        winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyContext _Add(
            const HRESULT expectedHR,
            winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependency packageDependency,
            const INT32 rank);

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

        static std::wstring GetPathEnvironmentVariableMinusProjectReunionFramework();

    private:
        static winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures GetCurrentArchitectureAsFilter();

    private:
        static wil::unique_hmodule m_bootstrapDll;
    };
}
