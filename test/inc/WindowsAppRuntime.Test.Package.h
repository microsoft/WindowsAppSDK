// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __WINDOWSAPPRUNTIME_TEST_PACKAGE_H
#define __WINDOWSAPPRUNTIME_TEST_PACKAGE_H

#include <appmodel.h>

#include <WindowsAppRuntime.Test.FileSystem.h>
#include <winrt/Windows.Management.Deployment.h>
#include <winrt/Windows.ApplicationModel.h>
#include <WexTestClass.h>

#define WINDOWSAPPRUNTIME_TEST_METADATA_VERSION            0x0004000107AF014DLLu
#define WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_MAJOR      4
#define WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_MINOR      1
#define WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_BUILD      1967
#define WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_REVISION   333
#define WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_STRING     L"4.1.1967.333"
#define WINDOWSAPPRUNTIME_TEST_METADATA_RELEASE_STRING     L"4.1"

#define WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID            L"8wekyb3d8bbwe"

#define WINDOWSAPPRUNTIME_TEST_MSIX_FRAMEWORK_PACKAGE_NAME L"Microsoft.WindowsAppRuntime.Framework-4.1"
#define WINDOWSAPPRUNTIME_TEST_MSIX_DDLM_PACKAGE_NAME      L"Microsoft.WindowsAppRuntime.DDLM"
#define WINDOWSAPPRUNTIME_TEST_MSIX_MAIN_PACKAGE_NAME      L"Microsoft.WindowsAppRuntime.Main-4.1"
#define WINDOWSAPPRUNTIME_TEST_MSIX_SINGLETON_PACKAGE_NAME L"Microsoft.WindowsAppRuntime.Singleton"

#define WINDOWSAPPRUNTIME_TEST_MSIX_DEPLOYMENT_FRAMEWORK_PACKAGE_NAME L"Microsoft.WindowsAppRuntime.1.0-Test"
#define WINDOWSAPPRUNTIME_TEST_MSIX_DEPLOYMENT_MAIN_PACKAGE_NAME      L"Microsoft.WindowsAppRuntime.Main.1.0-Test"
#define WINDOWSAPPRUNTIME_TEST_MSIX_DEPLOYMENT_SINGLETON_PACKAGE_NAME L"Microsoft.WindowsAppRuntime.Singleton-Test"

#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_NAMEPREFIX     L"WindowsAppRuntime.Test.DDLM"
#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_VERSION        WINDOWSAPPRUNTIME_TEST_METADATA_VERSION
#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_VERSION_STRING WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_STRING
#define MSIX_PACKAGE_ARCHITECTURE_ARM       L"arm"
#define MSIX_PACKAGE_ARCHITECTURE_ARM64     L"arm64"
#define MSIX_PACKAGE_ARCHITECTURE_NEUTRAL   L"neutral"
#define MSIX_PACKAGE_ARCHITECTURE_X64       L"x64"
#define MSIX_PACKAGE_ARCHITECTURE_X86       L"x86"
#if defined(_M_X64)
#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_ARCHITECTURE   MSIX_PACKAGE_ARCHITECTURE_X64
#elif defined(_M_IX86)
#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_ARCHITECTURE   MSIX_PACKAGE_ARCHITECTURE_X86
#elif defined(_M_ARM64)
#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_ARCHITECTURE   MSIX_PACKAGE_ARCHITECTURE_ARM64
#elif defined(_M_ARM)
#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_ARCHITECTURE   MSIX_PACKAGE_ARCHITECTURE_ARM
#else
#   error "Unknown processor architecture"
#endif
#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_NAME           WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_NAMEPREFIX L"-" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_VERSION_STRING L"-" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_ARCHITECTURE
#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_PUBLISHERID    WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID
#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_FAMILYNAME     WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_NAME L"_" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_PUBLISHERID
#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_FULLNAME       WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_NAME L"_" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_VERSION_STRING L"_" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_ARCHITECTURE L"__" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_PUBLISHERID

