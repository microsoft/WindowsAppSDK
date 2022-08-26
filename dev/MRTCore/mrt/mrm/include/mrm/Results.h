// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "mrm/common/Base.h"
#include "mrm/common/BaseInternal.h"

namespace Microsoft::Resources
{

class StringResult : public DefObject
{
protected:
    DEFSTRINGRESULT* m_pString;
    DEFSTRINGRESULT m_string;

public:
    HRESULT Init(_In_opt_ PCWSTR initialString, _In_ DEFRESULTTYPE type);

    HRESULT Init(_In_opt_ PCWSTR initialString);

    HRESULT Init(_In_ DEFSTRINGRESULT* initialString);

public:
    //! Creates an empty string
    StringResult();

    //! \see DefStringResult_New()
    static HRESULT CreateInstance(_In_opt_ PCWSTR initialString, _In_ DEFRESULTTYPE type, _Outptr_ StringResult** result);

    //! \see DefStringResult_NewRef()
    static HRESULT CreateInstance(_In_opt_ PCWSTR initialString, _Outptr_ StringResult** result);

    //! Creates a String based on a deep copy of a DEFSTRING
    static HRESULT CreateInstance(_In_ DEFSTRINGRESULT* initialString, _Outptr_ StringResult** result);

    ~StringResult();

    // Functionality
    /*! \returns access to the DEFSTRINGRESULT managed
         *           by this object, for use in the C apis.
         */
    DEFSTRINGRESULT* GetStringResult() { return m_pString; }

    //! \see DefStringResult_SetRef()
    HRESULT SetRef(_In_opt_ PCWSTR str);

    //! \see DefStringResult_SetCopy()
    HRESULT SetCopy(_In_opt_ PCWSTR str);

    //! \see DefStringResult_SetContents()
    HRESULT SetContents(_In_reads_(bufferSizeInChars) PWSTR buffer, _In_ size_t bufferSizeInChars);

    //! \see DefStringResult_SetEmptyContents()
    HRESULT
    SetEmptyContents(
        _In_ size_t minBufferSizeInChars,
        _Outptr_opt_result_bytebuffer_to_(*actualBufferSizeInCharsResult, minBufferSizeInChars) PWSTR* result = nullptr,
        _Out_opt_ size_t* actualBufferSizeInCharsResult = nullptr);

    HRESULT SetContentsFromOther(_Inout_ StringResult* other);

    //! \see DefStringResult_ReleaseContents()
    HRESULT ReleaseContents(_Outptr_result_buffer_(*bufferSizeInChars) PWSTR* buffer, _Out_ size_t* bufferSizeInChars);

    PCWSTR GetRef() const;

    HRESULT GetRef(_Out_ PCWSTR* result) const;

    HRESULT GetWritableRef(_Out_ PWSTR* result, _Out_opt_ size_t* writableRefSizeInChars);

    //! \see DefStringResult_GetCopy()
    HRESULT GetCopy(_Inout_ StringResult* str) const;

    //! \see DefStringResult_GetType()
    DEFRESULTTYPE GetType() const;

    //! \see DefStringResult_GetLength()
    HRESULT GetLength(_Out_ size_t* length) const;

    size_t GetLength() const;

    //! \see DefStringResult_GetSize()
    HRESULT GetSize(_Out_ size_t* size) const;

    bool IsEmpty()
    {
        PCWSTR pRef = GetRef();
        return ((pRef == nullptr) || (pRef[0] == L'\0'));
    }

    //! \see DefStringResult_Concat()
    HRESULT Concat(_In_ PCWSTR str);

    HRESULT ConcatPathElement(_In_ PCWSTR pathElement) { return ConcatPathElement(pathElement, L'\\'); }
    HRESULT ConcatPathElement(_In_ PCWSTR pathElement, _In_ WCHAR separator);

    HRESULT NormalizePathSlashes() { return NormalizePathSlashes(L'\\'); }
    HRESULT NormalizePathSlashes(_In_ WCHAR wantSlash);

    HRESULT IsAbsolutePath(_In_ WCHAR separator, _Out_ bool* absolutePath) const;
    HRESULT IsAbsolutePath(_Out_ bool* absolutePath) const { return IsAbsolutePath(L'\\', absolutePath); }

    bool IsAbsolutePath(_In_ WCHAR separator) const;
    bool IsAbsolutePath() const { return IsAbsolutePath(L'\\'); }

    HRESULT Truncate(_In_ size_t size);

