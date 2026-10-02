// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "mrm/common/BaseInternal.h"
#include "mrm/common/Base.h"

BOOLEAN
DefString_IsEmpty(__in PCWSTR pSelf) { return ((!pSelf) || (!pSelf[0])); }

static DEFCOMPARISON _IntToComparison(int cmpval)
{
    // Interpret result as DEFCOMPARISON
    if (cmpval == _NLSCMPERROR)
    {
        return Def_CompareError;
    }
    else if (cmpval < 0)
    {
        return Def_Less;
    }
    else if (cmpval > 0)
    {
        return Def_Greater;
    }
    else
    {
        return Def_Equal;
    }
}

#pragma warning(push)
#pragma warning(disable : 4995)

DEFCOMPARISON
DefString_CompareWithOptions(__in PCWSTR pSelf, __in PCWSTR pOther, __in DEFCOMPAREOPTIONS options)
{
    switch (options)
    {
    case DefCompare_Default:
        return _IntToComparison((CompareStringOrdinal(pSelf, -1, pOther, -1, FALSE) - 2));
    case DefCompare_CaseInsensitive:
        return _IntToComparison((CompareStringOrdinal(pSelf, -1, pOther, -1, TRUE) - 2));
    }
    return Def_CompareError;
}

DEFCOMPARISON
DefString_CchCompareWithOptions(__in PCWSTR pSelf, __in PCWSTR pOther, __in size_t cchMax, __in DEFCOMPAREOPTIONS options)
{
    size_t cchSelf = min(wcslen(pSelf), cchMax);
    size_t cchOther = min(wcslen(pOther), cchMax);

    switch (options)
    {
    case DefCompare_Default:
        return _IntToComparison((CompareStringOrdinal(pSelf, (int)cchSelf, pOther, (int)cchOther, FALSE) - 2));
    case DefCompare_CaseInsensitive:
        return _IntToComparison((CompareStringOrdinal(pSelf, (int)cchSelf, pOther, (int)cchOther, TRUE) - 2));
    }
    return Def_CompareError;
}

BOOLEAN
DefString_IsPrefixWithOptions(__in PCWSTR pPrefix, __in PCWSTR pString, __in DEFCOMPAREOPTIONS options)
{
    if ((!pPrefix) || (!pPrefix[0]))
    {
        // Empty string is a prefix of anything
        return TRUE;
    }
    if ((!pString) || (!pString[0]))
    {
        // Empty string has no prefix
        return FALSE;
    }

    if (options == DefCompare_CaseInsensitive)
    {
        while ((*pPrefix) && (*pString))
        {
            if (towupper(*pPrefix) != towupper(*pString))
            {
                return FALSE;
            }
            pPrefix++;
            pString++;
        }
    }
    else
    {
        while ((*pPrefix) && (*pString))
        {
            if (*pPrefix != *pString)
            {
                return FALSE;
            }
            pPrefix++;
            pString++;
        }
    }

    return ((*pPrefix) == '\0');
}

BOOLEAN
DefString_IsSuffixWithOptions(__in PCWSTR pSuffix, __in PCWSTR pString, __in DEFCOMPAREOPTIONS options)
{
    HRESULT hr = S_OK;
    size_t cchSuffix;
    size_t cchString;

    if ((!pSuffix) || (!pSuffix[0]))
    {
        // Empty string is a suffix of anything
        return TRUE;
    }
    if ((!pString) || (!pString[0]))
    {
        // Empty string has no suffix
        return FALSE;
    }

    hr = _DefStringCchLength(pSuffix, _DEF_STRSAFE_MAX_CCH, &cchSuffix);
    if (FAILED(hr))
    {
        return FALSE;
    }

    hr = _DefStringCchLength(pString, _DEF_STRSAFE_MAX_CCH, &cchString);
    if (FAILED(hr))
    {
        return FALSE;
    }

    if (cchString < cchSuffix)
    {
        // Suffix length is greater than that of given string, return false.
        return FALSE;
    }
    else
    {
        // Suffix length is lesser than or equal to that of given string,
        // position given string corresponding to suffix.
        pString += cchString - cchSuffix;
    }

    return (Def_Equal == DefString_CompareWithOptions(pSuffix, pString, options));
}

