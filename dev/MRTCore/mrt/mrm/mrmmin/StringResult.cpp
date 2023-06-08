// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "StdAfx.h"
#include "mrm/Results.h"
#include "StringResult.h"

namespace Microsoft::Resources
{

// Constructors
StringResult::StringResult()
{
    DefStringResult_InitBuf(&m_string, NULL);
    m_pString = &m_string;
}

_Use_decl_annotations_ HRESULT StringResult::CreateInstance(PCWSTR pStr, DEFRESULTTYPE type, StringResult** result)
{
    *result = nullptr;

    StringResult* newString = new StringResult();
    RETURN_IF_NULL_ALLOC(newString);

    HRESULT hr = newString->Init(pStr, type);
    if (FAILED(hr))
    {
        delete newString;
        return hr;
    }

    *result = newString;
    return S_OK;
}

_Use_decl_annotations_ HRESULT StringResult::CreateInstance(PCWSTR pStr, StringResult** result)
{
    *result = nullptr;

    StringResult* newString = new StringResult();
    RETURN_IF_NULL_ALLOC(newString);

    HRESULT hr = newString->Init(pStr);
    if (FAILED(hr))
    {
        delete newString;
        return hr;
    }

    *result = newString;
    return S_OK;
}

// Deep Copy
_Use_decl_annotations_ HRESULT StringResult::CreateInstance(DEFSTRINGRESULT* pString, StringResult** result)
{
    *result = nullptr;

    StringResult* newString = new StringResult();
    RETURN_IF_NULL_ALLOC(newString);

    HRESULT hr = newString->Init(pString);
    if (FAILED(hr))
    {
        delete newString;
        return hr;
    }

    *result = newString;
    return S_OK;
}

_Use_decl_annotations_ HRESULT StringResult::Init(PCWSTR pStr, DEFRESULTTYPE type)
{
    m_pString = &m_string;
    return DefStringResult_Init(&m_string, pStr, type);
}

_Use_decl_annotations_ HRESULT StringResult::Init(PCWSTR pStr)
{
    m_pString = &m_string;
    return DefStringResult_InitRef(&m_string, pStr);
}

// Deep Copy
_Use_decl_annotations_ HRESULT StringResult::Init(DEFSTRINGRESULT* pString)
{
    if (pString == nullptr)
    {
        return E_INVALIDARG;
    }

    m_pString = &m_string;
    return DefStringResult_GetCopy(pString, &m_string);
}

StringResult::~StringResult(void) { DefStringResult_Clear(&m_string, TRUE); }

_Use_decl_annotations_ HRESULT StringResult::SetRef(PCWSTR pStr) { return DefStringResult_SetRef(m_pString, pStr); }
_Use_decl_annotations_ HRESULT StringResult::SetCopy(PCWSTR pStr) { return DefStringResult_SetCopy(m_pString, pStr); }
_Use_decl_annotations_ HRESULT StringResult::SetContents(PWSTR pBuffer, size_t cchBuffer)
{
    return DefStringResult_SetContents(m_pString, pBuffer, cchBuffer);
}

_Use_decl_annotations_ HRESULT StringResult::SetContentsFromOther(StringResult* pOther)
{
    if (pOther == nullptr)
    {
        return E_INVALIDARG;
    }

    if (pOther->GetType() == DEFRESULTTYPE::DefResultType_Reference)
    {
        // pOther is a read only reference. No need for deep copy.
        RETURN_IF_FAILED(SetRef(pOther->GetRef()));
        RETURN_IF_FAILED(pOther->SetRef(NULL));
    }
    else if (pOther->GetType() == DEFRESULTTYPE::DefResultType_Buffer)
    {
        // pOther has an internal buffer.
        // Move Internal buffer from pOther to us
        PWSTR pBuffer = NULL;
        size_t cchBuf = 0;
        RETURN_IF_FAILED(pOther->ReleaseContents(&pBuffer, &cchBuf));
        RETURN_IF_FAILED(SetContents(pBuffer, cchBuf));
    }
    else
    {
        return E_INVALIDARG;
    }

    return S_OK;
}

_Use_decl_annotations_ HRESULT StringResult::SetEmptyContents(size_t cchBufferMin, PWSTR* result, size_t* pcchBufferOut)
{
    return DefStringResult_SetEmptyContents(m_pString, cchBufferMin, result, pcchBufferOut);
}

_Use_decl_annotations_ HRESULT StringResult::ReleaseContents(PWSTR* ppBufferOut, size_t* pcchBufferOut)
{
    return DefStringResult_ReleaseContents(m_pString, ppBufferOut, pcchBufferOut);
}

PCWSTR StringResult::GetRef() const
{
    PCWSTR pRef;
    if (FAILED(DefStringResult_GetRef(m_pString, &pRef)))
    {
        return NULL;
    }

    return pRef;
}

_Use_decl_annotations_ HRESULT StringResult::GetRef(PCWSTR* result) const { return DefStringResult_GetRef(m_pString, result); }

_Use_decl_annotations_ HRESULT StringResult::GetWritableRef(PWSTR* result, size_t* pcchRefOut)
{
    return DefStringResult_GetWritableRef(m_pString, 0, result, pcchRefOut);
}

_Use_decl_annotations_ HRESULT StringResult::GetCopy(StringResult* pStringRtrn) const
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pStringRtrn);

    return DefStringResult_GetCopy(m_pString, pStringRtrn->GetStringResult());
}

