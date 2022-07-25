#include "pch.h"
#include "AppNotificationProgressBar.h"
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationProgressBar.g.cpp"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    AppNotificationProgressBar::AppNotificationProgressBar() {};

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::SetTitle(winrt::hstring const& value)
    {
        m_title = value;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::BindTitle()
    {
        m_title = L"{progressTitle}";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::SetStatus(winrt::hstring const& value)
    {
        m_status = value;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::BindStatus()
    {
        m_status = L"{progressStatus}";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::SetValue(double value)
    {
        m_value = value;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::BindValue()
    {
        m_value = 1.0;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::SetValueStringOverride(winrt::hstring const& value)
    {
        m_valueStringOverride = value;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::BindValueStringOverride()
    {
        m_valueStringOverride = L"{progressValueString}";

        return *this;
    }
}