namespace Test::Packages
{
namespace DynamicDependencyLifetimeManager
{
    constexpr PCWSTR c_PackageDirName = L"DynamicDependencyLifetimeManager";
    constexpr PCWSTR c_PackageNamePrefix = WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_NAMEPREFIX;
    constexpr PCWSTR c_PackagePublisherId = WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_PUBLISHERID;
    constexpr PCWSTR c_PackageFamilyName = WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_FAMILYNAME;
    constexpr PCWSTR c_PackageFullName = WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_FULLNAME;
    constexpr const PACKAGE_VERSION GetPackageVersion()
    {
        PACKAGE_VERSION version{};
        version.Major = WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_MAJOR;
        version.Minor = WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_MINOR;
        version.Build = WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_BUILD;
        version.Revision = WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_REVISION;
        return version;
    }
    constexpr const PACKAGE_VERSION c_Version = GetPackageVersion();

    constexpr const UINT32 GetPackageVersionMajorMinor()
    {
        return static_cast<UINT32>((GetPackageVersion().Major << 16) | GetPackageVersion().Minor);
    }
    constexpr const UINT32 c_Version_MajorMinor = GetPackageVersionMajorMinor();
}

namespace WindowsAppRuntimeFramework
{
    constexpr PCWSTR c_PackageDirName = L"Microsoft.WindowsAppRuntime.Framework";
    constexpr PCWSTR c_PackageMsixFilename = L"Microsoft.WindowsAppRuntime.Framework.msix";
    constexpr PCWSTR c_PackageNamePrefix = L"Microsoft.WindowsAppRuntime.Framework";
    constexpr PCWSTR c_PackageFamilyName = WINDOWSAPPRUNTIME_TEST_MSIX_FRAMEWORK_PACKAGE_NAME L"_" WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID;
    constexpr PCWSTR c_PackageFullName = WINDOWSAPPRUNTIME_TEST_MSIX_FRAMEWORK_PACKAGE_NAME L"_" WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_STRING L"_neutral__" WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID;
}

namespace DynamicDependencyDataStore
{
    constexpr PCWSTR c_PackageDirName = L"DynamicDependency.DataStore";
    constexpr PCWSTR c_PackageNamePrefix = L"WindowsAppRuntime.Test.DynDep.DataStore";
    constexpr PCWSTR c_PackageFamilyName = L"WindowsAppRuntime.Test.DynDep.DataStore-" WINDOWSAPPRUNTIME_TEST_METADATA_RELEASE_STRING "_" WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID;
    constexpr PCWSTR c_PackageFullName = L"WindowsAppRuntime.Test.DynDep.DataStore-" WINDOWSAPPRUNTIME_TEST_METADATA_RELEASE_STRING "_" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_VERSION_STRING L"_neutral__" WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID;
}
namespace WindowsAppRuntimeMain = DynamicDependencyDataStore;

namespace WindowsAppRuntimeSingleton
{
    constexpr PCWSTR c_PackageDirName = L"WindowsAppRuntime.Test.Singleton";
    constexpr PCWSTR c_PackageFamilyName = L"WindowsAppRuntime.Test.Singleton_" WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID;
    constexpr PCWSTR c_PackageFullName = L"WindowsAppRuntime.Test.Singleton_" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_VERSION_STRING L"_neutral__" WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID;
}

namespace DeploymentWindowsAppRuntimeFramework
{
    constexpr PCWSTR c_PackageDirName = L"Deployment.WindowsAppRuntime.Test.Framework";
    constexpr PCWSTR c_PackageFamilyName = WINDOWSAPPRUNTIME_TEST_MSIX_DEPLOYMENT_FRAMEWORK_PACKAGE_NAME L"_" WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID;
    constexpr PCWSTR c_PackageFullName = WINDOWSAPPRUNTIME_TEST_MSIX_DEPLOYMENT_FRAMEWORK_PACKAGE_NAME L"_" WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_STRING L"_neutral__" WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID;
}

namespace DeploymentWindowsAppRuntimeMain
{
    constexpr PCWSTR c_PackageDirName = L"Deployment.WindowsAppRuntime.Test.Main";
    constexpr PCWSTR c_PackageFamilyName = WINDOWSAPPRUNTIME_TEST_MSIX_DEPLOYMENT_MAIN_PACKAGE_NAME L"_" WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID;
    constexpr PCWSTR c_PackageFullName = WINDOWSAPPRUNTIME_TEST_MSIX_DEPLOYMENT_MAIN_PACKAGE_NAME L"_" WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_STRING L"_neutral__" WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID;
}

namespace DeploymentWindowsAppRuntimeSingleton
{
    constexpr PCWSTR c_PackageDirName = L"Deployment.WindowsAppRuntime.Test.Singleton";
    constexpr PCWSTR c_PackageFamilyName = WINDOWSAPPRUNTIME_TEST_MSIX_DEPLOYMENT_SINGLETON_PACKAGE_NAME L"_" WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID;
    constexpr PCWSTR c_PackageFullName = WINDOWSAPPRUNTIME_TEST_MSIX_DEPLOYMENT_SINGLETON_PACKAGE_NAME L"_" WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_STRING L"_neutral__" WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID;
}

template <typename T=std::wstring>
inline T GetPackagePath(PCWSTR packageFullName)
{
    UINT32 pathLength{};
    const auto rc{ ::GetPackagePathByFullName(packageFullName, &pathLength, nullptr) };
    if (rc == ERROR_NOT_FOUND)
    {
        return T{};
    }

    VERIFY_ARE_EQUAL(ERROR_INSUFFICIENT_BUFFER, rc);
    auto path{ wil::make_process_heap_string(nullptr, pathLength) };
    VERIFY_ARE_EQUAL(ERROR_SUCCESS, GetPackagePathByFullName(packageFullName, &pathLength, path.get()));
    return T{ path.get() };
}

template <typename T=std::wstring>
inline T GetStagedPackagePath(PCWSTR packageFullName)
{
    UINT32 pathLength{};
    const auto rc{ ::GetStagedPackagePathByFullName(packageFullName, &pathLength, nullptr) };
    if (rc == ERROR_NOT_FOUND)
    {
        return T{};
    }

    VERIFY_ARE_EQUAL(ERROR_INSUFFICIENT_BUFFER, rc);
    auto path{ wil::make_process_heap_string(nullptr, pathLength) };
    VERIFY_ARE_EQUAL(ERROR_SUCCESS, ::GetStagedPackagePathByFullName(packageFullName, &pathLength, path.get()));
    return T{ path.get() };
}

#if defined(__APPMODEL_IDENTITY_H)
inline bool IsPackageFamilyRegistered(PCWSTR packageFamilyName, uint64_t minVersion = 0)
{
    winrt::Windows::Management::Deployment::PackageManager packageManager;
    auto packages{ packageManager.FindPackagesForUser(winrt::hstring(), packageFamilyName) };
    for (const winrt::Windows::ApplicationModel::Package& package : packages)
    {
        if (minVersion == 0)
        {
            // Any package in the family is good enough for us
            return true;
        }
        const auto version{ package.Id().Version() };
        const ::AppModel::Identity::PackageVersion packageVersion{ version };
        if (packageVersion >= minVersion)
        {
            return true;
        }
    }
    return false;
}
#endif // defined(__APPMODEL_IDENTITY_H)

#if defined(__APPMODEL_IDENTITY_H)
inline bool IsPackageFamilyRegistered(PCWSTR packageFamilyName, winrt::Windows::ApplicationModel::PackageVersion minVersion)
{
    const ::AppModel::Identity::PackageVersion packageVersion{ minVersion };
    return IsPackageFamilyRegistered(packageFamilyName, packageVersion.Version);
}
#endif // defined(__APPMODEL_IDENTITY_H)

inline std::wstring GetPackagePath(const std::wstring& packageFullName)
{
    return GetPackagePath(packageFullName.c_str());
}

inline bool IsPackageRegistered(PCWSTR packageFullName)
{
    // Check if the package is registered to the current user via GetPackagePath().
    // GetPackagePath() fails if the package isn't registered to the current user.
    // Simplest and most portable test across the platforms we might run on
    const auto path = GetPackagePath(packageFullName);
    return !path.empty();
}

inline bool IsPackageStaged(PCWSTR packageFullName)
{
    // Check if the package is staged
    PackageOrigin packageOrigin{};
    const auto rc{ GetStagedPackageOrigin(packageFullName, &packageOrigin) };
    if (rc == ERROR_SUCCESS)
    {
        return true;
    }
    else if (rc == ERROR_APP_DATA_NOT_FOUND)
    {
        return false;
    }
    THROW_WIN32(rc);
}

inline bool IsPackageAvailable(PCWSTR packageFullName)
{
    // Check if the package is available for use
    // This means registered to the current user OR staged
    // NOTE: To check if a package is staged and not registered to the current user:
    //              bool isStaged = IsPackageAvailable(p) && !IsPackageRegistered(p)
    return IsPackageRegistered(packageFullName) || IsPackageStaged(packageFullName);
}

inline std::filesystem::path GetMsixPackagePath(PCWSTR packageDirName)
{
    // Build the target package's .msix filename. It's under the Solution's $(OutDir)
    // NOTE: It could live in ...\Something.msix\... or ...\Something\...
    auto solutionOutDirPath{ ::Test::FileSystem::GetSolutionOutDirPath() };

    // Filename is packagedirName plus .msix (if not already present)
    std::filesystem::path filename{ packageDirName };
    if (CompareStringOrdinal(filename.extension().c_str(), -1, L".msix", -1, TRUE) != CSTR_EQUAL)
    {
        filename += L".msix";
    }

    // Look in ...\Something.msix\...
    auto msix(solutionOutDirPath);
    msix /= packageDirName;
    msix += L".msix";
    msix /= filename;
    if (!std::filesystem::is_regular_file(msix))
    {
        // Look in ...\Something\...
        msix = solutionOutDirPath;
        msix /= packageDirName;
        msix /= filename;
        WIN32_FILE_ATTRIBUTE_DATA data{};
        const auto ok{ GetFileAttributesExW(msix.c_str(), GetFileExInfoStandard, &data) };
        const auto lastError{ ::GetLastError() };
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"GetFileAttributesExW(%ls):%d LastError:%u", msix.c_str(), static_cast<int>(ok), lastError));

