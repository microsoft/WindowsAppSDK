// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"
#include "Helpers.h"
#include <mrm/build/AIDict.h>
#include "TestUtils.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;
using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTests
{

bool TestUtils::TryVerifyRemap(_In_ PCWSTR pVarName, _Inout_ const RemapUInt16* pRemap)
{
    String tmp;
    String varValue;

    if (SUCCEEDED(TestData::TryGetValue(pVarName, varValue)))
    {
        TestStringArray expectedStrings;
        int expectedValue;
        UINT16 gotValue;

        if (!expectedStrings.InitFromList(varValue))
        {
            Log::Warning(tmp.Format(L"[ Couldn't parse \"%s\" ]", pVarName));
            return false;
        }

        for (UINT16 i = 0; i < expectedStrings.GetNumStrings(); i++)
        {
            if (!expectedStrings.TryGetStringAsInt(i, &expectedValue))
            {
                Log::Warning(tmp.Format(L"[ \"%s\" malformed - value %d ignored ]", pVarName, i));
                continue;
            }
            pRemap->TryGetMapping(i, &gotValue);
            VERIFY(expectedValue == gotValue);
        }
        return true;
    }

    Log::Comment(tmp.Format(L"[ \"%s\" not defined ]", pVarName));
    return false;
}

_Success_(return == true) bool TestUtils::ParsePlatformString(_In_ PCWSTR pPlatformString, _Out_ MrmPlatformVersionInternal* pPlatformOut)
{
    String tmp;
    TestStringArray platformDef;
    if (pPlatformOut == nullptr)
    {
        return false;
    }
    if (DefString_ICompare(pPlatformString, L"Default") == Def_Equal)
    {
        *pPlatformOut = MrmPlatformVersionInternal::DefaultPlatformVersion;
    }
    else if (DefString_ICompare(pPlatformString, L"Core") == Def_Equal)
    {
        *pPlatformOut = MrmPlatformVersionInternal::WindowsCore;
    }
    else if (
        (DefString_ICompare(pPlatformString, L"WindowsClient8") == Def_Equal) ||
        (DefString_ICompare(pPlatformString, L"Client8") == Def_Equal))
    {
        *pPlatformOut = MrmPlatformVersionInternal::WindowsClient8;
    }
    else if (
        (DefString_ICompare(pPlatformString, L"WindowsClientBlue") == Def_Equal) ||
        (DefString_ICompare(pPlatformString, L"ClientBlue") == Def_Equal))
    {
        *pPlatformOut = MrmPlatformVersionInternal::WindowsClientBlue;
    }
    else if (
        (DefString_ICompare(pPlatformString, L"WindowsPhoneBlue") == Def_Equal) ||
        (DefString_ICompare(pPlatformString, L"PhoneBlue") == Def_Equal))
    {
        *pPlatformOut = MrmPlatformVersionInternal::WindowsPhoneBlue;
    }
    else if (DefString_ICompare(pPlatformString, L"FutureIncompatible") == Def_Equal)
    {
        *pPlatformOut = MrmPlatformVersionInternal::TestIncompatiblePlatformVersion;
    }
    else if (DefString_ICompare(pPlatformString, L"FutureCore") == Def_Equal)
    {
        *pPlatformOut = MrmPlatformVersionInternal::TestFutureCoreVersion;
    }
    else if (DefString_ICompare(pPlatformString, L"FutureCore2") == Def_Equal)
    {
        *pPlatformOut = MrmPlatformVersionInternal::TestFutureCoreVersion2;
    }
    else
    {
        Log::Warning(tmp.Format(L"[ Unrecognized platform string \"%s\" ]", pPlatformString));
        return false;
    }

    return true;
}

MrmPlatformVersionInternal TestUtils::GetPlatformFromOptionalTestVar(_In_ PCWSTR testVarName)
{
    String tmp;

    String platformString;
    MrmPlatformVersionInternal platform = MrmPlatformVersionInternal::DefaultPlatformVersion;
    if (SUCCEEDED(TestData::TryGetValue(testVarName, platformString)))
    {
        if (TestUtils::ParsePlatformString((PCWSTR)platformString, &platform))
        {
            Log::Comment(tmp.Format(L"[ Using platform '%s' for '%s' ]", (PCWSTR)platformString, testVarName));
        }
        else
        {
            Log::Warning(tmp.Format(L"[ Unknown platform '%s' for %s, using default ]", (PCWSTR)platformString, testVarName));
        }
    }
    else
    {
        Log::Comment(tmp.Format(L"[ %s not defined. Using default platform. ]", testVarName));
    }

    return platform;
}

_Success_(
    return ) bool TestUtils::GetSectionTypeIdFromOptionalTestVar(_In_ PCWSTR pTestVarName, _Out_ DEFFILE_SECTION_TYPEID* pSectionTypeResult)
{
    bool succeeded = false;
    String tmp;
    String sectionTypeString;
    DEFFILE_SECTION_TYPEID result;

    if (SUCCEEDED(TestData::TryGetValue(pTestVarName, sectionTypeString)))
    {
        if (sectionTypeString.GetLength() == sizeof(result.bType))
        {
            for (size_t i = 0; (i < sizeof(result.bType)); i++)
            {
                result.bType[i] = static_cast<BYTE>(sectionTypeString[i]);
            }

            *pSectionTypeResult = result;
            succeeded = true;
        }
        else
        {
            Log::Warning(tmp.Format(L"[ Malformed section type id \"%s\" for %s ]", static_cast<PCWSTR>(sectionTypeString), pTestVarName));
        }
    }
    else
    {
        Log::Comment(tmp.Format(L"[ %s not specified ]", pTestVarName));
    }

    return succeeded;
}

_Success_(return == true)
bool TestUtils::ParseDefResult(_In_ PCWSTR resultString, _Out_ DEFRESULT* result, _Out_opt_ bool* returnValue)
{
    bool expectedReturn = false;
    UINT32 value;

    if (DefString_ICompare(resultString, L"success") == Def_Equal)
    {
        expectedReturn = true;
        *result = ERROR_SUCCESS;
    }
    else if (DefString_ICompare(resultString, L"fail") == Def_Equal)
    {
        *result = ERROR_SUCCESS;
    }
    else if (DefString_ICompare(resultString, L"INVALID_QUALIFIER_NAME") == Def_Equal)
    {
        *result = E_DEF_INVALID_QUALIFIER_NAME;
    }
    else if (DefString_ICompare(resultString, L"INVALID_OPERATOR") == Def_Equal)
    {
        *result = E_DEF_INVALID_CONDITION_OPERATOR;
    }
    else if (DefString_ICompare(resultString, L"INVALID_QUALIFIER_VALUE") == Def_Equal)
    {
        *result = E_DEF_INVALID_ATTRIBUTE_VALUE;
    }
    else if (DefString_ICompare(resultString, L"LINK_TO_LINKED_RESOURCE") == Def_Equal)
    {
        *result = E_DEFFILE_BUILD_LINK_TO_LINKED_RESOURCE;
    }
    else if (swscanf_s(resultString, L"%x", &value) == 1)
    {
        *result = value;
        expectedReturn = (value == 0);
    }
    else
    {
        return false;
    }

    if (returnValue != nullptr)
    {
        *returnValue = expectedReturn;
    }

    return true;
}

void TestUtils::ValidateReturnAndStatus(_In_ bool returnValue, _In_ PCWSTR expectedResult, _In_ HRESULT hr)
{
    String tmp;
    DEFRESULT parsedResult = ERROR_SUCCESS;
    bool parsedReturn = true;

    if (DefString_ICompare(expectedResult, L"ignore") == Def_Equal)
    {
        Log::Comment(tmp.Format(L"[ Result %s - 0x%x ignored ]", (returnValue ? L"true" : L"false"), hr));
    }
    else if (!ParseDefResult(expectedResult, &parsedResult, &parsedReturn))
    {
        Log::Warning(tmp.Format(L"[ Unknown expectedResult %s - ignored]", expectedResult));
    }
    else
    {
        VERIFY_ARE_EQUAL(parsedResult, hr);
        VERIFY_ARE_EQUAL(returnValue, parsedReturn);
    }
}

void TestUtils::TryGetExpectedResult(_In_ PCWSTR varName, _Out_ DEFRESULT* result, _Out_opt_ bool* returnValue)
{
    String tmp;
    String expectedResultString;
    if (SUCCEEDED(TestData::TryGetValue(varName, expectedResultString)))
    {
        if (TestUtils::ParseDefResult((PCWSTR)expectedResultString, result, returnValue))
        {
            Log::Comment(tmp.Format(
                L"[ %s = {0x%x, %s} ]", varName, *result, ((returnValue != nullptr) ? ((*returnValue) ? L"true" : L"false") : L"ignored")));
        }
        else
        {
            Log::Warning(tmp.Format(L"Unknown DEFRESULT \"%s\" in %s.", (PCWSTR)expectedResultString, varName));
        }
    }
}

} // namespace UnitTests