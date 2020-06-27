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

// Include <wil/resource.h> from the NuGet package Microsoft.Windows.ImplementationLibrary
// before this file to have this handy lifecycle helper for C++ light up

#ifdef __WIL_RESOURCE

namespace wil
{
    using unique_sampleflat_handle = unique_any<HSAMPLEFLATAPI, decltype(CloseSampleFlatApi), &::CloseSampleFlatApi>;
}

#endif
