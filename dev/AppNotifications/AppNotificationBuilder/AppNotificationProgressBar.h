#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationProgressBar.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{

    struct AppNotificationProgressBar : AppNotificationProgressBarT<AppNotificationProgressBar, winrt::Windows::Foundation::IStringable>
    {
        AppNotificationProgressBar();

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar SetTitle(winrt::hstring const& value);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar BindTitle();

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar SetStatus(winrt::hstring const& value);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar BindStatus();

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar SetValue(double value);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar BindValue();

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar SetValueStringOverride(winrt::hstring const& value);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar BindValueStringOverride();

        winrt::hstring ToString();

        // IAppNotificationProgressBar
        //winrt::hstring GetTitle() { return m_title; };
        //winrt::hstring GetStatus() { return m_status; };
        //double GetValue() { return m_value; };
        //winrt::hstring GetValueStringOverride() { return m_valueStringOverride; };

    private:
        winrt::hstring m_title;
        winrt::hstring m_status;
        double m_value;
        winrt::hstring m_valueStringOverride;
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct AppNotificationProgressBar : AppNotificationProgressBarT<AppNotificationProgressBar, implementation::AppNotificationProgressBar>
    {
    };
}
