// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "stdafx.h"

#pragma prefast(disable : 28243, "28243 complains about _In_ annotation on int parameters, used extensively in this code base")

namespace Microsoft::Resources
{

const PCWSTR MrmEnvironment::ResourceItemTypeNames[] = {L"String", L"Path", L"EmbeddedData"};

const PCWSTR MrmEnvironment::ResourceValueTypeNames[] =
    {L"String", L"Path", L"EmbeddedData", L"AsciiString", L"Utf8String", L"AsciiPath", L"Utf8Path"};

const PCWSTR MrmEnvironment::ResourceValueLocatorNames[] = {L"Internal", L"DataItemsSectionLocator", L"FileListLocator"};

HRESULT MrmEnvironment::ChooseVersion(
    _In_ const ENVIRONMENT_DESCRIPTION* pEnvironmentDescription,
    _In_ int wantMajor,
    _In_ int wantMinor,
    _Out_ const MRMFILE_ENVIRONMENT_VERSION_INFO** info)
{
    *info = nullptr;
    const MRMFILE_ENVIRONMENT_VERSION_INFO* pBest = nullptr;

    // If we can't get an exact match, we want the next highest.
    // We can't accept a lower version because we don't know how to fill in the gaps.
    for (int i = 0; i < pEnvironmentDescription->numVersions; i++)
    {
        if ((wantMajor == pEnvironmentDescription->pVersions[i].major) && (wantMinor <= pEnvironmentDescription->pVersions[i].minor))
        {
#pragma prefast(disable : 26014, "26014 fires incorrectly here, reporting an overflow if numVersions is simultaneously >= 2 and <= 1.")
            if ((pBest == nullptr) || (pEnvironmentDescription->pVersions[i].minor < pBest->minor))
            {

                pBest = &pEnvironmentDescription->pVersions[i];

                if (pBest->minor == wantMinor)
                {
                    break;
                }
            }
        }
    }

    RETURN_HR_IF_NULL(E_DEF_UNSUPPORTED_VERSION, pBest);

    *info = pBest;
    return S_OK;
}

HRESULT MrmEnvironment::GetQualifierInfo(
    _In_ const ENVIRONMENT_INITIALIZER* pEnvironmentInitializer,
    _In_ const MRMFILE_ENVIRONMENT_VERSION_INFO* pVersion,
    _Out_ const QUALIFIER_INFO** info)
{
    *info = nullptr;

    // get the env version token (checksum)
    const UINT32 evToken = pVersion->checksum;

    // find the qualifier info with the matching evToken
    for (int i = 0; i < pEnvironmentInitializer->numQualifierInfos; i++)
    {

        if (pEnvironmentInitializer->pQualifierInfos[i].evToken == evToken)
        {
            *info = &pEnvironmentInitializer->pQualifierInfos[i];
            return S_OK;
        }
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT MrmEnvironment::CreateNames(
    _In_ const MRMFILE_ENVIRONMENT_VERSION_INFO* pVersion,
    _In_ const QUALIFIER_INFO* pQualifierInfo,
    _In_ EnvironmentNames which,
    _In_ AtomPoolGroup* pAtoms,
    _Outptr_opt_result_maybenull_ IAtomPool** pPoolOut)
{
    const PCWSTR* pNames = nullptr;
    PCWSTR pDescription = nullptr;
    int numNames = 0;
    bool bAtomGroupAssumesOwnership = false;

    RETURN_HR_IF_NULL(E_ABORT, pVersion);

    if (pPoolOut != nullptr)
    {
        *pPoolOut = nullptr;
    }

    // We have to use the legacy names in the pool description so we don't perturb
    // checksums.
    switch (which)
    {
    case Environment_QualifierTypeNames:
        pDescription = L"AttributeTypes";
        pNames = pQualifierInfo->pQualifierTypeNames;
        numNames = pQualifierInfo->numQualifierTypes;
        break;
    case Environment_QualifierNames:
        pDescription = L"Attributes";
        pNames = pQualifierInfo->pQualifierNames;
        numNames = pQualifierInfo->numQualifiers;
        break;
    case Environment_ItemTypeNames:
        // item types are obsolete but cannot be removed
        // for compatibility reasons.  It's safe to allow them
        // to align to resource value types.
        pDescription = L"ItemTypes";
        pNames = MrmEnvironment::ResourceValueTypeNames;
        numNames = pVersion->numItemTypes;

        DEF_ASSERT(numNames <= MrmEnvironment::NumResourceValueTypes);
        break;
    case Environment_ResourceValueTypeNames:
        pDescription = L"InstanceTypes";
        pNames = MrmEnvironment::ResourceValueTypeNames;
        numNames = pVersion->numResourceValueTypes;

        DEF_ASSERT(numNames <= MrmEnvironment::NumResourceValueTypes);
        break;
    case Environment_ResourceValueLocatorNames:
        pDescription = L"InstanceLocators";
        pNames = MrmEnvironment::ResourceValueLocatorNames;
        numNames = pVersion->numResourceValueLocators;

        DEF_ASSERT(numNames <= MrmEnvironment::NumResourceValueLocators);
        break;
    case Environment_ConditionOperatorNames:
        pDescription = L"ConditionOperators";
        pNames = nullptr;
        numNames = 0;
        break;
    default:
        RETURN_HR(E_ABORT);
    }

    AutoDeletePtr<StaticAtomPool> pRtrn;
    RETURN_IF_FAILED(StaticAtomPool::CreateInstance(pNames, numNames, pDescription, true, &pRtrn));
    RETURN_IF_FAILED(pAtoms->AddAtomPool(pRtrn, bAtomGroupAssumesOwnership));

    if (pPoolOut != nullptr)
    {
        *pPoolOut = pRtrn.Detach();
    }

    return S_OK;
}

HRESULT MrmEnvironment::CreateQualifiers(
    _In_ const MRMFILE_ENVIRONMENT_VERSION_INFO* pVersion,
    _In_ const QUALIFIER_INFO* pQualifierInfo,
    _Inout_ const IAtomPool* pQualifierNames,
    _Inout_ const IAtomPool* pQualifierTypeNames,
    _Outptr_result_buffer_maybenull_(*pNumQualifiersOut) ResourceQualifier** ppQualifiersOut,
    _Out_ int* pNumQualifiersOut)
{
    *ppQualifiersOut = nullptr;
    *pNumQualifiersOut = 0;

    int numQualifiers = pVersion->numQualifiers;

    // Actual size of the array might be larger if we're creating qualifiers for an earlier version that
    // defines only a subset.
    DEF_ASSERT((pQualifierNames->GetNumAtoms() >= numQualifiers) && (pQualifierInfo->numQualifiers >= numQualifiers));
    _Analysis_assume_(pQualifierInfo->numQualifiers >= numQualifiers);

    ResourceQualifier* pRtrn = _DefArray_AllocZeroed(ResourceQualifier, numQualifiers);
    RETURN_IF_NULL_ALLOC(pRtrn);

    for (int i = 0; i < numQualifiers; i++)
    {
        pRtrn[i].name.Set(i, pQualifierNames->GetPoolIndex());
        pRtrn[i].qualifierType.Set(pQualifierInfo->pQualifiers[i].qualifierTypeIndex, pQualifierTypeNames->GetPoolIndex());
        pRtrn[i].defaultRuntimePriority = pQualifierInfo->pQualifiers[i].runtimePriority;
        pRtrn[i].defaultBuildPriority = pQualifierInfo->pQualifiers[i].buildPriority;
    }

    *ppQualifiersOut = pRtrn;
    *pNumQualifiersOut = numQualifiers;
#pragma prefast(suppress : 26045, "Prefast doesn't detect that _DefArray_AllocZeroed guarantees numAttributes elements")
    return S_OK;
}

HRESULT MrmEnvironment::CreateVersion(
    _In_ const MRMFILE_ENVIRONMENT_VERSION_INFO* pVersion,
    _Outptr_result_maybenull_ IEnvironmentVersionInfo** ppEnvironmentOut)
{
    *ppEnvironmentOut = nullptr;

    RETURN_HR_IF_NULL(E_ABORT, pVersion);

    RETURN_IF_FAILED(EnvironmentVersionInfo::CreateInstance(pVersion, (EnvironmentVersionInfo**)ppEnvironmentOut));

    return S_OK;
}

HRESULT MrmEnvironment::ComputeEnvironmentVersionInfo(
    _In_ const IEnvironment* pEnvironment,
    _In_ int majorVersion,
    _In_ int minorVersion,
    _Out_ IEnvironmentVersionInfo** info)
{
    *info = nullptr;

    const ENVIRONMENT_DESCRIPTION* pEnvironmentDescription = pEnvironment->GetEnvironmentDescription();
    const MRMFILE_ENVIRONMENT_VERSION_INFO* pDesiredVersionInfo;
    RETURN_IF_FAILED(ChooseVersion(pEnvironmentDescription, majorVersion, minorVersion, &pDesiredVersionInfo));
    RETURN_IF_FAILED(EnvironmentVersionInfo::ComputeNew(pEnvironment, pDesiredVersionInfo, (EnvironmentVersionInfo**)info));

    return S_OK;
}

HRESULT MrmEnvironment::GetDefaultItemTypeForValueType(_In_ ResourceValueType rvTypeIn, _Out_ ResourceItemType* pItemTypeOut)
{
    if (IsPathResourceValueType(rvTypeIn))
    {
        *pItemTypeOut = ResourceItemType_Path;
    }
    else if (IsStringResourceValueType(rvTypeIn))
    {
        *pItemTypeOut = ResourceItemType_String;
    }
    else if (IsBinaryResourceValueType(rvTypeIn))
    {
        *pItemTypeOut = ResourceItemType_EmbeddedData;
    }
    else
    {
        RETURN_HR(HRESULT_FROM_WIN32(ERROR_MRM_RESOURCE_TYPE_MISMATCH));
    }

    return S_OK;
}

HRESULT MrmEnvironment::CreateInstance(
    _In_ AtomPoolGroup* pAtoms,
    _In_ const ENVIRONMENT_INITIALIZER* pInitializer,
    _In_ int major,
    _In_ int minor,
    _Outptr_ MrmEnvironment** env)
{
    *env = nullptr;

    RETURN_HR_IF_NULL(E_INVALIDARG, pAtoms);

    AutoDeletePtr<MrmEnvironment> pRtrn = new MrmEnvironment();
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->Init(pAtoms, pInitializer, major, minor));
    *env = pRtrn.Detach();

    return S_OK;
}

HRESULT MrmEnvironment::CreateInstance(
    _In_ AtomPoolGroup* pAtoms,
    _In_ const ENVIRONMENT_INITIALIZER* pInitializer,
    _In_ int index,
    _Outptr_ MrmEnvironment** env)
{
    *env = nullptr;

    DEF_ASSERT(pInitializer->pEnvironmentDescription->numVersions > 0);

    if ((index < 0) || (index >= pInitializer->pEnvironmentDescription->numVersions))
    {
        RETURN_HR(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND));
    }

    int major = pInitializer->pEnvironmentDescription->pVersions[index].major;
    int minor = pInitializer->pEnvironmentDescription->pVersions[index].minor;

    return CreateInstance(pAtoms, pInitializer, major, minor, env);
}

MrmEnvironment::~MrmEnvironment()
{
    if (m_pAtoms)
    {
        m_pAtoms->RemoveAtomPool(m_pQualifierTypeNames);
        m_pAtoms->RemoveAtomPool(m_pQualifierNames);
        m_pAtoms->RemoveAtomPool(m_pItemTypeNames);
        m_pAtoms->RemoveAtomPool(m_pResourceValueTypeNames);
        m_pAtoms->RemoveAtomPool(m_pResourceValueLocatorNames);
        m_pAtoms->RemoveAtomPool(m_pConditionOperatorNames);
    }

    delete m_pQualifierTypeNames;
    delete m_pQualifierNames;
    delete m_pItemTypeNames;
    delete m_pResourceValueTypeNames;
    delete m_pResourceValueLocatorNames;
    delete m_pConditionOperatorNames;

    m_pQualifierTypeNames = m_pQualifierNames = m_pItemTypeNames = nullptr;
    m_pResourceValueTypeNames = m_pResourceValueLocatorNames = m_pConditionOperatorNames = nullptr;

    Def_Free(m_pQualifiers);
    m_numQualifiers = 0;
    m_pQualifiers = nullptr;

    delete m_pVersion;
    m_pVersion = nullptr;
}

HRESULT MrmEnvironment::Init(
    _In_ AtomPoolGroup* pAtoms,
    _In_ const ENVIRONMENT_INITIALIZER* pEnvironmentInitializer,
    _In_ int major,
    _In_ int minor)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pAtoms);

    m_pEnvironmentInitializer = pEnvironmentInitializer;

    const MRMFILE_ENVIRONMENT_VERSION_INFO* pVersion;
    RETURN_IF_FAILED(ChooseVersion(m_pEnvironmentInitializer->pEnvironmentDescription, major, minor, &pVersion));
    RETURN_HR_IF_NULL(E_ABORT, pVersion);

    RETURN_IF_FAILED(GetQualifierInfo(m_pEnvironmentInitializer, pVersion, &m_pQualifierInfo));
    RETURN_HR_IF_NULL(E_ABORT, m_pQualifierInfo);

    m_pAtoms = pAtoms;

    RETURN_IF_FAILED(CreateNames(pVersion, m_pQualifierInfo, Environment_QualifierTypeNames, pAtoms, &m_pQualifierTypeNames));
    RETURN_IF_FAILED(CreateNames(pVersion, m_pQualifierInfo, Environment_QualifierNames, pAtoms, &m_pQualifierNames));
    RETURN_IF_FAILED(CreateNames(pVersion, m_pQualifierInfo, Environment_ItemTypeNames, pAtoms, &m_pItemTypeNames));
    RETURN_IF_FAILED(CreateNames(pVersion, m_pQualifierInfo, Environment_ResourceValueTypeNames, pAtoms, &m_pResourceValueTypeNames));
    RETURN_IF_FAILED(CreateNames(pVersion, m_pQualifierInfo, Environment_ResourceValueLocatorNames, pAtoms, &m_pResourceValueLocatorNames));
    RETURN_IF_FAILED(CreateNames(pVersion, m_pQualifierInfo, Environment_ConditionOperatorNames, pAtoms, &m_pConditionOperatorNames));
    RETURN_IF_FAILED(
        CreateQualifiers(pVersion, m_pQualifierInfo, m_pQualifierNames, m_pQualifierTypeNames, &m_pQualifiers, &m_numQualifiers));
    RETURN_IF_FAILED(CreateVersion(pVersion, &m_pVersion));

    return S_OK;
}

