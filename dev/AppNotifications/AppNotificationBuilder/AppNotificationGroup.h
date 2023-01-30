// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationGroup.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct AppNotificationGroup : AppNotificationGroupT<AppNotificationGroup, winrt::Windows::Foundation::IStringable>
    {
        AppNotificationGroup() = default;

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationGroup AddSubgroup(AppNotificationSubgroup value);

        // IStringable
        winrt::hstring ToString();

    private:
        std::wstring GetSubgroups();

        std::vector<AppNotificationSubgroup> m_subgroupList{};
    };
}

namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct AppNotificationGroup : AppNotificationGroupT<AppNotificationGroup, implementation::AppNotificationGroup>
    {
    };
}
