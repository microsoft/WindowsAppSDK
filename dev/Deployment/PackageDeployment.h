// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include <string>
#include <filesystem>
#include <vector>
#include <map>
#include "DeploymentActivityContext.h"

namespace WindowsAppRuntime::Deployment::PackageDeployment
{
    // Structure to hold deployment package arguments
    struct DeploymentPackageArguments
    {
        std::wstring identifier{};
        std::filesystem::path packagePath{};
        bool useExistingPackageIfHigherVersion{};
        bool isSingleton{};
    };

    struct PackagePathInfo
    {
        std::wstring packageFullName;
        std::filesystem::path packagePath;
    };

    // Get deployment package arguments
    std::vector<DeploymentPackageArguments> GetDeploymentPackageArguments(
        const std::filesystem::path& frameworkPackagePath,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext,
        const std::map<std::wstring, PackagePathInfo>& existingTargetPackagesIfHigherVersion);

    // Package deployment
    HRESULT DeployPackages(
        const std::vector<DeploymentPackageArguments>& deploymentPackageArguments,
        const bool forceDeployment,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivity);
}