    HRESULT CompareWithOptions(_In_ PCWSTR str, _In_ DEFCOMPAREOPTIONS options, _Out_ DEFCOMPARISON* result) const;
    HRESULT Compare(_In_ PCWSTR str, _Out_ DEFCOMPARISON* result) const;
    HRESULT ICompare(_In_ PCWSTR str, _Out_ DEFCOMPARISON* result) const;
    HRESULT CompareWithOptions(_In_ const StringResult* str, _In_ DEFCOMPAREOPTIONS options, _Out_ DEFCOMPARISON* result) const;
    HRESULT Compare(_In_ const StringResult* str, _Out_ DEFCOMPARISON* result) const;
    HRESULT ICompare(_In_ const StringResult* str, _Out_ DEFCOMPARISON* result) const;
    DEFCOMPARISON CompareWithOptions(_In_ PCWSTR str, _In_ DEFCOMPAREOPTIONS options) const;
    DEFCOMPARISON Compare(_In_ PCWSTR str) const;
    DEFCOMPARISON ICompare(_In_ PCWSTR str) const;

    void Inspect(void) const;

    bool TryFindLastOf(_In_ WCHAR charToFind, _Out_ size_t* foundAtPosition) const;
    bool TryFindFirstOf(_In_ WCHAR charToFind, _Out_ size_t* foundAtPosition) const;

    HRESULT ReplaceAll(_In_ WCHAR charToFind, _In_ WCHAR charToReplaceWith, _Out_ size_t* charPositionOfFirstReplacement);

    HRESULT SetCopyInteger(_In_ UINT32 value);

    HRESULT CopyToOutParams(
        _In_ size_t bufferSizeInChars,
        _Out_writes_to_opt_(bufferSizeInChars, *numCharsWritten) PWSTR buffer,
        _Out_opt_ size_t* numCharsWritten) const;

    static HRESULT SetRef(_In_opt_ StringResult* str, _In_opt_ PCWSTR refString)
    {
        if (str != nullptr)
        {
            return str->SetRef(refString);
        }
        return E_INVALIDARG;
    }

    HRESULT Contains(_In_ PCWSTR str, _Out_ bool* result) const;

    bool Contains(_In_ PCWSTR str) const;
};

class BlobResult : public DefObject
{
private:
    DEFBLOBRESULT m_blobResult;

public:
    static HRESULT NewRef(
        _In_reads_bytes_opt_(dataSizeInBytes) const void* dataToReference,
        _In_ size_t dataSizeInBytes,
        _Outptr_ BlobResult** result);

    static HRESULT NewBuf(
        _In_reads_bytes_opt_(dataSizeInBytes) const void* dataToCopy,
        _In_ size_t dataSizeInBytes,
        _Outptr_ BlobResult** result);

    BlobResult();
    virtual ~BlobResult();

    const void* GetRef(_Out_opt_ size_t* dataSizeInBytes) const;

    void* GetWritableRef(_Out_opt_ size_t* dataSizeInBytes);

    size_t GetSize() const;

    DEFRESULTTYPE GetType() const;

    DEFBLOBRESULT* GetBlobResult();
    const DEFBLOBRESULT* GetBlobResult() const;

    DEFCOMPARISON Compare(_In_ const BlobResult* other) const;

    HRESULT SetRef(_In_reads_bytes_opt_(dataSizeInBytes) const void* dataToReference, _In_ size_t dataSizeInBytes);
    HRESULT SetCopy(_In_reads_bytes_opt_(dataSizeInBytes) const void* dataToCopy, _In_ size_t dataSizeInBytes);
    HRESULT SetContents(_In_reads_bytes_(dataSizeInBytes) void* dataToOwn, _In_ size_t dataSizeInBytes);
    HRESULT SetEmptyContents(
        _In_ size_t minBufferSizeInBytes,
        _Outptr_opt_result_bytebuffer_to_(*pcbBufferOut, minBufferSizeInBytes) void** buffer = nullptr,
        _Out_opt_ size_t* pcbBufferOut = nullptr);
    HRESULT
    ReleaseContents(_Outptr_result_bytebuffer_(*releasedBufferSizeInBytes) void** releasedBuffer, _Out_ size_t* releasedBufferSizeInBytes);

    HRESULT CopyToOutParams(
        _In_ size_t bufferSizeInBytes,
        _Out_writes_bytes_to_opt_(bufferSizeInBytes, *numBytesWritten) void* buffer,
        _Out_opt_ size_t* numBytesWritten);

private: //disabling copy constructor and assignment operator
    BlobResult(const BlobResult&);
    BlobResult& operator=(BlobResult&);
};

/*!
     * InstanceType aware function to get StringResult from BlobResult
     * This will MOVE internal buffer from BlobResult to StringResult if DefType
     * is DefResultType_Buffer.
     */
HRESULT GetStringResultFromBlobResult(
    _In_ BlobResult* sourceBlob,
    _In_ DEFSTRING_ENCODING blobEncoding,
    _Inout_ StringResult* destinationString,
    _In_opt_ bool checkForType = true);

HRESULT GetBlobResultFromStringResult(_In_ StringResult* sourceString, _Inout_ BlobResult* destinationBlob);

template<class IITEM, class ICOLLECTION>
class ICollectionItemResult : public IITEM
{
public:
    virtual ~ICollectionItemResult() {}