HRESULT MrmEnvironment::GetResourceItemType(_In_ PCWSTR pTypeName, _Out_ MrmEnvironment::ResourceItemType* type)
{
    *type = ResourceItemType_String;
    for (int i = 0; i < ARRAYSIZE(ResourceItemTypeNames); i++)
    {
        if (DefString_ICompare(pTypeName, ResourceItemTypeNames[i]) == Def_Equal)
        {
            *type = static_cast<ResourceItemType>(i);
            return S_OK;
        }
    }

    return E_MRM_BAD_ITEM_TYPE;
}

HRESULT MrmEnvironment::GetResourceValueType(_In_ PCWSTR pTypeName, _Out_ MrmEnvironment::ResourceValueType* type)
{
    *type = ResourceValueType_Utf16String;
    for (int i = 0; i < ARRAYSIZE(ResourceValueTypeNames); i++)
    {
        if (DefString_ICompare(pTypeName, ResourceValueTypeNames[i]) == Def_Equal)
        {
            *type = static_cast<ResourceValueType>(i);
            return S_OK;
        }
    }

    return HRESULT_FROM_WIN32(ERROR_MRM_RESOURCE_TYPE_MISMATCH);
}

HRESULT MrmEnvironment::GetStringForResourceValueType(_In_ ResourceValueType rvType, _Inout_ StringResult* pStringOut)
{
    int typeIndex = static_cast<int>(rvType);

    if ((typeIndex >= 0) && (typeIndex < NumResourceValueTypes))
    {
        RETURN_IF_FAILED(pStringOut->SetRef(ResourceValueTypeNames[typeIndex]));
        return S_OK;
    }

    return HRESULT_FROM_WIN32(ERROR_MRM_RESOURCE_TYPE_MISMATCH);
}

HRESULT MrmEnvironment::GetExternalStringForResourceValueType(_In_ ResourceValueType actualType, _Inout_ StringResult* externalString)
{
    MrmEnvironment::ResourceValueType externalType;
    RETURN_IF_FAILED(GetExternalResourceValueType(actualType, &externalType));
    RETURN_IF_FAILED(GetStringForResourceValueType(externalType, externalString));

    return S_OK;
}

