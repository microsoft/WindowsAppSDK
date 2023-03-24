// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentRepairOptions.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    struct DeploymentRepairOptions : DeploymentRepairOptionsT<DeploymentRepairOptions>
    {
        DeploymentRepairOptions() = default;

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
    struct DeploymentRepairOptions : DeploymentRepairOptionsT<DeploymentRepairOptions, implementation::DeploymentRepairOptions>
    {
    };
}
