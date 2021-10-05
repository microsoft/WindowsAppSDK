// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Windows.PushNotifications.ToastNotificationManager.g.h"
#include <windows.foundation.h>
#include "winrt/Windows.UI.h"

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{

    struct ToastNotificationManager
    {
        ToastNotificationManager() = delete;

        static void RegisterActivator(winrt::hstring displayName, winrt::Windows::Foundation::Uri iconUri, winrt::Windows::UI::Color const& color);
    };
}
namespace winrt::Microsoft::Windows::PushNotifications::factory_implementation
{
    struct ToastNotificationManager : ToastNotificationManagerT<ToastNotificationManager, implementation::ToastNotificationManager>
    {
    };
}
