// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"
#include <mrm/platform/MrmWnf.h>
#include <mrm/platform/MrmWnfHelpers.h>

#ifndef DOWNLEVEL_PRIOR_TO_WIN8

void MrmWnf_PublishStateData(_In_ WNF_STATE_NAME stateName, _In_ size_t payloadSizeInChars, _In_ PCWSTR format, ...)
{
    WCHAR myBuffer[MrmWnf_DefaultMaxPayloadSizeInChars] = {};
    WCHAR* buffer =
        (payloadSizeInChars <= MrmWnf_DefaultMaxPayloadSizeInChars) ? &myBuffer[0] : _DefArray_AllocZeroed(WCHAR, payloadSizeInChars);

    if (buffer != nullptr)
    {
        va_list argList;
        va_start(argList, format);
        if (SUCCEEDED(StringCchVPrintf(buffer, payloadSizeInChars, format, argList)))
        {
            RtlPublishWnfStateData(stateName, nullptr, buffer, (static_cast<ULONG>(payloadSizeInChars) * sizeof(WCHAR)), nullptr);
        }
        va_end(argList);

        if (buffer != myBuffer)
        {
            _DefFree(buffer);
        }
    }
}

#endif

UINT64
MrmWnf_GetNow()
{
    FILETIME ft;
    ULARGE_INTEGER ull;
    GetSystemTimeAsFileTime(&ft);
    ull.LowPart = ft.dwLowDateTime;
    ull.HighPart = ft.dwHighDateTime;
    return ull.QuadPart;
}