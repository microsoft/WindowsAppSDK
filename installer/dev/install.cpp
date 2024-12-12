// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "packages.h"
#include "install.h"
#include "MachineTypeAttributes.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

using namespace winrt;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation;
using namespace Windows::Management::Deployment;
using namespace Windows::System;
using namespace WindowsAppRuntimeInstaller::InstallActivity;
using namespace WindowsAppRuntimeInstaller::Console;

namespace WindowsAppRuntimeInstaller
{

    HRESULT GetAndLogDeploymentOperationResult(
        WindowsAppRuntimeInstaller::InstallActivity::Context& installActivityContext,
        const winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Windows::Management::Deployment::DeploymentResult, winrt::Windows::Management::Deployment::DeploymentProgress> deploymentOperation)
    {
        deploymentOperation.get();
        if (deploymentOperation.Status() != AsyncStatus::Completed)
        {
            const auto deploymentResult{ deploymentOperation.GetResults() };
            installActivityContext.SetDeploymentErrorInfo(
                deploymentOperation.ErrorCode(),
                deploymentResult.ExtendedErrorCode(),
                deploymentResult.ErrorText().c_str(),
                deploymentResult.ActivityId());

            RETURN_HR(static_cast<HRESULT>(deploymentResult.ExtendedErrorCode() ? deploymentResult.ExtendedErrorCode() : deploymentOperation.ErrorCode()));
        }

        return S_OK;
    }

    HRESULT RegisterPackage(
        WindowsAppRuntimeInstaller::InstallActivity::Context& installActivityContext,
        const std::wstring& packageFullName,
        bool forceDeployment)
    {
        const auto deploymentOptions{ forceDeployment ?
            winrt::Windows::Management::Deployment::DeploymentOptions::ForceTargetApplicationShutdown :
            winrt::Windows::Management::Deployment::DeploymentOptions::None };

        PackageManager packageManager;

        return GetAndLogDeploymentOperationResult(
            installActivityContext,
            packageManager.RegisterPackageByFullNameAsync(packageFullName, nullptr, deploymentOptions));
    }

    HRESULT AddPackage(
        WindowsAppRuntimeInstaller::InstallActivity::Context& installActivityContext,
        const Uri& packageUri,
        const std::unique_ptr<PackageProperties>&,
        bool forceDeployment)
    {
        const auto deploymentOptions{ forceDeployment ?
            winrt::Windows::Management::Deployment::DeploymentOptions::ForceTargetApplicationShutdown :
            winrt::Windows::Management::Deployment::DeploymentOptions::None };

        PackageManager packageManager;

        return GetAndLogDeploymentOperationResult(
            installActivityContext,
            packageManager.AddPackageAsync(packageUri, nullptr, deploymentOptions));
    }

    HRESULT StagePackage(
        WindowsAppRuntimeInstaller::InstallActivity::Context& installActivityContext,
        const Uri& packageUri)
    {
        PackageManager packageManager;

        return GetAndLogDeploymentOperationResult(
            installActivityContext,
            packageManager.StagePackageAsync(packageUri, nullptr, DeploymentOptions::None));
    }

    HRESULT AddOrStagePackage(
        WindowsAppRuntimeInstaller::InstallActivity::Context& installActivityContext,
        const Uri& packageUri,
        const std::unique_ptr<PackageProperties>& packageProperties,
        bool forceDeployment)
    {
        // Windows doesn't support registering packages for LocalSystem
        // If you're doing that you're really intending to provision the package for all users on the machine
        // That means we need to Stage the package instead of Add it
        if (installActivityContext.IsLocalSystemUser())
        {
            installActivityContext.SetInstallStage(InstallStage::StagePackage);
            RETURN_IF_FAILED(StagePackage(installActivityContext, packageUri));
        }
        else
        {
            installActivityContext.SetInstallStage(InstallStage::AddPackage);
            RETURN_IF_FAILED(AddPackage(installActivityContext, packageUri, packageProperties, forceDeployment));
        }
        return S_OK;
    }

