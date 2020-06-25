// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include <windows.h>

DECLARE_HANDLE(HSAMPLEFLATAPI);

STDAPI SampleFlatApiCreate(
    _In_ LPCWSTR theString,
    _Outptr_ HSAMPLEFLATAPI* sampleFlat);

STDAPI_(VOID) CloseSampleFlatApi(
    HSAMPLEFLATAPI sampleFlat);

STDAPI GetSampleFlatApiString(
    _In_ HSAMPLEFLATAPI sampleFlat,
    _Outptr_ LPWSTR* theString);
