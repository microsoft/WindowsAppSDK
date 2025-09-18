// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>
#include <DeploymentManager.h>
#include <DeploymentResult.h>
#include <DeploymentActivityContext.h>
#include <PackageInfo.h>
#include <Deployer.h>
#include "PackagePathUtilities.h"
#include <TerminalVelocityFeatures-DeploymentAPI.h>
#include <PushNotificationsLongRunningPlatform-Startup.h>
#include "WindowsAppRuntime-License.h"

using namespace winrt;

namespace WindowsAppRuntime::Deployment::Deployer
{
    // Deploys all of the packages carried by the specified framework.
    HRESULT Deploy(const std::wstring& frameworkPackageFullName, const bool forceDeployment) try
    {
        auto& initializeActivityContext = ::WindowsAppRuntime::Deployment::Activity::Context::Get();
        ::WindowsAppRuntime::Deployment::PackagePathUtilities packagePathUtilities{};
        RETURN_IF_FAILED(InstallLicenses(frameworkPackageFullName, initializeActivityContext, packagePathUtilities.GetPackagePath(frameworkPackageFullName)));
        RETURN_IF_FAILED(DeployPackages(frameworkPackageFullName, forceDeployment, initializeActivityContext, packagePathUtilities));
        return S_OK;
    }
    CATCH_RETURN()

    HRESULT InstallLicenses(
        const std::wstring& frameworkPackageFullName,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext,
        std::wstring packagePath
    )
    {
        initializeActivityContext.SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::GetLicensePath);

        // Build path for licenses
        auto licensePath{ std::filesystem::path(packagePath) };
        licensePath /= WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_FOLDER;
        auto licenseFilespec{ licensePath };
        licenseFilespec /= L"*_license.xml";

        initializeActivityContext.SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::InstallLicense);

        // Deploy the licenses (if any)
        ::Microsoft::Windows::ApplicationModel::Licensing::Installer licenseInstaller;
        WIN32_FIND_DATA findFileData{};
        wil::unique_hfind hfind{ FindFirstFileW(licenseFilespec.c_str(), &findFileData) };
        if (!hfind)
        {
            const auto lastError{ GetLastError() };
            RETURN_HR_IF_MSG(HRESULT_FROM_WIN32(lastError), (lastError != ERROR_FILE_NOT_FOUND) && (lastError != ERROR_PATH_NOT_FOUND),
                             "FindFirstFile:%ls", licenseFilespec.c_str());
            return S_OK;
        }
        for (;;)
        {
            // Install the license file
            auto licenseFilename{ licensePath };
            licenseFilename /= findFileData.cFileName;

            initializeActivityContext.Reset();
            initializeActivityContext.SetCurrentResourceId(licenseFilename);

            RETURN_IF_FAILED_MSG(licenseInstaller.InstallLicenseFile(licenseFilename.c_str()),
                                 "LicenseFile:%ls", licenseFilename.c_str());

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

    HRESULT DeployPackages(
        const std::wstring& frameworkPackageFullName,
        const bool forceDeployment,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivity,
        ::WindowsAppRuntime::Deployment::PackagePathUtilities& packagePathUtilities
    )
    {
        initializeActivity.SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::GetPackagePath);
        const auto frameworkPath{ std::filesystem::path(packagePathUtilities.GetPackagePath(frameworkPackageFullName)) };

        initializeActivity.SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::AddPackage);
        for (auto package : winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation::c_targetPackages)
        {
            auto isSingleton{ CompareStringOrdinal(package.identifier.c_str(), -1, WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_SINGLETON, -1, TRUE) == CSTR_EQUAL };
            initializeActivity.Reset();
            initializeActivity.SetCurrentResourceId(package.identifier);

            std::filesystem::path packagePath{};

            // If there is exisiting target package version higher than that of framework current version package, then re-register it.
            // Otherwise, deploy the target msix package from the current framework package version.
            auto existingPackageIfHigherVersion = winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation::g_existingTargetPackagesIfHigherVersion.find(package.identifier);
            auto useExistingPackageIfHigherVersion { existingPackageIfHigherVersion != winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation::g_existingTargetPackagesIfHigherVersion.end() };
            if (useExistingPackageIfHigherVersion)
            {
                initializeActivity.SetUseExistingPackageIfHigherVersion();
                packagePath = std::filesystem::path(packagePathUtilities.GetPackagePath(existingPackageIfHigherVersion->second));
                packagePath /= WINDOWSAPPRUNTIME_PACKAGE_MANIFEST_FILE;
            }
            else
            {
                packagePath = frameworkPath;
                packagePath /= WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_FOLDER;
                packagePath /= package.identifier + WINDOWSAPPRUNTIME_FRAMEWORK_PACKAGE_FILE_EXTENSION;
            }

            // If the current application has runFullTrust capability, then Deploy the target package in a Breakaway process.
            // Otherwise, call PackageManager API to deploy the target package.
            // The Singleton package will always set true for forceDeployment and the running process will be terminated to update the package.
            if (initializeActivity.GetIsFullTrustPackage())
            {

                RETURN_IF_FAILED(::WindowsAppRuntime::Deployment::PackageRegistrar::AddOrRegisterPackageInBreakAwayProcess(
                    packagePath,
                    useExistingPackageIfHigherVersion,
                    forceDeployment || isSingleton,
                    initializeActivity
                ));
            }
            else
            {
                auto packageManager = winrt::Windows::Management::Deployment::PackageManager{};
                RETURN_IF_FAILED(::WindowsAppRuntime::Deployment::PackageRegistrar::AddOrRegisterPackage(
                    packagePath,
                    useExistingPackageIfHigherVersion,
                    forceDeployment || isSingleton,
                    packageManager,
                    initializeActivity
                ));
            }

            // Always restart Push Notifications Long Running Platform when Singleton package is processed and installed.
            if (isSingleton)
            {
                // wil callback is set up to log telemetry events for Push Notifications LRP.
                LOG_IF_FAILED_MSG(StartupNotificationsLongRunningPlatform(), "Restarting Notifications LRP failed in all 3 attempts.");
            }
        }

        return S_OK;
    }
}