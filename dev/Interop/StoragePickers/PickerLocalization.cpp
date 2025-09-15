// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// NOTE: Localization logic is intentionally separated from PickerCommon.cpp to avoid
// MRT Core dependencies in unit tests. Once unit tests are refactored to use component
// packages instead of mocked packages, this can be moved into CaptureParameters method.

#include "pch.h"
#include "PickerLocalization.h"
#include <wil/stl.h>
#include <wil/win32_helpers.h>
#include <winrt\base.h>
#include <winrt\Microsoft.Windows.ApplicationModel.Resources.h>

namespace PickerLocalization {
    static PCWSTR c_WindowsAppRuntimeLocalizationPRIFilename{ L"Microsoft.WindowsAppRuntime.pri" };
    std::wstring GetPriFilePath()
    {
        std::filesystem::path modulePath{ wil::GetModuleFileNameW<std::wstring>(wil::GetModuleInstanceHandle()) };
        return modulePath.parent_path() / c_WindowsAppRuntimeLocalizationPRIFilename;
    }

    winrt::hstring GetStoragePickersLocalizationText(winrt::hstring key)
    {
        static winrt::hstring priPath{ GetPriFilePath() };
        auto manager = winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceManager(priPath);
        return manager.MainResourceMap().GetValue(key).ValueAsString();
    }
}
