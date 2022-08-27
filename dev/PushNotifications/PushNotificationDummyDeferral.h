// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "pch.h"
#include <winrt/base.h>
#include <winrt/Windows.ApplicationModel.background.h>

struct PushNotificationDummyDeferral : winrt::implements <PushNotificationDummyDeferral, winrt::Windows::ApplicationModel::Background::IBackgroundTaskDeferral>
{
    PushNotificationDummyDeferral() {}

    void Complete() { };
};

struct PushNotificationDummyDeferralFactory : winrt::implements<PushNotificationDummyDeferralFactory, IClassFactory>
{
    HRESULT __stdcall CreateInstance(_In_opt_ IUnknown* aggregateInterface, _In_ REFIID interfaceId, _Outptr_ VOID** object) noexcept final try
    {
        THROW_HR_IF(CLASS_E_NOAGGREGATION, aggregateInterface != nullptr);
        return winrt::make<PushNotificationDummyDeferral>().as(interfaceId, object);
    }
    CATCH_RETURN()

    HRESULT __stdcall LockServer(BOOL) noexcept final
    {
        return S_OK;
    }
};
