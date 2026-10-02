// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityOptions.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    struct RuntimeCompatibilityOptions : RuntimeCompatibilityOptionsT<RuntimeCompatibilityOptions>
    {
        RuntimeCompatibilityOptions() = default;

        WindowsAppRuntimeVersion PatchLevel1() { return m_patchLevel1; }
        void PatchLevel1(WindowsAppRuntimeVersion const& value) { m_patchLevel1 = value; }
        WindowsAppRuntimeVersion PatchLevel2() { return m_patchLevel2; }
        void PatchLevel2(WindowsAppRuntimeVersion const& value) { m_patchLevel2 = value; }
        winrt::Windows::Foundation::Collections::IVector<RuntimeCompatibilityChange> DisabledChanges();

        void Apply();

    private:
        WindowsAppRuntimeVersion m_patchLevel1{ 0, 0, 0 };
        WindowsAppRuntimeVersion m_patchLevel2{ 0, 0, 0 };
        winrt::Windows::Foundation::Collections::IVector<RuntimeCompatibilityChange> m_disabledChanges{ winrt::single_threaded_vector<RuntimeCompatibilityChange>() };
    };
}

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::factory_implementation
{
    struct RuntimeCompatibilityOptions : RuntimeCompatibilityOptionsT<RuntimeCompatibilityOptions, implementation::RuntimeCompatibilityOptions>
    {
    };
}
