// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <Microsoft.Windows.ApplicationModel.WindowsAppSDK.DeploymentManager.g.h>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK::implementation
{
    struct DeploymentManager
    {
        DeploymentManager() = default;
        static DeploymentStatus GetStatus();
        static DeploymentStatus Initialize();

    private:
    };
}

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK::factory_implementation
{
    struct DeploymentManager : DeploymentManagerT<DeploymentManager, implementation::DeploymentManager>
    {
    };
}
