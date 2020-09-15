// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

#ifndef DOWNLEVEL_PRIOR_TO_WIN8

// workaround header issues
#ifndef _NTEXAPI_

typedef struct _WNF_STATE_NAME
{
    ULONG Data[2];
} WNF_STATE_NAME;

#endif // ifndef _NTEXAPI_

#include <wnfnamesp.h>

void MrmWnf_PublishStateData(_In_ WNF_STATE_NAME stateName, _In_ size_t payloadSizeInChars, _In_ PCWSTR format, ...);

#endif

UINT64 MrmWnf_GetNow();