    HRESULT ProvisionPackage(const std::wstring& packageFamilyName)
    {
        PackageManager packageManager;
        const auto deploymentOperation{ packageManager.ProvisionPackageForAllUsersAsync(packageFamilyName.c_str()) };
        deploymentOperation.get();
        if (deploymentOperation.Status() != AsyncStatus::Completed)
        {
            const auto deploymentResult{ deploymentOperation.GetResults() };
            WindowsAppRuntimeInstaller::InstallActivity::Context::Get().SetDeploymentErrorActivityId(deploymentResult.ActivityId());

            HRESULT errorCode{ static_cast<HRESULT>(deploymentOperation.ErrorCode()) };
            WindowsAppRuntimeInstaller::InstallActivity::Context::Get().LogInstallerFailureEvent(errorCode);
            return errorCode;
        }
        return S_OK;
    }

    bool IsPackageApplicable(const std::unique_ptr<PackageProperties>& packageProperties, const DeploymentBehavior& deploymentBehavior, const ProcessorArchitecture& systemArchitecture)
    {
        // Neutral package architecture is applicable on all systems.
        if (packageProperties->architecture == ProcessorArchitecture::Neutral)
        {
            return true;
        }

        // Same-arch is always applicable for any package type.
        if (packageProperties->architecture == systemArchitecture)
        {
            return true;
        }

        // It is assumed that all available architectures for non-framework packages are present,
        // so only the same-architecture or neutral will be matched for non-frameworks.
        if (!packageProperties->isFramework && (deploymentBehavior != DeploymentBehavior::Framework))
        {
            return false;
        }

        // Framework packages have additional logic.

        // On x64 systems, x86 architecture is also applicable.
        if (systemArchitecture == ProcessorArchitecture::X64 && packageProperties->architecture == ProcessorArchitecture::X86)
        {
            return true;
        }

        // On Windows 11 (i.e. builds 22000+) ARM64 systems, all framework package architectures are applicable.
        // On Windows 10 (i.e. builds 17763-190**) ARM64 systems (which don't support X64 apps), all x64 framework package architectures, except x64, are applicable.
        if (systemArchitecture == ProcessorArchitecture::Arm64)
        {
            if (packageProperties->architecture == ProcessorArchitecture::X64)
            {
                return MachineTypeAttributes::IsWindows11_IsArchitectureSupportedInUserMode(IMAGE_FILE_MACHINE_AMD64);
            }

            return true;
        }

        return false;
    }

    wil::com_ptr<IStream> CreateMemoryStream(const BYTE* data, size_t size)
    {
        wil::com_ptr<IStream> retval;
        retval.attach(::SHCreateMemStream(data, static_cast<UINT>(size)));
        return retval;
    }

    wil::com_ptr<IStream> GetResourceStream(const std::wstring& resourceName, const std::wstring& resourceType)
    {
        HMODULE const hModule{ GetModuleHandle(NULL) };
        HRSRC hResourceSource{ ::FindResource(hModule, resourceName.c_str(), resourceType.c_str()) };
        THROW_LAST_ERROR_IF_NULL(hResourceSource);
        HGLOBAL hResource{ LoadResource(hModule, hResourceSource) };
        THROW_LAST_ERROR_IF_NULL(hResource);
        const BYTE* data{ reinterpret_cast<BYTE*>(::LockResource(hResource)) };
        THROW_LAST_ERROR_IF_NULL(data);
        const DWORD size{ ::SizeofResource(hModule, hResourceSource) };
        return CreateMemoryStream(data, size);
    }

