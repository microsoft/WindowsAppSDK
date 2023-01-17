// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "Microsoft.Kozani.Settings.SettingsManager.g.h"

namespace winrt::Microsoft::Kozani::Settings::implementation
{
    struct SettingsManager : SettingsManagerT<SettingsManager>
    {
        SettingsManager() = default;

        static winrt::Microsoft::Kozani::Settings::SettingsManager Open();
        void TODO_ReplaceMeWithRealContent();
    };
}
namespace winrt::Microsoft::Kozani::Settings::factory_implementation
{
    struct SettingsManager : SettingsManagerT<SettingsManager, implementation::SettingsManager>
    {
    };
}