        std::error_code errorcode{};
        auto isregularfile{ std::filesystem::is_regular_file(msix, errorcode) };
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"std::filesystem::is_regular_file(%ls):%ls error_code:%d %hs", msix.c_str(), isregularfile ? L"True" : L"False", errorcode.value(), errorcode.message().c_str()));

        //VERIFY_IS_TRUE(std::filesystem::is_regular_file(msix));
    }
    return msix.c_str();
}

inline winrt::Windows::Foundation::Uri GetMsixPackageUri(PCWSTR packageDirName)
{
    auto path{ GetMsixPackagePath(packageDirName) };
    return winrt::Windows::Foundation::Uri{ path.c_str() };
}

inline std::filesystem::path GetAppxManifestPackagePath(PCWSTR packageFullName)
{
    auto path{ GetStagedPackagePath<std::filesystem::path>(packageFullName) };
    return path / L"AppxManifest.xml";
}

inline winrt::Windows::Foundation::Uri GetAppxManifestPackageUri(PCWSTR packageFullName)
{
    auto path{ GetAppxManifestPackagePath(packageFullName) };
    return winrt::Windows::Foundation::Uri{ path.c_str() };
}

inline void AddPackage(PCWSTR packageDirName, PCWSTR packageFullName)
{
    auto msixUri{ GetMsixPackageUri(packageDirName) };

    winrt::Windows::Management::Deployment::PackageManager packageManager;
    auto options{ winrt::Windows::Management::Deployment::DeploymentOptions::None };
    auto deploymentResult{ packageManager.AddPackageAsync(msixUri, nullptr, options).get() };
    VERIFY_SUCCEEDED(deploymentResult.ExtendedErrorCode(), WEX::Common::String().Format(L"AddPackageAsync('%s') = 0x%0X %s", packageFullName, deploymentResult.ExtendedErrorCode(), deploymentResult.ErrorText().c_str()));
}