    std::unique_ptr<PackageProperties> GetPackagePropertiesFromStream(wil::com_ptr<IStream>& stream)
    {
        // Get PackageId from the manifest.
        auto factory{ wil::CoCreateInstance<AppxFactory, IAppxFactory>() };
        wil::com_ptr<IAppxPackageReader> reader;
        THROW_IF_FAILED(factory->CreatePackageReader(stream.get(), wil::out_param(reader)));
        wil::com_ptr<IAppxManifestReader> manifest;
        THROW_IF_FAILED(reader->GetManifest(wil::out_param(manifest)));
        wil::com_ptr<IAppxManifestPackageId> id;
        THROW_IF_FAILED(manifest->GetPackageId(&id));

        // Populate properties from the manifest PackageId
        auto properties{ std::make_unique<PackageProperties>() };
        THROW_IF_FAILED(id->GetPackageFullName(&properties->fullName));
        THROW_IF_FAILED(id->GetPackageFamilyName(&properties->familyName));
        APPX_PACKAGE_ARCHITECTURE arch{};
        THROW_IF_FAILED(id->GetArchitecture(&arch));
        properties->architecture = static_cast<ProcessorArchitecture>(arch);
        THROW_IF_FAILED(id->GetVersion(&properties->version));

        // Populate framework from the manifest properties.
        wil::com_ptr<IAppxManifestProperties> manifestProperties;
        THROW_IF_FAILED(manifest->GetProperties(wil::out_param(manifestProperties)));
        BOOL isFramework{};
        THROW_IF_FAILED(manifestProperties->GetBoolValue(L"Framework", &isFramework));
        properties->isFramework = isFramework == TRUE;

        return properties;
    }

    wil::com_ptr<IStream> OpenFileStream(PCWSTR path)
    {
        wil::com_ptr<IStream> outstream;
        THROW_IF_FAILED(SHCreateStreamOnFileEx(path, STGM_WRITE | STGM_READ | STGM_SHARE_DENY_WRITE | STGM_CREATE, FILE_ATTRIBUTE_NORMAL, TRUE, nullptr, wil::out_param(outstream)));
        return outstream;
    }

    // RestartPushNotificationsLRP is best effort and non-blocking to Installer functionality.
    // Any failures in this helper method will be logged in Telemetry but will not return error to the caller.
    void RestartPushNotificationsLRP()
    {
        WindowsAppRuntimeInstaller::InstallActivity::Context::Get().SetInstallStage(WindowsAppRuntimeInstaller::InstallActivity::InstallStage::RestartPushNotificationsLRP);

        IID pushNotificationsIMPL_CLSID;
        LOG_IF_FAILED(CLSIDFromString(PUSHNOTIFICATIONS_IMPL_CLSID_WSTRING, &pushNotificationsIMPL_CLSID));

        IID pushNotificationsLRP_IID;
        LOG_IF_FAILED(CLSIDFromString(PUSHNOTIFICATIONS_LRP_CLSID_WSTRING, &pushNotificationsLRP_IID));

        wil::com_ptr<::IUnknown> pNotificationsLRP{};

        unsigned int retries{ 0 };
        HRESULT hr{ S_OK };
        while (retries < 3)
        {
            hr = CoCreateInstance(pushNotificationsIMPL_CLSID,
                NULL,
                CLSCTX_LOCAL_SERVER,
                pushNotificationsLRP_IID,
                reinterpret_cast<LPVOID*>(pNotificationsLRP.put()));

            if (SUCCEEDED(hr))
            {
                break;
            }
            retries++;
        }
        // WIL call back is setup to log telemetry event for any failure in restarting Notifications LRP.
        // Due to a bug in Windows OS, RestartPushNotificationsLRP will fail if Installer is run with Elevated privileges (IOW, with Admin privileges).
        LOG_IF_FAILED_MSG(hr, "Restarting Push Notifications LRP failed after 3 attempts.");
    }

