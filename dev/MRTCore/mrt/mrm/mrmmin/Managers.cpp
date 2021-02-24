// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"

using namespace Microsoft::Resources::Build;

namespace Microsoft::Resources
{

class UnifiedEnvironment::PerQualifierPoolInfo : public DefObject
{
public:
    static HRESULT CreateInstance(_In_ const IEnvironment* pEnvironment, _In_ CoreProfile* pProfile, _Outptr_ PerQualifierPoolInfo** result)
    {
        *result = nullptr;

        RETURN_HR_IF_NULL(E_INVALIDARG, pEnvironment);

        AutoDeletePtr<PerQualifierPoolInfo> pRtrn = new PerQualifierPoolInfo();
        RETURN_IF_NULL_ALLOC(pRtrn);
        RETURN_IF_FAILED(pRtrn->Init(pEnvironment, pProfile));

        *result = pRtrn.Detach();

        return S_OK;
    }

    ~PerQualifierPoolInfo()
    {
        // we own the qualifier types, so delete them
        if (m_pQualifierTypes != nullptr)
        {
            for (int i = 0; i < m_pQualifierTypes->Count(); i++)
            {
                IQualifierType* pQualifierType;
                if (SUCCEEDED(m_pQualifierTypes->Get(i, (IBuildQualifierType**)&pQualifierType)))
                {
                    delete pQualifierType;
                    m_pQualifierTypes->Set(i, nullptr);
                }
            }
            delete m_pQualifierTypes;
            m_pQualifierTypes = nullptr;
        }
    }

    const IEnvironment* GetEnvironment() const { return m_pEnvironment; }
    Atom::PoolIndex GetPoolIndex() const { return m_pPool->GetPoolIndex(); }

    HRESULT GetTypeOfQualifier(_In_ Atom qualifierNameAtom, _Out_ const IBuildQualifierType** result) const
    {
        *result = nullptr;
        if ((qualifierNameAtom.GetPoolIndex() != m_pPool->GetPoolIndex()) || (qualifierNameAtom.GetIndex() >= m_pPool->GetNumAtoms()))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER);
        }

        IBuildQualifierType* pType;
        if (FAILED(m_pQualifierTypes->Get(qualifierNameAtom.GetIndex(), &pType)) || (pType == nullptr))
        {
            RETURN_IF_FAILED(m_pProfile->GetTypeForQualifier(m_pEnvironment, qualifierNameAtom, &pType));
            RETURN_IF_FAILED(m_pQualifierTypes->Set(qualifierNameAtom.GetIndex(), pType));
        }

        *result = pType;

        return S_OK;
    }

    HRESULT GetTypeOfQualifier(_In_ PCWSTR pQualifier, _Out_ const IBuildQualifierType** result) const
    {
        *result = nullptr;

        Atom atom;
        if (!m_pPool->TryGetAtom(pQualifier, &atom))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER);
        }
        return GetTypeOfQualifier(atom, result);
    }

protected:
    const IEnvironment* m_pEnvironment;
    const IAtomPool* m_pPool;
    CoreProfile* m_pProfile;

    mutable DynamicArray<IBuildQualifierType*>* m_pQualifierTypes;

    PerQualifierPoolInfo() : m_pEnvironment(nullptr), m_pProfile(nullptr), m_pPool(nullptr), m_pQualifierTypes(nullptr) {}

    HRESULT Init(_In_ const IEnvironment* pEnvironment, _In_ CoreProfile* pProfile)
    {
        m_pEnvironment = pEnvironment;
        m_pProfile = pProfile;
        m_pPool = pEnvironment->GetQualifierNames();

        RETURN_IF_FAILED(DynamicArray<IBuildQualifierType*>::CreateInstance(m_pPool->GetNumAtoms(), &m_pQualifierTypes));
        RETURN_IF_FAILED(m_pQualifierTypes->SetExtent(m_pPool->GetNumAtoms()));

        return S_OK;
    }
};

class UnifiedEnvironment::CompatibleEnvironmentInfo : public DefObject
{
public:
    static HRESULT CreateInstance(
        _In_ PCWSTR compatibleEnvironmentName,
        _In_ const EnvironmentVersionInfo* compatibleEnvironmentVersion,
        _In_ Atom::PoolIndex unifiedQualifierNamesPoolIndex,
        _In_ Atom::PoolIndex compatibleQualifierNamesPoolIndex,
        _In_ int numQualifiers,
        _In_reads_opt_(numQualifiers) const Atom::SmallIndex* qualifierMappings,
        _Outptr_ CompatibleEnvironmentInfo** result)
    {
        *result = nullptr;

        AutoDeletePtr<RemapAtomPool> qualifierRemap;
        if (qualifierMappings != nullptr)
        {
            RETURN_IF_FAILED(RemapAtomPool::CreateInstance(
                compatibleQualifierNamesPoolIndex, unifiedQualifierNamesPoolIndex, numQualifiers, qualifierMappings, &qualifierRemap));
        }

        AutoDeletePtr<CompatibleEnvironmentInfo> rtrn = new CompatibleEnvironmentInfo();
        RETURN_IF_NULL_ALLOC(rtrn);
        RETURN_IF_FAILED(rtrn->Init(compatibleEnvironmentName, compatibleEnvironmentVersion, qualifierRemap));

        *result = rtrn.Detach();
        qualifierRemap.Detach();

        return S_OK;
    }

    virtual ~CompatibleEnvironmentInfo()
    {
        delete m_compatibleEnvironmentVersion;
        delete m_qualifierMapping;
    }

    PCWSTR GetEnvironmentName() const { return m_compatibleEnvironmentName.GetRef(); }
    const EnvironmentVersionInfo* GetEnvironmentVersion() const { return m_compatibleEnvironmentVersion; }
    const RemapAtomPool* GetQualifierMapping() const { return m_qualifierMapping; }

private:
    StringResult m_compatibleEnvironmentName;
    EnvironmentVersionInfo* m_compatibleEnvironmentVersion;
    RemapAtomPool* m_qualifierMapping;

    CompatibleEnvironmentInfo() : m_compatibleEnvironmentVersion(nullptr), m_qualifierMapping(nullptr) {}

