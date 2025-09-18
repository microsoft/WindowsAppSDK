// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include <string>
#include <filesystem>
#include <windows.h>
#include "PackagePathUtilities.h"
#include "PackageRegistrar.h"

namespace WindowsAppRuntime::Deployment::Deployer
{
    // Main deployment entry point
    HRESULT Deploy(const std::wstring& frameworkPackageFullName, const bool forceDeployment = false);

    // License installation
    HRESULT InstallLicenses(const std::wstring& frameworkPackageFullName, ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext, std::wstring packagePath);

    // Package deployment
    HRESULT DeployPackages(
        const std::wstring& frameworkPackageFullName,
        const bool forceDeployment,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext,
        ::WindowsAppRuntime::Deployment::PackagePathUtilities& packagePathUtilities);
}