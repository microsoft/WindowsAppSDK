// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>
#include <functional>
#include "DeploymentActivityContext.h"
#include "PackageDefinitions.h"
#include "PackageDeployment.h"
#include "PackageRegistrar.h"

namespace WindowsAppRuntime::Deployment::PackageDeployment
{
    std::vector<DeploymentPackageArguments> GetDeploymentPackageArguments(
        const std::wstring& frameworkPackageFullName,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext,
        const std::map<std::wstring, std::wstring>& existingTargetPackagesIfHigherVersion,
        const std::function<std::wstring(const std::wstring&)>& getPackagePathFunc)
    {
        initializeActivityContext.Reset();
        initializeActivityContext.SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::GetPackagePath);

        std::vector<DeploymentPackageArguments> deploymentPackageArguments;

        const auto frameworkPath{ std::filesystem::path(getPackagePathFunc(frameworkPackageFullName)) };
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
                packagePath = std::filesystem::path(getPackagePathFunc(existingPackageIfHigherVersion->second));
                packagePath /= WINDOWSAPPRUNTIME_PACKAGE_MANIFEST_FILE;
            }
            else
            {
                packagePath = frameworkPath;
                packagePath /= WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_FOLDER;
                packagePath /= package.identifier + WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_FILE_EXTENSION;
            }

            deploymentPackageArguments.push_back(DeploymentPackageArguments{ package.identifier, packagePath, useExistingPackageIfHigherVersion, isSingleton });
        }

        return deploymentPackageArguments;
    }

    HRESULT DeployPackages(
        const std::vector<DeploymentPackageArguments>& deploymentPackageArguments,
        const bool forceDeployment,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivity)
    {
        for (auto package : deploymentPackageArguments)
        {
            initializeActivity.Reset();
            initializeActivity.SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::AddPackage);
            initializeActivity.SetCurrentResourceId(package.identifier);
            if (package.useExistingPackageIfHigherVersion)
            {
                initializeActivity.SetUseExistingPackageIfHigherVersion();
            }

            // If the current application has runFullTrust capability, then Deploy the target package in a Breakaway process.
            // Otherwise, call PackageManager API to deploy the target package.
            // The Singleton package will always set true for forceDeployment and the running process will be terminated to update the package.
            if (initializeActivity.GetIsFullTrustPackage())
            {
                RETURN_IF_FAILED(::WindowsAppRuntime::Deployment::PackageRegistrar::AddOrRegisterPackageInBreakAwayProcess(
                    package.packagePath,
                    package.useExistingPackageIfHigherVersion,
                    forceDeployment || package.isSingleton,
                    initializeActivity,
                    ::WindowsAppRuntime::Deployment::PackageRegistrar::GenerateDeploymentAgentPath()
                ));
            }
            else
            {
                auto packageManager = winrt::Windows::Management::Deployment::PackageManager{};
                RETURN_IF_FAILED(::WindowsAppRuntime::Deployment::PackageRegistrar::AddOrRegisterPackage(
                    package.packagePath,
                    package.useExistingPackageIfHigherVersion,
                    forceDeployment || package.isSingleton,
                    packageManager,
                    initializeActivity
                ));
            }
        }

        return S_OK;
    }
}
