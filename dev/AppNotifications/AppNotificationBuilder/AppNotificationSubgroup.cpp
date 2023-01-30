// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "externs.h"
#include "AppNotificationSubgroup.h"
#include "AppNotificationBuilderTelemetry.h"
#include <winrt/Windows.Globalization.h>
#include <winrt/Windows.Globalization.DateTimeFormatting.h>
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationSubgroup.g.cpp"
#include "AppNotificationBuilderUtility.h"
#include <iomanip>
#include <ctime>
#include <sstream>
#include <IsWindowsVersion.h>

using namespace winrt::Windows::Globalization;
using namespace winrt::Windows::Globalization::DateTimeFormatting;

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationSubgroup AppNotificationSubgroup::AddText(hstring const& text)
    {
        //THROW_HR_IF_MSG(E_INVALIDARG, m_textLines.size() >= c_maxTextElements, "Maximum number of text elements added");

        m_textLines.push_back(wil::str_printf<std::wstring>(L"<text>%ls</text>", EncodeXml(text).c_str()).c_str());
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationSubgroup AppNotificationSubgroup::AddText(hstring const& text, AppNotificationTextProperties const& properties)
    {
        //THROW_HR_IF_MSG(E_INVALIDARG, m_textLines.size() >= c_maxTextElements, "Maximum number of text elements added");

        std::wstring props{ properties.as<winrt::Windows::Foundation::IStringable>().ToString() };
        m_textLines.push_back(wil::str_printf<std::wstring>(L"%ls%ls</text>", props.c_str(), EncodeXml(text).c_str()).c_str());

        //if (properties.IncomingCallAlignment())
        //{
        //    m_scenario = AppNotificationScenario::IncomingCall;
        //}
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationSubgroup AppNotificationSubgroup::SetInlineImage(winrt::Windows::Foundation::Uri const& /*imageUri*/)
    {
        //m_inlineImage = wil::str_printf<std::wstring>(L"<image src='%ls'/>", imageUri.ToString().c_str());
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationSubgroup AppNotificationSubgroup::SetInlineImage(winrt::Windows::Foundation::Uri const& /*imageUri*/, AppNotificationImageCrop const& imageCrop)
    {
        if (imageCrop == AppNotificationImageCrop::Circle)
        {
            //m_inlineImage = wil::str_printf<std::wstring>(L"<image src='%ls' hint-crop='circle'/>", imageUri.ToString().c_str());
        }
        else
        {
            //SetInlineImage(imageUri);
        }

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationSubgroup AppNotificationSubgroup::SetInlineImage(winrt::Windows::Foundation::Uri const& /*imageUri*/, AppNotificationImageCrop const& imageCrop, hstring const& alternateText)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, alternateText.empty(), "You must provide an alternate text string calling SetInlineImage");

        std::wstring hintCrop{ imageCrop == AppNotificationImageCrop::Circle ? L" hint-crop='circle'" : L"" };
        //m_inlineImage = wil::str_printf<std::wstring>(L"<image src='%ls' alt='%ls'%ls/>", imageUri.ToString().c_str(), EncodeXml(alternateText).c_str(), hintCrop.c_str());

        return *this;
    }

    std::wstring AppNotificationSubgroup::GetText()
    {
        std::wstring result{};
        for (auto text : m_textLines)
        {
            result.append(text);
        }

        return result;
    }

    winrt::hstring AppNotificationSubgroup::ToString()
    {
        //auto logTelemetry{ AppNotificationBuilderTelemetry::ProgressBarToString::Start(g_telemetryHelper) };

        //auto title{ wil::str_printf<std::wstring>(L" title='%ls'", m_titleBindMode == BindMode::Value ? m_title.c_str() : L"{progressTitle}") };
        //auto status{ wil::str_printf<std::wstring>(L" status='%ls'", m_statusBindMode == BindMode::Value ? m_status.c_str() : L"{progressStatus}") };
        //auto value{ wil::str_printf<std::wstring>(L" value='%ls'", m_valueBindMode == BindMode::Value ? wil::str_printf<std::wstring>(L"%g", m_value).c_str() : L"{progressValue}") };
        //auto valueStringOverride{ wil::str_printf < std::wstring>(L" valueStringOverride='%ls'", m_valueStringOverrideBindMode == BindMode::Value ? m_valueStringOverride.c_str() : L"{progressValueString}") };

        //logTelemetry.Stop();

        return wil::str_printf<std::wstring>(L"<subgroup>%ls</subgroup>",
            GetText().c_str()).c_str();
        //m_titleBindMode == BindMode::NotSet ? L"" : title.c_str(),
        //status.c_str(),
        //value.c_str(),
        //m_valueStringOverrideBindMode == BindMode::NotSet ? L"" : valueStringOverride.c_str()).c_str();
    }
}
