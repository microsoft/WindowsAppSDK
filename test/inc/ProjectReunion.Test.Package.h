// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef __PROJECTREUNION_TEST_PACKAGE_H
#define __PROJECTREUNION_TEST_PACKAGE_H

#include <appmodel.h>

#include <ProjectReunion.Test.FileSystem.h>

#include <WexTestClass.h>

#define PROJECTREUNION_TEST_METADATA_VERSION            0x0004000107AF014DLLu
#define PROJECTREUNION_TEST_METADATA_VERSION_MAJOR      4
#define PROJECTREUNION_TEST_METADATA_VERSION_MINOR      1
#define PROJECTREUNION_TEST_METADATA_VERSION_BUILD      1967
#define PROJECTREUNION_TEST_METADATA_VERSION_REVISION   333
#define PROJECTREUNION_TEST_METADATA_VERSION_STRING     L"4.1.1967.333"

#define PROJECTREUNION_TEST_MSIX_PUBLISHERID            L"8wekyb3d8bbwe"

#define PROJECTREUNION_TEST_MSIX_FRAMEWORK_PACKAGE_NAME L"Microsoft.ProjectReunion.Framework"
#define PROJECTREUNION_TEST_MSIX_DDLM_PACKAGE_NAME      L"Microsoft.ProjectReunion.DDLM"
#define PROJECTREUNION_TEST_MSIX_MAIN_PACKAGE_NAME      L"Microsoft.ProjectReunion.Main"

#define PROJECTREUNION_TEST_PACKAGE_DDLM_NAMEPREFIX     L"ProjectReunion.Test.DDLM"
#define PROJECTREUNION_TEST_PACKAGE_DDLM_VERSION        PROJECTREUNION_TEST_METADATA_VERSION_STRING
#if defined(_M_X64)
#define PROJECTREUNION_TEST_PACKAGE_DDLM_ARCHITECTURE   L"x64"
#elif defined(_M_IX86)
#define PROJECTREUNION_TEST_PACKAGE_DDLM_ARCHITECTURE   L"x86"
#elif defined(_M_ARM64)
#define PROJECTREUNION_TEST_PACKAGE_DDLM_ARCHITECTURE   L"arm64"
#elif defined(_M_ARM)
#define PROJECTREUNION_TEST_PACKAGE_DDLM_ARCHITECTURE   L"arm"
#else
#   error "Unknown processor architecture"
#endif
#define PROJECTREUNION_TEST_PACKAGE_DDLM_NAME           PROJECTREUNION_TEST_PACKAGE_DDLM_NAMEPREFIX L"-" PROJECTREUNION_TEST_PACKAGE_DDLM_VERSION L"-" PROJECTREUNION_TEST_PACKAGE_DDLM_ARCHITECTURE
#define PROJECTREUNION_TEST_PACKAGE_DDLM_PUBLISHERID    PROJECTREUNION_TEST_MSIX_PUBLISHERID
#define PROJECTREUNION_TEST_PACKAGE_DDLM_FAMILYNAME     PROJECTREUNION_TEST_PACKAGE_DDLM_NAME L"_" PROJECTREUNION_TEST_PACKAGE_DDLM_PUBLISHERID
#define PROJECTREUNION_TEST_PACKAGE_DDLM_FULLNAME       PROJECTREUNION_TEST_PACKAGE_DDLM_NAME L"_" PROJECTREUNION_TEST_PACKAGE_DDLM_VERSION L"_" PROJECTREUNION_TEST_PACKAGE_DDLM_ARCHITECTURE L"__" PROJECTREUNION_TEST_PACKAGE_DDLM_PUBLISHERID

namespace Test::Packages::DynamicDependencyLifetimeManager
{
    constexpr PCWSTR c_PackageDirName = L"DynamicDependencyLifetimeManager";
    constexpr PCWSTR c_PackageNamePrefix = PROJECTREUNION_TEST_PACKAGE_DDLM_NAMEPREFIX;
    constexpr PCWSTR c_PackagePublisherId = PROJECTREUNION_TEST_PACKAGE_DDLM_PUBLISHERID;
    constexpr PCWSTR c_PackageFamilyName = PROJECTREUNION_TEST_PACKAGE_DDLM_FAMILYNAME;
    constexpr PCWSTR c_PackageFullName = PROJECTREUNION_TEST_PACKAGE_DDLM_FULLNAME;
    constexpr const PACKAGE_VERSION GetPackageVersion()
    {
        PACKAGE_VERSION version{};
        version.Major = PROJECTREUNION_TEST_METADATA_VERSION_MAJOR;
        version.Minor = PROJECTREUNION_TEST_METADATA_VERSION_MINOR;
        version.Build = PROJECTREUNION_TEST_METADATA_VERSION_BUILD;
        version.Revision = PROJECTREUNION_TEST_METADATA_VERSION_REVISION;
        return version;
    }
    constexpr const PACKAGE_VERSION c_Version = GetPackageVersion();

