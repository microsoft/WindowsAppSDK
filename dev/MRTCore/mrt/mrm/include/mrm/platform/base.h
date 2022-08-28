// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

namespace Microsoft::Resources
{

#define MRT_PACKAGE_NAME_MAX_LENGTH (PACKAGE_NAME_MAX_LENGTH + 5)

class ProviderResolver;
class ExtensibilityAdapterBase;
class IBuildQualifierType;
class RemapAtomPool;

// The MrmPlatformVersionInternal enumeration describes known platform versions.
typedef enum _MrmPlatformVersionInternal
{
    DefaultPlatformVersion = 0,
    WindowsClient8 = 0x0C060201, // 0xC = Desktop, 6.2.1
    WindowsClientBlue = 0x0C060300, // 0xC = Desktop, 6.3.0
    WindowsPhoneBlue = 0x0F060301, // 0xF = Phone, 6.3.1
    WindowsCore = 0x010A0000, // 0x1 = OneCore, 10.0.0
    WindowsCoreRS4 =
        0x010A0005, // 0x1 = OneCore, 10.0.0.5 - we don't have enough bits to represent this, so we implicitly assume the middle 0 means two zeros.
    WindowsCoreVNext = 0x01990001, // 0x1 = Version for features not yet enabled but otherwise ready for production.
    // Test-only profiles.
    TestIncompatiblePlatformVersion = 0x07070707, // 0x7 = Test 7.7.7 - used for negative tests
    TestFutureCoreVersion =
        0x0707070A, // 0x7 = Test 7.7.A - a ficticious vnext (different from the real vnext in that it has a custom implementation to test specific scenarios)
    TestFutureCoreVersion2 = 0x0707070B, // 0x7 = Test 7.7.B - a ficticious vnextnext
} MrmPlatformVersionInternal;

inline bool IsPlatformAtLeastTH1(MrmPlatformVersionInternal platform)
{
    return (
        platform != WindowsClient8 && platform != WindowsClientBlue && platform != WindowsPhoneBlue &&
        platform != TestIncompatiblePlatformVersion);
}

inline bool IsPlatformAtLeastRS4(MrmPlatformVersionInternal platform)
{
    return (
        platform != WindowsClient8 && platform != WindowsClientBlue && platform != WindowsPhoneBlue && platform != WindowsCore &&
        platform != TestIncompatiblePlatformVersion);
}

inline bool IsPlatformVNext(MrmPlatformVersionInternal platform) { return (platform == WindowsCoreVNext); }

inline bool IsPlatformDefault(MrmPlatformVersionInternal platform) { return (platform == DefaultPlatformVersion); }

inline bool IsTestFutureCoreVersion(MrmPlatformVersionInternal platform)
{
    return (platform == TestFutureCoreVersion || platform == TestFutureCoreVersion2);
}

inline bool IsTestMrmPlatformVersionInternal(MrmPlatformVersionInternal platform)
{
    return (platform == TestIncompatiblePlatformVersion || IsTestFutureCoreVersion(platform));
}

typedef enum _MrtSharedObjectState
{
    NoState = 0x00,
    Instance = 0x01,
    Singleton = 0x02,
    StoreApp = 0x04,
    SystemComponent = 0x08,
    Win32App = 0x10,
} MrtSharedObjectState;
DEFINE_ENUM_FLAG_OPERATORS(MrtSharedObjectState);

class IRawResourceMap;
class IQualifierValueProvider;
class MrmBuildConfiguration;
class UnifiedEnvironment;

// MrmProfile phase is used to indicate the phase during which a particular method is called.
typedef enum _MRMPROFILE_PHASE
{
    PACKAGE_INIT = 0,
    EXPLICIT_LOAD = 1,
    EXPLICIT_LOAD_FROM_API = 2,
    EXPLICIT_LOAD_AS_PRIMARY = 3
} MRMPROFILE_PHASE;

/*! 
 * The CoreProfile and MrmProfile abstracts the environment and business logic for any
 * particular specific class of consumers of MRT. 
 *
 * A core profile abstracts only the platform & business logic required by low-level system
 * consumers of MRT.   The full MrmProfile extends the core profile to add information about
 * packages and build-time concepts.
 *
 * A few concepts:
 *
 * PRI files can be either loose or associated with packages.   Every PRI has an
 * associated root folder - paths in the PRI are interpreted relative to that
 * root folder.
 *
 * Packages to have as 'simple' name, typically used in markup or code, and a 'unique' 
 * name with some level of guaranteed uniqueness.  For example, a profile that supports
 * resource packs would use the same 'simple' name for the main package and all of its
 * related resources, but every package would still have a different unique name.  Profiles
 * are allowed to use the same value for simple and unique name, but may not return the 
 * same unique name for more than one package.
 *
 * The MrmProfile class allows profiles to constrain the locations from which PRI
 * files are loaded and the names of any resource maps.
 */

class CoreProfile : public DefObject
{
public:
    static HRESULT ChooseDefaultProfile(_Outptr_ CoreProfile** profile);

    virtual ~CoreProfile();

    // Package operations

