// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.AppNotifications.AppNotification.g.h"
#include "BaseNotification.h"

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    class IAppNotificationInternal
    {
    public:
        virtual void SetNotificationId(uint32_t id) = 0;
    };

    struct AppNotification : AppNotificationT<AppNotification, IAppNotificationInternal>, public ::Microsoft::Windows::BaseNotifications::BaseNotification
    {
        AppNotification();

        AppNotification(hstring const& payload);
        winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData Progress();
        void Progress(winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData const& value);

        // IAppNotificationInternal
        void SetNotificationId(uint32_t id);

        winrt::Microsoft::Windows::AppNotifications::AppNotificationConferencingConfig ConferencingConfig();
        void ConferencingConfig(winrt::Microsoft::Windows::AppNotifications::AppNotificationConferencingConfig const& value);

    private:
        winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData m_progressData{ nullptr };
        winrt::Microsoft::Windows::AppNotifications::AppNotificationConferencingConfig m_conferencingConfig{ nullptr };
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::factory_implementation
{
    struct AppNotification : AppNotificationT<AppNotification, implementation::AppNotification>
    {
    };
}
