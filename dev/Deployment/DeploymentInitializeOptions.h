// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// Copyright(c) Microsoft Corporation.All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentInitializeOptions.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    struct DeploymentInitializeOptions : DeploymentInitializeOptionsT<DeploymentInitializeOptions>
    {
        DeploymentInitializeOptions() = default;

        bool ForceDeployment();
        void ForceDeployment(bool value);

    private:
        bool m_ForceDeployment{};
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::factory_implementation
{
    struct DeploymentInitializeOptions : DeploymentInitializeOptionsT<DeploymentInitializeOptions, implementation::DeploymentInitializeOptions>
    {
    };
}