    /*! 
     * Determines if a specified PRI file can be loaded into the current
     * application using this profile.
     * 
     * \param pPriFileFullPath
     * The full, normalized absolute path to the PRI file.
     *
     * \return bool
     * Returns TRUE if the file can be loaded, false otherwise or if
     * an error occurs.  If the file cannot be loaded, extended status
     * contains additional details.
     *
     * \remarks
     * The base implementation allows any PRI file to be loaded.
     */
    virtual bool IsLoadPriFileAllowed(_In_ PCWSTR /*pPriFileFullPath*/
    ) const;

    /*! 
     * Determines if a specified package or PRI file can be accessed via a URI-based
     * indirect resource reference
     * 
     * \param pPriFileOrPacakage
     * The unique name of a package, or the full, normalized absolute path to the PRI file.
     *
     * \return bool
     * Returns true if the file can be loaded, false otherwise or if an error occurs.
     *
     * \remarks
     * The base implementation does not allow any fully qualified references.
     */
    virtual bool IsFullyQualifiedReferenceAllowed(_In_ PCWSTR pPriFileOrPackage) const;

    /*! 
     * Determines if a specified resource map can be acquired
     * 
     * \param pResourceMapName
     * The unique name of a resource name.
     *
     * \return bool
     * Returns true if the file can be loaded, false otherwise or if an error occurs.
     *
     * \remarks
     * The base implementation allows given resource map to be retrieved, and does not allow
     * retrieval.
     */
    virtual bool IsResourceMapLookupByNameAllowed(_In_opt_ PCWSTR pResourceMapName) const;

    /*!
     *  Check if the resource file can be loaded during resource search
     *
     *
     * \return bool
     * Returns TRUE if the resource file can be loaded during resource search/GetResourceMap operation
     *
     * \remarks
     * The base implementation does not load resource file.
     * When the function return true, the caller can call GetMainPriFilePathForResourceMapName to get the resource file path
     */
    virtual bool IsResourceFileAutoLoadSupported() const;

    /*! 
     * Determines the root folder for a specified PRI file.
     * 
     * \param pPriFileFullPath
     * The full, normalized, absolute path to the PRI file.
     *
     * \param pPriFileRoot
     * On success, returns the normalized absolute path of the
     * root folder for the specified PRI file.
     * 
     * \return HRESULT
     * Returns S_OK on success, failure if an error occurs.
     *
     * \remarks
     * The base implementation reports the folder that contains
     * the PRI file itself as the root folder.
     */
    virtual HRESULT GetRootFolderForPriFile(_In_ PCWSTR pPriFileFullPath, _Inout_ StringResult* pPriFileRootOut) const;

    /*! 
     * Determines if this profile allows a resource map to be loaded
     * into the current application. 
     * 
     * \param pResourceMapName
     * The name of the resource map to be loaded.
     *
     * \param MRMPROFILE_PHASE
     * Enum to indicate the phase during which this method is called.
     *
     * \param pPriFileFullPath
     * The full, normalized, absolute path of the PRI file that contains
     * the resource map.  Can be NULL or empty if the map is loaded from
     * memory or if the location is unknown.
     * 
     * \return bool
     * Returns true if the map can be loaded, false otherwise or if an error occurs.
     *
     * \remarks
     * The default implementation allows any resource map to be loaded.
     */
    virtual bool IsLoadResourceMapAllowed(
        _In_ PCWSTR pResourceMapName,
        _In_ MRMPROFILE_PHASE mrmProfilePhase,
        _In_opt_ PCWSTR pPriFileFullPath);

    // Determines if a profile is allowed to load PRI files that might be unsafe. Default is true.
    virtual bool IsUnsafeLoadPriFileAllowed() const;

    // Determines if a supplied file magic number is supported
    // Default implementation supports only universal PRI files
    virtual bool IsSupportedFileMagicNumber(_In_ const DEFFILE_MAGIC& fileMagicNumber) const;

    // Determines the MrmPlatformVersionInternal which corresponds to a
    // given file magic number.  Default implementation supports
    // only universal files for the WinCorePlatform default version.
    virtual HRESULT GetTargetPlatformVersionForFileMagic(
        _In_ const DEFFILE_MAGIC& fileMagicNumber,
        _Out_ MrmPlatformVersionInternal* pPlatformVersionOut);

    // Determines the platform and version which corresponds to a
    // given file magic number.  Default implementation supports
    // only universal files for the WinCore platform default version.
    virtual HRESULT GetTargetPlatformAndVersionForFileMagic(
        _In_ const DEFFILE_MAGIC& fileMagicNumber,
        _Inout_opt_ StringResult* correspondingPlatformName,
        _Inout_opt_ StringResult* correspondingPlatformVersion);

    // Gets the default target platform and version to use.
    // Default uses the WinCore platform default version.
    virtual HRESULT GetTargetPlatformAndVersion(
        _Inout_opt_ StringResult* correspondingPlatformName,
        _Inout_opt_ StringResult* correspondingPlatformVersion);

    /*! 
     * Gets the number of environments supported by this profile.
     * 
     * \return int
     * Returns the number of environments supported by this profile,
     * or 0 if an error occurs.
     *
     * \remarks
     * Base implementation supports only CoreEnvironment
     */
    virtual int GetNumEnvironments() const;

