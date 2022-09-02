// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "stdafx.h"
#include <mrm\common\mrmtracelogging.h>

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
