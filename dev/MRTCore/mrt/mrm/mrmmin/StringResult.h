// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

HRESULT DefStringResult_New(_In_opt_ PCWSTR pStr, DEFRESULTTYPE type, _Outptr_ DEFSTRINGRESULT** result);

HRESULT DefStringResult_NewRef(_In_opt_ PCWSTR pStr, _Outptr_ DEFSTRINGRESULT** result);

HRESULT DefStringResult_NewBuf(_In_opt_ PCWSTR pStr, _Outptr_ DEFSTRINGRESULT** result);

HRESULT DefStringResult_Init(_Inout_ DEFSTRINGRESULT* pSelf, _In_opt_ PCWSTR pStr, _In_ DEFRESULTTYPE type);

HRESULT DefStringResult_InitRef(_Inout_ DEFSTRINGRESULT* pSelf, _In_opt_ PCWSTR pStr);

HRESULT DefStringResult_InitBuf(_Inout_ DEFSTRINGRESULT* pSelf, _In_opt_ PCWSTR pInitStr);

// Returns a read-only ref to the result's contents.
HRESULT DefStringResult_GetRef(_In_ const DEFSTRINGRESULT* pSelf, _Out_ PCWSTR* ref);

// Returns a writable ref to the result's contents.
HRESULT DefStringResult_GetWritableRef(_In_ DEFSTRINGRESULT* pSelf, _In_ size_t cchMinBuffer, _Out_ PWSTR* ref, _Out_opt_ size_t* pcchRefOut);

HRESULT DefStringResult_GetCopy(_In_ const DEFSTRINGRESULT* pSelf, _Inout_ DEFSTRINGRESULT* pStringOut);

DEFRESULTTYPE DefStringResult_GetType(__in const DEFSTRINGRESULT* pSelf);

HRESULT DefStringResult_GetLength(_In_ const DEFSTRINGRESULT* pSelf, _Out_ size_t* pLengthOut);

HRESULT DefStringResult_GetSize(_In_ const DEFSTRINGRESULT* pSelf, _Out_ size_t* size);

HRESULT DefStringResult_CompareWithOptions(_In_ const DEFSTRINGRESULT* pSelf, _In_ PCWSTR pStr, DEFCOMPAREOPTIONS fOptions, _Out_ DEFCOMPARISON* result);

HRESULT DefStringResult_Compare(_In_ const DEFSTRINGRESULT* pSelf, _In_ PCWSTR pStr, _Out_ DEFCOMPARISON* result);

HRESULT DefStringResult_ICompare(_In_ const DEFSTRINGRESULT* pSelf, _In_ PCWSTR pStr, _Out_ DEFCOMPARISON* result);

/*! Prints the contents of self in a standard format
 *
 * e.g. #<String:8324F3A ref="A string" buf=#<Buffer:02348E23 str="Another string" cch=20>>
 *
 */
void DefStringResult_Inspect(__in const DEFSTRINGRESULT* pSelf);

/*! Sets self to reference an external str
 * 
 * The function fails, returning FALSE when:
 * - DefStringResult_IsInvalid(pSelf)
 */
HRESULT DefStringResult_SetRef(_Inout_ DEFSTRINGRESULT* pSelf, _In_opt_ PCWSTR pStr);

/*! Copies str to an internal buffer, and references it
 *
 * The function fails, returning FALSE when:
 * - DefStringResult_IsInvalid(pSelf)
 * - wcslen(pStr) >= STRSAFE_CCH_MAX
 * - allocation of the buffer fails
 */
HRESULT DefStringResult_SetCopy(_Inout_ DEFSTRINGRESULT* pSelf, _In_opt_ PCWSTR pStr);

/*! Takes on ownership of the provided pBuffer and references it,
 *  including responsibility to delete it when appropriate
 *
 * \warning To enforce proper ownership, buffer's attributes are set to null
 *
 * The function fails, returning FALSE when:
 * - DefStringResult_IsInvalid(pSelf)
 * - DefBuffer_Validate(pBuffer)
 */
HRESULT DefStringResult_SetContents(_Inout_ DEFSTRINGRESULT* pSelf, _Inout_ PWSTR pBuffer, _In_ size_t cchBuffer);

/*! 
 * Ensures that the provided \ref DEFSTRINGRESULT refers to a writable buffer
 * of at least cchBufferMin chararcters.
 *
 * If the provided \ref DEFSTRINGRESULT already owns a buffer of at least
 * cchBufferMin characters, the existing buffer is reused.
 * 
 * The buffer is initialized to an empty string.
 *
 * \param pSelf
 * The \ref DEFSTRINGRESULT to be modified.
 * \param cchBufferMin
 * The minimum number of writable characters to be present in the buffer
 * owned by pSelf.
 * \param result
 * Returns a reference to the internal buffer on success, NULL if an error
 * occurred.
 * \param pcchBufferOut
 * If present, returns the actual size of the buffer in characters.
 * \return HRESULT
 */
HRESULT DefStringResult_SetEmptyContents(_Inout_ DEFSTRINGRESULT* pSelf, _In_ size_t cchBufferMin, _Outptr_opt_result_bytebuffer_to_(*pcchBufferOut, cchBufferMin) WCHAR** result, _Out_opt_ size_t* pcchBufferOut);

