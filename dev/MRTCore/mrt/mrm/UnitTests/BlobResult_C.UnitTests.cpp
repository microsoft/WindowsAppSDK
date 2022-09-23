// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <windows.h>
#include <WexTestClass.h>
#include "Helpers.h"
#include "blobresult.h"

#define CHECK_BUFFER(pSelf, cbSelf, aGoal) \
    VERIFY_ARE_EQUAL(Def_Equal, DefBlob_Compare((pSelf), (aGoal), (cbSelf))); \
    VERIFY_ARE_EQUAL((size_t)(cbSelf), sizeof(aGoal))

#define CHECK_BLOBRESULT_BUF_EMPTY(pSelf) \
    VERIFY_IS_NULL((pSelf)->pBuf); \
    VERIFY((pSelf)->cbBuf == 0)

#define CHECK_BLOBRESULT_REF(pSelf, aStuff) \
    VERIFY_IS_TRUE(DefBlobResult_GetType((pSelf)) == DefResultType_Reference); \
    CHECK_BUFFER((pSelf)->pRef, (pSelf)->cbRef, (aStuff)); \
    VERIFY((pSelf)->pRef == (aStuff))

#define CHECK_BLOBRESULT_BUF(pSelf, aStuff) \
    VERIFY_IS_TRUE(DefBlobResult_GetType((pSelf)) == DefResultType_Buffer); \
    CHECK_BUFFER((pSelf)->pRef, (pSelf)->cbRef, (aStuff)); \
    VERIFY((pSelf)->pBuf == (pSelf)->pRef); \
    VERIFY((pSelf)->pRef == DefBlobResult_GetRef(pSelf, NULL)); \
    VERIFY((pSelf)->pRef == DefBlobResult_GetWritableRef(pSelf, NULL)); \
    VERIFY((pSelf)->cbBuf >= (pSelf)->cbRef)

#define CHECK_BLOBRESULT_EMPTY(pSelf) \
    VERIFY_IS_TRUE(DefBlobResult_GetType((pSelf)) == DefResultType_None); \
    CHECK_BLOBRESULT_BUF_EMPTY(pSelf); \
    VERIFY_IS_NULL((pSelf)->pRef); \
    VERIFY_IS_NULL(DefBlobResult_GetRef(pSelf, NULL)); \
    VERIFY((pSelf)->cbRef == 0)

namespace UnitTests
{

class DefBlobResultTests : public WEX::TestClass<DefBlobResultTests>
{
public:
    TEST_CLASS(DefBlobResultTests);

    //TEST_METHOD_SETUP(Setup);
    //TEST_METHOD_CLEANUP(Cleanup);

    TEST_METHOD(RefNew);
    TEST_METHOD(RefInit);
    TEST_METHOD(RefInitJunk);

    TEST_METHOD(BufNew);
    TEST_METHOD(BufInit);

    TEST_METHOD(GetRef);
    TEST_METHOD(GetWritableRefFromRefType);
    TEST_METHOD(GetWritableRefFromBufType);

    TEST_METHOD(SetRef);
    TEST_METHOD(SetBufSmaller);
    TEST_METHOD(SetBufLarger);
    TEST_METHOD(SetBufNull);
    TEST_METHOD(AcquireBuf);
    TEST_METHOD(AcquireBufNull);

    TEST_METHOD(ReleaseBuf);
    TEST_METHOD(ReleaseBufAfterAcquireBuf);
    TEST_METHOD(ReleaseBufAfterSetRef);

    TEST_METHOD(Compare);
    TEST_METHOD(CompareAfterSetRef);

    TEST_METHOD(GetSize);

