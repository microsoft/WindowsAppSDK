// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

namespace Microsoft::Resources
{

/*!
 * Describes a single resource qualifier.
 */
struct ResourceQualifier
{
    /*!
     * Gets the name of the qualifier, specified as an Atom.
     * \return Atom
     */
    Atom name;

    /*!
     * Gets the type of the qualifier, specified as an Atom.
     * \return Atom
     */
    Atom qualifierType;

    /*!
     * Gets the priority of the qualifier as an integer
     * in the range 0-1000.
     *
     * \return int
     * Returns an integer in the range 0-1000 which
     * represents the default priority of this qualifier
     * relative to other resource qualifiers defined
     * in the Environment.
     */
    int defaultRuntimePriority = 0;
    int defaultBuildPriority = 0;

    static const int MinPriority = MRM_MIN_QUALIFIER_PRIORITY;
    static const int MaxPriority = MRM_MAX_QUALIFIER_PRIORITY;
};

class IBuildQualifierType;

/*!
 * The QualifierBuildInfo struct encapsulates both runtime and build-time information
 * about a single attribute.
 */
struct QualifierBuildInfo
{
    ResourceQualifier qualifier; //!< Name, type and default priority
    PCWSTR pToken; //!< Token used by IBC to identify resources that depend on this qualifier
    PCWSTR pDefaultValue; //!< Default value for this qualifier
    bool alwaysMatches; //!< True if comparing this qualifier always yields a score > 0.0
    bool readOnlyForApp; //!< True if the app is not allowed to override this qualifier
    const IBuildQualifierType* pQualifierType; //!< The type of the qualifier, can be used for validation.
};

class IEnvironmentVersionInfo;

/*!
 * An IEnvironment is a named and versioned description of a specific
 * runtime environment in which a particular set of MRM content is
 * expected to be consumed.
 *
 * It defines the context attributes available in the runtime, as
 * well as the supported condition operators and the names of the
 * available implementations of the various types used by the modern
 * resource runtime itself.
 *
 * For Windows 8 we will support a single known runtime named "Windows"
 * with major version 8.0.  We anticipate adding ways to define new
 * Environments in the future, but Windows 8 will not support an
 * in-file representation of an Environment.
 */
class IEnvironment : public DefObject
{
public:
    virtual ~IEnvironment() {}

    virtual AtomPoolGroup* GetAtoms() const = 0;

    virtual PCWSTR GetUniqueName() const = 0;
    virtual PCWSTR GetDisplayName() const = 0;

    virtual const IEnvironmentVersionInfo* GetVersionInfo() const = 0;

    virtual const IAtomPool* GetQualifierTypeNames() const = 0;
    virtual const IAtomPool* GetQualifierNames() const = 0;
    virtual const IAtomPool* GetItemTypeNames() const = 0;
    virtual const IAtomPool* GetResourceValueTypeNames() const = 0;
    virtual const IAtomPool* GetResourceValueLocatorNames() const = 0;
    virtual const IAtomPool* GetConditionOperatorNames() const = 0;

    virtual HRESULT GetQualifier(_In_ PCWSTR pQualifierName, _Out_ ResourceQualifier* pQualifierRtrn) const = 0;

    virtual HRESULT GetQualifier(_In_ int qualifierIndex, _Out_ ResourceQualifier* pQualifierRtrn) const = 0;

    virtual HRESULT GetQualifier(_In_ Atom name, _Out_ ResourceQualifier* pQualifierRtrn) const = 0;

    virtual const ENVIRONMENT_DESCRIPTION* GetEnvironmentDescription() const = 0;
    virtual const QUALIFIER_INFO* GetQualifierInfo() const = 0;

    virtual HRESULT GetQualifierInfo(_In_ INT32 evIndex, _Outptr_ const QUALIFIER_INFO** ppQualifierInfo) const = 0;
};

class MrmEnvironment : public IEnvironment
{
protected:
    const ENVIRONMENT_INITIALIZER* m_pEnvironmentInitializer;
    const QUALIFIER_INFO* m_pQualifierInfo;

    AtomPoolGroup* m_pAtoms;
    IAtomPool* m_pQualifierTypeNames;
    IAtomPool* m_pQualifierNames;
    IAtomPool* m_pItemTypeNames;
    IAtomPool* m_pResourceValueTypeNames;
    IAtomPool* m_pResourceValueLocatorNames;
    IAtomPool* m_pConditionOperatorNames;

