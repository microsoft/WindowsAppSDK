// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

using namespace winrt::Windows::Foundation;

int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    int argc{};
    const std::wstring cmdLine{ GetCommandLineW() };
    const wil::unique_hlocal_ptr<PWSTR[]> argv{ CommandLineToArgvW(cmdLine.c_str(), &argc) };

    if (argc <= 1)
    {
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
        RETURN_IF_FAILED_MSG(static_cast<HRESULT>(deploymentOperation.ErrorCode()), "%ls", packagePath.c_str());
    }

    return S_OK;
}
