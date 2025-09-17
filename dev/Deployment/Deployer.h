// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include <string>
#include <filesystem>
#include <windows.h>
#include "PackagePathUtilities.h"
#include "PackageRegistrar.h"

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    class Deployer
    {
    public:
        // Main deployment entry point
        static HRESULT Deploy(const std::wstring& frameworkPackageFullName, const bool forceDeployment = false);

        // License installation
        static HRESULT InstallLicenses(const std::wstring& frameworkPackageFullName, ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext, std::wstring packagePath);

        // Package deployment
        static HRESULT DeployPackages(const std::wstring& frameworkPackageFullName, const bool forceDeployment, ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext, PackagePathUtilities& packagePathUtilities);
    };
}