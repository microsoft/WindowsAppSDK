// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include <PackageInfo.h>
#include <PackageDefinitions.h>
#include "Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentManager.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    struct DeploymentManager
    {
        DeploymentManager() = default;
        static WindowsAppRuntime::DeploymentResult GetStatus();
        static WindowsAppRuntime::DeploymentResult Initialize();
    private:
        static WindowsAppRuntime::DeploymentResult GetStatus(hstring const& packageFullName);
        static WindowsAppRuntime::DeploymentResult Initialize(hstring const& packageFullName);
        static MddCore::PackageInfo GetPackageInfoForPackage(std::wstring const& packageFullName);
        static std::vector<std::wstring> FindPackagesByFamily(std::wstring const& packageFamilyName);
        static HRESULT VerifyPackage(const std::wstring& packageFamilyName, const PACKAGE_VERSION targetVersion);
        static std::wstring GetPackagePath(std::wstring const& packageFullName);
        static HRESULT AddPackage(const std::filesystem::path& packagePath);
        static HRESULT Deploy(const std::wstring& frameworkPackageFullName);
        static HRESULT DeployPackages(const std::wstring& frameworkPackageFullName);
        static HRESULT InstallLicenses(const std::wstring& frameworkPackageFullName);
        static hstring GetCurrentFrameworkPackageFullName();
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::factory_implementation
{
    struct DeploymentManager : DeploymentManagerT<DeploymentManager, implementation::DeploymentManager>
    {
    };
}

