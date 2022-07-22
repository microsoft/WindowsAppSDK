#pragma once
#include "Microsoft.Windows.System.EnvironmentManager.h"
#include <WindowsAppRuntimeInsights.h>

DECLARE_TRACELOGGING_CLASS(
EnvironmentManagerTelemetryProvider,
    "Microsoft.Windows.System.EnvironmentManager.Insights",
    (0xfbce41fa, 0xf7bc, 0x538e, 0x11, 0xf2, 0xab, 0xe1, 0xb9, 0xd2, 0xab, 0x23));

class EnvironmentManagerInsights : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(EnvironmentManagerInsights, EnvironmentManagerTelemetryProvider);

    DEFINE_EVENT_METHOD(LogMessage)(std::wstring message) {
        TraceLoggingClassWriteMeasure(
            "CreateChannelAsync",
            TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingWideString(message.c_str(), "Message"));
    }

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
