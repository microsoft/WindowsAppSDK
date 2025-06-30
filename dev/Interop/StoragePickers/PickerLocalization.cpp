// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// NOTE: Localization logic is intentionally separated from PickerCommon.cpp to avoid
// MRT Core dependencies in unit tests. Once unit tests are refactored to use component
// packages instead of mocked packages, this can be moved into CaptureParameters method.

#include "pch.h"
#include "PickerLocalization.h"
#include <winrt\base.h>
#include <winrt\Microsoft.Windows.ApplicationModel.Resources.h>
#include <iostream>

namespace PickerLocalization {
    const winrt::hstring priPath = L"Microsoft.WindowsAppRuntime.pri";
    winrt::hstring GetStoragePickersLocalizationText(winrt::hstring key, winrt::hstring fallback)
    {
        // adding try-catch to prevent localization error break picker experience
        try
        {
            auto manager = winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceManager(priPath);
            return manager.MainResourceMap().GetValue(key).ValueAsString();
        }
        catch (...)
        {
            StoragePickersTelemetry::StoragePickerLocalizationLookupError(key.c_str());
            return fallback;
        }
    }
}

