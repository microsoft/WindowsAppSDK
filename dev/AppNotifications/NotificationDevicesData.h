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

struct NotificationDevicesData : winrt::implements<NotificationDevicesData, ToastABI::IToastDevicesData>
{
    NotificationDevicesData(winrt::AppNotificationConferencingConfig const& conferencingConfig);

    STDMETHOD(get_CameraDeviceId)(_Out_ HSTRING* value) noexcept;

    STDMETHOD(get_MicrophoneDeviceId)(_Out_ HSTRING* value) noexcept;

    STDMETHOD(get_SpeakerDeviceId)(_Out_ HSTRING* value) noexcept;

private:

    winrt::AppNotificationConferencingConfig m_devicesData;
};
