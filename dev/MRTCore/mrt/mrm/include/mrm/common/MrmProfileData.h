// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "mrm/common/base.h"
#include "mrm/common/file/FileBase.h" // for DEFFILE_MAGIC

#ifdef __cplusplus
extern "C"
{
#endif

// to be used in QUALIFIER_DESCRIPTION.flags
#define fQualifier_AlwaysMatches 0x0001
#define fQualifier_ReadOnlyForApp 0x0002
#define fQualifier_IsResourcePackQualifier 0x0004
#define fQualifier_ProviderNotifiesViaWNF 0x0008
#define fQualifier_IsThreadAware 0x0010
#define fQualifier_ValueProvidedbyCaller 0x0020
#define fQualifier_NoProvider 0x00040000
#define fQualifier_ExtensionProvider 0x00080000

    // describes a qualifier
    typedef struct _QUALIFIER_DESCRIPTION
    {
        PCWSTR pQualifierToken;
        PCWSTR pDefaultValue;
        UINT32 flags;
        UINT32 qualifierTypeIndex;
        UINT32 runtimePriority;
        UINT32 buildPriority;
    } QUALIFIER_DESCRIPTION, *PQUALIFIER_DESCRIPTION;

// to be used in QUALIFIER_TYPE_DESCRIPTION.flags
#define fQualifierType_NotUsingExtensionEvaluator 0x00
#define fQualifierType_UsesExtensionEvaluator 0x01
#define fQualifierType_ExtensionEvaluatorMask 0x01

#define fQualifierType_BlockResourcePackages 0x00
#define fQualifierType_AllowResourcePackages 0x02
#define fQualifierType_ResourcePackageMask 0x02

#define fQualifierType_DoNotReportQualifier 0x00
#define fQualifierType_ReportQualifier 0x04
#define fQualifierType_ReportQualifierMask 0x04

#define fQualifierType_AllFallbackToMainPackage 0x00
#define fQualifierType_PerfectFallbackToMainPackage 0x08
#define fQualifierType_FallbackHandlingMask 0x08

#define fQualifierType_DefaultFlags \
    (fQualifierType_NotUsingExtensionEvaluator | fQualifierType_BlockResourcePackages | fQualifierType_DoNotReportQualifier)

    // describes a qualifier type
    typedef struct _QUALIFIER_TYPE_DESCRIPTION
    {
        UINT32 flags;
    } QUALIFIER_TYPE_DESCRIPTION, *PQUALIFIER_TYPE_DESCRIPTION;

    // describes a set of qualifiers and qualifier types for a specific environment version
    typedef struct _QUALIFIER_INFO
    {
        UINT32 evToken;

        INT32 numQualifiers;
        _Field_size_(numQualifiers) const PCWSTR* pQualifierNames;
        _Field_size_(numQualifiers) const QUALIFIER_DESCRIPTION* pQualifiers;

        INT32 numQualifierTypes;
        _Field_size_(numQualifierTypes) const PCWSTR* pQualifierTypeNames;
        _Field_size_(numQualifierTypes) const QUALIFIER_TYPE_DESCRIPTION* pQualifierTypes;

    } QUALIFIER_INFO, *PQUALIFIER_INFO;

    /*!
 * Version info for an MRM Environment header.
 * NOTE: This is a copy of MRMFILE_ENVIRONMENT_VERSION_INFO in MrmFiles.h!
 * Make sure it has the same exact contents.
typedef struct _ENVIRONMENT_VERSION_INFO {
    UINT16						major;
    UINT16						minor;
    DEF_CHECKSUM				checksum;
    DEF_ATOM_COUNT_SMALL        numQualifierTypes;
    DEF_ATOM_COUNT_SMALL        numQualifiers;
    DEF_ATOM_COUNT_SMALL        numItemTypes;
    DEF_ATOM_COUNT_SMALL        numResourceValueTypes;
    DEF_ATOM_COUNT_SMALL        numResourceValueLocators;
    DEF_ATOM_COUNT_SMALL        numConditionOperators;        
} ENVIRONMENT_VERSION_INFO, *PENVIRONMENT_VERSION_INFO;
 */

    // describes a build configuration.
    typedef struct _BUILD_CONFIGURATION
    {
        DEFFILE_MAGIC defFileMagic; // the ullMagic portion of DEFFILE_MAGIC
        UINT32 flags; // e.g. AllConfigurationFlags
        PCWSTR pTargetPlatformName; // e.g. "Windows"
        PCWSTR pOSVersion; // e.g. "6.3"
        PCWSTR pOSVersionAlternate; // e.g. "6.3.0"
    } BUILD_CONFIGURATION, *PBUILD_CONFIGURATION;

    // describes an environment
    typedef struct _ENVIRONMENT_DESCRIPTION
    {
        PCWSTR pSimpleName;
        PCWSTR pUniqueName;
        INT32 numVersions; // Entry 0 is the default.
        _Field_size_(numVersions) const MRMFILE_ENVIRONMENT_VERSION_INFO* pVersions;
    } ENVIRONMENT_DESCRIPTION, *PENVIRONMENT_DESCRIPTION;

    typedef struct _ENVIRONMENT_INITIALIZER
    {
        const ENVIRONMENT_DESCRIPTION* pEnvironmentDescription;
        INT32 indexOfBaseEnvironment;
        INT32 numQualifierInfos;
        _Field_size_(numQualifierInfos) const QUALIFIER_INFO* pQualifierInfos;
    } ENVIRONMENT_INITIALIZER;

#ifdef __cplusplus
}
#endif