HRESULT MrmEnvironment::GetExternalResourceValueType(_In_ ResourceValueType actualType, _Inout_ ResourceValueType* externalType)
{
    if (IsStringResourceValueType(actualType))
    {
        *externalType = ResourceValueType_Utf16String;
    }
    else if (IsPathResourceValueType(actualType))
    {
        *externalType = ResourceValueType_Utf16Path;
    }
    else if (IsBinaryResourceValueType(actualType))
    {
        *externalType = ResourceValueType_EmbeddedData;
    }
    else
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_RESOURCE_TYPE_MISMATCH);
    }

    return S_OK;
}

HRESULT MrmEnvironment::GetQualifier(_In_ PCWSTR pQualifierName, _Out_ ResourceQualifier* pQualifierOut) const
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER), DefString_IsEmpty(pQualifierName));
    RETURN_HR_IF_NULL(E_INVALIDARG, pQualifierOut);

    Atom::Index index = Atom::IndexNone;
    if ((m_pQualifierNames == nullptr) || (!m_pQualifierNames->TryGetIndex(pQualifierName, &index)))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER);
    }

    *pQualifierOut = m_pQualifiers[index];
    return S_OK;
}

HRESULT MrmEnvironment::GetQualifier(_In_ int qualifierIndex, _Out_ ResourceQualifier* pQualifierOut) const
{
    RETURN_HR_IF(E_INVALIDARG, (pQualifierOut == nullptr) || (qualifierIndex < 0) || (qualifierIndex > m_numQualifiers - 1));

    *pQualifierOut = m_pQualifiers[qualifierIndex];
    return S_OK;
}

HRESULT MrmEnvironment::GetQualifier(_In_ Atom qualifierName, _Out_ ResourceQualifier* pQualifierOut) const
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pQualifierOut);
    RETURN_HR_IF(
        HRESULT_FROM_WIN32(ERROR_MRM_INVALID_FILE_TYPE),
        (m_pQualifierNames == nullptr) || (qualifierName.GetPoolIndex() != m_pQualifierNames->GetPoolIndex()));
    RETURN_HR_IF(E_INVALIDARG, (qualifierName.GetIndex() < 0) || (qualifierName.GetIndex() > m_numQualifiers - 1));

    *pQualifierOut = m_pQualifiers[qualifierName.GetIndex()];
    return S_OK;
}

HRESULT MrmEnvironment::GetQualifierInfo(_In_ INT32 evIndex, _Outptr_ const QUALIFIER_INFO** ppQualifierInfo) const
{
    // get the env version token (checksum)
    const UINT32 evToken = m_pEnvironmentInitializer->pEnvironmentDescription->pVersions[evIndex].checksum;

    // find the qualifier info with the matching evToken
    for (int qualifierInfoIx = 0; qualifierInfoIx < m_pEnvironmentInitializer->numQualifierInfos; qualifierInfoIx++)
    {
        if (m_pEnvironmentInitializer->pQualifierInfos[qualifierInfoIx].evToken == evToken)
        {
            *ppQualifierInfo = &(m_pEnvironmentInitializer->pQualifierInfos[qualifierInfoIx]);
            return S_OK;
        }
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT MrmEnvironment::FindInfoForVersion(
    _In_ const ENVIRONMENT_DESCRIPTION* pDescription,
    _In_ int major,
    _In_ int minor,
    _Out_opt_ const MRMFILE_ENVIRONMENT_VERSION_INFO** ppInfoOut,
    _Inout_opt_ StringResult* pUniqueNameOut,
    _Inout_opt_ StringResult* pSimpleNameOut)
{
    const MRMFILE_ENVIRONMENT_VERSION_INFO* pVersion;
    RETURN_IF_FAILED(MrmEnvironment::ChooseVersion(pDescription, major, minor, &pVersion));
    RETURN_HR_IF_NULL(E_DEF_UNSUPPORTED_VERSION, pVersion);

    if (ppInfoOut != nullptr)
    {
        *ppInfoOut = pVersion;
    }

    if (pUniqueNameOut != nullptr)
    {
        RETURN_IF_FAILED(pUniqueNameOut->SetRef(pDescription->pUniqueName));
    }

    if (pSimpleNameOut != nullptr)
    {
        RETURN_IF_FAILED(pSimpleNameOut->SetRef(pDescription->pSimpleName));
    }

    return S_OK;
}

HRESULT MrmEnvironment::FindInfoForVersion(
    _In_ const ENVIRONMENT_DESCRIPTION* environmentDescription,
    _In_ int index,
    _Out_opt_ const MRMFILE_ENVIRONMENT_VERSION_INFO** versionInfo,
    _Inout_opt_ StringResult* uniqueName,
    _Inout_opt_ StringResult* simpleName)
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND), (index < 0) || (index >= environmentDescription->numVersions));

    if (versionInfo != nullptr)
    {
        *versionInfo = &environmentDescription->pVersions[index];
    }

    if (uniqueName != nullptr)
    {
        RETURN_IF_FAILED(uniqueName->SetRef(environmentDescription->pUniqueName));
    }

    if (simpleName != nullptr)
    {
        RETURN_IF_FAILED(simpleName->SetRef(environmentDescription->pSimpleName));
    }

    return S_OK;
}

HRESULT MrmEnvironment::FindInfoForCurrentVersion(
    _In_ const ENVIRONMENT_DESCRIPTION* pDescription,
    _Out_opt_ const MRMFILE_ENVIRONMENT_VERSION_INFO** ppInfoOut,
    _Inout_opt_ StringResult* pUniqueNameOut,
    _Inout_opt_ StringResult* pSimpleNameOut)
{
    // Version 0 is default
    const MRMFILE_ENVIRONMENT_VERSION_INFO* pVersion = &pDescription->pVersions[0];

    if (ppInfoOut != nullptr)
    {
        *ppInfoOut = pVersion;
    }

    if (pUniqueNameOut != nullptr)
    {
        RETURN_IF_FAILED(pUniqueNameOut->SetRef(pDescription->pUniqueName));
    }

    if (pSimpleNameOut != nullptr)
    {
        RETURN_IF_FAILED(pSimpleNameOut->SetRef(pDescription->pSimpleName));
    }

    return S_OK;
}

_Success_(return == true)
bool MrmEnvironment::TryFindInfoByChecksum(
    _In_ const ENVIRONMENT_DESCRIPTION* description,
    _In_opt_ DefChecksum::Checksum checksum,
    _Out_opt_ const MRMFILE_ENVIRONMENT_VERSION_INFO** versionOut,
    _Inout_opt_ StringResult* uniqueNameOut,
    _Inout_opt_ StringResult* simpleNameOut)
{
    for (int i = 0; i < description->numVersions; i++)
    {
        if (description->pVersions[i].checksum == checksum)
        {
            if (versionOut != nullptr)
            {
                *versionOut = &description->pVersions[i];
            }

            if (uniqueNameOut != nullptr)
            {
                Def_IfFailedReturnFalse(uniqueNameOut->SetRef(description->pUniqueName));
            }

            if (simpleNameOut != nullptr)
            {
                Def_IfFailedReturnFalse(simpleNameOut->SetRef(description->pSimpleName));
            }

            return true;
        }
    }

    return false;
}

HRESULT
EnvironmentVersionInfo::CreateInstance(_In_ const MRMFILE_ENVIRONMENT_VERSION_INFO* pVersion, _Outptr_ EnvironmentVersionInfo** info)
{
    *info = nullptr;

    RETURN_HR_IF_NULL(E_INVALIDARG, pVersion);

    EnvironmentVersionInfo* pRtrn = new EnvironmentVersionInfo(pVersion);
    RETURN_IF_NULL_ALLOC(pRtrn);

    *info = pRtrn;
    return S_OK;
}

HRESULT EnvironmentVersionInfo::CreateInstance(_In_ const EnvironmentVersionInfo* cloneFrom, _Outptr_ EnvironmentVersionInfo** info)
{
    *info = nullptr;

    EnvironmentVersionInfo* rtrn = new EnvironmentVersionInfo(&cloneFrom->m_version);
    RETURN_IF_NULL_ALLOC(rtrn);

    *info = rtrn;
    return S_OK;
}

HRESULT EnvironmentVersionInfo::CreateEmpty(_Outptr_ EnvironmentVersionInfo** info)
{
    *info = nullptr;

    EnvironmentVersionInfo* pRtrn = new EnvironmentVersionInfo(nullptr);
    RETURN_IF_NULL_ALLOC(pRtrn);

    *info = pRtrn;
    return S_OK;
}

