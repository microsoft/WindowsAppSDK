// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <frameworkUdk/ToastNotificationsRT.h>

struct NotificationProgressData : winrt::implements<NotificationProgressData, ::ABI::Microsoft::Internal::ToastNotifications::IToastProgressData>
{
    NotificationProgressData(winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData const& progressData);

    STDMETHOD(get_SequenceNumber)(_Out_ unsigned int* value) noexcept;

    STDMETHOD(get_Title)(_Out_ HSTRING* value) noexcept;

    STDMETHOD(get_Value)(_Out_ double* value) noexcept;

    STDMETHOD(get_ValueStringOverride)(_Out_ HSTRING* value) noexcept;

    STDMETHOD(get_Status)(_Out_ HSTRING* value) noexcept;

private:

    winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData m_progressData;
};
