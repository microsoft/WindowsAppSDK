// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include <string>
#include <filesystem>
#include <windows.h>
#include "PackagePathUtilities.h"

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
        static HRESULT DeployPackages(const std::wstring& frameworkPackageFullName, const bool forceDeployment);
        
    private:
        // Package registration methods
        static HRESULT AddOrRegisterPackage(const std::filesystem::path& package, const bool useExistingPackageIfHigherVersion, const bool forceDeployment);
        static HRESULT AddOrRegisterPackageInBreakAwayProcess(const std::filesystem::path& packagePath, const bool useExistingPackageIfHigherVersion, const bool forceDeployment);
        
        // Utility methods
        static std::wstring GenerateDeploymentAgentPath();
    };
}