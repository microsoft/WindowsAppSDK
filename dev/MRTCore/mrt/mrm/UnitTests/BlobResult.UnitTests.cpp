// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <windows.h>
#include <WexTestClass.h>

#include "Helpers.h"

using namespace WEX::TestExecution;
using namespace WEX::Logging;
using namespace Microsoft::Resources;

namespace UnitTests
{

#define VERIFY_BUFFER(pSelf, cbSelf, aGoal) \
    { \
        VERIFY(DefBlob_Compare((pSelf), (aGoal), (cbSelf)) == Def_Equal); \
        VERIFY((cbSelf) == sizeof(aGoal)); \
    }

#define VERIFY_BLOBRESULT_BUF_EMPTY(pSelf) \
    { \
        VERIFY((pSelf)->GetBlobResult()->pBuf == NULL); \
        VERIFY((pSelf)->GetBlobResult()->cbBuf == 0); \
    }

#define VERIFY_BLOBRESULT_REF(pSelf, aStuff) \
    { \
        VERIFY((pSelf)->GetType() == DefResultType_Reference); \
        VERIFY_BUFFER((pSelf)->GetBlobResult()->pRef, (pSelf)->GetBlobResult()->cbRef, (aStuff)); \
        VERIFY((pSelf)->GetBlobResult()->pRef == (aStuff)); \
    }

#define VERIFY_BLOBRESULT_BUF(pSelf, aStuff) \
    { \
        VERIFY((pSelf)->GetType() == DefResultType_Buffer); \
        VERIFY_BUFFER((pSelf)->GetBlobResult()->pRef, (pSelf)->GetBlobResult()->cbRef, (aStuff)); \
        VERIFY((pSelf)->GetBlobResult()->pBuf == (pSelf)->GetBlobResult()->pRef); \
        VERIFY((pSelf)->GetBlobResult()->pRef == (pSelf)->GetRef(NULL)); \
        VERIFY((pSelf)->GetBlobResult()->pRef == (pSelf)->GetWritableRef(NULL)); \
        VERIFY((pSelf)->GetBlobResult()->cbBuf >= (pSelf)->GetBlobResult()->cbRef); \
    }

#define VERIFY_BLOBRESULT_EMPTY(pSelf) \
    { \
        VERIFY((pSelf)->GetType() == DefResultType_None); \
        VERIFY_BLOBRESULT_BUF_EMPTY(pSelf); \
        VERIFY_IS_NULL((pSelf)->GetBlobResult()->pRef); \
        VERIFY_IS_NULL((pSelf)->GetRef(NULL)); \
        VERIFY((pSelf)->GetBlobResult()->cbRef == 0); \
    }

class BlobResultUnitTests : public WEX::TestClass<BlobResultUnitTests>
{
public:
    TEST_CLASS(BlobResultUnitTests)

