// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "externs.h"
#include "AppNotificationExtendedImageProperties.h"
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationExtendedImageProperties.g.cpp"
#include "AppNotificationBuilderTelemetry.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedImageProperties AppNotificationExtendedImageProperties::SetAlign(AppNotificationImageAlign const& /*align*/)
    {
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedImageProperties AppNotificationExtendedImageProperties::SetRemoveMargin()
    {
        return *this;
    }

    winrt::hstring AppNotificationExtendedImageProperties::ToString()
    {
#if 0
        auto logTelemetry{ AppNotificationBuilderTelemetry::TextPropertiesToString::Start(g_telemetryHelper) };

        std::wstring language{ !m_language.empty() ? wil::str_printf<std::wstring>(L" lang='%ls'", m_language.c_str()) : L"" };
        std::wstring callScenarioAlign{ m_useCallScenarioAlign ? L" hint-callScenarioCenterAlign='true'" : L"" };
        std::wstring hintMaxLines{ m_maxLines ? wil::str_printf<std::wstring>(L" hint-maxLines='%d'", m_maxLines) : L"" };
        logTelemetry.Stop();

        return wil::str_printf<std::wstring>(L"<text%ls%ls%ls>", language.c_str(), hintMaxLines.c_str(), callScenarioAlign.c_str()).c_str();
#endif
        return wil::str_printf<std::wstring>(L"<text%ls%ls%ls>", L"", L"", L"").c_str();
    }
}
