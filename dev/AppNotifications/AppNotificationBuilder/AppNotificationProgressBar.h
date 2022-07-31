// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationProgressBar.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{

    struct AppNotificationProgressBar : AppNotificationProgressBarT<AppNotificationProgressBar, winrt::Windows::Foundation::IStringable>
    {
        AppNotificationProgressBar();

        // Properties
        void Title(winrt::hstring const& value) { m_title = value; m_titleStatus = Status1::value; };
        winrt::hstring Title() { return m_title; };

        void Status(winrt::hstring const& value) { m_status = value; m_statusStatus = Status1::value; };
        winrt::hstring Status() { return m_status; };

        void Value(double value)
        {
            THROW_HR_IF_MSG(E_INVALIDARG, value < 0.0 || value > 1.0, "You must provide a value between 0.0 and 1.0");

            m_value = value; m_valueStatus = Status1::value;
        };
        double Value() { return m_value; };

        void ValueStringOverride(winrt::hstring const& value) { m_valueStringOverride = value; m_valueStringOverrideStatus = Status1::value; };
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
        enum class Status1 {notset, bind, value};

        Status1 m_titleStatus;
        winrt::hstring m_title;
        Status1 m_statusStatus;
        winrt::hstring m_status;
        Status1 m_valueStatus;
        double m_value;
        Status1 m_valueStringOverrideStatus;
        winrt::hstring m_valueStringOverride;
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct AppNotificationProgressBar : AppNotificationProgressBarT<AppNotificationProgressBar, implementation::AppNotificationProgressBar>
    {
    };
}
