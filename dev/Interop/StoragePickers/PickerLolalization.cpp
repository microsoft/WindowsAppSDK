// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "PickerLocalization.h"
#include <winrt\base.h>
#include <winrt\Microsoft.Windows.ApplicationModel.Resources.h>
#include <iostream>

namespace PickerCommon {
    void UpdateAllTextLocalization(PickerCommon::PickerParameters& parameter)
    {
        winrt::hstring priPath = L"Microsoft.WindowsAppRuntime.pri";
        winrt::hstring resourceName = L"Microsoft.WindowsAppRuntime/StoragePickers/All Files";
        auto factory = winrt::get_activation_factory<winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceManager, winrt::Microsoft::Windows::ApplicationModel::Resources::IResourceManagerFactory>();
        winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceManager manager = factory.CreateInstance(priPath);
        std::cout << "test output direct compile with res" << std::endl;
        std::wcout << manager.MainResourceMap().GetValue(resourceName).ValueAsString().c_str() << std::endl;
        auto text = manager.MainResourceMap().GetValue(resourceName).ValueAsString();
        parameter.AllFilesText = text;
    }
}

