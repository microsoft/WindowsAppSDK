// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

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

    DEFINE_EVENT_METHOD(LogCreateForProcess)() {
        TraceLoggingClassWriteMeasure(
            "LogCreateForProcess",
            TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
            _GENERIC_PARTB_FIELDS_ENABLED);
    }

    DEFINE_EVENT_METHOD(LogCreateForUser)() {
        TraceLoggingClassWriteMeasure(
            "LogCreateForUser",
            TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
            _GENERIC_PARTB_FIELDS_ENABLED);
    }

    DEFINE_EVENT_METHOD(LogCreateForMachine)() {
        TraceLoggingClassWriteMeasure(
            "LogCreateForMachine",
            TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
            _GENERIC_PARTB_FIELDS_ENABLED);
    }

    DEFINE_EVENT_METHOD(LogGetEnvironmentVariables)(winrt::Microsoft::Windows::System::implementation::EnvironmentManager::Scope scope) {
        TraceLoggingClassWriteMeasure(
            "LogGetEnvironmentVariables",
            TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingWideString(ScopeToString(scope), "Scope"));
    }

    DEFINE_EVENT_METHOD(LogGetEnvironmentVariable)(winrt::Microsoft::Windows::System::implementation::EnvironmentManager::Scope scope) {
        TraceLoggingClassWriteMeasure(
            "LogGetEnvironmentVariable",
            TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingWideString(ScopeToString(scope), "Scope"));
    }

    DEFINE_EVENT_METHOD(LogSetEnvironmentVariable)(winrt::Microsoft::Windows::System::implementation::EnvironmentManager::Scope scope) {
        TraceLoggingClassWriteMeasure(
            "LogSetEnvironmentVariables",
            TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingWideString(ScopeToString(scope), "Scope"));
    }

    DEFINE_EVENT_METHOD(LogAppendToPath)(winrt::Microsoft::Windows::System::implementation::EnvironmentManager::Scope scope) {
        TraceLoggingClassWriteMeasure(
            "LogAppendToPath",
            TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingWideString(ScopeToString(scope), "Scope"));
    }

    DEFINE_EVENT_METHOD(LogRemoveFromPath)(winrt::Microsoft::Windows::System::implementation::EnvironmentManager::Scope scope) {
        TraceLoggingClassWriteMeasure(
            "LogRemoveFromPath",
            TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingWideString(ScopeToString(scope), "Scope"));
    }

    DEFINE_EVENT_METHOD(LogAddExecutableFileExtension)(winrt::Microsoft::Windows::System::implementation::EnvironmentManager::Scope scope) {
        TraceLoggingClassWriteMeasure(
            "LogAddExecutableFileExtension",
            TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingWideString(ScopeToString(scope), "Scope"));
    }

    DEFINE_EVENT_METHOD(LogRemoveExecutableFileExtension)(winrt::Microsoft::Windows::System::implementation::EnvironmentManager::Scope scope) {
        TraceLoggingClassWriteMeasure(
            "LogRemoveExecutableFileExtension",
            TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
            _GENERIC_PARTB_FIELDS_ENABLED,
            TraceLoggingWideString(ScopeToString(scope), "Scope"));
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
