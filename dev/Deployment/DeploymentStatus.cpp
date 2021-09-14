// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include <DeploymentStatus.h>
#include <Microsoft.Windows.ApplicationModel.WindowsAppSDK.DeploymentStatus.g.cpp>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK::implementation
{
    DeploymentStatus::DeploymentStatus(bool isOK, bool packageInstallRequired, winrt::hresult const& extendedError) :
        m_isOK(isOK),
        m_packageInstallRequired(packageInstallRequired),
        m_extendedError(extendedError)
    {
    }
    bool DeploymentStatus::IsOK()
    {
        return m_isOK;
    }
    bool DeploymentStatus::PackageInstallRequired()
    {
        return m_packageInstallRequired;
    }
    winrt::hresult DeploymentStatus::ExtendedError()
    {
        return m_extendedError;
    }
}