    /*! 
     * Returns name and version information about one of the
     * environments supported by this profile.
     * 
     * \param index
     * Index of the environment to be queried.
     *
     * \param pEnvironmentName
     * The name of the requested environment.
     * 
     * \param info
     * Pointer to an IEnvironmentVersionInfo describing the 
     * environment, or NULL if an error occurs.
     *
     * \return HRESULT.
     *
     * \remarks
     * The caller is responsible for freeing the returned structure.
     *
     * Base implementation supports only the core environment at index 0.
     */

    virtual HRESULT GetEnvironmentVersionInfo(
        _In_ int index,
        _Inout_ StringResult* environmentName,
        _Outptr_ IEnvironmentVersionInfo** info) const;

    /*! 
     * Creates one of the environments supported by this profile,
     * specified by index. 
     * 
     * \param index
     * Index of the environment to be returned.
     *
     * \param pAtoms
     * The AtomPoolGroup in which the environment atom pools should
     * be created.
     * 
     * \param environment
     * Returns the requested environment, or NULL if an error occurs.
     * 
     * \return HRESULT
     * \remarks
     * The caller is responsible for freeing the environment.
     *
     * The base implementation supports only CoreEnvironment at index 0.
     *
     */
    virtual HRESULT CreateEnvironment(_In_ int index, _In_ AtomPoolGroup* pAtoms, _Outptr_ IEnvironment** environment) const;

    /*! 
     * If the current profile has a base environment from which
     * deltas should be noted, this method returns the initializer
     * index of that base environment.
     * 
     * \param baseEnvironmentIndex
     * The initializer index of the base environment, if defined.
     * If no base environment is defined, returns -1.
     * 
     * \return bool
     * Returns true if a base environment is defined, false otherwise.
     *
     */
    virtual bool TryGetBaseEnvironmentIndex(_Out_ int* baseEnvironmentIndex) const;

    /*! 
     * Sets the profile to use a supplied environment, if supported.
     * 
     * \param initializer
     * The environment initializer to be used by this profile.
     *
     * \param defaultEnvironmentIndex
     * The index in initializer of the default environment
     * 
     * \remarks
     * Does _not_ take ownership of initializer.  Caller is responsible for
     * ensuring the lifespan and cleanup of initializer.
     *
     * The default implementation fails with DEF_NOT_WRITABLE.
     *
     * \return HERSULT
     */
    virtual HRESULT SetEnvironmentInitializer(_In_ const ENVIRONMENT_INITIALIZER* initializer, _In_ int defaultEnvironmentIndex);

    /*! 
     * Gets a new instance of the concrete qualifier type implementation
     * for a qualifier specified by index.
     * 
     * \param pEnvironment
     * The UnifiedEnvironment for which the type is to be created.
     *
     * \param qualifierAtom
     * Supplies the atom of the qualifier for which the type is to be returned.
     * 
     * \param ppTypeOut
     * Returns the requested qualifier type, or NULL if an error occurs.
     *
     * \return HRESULT
     *
     * \remarks
     * Caller is responsible for freeing the returned IQualifierType.
     *
     * There is no base implementation of this method.
     */
    virtual HRESULT GetTypeForQualifier(
        _In_ const IEnvironment* pEnvironment,
        _In_ Atom qualifierAtom,
        _Out_ IBuildQualifierType** ppTypeOut) const = 0;

    /*! 
     * Gets the appropriate provider for a qualifier specified by index.
     * 
     * \param pResolver
     * The ProviderResolver for which the value provider is to be created.
     *
     * \param qualifierAtom
     * Specifies the name of the qualifier for which the provider is to be returned
     * 
     * \param ppTypeOut
     * Returns the requested provider, or NULL if an error occurs.
     *
     * \return HRESULT
     *
     * \remarks
     * Caller is responsible for freeing the returned value provider.
     *
     * There is no base implementation of this method.
     */
    virtual HRESULT GetProviderForQualifier(
        _In_ const IEnvironment* pResolver,
        _In_ Atom qualifierAtom,
        _Out_ IQualifierValueProvider** ppProviderOut) const = 0;

    virtual HRESULT GetDefaultEnvironmentForFileMagic(
        _In_ const DEFFILE_MAGIC& fileMagicNumber,
        _Inout_opt_ StringResult* nameOut,
        _Inout_opt_ EnvironmentVersionInfo* versionInfoOut) const;

    virtual bool TryGetEnvironmentForChecksum(
        _In_ DefChecksum::Checksum checksum,
        _Inout_opt_ StringResult* nameOut,
        _Inout_opt_ EnvironmentVersionInfo* versionInfoOut) const;

    virtual HRESULT GetQualifierInfoForEnvironment(
        _In_ PCWSTR sourceName,
        _In_ const IEnvironmentVersionInfo* sourceVersion,
        _In_ const IEnvironment* targetEnvironment,
        _Out_ int* numMappedQualifiers,
        _Outptr_result_buffer_maybenull_(*numMappedQualifiers) const PCWSTR** mappedQualifierNames,
        _Outptr_result_buffer_maybenull_(*numMappedQualifiers) const Atom::SmallIndex** qualifierMappings) const;

    virtual bool IsCompatibleEnvironment(
        _In_ const EnvironmentReference* wantEnvironment,
        _In_ const IEnvironment* haveEnvironment,
        _Outptr_result_maybenull_ const RemapAtomPool** qualifierMapping) const;