    HRESULT Init(
        _In_ PCWSTR compatibleEnvironmentName,
        _In_ const EnvironmentVersionInfo* compatibleEnvironmentVersion,
        _In_opt_ RemapAtomPool* qualifierRemap)
    {
        RETURN_IF_FAILED(m_compatibleEnvironmentName.SetCopy(compatibleEnvironmentName));
        RETURN_IF_FAILED(EnvironmentVersionInfo::CreateInstance(compatibleEnvironmentVersion, &m_compatibleEnvironmentVersion));

        m_qualifierMapping = qualifierRemap;
        return S_OK;
    }
};

HRESULT UnifiedEnvironment::CreateInstance(_In_ CoreProfile* pProfile, _In_ AtomPoolGroup* pAtoms, _Outptr_ UnifiedEnvironment** result)
{
    *result = nullptr;

    RETURN_HR_IF_NULL(E_INVALIDARG, pAtoms);

    AutoDeletePtr<UnifiedEnvironment> pRtrn = new UnifiedEnvironment();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pProfile, pAtoms));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT UnifiedEnvironment::Init(_In_ CoreProfile* pProfile, _In_ AtomPoolGroup* pAtoms)
{
    m_pProfile = pProfile;
    m_pAtoms = pAtoms;

    RETURN_IF_FAILED(pProfile->CreateEnvironment(0, m_pAtoms, &m_pDefaultEnvironment));
    RETURN_IF_FAILED(PerQualifierPoolInfo::CreateInstance(m_pDefaultEnvironment, m_pProfile, &m_pQualifierPool));

    return S_OK;
}

UnifiedEnvironment::~UnifiedEnvironment()
{
    delete m_pDefaultEnvironment;
    delete m_pQualifierPool;

    if (m_compatibleEnvironments != nullptr)
    {
        for (int i = 0; i < m_compatibleEnvironments->Count(); i++)
        {
            CompatibleEnvironmentInfo* pEnvironment;
            if (m_compatibleEnvironments->TryGet(i, &pEnvironment) && (pEnvironment != nullptr))
            {
                m_compatibleEnvironments->Set(i, nullptr);
                delete pEnvironment;
            }
        }
        delete m_compatibleEnvironments;
    }
}

int UnifiedEnvironment::GetNumEnvironments() const { return 1; }

HRESULT UnifiedEnvironment::GetEnvironment(_In_ int index, _Out_ const IEnvironment** result) const
{
    if (index == 0)
    {
        *result = m_pDefaultEnvironment;
        return S_OK;
    }

    *result = nullptr;
    return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
}

HRESULT UnifiedEnvironment::AddEnvironment(_In_ const IEnvironment* pEnvironment, _Inout_opt_ RemapUInt16* pPoolMappingsOut)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pEnvironment);

    RETURN_HR_IF(
        E_MRM_UNSUPPORTED_ENVIRONMENT, !CheckEnvironmentVersionIsCompatible(m_pDefaultEnvironment, pEnvironment->GetVersionInfo()));

    RETURN_IF_FAILED(ComputeEnvironmentPoolMappings(m_pDefaultEnvironment, pEnvironment, pPoolMappingsOut));

    return S_OK;
}

bool UnifiedEnvironment::EnvironmentIsCompatible(
    _In_ PCWSTR wantName,
    _In_ const EnvironmentVersionInfo* wantVersion,
    _Outptr_opt_result_maybenull_ const RemapAtomPool** qualifierMappingOut) const
{
    bool compatible = true;
    const RemapAtomPool* mapping = nullptr;

    compatible = EnvironmentReference::CheckIsCompatible(wantName, wantVersion, m_pDefaultEnvironment);
    if ((!compatible) && (m_compatibleEnvironments != nullptr))
    {
        for (int i = 0; (i < m_compatibleEnvironments->Count()) && (!compatible); i++)
        {
            CompatibleEnvironmentInfo* pCompatibleEnvironment;
            if (m_compatibleEnvironments->TryGet(i, &pCompatibleEnvironment))
            {
                if (EnvironmentReference::CheckIsIdentical(
                        wantName,
                        wantVersion,
                        pCompatibleEnvironment->GetEnvironmentName(),
                        pCompatibleEnvironment->GetEnvironmentVersion()))
                {
                    mapping = pCompatibleEnvironment->GetQualifierMapping();
                    compatible = true;
                }
            }
        }
    }

    if (qualifierMappingOut != nullptr)
    {
        *qualifierMappingOut = mapping;
    }

    return compatible;
}

HRESULT UnifiedEnvironment::AddCompatibleEnvironment(
    _In_ PCWSTR wantName,
    _In_ const EnvironmentVersionInfo* wantVersion,
    _In_ int numQualifiers,
    _In_reads_(numQualifiers) const PCWSTR* qualifierNames,
    _In_reads_opt_(numQualifiers) const Atom::SmallIndex* qualifierMappings,
    _Outptr_opt_result_maybenull_ const RemapAtomPool** qualifierRemap)
{
    if (qualifierRemap != nullptr)
    {
        *qualifierRemap = nullptr;
    }

    if (EnvironmentIsCompatible(wantName, wantVersion, nullptr))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_ENTRY);
    }

    AutoDeletePtr<StaticAtomPool> compatibleNames;
    RETURN_IF_FAILED(StaticAtomPool::CreateInstance(
        qualifierNames, numQualifiers, nullptr, Microsoft::Resources::StaticAtomPool::DefaultFlags, &compatibleNames));
    RETURN_IF_FAILED(m_pAtoms->AddAtomPool(compatibleNames, true));

    AutoDeletePtr<CompatibleEnvironmentInfo> info;
    RETURN_IF_FAILED(CompatibleEnvironmentInfo::CreateInstance(
        wantName,
        wantVersion,
        m_pDefaultEnvironment->GetQualifierNames()->GetPoolIndex(),
        compatibleNames.Detach()->GetPoolIndex(),
        numQualifiers,
        qualifierMappings,
        &info));

    if (m_compatibleEnvironments == nullptr)
    {
        RETURN_IF_FAILED(DynamicArray<CompatibleEnvironmentInfo*>::CreateInstance(2, &m_compatibleEnvironments));
    }

    RETURN_IF_FAILED(m_compatibleEnvironments->Add(info, nullptr));

    if (qualifierRemap != nullptr)
    {
        *qualifierRemap = info->GetQualifierMapping();
    }

    info.Detach();

    return S_OK;
}

