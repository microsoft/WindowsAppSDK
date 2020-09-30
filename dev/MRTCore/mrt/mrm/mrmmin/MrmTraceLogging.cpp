// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"
#include <mrm\common\mrmtracelogging.h>

#ifndef DOWNLEVEL_PRIOR_TO_WIN8
#include <telemetry\MicrosoftTelemetryAssert.h>
#endif

#ifdef ENABLE_MRT_IN_MEMORY_LOGGING
class MrtLoggingData
{
public:
    MrtLoggingData() : m_hr(0), m_line(0), m_filename(nullptr), m_message(nullptr) { _DefInitializeSRWLock(&m_lock); }

    ~MrtLoggingData()
    {
        _DefAcquireSRWLockExclusive(&m_lock);
        Reset();
        _DefReleaseSRWLockExclusive(&m_lock);
    }

    void Set(HRESULT hr, ULONG line, _In_opt_ PCSTR filename, _In_opt_ PCWSTR message)
    {
        _DefAcquireSRWLockExclusive(&m_lock);

        Reset();

        m_hr = hr;
        m_line = line;

        if (filename != nullptr)
        {
            size_t filenameLen = strlen(filename);
            m_filename = _DefArray_Alloc(CHAR, filenameLen + 1);
            if (m_filename != nullptr)
            {
                StringCchCopyA(m_filename, filenameLen + 1, filename);
            }
        }

        if (message != nullptr)
        {
            size_t messageLen = wcslen(message);
            m_message = _DefArray_Alloc(WCHAR, messageLen + 1);
            if (m_message != nullptr)
            {
                StringCchCopyW(m_message, messageLen + 1, message);
            }
        }

        _DefReleaseSRWLockExclusive(&m_lock);
    }

private:
    void Reset()
    {
        m_hr = 0;
        m_line = 0;
        if (m_filename != nullptr)
        {
            _DefFree(m_filename);
            m_filename = nullptr;
        }

        if (m_message != nullptr)
        {
            _DefFree(m_message);
            m_message = nullptr;
        }
    }

    HRESULT m_hr;
    ULONG m_line;
    CHAR* m_filename;
    WCHAR* m_message;
    _DEF_SRWLOCK m_lock;
};

static const LONG c_logSize = 20;
static LONG s_logIndex = 0;
static MrtLoggingData s_errorLog[c_logSize];

void LogErrorInMemory(HRESULT hr, ULONG line, _In_opt_ PCSTR filename, _In_opt_ PCWSTR message)
{
    // Thread safety is not a goal. Only best effort is made
    // The log will start from 1. But that's ok.
    LONG index = InterlockedIncrement(&s_logIndex);

    if (index < 0)
    {
        // Overflow is unlikely. But in case it does, don't crash
        index = 0;
        s_logIndex = 0;
    }

    s_errorLog[index % c_logSize].Set(hr, line, filename, message);
}
#else
void LogErrorInMemory(HRESULT, ULONG, _In_ PCSTR, _In_ PCWSTR) {}
#endif

#ifndef DOWNLEVEL_PRIOR_TO_WIN8
// {19C13211-DEC8-42D5-885A-C4CFA82EA1ED}
TRACELOGGING_DEFINE_PROVIDER(
    MrtRuntimeProvider,
    "Microsoft.Windows.Mrt.Runtime",
    (0x19c13211, 0xdec8, 0x42d5, 0x88, 0x5a, 0xc4, 0xcf, 0xa8, 0x2e, 0xa1, 0xed),
    TraceLoggingOptionMicrosoftTelemetry());

// event name cannot be set dynamically, a GenericEvent use a field EventName to indicate the event name.
void MrtRuntimeTelemetry_GenericEventParam1(_In_ PCWSTR eventName, _In_ PCWSTR msg1, _In_ HRESULT hr)
{
    TraceLoggingWrite(
        MrtRuntimeProvider,
        "GenericEvent",
        TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
        TraceLoggingWideString(eventName, "EventName"),
        TraceLoggingInt64(hr, "HRESULT"),
        TraceLoggingWideString(msg1, "Message_1"),
        TraceLoggingKeyword(MICROSOFT_KEYWORD_TELEMETRY));
}

void MrtRuntimeTelemetry_GenericEventParam2(_In_ PCWSTR eventName, _In_ PCWSTR msg1, _In_ PCWSTR msg2, _In_ HRESULT hr)
{
    TraceLoggingWrite(
        MrtRuntimeProvider,
        "GenericEvent",
        TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
        TraceLoggingWideString(eventName, "EventName"),
        TraceLoggingInt64(hr, "HRESULT"),
        TraceLoggingWideString(msg1, "Message_1"),
        TraceLoggingWideString(msg2, "Message_2"),
        TraceLoggingKeyword(MICROSOFT_KEYWORD_TELEMETRY));
}