    /*! 
     * Gets the application and system merge folders for the current profile.
     *
     * \param pAppMergeFolder
     * Returns the application-specific merge folder, or an empty string
     * if no application merge folder is available.
     *
     * \param pSystemMergeFolder
     * Returns the system-shared merge folder, or an empty string if no
     * system merge folder is available.
     * 
     * \return HRESULT
     * Returns S_OK on success, failure if an error occurs.  Returns S_OK
     * even if both merge folders are empty.
     *
     * \remarks
     * The base implementation returns the default system merge folder and an
     * empty app merge folder.
     */
    virtual HRESULT GetMergeFolders(_Inout_opt_ StringResult* pAppMergeFolder, _Inout_opt_ StringResult* pSystemMergeFolder) const;

    /*!
    * Gets the cached Windows system folder. The purpose is to avoid calling GetSystemWindowsDirectory multiple times
    *
    * \param cachedWindowsFoldername
    * Returns the windows folder name.
    *
    * \return HRESULT
    */
    HRESULT GetCachedWindowsFolderName(_Inout_opt_ StringResult* cachedWindowsFoldername) const;

    /*!
    * Gets the OS Apps folder. 
    *
    * \param osAppsFoldername
    * Returns the OS apps folder name.
    *
    * \return HRESULT
    */
    HRESULT GetOsAppsFolderName(_Inout_opt_ StringResult* osAppsFoldername) const;

    /*! 
     * Gets the default build configuration for this profile.  Default build configuration
     * is determined by the platform and version used to create the profile.
     * 
     * \return const MrmBuildConfiguration*
     *
     * \remarks
     * The caller is responsible for freeing the returned object
     *
     * The base implementation returns the default build configuration for a universal PRI file
     */
    virtual MrmBuildConfiguration* GetBuildConfiguration();

    // Default unique name implementation uses ms-appx protocol
    virtual HRESULT GetDefaultUniqueName(_In_ PCWSTR pSimpleName, _Inout_ StringResult* pUniqueNameOut) const;

    /*!
     *  Return numbers of qualifiers that support thread specific data
     *
     * \return int
     * Returns the number of thread aware qualifiers.
     *
     * \remarks
     * The base implementation return 0.
     */
    virtual int GetNumThreadAwareQualifiers() const;

    /*!
     *  Get qualifier name by index of thread aware qualifiers
     *
     * \param index
     * Index of the thread aware qualifiers
     *
     * \param pResult
     * Returns the valid qualifier string name of given index.
     *
     * \return HRESULT
     *
     * \remarks
     * The base implementation return false.
     */
    virtual HRESULT GetThreadAwareQualifierName(_In_ int index, _Inout_ StringResult* pResult) const;

    /*!
     * Looks for an application-specific setting by name.
     *
     * \param subkeyName
     * Name of the subkey that holds the setting we're looking for
     *
     * \param settingName
     * Name of the setting we're looking for.
     *
     * \param returnedValue
     * Returns the value of the setting, if found.
     *
     * \return bool
     * Returns true if a value is found, false if no value is found
     * or if an error occurs.
     *
     * \remarks
     * Base implementation always returns false.
     */
    virtual bool TryGetApplicationSetting(_In_ PCWSTR subkeyName, _In_ PCWSTR settingName, _Inout_ StringResult* returnedValue) const;

    /*!
     * Sets an application setting specified by name to a supplied value.
     *
     * \param subkeyName
     * Name of the subkey that holds the setting we want to change
     *
     * \param settingName
     * Name of the setting we want to change
     *
     * \param settingValue
     * The new value for the setting.
     *
     * \return HRESULT
     *
     * \remarks
     * Base implementation always returns HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED).
     */
    virtual HRESULT SetApplicationSetting(_In_ PCWSTR subkeyName, _In_ PCWSTR settingName, _In_ PCWSTR settingValue) const;

    /*! 
     * Gets the unique and simple names and the root folder for one of the available packages,
     * specified by index.  If present, package 0 is the 'main' package.
     * 
     * \param index
     * Index of the package to be returned.
     *
     * \param pPackageUniqueNameOut
     * Returns the unique name of the specified package.
     *
     * \param pPackageSimpleNameOut
     * Returns the simple name of the specified package.
     *
     * \param pPackageRootOut
     * Returns the root folder of the specified package.
     * 
     * \return HRESULT
     *
     * \remarks
     * The base implementation does not support packages
	 * and simply returns an error.
     */
    virtual HRESULT GetPackageInfo(
        _In_ int index,
        _Inout_opt_ StringResult* pPackageUniqueNameOut,
        _Inout_opt_ StringResult* pPackageSimpleNameOut,
        _Inout_opt_ StringResult* pPackageRootOut) const;

protected:
    CoreProfile();

    bool TryGetRedirectedSystemMergeFolder(_Inout_ StringResult* redirectedMergeFolder) const;

    MrmBuildConfiguration* m_pBuildConfiguration;

