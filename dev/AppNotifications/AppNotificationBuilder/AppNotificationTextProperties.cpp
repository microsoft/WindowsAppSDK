// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "externs.h"
#include "AppNotificationTextProperties.h"
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationTextProperties.g.cpp"
#include "AppNotificationBuilderTelemetry.h"

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
        auto logTelemetry{ AppNotificationBuilderTelemetry::TextPropertiesToString::Start(g_telemetryHelper) };

        std::wstring language{ !m_language.empty() ? wil::str_printf<std::wstring>(L" lang='%ls'", m_language.c_str()) : L"" };
        std::wstring callScenarioAlign{ m_useCallScenarioAlign ? L" hint-callScenarioCenterAlign='true'" : L"" };
        std::wstring hintMaxLines{ m_maxLines ? wil::str_printf<std::wstring>(L" hint-maxLines='%d'", m_maxLines) : L"" };

        logTelemetry.Stop();

        return wil::str_printf<std::wstring>(L"<text%ls%ls%ls>", language.c_str(), hintMaxLines.c_str(), callScenarioAlign.c_str()).c_str();
    }
}