    int m_numQualifiers;

    _Field_size_(m_numQualifiers) ResourceQualifier* m_pQualifiers;

    IEnvironmentVersionInfo* m_pVersion;

    MrmEnvironment() :
        m_pEnvironmentInitializer(nullptr),
        m_pQualifierInfo(nullptr),
        m_pAtoms(nullptr),
        m_pQualifierTypeNames(nullptr),
        m_pQualifierNames(nullptr),
        m_pItemTypeNames(nullptr),
        m_pResourceValueTypeNames(nullptr),
        m_pResourceValueLocatorNames(nullptr),
        m_pConditionOperatorNames(nullptr),
        m_numQualifiers(0),
        m_pQualifiers(nullptr),
        m_pVersion(nullptr)
    {}

    HRESULT Init(_In_ AtomPoolGroup* pAtoms, _In_ const ENVIRONMENT_INITIALIZER* pInitializer, _In_ int major, _In_ int minor);

    static HRESULT ChooseVersion(
        _In_ const ENVIRONMENT_DESCRIPTION* pEnvironmentDescription,
        _In_ int wantMajor,
        _In_ int wantMinor,
        _Out_ const MRMFILE_ENVIRONMENT_VERSION_INFO** info);

    static HRESULT GetQualifierInfo(
        _In_ const ENVIRONMENT_INITIALIZER* pEnvironmentInitializer,
        _In_ const MRMFILE_ENVIRONMENT_VERSION_INFO* pVersion,
        _Out_ const QUALIFIER_INFO** info);

    typedef enum
    {
        Environment_QualifierTypeNames = 1,
        Environment_QualifierNames = 2,
        Environment_ItemTypeNames = 3,
        Environment_ResourceValueTypeNames = 4,
        Environment_ResourceValueLocatorNames = 5,
        Environment_ConditionOperatorNames = 6
    } EnvironmentNames;

    static HRESULT CreateNames(
        _In_ const MRMFILE_ENVIRONMENT_VERSION_INFO* pVersion,
        _In_ const QUALIFIER_INFO* pQualifierInfo,
        _In_ EnvironmentNames which,
        _In_ AtomPoolGroup* pAtoms,
        _Outptr_opt_result_maybenull_ IAtomPool** pPoolOut);

    static HRESULT CreateQualifiers(
        _In_ const MRMFILE_ENVIRONMENT_VERSION_INFO* pVersion,
        _In_ const QUALIFIER_INFO* pQualifierInfo,
        _Inout_ const IAtomPool* pQualifierNames,
        _Inout_ const IAtomPool* pQualifierTypeNames,
        _Outptr_result_buffer_maybenull_(*pNumQualifiersOut) ResourceQualifier** ppQualifiersOut,
        _Out_ int* pNumQualifiersOut);

    static HRESULT CreateVersion(
        _In_ const MRMFILE_ENVIRONMENT_VERSION_INFO* pVersion,
        _Outptr_result_maybenull_ IEnvironmentVersionInfo** ppEnvironmentOut);

    static HRESULT ComputeEnvironmentVersionInfo(
        _In_ const IEnvironment* pEnvironment,
        _In_ int majorVersion,
        _In_ int minorVersion,
        _Out_ IEnvironmentVersionInfo** info);

public:
    // There's no extension model for resource value type or resource locater type, so they must
    // be the same across all.
    typedef enum
    {
        ResourceValueType_Utf16String = 0,
        ResourceValueType_Utf16Path = 1,
        ResourceValueType_EmbeddedData = 2,
        ResourceValueType_AsciiString = 3,
        ResourceValueType_Utf8String = 4,
        ResourceValueType_AsciiPath = 5,
        ResourceValueType_Utf8Path = 6,
        ResourceValueType_Count
    } ResourceValueType;

    typedef enum
    {
        ResourceItemType_String = 0,
        ResourceItemType_Path = 1,
        ResourceItemType_EmbeddedData = 2,
        ResourceItemType_Resw = 3,
        ResourceItemType_ResJson = 4,
        ResourceItemType_ResFile = 5,
        ResourceItemType_PriFile = 6,
        ResourceItemType_PriInfo = 7,
        ResourceItemType_Count
    } ResourceItemType;