HRESULT EnvironmentVersionInfo::ComputeNew(
    _In_ const IEnvironment* pEnvironment,
    _In_opt_ const MRMFILE_ENVIRONMENT_VERSION_INFO* pDesiredVersionInfo,
    _Outptr_ EnvironmentVersionInfo** info)
{
    *info = nullptr;

    RETURN_HR_IF_NULL(E_INVALIDARG, pEnvironment);

    MRMFILE_ENVIRONMENT_VERSION_INFO vi;

    // Start out with the current version of the supplied environment
    pEnvironment->GetVersionInfo()->GetVersionInfo(&vi);

    // for compatible versions make some adjustments, if appropriate
    if (pDesiredVersionInfo != nullptr)
    {
        if (vi.major == pDesiredVersionInfo->major && vi.minor >= pDesiredVersionInfo->minor &&
            vi.numQualifierTypes >= pDesiredVersionInfo->numQualifierTypes && vi.numQualifiers >= pDesiredVersionInfo->numQualifiers &&
            vi.numItemTypes >= pDesiredVersionInfo->numItemTypes &&
            vi.numResourceValueTypes >= pDesiredVersionInfo->numResourceValueTypes &&
            vi.numResourceValueLocators >= pDesiredVersionInfo->numResourceValueLocators &&
            vi.numConditionOperators >= pDesiredVersionInfo->numConditionOperators)
        {
            vi.minor = pDesiredVersionInfo->minor;
            vi.numQualifierTypes = pDesiredVersionInfo->numQualifierTypes;
            vi.numQualifiers = pDesiredVersionInfo->numQualifiers;
            vi.numItemTypes = pDesiredVersionInfo->numItemTypes;
            vi.numResourceValueTypes = pDesiredVersionInfo->numResourceValueTypes;
            vi.numResourceValueLocators = pDesiredVersionInfo->numResourceValueLocators;
            vi.numConditionOperators = pDesiredVersionInfo->numConditionOperators;
        }
    }

    AutoDeletePtr<EnvironmentVersionInfo> pRtrn;
    RETURN_IF_FAILED(EnvironmentVersionInfo::CreateInstance(&vi, &pRtrn));

    DefChecksum::Checksum checksum = 0;
    RETURN_IF_FAILED(ComputeEnvironmentVersionChecksum(pEnvironment, pRtrn, &checksum));

    pRtrn->m_version.checksum = checksum;
    *info = pRtrn.Detach();

    return S_OK;
}

/*!
     * Computes the checksum that would apply to a supplied environment at
     * a specific previous version.
     *
     * \param pEnvironment
     * The environment for which the checksum is to be computed.
     *
     * \param pVersion
     * The version at which the checksum is to be computed.
     *
     * \param pStatus
     * This function fails immediately without extended status if pStatus in NULL.
     * Otherwise, pStatus reports extended status when an error occurs:
     * - INVALID_ARG if pEnvironment, pVersion or pChecksumOut are NULL
     * - SIZE_MISMATCH if any of the atom pools in pEnvironment are smaller than the
     *   sizes specified in pVersion.
     *
     * \param pChecksumOut
     * Returns the checksum of pEnvironment at the sizes specified in pVersion.
     *
     * \return bool
     * Returns true on success, false if an error occurs.
     */
HRESULT ComputeEnvironmentVersionChecksum(
    _In_ const IEnvironment* pEnvironment,
    _In_ const IEnvironmentVersionInfo* pVersion,
    _Out_ DefChecksum::Checksum* pChecksumOut)
{
    RETURN_HR_IF(E_INVALIDARG, (pEnvironment == nullptr) || (pVersion == nullptr) || (pChecksumOut == nullptr));

    union
    {
        UINT32 ui32;
        UINT16 ui16[2];
    } v;
    v.ui16[0] = pVersion->GetMajorVersion();
    v.ui16[1] = pVersion->GetMinorVersion();
    DEF_CHECKSUM crc;
    RETURN_IF_FAILED(DefChecksum::ComputeStringChecksum(0, true, pEnvironment->GetUniqueName(), &crc));
    crc = DefChecksum::ComputeUInt32Checksum(crc, v.ui32);
    RETURN_IF_FAILED(
        DefChecksum::ComputeAtomPoolChecksum(crc, pEnvironment->GetQualifierTypeNames(), pVersion->GetNumQualifierTypes(), &crc));
    RETURN_IF_FAILED(DefChecksum::ComputeAtomPoolChecksum(crc, pEnvironment->GetQualifierNames(), pVersion->GetNumQualifiers(), &crc));
    RETURN_IF_FAILED(DefChecksum::ComputeAtomPoolChecksum(crc, pEnvironment->GetItemTypeNames(), pVersion->GetNumItemTypes(), &crc));
    RETURN_IF_FAILED(
        DefChecksum::ComputeAtomPoolChecksum(crc, pEnvironment->GetResourceValueTypeNames(), pVersion->GetNumResourceValueTypes(), &crc));
    RETURN_IF_FAILED(DefChecksum::ComputeAtomPoolChecksum(
        crc, pEnvironment->GetResourceValueLocatorNames(), pVersion->GetNumResourceValueLocators(), &crc));
    RETURN_IF_FAILED(
        DefChecksum::ComputeAtomPoolChecksum(crc, pEnvironment->GetConditionOperatorNames(), pVersion->GetNumConditionOperators(), &crc));

    ResourceQualifier qualifier;
    UINT32 priority;
    for (int i = 0; i < pVersion->GetNumQualifiers(); i++)
    {
        RETURN_IF_FAILED(pEnvironment->GetQualifier(i, &qualifier));

        RETURN_IF_FAILED(DefChecksum::ComputeAtomChecksum(crc, qualifier.qualifierType, pEnvironment->GetAtoms(), &crc));

        if (qualifier.defaultRuntimePriority < ResourceQualifier::MinPriority)
        {
            priority = ResourceQualifier::MinPriority;
        }
        else if (qualifier.defaultRuntimePriority > ResourceQualifier::MaxPriority)
        {
            priority = ResourceQualifier::MaxPriority;
        }
        else
        {
            priority = qualifier.defaultRuntimePriority;
        }
        crc = DefChecksum::ComputeUInt32Checksum(crc, priority);
    }
    *pChecksumOut = crc;
    return S_OK;
}

/*!
     * Constructs an IEnvironmentVersionInfo from a supplied IEnvironment,
     * without referring to the existing environment version info.  Uses
     * the supplied major & minor versions and computes rather than copies
     * the version checksum.
     *
     * The caller is responsible for deleting the returned object.
     *
     * \param pEnvironment
     * The environment for which the version is to be computed.
     *
     * \param pStatus
     * Reports extended status if an error occurs.
     *
     * \return IEnvironmentVersionInfo*
     * Returns an IEnvironmentVersionInfo describing the supplied environment,
     * or NULL if an error occurs.   The caller is responsible for deleting
     * the returned version info.
     */
HRESULT ComputeEnvironmentVersionInfo(
    _In_ const IEnvironment* pEnvironment,
    _In_opt_ const MRMFILE_ENVIRONMENT_VERSION_INFO* pDesiredVersionInfo,
    _Outptr_ IEnvironmentVersionInfo** info)
{
    return EnvironmentVersionInfo::ComputeNew(pEnvironment, pDesiredVersionInfo, (EnvironmentVersionInfo**)info);
}

/*!
     * Determines if two IEnvironmentVersionInfo are identical.
     *
     * \param pVersion1
     * The first version info object to be compared.
     *
     * \param pVersion2
     * The second version info object to be compared.
     *
     * \param pStatus
     * CheckEnvironmentVersionIsIdentical returns false immediately and
     * without reporting extended status if pStatus is NULL.  Otherwise,
     * pStatus reports extended status if an error occurs:
     * - INVALID_ARG if either parameter is NULL
     *
     * \return bool
     * Returns true if the versions are identical, false otherwise or if
     * an error occurs.
     */
bool CheckEnvironmentVersionIsIdentical(_In_ const IEnvironmentVersionInfo* pVersion1, _In_ const IEnvironmentVersionInfo* pVersion2)
{
    if ((pVersion1 == nullptr) || (pVersion2 == nullptr))
    {
        return false;
    }

    if ((pVersion1->GetMajorVersion() != pVersion2->GetMajorVersion()) || (pVersion1->GetMinorVersion() != pVersion2->GetMinorVersion()) ||
        (pVersion1->GetVersionChecksum() != pVersion2->GetVersionChecksum()) ||
        (pVersion1->GetNumQualifierTypes() != pVersion2->GetNumQualifierTypes()) ||
        (pVersion1->GetNumQualifiers() != pVersion2->GetNumQualifiers()) ||
        (pVersion1->GetNumItemTypes() != pVersion2->GetNumItemTypes()) ||
        (pVersion1->GetNumResourceValueTypes() != pVersion2->GetNumResourceValueTypes()) ||
        (pVersion1->GetNumResourceValueLocators() != pVersion2->GetNumResourceValueLocators()) ||
        (pVersion1->GetNumConditionOperators() != pVersion2->GetNumConditionOperators()))
    {
        return false;
    }
    return true;
}

