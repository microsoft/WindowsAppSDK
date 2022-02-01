// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include <frameworkUdk/ToastNotificationsRT.h>

struct ToastProgressDataABI : winrt::implements<ToastProgressDataABI, ::ABI::Microsoft::Internal::ToastNotifications::IToastProgressData>
{
    ToastProgressDataABI(winrt::Microsoft::Windows::ToastNotifications::ToastProgressData const& progressData);

    STDMETHOD(get_SequenceNumber)(_Out_ unsigned int* value);

    STDMETHOD(get_Title)(_Out_ HSTRING* value);

    STDMETHOD(get_Value)(_Out_ double* value);

    STDMETHOD(get_ValueStringOverride)(_Out_ HSTRING* value);

    STDMETHOD(get_Status)(_Out_ HSTRING* value);

private:

    wil::srwlock m_lock;

    winrt::Microsoft::Windows::ToastNotifications::ToastProgressData m_progressData;        
};
