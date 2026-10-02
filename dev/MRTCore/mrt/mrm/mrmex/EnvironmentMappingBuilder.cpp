// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"

namespace Microsoft::Resources::Build
{

HRESULT EnvironmentMappingSectionBuilder::CreateInstance(
    _In_ const IEnvironment* haveEnvironment,
    _In_ const IEnvironment* wantEnvironment,
    _Outptr_ EnvironmentMappingSectionBuilder** result)
{
    *result = nullptr;

    AutoDeletePtr<EnvironmentMappingSectionBuilder> rtrn = new EnvironmentMappingSectionBuilder();
    RETURN_IF_NULL_ALLOC(rtrn);
    RETURN_IF_FAILED(rtrn->Init(haveEnvironment, wantEnvironment));

    *result = rtrn.Detach();
    return S_OK;
}

HRESULT EnvironmentMappingSectionBuilder::Init(_In_ const IEnvironment* currentEnvironment, _In_ const IEnvironment* baseEnvironment)
{
    const IEnvironmentVersionInfo* baseVersion = baseEnvironment->GetVersionInfo();
    const IEnvironmentVersionInfo* currentVersion = currentEnvironment->GetVersionInfo();
    const IAtomPool* currentQualifiers = currentEnvironment->GetQualifierNames();
    const IAtomPool* baseQualifiers = baseEnvironment->GetQualifierNames();
    int numNewQualifiers = currentQualifiers->GetNumAtoms() - baseQualifiers->GetNumAtoms();

    if ((DefString_ICompare(currentEnvironment->GetUniqueName(), baseEnvironment->GetUniqueName()) != Def_Equal) ||
        (currentVersion->GetMajorVersion() != baseVersion->GetMajorVersion()) ||
        (currentVersion->GetMinorVersion() <= baseVersion->GetMinorVersion()) || (numNewQualifiers < 1))
    {
        // The current environment is not a later version of the base environment
        return E_MRM_UNSUPPORTED_ENVIRONMENT;
    }

    StringResult baseQualifierName;
    StringResult currentQualifierName;
    for (Atom::Index i = 0; i < baseQualifiers->GetNumAtoms(); i++)
    {
        if ((!baseQualifiers->TryGetString(i, &baseQualifierName)) || (!currentQualifiers->TryGetString(i, &currentQualifierName)))
        {
            return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
        }

        if (DefString_ICompare(baseQualifierName.GetRef(), currentQualifierName.GetRef()) != Def_Equal)
        {
            // Versions claim compatibility but they actually aren't compatible.
            return E_MRM_BAD_ENVIRONMENT;
        }
    }

    size_t namesPoolSizeInChars = 0;
    for (Atom::Index i = baseQualifiers->GetNumAtoms(); i < currentQualifiers->GetNumAtoms(); i++)
    {
        if (!currentQualifiers->TryGetString(i, &currentQualifierName))
        {
            return E_ABORT;
        }

        namesPoolSizeInChars += wcslen(currentQualifierName.GetRef()) + 1;
    }

    m_header.baseEnvironmentChecksum = baseVersion->GetVersionChecksum();
    m_header.currentEnvironmentChecksum = currentVersion->GetVersionChecksum();
    m_header.currentMinorVersion = currentVersion->GetMinorVersion();

    RETURN_IF_FAILED(IntToUInt16(numNewQualifiers, &m_header.numNewQualifiers));
    RETURN_IF_FAILED(SizeTToUInt16(namesPoolSizeInChars, &m_header.namesPoolSizeInChars));

    m_header.pad = 0;

    m_names = _DefArray_AllocZeroed(PCWSTR, numNewQualifiers);
    RETURN_IF_NULL_ALLOC(m_names);

    m_namesPool = _DefArray_AllocZeroed(WCHAR, m_header.namesPoolSizeInChars);
    RETURN_IF_NULL_ALLOC(m_namesPool);

    size_t numWritten = 0;
    for (Atom::Index i = 0; i < numNewQualifiers; i++)
    {
        if (!currentQualifiers->TryGetString(i + baseQualifiers->GetNumAtoms(), &currentQualifierName))
        {
            return E_ABORT;
        }

        int err = wcscpy_s(&m_namesPool[numWritten], (m_header.namesPoolSizeInChars - numWritten), currentQualifierName.GetRef());
        if (err != 0)
        {
            return E_ABORT;
        }

        m_names[i] = &m_namesPool[numWritten];
        numWritten += wcslen(currentQualifierName.GetRef()) + 1;
    }

    DEF_ASSERT(numWritten <= m_header.namesPoolSizeInChars);

    return S_OK;
}

EnvironmentMappingSectionBuilder::~EnvironmentMappingSectionBuilder()
{
    Def_Free(m_names);
    Def_Free(m_namesPool);
}

bool EnvironmentMappingSectionBuilder::IsMappingRequired(
    _In_ const IEnvironment* currentEnvironment,
    _In_ const IEnvironment* baseEnvironment)
{
    return (DefString_ICompare(currentEnvironment->GetUniqueName(), baseEnvironment->GetUniqueName()) != Def_Equal) ||
           (!CheckEnvironmentVersionIsCompatible(currentEnvironment, baseEnvironment->GetVersionInfo()));
}

bool EnvironmentMappingSectionBuilder::IsValid() const { return true; }

HRESULT EnvironmentMappingSectionBuilder::Finalize()
{
    if (m_finalizedSizeInBytes > 0)
    {
        return S_OK;
    }

    m_finalizedSizeInBytes = sizeof(m_header);
    // 1 mapping & 1 name offset per qualifier
    m_finalizedSizeInBytes += m_header.numNewQualifiers * sizeof(UINT16);
    m_finalizedSizeInBytes += m_header.namesPoolSizeInChars * sizeof(WCHAR);
    m_finalizedSizeInBytes = _DEFFILE_PAD_SECTION(m_finalizedSizeInBytes);

    return S_OK;
}

UINT32 EnvironmentMappingSectionBuilder::GetMaxSizeInBytes() const
{
    if (!IsFinalized())
    {
        return 0;
    }

    return m_finalizedSizeInBytes;
}

HRESULT EnvironmentMappingSectionBuilder::Build(
    _Out_writes_bytes_to_(bufferSizeInBytes, *numBytesWritten) VOID* buffer,
    _In_ UINT32 bufferSizeInBytes,
    _Out_opt_ UINT32* numBytesWritten) const
{
    MRMFILE_ENVIRONMENT_MAPPING_HEADER* header;
    UINT16* nameOffsets;
    PWSTR namesPool;

    RETURN_HR_IF(E_DEF_NOT_READY, !IsFinalized());

    if (numBytesWritten != nullptr)
    {
        *numBytesWritten = 0;
    }

    SectionBuilderParser data;
    RETURN_IF_FAILED(data.Set(buffer, bufferSizeInBytes));

    HRESULT hr = S_OK;
    header = _SECTION_BUILDER_NEXT(data, MRMFILE_ENVIRONMENT_MAPPING_HEADER, &hr);
    nameOffsets = _SECTION_BUILDER_NEXT_ARRAY(data, m_header.numNewQualifiers, UINT16, &hr);
    namesPool = _SECTION_BUILDER_NEXT_ARRAY(data, m_header.namesPoolSizeInChars, WCHAR, &hr);
    _SECTION_BUILDER_PAD(&data, &hr);

    RETURN_IF_FAILED(hr);

    DEF_ASSERT(header != nullptr);
    DEF_ASSERT(nameOffsets != nullptr);
    DEF_ASSERT(namesPool != nullptr);

    *header = m_header;
    for (int i = 0; i < m_header.numNewQualifiers; i++)
    {
        size_t nameOffset = m_names[i] - &m_namesPool[0];
        if (nameOffset >= m_header.namesPoolSizeInChars)
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        nameOffsets[i] = static_cast<UINT16>(nameOffset);
    }

    CopyMemory(namesPool, m_namesPool, (m_header.namesPoolSizeInChars * sizeof(WCHAR)));

    DEF_ASSERT(data.UsedBufferSizeInBytes() <= bufferSizeInBytes);

    if (numBytesWritten != nullptr)
    {
        *numBytesWritten = static_cast<UINT32>(data.UsedBufferSizeInBytes());
    }

    return S_OK;
}

} // namespace Microsoft::Resources::Build