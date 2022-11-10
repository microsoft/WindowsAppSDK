// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>
#include "BadgeNotificationManager.h"

#include <Microsoft.Windows.AppNotifications.Badges.BadgeNotificationManager.g.cpp>

namespace winrt::Microsoft::Windows::AppNotifications::Badges::implementation
{
    void BadgeNotificationManager::PostValue(uint32_t) {};

    void BadgeNotificationManager::PostGlyph(winrt::Microsoft::Windows::AppNotifications::Badges::BadgeNotificationGlyph) {};

    void BadgeNotificationManager::PostCustomBadge(winrt::Windows::Foundation::Uri const&) {};

    void BadgeNotificationManager::Clear() {};
}
