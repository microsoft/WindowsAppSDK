// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef __WINDOWSAPPRUNTIME_TEST_PACKAGE_H
#define __WINDOWSAPPRUNTIME_TEST_PACKAGE_H

#include <appmodel.h>

#include <WindowsAppRuntime.Test.FileSystem.h>

#include <WexTestClass.h>

#define WINDOWSAPPRUNTIME_TEST_METADATA_VERSION            0x0004000107AF014DLLu
#define WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_MAJOR      4
#define WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_MINOR      1
#define WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_BUILD      1967
#define WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_REVISION   333
#define WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_STRING     L"4.1.1967.333"

#define WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID            L"8wekyb3d8bbwe"

#define WINDOWSAPPRUNTIME_TEST_MSIX_FRAMEWORK_PACKAGE_NAME L"Microsoft.WindowsAppRuntime.Framework"
#define WINDOWSAPPRUNTIME_TEST_MSIX_DDLM_PACKAGE_NAME      L"Microsoft.WindowsAppRuntime.DDLM"
#define WINDOWSAPPRUNTIME_TEST_MSIX_MAIN_PACKAGE_NAME      L"Microsoft.WindowsAppRuntime.Main"
#define WINDOWSAPPRUNTIME_TEST_MSIX_SINGLETON_PACKAGE_NAME L"Microsoft.WindowsAppRuntime.Singleton"

#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_NAMEPREFIX     L"WindowsAppRuntime.Test.DDLM"
#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_VERSION        WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_STRING
#if defined(_M_X64)
#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_ARCHITECTURE   L"x64"
#elif defined(_M_IX86)
#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_ARCHITECTURE   L"x86"
#elif defined(_M_ARM64)
#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_ARCHITECTURE   L"arm64"
#elif defined(_M_ARM)
#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_ARCHITECTURE   L"arm"
#else
#   error "Unknown processor architecture"
#endif
#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_NAME           WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_NAMEPREFIX L"-" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_VERSION L"-" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_ARCHITECTURE
#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_PUBLISHERID    WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID
#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_FAMILYNAME     WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_NAME L"_" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_PUBLISHERID
#define WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_FULLNAME       WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_NAME L"_" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_VERSION L"_" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_ARCHITECTURE L"__" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_PUBLISHERID

namespace Test::Packages::DynamicDependencyLifetimeManager
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

namespace Test::Packages::WindowsAppRuntimeFramework
{
    constexpr PCWSTR c_PackageDirName = L"Microsoft.WindowsAppRuntime.Framework";
    constexpr PCWSTR c_PackageMsixFilename = L"Microsoft.WindowsAppRuntime.Framework.msix";
    constexpr PCWSTR c_PackageFamilyName = WINDOWSAPPRUNTIME_TEST_MSIX_FRAMEWORK_PACKAGE_NAME L"_" WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID;
    constexpr PCWSTR c_PackageFullName = WINDOWSAPPRUNTIME_TEST_MSIX_FRAMEWORK_PACKAGE_NAME L"_" WINDOWSAPPRUNTIME_TEST_METADATA_VERSION_STRING L"_neutral__" WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID;
}

namespace Test::Packages::DynamicDependencyDataStore
{
    constexpr PCWSTR c_PackageDirName = L"DynamicDependency.DataStore";
    constexpr PCWSTR c_PackageFamilyName = L"WindowsAppRuntime.Test.DynDep.DataStore_" WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID;
    constexpr PCWSTR c_PackageFullName = L"WindowsAppRuntime.Test.DynDep.DataStore_" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_VERSION L"_neutral__" WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID;
}

namespace Test::Packages::WindowsAppRuntimeSingleton
{
    constexpr PCWSTR c_PackageDirName = L"WindowsAppRuntime.Test.Singleton";
    constexpr PCWSTR c_PackageFamilyName = L"WindowsAppRuntime.Test.Singleton_" WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID;
    constexpr PCWSTR c_PackageFullName = L"WindowsAppRuntime.Test.Singleton_" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_VERSION L"_neutral__" WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID;
}

namespace Test::Packages::PushNotificationsLongRunningTask
{
    constexpr PCWSTR c_PackageDirName = L"PushNotificationsLongRunningTask";
    constexpr PCWSTR c_PackageFamilyName = L"WindowsAppRuntime.Test.PushNotificationsTask_" WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID;
    constexpr PCWSTR c_PackageFullName = L"WindowsAppRuntime.Test.PushNotificationsTask_" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_VERSION L"_neutral__" WINDOWSAPPRUNTIME_TEST_MSIX_PUBLISHERID;
}

