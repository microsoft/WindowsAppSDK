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
#include "BaseNotification.h"
#include "BaseNotificationManager.h"
#include "BadgeNotification.h"

using namespace std::literals;

namespace winrt
{
    using namespace winrt::Windows::UI;
    using namespace winrt::Windows::Foundation;
    using namespace winrt::Windows::Foundation::Collections;
    using namespace winrt::Microsoft::Windows::AppNotifications;
    using namespace Windows::ApplicationModel::Core;
    using namespace winrt::Microsoft::Windows::BadgeNotifications;
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

namespace BaseNotifications
{
    using namespace ::Microsoft::Windows::BaseNotifications;
}

namespace winrt::Microsoft::Windows::BadgeNotifications::implementation
{
//    BadgeNotificationManager::BadgeNotificationManager() : m_processName(GetCurrentProcessPath()), m_appId(RetrieveNotificationAppId()) {}
    BadgeNotificationManager::BadgeNotificationManager() : BaseNotifications::BaseNotificationManager() {}

    winrt::Microsoft::Windows::BadgeNotifications::BadgeNotificationManager BadgeNotificationManager::Current()
    {
        auto appProperties{ winrt::CoreApplication::Properties() };

        static wil::srwlock lock;

        auto criticalSection{ lock.lock_exclusive() };
        auto storedBadgeNotificationManager{ appProperties.TryLookup(STORED_BADGENOTIFICATION_MANAGER_KEY) };
        if (storedBadgeNotificationManager)
        {
            return storedBadgeNotificationManager.as<winrt::Microsoft::Windows::BadgeNotifications::BadgeNotificationManager>();
        }
        else
        {
            // Need to clear the RoActivateInstance caching for the PushNotificationLongRunningProcess proxyStub to be found.
            ::Microsoft::RoApi::ClearRoActivateInstanceCache();

            // Store the BadgeNotificationManager in the COM static store
            auto badgeNotificationManager{ winrt::make<BadgeNotificationManager>() };
            appProperties.Insert(STORED_BADGENOTIFICATION_MANAGER_KEY, badgeNotificationManager);
            return badgeNotificationManager;
        }
    }

    void BadgeNotificationManager::SetBadgeAsCount(uint32_t notificationCount)
    {
        std::wstring notificationCountString = std::to_wstring(notificationCount);
        auto xmlResult{ wil::str_printf<std::wstring>(L"<badge value='%ls'>",
            notificationCountString.c_str()) };
        ::Microsoft::Windows::BadgeNotifications::BadgeNotification badgeNotifications (xmlResult.c_str());
        BaseNotifications::BaseNotificationManager::Show(badgeNotifications);
        return;
    }

    void BadgeNotificationManager::SetBadgeAsCount(uint32_t notificationCount, winrt::Windows::Foundation::DateTime expiration)
    {
        std::wstring notificationCountString = std::to_wstring(notificationCount);
        auto xmlResult{ wil::str_printf<std::wstring>(L"<badge value='%ls'>",
            notificationCountString.c_str()) };
        ::Microsoft::Windows::BadgeNotifications::BadgeNotification badgeNotifications(xmlResult.c_str());
        badgeNotifications.Expiration(expiration);
        BaseNotifications::BaseNotificationManager::Show(badgeNotifications);
        return;
    }

    void BadgeNotificationManager::SetBadgeAsGlyph(winrt::Microsoft::Windows::BadgeNotifications::BadgeNotificationGlyph glyphValue)
    {
        PCWSTR glyphValueString;
        GetBadgeNotificationGlyphToString(glyphValue, &glyphValueString);
        auto xmlResult{ wil::str_printf<std::wstring>(L"<badge value='%ls'>",
            glyphValueString) };
        ::Microsoft::Windows::BadgeNotifications::BadgeNotification badgeNotifications(xmlResult.c_str());
        BaseNotifications::BaseNotificationManager::Show(badgeNotifications);
        return;
    }

    void BadgeNotificationManager::SetBadgeAsGlyph(winrt::Microsoft::Windows::BadgeNotifications::BadgeNotificationGlyph glyphValue, winrt::Windows::Foundation::DateTime expiration)
    {
        PCWSTR glyphValueString;
        GetBadgeNotificationGlyphToString(glyphValue, &glyphValueString);
        auto xmlResult{ wil::str_printf<std::wstring>(L"<badge value='%ls'>",
            glyphValueString) };
        ::Microsoft::Windows::BadgeNotifications::BadgeNotification badgeNotifications(xmlResult.c_str());
        badgeNotifications.Expiration(expiration);
        BaseNotifications::BaseNotificationManager::Show(badgeNotifications);
        return;
    }

    void BadgeNotificationManager::ClearBadge()
    {
        BaseNotifications::BaseNotificationManager::RemoveAllNotification();
        return;
    }

    void BadgeNotificationManager::GetBadgeNotificationGlyphToString(_In_ winrt::BadgeNotificationGlyph glyphValue, _Out_ PCWSTR* glyphString)
    {
        static const std::unordered_map<winrt::BadgeNotificationGlyph, PCWSTR> enumMapping = {
            {winrt::BadgeNotificationGlyph::None, L"none"},
            {winrt::BadgeNotificationGlyph::Activity, L"activity"},
            {winrt::BadgeNotificationGlyph::Alarm, L"alarm"},
            {winrt::BadgeNotificationGlyph::Alert, L"alert"},
            {winrt::BadgeNotificationGlyph::Attention, L"attention"},
            {winrt::BadgeNotificationGlyph::Available, L"available"},
            {winrt::BadgeNotificationGlyph::Away, L"away"},
            {winrt::BadgeNotificationGlyph::Busy, L"busy"},
            {winrt::BadgeNotificationGlyph::Error, L"error"},
            {winrt::BadgeNotificationGlyph::NewMessage, L"newMessage"},
            {winrt::BadgeNotificationGlyph::Paused, L"paused"},
            {winrt::BadgeNotificationGlyph::Playing, L"playing"},
            {winrt::BadgeNotificationGlyph::Unavailable, L"unavailable"}
        };

        *glyphString = enumMapping.at(glyphValue);
        return;
    }
}