    static inline DEFSTRING_ENCODING MapResourceValueTypeToEncoding(_In_ ResourceValueType resourceType)
    {
        DEFSTRING_ENCODING stringEncoding = DEFSTRING_ENCODING_UTF16;

        if (resourceType == ResourceValueType_AsciiString || resourceType == ResourceValueType_AsciiPath)
        {
            stringEncoding = DEFSTRING_ENCODING_ASCII;
        }
        else if (resourceType == ResourceValueType_Utf8String || resourceType == ResourceValueType_Utf8Path)
        {
            stringEncoding = DEFSTRING_ENCODING_UTF8;
        }

        return stringEncoding;
    }

    static const PCWSTR ResourceItemTypeNames[];
    static const int NumResourceItemTypes = ResourceItemType_Count;

    static const PCWSTR ResourceValueTypeNames[];
    static const int NumResourceValueTypes = ResourceValueType_Count;

    static inline HRESULT GetNameForResourceValueType(_In_ ResourceValueType type, _Inout_ StringResult* pString)
    {
        return pString->SetRef(ResourceValueTypeNames[static_cast<int>(type)]);
    }

    static HRESULT GetDefaultItemTypeForValueType(_In_ ResourceValueType rvTypeIn, _Out_ ResourceItemType* pItemTypeOut);

    typedef enum
    {
        ResourceValueLocatorType_Internal = 0,
        ResourceValueLocatorType_DataItemsSection = 1,
        ResourceValueLocatorType_FileList = 2,
        ResourceValueLocatorType_Count
    } ResourceValueLocatorType;

    static const PCWSTR ResourceValueLocatorNames[];
    static const int NumResourceValueLocators = ResourceValueLocatorType_Count;

    static HRESULT CreateInstance(
        _In_ AtomPoolGroup* pAtoms,
        _In_ const ENVIRONMENT_INITIALIZER* pInitializer,
        _In_ int major,
        _In_ int minor,
        _Outptr_ MrmEnvironment** env);

    static HRESULT CreateInstance(
        _In_ AtomPoolGroup* pAtoms,
        _In_ const ENVIRONMENT_INITIALIZER* pInitializer,
        _In_ int index,
        _Outptr_ MrmEnvironment** env);

    static HRESULT CreateInstance(
        _In_ AtomPoolGroup* pAtoms,
        _In_ const ENVIRONMENT_INITIALIZER* pInitializer,
        _Outptr_ MrmEnvironment** env)
    {
        return CreateInstance(pAtoms, pInitializer, 0, env);
    }

    virtual ~MrmEnvironment();

    AtomPoolGroup* GetAtoms() const { return m_pAtoms; }

    PCWSTR GetUniqueName() const { return m_pEnvironmentInitializer->pEnvironmentDescription->pUniqueName; }
    PCWSTR GetDisplayName() const { return m_pEnvironmentInitializer->pEnvironmentDescription->pSimpleName; }

    const IEnvironmentVersionInfo* GetVersionInfo() const { return m_pVersion; }

    const IAtomPool* GetQualifierTypeNames() const { return m_pQualifierTypeNames; }
    const IAtomPool* GetQualifierNames() const { return m_pQualifierNames; }
    const IAtomPool* GetItemTypeNames() const { return m_pItemTypeNames; }
    const IAtomPool* GetResourceValueTypeNames() const { return m_pResourceValueTypeNames; }
    const IAtomPool* GetResourceValueLocatorNames() const { return m_pResourceValueLocatorNames; }
    const IAtomPool* GetConditionOperatorNames() const { return m_pConditionOperatorNames; }

    static HRESULT GetResourceItemType(_In_ PCWSTR pTypeName, _Out_ ResourceItemType* type);

    static HRESULT GetResourceValueType(_In_ PCWSTR pTypeName, _Out_ ResourceValueType* type);

    static HRESULT GetStringForResourceValueType(_In_ ResourceValueType rvType, _Inout_ StringResult* pStringOut);

    static HRESULT GetExternalStringForResourceValueType(_In_ ResourceValueType actualType, _Inout_ StringResult* externalString);

    static HRESULT GetExternalResourceValueType(_In_ ResourceValueType actualType, _Inout_ ResourceValueType* externalType);

