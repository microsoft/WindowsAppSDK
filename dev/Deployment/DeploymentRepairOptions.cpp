// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#include <pch.h>
#include <DeploymentRepairOptions.h>
#include <Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentRepairOptions.g.cpp>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    bool DeploymentRepairOptions::ForceDeployment()
    {
        return m_ForceDeployment;
    }
    void DeploymentRepairOptions::ForceDeployment(bool value)
    {
        m_ForceDeployment = value;
    }
    bool DeploymentRepairOptions::OnErrorShowUI()
    {
        return m_OnErrorShowUI;
    }
    void DeploymentRepairOptions::OnErrorShowUI(bool value)
    {
        m_OnErrorShowUI = value;
    }
}
