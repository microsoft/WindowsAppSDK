// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "AppNotificationDevicesData.h"
#include "NotificationDevicesData.h"
#include "AppNotificationUtility.h"

using namespace Microsoft::Windows::AppNotifications::Helpers;

NotificationDevicesData::NotificationDevicesData(winrt::AppNotificationDevicesData const& devicesData)
    : m_devicesData(devicesData)
{
}

STDMETHODIMP NotificationDevicesData::get_CameraDeviceId(_Out_ HSTRING* value) noexcept try
{
    *value = safe_make_unique_hstring(m_devicesData.CameraDeviceId().c_str()).release();
    return S_OK;
}
CATCH_RETURN()

STDMETHODIMP NotificationDevicesData::get_MicrophoneDeviceId(_Out_ HSTRING* value) noexcept try
{
    *value = safe_make_unique_hstring(m_devicesData.MicrophoneDeviceId().c_str()).release();
    return S_OK;
}
CATCH_RETURN() 


STDMETHODIMP NotificationDevicesData::get_SpeakerDeviceId(_Out_ HSTRING* value) noexcept try
{
    *value = safe_make_unique_hstring(m_devicesData.SpeakerDeviceId().c_str()).release();
    return S_OK;
}
CATCH_RETURN()