DEFRESULTTYPE StringResult::GetType() const { return DefStringResult_GetType(m_pString); }

_Use_decl_annotations_ HRESULT StringResult::GetLength(size_t* length) const { return DefStringResult_GetLength(m_pString, length); }
_Use_decl_annotations_ HRESULT StringResult::GetSize(size_t* size) const { return DefStringResult_GetSize(m_pString, size); }
_Use_decl_annotations_ HRESULT StringResult::Concat(PCWSTR pString) { return DefStringResult_Concat(m_pString, pString); }

_Use_decl_annotations_ HRESULT StringResult::IsAbsolutePath(WCHAR separator, bool* absolutePath) const
{
    __BOOL result;
    HRESULT hr = DefStringResult_IsAbsolutePath(m_pString, separator, &result);
    *absolutePath = !!result;
    return hr;
}

_Use_decl_annotations_ HRESULT StringResult::ConcatPathElement(PCWSTR pPathElem, WCHAR separator)
{
    return DefStringResult_ConcatPathElement(m_pString, pPathElem, separator);
}

_Use_decl_annotations_ HRESULT StringResult::NormalizePathSlashes(WCHAR wantSlash)
{
    RETURN_HR_IF(E_INVALIDARG, (wantSlash != L'\\') && (wantSlash != L'/'));

    size_t cchBuf = 0;
    PWSTR pBuf;
    RETURN_IF_FAILED(GetWritableRef(&pBuf, &cchBuf));

    for (size_t i = 0; i < cchBuf; i++)
    {
        if (pBuf[i] == L'\0')
        {
            break;
        }
        else if ((pBuf[i] == L'\\') || (pBuf[i] == L'/'))
        {
            pBuf[i] = wantSlash;
        }
    }

    return S_OK;
}

_Use_decl_annotations_ HRESULT StringResult::Truncate(size_t size) { return DefStringResult_Truncate(m_pString, size); }

_Use_decl_annotations_ HRESULT StringResult::CompareWithOptions(PCWSTR pStr, DEFCOMPAREOPTIONS fOptions, DEFCOMPARISON* result) const
{
    return DefStringResult_CompareWithOptions(m_pString, pStr, fOptions, result);
}

_Use_decl_annotations_ HRESULT StringResult::Compare(PCWSTR pStr, DEFCOMPARISON* result) const
{
    return DefStringResult_Compare(m_pString, pStr, result);
}
_Use_decl_annotations_ HRESULT StringResult::ICompare(PCWSTR pStr, DEFCOMPARISON* result) const
{
    return DefStringResult_ICompare(m_pString, pStr, result);
}

_Use_decl_annotations_ HRESULT
StringResult::CompareWithOptions(const StringResult* pStr, DEFCOMPAREOPTIONS fOptions, DEFCOMPARISON* result) const
{
    *result = Def_CompareError;
    RETURN_HR_IF_NULL(E_INVALIDARG, pStr);

    PCWSTR compareString;
    RETURN_IF_FAILED(pStr->GetRef(&compareString));

    return DefStringResult_CompareWithOptions(m_pString, compareString, fOptions, result);
}

_Use_decl_annotations_ HRESULT StringResult::Compare(const StringResult* pStr, DEFCOMPARISON* result) const
{
    *result = Def_CompareError;
    RETURN_HR_IF_NULL(E_INVALIDARG, pStr);

    PCWSTR compareString;
    RETURN_IF_FAILED(pStr->GetRef(&compareString));

    return DefStringResult_Compare(m_pString, compareString, result);
}

