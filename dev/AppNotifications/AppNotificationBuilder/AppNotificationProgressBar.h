// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationProgressBar.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{

    struct AppNotificationProgressBar : AppNotificationProgressBarT<AppNotificationProgressBar, winrt::Windows::Foundation::IStringable>
    {
        AppNotificationProgressBar();

        // Properties
        void Title(winrt::hstring const& value);
        winrt::hstring Title() { return m_title; };

        void Status(winrt::hstring const& value);
        winrt::hstring Status() { return m_status; };

        void Value(double value);
        double Value() { return m_value; };

        void ValueStringOverride(winrt::hstring const& value);
        winrt::hstring ValueStringOverride() { return m_valueStringOverride; };

        // Fluent setters
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar SetTitle(winrt::hstring const& value);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar BindTitle();

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar SetStatus(winrt::hstring const& value);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar BindStatus();

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar SetValue(double value);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar BindValue();

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar SetValueStringOverride(winrt::hstring const& value);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar BindValueStringOverride();

        // IStringable
        winrt::hstring ToString();

    private:
        enum class BindMode {NotSet, Bind, Value};

        BindMode m_titleBindMode;
        winrt::hstring m_title;
        BindMode m_statusBindMode;
        winrt::hstring m_status;
        BindMode m_valueBindMode;
        double m_value{ 0.0 };
        BindMode m_valueStringOverrideBindMode;
        winrt::hstring m_valueStringOverride;
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct AppNotificationProgressBar : AppNotificationProgressBarT<AppNotificationProgressBar, implementation::AppNotificationProgressBar>
    {
    };
}
