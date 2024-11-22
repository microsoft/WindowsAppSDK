// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "AppNotificationConferencingConfig.h"
#include "NotificationConferencingConfig.h"
#include "AppNotificationUtility.h"

using namespace Microsoft::Windows::AppNotifications::Helpers;

NotificationConferencingConfig::NotificationConferencingConfig(winrt::AppNotificationConferencingConfig const& conferencingConfig)
    : m_conferencingConfig(conferencingConfig)
{
}

STDMETHODIMP NotificationConferencingConfig::get_VideoDeviceId(_Out_ HSTRING* value) noexcept try
{
    winrt::copy_to_abi(m_conferencingConfig.VideoDeviceId(), reinterpret_cast<void*&>(value));
    return S_OK;
}
CATCH_RETURN()

STDMETHODIMP NotificationConferencingConfig::get_AudioInputDeviceId(_Out_ HSTRING* value) noexcept try
{
    winrt::copy_to_abi(m_conferencingConfig.AudioInputDeviceId(), reinterpret_cast<void*&>(value));
    return S_OK;
}
CATCH_RETURN() 


STDMETHODIMP NotificationConferencingConfig::get_AudioOutputDeviceId(_Out_ HSTRING* value) noexcept try
{
    winrt::copy_to_abi(m_conferencingConfig.AudioOutputDeviceId(), reinterpret_cast<void*&>(value));
    return S_OK;
}
CATCH_RETURN()




