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

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    // Deploys all of the packages carried by the specified framework.
    HRESULT Deployer::Deploy(const std::wstring& frameworkPackageFullName, const bool forceDeployment) try
    {
        auto& initializeActivityContext = ::WindowsAppRuntime::Deployment::Activity::Context::Get();
        RETURN_IF_FAILED(InstallLicenses(frameworkPackageFullName, initializeActivityContext));
        RETURN_IF_FAILED(DeployPackages(frameworkPackageFullName, forceDeployment));
        return S_OK;
    }
    CATCH_RETURN()

    HRESULT Deployer::InstallLicenses(
        const std::wstring& frameworkPackageFullName,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext
    )
    {
        initializeActivityContext.SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::GetLicensePath);

        // Build path for licenses
        auto licensePath{ std::filesystem::path(PackagePathUtilities::GetPackagePath(frameworkPackageFullName)) };
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

    HRESULT Deployer::DeployPackages(const std::wstring& frameworkPackageFullName, const bool forceDeployment)
    {
        auto initializeActivity{ ::WindowsAppRuntime::Deployment::Activity::Context::Get() };

        initializeActivity.SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::GetPackagePath);
        const auto frameworkPath{ std::filesystem::path(PackagePathUtilities::GetPackagePath(frameworkPackageFullName)) };

        initializeActivity.SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::AddPackage);
        for (auto package : c_targetPackages)
        {
            auto isSingleton{ CompareStringOrdinal(package.identifier.c_str(), -1, WINDOWSAPPRUNTIME_PACKAGE_SUBTYPENAME_SINGLETON, -1, TRUE) == CSTR_EQUAL };
            initializeActivity.Reset();
            initializeActivity.SetCurrentResourceId(package.identifier);

            std::filesystem::path packagePath{};

            // If there is exisiting target package version higher than that of framework current version package, then re-register it.
            // Otherwise, deploy the target msix package from the current framework package version.
            auto existingPackageIfHigherVersion = g_existingTargetPackagesIfHigherVersion.find(package.identifier);
            auto useExistingPackageIfHigherVersion { existingPackageIfHigherVersion != g_existingTargetPackagesIfHigherVersion.end() };
            if (useExistingPackageIfHigherVersion)
            {
                initializeActivity.SetUseExistingPackageIfHigherVersion();
                packagePath = std::filesystem::path(PackagePathUtilities::GetPackagePath(existingPackageIfHigherVersion->second));
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

                RETURN_IF_FAILED(AddOrRegisterPackageInBreakAwayProcess(packagePath, useExistingPackageIfHigherVersion, forceDeployment || isSingleton));
            }
            else
            {
                RETURN_IF_FAILED(AddOrRegisterPackage(packagePath, useExistingPackageIfHigherVersion, forceDeployment || isSingleton));
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

    // If useExistingPackageIfHigherVersion == false, Adds the current version package at the passed in path using PackageManager.
    // If useExistingPackageIfHigherVersion == true, Registers the higher version package using the passed in path as manifest path and PackageManager.
    // This requires the 'packageManagement' or 'runFullTrust' capabilities.
    HRESULT Deployer::AddOrRegisterPackage(const std::filesystem::path& path, const bool useExistingPackageIfHigherVersion, const bool forceDeployment) try
    {
        winrt::Windows::Management::Deployment::PackageManager packageManager;

        const auto options{ forceDeployment ?
                            winrt::Windows::Management::Deployment::DeploymentOptions::ForceTargetApplicationShutdown :
                            winrt::Windows::Management::Deployment::DeploymentOptions::None };

        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Windows::Management::Deployment::DeploymentResult,
            winrt::Windows::Management::Deployment::DeploymentProgress> deploymentOperation;

        const auto pathUri { winrt::Windows::Foundation::Uri(path.c_str()) };
        if (useExistingPackageIfHigherVersion)
        {
            deploymentOperation = packageManager.RegisterPackageAsync(pathUri, nullptr, options);
        }
        else
        {
            deploymentOperation = packageManager.AddPackageAsync(pathUri, nullptr, options);
        }
        deploymentOperation.get();
        const auto deploymentResult{ deploymentOperation.GetResults() };
        HRESULT deploymentOperationHResult{};
        HRESULT deploymentOperationExtendedHResult{};

        if (deploymentOperation.Status() != winrt::Windows::Foundation::AsyncStatus::Completed)
        {
            deploymentOperationHResult = static_cast<HRESULT>(deploymentOperation.ErrorCode());
            deploymentOperationExtendedHResult = deploymentResult.ExtendedErrorCode();

            ::WindowsAppRuntime::Deployment::Activity::Context::Get().SetDeploymentErrorInfo(
                deploymentOperationExtendedHResult,
                deploymentResult.ErrorText().c_str(),
                deploymentResult.ActivityId());
        }

        // If deploymentOperationHResult indicates success, take that, ignore deploymentOperationExtendedHResult.
        // Otherwise, return deploymentOperationExtendedHResult if there is an error in it, if not, return deploymentOperationHResult.
        return SUCCEEDED(deploymentOperationHResult) ? deploymentOperationHResult :
            (FAILED(deploymentOperationExtendedHResult) ? deploymentOperationExtendedHResult : deploymentOperationHResult);
    }
    CATCH_RETURN()

    std::wstring Deployer::GenerateDeploymentAgentPath()
    {
        // Calculate the path to the restart agent as being in the same directory as the current module.
        wil::unique_hmodule module;
        THROW_IF_WIN32_BOOL_FALSE(GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, reinterpret_cast<PCWSTR>(Deployer::GenerateDeploymentAgentPath), &module));

        std::filesystem::path modulePath{ wil::GetModuleFileNameW<std::wstring>(module.get()) };
        return modulePath.parent_path() / c_deploymentAgentFilename;
    }

    /// @warning This function is ONLY for processes with package identity. It's the caller's responsibility to ensure this.
    HRESULT Deployer::AddOrRegisterPackageInBreakAwayProcess(const std::filesystem::path& path, const bool useExistingPackageIfHigherVersion, const bool forceDeployment) try
    {
        auto exePath{ GenerateDeploymentAgentPath() };
        auto activityId{ winrt::to_hstring(*::WindowsAppRuntime::Deployment::Activity::Context::Get().GetActivity().Id()) };

        // <currentdirectory>\deploymentagent.exe <custom arguments passed by caller>
        auto cmdLine{ wil::str_printf<wil::unique_cotaskmem_string>(L"\"%s\" %u \"%s\" %u %s", exePath.c_str(), (useExistingPackageIfHigherVersion ? 1 : 0), path.c_str(), (forceDeployment ? 1 : 0), activityId.c_str()) };

        SIZE_T attributeListSize{};
        auto attributeCount{ 1 };

        // attributeCount is always >0 so we need to allocate a buffer. Call InitializeProcThreadAttributeList()
        // to determine the size needed so we always expect ERROR_INSUFFICIENT_BUFFER.
        THROW_HR_IF(E_UNEXPECTED, !!InitializeProcThreadAttributeList(nullptr, attributeCount, 0, &attributeListSize));
        const auto lastError{ GetLastError() };
        THROW_HR_IF(HRESULT_FROM_WIN32(lastError), lastError != ERROR_INSUFFICIENT_BUFFER);
        wistd::unique_ptr<BYTE[]> attributeListBuffer{ new BYTE[attributeListSize] };
        auto attributeList{ reinterpret_cast<PPROC_THREAD_ATTRIBUTE_LIST>(attributeListBuffer.get()) };
        THROW_IF_WIN32_BOOL_FALSE(InitializeProcThreadAttributeList(attributeList, attributeCount, 0, &attributeListSize));
        auto freeAttributeList{ wil::scope_exit([&] { DeleteProcThreadAttributeList(attributeList); }) };

        // https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-updateprocthreadattribute
        // The process being created will create any child processes outside of the desktop app runtime environment.
        // This behavior is the default for processes for which no policy has been set
        DWORD policy{ PROCESS_CREATION_DESKTOP_APP_BREAKAWAY_ENABLE_PROCESS_TREE };
        THROW_IF_WIN32_BOOL_FALSE(UpdateProcThreadAttribute(attributeList, 0, PROC_THREAD_ATTRIBUTE_DESKTOP_APP_POLICY, &policy, sizeof(policy), nullptr, nullptr));

        STARTUPINFOEX info{};
        info.StartupInfo.cb = sizeof(info);
        info.lpAttributeList = attributeList;

        wil::unique_process_information processInfo;
        THROW_IF_WIN32_BOOL_FALSE(CreateProcess(nullptr, cmdLine.get(), nullptr, nullptr, FALSE, EXTENDED_STARTUPINFO_PRESENT, nullptr, nullptr, &info.StartupInfo, &processInfo));

        // This API is designed to only return to the caller on failure, otherwise block until process termination.
        // Wait for the agent to exit.  If the agent succeeds, it will terminate this process.  If the agent fails,
        // it can exit or crash.  This API will be able to detect the failure and return.
        wil::handle_wait(processInfo.hProcess);

        DWORD processExitCode{};
        THROW_IF_WIN32_BOOL_FALSE_MSG(GetExitCodeProcess(processInfo.hProcess, &processExitCode), "CmdLine: %ls, processExitCode: %u", cmdLine.get(), processExitCode);
        RETURN_IF_FAILED_MSG(HRESULT_FROM_WIN32(processExitCode), "DeploymentAgent exitcode:0x%X", processExitCode);
        return S_OK;
    }
    CATCH_RETURN()
}