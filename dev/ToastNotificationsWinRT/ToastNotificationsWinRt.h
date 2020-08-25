// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "Microsoft.ToastNotificationsWinRt.DesktopToastNotificationManagerCompat.g.h"
#include <Microsoft.ToastNotificationsWinRt.ToastActivatedEventArgs.g.h>

namespace winrt::Microsoft::ToastNotificationsWinRt::implementation
{
    struct ToastActivatedEventArgs : ToastActivatedEventArgsT<ToastActivatedEventArgs>
    {
        ToastActivatedEventArgs() = default;
        ToastActivatedEventArgs(hstring const& appId, hstring const& arguments, Windows::Foundation::Collections::IMap<hstring, hstring> const& userInput);

        hstring Arguments();
        hstring AppId();
        Windows::Foundation::Collections::IMap<hstring, hstring> UserInput();

    private:
        hstring m_arguments;
        hstring m_appId;
        Windows::Foundation::Collections::IMap<hstring, hstring> m_userInput;
    };

    struct DesktopToastNotificationManagerCompat
    {
        DesktopToastNotificationManagerCompat() = default;

        static void RegisterApplication(hstring const& clsid, hstring const& appId, hstring const& displayName, hstring const& iconPath);
        static bool WasProcessToastActivated();
        static winrt::event_token ToastActivated(Windows::Foundation::EventHandler<Microsoft::ToastNotificationsWinRt::ToastActivatedEventArgs> const& handler);
        static void ToastActivated(winrt::event_token const& token) noexcept;
        static void ActivatorCompleted(_In_ PCWSTR appId, _In_ PCWSTR args, _In_ Windows::Foundation::Collections::IMap<hstring, hstring> const& userInput);

    private:
        ~DesktopToastNotificationManagerCompat();
    };
}

namespace winrt::Microsoft::ToastNotificationsWinRt::factory_implementation
{
    struct DesktopToastNotificationManagerCompat : DesktopToastNotificationManagerCompatT<DesktopToastNotificationManagerCompat, implementation::DesktopToastNotificationManagerCompat>
    {
    };

    struct ToastActivatedEventArgs : ToastActivatedEventArgsT<ToastActivatedEventArgs, implementation::ToastActivatedEventArgs>
    {
    };
}