HRESULT UnifiedEnvironment::GetTypeOfQualifier(
    _In_ PCWSTR pQualifierName,
    _Out_ Atom* pTypeAtomOut,
    _Out_opt_ const IEnvironment** ppEnvironmentOut) const
{
    ResourceQualifier qualifier = {};

    RETURN_IF_FAILED(m_pDefaultEnvironment->GetQualifier(pQualifierName, &qualifier));

    *pTypeAtomOut = qualifier.qualifierType;
    if (ppEnvironmentOut != nullptr)
    {
        *ppEnvironmentOut = m_pDefaultEnvironment;
    }

    return S_OK;
}

HRESULT UnifiedEnvironment::GetQualifierNameAtom(
    _In_ PCWSTR pQualifierName,
    _Out_ Atom* pNameAtomOut,
    _Out_opt_ const IEnvironment** ppEnvironmentOut) const
{
    ResourceQualifier qualifier = {};

    RETURN_IF_FAILED(m_pDefaultEnvironment->GetQualifier(pQualifierName, &qualifier));

    *pNameAtomOut = qualifier.name;
    if (ppEnvironmentOut != nullptr)
    {
        *ppEnvironmentOut = m_pDefaultEnvironment;
    }

    return S_OK;
}

HRESULT UnifiedEnvironment::GetQualifierNameFromAtom(_In_opt_ Atom nameAtom, _Inout_ StringResult* pNameOut) const
{
    if (!m_pDefaultEnvironment->GetQualifierNames()->TryGetString(nameAtom, pNameOut))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_FILE_TYPE);
    }

    return S_OK;
}

HRESULT UnifiedEnvironment::GetResourceQualifier(_In_ PCWSTR pQualifierName, _Out_ ResourceQualifier* pQualifierOut) const
{
    return m_pDefaultEnvironment->GetQualifier(pQualifierName, pQualifierOut);
}

HRESULT UnifiedEnvironment::GetResourceQualifier(_In_ Atom name, _Out_ ResourceQualifier* pQualifierOut) const
{
    return m_pDefaultEnvironment->GetQualifier(name, pQualifierOut);
}

HRESULT UnifiedEnvironment::GetResourceValueTypeAtom(
    _In_ MrmEnvironment::ResourceValueType valueType,
    _Out_ Atom* pNameAtomOut,
    _Out_opt_ const IEnvironment** ppEnvironmentOut) const
{
    // construct an atom
    Atom typeAtom(static_cast<Atom::Index>(valueType), m_pDefaultEnvironment->GetResourceValueTypeNames()->GetPoolIndex());

    // make sure it's valid
    if (!m_pDefaultEnvironment->GetResourceValueTypeNames()->Contains(typeAtom))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_RESOURCE_TYPE_MISMATCH);
    }

    *pNameAtomOut = typeAtom;

    if (ppEnvironmentOut != nullptr)
    {
        *ppEnvironmentOut = m_pDefaultEnvironment;
    }

    return S_OK;
}

HRESULT UnifiedEnvironment::GetResourceValueLocatorAtom(
    _In_ PCWSTR pLocatorName,
    _Out_ Atom* pNameAtomOut,
    _Out_opt_ const IEnvironment** ppEnvironmentOut) const
{
    if (m_pDefaultEnvironment->GetResourceValueLocatorNames()->TryGetAtom(pLocatorName, pNameAtomOut))
    {
        if (ppEnvironmentOut != nullptr)
        {
            *ppEnvironmentOut = m_pDefaultEnvironment;
        }
        return S_OK;
    }

    return E_MRM_BAD_NAME;
}

HRESULT UnifiedEnvironment::GetTypeOfQualifier(_In_ PCWSTR pQualifierName, _Outptr_ const IBuildQualifierType** ppTypeOut) const
{
    Atom name;
    if (!m_pDefaultEnvironment->GetQualifierNames()->TryGetAtom(pQualifierName, &name))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER);
    }

    RETURN_IF_FAILED(m_pQualifierPool->GetTypeOfQualifier(name, ppTypeOut));
    return S_OK;
}

HRESULT UnifiedEnvironment::GetTypeOfQualifier(_In_ Atom name, _Outptr_ const IBuildQualifierType** ppTypeOut) const
{
    return m_pQualifierPool->GetTypeOfQualifier(name, ppTypeOut);
}

HRESULT UnifiedEnvironment::ValidateQualifierValue(_In_ PCWSTR pQualifierName, _In_ PCWSTR pQualifierValue) const
{
    Atom name;
    if (!m_pDefaultEnvironment->GetQualifierNames()->TryGetAtom(pQualifierName, &name))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER);
    }

    const IQualifierType* pType;
    RETURN_IF_FAILED(m_pQualifierPool->GetTypeOfQualifier(name, (const IBuildQualifierType**)&pType));

    RETURN_IF_FAILED_EXPECTED(pType->ValidateQualifierValue(pQualifierValue));

    return S_OK;
}

HRESULT UnifiedEnvironment::ValidateQualifierValue(_In_ Atom qualifierName, _In_ PCWSTR pQualifierValue) const
{
    const IQualifierType* pType;
    RETURN_IF_FAILED(m_pQualifierPool->GetTypeOfQualifier(qualifierName, (const IBuildQualifierType**)&pType));

    RETURN_IF_FAILED_EXPECTED(pType->ValidateQualifierValue(pQualifierValue));

    return S_OK;
}

HRESULT UnifiedEnvironment::ValidateOrMakeCompatibleQualifierValue(
    _In_ PCWSTR qualifierName,
    _In_ PCWSTR qualifierValue,
    _Inout_ StringResult* compatibleValue) const
{
    const IQualifierType* qualifierType;
    RETURN_IF_FAILED(m_pQualifierPool->GetTypeOfQualifier(qualifierName, (const IBuildQualifierType**)&qualifierType));

    RETURN_IF_FAILED_EXPECTED(qualifierType->ValidateOrMakeCompatibleQualifierValue(qualifierValue, compatibleValue));

    return S_OK;
}

