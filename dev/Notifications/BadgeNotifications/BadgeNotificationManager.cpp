// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "BadgeNotificationManager.h"
#include "Microsoft.Windows.BadgeNotifications.BadgeNotificationManager.g.cpp"
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Storage.h>
#include <winrt/base.h>
#include "externs.h"
#include "PushNotificationUtility.h"
#include "AppNotificationUtility.h"
#include <frameworkudk/pushnotifications.h>
#include <frameworkudk/toastnotifications.h>
#include <FrameworkUdk/toastnotificationsrt.h>
#include "NotificationProperties.h"
#include "NotificationTransientProperties.h"
#include "AppNotification.h"
#include <NotificationProgressData.h>
#include "AppNotificationTelemetry.h"
#include <algorithm>
#include <winerror.h>
#include <string_view>
#include <winrt/Windows.Foundation.Collections.h>
#include <WindowsAppRuntime.SelfContained.h>
#include <Microsoft.RoApi.h>
#include <ShellLocalization.h>
#include <filesystem>
#include <NotificationPlatformActivation.h>

using namespace std::literals;

namespace winrt
{
    using namespace winrt::Windows::UI;
    using namespace winrt::Windows::Foundation;
    using namespace winrt::Windows::Foundation::Collections;
    using namespace winrt::Microsoft::Windows::AppNotifications;
    using namespace Windows::ApplicationModel::Core;
}

namespace ToastABI
{
    using namespace ::ABI::Microsoft::Internal::ToastNotifications;
    using namespace ::ABI::Windows::Foundation::Collections;
}

namespace PushNotificationHelpers
{
    using namespace winrt::Microsoft::Windows::PushNotifications::Helpers;
}

using namespace Microsoft::Windows::AppNotifications::Helpers;
using namespace Microsoft::Windows::AppNotifications::ShellLocalization;

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    BadgeNotificationManager::BadgeNotificationManager() : m_processName(GetCurrentProcessPath()), m_appId(RetrieveNotificationAppId()) {}

    winrt::Microsoft::Windows::BadgeNotifications::BadgeNotificationManager BadgeNotificationManager::Current()
    {
        auto appProperties{ winrt::CoreApplication::Properties() };

        static wil::srwlock lock;

        auto criticalSection{ lock.lock_exclusive() };
        auto storedBadgeNotificationManager{ appProperties.TryLookup(STORED_APPNOTIFICATION_MANAGER_KEY) };
        if (storedBadgeNotificationManager)
        {
            return storedBadgeNotificationManager.as<winrt::Microsoft::Windows::BadgeNotifications::BadgeNotificationManager>();
        }
        else
        {
            // Need to clear the RoActivateInstance caching for the PushNotificationLongRunningProcess proxyStub to be found.
            ::Microsoft::RoApi::ClearRoActivateInstanceCache();

            // Store the BadgeNotificationManager in the COM static store
            auto BadgeNotificationManager{ winrt::make<BadgeNotificationManager>() };
            appProperties.Insert(STORED_APPNOTIFICATION_MANAGER_KEY, BadgeNotificationManager);
            return BadgeNotificationManager;
        }
    }

    void SetBadgeAsCount(uint32_t notificationCount)
    {
        return;
    }

    void SetBadgeAsCount(uint32_t notificationCount, winrt::Windows::Foundation::DateTime expiration)
    {
        return;
    }

    void SetBadgeAsGlyph(winrt::Microsoft::Windows::BadgeNotifications::BadgeNotificationGlyph glyphValue)
    {
        return;
    }

    void SetBadgeAsGlyph(winrt::Microsoft::Windows::BadgeNotifications::BadgeNotificationGlyph glyphValue, winrt::Windows::Foundation::DateTime expiration)
    {
        return;
    }

    void ClearBadge()
    {
        return;
    }
}
