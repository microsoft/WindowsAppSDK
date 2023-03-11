// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "externs.h"
#include "AppNotificationImageProperties.h"
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationImageProperties.g.cpp"
#include "AppNotificationBuilderTelemetry.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationImageProperties AppNotificationImageProperties::SetImageQuery()
    {
        m_imageQuery = true;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationImageProperties AppNotificationImageProperties::SetAlternateText(winrt::hstring const& alternateText)
    {
        m_alternateText = alternateText;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationImageProperties AppNotificationImageProperties::SetCrop(AppNotificationImageCrop const& crop)
    {
        m_crop = crop;
        return *this;
    }

    winrt::hstring AppNotificationImageProperties::ToString()
    {
#if 0
        auto logTelemetry{ AppNotificationBuilderTelemetry::TextPropertiesToString::Start(g_telemetryHelper) };

        std::wstring language{ !m_language.empty() ? wil::str_printf<std::wstring>(L" lang='%ls'", m_language.c_str()) : L"" };
        std::wstring callScenarioAlign{ m_useCallScenarioAlign ? L" hint-callScenarioCenterAlign='true'" : L"" };
        std::wstring hintMaxLines{ m_maxLines ? wil::str_printf<std::wstring>(L" hint-maxLines='%d'", m_maxLines) : L"" };
        std::wstring style{ (m_style != AppNotificationTextStyle::Default) ? wil::str_printf<std::wstring>(L" hint-style='%ls'", StyleToString().c_str()) : L"" };
        std::wstring align{ (m_align != AppNotificationTextAlign::Default) ? wil::str_printf<std::wstring>(L" hint-align='%ls'", AlignToString().c_str()) : L"" };
        logTelemetry.Stop();

        return wil::str_printf<std::wstring>(L"<text%ls%ls%ls%ls%ls>", language.c_str(), hintMaxLines.c_str(), callScenarioAlign.c_str(), style.c_str(), align.c_str()).c_str();
#endif
        return wil::str_printf<std::wstring>(L"<text%ls%ls%ls%ls%ls>", L"", L"", L"", L"", L"").c_str();
    }
}
