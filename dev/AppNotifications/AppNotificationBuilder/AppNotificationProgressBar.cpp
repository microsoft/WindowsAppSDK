// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "AppNotificationProgressBar.h"
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationProgressBar.g.cpp"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    AppNotificationProgressBar::AppNotificationProgressBar()
        :m_titleBindMode{ BindMode::NotSet },
         m_statusBindMode{ BindMode::NotSet },
         m_valueBindMode{ BindMode::NotSet },
         m_valueStringOverrideBindMode{ BindMode::NotSet }
    {};

    void AppNotificationProgressBar::Title(winrt::hstring const& value)
    {
        m_title = value;
        m_titleBindMode = BindMode::Value;
    }

    void AppNotificationProgressBar::Status(winrt::hstring const& value)
    {
        m_status = value;
        m_statusBindMode = BindMode::Value;
    }

    void AppNotificationProgressBar::Value(double value)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, value < 0.0 || value > 1.0, "You must provide a value between 0.0 and 1.0");

        m_value = value;
        m_valueBindMode = BindMode::Value;
    }

    void AppNotificationProgressBar::ValueStringOverride(winrt::hstring const& value)
    {
        m_valueStringOverride = value;
        m_valueStringOverrideBindMode = BindMode::Value;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::SetTitle(winrt::hstring const& value)
    {
        Title(value);

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::BindTitle()
    {
        m_titleBindMode = BindMode::Bind;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::SetStatus(winrt::hstring const& value)
    {
        Status(value);

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::BindStatus()
    {
        m_statusBindMode = BindMode::Bind;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::SetValue(double value)
    {
        Value(value);

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::BindValue()
    {
        m_valueBindMode = BindMode::Bind;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::SetValueStringOverride(winrt::hstring const& value)
    {
        ValueStringOverride(value);

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::BindValueStringOverride()
    {
        m_valueStringOverrideBindMode = BindMode::Bind;

        return *this;
    }

    winrt::hstring AppNotificationProgressBar::ToString()
    {
        auto title{ wil::str_printf<std::wstring>(L" title='%ls'", m_titleBindMode == BindMode::Value ? m_title.c_str() : L"{progressTitle}") };
        auto status{ wil::str_printf<std::wstring>(L" status='%ls'", m_statusBindMode == BindMode::Value ? m_status.c_str() : L"{progressStatus}") };
        auto value{ wil::str_printf<std::wstring>(L" value='%ls'", m_valueBindMode == BindMode::Value ? wil::str_printf<std::wstring>(L"%g", m_value).c_str() : L"{progressValue}") };
        auto valueStringOverride{ wil::str_printf < std::wstring>(L" valueStringOverride='%ls'", m_valueStringOverrideBindMode == BindMode::Value ? m_valueStringOverride.c_str() : L"{progressValueString}") };

        return wil::str_printf<std::wstring>(L"<progress%ls%ls%ls%ls/>",
            m_titleBindMode == BindMode::NotSet ? L"" : title.c_str(),
            status.c_str(),
            value.c_str(),
            m_valueStringOverrideBindMode == BindMode::NotSet ? L"" : valueStringOverride.c_str()).c_str();
    }
}
