// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "mrm/platform/base.h"
#include "mrm/platform/MrmConstants.h"

namespace Microsoft::Resources
{

// forward declarations
class ExtensibilityAdapterBase;

namespace CoreEnvironment
{

__declspec(selectany) extern const DefChecksum::Checksum version1_0_Checksum = 0xac2e0167;
__declspec(selectany) extern const DefChecksum::Checksum version1_1_Checksum = 0xd8259fbe;
__declspec(selectany) extern const DefChecksum::Checksum version1_2_Checksum = 0x71FF1091;
__declspec(selectany) extern const DefChecksum::Checksum currentChecksum = 0x71FF1091;

__declspec(selectany) extern const QUALIFIER_TYPE_DESCRIPTION QualifierTypeDescriptions[] = {
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
    fQualifierType_NotUsingExtensionEvaluator, // Device Family
    fQualifierType_NotUsingExtensionEvaluator // Custom

};

const ENVIRONMENT_INITIALIZER* GetEnvironmentInitializer();

const HRESULT GetInitializers(
    _In_ MrmPlatformVersionInternal version,
    _Out_ const ENVIRONMENT_INITIALIZER** ppEnvironmentInitializerOut,
    _Out_ const QUALIFIER_INFO** ppDefaultQualifierInfoOut);

HRESULT CreateInstance(_In_ AtomPoolGroup* pAtoms, _Outptr_ MrmEnvironment** environment);

HRESULT CreateInstance(_In_ AtomPoolGroup* pAtoms, _In_ int major, _In_ int minor, _Outptr_ MrmEnvironment** environment);

HRESULT FindInfoForVersion(
    _In_ int major,
    _In_ int minor,
    _Out_opt_ const MRMFILE_ENVIRONMENT_VERSION_INFO** ppInfoOut,
    _Inout_opt_ StringResult* pUniqueNameOut,
    _Inout_opt_ StringResult* pSimpleNameOut);

HRESULT FindInfoForCurrentVersion(
    _Out_opt_ const MRMFILE_ENVIRONMENT_VERSION_INFO** ppInfoOut,
    _Inout_opt_ StringResult* pUniqueNameOut,
    _Inout_opt_ StringResult* pSimpleNameOut);

HRESULT GetDefaultQualifierType(_In_ CoreEnvironment::QualifierTypeIndex qualifierTypeIndex, _Out_ IBuildQualifierType** ppTypeOut);

} // namespace CoreEnvironment
} // namespace Microsoft::Resources
