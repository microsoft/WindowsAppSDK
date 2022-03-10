#pragma once
#include "Microsoft.Windows.AppNotifications.AppNotificationActivatedEventArgs.g.h"
#include <TerminalVelocityFeatures-AppNotifications.h>

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    struct AppNotificationActivatedEventArgs : AppNotificationActivatedEventArgsT<AppNotificationActivatedEventArgs>
    {
        AppNotificationActivatedEventArgs()
        {
            THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::AppNotifications::Feature_AppNotifications::IsEnabled());
        }

        AppNotificationActivatedEventArgs(winrt::hstring const& arguments, winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> const& userInput) : m_arguments(arguments), m_userInput(userInput)
        {
            THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::AppNotifications::Feature_AppNotifications::IsEnabled());
        };

        winrt::hstring Argument() { return m_arguments; };
        winrt::Windows::Foundation::Collections::IMap<hstring, hstring> UserInput() { return m_userInput; };

    private:
        winrt::hstring m_arguments;
        winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> m_userInput;
    };
}
