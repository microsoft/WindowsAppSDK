#pragma once
#include "Microsoft.Windows.PushNotifications.ToastActivatedEventArgs.g.h"
#include <winrt/Windows.Foundation.Collections.h>

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    struct ToastActivatedEventArgs : ToastActivatedEventArgsT<ToastActivatedEventArgs>
    {
        ToastActivatedEventArgs() = delete;

        ToastActivatedEventArgs(winrt::hstring const& arguments, winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> const& userInput) : m_arguments(arguments), m_userInput(userInput) {};

        winrt::hstring Arguments() { return m_arguments; };
        winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> UserInput() { return m_userInput; };

    private:
        winrt::hstring m_arguments;
        winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> m_userInput;
    };
}