#define ASCII_BOUNDARY 0x7F

#define UTF8_ONE_BYTE_BOUNDARY 0x7F
#define UTF8_TWO_BYTE_BOUNDARY 0x07FF
#define UTF8_THREE_BYTE_BOUNDARY 0xFFFF

#define UTF16_BMP_FIRST_BATCH_END 0xD7FF
#define UTF16_BMP_SECOND_BATCH_START 0xE000

#define UTF_16_LEAD_SURROGATE_MIN_VALUE 0xD800
#define UTF_16_LEAD_SURROGATE_MAX_VALUE 0xDBFF

#define UTF_16_TRAIL_SURROGATE_MIN_VALUE 0xDC00
#define UTF_16_TRAIL_SURROGATE_MAX_VALUE 0xDFFF
#define UTF_16_SUPPLEMENTARY_PLANES_START 0x10000

#define UNICODE_MAX_CODEPOINT 0x10FFFF

// Returns the encoding that results in the smallest needed buffer. Accounts for NULL terminator.
// If ASCII is possible it picks ASCII over UTF8 because it is easier to decode.
// If UTF8 and UTF16 produce the exact same size, it picks UTF16 because that is the encoding we use publicly.

// This function has no error model. If an invalid code point is passed in, it returns UTF-16.
// Why? Because we pass UTF-16 through without transformation (meaning invalid code points won't produce a break),
// and we cannot block on invalid code points because we didn't do this in the past and want to avoid changing behavior.

// This function is hand-rolled because it sits at a point in the stack where we cannot call many helpers.// This function is hand-rolled because it sits at a point in the stack where we cannot call many helpers,
// and the helpers it can call (eg, RtlUTF8ToUnicodeN) are not available downlevel.
DEFSTRING_ENCODING
DefString_ChooseBestEncoding(_In_ PCWSTR pszStringUtf16)
{
    PCWSTR pszRemainingStringUtf16 = pszStringUtf16;
    size_t cbStringUtf16;
    size_t cbStringUtf8 = 1; // 1 to account for the single-byte NULL terminator.
    BOOL fAllAscii = TRUE;

    while (pszRemainingStringUtf16[0] != L'\0')
    {

        UINT32 firstCodeUnitOfCurrentCharacter = (UINT32)pszRemainingStringUtf16[0];

        // See if it is in the basic multilingual plane.
        if (firstCodeUnitOfCurrentCharacter <= UTF16_BMP_FIRST_BATCH_END || firstCodeUnitOfCurrentCharacter >= UTF16_BMP_SECOND_BATCH_START)
        {
            // It's a two byte UTF-16 character. Move string up one character.
            pszRemainingStringUtf16++;

            // Next we have to determine if it is a single, double, triple-byte UTF-8 character.
            if (firstCodeUnitOfCurrentCharacter <= UTF8_ONE_BYTE_BOUNDARY)
            {
                // Single-byte UTF-8 strings are more efficiently encoded in ASCII, so leave fAllAscii as true;
                cbStringUtf8++;
            }
            else if (firstCodeUnitOfCurrentCharacter <= UTF8_TWO_BYTE_BOUNDARY)
            {
                // We cannot encode characters above 127 as ASCII so disallow ASCII for the entire string.
                fAllAscii = FALSE;
                cbStringUtf8 += 2;
            }
            else
            {
                fAllAscii = FALSE;
                cbStringUtf8 += 3;
            }
        }
        else if (
            firstCodeUnitOfCurrentCharacter >= UTF_16_LEAD_SURROGATE_MIN_VALUE &&
            firstCodeUnitOfCurrentCharacter <= UTF_16_LEAD_SURROGATE_MAX_VALUE)
        {
            // It's a four-byte UTF-8 and UTF-16 character.
            UINT32 secondCodeUnitOfCurrentCharacter = (UINT32)pszRemainingStringUtf16[1];
            if (secondCodeUnitOfCurrentCharacter < UTF_16_TRAIL_SURROGATE_MIN_VALUE ||
                secondCodeUnitOfCurrentCharacter > UTF_16_TRAIL_SURROGATE_MAX_VALUE)
            {
                // This is an invalid code point. Return UTF-16 to ensure the string is passed through the pipeline without processing.
                return DEFSTRING_ENCODING_UTF16;
            }

            pszRemainingStringUtf16 += 2;

            fAllAscii = FALSE;
            cbStringUtf8 += 4;
        }
        else
        {
            // This is an invalid code point. Return UTF-16 to ensure the string is passed through the pipeline without processing.
            return DEFSTRING_ENCODING_UTF16;
        }
    }

    // + 1 to account for the NULL terminator.
    cbStringUtf16 = (pszRemainingStringUtf16 - pszStringUtf16 + 1) * sizeof(pszStringUtf16[0]);

    if (fAllAscii)
    {

        return DEFSTRING_ENCODING_ASCII;
    }
    else if (cbStringUtf16 <= cbStringUtf8)
    {
        // If the strings are equal in size return UTF16 since it's easier to decode.
        return DEFSTRING_ENCODING_UTF16;
    }
    else
    {

        return DEFSTRING_ENCODING_UTF8;
    }
}

