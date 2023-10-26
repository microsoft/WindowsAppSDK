// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.RemovePackageOptions.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct RemovePackageOptions : RemovePackageOptionsT<RemovePackageOptions>
    {
        RemovePackageOptions() = default;

        bool PreserveApplicationData();
        void PreserveApplicationData(bool value);
        bool PreserveRoamableApplicationData();
        void PreserveRoamableApplicationData(bool value);
        bool RemoveForAllUsers();
        void RemoveForAllUsers(bool value);
        winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority Priority();
        void Priority(winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority const& value);

    private:
        bool m_preserveApplicationData{};
        bool m_preserveRoamableApplicationData{};
        bool m_removeForAllUsers{};
        winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority m_priority{ winrt::Microsoft::Windows::Management::Deployment::DeploymentPriority::Normal };
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct RemovePackageOptions : RemovePackageOptionsT<RemovePackageOptions, implementation::RemovePackageOptions>
    {
    };
}
