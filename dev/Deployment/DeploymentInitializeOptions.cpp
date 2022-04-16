// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
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
}
