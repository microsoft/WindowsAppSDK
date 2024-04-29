// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "Helpers.h"

BEGIN_MODULE()
    MODULE_PROPERTY(L"BinaryUnderTest", L"MrmCoreR.dll")
END_MODULE()

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;

namespace UnitTests
{
const UINT64 uMillisecondsPerSecond = 1000;
const UINT64 uMillisecondsPerMinute = 60 * uMillisecondsPerSecond;
const UINT64 uMillisecondsPerHour = 60 * uMillisecondsPerMinute;

bool ComputeElapsedTime(_In_ SYSTEMTIME start, _In_ SYSTEMTIME end, _Out_ SYSTEMTIME* pElapsed)
{
    FILETIME ftStart;
    FILETIME ftEnd;
    ULARGE_INTEGER ulStart;
    ULARGE_INTEGER ulEnd;
    UINT64 delta;

    SystemTimeToFileTime(&start, &ftStart);
    ulStart.LowPart = ftStart.dwLowDateTime;
    ulStart.HighPart = ftStart.dwHighDateTime;

    SystemTimeToFileTime(&end, &ftEnd);
    ulEnd.LowPart = ftEnd.dwLowDateTime;
    ulEnd.HighPart = ftEnd.dwHighDateTime;

    bool reversed = (ulEnd.QuadPart < ulStart.QuadPart);
    delta = (reversed ? ulStart.QuadPart - ulEnd.QuadPart : ulEnd.QuadPart - ulStart.QuadPart);
    delta /= 10000; // 100 nanoSeconds -> mSec.

    SecureZeroMemory(pElapsed, sizeof(SYSTEMTIME));

    pElapsed->wHour = (WORD)(delta / uMillisecondsPerHour);
    delta %= uMillisecondsPerHour;

    pElapsed->wMinute = (WORD)(delta / uMillisecondsPerMinute);
    delta %= uMillisecondsPerMinute;

    pElapsed->wSecond = (WORD)(delta / uMillisecondsPerSecond);
    delta %= uMillisecondsPerSecond;

    pElapsed->wMilliseconds = (WORD)delta;
    return reversed;
}

bool TestStringArray::TryGetStringAsInt(__in int index, __out int* pValueOut) const
{
    return (swscanf_s(m_ppStrings[index], L"%d", pValueOut) == 1);
}

bool TestStringArray::TryGetStringAsHexadecimal(_In_ int index, _Out_ UINT32* pValueOut) const
{
    return (swscanf_s(m_ppStrings[index], L"%x", pValueOut) == 1);
}

bool TestStringArray::TryGetStringAsBool(_In_ int index, _Out_ bool* pValueOut) const
{
    if (DefString_ICompare(m_ppStrings[index], L"true") == Def_Equal)
    {
        *pValueOut = true;
        return true;
    }
    else if (DefString_ICompare(m_ppStrings[index], L"false") == Def_Equal)
    {
        *pValueOut = false;
        return true;
    }

    *pValueOut = false;
    return false;
}

bool TestStringArray::TryGetStringAsDouble(__in int index, __out double* pValueOut) const
{
    return (swscanf_s(m_ppStrings[index], L"%lf", pValueOut) == 1);
}

// Initialize from a supplied TestDataArray<String>.
bool TestStringArray::InitFromArray(__in TestDataArray<String>& strings)
{
    Release();
    m_ppStrings = _DefArray_AllocZeroed(PWSTR, strings.GetSize());
    if (m_ppStrings == nullptr)
    {
        return false;
    }
    m_numStrings = static_cast<int>(strings.GetSize());
    for (UINT32 i = 0; i < strings.GetSize(); i++)
    {
        m_ppStrings[i] = _DefDuplicateString(strings[i]);
        if (m_ppStrings[i] == nullptr)
        {
#pragma prefast(suppress : 26045, "DefArray_AllocZeroed ensures size, but macros & intsafe make that invisible to prefast")
            return false;
        }
    }
#pragma prefast(suppress : 26045, "DefArray_AllocZeroed ensures size, but macros & intsafe make that invisible to prefast")
    return true;
}

bool TestStringArray::InitFromArray(__in_ecount(numStrings) String* pStrings, __in int numStrings)
{
    Release();

    m_ppStrings = _DefArray_AllocZeroed(PWSTR, numStrings);
    if (m_ppStrings == nullptr)
    {
        return false;
    }

    m_numStrings = numStrings;
    for (int i = 0; i < numStrings; i++)
    {
        m_ppStrings[i] = _DefDuplicateString((PCWSTR)pStrings[i]);
        if (m_ppStrings[i] == nullptr)
        {
#pragma prefast(suppress : 26045, "DefArray_AllocZeroed ensures size, but macros & intsafe make that invisible to prefast")
            return false;
        }
    }
#pragma prefast(suppress : 26045, "DefArray_AllocZeroed ensures size, but macros & intsafe make that invisible to prefast")
    return true;
}

// Initializes from test variables with names derived from a supplied prefix.
// 1) If a test data string named "<prefix>List" is present, it is treated as
//    a semi-colon-separated list of strings and used to initialize the list.
// 2) If a test data string array named "<prefix>Array" is present, it is used
//    to initialize the list.
// Returns true if a list was created, false otherwise.
bool TestStringArray::TryInitFromTestVars(__in PCWSTR pVarPrefix)
{
    String tmp;
    String strList;
    String varName;
    TestDataArray<String> strArray;

    Release();
    if (SUCCEEDED(TestData::TryGetValue(varName.Format(L"%sList", pVarPrefix), strList)))
    {
        return InitFromList(strList);
    }
    else if (SUCCEEDED(TestData::TryGetValue(varName.Format(L"%sArray", pVarPrefix), strArray)))
    {
        m_ppStrings = _DefArray_AllocZeroed(PWSTR, strArray.GetSize());
        if (m_ppStrings != nullptr)
        {
            for (UINT32 i = 0; i < strArray.GetSize(); i++)
            {
                m_ppStrings[i] = _DefDuplicateString(strArray[i]);
                if (m_ppStrings[i] == nullptr)
                {
                    Log::Error(L"Test setup: failed to duplicate string");
                    Release();
                    break;
                }
            }
            m_numStrings = static_cast<int>(strArray.GetSize());
        }
        else
        {
            Log::Error(L"Test setup: failed to create strings array");
            Release();
        }
    }
#pragma prefast(suppress : 26045, "DefArray_AllocZeroed ensures size, but macros & intsafe make that invisible to prefast")
    return (m_ppStrings != nullptr);
}

// Same as TryInitFromTestVars but logs an error if no data is found
bool TestStringArray::InitFromTestVars(__in PCWSTR varName)
{
    if (!TryInitFromTestVars(varName))
    {
        String logmsg;
        Log::Error(logmsg.Format(L"Test setup: couldn't load string data from %s", varName));
        return false;
    }
    return true;
}

// Initializes the TestStringArray from a supplied semi-colon separated list of strings.
bool TestStringArray::InitFromList(__in String stringsList)
{
    Release();
    m_ppStrings = ParseList(stringsList, m_numStrings);
    return (m_ppStrings != nullptr);
}

// Releases the array and its contents
void TestStringArray::Release()
{
    if (m_ppStrings != nullptr)
    {
        for (int i = 0; i < m_numStrings; i++)
        {
            if (m_ppStrings[i] != nullptr)
            {
                Def_Free(m_ppStrings[i]);
                m_ppStrings[i] = nullptr;
            }
        }
        Def_Free(m_ppStrings);
        m_ppStrings = nullptr;
    }
    m_numStrings = 0;
}

// Initializes the TestStringArray from the atoms in a supplied atom
// pool, in the order they appear in the pool.
bool TestStringArray::InitFromAtomPool(__in const IAtomPool* pAtomPool)
{
    bool complete = false;
    Release();

    if (pAtomPool != nullptr)
    {
        m_numStrings = pAtomPool->GetNumAtoms();
        m_ppStrings = _DefArray_AllocZeroed(PWSTR, m_numStrings);
        if (m_ppStrings != nullptr)
        {
            StringResult str;
            for (int i = 0; i < m_numStrings; i++)
            {
                if (pAtomPool->TryGetString(i, &str))
                {
                    m_ppStrings[i] = _DefDuplicateString(str.GetRef());
                    if (m_ppStrings[i] == nullptr)
                    {
                        Log::Error(L"Test setup: couldn't duplicate string");
                        break;
                    }
                }
            }
            __analysis_assume(m_numStrings > 0);
            complete = (m_ppStrings[m_numStrings - 1] != nullptr);
        }
        else if (m_numStrings > 0)
        {
            Log::Error(L"Test setup: couldn't allocate strings array");
        }
    }
    if (!complete)
    {
        Release();
    }
#pragma prefast(suppress : 26045, "DefArray_AllocZeroed ensured size, but macros and intsafe make that invisible to prefast")
    return complete;
}

// Parses a semi-colon separated list of strings into a counted array of PWSTR
_Success_(return != nullptr) PWSTR* TestStringArray::ParseList(String stringsList, __out int& numStringsOut)
{
    int sizeStrings = 1;
    int offset = 0;
    do
    {
        offset = stringsList.Find(L';', offset);
        if (offset > 0)
        {
            sizeStrings++;
            offset++;
        }
    } while (offset > 0);

    PWSTR* ppStrings = _DefArray_AllocZeroed(PWSTR, sizeStrings);
    if (ppStrings == nullptr)
    {
        return nullptr;
    }

    String key;
    int numStrings = 0;
    int nextOffset = 0;
    offset = 0;
    do
    {
        nextOffset = stringsList.Find(L';', offset);
        if (nextOffset > 0)
        {
            key = stringsList.Mid(offset, nextOffset - offset);
        }
        else
        {
            key = stringsList.Mid(offset);
        }
        offset = nextOffset + 1;
        key.Trim();
        if (key.GetLength() > 0)
        {
            ppStrings[numStrings++] = _DefDuplicateString(key);
        }
    } while (offset > 0);
    numStringsOut = numStrings;
    return ppStrings;
}

// static method to release an array of strings
void TestStringArray::ReleaseStrings(__in_ecount_opt(numStrings) PWSTR* ppStrings, int numStrings)
{
    if (ppStrings != nullptr)
    {
        for (int i = 0; i < numStrings; i++)
        {
            if (ppStrings[i])
            {
                Def_Free(ppStrings[i]);
                ppStrings[i] = nullptr;
            }
        }
        Def_Free(ppStrings);
    }
}

bool TestAtomPool::ParseAtomSpec(__in const String& spec, __inout String& keyOut, __inout String& valueOut)
{
    int eqIndex = spec.Find(L'=');
    if ((eqIndex < 1) || (eqIndex >= (spec.GetLength() - 1)))
    {
        return false;
    }
    keyOut = spec.Left(eqIndex);
    keyOut.Trim();
    if (keyOut.GetLength() < 1)
    {
        return false;
    }

    valueOut = spec.Mid(eqIndex + 1);
    valueOut.Trim();
    return true;
}

// Parses a string of the form "<key>=<index>", where <key> is a string
// and <index> is an int.
bool TestAtomPool::ParseAtomSpec(__in const String& spec, __inout String& keyOut, __inout int& indexOut)
{
    String indexStr;
    if (ParseAtomSpec(spec, keyOut, indexStr))
    {
        return (swscanf_s(indexStr, L"%d", &indexOut) == 1);
    }
    return false;
}

bool TestAtomPool::Init(__in PCWSTR pDesc, __in bool isCaseInsensitive, __in TestDataArray<String>& strings, __in_opt AtomPoolGroup* pAtoms)
{
    bool bAtomGroupAssumesOwnership = false;

    Release();

    if (TestStringArray::InitFromArray(strings))
    {
        if (FAILED(StaticAtomPool::CreateInstance(m_ppStrings, m_numStrings, pDesc, isCaseInsensitive, &m_pPool)))
        {
            return false;
        }

        if ((pAtoms != nullptr) && (m_pPool != nullptr))
        {
            if (FAILED(pAtoms->AddAtomPool(m_pPool, bAtomGroupAssumesOwnership)))
            {
                Log::Error(L"Test setup: Couldn't add atom pool");
                return false;
            }
        }
    }
    return (m_pPool != nullptr);
}

bool TestAtomPool::InitFromSpecs(
    __in PCWSTR pDesc,
    __in bool isCaseInsensitive,
    __in TestDataArray<String>& strings,
    __in_opt AtomPoolGroup* pAtoms)
{
    bool bAtomGroupAssumesOwnership = false;

    Release();
    m_ppStrings = _DefArray_AllocZeroed(PWSTR, strings.GetSize());
    if (m_ppStrings == nullptr)
    {
        return false;
    }

    String logmsg;
    String key;
    int index = 0;
    int maxIndex = -1;
    m_numStrings = static_cast<int>(strings.GetSize());
    for (UINT32 i = 0; i < strings.GetSize(); i++)
    {
        if (!ParseAtomSpec(strings[i], key, index))
        {
            Log::Error(logmsg.Format(L"Couldn't parse atom spec %d", i));
            return false;
        }
        if (index >= m_numStrings)
        {
            Log::Error(logmsg.Format(L"Index %d is out of range", index));
            return false;
        }
        if (m_ppStrings[index] == nullptr)
        {
            m_ppStrings[index] = _DefDuplicateString(key);
        }
        if (index > maxIndex)
        {
            maxIndex = index;
        }
    }

    m_numStrings = maxIndex + 1;

    if (FAILED(StaticAtomPool::CreateInstance(m_ppStrings, m_numStrings, pDesc, isCaseInsensitive, &m_pPool)))
    {
        return false;
    }

    if ((pAtoms != nullptr) && (m_pPool != nullptr))
    {
        if (FAILED(pAtoms->AddAtomPool(m_pPool, bAtomGroupAssumesOwnership)))
        {
            return false;
        }
    }
    return (m_pPool != nullptr);
}

bool TestAtomPool::InitFromList(__in PCWSTR pDesc, __in bool isCaseInsensitive, __in String stringsList, __in_opt AtomPoolGroup* pAtoms)
{
    bool bAtomGroupAssumesOwnership = false;

    Release();
    if (!TestStringArray::InitFromList(stringsList))
    {
        return false;
    }

    if (FAILED(StaticAtomPool::CreateInstance(m_ppStrings, m_numStrings, pDesc, isCaseInsensitive, &m_pPool)))
    {
        Log::Error(L"Test setup: coludn't create static atom pool");
        Release();
    }
    else if (pAtoms != nullptr)
    {
        if (FAILED(pAtoms->AddAtomPool(m_pPool, bAtomGroupAssumesOwnership)))
        {
            Log::Error(L"Test setup: couldn't add atom pool to group");
            Release();
        }
    }
    return (m_pPool != nullptr);
}

bool TestAtomPool::InitFromTestVarsOrClone(
    __in PCWSTR pDesc,
    __in bool isCaseInsensitive,
    __in String varName,
    __in_opt AtomPoolGroup* pAtoms,
    __in const IAtomPool* pOther)
{
    bool bAtomGroupAssumesOwnership = false;
    String listStr;
    Release();
    if ((!TestStringArray::TryInitFromTestVars(varName)) && (!TestStringArray::InitFromAtomPool(pOther)))
    {
        // If we have no data, create an empty pool
        m_ppStrings = nullptr;
        m_numStrings = 0;
    }

    if (SUCCEEDED(StaticAtomPool::CreateInstance(m_ppStrings, m_numStrings, pDesc, isCaseInsensitive, &m_pPool)))
    {
        if ((pAtoms != nullptr) && (FAILED(pAtoms->AddAtomPool(m_pPool, bAtomGroupAssumesOwnership))))
        {
            Log::Error(L"Test setup: couldn't add atom pool to group");
            Release();
        }
    }
    else
    {
        Log::Error(L"Test setup: couldn't create static atom pool");
        Release();
    }
    return (m_pPool != nullptr);
}

void TestAtomPool::Release()
{
    delete m_pPool;
    m_pPool = nullptr;

    TestStringArray::Release();
}

TestBlob::TestBlob() :
    m_pStringValue(nullptr), m_destinationAlignment(DefaultAlignment), m_cbBuffer(0), m_cbBlob(0), m_blobOffset(0), m_pBuffer(nullptr)
{
    m_bufferFill.ui32 = DefaultBufferFill;
}

void TestBlob::Release()
{
    if (m_pBuffer != nullptr)
    {
        Def_Free(m_pBuffer);
    }
    m_cbBuffer = m_cbBlob = m_blobOffset = 0;
    m_pBuffer = nullptr;

    if (m_pStringValue != nullptr)
    {
        Def_Free(m_pStringValue);
        m_pStringValue = nullptr;
    }
    m_destinationAlignment = DefaultAlignment;
}

bool TestBlob::Init(__in size_t cbBuffer, __in size_t cbBlob, __in UINT32 bufferFill, __in size_t blobOffset)
{
    Release();
    cbBuffer = (((cbBuffer + sizeof(UINT32) - 1) / sizeof(UINT32)) * sizeof(UINT32)); // buffer needs to be multiple of 4
    if ((cbBuffer < 1) || (blobOffset + cbBlob > cbBuffer))
    {
        return false;
    }

    m_pBuffer = _DefArray_Alloc(BYTE, cbBuffer);
    if (!m_pBuffer)
    {
        return false;
    }

    m_bufferFill.ui32 = bufferFill;
    m_cbBuffer = cbBuffer;
    m_cbBlob = cbBlob;
    m_blobOffset = blobOffset;

    // prepare the buffer
    for (size_t i = 0; i < m_cbBuffer; i++)
    {
        m_pBuffer[i] = GetBufferFill(i);
    }
    return true;
}

bool TestBlob::CheckBlobInitialized(__out_opt int* pOffsetOut)
{
    if (pOffsetOut != nullptr)
    {
        *pOffsetOut = 0;
    }
    BYTE* pData = GetBlob();

    for (size_t i = 0; i < m_cbBlob; i++)
    {
        if (pData[i] == GetBufferFill(m_blobOffset + i))
        {
            if (pOffsetOut)
            {
                *pOffsetOut = static_cast<int>(i);
            }
            return false;
        }
    }
    return true;
}

bool TestBlob::CheckBufferUndamaged(__out_opt int* pOffsetOut)
{
    if (pOffsetOut != nullptr)
    {
        *pOffsetOut = 0;
    }
    BYTE* pData = GetBuffer();

    // check before the blob
    for (size_t i = 0; i < m_blobOffset; i++)
    {
        if (pData[i] != GetBufferFill(i))
        {
            if (pOffsetOut)
            {
                *pOffsetOut = static_cast<int>(i);
            }
            return false;
        }
    }

    // check after the blob
    for (size_t i = m_blobOffset + m_cbBlob; i < m_cbBuffer - 1; i++)
    {
        if (pData[i] != GetBufferFill(i))
        {
            if (pOffsetOut)
            {
                *pOffsetOut = static_cast<int>(i);
            }
            return false;
        }
    }
    return true;
}

bool TestBlob::CheckCopy(__in_bcount(cbCopy) const BYTE* pCopy, __in size_t cbCopy, __in bool checkAlignment, __in bool checkPadZeroed)
{
    if ((cbCopy != GetBlobSizeInBytes()) || (memcmp(pCopy, GetBlob(), cbCopy) != 0))
    {
        Log::Comment(L"[ content mismatch ]");
        return false;
    }

    if ((checkAlignment) && (!_DEFFILE_PTR_IS_ALIGNED(pCopy, m_destinationAlignment)))
    {
        Log::Comment(L"[ incorrect pointer alignment ]");
        return false;
    }

    if (checkPadZeroed)
    {
        size_t cbPadded = (((cbCopy + sizeof(UINT32) - 1) / sizeof(UINT32)) * sizeof(UINT32));
        if (cbPadded > cbCopy)
        {
            // UNSAFE!  Walking off the official end of pCopy to check that pad bytes were zeroed
            const BYTE* pPad = &pCopy[cbCopy];
            for (size_t i = 0; i < (cbPadded - cbCopy); i++)
            {
#pragma prefast(suppress : 26000, "Test case being unsafe on purpose")
                if (pPad[i] != 0)
                {
                    Log::Comment(L"[ non-zero pad bytes ]");
                    return false;
                }
            }
        }
    }
    return true;
}

bool TestBlob::InitFromTestVars(__in PCWSTR pVarPrefix)
{
    String tmp;
    bool blobIsString = false;
    String blobString;
    size_t blobOffset = 0;
    size_t blobSize = 0;
    union
    {
        UINT32 ui32;
        BYTE b[4];
    } blobFill;
    size_t bufferSize = 0;
    size_t bufferFill = 0xdeadbeef;

    // Get information about the payload
    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%s_Size", pVarPrefix), blobSize)))
    {
        if (!SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%s_Fill", pVarPrefix), blobFill.ui32)))
        {
            blobFill.ui32 = 0xaabbccdd;
        }
    }
    else if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%s_String", pVarPrefix), blobString)))
    {
        blobIsString = true;
        blobSize = (wcslen((PCWSTR)blobString) + 1) * sizeof(WCHAR);
    }
    else
    {
        Log::Error(tmp.Format(L"Unable to initialize blob (neither %s_Fill nor %s_String exists).", pVarPrefix, pVarPrefix));
        return false;
    }

    if (!SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%s_Offset", pVarPrefix), blobOffset)))
    {
        blobOffset = 0;
    }

    // Now the buffer we're writing the payload into
    if (!SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%s_BufferSize", pVarPrefix), bufferSize)))
    {
        bufferSize = blobSize;
    }

    if (!SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%s_BufferFill", pVarPrefix), bufferFill)))
    {
        bufferFill = 0xdeadbeef;
    }

    // Now intialize the buffer
    if (!Init(bufferSize, blobSize, static_cast<UINT32>(bufferFill), blobOffset))
    {
        return false;
    }

    if (!SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%s_Alignment", pVarPrefix), m_destinationAlignment)))
    {
        m_destinationAlignment = DefaultAlignment;
    }
    else if (!BaseFile::IsValidAlignment(m_destinationAlignment))
    {
        Log::Warning(tmp.Format(L"Invalid alignment %d ignored", m_destinationAlignment));
        m_destinationAlignment = DefaultAlignment;
    }

    // Copy or fill the blob
    if (blobIsString)
    {
        if (FAILED(DefString_Dup((PCWSTR)blobString, &m_pStringValue)))
        {
            return false;
        }

        memcpy_s(GetBlob(), GetBlobSizeInBytes(), (PCWSTR)blobString, blobSize);
    }
    else
    {
        size_t cbBlob = GetBlobSizeInBytes();
        BYTE* pBlob = GetBlob();
        for (size_t i = 0; i < cbBlob; i++)
        {
            pBlob[i] = blobFill.b[i % 4];
        }
    }
    return true;
}

TestBlob** TestBlob::CreateBlobsFromTestVars(__in PCWSTR pVarPrefix, __out int* pNumBlobsOut)
{
    if (pNumBlobsOut != nullptr)
    {
        *pNumBlobsOut = -1;
    }
    String tmp;
    int numBlobs;
    if ((!SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%s_Count", pVarPrefix), numBlobs))) || (numBlobs < 1))
    {
        Log::Error(tmp.Format(L"Couldn't read the number of test blobs for %s", pVarPrefix));
        return nullptr;
    }

    TestBlob** ppRtrn = _DefArray_AllocZeroed(TestBlob*, numBlobs);
    if (ppRtrn == nullptr)
    {
        return nullptr;
    }

    for (int i = 0; i < numBlobs; i++)
    {
        TestBlob* pBlob = new TestBlob();
        if ((pBlob == nullptr) || (!pBlob->InitFromTestVars(tmp.Format(L"%s%d", pVarPrefix, i))))
        {
            Log::Error(tmp.Format(L"Couldn't initialized test blob %d", i));
            *pNumBlobsOut = i;
            return ppRtrn;
        }
        ppRtrn[i] = pBlob;
    }

    *pNumBlobsOut = numBlobs;
    return ppRtrn;
}

BuildHelper::~BuildHelper()
{
    if (m_pBuf != nullptr)
    {
        Def_Free(m_pBuf);
        m_pBuf = nullptr;
    }
}

HRESULT BuildHelper::Build(__in ISectionBuilder* pBuilder)
{
    RETURN_IF_FAILED(pBuilder->Finalize());

    UINT32 size = pBuilder->GetMaxSizeInBytes();

    BYTE* pBuffer = ((size > 0) ? _DefArray_AllocZeroed(BYTE, size) : nullptr);
    RETURN_IF_NULL_ALLOC(pBuffer);

    UINT32 cbWritten = 0;
    HRESULT hr = pBuilder->Build(pBuffer, size, &cbWritten);
    if (FAILED(hr))
    {
        Def_Free(pBuffer);
        return hr;
    }

    if (m_pBuf != nullptr)
    {
        Def_Free(m_pBuf);
    }
    m_cbBuf = size;
    m_cbEstimate = size;
    m_cbActual = cbWritten;
    m_pBuf = pBuffer;
    return S_OK;
}

}; // namespace UnitTests