    virtual HRESULT Set(_In_ const void* privateData, _In_ const ICOLLECTION* collection) = 0;
};

template<class ITEM, class ICOLLECTION, class COLLECTION, class ITEMDATA>
class CollectionItemResult : public ICollectionItemResult<ITEM, ICOLLECTION>
{
private:
    const COLLECTION* m_collection;
    const ITEMDATA* m_itemData;

protected:
    HRESULT GetItemData(_Out_ const ITEMDATA** data) const
    {
        *data = nullptr;
        if (m_itemData == nullptr)
        {
            return HRESULT_FROM_WIN32(ERROR_BAD_ENVIRONMENT);
        }
        *data = m_itemData;
        return S_OK;
    }

    void SetItemData(_In_opt_ const ITEMDATA* data) { m_itemData = data; }

    void SetCollection(_In_opt_ const COLLECTION* collection) { m_collection = collection; }

    CollectionItemResult(_In_ const COLLECTION* collection) : m_collection(collection), m_itemData(nullptr) {}

public:
    virtual ~CollectionItemResult() {}

    HRESULT GetParentCollection(_Out_ const COLLECTION** data) const
    {
        *data = nullptr;
        if (m_collection == nullptr)
        {
            return HRESULT_FROM_WIN32(ERROR_BAD_ENVIRONMENT);
        }

        *data = m_collection;
        return S_OK;
    }

    virtual HRESULT Set(_In_ const void* privateData, _In_ const ICOLLECTION* collection)
    {
        RETURN_HR_IF_NULL(E_INVALIDARG, privateData);

        const COLLECTION* parent;
        RETURN_IF_FAILED(GetParentCollection(&parent));

        if (collection != parent)
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_FILE_TYPE);
        }

        m_itemData = reinterpret_cast<const ITEMDATA*>(privateData);
        return S_OK;
    }
};

template<typename T>
class AutoDeletePtr : public DefObject
{
    T* m_data;

private:
    // this doesn't support reference counting. block the call of copy ctor and assignment operator
    AutoDeletePtr(const AutoDeletePtr&) {};

    AutoDeletePtr& operator=(const AutoDeletePtr&) {}

public:
    AutoDeletePtr(_In_opt_ T* init = nullptr) : m_data(init) {}

    virtual ~AutoDeletePtr() { Release(); }

    AutoDeletePtr& operator=(T* p)
    {
        Set(p);
        return (*this);
    }

    T& operator*()
    {
        if (m_data != nullptr)
        {
            return *m_data;
        }
    }

    T** operator&() { return &m_data; }

    const T& operator*() const
    {
        if (m_data != nullptr)
        {
            return *m_data;
        }
    }

    T* operator->() { return m_data; }

    const T* operator->() const { return m_data; }

    operator T*() { return m_data; }

    bool operator!() { return (m_data == nullptr); }

    bool Set(_In_opt_ T* data, bool shouldDelete = true)
    {
        if (shouldDelete)
        {
            Release();
        }

        m_data = data;
        return (data != nullptr);
    }

    void Release()
    {
        delete m_data;

        m_data = nullptr;
    }

    T* Data() const { return m_data; }

    T* Detach()
    {
        T* data = m_data;
        m_data = nullptr;

        return data;
    }
};

class AutoReaderWriterLock : public DefObject
{
public:
    _Acquires_exclusive_lock_(*this->m_srwLock) AutoReaderWriterLock(_DEF_SRWLOCK* srwLock) : m_srwLock(srwLock), m_shared(false)
    {
        _DefAcquireSRWLockExclusive(m_srwLock);
    }

    _Acquires_exclusive_lock_(*this->m_srwLock) AutoReaderWriterLock(_DEF_SRWLOCK* srwLock, bool shared) :
        m_srwLock(srwLock), m_shared(shared)
    {
        if (m_shared)
        {
            _DefAcquireSRWLockShared(m_srwLock);
        }
        else
        {
            _DefAcquireSRWLockExclusive(m_srwLock);
        }
    }

    _Releases_exclusive_lock_(*this->m_srwLock) ~AutoReaderWriterLock()
    {
        if (m_shared)
        {
            _DefReleaseSRWLockShared(m_srwLock);
        }
        else
        {
            _DefReleaseSRWLockExclusive(m_srwLock);
        }
    }

private:
    AutoReaderWriterLock();
    AutoReaderWriterLock(_In_ const AutoReaderWriterLock& lock);
    AutoReaderWriterLock& operator=(_In_ const AutoReaderWriterLock& lock);

    _DEF_SRWLOCK* m_srwLock;
    bool m_shared;
};

} // namespace Microsoft::Resources