HRESULT UnifiedEnvironment::ValidateQualifierComparison(
    _In_ PCWSTR pQualifierName,
    _In_ ICondition::ConditionOperator op,
    _In_ PCWSTR pQualifierValue) const
{
    Atom name;
    if (!m_pDefaultEnvironment->GetQualifierNames()->TryGetAtom(pQualifierName, &name))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER);
    }

    RETURN_IF_FAILED_EXPECTED(ValidateQualifierComparison(name, op, pQualifierValue));

    return S_OK;
}

HRESULT UnifiedEnvironment::ValidateQualifierComparison(
    _In_ Atom qualifierName,
    _In_ ICondition::ConditionOperator op,
    _In_ PCWSTR pQualifierValue) const
{
    const IQualifierType* pType;
    RETURN_IF_FAILED(m_pQualifierPool->GetTypeOfQualifier(qualifierName, (const IBuildQualifierType**)&pType));

    RETURN_IF_FAILED_EXPECTED(pType->ValidateQualifierComparison(qualifierName, op, pQualifierValue));

    return S_OK;
}

HRESULT UnifiedEnvironment::GetAtom(_In_ EnvironmentNamesType which, _In_ PCWSTR pName, _Inout_opt_ Atom* pAtomOut) const
{
    const IAtomPool* pPool = nullptr;

    if (pAtomOut != nullptr)
    {
        *pAtomOut = Atom::NullAtom;
    }

    RETURN_HR_IF(E_INVALIDARG, (pName == nullptr) || (*pName == 0));

    switch (which)
    {
    case QualifierNames:
        pPool = GetDefaultEnvironment()->GetQualifierNames();
        break;
    case QualifierTypeNames:
        pPool = GetDefaultEnvironment()->GetQualifierTypeNames();
        break;
    case ResourceValueTypeNames:
        pPool = GetDefaultEnvironment()->GetResourceValueTypeNames();
        break;
    case ResourceValueLocatorNames:
        pPool = GetDefaultEnvironment()->GetResourceValueLocatorNames();
        break;
    default:
        return E_INVALIDARG;
    }

    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), pPool);

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), !pPool->TryGetAtom(pName, pAtomOut));

    return S_OK;
}

HRESULT UnifiedEnvironment::GetName(_In_ EnvironmentNamesType which, _In_ Atom atom, _Inout_opt_ StringResult* pStringOut) const
{
    const IAtomPool* pPool = nullptr;

    if (pStringOut != nullptr)
    {
        RETURN_IF_FAILED(pStringOut->SetRef(nullptr));
    }

    switch (which)
    {
    case QualifierNames:
        pPool = GetDefaultEnvironment()->GetQualifierNames();
        break;
    case QualifierTypeNames:
        pPool = GetDefaultEnvironment()->GetQualifierTypeNames();
        break;
    case ResourceValueTypeNames:
        pPool = GetDefaultEnvironment()->GetResourceValueTypeNames();
        break;
    case ResourceValueLocatorNames:
        pPool = GetDefaultEnvironment()->GetResourceValueLocatorNames();
        break;
    default:
        return E_INVALIDARG;
    }

    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), pPool);

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), !pPool->TryGetString(atom, pStringOut));

    return S_OK;
}

HRESULT UnifiedEnvironment::GetAllAtoms(_In_ EnvironmentNamesType which, _Outptr_ DynamicArray<Atom>** result) const
{
    *result = nullptr;

    const IAtomPool* pPool = nullptr;

    switch (which)
    {
    case QualifierNames:
        pPool = GetDefaultEnvironment()->GetQualifierNames();
        break;
    case QualifierTypeNames:
        pPool = GetDefaultEnvironment()->GetQualifierTypeNames();
        break;
    case ResourceValueTypeNames:
        pPool = GetDefaultEnvironment()->GetResourceValueTypeNames();
        break;
    case ResourceValueLocatorNames:
        pPool = GetDefaultEnvironment()->GetResourceValueLocatorNames();
        break;
    default:
        return E_INVALIDARG;
    }

    DEF_ASSERT(pPool != nullptr);

    AutoDeletePtr<DynamicArray<Atom>> pRtrn;
    RETURN_IF_FAILED(DynamicArray<Atom>::CreateInstance(pPool->GetNumAtoms(), &pRtrn));
    ;

    Atom atom;
    for (int i = 0; i < pPool->GetNumAtoms(); i++)
    {
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), !pPool->TryGetAtom(i, &atom));
        RETURN_IF_FAILED(pRtrn->Add(atom));
    }

    *result = pRtrn.Detach();

    return S_OK;
}

HRESULT UnifiedDecisionInfo::CreateInstance(
    _In_ const UnifiedEnvironment* pEnvironment,
    _In_opt_ const IDecisionInfo* pInitialDecisions,
    _Outptr_ UnifiedDecisionInfo** result)
{
    return CreateInstance(pEnvironment, nullptr, pInitialDecisions, result);
}

HRESULT UnifiedDecisionInfo::CreateInstance(
    _In_ const UnifiedEnvironment* pEnvironment,
    _In_opt_ const ManagedFile* pInitialFile,
    _In_opt_ const IDecisionInfo* pInitialDecisions,
    _Outptr_ UnifiedDecisionInfo** result)
{
    *result = nullptr;

    RETURN_HR_IF_NULL(E_INVALIDARG, pEnvironment);

    AutoDeletePtr<UnifiedDecisionInfo> pRtrn = new UnifiedDecisionInfo();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pEnvironment, pInitialFile, pInitialDecisions));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT UnifiedDecisionInfo::Init(
    _In_ const UnifiedEnvironment* pEnvironment,
    _In_opt_ const ManagedFile* pBaseFile,
    _In_opt_ const IDecisionInfo* pBase)
{
    m_pEnvironment = pEnvironment;
    m_pDecisionInfo = pBase;
    m_pBase = pBase;
    m_pBaseFile = pBaseFile;

    if (m_pDecisionInfo == nullptr)
    {
        RETURN_IF_FAILED(
            DecisionInfoBuilder::CreateInstance(DecisionInfoBuilder::AllowUnknownQualifiersFlag, m_pEnvironment, m_pBase, &m_pBuilder));
        m_pDecisionInfo = m_pBuilder;
        m_pBase = nullptr;
        m_pBaseFile = nullptr;
    }

    return S_OK;
}

