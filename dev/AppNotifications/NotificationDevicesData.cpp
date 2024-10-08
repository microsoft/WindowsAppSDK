// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "AppNotificationDevicesData.h"
#include "NotificationDevicesData.h"
#include "AppNotificationUtility.h"

namespace winrt
{
    using namespace winrt::Microsoft::Windows::AppNotifications;
}

namespace ToastABI
{
    using namespace ::ABI::Microsoft::Internal::ToastNotifications;
}

NotificationDevicesData::NotificationDevicesData(winrt::AppNotificationDevicesData const& devicesData)
    : m_devicesData(devicesData)
{
}

STDMETHODIMP NotificationDevicesData::get_CameraDeviceId(_Out_ HSTRING* value) noexcept try
{
    *value = Microsoft::Windows::AppNotifications::Helpers::safe_make_unique_hstring(m_devicesData.CameraDeviceId().c_str()).release();
    return S_OK;
}
CATCH_RETURN()

STDMETHODIMP NotificationDevicesData::get_MicrophoneDeviceId(_Out_ HSTRING* value) noexcept try
{
    *value = Microsoft::Windows::AppNotifications::Helpers::safe_make_unique_hstring(m_devicesData.MicrophoneDeviceId().c_str()).release();
    return S_OK;
}
CATCH_RETURN() 


STDMETHODIMP NotificationDevicesData::get_SpeakerDeviceId(_Out_ HSTRING* value) noexcept try
{
    *value = Microsoft::Windows::AppNotifications::Helpers::safe_make_unique_hstring(m_devicesData.SpeakerDeviceId().c_str()).release();
    return S_OK;
}
CATCH_RETURN()


STDMETHODIMP NotificationDevicesData::IsVideoCallingSupported(_Out_ bool* value) noexcept
{
    *value = m_devicesData.IsVideoCallingSupported();
    return S_OK;
}



