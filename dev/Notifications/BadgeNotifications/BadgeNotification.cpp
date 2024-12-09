// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "BadgeNotification.h"
#include <frameworkUdk/ToastNotificationsRT.h>

using namespace Microsoft::Windows::BaseNotifications;

namespace ToastABI
{
    using namespace ::ABI::Microsoft::Internal::ToastNotifications;
}

namespace Microsoft::Windows::BadgeNotifications {
    // Default constructor
    BadgeNotification::BadgeNotification() : BaseNotification()
    {
        BaseNotification::NotificationType(ToastABI::NotificationType::NotificationType_Badge);
    }

    // Constructor that takes a payload and forwards it to the base class constructor
    BadgeNotification::BadgeNotification(winrt::hstring const& payload) : BaseNotification(payload)
    {
        BaseNotification::NotificationType(ToastABI::NotificationType::NotificationType_Badge);
    }
}
