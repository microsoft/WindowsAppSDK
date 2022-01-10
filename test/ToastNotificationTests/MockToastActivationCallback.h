// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "NotificationActivationCallback.h"

struct MockToastActivationCallback : winrt::implements<MockToastActivationCallback, INotificationActivationCallback>
{
    MockToastActivationCallback() {};

    HRESULT __stdcall Activate(
        LPCWSTR appUserModelId,
        LPCWSTR invokedArgs,
        [[maybe_unused]] NOTIFICATION_USER_INPUT_DATA const* data,
        [[maybe_unused]] ULONG dataCount) noexcept
    {
        return S_OK;
    };
};

struct MockToastActivationCallbackFactory : winrt::implements<MockToastActivationCallbackFactory, IClassFactory>
{
    HRESULT __stdcall CreateInstance(_In_opt_ IUnknown* aggregateInterface, _In_ REFIID interfaceId, _Outptr_ VOID** object) noexcept final
    {
        RETURN_HR_IF(CLASS_E_NOAGGREGATION, aggregateInterface != nullptr);
        return winrt::make<MockToastActivationCallback>().as(interfaceId, object);
    }

    HRESULT __stdcall LockServer(BOOL) noexcept final
    {
        return S_OK;
    }
};
