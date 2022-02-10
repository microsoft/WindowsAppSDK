// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

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

    wil::srwlock m_lock;

    winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData m_progressData;
};