    const ENVIRONMENT_INITIALIZER* m_initializer;
    int m_defaultEnvironmentIndex;
    mutable StringResult m_cachedWindowsFolderName;
};

/*! 
 * An MrmFileCapabilities describes the way the PRI file is built, to allow
 * for backward compatibility and developer preference.
 */
class MrmBuildConfiguration : public DefObject
{
public:
    static HRESULT CreateInstance(_In_ DEFFILE_MAGIC fileMagicNumber, _In_ UINT32 flags, _Outptr_ MrmBuildConfiguration** config)
    {
        *config = nullptr;
        MrmBuildConfiguration* pRtrn = new MrmBuildConfiguration(fileMagicNumber, flags);
        RETURN_IF_NULL_ALLOC(pRtrn);

        *config = pRtrn;

        return S_OK;
    }

    static HRESULT CreateInstance(_In_ MrmPlatformVersionInternal platformVersion, _Outptr_ MrmBuildConfiguration** config)
    {
        *config = nullptr;
        switch (platformVersion)
        {
        case MrmPlatformVersionInternal::WindowsClient8:
            return MrmBuildConfiguration::CreateInstance(gWin8PriFileMagic, Windows8ConfigurationFlags, config);
        case MrmPlatformVersionInternal::WindowsCoreRS4:
            return MrmBuildConfiguration::CreateInstance(gUniversalRS4PriFileMagic, UniversalConfigurationFlags, config);
        case MrmPlatformVersionInternal::WindowsClientBlue:
            return MrmBuildConfiguration::CreateInstance(gWinBluePriFileMagic, Windows8_1ConfigurationFlags, config);
        // Windowss 10 is the default.
        case MrmPlatformVersionInternal::DefaultPlatformVersion:
        case MrmPlatformVersionInternal::WindowsCore:
            return MrmBuildConfiguration::CreateInstance(gUniversalPriFileMagic, UniversalConfigurationFlags, config);
        case MrmPlatformVersionInternal::WindowsPhoneBlue:
            return MrmBuildConfiguration::CreateInstance(gWindowsPhoneBluePriFileMagic, Windows8_1ConfigurationFlags, config);
        // Tests future features, currently granular splitting and multi-dimensional splitting
        case MrmPlatformVersionInternal::WindowsCoreVNext:
            return MrmBuildConfiguration::CreateInstance(gUniversalVNextPriFileMagic, UniversalConfigurationFlags, config);
        default:
            __fallthrough;
        }

        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    // returns a new default (universal) build configuration
    static HRESULT CreateDefault(_Outptr_ MrmBuildConfiguration** config)
    {
        return CreateInstance(MrmPlatformVersionInternal::WindowsCoreRS4, config);
    }

    virtual ~MrmBuildConfiguration() {}

    static const UINT32 UseDataItemLocatorFlag = 0x01;
    static const UINT32 UseFileInfoLocatorFlag = 0x02;
    static const UINT32 UseInstanceLocatorFlag = 0x04;
    static const UINT32 UseOptimalSchemaEncodingFlag = 0x08;
    static const UINT32 UseOptimalPayloadEncodingFlag = 0x10;
    static const UINT32 UseFileGlobalEnvironmentFlag = 0x20;
    static const UINT32 UseSchemaReferenceFlag = 0x40;
    static const UINT32 UseDeduplicationFlag = 0x80;
    static const UINT32 UseGranularResourceSplittingFlag = 0x100;
    static const UINT32 SplitLanguageVariantsFlag = 0x200;

    static const UINT32 Windows8ConfigurationFlags = 0;

    static const UINT32 Windows8_1ConfigurationFlags = (UseDataItemLocatorFlag | UseFileInfoLocatorFlag | UseInstanceLocatorFlag);

    static const UINT32 UniversalConfigurationFlags =
        (UseDataItemLocatorFlag | UseFileInfoLocatorFlag | UseInstanceLocatorFlag | UseOptimalSchemaEncodingFlag |
         UseOptimalPayloadEncodingFlag | UseFileGlobalEnvironmentFlag | UseDeduplicationFlag);
    static const UINT32 UniversalConfigurationFlagsWithSchemaReference =
        (UseDataItemLocatorFlag | UseFileInfoLocatorFlag | UseInstanceLocatorFlag | UseOptimalSchemaEncodingFlag |
         UseOptimalPayloadEncodingFlag | UseFileGlobalEnvironmentFlag | UseSchemaReferenceFlag | UseDeduplicationFlag);

    DEFFILE_MAGIC GetFileMagicNumber() const { return m_magic; }
    UINT32 GetFlags() const { return m_flags; }
    void SetFlags(UINT32 flags) { m_flags = flags; }

    bool UseDataItemLocator() const { return ((m_flags & UseDataItemLocatorFlag) != 0); }
    bool UseFileInfoLocator() const { return ((m_flags & UseFileInfoLocatorFlag) != 0); }
    bool UseInstanceLocator() const { return ((m_flags & UseInstanceLocatorFlag) != 0); }
    bool UseOptimalSchemaEncoding() const { return ((m_flags & UseOptimalSchemaEncodingFlag) != 0); }
    bool UseOptimalPayloadEncoding() const { return ((m_flags & UseOptimalPayloadEncodingFlag) != 0); }
    bool UseFileGlobalEnvironment() const { return ((m_flags & UseFileGlobalEnvironmentFlag) != 0); }
    bool UseSchemaReference() const { return ((m_flags & UseSchemaReferenceFlag) != 0); }
    bool UseDeduplication() const { return ((m_flags & UseDeduplicationFlag) != 0); }
    bool UseGranularResourceSplitting() const { return ((m_flags & UseGranularResourceSplittingFlag) != 0); }
    bool SplitLanguageVariants() const { return ((m_flags & SplitLanguageVariantsFlag) != 0); }

protected:
    MrmBuildConfiguration(_In_ DEFFILE_MAGIC fileMagicNumber, _In_ UINT32 flags) : m_magic(fileMagicNumber), m_flags(flags) {}

private:
    DEFFILE_MAGIC m_magic;
    UINT32 m_flags;
};

class IQualifierType : public DefObject
{
public:
    virtual ~IQualifierType() {}
    // All "Validate" methods report details is pStatus if the return value is false,
    // typically one of DEF_INVALID_ATTRIBUTE_VALUE or DEF_INVALID_COMPARISON_OPERATOR.
    // All implementations must handle NULL status parameter, so that callers who don't care
    // can just pass NULL.
    virtual HRESULT ValidateQualifierValue(_In_ PCWSTR pValue) const = 0;
    virtual HRESULT ValidateQualifier(_In_ const IQualifier* pQualifier) const = 0;