    constexpr const UINT32 GetPackageVersionMajorMinor()
    {
        return static_cast<UINT32>((GetPackageVersion().Major << 16) | GetPackageVersion().Minor);
    }
    constexpr const UINT32 c_Version_MajorMinor = GetPackageVersionMajorMinor();
}

namespace Test::Packages::ProjectReunionFramework
{
    constexpr PCWSTR c_PackageDirName = L"Microsoft.ProjectReunion.Framework";
    constexpr PCWSTR c_PackageMsixFilename = L"Microsoft.ProjectReunion.Framework.msix";
    constexpr PCWSTR c_PackageFamilyName = PROJECTREUNION_TEST_MSIX_FRAMEWORK_PACKAGE_NAME L"_" PROJECTREUNION_TEST_MSIX_PUBLISHERID;
    constexpr PCWSTR c_PackageFullName = PROJECTREUNION_TEST_MSIX_FRAMEWORK_PACKAGE_NAME L"_" PROJECTREUNION_TEST_METADATA_VERSION_STRING L"_neutral__" PROJECTREUNION_TEST_MSIX_PUBLISHERID;
}

namespace Test::Packages::DynamicDependencyDataStore
{
    constexpr PCWSTR c_PackageDirName = L"DynamicDependency.DataStore";
    constexpr PCWSTR c_PackageFamilyName = L"ProjectReunion.Test.DynDep.DataStore_" PROJECTREUNION_TEST_MSIX_PUBLISHERID;
    constexpr PCWSTR c_PackageFullName = L"ProjectReunion.Test.DynDep.DataStore_" PROJECTREUNION_TEST_PACKAGE_DDLM_VERSION L"_neutral__" PROJECTREUNION_TEST_MSIX_PUBLISHERID;
}

namespace Test::Packages::PushNotificationsLongRunningTask
{
    constexpr PCWSTR c_PackageDirName = L"PushNotificationsLongRunningTask";
    constexpr PCWSTR c_PackageFamilyName = L"ProjectReunion.Test.PushNotificationsTask_" PROJECTREUNION_TEST_MSIX_PUBLISHERID;
    constexpr PCWSTR c_PackageFullName = L"ProjectReunion.Test.PushNotificationsTask_" PROJECTREUNION_TEST_PACKAGE_DDLM_VERSION L"_neutral__" PROJECTREUNION_TEST_MSIX_PUBLISHERID;
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

    inline void AddPackage_ProjectReunionFramework()
    {
        AddPackage(Test::Packages::ProjectReunionFramework::c_PackageDirName, Test::Packages::ProjectReunionFramework::c_PackageFullName);
    }

    inline void RemovePackage_ProjectReunionFramework()
    {
        // Best-effort removal. PackageManager.RemovePackage errors if the package
        // is not registered, but if it's not registered we're good. "'Tis the destination
        // that matters, not the journey" so regardless how much or little work
        // we need do, we're happy as long as the package isn't registered when we're done
        //
        // Thus, do a *IfNecessary removal
        RemovePackageIfNecessary(Test::Packages::ProjectReunionFramework::c_PackageFullName);
    }

    inline bool IsPackageRegistered_ProjectReunionFramework()
    {
        return IsPackageRegistered(Test::Packages::ProjectReunionFramework::c_PackageFullName);
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

    inline std::filesystem::path GetProjectReunionFrameworkMsixPath()
    {
        // Determine the location of ProjectReunion's Framework's msix. See GetSolutionOutDirPath() for more details.
        auto path = ::Test::FileSystem::GetSolutionOutDirPath();
        path /= Test::Packages::ProjectReunionFramework::c_PackageDirName;
        path /= Test::Packages::ProjectReunionFramework::c_PackageMsixFilename;
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
#endif // __PROJECTREUNION_TEST_PACKAGE_H
