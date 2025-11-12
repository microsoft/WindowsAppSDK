// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once
#include <PackageDefinitions.h>
#include <winrt/Windows.Foundation.h>
#include "Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentManager.g.h"

#include <DeploymentActivityContext.h>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    struct DeploymentManager
    {
        DeploymentManager() = default;
        static WindowsAppRuntime::DeploymentResult GetStatus();
        static WindowsAppRuntime::DeploymentResult Initialize();
        static WindowsAppRuntime::DeploymentResult Initialize(WindowsAppRuntime::DeploymentInitializeOptions const& deploymentInitializeOptions);
        static WindowsAppRuntime::DeploymentResult Repair();

    private:
        static WindowsAppRuntime::DeploymentResult GetStatus(hstring const& packageFullName);
        static WindowsAppRuntime::DeploymentResult Initialize(hstring const& packageFullName);
        static WindowsAppRuntime::DeploymentResult Initialize(hstring const& packageFullName,
            WindowsAppRuntime::DeploymentInitializeOptions const& deploymentInitializeOptions,
            bool isRepair = false);

        static WindowsAppRuntime::DeploymentResult _Initialize(
            ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext,
            hstring const& packageFullName,
            WindowsAppRuntime::DeploymentInitializeOptions const& deploymentInitializeOptions,
            bool isRepair);

        static HRESULT Deploy(
            const std::wstring& frameworkPackageFullName,
            ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext,
            const bool forceDeployment);

        static HRESULT InstallLicenses(const std::wstring& frameworkPackageFullName, ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext);
        static HRESULT DeployPackages(const std::wstring& frameworkPackageFullName, ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext, const bool forceDeployment);
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::factory_implementation
{
    struct DeploymentManager : DeploymentManagerT<DeploymentManager, implementation::DeploymentManager>
    {
    };
}
