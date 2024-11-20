#include "pch.h"
#include "BadgeNotification.h"

using namespace Microsoft::Windows::BaseNotifications;

namespace Microsoft::Windows::BadgeNotifications {
    // Default constructor
    BadgeNotification::BadgeNotification() : BaseNotification()
    {
        //set type in base
    }

    // Constructor that takes a payload and forwards it to the base class constructor
    BadgeNotification::BadgeNotification(winrt::hstring const& payload) : BaseNotification(payload)
    {
        //set type in base
    }
}
