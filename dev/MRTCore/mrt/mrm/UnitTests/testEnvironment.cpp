// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"
#include <mrm/build/AIDict.h>
#include "Helpers.h"
#include "TestEnvironment.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;
using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTests
{

TestEnvironment::TestEnvironment(PCWSTR pDisplayName, PCWSTR pUniqueName, AtomPoolGroup* pAtoms) :
    m_pAtoms(pAtoms),
    m_pDisplayName(nullptr),
    m_pUniqueName(nullptr),
    m_pQualifierTypeNames(nullptr),
    m_pQualifierNames(nullptr),
    m_pItemTypeNames(nullptr),
    m_pResourceValueTypeNames(nullptr),
    m_pResourceValueLocatorNames(nullptr),
    m_pConditionOperatorNames(nullptr),
    m_pQualifiers(nullptr),
    m_pVersion(nullptr)
{
    m_pDisplayName = _DefDuplicateString(pDisplayName);
    m_pUniqueName = _DefDuplicateString(pUniqueName);
}

TestEnvironment::~TestEnvironment()
{
    Def_Free(m_pDisplayName);
    Def_Free(m_pUniqueName);

    delete m_pQualifierTypeNames;
    delete m_pQualifierNames;
    delete m_pItemTypeNames;
    delete m_pResourceValueTypeNames;
    delete m_pResourceValueLocatorNames;
    delete m_pConditionOperatorNames;
    delete m_pQualifiers;
    delete m_pVersion;
}

HRESULT TestEnvironment::InitQualifiers(PCWSTR pVarPrefix, _In_opt_ TestEnvironment* pCloneFrom)
{
    RETURN_IF_FAILED(AtomIndexedStructDictionary<ResourceQualifier>::CreateInstance(
        m_pQualifierNames->GetPool(), AtomIndexedDictionaryBase::Auto, &m_pQualifiers));

    const IAtomPool* pQualifierNames = m_pQualifierNames->GetPool();
    int numQualifiers = pQualifierNames->GetNumAtoms();

    if (numQualifiers < 1)
    {
        return S_OK;
    }

    String var;

    TestStringArray types;
    TestStringArray runtimePriorities;
    TestStringArray buildPriorities;

    Atom typeAtom;
    ResourceQualifier qualifier;
    ResourceQualifier otherQualifier;
    const IAtomPool* pQualifierTypeNames;

    if (types.TryInitFromTestVars(var.Format(L"%sQualifierTypes", pVarPrefix)))
    {
        if (types.GetNumStrings() != numQualifiers)
        {
            Log::Error(L"Test setup: Incorrect qualifier type count");
            return E_FAIL;
        }
    }
    else if (pCloneFrom == nullptr)
    {
        Log::Error(L"Test setup: Qualifier types not specified");
        return E_FAIL;
    }

    if (runtimePriorities.TryInitFromTestVars(var.Format(L"%sQualifierRuntimePriorities", pVarPrefix)))
    {
        if (runtimePriorities.GetNumStrings() != numQualifiers)
        {
            Log::Error(L"Test setup: Incorrect qualifier runtime priority count");
            return E_FAIL;
        }
    }
    else if (pCloneFrom == nullptr)
    {
        Log::Error(L"Test setup: Qualifier runtime priorities not specified");
        return E_FAIL;
    }

    if (buildPriorities.TryInitFromTestVars(var.Format(L"%sQualifierBuildPriorities", pVarPrefix)))
    {
        if (buildPriorities.GetNumStrings() != numQualifiers)
        {
            Log::Error(L"Test setup: Incorrect qualifier build priorities count");
            return E_FAIL;
        }
    }
    else if (pCloneFrom == nullptr)
    {
        Log::Error(L"Test setup: Qualifier build priorities not specified");
        return E_FAIL;
    }

    pQualifierTypeNames = m_pQualifierTypeNames->GetPool();
    for (int i = 0; i < numQualifiers; i++)
    {
        if ((types.GetNumStrings() < 1) || (runtimePriorities.GetNumStrings() < 1) || (buildPriorities.GetNumStrings() < 1))
        {
            if (FAILED(pCloneFrom->GetQualifier(i, &otherQualifier)))
            {
                Log::Error(L"Couldn't get existing qualifier to clone");
                return E_FAIL;
            }
        }

        qualifier.name.Set(i, pQualifierNames->GetPoolIndex());

        if (types.GetNumStrings() > 0)
        {
            if (!pQualifierTypeNames->TryGetAtom(types.GetString(i), &qualifier.qualifierType))
            {
                Log::Error(L"Unknown qualifier type");
                return E_FAIL;
            }
        }
        else
        {
            qualifier.qualifierType = otherQualifier.qualifierType;
        }

        if (runtimePriorities.GetNumStrings() > 0)
        {
            if (swscanf_s(runtimePriorities.GetString(i), L"%d", &qualifier.defaultRuntimePriority) != 1)
            {
                Log::Error(L"Illegal runtime priority for qualifier");
                return E_FAIL;
            }
        }
        else
        {
            qualifier.defaultRuntimePriority = otherQualifier.defaultRuntimePriority;
        }

        if (buildPriorities.GetNumStrings() > 0)
        {
            if (swscanf_s(buildPriorities.GetString(i), L"%d", &qualifier.defaultBuildPriority) != 1)
            {
                Log::Error(L"Illegal build priority for qualifier");
                return E_FAIL;
            }
        }
        else
        {
            qualifier.defaultBuildPriority = otherQualifier.defaultBuildPriority;
        }

        if (FAILED(m_pQualifiers->SetItemData(i, qualifier, true)))
        {
            Log::Error(L"Adding qualifier failed");
            return E_FAIL;
        }
    }
    return S_OK;
}

HRESULT TestEnvironment::CreateInstance(
    _In_ PCWSTR pVarPrefix,
    _In_ AtomPoolGroup* pAtoms,
    _In_opt_ TestEnvironment* pCloneFrom,
    _Outptr_ TestEnvironment** value)
{
    String displayName;
    String uniqueName;
    int majorVersion;
    int minorVersion;
    String qualifierTypes;
    String itemTypes;
    String resourceValueTypes;
    String resourceValueLocators;
    String conditionOperators;

    String var;

    *value = nullptr;

    if (pCloneFrom != nullptr)
    {
        if (FAILED(TestData::TryGetValue(var.Format(L"%sDisplayName", pVarPrefix), displayName)))
        {
            displayName = pCloneFrom->GetDisplayName();
        }
        if (FAILED(TestData::TryGetValue(var.Format(L"%sUniqueName", pVarPrefix), uniqueName)))
        {
            uniqueName = pCloneFrom->GetUniqueName();
        }
        if (FAILED(TestData::TryGetValue(var.Format(L"%sMajorVersion", pVarPrefix), majorVersion)))
        {
            majorVersion = pCloneFrom->GetVersionInfo()->GetMajorVersion();
        }
        if (FAILED(TestData::TryGetValue(var.Format(L"%sMinorVersion", pVarPrefix), minorVersion)))
        {
            minorVersion = pCloneFrom->GetVersionInfo()->GetMinorVersion();
        }
    }
    else if (
        FAILED(TestData::TryGetValue(var.Format(L"%sDisplayName", pVarPrefix), displayName)) ||
        FAILED(TestData::TryGetValue(var.Format(L"%sUniqueName", pVarPrefix), uniqueName)) ||
        FAILED(TestData::TryGetValue(var.Format(L"%sMajorVersion", pVarPrefix), majorVersion)) ||
        FAILED(TestData::TryGetValue(var.Format(L"%sMinorVersion", pVarPrefix), minorVersion)))
    {
        Log::Error(L"Missing required test data");
        return E_FAIL;
    }

    TestEnvironment* pRtrn = new TestEnvironment(displayName, uniqueName, pAtoms);
    if (pRtrn == nullptr)
    {
        Log::Error(L"TestEnvironment constructor failed");
        return E_OUTOFMEMORY;
    }

    const IAtomPool* pOtherQualifierTypes = (pCloneFrom ? pCloneFrom->GetQualifierTypeNames() : nullptr);
    const IAtomPool* pOtherQualifiers = (pCloneFrom ? pCloneFrom->GetQualifierNames() : nullptr);
    const IAtomPool* pOtherItemTypes = (pCloneFrom ? pCloneFrom->GetItemTypeNames() : nullptr);
    const IAtomPool* pOtherInstanceTypes = (pCloneFrom ? pCloneFrom->GetResourceValueTypeNames() : nullptr);
    const IAtomPool* pOtherInstanceLocators = (pCloneFrom ? pCloneFrom->GetResourceValueLocatorNames() : nullptr);
    const IAtomPool* pOtherConditionOperators = (pCloneFrom ? pCloneFrom->GetConditionOperatorNames() : nullptr);

    pRtrn->m_pQualifierTypeNames = new TestAtomPool();
    pRtrn->m_pQualifierNames = new TestAtomPool();
    pRtrn->m_pItemTypeNames = new TestAtomPool();
    pRtrn->m_pResourceValueTypeNames = new TestAtomPool();
    pRtrn->m_pResourceValueLocatorNames = new TestAtomPool();
    pRtrn->m_pConditionOperatorNames = new TestAtomPool();

    if (!pRtrn->m_pQualifierTypeNames->InitFromTestVarsOrClone(
            L"QualifierTypes", true, var.Format(L"%sQualifierTypeNames", pVarPrefix), pAtoms, pOtherQualifierTypes) ||
        !pRtrn->m_pQualifierNames->InitFromTestVarsOrClone(
            L"Qualifiers", true, var.Format(L"%sQualifierNames", pVarPrefix), pAtoms, pOtherQualifiers) ||
        !pRtrn->m_pItemTypeNames->InitFromTestVarsOrClone(
            L"ItemTypes", true, var.Format(L"%sItemTypeNames", pVarPrefix), pAtoms, pOtherItemTypes) ||
        !pRtrn->m_pResourceValueTypeNames->InitFromTestVarsOrClone(
            L"ResourceValueTypes", true, var.Format(L"%sResourceValueTypeNames", pVarPrefix), pAtoms, pOtherInstanceTypes) ||
        !pRtrn->m_pResourceValueLocatorNames->InitFromTestVarsOrClone(
            L"ResourceValueLocators", true, var.Format(L"%sResourceValueLocatorNames", pVarPrefix), pAtoms, pOtherInstanceLocators) ||
        !pRtrn->m_pConditionOperatorNames->InitFromTestVarsOrClone(
            L"ConditionOperators", true, var.Format(L"%sConditionOperatorNames", pVarPrefix), pAtoms, pOtherConditionOperators))
    {
        delete pRtrn;
        return E_FAIL;
    }

    HRESULT hr = pRtrn->InitQualifiers(pVarPrefix, pCloneFrom);
    if (FAILED(hr))
    {
        delete pRtrn;
        return hr;
    }

    MRMFILE_ENVIRONMENT_VERSION_INFO vi;
    vi.major = static_cast<UINT16>(majorVersion);
    vi.minor = static_cast<UINT16>(minorVersion);
    vi.checksum = 0;
    vi.numQualifierTypes = static_cast<DEF_ATOM_COUNT_SMALL>(pRtrn->m_pQualifierTypeNames->GetNumStrings());
    vi.numQualifiers = static_cast<DEF_ATOM_COUNT_SMALL>(pRtrn->m_pQualifierNames->GetNumStrings());
    vi.numItemTypes = static_cast<DEF_ATOM_COUNT_SMALL>(pRtrn->m_pItemTypeNames->GetNumStrings());
    vi.numResourceValueTypes = static_cast<DEF_ATOM_COUNT_SMALL>(pRtrn->m_pResourceValueTypeNames->GetNumStrings());
    vi.numResourceValueLocators = static_cast<DEF_ATOM_COUNT_SMALL>(pRtrn->m_pResourceValueLocatorNames->GetNumStrings());
    vi.numConditionOperators = static_cast<DEF_ATOM_COUNT_SMALL>(pRtrn->m_pConditionOperatorNames->GetNumStrings());

    // Need a temporary environment version info to compute the checksum
    AutoDeletePtr<EnvironmentVersionInfo> pVersion;
    RETURN_IF_FAILED(EnvironmentVersionInfo::CreateInstance(&vi, &pVersion));
    DefChecksum::Checksum crc = 0;
    if ((pVersion == nullptr) || (FAILED(ComputeEnvironmentVersionChecksum(pRtrn, pVersion, &crc))))
    {
        delete pRtrn;
        return E_FAIL;
    }

    vi.checksum = crc;
    RETURN_IF_FAILED(EnvironmentVersionInfo::CreateInstance(&vi, (EnvironmentVersionInfo**)&pRtrn->m_pVersion));

    Log::Comment(var.Format(
        L"Created test environment %s v%d.%d (%s)",
        pRtrn->m_pUniqueName,
        pRtrn->m_pVersion->GetMajorVersion(),
        pRtrn->m_pVersion->GetMinorVersion(),
        pRtrn->m_pDisplayName));
    Log::Comment(var.Format(
        L"    sizes: [%d, %d, %d, %d, %d, %d ]",
        pRtrn->m_pQualifierTypeNames->GetNumStrings(),
        pRtrn->m_pQualifierNames->GetNumStrings(),
        pRtrn->m_pItemTypeNames->GetNumStrings(),
        pRtrn->m_pResourceValueTypeNames->GetNumStrings(),
        pRtrn->m_pResourceValueLocatorNames->GetNumStrings(),
        pRtrn->m_pConditionOperatorNames->GetNumStrings()));

    *value = pRtrn;
    return S_OK;
}

HRESULT
TestEnvironment::ValidateQualifierValue(_In_ PCWSTR /* pQualifierName */, _In_ PCWSTR /* pQualifierValue */) const { return E_NOTIMPL; }

HRESULT
TestEnvironment::ValidateQualifierValue(_In_ Atom /* qualifierName */, _In_ PCWSTR /* pQualifierValue */) const { return E_NOTIMPL; }

HRESULT
TestEnvironment::ValidateCondition(
    _In_ PCWSTR /* pQualifierName */,
    _In_ ICondition::ConditionOperator
    /*conditionOp*/,
    _In_ PCWSTR /* pQualifierValue */) const
{
    return E_NOTIMPL;
}

HRESULT
TestEnvironment::ValidateCondition(
    _In_ Atom /* qualifierName */,
    _In_ ICondition::ConditionOperator
    /*conditionOp*/,
    _In_ PCWSTR /* pQualifierValue */) const
{
    return E_NOTIMPL;
}

HRESULT
TestEnvironment::ValidateCondition(
    _In_ ResourceQualifier* /* pResourceQualifier */,
    _In_ ICondition::ConditionOperator
    /*conditionOp*/,
    _In_ PCWSTR /* pQualifierValue */) const
{
    return E_NOTIMPL;
}

HRESULT
TestEnvironment::GetTypeForQualifier(_In_ PCWSTR /* pQualifierName */, _Outptr_opt_result_maybenull_ const IBuildQualifierType** ppTypeOut)
    const
{
    if (ppTypeOut != nullptr)
    {
        *ppTypeOut = nullptr;
    }
    return E_NOTIMPL;
}

HRESULT
TestEnvironment::GetTypeForQualifier(_In_ Atom /*qualifierName*/, _Outptr_opt_result_maybenull_ const IBuildQualifierType** ppTypeOut) const
{
    if (ppTypeOut != nullptr)
    {
        *ppTypeOut = nullptr;
    }
    return E_NOTIMPL;
}

HRESULT
TestEnvironment::GetProviderForQualifier(
    _In_ PCWSTR /* pQualifierName */,
    _Outptr_opt_result_maybenull_ const IQualifierValueProvider** ppProvider) const
{
    if (ppProvider != nullptr)
    {
        *ppProvider = nullptr;
    }
    return E_NOTIMPL;
}

HRESULT
TestEnvironment::GetProviderForQualifier(
    _In_ Atom /*qualifierName*/,
    _Outptr_opt_result_maybenull_ const IQualifierValueProvider** ppProvider) const
{
    if (ppProvider != nullptr)
    {
        *ppProvider = nullptr;
    }
    return E_NOTIMPL;
}

const ENVIRONMENT_DESCRIPTION* TestEnvironment::GetEnvironmentDescription() const { return nullptr; }

const QUALIFIER_INFO* TestEnvironment::GetQualifierInfo() const { return nullptr; }

HRESULT
TestEnvironment::GetQualifierInfo(_In_ INT32 evIndex, _Outptr_ const QUALIFIER_INFO** ppQualifierInfo) const
{
    UNREFERENCED_PARAMETER(evIndex);
    *ppQualifierInfo = nullptr;
    return E_NOTIMPL;
}

TestEnvironmentCollection::TestEnvironmentCollection() {}

TestEnvironmentCollection::~TestEnvironmentCollection() { delete m_pEnvironments; }

HRESULT TestEnvironmentCollection::Initialize()
{
    return DefList<TestEnvironment*>::CreateInstance(
        10, &CompareGenericType<TestEnvironment*>, &HashGenericType<TestEnvironment*>, &m_pEnvironments);
}

int TestEnvironmentCollection::GetNumEnvironments() const { return m_pEnvironments->Count(); }

const IEnvironment* TestEnvironmentCollection::GetEnvironment(_In_ int index) const
{
    TestEnvironment* pEnvironment = nullptr;
    if (m_pEnvironments->TryGetValue(index, &pEnvironment))
    {
        return pEnvironment;
    }
    return nullptr;
}

/*!
    * Simple projection of MRMFILE_ENVIRONMENT_VERSION_INFO file data structure to the
    * IEnvironmentVersionInfo interface.
    */

HRESULT TestEnvironmentVersionInfo::CreateInstance(_In_ unsigned int versionIx, _Outptr_ TestEnvironmentVersionInfo** value)
{
    *value = nullptr;

    RETURN_HR_IF(E_INVALIDARG, versionIx >= ARRAYSIZE(TestEnvironmentVersions));

    TestEnvironmentVersionInfo* pRtrn = new (Microsoft::Resources::nothrow) TestEnvironmentVersionInfo(&TestEnvironmentVersions[versionIx]);
    RETURN_IF_NULL_ALLOC(pRtrn);

    *value = pRtrn;
    return S_OK;
}

} // namespace UnitTests