_Use_decl_annotations_ HRESULT StringResult::ICompare(const StringResult* pStr, DEFCOMPARISON* result) const
{
    *result = Def_CompareError;
    RETURN_HR_IF_NULL(E_INVALIDARG, pStr);

    PCWSTR compareString;
    RETURN_IF_FAILED(pStr->GetRef(&compareString));

    return DefStringResult_ICompare(m_pString, compareString, result);
}

void StringResult::Inspect(void) const { DefStringResult_Inspect(m_pString); }

_Use_decl_annotations_ HRESULT
GetStringResultFromBlobResult(BlobResult* pBlobResult, DEFSTRING_ENCODING blobEncoding, StringResult* pStringResult, bool bCheckForType)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pBlobResult);
    RETURN_HR_IF_NULL(E_INVALIDARG, pStringResult);

    bool bIsTypeString = false;
    size_t cbBlob;
    const void* pBlob = nullptr;
    pBlob = pBlobResult->GetRef(&cbBlob);
    RETURN_HR_IF_NULL(E_INVALIDARG, pBlob);

    if (bCheckForType)
    {
        // Check for a null in the blob. Work from the back, since that's usually where the null is.
        if (blobEncoding == DEFSTRING_ENCODING_UTF16)
        {
            int cchBlob = static_cast<int>(cbBlob / sizeof(WCHAR));
            for (int i = cchBlob - 1; i >= 0; i--)
            {
                if (reinterpret_cast<PCWSTR>(pBlob)[i] == L'\0')
                {
                    bIsTypeString = true;
                    break;
                }
            }
        }
        else
        {
            int cchBlob = static_cast<int>(cbBlob / sizeof(CHAR));
            for (int i = cchBlob - 1; i >= 0; i--)
            {
                if (reinterpret_cast<PCSTR>(pBlob)[i] == '\0')
                {
                    bIsTypeString = true;
                    break;
                }
            }
        }

        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_FILE_TYPE), !bIsTypeString);
    }

    DEF_ASSERT(
        pBlobResult->GetType() == DEFRESULTTYPE::DefResultType_Reference || pBlobResult->GetType() == DEFRESULTTYPE::DefResultType_Buffer);

    bool bIsReference = (pBlobResult->GetType() == DEFRESULTTYPE::DefResultType_Reference);

    if (blobEncoding == DEFSTRING_ENCODING_UTF16)
    {
        if (bIsReference)
        {
            // Blob is a read only reference. No need for deep copy.
            RETURN_IF_FAILED(pStringResult->SetRef(reinterpret_cast<PCWSTR>(pBlob)));
        }
        else
        {
            // Blob is internal buffer. Move Internal buffer from Blob to String.
            void* pBuffer = nullptr;
            RETURN_IF_FAILED(pBlobResult->ReleaseContents(&pBuffer, &cbBlob));

#pragma prefast(suppress : 26035, "Caller has to ensure that blob is NULL terminated.")
            HRESULT hr = pStringResult->SetContents(reinterpret_cast<PWSTR>(pBuffer), cbBlob / sizeof(WCHAR));
            if (FAILED(hr))
            {
                _DefFree(pBuffer);
                return hr;
            }
        }
    }
    else
    {
        // Need to convert the string to UTF-16 first.
        size_t cchResultString;
        PWSTR pszResultString = nullptr;

        if (blobEncoding == DEFSTRING_ENCODING_UTF8)
        {
            RETURN_IF_FAILED(DefString_ConvertUtf8ToUtf16(reinterpret_cast<PCSTR>(pBlob), cbBlob, &cchResultString, &pszResultString));
        }
        else
        {
            cchResultString = cbBlob;
            RETURN_IF_FAILED(DefString_ConvertAsciiToUtf16(reinterpret_cast<PCSTR>(pBlob), cbBlob, &pszResultString));
        }

#pragma prefast(suppress : 26035, "Caller has to ensure that blob is NULL terminated")
        HRESULT hr = pStringResult->SetContents(pszResultString, cchResultString);
        if (FAILED(hr))
        {
            _DefFree(pszResultString);
            return hr;
        }
    }

    return S_OK;
}

