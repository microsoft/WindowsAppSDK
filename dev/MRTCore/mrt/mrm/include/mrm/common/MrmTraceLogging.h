// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#ifndef MRMTRACELOGGING_H
#define MRMTRACELOGGING_H

#include <guiddef.h>
#include <TraceLoggingProvider.h>

#ifndef DOWNLEVEL_PRIOR_TO_WIN8
#include <telemetry\MicrosoftTelemetry.h>
#include <telemetry\MicrosoftTelemetryPrivacy.h>
#endif

#include <windows.h>

#define ENABLE_MRT_IN_MEMORY_LOGGING

#ifdef ENABLE_MRT_IN_MEMORY_LOGGING
void LogErrorInMemory(HRESULT hr, ULONG line, _In_ PCSTR filename, _In_ PCWSTR message);
#define LOG_ERROR_IN_MEMORY(hr, line, filename, message) LogErrorInMemory(hr, line, filename, message);
#else
#define LOG_ERROR_IN_MEMORY(hr, line, filename, message) __noop
#endif

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

#ifdef __cplusplus
extern "C"
{
#endif

    TRACELOGGING_DECLARE_PROVIDER(MrtRuntimeProvider);

    void MrtRuntimeTelemetry_GenericEventParam1(_In_ PCWSTR eventName, _In_ PCWSTR msg1, _In_ HRESULT hr);
    void MrtRuntimeTelemetry_GenericEventParam2(_In_ PCWSTR eventName, _In_ PCWSTR msg1, _In_ PCWSTR msg2, _In_ HRESULT hr);
    void MrtRuntimeMeasure_GenericEventParam1(_In_ PCWSTR eventName, _In_ PCWSTR msg1, _In_ HRESULT hr);
    void MrtRuntimeMeasure_GenericEventParam2(_In_ PCWSTR eventName, _In_ PCWSTR msg1, _In_ PCWSTR msg2, _In_ HRESULT hr);

    void MrtRuntimeMeasure_UnableToOpenOverlayFile(_In_ PCWSTR function, _In_ PCWSTR overlayFileName, _In_ HRESULT result);

    void MrtRuntimeTelemetry_PriMerge(_In_ DWORD mergeState, _In_ PCWSTR mergeInfo, _In_ HRESULT result);
    void MrtRuntimeMeasure_PriMerge(_In_ DWORD mergeState, _In_ PCWSTR mergeInfo, _In_ HRESULT result);

#ifdef __cplusplus
}
#endif

#endif // ! MRMTRACELOGGING_H
