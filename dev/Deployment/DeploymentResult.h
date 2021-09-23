// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentResult.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    struct DeploymentResult : DeploymentResultT<DeploymentResult>
    {
        DeploymentResult() = default;

        DeploymentResult(winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentStatus const& status, winrt::hresult const& extendedError);
        winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentStatus Status();
        winrt::hresult ExtendedError();

    private:
        const winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentStatus m_status{winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentStatus::Unknown};
        const winrt::hresult m_extendedError{};
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::factory_implementation
{
    struct DeploymentResult : DeploymentResultT<DeploymentResult, implementation::DeploymentResult>
    {
    };
}