    static ResourceValueType GetResourceValueTypeForAtom(_In_ const Atom& valueTypeAtom)
    {
        return static_cast<ResourceValueType>(valueTypeAtom.GetIndex());
    }

    static bool IsStringResourceValueType(_In_ ResourceValueType type)
    {
        return (
            (type == ResourceValueType_Utf16String) || (type == ResourceValueType_Utf8String) || (type == ResourceValueType_AsciiString));
    }

    static bool IsPathResourceValueType(_In_ ResourceValueType type)
    {
        return ((type == ResourceValueType_Utf16Path) || (type == ResourceValueType_Utf8Path) || (type == ResourceValueType_AsciiPath));
    }

    static bool IsAsciiResourceValueType(_In_ ResourceValueType type)
    {
        return ((type == ResourceValueType_AsciiString) || (type == ResourceValueType_AsciiPath));
    }

    static bool IsUtf8ResourceValueType(_In_ ResourceValueType type)
    {
        return ((type == ResourceValueType_Utf8String) || (type == ResourceValueType_Utf8Path));
    }

    static bool IsUtf16ResourceValueType(_In_ ResourceValueType type)
    {
        return ((type == ResourceValueType_Utf16String) || (type == ResourceValueType_Utf16Path));
    }

    static bool IsBinaryResourceValueType(_In_ ResourceValueType type) { return (type == ResourceValueType_EmbeddedData); }

    static bool ResourceValueTypesAreCompatible(_In_ ResourceValueType rvt1, _In_ ResourceValueType rvt2)
    {
        return (rvt1 == rvt2) || (IsPathResourceValueType(rvt1) && IsPathResourceValueType(rvt2)) ||
               (IsStringResourceValueType(rvt1) && IsStringResourceValueType(rvt2)) ||
               (IsBinaryResourceValueType(rvt1) && IsBinaryResourceValueType(rvt2));
    }

    static ResourceValueType ConvertToBestValueType(_In_ ResourceValueType originalType, _In_ DEFSTRING_ENCODING bestEncoding)
    {
        ResourceValueType bestValueType = originalType;

        if (IsStringResourceValueType(originalType))
        {
            if (bestEncoding == DEFSTRING_ENCODING_ASCII)
            {
                bestValueType = ResourceValueType_AsciiString;
            }
            else if (bestEncoding == DEFSTRING_ENCODING_UTF16)
            {
                bestValueType = ResourceValueType_Utf16String;
            }
            else
            {
                bestValueType = ResourceValueType_Utf8String;
            }
        }
        else if (IsPathResourceValueType(originalType))
        {
            if (bestEncoding == DEFSTRING_ENCODING_ASCII)
            {
                bestValueType = ResourceValueType_AsciiPath;
            }
            else if (bestEncoding == DEFSTRING_ENCODING_UTF16)
            {
                bestValueType = ResourceValueType_Utf16Path;
            }
            else
            {
                bestValueType = ResourceValueType_Utf8Path;
            }
        }

        return bestValueType;
    }

    HRESULT GetQualifier(_In_ PCWSTR pQualifierName, _Out_ ResourceQualifier* pQualifierOut) const;

    HRESULT GetQualifier(_In_ int qualifierIndex, _Out_ ResourceQualifier* pQualifierOut) const;

    HRESULT GetQualifier(_In_ Atom qualifierName, _Out_ ResourceQualifier* pQualifierOut) const;

    const ENVIRONMENT_DESCRIPTION* GetEnvironmentDescription() const { return m_pEnvironmentInitializer->pEnvironmentDescription; }
    const QUALIFIER_INFO* GetQualifierInfo() const { return m_pQualifierInfo; }

    HRESULT GetQualifierInfo(_In_ INT32 evIndex, _Outptr_ const QUALIFIER_INFO** ppQualifierInfoOut) const;

    static const int DefaultVersionIndex = 0;

    static HRESULT FindInfoForVersion(
        _In_ const ENVIRONMENT_DESCRIPTION* pDescription,
        _In_ int major,
        _In_ int minor,
        _Out_opt_ const MRMFILE_ENVIRONMENT_VERSION_INFO** ppInfoOut,
        _Inout_opt_ StringResult* pUniqueNameOut,
        _Inout_opt_ StringResult* pSimpleNameOut);

