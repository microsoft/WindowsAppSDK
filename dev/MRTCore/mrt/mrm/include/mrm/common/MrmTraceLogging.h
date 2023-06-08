// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <guiddef.h>
#include <WindowsAppRuntimeInsights.h>

#include <windows.h>

#define ENABLE_MRT_IN_MEMORY_LOGGING

#ifdef ENABLE_MRT_IN_MEMORY_LOGGING
void LogErrorInMemory(HRESULT hr, ULONG line, _In_ PCSTR filename, _In_ PCWSTR message);
#define LOG_ERROR_IN_MEMORY(hr, line, filename, message) LogErrorInMemory(hr, line, filename, message);
#else
#define LOG_ERROR_IN_MEMORY(hr, line, filename, message) __noop
#endif

class MrtRuntimeTraceLoggingProvider : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(MrtRuntimeTraceLoggingProvider, "Microsoft.WindowsAppSdk.MrtCore.Runtime",
        // {297d729d-7733-5616-aafc-9a3c8b0d5f22}
        (0x297d729d, 0x7733, 0x5616, 0xaa, 0xfc, 0x9a, 0x3c, 0x8b, 0x0d, 0x5f, 0x22));

    DEFINE_COMPLIANT_MEASURES_EVENT(MrmCreateResourceManager, PDT_ProductAndServicePerformance);

    DEFINE_COMPLIANT_TELEMETRY_EVENT_PARAM3(TelemetryGenericEvent, PDT_ProductAndServicePerformance, PCWSTR, functionName, PCWSTR, message, int, hresult);
    DEFINE_COMPLIANT_TELEMETRY_EVENT_PARAM4(TelemetryGenericEvent, PDT_ProductAndServicePerformance, PCWSTR, functionName, PCWSTR, message1, PCWSTR, message2, int, hresult);
    DEFINE_COMPLIANT_MEASURES_EVENT_PARAM3(MeasureGenericEvent, PDT_ProductAndServicePerformance, PCWSTR, functionName, PCWSTR, message, int, hresult);
    DEFINE_COMPLIANT_MEASURES_EVENT_PARAM4(MeasureGenericEvent, PDT_ProductAndServicePerformance, PCWSTR, functionName, PCWSTR, message1, PCWSTR, message2, int, hresult);
};

// Remove PII from string
inline PCWSTR RemovePiiUserProfileFilename(PCWSTR)
{
    // TODO: Once the feature below is available, this function can be removed.
    // Create a centralized PII scrubber · Issue #1461 (https://github.com/microsoft/WindowsAppSDK/issues/1461)
    return L"";
}
