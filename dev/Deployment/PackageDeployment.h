// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include <string>
#include <filesystem>
#include <vector>
#include <functional>
#include <DeploymentActivityContext.h>

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

    // Get deployment package arguments
    std::vector<DeploymentPackageArguments> GetDeploymentPackageArguments(
        const std::wstring& frameworkPackageFullName,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext,
        const std::function<std::wstring(const std::wstring&)>& getPackagePathFunc);

    // Package deployment
    HRESULT DeployPackages(
        const std::vector<DeploymentPackageArguments>& deploymentPackageArguments,
        const bool forceDeployment,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivity);
}