// Converts an ASCII encoded string into a UTF-16-encoded one.
// Returns NULL on failure.

// This function is hand-rolled because it sits at a point in the stack where we cannot call many helpers,
// and the helpers it can call (eg, RtlUTF8ToUnicodeN) are not available downlevel.
HRESULT
DefString_ConvertAsciiToUtf16(
    _In_reads_(cchStringAsciiIncludingNull) PCSTR pszStringAscii,
    _Pre_satisfies_(cchStringAsciiIncludingNull > 0) size_t cchStringAsciiIncludingNull,
    _Outptr_ PWSTR* result)
{
    *result = nullptr;

    PWSTR pszRet;
    DEF_ASSERT(cchStringAsciiIncludingNull >= 1);

    pszRet = _DefArray_Alloc(WCHAR, cchStringAsciiIncludingNull);
    if (pszRet == nullptr)
    {

        return E_OUTOFMEMORY;
    }

    for (size_t i = 0; i < cchStringAsciiIncludingNull; i++)
    {

        // Since we control who creates these strings we don't test for them being ASCII here for performance reasons.
        // Even if they are not, they will convert up cleanly if they are ANSI and will convert into garbage but won't
        // produce a failure if they are UTF-8 or garbage to begin with. We will never read over the end of the buffer
        // or do other truly bad things so the extra check is not worth it.
        // We still do the check on debug builds to catch any potential violations of the "is always ASCII in the PRI file"
        // invariant or other bugs.

#ifdef DBG

        if (((unsigned char)pszStringAscii[i]) > ASCII_BOUNDARY)
        {

            _DefFree(pszRet);
            return E_INVALIDARG;
        }
#endif

        // Even though this compiles without the cast, the cast is critical to avoid the compiler doing sign extension
        // when the string isn't ASCII.
        pszRet[i] = (unsigned char)(pszStringAscii[i]);
    }

    *result = pszRet;

    return S_OK;
}