    virtual HRESULT ValidateOrMakeCompatibleQualifierValue(_In_ PCWSTR value, _Inout_ StringResult* compatibleValue) const = 0;

    virtual HRESULT ValidateQualifierComparison(_In_ Atom qualifierName, _In_ ICondition::ConditionOperator op, _In_ PCWSTR pQualifierValue)
        const = 0;

    virtual HRESULT Evaluate(_In_ const IQualifier* pQualifier, _In_ PCWSTR pAttributeValue, _Out_ double* score) const = 0;

    virtual HRESULT Compare(_In_ const IQualifier* pQualifier1, _In_ const IQualifier* pQualifier2, _Out_ DEFCOMPARISON* result) const = 0;

    virtual HRESULT CompareForValue(
        _In_ const IQualifier* pQualifier1,
        _In_ const IQualifier* pQualifier2,
        _In_ PCWSTR pValue,
        _Out_ DEFCOMPARISON* result) const = 0;
};

class IBuildQualifierType : public IQualifierType
{
public:
    static const PCWSTR DefaultPackagingAffinity;

    typedef enum _PackagingFlags
    {
        PackagingBlockResourcePackage = 0x0000, // Candidate must go to main package by default
        PackagingAllowResourcePackage = 0x0001, // Candidate is allowed to go to a resource package
        PackagingResourcePackageMask = 0x0001,

        PackagingDoNotReportQualifier = 0x0000, // Qualifier is not reported in mapping files
        PackagingReportQualifier = 0x0002, // Qualifier is reported in mapping files
        PackagingReportQualifierMask = 0x0002,

        PackagingAllFallbackToMainPackage = 0x0000, // All fallback resources (score as fallback > 0) go to main package
        PackagingPerfectFallbackToMainPackage = 0x0004, // Only perfect fallback (score as fallback == 1.0) go to main package
        PackagingFallbackHandlingMask = 0x0004,

        PackagingDefaultFlags = PackagingBlockResourcePackage | PackagingDoNotReportQualifier | PackagingAllFallbackToMainPackage
    } PackagingFlags;

    // Determines default packaging flags for a qualifier type.
    // If the default flags do not include "AllowResourcePackage",
    // then automatic resource packaging will fail if the
    // user attempts to use the qualifier.
    virtual PackagingFlags GetDefaultPackagingFlags() const = 0;

    // Determines default packaging behavior for auto resource packages and
    // for reporting of qualifiers in mapping files for a specific
    // qualifier operation (e.g. "lang-en-us" or "scale-80"
    virtual HRESULT GetPackagingInfo(
        _In_ const IQualifier* pQualifier,
        _In_ UINT32 buildConfiguration,
        _In_reads_(numAutoPackageValues) PCWSTR* ppAutoPackageValues,
        _In_ size_t numAutoPackageValues,
        _Out_ PackagingFlags* pFlagsOut,
        _Inout_ StringResult* pAffinityOut) const = 0;
};

DEFINE_ENUM_FLAG_OPERATORS(IBuildQualifierType::PackagingFlags);

class QualifierTypeBase : public IBuildQualifierType
{
public:
    typedef enum _QualifierTypeFlags
    {
        ListValuesNotAllowed = 0x0000, // Candidate must go to main package by default
        ListValuesAllowed = 0x0001, // Candidate is allowed to go to a resource package
        ListValuesMask = 0x0001,

        EmptyValuesAllowed = 0x0000,
        EmptyValuesNotAllowed = 0x0002,
        EmptyValuesMask = 0x0002,

        OptionalValueQualifierTypeFlags = ListValuesNotAllowed | EmptyValuesAllowed,
        RequiredValueQualifierTypeFlags = ListValuesNotAllowed | EmptyValuesNotAllowed,

        OptionalListQualifierTypeFlags = ListValuesAllowed | EmptyValuesAllowed,
        RequiredListQualifierTypeFlags = ListValuesAllowed | EmptyValuesNotAllowed,

        QualifierTypeDefaultFlags = ListValuesNotAllowed | EmptyValuesAllowed,
    } QualifierTypeFlags;

