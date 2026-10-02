// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "BadgeNotificationManager.h"
#include "Microsoft.Windows.BadgeNotifications.BadgeNotificationManager.g.cpp"
#include "externs.h"
#include "AppNotificationUtility.h"
#include "NotificationProperties.h"
#include "NotificationTransientProperties.h"
#include <frameworkudk/toastnotifications.h>
#include <FrameworkUdk/toastnotificationsrt.h>
#include <frameworkudk/wnpnotifications.h>
#include <Microsoft.RoApi.h>
#include "BadgeNotification.h"
#include "BadgeNotificationTelemetry.h"

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

using namespace Microsoft::Windows::AppNotifications::Helpers;
using namespace Microsoft::Windows::AppNotifications::ShellLocalization;


namespace winrt::Microsoft::Windows::BadgeNotifications::implementation
{
    BadgeNotificationManager::BadgeNotificationManager() : m_processName(GetCurrentProcessPath()), m_appId(RetrieveNotificationAppId()) {}

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
        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, !AppModel::Identity::IsPackagedProcess(), "Not applicable for unpackaged applications");

        auto logTelemetry{ BadgeNotificationTelemetry::SetBadgeAsCount::Start(
            g_telemetryHelper,
            m_appId) };

        SetBadge(std::to_wstring(notificationCount), nullptr);

        logTelemetry.Stop();

        return;
    }

    void BadgeNotificationManager::SetBadgeAsCount(uint32_t notificationCount, winrt::DateTime expiration)
    {
        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, !AppModel::Identity::IsPackagedProcess(), "Not applicable for unpackaged applications");

        auto logTelemetry{ BadgeNotificationTelemetry::SetBadgeAsCountWithExpiration::Start(
            g_telemetryHelper,
            m_appId) };

        SetBadge(std::to_wstring(notificationCount), &expiration);

        logTelemetry.Stop();

        return;
    }

    void BadgeNotificationManager::SetBadgeAsGlyph(winrt::BadgeNotificationGlyph glyphValue)
    {
        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, !AppModel::Identity::IsPackagedProcess(), "Not applicable for unpackaged applications");

        auto logTelemetry{ BadgeNotificationTelemetry::SetBadgeAsGlyph::Start(
            g_telemetryHelper,
            m_appId) };

        std::wstring glyphValueString = GetBadgeNotificationGlyphToString(glyphValue);

        THROW_HR_IF_MSG(E_INVALIDARG, glyphValueString.empty(), "Invalid Glyph value");

        SetBadge(glyphValueString, nullptr);

        logTelemetry.Stop();

        return;
    }

    void BadgeNotificationManager::SetBadgeAsGlyph(winrt::BadgeNotificationGlyph glyphValue, winrt::DateTime expiration)
    {
        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, !AppModel::Identity::IsPackagedProcess(), "Not applicable for unpackaged applications");

        auto logTelemetry{ BadgeNotificationTelemetry::SetBadgeAsGlyphWithExpiration::Start(
            g_telemetryHelper,
            m_appId) };

        std::wstring glyphValueString = GetBadgeNotificationGlyphToString(glyphValue);

        THROW_HR_IF_MSG(E_INVALIDARG, glyphValueString.empty(), "Invalid Glyph value");

        SetBadge(glyphValueString, &expiration);

        logTelemetry.Stop();

        return;
    }

    void BadgeNotificationManager::ClearBadge()
    {
        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, !AppModel::Identity::IsPackagedProcess(), "Not applicable for unpackaged applications");

        auto logTelemetry{ BadgeNotificationTelemetry::ClearBadge::Start(
            g_telemetryHelper,
            m_appId) };

        THROW_IF_FAILED(WnpNotifications_RemoveAllNotificationsForAppOfType(m_appId.c_str(), ToastABI::NotificationType::NotificationType_Badge));

        logTelemetry.Stop();

        return;
    }

    std::wstring BadgeNotificationManager::GetBadgeNotificationGlyphToString(_In_ winrt::BadgeNotificationGlyph glyphValue)
    {
        constexpr static std::pair<winrt::BadgeNotificationGlyph, PCWSTR> enumMapping[] = {
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

        auto it = std::find_if(std::begin(enumMapping), std::end(enumMapping), [&](const auto& item)
        {
            return item.first == glyphValue;
        });

        if (it != std::end(enumMapping))
        {
            return std::wstring(it->second); // Return the string directly
        }
        else
        {
            return std::wstring(); // Return an empty string if not found
        }
    }

    void BadgeNotificationManager::SetBadge(_In_ const std::wstring& value, _In_opt_ const winrt::Windows::Foundation::DateTime* expiration)
    {
        auto xmlResult = wil::str_printf<std::wstring>(L"<badge value='%ls'/>", value.c_str());
        ::Microsoft::Windows::BadgeNotifications::BadgeNotification badgeNotification(xmlResult.c_str());

        if (expiration != nullptr)
        {
            badgeNotification.Expiration(*expiration);
        }

        THROW_HR_IF(WPN_E_NOTIFICATION_POSTED, badgeNotification.Id() != 0);

        winrt::com_ptr<::ABI::Microsoft::Internal::ToastNotifications::INotificationProperties> notificationProperties = winrt::make_self<NotificationProperties>(badgeNotification);

        winrt::com_ptr<::ABI::Microsoft::Internal::ToastNotifications::INotificationTransientProperties> notificationTransientProperties = winrt::make_self<NotificationTransientProperties>(badgeNotification);

        DWORD notificationId = 0;
        THROW_IF_FAILED(ToastNotifications_PostToast(m_appId.c_str(), notificationProperties.get(), notificationTransientProperties.get(), &notificationId));

        THROW_HR_IF(E_UNEXPECTED, notificationId == 0);

        badgeNotification.Id(notificationId);
        return;
    }
}
