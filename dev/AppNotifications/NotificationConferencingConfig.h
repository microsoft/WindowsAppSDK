// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <frameworkUdk/ToastNotificationsRT.h>

namespace winrt
{
    using namespace winrt::Microsoft::Windows::AppNotifications;
}

namespace ToastABI
{
    using namespace ::ABI::Microsoft::Internal::ToastNotifications;
}

struct NotificationConferencingConfig : winrt::implements<NotificationConferencingConfig, ToastABI::IToastConferencingConfig>
{
    NotificationConferencingConfig(winrt::AppNotificationConferencingConfig const& conferencingConfig);

    STDMETHOD(get_VideoDeviceId)(_Out_ HSTRING* value) noexcept;

    STDMETHOD(get_AudioInputDeviceId)(_Out_ HSTRING* value) noexcept;

    STDMETHOD(get_AudioOutputDeviceId)(_Out_ HSTRING* value) noexcept;

private:

    winrt::AppNotificationConferencingConfig m_conferencingConfig;
};
