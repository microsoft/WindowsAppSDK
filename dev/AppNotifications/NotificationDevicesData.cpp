// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "AppNotificationConferencingConfig.h"
#include "NotificationDevicesData.h"
#include "AppNotificationUtility.h"

using namespace Microsoft::Windows::AppNotifications::Helpers;

NotificationDevicesData::NotificationDevicesData(winrt::AppNotificationConferencingConfig const& conferencingConfig)
    : m_devicesData(conferencingConfig)
{
}

STDMETHODIMP NotificationDevicesData::get_CameraDeviceId(_Out_ HSTRING* value) noexcept try
{
    winrt::copy_to_abi(m_devicesData.VideoDeviceId(), reinterpret_cast<void*&>(value));
    return S_OK;
}
CATCH_RETURN()

STDMETHODIMP NotificationDevicesData::get_MicrophoneDeviceId(_Out_ HSTRING* value) noexcept try
{
    winrt::copy_to_abi(m_devicesData.AudioInputDeviceId(), reinterpret_cast<void*&>(value));
    return S_OK;
}
CATCH_RETURN() 


STDMETHODIMP NotificationDevicesData::get_SpeakerDeviceId(_Out_ HSTRING* value) noexcept try
{
    winrt::copy_to_abi(m_devicesData.AudioOutputDeviceId(), reinterpret_cast<void*&>(value));
    return S_OK;
}
CATCH_RETURN()




