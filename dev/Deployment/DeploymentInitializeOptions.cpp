// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#include <pch.h>
#include <DeploymentInitializeOptions.h>
#include <Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentInitializeOptions.g.cpp>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    bool DeploymentInitializeOptions::ForceDeployment()
    {
        return m_ForceDeployment;
    }
    void DeploymentInitializeOptions::ForceDeployment(bool value)
    {
        m_ForceDeployment = value;
    }
    bool DeploymentInitializeOptions::OnErrorShowUI()
    {
        return m_OnErrorShowUI;
    }
    void DeploymentInitializeOptions::OnErrorShowUI(bool value)
    {
        m_OnErrorShowUI = value;
    }
}
