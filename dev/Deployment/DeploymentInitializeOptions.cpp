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
    bool DeploymentInitializeOptions::OnError_DebugBreak()
    {
        return m_OnError_DebugBreak;
    }
    void DeploymentInitializeOptions::OnError_DebugBreak(bool value)
    {
        m_OnError_DebugBreak = value;
    }
    bool DeploymentInitializeOptions::OnError_DebugBreak_IfDebuggerAttached()
    {
        return m_OnError_DebugBreak_IfDebuggerAttached;
    }
    void DeploymentInitializeOptions::OnError_DebugBreak_IfDebuggerAttached(bool value)
    {
        m_OnError_DebugBreak_IfDebuggerAttached = value;
    }
    bool DeploymentInitializeOptions::OnError_FailFast()
    {
        return m_OnError_FailFast;
    }
    void DeploymentInitializeOptions::OnError_FailFast(bool value)
    {
        m_OnError_FailFast = value;
    }
    bool DeploymentInitializeOptions::OnError_ShowUI()
    {
        return m_OnError_ShowUI;
    }
    void DeploymentInitializeOptions::OnError_ShowUI(bool value)
    {
        m_OnError_ShowUI = value;
    }
    bool DeploymentInitializeOptions::OnNoPackageIdentity_NOOP()
    {
        return m_OnNoPackageIdentity_NOOP;
    }
    void DeploymentInitializeOptions::OnNoPackageIdentity_NOOP(bool value)
    {
        m_OnNoPackageIdentity_NOOP = value;
    }
}