UnifiedDecisionInfo::~UnifiedDecisionInfo()
{
    delete m_pBuilder;

    m_pDecisionInfo = nullptr;
    m_pBase = nullptr;
    m_pBaseFile = nullptr;
    m_pBuilder = nullptr;
}

HRESULT UnifiedDecisionInfo::Merge(
    _In_ const IDecisionInfo* pMerge,
    _Inout_opt_ RemapUInt16* pQualifierMap,
    _Inout_opt_ RemapUInt16* pQualifierSetMap,
    _Inout_opt_ RemapUInt16* pDecisionMap)
{
    if (m_pBuilder == nullptr)
    {
        RETURN_IF_FAILED(
            DecisionInfoBuilder::CreateInstance(DecisionInfoBuilder::AllowUnknownQualifiersFlag, m_pEnvironment, m_pBase, &m_pBuilder));

        m_pDecisionInfo = m_pBuilder;
        m_pBase = nullptr;
        m_pBaseFile = nullptr;
    }

    return m_pBuilder->Merge(pMerge, pQualifierMap, pQualifierSetMap, pDecisionMap);
}

HRESULT UnifiedDecisionInfo::Merge(
    _In_opt_ const ManagedFile* pFile,
    _In_ const IDecisionInfo* pMerge,
    _Inout_opt_ RemapUInt16* pQualifierMap,
    _Inout_opt_ RemapUInt16* pQualifierSetMap,
    _Inout_opt_ RemapUInt16* pDecisionMap)
{
    if ((m_pBase == nullptr) && (m_pBuilder == nullptr))
    {
        m_pBaseFile = pFile;
        m_pBase = pMerge;
        m_pDecisionInfo = pMerge;
        return S_OK;
    }
    return UnifiedDecisionInfo::Merge(pMerge, pQualifierMap, pQualifierSetMap, pDecisionMap);
}

HRESULT UnifiedDecisionInfo::NoteFileUnloading(_In_ const ManagedFile* pFile, _Out_ bool* pbCancelUnloadOut)
{
    *pbCancelUnloadOut = true;
    if (pFile == m_pBaseFile)
    {
        if ((m_pBuilder == nullptr) && (m_pBase != nullptr))
        {
            RETURN_IF_FAILED(
                DecisionInfoBuilder::CreateInstance(DecisionInfoBuilder::AllowUnknownQualifiersFlag, m_pEnvironment, m_pBase, &m_pBuilder));

            m_pDecisionInfo = m_pBuilder;
        }

        m_pBase = nullptr;
        m_pBaseFile = nullptr;
    }

    *pbCancelUnloadOut = false;
    return S_OK;
}

HRESULT ManagedSchema::CreateInstance(
    _In_ const ManagedFile* pInitialFile,
    _In_ const IHierarchicalSchema* pInitialSchema,
    _Outptr_ ManagedSchema** result)
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, (pInitialFile == nullptr) || (pInitialSchema == nullptr));

    ManagedSchema* pRtrn = new ManagedSchema(pInitialFile, pInitialSchema);
    RETURN_IF_NULL_ALLOC(pRtrn);

    *result = pRtrn;

    return S_OK;
}

ManagedSchema::ManagedSchema(_In_ const ManagedFile* pInitialFile, _In_ const IHierarchicalSchema* pInitialSchema) :
    m_pCurrentSchema(pInitialSchema),
    m_pCurrentFile(pInitialFile),
    m_generation(1),
    m_pFileManager(pInitialFile->GetFileManager()),
    m_pFiles(nullptr),
    m_pMySchema(nullptr)
{
    // lazy create m_pFiles
}

ManagedSchema::~ManagedSchema()
{
    delete m_pFiles;
    delete m_pMySchema;

    m_pFiles = nullptr;
    m_pMySchema = nullptr;
}

HRESULT ManagedSchema::NoteFileAdded(_In_ const ManagedFile* pNewFile, _In_ const IHierarchicalSchema* pNewSchema)
{
    // See if we already have it
    if (pNewFile == m_pCurrentFile)
    {
        DEF_ASSERT(pNewSchema == m_pCurrentSchema);
        return S_OK;
    }
    else if (m_pFiles != nullptr)
    {
        SchemaPerFileInfo finfo;
        for (unsigned i = 0; i < m_pFiles->Count(); i++)
        {
            if (m_pFiles->TryGet(i, &finfo) && (finfo.pFile == pNewFile))
            {
                if (finfo.pSchema == nullptr)
                {
                    finfo.pSchema = pNewSchema;
                    RETURN_IF_FAILED(m_pFiles->Set(i, finfo));
                }

                DEF_ASSERT(pNewSchema == finfo.pSchema);
                // already have it
                return S_OK;
            }
        }
    }

    // Nope.  If it's compatible, we'll have to add it.
    // true if the new schema is a later version than we currently have
    bool upgrade = false;

    const IHierarchicalSchemaVersionInfo* pCurrentSchemaVersion = m_pCurrentSchema->GetVersionInfo();
    const IHierarchicalSchemaVersionInfo* pNewSchemaVersion = pNewSchema->GetVersionInfo();
    DEF_ASSERT(pCurrentSchemaVersion != nullptr);
    DEF_ASSERT(pNewSchemaVersion != nullptr);
    _Analysis_assume_(pCurrentSchemaVersion != nullptr);
    _Analysis_assume_(pNewSchemaVersion != nullptr);

    if (CheckHierarchicalSchemaVersionIsCompatible(pNewSchema, pCurrentSchemaVersion))
    {
        // The new schema is either identical or later
        upgrade = !CheckHierarchicalSchemaVersionIsIdentical(pNewSchema->GetVersionInfo(), pCurrentSchemaVersion);
    }
    else if (!CheckHierarchicalSchemaVersionIsCompatible(m_pCurrentSchema, pNewSchemaVersion))
    {
        // not compatible at all
        return HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND);
    }

    if (m_pFiles == nullptr)
    {
        // Lazy create m_pFiles
        RETURN_IF_FAILED(DynamicArray<SchemaPerFileInfo>::CreateInstance(4, &m_pFiles));

        // Don't forget to add the original file to the list
        if (m_pCurrentFile != nullptr)
        {
            SchemaPerFileInfo current;
            current.pFile = m_pCurrentFile;
            current.pSchema = m_pCurrentSchema;
            RETURN_IF_FAILED(m_pFiles->Add(current));
        }
    }

    SchemaPerFileInfo newEntry;
    newEntry.pFile = pNewFile;
    newEntry.pSchema = pNewSchema;
    RETURN_IF_FAILED(m_pFiles->Add(newEntry));

    if (upgrade)
    {
        m_pCurrentSchema = pNewSchema;
        m_pCurrentFile = pNewFile;
        m_generation++;

        // in case we owned the previous schema
        delete m_pMySchema;
        m_pMySchema = nullptr;
    }
    return S_OK;
}