    TEST_METHOD(InvalidTests);
};

void DefBlobResultTests::RefNew(void)
{
    CHAR aStuff[] = "asdfaeaef";

    DEFBLOBRESULT* pSelf;
    VERIFY_SUCCEEDED(DefBlobResult_NewRef(aStuff, sizeof(aStuff), &pSelf));
    VERIFY_IS_TRUE(pSelf != NULL);
    CHECK_BLOBRESULT_REF(pSelf, aStuff);
    CHECK_BLOBRESULT_BUF_EMPTY(pSelf);

    DefBlobResult_Delete(pSelf);
}

void DefBlobResultTests::RefInit(void)
{
    CHAR aStuff[] = "asdfaeaef";

    DEFBLOBRESULT self = {0};
    VERIFY_SUCCEEDED(DefBlobResult_InitRef(&self, aStuff, sizeof(aStuff)));
    CHECK_BLOBRESULT_REF(&self, aStuff);
    CHECK_BLOBRESULT_BUF_EMPTY(&self);

    DefBlobResult_Clear(&self);
    CHECK_BLOBRESULT_REF(&self, aStuff);
    CHECK_BLOBRESULT_BUF_EMPTY(&self);
}

void DefBlobResultTests::RefInitJunk(void)
{
    CHAR aStuff[] = "asdfaeaef";

    DEFBLOBRESULT self;
    self.cbBuf = 100;
    self.pBuf = reinterpret_cast<void*>(12);
    self.cbRef = 5;
    self.pRef = reinterpret_cast<void*>(72);
    VERIFY_SUCCEEDED(DefBlobResult_InitRef(&self, aStuff, sizeof(aStuff)));
    CHECK_BLOBRESULT_REF(&self, aStuff);
    CHECK_BLOBRESULT_BUF_EMPTY(&self);

    DefBlobResult_Clear(&self);
    CHECK_BLOBRESULT_REF(&self, aStuff);
    CHECK_BLOBRESULT_BUF_EMPTY(&self);
}

void DefBlobResultTests::BufNew(void)
{
    CHAR aStuff[] = "asdfaeaef";

    DEFBLOBRESULT* pSelf;
    VERIFY_SUCCEEDED(DefBlobResult_NewBuf(aStuff, sizeof(aStuff), &pSelf));
    CHECK_BLOBRESULT_BUF(pSelf, aStuff);

    DefBlobResult_Delete(pSelf);
}

void DefBlobResultTests::BufInit(void)
{
    CHAR aStuff[] = "asdfaeaef";

    DEFBLOBRESULT self = {0};
    VERIFY_SUCCEEDED(DefBlobResult_InitBuf(&self, aStuff, sizeof(aStuff)));
    CHECK_BLOBRESULT_BUF(&self, aStuff);

    DefBlobResult_Clear(&self);
    CHECK_BLOBRESULT_EMPTY(&self);
}

void DefBlobResultTests::GetRef(void)
{
    CHAR aStuff[] = "asdfaeaef";

    DEFBLOBRESULT* pSelf;
    VERIFY_SUCCEEDED(DefBlobResult_NewRef(aStuff, sizeof(aStuff), &pSelf));

    size_t cbRef;
    VERIFY_IS_TRUE(DefBlobResult_GetRef(pSelf, &cbRef) == aStuff);
    VERIFY(cbRef == sizeof(aStuff));

    DefBlobResult_Delete(pSelf);
}

void DefBlobResultTests::GetWritableRefFromRefType(void)
{
    CHAR aStuff[] = "asdfaeaef";
    CHAR newStuff[] = "qwpoqweq"; // must be smaller than aStuff

    DEFBLOBRESULT* pSelf;
    VERIFY_SUCCEEDED(DefBlobResult_NewRef(aStuff, sizeof(aStuff), &pSelf));
    VERIFY_IS_TRUE(DefBlobResult_GetType(pSelf) == DefResultType_Reference);

    size_t cbRef;
    size_t cbWritableRef;
    void* pRef = DefBlobResult_GetWritableRef(pSelf, &cbWritableRef);
    VERIFY_IS_TRUE(pRef != aStuff);
    CHECK_BLOBRESULT_BUF(pSelf, aStuff);
    VERIFY_IS_TRUE(DefBlobResult_GetRef(pSelf, &cbRef) == pRef);
    VERIFY(cbRef == cbWritableRef);
    CHECK_BUFFER(pRef, cbWritableRef, aStuff);

    // verify that the buffer is writable
    memcpy_s(pRef, cbWritableRef, newStuff, sizeof(newStuff));
    CHECK_BUFFER(pSelf->pRef, sizeof(newStuff), newStuff);

    // verify that size does not have to be obtained
    pRef = DefBlobResult_GetWritableRef(pSelf, NULL);
    CHECK_BUFFER(pRef, sizeof(newStuff), newStuff);

    DefBlobResult_Delete(pSelf);
}

void DefBlobResultTests::GetWritableRefFromBufType(void)
{
    CHAR aStuff[] = "asdfaeaef";
    CHAR newStuff[] = "qwpoqweq"; // must be smaller than aStuff

    DEFBLOBRESULT* pSelf;
    VERIFY_SUCCEEDED(DefBlobResult_NewBuf(aStuff, sizeof(aStuff), &pSelf));
    CHECK_BLOBRESULT_BUF(pSelf, aStuff);

    size_t cbWritableRef;
    void* pRef = DefBlobResult_GetWritableRef(pSelf, &cbWritableRef);
    CHECK_BLOBRESULT_BUF(pSelf, aStuff);
    CHECK_BUFFER(pRef, cbWritableRef, aStuff);

    // verify that the buffer is writable
    memcpy_s(pRef, cbWritableRef, newStuff, sizeof(newStuff));
    CHECK_BUFFER(pSelf->pRef, sizeof(newStuff), newStuff);

    DefBlobResult_Delete(pSelf);
}

void DefBlobResultTests::SetRef(void)
{
    DEFBLOBRESULT self;

    BYTE aOrig[] = "Hey There, I'm first";
    BYTE aSet[] = "And I'm second";
    size_t cbOrig = sizeof(aOrig);
    size_t cbSet = sizeof(aSet);

    void* pRef;
    size_t cbRef;

    VERIFY_SUCCEEDED(DefBlobResult_InitBuf(&self, aOrig, cbOrig));
    CHECK_BLOBRESULT_BUF(&self, aOrig);

    VERIFY_SUCCEEDED(DefBlobResult_SetRef(&self, aSet, cbSet));
    CHECK_BLOBRESULT_REF(&self, aSet);
    CHECK_BUFFER(self.pBuf, self.cbBuf, aOrig); // original buf should remain

    VERIFY_IS_TRUE(DefBlobResult_GetRef(&self, &cbRef) == aSet);
    VERIFY(cbRef == cbSet);

    pRef = DefBlobResult_GetWritableRef(&self, &cbRef);
    VERIFY_IS_TRUE(pRef != aSet);
    CHECK_BLOBRESULT_BUF(&self, aSet);
    CHECK_BUFFER(pRef, cbRef, aSet);
    VERIFY(self.cbBuf == cbSet);

    VERIFY_SUCCEEDED(DefBlobResult_SetRef(&self, NULL, 1));
    VERIFY_IS_TRUE(DefBlobResult_GetType(&self) == DefResultType_None);
    VERIFY_IS_TRUE(DefBlobResult_GetRef(&self, &cbRef) == NULL);
    VERIFY(cbRef == 1);
    CHECK_BUFFER(self.pBuf, self.cbBuf, aSet); // buf should remain

    VERIFY_SUCCEEDED(DefBlobResult_SetRef(&self, NULL, 0));
    DefBlobResult_Clear(&self); // clear out buf contents
    CHECK_BLOBRESULT_EMPTY(&self);
}

void DefBlobResultTests::SetBufSmaller(void)
{
    DEFBLOBRESULT self;

    BYTE aOrig[] = "Hey There, I'm first";
    BYTE aSet[] = "And I'm second"; // aSet must be shorter than aOrig
    size_t cbOrig = sizeof(aOrig);
    size_t cbSet = sizeof(aSet);

    VERIFY_SUCCEEDED(DefBlobResult_InitBuf(&self, aOrig, cbOrig));
    CHECK_BLOBRESULT_BUF(&self, aOrig);

    VERIFY_SUCCEEDED(DefBlobResult_SetCopy(&self, aSet, cbSet));
    CHECK_BLOBRESULT_BUF(&self, aSet);
    VERIFY(self.pBuf != aSet);
    VERIFY_ARE_EQUAL((size_t)self.cbBuf, sizeof(aOrig)); // buffer should still be the same size. cbRef tracks current usage
    VERIFY_ARE_EQUAL((size_t)self.cbRef, sizeof(aSet));

    DefBlobResult_Clear(&self);
    CHECK_BLOBRESULT_EMPTY(&self);
}

void DefBlobResultTests::SetBufLarger(void)
{
    DEFBLOBRESULT self;

    BYTE aOrig[] = "I'm first";
    BYTE aSet[] = "And I'm second"; // aSet must be longer than aOrig
    size_t cbOrig = sizeof(aOrig);
    size_t cbSet = sizeof(aSet);

    VERIFY_SUCCEEDED(DefBlobResult_InitBuf(&self, aOrig, cbOrig));
    CHECK_BLOBRESULT_BUF(&self, aOrig);

    VERIFY_SUCCEEDED(DefBlobResult_SetCopy(&self, aSet, cbSet));
    CHECK_BLOBRESULT_BUF(&self, aSet);
    VERIFY(self.pBuf != aSet);
    VERIFY_ARE_EQUAL((size_t)self.cbBuf, sizeof(aSet));
    VERIFY_ARE_EQUAL((size_t)self.cbRef, sizeof(aSet));

    DefBlobResult_Clear(&self);
    CHECK_BLOBRESULT_EMPTY(&self);
}

void DefBlobResultTests::SetBufNull(void)
{
    DEFBLOBRESULT self;

    BYTE aOrig[] = "I'm first";
    size_t cbOrig = sizeof(aOrig);

    VERIFY_SUCCEEDED(DefBlobResult_InitBuf(&self, aOrig, cbOrig));
    CHECK_BLOBRESULT_BUF(&self, aOrig);

    // Calling SetCopy with NULL is equivalent to calling DefBlobResult_Clear()
    VERIFY_SUCCEEDED(DefBlobResult_SetCopy(&self, NULL, 0));
    CHECK_BLOBRESULT_EMPTY(&self);
}

void DefBlobResultTests::AcquireBuf(void)
{
    CHAR aOrig[] = "asdfaeaef";
    CHAR aAcquire[] = "fdsa";

    DEFBLOBRESULT self = {0};
    VERIFY_SUCCEEDED(DefBlobResult_InitBuf(&self, aOrig, sizeof(aOrig)));
    CHECK_BLOBRESULT_BUF(&self, aOrig);

    VERIFY_SUCCEEDED(DefBlobResult_SetContents(&self, aAcquire, sizeof(aAcquire)));
    CHECK_BLOBRESULT_BUF(&self, aAcquire);
    VERIFY_ARE_EQUAL((size_t)self.cbBuf, sizeof(aAcquire));
    VERIFY_ARE_EQUAL((size_t)self.cbRef, sizeof(aAcquire));
    VERIFY(self.pRef == (aAcquire));

    // don't call clear, as it would free static array aAcquire
}

void DefBlobResultTests::AcquireBufNull(void)
{
    CHAR aOrig[] = "asdfaeaef";

    DEFBLOBRESULT self = {0};
    VERIFY_SUCCEEDED(DefBlobResult_InitBuf(&self, aOrig, sizeof(aOrig)));
    CHECK_BLOBRESULT_BUF(&self, aOrig);

    VERIFY_FAILED(DefBlobResult_SetContents(&self, NULL, 0));
    // cleanup blob result
    DefBlobResult_Clear(&self);
    CHECK_BLOBRESULT_EMPTY(&self);
}

void DefBlobResultTests::ReleaseBuf(void)
{
    CHAR aOrig[] = "asdfaeaef";
    void* pRelease = NULL;
    size_t cbRelease = 0;

    DEFBLOBRESULT self = {0};
    VERIFY_SUCCEEDED(DefBlobResult_InitBuf(&self, aOrig, sizeof(aOrig)));
    CHECK_BLOBRESULT_BUF(&self, aOrig);

    VERIFY_SUCCEEDED(DefBlobResult_ReleaseContents(&self, &pRelease, &cbRelease));
    CHECK_BLOBRESULT_EMPTY(&self);
    CHECK_BUFFER(pRelease, cbRelease, aOrig);

    DefBlobResult_Clear(&self);
    CHECK_BLOBRESULT_EMPTY(&self);

    _DefFree(pRelease);
}

void DefBlobResultTests::ReleaseBufAfterAcquireBuf(void)
{
    CHAR aOrig[] = "asdfaeaef";
    CHAR aAcquire[] = "fdsa";
    void* pRelease = NULL;
    size_t cbRelease = 0;

    DEFBLOBRESULT self = {0};
    VERIFY_SUCCEEDED(DefBlobResult_InitBuf(&self, aOrig, sizeof(aOrig)));
    CHECK_BLOBRESULT_BUF(&self, aOrig);

    VERIFY_SUCCEEDED(DefBlobResult_SetContents(&self, aAcquire, sizeof(aAcquire)));
    CHECK_BLOBRESULT_BUF(&self, aAcquire);

    VERIFY_SUCCEEDED(DefBlobResult_ReleaseContents(&self, &pRelease, &cbRelease));
    CHECK_BLOBRESULT_EMPTY(&self);
    CHECK_BUFFER(pRelease, cbRelease, aAcquire);
}

void DefBlobResultTests::ReleaseBufAfterSetRef(void)
{
    DEFBLOBRESULT self;

    BYTE aOrig[] = "Hey There, I'm first";
    BYTE aSet[] = "And I'm second";
    size_t cbOrig = sizeof(aOrig);
    size_t cbSet = sizeof(aSet);

    void* pBufOut;
    size_t cbBufOut;

    VERIFY_SUCCEEDED(DefBlobResult_InitBuf(&self, aOrig, cbOrig));
    CHECK_BLOBRESULT_BUF(&self, aOrig);

    VERIFY_SUCCEEDED(DefBlobResult_SetRef(&self, aSet, cbSet));
    CHECK_BLOBRESULT_REF(&self, aSet);
    CHECK_BUFFER(self.pBuf, self.cbBuf, aOrig); // original buf contents should still remain

    VERIFY_SUCCEEDED(DefBlobResult_ReleaseContents(&self, &pBufOut, &cbBufOut));
    CHECK_BLOBRESULT_EMPTY(&self);
    CHECK_BUFFER(pBufOut, cbBufOut, aOrig);

    _DefFree(pBufOut);
}

void DefBlobResultTests::Compare(void)
{
    DEFBLOBRESULT self, greater, lesser, shorter, longer, nullResult, emptyResult;

    VERIFY_SUCCEEDED(DefBlobResult_InitRef(&self, "1111111", sizeof("1111111")));
    VERIFY_SUCCEEDED(DefBlobResult_InitRef(&greater, "2222222", sizeof("2222222")));
    VERIFY_SUCCEEDED(DefBlobResult_InitRef(&lesser, "0000000", sizeof("0000000")));
    VERIFY_SUCCEEDED(DefBlobResult_InitRef(&longer, "1111111111", sizeof("1111111111")));
    VERIFY_SUCCEEDED(DefBlobResult_InitRef(&shorter, "11111", sizeof("11111")));
    VERIFY_SUCCEEDED(DefBlobResult_InitRef(&nullResult, NULL, 0));
    VERIFY_SUCCEEDED(DefBlobResult_InitRef(&emptyResult, "", sizeof("")));

    VERIFY_IS_TRUE(DefBlobResult_Compare(&self, &self) == Def_Equal);
    VERIFY_IS_TRUE(DefBlobResult_Compare(&self, &greater) == Def_Less);
    VERIFY_IS_TRUE(DefBlobResult_Compare(&self, &lesser) == Def_Greater);
    VERIFY_IS_TRUE(DefBlobResult_Compare(&self, &longer) == Def_Less);
    VERIFY_IS_TRUE(DefBlobResult_Compare(&self, &shorter) == Def_Greater);

    // null string comparisons
    VERIFY_IS_TRUE(DefBlobResult_Compare(&nullResult, &nullResult) == Def_Equal);
    VERIFY_IS_TRUE(DefBlobResult_Compare(&nullResult, &self) == Def_Less);
    VERIFY_IS_TRUE(DefBlobResult_Compare(&self, &nullResult) == Def_Greater);

    // empty string comparisons
    VERIFY_IS_TRUE(DefBlobResult_Compare(&emptyResult, &self) == Def_Less);
    VERIFY_IS_TRUE(DefBlobResult_Compare(&self, &emptyResult) == Def_Greater);
}

void DefBlobResultTests::CompareAfterSetRef(void)
{
    DEFBLOBRESULT self, other;

    BYTE aOrig[] = "Hey There, I'm first";
    BYTE aSet[] = "And I'm second";
    size_t cbOrig = sizeof(aOrig);
    size_t cbSet = sizeof(aSet);

    VERIFY_SUCCEEDED(DefBlobResult_InitBuf(&self, aOrig, cbOrig));
    CHECK_BLOBRESULT_BUF(&self, aOrig);

    VERIFY_SUCCEEDED(DefBlobResult_SetRef(&self, aSet, cbSet));
    CHECK_BLOBRESULT_REF(&self, aSet);
    CHECK_BUFFER(self.pBuf, self.cbBuf, aOrig); // original buf contents should still remain

    VERIFY_SUCCEEDED(DefBlobResult_InitBuf(&other, aSet, cbSet));
    CHECK_BLOBRESULT_BUF(&other, aSet);

    // compare should use cbRef, and not cbBuf
    VERIFY_IS_TRUE(DefBlobResult_Compare(&self, &other) == Def_Equal);

    DefBlobResult_Clear(&self);
    DefBlobResult_Clear(&other);
}

void DefBlobResultTests::GetSize(void)
{
    DEFBLOBRESULT self;

    BYTE aOrig[] = "Hey There, I'm first";
    BYTE aSet[] = "And I'm second";
    size_t cbOrig = sizeof(aOrig);
    size_t cbSet = sizeof(aSet);

    void* pBufOut;
    size_t cbBufOut;

    VERIFY_SUCCEEDED(DefBlobResult_InitBuf(&self, aOrig, cbOrig));
    CHECK_BLOBRESULT_BUF(&self, aOrig);
    VERIFY_IS_TRUE(DefBlobResult_GetSize(&self) == cbOrig);

    VERIFY_SUCCEEDED(DefBlobResult_SetRef(&self, aSet, cbSet));
    CHECK_BLOBRESULT_REF(&self, aSet);
    VERIFY_IS_TRUE(DefBlobResult_GetSize(&self) == cbSet);
    CHECK_BUFFER(self.pBuf, self.cbBuf, aOrig); // original buf contents should still remain

    VERIFY_SUCCEEDED(DefBlobResult_ReleaseContents(&self, &pBufOut, &cbBufOut));
    CHECK_BLOBRESULT_EMPTY(&self);
    VERIFY_IS_TRUE(DefBlobResult_GetSize(&self) == 0);
    CHECK_BUFFER(pBufOut, cbBufOut, aOrig);
    if (pBufOut != nullptr)
    {
        _DefFree(pBufOut);
    }
}

void DefBlobResultTests::InvalidTests(void)
{
    DEFBLOBRESULT selfInvalid1 = {0}, selfInvalid2 = {0}, selfValid = {0};
    DEFBLOBRESULT* pSelfNull = NULL;

    CHAR aStuff[] = "asdfaeaef";

    // setup invalid blob results
    // pBuf is NULL, but cbBuf is > 0
    selfInvalid1.cbBuf = 1;
    selfInvalid1.pBuf = NULL;
    selfInvalid1.cbRef = 1;
    selfInvalid1.pRef = NULL;
    // pBuf is non-NULL, but cbBuf is 0
    selfInvalid2.cbBuf = 0;
    selfInvalid2.pBuf = reinterpret_cast<void*>(12);
    selfInvalid2.cbRef = 0;
    selfInvalid2.pRef = selfInvalid2.pBuf;

    // null blob results
    VERIFY_FAILED(DefBlobResult_InitRef(pSelfNull, aStuff, sizeof(aStuff)));

    VERIFY_FAILED(DefBlobResult_InitBuf(pSelfNull, aStuff, sizeof(aStuff)));

    DefBlobResult_Clear(pSelfNull);

    DefBlobResult_Delete(pSelfNull);

    VERIFY(DefBlobResult_GetSize(pSelfNull) == 0);

    VERIFY(DefBlobResult_GetType(pSelfNull) == DefResultType_None);

    VERIFY(DefBlobResult_Compare(pSelfNull, &selfValid) == Def_CompareError);

    VERIFY(DefBlobResult_Compare(&selfValid, pSelfNull) == Def_CompareError);

    // invalid blob results
    VERIFY_IS_NULL(DefBlobResult_GetRef(&selfInvalid1, NULL));

    VERIFY_IS_NULL(DefBlobResult_GetWritableRef(&selfInvalid2, NULL));

    VERIFY_FAILED(DefBlobResult_SetRef(&selfInvalid1, NULL, 0));

    // invalid parameters
    VERIFY_FAILED(DefBlobResult_SetCopy(&selfValid, NULL, 10));

    VERIFY_FAILED(DefBlobResult_SetContents(&selfValid, NULL, 10));

    VERIFY_FAILED(DefBlobResult_SetContents(&selfValid, aStuff, 0));

    VERIFY_FAILED(DefBlobResult_ReleaseContents(&selfValid, NULL, NULL));
}

} // namespace UnitTests
