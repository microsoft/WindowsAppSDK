// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <wil/resource.h>
#include "externs.h"
#include <BaseNotification.h>

namespace Microsoft::Windows::BaseNotifications {
    struct BaseNotificationManager
    {
        BaseNotificationManager();

        void Show(BaseNotification& notification);
        void RemoveAllNotification(ABI::Microsoft::Internal::ToastNotifications::NotificationType notificationType);

    protected:
        wil::srwlock m_lock;
        std::wstring m_processName;
        std::wstring m_appId;
    };
}
