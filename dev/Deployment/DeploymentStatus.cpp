// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include <DeploymentStatus.h>
#include <Microsoft.Windows.ApplicationModel.WindowsAppSDK.DeploymentStatus.g.cpp>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK::implementation
{
    DeploymentStatus::DeploymentStatus(bool const isOK, bool const packageInstallRequired, winrt::hresult const& extendedError) :
        m_isOK(isOK),
        m_packageInstallRequired(packageInstallRequired),
        m_extendedError(extendedError)
    {
    }
}
