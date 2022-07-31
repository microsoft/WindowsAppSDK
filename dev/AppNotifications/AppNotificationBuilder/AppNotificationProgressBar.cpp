// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "AppNotificationProgressBar.h"
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationProgressBar.g.cpp"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    AppNotificationProgressBar::AppNotificationProgressBar()
        :m_titleStatus{ Status1::notset},
         m_statusStatus{ Status1::notset },
         m_valueStatus{ Status1::notset },
         m_valueStringOverrideStatus{ Status1::notset }
    {};

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::SetTitle(winrt::hstring const& value)
    {
        m_title = value;
        m_titleStatus = Status1::value;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::BindTitle()
    {
        m_titleStatus = Status1::bind;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::SetStatus(winrt::hstring const& value)
    {
        m_status = value;
        m_statusStatus = Status1::value;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::BindStatus()
    {
        m_statusStatus = Status1::bind;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::SetValue(double value)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, value < 0.0 || value > 1.0, "You must provide a value between 0.0 and 1.0");

        m_value = value;
        m_valueStatus = Status1::value;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::BindValue()
    {
        m_valueStatus = Status1::bind;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::SetValueStringOverride(winrt::hstring const& value)
    {
        m_valueStringOverride = value;
        m_valueStringOverrideStatus = Status1::value;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar AppNotificationProgressBar::BindValueStringOverride()
    {
        m_valueStringOverrideStatus = Status1::bind;

        return *this;
    }

    winrt::hstring AppNotificationProgressBar::ToString()
    {
        std::wstring title1{ m_titleStatus == Status1::value ? m_title : L"{progressTitle}" };
        std::wstring status1{ m_statusStatus == Status1::value ? m_status : L"{progressStatus}" };
        std::wstring value1{ m_valueStatus == Status1::value ? wil::str_printf<std::wstring>(L"%g", m_value) : L"{progressValue}" };
        std::wstring valueStringOverride1{ m_valueStringOverrideStatus == Status1::value ? m_valueStringOverride : L"{progressValueString}" };

        std::wstring title{ m_titleStatus == Status1::notset ? L"" : L" title='" + title1 + L"'" };
        std::wstring status{ L" status='" + status1 + L"'" };
        std::wstring value{ L" value='" + value1 + L"'" };
        std::wstring valueStringOverride{ m_valueStringOverrideStatus == Status1::notset ? L"" : L" valueStringOverride='" + valueStringOverride1 + L"'" };

        return wil::str_printf<std::wstring>(L"<progress%ls%ls%ls%ls/>", title.c_str(), status.c_str(), value.c_str(), valueStringOverride.c_str()).c_str();
    }
}
