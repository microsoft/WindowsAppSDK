// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// NOTE: Localization logic is intentionally separated from PickerCommon.cpp to avoid
// MRT Core dependencies in unit tests. Once unit tests are refactored to use component
// packages instead of mocked packages, this can be moved into CaptureParameters method.

#include "pch.h"
#include "PickerLocalization.h"
#include <winrt\base.h>
#include <winrt\Microsoft.Windows.ApplicationModel.Resources.h>

namespace PickerLocalization {
    static PCWSTR c_WindowsAppRuntimeLocalizationPRIFilename{ L"Microsoft.WindowsAppRuntime.pri" };
    std::wstring GetPriFilePath()
    {
        wil::unique_hmodule module;
        THROW_IF_WIN32_BOOL_FALSE(GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, reinterpret_cast<PCWSTR>(PickerLocalization::GetPriFilePath), &module));
        std::filesystem::path modulePath{ wil::GetModuleFileNameW<std::wstring>(module.get()) };
        return modulePath.parent_path() / c_WindowsAppRuntimeLocalizationPRIFilename;
    }

    winrt::hstring GetStoragePickersLocalizationText(winrt::hstring key)
    {
        static winrt::hstring priPath{ GetPriFilePath() };
        auto manager = winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceManager(priPath);
        return manager.MainResourceMap().GetValue(key).ValueAsString();
    }
}