    virtual ~QualifierTypeBase() {}

    virtual HRESULT ValidateQualifierValue(_In_ PCWSTR pValue) const;

    virtual HRESULT ValidateQualifier(_In_ const IQualifier* pQualifier) const;

    virtual HRESULT ValidateOrMakeCompatibleQualifierValue(_In_ PCWSTR value, _Inout_ StringResult* compatibleValue) const;

    virtual HRESULT ValidateQualifierComparison(_In_ Atom qualifierName, _In_ ICondition::ConditionOperator op, _In_ PCWSTR pQualifierValue)
        const;

    virtual HRESULT Evaluate(_In_ const IQualifier* pQualifier, _In_ PCWSTR pValue, _Out_ double* score) const;

    virtual HRESULT Compare(_In_ const IQualifier* pQualifier1, _In_ const IQualifier* pQualifier2, _Out_ DEFCOMPARISON* result) const;

    virtual HRESULT CompareForValue(
        _In_ const IQualifier* pQualifier1,
        _In_ const IQualifier* pQualifier2,
        _In_ PCWSTR pValue,
        _Out_ DEFCOMPARISON* result) const;

    virtual PackagingFlags GetDefaultPackagingFlags() const;

    virtual HRESULT GetPackagingInfo(
        _In_ const IQualifier* pQualifier,
        _In_ UINT32 buildConfiguration,
        _In_reads_(numAutoPackageValues) PCWSTR* ppAutoPackageValues,
        _In_ size_t numAutoPackageValues,
        _Out_ PackagingFlags* pFlagsOut,
        _Inout_ StringResult* pAffinityOut) const;

    virtual int GetMaxQualifierEntries() const;

protected:
    static const int MaxItemsInList = 10;

    // Any single value in the list yields a score in the range 0.0-1.0 individually,
    // but a list can have up to 10 values.  So we map each of the qualifiers into
    // 1/10th of our available range, with the first in the list getting 0.91-1.0,
    // second getting 0.81-0.90 and so forth.
    static double ScoreInPosition(_In_ unsigned position, _In_ double score)
    {
        DEF_ASSERT(position < MaxItemsInList);

        return (0.9 - (position * 0.1)) + (score / 10.0);
    }

    QualifierTypeFlags m_flags;

    bool AreListValuesAllowed() const { return (m_flags & ListValuesMask) == ListValuesAllowed; }

    bool AreEmptyValuesAllowed() const { return (m_flags & EmptyValuesMask) == EmptyValuesAllowed; }

    QualifierTypeBase(_In_ QualifierTypeFlags flags) : m_flags(flags) {}

    virtual HRESULT ValidateSingleQualifierValue(_In_ PCWSTR pValue) const = 0;

    virtual HRESULT ValidateOrMakeCompatibleSingleQualifierValue(_In_ PCWSTR value, _Inout_ StringResult* compatibleValue) const;

    virtual double EvaluateSingleQualifierValue(_In_ PCWSTR valueOnAsset, _In_ PCWSTR valueFromProvider) const;

    // Compare does all standard comparisons (e.g. priority) and
    // only calls InnerCompare to break ties.
    virtual HRESULT InnerCompare(_In_ const IQualifier* pQualifier1, _In_ const IQualifier* pQualifier2, _Out_ DEFCOMPARISON* result) const;

    typedef enum
    {
        StringQualifier = 0,
        NumericQualifier = 1
    } QualifierFormat;

    _Success_(return ) static bool IsValidValue(_In_ PCWSTR pValue, _In_ QualifierFormat format, _In_ bool bAllowList);
};

DEFINE_ENUM_FLAG_OPERATORS(QualifierTypeBase::QualifierTypeFlags);

class StringIdentifierQualifierType : public QualifierTypeBase
{
public:
    _Pre_satisfies_(maxAllowedLength > 0) static HRESULT
        CreateInstance(_In_ size_t maxAllowedLength, _In_ QualifierTypeFlags flags, _Outptr_ StringIdentifierQualifierType** type);

    virtual ~StringIdentifierQualifierType() {}

    static bool IsValidStringIdentifier(_In_ PCWSTR pValue, _In_ size_t maxSize);

protected:
    StringIdentifierQualifierType(_In_ size_t maxAllowedLength, _In_ QualifierTypeFlags flags) :
        QualifierTypeBase(flags), m_maxAllowedLength(maxAllowedLength)
    {}

    size_t m_maxAllowedLength;

    virtual HRESULT ValidateSingleQualifierValue(_In_ PCWSTR pValue) const;
};

class EnumerationQualifierType : public QualifierTypeBase
{
public:
    static HRESULT CreateInstance(
        _In_reads_(numAllowedValues) const PCWSTR* pAllowedValues,
        _In_ size_t numAllowedValues,
        _Outptr_ EnumerationQualifierType** type);

    virtual ~EnumerationQualifierType() {}

    virtual HRESULT Evaluate(_In_ const IQualifier* pQualifier, _In_ PCWSTR pszProviderValue, _Out_ double* score) const;

protected:
    EnumerationQualifierType(_In_reads_(numAllowedValues) const PCWSTR* pAllowedValues, _In_ size_t numAllowedValues) :
        QualifierTypeBase(ListValuesNotAllowed | EmptyValuesNotAllowed),
        m_pAllowedValues(pAllowedValues),
        m_numAllowedValues(numAllowedValues)
    {}

