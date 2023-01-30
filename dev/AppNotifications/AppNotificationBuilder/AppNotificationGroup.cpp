// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "externs.h"
#include "AppNotificationGroup.h"
#include "AppNotificationBuilderTelemetry.h"
#include <winrt/Windows.Globalization.h>
#include <winrt/Windows.Globalization.DateTimeFormatting.h>
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationGroup.g.cpp"
#include "AppNotificationBuilderUtility.h"
#include <iomanip>
#include <ctime>
#include <sstream>
#include <IsWindowsVersion.h>

using namespace winrt::Windows::Globalization;
using namespace winrt::Windows::Globalization::DateTimeFormatting;

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationGroup AppNotificationGroup::AddSubgroup(AppNotificationSubgroup value)
    {
        m_subgroupList.push_back(value);

        return *this;
    }

    std::wstring AppNotificationGroup::GetSubgroups()
    {
        std::wstring result{};
        for (auto subgroup : m_subgroupList)
        {
            result.append(subgroup.as<winrt::Windows::Foundation::IStringable>().ToString());
        }

        return result;
    }

    winrt::hstring AppNotificationGroup::ToString()
    {
        //auto logTelemetry{ AppNotificationBuilderTelemetry::ProgressBarToString::Start(g_telemetryHelper) };

        //auto title{ wil::str_printf<std::wstring>(L" title='%ls'", m_titleBindMode == BindMode::Value ? m_title.c_str() : L"{progressTitle}") };
        //auto status{ wil::str_printf<std::wstring>(L" status='%ls'", m_statusBindMode == BindMode::Value ? m_status.c_str() : L"{progressStatus}") };
        //auto value{ wil::str_printf<std::wstring>(L" value='%ls'", m_valueBindMode == BindMode::Value ? wil::str_printf<std::wstring>(L"%g", m_value).c_str() : L"{progressValue}") };
        //auto valueStringOverride{ wil::str_printf < std::wstring>(L" valueStringOverride='%ls'", m_valueStringOverrideBindMode == BindMode::Value ? m_valueStringOverride.c_str() : L"{progressValueString}") };

        //logTelemetry.Stop();

        return wil::str_printf<std::wstring>(L"<group>%ls</group>",
            GetSubgroups().c_str()).c_str();
            //m_titleBindMode == BindMode::NotSet ? L"" : title.c_str(),
            //status.c_str(),
            //value.c_str(),
            //m_valueStringOverrideBindMode == BindMode::NotSet ? L"" : valueStringOverride.c_str()).c_str();
    }
}
