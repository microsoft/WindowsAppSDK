// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.RemovePackageOptions.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct RemovePackageOptions : RemovePackageOptionsT<RemovePackageOptions>
    {
        RemovePackageOptions() = default;

        bool FailIfNotFound();
        void FailIfNotFound(bool value);
        bool PreserveApplicationData();
        void PreserveApplicationData(bool value);
        bool PreserveRoamableApplicationData();
        void PreserveRoamableApplicationData(bool value);
        bool RemoveForAllUsers();
        void RemoveForAllUsers(bool value);

    private:
        bool m_failIfNotFound{};
        bool m_preserveApplicationData{};
        bool m_preserveRoamableApplicationData{};
        bool m_removeForAllUsers{};
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct RemovePackageOptions : RemovePackageOptionsT<RemovePackageOptions, implementation::RemovePackageOptions>
    {
    };
}
