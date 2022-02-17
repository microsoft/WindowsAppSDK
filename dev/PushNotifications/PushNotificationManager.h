// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationManager.g.h"
#include <windows.foundation.h>

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{

    struct PushNotificationManager : PushNotificationManagerT<PushNotificationManager>
    {
        PushNotificationManager() = default;

        static winrt::Microsoft::Windows::PushNotifications::PushNotificationManager Default();
        void Register();
        void Unregister();
        void UnregisterAll();

        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult, winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus> CreateChannelAsync(winrt::guid const remoteId);
    };
}

namespace winrt::Microsoft::Windows::PushNotifications::factory_implementation
{
    struct PushNotificationManager : PushNotificationManagerT<PushNotificationManager, implementation::PushNotificationManager>
    {
    };
}