// Converts an UTF-8 encoded string into a UTF-16-encoded one.
// Returns NULL on failure.
HRESULT
DefString_ConvertUtf8ToUtf16(
    _In_reads_bytes_(cbStringUtf8IncludingNull) PCSTR pszStringUtf8,
    _Pre_satisfies_(cbStringUtf8IncludingNull > 0) size_t cbStringUtf8IncludingNull,
    _Out_ size_t* cchStringUtf16IncludingNull,
    _Outptr_ PWSTR* result)
{
    *result = nullptr;

    DEF_ASSERT(cbStringUtf8IncludingNull > 0);

    *cchStringUtf16IncludingNull = 0;

    int cchStringUtf16IncludingNullLocal =
        MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, pszStringUtf8, (int)cbStringUtf8IncludingNull, nullptr, 0);
    if (cchStringUtf16IncludingNullLocal == 0)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    PWSTR pszRet = _DefArray_Alloc(WCHAR, cchStringUtf16IncludingNullLocal);
    if (pszRet == nullptr)
    {
        return E_OUTOFMEMORY;
    }

    cchStringUtf16IncludingNullLocal = MultiByteToWideChar(
        CP_UTF8, MB_ERR_INVALID_CHARS, pszStringUtf8, (int)cbStringUtf8IncludingNull, pszRet, cchStringUtf16IncludingNullLocal);
    if (cchStringUtf16IncludingNullLocal == 0)
    {
        _DefFree(pszRet);
        return HRESULT_FROM_WIN32(GetLastError());
    }

    *cchStringUtf16IncludingNull = cchStringUtf16IncludingNullLocal;

    *result = pszRet;
    return S_OK;
}

DEFCOMPARISON
DefBlob_Compare(__in const void* pSelf, __in const void* pOther, __in size_t cbCmp)
{
    return _IntToComparison(memcmp(pSelf, pOther, cbCmp));
}

HRESULT
DefString_CchCopy(_Out_writes_(cchDest) PWSTR pDest, _In_ size_t cchDest, _In_ PCWSTR pSrc)
{
    return _DefStringCchCopy(pDest, cchDest, pSrc);
}

HRESULT
DefString_Dup(__in PCWSTR pString, _Outptr_ PWSTR* result)
{
    *result = nullptr;

    size_t len;
    PWSTR pRtrn = nullptr;
    if (!pString)
    {
        return S_OK;
    }
    len = wcslen(pString);
    pRtrn = _DefArray_AllocZeroed(WCHAR, len + 1);
    if (pRtrn == nullptr)
    {
        return E_OUTOFMEMORY;
    }
    memcpy(pRtrn, pString, sizeof(WCHAR) * (len + 1));
    *result = pRtrn;
    return S_OK;
}

_Success_(return ) BOOLEAN DefString_ToInteger(_In_ PCWSTR str, _Out_opt_ int* valueAsInteger)
{
    PCWSTR tmp = str;

    while (*tmp != L'\0')
    {
        if (!iswdigit(*tmp))
        {
            return FALSE;
        }
        tmp++;
    }

    if (tmp != str) // empty string is not integer
    {
        if (valueAsInteger != nullptr)
        {
            *valueAsInteger = _wtoi(str);
        }
        return TRUE;
    }

    return FALSE;
}

#pragma warning(pop)

HRESULT
ErrnoToHResult(__in errno_t err)
{
    switch (err)
    {
    case 0:
        return S_OK;
    case EACCES:
        return HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED);
    case EBADF:
        return HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
    case EEXIST:
        return HRESULT_FROM_WIN32(ERROR_ALREADY_EXISTS);
    case ENOENT:
        return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
    case EISDIR:
        return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
    case EFBIG:
        return HRESULT_FROM_WIN32(ERROR_FILE_TOO_LARGE);
    case ENOMEM:
        return E_OUTOFMEMORY;
    case EINVAL:
        return E_INVALIDARG;
    case ERANGE:
        return E_INVALIDARG;
    default:
        return E_FAIL;
    }
}

__checkReturn size_t _DefArray_Size(__in size_t cbElem, __in size_t nElems)
{
    size_t cbArray;

    if (FAILED(_DefSizeTMult(nElems, cbElem, &cbArray)))
    {
        return 0;
    }

    return cbArray;
}

