// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include <string>
#include <filesystem>
#include <vector>
#include <windows.h>
#include "PackagePathUtilities.h"
#include "PackageRegistrar.h"

namespace WindowsAppRuntime::Deployment::Deployer
{
    // Structure to hold deployment package arguments
    struct DeploymentPackageArguments
    {
        const std::wstring packageIdentifier;
        const std::filesystem::path packagePath;
        const bool useExistingPackageIfHigherVersion;
        const bool isSingleton;
    };

    // Main deployment entry point
    HRESULT Deploy(const std::wstring& frameworkPackageFullName, const bool forceDeployment = false);

    // License installation
    HRESULT InstallLicenses(
        const std::wstring& frameworkPackageFullName, 
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext, 
        std::wstring packagePath);

    // Get deployment package arguments
    std::vector<DeploymentPackageArguments> GetDeploymentPackageArguments(
        const std::wstring& frameworkPackageFullName,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext,
        ::WindowsAppRuntime::Deployment::PackagePathUtilities& packagePathUtilities);

    // Package deployment
    HRESULT DeployPackages(
        std::vector<DeploymentPackageArguments> deploymentPackageArguments,
        const bool forceDeployment,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivity);
}