HRESULT ManagedSchema::NoteFileUnloading(_In_ const ManagedFile* pFile, _Out_ bool* pbCancelUnloadOut)
{
    *pbCancelUnloadOut = true;

    if (m_pFiles != nullptr)
    {
        SchemaPerFileInfo finfo;

        // If we're holding onto a schema for this file, let it go.
        for (int i = 0; i < m_pFiles->Count(); i++)
        {
            if (m_pFiles->TryGet(i, &finfo))
            {
                if (finfo.pFile == pFile)
                {
                    finfo.pSchema = nullptr;
                    RETURN_IF_FAILED(m_pFiles->Set(i, finfo));
                    break;
                }
            }
        }
    }

    if (pFile != m_pCurrentFile)
    {
        // Otherwise, if it isn't our current file, we don't care.
        *pbCancelUnloadOut = false;
        return S_OK;
    }

    // Oops. Current file is going away, better find
    // or create a replacement.
    const ManagedFile* pReplacementFile = nullptr;
    const IHierarchicalSchema* pReplacementSchema = nullptr;
    const IHierarchicalSchemaVersionInfo* pCurrentSchemaVersion = m_pCurrentSchema->GetVersionInfo();

    DEF_ASSERT(pCurrentSchemaVersion != nullptr);
    _Analysis_assume_(pCurrentSchemaVersion != nullptr);

    if (m_pFiles != nullptr)
    {
        SchemaPerFileInfo finfo;
        for (int i = 0; i < m_pFiles->Count(); i++)
        {
            if (m_pFiles->TryGet(i, &finfo) && (finfo.pSchema != nullptr))
            {
                if (CheckHierarchicalSchemaVersionIsIdentical(pCurrentSchemaVersion, finfo.pSchema->GetVersionInfo()))
                {
                    pReplacementFile = finfo.pFile;
                    pReplacementSchema = finfo.pSchema;
                    break;
                }
            }
        }
    }

    // Hmm.  No replacement in any of the loaded files.  We'd better make a copy.
    if (pReplacementFile == nullptr)
    {
        RETURN_IF_FAILED(m_pCurrentSchema->Clone(&m_pMySchema));

        pReplacementSchema = m_pMySchema;
    }

    if (pReplacementSchema == nullptr)
    {
        return E_ABORT;
    }

    *pbCancelUnloadOut = false;

    m_pCurrentSchema = pReplacementSchema;
    m_pCurrentFile = pReplacementFile;

    // increase generation so any callers know to reacquire stored pointers
    m_generation++;
    return S_OK;
}

HRESULT ManagedSchema::NoteFileRemoving(_In_ const ManagedFile* pFile, _Out_ bool* pbCancelRemovalOut)
{
    RETURN_IF_FAILED(NoteFileUnloading(pFile, pbCancelRemovalOut));

    if (m_pFiles != nullptr)
    {
        SchemaPerFileInfo finfo;
        for (int i = 0; i < m_pFiles->Count(); i++)
        {
            if (m_pFiles->TryGet(i, &finfo) && (finfo.pFile == pFile))
            {
                RETURN_IF_FAILED(m_pFiles->Delete(i));
                return S_OK;
            }
        }
    }

    return S_OK;
}

int ManagedSchema::GetNumVersionInfos() const { return m_pCurrentSchema->GetNumVersionInfos(); }

const IHierarchicalSchemaVersionInfo* ManagedSchema::GetVersionInfo(_In_ int index) const
{
    return m_pCurrentSchema->GetVersionInfo(index);
}

HRESULT ManagedSchema::Clone(_Outptr_ IHierarchicalSchema**) const { return E_NOTIMPL; }

HRESULT ManagedSchema::GetSchemaBlobFromFileSection(
    _Inout_opt_ DEFFILE_SECTION_TYPEID* /*pSectionTypeResult*/,
    _Inout_opt_ BlobResult* /*pBlobResult*/) const
{
    return E_NOTIMPL;
}

HRESULT ManagedResourceMap::CreateInstance(
    _In_ const ManagedFile* pInitialFile,
    _In_ const IResourceMapBase* pInitialMap,
    _In_ const ManagedSchema* pSchema,
    _In_ UnifiedDecisionInfo* pDecisions,
    _In_ UnifiedResourceView* pUnifiedResourceView,
    _Outptr_ ManagedResourceMap** result)
{
    *result = nullptr;

    RETURN_HR_IF_NULL(E_INVALIDARG, pInitialFile);
    RETURN_HR_IF_NULL(E_INVALIDARG, pInitialMap);
    RETURN_HR_IF_NULL(E_INVALIDARG, pSchema);
    RETURN_HR_IF_NULL(E_INVALIDARG, pDecisions);
    RETURN_HR_IF_NULL(E_INVALIDARG, pUnifiedResourceView);

    AutoDeletePtr<ManagedResourceMap> pRtrn = new ManagedResourceMap();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pInitialFile, pInitialMap, pSchema, pDecisions, pUnifiedResourceView));
    RETURN_IF_FAILED(pRtrn->InitResourceMapSubtree(pRtrn, 0));

    *result = pRtrn.Detach();

    return S_OK;
}

