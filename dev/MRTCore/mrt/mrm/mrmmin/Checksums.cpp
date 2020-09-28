// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"
#include "mrm/Checksums.h"

namespace Microsoft::Resources
{

DefChecksum::Checksum DefChecksum::ComputeChecksum(
    __in Checksum partialChecksum,
    __in_bcount_opt(cbData) const BYTE* pData,
    __in UINT32 cbData)
{
    UINT32 crc = partialChecksum;
    if (pData == NULL)
    {
        if (cbData > 0)
        {
            return 0;
        }
        UINT32 tmp = 0;
        crc = _DefComputeCrc32(crc, reinterpret_cast<const BYTE*>(&tmp), sizeof(UINT32));
        crc = _DefComputeCrc32(crc, reinterpret_cast<const BYTE*>(&tmp), sizeof(UINT32));
        return crc;
    }
    else
    {
        crc = _DefComputeCrc32(partialChecksum, reinterpret_cast<const BYTE*>(&cbData), sizeof(UINT32));
        if (cbData > 0)
        {
            crc = _DefComputeCrc32(crc, pData, cbData);
        }
    }
    return crc;
}

DefChecksum::Checksum DefChecksum::ComputeUInt32Checksum(__in Checksum partialChecksum, __in UINT32 value)
{
    return _DefComputeCrc32(partialChecksum, reinterpret_cast<const BYTE*>(&value), sizeof(UINT32));
}

HRESULT
DefChecksum::ComputeStringChecksum(
    __in Checksum partialChecksum,
    __in bool caseInsensitive,
    __in_opt PCWSTR pString,
    _Out_ DefChecksum::Checksum* checksum)
{
    *checksum = partialChecksum;
    if (pString == NULL)
    {
        *checksum = ComputeChecksum(partialChecksum, NULL, 0);
        return S_OK;
    }
    StringResult str;
    RETURN_IF_FAILED(str.Init(pString));
    if (caseInsensitive)
    {
        size_t size = 0;
        PWSTR pStr;
        RETURN_IF_FAILED(str.GetWritableRef(&pStr, &size));
        if (pStr == NULL)
        {
            return S_OK;
        }
        while ((*pStr) != L'\0')
        {
            (*pStr) = towlower(*pStr);
            pStr++;
        }
    }
    size_t length;
    RETURN_IF_FAILED(str.GetLength(&length));
    length = (length + 1) * sizeof(WCHAR); // include terminating NULL
    *checksum = ComputeChecksum(partialChecksum, reinterpret_cast<const BYTE*>(str.GetRef()), static_cast<UINT32>(length));

    return S_OK;
}

HRESULT
DefChecksum::ComputeAtomPoolChecksum(__in Checksum partialChecksum, __in_opt const IAtomPool* pPool, _Out_ DefChecksum::Checksum* checksum)
{
    if (pPool == NULL)
    {
        *checksum = ComputeChecksum(partialChecksum, NULL, 0);
        return S_OK;
    }
    return ComputeAtomPoolChecksum(partialChecksum, pPool, pPool->GetNumAtoms(), checksum);
}

HRESULT
DefChecksum::ComputeAtomPoolChecksum(
    __in Checksum partialChecksum,
    __in_opt const IAtomPool* pPool,
    __in UINT32 numAtoms,
    _Out_ DefChecksum::Checksum* checksum)
{
    *checksum = partialChecksum;
    if (pPool == NULL)
    {
        if (numAtoms > 0)
        {
            return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
        }
        *checksum = ComputeChecksum(partialChecksum, NULL, 0);
        return S_OK;
    }
    StringResult atomStr;
    UINT32 size = pPool->GetNumAtoms();
    if (size >= numAtoms)
    {
        size = numAtoms;
    }
    else
    {
        return E_DEF_SIZE_MISMATCH;
    }

    UINT32 crc;
    RETURN_IF_FAILED(ComputeStringChecksum(partialChecksum, true, pPool->GetDescription(), &crc));
    crc = ComputeUInt32Checksum(crc, (pPool->GetIsCaseInsensitive() ? 1 : 0));
    crc = ComputeUInt32Checksum(crc, size);
    for (UINT32 i = 0; i < size; i++)
    {
        if (!pPool->TryGetString(i, &atomStr))
        {
            *checksum = crc;
            return S_OK;
        }
        RETURN_IF_FAILED(ComputeStringChecksum(crc, pPool->GetIsCaseInsensitive(), atomStr.GetRef(), &crc));
    }

    *checksum = crc;
    return S_OK;
}

HRESULT
DefChecksum::ComputeAtomChecksum(
    __in Checksum partialChecksum,
    __in Atom atom,
    __in const AtomPoolGroup* pAtoms,
    _Out_ DefChecksum::Checksum* checksum)
{
    *checksum = partialChecksum;

    if (pAtoms == nullptr)
    {
        return S_OK;
    }

    if (atom.IsNull())
    {
        *checksum = ComputeUInt32Checksum(partialChecksum, 0);
        return S_OK;
    }

    IAtomPool* pPool = pAtoms->GetAtomPool(atom.GetPoolIndex());
    if (pPool == NULL)
    {
        return S_OK;
    }
    // TODO: get fully-qualified name from the atom pool group
    Checksum crc;
    RETURN_IF_FAILED(ComputeStringChecksum(partialChecksum, true, pPool->GetDescription(), &crc));
    *checksum = ComputeUInt32Checksum(crc, atom.GetIndex());

    return S_OK;
}

struct SortContext
{
    bool caseInsensitive;
};

static int __cdecl StringSorter(_In_ void* context, _In_ const void* elem1, _In_ const void* elem2)
{
    return CompareStringOrdinal(
               *reinterpret_cast<const PCWSTR*>(elem1),
               -1,
               *reinterpret_cast<const PCWSTR*>(elem2),
               -1,
               reinterpret_cast<SortContext*>(context)->caseInsensitive) -
           CSTR_EQUAL;
}

HRESULT DefChecksum::ComputeStringArrayChecksum(
    _In_ Checksum partialChecksum,
    _In_ ChecksumFlags flags,
    _In_ size_t numStrings,
    _In_reads_(numStrings) const PCWSTR* strings,
    _Out_ DefChecksum::Checksum* checksum)
{
    *checksum = partialChecksum;

    Checksum cs = partialChecksum;
    bool caseInsensitive = ((flags & Checksum_CaseSensitivityMask) == Checksum_CaseInsensitive);
    unique_deffree_ptr<PCWSTR> myStrings;
    const PCWSTR* tmpStrings = strings;

    if ((flags & Checksum_SortMask) == Checksum_Sorted)
    {
        // need to copy the array so we can sort
        myStrings.reset(_DefArray_AllocZeroed(PCWSTR, numStrings));
        RETURN_IF_NULL_ALLOC(myStrings);

        for (size_t i = 0; i < numStrings; i++)
        {
            myStrings.get()[i] = strings[i];
        }

        SortContext context {caseInsensitive};
        qsort_s(myStrings.get(), numStrings, sizeof(PCWSTR), StringSorter, &context);
        tmpStrings = myStrings.get();
    }

    for (size_t i = 0; (i < numStrings); i++)
    {
        RETURN_IF_FAILED(ComputeStringChecksum(cs, caseInsensitive, tmpStrings[i], &cs));
    }

    *checksum = cs;

    return S_OK;
}

// When calculating the hash of an external file, we will read it in chunks of this size
#define FILE_CHECKSUM_CHUNK_SIZE 32 * 1024

HRESULT
DefChecksum::ComputeFileChecksum(_In_ Checksum partialChecksum, _In_ PCWSTR fileToAdd, _Out_ DefChecksum::Checksum* checksum)
{
    *checksum = partialChecksum;

    unique_DefHandle fileHandle;
    LARGE_INTEGER fileLength = {};

    RETURN_IF_FAILED(_DefCreateFile(fileToAdd, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, 0, &fileHandle));

    RETURN_IF_FAILED(_DefGetFileSizeEx(fileHandle.get(), &fileLength));

    // Only process if the file is smaller than 4GB
    if (0 == fileLength.HighPart)
    {
        DWORD dataSizeInBytes = fileLength.LowPart;
        partialChecksum = ComputeChecksum(partialChecksum, reinterpret_cast<const BYTE*>(&dataSizeInBytes), sizeof(dataSizeInBytes));

        unique_deffree_ptr<unsigned char> buffer(_DefArray_Alloc(unsigned char, FILE_CHECKSUM_CHUNK_SIZE));
        RETURN_IF_NULL_ALLOC(buffer);

        DWORD bytesRead = 0;
        DWORD remainingBytesInFile = dataSizeInBytes;
        DWORD bytesToCopy = min(remainingBytesInFile, FILE_CHECKSUM_CHUNK_SIZE);

        while (bytesToCopy > 0)
        {
            RETURN_IF_FAILED(_DefReadFile(fileHandle.get(), buffer.get(), bytesToCopy, &bytesRead));
            RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), bytesToCopy != bytesRead);

            partialChecksum = ComputeChecksum(partialChecksum, buffer.get(), bytesRead);
            remainingBytesInFile -= bytesRead;
            bytesToCopy = min(remainingBytesInFile, FILE_CHECKSUM_CHUNK_SIZE);
        }
    }

    *checksum = partialChecksum;
    return S_OK;
}

} // namespace Microsoft::Resources