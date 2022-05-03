// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "packages.h"
#include "install.h"

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
    HRESULT RegisterPackage(const std::wstring& packageFullName)
    {
        PackageManager packageManager;
        const auto deploymentOperation{ packageManager.RegisterPackageByFullNameAsync(packageFullName, nullptr, DeploymentOptions::None) };

        deploymentOperation.get();
        if (deploymentOperation.Status() != AsyncStatus::Completed)
        {
            const auto deploymentResult{ deploymentOperation.GetResults() };
            WindowsAppRuntimeInstaller::InstallActivity::Context::Get().SetDeploymentErrorInfo(
                deploymentResult.ExtendedErrorCode(),
                deploymentResult.ErrorText().c_str(),
                deploymentResult.ActivityId());

            return static_cast<HRESULT>(deploymentOperation.ErrorCode());
        }

        return S_OK;
    }

    HRESULT AddPackage(const Uri& packageUri, const std::unique_ptr<PackageProperties>& packageProperties, bool forceDeployment)
    {
        PackageManager packageManager;

        const auto deploymentOptions{ forceDeployment ?
                winrt::Windows::Management::Deployment::DeploymentOptions::ForceTargetApplicationShutdown :
                winrt::Windows::Management::Deployment::DeploymentOptions::None };

        const auto deploymentOperation{ packageManager.AddPackageAsync(packageUri, nullptr, DeploymentOptions::None) };
        deploymentOperation.get();
        if (deploymentOperation.Status() != AsyncStatus::Completed)
        {
            auto hrAddPackage{ static_cast<HRESULT>(deploymentOperation.ErrorCode()) };
            if (hrAddPackage == ERROR_PACKAGE_ALREADY_EXISTS)
            {
                WindowsAppRuntimeInstaller::InstallActivity::Context::Get().SetInstallStage(InstallStage::RegisterPackage);

                // Package already exists (such as via provisioning), re-register it instead.
                RETURN_IF_FAILED(RegisterPackage(packageProperties->fullName.get()));
                return S_OK;
            }
            else
            {
                const auto deploymentResult{ deploymentOperation.GetResults() };
                WindowsAppRuntimeInstaller::InstallActivity::Context::Get().SetDeploymentErrorInfo(deploymentResult.ExtendedErrorCode(), deploymentResult.ErrorText().c_str(), deploymentResult.ActivityId());

                RETURN_HR(hrAddPackage);
            }
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

    bool IsPackageApplicable(const std::unique_ptr<PackageProperties>& packageProperties, DeploymentBehavior deploymentBehavior)
    {
        // Neutral package architecture is applicable on all systems.
        if (packageProperties->architecture == ProcessorArchitecture::Neutral)
        {
            return true;
        }

        USHORT processMachine{ IMAGE_FILE_MACHINE_UNKNOWN };
        USHORT nativeMachine{ IMAGE_FILE_MACHINE_UNKNOWN };
        THROW_IF_WIN32_BOOL_FALSE(::IsWow64Process2(::GetCurrentProcess(), &processMachine, &nativeMachine));
        ProcessorArchitecture systemArchitecture{};
        switch (nativeMachine)
        {
        case IMAGE_FILE_MACHINE_I386:
            systemArchitecture = ProcessorArchitecture::X86;
            break;
        case IMAGE_FILE_MACHINE_AMD64:
            systemArchitecture = ProcessorArchitecture::X64;
            break;
        case IMAGE_FILE_MACHINE_ARM64:
            systemArchitecture = ProcessorArchitecture::Arm64;
            break;
        default:
            THROW_HR_MSG(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), "nativeMachine=%hu", nativeMachine);
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

        // On Arm64 systems, all current package architectures are applicable.
        if (systemArchitecture == ProcessorArchitecture::Arm64)
        {
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
        BOOL isFramework{ FALSE };
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

    void DeployPackageFromResource(const WindowsAppRuntimeInstaller::ResourcePackageInfo& resource, const WindowsAppRuntimeInstaller::Options options)
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
        if (!IsPackageApplicable(packageProperties, resource.deploymentBehavior))
        {
            return;
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
            std::wcout << "Deploying package: " << packageProperties->fullName.get() << std::endl;
        }

        // DryRun = Don't do the work
        if (WI_IsFlagSet(options, WindowsAppRuntimeInstaller::Options::DryRun))
        {
            return;
        }

        installActivityContext.SetInstallStage(InstallStage::CreatePackageURI);

        // Write the package to a temp file. The PackageManager APIs require a Uri.
        wil::com_ptr<IStream> outStream{ OpenFileStream(packageFilename) };
        ULARGE_INTEGER streamSize{};
        THROW_IF_FAILED(::IStream_Size(packageStream.get(), &streamSize));
        THROW_IF_FAILED(packageStream->CopyTo(outStream.get(), streamSize, nullptr, nullptr));
        THROW_IF_FAILED(outStream->Commit(STGC_OVERWRITE));
        outStream.reset();

        installActivityContext.SetInstallStage(InstallStage::AddPackage);

        // Add the package
        Uri packageUri{ packageFilename };
        auto hrAddResult{ AddPackage(packageUri, packageProperties, forceDeployment) };
        if (!quiet)
        {
            std::wcout << "Package deployment result : 0x" << std::hex << hrAddResult << " ";
            DisplayError(hrAddResult);
        }
        THROW_IF_FAILED(hrAddResult);

        // Framework provisioning is not supported by the PackageManager ProvisionPackageForAllUsersAsync API.
        // Hence, skip attempting to provision framework package.
        if (!packageProperties->isFramework &&
            Security::IntegrityLevel::IsElevated())
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
        // wil call back is setup to log telemetry event for any failure in restarting Notifications LRP
        LOG_IF_FAILED_MSG(hr, "Restarting Push Notifications LRP failed after 3 attempts.");
    }

    HRESULT InstallLicenses(const WindowsAppRuntimeInstaller::Options options)
    {
#if defined(MSIX_PROCESS_LICENSES)
        const auto quiet{ WI_IsFlagSet(options, WindowsAppRuntimeInstaller::Options::Quiet) };

        if (WI_IsFlagSet(options, WindowsAppRuntimeInstaller::Options::InstallLicenses))
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
                    std::wcout << "Install result : 0x" << std::hex << hr << " ";
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
        if (WI_IsFlagSet(options, WindowsAppRuntimeInstaller::Options::InstallPackages))
        {
            for (const auto& package : WindowsAppRuntimeInstaller::c_packages)
            {
                WindowsAppRuntimeInstaller::InstallActivity::Context::Get().Reset();
                DeployPackageFromResource(package, options);

                // Restart Push Notifications Long Running Platform when ForceDeployment option is applied.
                if (WI_IsFlagSet(options, WindowsAppRuntimeInstaller::Options::ForceDeployment) &&
                    CompareStringOrdinal(package.id.c_str(), static_cast<int>(package.id.size() - 3), MSIX_SINGLETON_X86_ID, static_cast<int>(package.id.size() - 3), TRUE) == CSTR_EQUAL)
                {
                    RestartPushNotificationsLRP();
                }
            }
        }

        return S_OK;
    }
}
