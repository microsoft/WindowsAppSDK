// Copyright (C) Microsoft Corporation. All rights reserved.
#pragma once

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct WinMLAsyncBlock WinMLAsyncBlock;

typedef void (CALLBACK* WinMLAsyncCompletionCallback)(
    _Inout_ WinMLAsyncBlock* async
);

typedef void (CALLBACK* WinMLAsyncProgressCallback)(
    _Inout_ WinMLAsyncBlock* async,
    double progress
);

typedef struct WinMLAsyncBlock
{
    void* context;
    WinMLAsyncCompletionCallback callback;
    WinMLAsyncProgressCallback progress;
} WinMLAsyncBlock;

typedef BOOL (CALLBACK* WinMLStringEnumCallback)(
    _In_z_ const char* value,
    _In_opt_ void* context
);

STDAPI WinMLAsyncGetStatus(
    _In_ WinMLAsyncBlock* async,
    BOOL wait
);

STDAPI WinMLAsyncCancel(
    _Inout_ WinMLAsyncBlock* async
);

STDAPI_(void) WinMLAsyncClose(
    _In_opt_ WinMLAsyncBlock* async
);

#ifdef __cplusplus
}
#endif
