// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <mrm/build/AIDict.h>
#include "Helpers.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;
using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTests
{

// Compatible "future" version of the core environment, for testing purposes
namespace FutureCoreEnvironment
{
static const PCWSTR PlatformName = CoreEnvironment::PlatformName;
static const PCWSTR EnvironmentSimpleName = CoreEnvironment::EnvironmentSimpleName;
static const PCWSTR EnvironmentUniqueName = CoreEnvironment::EnvironmentUniqueName;

static const int MajorVersion = CoreEnvironment::MajorVersion;
static const int NextMinorVersion = CoreEnvironment::MinorVersion + 1;
static const int NextNextMinorVersion = CoreEnvironment::MinorVersion + 2;

static const PCWSTR QualifierType_FutureType1 = L"FutureType1";
static const PCWSTR QualifierType_FutureType2 = L"FutureType2";

enum class QualifierTypeIndex
{
    LanguageList = 0,
    Contrast = 1,
    Scale = 2,
    RegionId = 3,
    TargetSize = 4,
    LayoutDirection = 5,
    Theme = 6,
    AlternateForm = 7,
    DXFeatureLevel = 8,
    Configuration = 9,
    DeviceFamily = 10,
    Custom = 11,
    FutureType1 = 12,
    FutureType2 = 13
};

static const PCWSTR Qualifier_Future1 = L"Future1";
static const PCWSTR Qualifier_Future2 = L"Future2";

enum class QualifierIndex
{
    Language = 0,
    Contrast = 1,
    Scale = 2,
    HomeRegion = 3,
    TargetSize = 4,
    LayoutDirection = 5,
    Theme = 6,
    AlternateForm = 7,
    DXFeatureLevel = 8,
    Configuration = 9,
    DeviceFamily = 10,
    Custom = 11,
    Future1 = 12,
    Future2 = 13
};

static const PCWSTR Qualifier_Future1_AllowedValues[] = {L"IonDrive", L"Antigravity", L"Teleportation"};
static int Qualifier_Future1_NumAllowedValues = ARRAYSIZE(Qualifier_Future1_AllowedValues);

static const PCWSTR QualifierTypeNames[] = {
    CoreEnvironment::QualifierType_LanguageList,
    CoreEnvironment::QualifierType_Contrast,
    CoreEnvironment::QualifierType_Scale,
    CoreEnvironment::QualifierType_RegionId,
    CoreEnvironment::QualifierType_TargetSize,
    CoreEnvironment::QualifierType_LayoutDirection,
    CoreEnvironment::QualifierType_Theme,
    CoreEnvironment::QualifierType_AlternateForm,
    CoreEnvironment::QualifierType_DXFeatureLevel,
    CoreEnvironment::QualifierType_Configuration,
    CoreEnvironment::QualifierType_DeviceFamily,
    CoreEnvironment::QualifierType_CustomQualifier,
    QualifierType_FutureType1,
    QualifierType_FutureType2};

static const QUALIFIER_TYPE_DESCRIPTION QualifierTypeDescriptions[] = {
    fQualifierType_NotUsingExtensionEvaluator, // Language List
    fQualifierType_NotUsingExtensionEvaluator, // Contrast
    fQualifierType_NotUsingExtensionEvaluator, // Scale
    fQualifierType_NotUsingExtensionEvaluator, // Region ID
    fQualifierType_NotUsingExtensionEvaluator, // Target Size
    fQualifierType_NotUsingExtensionEvaluator, // Layout Direction
    fQualifierType_NotUsingExtensionEvaluator, // Theme
    fQualifierType_NotUsingExtensionEvaluator, // Alternate Form
    fQualifierType_NotUsingExtensionEvaluator, // DX Feature Level
    fQualifierType_NotUsingExtensionEvaluator, // Configuration,
    fQualifierType_NotUsingExtensionEvaluator, // Platform
    fQualifierType_NotUsingExtensionEvaluator, // App Specific Qualifier
    fQualifierType_NotUsingExtensionEvaluator, // FutureType1
    fQualifierType_NotUsingExtensionEvaluator, // FutureType2
};

static const PCWSTR QualifierNames[] = {
    CoreEnvironment::Qualifier_Language,
    CoreEnvironment::Qualifier_Contrast,
    CoreEnvironment::Qualifier_Scale,
    CoreEnvironment::Qualifier_HomeRegion,
    CoreEnvironment::Qualifier_TargetSize,
    CoreEnvironment::Qualifier_LayoutDirection,
    CoreEnvironment::Qualifier_Theme,
    CoreEnvironment::Qualifier_AlternateForm,
    CoreEnvironment::Qualifier_DXFeatureLevel,
    CoreEnvironment::Qualifier_Configuration,
    CoreEnvironment::Qualifier_DeviceFamily,
    CoreEnvironment::Qualifier_Custom,
    Qualifier_Future1,
    Qualifier_Future2};

static const QUALIFIER_DESCRIPTION QualifierDescriptions[] = {
    {
        // CoreEnvironment::Qualifier_Language
        L"lang",
        L"en-US",
        0,
        static_cast<UINT32>(CoreEnvironment::QualifierTypeIndex::LanguageList),
        900,
        700,
    },
    {
        // CoreEnvironment::Qualifier_Contrast
        L"contrast",
        CoreEnvironment::ContrastValue_Standard,
        0,
        static_cast<UINT32>(CoreEnvironment::QualifierTypeIndex::Contrast),
        700,
        400,
    },
    {
        // CoreEnvironment::Qualifier_Scale
        L"scale",
        CoreEnvironment::ScaleValue_100,
        fQualifier_AlwaysMatches | fQualifier_IsThreadAware,
        static_cast<UINT32>(CoreEnvironment::QualifierTypeIndex::Scale),
        500,
        200,
    },
    {
        // CoreEnvironment::Qualifier_HomeRegion
        L"region",
        CoreEnvironment::HomeRegionValue_001,
        0,
        static_cast<UINT32>(CoreEnvironment::QualifierTypeIndex::RegionId),
        950,
        800,
    },
    {
        // CoreEnvironment::Qualifier_TargetSize
        L"target",
        CoreEnvironment::TargetSizeValue_256,
        fQualifier_ValueProvidedbyCaller,
        static_cast<UINT32>(CoreEnvironment::QualifierTypeIndex::TargetSize),
        400,
        300,
    },
    {
        // CoreEnvironment::Qualifier_LayoutDirection
        L"layoutdir",
        CoreEnvironment::LayoutDirectionValue_LTR,
        0,
        static_cast<UINT32>(CoreEnvironment::QualifierTypeIndex::LayoutDirection),
        450,
        600,
    },
    {
        // CoreEnvironment::Qualifier_Theme
        L"theme",
        CoreEnvironment::ThemeValue_Dark,
        0,
        static_cast<UINT32>(CoreEnvironment::QualifierTypeIndex::Theme),
        600,
        350,
    },
    {
        // WindowsCoreConstDefs::Qualifier_AlternateForm,
        L"altform",
        L"",
        fQualifier_ValueProvidedbyCaller,
        static_cast<UINT32>(CoreEnvironment::QualifierTypeIndex::AlternateForm),
        10,
        100,
    },
    {
        // WindowsCoreConstDefs::Qualifier_DXFeatureLevel,
        L"dxfl",
        CoreEnvironment::DXFeatureLevelValue_9,
        fQualifier_ValueProvidedbyCaller,
        static_cast<UINT32>(CoreEnvironment::QualifierTypeIndex::DXFeatureLevel),
        150,
        150,
    },
    {
        // CoreEnvironment::Qualifier_Configuration
        L"config",
        L"",
        fQualifier_ReadOnlyForApp,
        static_cast<UINT32>(CoreEnvironment::QualifierTypeIndex::Configuration),
        1000,
        900,
    },
    {
        // CoreEnvironment::Qualifier_DeviceFamily
        L"devicefamily",
        CoreEnvironment::DeviceFamilyValue_UniversalAppPlatform,
        0,
        static_cast<UINT32>(CoreEnvironment::QualifierTypeIndex::DeviceFamily),
        500,
        500,
    },
    {// CoreEnvironment::Qualifier_Custom
     L"custom",
     L"",
     0,
     static_cast<UINT32>(CoreEnvironment::QualifierTypeIndex::CustomQualifier),
     850,
     850},
    {// Qualifier_Future1
     L"future1",
     L"",
     0,
     static_cast<UINT32>(QualifierTypeIndex::FutureType1),
     975,
     975},
    {// Qualifier_Future2
     L"future2",
     L"",
     0,
     static_cast<UINT32>(QualifierTypeIndex::FutureType2),
     50,
     50}};

static const int NumQualifierDescriptions = ARRAYSIZE(QualifierDescriptions);

// NOTE: We store the pre-computed value for efficiency, but it must
// be updated whenever the contents of the environment change in any
// way.  _Always_ run all Environment unit tests to verify that the
// stored and computed version checksums match.
static const DefChecksum::Checksum version1_0_Checksum = CoreEnvironment::version1_0_Checksum;
static const DefChecksum::Checksum version1_1_Checksum = CoreEnvironment::version1_1_Checksum;
static const DefChecksum::Checksum version1_2_Checksum = CoreEnvironment::version1_2_Checksum;
static const DefChecksum::Checksum version_next_Checksum = 0xa0001c6c;
static const DefChecksum::Checksum version_nextnext_Checksum = 0x3abba8d1;

static const int version1_0_NumQualifiers = CoreEnvironment::version1_0_NumQualifiers;
static const int version1_0_NumQualifierTypes = CoreEnvironment::version1_0_NumQualifierTypes;
static const int version1_1_NumQualifiers = CoreEnvironment::version1_1_NumQualifiers;
static const int version1_1_NumQualifierTypes = CoreEnvironment::version1_1_NumQualifierTypes;
static const int version1_2_NumQualifiers = CoreEnvironment::version1_2_NumQualifiers;
static const int version1_2_NumQualifierTypes = CoreEnvironment::version1_2_NumQualifierTypes;
static const int version_next_NumQualifiers = version1_2_NumQualifiers + 1;
static const int version_next_NumQualifierTypes = version1_2_NumQualifierTypes + 1;
static const int version_nextnext_NumQualifiers = version_next_NumQualifiers + 1;
static const int version_nextnext_NumQualifierTypes = version_next_NumQualifierTypes + 1;

static const int version_nextnext_Index = 0;
static const int version_next_Index = 1;

static_assert(
    ARRAYSIZE(QualifierDescriptions) == version_nextnext_NumQualifiers,
    "Incorrect qualifier count for future core environment version nextnext");

static const QUALIFIER_INFO QualifierInfo[] = {
    {// (Ver 1.nextnext) Test future version
     version_nextnext_Checksum, // evToken
     version_nextnext_NumQualifiers,
     QualifierNames,
     QualifierDescriptions,
     version_nextnext_NumQualifierTypes,
     QualifierTypeNames,
     QualifierTypeDescriptions},
    {// (Ver 1.next) Test future version
     version_next_Checksum, // evToken
     version_next_NumQualifiers,
     QualifierNames,
     QualifierDescriptions,
     version_next_NumQualifierTypes,
     QualifierTypeNames,
     QualifierTypeDescriptions},
    {// (Ver 1.2) RS4 Version
     version1_2_Checksum, // evToken
     version1_2_NumQualifiers,
     QualifierNames,
     QualifierDescriptions,
     version1_2_NumQualifierTypes,
     QualifierTypeNames,
     QualifierTypeDescriptions},
    {// (Ver 1.1) Windows 10 RTM Version
     version1_1_Checksum, // evToken
     version1_1_NumQualifiers,
     QualifierNames,
     QualifierDescriptions,
     version1_1_NumQualifierTypes,
     QualifierTypeNames,
     QualifierTypeDescriptions},
    {// (Ver 1.0) Windows 10 pre-RTM Version
     version1_0_Checksum, // evToken
     version1_0_NumQualifiers,
     QualifierNames,
     QualifierDescriptions,
     version1_0_NumQualifierTypes,
     QualifierTypeNames,
     QualifierTypeDescriptions},
};

// Each time a new minor version of the environment is to be created, add an entry as pVersions[1] (ie, the
// most recent previous verions) with the entries as constants.  Then update majorVersion, minorVersion, etc
// When rev'ing the major version, delete all the "previous version" array entries (ie, delete pVersions[1+])
static const MRMFILE_ENVIRONMENT_VERSION_INFO AllVersions[] = {
    // future test version
    {FutureCoreEnvironment::MajorVersion,
     FutureCoreEnvironment::NextNextMinorVersion,
     version_nextnext_Checksum,
     version_nextnext_NumQualifierTypes,
     version_nextnext_NumQualifiers,
     MrmEnvironment::NumResourceValueTypes,
     MrmEnvironment::NumResourceValueTypes,
     MrmEnvironment::NumResourceValueLocators,
     0},
    // future test version
    {FutureCoreEnvironment::MajorVersion,
     FutureCoreEnvironment::NextMinorVersion,
     version_next_Checksum,
     version_next_NumQualifierTypes,
     version_next_NumQualifiers,
     MrmEnvironment::NumResourceValueTypes,
     MrmEnvironment::NumResourceValueTypes,
     MrmEnvironment::NumResourceValueLocators,
     0},
    // RS4 version
    {CoreEnvironment::MajorVersion,
     CoreEnvironment::MinorVersion,
     version1_2_Checksum,
     version1_2_NumQualifierTypes,
     version1_2_NumQualifiers,
     MrmEnvironment::NumResourceValueTypes,
     MrmEnvironment::NumResourceValueTypes,
     MrmEnvironment::NumResourceValueLocators,
     0},
    // TH1 rtm version
    {CoreEnvironment::MajorVersion,
     1,
     version1_1_Checksum,
     version1_1_NumQualifierTypes,
     version1_1_NumQualifiers,
     MrmEnvironment::NumResourceValueTypes,
     MrmEnvironment::NumResourceValueTypes,
     MrmEnvironment::NumResourceValueLocators,
     0},
    // TH1 pre-rtm version
    {CoreEnvironment::MajorVersion,
     0,
     version1_0_Checksum,
     version1_0_NumQualifierTypes,
     version1_0_NumQualifiers,
     MrmEnvironment::NumResourceValueTypes,
     MrmEnvironment::NumResourceValueTypes,
     MrmEnvironment::NumResourceValueLocators,
     0},
};

static const int NumVersions = ARRAYSIZE(AllVersions);

static const ENVIRONMENT_DESCRIPTION FutureCoreEnvironmentDescription = {
    EnvironmentSimpleName,
    EnvironmentUniqueName,
    NumVersions,
    AllVersions,
};

static const ENVIRONMENT_INITIALIZER FutureCoreEnvironmentInitializer = {
    &FutureCoreEnvironmentDescription,
    2, // index 2 (RS4) is our base environment
    ARRAYSIZE(QualifierInfo),
    &QualifierInfo[0]};

inline HRESULT CreateInstance(_In_ AtomPoolGroup* pAtoms, _Outptr_ MrmEnvironment** value)
{
    return MrmEnvironment::CreateInstance(pAtoms, &FutureCoreEnvironmentInitializer, MajorVersion, NextNextMinorVersion, value);
}

inline HRESULT CreateInstance(_In_ AtomPoolGroup* pAtoms, _In_ int index, _Outptr_ MrmEnvironment** value)
{
    return MrmEnvironment::CreateInstance(pAtoms, &FutureCoreEnvironmentInitializer, index, value);
}

inline HRESULT CreateInstance(_In_ AtomPoolGroup* pAtoms, _In_ int major, _In_ int minor, _Outptr_ MrmEnvironment** value)
{
    return MrmEnvironment::CreateInstance(pAtoms, &FutureCoreEnvironmentInitializer, major, minor, value);
}

inline HRESULT FindInfoForVersion(
    _In_ int major,
    _In_ int minor,
    _Out_opt_ const MRMFILE_ENVIRONMENT_VERSION_INFO** ppInfoOut,
    _Inout_opt_ StringResult* pUniqueNameOut,
    _Inout_opt_ StringResult* pSimpleNameOut)
{
    return MrmEnvironment::FindInfoForVersion(&FutureCoreEnvironmentDescription, major, minor, ppInfoOut, pUniqueNameOut, pSimpleNameOut);
}

inline HRESULT FindInfoForVersion(
    _In_ int index,
    _Out_opt_ const MRMFILE_ENVIRONMENT_VERSION_INFO** ppInfoOut,
    _Inout_opt_ StringResult* pUniqueNameOut,
    _Inout_opt_ StringResult* pSimpleNameOut)
{
    return MrmEnvironment::FindInfoForVersion(&FutureCoreEnvironmentDescription, index, ppInfoOut, pUniqueNameOut, pSimpleNameOut);
}

inline HRESULT FindInfoForCurrentVersion(
    _Out_opt_ const MRMFILE_ENVIRONMENT_VERSION_INFO** ppInfoOut,
    _Inout_opt_ StringResult* pUniqueNameOut,
    _Inout_opt_ StringResult* pSimpleNameOut)
{
    return MrmEnvironment::FindInfoForCurrentVersion(&FutureCoreEnvironmentDescription, ppInfoOut, pUniqueNameOut, pSimpleNameOut);
}
}; // namespace FutureCoreEnvironment

// This should match the Microsoft::Resources::Windows8RuntimeData::versions[] array in Environment.cpp
static const MRMFILE_ENVIRONMENT_VERSION_INFO TestEnvironmentVersions[] = {
    // {majorVer, minorVer, verChecksum, numAttrTypes, numAttrs, numItemType, numInstanceTypes, numInstanceLocators, numConditionOps}
    {1, 4, 0x64d4872b, 9, 9, 3, 3, 3, 0}, // The current environ version infd (added DXFeatureLevel qualifier)
    {1, 3, 0x2aeb3101, 8, 8, 3, 3, 3, 0}, // The previous environ version info (added EmbeddedFile value type)
    {1, 2, 0x29cb5a06, 8, 8, 2, 2, 3, 0}, // The previous environ version info (added AlternateForm dimension)
    {1,
     1,
     0x8ae57d17,
     7,
     7,
     2,
     2,
     3,
     0}, // The previous environ version info (added HomeRegion, TargetSize, LayoutDirection, and Configuration dimension)
    {1, 0, 0xc5872444, 3, 3, 2, 2, 3, 0}, // The initial environ version (Language, Scale, and Contrast dimensions)
};

class TestEnvironment : public IEnvironment
{
protected:
    AtomPoolGroup* m_pAtoms;
    PWSTR m_pDisplayName;
    PWSTR m_pUniqueName;
    TestAtomPool* m_pQualifierNames;
    TestAtomPool* m_pQualifierTypeNames;
    TestAtomPool* m_pItemTypeNames;
    TestAtomPool* m_pResourceValueTypeNames;
    TestAtomPool* m_pResourceValueLocatorNames;
    TestAtomPool* m_pConditionOperatorNames;
    AtomIndexedStructDictionary<ResourceQualifier>* m_pQualifiers;
    IEnvironmentVersionInfo* m_pVersion;

    TestEnvironment(PCWSTR pDisplayName, PCWSTR pUniqueName, AtomPoolGroup* pAtoms);

    HRESULT InitQualifiers(PCWSTR pVarPrefix, _In_opt_ TestEnvironment* pCloneFrom);

    HRESULT ValidateCondition(
        _In_ ResourceQualifier* pResourceQualifier,
        _In_ ICondition::ConditionOperator conditionOp,
        _In_ PCWSTR pQualifierValue) const;

public:
    static HRESULT CreateInstance(
        _In_ PCWSTR pVarPrefix,
        _In_ AtomPoolGroup* pAtoms,
        _In_opt_ TestEnvironment* pCloneFrom,
        _Outptr_ TestEnvironment** value);

    ~TestEnvironment();

    AtomPoolGroup* GetAtoms() const { return m_pAtoms; }

    HRESULT GetQualifier(_In_ PCWSTR pQualifierName, _Out_ ResourceQualifier* pQualifierOut) const
    {
        return m_pQualifiers->TryGetItemData(pQualifierName, pQualifierOut) ? S_OK : HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    }

    HRESULT GetQualifier(_In_ int attrIndex, _Out_ ResourceQualifier* pQualifierOut) const
    {
        return m_pQualifiers->TryGetItemData(attrIndex, pQualifierOut) ? S_OK : HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    }

    HRESULT GetQualifier(_In_ Atom name, _Out_ ResourceQualifier* pQualifierOut) const
    {
        return m_pQualifiers->TryGetItemData(name, pQualifierOut) ? S_OK : HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    }

    const ENVIRONMENT_DESCRIPTION* GetEnvironmentDescription() const;
    const QUALIFIER_INFO* GetQualifierInfo() const;

    HRESULT GetQualifierInfo(_In_ INT32 evIndex, _Outptr_ const QUALIFIER_INFO** ppQualifierInfo) const;

    PCWSTR GetDisplayName() const { return m_pDisplayName; }
    PCWSTR GetUniqueName() const { return m_pUniqueName; }

    const IAtomPool* GetQualifierTypeNames() const { return m_pQualifierTypeNames->GetPool(); }
    const IAtomPool* GetQualifierNames() const { return m_pQualifierNames->GetPool(); }
    const IAtomPool* GetItemTypeNames() const { return m_pItemTypeNames->GetPool(); }
    const IAtomPool* GetResourceValueTypeNames() const { return m_pResourceValueTypeNames->GetPool(); }
    const IAtomPool* GetResourceValueLocatorNames() const { return m_pResourceValueLocatorNames->GetPool(); }
    const IAtomPool* GetConditionOperatorNames() const { return m_pConditionOperatorNames->GetPool(); }
    const IEnvironmentVersionInfo* GetVersionInfo() const { return m_pVersion; }

    HRESULT ValidateQualifierValue(_In_ PCWSTR pQualifierName, _In_ PCWSTR pQualifierValue) const;

    HRESULT ValidateQualifierValue(_In_ Atom qualifierName, _In_ PCWSTR pQualifierValue) const;

    HRESULT ValidateCondition(_In_ PCWSTR pQualifierName, _In_ ICondition::ConditionOperator conditionOp, _In_ PCWSTR pQualifierValue)
        const;

    HRESULT ValidateCondition(_In_ Atom qualifierName, _In_ ICondition::ConditionOperator conditionOp, _In_ PCWSTR pQualifierValue) const;

    HRESULT GetTypeForQualifier(_In_ PCWSTR pQualifierTypeName, _Outptr_opt_result_maybenull_ const IBuildQualifierType** ppTypeOut) const;

    HRESULT GetTypeForQualifier(_In_ Atom qualifierTypeName, _Outptr_opt_result_maybenull_ const IBuildQualifierType** ppTypeOut) const;

    HRESULT GetProviderForQualifier(_In_ PCWSTR pQualifierName, _Outptr_opt_result_maybenull_ const IQualifierValueProvider** ppProvider)
        const;

    HRESULT GetProviderForQualifier(_In_ Atom qualifierName, _Outptr_opt_result_maybenull_ const IQualifierValueProvider** ppProvider)
        const;
};

class TestEnvironmentCollection : public EnvironmentCollectionBase
{
protected:
    DefList<TestEnvironment*>* m_pEnvironments;

    TestEnvironmentCollection();
    HRESULT Initialize();

public:
    ~TestEnvironmentCollection();

    virtual int GetNumEnvironments() const;
    virtual const IEnvironment* GetEnvironment(_In_ int index) const;
};

class TestEnvironmentVersionInfo : public IEnvironmentVersionInfo
{
protected:
    MRMFILE_ENVIRONMENT_VERSION_INFO m_version;

    TestEnvironmentVersionInfo(_In_ const MRMFILE_ENVIRONMENT_VERSION_INFO* pVersion) { m_version = *pVersion; }

public:
    static HRESULT CreateInstance(_In_ unsigned int versionIx, _Outptr_ TestEnvironmentVersionInfo** value);

    UINT16 GetMajorVersion() const { return m_version.major; }
    UINT16 GetMinorVersion() const { return m_version.minor; }

    DEF_CHECKSUM GetVersionChecksum() const { return m_version.checksum; }
    int GetNumQualifierTypes() const { return m_version.numQualifierTypes; }
    int GetNumQualifiers() const { return m_version.numQualifiers; }
    int GetNumItemTypes() const { return m_version.numItemTypes; }
    int GetNumResourceValueTypes() const { return m_version.numResourceValueTypes; }
    int GetNumResourceValueLocators() const { return m_version.numResourceValueLocators; }
    int GetNumConditionOperators() const { return m_version.numConditionOperators; }

    void GetVersionInfo(_Out_ MRMFILE_ENVIRONMENT_VERSION_INFO* pVersionOut) const { *pVersionOut = m_version; }
};
} // namespace UnitTests
