// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <frameworkUdk/ToastNotificationsRT.h>

struct NotificationDevicesData : winrt::implements<NotificationDevicesData, ::ABI::Microsoft::Internal::ToastNotifications::IToastDevicesData>
{
    NotificationDevicesData(winrt::Microsoft::Windows::AppNotifications::AppNotificationDevicesData const& devicesData);

    STDMETHOD(get_CameraDeviceId)(_Out_ HSTRING* value) noexcept;

    STDMETHOD(get_MicrophoneDeviceId)(_Out_ HSTRING* value) noexcept;

    STDMETHOD(get_SpeakerDeviceId)(_Out_ HSTRING* value) noexcept;

    STDMETHOD(IsVideoCallingSupported)(_Out_ bool* value) noexcept;

private:

    winrt::Microsoft::Windows::AppNotifications::AppNotificationDevicesData m_devicesData;
};