    HRESULT ValidateSingleQualifierValue(_In_ PCWSTR pValue) const;

    _Field_size_(m_numAllowedValues) const PCWSTR* m_pAllowedValues;
    size_t m_numAllowedValues;
};

class IntegerQualifierType : public QualifierTypeBase
{
public:
    _Pre_satisfies_(maxAllowedValue > minAllowedValue) static HRESULT CreateInstance(
        _In_ int minAllowedValue,
        _In_ int maxAllowedValue,
        _In_ bool allowEmptyProviderValue,
        _Outptr_ IntegerQualifierType** type);

    virtual ~IntegerQualifierType() {}

    virtual HRESULT Evaluate(_In_ const IQualifier* pQualifier, _In_ PCWSTR pszProviderValue, _Out_ double* score) const;

    HRESULT
    CompareForValue(_In_ const IQualifier* pQualifier1, _In_ const IQualifier* pQualifier2, _In_ PCWSTR pValue, _Out_ DEFCOMPARISON* result)
        const;

protected:
    IntegerQualifierType(_In_ int minAllowedValue, _In_ int maxAllowedValue, _In_ bool allowEmptyProviderValue) :
        QualifierTypeBase(ListValuesNotAllowed | EmptyValuesNotAllowed),
        m_minAllowedValue(minAllowedValue),
        m_maxAllowedValue(maxAllowedValue),
        m_allowEmptyProviderValue(allowEmptyProviderValue)
    {}

    int m_minAllowedValue;
    int m_maxAllowedValue;
    bool m_allowEmptyProviderValue;

    HRESULT ValidateSingleQualifierValue(_In_ PCWSTR pValue) const;

    HRESULT InnerCompare(_In_ const IQualifier* pQualifier1, _In_ const IQualifier* pQualifier2, _Out_ DEFCOMPARISON* result) const;
};

class IProviderDataSources;

class IQualifierValueProvider : public DefObject
{
public:
    virtual ~IQualifierValueProvider() {}

    virtual HRESULT GetQualifierValue(_In_ Atom attr, _Inout_ const IProviderDataSources* pData, _Inout_ StringResult* pResultOut)
        const = 0;

    virtual bool IsPersistentQualifier() const = 0;

    virtual HRESULT SetPersistentQualifierValue(
        _In_ PCWSTR qualifierName,
        _In_ PCWSTR qualifierValue,
        _Inout_opt_ const IProviderDataSources* dataSources) const = 0;
};

class QualifierValueProviderBase : public IQualifierValueProvider
{
public:
    virtual ~QualifierValueProviderBase() {}

    virtual bool IsPersistentQualifier() const override;

    virtual bool AllowPersistentEmptyStringValue() const;

    virtual HRESULT SetPersistentQualifierValue(
        _In_ PCWSTR qualifierName,
        _In_ PCWSTR qualifierValue,
        _Inout_opt_ const IProviderDataSources* dataSources) const override;

    virtual HRESULT GetQualifierValue(_In_ Atom attr, _Inout_ const IProviderDataSources* pData, _Inout_ StringResult* pResultOut)
        const override final;

    virtual HRESULT GetQualifierValueInner(_In_ Atom attr, _Inout_ const IProviderDataSources* pData, _Inout_ StringResult* pResultOut)
        const = 0;

protected:
    QualifierValueProviderBase() : m_profile(nullptr), m_subKeyName(), m_qualifierKeyName() {}

    const CoreProfile* m_profile;
    StringResult m_subKeyName;
    StringResult m_qualifierKeyName;
};

class GenericQVProvider : public QualifierValueProviderBase
{
public:
    static HRESULT CreateInstance(_In_ PCWSTR pValue, _Outptr_ GenericQVProvider** provider);

    static HRESULT CreateInstance(_Outptr_ GenericQVProvider** provider) { return CreateInstance(L"", provider); }

    virtual ~GenericQVProvider();

    virtual HRESULT GetQualifierValueInner(_In_ Atom attr, _Inout_ const IProviderDataSources* pData, _Inout_ StringResult* pResultOut)
        const override;

protected:
    StringResult m_value;
};

class WindowsDisplayLanguageProvider : public QualifierValueProviderBase
{
public:
    static HRESULT CreateInstance(
        _In_ const CoreProfile* profile,
        _In_opt_ PCWSTR subKeyName,
        _In_opt_ PCWSTR qualifierKeyName,
        _Outptr_ WindowsDisplayLanguageProvider** provider);

    static HRESULT CreateInstance(_In_ const CoreProfile* profile, _Outptr_ WindowsDisplayLanguageProvider** provider)
    {
        return CreateInstance(profile, nullptr, nullptr, provider);
    }

    bool IsPersistentQualifier() const override;

    HRESULT GetQualifierValueInner(_In_ Atom /*attr*/, _Inout_ const IProviderDataSources* /*pData*/, _Inout_ StringResult* pResultOut)
        const override;

protected:
    WindowsDisplayLanguageProvider();
};

} // namespace Microsoft::Resources