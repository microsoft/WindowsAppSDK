// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <wil/resource.h>
#include "externs.h"
#include "ShellLocalization.h"
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Microsoft.Windows.AppNotifications.h>
#include <BaseNotification.h>

namespace Microsoft::Windows::BaseNotifications {
    struct BaseNotificationManager
    {
        BaseNotificationManager();

        void Show(BaseNotification const& notification);
        void RemoveAllNotification();

    protected:
        wil::srwlock m_lock;
        std::wstring m_processName;
        std::wstring m_appId;
    };
}