inline void AddPackageDefer(PCWSTR packageDirName, PCWSTR packageFullName)
{
    auto msixUri{ GetMsixPackageUri(packageDirName) };

    winrt::Windows::Management::Deployment::PackageManager packageManager;
    winrt::Windows::Management::Deployment::AddPackageOptions options;
    options.DeferRegistrationWhenPackagesAreInUse(true);
    auto deploymentResult{ packageManager.AddPackageByUriAsync(msixUri, options).get() };
    VERIFY_SUCCEEDED(deploymentResult.ExtendedErrorCode(), WEX::Common::String().Format(L"AddPackageByUriAsync('%s') = 0x%0X %s", packageFullName, deploymentResult.ExtendedErrorCode(), deploymentResult.ErrorText().c_str()));
}

inline void AddPackageIfNecessary(PCWSTR packageDirName, PCWSTR packageFullName)
{
    if (IsPackageRegistered(packageFullName))
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"AddPackageIfNecessary: %s already registered", packageFullName));
    }
    else
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"AddPackageIfNecessary: %s not registered, adding...", packageFullName));
        AddPackage(packageDirName, packageFullName);
    }
}

inline void AddPackageDeferIfNecessary(PCWSTR packageDirName, PCWSTR packageFullName)
{
    if (IsPackageRegistered(packageFullName))
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"AddPackageDeferIfNecessary: %s already registered", packageFullName));
    }
    else
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"AddPackageDeferIfNecessary: %s not registered, adding...", packageFullName));
        AddPackageDefer(packageDirName, packageFullName);
    }
}

