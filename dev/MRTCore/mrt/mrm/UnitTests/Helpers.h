// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "WexTestClass.h"
#include "mrm/BaseInternal.h"
#include "mrm/build/Base.h"

using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;

#define VERIFY(EXPR, ...) VERIFY_WIN32_BOOL_SUCCEEDED(EXPR, __VA_ARGS__)

#define VERIFY_HRESULT(hr) \
    { \
        VERIFY(SUCCEEDED(hr)); \
    }

#define VERIFY_HRESULT_EXPR(EXPR, hr, ...) \
    { \
        VERIFY((static_cast<BOOL>(EXPR) && (SUCCEEDED(hr)))); \
    }

#define VERIFY_HRESULT_FAILURE(EXPECT, hr, ...) \
    { \
        VERIFY((hr) == (EXPECT), __VA_ARGS__); \
    }

namespace UnitTests
{
bool ComputeElapsedTime(_In_ SYSTEMTIME start, _In_ SYSTEMTIME end, _Out_ SYSTEMTIME* pElapsed);

class TestStringArray
{
protected:
    int m_numStrings;
    __ecount(m_numStrings) PWSTR* m_ppStrings;

public:
    TestStringArray() : m_numStrings(0), m_ppStrings(NULL) {}
    ~TestStringArray() { Release(); }

    int GetNumStrings() const { return m_numStrings; }
    const PWSTR* GetStrings() const { return m_ppStrings; }

    PCWSTR GetString(int index) const { return m_ppStrings[index]; }
    PWSTR GetWritableString(int index) const { return m_ppStrings[index]; }
    bool TryGetStringAsBool(_In_ int index, _Out_ bool* pValueOut) const;
    bool TryGetStringAsHexadecimal(_In_ int index, _Out_ UINT32* pValueOut) const;
    bool TryGetStringAsInt(__in int index, __out int* pValueOut) const;
    bool TryGetStringAsDouble(__in int index, __out double* pValueOut) const;

    // Initialize from a supplied TestDataArray<String>.
    virtual bool InitFromArray(__in TestDataArray<String>& strings);

    // Initialize from a supplied array of String.
    virtual bool InitFromArray(__in_ecount(numStrings) String* strings, __in int numStrings);

    // Initializes from test variables with names derived from a supplied prefix.
    // 1) If a test data string named "<prefix>List" is present, it is treated as
    //    a semi-colon-separated list of strings and used to initialize the list.
    // 2) If a test data string array named "<prefix>Array" is present, it is used
    //    to initialize the list.
    // Returns true if a list was created, false otherwise.
    virtual bool TryInitFromTestVars(__in PCWSTR pVarPrefix);

    // Same as TryInitFromTestVars but logs an error if no data is found
    virtual bool InitFromTestVars(__in PCWSTR varName);

    // Initializes the TestStringArray from a supplied semi-colon separated list of strings.
    virtual bool InitFromList(__in String stringsList);

    // Releases the array and its contents
    virtual void Release();

    // Initializes the TestStringArray from the atoms in a supplied atom
    // pool, in the order they appear in the pool.
    virtual bool InitFromAtomPool(__in const IAtomPool* pAtomPool);

    // Parses a semi-colon separated list of strings into a counted array of PWSTR
    _Success_(return != nullptr) static PWSTR* ParseList(String stringsList, __out int& numStringsOut);

    // static method to release an array of strings
    static void ReleaseStrings(__in_ecount_opt(numStrings) PWSTR* ppStrings, int numStrings);
};

class TestAtomPool : public TestStringArray
{
protected:
    StaticAtomPool* m_pPool;

public:
    TestAtomPool() : TestStringArray(), m_pPool(NULL) {}
    ~TestAtomPool() { Release(); }

    // Parses a string of the form "<key>=<value>", where <key> is a string
    // and <value> is a string.
    static bool ParseAtomSpec(__in const String& spec, __inout String& keyOut, __inout String& valueOut);

