// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "ToastNotification.h"
#include "NotificationProperties.h"
#include "ToastNotificationUtility.h"
#include "../PushNotifications/PushNotificationUtility.h"

namespace winrt
{
    using namespace winrt::Microsoft::Windows::ToastNotifications;
}

namespace Helpers
{
    using namespace winrt::Microsoft::Windows::PushNotifications::Helpers;
}

NotificationProperties::NotificationProperties(winrt::ToastNotification const& toastNotification)
{
    // Extract payload and convert it from XML to a byte array
    auto payload = toastNotification.Payload();
    auto payloadAsHstring = payload.GetXml();

    std::wstring payloadAsStdWstring{ payloadAsHstring };

    auto payloadAsSimpleString = Helpers::WideStringToUtf8String(payloadAsStdWstring);

    m_payload = wil::unique_cotaskmem_array_ptr<byte>(static_cast<byte*>(CoTaskMemAlloc(payloadAsSimpleString.size())), payloadAsSimpleString.size());
    CopyMemory(m_payload.data(), payloadAsSimpleString.c_str(), payloadAsSimpleString.size());

    m_notificationId = toastNotification.ToastId();

    m_tag = toastNotification.Tag();
    m_group = toastNotification.Group();

    auto expiry = toastNotification.ExpirationTime();
    m_expiry = winrt::clock::to_file_time(expiry);

    auto arrivalTime = winrt::clock::now();
    m_arrivalTime = winrt::clock::to_file_time(arrivalTime);

    m_expiresOnReboot = toastNotification.ExpiresOnReboot();

    // TODO: Uncomment once ToastProgressData is implemented
    // m_progressData = toastNotification.ProgressData();
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_NotificationId(_Out_ unsigned int* notificationId) noexcept
{
    auto lock = m_lock.lock_shared();

    *notificationId = m_notificationId;
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_Payload(_Out_ unsigned int* payloadSize, _Out_ byte** payload) noexcept
{
    auto lock = m_lock.lock_shared();

    size_t tempPayloadSize = m_payload.size();

    auto tempPayload = wil::unique_cotaskmem_array_ptr<byte>(static_cast<byte*>(CoTaskMemAlloc(tempPayloadSize)), tempPayloadSize);
    CopyMemory(tempPayload.data(), m_payload.get(), tempPayloadSize);

    *payloadSize = static_cast<unsigned int>(tempPayloadSize);
    *payload = tempPayload.release();
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_PayloadSize(_Out_ unsigned int* payloadSize) noexcept
{
    auto lock = m_lock.lock_shared();

    *payloadSize = static_cast<unsigned int>(m_payload.size());
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_Tag(_Out_ HSTRING* tag) noexcept
{
    auto lock = m_lock.lock_shared();

    *tag = safe_make_unique_hstring(m_tag.c_str()).release();
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_Group(_Out_ HSTRING* group) noexcept
{
    auto lock = m_lock.lock_shared();

    *group = safe_make_unique_hstring(m_group.c_str()).release();
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_Expiry(_Out_ unsigned long long* expiry) noexcept
{
    auto lock = m_lock.lock_shared();

    *expiry = static_cast<ULONGLONG>(m_expiry.dwHighDateTime) << 32 | static_cast<ULONGLONG>(m_expiry.dwLowDateTime);
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_ArrivalTime(_Out_ unsigned long long* arrivalTime) noexcept
{
    auto lock = m_lock.lock_shared();

    *arrivalTime = static_cast<ULONGLONG>(m_arrivalTime.dwHighDateTime) << 32 | static_cast<ULONGLONG>(m_arrivalTime.dwLowDateTime);
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_BootId(_Out_ unsigned long long* bootId) noexcept
{
    *bootId = 0;
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_ExpiresOnReboot(_Out_ boolean* expiresOnReboot) noexcept
{
    auto lock = m_lock.lock_shared();

    *expiresOnReboot = m_expiresOnReboot;
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_ToastProgressData(_Out_ ABI::Microsoft::Internal::ToastNotifications::IToastProgressData** /*progressData*/) noexcept
{
    // TODO: Uncomment once ToastProgressData is implemented
    // auto lock = m_lock.lock_shared();
    // *toastProgressData = m_toastProgressData.get();
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_ActivityId(_Out_ GUID* activityId) noexcept
{
    *activityId = GUID_NULL;
    return S_OK;
}
