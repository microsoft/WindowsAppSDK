// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include <DeploymentManager.h>
#include <DeploymentResult.h>
#include <PackageInfo.h>
#include <PackageId.h>
#include <TerminalVelocityFeatures-DeploymentAPI.h>
#include <Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentManager.g.cpp>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{

    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentResult DeploymentManager::GetStatus()
    {
        FAIL_FAST_HR_IF(HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE), !AppModel::Identity::IsPackagedProcess());
        return GetStatus(GetCurrentFrameworkPackageFullName());
    }

    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentResult DeploymentManager::Initialize()
    {
        FAIL_FAST_HR_IF(HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE), !AppModel::Identity::IsPackagedProcess());
        return Initialize(GetCurrentFrameworkPackageFullName());
    }

    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentResult DeploymentManager::GetStatus(hstring const& packageFullName)
    {
        std::wstring frameworkPackageFullName{ packageFullName };
        auto frameworkPackageInfo{ GetPackageInfoForPackage(frameworkPackageFullName) };

        // Should only be called with a framework name that exists.
        FAIL_FAST_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), frameworkPackageInfo.Count() != 1);

        // Only the Microsoft Publisher Id is supported.
        auto expectedPublisherId{ frameworkPackageInfo.Package(0).packageId.publisherId };
        FAIL_FAST_HR_IF(E_INVALIDARG, CompareStringOrdinal(expectedPublisherId, -1, WINDOWSAPPRUNTIME_PACKAGE_PUBLISHERID, -1, TRUE) != CSTR_EQUAL);

        // The framework and package naming scheme is specified here:
        //     https://github.com/microsoft/WindowsAppSDK/blob/main/specs/Deployment/MSIXPackages.md#3-package-naming
        std::wstring frameworkName{ frameworkPackageInfo.Package(0).packageId.name };
        FAIL_FAST_HR_IF(E_INVALIDARG, frameworkName.find(WINDOWSAPPRUNTIME_PACKAGE_NAME_PREFIX) != 0);
        const int c_namePrefixLength{ ARRAYSIZE(WINDOWSAPPRUNTIME_PACKAGE_NAME_PREFIX) - 1 };

        // We assume that since this is a framework there is no subtype name, meaning the remainder
        // of the name is the VersionTag
        auto packageNameVersionTag{ frameworkName.substr(c_namePrefixLength) };

        // Loop through all of the target packages and validate.
        HRESULT verifyResult{};
        for (const auto& package : c_targetPackages)
        {
            // Build package family name based on the framework naming scheme:
            //     Prefix + SubTypeName + VersionTag + '_' + PublisherId
            std::wstring packageFamilyName{ package.prefix + WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_DELIMETER + package.identifier + packageNameVersionTag + WINDOWSAPPRUNTIME_PACKAGE_NAME_SUFFIX };

            // Get target version based on the framework.
            auto targetPackageVersion{ frameworkPackageInfo.Package(0).packageId.version };

            verifyResult = VerifyPackage(packageFamilyName, targetPackageVersion);
            if (FAILED(verifyResult))
            {
                break;
            }
        }

        DeploymentStatus status{};
        if (SUCCEEDED(verifyResult))
        {
            status = DeploymentStatus::Ok;
        }
        else
        {
            status = DeploymentStatus::PackageInstallRequired;
        }

        return winrt::make<implementation::DeploymentResult>(status, verifyResult);
    }

    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentResult DeploymentManager::Initialize(hstring const& packageFullName)
    {
        auto getStatusResult{ DeploymentManager::GetStatus(packageFullName) };
        if (getStatusResult.Status() == DeploymentStatus::Ok)
        {
            return getStatusResult;
        }

        std::wstring frameworkPackageFullName{ packageFullName };
        auto deployPackagesResult{ DeployPackages(frameworkPackageFullName) };
        DeploymentStatus status{};
        if (SUCCEEDED(deployPackagesResult))
        {
            status = DeploymentStatus::Ok;
        }
        else
        {
            status = DeploymentStatus::PackageInstallFailed;
        }

        return winrt::make<implementation::DeploymentResult>(status, deployPackagesResult);
    }

    MddCore::PackageInfo DeploymentManager::GetPackageInfoForPackage(std::wstring const& packageFullName)
    {
        wil::unique_package_info_reference packageInfoReference;
        THROW_IF_WIN32_ERROR(OpenPackageInfoByFullName(packageFullName.c_str(), 0, &packageInfoReference));
        return MddCore::PackageInfo::FromPackageInfoReference(packageInfoReference.get());
    }

    // Borrowed and repurposed from Dynamic Dependencies
    std::vector<std::wstring> DeploymentManager::FindPackagesByFamily(std::wstring const& packageFamilyName)
    {
        UINT32 count{};
        UINT32 bufferLength{};
        const auto rc{ FindPackagesByPackageFamily(packageFamilyName.c_str(), PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT, &count, nullptr, &bufferLength, nullptr, nullptr) };
        if (rc == ERROR_SUCCESS)
        {
            // The package family has no packages registered to the user
            return std::vector<std::wstring>();
        }
        else if (rc != ERROR_INSUFFICIENT_BUFFER)
        {
            THROW_WIN32(rc);
        }

        auto packageFullNames{ wil::make_unique_cotaskmem<PWSTR[]>(count) };
        auto buffer{ wil::make_unique_cotaskmem<WCHAR[]>(bufferLength) };
        THROW_IF_WIN32_ERROR(FindPackagesByPackageFamily(packageFamilyName.c_str(), PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT, &count, packageFullNames.get(), &bufferLength, buffer.get(), nullptr));

        std::vector<std::wstring> packageFullNamesList;
        for (UINT32 index=0; index < count; ++index)
        {
            const auto packageFullName{ packageFullNames[index] };
            packageFullNamesList.push_back(std::wstring(packageFullName));
        }
        return packageFullNamesList;
    }

    HRESULT DeploymentManager::VerifyPackage(const std::wstring& packageFamilyName, const PACKAGE_VERSION targetVersion) try
    {
        auto packageFullNames{ FindPackagesByFamily(packageFamilyName) };
        bool match{};
        for (const auto& packageFullName : packageFullNames)
        {
            auto packagePath{ GetPackagePath(packageFullName) };
            if (packagePath.empty())
            {
                continue;
            }

            auto packageId{ MddCore::PackageId::FromPackageFullName(packageFullName.c_str()) };
            if (packageId.Version().Version >= targetVersion.Version)
            {
                match = true;
                break;
            }
        }

        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), !match);
        return S_OK;
    }
    CATCH_RETURN()

    // Gets the package path, which is a fast and reliable way to check if the package is
    // registered for the user, even without package query capabilities.
    std::wstring DeploymentManager::GetPackagePath(std::wstring const& packageFullName)
    {
        UINT32 pathLength{};
        const auto rc{ GetPackagePathByFullName(packageFullName.c_str(), &pathLength, nullptr) };
        if (rc == ERROR_NOT_FOUND)
        {
            return std::wstring();
        }
        else if (rc != ERROR_INSUFFICIENT_BUFFER)
        {
            THROW_WIN32(rc);
        }

        auto path = wil::make_process_heap_string(nullptr, pathLength);
        THROW_IF_WIN32_ERROR(GetPackagePathByFullName(packageFullName.c_str(), &pathLength, path.get()));
        return std::wstring(path.get());
    }

    // Adds the package at the path using PackageManager.
    // This requires the 'packageManagement' or 'runFullTrust' capabilities.
    HRESULT DeploymentManager::AddPackage(const std::filesystem::path& packagePath) try
    {
        auto packagePathUri = winrt::Windows::Foundation::Uri(packagePath.c_str());
        winrt::Windows::Management::Deployment::PackageManager packageManager;
        auto options{ winrt::Windows::Management::Deployment::DeploymentOptions::None };
        auto deploymentResult{ packageManager.AddPackageAsync(packagePathUri, nullptr, options).get() };
        return deploymentResult.ExtendedErrorCode();
    }
    CATCH_RETURN()

    // Deploys all of the packages carried by the specified framework.
    HRESULT DeploymentManager::DeployPackages(const std::wstring& frameworkPackageFullName) try
    {
        auto frameworkPath = std::filesystem::path(GetPackagePath(frameworkPackageFullName));
        for (const auto& package : c_targetPackages)
        {
            // Build path for the packages.
            auto packagePath{ frameworkPath };
            packagePath /= WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_FOLDER;
            packagePath /= package.identifier + WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_FILE_EXTENSION;
            
            // Deploy package.
            RETURN_IF_FAILED(AddPackage(packagePath));
        }

        return S_OK;
    }
    CATCH_RETURN()

    hstring DeploymentManager::GetCurrentFrameworkPackageFullName()
    {
        // Get current package identity.
        WCHAR packageFullName[PACKAGE_FULL_NAME_MAX_LENGTH + 1]{};
        UINT32 packageFullNameLength{ static_cast<UINT32>(ARRAYSIZE(packageFullName)) };
        const auto rc{ ::GetCurrentPackageFullName(&packageFullNameLength, packageFullName) };
        if (rc != ERROR_SUCCESS)
        {
            THROW_WIN32(rc);
        }

        // Get package info for this package.
        std::wstring currentPackageFullName{ packageFullName };
        auto currentPackageInfo{ GetPackageInfoForPackage(currentPackageFullName) };

        // Index starts at 1 since the first package is the current page and we are interested in
        // dependency packages only.
        for (size_t i = 0; i < currentPackageInfo.Count(); ++i)
        {
            auto dependencyPackage{ currentPackageInfo.Package(i) };

            // Verify PublisherId matches.
            if (CompareStringOrdinal(currentPackageInfo.Package(i).packageId.publisherId, -1, WINDOWSAPPRUNTIME_PACKAGE_PUBLISHERID, -1, TRUE) != CSTR_EQUAL)
            {
                continue;
            }

            // Verify that the WindowsAppRuntime prefix identifier is in the name.
            // This should also be the beginning of the name, so its find position is expected to be 0.
            std::wstring dependencyPackageName{ currentPackageInfo.Package(i).packageId.name };
            if (dependencyPackageName.find(WINDOWSAPPRUNTIME_PACKAGE_NAME_PREFIX) != 0)
            {
                continue;
            }

            // Verify that no other SubTypeNames appear in the name.
            for (const auto& subType : c_subTypeNames)
            {
                if (dependencyPackageName.find(subType.identifier) != std::string::npos)
                {
                    continue;
                }
            }
 
            return hstring(currentPackageInfo.Package(i).packageFullName);
        }

        THROW_WIN32(ERROR_NOT_FOUND);
    }
}
