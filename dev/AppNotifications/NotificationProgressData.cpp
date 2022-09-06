// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "AppNotificationProgressData.h"
#include "NotificationProgressData.h"
#include "AppNotificationUtility.h"

namespace winrt
{
    using namespace winrt::Microsoft::Windows::AppNotifications;
}

namespace ToastABI
{
    using namespace ::ABI::Microsoft::Internal::ToastNotifications;
}

NotificationProgressData::NotificationProgressData(winrt::AppNotificationProgressData const& progressData)
    : m_progressData(progressData.SequenceNumber())
{
    m_progressData.Status(progressData.Status());
    m_progressData.Title(progressData.Title());
    m_progressData.Value(progressData.Value());
    m_progressData.ValueStringOverride(progressData.ValueStringOverride());
}

STDMETHODIMP NotificationProgressData::get_SequenceNumber(_Out_ unsigned int* value) noexcept
{
    *value = m_progressData.SequenceNumber();
    return S_OK;
}

STDMETHODIMP NotificationProgressData::get_Title(_Out_ HSTRING* value) noexcept try
{
    *value = Microsoft::Windows::AppNotifications::Helpers::safe_make_unique_hstring(m_progressData.Title().c_str()).release();
    return S_OK;
}
CATCH_RETURN()

STDMETHODIMP NotificationProgressData::get_Value(_Out_ double* value) noexcept
{
    *value = m_progressData.Value();
    return S_OK;
}

STDMETHODIMP NotificationProgressData::get_ValueStringOverride(_Out_ HSTRING* value) noexcept try
{
    *value = Microsoft::Windows::AppNotifications::Helpers::safe_make_unique_hstring(m_progressData.ValueStringOverride().c_str()).release();
    return S_OK;
}
CATCH_RETURN()

STDMETHODIMP NotificationProgressData::get_Status(_Out_ HSTRING* value) noexcept try
{
    *value = Microsoft::Windows::AppNotifications::Helpers::safe_make_unique_hstring(m_progressData.Status().c_str()).release();
    return S_OK;
}
CATCH_RETURN()

