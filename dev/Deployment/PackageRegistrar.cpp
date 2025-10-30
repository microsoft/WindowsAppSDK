// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>
#include <filesystem>
#include <wil/result.h>
#include <wil/resource.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Management.Deployment.h>
#include "PackageRegistrar.h"
#include "DeploymentActivityContext.h"

namespace WindowsAppRuntime::Deployment::PackageRegistrar
{
    // If useExistingPackageIfHigherVersion == false, Adds the current version package at the passed in path using PackageManager.
    // If useExistingPackageIfHigherVersion == true, Registers the higher version package using the passed in path as manifest path and PackageManager.
    // This requires the 'packageManagement' or 'runFullTrust' capabilities.
    HRESULT AddOrRegisterPackage(
        const std::filesystem::path& path,
        const bool useExistingPackageIfHigherVersion,
        const bool forceDeployment,
        winrt::Windows::Management::Deployment::IPackageManager& packageManager,
        ::WindowsAppRuntime::Deployment::Activity::Context& activityContext) try
    {
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
        HRESULT hrError{};
        HRESULT hrExtendedError{};

        if (deploymentOperation.Status() != winrt::Windows::Foundation::AsyncStatus::Completed)
        {
            hrError = static_cast<HRESULT>(deploymentOperation.ErrorCode());
            hrExtendedError = deploymentResult.ExtendedErrorCode();

            activityContext.SetDeploymentErrorInfo(
                hrExtendedError,
                deploymentResult.ErrorText().c_str(),
                deploymentResult.ActivityId());
        }

        // If hrError indicates success, take that, ignore hrExtendedError.
        // Otherwise, return hrExtendedError if there is an error in it, if not, return hrError.
        return (FAILED(hrError) && FAILED(hrExtendedError) ? hrExtendedError : hrError);
    }
    CATCH_RETURN()

    std::wstring GenerateDeploymentAgentPath()
    {
        // Calculate the path to the restart agent as being in the same directory as the current module.
        wil::unique_hmodule module;
        THROW_IF_WIN32_BOOL_FALSE(GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, reinterpret_cast<PCWSTR>(PackageRegistrar::GenerateDeploymentAgentPath), &module));

        std::filesystem::path modulePath{ wil::GetModuleFileNameW<std::wstring>(module.get()) };
        return modulePath.parent_path() / c_deploymentAgentFilename;
    }

    /// @warning This function is ONLY for processes with package identity. It's the caller's responsibility to ensure this.
    HRESULT AddOrRegisterPackageInBreakAwayProcess(
        const std::filesystem::path& path,
        const bool useExistingPackageIfHigherVersion,
        const bool forceDeployment,
        ::WindowsAppRuntime::Deployment::Activity::Context& activityContext,
        const std::wstring& deploymentAgentPath) try
    {
        auto exePath{ deploymentAgentPath };
        auto activityId{ winrt::to_hstring(*activityContext.GetActivity().Id()) };

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