    static HRESULT FindInfoForVersion(
        _In_ const ENVIRONMENT_DESCRIPTION* environmentDescription,
        _In_ int index,
        _Out_opt_ const MRMFILE_ENVIRONMENT_VERSION_INFO** versionInfo,
        _Inout_opt_ StringResult* uniqueName,
        _Inout_opt_ StringResult* simpleName);

    static HRESULT FindInfoForCurrentVersion(
        _In_ const ENVIRONMENT_DESCRIPTION* pDescription,
        _Out_opt_ const MRMFILE_ENVIRONMENT_VERSION_INFO** pInfoOut,
        _Inout_opt_ StringResult* pUniqueNameOut,
        _Inout_opt_ StringResult* pSimpleNameOut);

    _Success_(return == true)
    static bool TryFindInfoByChecksum(
        _In_ const ENVIRONMENT_DESCRIPTION* description,
        _In_opt_ DefChecksum::Checksum checksum,
        _Out_opt_ const MRMFILE_ENVIRONMENT_VERSION_INFO** versionOut,
        _Inout_opt_ StringResult* uniqueNameOut,
        _Inout_opt_ StringResult* simpleNameOut);
};

/*!
 * An IEnvironmentVersionInfo contains a checksum and item counts that can be used
 * to verify compatibility between two versions of the same Environment.
 */
class IEnvironmentVersionInfo : public DefObject
{
public:
    /*!
     * Gets the major version of this Environment description.
     * \return int
     */
    virtual UINT16 GetMajorVersion() const = 0;

    /*!
     * Gets the minor version of this Environment description.
     * \return int
     */
    virtual UINT16 GetMinorVersion() const = 0;

    /*!
     * Gets the checksum of a specific version of an Environment description.
     * The version checksum is computed from all names and descriptions present
     * in a specific version of the Environment.
     *
     * \return DEF_CHECKSUM
     */
    virtual DEF_CHECKSUM GetVersionChecksum() const = 0;

    /*!
     * Gets the number of qualifier types present in the specified version
     * of the Environment.
     * \return int
     */
    virtual int GetNumQualifierTypes() const = 0;

    /*!
     * Gets the number of qualifiers present in the specified version
     * of the Environment.
     * \return int
     */
    virtual int GetNumQualifiers() const = 0;

    /*!
     * Gets the number of item types present in the specified version
     * of the Environment.
     * \return int
     */
    virtual int GetNumItemTypes() const = 0;

    /*!
     * Gets the number of resource value types present in the specified version
     * of the Environment.
     * \return int
     */
    virtual int GetNumResourceValueTypes() const = 0;

    /*!
     * Gets the number of resource value locators present in the specified version
     * of the Environment.
     * \return int
     */
    virtual int GetNumResourceValueLocators() const = 0;

    /*!
     * Gets the number of condition operators present in the specified version
     * of the Environment.
     * \return int
     */
    virtual int GetNumConditionOperators() const = 0;

    virtual void GetVersionInfo(_Out_ MRMFILE_ENVIRONMENT_VERSION_INFO* pVersionInfoOut) const = 0;

    virtual ~IEnvironmentVersionInfo() {};
};

/*!
 * Simple projection of MRMFILE_ENVIRONMENT_VERSION_INFO file data structure to the
 * IEnvironmentVersionInfo interface.
 */

class EnvironmentVersionInfo : public IEnvironmentVersionInfo
{
protected:
    MRMFILE_ENVIRONMENT_VERSION_INFO m_version{};

    EnvironmentVersionInfo(_In_opt_ const MRMFILE_ENVIRONMENT_VERSION_INFO* version)
    {
        if (version != nullptr)
        {
            m_version = *version;
        }
    }

public:
    static HRESULT CreateInstance(_In_ const MRMFILE_ENVIRONMENT_VERSION_INFO* pVersion, _Outptr_ EnvironmentVersionInfo** info);

    static HRESULT CreateInstance(_In_ const EnvironmentVersionInfo* cloneFrom, _Outptr_ EnvironmentVersionInfo** info);

    static HRESULT CreateEmpty(_Outptr_ EnvironmentVersionInfo** info);

    static HRESULT ComputeNew(
        _In_ const IEnvironment* pEnvironment,
        _In_opt_ const MRMFILE_ENVIRONMENT_VERSION_INFO* pDesiredVersionInfo,
        _Outptr_ EnvironmentVersionInfo** info);

