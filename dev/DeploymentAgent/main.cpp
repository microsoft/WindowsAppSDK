// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "tracelogging.h"

using namespace winrt::Windows::Foundation;

// argv[1] tells whether to use AddPackageAsync (argv[1] == "0") or RegisterPackageAsync (argv[1] == "1") on the path passed in argv[2].
int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int) try
{
    int argc{};
    const std::wstring cmdLine{ GetCommandLineW() };
    const wil::unique_hlocal_ptr<PWSTR[]> argv{ CommandLineToArgvW(cmdLine.c_str(), &argc) };

    if (argc <= 1)
    {
        WindowsAppRuntimeDeploymentAgent_TraceLogger::FailedDueToBadArguments(argc);
        return HRESULT_FROM_WIN32(ERROR_BAD_ARGUMENTS);
    }

    bool useExistingPackageIfHigherVersion{};
    if (argc >= 2)
    {
        if (CompareStringOrdinal(argv[1], -1, L"1", -1, TRUE) == CSTR_EQUAL)
        {
            useExistingPackageIfHigherVersion = true;
        }
    }

    bool forceDeployment{};
    if (argc >= 4)
    {
        if (CompareStringOrdinal(argv[3], -1, L"1", -1, TRUE) == CSTR_EQUAL)
        {
            forceDeployment = true;
        }
    }

    GUID callerActivityId{};
    if (argc >= 5)
    {
        // Best effort for telemetry purpose and a failure doesn't affect functionality.
        std::ignore = CLSIDFromString(argv[4], &callerActivityId);
    }

    winrt::Windows::Management::Deployment::PackageManager packageManager;

    const auto options{ forceDeployment ?
            winrt::Windows::Management::Deployment::DeploymentOptions::ForceTargetApplicationShutdown :
            winrt::Windows::Management::Deployment::DeploymentOptions::None };

    winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Windows::Management::Deployment::DeploymentResult,
        winrt::Windows::Management::Deployment::DeploymentProgress> deploymentOperation;
    const auto pathUri{ winrt::Windows::Foundation::Uri(argv[2]) };
    if (useExistingPackageIfHigherVersion)
    {
        deploymentOperation = packageManager.RegisterPackageAsync(pathUri, nullptr, options);    }
    else
    {
        deploymentOperation = packageManager.AddPackageAsync(pathUri, nullptr, options);
    }

    deploymentOperation.get();
    const auto deploymentResult{ deploymentOperation.GetResults() };
    if (deploymentOperation.Status() != AsyncStatus::Completed)
    {
        HRESULT deploymentOperationHResult = static_cast<HRESULT>(deploymentOperation.ErrorCode());
        HRESULT deploymentOperationExtendedHResult = static_cast<HRESULT>(deploymentResult.ExtendedErrorCode());
        if (FAILED(deploymentOperationHResult))
        {
            WindowsAppRuntimeDeploymentAgent_TraceLogger::FailedInDeployment(
                deploymentOperationHResult,
                argv[1],
                argv[2],
                forceDeployment,
                callerActivityId,
                deploymentOperationExtendedHResult,
                deploymentResult.ErrorText().c_str(),
                deploymentResult.ActivityId());
        }
        return static_cast<int>(FAILED(deploymentOperationExtendedHResult) ? deploymentOperationExtendedHResult : deploymentOperationHResult);
    }

    WindowsAppRuntimeDeploymentAgent_TraceLogger::Success(
        argv[1],
        argv[2],
        forceDeployment,
        callerActivityId);
    return S_OK;
}
CATCH_RETURN()