/*! Yields ownership of pSelf's internal buffer to a supplied ppBufferOut.
 * \returns S_OK on success, failure if an error occurs.
 *
 * The function fails, returning failure when:
 * - pBufferOut is NULL
 * - DefStringResult_IsInvalid(pSelf)
 *
 * \warning The returned buffered will only hold the referenced str if self's
 *          ::DEFRESULTTYPE is #DefResultType_Buffer
 */
HRESULT DefStringResult_ReleaseContents(_Inout_ DEFSTRINGRESULT* pSelf, _Outptr_result_buffer_(*pcchBufferOut) PWSTR* ppBufferOut, _Out_ size_t* pcchBufferOut);

/*! Concatenates a str to the referenced str.
 * 
 * If the referenced str is external, it is first copied to an internal buffer.
 *
 * The function fails, returning failure when:
 * - DefStringResult_IsInvalid(pSelf)
 * - pStr == NULL
 * - DefStringResult_GetLength(pSelf) + wcslen(pStr) + 1 >= STRSAFE_MAX_CCH
 */
HRESULT DefStringResult_Concat(_Inout_ DEFSTRINGRESULT* pSelf, _In_opt_ PCWSTR pStr);

/*!
 * Concatenates a path element (file or directory) to the referenced string.
 * Ensures a single path separator ('\\') between the existing path and the
 * appended element.
 * 
 * If the referenced string is external, it is first copied to an internal buffer.
 */
HRESULT DefStringResult_ConcatPathElement(_Inout_ DEFSTRINGRESULT* pSelf, _In_ PCWSTR pPathElem, _In_ WCHAR separator);

/*! 
 * Returns true if the referenced string is an absolute path
 * (begins with the supplied separator, or '[A-Z]:<separator>'
 */
HRESULT DefStringResult_IsAbsolutePath(_Inout_ const DEFSTRINGRESULT* pSelf, _In_ WCHAR separator, _Out_ __BOOL* absolutePath);

/*!
 * Truncates a string result to the desired size.  Fails if the string is shorter
 * than the requested size.
 *
 * If the string changes size and is external, it is first copied to an internal
 * buffer.
 */
HRESULT DefStringResult_Truncate(_Inout_ DEFSTRINGRESULT* pSelf, _In_ size_t size);

/*! Case-insensitively deterimines if a str is contained in self.
*
* \returns HRESULT
*/
HRESULT DefStringResult_Contains(_In_ const DEFSTRINGRESULT* pSelf, _In_ PCWSTR subStr, _Out_ __BOOL* result);

/*! 
 * Resets the string buffer to be empty.
 * 
 * \param pSelf
 * The \ref DEFSTRINGRESULT to be cleared.
 * 
 * \param releaseBuffer
 * If TRUE, pSelf's buffer is freed.  If FALSE,
 * pSelf's buffer is reset but is not freed.
 * 
 * \return HRESULT 
 */
HRESULT DefStringResult_Clear(_Inout_ DEFSTRINGRESULT* pSelf, _In_ __BOOL releaseBuffer);

/*! Deletes self and its members
 *
 */
void DefStringResult_Delete(_In_ DEFSTRINGRESULT* pSelf);

/*!
 *
 * Finds the position of occurrance of charToFind from end of the string.
 *
 * Returns TRUE if found, FALSE if charToFind is not found in the string.
 *
 */
HRESULT DefStringResult_FindLastOf(_In_ const DEFSTRINGRESULT* pSelf, _In_ WCHAR charToFind, _Out_ __BOOL* found, _Out_ size_t* pCharPos);

/*!
 *
 * Finds the position of occurrance of charToFind from beginning of the string.
 *
 * Returns TRUE if found, FALSE if charToFind is not found in the string.
 *
 */
HRESULT DefStringResult_FindFirstOf(_In_ const DEFSTRINGRESULT* pSelf, _In_ WCHAR charToFind, _Out_ __BOOL* found, _Out_ size_t* pCharPos);

/*!
 *
 * Replaces all occurances of charToFind with charToReplaceWith from beginning of the string.
 *
 * Returns TRUE if atleast one char is replaced, FALSE if charToFind is not found in the string.
 *
 */
HRESULT DefStringResult_ReplaceAll(_In_ DEFSTRINGRESULT* pSelf, _In_ WCHAR charToFind, _In_ WCHAR charToReplaceWith, _Out_ size_t* pCharPosFirstReplace);

/*!
 *
 * Sets the string to the string value of the given integer.
 *
 * Returns HRESULT
 *
 */
HRESULT DefStringResult_SetCopyInteger(_In_ DEFSTRINGRESULT* pSelf, _In_ UINT32 nValue);

#define DefStringResult_IsInvalid(SELF) \
        (((SELF) == NULL) || ((((SELF)->pBuf == NULL) && ((SELF)->cchBuf > 0)) || (((SELF)->cchBuf == 0) && ((SELF)->pBuf != NULL))) || \
         ((SELF)->cchBuf > DEFRESULT_MAX))

typedef void (*Def_DescribeCallback)(const void*);

