// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include <DeploymentResult.h>
#include <Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentResult.g.cpp>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    DeploymentResult::DeploymentResult(winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentStatus const& status, winrt::hresult const& extendedError) :
        m_status(status),
        m_extendedError(extendedError)
    {
    }
    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentStatus DeploymentResult::Status()
    {
        return m_status;
    }
    winrt::hresult DeploymentResult::ExtendedError()
    {
        return m_extendedError;
    }
}
