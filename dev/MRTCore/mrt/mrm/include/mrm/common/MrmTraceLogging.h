// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include <guiddef.h>
#include <WindowsAppSDKInsights.h>

#include <windows.h>

#define ENABLE_MRT_IN_MEMORY_LOGGING

#ifdef ENABLE_MRT_IN_MEMORY_LOGGING
void LogErrorInMemory(HRESULT hr, ULONG line, _In_ PCSTR filename, _In_ PCWSTR message);
#define LOG_ERROR_IN_MEMORY(hr, line, filename, message) LogErrorInMemory(hr, line, filename, message);
#else
#define LOG_ERROR_IN_MEMORY(hr, line, filename, message) __noop
#endif

class MrtRuntimeProvider : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(MrtRuntimeProvider, "Microsoft.Windows.Mrt.Runtime",
        // {19C13211-DEC8-42D5-885A-C4CFA82EA1ED}
        (0x19c13211, 0xdec8, 0x42d5, 0x88, 0x5a, 0xc4, 0xcf, 0xa8, 0x2e, 0xa1, 0xed));

    DEFINE_COMPLIANT_TELEMETRY_EVENT_PARAM3(TelemetryGenericEventParam1, PDT_ProductAndServicePerformance, PCWSTR, functionName, PCWSTR, message, int, hresult);
    DEFINE_COMPLIANT_TELEMETRY_EVENT_PARAM4(TelemetryGenericEventParam2, PDT_ProductAndServicePerformance, PCWSTR, functionName, PCWSTR, message1, PCWSTR, message2, int, hresult);
    DEFINE_COMPLIANT_MEASURES_EVENT_PARAM3(MeasureGenericEventParam1, PDT_ProductAndServicePerformance, PCWSTR, functionName, PCWSTR, message, int, hresult);
    DEFINE_COMPLIANT_MEASURES_EVENT_PARAM4(MeasureGenericEventParam2, PDT_ProductAndServicePerformance, PCWSTR, functionName, PCWSTR, message1, PCWSTR, message2, int, hresult);

    DEFINE_COMPLIANT_MEASURES_EVENT_PARAM3(MeasureUnableToOpenOverlayFile, PDT_ProductAndServicePerformance, PCWSTR, functionName, PCWSTR, overlayFileName, int, hresult);

    DEFINE_COMPLIANT_TELEMETRY_EVENT_PARAM3(PriMergeInfo, PDT_ProductAndServicePerformance, DWORD, mergeState, PCWSTR, mergeInfo, int, hresult);
    DEFINE_COMPLIANT_MEASURES_EVENT_PARAM3(PriMergeError, PDT_ProductAndServicePerformance, DWORD, mergeState, PCWSTR, mergeInfo, int, hresult);

};

// case insensitive prefix match of "*:\users"
__inline PCWSTR RemoveUsernameFromPath(_In_ PCWSTR filePath)
{
    if ((filePath != NULL) &&
        (filePath[0] != 0) &&
        (filePath[1] == L':') &&
        (filePath[2] == L'\\') &&
        ((filePath[3] == L'u') || (filePath[3] == L'U')) && 
        ((filePath[4] == L's') || (filePath[4] == L'S')) &&
        ((filePath[5] == L'e') || (filePath[5] == L'E')) &&
        ((filePath[6] == L'r') || (filePath[6] == L'R')) &&
        ((filePath[7] == L's') || (filePath[7] == L'S')) &&
        (filePath[8] == L'\\'))
    {
        PCWSTR logPath = wcsstr(&filePath[9], L"\\");
        return (logPath != NULL) ? logPath : L"";
    }
    return filePath;
}
