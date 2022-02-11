// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "NotificationActivationCallback.h"

struct AppNotificationActivationCallback : winrt::implements<AppNotificationActivationCallback, INotificationActivationCallback>
{
    HRESULT __stdcall Activate(
        LPCWSTR appUserModelId,
        LPCWSTR invokedArgs,
        [[maybe_unused]] NOTIFICATION_USER_INPUT_DATA const* data,
        [[maybe_unused]] ULONG dataCount) noexcept;
};

struct AppNotificationActivationCallbackFactory : winrt::implements<AppNotificationActivationCallbackFactory, IClassFactory>
{
    STDMETHODIMP CreateInstance(_In_opt_ IUnknown* aggregateInterface, _In_ REFIID interfaceId, _Outptr_ VOID** object) noexcept final try
    {
        RETURN_HR_IF(CLASS_E_NOAGGREGATION, aggregateInterface != nullptr);
        return winrt::make<AppNotificationActivationCallback>().as(interfaceId, object);
    }
    CATCH_RETURN()

    STDMETHODIMP LockServer(BOOL fLock) noexcept final
    {
        if (fLock)
        {
            ++winrt::get_module_lock();
        }
        else
        {
            --winrt::get_module_lock();
        }
        return S_OK;
    }
};
