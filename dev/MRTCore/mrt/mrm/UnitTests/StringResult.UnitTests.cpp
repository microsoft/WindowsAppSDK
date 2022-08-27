// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <windows.h>
#include <WexTestClass.h>

#include "Helpers.h"

#define CHECK_BUFFER(pSelf, cchSelf, aGoal) \
    VERIFY_ARE_EQUAL(Def_Equal, DefBlob_Compare((pSelf), (aGoal), (cchSelf) * sizeof(wchar_t))); \
    VERIFY_ARE_EQUAL(wcslen(aGoal) + 1, (size_t)(cchSelf))

#define CHECK_STRINGRESULT_BUF_EMPTY(pSelf) \
    VERIFY_IS_NULL((pSelf)->GetStringResult()->pBuf); \
    VERIFY((pSelf)->GetStringResult()->cchBuf == 0)

#define CHECK_STRINGRESULT_COMPLETELY_EMPTY(pSelf) \
    VERIFY((pSelf)->GetType() == DefResultType_None); \
    CHECK_STRINGRESULT_BUF_EMPTY(pSelf); \
    VERIFY_IS_NULL((pSelf)->GetStringResult()->pRef)

#define CHECK_STRINGRESULT_EMPTY(pSelf) \
    VERIFY((pSelf)->GetType() == DefResultType_None); \
    VERIFY_IS_NULL((pSelf)->GetStringResult()->pRef)

#define CHECK_STRINGRESULT_REF(pSelf, aStuff) \
    VERIFY((pSelf)->GetType() == DefResultType_Reference); \
    VERIFY_ARE_EQUAL((pSelf)->GetStringResult()->pRef, static_cast<PCWSTR>(aStuff))

#define CHECK_STRINGRESULT_BUF(pSelf, aStuff) \
    VERIFY((pSelf)->GetType() == DefResultType_Buffer); \
    CHECK_BUFFER((pSelf)->GetStringResult()->pBuf, (pSelf)->GetStringResult()->cchBuf, (aStuff)); \
    VERIFY_ARE_EQUAL(static_cast<PCWSTR>((pSelf)->GetStringResult()->pBuf), (pSelf)->GetStringResult()->pRef)

using namespace Microsoft::Resources;

namespace UnitTests
{

struct StringResult_Struct
{

    StringResult_Struct()
    {
        shortStr = L"Bye!";
        medStr = L"Hello!";
        concatStr = L" What's Up?";
        longStr = L"Hello! What's Up?";
        endStr = longStr;
        origStr = medStr;
        nullStr = NULL;

        shortLen = wcslen(shortStr);
        medLen = wcslen(medStr);
        longLen = wcslen(longStr);
        origLen = medLen;
    }

    ~StringResult_Struct() {}

    PCWSTR origRef;
    PWSTR shortStr, medStr, longStr, origStr, nullStr;
    size_t shortLen, medLen, longLen, origLen;

    PCWSTR concatStr, endStr;
};

class StringResult_Reference : public WEX::TestClass<StringResult_Reference>, public StringResult_Struct
{
    TEST_CLASS(StringResult_Reference);