    // Parses a string of the form "<key>=<index>", where <key> is a string
    // and <index> is an int.
    static bool ParseAtomSpec(__in const String& spec, __inout String& keyOut, __inout int& indexOut);

    bool Init(__in PCWSTR pDesc, __in bool isCaseInsensitive, __in TestDataArray<String>& strings, __in_opt AtomPoolGroup* pAtoms);

    bool InitFromSpecs(__in PCWSTR pDesc, __in bool isCaseInsensitive, __in TestDataArray<String>& strings, __in_opt AtomPoolGroup* pAtoms);

    bool InitFromList(__in PCWSTR pDesc, __in bool isCaseInsensitive, __in String stringsList, __in_opt AtomPoolGroup* pAtoms);

    bool InitFromTestVarsOrClone(
        __in PCWSTR pDesc,
        __in bool isCaseInsensitive,
        __in String varName,
        __in_opt AtomPoolGroup* pAtoms,
        __in const IAtomPool* pOther);

    void Release();

    const IAtomPool* GetPool() const { return m_pPool; }
};

class TestBlob
{
public:
    static const int DefaultAlignment = BaseFile::Align32Bit;
    static const UINT32 DefaultBufferFill = 0xdeadbeef;

    TestBlob();
    ~TestBlob() { Release(); }

    bool Init(__in size_t cbBuffer, __in size_t cbBlob, __in UINT32 bufferFill = 0xdeadbeef, __in size_t blobOffset = 0);

    bool GetIsString() const { return m_pStringValue != NULL; }
    PCWSTR GetInitString() const { return m_pStringValue; }

    size_t GetBufferSizeInBytes() const { return m_cbBuffer; }
    size_t GetBlobSizeInBytes() const { return m_cbBlob; }
    size_t GetBlobOffset() const { return m_blobOffset; }
    BYTE* GetBuffer() const { return m_pBuffer; }
    BYTE* GetBlob() const { return &m_pBuffer[m_blobOffset]; }
    PCWSTR GetString() const { return (GetIsString() ? reinterpret_cast<PCWSTR>(&m_pBuffer[m_blobOffset]) : NULL); }

    int GetDestinationAlignment() const { return m_destinationAlignment; }

    UINT32 GetBufferFill() const { return m_bufferFill.ui32; }
    BYTE GetBufferFill(__in size_t offset) const { return m_bufferFill.b[(offset % 4)]; }

    bool CheckBlobInitialized(__out_opt int* pOffsetOut = NULL);
    bool CheckBufferUndamaged(__out_opt int* pOffsetOut = NULL);
    bool CheckCopy(
        __in_bcount(cbCopy) const BYTE* pCopy,
        __in size_t cbCopy,
        __in bool checkAlignment = true,
        __in bool checkPadZeroed = true);

    bool InitFromTestVars(__in PCWSTR pVarPrefix);
    static TestBlob** CreateBlobsFromTestVars(__in PCWSTR pVarPrefix, __out int* pNumBlobsOut);

protected:
    union
    {
        UINT32 ui32;
        BYTE b[4];
    } m_bufferFill;

    size_t m_cbBuffer;
    size_t m_cbBlob;
    size_t m_blobOffset;
    BYTE* m_pBuffer;

    PWSTR m_pStringValue;
    int m_destinationAlignment;

    void Release();
};

class BuildHelper
{
protected:
    UINT32 m_cbEstimate;
    UINT32 m_cbActual;
    int m_cbBuf;
    BYTE* m_pBuf;

public:
    BuildHelper() : m_cbEstimate(0), m_cbActual(0), m_cbBuf(0), m_pBuf(NULL) {}
    ~BuildHelper();

    UINT32 GetEstimatedSize() const { return m_cbEstimate; }
    UINT32 GetWrittenSize() const { return m_cbActual; }
    int GetBufferSize() const { return m_cbBuf; }
    BYTE* GetBuffer() const { return m_pBuf; }

    HRESULT Build(__in ISectionBuilder* pBuilder);
};
} // namespace UnitTests