inline void StagePackage(PCWSTR packageDirName, PCWSTR packageFullName)
{
    auto msixUri{ GetMsixPackageUri(packageDirName) };

    winrt::Windows::Management::Deployment::PackageManager packageManager;
    auto options{ winrt::Windows::Management::Deployment::DeploymentOptions::None };
    auto deploymentResult{ packageManager.StagePackageAsync(msixUri, nullptr, options).get() };
    VERIFY_SUCCEEDED(deploymentResult.ExtendedErrorCode(), WEX::Common::String().Format(L"StagePackageAsync('%s') = 0x%0X %s", packageFullName, deploymentResult.ExtendedErrorCode(), deploymentResult.ErrorText().c_str()));
}

inline void StagePackageIfNecessary(PCWSTR packageDirName, PCWSTR packageFullName)
{
    if (IsPackageAvailable(packageFullName))
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"StagePackageIfNecessary: %s already staged", packageFullName));
    }
    else
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"StagePackageIfNecessary: %s not staged, staging...", packageFullName));
        StagePackage(packageDirName, packageFullName);
    }
}

inline void RegisterPackage(PCWSTR packageFullName)
{
    winrt::hstring mainPackageFullName{ packageFullName };

    winrt::Windows::Management::Deployment::PackageManager packageManager;
    auto options{ winrt::Windows::Management::Deployment::DeploymentOptions::None };
    auto deploymentResult{ packageManager.RegisterPackageByFullNameAsync(mainPackageFullName, nullptr, options).get() };
    VERIFY_SUCCEEDED(deploymentResult.ExtendedErrorCode(), WEX::Common::String().Format(L"RegisterPackageByFullNameAsync('%s') = 0x%0X %s", packageFullName, deploymentResult.ExtendedErrorCode(), deploymentResult.ErrorText().c_str()));
}

