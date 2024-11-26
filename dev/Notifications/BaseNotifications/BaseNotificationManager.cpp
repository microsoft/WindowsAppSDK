// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "BaseNotificationManager.h"
#include "BaseNotification.h"
#include <winrt/Windows.Storage.h>
#include <winrt/base.h>
#include "externs.h"
#include "AppNotificationUtility.h"
#include "NotificationProperties.h"
#include "NotificationTransientProperties.h"
#include <frameworkudk/toastnotifications.h>
//#include <frameworkudk/wnpnotifications.h>
#include <FrameworkUdk/toastnotificationsrt.h>
#include <algorithm>
#include <winerror.h>

using namespace Microsoft::Windows::AppNotifications::Helpers;
using namespace Microsoft::Windows::AppNotifications::ShellLocalization;

namespace Microsoft::Windows::BaseNotifications {
    BaseNotificationManager::BaseNotificationManager() : m_processName(GetCurrentProcessPath()), m_appId(RetrieveNotificationAppId()) {};

    void BaseNotificationManager::Show(BaseNotification& notification)
    {
        /*if (!IsSupported())
        {
            return;
        }

        auto logTelemetry{ AppNotificationTelemetry::Show::Start(
            g_telemetryHelper,
            m_appId,
            notification.Payload(),
            notification.Tag(),
            notification.Group()) }; */

        THROW_HR_IF(WPN_E_NOTIFICATION_POSTED, notification.Id() != 0);

        winrt::com_ptr<::ABI::Microsoft::Internal::ToastNotifications::INotificationProperties> notificationProperties = winrt::make_self<NotificationProperties>(notification);

        winrt::com_ptr<::ABI::Microsoft::Internal::ToastNotifications::INotificationTransientProperties> notificationTransientProperties = winrt::make_self<NotificationTransientProperties>(notification);

        DWORD notificationId = 0;
        THROW_IF_FAILED(ToastNotifications_PostToast(m_appId.c_str(), notificationProperties.get(), notificationTransientProperties.get(), &notificationId));

        THROW_HR_IF(E_UNEXPECTED, notificationId == 0);

        /*implementation::AppNotification* notificationImpl = get_self<implementation::AppNotification>(notification);
        notificationImpl->SetNotificationId(notificationId);*/
        notification.Id(notificationId);

        /*logTelemetry.Stop();*/
    }

    void BaseNotificationManager::RemoveAllNotification(ABI::Microsoft::Internal::ToastNotifications::NotificationType notificationType)
    {
        /*if (!IsSupported())
        {
            co_return;
        }

        auto strong = get_strong();
        co_await winrt::resume_background();

        auto logTelemetry{ AppNotificationTelemetry::RemoveAllAsync::Start(g_telemetryHelper, m_appId) };*/

        //THROW_IF_FAILED(WnpNotifications_RemoveAllNotificationsForAppOfType(m_appId.c_str(), notificationType));

        /*logTelemetry.Stop();*/
    }
}