    TEST_METHOD(NewRef);
    TEST_METHOD(NewBuf);
    TEST_METHOD(Compare);
    TEST_METHOD(SetCopy);
    TEST_METHOD(SetRef);
    TEST_METHOD(SetContents);
    TEST_METHOD(ReleaseContents);
    TEST_METHOD(ReleaseContentsAfterSetRef);
    TEST_METHOD(AsciiStringConversionFromReference);
    TEST_METHOD(AsciiStringConversionFromBuffer);
    TEST_METHOD(AnsiInsteadOfAsciiStringConversionFromReference);
    TEST_METHOD(AnsiInsteadOfAsciiStringConversionFromBuffer);
    TEST_METHOD(Utf8InsteadOfAsciiStringConversionFromReference);
    TEST_METHOD(Utf8InsteadOfAsciiStringConversionFromBuffer);
    TEST_METHOD(Utf8StringConversionFromReference);
    TEST_METHOD(Utf8StringConversionFromBuffer);
    TEST_METHOD(Utf16StringConversionFromReference);
    TEST_METHOD(Utf16StringConversionFromBuffer);
    TEST_METHOD(InvalidTests);

private:
    void AsciiStringTests(bool useReference);
    void AnsiInsteadOfAsciiStringTests(bool useReference);
    void Utf8InsteadOfAsciiStringTests(bool useReference);
    void Utf8StringTests(bool useReference);
    void Utf16StringTests(bool useReference);
};

void BlobResultUnitTests::NewRef(void)
{
    CHAR aStuff[] = "asdfaeaef";

    BlobResult* pSelf;
    VERIFY_SUCCEEDED(BlobResult::NewRef(aStuff, sizeof(aStuff), &pSelf));
    VERIFY_BLOBRESULT_REF(pSelf, aStuff);
    VERIFY_BLOBRESULT_BUF_EMPTY(pSelf);

    delete pSelf;
}

void BlobResultUnitTests::NewBuf(void)
{
    CHAR aStuff[] = "asdfaeaef";

    BlobResult* pSelf;
    VERIFY_SUCCEEDED(BlobResult::NewBuf(aStuff, sizeof(aStuff), &pSelf));
    VERIFY_BLOBRESULT_BUF(pSelf, aStuff);

    delete pSelf;
}

void BlobResultUnitTests::Compare(void)
{
    BlobResult self, greater, lesser, shorter, longer;

    VERIFY_SUCCEEDED(self.SetRef("1111111", sizeof("1111111")));
    VERIFY_SUCCEEDED(greater.SetRef("2222222", sizeof("2222222")));
    VERIFY_SUCCEEDED(lesser.SetRef("0000000", sizeof("0000000")));
    VERIFY_SUCCEEDED(longer.SetRef("1111111111", sizeof("1111111111")));
    VERIFY_SUCCEEDED(shorter.SetRef("11111", sizeof("11111")));

    VERIFY_IS_TRUE(self.Compare(&self) == 0);
    VERIFY_IS_TRUE(self.Compare(&greater) < 0);
    VERIFY_IS_TRUE(self.Compare(&lesser) > 0);
    VERIFY_IS_TRUE(self.Compare(&longer) < 0);
    VERIFY_IS_TRUE(self.Compare(&shorter) > 0);
}

void BlobResultUnitTests::SetCopy(void)
{
    BlobResult self;

    BYTE aOrig[] = "Hey There, I'm first";
    BYTE aSet[] = "And I'm second"; // aSet must be shorter than aOrig
    size_t cbOrig = sizeof(aOrig);
    size_t cbSet = sizeof(aSet);

    VERIFY_SUCCEEDED(self.SetCopy(aOrig, cbOrig));
    VERIFY_BLOBRESULT_BUF(&self, aOrig);

    VERIFY_SUCCEEDED(self.SetCopy(aSet, cbSet));
    VERIFY_BLOBRESULT_BUF(&self, aSet);
    VERIFY(self.GetBlobResult()->pBuf != aSet);
    VERIFY(self.GetBlobResult()->cbBuf == sizeof(aOrig)); // buffer should still be the same size. cbRef tracks current usage
    VERIFY(self.GetBlobResult()->cbRef == sizeof(aSet));
}

void BlobResultUnitTests::SetRef(void)
{
    BlobResult self;

    BYTE aOrig[] = "Hey There, I'm first";
    BYTE aSet[] = "And I'm second";
    size_t cbOrig = sizeof(aOrig);
    size_t cbSet = sizeof(aSet);

    size_t cbRef;

    VERIFY_SUCCEEDED(self.SetCopy(aOrig, cbOrig));
    VERIFY_BLOBRESULT_BUF(&self, aOrig);

    VERIFY_SUCCEEDED(self.SetRef(aSet, cbSet));
    VERIFY_BLOBRESULT_REF(&self, aSet);
    VERIFY_BUFFER(self.GetBlobResult()->pBuf, self.GetBlobResult()->cbBuf, aOrig); // original buf should remain

    VERIFY(self.GetRef(&cbRef) == aSet);
    VERIFY(cbRef == cbSet);
}

void BlobResultUnitTests::SetContents(void)
{
    CHAR aOrig[] = "asdfaeaef";
    CHAR aAcquire[] = "fdsa";

    BlobResult self;
    VERIFY_SUCCEEDED(self.SetCopy(aOrig, sizeof(aOrig)));
    VERIFY_BLOBRESULT_BUF(&self, aOrig);

    VERIFY_SUCCEEDED(self.SetContents(aAcquire, sizeof(aAcquire)));
    VERIFY_BLOBRESULT_BUF(&self, aAcquire);
    VERIFY(self.GetBlobResult()->cbBuf == sizeof(aAcquire));
    VERIFY(self.GetBlobResult()->cbRef == sizeof(aAcquire));
    VERIFY(self.GetBlobResult()->pBuf == (aAcquire));

    self.GetBlobResult()->pBuf = NULL; // Set buf to prevent destructor from freeing static array aAcquire
}

void BlobResultUnitTests::ReleaseContents(void)
{
    CHAR aOrig[] = "asdfaeaef";
    void* pRelease = NULL;
    size_t cbRelease = 0;

    BlobResult self;
    VERIFY_SUCCEEDED(self.SetCopy(aOrig, sizeof(aOrig)));
    VERIFY_BLOBRESULT_BUF(&self, aOrig);

    VERIFY_SUCCEEDED(self.ReleaseContents(&pRelease, &cbRelease));
    VERIFY_BLOBRESULT_EMPTY(&self);
    VERIFY_BUFFER(pRelease, cbRelease, aOrig);

    _DefFree(pRelease);
}

void BlobResultUnitTests::ReleaseContentsAfterSetRef(void)
{
    BlobResult self;

    BYTE aOrig[] = "Hey There, I'm first";
    BYTE aSet[] = "And I'm second";
    size_t cbOrig = sizeof(aOrig);
    size_t cbSet = sizeof(aSet);

    void* pBufOut;
    size_t cbBufOut;

    VERIFY_SUCCEEDED(self.SetCopy(aOrig, cbOrig));
    VERIFY_BLOBRESULT_BUF(&self, aOrig);

    VERIFY_SUCCEEDED(self.SetRef(aSet, cbSet));
    VERIFY_BLOBRESULT_REF(&self, aSet);
    VERIFY_BUFFER(self.GetBlobResult()->pBuf, self.GetBlobResult()->cbBuf, aOrig); // original buf should remain

    VERIFY_SUCCEEDED(self.ReleaseContents(&pBufOut, &cbBufOut));
    VERIFY_BLOBRESULT_EMPTY(&self);
    VERIFY_BUFFER(pBufOut, cbBufOut, aOrig);

    _DefFree(pBufOut);
}

void BlobResultUnitTests::AsciiStringTests(bool useReference)
{
    char string[] = "foobar";

    StringResult stringResult;
    BlobResult* blobResult;
    VERIFY_SUCCEEDED(
        useReference ? BlobResult::NewRef(string, sizeof(string), &blobResult) : BlobResult::NewBuf(string, sizeof(string), &blobResult));

    // Fails because UTF-16 expects a two-byte NULL terminator.
    VERIFY_FAILED(GetStringResultFromBlobResult(blobResult, DEFSTRING_ENCODING_UTF16, &stringResult, true));

    VERIFY_SUCCEEDED(GetStringResultFromBlobResult(blobResult, DEFSTRING_ENCODING_ASCII, &stringResult, true));

    VERIFY_ARE_EQUAL(wcscmp(L"foobar", stringResult.GetRef()), 0);

    // This should have created a copy of the buffer.
    VERIFY_IS_TRUE(blobResult->GetRef(nullptr) != stringResult.GetRef());
    VERIFY_IS_TRUE(stringResult.GetStringResult()->pBuf != nullptr);
    VERIFY_IS_TRUE(stringResult.GetStringResult()->cchBuf != 0);
    VERIFY_ARE_EQUAL(stringResult.GetStringResult()->pBuf, stringResult.GetStringResult()->pRef);

    delete blobResult;
}

// ANSI strings are interesting.
// An ANSI string converts up cleanly to UTF-16. However, if you think it is ANSI and it actually
// is UTF-8 then you get a garbled string. The conversion still passes, you never read over the buffer end.
// Since we control what writes these strings we don't check at runtime if it really is ASCII
// to avoid the perf hit. However, to ensure we don't have bugs we do check on debug builds.
void BlobResultUnitTests::AnsiInsteadOfAsciiStringTests(bool useReference)
{
    char string[] = "³fÿÿbar±²"; // This is a string that contains ANSI characters.

    StringResult stringResult;
    BlobResult* blobResult;
    VERIFY_SUCCEEDED(
        useReference ? BlobResult::NewRef(string, sizeof(string), &blobResult) : BlobResult::NewBuf(string, sizeof(string), &blobResult));

#ifdef DBG

    // Fails on debug builds since we check there.
    VERIFY_IS_FALSE(GetStringResultFromBlobResult(blobResult, DEFSTRING_ENCODING_ASCII, &stringResult, true));

#else

    // Succeeds on retail builds since we don't check there.
    VERIFY_SUCCEEDED(GetStringResultFromBlobResult(blobResult, DEFSTRING_ENCODING_ASCII, &stringResult, true));

    Log::Comment(stringResult.GetRef());

    VERIFY_ARE_EQUAL(wcscmp(L"³fÿÿbar±²", stringResult.GetRef()), 0);

    // This should have created a copy of the buffer.
    VERIFY_IS_TRUE(blobResult->GetRef(nullptr) != stringResult.GetRef());
    VERIFY_IS_TRUE(stringResult.GetStringResult()->pBuf != nullptr);
    VERIFY_IS_TRUE(stringResult.GetStringResult()->cchBuf != 0);
    VERIFY_ARE_EQUAL(stringResult.GetStringResult()->pBuf, stringResult.GetStringResult()->pRef);
#endif

    delete blobResult;
}

void BlobResultUnitTests::Utf8InsteadOfAsciiStringTests(bool useReference)
{
    // This list contains no ASCII strings.
    PCWSTR const c_pszStringsToTest[] = {
        L"©",
        L"ab©cd",
        L"©Ö",
        L"©ÖĆ",
        L"ûhæ",
        L"┌╟●☺",
        L"ﬕײַﬥ﬩",
        L"ﬕײַⱶⱩⱭ",
        L"!1QAﬕײַⱶⱩⱭ",
        L"ûhæ123",
        L"a┌╟●☺a",
        L"11vvﬕײַﬥ﬩",
        L"aﬕײַⱶⱩⱭ18@1",
        L"𥧄foo╔╩╦═╬𥧄123!@#𥧄",
        // These are compliance test cases.
        L"中文",
        L"⒈①Ⅻㄨㄩ",
        L"啊阿鼾齄",
        L"丂丄狚狛",
        L"狜狝﨨﨩",
        L"ˊˋ˙–〇",
        L"㐀㐁䶴䶵",
        L"𠀀𠀁𪛕𪛖",
        L"བོད་ཡིག   ༀ༁༂༃༄༅ྡྷྣྤྥ",
        L"དབྱངས་ཅན་སྒྲོལ་དཀར། བཀྲ་ཤིས་རྒྱལ།",
        L"ئۇيغۇر تىلى   ;؋ ، ؍ ؎ ؏ؐ   ﻲ ﻳ ﻴ ﻵ ﻶ ﻷ ﻸ ﻹ ﻺ ﻻ",
        L"ۋېڭكقق ھس قك كدسدق د",
        L"ᠮᠣᠩᠭᠣᠯ  ᠦᠰᠦᠭ ᢎᢏᢐᢑᢒᢓᢔᢕᢖᢗ",
        L"ᠣᠺᠵᠡᠵᠺᠰ ᠬᠵᠠᠬᠳᠰᠣᠬᠡᠵᠬ ᠬᠵᠺᠠᠬᠳᠰ ᠺᠬᠣ ᠠ",
        L"ꆈꌠꁱꂷ;ꀀꀁꀂꀃꀄꀅꀆ꓁꓂꓃꓄꓅꓆",
        L"ꉬꄒꐵꄓꐨꐵꄓꐨ",
        L"ᥘᥣᥭᥰ ᥖᥭᥰ ᥖᥬᥲᥑᥨᥒᥰ",
        L"ᦎᦷᦑᦺᦖᦺᧈᦉᦲᧇᦉᦸᧂᦗᧃᦓᦱ",
    };

    for (unsigned int i = 0; i < ARRAYSIZE(c_pszStringsToTest); i++)
    {
        const wchar_t* const stringUtf16 = c_pszStringsToTest[i];
        char stringUtf8[128];

        // This is needed because the compiler doesn't like both UTF-8 and UTF-16 in the same file.
        int utf8Length = WideCharToMultiByte(CP_UTF8, 0, stringUtf16, -1, stringUtf8, ARRAYSIZE(stringUtf8), nullptr, nullptr);

        VERIFY_IS_TRUE(utf8Length != 0);

        StringResult stringResult;
        BlobResult* blobResult;
        VERIFY_SUCCEEDED(
            useReference ? BlobResult::NewRef(stringUtf8, utf8Length, &blobResult) :
                           BlobResult::NewBuf(stringUtf8, utf8Length, &blobResult));

#ifdef DBG

        // Fails on debug builds since we check there.
        VERIFY_FAILED(GetStringResultFromBlobResult(blobResult, DEFSTRING_ENCODING_ASCII, &stringResult, true));

#else

        // Succeeds on retail builds since we don't check there.
        VERIFY_SUCCEEDED(GetStringResultFromBlobResult(blobResult, DEFSTRING_ENCODING_ASCII, &stringResult, true));

        // Since we had a corrupted string it doesn't round trip cleanly.
        VERIFY_IS_TRUE(wcscmp(stringUtf16, stringResult.GetRef()) != 0);

        // This should have created a copy of the buffer.
        VERIFY_IS_TRUE(blobResult->GetRef(nullptr) != stringResult.GetRef());
        VERIFY_IS_TRUE(stringResult.GetStringResult()->pBuf != nullptr);
        VERIFY_IS_TRUE(stringResult.GetStringResult()->cchBuf != 0);
        VERIFY_ARE_EQUAL(stringResult.GetStringResult()->pBuf, stringResult.GetStringResult()->pRef);

#endif

        delete blobResult;
    }
}

void BlobResultUnitTests::Utf8StringTests(bool useReference)
{
    PCWSTR const c_pszStringsToTest[] = {
        L"foo",
        L"",
        L"!@#$~19az",
        L"©",
        L"ab©cd",
        L"©Ö",
        L"©ÖĆ",
        L"ûhæ",
        L"┌╟●☺",
        L"ﬕײַﬥ﬩",
        L"ﬕײַⱶⱩⱭ",
        L"!1QAﬕײַⱶⱩⱭ",
        L"ûhæ123",
        L"a┌╟●☺a",
        L"11vvﬕײַﬥ﬩",
        L"aﬕײַⱶⱩⱭ18@1",
        L"𥧄foo╔╩╦═╬𥧄123!@#𥧄",
        // These are compliance test cases.
        L"中文",
        L"⒈①Ⅻㄨㄩ",
        L"啊阿鼾齄",
        L"丂丄狚狛",
        L"狜狝﨨﨩",
        L"ˊˋ˙–〇",
        L"㐀㐁䶴䶵",
        L"𠀀𠀁𪛕𪛖",
        L"བོད་ཡིག   ༀ༁༂༃༄༅ྡྷྣྤྥ",
        L"དབྱངས་ཅན་སྒྲོལ་དཀར། བཀྲ་ཤིས་རྒྱལ།",
        L"ئۇيغۇر تىلى   ;؋ ، ؍ ؎ ؏ؐ   ﻲ ﻳ ﻴ ﻵ ﻶ ﻷ ﻸ ﻹ ﻺ ﻻ",
        L"ۋېڭكقق ھس قك كدسدق د",
        L"ᠮᠣᠩᠭᠣᠯ  ᠦᠰᠦᠭ ᢎᢏᢐᢑᢒᢓᢔᢕᢖᢗ",
        L"ᠣᠺᠵᠡᠵᠺᠰ ᠬᠵᠠᠬᠳᠰᠣᠬᠡᠵᠬ ᠬᠵᠺᠠᠬᠳᠰ ᠺᠬᠣ ᠠ",
        L"ꆈꌠꁱꂷ;ꀀꀁꀂꀃꀄꀅꀆ꓁꓂꓃꓄꓅꓆",
        L"ꉬꄒꐵꄓꐨꐵꄓꐨ",
        L"ᥘᥣᥭᥰ ᥖᥭᥰ ᥖᥬᥲᥑᥨᥒᥰ",
        L"ᦎᦷᦑᦺᦖᦺᧈᦉᦲᧇᦉᦸᧂᦗᧃᦓᦱ",
    };

    for (unsigned int i = 0; i < ARRAYSIZE(c_pszStringsToTest); i++)
    {
        const wchar_t* const stringUtf16 = c_pszStringsToTest[i];
        char stringUtf8[128];

        // This is needed because the compiler doesn't like both UTF-8 and UTF-16 in the same file.
        int utf8Length = WideCharToMultiByte(CP_UTF8, 0, stringUtf16, -1, stringUtf8, ARRAYSIZE(stringUtf8), nullptr, nullptr);

        VERIFY_IS_TRUE(utf8Length != 0);

        StringResult stringResult;
        BlobResult* blobResult;
        VERIFY_SUCCEEDED(
            useReference ? BlobResult::NewRef(stringUtf8, utf8Length, &blobResult) :
                           BlobResult::NewBuf(stringUtf8, utf8Length, &blobResult));

        // Fails because UTF-16 expects a two-byte NULL terminator.
        VERIFY_FAILED(GetStringResultFromBlobResult(blobResult, DEFSTRING_ENCODING_UTF16, &stringResult, true));

        VERIFY_SUCCEEDED(GetStringResultFromBlobResult(blobResult, DEFSTRING_ENCODING_UTF8, &stringResult, true));

        VERIFY_ARE_EQUAL(wcscmp(stringUtf16, stringResult.GetRef()), 0);

        // This should have created a copy of the buffer.
        VERIFY_IS_TRUE(blobResult->GetRef(nullptr) != stringResult.GetRef());
        VERIFY_IS_TRUE(stringResult.GetStringResult()->pBuf != nullptr);
        VERIFY_IS_TRUE(stringResult.GetStringResult()->cchBuf != 0);
        VERIFY_ARE_EQUAL(stringResult.GetStringResult()->pBuf, stringResult.GetStringResult()->pRef);

        delete blobResult;
    }
}

void BlobResultUnitTests::Utf16StringTests(bool useReference)
{
    PCWSTR const c_pszStringsToTest[] = {
        L"foo",
        L"",
        L"!@#$~19az",
        L"©",
        L"ab©cd",
        L"©Ö",
        L"©ÖĆ",
        L"ûhæ",
        L"┌╟●☺",
        L"ﬕײַﬥ﬩",
        L"ﬕײַⱶⱩⱭ",
        L"!1QAﬕײַⱶⱩⱭ",
        L"ûhæ123",
        L"a┌╟●☺a",
        L"11vvﬕײַﬥ﬩",
        L"aﬕײַⱶⱩⱭ18@1",
        L"𥧄foo╔╩╦═╬𥧄123!@#𥧄",
        // These are compliance test cases.
        L"中文",
        L"⒈①Ⅻㄨㄩ",
        L"啊阿鼾齄",
        L"丂丄狚狛",
        L"狜狝﨨﨩",
        L"ˊˋ˙–〇",
        L"㐀㐁䶴䶵",
        L"𠀀𠀁𪛕𪛖",
        L"བོད་ཡིག   ༀ༁༂༃༄༅ྡྷྣྤྥ",
        L"དབྱངས་ཅན་སྒྲོལ་དཀར། བཀྲ་ཤིས་རྒྱལ།",
        L"ئۇيغۇر تىلى   ;؋ ، ؍ ؎ ؏ؐ   ﻲ ﻳ ﻴ ﻵ ﻶ ﻷ ﻸ ﻹ ﻺ ﻻ",
        L"ۋېڭكقق ھس قك كدسدق د",
        L"ᠮᠣᠩᠭᠣᠯ  ᠦᠰᠦᠭ ᢎᢏᢐᢑᢒᢓᢔᢕᢖᢗ",
        L"ᠣᠺᠵᠡᠵᠺᠰ ᠬᠵᠠᠬᠳᠰᠣᠬᠡᠵᠬ ᠬᠵᠺᠠᠬᠳᠰ ᠺᠬᠣ ᠠ",
        L"ꆈꌠꁱꂷ;ꀀꀁꀂꀃꀄꀅꀆ꓁꓂꓃꓄꓅꓆",
        L"ꉬꄒꐵꄓꐨꐵꄓꐨ",
        L"ᥘᥣᥭᥰ ᥖᥭᥰ ᥖᥬᥲᥑᥨᥒᥰ",
        L"ᦎᦷᦑᦺᦖᦺᧈᦉᦲᧇᦉᦸᧂᦗᧃᦓᦱ",
    };

    for (unsigned int i = 0; i < ARRAYSIZE(c_pszStringsToTest); i++)
    {
        const wchar_t* const string = c_pszStringsToTest[i];

        StringResult stringResult;
        BlobResult* blobResult;
        VERIFY_SUCCEEDED(
            useReference ? BlobResult::NewRef(string, (wcslen(string) + 1) * sizeof(wchar_t), &blobResult) :
                           BlobResult::NewBuf(string, (wcslen(string) + 1) * sizeof(wchar_t), &blobResult));

        const void* bufferReference = blobResult->GetRef(nullptr);

        VERIFY_SUCCEEDED(GetStringResultFromBlobResult(blobResult, DEFSTRING_ENCODING_UTF16, &stringResult, true));

        VERIFY_IS_TRUE(stringResult.GetRef() != nullptr);
        VERIFY_ARE_EQUAL(wcscmp(string, stringResult.GetRef()), 0);

        // This should *not* have created a copy of the buffer.
        // Instead, the string result will take over the buffer if it was owned, or just take another reference if it wasn't.
        if (useReference)
        {
            VERIFY_ARE_EQUAL(blobResult->GetRef(nullptr), stringResult.GetRef());

            VERIFY_ARE_EQUAL(stringResult.GetStringResult()->cchBuf, 0u);
            VERIFY_ARE_EQUAL(stringResult.GetStringResult()->pBuf, nullptr);
        }
        else
        {
            VERIFY_ARE_EQUAL(blobResult->GetRef(nullptr), nullptr);

            VERIFY_IS_TRUE(stringResult.GetStringResult()->cchBuf != 0);
            VERIFY_ARE_EQUAL(stringResult.GetStringResult()->pBuf, stringResult.GetStringResult()->pRef);
        }

        // This should still be the original buffer content.
        VERIFY_ARE_EQUAL(stringResult.GetRef(), bufferReference);

        delete blobResult;
    }
}

void BlobResultUnitTests::AsciiStringConversionFromReference(void) { AsciiStringTests(true); }

void BlobResultUnitTests::AsciiStringConversionFromBuffer(void) { AsciiStringTests(false); }

void BlobResultUnitTests::AnsiInsteadOfAsciiStringConversionFromReference(void) { AnsiInsteadOfAsciiStringTests(true); }

void BlobResultUnitTests::AnsiInsteadOfAsciiStringConversionFromBuffer(void) { AnsiInsteadOfAsciiStringTests(false); }

void BlobResultUnitTests::Utf8InsteadOfAsciiStringConversionFromReference(void) { Utf8InsteadOfAsciiStringTests(true); }

void BlobResultUnitTests::Utf8InsteadOfAsciiStringConversionFromBuffer(void) { Utf8InsteadOfAsciiStringTests(false); }

void BlobResultUnitTests::Utf8StringConversionFromReference(void) { Utf8StringTests(true); }

void BlobResultUnitTests::Utf8StringConversionFromBuffer(void) { Utf8StringTests(false); }

void BlobResultUnitTests::Utf16StringConversionFromReference(void) { Utf16StringTests(true); }

void BlobResultUnitTests::Utf16StringConversionFromBuffer(void) { Utf16StringTests(false); }

void BlobResultUnitTests::InvalidTests(void)
{
    BlobResult self;
    BlobResult* nullResult = nullptr;

    // null arguments
    VERIFY(self.Compare(nullResult) == Def_CompareError);
}
} // namespace UnitTests