// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "TestSections.h"

namespace UnitTests
{

class TestUtils
{
public:
    static bool TryVerifyRemap(__in PCWSTR pVarName, __inout const Microsoft::Resources::RemapUInt16* pRemap);

    _Success_(return == true) static bool ParsePlatformString(_In_ PCWSTR pPlatformString, _Out_ MrmPlatformVersionInternal* pPlatformOut);

    static MrmPlatformVersionInternal GetPlatformFromOptionalTestVar(_In_ PCWSTR pTestVarName);

    _Success_(return ) static bool GetSectionTypeIdFromOptionalTestVar(
        _In_ PCWSTR pTestVarName,
        _Out_ DEFFILE_SECTION_TYPEID* pSectionTypeResult);

    _Success_(return == true) static bool ParseDefResult(_In_ PCWSTR resultString, _Out_ DEFRESULT* result, _Out_opt_ bool* returnValue);

    static void ValidateReturnAndStatus(_In_ bool returnValue, _In_ PCWSTR expectedResult, _In_ HRESULT hr);

    static void TryGetExpectedResult(_In_ PCWSTR varName, _Out_ DEFRESULT* result, _Out_opt_ bool* returnValue);
};

} // namespace UnitTests
