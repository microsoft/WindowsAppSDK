// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "ToastProgressData.h"
#include "ToastProgressDataABI.h"
#include "ToastNotificationUtility.h"

namespace winrt
{
    using namespace winrt::Microsoft::Windows::ToastNotifications;
}

namespace ToastABI
{
    using namespace ::ABI::Microsoft::Internal::ToastNotifications;
}

ToastProgressDataABI::ToastProgressDataABI(winrt::ToastProgressData const& progressData)
{
    m_progressData = progressData;
}

STDMETHODIMP_(HRESULT __stdcall) ToastProgressDataABI::get_SequenceNumber(_Out_ unsigned int* value)
{
    auto lock = m_lock.lock_shared();

    *value = m_progressData.SequenceNumber();

    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ToastProgressDataABI::get_Title(_Out_ HSTRING* value)
{
    auto lock = m_lock.lock_shared();

    *value = safe_make_unique_hstring(m_progressData.Title().c_str()).release();

    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ToastProgressDataABI::get_Value(_Out_ double* value)
{
    auto lock = m_lock.lock_shared();

    *value = m_progressData.Value();

    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ToastProgressDataABI::get_ValueStringOverride(_Out_ HSTRING* value)
{
    auto lock = m_lock.lock_shared();

    *value = safe_make_unique_hstring(m_progressData.ValueStringOverride().c_str()).release();

    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) ToastProgressDataABI::get_Status(_Out_ HSTRING* value)
{
    auto lock = m_lock.lock_shared();

    *value = safe_make_unique_hstring(m_progressData.Status().c_str()).release();

    return S_OK;
}

