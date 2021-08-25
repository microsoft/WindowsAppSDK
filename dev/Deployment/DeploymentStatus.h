// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <Microsoft.Windows.ApplicationModel.WindowsAppSDK.DeploymentStatus.g.h>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK::implementation
{
    struct DeploymentStatus : DeploymentStatusT<DeploymentStatus>
    {
        DeploymentStatus(bool const isOK, bool const packageInstallRequired, hresult const& extendedError);
        bool IsOK() { return m_isOK; }
        bool PackageInstallRequired() { return m_packageInstallRequired; }
        winrt::hresult ExtendedError() { return m_extendedError; }

    private:
        const bool m_isOK{ false };
        const bool m_packageInstallRequired{ false };
        const winrt::hresult m_extendedError{};
    };
}

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK::factory_implementation
{
    struct DeploymentStatus : DeploymentStatusT<DeploymentStatus, implementation::DeploymentStatus>
    {
    };
}