inline void RegisterPackageIfNecessary(PCWSTR packageFullName)
{
    if (IsPackageRegistered(packageFullName))
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"RegisterPackageIfNecessary: %s already registered", packageFullName));
    }
    else
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"RegisterPackageIfNecessary: %s not registered, adding...", packageFullName));
        RegisterPackage(packageFullName);
    }
}

inline void RemovePackage(PCWSTR packageFullName)
{
    winrt::Windows::Management::Deployment::PackageManager packageManager;
    auto deploymentResult{ packageManager.RemovePackageAsync(packageFullName).get() };
    if (!deploymentResult)
    {
        VERIFY_FAIL(WEX::Common::String().Format(L"RemovePackageAsync('%s') = 0x%0X %s", packageFullName, deploymentResult.ExtendedErrorCode(), deploymentResult.ErrorText().c_str()));
    }
}

inline void RemovePackageIfNecessary(PCWSTR packageFullName)
{
    if (IsPackageRegistered(packageFullName))
    {
        RemovePackage(packageFullName);
    }
}

inline bool IsPackageProvisioned(PCWSTR packageFamilyName)
{
    // We have no random access check for a specific package family
    // so we'll have to brute force it by scanning the list of all
    // provisioned packages for the one we're interested in
    winrt::Windows::Management::Deployment::PackageManager packageManager;
    const auto provisionedPackages{ packageManager.FindProvisionedPackages() };
    for (const winrt::Windows::ApplicationModel::Package& provisionedPackage: provisionedPackages)
    {
        if (CompareStringOrdinal(packageFamilyName, -1, provisionedPackage.Id().FamilyName().c_str(), -1, TRUE) == CSTR_EQUAL)
        {
            return true;
        }
    }
    return false;
}

inline void ProvisionPackage(PCWSTR packageFamilyName)
{
    winrt::Windows::Management::Deployment::PackageManager packageManager;
    auto deploymentResult{ packageManager.ProvisionPackageForAllUsersAsync(packageFamilyName).get() };
    VERIFY_SUCCEEDED(deploymentResult.ExtendedErrorCode(), WEX::Common::String().Format(L"ProvisionPackageForAllUsersAsync('%s') = 0x%0X %s", packageFamilyName, deploymentResult.ExtendedErrorCode(), deploymentResult.ErrorText().c_str()));
}

inline void ProvisionPackageIfNecessary(PCWSTR packageFamilyName)
{
    if (IsPackageProvisioned(packageFamilyName))
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"ProvisionPackageIfNecessary: %s already provisioned", packageFamilyName));
    }
    else
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"ProvisionPackageIfNecessary: %s not provisioned, provisioning...", packageFamilyName));
        ProvisionPackage(packageFamilyName);
    }
}

inline void DeprovisionPackage(PCWSTR packageFamilyName)
{
    winrt::Windows::Management::Deployment::PackageManager packageManager;
    auto deploymentResult{ packageManager.DeprovisionPackageForAllUsersAsync(packageFamilyName).get() };
    VERIFY_SUCCEEDED(deploymentResult.ExtendedErrorCode(), WEX::Common::String().Format(L"DeprovisionPackageForAllUsersAsync('%s') = 0x%0X %s", packageFamilyName, deploymentResult.ExtendedErrorCode(), deploymentResult.ErrorText().c_str()));
}

inline void DeprovisionPackageIfNecessary(PCWSTR packageFamilyName)
{
    if (IsPackageProvisioned(packageFamilyName))
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"DeprovisionPackageIfNecessary: %s is provisioned, deprovisioning...", packageFamilyName));
        DeprovisionPackage(packageFamilyName);
    }
    else
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"DeprovisionPackageIfNecessary: %s not provisioned", packageFamilyName));
    }
}

inline void AddPackage_DynamicDependencyLifetimeManager()
{
    AddPackage(Test::Packages::DynamicDependencyLifetimeManager::c_PackageDirName, Test::Packages::DynamicDependencyLifetimeManager::c_PackageFullName);
}