    UINT16 GetMajorVersion() const { return m_version.major; }
    UINT16 GetMinorVersion() const { return m_version.minor; }

    DEF_CHECKSUM GetVersionChecksum() const { return m_version.checksum; }
    int GetNumQualifierTypes() const { return m_version.numQualifierTypes; }
    int GetNumQualifiers() const { return m_version.numQualifiers; }
    int GetNumItemTypes() const { return m_version.numItemTypes; }
    int GetNumResourceValueTypes() const { return m_version.numResourceValueTypes; }
    int GetNumResourceValueLocators() const { return m_version.numResourceValueLocators; }
    int GetNumConditionOperators() const { return m_version.numConditionOperators; }

    void GetVersionInfo(_Out_ MRMFILE_ENVIRONMENT_VERSION_INFO* pVersionInfoOut) const { *pVersionInfoOut = m_version; }

    void SetVersionInfo(_In_ const MRMFILE_ENVIRONMENT_VERSION_INFO* versionInfo) { m_version = *versionInfo; }
};

class EnvironmentReference : public IEnvironmentVersionInfo
{
protected:
    MRMFILE_ENVIRONMENT_REF m_ref{};

    EnvironmentReference() {}

    HRESULT Init(_In_ const IEnvironment* pEnvironment);

public:
    static HRESULT CreateInstance(_In_ const MRMFILE_ENVIRONMENT_REF* pFileRef, _Outptr_ EnvironmentReference** ref);

    static HRESULT CreateInstance(_In_ const IEnvironment* cloneFrom, _Outptr_ EnvironmentReference** ref);

    static HRESULT CreateInstance(_In_ const EnvironmentReference* cloneFrom, _Outptr_ EnvironmentReference** ref);

    bool CheckIsIdentical(_In_ const IEnvironment* pEnvironment) const;

    bool CheckIsIdentical(_In_ const EnvironmentReference* other) const { return (memcmp(other, &m_ref, sizeof(m_ref)) == 0); }

    bool CheckIsCompatible(_In_ const IEnvironment* pEnvironment) const;

    static bool CheckIsIdentical(
        _In_ PCWSTR wantName,
        _In_ const IEnvironmentVersionInfo* wantVersion,
        _In_ PCWSTR haveName,
        _In_ const IEnvironmentVersionInfo* haveVersion);

    static bool CheckIsCompatible(
        _In_ PCWSTR wantEnvironmentName,
        _In_ const IEnvironmentVersionInfo* wantEnvironment,
        _In_ const IEnvironment* haveEnvironment);

    PCWSTR GetUniqueName() const { return &m_ref.uniqueName[0]; }

    Atom::PoolIndex GetQualifierTypesPoolIndex() const { return m_ref.qualifierTypesPoolIndex; }
    Atom::PoolIndex GetQualifiersPoolIndex() const { return m_ref.qualifiersPoolIndex; }
    Atom::PoolIndex GetItemTypesPoolIndex() const { return m_ref.itemTypesPoolIndex; }
    Atom::PoolIndex GetResourceValueTypesPoolIndex() const { return m_ref.resourceValueTypesPoolIndex; }
    Atom::PoolIndex GetResourceValueLocatorsPoolIndex() const { return m_ref.resourceValueLocatorsPoolIndex; }
    Atom::PoolIndex GetConditionOperatorsPoolIndex() const { return m_ref.conditionOperatorsPoolIndex; }

    /*
     * IEnvironmentVersionInfo implementation
     */
    UINT16 GetMajorVersion() const { return m_ref.version.major; }
    UINT16 GetMinorVersion() const { return m_ref.version.minor; }

    DEF_CHECKSUM GetVersionChecksum() const { return m_ref.version.checksum; }

    int GetNumQualifierTypes() const { return m_ref.version.numQualifierTypes; }
    int GetNumQualifiers() const { return m_ref.version.numQualifiers; }
    int GetNumItemTypes() const { return m_ref.version.numItemTypes; }
    int GetNumResourceValueTypes() const { return m_ref.version.numResourceValueTypes; }
    int GetNumResourceValueLocators() const { return m_ref.version.numResourceValueLocators; }
    int GetNumConditionOperators() const { return m_ref.version.numConditionOperators; }

