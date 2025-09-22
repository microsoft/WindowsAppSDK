// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include <string>
#include <filesystem>
#include <vector>
#include <functional>
#include <DeploymentActivityContext.h>

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

    // Proxy/Wrapper for license installer. Open possibility to add more methods if needed.
    struct ILicenseInstaller
    {
        virtual HRESULT InstallLicenseFile(const std::wstring& licenseFilename) = 0;
    };

    // Get license files from the specified path pattern
    HRESULT GetLicenseFiles(const std::wstring& licenseFileSpec, std::vector<std::wstring>& licenseFiles);

    // Install license files
    HRESULT InstallLicenses(
        const std::vector<std::wstring>& licenseFiles,
        std::filesystem::path licensePath,
        ILicenseInstaller& licenseInstaller,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext);

    // Get deployment package arguments
    std::vector<DeploymentPackageArguments> GetDeploymentPackageArguments(
        const std::wstring& frameworkPackageFullName,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext,
        const std::function<std::wstring(const std::wstring&)>& getPackagePathFunc);

    // Package deployment
    HRESULT DeployPackages(
        const std::vector<DeploymentPackageArguments>& deploymentPackageArguments,
        const bool forceDeployment,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivity,
        const std::function<HRESULT()>& startupNotificationsLongRunningPlatformFunc);
}