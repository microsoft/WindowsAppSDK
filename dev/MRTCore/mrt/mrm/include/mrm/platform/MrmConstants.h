// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

namespace Microsoft::Resources
{
namespace MrmWindowsCoreConstDefs
{

__declspec(selectany) extern const unsigned int defaultVerIx = 0;
__declspec(selectany) extern const ULONG64 uOSVersionThreshold = 0x000A000000000000uI64;
__declspec(selectany) extern const ULONG64 uOSVersionPhoneBlue = 0x0006000300010000uI64;
__declspec(selectany) extern const ULONG64 uOSVersionBlue = 0x0006000300000000uI64;
__declspec(selectany) extern const ULONG64 uOSVersion8 = 0x0006000200010000uI64;
__declspec(selectany) extern const ULONG64 uOSVersionAny = 0xFFFFFFFFFFFFFFFFuI64;

__declspec(selectany) extern PCWSTR const LongFilePathPrefix = L"\\\\?\\";
__declspec(selectany) extern PCWSTR const LongFileNetworkPathPrefix = L"\\\\?\\UNC\\";
__declspec(selectany) extern PCWSTR const UriScheme_Resource = L"ms-resource";
__declspec(selectany) extern PCWSTR const UriScheme_Resource_Delimited = L"ms-resource:";
__declspec(selectany) extern PCWSTR const BadLangValue = L"#";

__declspec(selectany) extern PCWSTR const Scope_StringNames = L"Resources";
__declspec(selectany) extern PCWSTR const Scope_FilePaths = L"Files";

__declspec(selectany) extern const int UriScheme_Resource_Length = ARRAYSIZE(L"ms-resource") - 1;
__declspec(selectany) extern const int UriScheme_Resource_Delimited_Length = ARRAYSIZE(L"ms-resource:") - 1;

__declspec(selectany) extern PCWSTR const DefaultUriScheme = L"ms-appx://";
__declspec(selectany) extern PCWSTR const DefaultUriFormat = L"ms-appx://%s/";

__declspec(selectany) extern PCWSTR const MergeFolderName = L"PRICache";
__declspec(selectany) extern PCWSTR const SystemMergeFolderRoot = L"rescache\\_merged"; // Windows 8.1 auto merged folder
__declspec(selectany) extern PCWSTR const MicrosoftMergeFolderName = L"Microsoft"; // App merge folder naming
__declspec(selectany) extern PCWSTR const WindowsMergeFolderName = L"Windows"; // App merge folder naming

__declspec(selectany) extern PCWSTR const CachedFilePathRegistryName = L"CachedMergedResourcesPriFileName";
__declspec(selectany) extern PCWSTR const MrtConfigKeyName = L"Software\\Microsoft\\Windows\\CurrentVersion\\Mrt";
__declspec(selectany) extern PCWSTR const MrtUseSystemMetadataPathRegistryName = L"UseSystemMetadataPath";

__declspec(selectany) extern PCWSTR const SystemComponentPackageName = L"Windows";
__declspec(selectany) extern PCWSTR const SystemResourcesFolder = L"%s\\SystemResources\\%s\\%s.pri";
__declspec(selectany) extern PCWSTR const OSAppsFolderName = L"OsApps";

}; // namespace MrmWindowsCoreConstDefs

namespace CoreEnvironment
{

__declspec(selectany) extern PCWSTR const PlatformName = L"universal";
__declspec(selectany) extern PCWSTR const EnvironmentSimpleName = L"WinCore";
__declspec(selectany) extern PCWSTR const EnvironmentUniqueName = L"win://WinCore/1";

__declspec(selectany) extern const int MajorVersion = 1;
__declspec(selectany) extern const int MinorVersion = 2;

__declspec(selectany) extern PCWSTR const DefaultPlatformVersion = L"10.0.0.5";

__declspec(selectany) extern PCWSTR const QualifierType_LanguageList = L"LanguageList";
__declspec(selectany) extern PCWSTR const QualifierType_Contrast = L"ContrastMode";
__declspec(selectany) extern PCWSTR const QualifierType_Scale = L"ScaleFactor";
__declspec(selectany) extern PCWSTR const QualifierType_RegionId = L"RegionId";
__declspec(selectany) extern PCWSTR const QualifierType_TargetSize = L"TargetSizeValue";
__declspec(selectany) extern PCWSTR const QualifierType_LayoutDirection = L"LayoutDirectionValue";
__declspec(selectany) extern PCWSTR const QualifierType_Theme = L"Theme";
__declspec(selectany) extern PCWSTR const QualifierType_AlternateForm = L"AlternateForm";
__declspec(selectany) extern PCWSTR const QualifierType_DXFeatureLevel = L"DXFeatureLevel";
__declspec(selectany) extern PCWSTR const QualifierType_Configuration = L"Configuration";
__declspec(selectany) extern PCWSTR const QualifierType_DeviceFamily = L"DeviceFamily";
__declspec(selectany) extern PCWSTR const QualifierType_CustomQualifier = L"CustomQualifier";

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
    CustomQualifier = 11
};

__declspec(selectany) extern PCWSTR const Qualifier_Language = L"Language";
__declspec(selectany) extern PCWSTR const Qualifier_Contrast = L"Contrast";
__declspec(selectany) extern PCWSTR const Qualifier_Scale = L"Scale";
__declspec(selectany) extern PCWSTR const Qualifier_HomeRegion = L"HomeRegion";
__declspec(selectany) extern PCWSTR const Qualifier_TargetSize = L"TargetSize";
__declspec(selectany) extern PCWSTR const Qualifier_LayoutDirection = L"LayoutDirection";
__declspec(selectany) extern PCWSTR const Qualifier_Theme = L"Theme";
__declspec(selectany) extern PCWSTR const Qualifier_AlternateForm = L"AlternateForm";
__declspec(selectany) extern PCWSTR const Qualifier_DXFeatureLevel = L"DXFeatureLevel";
__declspec(selectany) extern PCWSTR const Qualifier_Configuration = L"Configuration";
__declspec(selectany) extern PCWSTR const Qualifier_DeviceFamily = L"DeviceFamily";
__declspec(selectany) extern PCWSTR const Qualifier_Custom = L"Custom";

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
    Custom = 11
};

