// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

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

