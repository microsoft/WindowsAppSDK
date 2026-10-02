// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <windows.h>
#include <WexTestClass.h>
#include "Helpers.h"
#include "mrm/common/BaseInternal.h"
#include "stringresult.h"

namespace UnitTests
{

#define CHECK_BUFFER(pSelf, cchSelf, aGoal) \
    VERIFY_ARE_EQUAL(Def_Equal, DefBlob_Compare((pSelf), (aGoal), (cchSelf) * sizeof(wchar_t))); \
    VERIFY_ARE_EQUAL(wcslen(aGoal) + 1, (size_t)(cchSelf))

#define CHECK_STRINGRESULT_BUF_EMPTY(pSelf) \
    VERIFY_IS_NULL((pSelf)->pBuf); \
    VERIFY((pSelf)->cchBuf == 0)

#define CHECK_STRINGRESULT_COMPLETELY_EMPTY(pSelf) \
    VERIFY(DefStringResult_GetType((pSelf)) == DefResultType_None); \
    CHECK_STRINGRESULT_BUF_EMPTY(pSelf); \
    VERIFY_IS_NULL((pSelf)->pRef)

#define CHECK_STRINGRESULT_EMPTY(pSelf) \
    VERIFY(DefStringResult_GetType((pSelf)) == DefResultType_None); \
    VERIFY_IS_NULL((pSelf)->pRef)

#define CHECK_STRINGRESULT_REF(pSelf, aStuff) \
    VERIFY(DefStringResult_GetType((pSelf)) == DefResultType_Reference); \
    VERIFY_ARE_EQUAL((pSelf)->pRef, static_cast<PCWSTR>(aStuff))

#define CHECK_STRINGRESULT_BUF(pSelf, aStuff) \
    VERIFY(DefStringResult_GetType((pSelf)) == DefResultType_Buffer); \
    CHECK_BUFFER((pSelf)->pBuf, (pSelf)->cchBuf, (aStuff)); \
    VERIFY_ARE_EQUAL(static_cast<PCWSTR>((pSelf)->pBuf), (pSelf)->pRef)

class DefStringResult_Base
{
public:
    bool SetupBase(DEFRESULTTYPE type)
    {
        shortStr = L"Bye!";
        medStr = L"Hello!";
        longStr = L"Hello! What's Up?";
        emptyStr = L"";

        origStr = medStr;
        nullStr = NULL;

        shortLen = wcslen(shortStr);
        medLen = wcslen(medStr);
        longLen = wcslen(longStr);
        origLen = medLen;

        HRESULT hr = DefStringResult_New(medStr, type, &pSelf);
        if ((!pSelf) || FAILED(hr))
        {
            CleanupBase();
            return false;
        }
        hr = DefStringResult_New(NULL, type, &pNullSelf);
        if ((!pNullSelf) || FAILED(hr))
        {
            CleanupBase();
            return false;
        }
        origRef = pSelf->pRef;
        return true;
    }

    bool CleanupBase()
    {
        if (pSelf)
            DefStringResult_Delete(pSelf);
        if (pNullSelf)
            DefStringResult_Delete(pNullSelf);
        return true;
    }

    PCWSTR origRef;
    PCWSTR shortStr, medStr, origStr, longStr, nullStr;
    PWSTR emptyStr;
    size_t shortLen, medLen, origLen, longLen;

    DEFSTRINGRESULT *pSelf, *pNullSelf;
};

class DefStringResultTests_Reference : public WEX::TestClass<DefStringResultTests_Reference>, public DefStringResult_Base
{
public:
    TEST_CLASS(DefStringResultTests_Reference);

    TEST_METHOD_SETUP(Setup);
    TEST_METHOD_CLEANUP(Cleanup);

