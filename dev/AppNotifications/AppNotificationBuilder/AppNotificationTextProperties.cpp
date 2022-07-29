// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "AppNotificationTextProperties.h"
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationTextProperties.g.cpp"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties AppNotificationTextProperties::SetLanguage(winrt::hstring const& value)
    {
        m_language = value;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties AppNotificationTextProperties::SetIncomingCallAlignment()
    {
        m_useCallScenarioAlign = true;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties AppNotificationTextProperties::SetMaxLines(int const& value)
    {
        m_maxLines = value;
        return *this;
    }

    winrt::hstring AppNotificationTextProperties::ToString()
    {
        std::wstring language{ !m_language.empty() ? wil::str_printf<std::wstring>(L" lang='%ws'", m_language.c_str()) : L""};
        std::wstring callScenarioAlign{ m_useCallScenarioAlign ? L" hint-callScenarioCenterAlign='true'" : L""};
        std::wstring hintMaxLines{ m_maxLines ? wil::str_printf<std::wstring>(L" hint-maxLines='%d'", m_maxLines) : L"" };

        return wil::str_printf<std::wstring>(L"<text%ws%ws%ws>", language.c_str(), hintMaxLines.c_str(), callScenarioAlign.c_str()).c_str();
    }
}
