// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#include <pch.h>
#include "Logging.h"

void LogDebugMessage(PCSTR formatString, ...)
{
    if (IsDebuggerPresent())
    {
        char debugMsg[1000] = {};

        va_list args;
        va_start(args, formatString);

        HRESULT hr = StringCchVPrintfA(
            debugMsg,
            ARRAYSIZE(debugMsg),
            formatString,
            args);
        if (FAILED(hr) && (hr != STRSAFE_E_INSUFFICIENT_BUFFER))
        {
            OutputDebugStringA("Cannot construct debug message. StringCchVPrintfA() failed. Input format string: ");
            OutputDebugStringA(formatString);
            OutputDebugStringA("\n");
        }
        else
        {
            OutputDebugStringA(debugMsg);
            OutputDebugStringA("\n");
        }
    }
}