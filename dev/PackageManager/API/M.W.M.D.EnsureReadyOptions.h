// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.EnsureReadyOptions.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct EnsureReadyOptions : EnsureReadyOptionsT<EnsureReadyOptions>
    {
        EnsureReadyOptions() = default;

        winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions AddPackageOptions();
        bool RegisterNewerIfAvailable();
        void RegisterNewerIfAvailable(bool value);
    private:
        winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions m_addPackageOptions{};
        bool m_registerNewerIfAvailable{};
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct EnsureReadyOptions : EnsureReadyOptionsT<EnsureReadyOptions, implementation::EnsureReadyOptions>
    {
    };
}
