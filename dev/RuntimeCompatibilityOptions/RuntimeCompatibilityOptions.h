// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.WindowsAppRuntime.CompatibilityOptions.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    struct CompatibilityOptions : CompatibilityOptionsT<CompatibilityOptions>
    {
        CompatibilityOptions() = default;

        WindowsAppRuntimeVersion PatchMode1() { return m_patchMode1; }
        void PatchMode1(WindowsAppRuntimeVersion const& value) { m_patchMode1 = value; }
        WindowsAppRuntimeVersion PatchMode2() { return m_patchMode2; }
        void PatchMode2(WindowsAppRuntimeVersion const& value) { m_patchMode2 = value; }
        winrt::Windows::Foundation::Collections::IVector<CompatibilityChange> DisabledChanges();

        void Apply();

    private:
        WindowsAppRuntimeVersion m_patchMode1{ 0, 0, 0 };
        WindowsAppRuntimeVersion m_patchMode2{ 0, 0, 0 };
        winrt::Windows::Foundation::Collections::IVector<CompatibilityChange> m_disabledChanges{ winrt::single_threaded_vector<CompatibilityChange>() };
    };
}

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::factory_implementation
{
    struct CompatibilityOptions : CompatibilityOptionsT<CompatibilityOptions, implementation::CompatibilityOptions>
    {
    };
}
