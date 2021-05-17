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
        winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs args = nullptr;

        {
            auto lock = g_lock.lock();
            THROW_HR_IF_NULL_MSG(E_UNEXPECTED, g_waitHandleForArgs, "PushNotificationManager::RegisterActivator has not been called.");
        }

        if (WaitForSingleObject(g_waitHandleForArgs.get(), 1000) == WAIT_OBJECT_0)
        {
            auto lock = g_lock.lock();
            std::swap(args, g_activatedEventArgs);
        }
        return args;
    }
}
