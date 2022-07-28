// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

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

    winrt::hstring AppNotificationProgressBar::ToString()
    {
        winrt::hstring xml{ L"" };

        // props.as<ITextProperties>()->GetCallScenarioAlign()
        // <progress title = "{progressTitle}" value = "{progressValue}" valueStringOverride = "{progressValueString}" status = "{progressStatus}"/>
        if (!m_title.empty())
        {
            xml = xml + L"<progress title = \"" + m_title + L"\"";

            if (m_value != 0.0)
            {
                xml = xml + L" value = \"" + std::to_wstring(m_value) + L"\"";
            }

            if (!m_valueStringOverride.empty())
            {
                xml = xml + L" valueStringOverride = \"" + m_valueStringOverride + L"\"";
            }

            if (!m_status.empty())
            {
                xml = xml + L" status = \"" + xml + L"\"";
            }

            xml = xml + L"/>";
        }

        return xml;
    }
}
