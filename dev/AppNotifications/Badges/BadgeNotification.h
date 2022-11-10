// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include <Microsoft.Windows.AppNotifications.Badges.BadgeNotification.g.h>

namespace winrt::Microsoft::Windows::AppNotifications::Badges::implementation
{
    struct BadgeNotification
    {
        BadgeNotification(uint32_t value);
        BadgeNotification(winrt::Microsoft::Windows::AppNotifications::Badges::BadgeNotificationGlyph glyph);
    };
}

namespace winrt::Microsoft::Windows::AppNotifications::Badges::factory_implementation
{
    struct BadgeNotification : BadgeNotificationT<BadgeNotification,
        implementation::BadgeNotification>
    {
    };
}