/*!
     * Determines if a desired IEnvironmentVersionInfo is compatible with
     * an available IEnvironment.
     *
     * \param pHaveEnvironment
     * A version info object describing the environment that
     * is actually present.
     *
     * \param pWantVersion
     * A version info object describing the desired environment version.
     *
     * \param pStatus
     * CheckEnvironmentVersionIsCompatible returns false immediately and
     * without reporting extended status if pStatus is NULL.  Otherwise,
     * pStatus reports extended status if an error occurs:
     * - INVALID_ARG if either parameter is NULL
     *
     * \return bool
     * Returns true if the versions are compatible, false otherwise or if
     * an error occurs.
     */
bool CheckEnvironmentVersionIsCompatible(_In_ const IEnvironment* pHaveEnvironment, _In_ const IEnvironmentVersionInfo* pWantVersion)
{
    if ((pHaveEnvironment == nullptr) || (pWantVersion == nullptr))
    {
        return false;
    }

    const IEnvironmentVersionInfo* pHaveVersion = pHaveEnvironment->GetVersionInfo();
    if (CheckEnvironmentVersionIsIdentical(pWantVersion, pHaveVersion))
    {
        return true;
    }
    if ((pWantVersion->GetMajorVersion() != pHaveVersion->GetMajorVersion()) ||
        (pWantVersion->GetMinorVersion() >= pHaveVersion->GetMinorVersion()))
    {
        return false;
    }

    DefChecksum::Checksum cs = 0;
    return (
        SUCCEEDED(ComputeEnvironmentVersionChecksum(pHaveEnvironment, pWantVersion, &cs)) && (cs == pWantVersion->GetVersionChecksum()));
}

/*!
     * Computes the atom pool mappings from the environment we want to the environment
     * we actually have.
     *
     * \param pHaveEnvironment
     * The environment we have.
     *
     * \param pWantEnvironment
     * The environment we want.
     *
     * \param pStatus
     * Reports extended status if an error occurs.
     *
     * \param pPoolMappingsOut
     * Remap info to be initialized with the appropriate mappings.
     *
     * \return bool
     * Returns true on success, false if an error occurs.
     */
HRESULT ComputeEnvironmentPoolMappings(
    _In_ const IEnvironment* pHaveEnvironment,
    _In_ const IEnvironment* pWantEnvironment,
    _Inout_ RemapInfo* pPoolMappingsOut)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pHaveEnvironment);
    RETURN_HR_IF_NULL(E_INVALIDARG, pWantEnvironment);
    RETURN_HR_IF_NULL(E_INVALIDARG, pPoolMappingsOut);

    Atom::PoolIndex maxIndex = pWantEnvironment->GetQualifierTypeNames()->GetPoolIndex();
    maxIndex = max(maxIndex, pWantEnvironment->GetQualifierNames()->GetPoolIndex());
    maxIndex = max(maxIndex, pWantEnvironment->GetItemTypeNames()->GetPoolIndex());
    maxIndex = max(maxIndex, pWantEnvironment->GetResourceValueTypeNames()->GetPoolIndex());
    maxIndex = max(maxIndex, pWantEnvironment->GetResourceValueLocatorNames()->GetPoolIndex());
    maxIndex = max(maxIndex, pWantEnvironment->GetConditionOperatorNames()->GetPoolIndex());

    RETURN_IF_FAILED(pPoolMappingsOut->SetAtomPoolMappingArray(maxIndex + 1, NULL));

    RETURN_IF_FAILED(pPoolMappingsOut->SetAtomPoolMapping(
        pWantEnvironment->GetQualifierTypeNames()->GetPoolIndex(), pHaveEnvironment->GetQualifierTypeNames()->GetPoolIndex()));
    RETURN_IF_FAILED(pPoolMappingsOut->SetAtomPoolMapping(
        pWantEnvironment->GetQualifierNames()->GetPoolIndex(), pHaveEnvironment->GetQualifierNames()->GetPoolIndex()));
    RETURN_IF_FAILED(pPoolMappingsOut->SetAtomPoolMapping(
        pWantEnvironment->GetItemTypeNames()->GetPoolIndex(), pHaveEnvironment->GetItemTypeNames()->GetPoolIndex()));
    RETURN_IF_FAILED(pPoolMappingsOut->SetAtomPoolMapping(
        pWantEnvironment->GetResourceValueTypeNames()->GetPoolIndex(), pHaveEnvironment->GetResourceValueTypeNames()->GetPoolIndex()));
    RETURN_IF_FAILED(pPoolMappingsOut->SetAtomPoolMapping(
        pWantEnvironment->GetResourceValueLocatorNames()->GetPoolIndex(),
        pHaveEnvironment->GetResourceValueLocatorNames()->GetPoolIndex()));
    RETURN_IF_FAILED(pPoolMappingsOut->SetAtomPoolMapping(
        pWantEnvironment->GetConditionOperatorNames()->GetPoolIndex(), pHaveEnvironment->GetConditionOperatorNames()->GetPoolIndex()));

    return S_OK;
}

/*!
     * Computes the atom pool mappings from the environment we want to the environment
     * we actually have.
     *
     * \param pHaveEnvironment
     * The environment we have.
     *
     * \param pWantEnvironment
     * The environment we want.
     *
     * \param pStatus
     * Reports extended status if an error occurs.
     *
     * \param pPoolMappingsOut
     * UInt16Remap to be initialized with the appropriate mappings.
     *
     * \return HRESULT
     * Returns S_OK on success, a failure HRESULT if an error occurs.
     */
HRESULT ComputeEnvironmentPoolMappings(
    _In_ const IEnvironment* pHave,
    _In_ const IEnvironment* pWant,
    _Inout_ RemapUInt16* pPoolMappingsOut)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pHave);
    RETURN_HR_IF_NULL(E_INVALIDARG, pWant);
    RETURN_HR_IF_NULL(E_INVALIDARG, pPoolMappingsOut);

    UINT16 have;
    UINT16 want;
    RETURN_IF_FAILED(pHave->GetQualifierTypeNames()->GetSmallPoolIndex(&have));
    RETURN_IF_FAILED(pWant->GetQualifierTypeNames()->GetSmallPoolIndex(&want));
    RETURN_HR_IF(E_FAIL, !pPoolMappingsOut->TrySetMapping(want, have));

    RETURN_IF_FAILED(pHave->GetQualifierNames()->GetSmallPoolIndex(&have));
    RETURN_IF_FAILED(pWant->GetQualifierNames()->GetSmallPoolIndex(&want));
    RETURN_HR_IF(E_FAIL, !pPoolMappingsOut->TrySetMapping(want, have));

    RETURN_IF_FAILED(pHave->GetItemTypeNames()->GetSmallPoolIndex(&have));
    RETURN_IF_FAILED(pWant->GetItemTypeNames()->GetSmallPoolIndex(&want));
    RETURN_HR_IF(E_FAIL, !pPoolMappingsOut->TrySetMapping(want, have));

    RETURN_IF_FAILED(pHave->GetResourceValueTypeNames()->GetSmallPoolIndex(&have));
    RETURN_IF_FAILED(pWant->GetResourceValueTypeNames()->GetSmallPoolIndex(&want));
    RETURN_HR_IF(E_FAIL, !pPoolMappingsOut->TrySetMapping(want, have));

    RETURN_IF_FAILED(pHave->GetResourceValueLocatorNames()->GetSmallPoolIndex(&have));
    RETURN_IF_FAILED(pWant->GetResourceValueLocatorNames()->GetSmallPoolIndex(&want));
    RETURN_HR_IF(E_FAIL, !pPoolMappingsOut->TrySetMapping(want, have));

    RETURN_IF_FAILED(pHave->GetConditionOperatorNames()->GetSmallPoolIndex(&have));
    RETURN_IF_FAILED(pWant->GetConditionOperatorNames()->GetSmallPoolIndex(&want));
    RETURN_HR_IF(E_FAIL, !pPoolMappingsOut->TrySetMapping(want, have));

    return S_OK;
}

