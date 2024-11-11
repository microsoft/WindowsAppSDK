// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "CompatibilityOptions.h"
#include "Microsoft.Windows.ApplicationModel.WindowsAppRuntime.CompatibilityOptions.g.cpp"

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    winrt::Windows::Foundation::Collections::IVector<WindowsAppRuntimeVersion> CompatibilityOptions::PatchModes()
    {
        return m_patchModes;
    }
    winrt::Windows::Foundation::Collections::IVector<uint64_t> CompatibilityOptions::DisabledFixesList()
    {
        return m_disabledFixesList;
    }
    void CompatibilityOptions::Apply()
    {
        throw hresult_not_implemented();
    }
}
