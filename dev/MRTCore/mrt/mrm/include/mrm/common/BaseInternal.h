// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "mrm/common/Base.h"

#ifdef __cplusplus
extern "C"
{
#endif

    _Check_return_ size_t _DefArray_Size(_In_ size_t elemSizeInBytes, _In_ size_t numElems);

    /*!
     * Expands an array, copying nOldElems from the old array to the new.  If
     * allocation fails, the old data is  unaffected.  If allocation succeeds,
     * the old array is freed.
     * NOTE: _Can_ be used to grow a null array from 0 elems.
     * NOTE: Returns NULL if nOldElems is greater or equal to nNewElems.
     */

    _Check_return_ extern HRESULT _DefArray_ExpandBySize(
        _In_reads_bytes_opt_(elemSizeInBytes* numOldElems) void* existingPtr,
        _In_ size_t elemSizeInBytes,
        _In_ size_t numOldElems,
        _In_ size_t numNewElems,
        _Outptr_result_bytebuffer_(numNewElems* elemSizeInBytes) void** result);

    _Success_(return == true) extern BOOLEAN _DefArray_TryEnsureSizeByElemSize(
        _In_reads_bytes_opt_(elemSizeInBytes* numOldElems) void* existingPtr,
        _In_ size_t elemSizeInBytes,
        _In_ size_t numOldElems,
        _In_ size_t numNewElems,
        _Outptr_result_bytebuffer_(elemSizeInBytes* numNewElems) void** newPtr);

    _Success_(return == true) extern BOOLEAN _DefArray_TryExpandAndRelocate(
        _In_reads_bytes_opt_(elemSizeInBytes* oldSize) void* existingPtr,
        _In_ size_t elemSizeInBytes,
        _In_ size_t oldSize,
        _In_ size_t newSize,
        _In_ size_t offset,
        _Outptr_result_bytebuffer_(elemSizeInBytes* newSize) void** newPtr);

#ifndef __cplusplus
#define _DEF_STATIC_CAST(TYPE) (TYPE)
#define _DEF_REINTERPRET_CAST(TYPE) (TYPE)
#else
#define _DEF_STATIC_CAST(TYPE) static_cast<TYPE>
#define _DEF_REINTERPRET_CAST(TYPE) reinterpret_cast<TYPE>
#endif

#define _DefBlob_Alloc(SZ) _DefPlatformAlloc((SZ))
#define _DefBlob_AllocZeroed(SZ) _DefPlatformAllocZeroed((SZ))
#define _DefFree(PTR) _DefPlatformFree((PTR))

#define _DefAlloc(TYPE) (_DEF_STATIC_CAST(TYPE*)(_DefBlob_Alloc(sizeof(TYPE))))
#define _DefAllocZeroed(TYPE) (_DEF_STATIC_CAST(TYPE*)(_DefBlob_AllocZeroed(sizeof(TYPE))))
#define _DefArray_Alloc(TYPE, SIZE) \
    ((_DefArray_Size(sizeof(TYPE), SIZE) > 0) ? (_DEF_STATIC_CAST(TYPE*)(_DefBlob_Alloc(_DefArray_Size(sizeof(TYPE), SIZE)))) : NULL)

#define _DefArray_AllocZeroed(TYPE, SIZE) \
    ((_DefArray_Size(sizeof(TYPE), SIZE) > 0) ? (_DEF_STATIC_CAST(TYPE*)(_DefBlob_AllocZeroed(_DefArray_Size(sizeof(TYPE), SIZE)))) : NULL)

//! \todo The call signature for _DefArray_TryEnsureSize is perhaps error prone
//!       (specifically, the reinterpret_cast).  There may be a better way...
#define _DefArray_Expand(POLD, TYPE, NOLD, NNEW, RESULT) \
    ((_DefArray_ExpandBySize((POLD), sizeof(TYPE), (NOLD), (NNEW), _DEF_REINTERPRET_CAST(void**)(RESULT))))

#define _DefArray_TryEnsureSize(PPOLD, TYPE, NOLD, NNEW) \
    _DefArray_TryEnsureSizeByElemSize((*(PPOLD)), sizeof(TYPE), (NOLD), (NNEW), _DEF_REINTERPRET_CAST(void**)(PPOLD))

    /*
     * (Wrappers for) platform-independent string operations.
     */

    /*!
     * Test if string is null or empty.
     */
    BOOLEAN DefString_IsEmpty(_In_ PCWSTR pSelf);

    HRESULT DefString_Dup(_In_ PCWSTR pDup, _Outptr_ PWSTR* result);

    _Success_(return ) BOOLEAN DefString_ToInteger(_In_ PCWSTR str, _Out_opt_ int* valueAsInteger);

    HRESULT
    DefString_CchCopy(_Out_writes_(destinationSizeInChars) PWSTR destination, _In_ size_t destinationSizeInChars, _In_ PCWSTR source);

    //! Equivalent to wcscmp
    DEFCOMPARISON DefString_CompareWithOptions(_In_ PCWSTR selfString, _In_ PCWSTR otherString, _In_ DEFCOMPAREOPTIONS options);

    DEFCOMPARISON DefString_CchCompareWithOptions(
        _In_reads_z_(maxCharsToCompare) PCWSTR selfString,
        _In_reads_z_(maxCharsToCompare) PCWSTR otherString,
        _In_ size_t maxCharsToCompare,
        _In_ DEFCOMPAREOPTIONS options);

    BOOLEAN DefString_IsPrefixWithOptions(_In_ PCWSTR desiredPrefix, _In_ PCWSTR fullString, _In_ DEFCOMPAREOPTIONS options);

    BOOLEAN DefString_IsSuffixWithOptions(_In_ PCWSTR desiredSuffix, _In_ PCWSTR fullString, _In_ DEFCOMPAREOPTIONS options);

    typedef UINT32 DEFSTRING_ENCODING;

    static const DEFSTRING_ENCODING DEFSTRING_ENCODING_UTF16 = 0;
    static const DEFSTRING_ENCODING DEFSTRING_ENCODING_UTF8 = 1;
    static const DEFSTRING_ENCODING DEFSTRING_ENCODING_ASCII = 2;

    DEFSTRING_ENCODING DefString_ChooseBestEncoding(_In_ PCWSTR utf16String);

    // Convert to UTF-16 from ASCII and UTF-8.
    // We don't need the other direction here, because the tools that write these strings can call existing system helpers.
    // These functions operate on string sizes that include the nul terminator since that is what our pipeline deals with.
    HRESULT DefString_ConvertAsciiToUtf16(
        _In_reads_z_(stringSizeInAsciiCharsIncludingNull) PCSTR asciiString,
        _Pre_satisfies_(stringSizeInAsciiCharsIncludingNull > 0) size_t stringSizeInAsciiCharsIncludingNull,
        _Outptr_ PWSTR* result);

    HRESULT DefString_ConvertUtf8ToUtf16(
        _In_reads_z_(stringSizeInBytesIncludingNull) PCSTR utf8String,
        _Pre_satisfies_(stringSizeInBytesIncludingNull > 0) size_t stringSizeInBytesIncludingNull,
        _Out_ size_t* resultStringSizeInUtf16CharsIncludingNull,
        _Outptr_ PWSTR* result);

#define DefString_Compare(S1, S2) DefString_CompareWithOptions((S1), (S2), DefCompare_Default)
#define DefString_ICompare(S1, S2) DefString_CompareWithOptions((S1), (S2), DefCompare_CaseInsensitive)
#define DefString_CchCompare(S1, S2, N) DefString_CchCompareWithOptions((S1), (S2), DefCompare_Default)
#define DefString_CchICompare(S1, S2, N) DefString_CchCompareWithOptions((S1), (S2), DefCompare_CaseInsensitive)
#define DefString_IsPrefix(PFX, STR) DefString_IsPrefixWithOptions((PFX), (STR), DefCompare_Default)
#define DefString_IsPrefixI(PFX, STR) DefString_IsPrefixWithOptions((PFX), (STR), DefCompare_CaseInsensitive)
#define DefString_IsSuffix(SFX, STR) DefString_IsSuffixWithOptions((SFX), (STR), DefCompare_Default)
#define DefString_IsSuffixI(SFX, STR) DefString_IsSuffixWithOptions((SFX), (STR), DefCompare_CaseInsensitive)
#define DefString_Equal(S1, S2) (DefString_Compare(S1, S2) == Def_Equal)
#define DefString_IEqual(S1, S2) (DefString_ICompare(S1, S2) == Def_Equal)

    //! Equivalent to memcmp
    DEFCOMPARISON DefBlob_Compare(
        _In_reads_bytes_(maxBytesToCompare) const void* selfBlob,
        _In_reads_bytes_(maxBytesToCompare) const void* otherBlob,
        _In_ size_t maxBytesToCompare);

#define Def_IfFailedReturnFalse(exp) \
    do \
    { \
        if (FAILED(exp)) \
        { \
            return false; \
        } \
    } while (0, 0)

#ifdef __cplusplus
}
#endif