inline void RemovePackage_DynamicDependencyLifetimeManager()
{
    // Best-effort removal. PackageManager.RemovePackage errors if the package
    // is not registered, but if it's not registered we're good. "'Tis the destination
    // that matters, not the journey" so regardless how much or little work
    // we need do, we're happy as long as the package isn't registered when we're done
    //
    // Thus, do a *IfNecessary removal
    RemovePackageIfNecessary(Test::Packages::DynamicDependencyLifetimeManager::c_PackageFullName);
}

inline bool IsPackageRegistered_DynamicDependencyLifetimeManager()
{
    return IsPackageRegistered(Test::Packages::DynamicDependencyLifetimeManager::c_PackageFullName);
}

inline void AddPackage_WindowsAppRuntimeFramework()
{
    AddPackage(Test::Packages::WindowsAppRuntimeFramework::c_PackageDirName, Test::Packages::WindowsAppRuntimeFramework::c_PackageFullName);
}

inline void RemovePackage_WindowsAppRuntimeFramework()
{
    // Best-effort removal. PackageManager.RemovePackage errors if the package
    // is not registered, but if it's not registered we're good. "'Tis the destination
    // that matters, not the journey" so regardless how much or little work
    // we need do, we're happy as long as the package isn't registered when we're done
    //
    // Thus, do a *IfNecessary removal
    RemovePackageIfNecessary(Test::Packages::WindowsAppRuntimeFramework::c_PackageFullName);
}

inline bool IsPackageRegistered_WindowsAppRuntimeFramework()
{
    return IsPackageRegistered(Test::Packages::WindowsAppRuntimeFramework::c_PackageFullName);
}

inline void AddPackage_DynamicDependencyDataStore()
{
    AddPackage(Test::Packages::DynamicDependencyDataStore::c_PackageDirName, Test::Packages::DynamicDependencyDataStore::c_PackageFullName);
}

inline void RemovePackage_DynamicDependencyDataStore()
{
    // Best-effort removal. PackageManager.RemovePackage errors if the package
    // is not registered, but if it's not registered we're good. "'Tis the destination
    // that matters, not the journey" so regardless how much or little work
    // we need do, we're happy as long as the package isn't registered when we're done
    //
    // Thus, do a *IfNecessary removal
    RemovePackageIfNecessary(Test::Packages::DynamicDependencyDataStore::c_PackageFullName);
}

inline bool IsPackageRegistered_DynamicDependencyDataStore()
{
    return IsPackageRegistered(Test::Packages::DynamicDependencyDataStore::c_PackageFullName);
}

inline void AddPackage_WindowsAppRuntimeSingleton()
{
    AddPackage(Test::Packages::WindowsAppRuntimeSingleton::c_PackageDirName, Test::Packages::WindowsAppRuntimeSingleton::c_PackageFullName);
}

inline void RemovePackage_WindowsAppRuntimeSingleton()
{
    // Best-effort removal. PackageManager.RemovePackage errors if the package
    // is not registered, but if it's not registered we're good. "'Tis the destination
    // that matters, not the journey" so regardless how much or little work
    // we need do, we're happy as long as the package isn't registered when we're done
    //
    // Thus, do a *IfNecessary removal
    RemovePackageIfNecessary(Test::Packages::WindowsAppRuntimeSingleton::c_PackageFullName);
}

inline bool IsPackageRegistered_WindowsAppRuntimeSingleton()
{
    return IsPackageRegistered(Test::Packages::WindowsAppRuntimeSingleton::c_PackageFullName);
}

inline void AddPackage_DeploymentWindowsAppRuntimeFramework()
{
    AddPackage(Test::Packages::DeploymentWindowsAppRuntimeFramework::c_PackageDirName, Test::Packages::DeploymentWindowsAppRuntimeFramework::c_PackageFullName);
}

inline void RemovePackage_DeploymentWindowsAppRuntimeFramework()
{
    // Best-effort removal. PackageManager.RemovePackage errors if the package
    // is not registered, but if it's not registered we're good. "'Tis the destination
    // that matters, not the journey" so regardless how much or little work
    // we need do, we're happy as long as the package isn't registered when we're done
    //
    // Thus, do a *IfNecessary removal
    RemovePackageIfNecessary(Test::Packages::DeploymentWindowsAppRuntimeFramework::c_PackageFullName);
}

