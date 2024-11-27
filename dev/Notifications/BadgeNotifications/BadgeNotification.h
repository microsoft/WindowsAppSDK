// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <wil/resource.h>
#include "BaseNotification.h"


namespace Microsoft::Windows::BadgeNotifications
{
    struct BadgeNotification : Microsoft::Windows::BaseNotifications::BaseNotification
    {
        BadgeNotification();
        BadgeNotification(winrt::hstring const& payload);
    };
}