    void GetVersionInfo(_Out_ MRMFILE_ENVIRONMENT_VERSION_INFO* pVersionOut) const { *pVersionOut = m_ref.version; }
};

class RemapInfo;
class RemapUInt16;
class CoreProfile;

/*
 * Environment version checksum and comparison functions.
 */
HRESULT ComputeEnvironmentVersionChecksum(
    _In_ const IEnvironment* pEnvironment,
    _In_ const IEnvironmentVersionInfo* pVersion,
    _Out_ DefChecksum::Checksum* pChecksumOut);

HRESULT ComputeEnvironmentVersionInfo(
    _In_ const IEnvironment* pEnvironment,
    _In_opt_ const MRMFILE_ENVIRONMENT_VERSION_INFO* pDesiredVersionInfo,
    _Outptr_ IEnvironmentVersionInfo** info);

bool CheckEnvironmentVersionIsIdentical(_In_ const IEnvironmentVersionInfo* pVersion1, _In_ const IEnvironmentVersionInfo* pVersion2);

bool CheckEnvironmentVersionIsCompatible(_In_ const IEnvironment* pHaveEnvironment, _In_ const IEnvironmentVersionInfo* pWantVersion);

HRESULT ComputeEnvironmentPoolMappings(
    _In_ const IEnvironment* pHaveEnvironment,
    _In_ const IEnvironment* pWantEnvironment,
    _Inout_ RemapInfo* pPoolMappingsOut);

HRESULT ComputeEnvironmentPoolMappings(
    _In_ const IEnvironment* pHaveEnvironment,
    _In_ const IEnvironment* pWantEnvironment,
    _Inout_ RemapUInt16* pPoolMappingsOut);

HRESULT ComputeEnvironmentPoolMappings(
    _In_ const IEnvironment* pHaveEnvironment,
    _In_ const EnvironmentReference* pWantRef,
    _Inout_ RemapInfo* pPoolMappingsOut);

HRESULT ComputeWindowsEnvironmentVersionInfo(
    _In_ const IEnvironment* pEnvironment,
    _In_ int majorVersion,
    _In_ int minorVersion,
    _Outptr_ IEnvironmentVersionInfo** info);

class IEnvironmentCollection
{
protected:
    IEnvironmentCollection() {}
    virtual ~IEnvironmentCollection() {}

public:
    virtual const IEnvironment* GetDefaultEnvironment() const = 0;

    virtual int GetNumEnvironments() const = 0;

    virtual HRESULT GetEnvironment(_In_ int index, _Out_ const IEnvironment** env) const = 0;

    virtual bool TryFindEnvironment(_In_ const IEnvironmentVersionInfo* pRef, _Out_ const IEnvironment** pEnvironmentOut) const = 0;

    _Success_(return == true)
    virtual bool TryFindEnvironment(_In_ PCWSTR pUniqueName, _Out_ const IEnvironment** pEnvironmentOut) const = 0;

    virtual bool TryFindCompatibleEnvironment(
        _In_ PCWSTR pUniqueName,
        _In_ int major,
        _In_ int minor,
        _Out_ const IEnvironment** pEnvironmentOut) const = 0;

    virtual bool TryFindCompatibleEnvironment(
        _In_ const EnvironmentReference* pRef,
        _Out_ const IEnvironment** ppEnvironmentOut,
        _Inout_opt_ RemapInfo* pPoolMappingsOut) const = 0;

    virtual bool TryFindCompatibleEnvironment(
        _In_ const IEnvironment* pWantEnvironment,
        _Out_ const IEnvironment** ppEnvironmentOut,
        _Inout_opt_ RemapInfo* pPoolMappingsOut) const = 0;
};

class EnvironmentCollectionBase : public IEnvironmentCollection
{
protected:
    EnvironmentCollectionBase() {}
    virtual ~EnvironmentCollectionBase() {}

public:
    virtual bool TryFindEnvironment(
        _In_ const IEnvironmentVersionInfo* pRef,
        _Outptr_opt_result_maybenull_ const IEnvironment** pEnvironmentOut) const;

    virtual bool TryFindEnvironment(_In_ PCWSTR pUniqueName, _Outptr_opt_result_maybenull_ const IEnvironment** pEnvironmentOut) const;

