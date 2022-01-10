// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationManager.g.h"
#include <windows.foundation.h>

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    // my code change
    struct PushNotificationManager
    {
        PushNotificationManager() = delete;

        static void RegisterActivator(Microsoft::Windows::PushNotifications::PushNotificationActivationInfo const& details);
        static void UnregisterActivator(Microsoft::Windows::PushNotifications::PushNotificationRegistrationActivators const& activators);
        static void UnregisterAllActivators();

        static winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult, winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus> CreateChannelAsync(winrt::guid const remoteId);

        static bool IsActivatorSupported(Microsoft::Windows::PushNotifications::PushNotificationRegistrationActivators const& activators);
    };
}

namespace winrt::Microsoft::Windows::PushNotifications::factory_implementation
{
    struct PushNotificationManager : PushNotificationManagerT<PushNotificationManager, implementation::PushNotificationManager>
    {
    };
}
