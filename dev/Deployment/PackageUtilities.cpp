// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>
#include <windows.h>
#include <wil/resource.h>
#include <PackageInfo.h>
#include "PackageUtilities.h"
#include "PackageDefinitions.h"
#include <appmodel.identity.h>

namespace WindowsAppRuntime::Deployment::Package
{
    std::wstring GetPackagePath(std::wstring const& packageFullName)
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

        auto path{ wil::make_process_heap_string(nullptr, pathLength) };
        THROW_IF_WIN32_ERROR(GetPackagePathByFullName(packageFullName.c_str(), &pathLength, path.get()));
        return std::wstring{ path.get() };
    }

    // Borrowed and repurposed from Dynamic Dependencies
    std::vector<std::wstring> FindPackagesByFamily(std::wstring const& packageFamilyName)
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

    HRESULT VerifyPackage(const std::wstring& packageFamilyName, const PACKAGE_VERSION targetVersion,
        const std::wstring& packageIdentifier) try
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

            auto packageId{ AppModel::Identity::PackageIdentity::FromPackageFullName(packageFullName.c_str()) };
            if (packageId.Version().Version >= targetVersion.Version)
            {
                match = true;
                if (packageId.Version().Version > targetVersion.Version)
                {
                    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation::g_existingTargetPackagesIfHigherVersion.insert(std::make_pair(packageIdentifier, packageFullName));
                }
                break;
            }
        }

        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), !match);
        return S_OK;
    }
    CATCH_RETURN()

    MddCore::PackageInfo GetPackageInfoForPackage(std::wstring const& packageFullName)
    {
        wil::unique_package_info_reference packageInfoReference;
        THROW_IF_WIN32_ERROR(OpenPackageInfoByFullName(packageFullName.c_str(), 0, &packageInfoReference));
        return MddCore::PackageInfo::FromPackageInfoReference(packageInfoReference.get());
    }

    winrt::hstring GetCurrentFrameworkPackageFullName()
    {
        // Get current package identity.
        WCHAR packageFullName[PACKAGE_FULL_NAME_MAX_LENGTH + 1]{};
        UINT32 packageFullNameLength{ static_cast<UINT32>(ARRAYSIZE(packageFullName)) };
        const auto rc{ ::GetCurrentPackageFullName(&packageFullNameLength, packageFullName) };
        if (rc != ERROR_SUCCESS)
        {
            THROW_WIN32(rc);
        }

        // Get the PackageInfo of current package and it's dependency packages
        std::wstring currentPackageFullName{ packageFullName };
        auto currentPackageInfo{ GetPackageInfoForPackage(currentPackageFullName) };

        // Index starts at 1 since the first package is the current package and we are interested in
        // dependency packages only.
        for (size_t i = 0; i < currentPackageInfo.Count(); ++i)
        {
            auto dependencyPackage{ currentPackageInfo.Package(i) };

            // Verify PublisherId matches.
            if (CompareStringOrdinal(dependencyPackage.packageId.publisherId, -1, WINDOWSAPPRUNTIME_PACKAGE_PUBLISHERID, -1, TRUE) != CSTR_EQUAL)
            {
                continue;
            }

            // Verify that the WindowsAppRuntime prefix identifier is in the name.
            // This should also be the beginning of the name, so its find position is expected to be 0.
            std::wstring dependencyPackageName{ dependencyPackage.packageId.name };
            if (dependencyPackageName.find(WINDOWSAPPRUNTIME_PACKAGE_NAME_PREFIX) != 0)
            {
                continue;
            }

            // On WindowsAppSDK 1.1+, there is no need to check and rule out Main, Singleton and DDLM Package identifiers as their names don't have a overlap with WINDOWSAPPRUNTIME_PACKAGE_NAME_PREFIX.

            return winrt::hstring(dependencyPackage.packageFullName);
        }

        THROW_WIN32(ERROR_NOT_FOUND);
    }
}
