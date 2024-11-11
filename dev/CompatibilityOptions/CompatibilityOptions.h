// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.WindowsAppRuntime.CompatibilityOptions.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    struct CompatibilityOptions : CompatibilityOptionsT<CompatibilityOptions>
    {
        CompatibilityOptions() = default;

        winrt::Windows::Foundation::Collections::IVector<WindowsAppRuntimeVersion> PatchModes();
        winrt::Windows::Foundation::Collections::IVector<uint64_t> DisabledFixesList();

        void Apply();

    private:
        winrt::Windows::Foundation::Collections::IVector<WindowsAppRuntimeVersion> m_patchModes{ winrt::single_threaded_vector<WindowsAppRuntimeVersion>() };
        winrt::Windows::Foundation::Collections::IVector<uint64_t> m_disabledFixesList{ winrt::single_threaded_vector<uint64_t>() };
    };
}

#if FALSE
namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::factory_implementation
{
    struct CompatibilityOptions : CompatibilityOptionsT<CompatibilityOptions, implementation::CompatibilityOptions>
    {
    };
}
#endif
