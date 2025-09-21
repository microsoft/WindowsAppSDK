// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>
#include <DeploymentActivityContext.h>
#include <PackageDefinitions.h>
#include <Deployer.h>
#include <PackageUtilities.h>
#include <functional>

using namespace winrt;

namespace WindowsAppRuntime::Deployment::Deployer
{
    // Deploys all of the packages carried by the specified framework.
    HRESULT Deploy(
        const std::wstring& frameworkPackageFullName,
        const std::function<HRESULT()>& startupNotificationsLongRunningPlatformFunc,
        ILicenseInstaller& licenseInstaller,
        const bool forceDeployment
    ) try
    {
        auto& initializeActivityContext = ::WindowsAppRuntime::Deployment::Activity::Context::Get();

        // Install licenses scope
        {
            initializeActivityContext.SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::GetLicensePath);

            auto packagePath = ::WindowsAppRuntime::Deployment::Package::GetPackagePath(frameworkPackageFullName);

            // Build path for licenses
            auto licensePath{ std::filesystem::path(packagePath) };
            licensePath /= WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_FOLDER;
            auto licenseFilespec{ licensePath };
            licenseFilespec /= L"*_license.xml";

            std::vector<std::wstring> licenseFiles;


            RETURN_IF_FAILED(GetLicenseFiles(licenseFilespec, licenseFiles));

            RETURN_IF_FAILED(InstallLicenses(licenseFiles, licensePath, licenseInstaller, initializeActivityContext));
        }

        //  Deploy packages scope
        {
            std::function<std::wstring(const std::wstring&)> getPackagePathFunc { ::WindowsAppRuntime::Deployment::Package::GetPackagePath };
            auto deploymentPackageArguments = GetDeploymentPackageArguments(frameworkPackageFullName, initializeActivityContext, getPackagePathFunc);
            RETURN_IF_FAILED(DeployPackages(deploymentPackageArguments, forceDeployment, initializeActivityContext, startupNotificationsLongRunningPlatformFunc));
        }

        return S_OK;
    }
    CATCH_RETURN()
    
    // licenseFileSpec: This parameter specifies the file specification (e.g., path and pattern) for the license files to be retrieved.
    // licenseFiles: This is an output parameter that will be populated with the names of the license files found matching the specified file specification.
    HRESULT GetLicenseFiles(const std::wstring& licenseFileSpec, std::vector<std::wstring>& licenseFiles)
    {
        licenseFiles.clear();

        WIN32_FIND_DATA findFileData{};
        wil::unique_hfind hfind{ FindFirstFileW(licenseFileSpec.c_str(), &findFileData) };
        if (!hfind)
        {
            const auto lastError{ GetLastError() };
            RETURN_HR_IF_MSG(HRESULT_FROM_WIN32(lastError), (lastError != ERROR_FILE_NOT_FOUND) && (lastError != ERROR_PATH_NOT_FOUND),
                             "FindFirstFile:%ls", licenseFileSpec.c_str());
            return S_OK;
        }
        for (;;)
        {
            // Add the license file
            licenseFiles.push_back(findFileData.cFileName);

            // Next! (if any)
            if (!FindNextFileW(hfind.get(), &findFileData))
            {
                const auto lastError{ GetLastError() };
                RETURN_HR_IF(HRESULT_FROM_WIN32(lastError), lastError != ERROR_NO_MORE_FILES);
                break;
            }
        }
        return S_OK;
    }

    HRESULT InstallLicenses(
        const std::vector<std::wstring>& licenseFiles,
        std::filesystem::path licensePath,
        ILicenseInstaller& licenseInstaller,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext
    )
    {
        initializeActivityContext.SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::InstallLicense);

        // Deploy the licenses (if any)
        for (const auto& licenseFileName : licenseFiles)
        {
            // Install the license file
            auto licenseFileFullName{ licensePath };
            licenseFileFullName /= licenseFileName;

            // initializeActivityContext.Reset(); --> Why are we reseting here? It clears out all the info.
            initializeActivityContext.SetCurrentResourceId(licenseFileFullName);

            RETURN_IF_FAILED_MSG(licenseInstaller.InstallLicenseFile(licenseFileFullName.c_str()),
                                 "LicenseFile:%ls", licenseFileFullName.c_str());
        }
        return S_OK;
    }

    std::vector<DeploymentPackageArguments> GetDeploymentPackageArguments(
        const std::wstring& frameworkPackageFullName,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext,
        const std::function<std::wstring(const std::wstring&)>& getPackagePathFunc)
    {
        initializeActivityContext.SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::GetPackagePath);

        std::vector<DeploymentPackageArguments> deploymentPackageArguments;

        const auto frameworkPath{ std::filesystem::path(getPackagePathFunc(frameworkPackageFullName)) };
        for (auto package : winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation::c_targetPackages)
        {
            auto isSingleton{ CompareStringOrdinal(package.identifier.c_str(), -1, WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_SINGLETON, -1, TRUE) == CSTR_EQUAL };

            std::filesystem::path packagePath{};

            // If there is exisiting target package version higher than that of framework current version package, then re-register it.
            // Otherwise, deploy the target msix package from the current framework package version.
            auto existingPackageIfHigherVersion = winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation::g_existingTargetPackagesIfHigherVersion.find(package.identifier);
            auto useExistingPackageIfHigherVersion { existingPackageIfHigherVersion != winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation::g_existingTargetPackagesIfHigherVersion.end() };
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
        std::vector<DeploymentPackageArguments> deploymentPackageArguments,
        const bool forceDeployment,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivity,
        const std::function<HRESULT()>& startupNotificationsLongRunningPlatformFunc
    )
    {
        for (auto package : deploymentPackageArguments)
        {
            initializeActivity.Reset();
            initializeActivity.SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::AddPackage);
            initializeActivity.SetCurrentResourceId(package.packageIdentifier);
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
                    initializeActivity
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

            // Always restart Push Notifications Long Running Platform when Singleton package is processed and installed.
            if (package.isSingleton)
            {
                // wil callback is set up to log telemetry events for Push Notifications LRP.
                LOG_IF_FAILED_MSG(startupNotificationsLongRunningPlatformFunc(), "Restarting Notifications LRP failed in all 3 attempts.");
            }
        }

        return S_OK;
    }
}