HRESULT ComputeEnvironmentPoolMappings(
    _In_ const IEnvironment* pHaveEnvironment,
    _In_ const EnvironmentReference* pWantRef,
    _Inout_ RemapInfo* pPoolMappingsOut)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pHaveEnvironment);
    RETURN_HR_IF_NULL(E_INVALIDARG, pWantRef);
    RETURN_HR_IF_NULL(E_INVALIDARG, pPoolMappingsOut);

    Atom::PoolIndex maxIndex = pWantRef->GetQualifierTypesPoolIndex();
    maxIndex = max(maxIndex, pWantRef->GetQualifiersPoolIndex());
    maxIndex = max(maxIndex, pWantRef->GetItemTypesPoolIndex());
    maxIndex = max(maxIndex, pWantRef->GetResourceValueTypesPoolIndex());
    maxIndex = max(maxIndex, pWantRef->GetResourceValueLocatorsPoolIndex());
    maxIndex = max(maxIndex, pWantRef->GetConditionOperatorsPoolIndex());

    RETURN_IF_FAILED(pPoolMappingsOut->SetAtomPoolMappingArray(maxIndex + 1, nullptr));

    RETURN_IF_FAILED(pPoolMappingsOut->SetAtomPoolMapping(
        pWantRef->GetQualifierTypesPoolIndex(), pHaveEnvironment->GetQualifierTypeNames()->GetPoolIndex()));
    RETURN_IF_FAILED(
        pPoolMappingsOut->SetAtomPoolMapping(pWantRef->GetQualifiersPoolIndex(), pHaveEnvironment->GetQualifierNames()->GetPoolIndex()));
    RETURN_IF_FAILED(
        pPoolMappingsOut->SetAtomPoolMapping(pWantRef->GetItemTypesPoolIndex(), pHaveEnvironment->GetItemTypeNames()->GetPoolIndex()));
    RETURN_IF_FAILED(pPoolMappingsOut->SetAtomPoolMapping(
        pWantRef->GetResourceValueTypesPoolIndex(), pHaveEnvironment->GetResourceValueTypeNames()->GetPoolIndex()));
    RETURN_IF_FAILED(pPoolMappingsOut->SetAtomPoolMapping(
        pWantRef->GetResourceValueLocatorsPoolIndex(), pHaveEnvironment->GetResourceValueLocatorNames()->GetPoolIndex()));
    RETURN_IF_FAILED(pPoolMappingsOut->SetAtomPoolMapping(
        pWantRef->GetConditionOperatorsPoolIndex(), pHaveEnvironment->GetConditionOperatorNames()->GetPoolIndex()));

    return S_OK;
}

/*!
 * Simple projection of an MRMFILE_ENVIRONMENT_REF file data structure
 */

HRESULT EnvironmentReference::Init(_In_ const IEnvironment* pEnvironment)
{
    DEF_ASSERT(pEnvironment != nullptr);

    SecureZeroMemory(&m_ref, sizeof(MRMFILE_ENVIRONMENT_REF));
    RETURN_IF_FAILED(_DefStringCchCopy(&m_ref.uniqueName[0], MRM_UNIQUE_NAME_LENGTH, pEnvironment->GetUniqueName()));

    const IEnvironmentVersionInfo* pVersion = pEnvironment->GetVersionInfo();

    m_ref.version.major = pVersion->GetMajorVersion();
    m_ref.version.minor = pVersion->GetMinorVersion();
    m_ref.version.checksum = pVersion->GetVersionChecksum();
    m_ref.version.numQualifierTypes = static_cast<DEF_ATOM_COUNT_SMALL>(pVersion->GetNumQualifierTypes());
    m_ref.version.numQualifiers = static_cast<DEF_ATOM_COUNT_SMALL>(pVersion->GetNumQualifiers());
    m_ref.version.numItemTypes = static_cast<DEF_ATOM_COUNT_SMALL>(pVersion->GetNumItemTypes());
    m_ref.version.numResourceValueTypes = static_cast<DEF_ATOM_COUNT_SMALL>(pVersion->GetNumResourceValueTypes());
    m_ref.version.numResourceValueLocators = static_cast<DEF_ATOM_COUNT_SMALL>(pVersion->GetNumResourceValueLocators());
    m_ref.version.numConditionOperators = static_cast<DEF_ATOM_COUNT_SMALL>(pVersion->GetNumConditionOperators());
    m_ref.qualifierTypesPoolIndex = pEnvironment->GetQualifierTypeNames()->GetPoolIndex();
    m_ref.qualifiersPoolIndex = pEnvironment->GetQualifierNames()->GetPoolIndex();
    m_ref.itemTypesPoolIndex = pEnvironment->GetItemTypeNames()->GetPoolIndex();
    m_ref.resourceValueTypesPoolIndex = pEnvironment->GetResourceValueTypeNames()->GetPoolIndex();
    m_ref.resourceValueLocatorsPoolIndex = pEnvironment->GetResourceValueLocatorNames()->GetPoolIndex();
    m_ref.conditionOperatorsPoolIndex = pEnvironment->GetConditionOperatorNames()->GetPoolIndex();
    return S_OK;
}

HRESULT EnvironmentReference::CreateInstance(_In_ const MRMFILE_ENVIRONMENT_REF* pFileRef, _Outptr_ EnvironmentReference** ref)
{
    *ref = nullptr;

    RETURN_HR_IF_NULL(E_INVALIDARG, pFileRef);

    EnvironmentReference* pRtrn = new EnvironmentReference();
    RETURN_IF_NULL_ALLOC(pRtrn);

    pRtrn->m_ref = *pFileRef;
    *ref = pRtrn;

    return S_OK;
}

HRESULT EnvironmentReference::CreateInstance(_In_ const IEnvironment* pEnvironment, _Outptr_ EnvironmentReference** ref)
{
    *ref = nullptr;

    RETURN_HR_IF_NULL(E_INVALIDARG, pEnvironment);

    AutoDeletePtr<EnvironmentReference> pRtrn = new EnvironmentReference();
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->Init(pEnvironment));

    *ref = pRtrn.Detach();

    return S_OK;
}

HRESULT EnvironmentReference::CreateInstance(_In_ const EnvironmentReference* cloneFrom, _Outptr_ EnvironmentReference** ref)
{
    *ref = nullptr;

    RETURN_HR_IF_NULL(E_INVALIDARG, cloneFrom);

    EnvironmentReference* rtrn = new EnvironmentReference();
    RETURN_IF_NULL_ALLOC(rtrn);

    rtrn->m_ref = cloneFrom->m_ref;
    *ref = rtrn;
    return S_OK;
}

bool EnvironmentReference::CheckIsIdentical(_In_ const IEnvironment* pEnvironment) const
{
    if (pEnvironment == nullptr)
    {
        return false;
    }

    const IEnvironmentVersionInfo* pVersion = pEnvironment->GetVersionInfo();
    if ((DefString_CchCompareWithOptions(
             &m_ref.uniqueName[0], pEnvironment->GetUniqueName(), MRM_UNIQUE_NAME_LENGTH, DefCompare_CaseInsensitive) != Def_Equal) ||
        (!CheckEnvironmentVersionIsIdentical(this, pVersion)))
    {
        return false;
    }

    return true;
}

bool EnvironmentReference::CheckIsCompatible(_In_ const IEnvironment* pEnvironment) const
{
    if (pEnvironment == nullptr)
    {
        return false;
    }

    if ((DefString_CchCompareWithOptions(
             &m_ref.uniqueName[0], pEnvironment->GetUniqueName(), MRM_UNIQUE_NAME_LENGTH, DefCompare_CaseInsensitive) != Def_Equal) ||
        (GetMajorVersion() != pEnvironment->GetVersionInfo()->GetMajorVersion()) ||
        (GetMinorVersion() > pEnvironment->GetVersionInfo()->GetMinorVersion()))
    {
        return false;
    }

    if (CheckIsIdentical(pEnvironment))
    {
        return true;
    }

    DefChecksum::Checksum cs = 0;
    return (SUCCEEDED(ComputeEnvironmentVersionChecksum(pEnvironment, this, &cs)) && (cs == m_ref.version.checksum));
}

bool EnvironmentReference::CheckIsIdentical(
    _In_ PCWSTR wantName,
    _In_ const IEnvironmentVersionInfo* wantVersion,
    _In_ PCWSTR haveName,
    _In_ const IEnvironmentVersionInfo* haveVersion)
{
    if ((DefString_ICompare(wantName, haveName) != Def_Equal) || (!CheckEnvironmentVersionIsIdentical(wantVersion, haveVersion)))
    {
        return false;
    }

    return true;
}