inline bool IsPackageRegistered_DeploymentWindowsAppRuntimeFramework()
{
    return IsPackageRegistered(Test::Packages::DeploymentWindowsAppRuntimeFramework::c_PackageFullName);
}

inline void AddPackage_DeploymentWindowsAppRuntimeMain()
{
    AddPackage(Test::Packages::DeploymentWindowsAppRuntimeMain::c_PackageDirName, Test::Packages::DeploymentWindowsAppRuntimeMain::c_PackageFullName);
}

inline void RemovePackage_DeploymentWindowsAppRuntimeMain()
{
    // Best-effort removal. PackageManager.RemovePackage errors if the package
    // is not registered, but if it's not registered we're good. "'Tis the destination
    // that matters, not the journey" so regardless how much or little work
    // we need do, we're happy as long as the package isn't registered when we're done
    //
    // Thus, do a *IfNecessary removal
    RemovePackageIfNecessary(Test::Packages::DeploymentWindowsAppRuntimeMain::c_PackageFullName);
}

inline bool IsPackageRegistered_DeploymentWindowsAppRuntimeMain()
{
    return IsPackageRegistered(Test::Packages::DeploymentWindowsAppRuntimeMain::c_PackageFullName);
}

inline void AddPackage_DeploymentWindowsAppRuntimeSingleton()
{
    AddPackage(Test::Packages::DeploymentWindowsAppRuntimeSingleton::c_PackageDirName, Test::Packages::DeploymentWindowsAppRuntimeSingleton::c_PackageFullName);
}

inline void RemovePackage_DeploymentWindowsAppRuntimeSingleton()
{
    // Best-effort removal. PackageManager.RemovePackage errors if the package
    // is not registered, but if it's not registered we're good. "'Tis the destination
    // that matters, not the journey" so regardless how much or little work
    // we need do, we're happy as long as the package isn't registered when we're done
    //
    // Thus, do a *IfNecessary removal
    RemovePackageIfNecessary(Test::Packages::DeploymentWindowsAppRuntimeSingleton::c_PackageFullName);
}

inline bool IsPackageRegistered_DeploymentWindowsAppRuntimeSingleton()
{
    return IsPackageRegistered(Test::Packages::DeploymentWindowsAppRuntimeSingleton::c_PackageFullName);
}

inline std::filesystem::path GetWindowsAppRuntimeFrameworkMsixPath()
{
    // Determine the location of the WindowsAppRuntime Framework's msix. See GetSolutionOutDirPath() for more details.
    auto path = ::Test::FileSystem::GetSolutionOutDirPath();
    path /= Test::Packages::WindowsAppRuntimeFramework::c_PackageDirName;
    path /= Test::Packages::WindowsAppRuntimeFramework::c_PackageMsixFilename;
    return path;
}

namespace WapProj
{
    inline void AddPackage(std::filesystem::path packagePath, const PCWSTR& packageName, const PCWSTR& packageExtension)
    {
        packagePath /= packageName;
        packagePath += packageExtension;
        auto packagePathUri = winrt::Windows::Foundation::Uri(packagePath.c_str());

        // Install the package
        winrt::Windows::Management::Deployment::PackageManager packageManager;
        auto options{ winrt::Windows::Management::Deployment::DeploymentOptions::None };
        auto deploymentResult{ packageManager.AddPackageAsync(packagePathUri, nullptr, options).get() };
        VERIFY_SUCCEEDED(deploymentResult.ExtendedErrorCode(), WEX::Common::String().Format(L"AddPackageAsync('%s') = 0x%0X %s", packagePath.c_str(), deploymentResult.ExtendedErrorCode(), deploymentResult.ErrorText().c_str()));
    }
}
}
#endif // __WINDOWSAPPRUNTIME_TEST_PACKAGE_H