__declspec(selectany) extern PCWSTR const ScaleValue_100 = L"100";

__declspec(selectany) extern PCWSTR const ContrastValue_Standard = L"standard";
__declspec(selectany) extern PCWSTR const ContrastValue_High = L"high";
__declspec(selectany) extern PCWSTR const ContrastValue_Black = L"black";
__declspec(selectany) extern PCWSTR const ContrastValue_White = L"white";

__declspec(selectany) extern PCWSTR const
    Qualifier_Contrast_AllowedValues[] = {ContrastValue_Standard, ContrastValue_High, ContrastValue_Black, ContrastValue_White};
__declspec(selectany) extern int Qualifier_Contrast_NumAllowedValues = ARRAYSIZE(Qualifier_Contrast_AllowedValues);

__declspec(selectany) extern PCWSTR const LayoutDirectionValue_LTR = L"LTR";
__declspec(selectany) extern PCWSTR const LayoutDirectionValue_RTL = L"RTL";
__declspec(selectany) extern PCWSTR const LayoutDirectionValue_TTBLTR = L"TTBLTR";
__declspec(selectany) extern PCWSTR const LayoutDirectionValue_TTBRTL = L"TTBRTL";

__declspec(selectany) extern PCWSTR const Qualifier_LayoutDirection_AllowedValues[] =
    {LayoutDirectionValue_LTR, LayoutDirectionValue_RTL, LayoutDirectionValue_TTBLTR, LayoutDirectionValue_TTBRTL};
__declspec(selectany) extern int Qualifier_LayoutDirection_NumAllowedValues = ARRAYSIZE(Qualifier_LayoutDirection_AllowedValues);

__declspec(selectany) extern PCWSTR const HomeRegionValue_001 = L"001";

__declspec(selectany) extern PCWSTR const TargetSizeValue_256 = L"256";

__declspec(selectany) extern PCWSTR const ThemeValue_Dark = L"dark";
__declspec(selectany) extern PCWSTR const ThemeValue_Light = L"light";
__declspec(selectany) extern PCWSTR const Qualifier_Theme_AllowedValues[] = {ThemeValue_Dark, ThemeValue_Light};
__declspec(selectany) extern int Qualifier_Theme_NumAllowedValues = ARRAYSIZE(Qualifier_Theme_AllowedValues);