    void DeployPackageFromResource(const WindowsAppRuntimeInstaller::ResourcePackageInfo& resource, const WindowsAppRuntimeInstaller::Options& options,
        const ProcessorArchitecture& systemArchitecture, const std::wstring& applicableSingletonResourceID)
    {
        const auto quiet{ WI_IsFlagSet(options, WindowsAppRuntimeInstaller::Options::Quiet) };
        const auto forceDeployment{ WI_IsFlagSet(options, WindowsAppRuntimeInstaller::Options::ForceDeployment) };
        auto& installActivityContext{ WindowsAppRuntimeInstaller::InstallActivity::Context::Get() };

        installActivityContext.SetInstallStage(InstallStage::GetPackageProperties);

        // Get package properties by loading the resource as a stream and reading the manifest.
        auto packageStream{ GetResourceStream(resource.id, resource.resourceType) };
        auto packageProperties{ GetPackagePropertiesFromStream(packageStream) };

        installActivityContext.SetCurrentResourceId(packageProperties->fullName.get());

        // Skip non-applicable packages.
        if (!IsPackageApplicable(packageProperties, resource.deploymentBehavior, systemArchitecture))
        {
            return;
        }

        // Correct WindowsAppSDK MSIX package is considered installed if it's version is same or higher than that from the installer.
        // Check if a higher version of the package is already installed.
        PackageManager packageManager;
        winrt::hstring currentUserSID;
        auto installedPackages{ packageManager.FindPackagesForUserWithPackageTypes(currentUserSID, packageProperties->familyName.get(),
                                                                                                            ::Windows::Management::Deployment::PackageTypes::Framework |
                                                                                                            ::Windows::Management::Deployment::PackageTypes::Main) };
        bool isPackageInstalledAndIsPackageStatusOK{};

        // installedPackages can contain only one version of the packagefamily across all servicing revisions of a WindowsAppSDK version.
        // installedPackages can contain different architectures of same package version (for Framework package).
        for (auto installedPackage : installedPackages)
        {
            // For the already installed package of same WindowsAppSDK Major.Minor version with matching architecture, compare version
            if (installedPackage.Id().Architecture() == packageProperties->architecture)
            {
                const auto installedPackageVersion{ AppModel::Package::ToPackageVersion(installedPackage.Id().Version()).Version };
                if (installedPackageVersion > packageProperties->version)
                {
                    installActivityContext.SetExistingPackageIfHigherVersion(installedPackage.Id().FullName());
                    isPackageInstalledAndIsPackageStatusOK = installedPackage.Status().VerifyIsOK();
                }
                else if (installedPackageVersion == packageProperties->version)
                {
                    isPackageInstalledAndIsPackageStatusOK = installedPackage.Status().VerifyIsOK();
                }
            }
        }

        // Install option should install the applicable WindowsAppSDK MSIX package only if it is not already installed or if it's status is not OK.
        // Repair option should install the applicable WindowsAppSDK MSIX package independent of it's state.
        if (WI_IsFlagSet(options, WindowsAppRuntimeInstaller::Options::InstallPackages) ||
            WI_IsFlagSet(options, WindowsAppRuntimeInstaller::Options::Install))
        {
            if (isPackageInstalledAndIsPackageStatusOK)
            {
                // If currently installed Package (either same or higher version than the version from the installer) is in good state, clear the package higher version and return.
                installActivityContext.SetExistingPackageIfHigherVersion(L"");  
                return;
            }
        }

        PCWSTR c_windowsAppRuntimeTempDirectoryPrefix{ L"MSIX" };
        wchar_t packageFilename[MAX_PATH];
        THROW_LAST_ERROR_IF(0 == GetTempFileName(std::filesystem::temp_directory_path().c_str(), c_windowsAppRuntimeTempDirectoryPrefix, 0u, packageFilename));

        // GetTempFileName will create the temp file by that name due to the unique parameter being specified.
        // From here on out if we leave scope for any reason we will attempt to delete that file.
        auto removeTempFileOnScopeExit{ wil::scope_exit([&]
            {
                LOG_IF_WIN32_BOOL_FALSE(::DeleteFile(packageFilename));
            }) };

        if (!quiet)
        {
            std::wcout << L"Deploying package: " << packageProperties->fullName.get() << std::endl;
        }

        // DryRun = Don't do the work
        if (WI_IsFlagSet(options, WindowsAppRuntimeInstaller::Options::DryRun))
        {
            return;
        }

        HRESULT hrDeploymentResult{};

        // Windows doesn't support registering packages for LocalSystem
        // If you're doing that you're really intending to provision the package for all users on the machine
        if (installActivityContext.GetExistingPackageIfHigherVersion().size() &&
            !installActivityContext.IsLocalSystemUser())
        {
           installActivityContext.SetInstallStage(InstallStage::RegisterPackage);

            // Re-register higher version of the package that is already installed.
           hrDeploymentResult = RegisterPackage(installActivityContext, installActivityContext.GetExistingPackageIfHigherVersion().c_str(), forceDeployment);

           // Clear the package higher version after it has been re-registered 
           installActivityContext.SetExistingPackageIfHigherVersion(L"");
        }
        else
        {
            installActivityContext.SetInstallStage(InstallStage::CreatePackageURI);

            // Write the package to a temp file. The PackageManager APIs require a Uri.
            wil::com_ptr<IStream> outStream{ OpenFileStream(packageFilename) };
            ULARGE_INTEGER streamSize{};
            THROW_IF_FAILED(::IStream_Size(packageStream.get(), &streamSize));
            THROW_IF_FAILED(packageStream->CopyTo(outStream.get(), streamSize, nullptr, nullptr));
            THROW_IF_FAILED(outStream->Commit(STGC_OVERWRITE));
            outStream.reset();

            // Add-or-Stage the package
            Uri packageUri{ packageFilename };
            hrDeploymentResult = AddOrStagePackage(installActivityContext, packageUri, packageProperties, forceDeployment);
        }
        if (!quiet)
        {
            std::wcout << "Package deployment result : 0x" << std::hex << hrDeploymentResult << " ";
            DisplayError(hrDeploymentResult);
        }
        THROW_IF_FAILED(hrDeploymentResult);

        // If successful install is for Singleton package, restart Push Notifications Long Running Platform when ForceDeployment option is applied.
        if (WI_IsFlagSet(options, WindowsAppRuntimeInstaller::Options::ForceDeployment))
        {
            if (CompareStringOrdinal(resource.id.c_str(), static_cast<int>(resource.id.size()), applicableSingletonResourceID.c_str(), static_cast<int>(applicableSingletonResourceID.size()), TRUE) == CSTR_EQUAL)
            {
                RestartPushNotificationsLRP();
            }
        }

        // Framework provisioning is not supported by the PackageManager ProvisionPackageForAllUsersAsync API.
        // Hence, skip attempting to provision framework package.
        if (!packageProperties->isFramework && Security::IntegrityLevel::IsElevated())
        {
            installActivityContext.SetInstallStage(InstallStage::ProvisionPackage);

            // Provisioning is expected to fail if the program is not run elevated or the user is not admin.
            auto hrProvisionResult{ ProvisionPackage(packageProperties->familyName.get()) };
            if (!quiet)
            {
                std::wcout << "Provisioning result : 0x" << std::hex << hrProvisionResult << " ";
                DisplayError(hrProvisionResult);
            }
            LOG_IF_FAILED(hrProvisionResult);
        }
    }