namespace Test::Packages
{
    inline std::wstring GetPackagePath(PCWSTR packageFullName)
    {
        UINT32 pathLength{};
        const auto rc{ GetPackagePathByFullName(packageFullName, &pathLength, nullptr) };
        if (rc == ERROR_NOT_FOUND)
        {
            return std::wstring();
        }

        VERIFY_ARE_EQUAL(ERROR_INSUFFICIENT_BUFFER, rc);
        auto path = wil::make_process_heap_string(nullptr, pathLength);
        VERIFY_ARE_EQUAL(ERROR_SUCCESS, GetPackagePathByFullName(packageFullName, &pathLength, path.get()));
        return std::wstring(path.get());
    }

    inline std::wstring GetPackagePath(const std::wstring& packageFullName)
    {
        return GetPackagePath(packageFullName.c_str());
    }

    inline bool IsPackageRegistered(PCWSTR packageFullName)
    {
        // Check if the package is registered to the current user via GetPackagePath().
        // GetPackagePath() fails if the package isn't registerd to the current user.
        // Simplest and most portable test across the platforms we might run on
        const auto path = GetPackagePath(packageFullName);
        return !path.empty();
    }

    inline void AddPackage(PCWSTR packageDirName, PCWSTR packageFullName)
    {
        // Build the target package's .msix filename. It's under the Solution's $(OutDir)
        // NOTE: It could live in ...\Something.msix\... or ...\Something\...
        auto solutionOutDirPath = ::Test::FileSystem::GetSolutionOutDirPath();
        //
        // Look in ...\Something.msix\...
        auto msix(solutionOutDirPath);
        msix /= packageDirName;
        msix += L".msix";
        msix /= packageDirName;
        msix += L".msix";
        if (!std::filesystem::is_regular_file(msix))
        {
            // Look in ...\Something\...
            msix = solutionOutDirPath;
            msix /= packageDirName;
            msix /= packageDirName;
            msix += L".msix";
            WIN32_FILE_ATTRIBUTE_DATA data{};
            const auto ok{ GetFileAttributesExW(msix.c_str(), GetFileExInfoStandard, &data) };
            const auto lastError{ ::GetLastError() };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"GetFileAttributesExW(%ls):%d LastError:%u", msix.c_str(), static_cast<int>(ok), lastError));

            std::error_code errorcode{};
            auto isregularfile{ std::filesystem::is_regular_file(msix, errorcode) };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"std::filesystem::is_regular_file(%ls):%ls error_code:%d %hs", msix.c_str(), isregularfile ? L"True" : L"False", errorcode.value(), errorcode.message().c_str()));

            //VERIFY_IS_TRUE(std::filesystem::is_regular_file(msix));
        }
        auto msixUri = winrt::Windows::Foundation::Uri(msix.c_str());

        // Install the package
        winrt::Windows::Management::Deployment::PackageManager packageManager;
        auto options{ winrt::Windows::Management::Deployment::DeploymentOptions::None };
        auto deploymentResult{ packageManager.AddPackageAsync(msixUri, nullptr, options).get() };
        VERIFY_SUCCEEDED(deploymentResult.ExtendedErrorCode(), WEX::Common::String().Format(L"AddPackageAsync('%s') = 0x%0X %s", packageFullName, deploymentResult.ExtendedErrorCode(), deploymentResult.ErrorText().c_str()));
    }

    inline void AddPackageIfNecessary(PCWSTR packageDirName, PCWSTR packageFullName)
    {
        if (!IsPackageRegistered(packageFullName))
        {
            AddPackage(packageDirName, packageFullName);
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

    inline void AddPackage_PushNotificationsLongRunningTask()
    {
        AddPackage(Test::Packages::PushNotificationsLongRunningTask::c_PackageDirName, Test::Packages::PushNotificationsLongRunningTask::c_PackageFullName);
    }

    inline void RemovePackage_PushNotificationsLongRunningTask()
    {
        // Best-effort removal. PackageManager.RemovePackage errors if the package
        // is not registered, but if it's not registered we're good. "'Tis the destination
        // that matters, not the journey" so regardless how much or little work
        // we need do, we're happy as long as the package isn't registered when we're done
        //
        // Thus, do a *IfNecessary removal
        RemovePackageIfNecessary(Test::Packages::PushNotificationsLongRunningTask::c_PackageFullName);
    }

    inline bool IsPackageRegistered_PushNotificationsLongRunningTask()
    {
        return IsPackageRegistered(Test::Packages::PushNotificationsLongRunningTask::c_PackageFullName);
    }

    inline std::filesystem::path GetWindowsAppRuntimeFrameworkMsixPath()
    {
        // Determine the location of the WindowsAppRuntime Framework's msix. See GetSolutionOutDirPath() for more details.
        auto path = ::Test::FileSystem::GetSolutionOutDirPath();
        path /= Test::Packages::WindowsAppRuntimeFramework::c_PackageDirName;
        path /= Test::Packages::WindowsAppRuntimeFramework::c_PackageMsixFilename;
        return path;
    }
}

namespace Test::Packages::WapProj
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
#endif // __WINDOWSAPPRUNTIME_TEST_PACKAGE_H
