// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>
#include <windows.h>
#include <wil/resource.h>
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
}