    TEST_METHOD(New);
    TEST_METHOD(Basics);
    TEST_METHOD(InitRef);
    TEST_METHOD(InitRef_Junk);
    TEST_METHOD(GetRef);
    TEST_METHOD(GetWritableRef);
    TEST_METHOD(SetRef);
    TEST_METHOD(SetBuf);
    TEST_METHOD(SetBufNull);
    TEST_METHOD(AcquireBuf);
    TEST_METHOD(AcquireBufNull);
    TEST_METHOD(SetContents);
    TEST_METHOD(SetEmptyContents);
    TEST_METHOD(ReleaseAfterAcquire);
    TEST_METHOD(ReleaseEmptyBuf);
    TEST_METHOD(Length);
    TEST_METHOD(Compare);
    TEST_METHOD(Concat);
    TEST_METHOD(Copy);
    TEST_METHOD(InvalidTests);
};

bool DefStringResultTests_Reference::Setup(void) { return SetupBase(DefResultType_Reference); }

bool DefStringResultTests_Reference::Cleanup(void) { return CleanupBase(); }

void DefStringResultTests_Reference::New(void)
{
    VERIFY_IS_NOT_NULL(pNullSelf);
    CHECK_STRINGRESULT_EMPTY(pNullSelf);
    VERIFY_ARE_NOT_EQUAL(pSelf, pNullSelf);

    DEFSTRINGRESULT* pNewRef;
    VERIFY_SUCCEEDED(DefStringResult_NewRef(origStr, &pNewRef));
    VERIFY(pNewRef != NULL);
    CHECK_STRINGRESULT_REF(pNewRef, origStr);
    CHECK_STRINGRESULT_BUF_EMPTY(pNewRef);

    VERIFY_ARE_NOT_EQUAL(pSelf, pNewRef);
    VERIFY_ARE_EQUAL(pSelf->pRef, pNewRef->pRef);

    DefStringResult_Delete(pNewRef);
}

void DefStringResultTests_Reference::Basics(void)
{
    VERIFY_IS_NOT_NULL(pSelf);
    CHECK_STRINGRESULT_REF(pSelf, medStr);
    CHECK_STRINGRESULT_BUF_EMPTY(pSelf);
}

void DefStringResultTests_Reference::InitRef(void)
{
    const WCHAR aStuff[] = L"asdfaeaef";

    DEFSTRINGRESULT self = {0};

    VERIFY_SUCCEEDED(DefStringResult_InitRef(&self, aStuff));
    CHECK_STRINGRESULT_REF(&self, aStuff);
    CHECK_STRINGRESULT_BUF_EMPTY(&self);

    VERIFY_SUCCEEDED(DefStringResult_Clear(&self, true));
    CHECK_STRINGRESULT_COMPLETELY_EMPTY(&self);

    // test init wrapper
    VERIFY_SUCCEEDED(DefStringResult_Init(&self, aStuff, DefResultType_Reference));
    CHECK_STRINGRESULT_REF(&self, aStuff);
    CHECK_STRINGRESULT_BUF_EMPTY(&self);

    VERIFY_SUCCEEDED(DefStringResult_Clear(&self, true));
    CHECK_STRINGRESULT_COMPLETELY_EMPTY(&self);
}

void DefStringResultTests_Reference::InitRef_Junk(void)
{
    WCHAR aStuff[] = L"asdfaeaef";

    DEFSTRINGRESULT self;
    self.cchBuf = 100;
    self.pBuf = reinterpret_cast<PWSTR>(12);
    self.pRef = reinterpret_cast<PCWSTR>(72);
    VERIFY_SUCCEEDED(DefStringResult_InitRef(&self, aStuff));
    CHECK_STRINGRESULT_REF(&self, aStuff);
    CHECK_STRINGRESULT_BUF_EMPTY(&self);

    VERIFY_SUCCEEDED(DefStringResult_Clear(&self, true));
    CHECK_STRINGRESULT_COMPLETELY_EMPTY(&self);
}

void DefStringResultTests_Reference::GetRef(void)
{
    CHECK_STRINGRESULT_REF(pSelf, medStr);

    PCWSTR ref;
    VERIFY_SUCCEEDED(DefStringResult_GetRef(pSelf, &ref));
    VERIFY(ref == medStr);
}

void DefStringResultTests_Reference::GetWritableRef(void)
{
    PWSTR pRef;
    size_t cchRef;
    PWSTR stuff = L"pqowl"; // must be shorter than medStr
    size_t cchStuff = _countof(L"pqowl");

    CHECK_STRINGRESULT_REF(pSelf, medStr);

    VERIFY_SUCCEEDED(DefStringResult_GetWritableRef(pSelf, 0, &pRef, &cchRef));
    VERIFY(pRef != medStr);
    CHECK_STRINGRESULT_BUF(pSelf, medStr);
    CHECK_BUFFER(pRef, cchRef, medStr);

    // verify that the buffer is writable
    StringCchCopy(pRef, cchStuff, stuff);
    CHECK_BUFFER(pSelf->pRef, cchStuff, stuff);
}

void DefStringResultTests_Reference::SetRef(void)
{
    CHECK_STRINGRESULT_REF(pSelf, medStr);

    VERIFY_SUCCEEDED(DefStringResult_SetRef(pSelf, longStr));
    CHECK_STRINGRESULT_REF(pSelf, longStr);

    VERIFY_SUCCEEDED(DefStringResult_SetRef(pSelf, emptyStr));
    CHECK_STRINGRESULT_REF(pSelf, emptyStr);

    VERIFY_SUCCEEDED(DefStringResult_SetRef(pSelf, NULL));
    CHECK_STRINGRESULT_EMPTY(pSelf);
}

void DefStringResultTests_Reference::SetBuf(void)
{
    CHECK_STRINGRESULT_REF(pSelf, origRef);

    VERIFY_SUCCEEDED(DefStringResult_SetCopy(pSelf, medStr));
    CHECK_STRINGRESULT_BUF(pSelf, medStr);
    VERIFY(pSelf->pRef != origRef);
    VERIFY(pSelf->pRef != medStr);

    VERIFY_SUCCEEDED(DefStringResult_SetRef(pSelf, longStr));
    CHECK_STRINGRESULT_REF(pSelf, longStr);
    CHECK_BUFFER(pSelf->pBuf, pSelf->cchBuf, medStr); // original buf remains
    VERIFY_ARE_EQUAL((size_t)(pSelf->cchBuf), medLen + 1);
}

void DefStringResultTests_Reference::SetBufNull(void)
{
    CHECK_STRINGRESULT_REF(pSelf, origRef);

    // Calling SetCopy with NULL is equivalent to calling DefStringResult_Clear()
    VERIFY_SUCCEEDED(DefStringResult_SetCopy(pSelf, NULL));
    CHECK_STRINGRESULT_EMPTY(pSelf);
}

void DefStringResultTests_Reference::AcquireBuf(void)
{
    PWSTR bufStr = L"The new pStr";
    size_t bufCch = _countof(L"The new pStr");

    VERIFY(origRef != bufStr);
    VERIFY_SUCCEEDED(DefStringResult_SetContents(pSelf, bufStr, bufCch));
    CHECK_STRINGRESULT_BUF(pSelf, bufStr);
    VERIFY(pSelf->cchBuf == bufCch);
    VERIFY(pSelf->pRef == bufStr);

    // null out pBuf or else static array bufStr will be free'd
    pSelf->pBuf = NULL;
    pSelf->cchBuf = 0;
    pSelf->pRef = NULL;
}

void DefStringResultTests_Reference::AcquireBufNull(void)
{
    PCWSTR pOldRef;
    VERIFY_SUCCEEDED(DefStringResult_GetRef(pSelf, &pOldRef));
    VERIFY_FAILED(DefStringResult_SetContents(pSelf, NULL, 0));

    PCWSTR newRef;
    VERIFY_SUCCEEDED(DefStringResult_GetRef(pSelf, &newRef));
    VERIFY(pOldRef == newRef);
}

void DefStringResultTests_Reference::SetContents(void)
{
    VERIFY(pSelf->pRef == origStr);
    WCHAR* pBuf = (WCHAR*)Def_Alloc(sizeof(WCHAR) * 100);
    VERIFY(pBuf != NULL);
    HRESULT hr = StringCchCopyW(pBuf, 100, L"Test");
    VERIFY(hr == S_OK);
    VERIFY_SUCCEEDED(DefStringResult_SetContents(pSelf, pBuf, 100));
    VERIFY(pSelf->pBuf == pBuf);
    VERIFY(pSelf->pRef == pBuf);
}

void DefStringResultTests_Reference::SetEmptyContents(void)
{
    VERIFY(pSelf->pRef == origStr);

    // First we set to an empty 100 character buffer, then verify that:
    // 1) what we get back is actually an empty buffer with at least 100 characters
    // 2) pSelf actually refers to it
    size_t cchBuf;
    WCHAR* pFirstBuf;
    VERIFY_SUCCEEDED(DefStringResult_SetEmptyContents(pSelf, 100, &pFirstBuf, &cchBuf));
    VERIFY((pFirstBuf != NULL) && (cchBuf >= 100));
    VERIFY(pSelf->pRef == pFirstBuf);
    VERIFY(pFirstBuf[0] == '\0');

    // We don't actually need this buffer, but if we don't allocate something after
    // the initial call to SetEmptyContents we get spurious failures in the second
    // test below -- the call to SetEmptyContents with length 200 causes the buffer
    // to be freed and reallocated, but some allocators just reuse the original memory.
    // As a result, the test that pThirdBuf!=pFirstBuf below fails.

    // Copy a string into the buffer
    HRESULT hr = StringCchCopyW(pFirstBuf, 100, L"Test");
    VERIFY(hr == S_OK);

    // Now set it to a smaller (50 character) buffer.  And verify that:
    // 1) what we get back is an empty buffer with at least 50 characters
    // 2) pSelf actually refers to it
    // 3) The buffer we got back is actually the original buffer and that the
    //    full size is reported.
    WCHAR* pSecondBuf;
    VERIFY_SUCCEEDED(DefStringResult_SetEmptyContents(pSelf, 50, &pSecondBuf, &cchBuf));
    VERIFY((pSecondBuf != NULL) && (cchBuf >= 50));
    VERIFY(pSecondBuf[0] == '\0');
    VERIFY((pSecondBuf == pFirstBuf) && (cchBuf == 100));

    hr = StringCchCopyW(pSecondBuf, 50, L"2Test");

    // Now set it to a larger (200 character) empty buffer and verify that:
    // 1) What we get back is an empty buffer with at least 200 characters
    // 2) pSelf actually referst to it
    // 3) The buffer we got back is _not_ the original buffer
    WCHAR* pThirdBuf;
    VERIFY_SUCCEEDED(DefStringResult_SetEmptyContents(pSelf, 200, &pThirdBuf, &cchBuf));
    VERIFY((pThirdBuf != NULL) && (cchBuf >= 200));
    VERIFY(pThirdBuf[0] == '\0');
    VERIFY((pThirdBuf != pFirstBuf));
}

void DefStringResultTests_Reference::ReleaseAfterAcquire(void)
{
    PWSTR bufStr = L"The new pStr";
    size_t bufCch = _countof(L"The new pStr");

    PWSTR strOut = NULL;
    size_t cchStrOut = 0;

    VERIFY_SUCCEEDED(DefStringResult_SetContents(pSelf, bufStr, bufCch));
    CHECK_STRINGRESULT_BUF(pSelf, bufStr);

    VERIFY_SUCCEEDED(DefStringResult_ReleaseContents(pSelf, &strOut, &cchStrOut));
    CHECK_STRINGRESULT_COMPLETELY_EMPTY(pSelf);
    VERIFY(strOut == bufStr);
    VERIFY(cchStrOut == bufCch);
}

void DefStringResultTests_Reference::ReleaseEmptyBuf(void)
{
    PWSTR strOut = NULL;
    size_t cchStrOut = 0;
    VERIFY_FAILED(DefStringResult_ReleaseContents(pSelf, &strOut, &cchStrOut));
    VERIFY(strOut == NULL);
    VERIFY(cchStrOut == 0);
}

void DefStringResultTests_Reference::Length(void)
{
    PWSTR pWritableRef;
    size_t cchWritableRef;
    PWSTR stuff = L"pqowl"; // must be shorter than medStr
    size_t cchStuff = _countof(L"pqowl");

    size_t length;
    size_t size;
    VERIFY_SUCCEEDED(DefStringResult_GetLength(pNullSelf, &length));
    VERIFY(length == 0);
    VERIFY_SUCCEEDED(DefStringResult_GetSize(pNullSelf, &size));
    VERIFY(size == 0);

    VERIFY_SUCCEEDED(DefStringResult_GetLength(pSelf, &length));
    VERIFY(length == origLen);
    VERIFY_SUCCEEDED(DefStringResult_GetSize(pSelf, &size));
    VERIFY(size == origLen + 1);

    VERIFY_IS_LESS_THAN(shortLen, origLen);
    VERIFY_SUCCEEDED(DefStringResult_SetCopy(pSelf, shortStr));
    VERIFY_SUCCEEDED(DefStringResult_GetLength(pSelf, &length));
    VERIFY(length == shortLen);
    VERIFY_SUCCEEDED(DefStringResult_GetSize(pSelf, &size));
    VERIFY(size == shortLen + 1);

    VERIFY_SUCCEEDED(DefStringResult_SetRef(pSelf, longStr));
    VERIFY_SUCCEEDED(DefStringResult_GetLength(pSelf, &length));
    VERIFY(length == longLen);
    VERIFY_SUCCEEDED(DefStringResult_GetSize(pSelf, &size));
    VERIFY(size == longLen + 1);

    VERIFY_SUCCEEDED(DefStringResult_GetWritableRef(pSelf, 0, &pWritableRef, &cchWritableRef));
    CHECK_STRINGRESULT_BUF(pSelf, longStr);
    StringCchCopy(pWritableRef, cchStuff, stuff);
    CHECK_BUFFER(pSelf->pBuf, cchStuff, stuff);
    VERIFY_SUCCEEDED(DefStringResult_GetLength(pSelf, &length));
    VERIFY(length == cchStuff - 1); // null terminator not included
    VERIFY_SUCCEEDED(DefStringResult_GetSize(pSelf, &size));
    VERIFY(size == longLen + 1);

    VERIFY_SUCCEEDED(DefStringResult_SetRef(pSelf, L""));
    VERIFY_SUCCEEDED(DefStringResult_GetLength(pSelf, &length));
    VERIFY(length == 0);
    VERIFY_SUCCEEDED(DefStringResult_GetSize(pSelf, &size));
    VERIFY(size == 1);
}

void DefStringResultTests_Reference::Compare(void)
{
    DEFSTRINGRESULT* nullDefStr = NULL;
    DEFCOMPARISON comp;

    VERIFY_SUCCEEDED(DefStringResult_Compare(pSelf, longStr, &comp));
    VERIFY(comp == Def_Less);
    VERIFY_SUCCEEDED(DefStringResult_Compare(pSelf, shortStr, &comp));
    VERIFY(comp == Def_Greater);
    VERIFY_SUCCEEDED(DefStringResult_Compare(pSelf, origStr, &comp));
    VERIFY(comp == Def_Equal);
    VERIFY_SUCCEEDED(DefStringResult_Compare(pSelf, L"hello!", &comp));
    VERIFY(comp == Def_Less);

    VERIFY_SUCCEEDED(DefStringResult_CompareWithOptions(pSelf, longStr, DefCompare_Default, &comp));
    VERIFY(comp == Def_Less);
    VERIFY_SUCCEEDED(DefStringResult_CompareWithOptions(pSelf, shortStr, DefCompare_Default, &comp));
    VERIFY(comp == Def_Greater);
    VERIFY_SUCCEEDED(DefStringResult_CompareWithOptions(pSelf, origStr, DefCompare_Default, &comp));
    VERIFY(comp == Def_Equal);
    VERIFY_SUCCEEDED(DefStringResult_CompareWithOptions(pSelf, L"hello!", DefCompare_Default, &comp));
    VERIFY(comp == Def_Less);

    VERIFY_SUCCEEDED(DefStringResult_ICompare(pSelf, longStr, &comp));
    VERIFY(comp == Def_Less);
    VERIFY_SUCCEEDED(DefStringResult_ICompare(pSelf, shortStr, &comp));
    VERIFY(comp == Def_Greater);
    VERIFY_SUCCEEDED(DefStringResult_ICompare(pSelf, origStr, &comp));
    VERIFY(comp == Def_Equal);
    VERIFY_SUCCEEDED(DefStringResult_ICompare(pSelf, L"hello!", &comp));
    VERIFY(comp == Def_Equal);

    VERIFY_SUCCEEDED(DefStringResult_CompareWithOptions(pSelf, longStr, DefCompare_CaseInsensitive, &comp));
    VERIFY(comp == Def_Less);
    VERIFY_SUCCEEDED(DefStringResult_CompareWithOptions(pSelf, shortStr, DefCompare_CaseInsensitive, &comp));
    VERIFY(comp == Def_Greater);
    VERIFY_SUCCEEDED(DefStringResult_CompareWithOptions(pSelf, origStr, DefCompare_CaseInsensitive, &comp));
    VERIFY(comp == Def_Equal);
    VERIFY_SUCCEEDED(DefStringResult_CompareWithOptions(pSelf, L"hello!", DefCompare_CaseInsensitive, &comp));
    VERIFY(comp == Def_Equal);

    VERIFY_SUCCEEDED(DefStringResult_Compare(pSelf, nullStr, &comp));
    VERIFY(comp == Def_Greater);
    VERIFY_SUCCEEDED(DefStringResult_ICompare(pSelf, nullStr, &comp));
    VERIFY(comp == Def_Greater);

    VERIFY_FAILED(DefStringResult_Compare(nullDefStr, nullStr, &comp));
    VERIFY(comp == Def_CompareError);
    VERIFY_FAILED(DefStringResult_Compare(nullDefStr, origStr, &comp));
    VERIFY(comp == Def_CompareError);

    VERIFY_FAILED(DefStringResult_ICompare(nullDefStr, nullStr, &comp));
    VERIFY(comp == Def_CompareError);
    VERIFY_FAILED(DefStringResult_ICompare(nullDefStr, origStr, &comp));
    VERIFY(comp == Def_CompareError);
}

void DefStringResultTests_Reference::Concat(void)
{
    PCWSTR concatStr = L" What's Up?";
    PCWSTR endStr = longStr;
    PCWSTR oldStr = NULL;

    CHECK_STRINGRESULT_REF(pSelf, origStr);
    VERIFY_SUCCEEDED(DefStringResult_Concat(pSelf, concatStr));
    VERIFY(pSelf->pRef != origStr);
    CHECK_STRINGRESULT_BUF(pSelf, endStr);

    VERIFY_SUCCEEDED(DefStringResult_GetRef(pSelf, &oldStr));

    VERIFY_SUCCEEDED(DefStringResult_Concat(pSelf, nullStr));
    PCWSTR newStr;
    VERIFY_SUCCEEDED(DefStringResult_GetRef(pSelf, &newStr));
    VERIFY(newStr == oldStr);

    CHECK_STRINGRESULT_BUF(pSelf, endStr);

    VERIFY_SUCCEEDED(DefStringResult_Concat(pSelf, L""));
    CHECK_STRINGRESULT_BUF(pSelf, endStr);

    // concatenate empty string to null string
    VERIFY_SUCCEEDED(DefStringResult_Concat(pNullSelf, L""));
    CHECK_STRINGRESULT_BUF(pNullSelf, L"");
    size_t length;
    VERIFY_SUCCEEDED(DefStringResult_GetLength(pNullSelf, &length));
    VERIFY(length == 0);
    size_t size;
    VERIFY_SUCCEEDED(DefStringResult_GetSize(pNullSelf, &size));
    VERIFY(size == 1);
}

void DefStringResultTests_Reference::Copy(void)
{
    DEFSTRINGRESULT copy;
    VERIFY_SUCCEEDED(DefStringResult_InitRef(&copy, NULL));

    // populate the copy
    VERIFY_SUCCEEDED(DefStringResult_SetRef(&copy, longStr));
    CHECK_STRINGRESULT_REF(&copy, longStr);

    VERIFY_SUCCEEDED(DefStringResult_GetCopy(pNullSelf, &copy));
    size_t length;
    VERIFY_SUCCEEDED(DefStringResult_GetLength(&copy, &length));
    VERIFY(length == 0);

    VERIFY_SUCCEEDED(DefStringResult_GetCopy(pSelf, &copy));
    VERIFY(copy.pRef != pSelf->pRef);
    CHECK_STRINGRESULT_BUF(&copy, pSelf->pRef);

    VERIFY_SUCCEEDED(DefStringResult_Clear(&copy, true));
    CHECK_STRINGRESULT_COMPLETELY_EMPTY(&copy);
}

// this tests both Reference and Buffer-related functions
void DefStringResultTests_Reference::InvalidTests(void)
{
    DEFSTRINGRESULT selfInvalid1 = {0}, selfInvalid2 = {0}, selfValid = {0};
    DEFSTRINGRESULT* pSelfNull = NULL;

    PWSTR aStuff = L"asdfaeaef";

    // setup invalid blob results
    // pBuf is NULL, but cbBuf is > 0
    selfInvalid1.cchBuf = 1;
    selfInvalid1.pBuf = NULL;
    selfInvalid1.pRef = NULL;
    // pBuf is non-NULL, but cbBuf is 0
    selfInvalid2.cchBuf = 0;
    selfInvalid2.pBuf = reinterpret_cast<PWSTR>(12);
    selfInvalid2.pRef = selfInvalid2.pBuf;

    // null string results
    VERIFY_FAILED(DefStringResult_InitRef(pSelfNull, aStuff));

    VERIFY_FAILED(DefStringResult_InitBuf(pSelfNull, aStuff));

    VERIFY(DefStringResult_GetType(pSelfNull) == DefResultType_None);

    DEFCOMPARISON comp;
    VERIFY_FAILED(DefStringResult_Compare(pSelfNull, aStuff, &comp));
    VERIFY(comp == Def_CompareError);

    VERIFY_FAILED(DefStringResult_ICompare(pSelfNull, aStuff, &comp));
    VERIFY(comp == Def_CompareError);

    VERIFY_FAILED(DefStringResult_Clear(pSelfNull, true));

    DefStringResult_Delete(pSelfNull);

    // invalid string results
    size_t length;
    VERIFY_FAILED(DefStringResult_GetLength(&selfInvalid1, &length));
    VERIFY(length == 0);

    PCWSTR ref;
    VERIFY_FAILED(DefStringResult_GetRef(&selfInvalid2, &ref));
    VERIFY_IS_NULL(ref);

    PWSTR writableRef;
    VERIFY_FAILED(DefStringResult_GetWritableRef(&selfInvalid1, 0, &writableRef, NULL));
    VERIFY_IS_NULL(writableRef);

    size_t size;
    VERIFY_FAILED(DefStringResult_GetSize(&selfInvalid2, &size));
    VERIFY(size == 0);

    VERIFY_FAILED(DefStringResult_SetRef(&selfInvalid1, NULL));

    VERIFY_FAILED(DefStringResult_SetCopy(&selfInvalid2, NULL));

    // invalid parameters
    VERIFY_FAILED(DefStringResult_GetCopy(&selfValid, NULL));

    VERIFY_FAILED(DefStringResult_SetContents(&selfValid, NULL, 10));

    VERIFY_FAILED(DefStringResult_SetContents(&selfValid, aStuff, 0));

    VERIFY_FAILED(DefStringResult_ReleaseContents(&selfValid, NULL, NULL));

    DEFSTRINGRESULT* result;
    VERIFY_FAILED(DefStringResult_New(aStuff, DefResultType_None, &result));
    VERIFY_IS_NULL(result);

    VERIFY_FAILED(DefStringResult_Init(&selfValid, aStuff, (DEFRESULTTYPE)4));

    VERIFY_SUCCEEDED(DefStringResult_CompareWithOptions(pSelf, L"hello!", (DEFCOMPAREOPTIONS)2, &comp));
    VERIFY(comp == Def_Less);
}

class DefStringResultTests_Buffer : public WEX::TestClass<DefStringResultTests_Buffer>, DefStringResult_Base
{
public:
    TEST_CLASS(DefStringResultTests_Buffer);