bool EnvironmentReference::CheckIsCompatible(
    _In_ PCWSTR wantEnvironmentName,
    _In_ const IEnvironmentVersionInfo* wantEnvironmentVersion,
    _In_ const IEnvironment* haveEnvironment)
{
    if ((DefString_CchCompareWithOptions(
             wantEnvironmentName, haveEnvironment->GetUniqueName(), MRM_UNIQUE_NAME_LENGTH, DefCompare_CaseInsensitive) != Def_Equal) ||
        (!CheckEnvironmentVersionIsCompatible(haveEnvironment, wantEnvironmentVersion)))
    {
        return false;
    }

    return true;
}

HRESULT EnvironmentMapping::CreateInstance(
    _In_ const CoreProfile* profile,
    _In_ const IEnvironmentCollection* environments,
    _In_reads_bytes_(dataSizeInBytes) const void* rawData,
    _In_ size_t dataSizeInBytes,
    _Outptr_ EnvironmentMapping** mapping)
{
    *mapping = nullptr;
    AutoDeletePtr<EnvironmentMapping> rtrn = new EnvironmentMapping();
    RETURN_IF_NULL_ALLOC(rtrn);

    RETURN_IF_FAILED(rtrn->Init(profile, environments, rawData, dataSizeInBytes));

    *mapping = rtrn.Detach();

    return S_OK;
}

EnvironmentMapping::~EnvironmentMapping()
{
    Def_Free(m_qualifierMappings);
    Def_Free(m_qualifierNames);
}

HRESULT EnvironmentMapping::GetEnvironmentInfo(_Inout_ StringResult* uniqueName, _Out_ EnvironmentVersionInfo* versionInfo) const
{
    RETURN_IF_FAILED(uniqueName->SetRef(m_uniqueName.GetRef()));
    versionInfo->SetVersionInfo(&m_version);
    return S_OK;
}

HRESULT EnvironmentMapping::GetQualifierInfo(
    _Out_ int* numMappedQualifiers,
    _Outptr_result_buffer_maybenull_(*numMappedQualifiers) const PCWSTR** mappedQualifierNames,
    _Outptr_result_buffer_maybenull_(*numMappedQualifiers) const Atom::SmallIndex** qualifierMappings) const
{
    *numMappedQualifiers = GetNumQualifiers();

    if (mappedQualifierNames != nullptr)
    {
        *mappedQualifierNames = m_qualifierNames;
    }

    if (qualifierMappings != nullptr)
    {
        *qualifierMappings = m_qualifierMappings;
    }

    return S_OK;
}

HRESULT EnvironmentMapping::Init(
    _In_ const CoreProfile* profile,
    _In_ const IEnvironmentCollection* environments,
    _In_reads_bytes_(dataSizeInBytes) const void* rawData,
    _In_ size_t dataSizeInBytes)
{
    SectionParser data;

    RETURN_IF_FAILED(data.Set(rawData, static_cast<UINT32>(dataSizeInBytes)));

    // This section describes the environment expected by this file, relative to some
    // baseline environment in the past.  We need to figure to map from the desired
    // environment to the our actual runtime ("default") environment, which could
    // be any of:
    // - Baseline or newer than the baseline but older than the expected environment
    //   Any unknown ("future") qualifiers are unmapped and cannot be resolved at runtime. The
    //   names of unknown qualifiers are correct, though, when resource candidates are examined.
    // - Same as or newer than the expected environment
    //   No mapping is necessary as the default environment knows all qualifiers

    HRESULT hr = S_OK;
    m_header = _SECTION_PARSER_NEXT(data, MRMFILE_ENVIRONMENT_MAPPING_HEADER, &hr);
    RETURN_IF_FAILED(hr);
    RETURN_HR_IF_EXPECTED(S_OK, m_header == nullptr);

    AutoDeletePtr<EnvironmentVersionInfo> baseVersion;
    RETURN_IF_FAILED(EnvironmentVersionInfo::CreateEmpty(&baseVersion));
    const IEnvironment* defaultEnvironment = environments->GetDefaultEnvironment();
    const IAtomPool* defaultQualifiers = defaultEnvironment->GetQualifierNames();

    RETURN_HR_IF(
        E_MRM_UNKNOWN_ENVIRONMENT, !profile->TryGetEnvironmentForChecksum(m_header->baseEnvironmentChecksum, &m_uniqueName, baseVersion));

    // Even the base environment is greater than our runtime. We don't support that.
    RETURN_HR_IF(E_MRM_UNSUPPORTED_ENVIRONMENT, baseVersion->GetNumQualifiers() > defaultEnvironment->GetQualifierNames()->GetNumAtoms());

    // Construct a version info for our expected environment, starting from the base.
    // Number of qualifiers, version & checksum all come from the expected environment.
    // Strictly speaking this version structure is incorrect as qualifier types might
    // also have been added, but that's immaterial since we ignore the values at runtime anyway.
    baseVersion->GetVersionInfo(&m_version);
    m_version.numQualifiers += m_header->numNewQualifiers;
    m_version.minor = m_header->currentMinorVersion;
    m_version.checksum = m_header->currentEnvironmentChecksum;

    // num qualifiers & names pool size must be > 0
    RETURN_HR_IF(
        HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), (m_header->numNewQualifiers == 0) || (m_header->namesPoolSizeInChars == 0));

    const UINT16* nameOffsets = _SECTION_PARSER_NEXT_ARRAY(data, m_header->numNewQualifiers, UINT16, &hr);
    RETURN_IF_FAILED(hr);

    m_namesPool = _SECTION_PARSER_NEXT_ARRAY(data, m_header->namesPoolSizeInChars, WCHAR, &hr);
    RETURN_IF_FAILED(hr);

    DEF_ASSERT(nameOffsets != nullptr);
    DEF_ASSERT(m_namesPool != nullptr);

    // we need qualifier mappings & names for all qualifiers in the expected environment
    m_qualifierMappings = _DefArray_AllocZeroed(Atom::SmallIndex, m_version.numQualifiers);
    RETURN_IF_NULL_ALLOC(m_qualifierMappings);

    m_qualifierNames = _DefArray_AllocZeroed(PCWSTR, m_version.numQualifiers);
    RETURN_IF_NULL_ALLOC(m_qualifierNames);

    StringResult qualifierName;

    for (UINT16 i = 0; i < m_version.numQualifiers; i++)
    {
        if (i < defaultQualifiers->GetNumAtoms())
        {
            // This qualifier is known by our runtime default environment. Use the
            // name from the runtime and map the qualifier directly.
            RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND), !defaultQualifiers->TryGetString(i, &qualifierName));

            m_qualifierNames[i] = qualifierName.GetRef();
            m_qualifierMappings[i] = i;
        }
        else
        {
            // This qualifier is not known by our runtime default environment. Use
            // the name from this section and map the qualifier to nothing.
            // Note that this section is relative to the _baseline_, not the runtime.
            int indexInFile = i - baseVersion->GetNumQualifiers();

            if ((indexInFile < 0) || (indexInFile >= m_header->numNewQualifiers) ||
                (nameOffsets[indexInFile] >= m_header->namesPoolSizeInChars))
            {
                RETURN_HR(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE));
            }

            m_qualifierNames[i] = &m_namesPool[nameOffsets[indexInFile]];
            m_qualifierMappings[i] = Atom::SmallIndexNone;
        }
    }

    return S_OK;
}

bool EnvironmentCollectionBase::TryFindEnvironment(_In_ const IEnvironmentVersionInfo* pRef, _Out_ const IEnvironment** pEnvironmentOut)
    const
{
    *pEnvironmentOut = nullptr;

    if ((pRef == nullptr) || (pEnvironmentOut == nullptr))
    {
        return false;
    }

    const IEnvironment* pCandidate;
    for (int i = 0; i < GetNumEnvironments(); i++)
    {

        if (SUCCEEDED(this->GetEnvironment(i, &pCandidate)))
        {
            if (CheckEnvironmentVersionIsIdentical(pRef, pCandidate->GetVersionInfo()))
            {
                *pEnvironmentOut = pCandidate;
                return true;
            }
        }
    }

    return false;
}

_Success_(return == true)
bool EnvironmentCollectionBase::TryFindEnvironment(_In_ PCWSTR pUniqueName, _Out_ const IEnvironment** ppEnvironmentOut) const
{
    *ppEnvironmentOut = nullptr;

    if ((pUniqueName == nullptr) || DefString_IsEmpty(pUniqueName))
    {
        return false;
    }

    const IEnvironment* pBest = nullptr;
    const IEnvironment* pCandidate = nullptr;
    for (int i = 0; i < GetNumEnvironments(); i++)
    {

        if (SUCCEEDED(this->GetEnvironment(i, &pCandidate)))
        {
            if (DefString_ICompare(pUniqueName, pCandidate->GetUniqueName()) == Def_Equal)
            {
                if (pBest == nullptr)
                {
                    pBest = pCandidate;
                }
                else if (
                    (pCandidate->GetVersionInfo()->GetMajorVersion() > pBest->GetVersionInfo()->GetMajorVersion()) ||
                    ((pCandidate->GetVersionInfo()->GetMajorVersion() == pBest->GetVersionInfo()->GetMajorVersion()) &&
                     (pCandidate->GetVersionInfo()->GetMinorVersion() > pBest->GetVersionInfo()->GetMinorVersion())))
                {
                    // See if this one is newer than the one we found before
                    pBest = pCandidate;
                }
            }
        }
    }

    *ppEnvironmentOut = pBest;

    return (pBest != nullptr);
}