    HRESULT Deploy(const WindowsAppRuntimeInstaller::Options options) noexcept try
    {
        // Install licenses before packages as we stop on first error. If something
        // does go wrong better to have all licenses and some packages than all
        // packages and some licenses, as the latter is harder to detect something
        // is wrong (there's lots of ways to tell if a package is present or not
        // but very few to determine if licenses are present). So worst case,
        // it's easier (for tools and people) to see 'incomplete packages' and
        // know what to do about it than for 'incomplete licenses'.
        RETURN_IF_FAILED(InstallLicenses(options));
        RETURN_IF_FAILED(DeployPackages(options));

        return S_OK;
    }
    CATCH_RETURN()

    HRESULT InstallLicenses(const WindowsAppRuntimeInstaller::Options options)
    {
#if defined(MSIX_PROCESS_LICENSES)
        const auto quiet{ WI_IsFlagSet(options, WindowsAppRuntimeInstaller::Options::Quiet) };

        if (WI_IsFlagSet(options, WindowsAppRuntimeInstaller::Options::InstallLicenses) ||
            WI_IsFlagSet(options, WindowsAppRuntimeInstaller::Options::Install) ||
            WI_IsFlagSet(options, WindowsAppRuntimeInstaller::Options::Repair))
        {
            auto& installActivityContext{ WindowsAppRuntimeInstaller::InstallActivity::Context::Get() };
            installActivityContext.SetInstallStage(InstallStage::InstallLicense);

            Microsoft::Windows::ApplicationModel::Licensing::Installer licenseInstaller;
            for (const auto& license : WindowsAppRuntimeInstaller::c_licenses)
            {
                installActivityContext.Reset();
                installActivityContext.SetCurrentResourceId(license.id.c_str());
                if (!quiet)
                {
                    std::wcout << "Installing license: " << license.id << std::endl;
                }

                // DryRun = Don't do the work
                if (WI_IsFlagSet(options, WindowsAppRuntimeInstaller::Options::DryRun))
                {
                    continue;
                }

                // Install the license
                auto thisModule{ reinterpret_cast<HINSTANCE>(&__ImageBase) };
                const auto hr{ licenseInstaller.InstallLicense(thisModule, license.id) };
                if (!quiet)
                {
                    std::wcout << "Install License result : 0x" << std::hex << hr << " ";
                    DisplayError(hr);
                }
                RETURN_IF_FAILED_MSG(hr, "License:%ls", license.id.c_str());
            }
        }
#endif
        return S_OK;
    }

