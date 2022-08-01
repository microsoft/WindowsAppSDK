// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Windows.AppNotifications.AppNotificationActivatedEventArgs.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    struct AppNotificationActivatedEventArgs : AppNotificationActivatedEventArgsT<AppNotificationActivatedEventArgs>
    {
        AppNotificationActivatedEventArgs() = default;

        AppNotificationActivatedEventArgs(winrt::hstring const& argument, winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> const& userInput) : m_argument(argument), m_userInput(userInput) {};
        winrt::hstring Argument() { return m_argument; };
        winrt::Windows::Foundation::Collections::IMap<hstring, hstring> UserInput() { return m_userInput; };
        winrt::Windows::Foundation::Collections::IMap<hstring, hstring> Arguments() { return m_arguments; };

    private:
        winrt::hstring m_argument;
        winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> m_userInput;
        winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> m_arguments{ nullptr };
    };
}