_Success_(return == true)
bool EnvironmentCollectionBase::TryFindCompatibleEnvironment(
    _In_ PCWSTR pUniqueName,
    _In_ int major,
    _In_ int minor,
    _Outptr_opt_result_maybenull_ const IEnvironment** pEnvironmentOut) const
{
    if (pEnvironmentOut != nullptr)
    {
        *pEnvironmentOut = NULL;
    }
    if ((pUniqueName == nullptr) || DefString_IsEmpty(pUniqueName))
    {
        return false;
    }

    const IEnvironment* pBest = NULL;
    const IEnvironment* pCandidate = NULL;
    for (int i = 0; i < GetNumEnvironments(); i++)
    {

        if (SUCCEEDED(this->GetEnvironment(i, &pCandidate)))
        {
            if ((DefString_ICompare(pUniqueName, pCandidate->GetUniqueName()) == Def_Equal) &&
                (pCandidate->GetVersionInfo()->GetMajorVersion() == major) && (pCandidate->GetVersionInfo()->GetMinorVersion() >= minor))
            {

                if ((pBest == NULL) || (pCandidate->GetVersionInfo()->GetMinorVersion() < pBest->GetVersionInfo()->GetMinorVersion()))
                {
                    pBest = pCandidate;
                }

                if (pBest->GetVersionInfo()->GetMinorVersion() == minor)
                {
                    // exact match.  we're done.
                    break;
                }
            }
        }
    }

    if (pEnvironmentOut != NULL)
    {
        *pEnvironmentOut = pBest;
    }
    return (pBest != NULL);
}

_Success_(return == true)
bool EnvironmentCollectionBase::TryFindCompatibleEnvironment(
    _In_ const EnvironmentReference* pWantRef,
    _Outptr_opt_result_maybenull_ const IEnvironment** ppEnvironmentOut,
    _Inout_opt_ RemapInfo* pPoolMappingsOut) const
{
    if ((pWantRef == nullptr) || (ppEnvironmentOut == nullptr))
    {
        return false;
    }

    const IEnvironment* pCompatible = NULL;
    const IEnvironment* pIdentical = NULL;
    const IEnvironment* pCandidate = NULL;
    for (int i = 0; i < GetNumEnvironments(); i++)
    {

        if (SUCCEEDED(this->GetEnvironment(i, &pCandidate)))
        {
            if (CheckEnvironmentVersionIsCompatible(pCandidate, pWantRef))
            {
                // we have a compatible environment.  See if it's identical.
                if (CheckEnvironmentVersionIsIdentical(pCandidate->GetVersionInfo(), pWantRef))
                {
                    pIdentical = pCandidate;
                    break;
                }
                else if ((pCompatible == NULL) || (pCompatible->GetVersionInfo()->GetMinorVersion() > pWantRef->GetMinorVersion()))
                {
                    // just compatible, keep looking
                    pCompatible = pCandidate;
                }
            }
        }
    }

    *ppEnvironmentOut = pCandidate = ((pIdentical != NULL) ? pIdentical : pCompatible);

    if ((pCandidate != NULL) && (pPoolMappingsOut != NULL))
    {
        (void)ComputeEnvironmentPoolMappings(pCandidate, pWantRef, pPoolMappingsOut);
    }

    return (pCandidate != NULL);
}

bool EnvironmentCollectionBase::TryFindCompatibleEnvironment(
    _In_ const IEnvironment* pWantEnvironment,
    _Outptr_opt_result_maybenull_ const IEnvironment** ppEnvironmentOut,
    _Inout_opt_ RemapInfo* pPoolMappingsOut) const
{
    if ((pWantEnvironment == nullptr) || (ppEnvironmentOut == nullptr))
    {
        return false;
    }

    const IEnvironment* pCompatible = NULL;
    const IEnvironment* pIdentical = NULL;
    const IEnvironment* pCandidate = NULL;
    for (int i = 0; i < GetNumEnvironments(); i++)
    {

        if (SUCCEEDED(this->GetEnvironment(i, &pCandidate)))
        {
            if (CheckEnvironmentVersionIsCompatible(pCandidate, pWantEnvironment->GetVersionInfo()))
            {
                // we have a compatible environment.  See if it's identical.
                if (CheckEnvironmentVersionIsIdentical(pCandidate->GetVersionInfo(), pWantEnvironment->GetVersionInfo()))
                {
                    pIdentical = pCandidate;
                    break;
                }
                else if (
                    (pCompatible == NULL) ||
                    (pCompatible->GetVersionInfo()->GetMinorVersion() > pCandidate->GetVersionInfo()->GetMinorVersion()))
                {
                    // just compatible, keep looking
                    pCompatible = pCandidate;
                }
            }
        }
    }

    *ppEnvironmentOut = pCandidate = ((pIdentical != NULL) ? pIdentical : pCompatible);

    if ((pCandidate != NULL) && (pPoolMappingsOut != NULL))
    {
        (void)ComputeEnvironmentPoolMappings(pCandidate, pWantEnvironment, pPoolMappingsOut);
    }

    return (pCandidate != NULL);
}

HRESULT EnvironmentCollection::CreateInstance(
    _In_ const CoreProfile* pProfile,
    _In_ AtomPoolGroup* pAtoms,
    _In_ bool initDefaults,
    _Outptr_ EnvironmentCollection** collection)
{
    *collection = nullptr;

    AutoDeletePtr<EnvironmentCollection> pRtrn = new EnvironmentCollection();
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->Init(pAtoms));

    if (initDefaults)
    {
        RETURN_IF_FAILED(pRtrn->AddDefaultEnvironments(pProfile));
    }

    *collection = pRtrn.Detach();

    return S_OK;
}

HRESULT EnvironmentCollection::Init(_In_ AtomPoolGroup* pAtoms)
{
    RETURN_IF_FAILED(DynamicArray<const IEnvironment*>::CreateInstance(1, &m_pEnvironments));
    m_pAtoms = pAtoms;
    return S_OK;
}

EnvironmentCollection::~EnvironmentCollection()
{
    if (m_pEnvironments != nullptr)
    {
        for (int i = 0; i < m_pEnvironments->Count(); i++)
        {
            const IEnvironment* pEnvironment;
            if (SUCCEEDED(m_pEnvironments->Get(i, &pEnvironment)) && (pEnvironment != nullptr))
            {
                delete pEnvironment;
            }
        }
        delete m_pEnvironments;
    }
}

const IEnvironment* EnvironmentCollection::GetDefaultEnvironment() const
{
    const IEnvironment* env;
    (void)GetEnvironment(0, &env);
    return env;
}

HRESULT EnvironmentCollection::AddDefaultEnvironments(_Inout_ const CoreProfile* pProfile)
{
    for (int i = 0; i < pProfile->GetNumEnvironments(); i++)
    {
        IEnvironment* pEnvironment;
        RETURN_IF_FAILED(pProfile->CreateEnvironment(i, m_pAtoms, &pEnvironment));

        RETURN_IF_FAILED(m_pEnvironments->Add(pEnvironment));
    }
    return S_OK;
}

HRESULT EnvironmentCollection::GetOrAddEnvironment(_In_ const IEnvironment* pWantEnvironment, bool clone, _Out_ const IEnvironment** env)
{
    *env = nullptr;

    // clone/upgrade not supported yet
    RETURN_HR_IF(E_NOTIMPL, clone);

    for (int i = 0; i < m_pEnvironments->Count(); i++)
    {
        const IEnvironment* pHaveEnvironment;
        if (SUCCEEDED(m_pEnvironments->Get(i, &pHaveEnvironment)) &&
            CheckEnvironmentVersionIsCompatible(pHaveEnvironment, pWantEnvironment->GetVersionInfo()))
        {
            *env = pHaveEnvironment;

            return S_OK;
        }
    }

    RETURN_IF_FAILED(m_pEnvironments->Add(pWantEnvironment));
    *env = pWantEnvironment;

    return S_OK;
}

} // namespace Microsoft::Resources
