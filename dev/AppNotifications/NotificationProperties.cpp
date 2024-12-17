// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "AppNotification.h"
#include "NotificationProperties.h"
#include "AppNotificationUtility.h"
#include "../PushNotifications/PushNotificationUtility.h"
#include "NotificationProgressData.h"
#include "NotificationConferencingConfig.h"
#include "AppNotificationConferencingConfig.h"

namespace winrt
{
    using namespace winrt::Microsoft::Windows::AppNotifications;
}

namespace ToastABI
{
    using namespace ::ABI::Microsoft::Internal::ToastNotifications;
}

namespace Helpers
{
    using namespace winrt::Microsoft::Windows::PushNotifications::Helpers;
}

NotificationProperties::NotificationProperties(winrt::AppNotification const& toastNotification)
{
    // Extract payload and convert it from XML to a byte array
    auto payloadAsSimpleString = Helpers::WideStringToPayloadUtf8String(toastNotification.Payload());

    m_payload = wil::unique_cotaskmem_array_ptr<byte>(static_cast<byte*>(CoTaskMemAlloc(payloadAsSimpleString.size())), payloadAsSimpleString.size());
    THROW_IF_NULL_ALLOC(m_payload.get());
    CopyMemory(m_payload.data(), payloadAsSimpleString.c_str(), payloadAsSimpleString.size());

    m_notificationId = toastNotification.Id();

    m_tag = toastNotification.Tag();
    m_group = toastNotification.Group();

    m_expiry = winrt::clock::to_file_time(toastNotification.Expiration());
    m_arrivalTime = winrt::clock::to_file_time(winrt::clock::now());

    m_expiresOnReboot = toastNotification.ExpiresOnReboot();

    if (toastNotification.Progress() != nullptr)
    {
        m_toastProgressData = winrt::make_self<NotificationProgressData>(toastNotification.Progress());
    }

    if (winrt::AppNotificationConferencingConfig::IsCallingPreviewSupported())
    {
        if (auto config = toastNotification.ConferencingConfig())
        {
            m_toastConferencingConfig = winrt::make_self<NotificationConferencingConfig>(config);
        }
    }


    m_notificationType = ToastABI::NotificationType::NotificationType_Toast;
}

NotificationProperties::NotificationProperties(Microsoft::Windows::BadgeNotifications::BadgeNotification &badgeNotification)
{
    // Extract payload and convert it from XML to a byte array
    auto payloadAsSimpleString = Helpers::WideStringToPayloadUtf8String(badgeNotification.Payload());

    m_payload = wil::unique_cotaskmem_array_ptr<byte>(static_cast<byte*>(CoTaskMemAlloc(payloadAsSimpleString.size())), payloadAsSimpleString.size());
    THROW_IF_NULL_ALLOC(m_payload.get());
    CopyMemory(m_payload.data(), payloadAsSimpleString.c_str(), payloadAsSimpleString.size());

    m_notificationId = badgeNotification.Id();

    m_tag = badgeNotification.Tag();
    m_group = badgeNotification.Group();

    m_expiry = winrt::clock::to_file_time(badgeNotification.Expiration());
    m_arrivalTime = winrt::clock::to_file_time(winrt::clock::now());

    m_expiresOnReboot = badgeNotification.ExpiresOnReboot();

    m_notificationType = badgeNotification.NotificationType();
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_NotificationId(_Out_ unsigned int* notificationId) noexcept
{
    auto lock{ m_lock.lock_shared() };

    *notificationId = m_notificationId;
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_Payload(_Out_ unsigned int* payloadSize, _Out_ byte** payload) noexcept try
{
    auto lock{ m_lock.lock_shared() };

    size_t tempPayloadSize = m_payload.size();

    auto tempPayload = wil::unique_cotaskmem_array_ptr<byte>(static_cast<byte*>(CoTaskMemAlloc(tempPayloadSize)), tempPayloadSize);
    CopyMemory(tempPayload.data(), m_payload.get(), tempPayloadSize);

    *payloadSize = static_cast<unsigned int>(tempPayloadSize);
    *payload = tempPayload.release();
    return S_OK;
}
CATCH_RETURN()

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_PayloadSize(_Out_ unsigned int* payloadSize) noexcept
{
    auto lock{ m_lock.lock_shared() };

    *payloadSize = static_cast<unsigned int>(m_payload.size());
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_Tag(_Out_ HSTRING* tag) noexcept try
{
    auto lock{ m_lock.lock_shared() };

    *tag = Microsoft::Windows::AppNotifications::Helpers::safe_make_unique_hstring(m_tag.c_str()).release();
    return S_OK;
}
CATCH_RETURN()

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_Group(_Out_ HSTRING* group) noexcept try
{
    auto lock{ m_lock.lock_shared() };

    *group = Microsoft::Windows::AppNotifications::Helpers::safe_make_unique_hstring(m_group.c_str()).release();
    return S_OK;
}
CATCH_RETURN()

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_Expiry(_Out_ unsigned long long* expiry) noexcept
{
    auto lock{ m_lock.lock_shared() };

    *expiry = static_cast<ULONGLONG>(m_expiry.dwHighDateTime) << 32 | static_cast<ULONGLONG>(m_expiry.dwLowDateTime);
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_ArrivalTime(_Out_ unsigned long long* arrivalTime) noexcept
{
    auto lock{ m_lock.lock_shared() };

    *arrivalTime = static_cast<ULONGLONG>(m_arrivalTime.dwHighDateTime) << 32 | static_cast<ULONGLONG>(m_arrivalTime.dwLowDateTime);
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_BootId(_Out_ unsigned long long* bootId) noexcept
{
    auto lock{ m_lock.lock_shared() };

    *bootId = m_bootId;
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_ExpiresOnReboot(_Out_ boolean* expiresOnReboot) noexcept
{
    auto lock{ m_lock.lock_shared() };

    *expiresOnReboot = m_expiresOnReboot;
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_ToastProgressData(_Out_ ToastABI::IToastProgressData** progressData) noexcept
{
    *progressData = nullptr;
    auto lock{ m_lock.lock_shared() };
    if (m_toastProgressData != nullptr)
    {
        m_toastProgressData.copy_to(progressData);
    }

    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_ActivityId(_Out_ GUID* activityId) noexcept
{
    *activityId = GUID_NULL;
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_ToastConferencingConfig(_Out_ ToastABI::IToastConferencingConfig** conferencingConfig) noexcept
{
    auto lock{ m_lock.lock_shared() };
    m_toastConferencingConfig.copy_to(conferencingConfig);
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationProperties::get_NotificationType(_Out_ ToastABI::NotificationType* notificationType) noexcept
{
    auto lock{ m_lock.lock_shared() };
    *notificationType = m_notificationType;

    return S_OK;
}
