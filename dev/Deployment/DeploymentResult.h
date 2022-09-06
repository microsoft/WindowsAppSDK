// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentResult.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    struct DeploymentResult : DeploymentResultT<DeploymentResult>
    {
        DeploymentResult() = default;

        DeploymentResult(WindowsAppRuntime::DeploymentStatus const& status, winrt::hresult const& extendedError);
        winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentStatus Status();
        winrt::hresult ExtendedError();

    private:
        const WindowsAppRuntime::DeploymentStatus m_status{WindowsAppRuntime::DeploymentStatus::Unknown};
        const winrt::hresult m_extendedError{};
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::factory_implementation
{
    struct DeploymentResult : DeploymentResultT<DeploymentResult, implementation::DeploymentResult>
    {
    };
}
