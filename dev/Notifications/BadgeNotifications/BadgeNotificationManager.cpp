// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "BadgeNotificationManager.h"
#include "Microsoft.Windows.BadgeNotifications.BadgeNotificationManager.g.cpp"
#include "externs.h"
#include <frameworkudk/toastnotifications.h>
#include <FrameworkUdk/toastnotificationsrt.h>
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

namespace BaseNotifications
{
    using namespace ::Microsoft::Windows::BaseNotifications;
}

namespace winrt::Microsoft::Windows::BadgeNotifications::implementation
{
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
        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, !AppModel::Identity::IsPackagedProcess(), "Not applicable for unpackaged applications");

        SetBadge(std::to_wstring(notificationCount), nullptr);
        return;
    }

    void BadgeNotificationManager::SetBadgeAsCount(uint32_t notificationCount, winrt::DateTime expiration)
    {
        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, !AppModel::Identity::IsPackagedProcess(), "Not applicable for unpackaged applications");

        SetBadge(std::to_wstring(notificationCount), &expiration);
        return;
    }

    void BadgeNotificationManager::SetBadgeAsGlyph(winrt::BadgeNotificationGlyph glyphValue)
    {
        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, !AppModel::Identity::IsPackagedProcess(), "Not applicable for unpackaged applications");

        PCWSTR glyphValueString;
        GetBadgeNotificationGlyphToString(glyphValue, &glyphValueString);
        SetBadge(glyphValueString, nullptr);
        return;
    }

    void BadgeNotificationManager::SetBadgeAsGlyph(winrt::BadgeNotificationGlyph glyphValue, winrt::DateTime expiration)
    {
        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, !AppModel::Identity::IsPackagedProcess(), "Not applicable for unpackaged applications");

        PCWSTR glyphValueString;
        GetBadgeNotificationGlyphToString(glyphValue, &glyphValueString);
        SetBadge(glyphValueString, &expiration);
        return;
    }

    void BadgeNotificationManager::ClearBadge()
    {
        THROW_HR_IF_MSG(E_ILLEGAL_METHOD_CALL, !AppModel::Identity::IsPackagedProcess(), "Not applicable for unpackaged applications");

        auto logTelemetry{ BadgeNotificationTelemetry::ClearBadge::Start(
            g_telemetryHelper,
            m_appId) };

        BaseNotifications::BaseNotificationManager::RemoveAllNotification(ToastABI::NotificationType::NotificationType_Badge);

        logTelemetry.Stop();

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

    void BadgeNotificationManager::SetBadge(_In_ const std::wstring& value, _In_opt_ const winrt::Windows::Foundation::DateTime* expiration)
    {
        auto xmlResult = wil::str_printf<std::wstring>(L"<badge value='%ls'/>", value.c_str());
        ::Microsoft::Windows::BadgeNotifications::BadgeNotification badgeNotifications(xmlResult.c_str());

        auto logTelemetry{ BadgeNotificationTelemetry::SetBadge::Start(
            g_telemetryHelper,
            m_appId,
            badgeNotifications.Payload().c_str()) };

        if (expiration != nullptr)
        {
            badgeNotifications.Expiration(*expiration);
        }

        BaseNotifications::BaseNotificationManager::Show(badgeNotifications);

        logTelemetry.Stop();
    }
}
