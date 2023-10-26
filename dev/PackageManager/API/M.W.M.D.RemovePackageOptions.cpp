// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.M.D.RemovePackageOptions.h"
#include "Microsoft.Windows.Management.Deployment.RemovePackageOptions.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    bool RemovePackageOptions::PreserveApplicationData()
    {
        return m_preserveApplicationData;
    }
    void RemovePackageOptions::PreserveApplicationData(bool value)
    {
        m_preserveApplicationData = value;
    }
    bool RemovePackageOptions::PreserveRoamableApplicationData()
    {
        return m_preserveRoamableApplicationData;
    }
    void RemovePackageOptions::PreserveRoamableApplicationData(bool value)
    {
        m_preserveRoamableApplicationData = value;
    }
    bool RemovePackageOptions::RemoveForAllUsers()
    {
        return m_removeForAllUsers;
    }
    void RemovePackageOptions::RemoveForAllUsers(bool value)
    {
        m_removeForAllUsers = value;
    }
    winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority RemovePackageOptions::Priority()
    {
        return m_priority;
    }
    void RemovePackageOptions::Priority(winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority const& value)
    {
        m_priority = value;
    }
}
