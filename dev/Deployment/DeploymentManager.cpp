// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include <DeploymentManager.h>
#include <DeploymentStatus.h>
#include <PackageInfo.h>
#include <Microsoft.Windows.ApplicationModel.WindowsAppSDK.DeploymentManager.g.cpp>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK::implementation
{
    winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK::DeploymentStatus DeploymentManager::GetStatus(hstring const& packageFullName)
    {
        std::wstring frameworkPackageFullName{ packageFullName };
        auto frameworkPackageInfo{ GetPackageInfoForPackage(frameworkPackageFullName) };

        // Should only be called with a framework name that exists.
        FAIL_FAST_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), frameworkPackageInfo.Count() != 1);

        // Only the Microsoft Publisher Id is supported.
        auto expectedPublisherId{ frameworkPackageInfo.Package(0).packageId.publisherId };
        FAIL_FAST_HR_IF(E_INVALIDARG, CompareStringOrdinal(expectedPublisherId, -1, WINDOWSAPPSDK_IDENTITY_PUBLISHERID, -1, TRUE) != CSTR_EQUAL);

        // The framework naming scheme consists of a prefix (ex: "Microsoft.WindowsAppSDK.") and a possible
        // postfix (ex: "-1.0-Release"). We assume all packages of this release match this similar naming scheme
        // but for their specific identifiers. The framework package is input, so we know its constant identifier,
        // therefore we can derive the prefix and postfix from the rest of the Name attribute of the Package Family.
        std::wstring frameworkFamilyName{ frameworkPackageInfo.Package(0).packageFamilyName };
        auto posFrameworkIdentifier{ frameworkFamilyName.find(WINDOWSAPPSDK_FRAMEWORK_PACKAGE_IDENTIFIER) };
        const int c_frameworkIdentifierLength{ ARRAYSIZE(WINDOWSAPPSDK_FRAMEWORK_PACKAGE_IDENTIFIER) - 1 };
        auto posFrameworkDelimeter{ frameworkFamilyName.find(WINDOWSAPPSDK_NAME_DELIMETER) };
        auto packageFamilyPrefix{ frameworkFamilyName.substr(0, posFrameworkIdentifier)};
        auto packageFamilyPostfix{ frameworkFamilyName.substr(posFrameworkIdentifier + c_frameworkIdentifierLength, posFrameworkDelimeter - (posFrameworkIdentifier + c_frameworkIdentifierLength))};

        // Loop through all of the target packages and validate.
        HRESULT verifyResult{ S_OK };
        for (const auto& package : c_targetPackages)
        {
            // Build package family name based on the framework naming scheme.
            std::wstring packageFamilyName{ packageFamilyPrefix + package.identifier + packageFamilyPostfix + WINDOWSAPPSDK_NAME_SUFFIX };

            // Get target version based on the framework.
            auto targetPackageVersion{ frameworkPackageInfo.Package(0).packageId.version };

            verifyResult = VerifyPackage(packageFamilyName, targetPackageVersion);
            if (FAILED(verifyResult))
            {
                break;
            }
        }

        auto status{ winrt::make<implementation::DeploymentStatus>(SUCCEEDED(verifyResult), FAILED(verifyResult), verifyResult) };
        return status;
    }

    winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK::DeploymentStatus DeploymentManager::Initialize(hstring const& packageFullName)
    {
        return DeploymentManager::GetStatus(packageFullName);
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
        const LONG rc{ FindPackagesByPackageFamily(packageFamilyName.c_str(), PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT, &count, nullptr, &bufferLength, nullptr, nullptr) };
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


    HRESULT DeploymentManager::VerifyPackage(const std::wstring& packageFamilyName, const PACKAGE_VERSION targetVersion)
    {
        auto packageFullNames{ FindPackagesByFamily(packageFamilyName) };
        bool match{ false };
        for (const auto& packageFullName : packageFullNames)
        {
            auto packageInfo{ GetPackageInfoForPackage(packageFullName) };
            if (packageInfo.Count() == 0)
            {
                continue;
            }

            if (packageInfo.Package(0).packageId.version.Version >= targetVersion.Version)
            {
                match = true;
                break;
            }
        }

        if (!match)
        {
            return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
        }

        return S_OK;
    }

}
