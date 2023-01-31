// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "externs.h"
#include "AppNotificationHeader.h"
#include "AppNotificationBuilderTelemetry.h"
#include <winrt/Windows.Globalization.h>
#include <winrt/Windows.Globalization.DateTimeFormatting.h>
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationHeader.g.cpp"
#include "AppNotificationBuilderUtility.h"
#include <iomanip>
#include <ctime>
#include <sstream>
#include <IsWindowsVersion.h>

using namespace winrt::Windows::Globalization;
using namespace winrt::Windows::Globalization::DateTimeFormatting;

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    AppNotificationHeader::AppNotificationHeader(winrt::hstring const& id, winrt::hstring const& title) : m_id(id), m_title(title) { }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationHeader AppNotificationHeader::AddArgument(winrt::hstring const& key, winrt::hstring const& value)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, key.empty(), "You must provide a key when adding an argument");

        m_arguments.Insert(EncodeArgument(key.c_str()), EncodeArgument(value.c_str()));
        return *this;
    }

    std::wstring AppNotificationHeader::GetArguments()
    {
        // Add header launch arguments if given arguments
        if (m_arguments.Size())
        {
            std::wstring arguments;
            for (auto pair : m_arguments)
            {
                if (!pair.Value().empty())
                {
                    arguments.append(wil::str_printf<std::wstring>(L"%ls=%ls;", pair.Key().c_str(), pair.Value().c_str()));
                }
                else
                {
                    arguments.append(wil::str_printf<std::wstring>(L"%ls;", pair.Key().c_str()));
                }
            }
            arguments.pop_back();

            return wil::str_printf<std::wstring>(L"arguments='%ls'", arguments.c_str());
        }
        else
        {
            return {};
        }
    }

    winrt::hstring AppNotificationHeader::ToString()
    {
        //auto logTelemetry{ AppNotificationBuilderTelemetry::ProgressBarToString::Start(g_telemetryHelper) };

        //auto title{ wil::str_printf<std::wstring>(L" title='%ls'", m_titleBindMode == BindMode::Value ? m_title.c_str() : L"{progressTitle}") };
        //auto status{ wil::str_printf<std::wstring>(L" status='%ls'", m_statusBindMode == BindMode::Value ? m_status.c_str() : L"{progressStatus}") };
        //auto value{ wil::str_printf<std::wstring>(L" value='%ls'", m_valueBindMode == BindMode::Value ? wil::str_printf<std::wstring>(L"%g", m_value).c_str() : L"{progressValue}") };
        //auto valueStringOverride{ wil::str_printf < std::wstring>(L" valueStringOverride='%ls'", m_valueStringOverrideBindMode == BindMode::Value ? m_valueStringOverride.c_str() : L"{progressValueString}") };

        //logTelemetry.Stop();

        //        m_header = wil::str_printf<std::wstring>(L"<header id='%ls' title='%ls' arguments='%ls'/>", std::locale::id::id.c_str(), title.c_str(), arguments.c_str());

        return wil::str_printf<std::wstring>(L"<header id='%ls' title='%ls' %ls/>",
                m_id.c_str(),
                m_title.c_str(),
                GetArguments().c_str()).c_str();
    }
}
