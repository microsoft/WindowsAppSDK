// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "AppNotificationProgressBar.h"
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationProgressBar.g.cpp"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    AppNotificationProgressBar::AppNotificationProgressBar()
        :m_titleStatus{ BindMode::NotSet},
         m_statusStatus{ BindMode::NotSet },
         m_valueStatus{ BindMode::NotSet },
         m_valueStringOverrideStatus{ BindMode::NotSet }
    {};

    void AppNotificationProgressBar::Title(winrt::hstring const& value)
    {
        m_title = value;
        m_titleStatus = BindMode::Value;
    }

    void AppNotificationProgressBar::Status(winrt::hstring const& value)
    {
        m_status = value;
        m_statusStatus = BindMode::Value;
    }

    void AppNotificationProgressBar::Value(double value)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, value < 0.0 || value > 1.0, "You must provide a value between 0.0 and 1.0");

        m_value = value; m_valueStatus = BindMode::Value;
    }

    void AppNotificationProgressBar::ValueStringOverride(winrt::hstring const& value)
    {
        m_valueStringOverride = value;
        m_valueStringOverrideStatus = BindMode::Value;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::SetTitle(winrt::hstring const& value)
    {
        Title(value);

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::BindTitle()
    {
        m_titleStatus = BindMode::Bind;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::SetStatus(winrt::hstring const& value)
    {
        Status(value);

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::BindStatus()
    {
        m_statusStatus = BindMode::Bind;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::SetValue(double value)
    {
        Value(value);

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::BindValue()
    {
        m_valueStatus = BindMode::Bind;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::SetValueStringOverride(winrt::hstring const& value)
    {
        ValueStringOverride(value);

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::BindValueStringOverride()
    {
        m_valueStringOverrideStatus = BindMode::Bind;

        return *this;
    }

    winrt::hstring AppNotificationProgressBar::ToString()
    {
        auto titleValue{ m_titleStatus == BindMode::Value ? m_title : L"{progressTitle}" };
        auto statusValue{ m_statusStatus == BindMode::Value ? m_status : L"{progressStatus}" };
        auto valueValue{ m_valueStatus == BindMode::Value ? wil::str_printf<std::wstring>(L"%g", m_value) : L"{progressValue}" };
        auto valueStringOverrideValue{ m_valueStringOverrideStatus == BindMode::Value ? m_valueStringOverride : L"{progressValueString}" };

        auto title{ m_titleStatus == BindMode::NotSet ? L"" : wil::str_printf<std::wstring>(L" title='%ls'", titleValue.c_str()) };
        auto status{ wil::str_printf<std::wstring>(L" status='%ls'", statusValue.c_str()) };
        auto value{ wil::str_printf<std::wstring>(L" value='%ls'", valueValue.c_str()) };
        auto valueStringOverride{ m_valueStringOverrideStatus == BindMode::NotSet ? L"" : wil::str_printf < std::wstring>(L" valueStringOverride='%ls'", valueStringOverrideValue.c_str()) };

        return wil::str_printf<std::wstring>(L"<progress%ls%ls%ls%ls/>", title.c_str(), status.c_str(), value.c_str(), valueStringOverride.c_str()).c_str();
    }
}
