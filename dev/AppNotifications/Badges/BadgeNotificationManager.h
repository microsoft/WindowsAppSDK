// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include <Microsoft.Windows.AppNotifications.Badges.BadgeNotificationManager.g.h>

namespace winrt::Microsoft::Windows::AppNotifications::Badges::implementation
{
    struct BadgeNotificationManager
    {
        struct BadgeNotificationManager() = default;

        static void PostValue(uint32_t value);

        static void PostGlyph(winrt::Microsoft::Windows::AppNotifications::Badges::BadgeNotificationGlyph glyph);

        static void PostCustomBadge(winrt::Windows::Foundation::Uri const& customBadgeUri);

        static void Clear();
    };
}

namespace winrt::Microsoft::Windows::AppNotifications::Badges::factory_implementation
{
    struct BadgeNotificationManager : BadgeNotificationManagerT<BadgeNotificationManager,
        implementation::BadgeNotificationManager>
    {
    };
}
