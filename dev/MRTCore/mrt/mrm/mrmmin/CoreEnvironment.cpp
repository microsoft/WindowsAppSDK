// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"
#include "mrm/platform/WindowsCore.h"

namespace Microsoft::Resources::CoreEnvironment
{

static const QUALIFIER_DESCRIPTION QualifierDescriptions[] = {
    {
        // CoreEnvironment::Qualifier_Language
        L"lang",
        L"en-US",
        0,
        static_cast<UINT32>(QualifierTypeIndex::LanguageList),
        900,
        700,
    },
    {
        // CoreEnvironment::Qualifier_Contrast
        L"contrast",
        ContrastValue_Standard,
        0,
        static_cast<UINT32>(QualifierTypeIndex::Contrast),
        700,
        400,
    },
    {
        // CoreEnvironment::Qualifier_Scale
        L"scale",
        ScaleValue_100,
        fQualifier_AlwaysMatches | fQualifier_IsThreadAware,
        static_cast<UINT32>(QualifierTypeIndex::Scale),
        500,
        200,
    },
    {
        // CoreEnvironment::Qualifier_HomeRegion
        L"region",
        HomeRegionValue_001,
        0,
        static_cast<UINT32>(QualifierTypeIndex::RegionId),
        950,
        800,
    },
    {
        // CoreEnvironment::Qualifier_TargetSize
        L"target",
        TargetSizeValue_256,
        fQualifier_ValueProvidedbyCaller,
        static_cast<UINT32>(QualifierTypeIndex::TargetSize),
        400,
        300,
    },
    {
        // CoreEnvironment::Qualifier_LayoutDirection
        L"layoutdir",
        LayoutDirectionValue_LTR,
        0,
        static_cast<UINT32>(QualifierTypeIndex::LayoutDirection),
        450,
        600,
    },
    {
        // CoreEnvironment::Qualifier_Theme
        L"theme",
        ThemeValue_Dark,
        0,
        static_cast<UINT32>(QualifierTypeIndex::Theme),
        600,
        350,
    },
    {
        // WindowsCoreConstDefs::Qualifier_AlternateForm,
        L"altform",
        L"",
        fQualifier_ValueProvidedbyCaller,
        static_cast<UINT32>(QualifierTypeIndex::AlternateForm),
        10,
        100,
    },
    {
        // WindowsCoreConstDefs::Qualifier_DXFeatureLevel,
        L"dxfl",
        DXFeatureLevelValue_9,
        fQualifier_ValueProvidedbyCaller,
        static_cast<UINT32>(QualifierTypeIndex::DXFeatureLevel),
        150,
        150,
    },
    {
        // CoreEnvironment::Qualifier_Configuration
        L"config",
        L"",
        fQualifier_ReadOnlyForApp,
        static_cast<UINT32>(QualifierTypeIndex::Configuration),
        1000,
        900,
    },
    {
        // CoreEnvironment::Qualifier_DeviceFamily
        L"devicefamily",
        DeviceFamilyValue_UniversalAppPlatform,
        0,
        static_cast<UINT32>(QualifierTypeIndex::DeviceFamily),
        500,
        500,
    },
    {// CoreEnvironment::Qualifier_Custom
     L"custom",
     L"",
     0,
     static_cast<UINT32>(QualifierTypeIndex::CustomQualifier),
     850,
     850}};

static const int NumQualifierDescriptions = ARRAYSIZE(QualifierDescriptions);

// NOTE: We store the pre-computed value for efficiency, but it must
// be updated whenever the contents of the environment change in any
// way.  _Always_ run all Environment unit tests to verify that the
// stored and computed version checksums match.

static const QUALIFIER_INFO QualifierInfo[] = {
    {// (Ver 1.2) CURRENT VERSION
     version1_2_Checksum, // evToken
     version1_2_NumQualifiers,
     QualifierNames,
     QualifierDescriptions,
     version1_2_NumQualifierTypes,
     QualifierTypeNames,
     QualifierTypeDescriptions},
    {// (Ver 1.1)
     version1_1_Checksum, // evToken
     version1_1_NumQualifiers,
     QualifierNames,
     QualifierDescriptions,
     version1_1_NumQualifierTypes,
     QualifierTypeNames,
     QualifierTypeDescriptions},
    {// (Ver 1.0) CURRENT VERSION
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
    // current version
    {CoreEnvironment::MajorVersion,
     CoreEnvironment::MinorVersion,
     version1_2_Checksum,
     version1_2_NumQualifierTypes,
     version1_2_NumQualifiers,
     MrmEnvironment::NumResourceValueTypes,
     MrmEnvironment::NumResourceValueTypes,
     MrmEnvironment::NumResourceValueLocators,
     0},
    {CoreEnvironment::MajorVersion,
     1,
     version1_1_Checksum,
     version1_1_NumQualifierTypes,
     version1_1_NumQualifiers,
     MrmEnvironment::NumResourceValueTypes,
     MrmEnvironment::NumResourceValueTypes,
     MrmEnvironment::NumResourceValueLocators,
     0},
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

static const ENVIRONMENT_DESCRIPTION CoreEnvironmentDescription = {
    EnvironmentSimpleName,
    EnvironmentUniqueName,
    NumVersions,
    AllVersions,
};

static const ENVIRONMENT_INITIALIZER CoreEnvironmentInitializer =
    {&CoreEnvironmentDescription, NoBaseEnvironment, ARRAYSIZE(QualifierInfo), &QualifierInfo[0]};

const ENVIRONMENT_INITIALIZER* GetEnvironmentInitializer() { return &CoreEnvironmentInitializer; }

const HRESULT GetInitializers(
    MrmPlatformVersionInternal version,
    _Out_ const ENVIRONMENT_INITIALIZER** ppEnvironmentInitializerOut,
    _Out_ const QUALIFIER_INFO** ppDefaultQualifierInfoOut)
{
    if (IsPlatformAtLeastTH1(version) || IsPlatformDefault(version))
    {
        *ppEnvironmentInitializerOut = &CoreEnvironmentInitializer;
        *ppDefaultQualifierInfoOut = &CoreEnvironmentInitializer.pQualifierInfos[0];
    }
    else
    {
        RETURN_HR(E_DEF_UNSUPPORTED_VERSION);
    }

    return S_OK;
}

HRESULT CreateInstance(_In_ AtomPoolGroup* pAtoms, _Outptr_ MrmEnvironment** environment)
{
    return MrmEnvironment::CreateInstance(pAtoms, &CoreEnvironmentInitializer, MajorVersion, MinorVersion, environment);
}

HRESULT CreateInstance(_In_ AtomPoolGroup* pAtoms, _In_ int major, _In_ int minor, _Outptr_ MrmEnvironment** environment)
{
    return MrmEnvironment::CreateInstance(pAtoms, &CoreEnvironmentInitializer, major, minor, environment);
}

HRESULT FindInfoForVersion(
    int major,
    int minor,
    _Out_opt_ const MRMFILE_ENVIRONMENT_VERSION_INFO** ppInfoOut,
    _Inout_opt_ StringResult* pUniqueNameOut,
    _Inout_opt_ StringResult* pSimpleNameOut)
{
    return MrmEnvironment::FindInfoForVersion(&CoreEnvironmentDescription, major, minor, ppInfoOut, pUniqueNameOut, pSimpleNameOut);
}

HRESULT FindInfoForCurrentVersion(
    _Out_opt_ const MRMFILE_ENVIRONMENT_VERSION_INFO** ppInfoOut,
    _Inout_opt_ StringResult* pUniqueNameOut,
    _Inout_opt_ StringResult* pSimpleNameOut)
{
    return MrmEnvironment::FindInfoForCurrentVersion(&CoreEnvironmentDescription, ppInfoOut, pUniqueNameOut, pSimpleNameOut);
}

} // namespace Microsoft::Resources::CoreEnvironment