_Use_decl_annotations_ HRESULT GetBlobResultFromStringResult(StringResult* pStringResult, BlobResult* pBlobResult)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pBlobResult);
    RETURN_HR_IF_NULL(E_INVALIDARG, pStringResult);
    RETURN_HR_IF_NULL(E_INVALIDARG, pStringResult->GetRef());

    size_t cbBuffer;

    if (pStringResult->GetType() == DEFRESULTTYPE::DefResultType_Reference)
    {
        // String  is a read only reference. No need for deep copy
        size_t len;
        RETURN_IF_FAILED(pStringResult->GetLength(&len));
        RETURN_IF_FAILED(pBlobResult->SetRef(pStringResult->GetRef(), (len + 1) * sizeof(WCHAR)));
    }
    else if (pStringResult->GetType() == DEFRESULTTYPE::DefResultType_Buffer)
    {
        // String  is internal buffer
        // Move Internal buffer from String to Btring
        PWSTR pBuffer = NULL;
        RETURN_IF_FAILED(pStringResult->ReleaseContents(&pBuffer, &cbBuffer));

        RETURN_IF_FAILED(pBlobResult->SetContents(pBuffer, cbBuffer * sizeof(WCHAR)));
    }
    else
    {
        return E_FAIL;
    }

    return S_OK;
}

_Use_decl_annotations_ bool StringResult::TryFindLastOf(WCHAR charToFind, size_t* pCharPos) const
{
    __BOOL found;
    return SUCCEEDED(DefStringResult_FindLastOf(m_pString, charToFind, &found, pCharPos)) && found;
}

_Use_decl_annotations_ bool StringResult::TryFindFirstOf(WCHAR charToFind, size_t* pCharPos) const
{
    __BOOL found;
    return SUCCEEDED(DefStringResult_FindFirstOf(m_pString, charToFind, &found, pCharPos)) && found;
}

_Use_decl_annotations_ HRESULT StringResult::ReplaceAll(WCHAR charToFind, WCHAR charToReplaceWith, size_t* pCharPosFirstReplace)
{
    return DefStringResult_ReplaceAll(m_pString, charToFind, charToReplaceWith, pCharPosFirstReplace);
}

_Use_decl_annotations_ HRESULT StringResult::SetCopyInteger(UINT32 nValue) { return DefStringResult_SetCopyInteger(m_pString, nValue); }

_Use_decl_annotations_ HRESULT StringResult::CopyToOutParams(size_t cchBuffer, PWSTR pBuffer, size_t* pcchWritten) const
{
    size_t len;
    RETURN_IF_FAILED(DefStringResult_GetLength(m_pString, &len));
    len++;

    if (pcchWritten != nullptr)
    {
        *pcchWritten = len;
    }

    if (len <= cchBuffer && pBuffer != nullptr)
    {
        if (len == 1)
        {
            *pBuffer = L'\0';
        }
        else
        {
            _Analysis_assume_(wcslen(m_pString->pRef) < len); // this is true for all cases (if DefStringResult_GetLength failed, len == 1)
            CopyMemory(pBuffer, m_pString->pRef, len * sizeof(pBuffer[0]));
            pBuffer[len - 1] = L'\0';
        }
    }
    else
    {
        if ((pBuffer != nullptr) && (cchBuffer > 0))
        {
            *pBuffer = L'\0';
        }

        return HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER);
    }

    return S_OK;
}

_Use_decl_annotations_ HRESULT StringResult::Contains(PCWSTR subStr, bool* result) const
{
    __BOOL value;
    HRESULT hr = DefStringResult_Contains(m_pString, subStr, &value);
    *result = !!value;
    return hr;
}

_Use_decl_annotations_ bool StringResult::Contains(PCWSTR subStr) const
{
    __BOOL contains;
    return SUCCEEDED(DefStringResult_Contains(m_pString, subStr, &contains)) && contains;
}

_Use_decl_annotations_ bool StringResult::IsAbsolutePath(WCHAR separator) const
{
    bool absPath = false;
    (void)IsAbsolutePath(separator, &absPath);
    return absPath;
}

_Use_decl_annotations_ DEFCOMPARISON StringResult::CompareWithOptions(PCWSTR pStr, DEFCOMPAREOPTIONS fOptions) const
{
    DEFCOMPARISON comp;
    (void)CompareWithOptions(pStr, fOptions, &comp);
    return comp;
}

_Use_decl_annotations_ DEFCOMPARISON StringResult::Compare(PCWSTR pStr) const
{
    DEFCOMPARISON comp;
    (void)Compare(pStr, &comp);
    return comp;
}

_Use_decl_annotations_ DEFCOMPARISON StringResult::ICompare(PCWSTR pStr) const
{
    DEFCOMPARISON comp;
    (void)ICompare(pStr, &comp);
    return comp;
}

size_t StringResult::GetLength() const
{
    size_t length;
    (void)GetLength(&length);
    return length;
}

} // namespace Microsoft::Resources