    TEST_METHOD(New);
    TEST_METHOD(GetRef);
    TEST_METHOD(GetWritableRef);
    TEST_METHOD(SetRef);
    TEST_METHOD(SetBuf);
    TEST_METHOD(AcquireAndReleaseBuf);
    TEST_METHOD(AcquireBufNull);
    TEST_METHOD(GetLengthAndSize);
    TEST_METHOD(Compare);
    TEST_METHOD(Concat);
    TEST_METHOD(Truncate);
    TEST_METHOD(Copy);
    TEST_METHOD(InvalidTests);
};

void StringResult_Reference::New(void)
{
    StringResult* pResult;

    VERIFY_SUCCEEDED(StringResult::CreateInstance(NULL, DefResultType_Reference, &pResult));
    VERIFY(pResult != NULL);
    CHECK_STRINGRESULT_EMPTY(pResult);

    delete pResult;

    VERIFY_SUCCEEDED(StringResult::CreateInstance(medStr, DefResultType_Reference, &pResult));
    VERIFY(pResult != NULL);
    CHECK_STRINGRESULT_REF(pResult, medStr);
    CHECK_STRINGRESULT_BUF_EMPTY(pResult);

    delete pResult;

    VERIFY_SUCCEEDED(StringResult::CreateInstance(longStr, &pResult));
    VERIFY(pResult != NULL);
    CHECK_STRINGRESULT_REF(pResult, longStr);
    CHECK_STRINGRESULT_BUF_EMPTY(pResult);

    delete pResult;

    pResult = new StringResult();
    VERIFY(pResult != NULL);
    CHECK_STRINGRESULT_EMPTY(pResult);

    delete pResult;
}

void StringResult_Reference::GetRef(void)
{
    StringResult result;
    VERIFY_SUCCEEDED(result.Init(medStr));

    CHECK_STRINGRESULT_REF(&result, medStr);

    VERIFY(result.GetRef() == medStr);
}

void StringResult_Reference::GetWritableRef(void)
{
    StringResult result;
    VERIFY_SUCCEEDED(result.Init(medStr));
    PWSTR pRef;
    size_t cchRef;

    CHECK_STRINGRESULT_REF(&result, medStr);

    VERIFY_SUCCEEDED(result.GetWritableRef(&pRef, &cchRef));
    VERIFY(pRef != NULL);
    CHECK_STRINGRESULT_BUF(&result, medStr);
    VERIFY(pRef != medStr);
    CHECK_BUFFER(pRef, cchRef, medStr);
}

void StringResult_Reference::SetRef(void)
{
    StringResult result;

    CHECK_STRINGRESULT_EMPTY(&result);
    VERIFY(result.GetRef() == NULL);

    VERIFY_SUCCEEDED(result.SetRef(shortStr));
    CHECK_STRINGRESULT_REF(&result, shortStr);
    VERIFY(result.GetRef() == shortStr);
}

void StringResult_Reference::SetBuf(void)
{
    StringResult result;
    VERIFY_SUCCEEDED(result.Init(shortStr));

    CHECK_STRINGRESULT_REF(&result, shortStr);

    VERIFY_SUCCEEDED(result.SetCopy(medStr));
    CHECK_STRINGRESULT_BUF(&result, medStr);
    VERIFY(result.GetStringResult()->pRef != medStr);

    VERIFY_SUCCEEDED(result.SetCopy(NULL));
    CHECK_STRINGRESULT_EMPTY(&result);
}

void StringResult_Reference::AcquireAndReleaseBuf(void)
{
    PWSTR pStr = L"The new pStr";
    size_t cchStr = _countof(L"The new pStr");

    PWSTR pStrOut = NULL;
    size_t cchStrOut = 0;

    StringResult result;
    VERIFY_SUCCEEDED(result.Init(longStr));

    CHECK_STRINGRESULT_REF(&result, longStr);

    VERIFY_SUCCEEDED(result.SetContents(pStr, cchStr));
    CHECK_STRINGRESULT_BUF(&result, pStr);
    VERIFY(result.GetStringResult()->pRef == pStr);
    VERIFY(result.GetStringResult()->cchBuf == cchStr);

    VERIFY_SUCCEEDED(result.ReleaseContents(&pStrOut, &cchStrOut));
    CHECK_STRINGRESULT_EMPTY(&result);
    CHECK_STRINGRESULT_BUF_EMPTY(&result);
    VERIFY(pStrOut == pStr);
    VERIFY(cchStrOut == cchStr);
}

void StringResult_Reference::AcquireBufNull(void)
{
    StringResult result;
    VERIFY_SUCCEEDED(result.Init(longStr));

    CHECK_STRINGRESULT_REF(&result, longStr);

#pragma prefast(suppress : 6309, "Test case testing illegal arguments")
    VERIFY_FAILED(result.SetContents(NULL, 0));
}

void StringResult_Reference::GetLengthAndSize(void)
{
    StringResult* pResult;

    pResult = new StringResult();
    CHECK_STRINGRESULT_EMPTY(pResult);

    size_t length;
    VERIFY_SUCCEEDED(pResult->GetLength(&length));
    VERIFY(length == 0);

    size_t size;
    VERIFY_SUCCEEDED(pResult->GetSize(&size));
    VERIFY(size == 0);

    delete pResult;

    VERIFY_SUCCEEDED(StringResult::CreateInstance(medStr, &pResult));
    CHECK_STRINGRESULT_REF(pResult, medStr);

    VERIFY_SUCCEEDED(pResult->GetLength(&length));
    VERIFY(length == medLen);

    VERIFY_SUCCEEDED(pResult->GetSize(&size));
    VERIFY(size == medLen + 1);

    delete pResult;
}

void StringResult_Reference::Compare(void)
{
    StringResult result;
    VERIFY_SUCCEEDED(result.Init(medStr));

    StringResult medResult;
    VERIFY_SUCCEEDED(medResult.Init(medStr));

    StringResult shortResult;
    VERIFY_SUCCEEDED(shortResult.Init(shortStr));

    StringResult longResult;
    VERIFY_SUCCEEDED(longResult.Init(longStr));

    StringResult nullResult;
    StringResult iResult;
    VERIFY_SUCCEEDED(iResult.Init(L"hello!"));

    DEFCOMPARISON comp;
    VERIFY_SUCCEEDED(result.Compare(longStr, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);
    VERIFY_SUCCEEDED(result.Compare(shortStr, &comp));
    VERIFY_IS_TRUE(comp == Def_Greater);
    VERIFY_SUCCEEDED(result.Compare(origStr, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.Compare(L"hello!", &comp));
    VERIFY_IS_TRUE(comp == Def_Less);

    VERIFY_SUCCEEDED(result.CompareWithOptions(longStr, DefCompare_Default, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);
    VERIFY_SUCCEEDED(result.CompareWithOptions(shortStr, DefCompare_Default, &comp));
    VERIFY_IS_TRUE(comp == Def_Greater);
    VERIFY_SUCCEEDED(result.CompareWithOptions(origStr, DefCompare_Default, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.CompareWithOptions(L"hello!", DefCompare_Default, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);

    VERIFY_SUCCEEDED(result.ICompare(longStr, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);
    VERIFY_SUCCEEDED(result.ICompare(shortStr, &comp));
    VERIFY_IS_TRUE(comp == Def_Greater);
    VERIFY_SUCCEEDED(result.ICompare(origStr, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.ICompare(L"hello!", &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);

    VERIFY_SUCCEEDED(result.CompareWithOptions(longStr, DefCompare_CaseInsensitive, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);
    VERIFY_SUCCEEDED(result.CompareWithOptions(shortStr, DefCompare_CaseInsensitive, &comp));
    VERIFY_IS_TRUE(comp == Def_Greater);
    VERIFY_SUCCEEDED(result.CompareWithOptions(origStr, DefCompare_CaseInsensitive, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.CompareWithOptions(L"hello!", DefCompare_CaseInsensitive, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);

    VERIFY_SUCCEEDED(result.Compare(&longResult, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);
    VERIFY_SUCCEEDED(result.Compare(&shortResult, &comp));
    VERIFY_IS_TRUE(comp == Def_Greater);
    VERIFY_SUCCEEDED(result.Compare(&result, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.Compare(&medResult, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.Compare(&iResult, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);

    VERIFY_SUCCEEDED(result.CompareWithOptions(&longResult, DefCompare_Default, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);
    VERIFY_SUCCEEDED(result.CompareWithOptions(&shortResult, DefCompare_Default, &comp));
    VERIFY_IS_TRUE(comp == Def_Greater);
    VERIFY_SUCCEEDED(result.CompareWithOptions(&result, DefCompare_Default, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.CompareWithOptions(&medResult, DefCompare_Default, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.CompareWithOptions(&iResult, DefCompare_Default, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);

    VERIFY_SUCCEEDED(result.ICompare(&longResult, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);
    VERIFY_SUCCEEDED(result.ICompare(&shortResult, &comp));
    VERIFY_IS_TRUE(comp == Def_Greater);
    VERIFY_SUCCEEDED(result.ICompare(&result, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.ICompare(&medResult, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.ICompare(&iResult, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);

    VERIFY_SUCCEEDED(result.CompareWithOptions(&longResult, DefCompare_CaseInsensitive, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);
    VERIFY_SUCCEEDED(result.CompareWithOptions(&shortResult, DefCompare_CaseInsensitive, &comp));
    VERIFY_IS_TRUE(comp == Def_Greater);
    VERIFY_SUCCEEDED(result.CompareWithOptions(&result, DefCompare_CaseInsensitive, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.CompareWithOptions(&medResult, DefCompare_CaseInsensitive, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.CompareWithOptions(&iResult, DefCompare_CaseInsensitive, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);

    VERIFY_SUCCEEDED(result.Compare(&nullResult, &comp));
    VERIFY_IS_TRUE(comp == Def_Greater);
    VERIFY_SUCCEEDED(nullResult.Compare(&result, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);
}

void StringResult_Reference::Concat(void)
{
    StringResult result;
    VERIFY_SUCCEEDED(result.Init(medStr));

    CHECK_STRINGRESULT_REF(&result, medStr);

    VERIFY_SUCCEEDED(result.Concat(concatStr));
    VERIFY(result.GetStringResult()->pRef != medStr);
    CHECK_STRINGRESULT_BUF(&result, endStr);
}

void StringResult_Reference::Truncate(void)
{
    PCWSTR pFullString = L"Test string to be truncated";
    PCWSTR pShortString = L"Short";

    StringResult result;
    VERIFY_SUCCEEDED(result.Init(pFullString));

    CHECK_STRINGRESULT_REF(&result, pFullString);

    // first ensure that a read-only buffer is copied and that the result is as expected
    VERIFY_SUCCEEDED(result.Truncate(11));
    VERIFY(result.GetRef() != pFullString);

    size_t length;
    VERIFY_SUCCEEDED(result.GetLength(&length));
    VERIFY_IS_TRUE(length == 11);

    DEFCOMPARISON comp;
    VERIFY_SUCCEEDED(result.Compare(L"Test string", &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);

    PCWSTR pRef = result.GetRef();
    VERIFY_SUCCEEDED(result.Truncate(4));
    VERIFY(result.GetStringResult()->pRef == pRef);
    VERIFY_SUCCEEDED(result.GetLength(&length));
    VERIFY_IS_TRUE(length == 4);
    VERIFY_SUCCEEDED(result.Compare(L"Test", &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);

    VERIFY_SUCCEEDED(result.Truncate(4));
    VERIFY(result.GetStringResult()->pRef == pRef);
    VERIFY_SUCCEEDED(result.GetLength(&length));
    VERIFY_IS_TRUE(length == 4);
    VERIFY_SUCCEEDED(result.Compare(L"Test", &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);

    VERIFY_SUCCEEDED(result.SetRef(pShortString));
    VERIFY_SUCCEEDED(result.Truncate(5));
    VERIFY(result.GetRef() == pShortString);

    VERIFY_FAILED(result.Truncate(8));
}

void StringResult_Reference::Copy(void)
{
    StringResult result;
    VERIFY_SUCCEEDED(result.Init(medStr));
    StringResult copy;
    VERIFY_SUCCEEDED(copy.Init(shortStr));
    StringResult* pCopy;

    CHECK_STRINGRESULT_REF(&result, medStr);
    CHECK_STRINGRESULT_REF(&copy, shortStr);

    VERIFY_SUCCEEDED(result.GetCopy(&copy));
    VERIFY(copy.GetRef() != result.GetRef());
    CHECK_STRINGRESULT_BUF(&copy, medStr);

    // test copy constructor
    VERIFY_SUCCEEDED(result.SetRef(longStr));
    CHECK_STRINGRESULT_REF(&result, longStr);
    //
    VERIFY_SUCCEEDED(StringResult::CreateInstance(result.GetStringResult(), &pCopy));
    VERIFY(pCopy != NULL);
    VERIFY(pCopy->GetRef() != result.GetRef());
    CHECK_STRINGRESULT_BUF(pCopy, longStr);

    delete pCopy;
}

void StringResult_Reference::InvalidTests(void)
{
    StringResult result;
    StringResult* nullResult = NULL;
    size_t cchStrOut = 0;

#pragma prefast(suppress : 6309, "Test case testing illegal arguments")
    VERIFY_FAILED(result.ReleaseContents(NULL, &cchStrOut));
    VERIFY_FAILED(result.GetCopy(nullResult));
    DEFCOMPARISON comp;
    result.CompareWithOptions(nullResult, DefCompare_Default, &comp);
    VERIFY(comp == Def_CompareError);
    result.Compare(nullResult, &comp);
    VERIFY(comp == Def_CompareError);
    result.ICompare(nullResult, &comp);
    VERIFY(comp == Def_CompareError);
}

class StringResult_Buffer : public WEX::TestClass<StringResult_Buffer>, public StringResult_Struct
{
    TEST_CLASS(StringResult_Buffer);

    TEST_METHOD(New);
    TEST_METHOD(GetRef);
    TEST_METHOD(GetWritableRef);
    TEST_METHOD(SetRef);
    TEST_METHOD(SetBuf);
    TEST_METHOD(AcquireAndReleaseBuf);
    TEST_METHOD(GetLengthAndSize);
    TEST_METHOD(Compare);
    TEST_METHOD(Concat);
    TEST_METHOD(Copy);
};

void StringResult_Buffer::New(void)
{
    StringResult* pResult;

    VERIFY_SUCCEEDED(StringResult::CreateInstance(NULL, DefResultType_Buffer, &pResult));
    VERIFY(pResult != NULL);
    CHECK_STRINGRESULT_EMPTY(pResult);

    delete pResult;

    VERIFY_SUCCEEDED(StringResult::CreateInstance(medStr, DefResultType_Buffer, &pResult));
    VERIFY(pResult != NULL);
    CHECK_STRINGRESULT_BUF(pResult, medStr);

    delete pResult;
}

void StringResult_Buffer::GetRef(void)
{
    StringResult result;
    VERIFY_SUCCEEDED(result.Init(medStr, DefResultType_Buffer));
    PCWSTR pRef;

    CHECK_STRINGRESULT_BUF(&result, medStr);

    pRef = result.GetRef();
    VERIFY(pRef != NULL);
    VERIFY(pRef != medStr);
    VERIFY(pRef == result.GetStringResult()->pBuf);
}

void StringResult_Buffer::GetWritableRef(void)
{
    StringResult result;
    VERIFY_SUCCEEDED(result.Init(shortStr, DefResultType_Buffer));
    PWSTR pRef;
    size_t cchRef;

    CHECK_STRINGRESULT_BUF(&result, shortStr);

    VERIFY_SUCCEEDED(result.GetWritableRef(&pRef, &cchRef));
    VERIFY(pRef != NULL);
    CHECK_STRINGRESULT_BUF(&result, shortStr);
    VERIFY(pRef != shortStr);
    CHECK_BUFFER(pRef, cchRef, shortStr);
}

void StringResult_Buffer::SetRef(void)
{
    StringResult result;
    VERIFY_SUCCEEDED(result.Init(longStr, DefResultType_Buffer));

    CHECK_STRINGRESULT_BUF(&result, longStr);
    VERIFY(result.GetRef() != shortStr);

    VERIFY_SUCCEEDED(result.SetRef(shortStr));
    CHECK_STRINGRESULT_REF(&result, shortStr);
    CHECK_BUFFER(result.GetStringResult()->pBuf, result.GetStringResult()->cchBuf, longStr); // original buf should remain
}

void StringResult_Buffer::SetBuf(void)
{
    StringResult result;
    VERIFY_SUCCEEDED(result.Init(shortStr, DefResultType_Buffer));

    CHECK_STRINGRESULT_BUF(&result, shortStr);

    VERIFY_SUCCEEDED(result.SetCopy(medStr));
    CHECK_STRINGRESULT_BUF(&result, medStr);
}

void StringResult_Buffer::AcquireAndReleaseBuf(void)
{
    PWSTR pStr = L"The new pStr";
    size_t cchStr = _countof(L"The new pStr");

    PWSTR pStrOut = NULL;
    size_t cchStrOut = 0;

    StringResult result;
    VERIFY_SUCCEEDED(result.Init(medStr, DefResultType_Buffer));

    CHECK_STRINGRESULT_BUF(&result, medStr);

    VERIFY_SUCCEEDED(result.SetContents(pStr, cchStr));
    CHECK_STRINGRESULT_BUF(&result, pStr);
    VERIFY(result.GetStringResult()->pRef == pStr);
    VERIFY(result.GetStringResult()->cchBuf == cchStr);

    VERIFY_SUCCEEDED(result.ReleaseContents(&pStrOut, &cchStrOut));
    CHECK_STRINGRESULT_EMPTY(&result);
    CHECK_STRINGRESULT_BUF_EMPTY(&result);
    VERIFY(pStrOut == pStr);
    VERIFY(cchStrOut == cchStr);
}

void StringResult_Buffer::GetLengthAndSize(void)
{
    StringResult result;
    VERIFY_SUCCEEDED(result.Init(shortStr, DefResultType_Buffer));

    CHECK_STRINGRESULT_BUF(&result, shortStr);

    size_t length;
    VERIFY_SUCCEEDED(result.GetLength(&length));
    VERIFY(length == shortLen);

    size_t size;
    VERIFY_SUCCEEDED(result.GetSize(&size));
    VERIFY(size == shortLen + 1);

    VERIFY_SUCCEEDED(result.SetCopy(longStr));
    CHECK_STRINGRESULT_BUF(&result, longStr);

    VERIFY_SUCCEEDED(result.GetLength(&length));
    VERIFY(length == longLen);

    VERIFY_SUCCEEDED(result.GetSize(&size));
    VERIFY(size == longLen + 1);
}

void StringResult_Buffer::Compare(void)
{
    StringResult result;
    VERIFY_SUCCEEDED(result.Init(medStr, DefResultType_Buffer));
    StringResult medResult;
    VERIFY_SUCCEEDED(medResult.Init(medStr, DefResultType_Buffer));
    StringResult shortResult;
    VERIFY_SUCCEEDED(shortResult.Init(shortStr, DefResultType_Buffer));
    StringResult longResult;
    VERIFY_SUCCEEDED(longResult.Init(longStr, DefResultType_Buffer));
    StringResult nullResult;
    StringResult iResult;
    VERIFY_SUCCEEDED(iResult.Init(L"hello!", DefResultType_Buffer));

    DEFCOMPARISON comp;
    VERIFY_SUCCEEDED(result.Compare(longStr, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);
    VERIFY_SUCCEEDED(result.Compare(shortStr, &comp));
    VERIFY_IS_TRUE(comp == Def_Greater);
    VERIFY_SUCCEEDED(result.Compare(origStr, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.Compare(L"hello!", &comp));
    VERIFY_IS_TRUE(comp == Def_Less);

    VERIFY_SUCCEEDED(result.CompareWithOptions(longStr, DefCompare_Default, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);
    VERIFY_SUCCEEDED(result.CompareWithOptions(shortStr, DefCompare_Default, &comp));
    VERIFY_IS_TRUE(comp == Def_Greater);
    VERIFY_SUCCEEDED(result.CompareWithOptions(origStr, DefCompare_Default, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.CompareWithOptions(L"hello!", DefCompare_Default, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);

    VERIFY_SUCCEEDED(result.ICompare(longStr, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);
    VERIFY_SUCCEEDED(result.ICompare(shortStr, &comp));
    VERIFY_IS_TRUE(comp == Def_Greater);
    VERIFY_SUCCEEDED(result.ICompare(origStr, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.ICompare(L"hello!", &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);

    VERIFY_SUCCEEDED(result.CompareWithOptions(longStr, DefCompare_CaseInsensitive, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);
    VERIFY_SUCCEEDED(result.CompareWithOptions(shortStr, DefCompare_CaseInsensitive, &comp));
    VERIFY_IS_TRUE(comp == Def_Greater);
    VERIFY_SUCCEEDED(result.CompareWithOptions(origStr, DefCompare_CaseInsensitive, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.CompareWithOptions(L"hello!", DefCompare_CaseInsensitive, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);

    VERIFY_SUCCEEDED(result.Compare(&longResult, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);
    VERIFY_SUCCEEDED(result.Compare(&shortResult, &comp));
    VERIFY_IS_TRUE(comp == Def_Greater);
    VERIFY_SUCCEEDED(result.Compare(&result, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.Compare(&medResult, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.Compare(&iResult, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);

    VERIFY_SUCCEEDED(result.CompareWithOptions(&longResult, DefCompare_Default, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);
    VERIFY_SUCCEEDED(result.CompareWithOptions(&shortResult, DefCompare_Default, &comp));
    VERIFY_IS_TRUE(comp == Def_Greater);
    VERIFY_SUCCEEDED(result.CompareWithOptions(&result, DefCompare_Default, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.CompareWithOptions(&medResult, DefCompare_Default, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.CompareWithOptions(&iResult, DefCompare_Default, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);

    VERIFY_SUCCEEDED(result.ICompare(&longResult, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);
    VERIFY_SUCCEEDED(result.ICompare(&shortResult, &comp));
    VERIFY_IS_TRUE(comp == Def_Greater);
    VERIFY_SUCCEEDED(result.ICompare(&result, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.ICompare(&medResult, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.ICompare(&iResult, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);

    VERIFY_SUCCEEDED(result.CompareWithOptions(&longResult, DefCompare_CaseInsensitive, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);
    VERIFY_SUCCEEDED(result.CompareWithOptions(&shortResult, DefCompare_CaseInsensitive, &comp));
    VERIFY_IS_TRUE(comp == Def_Greater);
    VERIFY_SUCCEEDED(result.CompareWithOptions(&result, DefCompare_CaseInsensitive, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.CompareWithOptions(&medResult, DefCompare_CaseInsensitive, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);
    VERIFY_SUCCEEDED(result.CompareWithOptions(&iResult, DefCompare_CaseInsensitive, &comp));
    VERIFY_IS_TRUE(comp == Def_Equal);

    VERIFY_SUCCEEDED(result.Compare(&nullResult, &comp));
    VERIFY_IS_TRUE(comp == Def_Greater);
    VERIFY_SUCCEEDED(nullResult.Compare(&result, &comp));
    VERIFY_IS_TRUE(comp == Def_Less);
}

void StringResult_Buffer::Concat(void)
{
    StringResult result;
    VERIFY_SUCCEEDED(result.Init(medStr, DefResultType_Buffer));

    CHECK_STRINGRESULT_BUF(&result, medStr);

    VERIFY_SUCCEEDED(result.Concat(concatStr));
    VERIFY(result.GetStringResult()->pRef != medStr);
    CHECK_STRINGRESULT_BUF(&result, endStr);
}

void StringResult_Buffer::Copy(void)
{
    StringResult result;
    VERIFY_SUCCEEDED(result.Init(medStr, DefResultType_Buffer));
    StringResult copy;
    VERIFY_SUCCEEDED(copy.Init(shortStr));
    StringResult* pCopy;

    CHECK_STRINGRESULT_BUF(&result, medStr);
    CHECK_STRINGRESULT_REF(&copy, shortStr);

    VERIFY_SUCCEEDED(result.GetCopy(&copy));
    VERIFY(copy.GetRef() != result.GetRef());
    CHECK_STRINGRESULT_BUF(&copy, medStr);

    // test copy constructor
    VERIFY_SUCCEEDED(result.SetCopy(longStr));
    CHECK_STRINGRESULT_BUF(&result, longStr);
    //
    VERIFY_SUCCEEDED(StringResult::CreateInstance(result.GetStringResult(), &pCopy));
    VERIFY(pCopy != NULL);
    VERIFY(pCopy->GetRef() != result.GetRef());
    CHECK_STRINGRESULT_BUF(pCopy, longStr);

    delete pCopy;
}

} // namespace UnitTests
