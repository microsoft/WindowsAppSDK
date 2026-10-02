// Copyright (c) Microsoft Corporation and Contributors.
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
        bool OnErrorShowUI();
        void OnErrorShowUI(bool value);

    private:
        bool m_ForceDeployment{};
        bool m_OnErrorShowUI{};
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::factory_implementation
{
    struct DeploymentInitializeOptions : DeploymentInitializeOptionsT<DeploymentInitializeOptions, implementation::DeploymentInitializeOptions>
    {
    };
}
