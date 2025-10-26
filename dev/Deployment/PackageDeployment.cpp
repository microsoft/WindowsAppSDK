// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>
#include "DeploymentActivityContext.h"
#include "PackageDefinitions.h"
#include "PackageDeployment.h"

namespace WindowsAppRuntime::Deployment::PackageDeployment
{
    std::vector<DeploymentPackageArguments> GetDeploymentPackageArguments(
        const std::filesystem::path& frameworkPackagePath,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext,
        const std::map<std::wstring, PackagePathInfo>& existingTargetPackagesIfHigherVersion)
    {
        initializeActivityContext.Reset();
        initializeActivityContext.SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::GetPackagePath);

        std::vector<DeploymentPackageArguments> deploymentPackageArguments;

        for (auto package : winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation::c_targetPackages)
        {
            auto isSingleton{ CompareStringOrdinal(package.identifier.c_str(), -1, WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_SINGLETON, -1, TRUE) == CSTR_EQUAL };

            std::filesystem::path packagePath{};

            // If there is exisiting target package version higher than that of framework current version package, then re-register it.
            // Otherwise, deploy the target msix package from the current framework package version.
            auto existingPackageIfHigherVersion = existingTargetPackagesIfHigherVersion.find(package.identifier);
            auto useExistingPackageIfHigherVersion { existingPackageIfHigherVersion != existingTargetPackagesIfHigherVersion.end() };
            if (useExistingPackageIfHigherVersion)
            {
                packagePath = existingPackageIfHigherVersion->second.packagePath;
                packagePath /= WINDOWSAPPRUNTIME_PACKAGE_MANIFEST_FILE;
            }
            else
            {
                packagePath = frameworkPackagePath;
                packagePath /= WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_FOLDER;
                packagePath /= package.identifier + WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_FILE_EXTENSION;
            }

            deploymentPackageArguments.push_back(DeploymentPackageArguments{ package.identifier, packagePath, useExistingPackageIfHigherVersion, isSingleton });
        }

        return deploymentPackageArguments;
    }
}