    virtual bool TryFindCompatibleEnvironment(
        _In_ PCWSTR pUniqueName,
        _In_ int major,
        _In_ int minor,
        _Outptr_opt_result_maybenull_ const IEnvironment** pEnvironmentOut) const;

    virtual bool TryFindCompatibleEnvironment(
        _In_ const EnvironmentReference* pRef,
        _Outptr_opt_result_maybenull_ const IEnvironment** ppEnvironmentOut,
        _Inout_opt_ RemapInfo* pPoolMappingsOut) const;

    virtual bool TryFindCompatibleEnvironment(
        _In_ const IEnvironment* pWantEnvironment,
        _Outptr_opt_result_maybenull_ const IEnvironment** ppEnvironmentOut,
        _Inout_opt_ RemapInfo* pPoolMappingsOut) const;
};

class EnvironmentCollection : public EnvironmentCollectionBase, public DefObject
{
public:
    static HRESULT CreateInstance(
        _In_ const CoreProfile* pProfile,
        _In_ AtomPoolGroup* pAtoms,
        _In_ bool initDefaults,
        _Outptr_ EnvironmentCollection** collection);

    virtual ~EnvironmentCollection();

    int GetNumEnvironments() const { return m_pEnvironments->Count(); }
    virtual const IEnvironment* GetDefaultEnvironment() const override;

    HRESULT GetEnvironment(_In_ int index, _Out_ const IEnvironment** env) const { return m_pEnvironments->Get(index, env); }

    HRESULT GetOrAddEnvironment(_In_ const IEnvironment* pWantEnvironment, bool clone, _Out_ const IEnvironment** env);

    HRESULT AddDefaultEnvironments(_Inout_ const CoreProfile* pProfile);

protected:
    HRESULT Init(_In_ AtomPoolGroup* pAtoms);

    AtomPoolGroup* m_pAtoms{ nullptr };
    DynamicArray<const IEnvironment*>* m_pEnvironments{ nullptr };
};

class EnvironmentMapping : DefObject
{
public:
    using DefObject::operator delete;

    static HRESULT CreateInstance(
        _In_ const CoreProfile* profile,
        _In_ const IEnvironmentCollection* environments,
        _In_reads_bytes_(dataSizeInBytes) const void* rawData,
        _In_ size_t dataSizeInBytes,
        _Outptr_ EnvironmentMapping** mapping);

    virtual ~EnvironmentMapping();

    int GetCurrentMinorVersion() const { return m_header->currentMinorVersion; }
    DEF_CHECKSUM GetCurrentVersionChecksum() const { return m_header->currentEnvironmentChecksum; }
    DEF_CHECKSUM GetBaseVersionChecksum() const { return m_header->baseEnvironmentChecksum; }
    int GetNumNewQualifiers() const { return m_header->numNewQualifiers; }
    int GetNumQualifiers() const { return m_version.numQualifiers; }

    HRESULT GetEnvironmentInfo(_Inout_ StringResult* uniqueName, _Out_ EnvironmentVersionInfo* versionInfo) const;

    HRESULT GetQualifierInfo(
        _Out_ int* numMappedQualifiers,
        _Outptr_result_buffer_maybenull_(*numMappedQualifiers) const PCWSTR** mappedQualifierNames,
        _Outptr_result_buffer_maybenull_(*numMappedQualifiers) const Atom::SmallIndex** qualifierMappings) const;

private:
    EnvironmentMapping() : m_header(nullptr), m_qualifierMappings(nullptr), m_qualifierNames(nullptr), m_namesPool(nullptr) {}

    HRESULT Init(
        _In_ const CoreProfile* coreProfile,
        _In_ const IEnvironmentCollection* environments,
        _In_reads_bytes_(dataSizeInBytes) const void* rawData,
        _In_ size_t dataSizeInBytes);

    MRMFILE_ENVIRONMENT_VERSION_INFO m_version{};
    const MRMFILE_ENVIRONMENT_MAPPING_HEADER* m_header;
    _Field_size_(m_version.numQualifiers) Atom::SmallIndex* m_qualifierMappings;
    _Field_size_(m_version.numQualifiers) PCWSTR* m_qualifierNames;

    _Field_size_(m_header->namesPoolSizeInChars) PCWSTR m_namesPool;

    StringResult m_uniqueName;
};

} // namespace Microsoft::Resources