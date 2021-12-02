#pragma once
#include "Microsoft.Windows.ToastNotifications.ToastActivatedEventArgs.g.h"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    struct ToastActivatedEventArgs : ToastActivatedEventArgsT<ToastActivatedEventArgs>
    {
        ToastActivatedEventArgs() = default;

        ToastActivatedEventArgs(winrt::hstring const& arguments, winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> const& userInput) : m_arguments(arguments), m_userInput(userInput) {};

        winrt::hstring ActivationArgs() { return m_arguments; };
        winrt::Windows::Foundation::Collections::IMap<hstring, hstring> UserInput() { return m_userInput; };

    private:
        winrt::hstring m_arguments;
        winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> m_userInput;
    };
}
