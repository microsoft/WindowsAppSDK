// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Windows.System.EnvironmentManager.h"
#include <WindowsAppRuntimeInsights.h>

class EnvironmentManagerInsights : public wil::TraceLoggingProvider

{
    IMPLEMENT_TRACELOGGING_CLASS(
        EnvironmentManagerInsights,
        "Microsoft.Windows.System.EnvironmentManager.Insights",
        (0xfbce41fa, 0xf7bc, 0x538e, 0x11, 0xf2, 0xab, 0xe1, 0xb9, 0xd2, 0xab, 0x23));

    DEFINE_COMPLIANT_MEASURES_EVENT_STRING(LogMessage,
        MICROSOFT_KEYWORD_MEASURES, stringvalue);

    static void LogWithScopeAndMessage(winrt::Microsoft::Windows::System::implementation::EnvironmentManager::Scope const& scope,
        PCWSTR message)
    {
        TraceLoggingClassWrite("LogMessageWithScope",
             _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingValue(ScopeToString(scope), "scope"),
            TraceLoggingValue(message, "message"));
    }

    static constexpr PCWSTR ScopeToString(winrt::Microsoft::Windows::System::implementation::EnvironmentManager::Scope scope)
    {
        if (scope == winrt::Microsoft::Windows::System::implementation::EnvironmentManager::Scope::Process)
        {
            return L"Process";
        }
        else if (scope == winrt::Microsoft::Windows::System::implementation::EnvironmentManager::Scope::User)
        {
            return L"User";
        }
        else
        {
            return L"Machine";
        }
    }

};
