// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include "PushNotificationReceivedEventArgs.h"
#include "externs.h"

static PCWSTR c_pushContractId = L"Windows.Push";

namespace winrt::Microsoft::Windows::PushNotifications
{
    static winrt::Windows::Foundation::IInspectable Deserialize(winrt::Windows::Foundation::Uri const&)
    {
        {
            auto lock = g_lock.lock();
            if (g_activatedEventArgs)
            {
                return g_activatedEventArgs;
            }

            THROW_HR_IF_NULL_MSG(E_UNEXPECTED, g_waitHandleForArgs, "PushNotificationManager::RegisterActivator has not been called.");      
        }

        if (WaitForSingleObject(g_waitHandleForArgs.get(), 1000) == WAIT_OBJECT_0)
        {
            auto lock = g_lock.lock();
            return g_activatedEventArgs;
        }
        winrt::throw_hresult(HRESULT_FROM_WIN32(ERROR_TIMEOUT));
    }
}
