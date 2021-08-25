// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include <DeploymentManager.h>
#include <Microsoft.Windows.ApplicationModel.WindowsAppSDK.DeploymentManager.g.cpp>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK::implementation
{
    DeploymentStatus DeploymentManager::GetStatus()
    {
        DeploymentStatus status = { true, true, S_OK };
        return status;
    }

    DeploymentStatus DeploymentManager::Initialize()
    {
        return DeploymentManager::GetStatus();
    }
}
