// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "SampleFlatC.h"
#include <string>

struct MyRealType
{
    std::wstring theString;
};

STDAPI SampleFlatApiCreate(
    _Outptr_ HSAMPLEFLATAPI* sampleFlat) try
{
    auto real = std::make_unique<MyRealType>();
    real->theString = L"kittens";
    *sampleFlat = reinterpret_cast<HSAMPLEFLATAPI>(real.release());
    return S_OK;
}
CATCH_RETURN();

STDAPI_(VOID) CloseSampleFlatApi(HSAMPLEFLATAPI sampleFlat) try
{
    auto real = std::unique_ptr<MyRealType>(reinterpret_cast<MyRealType*>(sampleFlat));
    // Do something with 'real', the destructor will clean it up
}
CATCH_LOG();

STDAPI GetSampleFlatApiString(
    _In_ HSAMPLEFLATAPI sampleFlat,
    _Outptr_ LPWSTR* theString) try
{
    auto real = reinterpret_cast<MyRealType*>(sampleFlat);
    auto cloned = wil::make_cotaskmem_string(real->theString.data());
    *theString = cloned.release();
    return S_OK;
}
CATCH_RETURN();