    TEST_METHOD_SETUP(Setup);
    TEST_METHOD_CLEANUP(Cleanup);

    TEST_METHOD(New);
    TEST_METHOD(NewEmptyString);
    TEST_METHOD(Basics);
    TEST_METHOD(InitBuf_Junk);
    TEST_METHOD(GetRef);
    TEST_METHOD(GetWritableRef);
    TEST_METHOD(SetRef);
    TEST_METHOD(SetBufSmallerLargerAndNull);
    TEST_METHOD(AcquireBuf);
    TEST_METHOD(AcquireBufNull);
    TEST_METHOD(Release);
    TEST_METHOD(Length);
    TEST_METHOD(Compare);
    TEST_METHOD(Concat);
    TEST_METHOD(Copy);
};

bool DefStringResultTests_Buffer::Setup(void) { return SetupBase(DefResultType_Buffer); }

bool DefStringResultTests_Buffer::Cleanup(void) { return CleanupBase(); }

void DefStringResultTests_Buffer::New()
{
    DEFSTRINGRESULT* newDef;
    VERIFY_SUCCEEDED(DefStringResult_NewBuf(medStr, &newDef));
    VERIFY(pSelf != newDef);
    VERIFY_ARE_EQUAL(pSelf->cchBuf, newDef->cchBuf);
    VERIFY(pSelf->pRef != newDef->pRef);
    CHECK_STRINGRESULT_BUF(newDef, medStr);

    DefStringResult_Delete(newDef);
}

void DefStringResultTests_Buffer::NewEmptyString()
{
    DEFSTRINGRESULT* newDef;
    VERIFY_SUCCEEDED(DefStringResult_NewBuf(L"", &newDef));

    CHECK_STRINGRESULT_EMPTY(newDef);

    DefStringResult_Delete(newDef);
}

void DefStringResultTests_Buffer::Basics()
{
    VERIFY(pNullSelf != NULL);
    CHECK_STRINGRESULT_EMPTY(pNullSelf);

    VERIFY(pSelf != NULL);
    CHECK_STRINGRESULT_BUF(pSelf, medStr);
    VERIFY(pSelf->pRef != medStr);
    VERIFY(pSelf->cchBuf == wcslen(medStr) + 1);
    VERIFY(wcslen(pSelf->pBuf) == wcslen(medStr));

    VERIFY_SUCCEEDED(DefStringResult_Clear(pSelf, true));
    CHECK_STRINGRESULT_EMPTY(pSelf);
}

void DefStringResultTests_Buffer::InitBuf_Junk(void)
{
    WCHAR aStuff[] = L"asdfaeaef";

    DEFSTRINGRESULT self;
    self.cchBuf = 100;
    self.pBuf = reinterpret_cast<PWSTR>(12);
    self.pRef = reinterpret_cast<PCWSTR>(72);
    VERIFY_SUCCEEDED(DefStringResult_InitBuf(&self, aStuff));
    CHECK_STRINGRESULT_BUF(&self, aStuff);

    VERIFY_SUCCEEDED(DefStringResult_Clear(&self, true));
    CHECK_STRINGRESULT_EMPTY(&self);

    // test init wrapper
    self.cchBuf = 100;
    self.pBuf = reinterpret_cast<PWSTR>(12);
    self.pRef = reinterpret_cast<PCWSTR>(72);
    VERIFY_SUCCEEDED(DefStringResult_Init(&self, aStuff, DefResultType_Buffer));
    CHECK_STRINGRESULT_BUF(&self, aStuff);

    VERIFY_SUCCEEDED(DefStringResult_Clear(&self, true));
    CHECK_STRINGRESULT_EMPTY(&self);
}

void DefStringResultTests_Buffer::GetRef()
{
    PCWSTR pRef;
    VERIFY_SUCCEEDED(DefStringResult_GetRef(pSelf, &pRef));
    VERIFY(pRef != NULL);
    VERIFY(pRef != medStr);
    VERIFY(pRef == pSelf->pBuf);
}

void DefStringResultTests_Buffer::GetWritableRef()
{
    PWSTR pWritableRef;
    size_t cchWritableRef;
    PWSTR stuff = L"pqowl"; // must be shorter than medStr
    size_t cchStuff = _countof(L"pqowl");

    CHECK_STRINGRESULT_BUF(pSelf, medStr);

    VERIFY_SUCCEEDED(DefStringResult_GetWritableRef(pSelf, 0, &pWritableRef, &cchWritableRef));
    PCWSTR ref;
    VERIFY_SUCCEEDED(DefStringResult_GetRef(pSelf, &ref));
    VERIFY(pWritableRef == ref);
    CHECK_STRINGRESULT_BUF(pSelf, medStr);
    CHECK_BUFFER(pWritableRef, cchWritableRef, pSelf->pRef);

    // verify that the buffer is writable
    StringCchCopy(pWritableRef, cchStuff, stuff);
    CHECK_BUFFER(pSelf->pBuf, cchStuff, stuff);

    // verify that size does not have to be obtained
    VERIFY_SUCCEEDED(DefStringResult_GetWritableRef(pSelf, 0, &pWritableRef, NULL));
    CHECK_BUFFER(pWritableRef, cchStuff, stuff);
}

void DefStringResultTests_Buffer::SetRef()
{
    PWSTR pWritableRef;
    size_t cchWritableRef;

    CHECK_STRINGRESULT_BUF(pSelf, medStr);
    VERIFY(pSelf->pRef != longStr);

    VERIFY_SUCCEEDED(DefStringResult_SetRef(pSelf, longStr));
    CHECK_STRINGRESULT_REF(pSelf, longStr);
    CHECK_BUFFER(pSelf->pBuf, pSelf->cchBuf, medStr); // original buf should remain

    VERIFY_SUCCEEDED(DefStringResult_GetWritableRef(pSelf, 0, &pWritableRef, &cchWritableRef));
    VERIFY(pWritableRef != longStr);
    CHECK_STRINGRESULT_BUF(pSelf, longStr);
    CHECK_BUFFER(pWritableRef, cchWritableRef, pSelf->pRef);

    VERIFY_SUCCEEDED(DefStringResult_SetRef(pSelf, NULL));
    VERIFY(DefStringResult_GetType(pSelf) == DefResultType_None);
    CHECK_BUFFER(pSelf->pBuf, pSelf->cchBuf, longStr); // original buf should remain
}

void DefStringResultTests_Buffer::SetBufSmallerLargerAndNull()
{
    CHECK_STRINGRESULT_BUF(pSelf, medStr);
    VERIFY_ARE_EQUAL((size_t)(pSelf->cchBuf), medLen + 1);

    // set shorter string
    VERIFY(shortLen < medLen);
    VERIFY_SUCCEEDED(DefStringResult_SetCopy(pSelf, shortStr));
    VERIFY(pSelf->pRef == origRef); // pBuf was not reallocated
    VERIFY(pSelf->pRef != shortStr);
    VERIFY_ARE_EQUAL((size_t)(pSelf->cchBuf), medLen + 1);
    // can't call CHECK_STRINGRESULT_BUF, because pSelf->cchBuf is too large for comparison
    VERIFY(DefStringResult_GetType(pSelf) == DefResultType_Buffer);
    CHECK_BUFFER(pSelf->pBuf, shortLen + 1, shortStr);

    // set longer string
    VERIFY(longLen > medLen);
    VERIFY_SUCCEEDED(DefStringResult_SetCopy(pSelf, longStr));
    VERIFY(pSelf->pRef != origRef); // pBuf was reallocated
    VERIFY(pSelf->pRef != longStr);
    VERIFY_ARE_EQUAL((size_t)(pSelf->cchBuf), longLen + 1);
    CHECK_STRINGRESULT_BUF(pSelf, longStr);

    // set empty string
    VERIFY_SUCCEEDED(DefStringResult_SetCopy(pSelf, emptyStr));
    // can't call CHECK_STRINGRESULT_BUF, because pSelf->cchBuf is too large for comparison
    VERIFY(DefStringResult_GetType(pSelf) == DefResultType_Buffer);
    VERIFY_ARE_EQUAL((size_t)(pSelf->cchBuf), longLen + 1);
    CHECK_BUFFER(pSelf->pBuf, (size_t)1, emptyStr);

    VERIFY_SUCCEEDED(DefStringResult_SetCopy(pNullSelf, emptyStr));
    CHECK_STRINGRESULT_BUF(pNullSelf, emptyStr);
    VERIFY_ARE_EQUAL((size_t)(pNullSelf->cchBuf), (size_t)1);

    // set null
    // Calling SetCopy with NULL is equivalent to calling DefStringResult_Clear()
    VERIFY_SUCCEEDED(DefStringResult_SetCopy(pSelf, NULL));
    CHECK_STRINGRESULT_EMPTY(pSelf);
}

void DefStringResultTests_Buffer::AcquireBuf(void)
{
    PWSTR bufStr = L"The new pStr";
    size_t bufCch = _countof(L"The new pStr");

    CHECK_STRINGRESULT_BUF(pSelf, origStr);

    VERIFY(origRef != bufStr);
    VERIFY_SUCCEEDED(DefStringResult_SetContents(pSelf, bufStr, bufCch));
    CHECK_STRINGRESULT_BUF(pSelf, bufStr);
    VERIFY(pSelf->cchBuf == bufCch);
    VERIFY(pSelf->pRef == bufStr);

    // null out pBuf or else static array bufStr will be free'd
    pSelf->pBuf = NULL;
    pSelf->cchBuf = 0;
    pSelf->pRef = NULL;
}

void DefStringResultTests_Buffer::AcquireBufNull(void) { VERIFY_FAILED(DefStringResult_SetContents(pSelf, NULL, 0)); }

void DefStringResultTests_Buffer::Release()
{
    PWSTR bufStr = L"The new pStr";
    size_t bufCch = _countof(L"The new pStr");

    PWSTR rtrn = NULL;
    size_t cchRtrn = 0;

    // release initial contents
    VERIFY_SUCCEEDED(DefStringResult_ReleaseContents(pSelf, &rtrn, &cchRtrn));
    VERIFY(rtrn != medStr);
    VERIFY(rtrn == origRef);
    CHECK_STRINGRESULT_COMPLETELY_EMPTY(pSelf);

    _DefFree(rtrn);

    // set contents
    VERIFY_SUCCEEDED(DefStringResult_SetContents(pSelf, bufStr, bufCch));
    CHECK_STRINGRESULT_BUF(pSelf, bufStr);

    // set ref
    VERIFY(longLen > (bufCch - 1));
    VERIFY_SUCCEEDED(DefStringResult_SetRef(pSelf, longStr));
    CHECK_STRINGRESULT_REF(pSelf, longStr);
    CHECK_BUFFER(pSelf->pBuf, pSelf->cchBuf, bufStr); // original buf should remain

    // release after acquire and set
    VERIFY_SUCCEEDED(DefStringResult_ReleaseContents(pSelf, &rtrn, &cchRtrn));
    VERIFY(rtrn == bufStr);
    VERIFY(cchRtrn == bufCch);
    CHECK_STRINGRESULT_COMPLETELY_EMPTY(pSelf);
}

void DefStringResultTests_Buffer::Length()
{
    size_t length;
    size_t size;
    VERIFY_SUCCEEDED(DefStringResult_GetLength(pNullSelf, &length));
    VERIFY(length == 0);
    VERIFY_SUCCEEDED(DefStringResult_GetSize(pNullSelf, &size));
    VERIFY(size == 0);

    VERIFY_SUCCEEDED(DefStringResult_GetLength(pSelf, &length));
    VERIFY(length == origLen);
    VERIFY_SUCCEEDED(DefStringResult_GetSize(pSelf, &size));
    VERIFY(size == origLen + 1);

    VERIFY_IS_LESS_THAN(shortLen, origLen);
    VERIFY_SUCCEEDED(DefStringResult_SetCopy(pSelf, shortStr));
    VERIFY_SUCCEEDED(DefStringResult_GetLength(pSelf, &length));
    VERIFY(length == shortLen);
    VERIFY_SUCCEEDED(DefStringResult_GetSize(pSelf, &size));
    VERIFY(size == origLen + 1); // did not realloc buf

    VERIFY_SUCCEEDED(DefStringResult_SetRef(pSelf, longStr));
    VERIFY_SUCCEEDED(DefStringResult_GetLength(pSelf, &length));
    VERIFY(length == longLen);
    VERIFY_SUCCEEDED(DefStringResult_GetSize(pSelf, &size));
    VERIFY(size == longLen + 1);

    VERIFY_SUCCEEDED(DefStringResult_SetCopy(pSelf, emptyStr));
    VERIFY_SUCCEEDED(DefStringResult_GetLength(pSelf, &length));
    VERIFY(length == 0);
    VERIFY_SUCCEEDED(DefStringResult_GetSize(pSelf, &size));
    VERIFY(size == origLen + 1); // did not realloc buf

    VERIFY_SUCCEEDED(DefStringResult_SetCopy(pNullSelf, emptyStr));
    VERIFY_SUCCEEDED(DefStringResult_GetLength(pNullSelf, &length));
    VERIFY(length == 0);
    VERIFY_SUCCEEDED(DefStringResult_GetSize(pNullSelf, &size));
    VERIFY(size == 1);

    VERIFY_SUCCEEDED(DefStringResult_SetContents(pNullSelf, emptyStr, 10));
    VERIFY_SUCCEEDED(DefStringResult_GetLength(pNullSelf, &length));
    VERIFY(length == 0);
    VERIFY_SUCCEEDED(DefStringResult_GetSize(pNullSelf, &size));
    VERIFY(size == 10);

    // null out pBuf or else static array bufStr will be free'd
    pNullSelf->pBuf = NULL;
    pNullSelf->cchBuf = 0;
    pNullSelf->pRef = NULL;
}

void DefStringResultTests_Buffer::Compare()
{
    DEFSTRINGRESULT* nullDefStr = NULL;
    DEFCOMPARISON comp;

    VERIFY_SUCCEEDED(DefStringResult_Compare(pSelf, shortStr, &comp));
    VERIFY(comp == Def_Greater);
    VERIFY_SUCCEEDED(DefStringResult_Compare(pSelf, longStr, &comp));
    VERIFY(comp == Def_Less);
    VERIFY_SUCCEEDED(DefStringResult_Compare(pSelf, origStr, &comp));
    VERIFY(comp == Def_Equal);
    VERIFY_SUCCEEDED(DefStringResult_Compare(pSelf, L"hello!", &comp));
    VERIFY(comp == Def_Less);

    VERIFY_SUCCEEDED(DefStringResult_CompareWithOptions(pSelf, shortStr, DefCompare_Default, &comp));
    VERIFY(comp == Def_Greater);
    VERIFY_SUCCEEDED(DefStringResult_CompareWithOptions(pSelf, longStr, DefCompare_Default, &comp));
    VERIFY(comp == Def_Less);
    VERIFY_SUCCEEDED(DefStringResult_CompareWithOptions(pSelf, origStr, DefCompare_Default, &comp));
    VERIFY(comp == Def_Equal);
    VERIFY_SUCCEEDED(DefStringResult_CompareWithOptions(pSelf, L"hello!", DefCompare_Default, &comp));
    VERIFY(comp == Def_Less);

    VERIFY_SUCCEEDED(DefStringResult_ICompare(pSelf, shortStr, &comp));
    VERIFY(comp == Def_Greater);
    VERIFY_SUCCEEDED(DefStringResult_ICompare(pSelf, longStr, &comp));
    VERIFY(comp == Def_Less);
    VERIFY_SUCCEEDED(DefStringResult_ICompare(pSelf, origStr, &comp));
    VERIFY(comp == Def_Equal);
    VERIFY_SUCCEEDED(DefStringResult_ICompare(pSelf, L"hello!", &comp));
    VERIFY(comp == Def_Equal);

    VERIFY_SUCCEEDED(DefStringResult_CompareWithOptions(pSelf, shortStr, DefCompare_CaseInsensitive, &comp));
    VERIFY(comp == Def_Greater);
    VERIFY_SUCCEEDED(DefStringResult_CompareWithOptions(pSelf, longStr, DefCompare_CaseInsensitive, &comp));
    VERIFY(comp == Def_Less);
    VERIFY_SUCCEEDED(DefStringResult_CompareWithOptions(pSelf, origStr, DefCompare_CaseInsensitive, &comp));
    VERIFY(comp == Def_Equal);
    VERIFY_SUCCEEDED(DefStringResult_CompareWithOptions(pSelf, L"hello!", DefCompare_CaseInsensitive, &comp));
    VERIFY(comp == Def_Equal);

    VERIFY_SUCCEEDED(DefStringResult_Compare(pSelf, nullStr, &comp));
    VERIFY(comp == Def_Greater);
    VERIFY_SUCCEEDED(DefStringResult_ICompare(pSelf, nullStr, &comp));
    VERIFY(comp == Def_Greater);

    VERIFY_FAILED(DefStringResult_Compare(nullDefStr, nullStr, &comp));
    VERIFY(comp == Def_CompareError);
    VERIFY_FAILED(DefStringResult_Compare(nullDefStr, origStr, &comp));
    VERIFY(comp == Def_CompareError);
    ;

    VERIFY_FAILED(DefStringResult_ICompare(nullDefStr, nullStr, &comp));
    VERIFY(comp == Def_CompareError);
    VERIFY_FAILED(DefStringResult_ICompare(nullDefStr, origStr, &comp));
    VERIFY(comp == Def_CompareError);

    VERIFY_SUCCEEDED(DefStringResult_CompareWithOptions(pSelf, L"hello!", (DEFCOMPAREOPTIONS)2, &comp));
    VERIFY(comp == Def_Less);
}

void DefStringResultTests_Buffer::Concat()
{
    PCWSTR concatStr = L" What's Up?";
    PCWSTR endStr = longStr;

    VERIFY(DefString_Compare(pSelf->pRef, origStr) == Def_Equal);
    VERIFY_SUCCEEDED(DefStringResult_Concat(pSelf, concatStr));
    VERIFY(DefString_Compare(pSelf->pRef, endStr) == Def_Equal);
    CHECK_STRINGRESULT_BUF(pSelf, endStr);

    // Test non-interference with referred to pStr
    VERIFY_SUCCEEDED(DefStringResult_Clear(pSelf, true));
    CHECK_STRINGRESULT_EMPTY(pSelf);

    DEFSTRINGRESULT* buf;
    VERIFY_SUCCEEDED(DefStringResult_NewBuf(origStr, &buf));
    VERIFY(buf != NULL);
    CHECK_STRINGRESULT_BUF(buf, origStr);

    VERIFY_SUCCEEDED(DefStringResult_SetRef(pSelf, buf->pRef));
    CHECK_STRINGRESULT_REF(pSelf, buf->pRef);
    DEFCOMPARISON comp;
    VERIFY_SUCCEEDED(DefStringResult_Compare(pSelf, origStr, &comp));
    VERIFY(comp == Def_Equal);
    VERIFY_SUCCEEDED(DefStringResult_Concat(pSelf, concatStr));

    // pSelf contents should have changed, but buf contents should not
    CHECK_STRINGRESULT_BUF(buf, origStr);
    VERIFY_SUCCEEDED(DefStringResult_Compare(buf, origStr, &comp));
    VERIFY(comp == Def_Equal);
    CHECK_STRINGRESULT_BUF(pSelf, endStr);

    DefStringResult_Delete(buf);
}

void DefStringResultTests_Buffer::Copy()
{
    DEFSTRINGRESULT copy, copy2;
    VERIFY_SUCCEEDED(DefStringResult_InitRef(&copy, NULL));
    VERIFY_SUCCEEDED(DefStringResult_InitRef(&copy2, NULL));

    VERIFY_SUCCEEDED(DefStringResult_GetCopy(pSelf, &copy));
    VERIFY(copy.cchBuf == pSelf->cchBuf);
    VERIFY(copy.pRef != pSelf->pRef);
    CHECK_STRINGRESULT_BUF(&copy, pSelf->pRef);

    VERIFY_SUCCEEDED(DefStringResult_SetRef(&copy, longStr));
    CHECK_STRINGRESULT_REF(&copy, longStr);
    CHECK_BUFFER(copy.pBuf, copy.cchBuf, origStr); // orig buf remains

    VERIFY_SUCCEEDED(DefStringResult_GetCopy(&copy, &copy2));
    VERIFY(copy2.pRef != copy.pRef);
    CHECK_STRINGRESULT_BUF(&copy2, copy.pRef);

    VERIFY_SUCCEEDED(DefStringResult_Clear(&copy, true));
    VERIFY_SUCCEEDED(DefStringResult_Clear(&copy2, true));
}

}; // namespace UnitTests
