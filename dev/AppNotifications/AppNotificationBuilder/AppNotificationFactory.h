// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationFactory.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct AppNotificationFactory
    {
        AppNotificationFactory() = default;

        static winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton MakeSnoozeButton(winrt::hstring const& id);

        static winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton MakeDismissButton();
    };
}

namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct AppNotificationFactory : AppNotificationFactoryT<AppNotificationFactory, implementation::AppNotificationFactory>
    {
    };
}