    HRESULT DeployPackages(const WindowsAppRuntimeInstaller::Options options)
    {
        if (WI_IsFlagSet(options, WindowsAppRuntimeInstaller::Options::InstallPackages) ||
            WI_IsFlagSet(options, WindowsAppRuntimeInstaller::Options::Install) ||
            WI_IsFlagSet(options, WindowsAppRuntimeInstaller::Options::Repair))
        {
            USHORT processMachine{ IMAGE_FILE_MACHINE_UNKNOWN };
            USHORT nativeMachine{ IMAGE_FILE_MACHINE_UNKNOWN };
            THROW_IF_WIN32_BOOL_FALSE(::IsWow64Process2(::GetCurrentProcess(), &processMachine, &nativeMachine));
            ProcessorArchitecture systemArchitecture{};
            std::wstring applicableSingletonResourceID;
            switch (nativeMachine)
            {
            case IMAGE_FILE_MACHINE_I386:
                systemArchitecture = ProcessorArchitecture::X86;
                applicableSingletonResourceID = MSIX_SINGLETON_X86_ID;
                break;
            case IMAGE_FILE_MACHINE_AMD64:
                systemArchitecture = ProcessorArchitecture::X64;
                applicableSingletonResourceID = MSIX_SINGLETON_X64_ID;
                break;
            case IMAGE_FILE_MACHINE_ARM64:
                systemArchitecture = ProcessorArchitecture::Arm64;
                applicableSingletonResourceID = MSIX_SINGLETON_ARM64_ID;
                break;
            default:
                THROW_HR_MSG(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), "nativeMachine=%hu", nativeMachine);
            }

            for (const auto& package : WindowsAppRuntimeInstaller::c_packages)
            {
                WindowsAppRuntimeInstaller::InstallActivity::Context::Get().Reset();
                DeployPackageFromResource(package, options, systemArchitecture, applicableSingletonResourceID);
            }
        }
        return S_OK;
    }
}
