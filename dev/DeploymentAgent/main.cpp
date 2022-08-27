// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "tracelogging.h"
#include <debugapi.h>

using namespace winrt::Windows::Foundation;

int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int) try
{
    DebugBreak();
    DWORD sleepTime = 15 * 1000;
    Sleep(sleepTime);
    int argc{};
    const std::wstring cmdLine{ GetCommandLineW() };
    const wil::unique_hlocal_ptr<PWSTR[]> argv{ CommandLineToArgvW(cmdLine.c_str(), &argc) };

    if (argc <= 1)
    {
        WindowsAppRuntimeDeploymentAgent_TraceLogger::FailedDueToBadArguments(argc);
        return HRESULT_FROM_WIN32(ERROR_BAD_ARGUMENTS);
    }
    std::filesystem::path packagePath{ argv[1] };

    bool forceDeployment{};
    if (argc >= 3)
    {
        if (CompareStringOrdinal(argv[2], -1, L"1", -1, TRUE) == CSTR_EQUAL)
        {
            forceDeployment = true;
        }
    }

    GUID callerActivityId{};
    if (argc >= 4)
    {
        // Best effort for telemetry purpose and a failure doesn't affect functionality.
        std::ignore = CLSIDFromString(argv[3], &callerActivityId);
    }

    winrt::Windows::Management::Deployment::PackageManager packageManager;

    const auto options{ forceDeployment ?
            winrt::Windows::Management::Deployment::DeploymentOptions::ForceTargetApplicationShutdown :
            winrt::Windows::Management::Deployment::DeploymentOptions::None };

    const auto packagePathUri{ winrt::Windows::Foundation::Uri(packagePath.c_str()) };
    const auto deploymentOperation{ packageManager.AddPackageAsync(packagePathUri, nullptr, options) };
    deploymentOperation.get();
    const auto deploymentResult{ deploymentOperation.GetResults() };
    if (deploymentOperation.Status() != AsyncStatus::Completed)
    {
        HRESULT hr = static_cast<HRESULT>(deploymentOperation.ErrorCode());
        if (FAILED(hr))
        {
            WindowsAppRuntimeDeploymentAgent_TraceLogger::FailedInDeployment(
                hr,
                packagePath.wstring().c_str(),
                forceDeployment,
                callerActivityId,
                deploymentResult.ExtendedErrorCode(),
                deploymentResult.ErrorText().c_str(),
                deploymentResult.ActivityId());
        }
        return deploymentResult.ExtendedErrorCode();
    }

    WindowsAppRuntimeDeploymentAgent_TraceLogger::Success(
        packagePath.wstring().c_str(),
        forceDeployment,
        callerActivityId);
    return S_OK;
}
CATCH_RETURN();