void MrtRuntimeMeasure_GenericEventParam1(_In_ PCWSTR eventName, _In_ PCWSTR msg1, _In_ HRESULT hr)
{
    LOG_ERROR_IN_MEMORY(hr, 1, nullptr, msg1);
    TraceLoggingWrite(
        MrtRuntimeProvider,
        "GenericEvent",
        TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
        TraceLoggingWideString(eventName, "EventName"),
        TraceLoggingInt64(hr, "HRESULT"),
        TraceLoggingWideString(msg1, "Message_1"),
        TraceLoggingKeyword(MICROSOFT_KEYWORD_MEASURES));
}

void MrtRuntimeMeasure_GenericEventParam2(_In_ PCWSTR eventName, _In_ PCWSTR msg1, _In_ PCWSTR msg2, _In_ HRESULT hr)
{
    LOG_ERROR_IN_MEMORY(hr, 2, nullptr, msg2);
    TraceLoggingWrite(
        MrtRuntimeProvider,
        "GenericEvent",
        TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
        TraceLoggingWideString(eventName, "EventName"),
        TraceLoggingInt64(hr, "HRESULT"),
        TraceLoggingWideString(msg1, "Message_1"),
        TraceLoggingWideString(msg2, "Message_2"),
        TraceLoggingKeyword(MICROSOFT_KEYWORD_MEASURES));
}

void MrtRuntimeMeasure_UnableToOpenOverlayFile(_In_ PCWSTR function, _In_ PCWSTR overlayFileName, _In_ HRESULT result)
{
    TraceLoggingWrite(
        MrtRuntimeProvider,
        "UnableToOpenOverlayFile",
        TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
        TraceLoggingWideString(function, "Function"),
        TraceLoggingWideString(overlayFileName, "OverlayFileName"),
        TraceLoggingInt64(result, "HRESULT"),
        TraceLoggingKeyword(MICROSOFT_KEYWORD_MEASURES));

    // Auto bug will be created with telemetry ASSERT. The bug will be assigned to overlay owner.
    MICROSOFT_TELEMETRY_ASSERT(FALSE);
}

void MrtRuntimeTelemetry_PriMerge(_In_ DWORD mergeState, _In_ PCWSTR mergeInfo, _In_ HRESULT result)
{
    TraceLoggingWrite(
        MrtRuntimeProvider,
        "PriMergeInfo",
        TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
        TraceLoggingInt32(mergeState, "MergeState"),
        TraceLoggingWideString(mergeInfo, "MergeInfo"),
        TraceLoggingInt64(result, "HRESULT"),
        TraceLoggingKeyword(MICROSOFT_KEYWORD_TELEMETRY));
}

void MrtRuntimeMeasure_PriMerge(_In_ DWORD mergeState, _In_ PCWSTR mergeInfo, _In_ HRESULT result)
{
    TraceLoggingWrite(
        MrtRuntimeProvider,
        "PriMergeError",
        TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance),
        TraceLoggingInt32(mergeState, "MergeState"),
        TraceLoggingWideString(mergeInfo, "MergeInfo"),
        TraceLoggingInt64(result, "HRESULT"),
        TraceLoggingKeyword(MICROSOFT_KEYWORD_MEASURES));
}

#else

void MrtRuntimeTelemetry_GenericEventParam1(_In_ PCWSTR, _In_ PCWSTR, _In_ HRESULT) {}

void MrtRuntimeTelemetry_GenericEventParam2(_In_ PCWSTR, _In_ PCWSTR, _In_ PCWSTR, _In_ HRESULT) {}

void MrtRuntimeMeasure_GenericEventParam1(_In_ PCWSTR, _In_ PCWSTR, _In_ HRESULT) {}

void MrtRuntimeMeasure_GenericEventParam2(_In_ PCWSTR, _In_ PCWSTR, _In_ PCWSTR, _In_ HRESULT) {}

void MrtRuntimeMeasure_UnableToOpenOverlayFile(_In_ PCWSTR, _In_ PCWSTR, _In_ HRESULT) {}

void MrtRuntimeTelemetry_PriMerge(_In_ DWORD, _In_ PCWSTR, _In_ HRESULT) {}

void MrtRuntimeMeasure_PriMerge(_In_ DWORD, _In_ PCWSTR, _In_ HRESULT) {}

#endif