HRESULT ManagedResourceMap::Init(
    _In_ const ManagedFile* pInitialFile,
    _In_ const IResourceMapBase* pInitialMap,
    _In_ const ManagedSchema* pSchema,
    _In_ UnifiedDecisionInfo* pDecisions,
    _In_ UnifiedResourceView* pUnifiedResourceView)
{
    m_pCurrentMap = pInitialMap;
    m_pCurrentFile = pInitialFile;
    m_pSchema = pSchema;
    m_pDecisions = pDecisions;
    m_pFileManager = pInitialFile->GetFileManager();

    AutoDeletePtr<RemapUInt16> pDecisionMap;
    RETURN_IF_FAILED(RemapUInt16::CreateInstance(pInitialMap->GetDecisionInfo()->GetNumDecisions(), &pDecisionMap));
    RETURN_IF_FAILED(pDecisions->Merge(pInitialFile, pInitialMap->GetDecisionInfo(), nullptr, nullptr, pDecisionMap));
    RETURN_IF_FAILED(pInitialMap->SetDecisionInfoOverride(pDecisions, pDecisionMap));
    RETURN_IF_FAILED(pInitialMap->SetSchemaOverride(pSchema));

    if (pInitialFile->GetPackageRoot())
    {
        RETURN_IF_FAILED(SetPackageRootPath(pInitialFile->GetPackageRoot()));
    }

    m_pUnifiedResourceView = pUnifiedResourceView;

    return S_OK;
}

ManagedResourceMap::~ManagedResourceMap()
{
    delete m_pFiles;
    m_pFiles = nullptr;
}

HRESULT ManagedResourceMap::UpdateCurrent() const
{
    if (m_pFiles != nullptr)
    {
        MapPerFileInfo* pAllFiles = m_pFiles->GetAll();

        switch (m_pFiles->Count())
        {
        case 0:
            // nothing loaded
            if ((m_pCurrentMap != nullptr) || (m_pCurrentFile != nullptr))
            {
                m_pCurrentMap = nullptr;
                m_pCurrentFile = nullptr;
                m_generation++;
            }
            break;
        case 1:
            // one file, just use it.
            if (m_pCurrentMap != pAllFiles[0].pMap)
            {
                m_pCurrentFile = pAllFiles[0].pFile;
                m_pCurrentMap = pAllFiles[0].pMap;
                m_generation++;
            }
            break;
        default:
            if ((m_pCurrentMap != nullptr) || (m_pCurrentFile != nullptr))
            {
                m_pCurrentMap = nullptr;
                m_pCurrentFile = nullptr;
                m_generation++;
            }

            break;
        }
    }
    return S_OK;
}

const IResourceMapBase* ManagedResourceMap::GetCurrentResourceMap() const
{
    if ((m_pCurrentMap == nullptr) && (FAILED(UpdateCurrent())))
    {
        return nullptr;
    }

    return m_pCurrentMap;
}

HRESULT ManagedResourceMap::NoteFileAdded(_In_ const ManagedFile* pNewFile, _In_opt_ const IResourceMapBase* pNewMap)
{
    bool isNew = true;

    // See if this is already the file in use
    if (pNewFile == m_pCurrentFile)
    {
        DEF_ASSERT(pNewMap == m_pCurrentMap);
        return S_OK;
    }
    else if (m_pFiles != nullptr)
    {
        MapPerFileInfo finfo;
        for (unsigned i = 0; i < m_pFiles->Count(); i++)
        {
            if (m_pFiles->TryGet(i, &finfo) && (finfo.pFile == pNewFile))
            {
                if (finfo.pMap != nullptr)
                {
                    DEF_ASSERT(pNewMap == finfo.pMap);
                    // already loaded, nothing to do.
                    return S_OK;
                }

                // We have the file but it isn't currently
                // loaded.  Add it to the set of loaded files
                // and stop looking.
                isNew = false;
                finfo.loaded = true;
                finfo.pMap = pNewMap;
                RETURN_IF_FAILED(m_pFiles->Set(i, finfo));
                break;
            }
        }
    }

    // If the file is new to us, validate it and add to the list of files
    if (isNew)
    {
        if (!CheckHierarchicalSchemaVersionIsCompatible(m_pSchema, pNewMap->GetSchema()->GetVersionInfo()))
        {
            WRITE_MRMMIN_INIT_TRACE_ERROR(m_pSchema->GetSimpleId(), HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND));
            return HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND);
        }

        // set up schema & decision overrides
        AutoDeletePtr<RemapUInt16> pDecisionMap;
        RETURN_IF_FAILED(RemapUInt16::CreateInstance(pNewMap->GetDecisionInfo()->GetNumDecisions(), &pDecisionMap));
        RETURN_IF_FAILED(m_pDecisions->Merge(pNewFile, pNewMap->GetDecisionInfo(), nullptr, nullptr, pDecisionMap));
        RETURN_IF_FAILED(pNewMap->SetDecisionInfoOverride(m_pDecisions, pDecisionMap));

        RETURN_IF_FAILED(pNewMap->SetSchemaOverride(m_pSchema));

        // Lazy create m_pFiles if needed by calling GetOrCreateFilesList
        RETURN_IF_FAILED(GetOrCreateFilesList());

        _Analysis_assume_(m_pFiles != nullptr);

        MapPerFileInfo finfo;
        finfo.loaded = true;
        finfo.pFile = pNewFile;
        finfo.pMap = pNewMap;
        RETURN_IF_FAILED(m_pFiles->Add(finfo));
    }

    WRITE_MRMMIN_INIT_TRACE_INFO_CHECK(pNewFile->GetPath(), S_OK);

    RETURN_IF_FAILED(UpdateCurrent());

    return S_OK;
}

