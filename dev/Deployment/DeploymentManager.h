// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include <PackageInfo.h>
#include <PackageDefinitions.h>
#include "Microsoft.Windows.ApplicationModel.WindowsAppSDK.DeploymentManager.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK::implementation
{
    struct DeploymentManager
    {
        DeploymentManager() = default;
        static winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK::DeploymentStatus GetStatus();
        static winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK::DeploymentStatus GetStatus(hstring const& packageFullName);
        static winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK::DeploymentStatus Initialize();
        static winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK::DeploymentStatus Initialize(hstring const& packageFullName);
    private:
        static MddCore::PackageInfo GetPackageInfoForPackage(std::wstring const& packageFullName);
        static std::vector<std::wstring> FindPackagesByFamily(std::wstring const& packageFamilyName);
        static HRESULT VerifyPackage(const std::wstring& packageFamilyName, const PACKAGE_VERSION targetVersion);
        static std::wstring GetPackagePath(std::wstring const& packageFullName);
        static HRESULT AddPackage(const std::filesystem::path& packagePath);
        static HRESULT DeployPackages(const std::wstring& frameworkPackageFullName);
        static hstring GetCurrentFrameworkPackageFullName();
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK::factory_implementation
{
    struct DeploymentManager : DeploymentManagerT<DeploymentManager, implementation::DeploymentManager>
    {
    };
}