_Use_decl_annotations_ HRESULT _DefArray_ExpandBySize(void* pOld, size_t cbElem, size_t nOldElems, size_t nNewElems, void** result)
{
    *result = nullptr;

    void* pNew;
    size_t cbOld = 0;
    size_t cbNew = 0;

    if (nOldElems >= nNewElems)
    {
        return E_INVALIDARG;
    }

    HRESULT hr = _DefSizeTMult(cbElem, nNewElems, &cbNew);
    if (FAILED(hr))
    {
        return hr;
    }

    hr = _DefSizeTMult(cbElem, nOldElems, &cbOld);
    if (FAILED(hr))
    {
        return hr;
    }

    if ((pOld == nullptr) && (nOldElems != 0))
    {
        return E_INVALIDARG;
    }

    pNew = _DefBlob_AllocZeroed(cbNew);
    if (pNew == nullptr)
    {
        return E_OUTOFMEMORY;
    }

    if (pOld)
    {
        if (cbOld > 0)
        {
            errno_t err = memcpy_s(pNew, cbNew, pOld, cbOld);
            hr = ErrnoToHResult(err);
            if (FAILED(hr))
            {
                _DefFree(pNew);
                return hr;
            }
        }
        _DefFree(pOld);
    }

    *result = pNew;
    return S_OK;
}

BOOLEAN
_DefArray_TryEnsureSizeByElemSize(
    __in_bcount(cbElem* nOldElems) void* pOld,
    __in size_t cbElem,
    __in size_t nOldElems,
    __in size_t nNewElems,
    __deref_out_bcount(cbElem* nNewElems) void** ppNewOut)
{
    if (ppNewOut != nullptr)
    {
        *ppNewOut = nullptr;
    }

    if ((cbElem == 0) || (nNewElems == 0))
    {
        *ppNewOut = pOld;
        return FALSE;
    }

    if (nNewElems <= nOldElems)
    {
        return TRUE;
    }

    void* pNew;
    if (SUCCEEDED(_DefArray_ExpandBySize(pOld, cbElem, nOldElems, nNewElems, &pNew)))
    {
        *ppNewOut = pNew;
        // pOld is now invalid (freed by expand)
        return TRUE;
    }
    return FALSE;
}

_Success_(return == true)
BOOLEAN
_DefArray_TryExpandAndRelocate(
    __in_bcount(cbElem* oldSize) void* pOld,
    __in size_t cbElem,
    __in size_t oldSize,
    __in size_t newSize,
    __in size_t offset,
    __deref_out_bcount(cbElem* newSize) void** ppNewOut)
{
    if ((cbElem == 0) || (newSize == 0) || (newSize < oldSize))
    {
        return FALSE;
    }

    if ((pOld == nullptr) && (oldSize != 0))
    {
        return FALSE;
    }

    size_t cbOld = 0;
    size_t cbNew = 0;
    size_t cbOffset = 0;
    void* pNew = nullptr;

    if (FAILED(_DefSizeTMult(cbElem, oldSize, &cbOld)) || FAILED(_DefSizeTMult(cbElem, newSize, &cbNew)) ||
        FAILED(_DefSizeTMult(cbElem, offset, &cbOffset)))
    {
        return FALSE;
    }

    if ((cbOffset + cbOld) > cbNew)
    {
        return FALSE;
    }

    pNew = _DefBlob_AllocZeroed(cbNew);
    if (pNew == nullptr)
    {
        return FALSE;
    }

    if (pOld)
    {
        if (cbOld > 0)
        {
            errno_t err = memcpy_s(((BYTE*)pNew) + cbOffset, cbNew - cbOffset, pOld, cbOld);
            HRESULT hr = ErrnoToHResult(err);
            if (FAILED(hr))
            {
                _DefFree(pNew);
                return FALSE;
            }
        }
        _DefFree(pOld);
    }
    *ppNewOut = pNew;
    return TRUE;
}

// Caller must free the returned buffer.
PWSTR _DefDuplicateString(__in PCWSTR Source)
{
    PWSTR Dup = nullptr;
    size_t Len = wcslen(Source) + 1;

    Dup = (PWSTR)_DefPlatformAllocZeroed(Len * sizeof(WCHAR));
    if (!Dup)
    {
        return nullptr;
    }

    _DefStringCchCopy(Dup, Len, Source);

    return Dup;
}

#ifdef DEF_RTL
int __cdecl _purecall(void)
{
    // TODO - consider whether we should do some error reporting here.  This function
    // exists only to prevent linker errors when compiling in non-MSVCRT environments.
    return 0;
}
#endif
