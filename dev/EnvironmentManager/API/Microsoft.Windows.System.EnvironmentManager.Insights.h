#pragma once
#include "Microsoft.Windows.System.EnvironmentManager.h"

class EnvironmentManagerInsights : public wil::TraceLoggingProvider

{
    IMPLEMENT_TRACELOGGING_CLASS(
        EnvironmentManagerInsights,
        "Microsoft.Windows.System.EnvironmentManager.Insights",
        // {fbce41fa-f7bc-538e-11f2-abe1b9d2ab23}
        (0xfbce41fa, 0xf7bc, 0x538e, 0x11, 0xf2, 0xab, 0xe1, 0xb9, 0xd2, 0xab, 0x23));

    DEFINE_COMPLIANT_MEASURES_EVENT_STRING(StringTelemetryEvent, // Event name 
        MICROSOFT_KEYWORD_MEASURES, // Check wil/traceloggingconfig.h for a full list 
        stringvalue/* value to be logged*/);

    DEFINE_COMPLIANT_TELEMETRY_EVENT_PARAM2(ScopeTelemetryEvent, //Event name
        MICROSOFT_KEYWORD_MEASURES, // Privacy data data for events. Check wil/traceloggingconfig.h for a full list
        winrt::Microsoft::Windows::System::implementation::EnvironmentManager::Scope, // Payload data type
        value,
        PCWSTR, message);

    static void LogWithScopeAndMessage(winrt::Microsoft::Windows::System::implementation::EnvironmentManager::Scope const& scope,
        PCWSTR message)
    {
        std::wstring scopeAsString{};

        if (scope == winrt::Microsoft::Windows::System::implementation::EnvironmentManager::Scope::Process)
        {
            scopeAsString = L"Process";
        }
        else if (scope == winrt::Microsoft::Windows::System::implementation::EnvironmentManager::Scope::User)
        {
            scopeAsString = L"User";
        }
        else
        {
            scopeAsString = L"Machine";
        }

        TraceLoggingClassWrite("CustomEvent", TraceLoggingValue(scopeAsString.c_str(), "scope"),
            TraceLoggingValue(message, "message"));
    }

};
