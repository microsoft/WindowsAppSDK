// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "externs.h"
#include "AppNotificationExtendedTextProperties.h"
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationExtendedTextProperties.g.cpp"
#include "AppNotificationBuilderTelemetry.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    AppNotificationExtendedTextProperties::AppNotificationExtendedTextProperties()
    {
        m_basicTextProperties = winrt::make_self<AppNotificationTextProperties>();
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedTextProperties AppNotificationExtendedTextProperties::SetStyle(AppNotificationTextStyle const& value)
    {
        m_style = value;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedTextProperties AppNotificationExtendedTextProperties::SetMinLines(int const& /*value*/)
    {
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedTextProperties AppNotificationExtendedTextProperties::SetAlign(AppNotificationTextAlign const& value)
    {
        m_align = value;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedTextProperties AppNotificationExtendedTextProperties::SetLanguage(winrt::hstring const& value)
    {
        Language(value);

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedTextProperties AppNotificationExtendedTextProperties::SetIncomingCallAlignment()
    {
        IncomingCallAlignment();

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedTextProperties AppNotificationExtendedTextProperties::SetMaxLines(int const& value)
    {
        MaxLines(value);

        return *this;
    }

    std::wstring AppNotificationExtendedTextProperties::StyleToString()
    {
        std::wstring style{};

        switch (m_style)
        {
        case AppNotificationTextStyle::Base:
            style = L"base";
            break;

        case AppNotificationTextStyle::CaptionSubtle:
            style = L"captionSubtle";
            break;
        }

        return style;
    }

    std::wstring AppNotificationExtendedTextProperties::AlignToString()
    {
        std::wstring align{};

        switch (m_align)
        {
        case AppNotificationTextAlign::Right:
            align = L"right";
            break;
        }

        return align;
    }

    winrt::hstring AppNotificationExtendedTextProperties::ToString()
    {
        return ToStringInternal();
    }

    winrt::hstring AppNotificationExtendedTextProperties::ToStringInternal()
    {
        auto logTelemetry{ AppNotificationBuilderTelemetry::TextPropertiesToString::Start(g_telemetryHelper) };

        auto languageProp{ m_basicTextProperties->Language() };
        auto incomingCallAlignment{ m_basicTextProperties->IncomingCallAlignment() };
        auto maxLines{ m_basicTextProperties->MaxLines() };

        std::wstring language{ !languageProp.empty() ? wil::str_printf<std::wstring>(L" lang='%ls'", languageProp.c_str()) : L"" };
        std::wstring callScenarioAlign{ incomingCallAlignment ? L" hint-callScenarioCenterAlign='true'" : L"" };
        std::wstring hintMaxLines{ maxLines ? wil::str_printf<std::wstring>(L" hint-maxLines='%d'", maxLines) : L"" };

        std::wstring style{ (m_style != AppNotificationTextStyle::Default) ? wil::str_printf<std::wstring>(L" hint-style='%ls'", StyleToString().c_str()) : L"" };
        std::wstring align{ (m_align != AppNotificationTextAlign::Default) ? wil::str_printf<std::wstring>(L" hint-align='%ls'", AlignToString().c_str()) : L"" };
        logTelemetry.Stop();

        return wil::str_printf<std::wstring>(L"<text%ls%ls%ls%ls%ls>", language.c_str(), callScenarioAlign.c_str(), hintMaxLines.c_str(), style.c_str(), align.c_str()).c_str();
    }
}
