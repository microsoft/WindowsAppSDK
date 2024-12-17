// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "AppNotification.h"

#include "AppNotificationUtility.h"
#include "NotificationTransientProperties.h"

namespace winrt
{
    using namespace winrt::Microsoft::Windows::AppNotifications;
}

namespace ToastABI
{
    using namespace ::ABI::Microsoft::Internal::ToastNotifications;
}

NotificationTransientProperties::NotificationTransientProperties(winrt::AppNotification const& toastNotification) noexcept
{
    m_suppressPopup = toastNotification.SuppressDisplay();

    if (toastNotification.Priority() == winrt::AppNotificationPriority::High)
    {
        m_toastNotificationPriority = ToastABI::ToastNotificationPriority::ToastNotificationPriority_High;
    }
}

NotificationTransientProperties::NotificationTransientProperties(_In_ Microsoft::Windows::BadgeNotifications::BadgeNotification &badgeNotification) noexcept
{
    m_suppressPopup = badgeNotification.SuppressDisplay();

    if (badgeNotification.Priority() == winrt::AppNotificationPriority::High)
    {
        m_toastNotificationPriority = ToastABI::ToastNotificationPriority::ToastNotificationPriority_High;
    }
}

STDMETHODIMP_(HRESULT __stdcall) NotificationTransientProperties::get_OfflineCacheCount(_Out_ unsigned long long* offlineCacheCount) noexcept
{
    *offlineCacheCount = 0;
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationTransientProperties::get_OfflineBundleId(_Out_ HSTRING* offlineBundleId) noexcept
{
    *offlineBundleId = nullptr;
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationTransientProperties::get_ServerCacheRollover(_Out_ boolean* serverCacheRollover) noexcept
{
    *serverCacheRollover = false;
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationTransientProperties::get_SuppressPopup(_Out_ boolean* suppressPopup) noexcept
{
    auto lock = m_lock.lock_shared();

    *suppressPopup = m_suppressPopup;
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationTransientProperties::get_RecurrenceId(_Out_ GUID* recurrenceId) noexcept
{
    *recurrenceId = GUID_NULL;
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationTransientProperties::get_MessageId(_Out_ GUID* messageId) noexcept
{
    *messageId = GUID_NULL;
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationTransientProperties::get_ToastNotificationPriority(_Out_ ToastABI::ToastNotificationPriority* priority) noexcept
{
    auto lock = m_lock.lock_shared();

    *priority = m_toastNotificationPriority;
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationTransientProperties::get_CorrelationVector(_Out_ HSTRING* correlationVector) noexcept try
{
    // In the UDK, a null/empty CV will make the UDK to throw.
    // Temporarily return a fixed CV until we address CV properly in the UDK.
    *correlationVector = Microsoft::Windows::AppNotifications::Helpers::safe_make_unique_hstring(L"PmvzQKgYek6Sdk/T5sWaqw.0").release();
    return S_OK;
}
CATCH_RETURN()