__declspec(selectany) extern PCWSTR const DXFeatureLevelValue_9 = L"DX9";
__declspec(selectany) extern PCWSTR const DXFeatureLevelValue_10 = L"DX10";
__declspec(selectany) extern PCWSTR const DXFeatureLevelValue_11 = L"DX11";
__declspec(selectany) extern PCWSTR const DXFeatureLevelValue_12 = L"DX12";

__declspec(selectany) extern PCWSTR const Qualifier_DXFeatureLevel_AllowedValues[] =
    {DXFeatureLevelValue_9, DXFeatureLevelValue_10, DXFeatureLevelValue_11, DXFeatureLevelValue_12};
__declspec(selectany) extern int Qualifier_DXFeatureLevel_NumAllowedValues = ARRAYSIZE(Qualifier_DXFeatureLevel_AllowedValues);

__declspec(selectany) extern const int Qualifier_Scale_Min_Value = 50;
__declspec(selectany) extern const int Qualifier_Scale_Max_Value = 1000;
__declspec(selectany) extern const int Qualifier_TargetSize_Min_Value = 1;
__declspec(selectany) extern const int Qualifier_TargetSize_Max_Value = UINT16_MAX;
__declspec(selectany) extern const int Qualifier_AlternateForm_Max_Length = 32;
__declspec(selectany) extern const int Qualifier_Configuration_Max_Length = 8;

__declspec(selectany) extern PCWSTR const DeviceFamilyValue_UniversalAppPlatform = L"Universal";
__declspec(selectany) extern PCWSTR const DeviceFamilyValue_Core = L"Core";
__declspec(selectany) extern PCWSTR const DeviceFamilyValue_Desktop = L"Desktop";
__declspec(selectany) extern PCWSTR const DeviceFamilyValue_UnknownAppPlatform = L"Unknown";
__declspec(selectany) extern PCWSTR const Qualifier_DeviceFamily_ProviderDefaultPrefix = L"Windows.";
__declspec(selectany) extern const int Qualifier_DeviceFamily_ProviderDefaultPrefix_Length = ARRAYSIZE(L"Windows.") - 1;
__declspec(selectany) extern const int Qualifier_DeviceFamily_MaxLength = 64;

__declspec(selectany) extern const int Qualifier_Custom_MaxLength = 32;
__declspec(selectany) extern PCWSTR const Qualifier_Custom_AppContainerValueName = L"Custom";

__declspec(selectany) extern PCWSTR const QualifierTypeNames[] = {
    QualifierType_LanguageList,
    QualifierType_Contrast,
    QualifierType_Scale,
    QualifierType_RegionId,
    QualifierType_TargetSize,
    QualifierType_LayoutDirection,
    QualifierType_Theme,
    QualifierType_AlternateForm,
    QualifierType_DXFeatureLevel,
    QualifierType_Configuration,
    QualifierType_DeviceFamily,
    QualifierType_CustomQualifier,
};

__declspec(selectany) extern PCWSTR const QualifierNames[] = {
    Qualifier_Language,
    Qualifier_Contrast,
    Qualifier_Scale,
    Qualifier_HomeRegion,
    Qualifier_TargetSize,
    Qualifier_LayoutDirection,
    Qualifier_Theme,
    Qualifier_AlternateForm,
    Qualifier_DXFeatureLevel,
    Qualifier_Configuration,
    Qualifier_DeviceFamily,
    Qualifier_Custom,
};

__declspec(selectany) extern const int version1_0_NumQualifiers = 11;
__declspec(selectany) extern const int version1_0_NumQualifierTypes = 11;
__declspec(selectany) extern const int version1_1_NumQualifiers = 12;
__declspec(selectany) extern const int version1_1_NumQualifierTypes = 12;

// TODO: This is currently identical to version 1.1 since we haven't added RS4 qualifiers yet.
// When we do, update this number but don't create a new version.
__declspec(selectany) extern const int version1_2_NumQualifiers = 12;
__declspec(selectany) extern const int version1_2_NumQualifierTypes = 12;

__declspec(selectany) extern const int NoBaseEnvironment = -1;

} // namespace CoreEnvironment
} // namespace Microsoft::Resources