// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "NotificationsLongRunningProcess_h.h"
#include <wil/resource.h>

namespace NotificationPlatform
{
    inline wil::com_ptr<INotificationsLongRunningPlatform> GetNotificationPlatform()
    {
        // If supported, allow use of class registrations from less trusted sources.
        auto supportMarker{ wil::CoCreateInstanceNoThrow<ISupportAllowLowerTrustActivation>(CLSID_ActivationCapabilities) };
        if (supportMarker)
        {
            return wil::CoCreateInstance<INotificationsLongRunningPlatform>(CLSID_NotificationsLongRunningPlatform, CLSCTX_LOCAL_SERVER |
                CLSCTX_ALLOW_LOWER_TRUST_REGISTRATION);
        }
        else
        {
            // Even if we can't pass CLSCTX_ALLOW_LOWER_TRUST_REGISTRATION, we still want to attempt the activation.
            // This might fail to find the class when run elevated on a downlevel SKU, but it will work otherwise.
            return wil::CoCreateInstance<INotificationsLongRunningPlatform>(CLSID_NotificationsLongRunningPlatform, CLSCTX_LOCAL_SERVER);
        }
    }
}