HRESULT ManagedResourceMap::NoteFileUnloading(_In_ const ManagedFile* pFile, _Out_ bool* pbCancelUnloadOut)
{
    *pbCancelUnloadOut = false;

    // If this is the current file, clear it.
    if (pFile == m_pCurrentFile)
    {
        m_pCurrentFile = nullptr;
        m_pCurrentMap = nullptr;
        m_generation++;
    }

    if (m_pFiles != nullptr)
    {
        bool found = false;
        MapPerFileInfo* pAllFiles = m_pFiles->GetAll();
        for (int i = 0; (i < m_pFiles->Count()) && (!found); i++)
        {
            if (pAllFiles[i].pFile == pFile)
            {
                pAllFiles[i].loaded = false;
                pAllFiles[i].pMap = nullptr;
                found = true;
            }
        }

        if (!found)
        {
            // We don't have the file, nothing to do.
            return S_OK;
        }
    }

    HRESULT hr = UpdateCurrent();
    if (FAILED(hr))
    {
        *pbCancelUnloadOut = true;
        WRITE_MRMMIN_INIT_TRACE_ERROR_CHECK(pFile->GetPath(), hr);
        return hr;
    }

    WRITE_MRMMIN_INIT_TRACE_INFO_CHECK(pFile->GetPath(), S_OK);
    return S_OK;
}

HRESULT ManagedResourceMap::NoteFileRemoving(_In_ const ManagedFile* pFile, _Out_ bool* pbCancelRemovalOut)
{
    RETURN_IF_FAILED(NoteFileUnloading(pFile, pbCancelRemovalOut));

    if (m_pFiles != nullptr)
    {
        bool found = false;
        MapPerFileInfo* pAllFiles = m_pFiles->GetAll();
        for (int i = 0; (i < m_pFiles->Count()) && (!found); i++)
        {
            if (pAllFiles[i].pFile == pFile)
            {
                m_pFiles->Delete(i);
                found = true;
            }
        }
        if (!found)
        {
            // We don't have the file, nothing to do.
            return S_OK;
        }
    }

    // no need to call UpdateCurrent because NoteFileUnloading already did.
    return S_OK;
}

const IHierarchicalSchema* ManagedResourceMap::GetSchema() const { return m_pSchema; }

const IHierarchicalSchema* ManagedResourceMap::GetOriginalSchema() const { return m_pSchema->GetCurrentSchema(); }

const IDecisionInfo* ManagedResourceMap::GetDecisionInfo() const { return m_pDecisions; }

const ResourceMapSubtree* ManagedResourceMap::GetRootSubtree() const
{
    const IResourceMapBase* pMap = GetCurrentResourceMap();
    return ((pMap != nullptr) ? pMap->GetRootSubtree() : nullptr);
}

int ManagedResourceMap::GetNumResources() const { return m_pSchema->GetNumItems(); }

HRESULT ManagedResourceMap::GetResourceByIndex(_In_ int indexInSchema, _Inout_ NamedResourceResult* pItemOut) const
{
    if (this->GetCurrentResourceMap() != nullptr)
    {
        DEF_ASSERT(m_pCurrentMap);
        return m_pCurrentMap->GetResourceByIndex(indexInSchema, pItemOut);
    }

    return pItemOut->Set(m_pSchema, indexInSchema);
}

int ManagedResourceMap::GetTotalNumResourceValues() const
{
    if (this->GetCurrentResourceMap() != nullptr)
    {
        DEF_ASSERT(m_pCurrentMap);
        return m_pCurrentMap->GetTotalNumResourceValues();
    }
    return 0;
}

HRESULT ManagedResourceMap::GetResource(_In_ PCWSTR pPath, _Inout_ NamedResourceResult* pItemOut) const
{
    if (this->GetCurrentResourceMap() != nullptr)
    {
        DEF_ASSERT(m_pCurrentMap);
        return m_pCurrentMap->GetResource(pPath, pItemOut);
    }

    int schemaScopeIndex = -1;
    int schemaItemIndex = -1;

    if (m_pSchema->Contains(pPath, 0, &schemaScopeIndex, &schemaItemIndex))
    {
        if (schemaItemIndex >= 0)
        {
            return pItemOut->Set(m_pSchema, schemaItemIndex);
        }

        return HRESULT_FROM_WIN32(ERROR_BAD_ENVIRONMENT);
    }

    return HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND);
}

HRESULT ManagedResourceMap::SetDecisionInfoOverride(
    _In_ const IDecisionInfo* /*pOverrideDecisions*/,
    _In_ const RemapUInt16* /*pDecisionMap*/) const
{
    return E_NOTIMPL;
}

void ManagedResourceMap::ResetDecisionInfoOverride() const {}

HRESULT ManagedResourceMap::SetSchemaOverride(_In_ const IHierarchicalSchema* /*pOverrideSchema*/) const { return E_NOTIMPL; }

HRESULT ManagedResourceMap::GetOrCreateFilesList() const
{
    if (m_pFiles != nullptr)
    {
        return S_OK;
    }
    else
    {
        // lazy create m_pFiles & add the initial file
        RETURN_IF_FAILED(DynamicArray<MapPerFileInfo>::CreateInstance(4, &m_pFiles));

        if (m_pCurrentFile != nullptr)
        {
            MapPerFileInfo current;
            current.loaded = true;
            current.pFile = m_pCurrentFile;
            current.pMap = m_pCurrentMap;
            RETURN_IF_FAILED(m_pFiles->Add(current));
        }
    }

    return S_OK;
}

HRESULT ManagedResourceMap::GetFiles(
    _Inout_opt_ DynamicArray<const IResourceMapBase*>* pMapsOut,
    _Inout_opt_ DynamicArray<const ManagedFile*>* pFilesOut) const
{
    RETURN_IF_FAILED(GetOrCreateFilesList());

    if (pMapsOut != nullptr)
    {
        pMapsOut->Reset();
        MapPerFileInfo* pAllFiles = m_pFiles->GetAll();
        for (int i = 0; i < m_pFiles->Count(); i++)
        {
            RETURN_IF_FAILED(pMapsOut->Add(pAllFiles[i].pMap));
        }
    }

    if (pFilesOut != nullptr)
    {
        pFilesOut->Reset();
        MapPerFileInfo* pAllFiles = m_pFiles->GetAll();
        for (int i = 0; i < m_pFiles->Count(); i++)
        {
            RETURN_IF_FAILED(pFilesOut->Add(pAllFiles[i].pFile));
        }
    }

    return S_OK;
}

} // namespace Microsoft::Resources
