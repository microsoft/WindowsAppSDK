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

namespace PickerCommon {
    const winrt::hstring priPath = L"Microsoft.WindowsAppRuntime.pri";
    const winrt::hstring resourceName = L"Microsoft.WindowsAppRuntime/StoragePickers/All Files";
    void UpdateAllTextLocalization(PickerCommon::PickerParameters& parameter)
    {
        winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceManager manager = winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceManager(priPath);
        auto text = manager.MainResourceMap().GetValue(resourceName).ValueAsString();
        parameter.AllFilesText = text;
    }
}

