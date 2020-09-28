// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "mrm/readers/BaseFile.h"
#include "mrm/readers/RemapInfo.h"
#include "mrm/readers/SectionReaders.h"
#include "mrm/readers/HNames.h"
#include "mrm/readers/FileLists.h"
#include "mrm/common/file/MrmFiles.h"
#include "mrm/Checksums.h"
#include "mrm/MrmQualifiers.h"
#include "mrm/Collections.h"
#include "mrm/common/MrmProfileData.h"
#include "mrm/MrmEnvironment.h"

namespace Microsoft::Resources
{

class CoreProfile;
class IHierarchicalSchema;
class HierarchicalSchema;
class HierarchicalSchemaReference;

class ISchemaCollection : public DefObject
{
public:
    virtual ~ISchemaCollection() {}

    virtual int GetNumSchemas() const = 0;

    virtual HRESULT GetSchema(_In_ int index, _Out_ const IHierarchicalSchema** result) const = 0;

    virtual HRESULT GetPrimarySchema(_Out_ const IHierarchicalSchema** result) const = 0;

    virtual HRESULT GetSchemaById(_In_ PCWSTR pSchemaId, _Out_ const IHierarchicalSchema** result) const = 0;

    virtual HRESULT FindSchema(_In_ const HierarchicalSchemaReference* pRef, _Outptr_ const IHierarchicalSchema** ppSchemaOut) const = 0;
};

class SchemaCollectionSchemaWrapper : public ISchemaCollection
{
public:
    static HRESULT CreateInstance(
        _In_ const IHierarchicalSchema* schema,
        _In_ bool assumeOwnership,
        _Outptr_ SchemaCollectionSchemaWrapper** result);

    static HRESULT CreateInstance(_In_ const IHierarchicalSchema* schema, _Outptr_ SchemaCollectionSchemaWrapper** result);

    virtual ~SchemaCollectionSchemaWrapper();

    int GetNumSchemas() const { return 1; }

    HRESULT GetSchema(_In_ int index, _Out_ const IHierarchicalSchema** result) const;

    HRESULT GetPrimarySchema(_Out_ const IHierarchicalSchema** result) const
    {
        *result = m_schema;
        return S_OK;
    }

    HRESULT GetSchemaById(_In_ PCWSTR schemaId, _Out_ const IHierarchicalSchema** result) const;

    HRESULT FindSchema(_In_ const HierarchicalSchemaReference* wantRef, _Outptr_ const IHierarchicalSchema** matchingSchema) const;

protected:
    SchemaCollectionSchemaWrapper(_In_ const IHierarchicalSchema* schema, _In_ bool assumeOwnership);

    const IHierarchicalSchema* m_mySchema;
    const IHierarchicalSchema* m_schema;
};

class IResourceMapBase;
class ResourceMapBase;

class IResourceMapCollection : public DefObject
{
public:
    virtual int GetNumResourceMaps() const = 0;

    virtual HRESULT GetResourceMap(_In_ int index, _Out_ const IResourceMapBase** result) const = 0;

    virtual HRESULT GetPrimaryResourceMap(_Out_ const IResourceMapBase** result) const = 0;

    virtual HRESULT GetResourceMapById(_In_ PCWSTR pSchemaId, _Out_ const IResourceMapBase** result) const = 0;

    virtual bool TryFindResourceMap(_In_ const HierarchicalSchemaReference* pRef, __deref_opt_out_opt const IResourceMapBase** ppSchemaOut)
        const = 0;
};

class IHierarchicalSchemaVersionInfo : public DefObject
{
public:
    virtual UINT16 GetMajorVersion() const = 0;
    virtual UINT16 GetMinorVersion() const = 0;
    virtual DEF_CHECKSUM GetVersionChecksum() const = 0;

    virtual int GetNumScopes() const = 0;
    virtual int GetNumItems() const = 0;

    virtual ~IHierarchicalSchemaVersionInfo() {};
};

class IHierarchicalSchema;

class HierarchicalSchemaVersionInfo : public IHierarchicalSchemaVersionInfo
{
public:
    static HRESULT CreateInstance(
        _In_reads_bytes_(cbData) const void* pData,
        _In_ size_t cbData,
        _Outptr_ HierarchicalSchemaVersionInfo** result);

    static HRESULT CreateInstance(_In_ const MRMFILE_HSCHEMA_VERSION_INFO* pHeader, _Outptr_ HierarchicalSchemaVersionInfo** result);

    // IHierarchicalSchemaVersionInfo implementation
    UINT16 GetMajorVersion() const { return m_pHeader->major; }
    UINT16 GetMinorVersion() const { return m_pHeader->minor; }
    DEF_CHECKSUM GetVersionChecksum() const { return m_pHeader->checksum; }

    int GetNumScopes() const { return m_pHeader->numScopes; }
    int GetNumItems() const { return m_pHeader->numItems; }

protected:
    const MRMFILE_HSCHEMA_VERSION_INFO* m_pHeader;
    PCWSTR m_pUniqueId;

    HRESULT Init(_In_reads_bytes_(cbData) const void* pData, _In_ size_t cbData);

    HierarchicalSchemaVersionInfo() {}

    HierarchicalSchemaVersionInfo(_In_ const MRMFILE_HSCHEMA_VERSION_INFO* pHeader);
};

class HierarchicalSchemaReference : public DefObject
{
public:
    static HRESULT CreateInstance(
        _In_reads_bytes_(cbData) const void* pData,
        _In_ size_t cbData,
        _Outptr_ HierarchicalSchemaReference** result);

    virtual ~HierarchicalSchemaReference();

    bool CheckIsIdentical(_In_ const IHierarchicalSchema* pSchema) const;
    bool CheckIsCompatible(_In_ const IHierarchicalSchema* pSchema) const;
    bool CheckIsIdentical(_In_ const HierarchicalSchemaReference* schema) const;

    PCWSTR GetUniqueId() const { return m_pUniqueId; }
    Atom::PoolIndex GetItemsPoolIndex() const { return m_pHdr->itemsPoolIndex; }

    const IHierarchicalSchemaVersionInfo* GetVersionInfo() const { return m_pVersion; }
    int GetMajorVersion() const { return m_pVersion->GetMajorVersion(); }
    int GetMinorVersion() const { return m_pVersion->GetMinorVersion(); }

    int GetNumScopes() const { return m_pVersion->GetNumScopes(); }
    int GetNumItems() const { return m_pVersion->GetNumItems(); }

protected:
    const MRMFILE_HSCHEMA_REF* m_pHdr;
    PCWSTR m_pUniqueId;
    const IHierarchicalSchemaVersionInfo* m_pVersion;

    HierarchicalSchemaReference() : m_pHdr(nullptr), m_pUniqueId(nullptr), m_pVersion(nullptr) {}

    HRESULT Init(_In_reads_bytes_(cbData) const void* pData, _In_ size_t cbData);
};

class IHierarchicalSchema;

HRESULT ComputeHierarchicalSchemaVersionChecksum(
    _In_ const IHierarchicalSchema* pSchema,
    _In_ const IHierarchicalSchemaVersionInfo* pVersion,
    _Out_ DefChecksum::Checksum* pChecksumOut);

bool CheckHierarchicalSchemaVersionIsIdentical(
    _In_opt_ const IHierarchicalSchemaVersionInfo* pVersion1,
    _In_opt_ const IHierarchicalSchemaVersionInfo* pVersion2);

bool CheckHierarchicalSchemaVersionIsCompatible(
    _In_opt_ const IHierarchicalSchema* pHaveSchema,
    _In_opt_ const IHierarchicalSchemaVersionInfo* pWantVersion);

class IEnvironment;
class PackageResources;
class ConditionSetPoolResult;

class IHierarchicalSchemaDescription : public DefObject
{
public:
    virtual ~IHierarchicalSchemaDescription() {};

    virtual PCWSTR GetUniqueId() const = 0;
    virtual PCWSTR GetSimpleId() const = 0;

    virtual UINT16 GetMajorVersion() const = 0;
    virtual UINT16 GetMinorVersion() const = 0;

    virtual int GetNumScopes() const = 0;
    virtual IAtomPool* GetScopeNames() const = 0;

    virtual int GetNumItems() const = 0;
    virtual IAtomPool* GetItemNames() const = 0;
};

class IHierarchicalSchema : public IHierarchicalSchemaDescription
{
public:
    virtual ~IHierarchicalSchema() {}

    virtual int GetNumVersionInfos() const = 0;

    virtual const IHierarchicalSchemaVersionInfo* GetVersionInfo(_In_ int index = 0) const = 0;

    virtual int GetNumNames() const = 0;

    virtual bool Contains(_In_ PCWSTR path, _Out_opt_ int* pScopeIndexOut = NULL, _Out_opt_ int* pItemIndexOut = NULL) const = 0;

    virtual bool Contains(
        _In_ PCWSTR path,
        _In_ int relativeToScope,
        _Out_opt_ int* pScopeIndexOut = NULL,
        _Out_opt_ int* pItemIndexOut = NULL) const = 0;

    virtual bool TryGetScopeInfo(_In_ int scopeIndex, _Inout_ StringResult* pNameOut, _Out_opt_ int* pNumChildrenOut = NULL) const = 0;

    virtual bool TryGetScopeChild(
        _In_ int scopeIndex,
        _In_ int childIndex,
        _Out_opt_ int* pChildScopeIndexOut,
        _Out_opt_ int* pChildItemIndexOut) const = 0;

    virtual bool TryGetScopeChildName(_In_ int scopeIndex, _In_ int childIndex, _Inout_ StringResult* pNameOut) const = 0;

    virtual bool TryGetItemInfo(_In_ int itemIndex, _Inout_ StringResult* pNameOut) const = 0;

    virtual bool TryGetRelativeItemName(_In_ int relativeToScope, _Inout_ int itemIndex, _Inout_ StringResult* pNameOut) const = 0;

    virtual bool TryGetItemLocalName(_Inout_ int itemIndex, _Inout_ StringResult* pNameOut) const = 0;

    virtual bool TryGetRelativeScopeName(_In_ int relativeToScope, _Inout_ int scopeIndex, _Inout_ StringResult* pNameOut) const = 0;

    virtual HRESULT GetNumDescendents(_In_ int scopeIndex, _Out_opt_ int* pNumScopes, _Out_opt_ int* pNumItems) const = 0;

    virtual HRESULT GetDescendents(
        _In_ int scopeIndex,
        _In_ int sizeScopes,
        _Out_writes_to_opt_(sizeScopes, *pNumScopesWritten) int* pScopesOut,
        _Out_opt_ int* pNumScopesWritten,
        _In_ int sizeItems,
        _Out_writes_to_opt_(sizeItems, *pNumItemsWritten) int* pItemsOut,
        _Out_opt_ int* pNumItemsWritten) const = 0;

    virtual HRESULT Clone(_Outptr_ IHierarchicalSchema** result) const = 0;

    virtual HRESULT GetSchemaBlobFromFileSection(
        _Inout_opt_ DEFFILE_SECTION_TYPEID* pSectionTypeResult,
        _Inout_opt_ BlobResult* pBlobResult) const = 0;
};

class StaticHierarchicalSchemaDescription : public IHierarchicalSchemaDescription
{
public:
    enum StaticSchemaDescriptionFlags
    {
        Default = 0x00,
        CreateByReference = 0x01
    };

    static HRESULT CreateInstance(
        _In_ StaticSchemaDescriptionFlags flags,
        _In_ PCWSTR pSimpleName,
        _In_ PCWSTR pUniqueName,
        _In_ UINT16 majorVersion,
        _In_ UINT16 minorVersion,
        _In_ size_t numScopes,
        _In_reads_(numScopes) PWSTR* ppScopeNames,
        _In_ size_t numItems,
        _In_reads_(numItems) PWSTR* ppItemNames,
        _Outptr_ StaticHierarchicalSchemaDescription** result);

    virtual ~StaticHierarchicalSchemaDescription();

    inline PCWSTR GetUniqueId() const { return m_uniqueName.GetRef(); }
    inline PCWSTR GetSimpleId() const { return m_simpleName.GetRef(); }

    inline UINT16 GetMajorVersion() const { return m_majorVersion; }
    inline UINT16 GetMinorVersion() const { return m_minorVersion; }

    inline int GetNumScopes() const { return m_numScopeNames; }
    inline IAtomPool* GetScopeNames() const { return m_pScopeNames; }

    inline int GetNumItems() const { return m_numItemNames; }
    inline IAtomPool* GetItemNames() const { return m_pItemNames; }

private:
    StaticHierarchicalSchemaDescription() :
        m_ppMyScopeNames(nullptr), m_ppMyItemNames(nullptr), m_pScopeNames(nullptr), m_pItemNames(nullptr)
    {}

    HRESULT Init(
        _In_ StaticSchemaDescriptionFlags flags,
        _In_ PCWSTR pSimpleName,
        _In_ PCWSTR pUniqueName,
        _In_ UINT16 majorVersion,
        _In_ UINT16 minorVersion,
        _In_range_(<=, INT_MAX) size_t numScopeNames,
        _In_reads_(numScopeNames) PWSTR* ppScopeNames,
        _In_range_(<=, INT_MAX) size_t numItemNames,
        _In_reads_(numItemNames) PWSTR* ppItemNames);

    StringResult m_simpleName;
    StringResult m_uniqueName;
    UINT16 m_majorVersion;
    UINT16 m_minorVersion;

    int m_numScopeNames;
    PWSTR* m_ppMyScopeNames;

    int m_numItemNames;
    PWSTR* m_ppMyItemNames;

    StaticAtomPool* m_pScopeNames;
    StaticAtomPool* m_pItemNames;
};

class HierarchicalSchema : public FileSectionBase, public IHierarchicalSchema
{
public:
    static HRESULT CreateFromSection(_In_opt_ const IFileSection* pSection, _Outptr_ HierarchicalSchema** result);

    static HRESULT CreateInstance(
        _In_ const DEFFILE_SECTION_TYPEID& type,
        _In_reads_bytes_(cbData) const void* pData,
        _In_ int cbData,
        _Outptr_ HierarchicalSchema** result);

    virtual ~HierarchicalSchema();

    PCWSTR GetUniqueId() const { return m_pUniqueId; }
    PCWSTR GetSimpleId() const { return m_pSimpleId; }

    int GetNumVersionInfos() const { return m_header.numVersions; }

    const IHierarchicalSchemaVersionInfo* GetVersionInfo(_In_ int index = 0) const;

    UINT16 GetMajorVersion() const { return m_pFileVersions[0].major; }
    UINT16 GetMinorVersion() const { return m_pFileVersions[0].minor; }

    static const DEFFILE_SECTION_TYPEID GetSectionTypeId();
    static const DEFFILE_SECTION_TYPEID GetExSectionTypeId();

    int GetNumNames() const { return m_pNames->GetNumNames(); }
    int GetMaxNameLength() const { return m_pNames->GetMaxNameLength(); }

    bool TryGetName(
        _In_ int nodeIndex,
        _Inout_ StringResult* pNameOut,
        _Out_opt_ int* pScopeIndexOut = NULL,
        _Out_opt_ int* pItemIndexOut = NULL) const
    {
        return m_pNames->TryGetName(nodeIndex, pNameOut, pScopeIndexOut, pItemIndexOut);
    }

    bool TryGetName(
        _In_ int nodeIndex,
        _In_ int relativeToScope,
        _Inout_ StringResult* pNameOut,
        _Out_opt_ int* pScopeIndexOut = NULL,
        _Out_opt_ int* pItemIndexOut = NULL) const
    {
        return m_pNames->TryGetName(nodeIndex, relativeToScope, pNameOut, pScopeIndexOut, pItemIndexOut);
    }

    bool Contains(_In_ PCWSTR path, _Out_opt_ int* pScopeIndexOut = NULL, _Out_opt_ int* pItemIndexOut = NULL) const
    {
        return m_pNames->Contains(path, pScopeIndexOut, pItemIndexOut);
    }

    bool Contains(
        _In_ PCWSTR path,
        _Out_opt_ int* pScopeIndexOut = NULL,
        _Out_opt_ int* pItemIndexOut = NULL,
        _Out_opt_ int* pNameIndexOut = NULL) const
    {
        return m_pNames->Contains(path, pScopeIndexOut, pItemIndexOut, pNameIndexOut);
    }

    bool Contains(_In_ PCWSTR path, _In_ int relativeToScope, _Out_opt_ int* pScopeIndexOut = NULL, _Out_opt_ int* pItemIndexOut = NULL)
        const
    {
        return m_pNames->Contains(path, relativeToScope, pScopeIndexOut, pItemIndexOut);
    }

    bool Contains(
        _In_ PCWSTR path,
        _In_ int relativeToScope,
        _Out_opt_ int* pScopeIndexOut,
        _Out_opt_ int* pItemIndexOut,
        _Out_opt_ int* pNameIndexOut) const
    {
        return m_pNames->Contains(path, relativeToScope, pScopeIndexOut, pItemIndexOut, pNameIndexOut);
    }

    int GetNumScopes() const { return m_pNames->GetNumScopes(); }
    IAtomPool* GetScopeNames() const { return m_pNames->GetScopeNames(); }

    bool TryGetScopeInfo(_In_ int scopeIndex, _Inout_ StringResult* pNameOut, _Out_opt_ int* pNumChildrenOut = NULL) const
    {
        return m_pNames->TryGetScopeInfo(scopeIndex, pNameOut, pNumChildrenOut);
    }

    bool TryGetScopeChild(_In_ int scopeIndex, _In_ int childIndex, _Out_opt_ int* pChildScopeIndexOut, _Out_opt_ int* pChildItemIndexOut)
        const
    {
        return m_pNames->TryGetScopeChild(scopeIndex, childIndex, pChildScopeIndexOut, pChildItemIndexOut);
    }

    bool TryGetScopeChildName(_In_ int scopeIndex, _In_ int childIndex, _Inout_ StringResult* pNameOut) const
    {
        return m_pNames->TryGetScopeChildName(scopeIndex, childIndex, pNameOut);
    }

    int GetNumItems() const { return m_pNames->GetNumItems(); }
    IAtomPool* GetItemNames() const { return m_pNames->GetItemNames(); }

    bool TryGetItemInfo(_In_ int itemIndex, _Inout_ StringResult* pNameOut) const { return m_pNames->TryGetItemInfo(itemIndex, pNameOut); }

    bool TryGetRelativeItemName(_In_ int relativeToScope, _Inout_ int itemIndex, _Inout_ StringResult* pNameOut) const
    {
        return m_pNames->TryGetRelativeItemName(relativeToScope, itemIndex, pNameOut);
    }

    bool TryGetItemLocalName(_Inout_ int itemIndex, _Inout_ StringResult* pNameOut) const
    {
        return m_pNames->TryGetItemLocalName(itemIndex, pNameOut);
    }

    bool TryGetRelativeScopeName(_In_ int relativeToScope, _Inout_ int scopeIndex, _Inout_ StringResult* pNameOut) const
    {
        return m_pNames->TryGetRelativeScopeName(relativeToScope, scopeIndex, pNameOut);
    }

    HRESULT GetNumDescendents(_In_ int scopeIndex, _Out_opt_ int* pNumScopes, _Out_opt_ int* pNumItems) const
    {
        return m_pNames->GetNumDescendents(scopeIndex, pNumScopes, pNumItems);
    }

    HRESULT GetDescendents(
        _In_ int scopeIndex,
        _In_ int sizeScopes,
        _Out_writes_to_opt_(sizeScopes, *pNumScopesWritten) int* pScopesOut,
        _Out_ int* pNumScopesWritten,
        _In_ int sizeItems,
        _Out_writes_to_opt_(sizeItems, *pNumItemsWritten) int* pItemsOut,
        _Out_ int* pNumItemsWritten) const
    {
        return m_pNames->GetDescendents(scopeIndex, sizeScopes, pScopesOut, pNumScopesWritten, sizeItems, pItemsOut, pNumItemsWritten);
    }

    HRESULT Clone(_Outptr_ IHierarchicalSchema** result) const;

    virtual HRESULT GetSchemaBlobFromFileSection(
        _Inout_opt_ DEFFILE_SECTION_TYPEID* pSectionTypeResult,
        _Inout_opt_ BlobResult* pBlobResult) const;

private:
    BYTE* m_pMyBuffer;

    MRMFILE_HSCHEMA_HEADER_EX m_header;

    _Field_size_(m_header.numVersions) const MRMFILE_HSCHEMA_VERSION_INFO* m_pFileVersions;

    PCWSTR m_pUniqueId;
    PCWSTR m_pSimpleId;

    _Field_size_(m_header.numVersions) mutable HierarchicalSchemaVersionInfo** m_pVersions;
    const HierarchicalNames* m_pNames;

    const void* m_pSectionData;
    int m_cbSection;

    HierarchicalSchema();

    HRESULT Init(
        _In_ const DEFFILE_SECTION_TYPEID& type,
        _In_opt_ const IFileSection* pSection,
        _In_reads_bytes_(cbData) const void* pData,
        _In_ int cbData);
};

class IFileSectionResolver;

class ReverseFileMap : public FileSectionBase
{
public:
    static HRESULT CreateInstance(_In_ const IFileSection* const pSection, _Outptr_ ReverseFileMap** result);

    static HRESULT CreateInstance(_In_reads_bytes_(cbData) const void* pData, _In_ int cbData, _Outptr_ ReverseFileMap** result);

    virtual ~ReverseFileMap();

    bool TryGetReverseMapCandidateIndex(_In_ PCWSTR pCandidateValue, _Out_ int* pReverseMapIndexOut) const;

    _Success_(return ) _Check_return_ HRESULT
        GetCandidateInfo(_In_ int reverseMapIndex, _Out_ int* pQualifierSetIndexOut, _Out_ int* pNamedResourceIndexOut) const;

    int GetNumEntries() const { return m_pHeader->numFiles; }

    static const DEFFILE_SECTION_TYPEID GetSectionTypeId();

private:
    const MRMFILE_REVERSEFILEMAP_HEADER* m_pHeader;
    const MRMFILE_REVERSEFILEMAP_ENTRY* m_pEntries;
    const HierarchicalNames* m_pNames;
    int m_cbSection;

    ReverseFileMap();

    HRESULT Init(_In_opt_ const IFileSection* pSection, _In_reads_bytes_(cbData) const void* pData, _In_ int cbData);
};

class IRawResourceMap;
class IResourceMapBase;
class NamedResourceResult;
class ResourceCandidateResult;

class ResourceCandidateResult : public DefObject
{
public:
    using DefObject::operator delete;

    ResourceCandidateResult();
    ~ResourceCandidateResult() {}

    void Set(_In_ const IRawResourceMap* pRawMap, _In_ int valueGlobalIndex, _In_ int decisionIndex, _In_ int candidateIndexInDecision);

    HRESULT GetResourceValueType(_Out_ MrmEnvironment::ResourceValueType* pTypeOut) const;

    int GetCandidateIndex() const { return m_candidateIndexInDecision; }
    const IRawResourceMap* GetRawResourceMap() const { return m_pRawMap; }

    HRESULT GetValueLocation(
        _Out_opt_ MRMFILE_MAP_VALUE_LOCATOR* pLocatorType,
        _Out_opt_ UINT32* pDataOut,
        _Out_opt_ UINT16* extraDataOut,
        _Out_opt_ UINT16* pDetailOut) const;

    bool TryGetStringValue(_Inout_ StringResult* pStringOut) const;

    bool TryGetBlobValue(_Inout_ BlobResult* pBlobOut) const;

    HRESULT GetQualifiers(_Inout_ QualifierSetResult* pQualifiersOut) const;

    HRESULT GetSourceFileIndex(_Inout_ int* pIndexOut) const;

protected:
    const IRawResourceMap* m_pRawMap;
    int m_valueGlobalIndex;
    int m_decisionIndex;
    int m_candidateIndexInDecision;
};

class NamedResourceResult : public DefObject
{
public:
    using DefObject::operator delete;

    NamedResourceResult();
    ~NamedResourceResult();

    HRESULT
    Set(_In_ const IRawResourceMap* pRawMap, _In_ int itemIndexInSchema, _In_ int decisionIndex, _In_ int firstCandidateGlobalIndex);

    HRESULT Set(_In_ const IRawResourceMap* pRawMap, _In_ int itemIndexInSchema) { return Set(pRawMap, itemIndexInSchema, -1, -1); }

    HRESULT Set(_In_ const IHierarchicalSchema* pRawMap, _In_ int itemIndexInSchema);

    const IHierarchicalSchema* GetParentSchema() const { return m_pSchema; }

    HRESULT GetResourceName(_Out_ Atom* pNameOut) const;

    HRESULT GetResourceName(_Inout_ StringResult* pNameOut) const;

    HRESULT GetItemLocalName(_Inout_ StringResult* pNameOut) const;

    int GetResourceIndexInSchema() const { return m_resourceIndexInSchema; }

    HRESULT GetDecision(_Inout_ DecisionResult* pDecisionOut) const;

    int GetNumCandidates() const;

    HRESULT GetCandidate(_In_ int index, _Inout_ ResourceCandidateResult* pCandidateOut) const;

    virtual bool TryGetResourceLink(_Out_ const IHierarchicalSchema** linksToSchema, _Out_ UINT32* linksToResourceIndex) const;

protected:
    const IHierarchicalSchema* m_pSchema;
    const IRawResourceMap* m_pRawMap;
    int m_resourceIndexInSchema;
    int m_decisionIndex;
    int m_firstCandidateGlobalIndex;
};

class IEnvironment;
class ResourceMapSubtree;

class IRawResourceMap : public DefObject
{
public:
    virtual ~IRawResourceMap() {}

    virtual const IHierarchicalSchema* GetSchema() const = 0;
    virtual const IDecisionInfo* GetDecisionInfo() const = 0;

    virtual HRESULT SetPackageRootPath(_In_ PCWSTR pPath) const = 0;
    virtual PCWSTR GetPackageRootPath() const = 0;

    virtual int GetTotalNumResourceValues() const = 0;
    virtual bool IsValidResourceValueIndex(_In_ int index) const = 0;

    virtual HRESULT GetDecision(_In_ int index, _Inout_ DecisionResult* pDecisionOut) const = 0;

    virtual HRESULT GetRawResourceInfo(
        _In_ int resourceIndexInSchema,
        _Out_opt_ int* pDecisionIndexOut,
        _Out_opt_ int* pFirstCandidateValueIndexOut) const = 0;

    virtual HRESULT GetRawValueInfo(
        _In_ int valueIndex,
        _Out_opt_ MRMFILE_MAP_VALUE_LOCATOR* pLocatorTypeOut,
        _Out_opt_ UINT32* pDataOut,
        _Out_opt_ UINT16* extraDataOut,
        _Out_opt_ UINT16* pDetailOut,
        _Out_opt_ MrmEnvironment::ResourceValueType* pValueTypeOut) const = 0;

    virtual HRESULT GetInternalData(_In_ UINT32 offset, _In_ UINT32 cbData, _Inout_ BlobResult* pDataOut) const = 0;

    virtual HRESULT GetInternalDataAsString(
        _In_ UINT32 offset,
        _In_ UINT32 cbData,
        _In_ MrmEnvironment::ResourceValueType valueType,
        _Inout_ StringResult* pDataOut) const = 0;

    virtual HRESULT GetReferenceDataAsString(
        _In_ UINT32 itemIndex,
        _In_ UINT16 sectionIndex,
        _In_ UINT16 detail,
        _In_ MrmEnvironment::ResourceValueType valueType,
        _Inout_ StringResult* pStringOut) const = 0;

    virtual HRESULT GetReferenceDataAsBlob(
        _In_ UINT32 itemIndex,
        _In_ UINT16 sectionIndex,
        _In_ UINT16 detail,
        _Inout_ BlobResult* pDataOut) const = 0;

    virtual HRESULT GetFilePath(_In_ int fileIndex, _Inout_ StringResult* pPathOut) const = 0;

    virtual int GetNumFiles() const = 0;

    virtual bool TryGetResourceLinkForResourceIndex(
        _In_ UINT32 linksFromResourceIndex,
        _Out_ const IHierarchicalSchema** linksToSchema,
        _Out_ UINT32* linksToResourceIndex) const = 0;

protected:
    IRawResourceMap() {}
};

class IResourceMapBase : protected DefObject
{
public:
    using DefObject::operator delete;

    virtual const IHierarchicalSchema* GetSchema() const = 0;
    virtual const IHierarchicalSchema* GetOriginalSchema() const = 0;
    virtual const IDecisionInfo* GetDecisionInfo() const = 0;

    virtual const ResourceMapSubtree* GetRootSubtree() const = 0;

    virtual int GetNumResources() const = 0;

    virtual HRESULT GetResourceByIndex(_In_ int indexInSchema, _Inout_ NamedResourceResult* pItemOut) const = 0;

    virtual HRESULT GetResource(_In_ PCWSTR pPath, _Inout_ NamedResourceResult* pItemOut) const = 0;

    virtual int GetTotalNumResourceValues() const = 0;

    virtual HRESULT SetDecisionInfoOverride(_In_ const IDecisionInfo* pOverrideDecisionInfo, _In_ const RemapUInt16* pOverrideDecisionMap)
        const = 0;

    virtual void ResetDecisionInfoOverride() const = 0;

    virtual HRESULT SetSchemaOverride(_In_ const IHierarchicalSchema* pOverrideSchema) const = 0;

    virtual HRESULT SetPackageRootPath(_In_ PCWSTR pPath) const = 0;

    virtual PCWSTR GetPackageRootPath() const = 0;

    virtual UINT64 GetCurrentGeneration() const = 0;
};

class ResourceMapSubtree : protected DefObject
{
public:
    using DefObject::operator delete;

    virtual ~ResourceMapSubtree();

    const IResourceMapBase* GetFullResourceMap() const { return m_pFullMap; }
    const ResourceMapSubtree* GetRootSubtree() const { return m_pFullMap->GetRootSubtree(); }

    virtual int GetSubtreeRootIndex() const { return m_scopeIndex; }

    PCWSTR GetFullScopeName() const;

    // The following get immediate children (scope or item) by index
    int GetNumChildren() const;

    HRESULT GetChildName(_In_ int childIndex, _Inout_ StringResult* pNameOut) const;

    bool ChildIsScope(_In_ int childIndex) const;

    HRESULT GetChildScopeSubtree(_In_ int childIndex, _Out_ const ResourceMapSubtree** result) const;

    HRESULT GetChildResource(_In_ int childIndex, _Inout_ NamedResourceResult* pItemOut) const;

    // The following get any contained
    HRESULT GetResource(_In_ PCWSTR pPath, _Inout_ NamedResourceResult* pItemOut) const;

    HRESULT GetSubtree(_In_ PCWSTR pPath, _Out_ const ResourceMapSubtree** result) const;

    HRESULT GetSubtreeByIndex(_In_ int indexInSchema, _Out_ const ResourceMapSubtree** result) const;

    bool CheckVersionIsCompatible(_In_ HierarchicalSchemaVersionInfo* wantVersion) const;

    int GetIndexInSchema() const;

    virtual HRESULT MoveToSubtree(_In_ PCWSTR pPath);

    // The following enable enumeration of descendent resources and scopes
    int GetNumDescendentResources() const;

    HRESULT GetDescendentResource(_In_ int index, _Inout_ NamedResourceResult* pItemOut) const;

    HRESULT GetResourceNameBySchemaIndex(_In_ int indexInSchema, _Inout_ StringResult* pNameOut) const;

    // Gets the name of the resource relative to this scope
    HRESULT GetDescendentResourceName(_In_ int index, _Inout_ StringResult* pNameOut) const;

    int GetNumDescendentScopes() const;

    HRESULT GetDescendentScopeSubtree(_In_ int index, _Out_ const ResourceMapSubtree** result) const;

    // Gets the name of the descendent scope relative to this one
    HRESULT GetDescendentScopeName(_In_ int index, _Inout_ StringResult* pNameOut) const;

    bool MoveToRoot()
    {
        m_scopeIndex = 0;
        return true;
    }

    // Tells if the Managed File behind this object is still valid

    bool IsValid() const;

protected:
    ResourceMapSubtree();

    HRESULT InitResourceMapSubtree(_In_ const IResourceMapBase* pFullMap, _In_ int scopeIndex);

    static HRESULT CreateInstance(_In_ const IResourceMapBase* pFullMap, _In_ int scopeIndex, _Outptr_ const ResourceMapSubtree** result);

    HRESULT GetOrUpdateDescendentResources() const;

    HRESULT GetOrUpdateDescendentScopes() const;

    HRESULT GetOrUpdateDescendents() const;

    const IResourceMapBase* m_pFullMap;
    const IHierarchicalSchema* m_pSchema;
    int m_scopeIndex;
    StringResult m_strResMapFullScopeName;

    mutable int m_numDescendentResources;
    mutable int m_numDescendentScopes;
    mutable _Field_size_(m_numDescendentResources) int* m_pDescendentResources;
    mutable _Field_size_(m_numDescendentScopes) int* m_pDescendentScopes;

    UINT64 m_initGeneration;
    mutable UINT16 m_currentMinorVersion;
};

class IFileSectionResolver;
class ResourceMapFileData;

class IResourceLinks
{
public:
    virtual ~IResourceLinks() {}

    virtual const IHierarchicalSchema* GetSchema() const = 0;

    virtual int GetNumReferencedSchemas() const = 0;

    virtual HRESULT GetReferencedSchema(_In_ int index, _Out_ const IHierarchicalSchema** result) const = 0;

    virtual int GetNumInternalLinks() const = 0;
    virtual int GetNumFullLinks() const = 0;
    virtual int GetNumTotalLinks() const = 0;
    virtual int GetNumLinksByResourceIndex() const = 0;

    virtual HRESULT GetInternalResourceLink(
        _In_ UINT32 linkIndexInSection,
        _Outptr_opt_result_maybenull_ const IHierarchicalSchema** mapsToSchema,
        _Out_opt_ UINT32* mapsToItemIndex) const = 0;

    virtual HRESULT GetFullResourceLink(
        _In_ UINT32 linkIndexInSection,
        _Outptr_opt_result_maybenull_ const IHierarchicalSchema** mapsToSchema,
        _Out_opt_ UINT32* mapsToItemIndex) const = 0;

    virtual HRESULT GetResourceLinkById(
        _In_ UINT32 linkIndexInSection,
        _In_ UINT32* linksFromResourceIndex,
        _Out_ const IHierarchicalSchema** mapsToSchema,
        _Out_ UINT32* linksToResourceIndex) const = 0;

    virtual bool TryGetResourceLinkForResourceIndex(
        _In_ UINT32 linksFromResourceIndex,
        _Out_ const IHierarchicalSchema** linksToSchema,
        _Out_ UINT32* linksToResourceIndex) const = 0;
};

class ResourceMapBase : public FileSectionBase, public IResourceMapBase, public ResourceMapSubtree, public IResourceLinks
{
public:
    using IResourceMapBase::operator delete;

    static HRESULT CreateInstance(
        _In_ const IFileSectionResolver* pSections,
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_ const IFileSection* const pSection,
        _Outptr_ ResourceMapBase** result);

    static HRESULT CreateInstance(
        _In_ const IFileSectionResolver* pSections,
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_ const DEFFILE_SECTION_TYPEID& sectionType,
        _In_reads_bytes_(cbData) const BYTE* pData,
        _In_ int cbData,
        _Outptr_ ResourceMapBase** result);

    virtual ~ResourceMapBase();

    HRESULT SetPackageRootPath(_In_ PCWSTR pPath) const;

    PCWSTR GetPackageRootPath() const;

    const IHierarchicalSchema* GetSchema() const;
    const IHierarchicalSchema* GetOriginalSchema() const;
    const IDecisionInfo* GetDecisionInfo() const;

    const ResourceMapSubtree* GetRootSubtree() const { return this; }

    int GetNumResources() const;

    HRESULT GetResourceByIndex(_In_ int indexInSchema, _Inout_ NamedResourceResult* pItemOut) const;

    virtual HRESULT MoveToSubtree(_In_ PCWSTR pPath) const;

    HRESULT GetResource(_In_ PCWSTR pPath, _Inout_ NamedResourceResult* pItemOut) const;

    int GetTotalNumResourceValues() const;

    HRESULT SetDecisionInfoOverride(_In_ const IDecisionInfo* pOverrideDecisionInfo, _In_ const RemapUInt16* pOverrideDecisionMap) const;

    void ResetDecisionInfoOverride() const;

    HRESULT SetSchemaOverride(_In_ const IHierarchicalSchema* pOverrideSchema) const;

    UINT64 GetCurrentGeneration() const { return 0; }

    HRESULT SetLinks(_In_ const IResourceLinks* links);

    // IResourceLinks implementation
    int GetNumReferencedSchemas() const;

    HRESULT GetReferencedSchema(_In_ int index, _Out_ const IHierarchicalSchema** result) const;

    int GetNumInternalLinks() const;
    int GetNumFullLinks() const;
    int GetNumTotalLinks() const;
    int GetNumLinksByResourceIndex() const;

    HRESULT GetInternalResourceLink(
        _In_ UINT32 linkIndexInSection,
        _Outptr_opt_result_maybenull_ const IHierarchicalSchema** mapsToSchema,
        _Out_opt_ UINT32* mapsToItemIndex) const;

    HRESULT GetFullResourceLink(
        _In_ UINT32 linkIndexInSection,
        _Outptr_opt_result_maybenull_ const IHierarchicalSchema** mapsToSchema,
        _Out_opt_ UINT32* mapsToItemIndex) const;

    HRESULT GetResourceLinkById(
        _In_ UINT32 linkIndexInSection,
        _In_ UINT32* linksFromResourceIndex,
        _Out_ const IHierarchicalSchema** mapsToSchema,
        _Out_ UINT32* linksToResourceIndex) const;

    bool TryGetResourceLinkForResourceIndex(
        _In_ UINT32 linksFromResourceIndex,
        _Out_ const IHierarchicalSchema** linksToSchema,
        _Out_ UINT32* linksToResourceIndex) const;

protected:
    const IFileSectionResolver* m_pSections;
    const IHierarchicalSchema* m_pSchema;
    const IDecisionInfo* m_pDecisionInfo;
    const IResourceLinks* m_links;

    ResourceMapFileData* m_pFileData;

    bool HaveLinks() const { return (m_links != nullptr); }

    ResourceMapBase() : m_pFileData(nullptr) {}

    HRESULT Init(
        _In_ const IFileSectionResolver* pPackageResources,
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_ const DEFFILE_SECTION_TYPEID& sectionType,
        _In_opt_ const IFileSection* const pSection,
        _In_reads_bytes_(cbData) const BYTE* pData,
        _In_ UINT32 cbData);

    const ResourceMapBase* GetResourceMap() const { return this; }
};

class DecisionInfoFileData;

class DecisionInfoFileSection : public FileSectionBase, public IDecisionInfo
{
public:
    static HRESULT CreateInstance(
        _In_ const IFileSection* const pSection,
        _In_opt_ const RemapAtomPool* pQualifierMapping,
        _Outptr_ DecisionInfoFileSection** result);

    static HRESULT CreateInstance(
        _In_reads_bytes_(cbData) const BYTE* pData,
        _In_ int cbData,
        _In_opt_ const RemapAtomPool* pQualifierMapping,
        _Outptr_ DecisionInfoFileSection** result);

    virtual ~DecisionInfoFileSection();

    int GetNumQualifiers() const;

    const RemapAtomPool* GetQualifierMapping() const;

    HRESULT GetQualifier(_In_ int index, _Inout_ QualifierResult* pResult) const;

    int GetNumQualifierSets() const;

    HRESULT GetQualifierSet(_In_ int index, _Inout_ QualifierSetResult* pResult) const;

    int GetNumDecisions() const;

    HRESULT GetDecision(_In_ int index, _Inout_ DecisionResult* pResult) const;

    HRESULT GetDecisionNumQualifierSets(_In_ int index, _Out_ int* pNumSetsOut) const;

protected:
    HRESULT Init(
        _In_opt_ const IFileSection* pFileSection,
        _In_reads_bytes_(cbData) const BYTE* pData,
        _In_ int cbData,
        _In_opt_ const RemapAtomPool* pQualifierMapping);

    DecisionInfoFileData* m_pFileData;
};

class ResourceLinkSection : public FileSectionBase, public IResourceLinks
{
public:
    static HRESULT CreateFromSection(
        _In_opt_ const IFileSectionResolver* sectionResolver,
        _In_opt_ const ISchemaCollection* schemaCollection,
        _In_ const IFileSection* const section,
        _Outptr_ ResourceLinkSection** result);

    static HRESULT CreateInstance(
        _In_opt_ const IFileSectionResolver* sectionResolver,
        _In_opt_ const ISchemaCollection* schemaCollection,
        _In_ const DEFFILE_SECTION_TYPEID& type,
        _In_reads_bytes_(dataSizeInBytes) const BYTE* rawData,
        _In_ int dataSizeInBytes,
        _Outptr_ ResourceLinkSection** result);

    virtual ~ResourceLinkSection();

    HRESULT ResolveSchemaReferences(_In_opt_ const IFileSectionResolver* sections, _In_opt_ const ISchemaCollection* schemas);

    const IHierarchicalSchema* GetSchema() const { return m_schema; }

    int GetNumReferencedSchemas() const { return m_header->numSchemas; }

    int GetNumInternalLinks() const { return m_header->numInternalLinks; }
    int GetNumFullLinks() const { return m_header->numFullLinks; }
    int GetNumLinksByResourceIndex() const { return m_header->numLinksById; }
    int GetNumTotalLinks() const { return m_header->numInternalLinks + m_header->numFullLinks; }

    HRESULT GetReferencedSchema(_In_ int index, _Out_ const IHierarchicalSchema** result) const;

    HRESULT GetInternalResourceLink(
        _In_ UINT32 linkIndexInSection,
        _Outptr_opt_result_maybenull_ const IHierarchicalSchema** mapsToSchema,
        _Out_opt_ UINT32* mapsToItemIndex) const;

    HRESULT GetFullResourceLink(
        _In_ UINT32 linkIndexInSection,
        _Outptr_opt_result_maybenull_ const IHierarchicalSchema** mapsToSchema,
        _Out_opt_ UINT32* mapsToItemIndex) const;

    HRESULT GetResourceLink(
        _In_ UINT32 linkIndexInSection,
        _Outptr_opt_result_maybenull_ const IHierarchicalSchema** mapsToSchema,
        _Out_opt_ UINT32* mapsToItemIndex) const;

    HRESULT GetResourceLinkById(
        _In_ UINT32 linkIndexInSection,
        _Out_opt_ UINT32* linksFromResourceIndex,
        _Outptr_opt_result_maybenull_ const IHierarchicalSchema** mapsToSchema,
        _Out_opt_ UINT32* linksToResourceIndex) const;

    bool TryGetResourceLinkForResourceIndex(
        _In_ UINT32 linksFromResourceIndex,
        _Outptr_opt_result_maybenull_ const IHierarchicalSchema** linksToSchema,
        _Out_opt_ UINT32* linksToResourceIndex) const;

    static const DEFFILE_SECTION_TYPEID GetSectionTypeId();

private:
    bool IsValidResourceLinkIndex(_In_ int index) const { return ((index >= 0) && (index < GetNumTotalLinks())); }

    _Field_size_(1) const MRMFILE_RESOURCE_LINK_HEADER* m_header;
    _Field_size_(m_header->numSchemas) const MRMFILE_LINK_SCHEMA_MAP* m_schemaMap;
    _Field_size_(m_header->schemaDataSizeInBytes) const BYTE* m_schemaData;

    _Field_size_(m_header->firstLargeInternalLink) const UINT16* m_internalLinks;
    _Field_size_(m_header->numInternalLinks - m_header->firstLargeInternalLink) const UINT32* m_largeInternalLinks;

    _Field_size_(m_header->firstLargeFullLink) const MRMFILE_FULL_LINK* m_fullLinks;
    _Field_size_(m_header->numFullLinks - m_header->firstLargeFullLink) const MRMFILE_LARGE_FULL_LINK* m_largeFullLinks;

    _Field_size_(m_header->firstLargeLinkById) const MRMFILE_LINK_BY_ID* m_linksById;
    _Field_size_(m_header->numLinksById - m_header->firstLargeLinkById) const MRMFILE_LARGE_LINK_BY_ID* m_largeLinksById;

    _Field_size_(m_header->numSchemas) const IHierarchicalSchema** m_schemas;

    const IHierarchicalSchema* m_schema;

    ResourceLinkSection() {}

    HRESULT Init(
        _In_ const DEFFILE_SECTION_TYPEID& sectionType,
        _In_opt_ const IFileSectionResolver* sections,
        _In_opt_ const ISchemaCollection* schemaCollection,
        _In_reads_bytes_(dataSizeInBytes) const BYTE* rawData,
        _In_ UINT32 dataSizeInBytes);
};

class PriDescriptor : public FileSectionBase
{
public:
    static HRESULT CreateInstance(
        _In_ const IFileSectionResolver* const pSections,
        _In_ const ISchemaCollection* const pSchemaCollection,
        _In_ const IFileSection* const pSection,
        _Outptr_ PriDescriptor** result);

    static HRESULT CreateInstance(
        _In_ const IFileSectionResolver* pSections,
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_reads_bytes_(cbData) const BYTE* pData,
        _In_ int cbData,
        _Outptr_ PriDescriptor** result);

    virtual ~PriDescriptor() {}

    int GetNumSchemas() const { return m_pHeader->numSchemas; }

    HRESULT GetSchema(_In_ int index, _In_ bool fallbackToMap, _Out_ const IHierarchicalSchema** result) const;

    int GetNumResourceMaps() const { return m_pHeader->numResourceMaps; }

    HRESULT GetResourceMap(_In_ int index, _Out_ const ResourceMapBase** result) const;

    HRESULT GetPrimaryResourceMap(_Out_ const ResourceMapBase** result) const;

    int GetNumDecisionInfos() const { return m_pHeader->numDecisionInfos; }

    HRESULT GetDecisionInfo(_In_ int index, _Out_ const DecisionInfoFileSection** result) const;

    HRESULT GetIncludedFiles(_Out_ const FileFileList** result) const;

    int GetNumReferencedFileSections() const { return m_pHeader->numReferencedFileSections; }

    HRESULT GetReferencedFileSection(_In_ int index, _Out_ const FileFileList** result) const;

    int GetNumDataItemSections() const { return m_pHeader->numDataItemSections; }

    HRESULT GetDataItemSection(_In_ int index, _Out_ const FileDataItemsSection** result) const;

    bool GetAutoMergeEnabled() const { return ((m_pHeader->flags & MRMFILE_PRI_FLAGS_AUTO_MERGE) != 0); }

    bool GetIsDeploymentMergeable() const { return ((m_pHeader->flags & MRMFILE_PRI_FLAGS_DEPLOYMENT_MERGEABLE) != 0); }

    bool GetIsDeploymentMergeResult() const { return ((m_pHeader->flags & MRMFILE_PRI_FLAGS_IS_DEPLOYMENT_MERGE_RESULT) != 0); }

    bool GetIsAutomergeMergeResult() const { return ((m_pHeader->flags & MRMFILE_PRI_FLAGS_IS_AUTOMERGE_MERGE_RESULT) != 0); }

    HRESULT
    GetTargetOsVersion(_In_ CoreProfile* pProfile, _Inout_opt_ StringResult* pPlatformOut, _Inout_opt_ StringResult* pVersionOut) const;

protected:
    const IFileSectionResolver* m_pSections;
    const ISchemaCollection* m_pSchemaCollection;

    const MRMFILE_PRI_DESCRIPTOR_EX* m_pHeader;
    const DEFFILE_SECTION_INDEX* m_pSchemaSectionIndices;
    const DEFFILE_SECTION_INDEX* m_pDecisionInfoSectionIndices;
    const DEFFILE_SECTION_INDEX* m_pResourceMapSectionIndices;
    const DEFFILE_SECTION_INDEX* m_pReferencedFileSectionIndices;
    const DEFFILE_SECTION_INDEX* m_pDataItemSectionIndices;

    HRESULT Init(
        _In_ const IFileSectionResolver* pSections,
        _In_ const ISchemaCollection* const pSchemaCollection,
        _In_opt_ const IFileSection* const pSection,
        _In_reads_bytes_(cbData) const void* const pData,
        _In_ int cbData);

private:
    HRESULT ValidateSectionIndex(_In_reads_opt_(indexCounts) const DEFFILE_SECTION_INDEX* pSectionIndexes, _In_ int indexCounts) const;
};

/*!
     * Gets a structured representation of a file section from some
     * file, specified by its index in the local file list of the 
     * IFileSectionResolver itself.
     */

class FileAtomPool;
class UnifiedEnvironment;

class IFileSectionResolver : public DefObject
{
public:
    virtual ~IFileSectionResolver() {}

    virtual CoreProfile* GetProfile() const = 0;
    virtual UnifiedEnvironment* GetUnifiedEnvironment() const = 0;

    virtual HRESULT GetSection(
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_ int fileIndex,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ const IFileSection** result) const = 0;

    virtual const bool TryGetSectionIndexByType(
        _In_ const DEFFILE_SECTION_TYPEID& sectionType,
        _In_ int fileIndex,
        _In_ int startAtSectionIndex,
        _Out_ int* nextSectionIndex) const = 0;

    virtual HRESULT GetAtomPoolSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileAtomPool** result) const = 0;

    virtual HRESULT GetDecisionInfoSection(
        _In_ int fileIndex,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ DecisionInfoFileSection** result) const = 0;

    virtual HRESULT GetSchemaSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ HierarchicalSchema** result)
        const = 0;

    virtual HRESULT GetResourceMapSection(
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_ int fileIndex,
        _Inout_ BaseFile::SectionIndex sectionIndex,
        _Out_ ResourceMapBase** result) const = 0;

    virtual HRESULT GetPriDescriptorSection(
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_ int fileIndex,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ PriDescriptor** result) const = 0;

    virtual HRESULT GetFileListSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileFileList** result) const = 0;

    virtual HRESULT GetDataItemsSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileDataItemsSection** result)
        const = 0;

    virtual HRESULT GetDataSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileDataSection** result) const = 0;

    virtual HRESULT GetAbsoluteFolderPath(_In_ int fileIndex, _Inout_ StringResult* pStringResult) const = 0;

    virtual HRESULT GetReverseFileMapSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ ReverseFileMap** result)
        const = 0;

    virtual HRESULT GetEnvironmentMappingSection(
        _In_ int fileIndex,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ const EnvironmentMapping** result) const = 0;

    virtual HRESULT GetResourceLinkSection(
        _In_opt_ const ISchemaCollection* schemas,
        _In_ int fileIndex,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ const ResourceLinkSection** result) const = 0;

    virtual HRESULT GetFilePath(_In_ int fileIndex, _Inout_ StringResult* pStringResult) const = 0;

    virtual HRESULT GetFileDefaultEnvironment(
        _In_ int fileIndex,
        _Inout_opt_ StringResult* fileEnvironmentName,
        _Inout_opt_ EnvironmentVersionInfo* fileEnvironmentVersion) const = 0;

    virtual HRESULT GetDefaultQualifierMapping(_In_ int fileIndex, _Out_ const RemapAtomPool** result) const = 0;

    virtual int GetNumFiles() const = 0;
};

class MrmFileSection;

class IMrmFile : public IFileSectionResolver
{
public:
    virtual ~IMrmFile() {}

    virtual HRESULT GetBaseFile(_Out_ const BaseFile** result) const = 0;

    virtual HRESULT GetSection(
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_ int fileIndex,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ const IFileSection** result) const = 0;

    virtual HRESULT GetAtomPoolSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileAtomPool** result) const = 0;

    virtual HRESULT GetDecisionInfoSection(
        _In_ int fileIndex,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ DecisionInfoFileSection** result) const = 0;

    virtual HRESULT GetSchemaSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ HierarchicalSchema** result)
        const = 0;

    virtual HRESULT GetResourceMapSection(
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_ int fileIndex,
        _Inout_ BaseFile::SectionIndex sectionIndex,
        _Out_ ResourceMapBase** result) const = 0;

    virtual HRESULT GetPriDescriptorSection(
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_ int fileIndex,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ PriDescriptor** result) const = 0;

    virtual HRESULT GetFileListSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileFileList** result) const = 0;

    virtual HRESULT GetDataItemsSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileDataItemsSection** result)
        const = 0;

    virtual HRESULT GetDataSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileDataSection** result) const = 0;

    virtual HRESULT GetReverseFileMapSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ ReverseFileMap** result)
        const = 0;

    virtual HRESULT GetEnvironmentMappingSection(
        _In_ int fileIndex,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ const EnvironmentMapping** result) const = 0;

    virtual HRESULT GetFileDefaultEnvironment(
        _In_ int fileIndex,
        _Inout_opt_ StringResult* fileEnvironmentName,
        _Inout_opt_ EnvironmentVersionInfo* fileEnvironmentVersion) const = 0;

    virtual HRESULT GetDefaultQualifierMapping(_In_ int fileIndex, _Out_ const RemapAtomPool** result) const = 0;

    virtual HRESULT ResolveFileFileList(_In_ const FileFileList* pFileFileList) = 0;

    HRESULT GetSection(
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ const IFileSection** result) const
    {
        return GetSection(pSchemaCollection, 0, sectionIndex, result);
    }

    HRESULT GetAtomPoolSection(_In_ BaseFile::SectionIndex sectionIndex, _Out_ FileAtomPool** result) const
    {
        return GetAtomPoolSection(0, sectionIndex, result);
    }

    HRESULT
    GetPriDescriptorSection(
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ PriDescriptor** result) const
    {
        return GetPriDescriptorSection(pSchemaCollection, 0, sectionIndex, result);
    }

    HRESULT GetReverseFileMapSection(_In_ BaseFile::SectionIndex sectionIndex, _Out_ ReverseFileMap** result) const
    {
        return GetReverseFileMapSection(0, sectionIndex, result);
    }

    HRESULT GetEnvironmentMappingSection(_In_ BaseFile::SectionIndex sectionIndex, _Out_ const EnvironmentMapping** result) const
    {
        return GetEnvironmentMappingSection(0, sectionIndex, result);
    }

    HRESULT GetDecisionInfoSection(_In_ BaseFile::SectionIndex sectionIndex, _Out_ DecisionInfoFileSection** result) const
    {
        return GetDecisionInfoSection(0, sectionIndex, result);
    }

    HRESULT GetSchemaSection(_In_ BaseFile::SectionIndex sectionIndex, _Out_ HierarchicalSchema** result) const
    {
        return GetSchemaSection(0, sectionIndex, result);
    }

    HRESULT
    GetResourceMapSection(
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ ResourceMapBase** result) const
    {
        return GetResourceMapSection(pSchemaCollection, 0, sectionIndex, result);
    }

    HRESULT GetFileListSection(_In_ BaseFile::SectionIndex sectionIndex, _Out_ FileFileList** result) const
    {
        return GetFileListSection(0, sectionIndex, result);
    }

    HRESULT GetDataItemsSection(_In_ BaseFile::SectionIndex sectionIndex, _Out_ FileDataItemsSection** result) const
    {
        return GetDataItemsSection(0, sectionIndex, result);
    }

    HRESULT GetDataSection(_In_ BaseFile::SectionIndex sectionIndex, _Out_ FileDataSection** result) const
    {
        return GetDataSection(0, sectionIndex, result);
    }
};

class MrmFileResolver;
class PriFileManager;
class MrmFile : public IMrmFile
{
public:
    static HRESULT CreateInstance(
        _In_ UnifiedEnvironment* pEnvironment,
        _In_ UINT32 flags,
        _In_ PCWSTR pFileName,
        _Outptr_ MrmFile** result);

    static HRESULT CreateInstance(_In_ PriFileManager* pManager, _In_ PCWSTR pFileName, _Outptr_ MrmFile** result);

    static HRESULT CreateInstance(
        _In_ UnifiedEnvironment* pEnivironment,
        _In_ UINT32 flags,
        _In_reads_bytes_(cbData) const BYTE* pData,
        _In_ size_t cbData,
        _Outptr_ MrmFile** result);

    // This CreateInstance method is temporary scaffolding that makes it easier to slide
    // the updated infrastructure under the existing API surface.  It will go
    // away once we move fully to the new infrastructure.
    static HRESULT CreateInstance(_In_ UnifiedEnvironment* pEnvironment, _In_ const BaseFile* pBaseFile, _Outptr_ MrmFile** result);

    virtual ~MrmFile();

    virtual UnifiedEnvironment* GetUnifiedEnvironment() const { return m_pEnvironment; }
    virtual CoreProfile* GetProfile() const;

    HRESULT GetBaseFile(_Out_ const BaseFile** result) const
    {
        *result = m_pBaseFile;
        return S_OK;
    }

    HRESULT
    GetSection(
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_ int fileIndex,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ const IFileSection** result) const;

    virtual const bool TryGetSectionIndexByType(
        _In_ const DEFFILE_SECTION_TYPEID& sectionType,
        _In_ int fileIndex,
        _In_ int startAtSectionIndex,
        _Out_ int* nextSectionIndex) const;

    HRESULT GetAtomPoolSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileAtomPool** result) const;

    HRESULT GetPriDescriptorSection(
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_ int fileIndex,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ PriDescriptor** result) const;

    HRESULT
    GetDecisionInfoSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ DecisionInfoFileSection** result) const;

    HRESULT GetSchemaSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ HierarchicalSchema** result) const;

    HRESULT GetResourceMapSection(
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_ int fileIndex,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ ResourceMapBase** result) const;

    HRESULT GetFileListSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileFileList** result) const;

    HRESULT GetDataItemsSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileDataItemsSection** result) const;

    HRESULT GetDataSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileDataSection** result) const;

    HRESULT GetReverseFileMapSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ ReverseFileMap** result) const;

    HRESULT GetEnvironmentMappingSection(
        _In_ int fileIndex,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ const EnvironmentMapping** result) const override;

    HRESULT GetResourceLinkSection(
        _In_opt_ const ISchemaCollection* schemas,
        _In_ int fileIndex,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ const ResourceLinkSection** result) const override;

    virtual HRESULT GetFileDefaultEnvironment(
        _In_ int fileIndex,
        _Inout_opt_ StringResult* fileEnvironmentName,
        _Inout_opt_ EnvironmentVersionInfo* fileEnvironmentVersion) const override;

    HRESULT GetDefaultQualifierMapping(_In_ int fileIndex, _Out_ const RemapAtomPool** result) const;

    HRESULT ResolveFileFileList(_In_ const FileFileList* pFileFileList);

    HRESULT GetAbsoluteFolderPath(_In_ int fileIndex, _Inout_ StringResult* pStringResult) const;

    HRESULT GetFilePath(_In_ int fileIndex, _Inout_ StringResult* pStringResult) const;

    int GetNumFiles() const;

protected:
    mutable const BaseFile* m_pBaseFile;
    mutable const BaseFile* m_pMyBaseFile;
    mutable MrmFileSection* m_pSections;
    mutable PriFileManager* m_pPriFileManager;
    mutable MrmFileResolver* m_pFileResolver;
    UnifiedEnvironment* m_pEnvironment;

    MrmFile() :
        m_pBaseFile(nullptr),
        m_pMyBaseFile(nullptr),
        m_pSections(nullptr),
        m_pPriFileManager(nullptr),
        m_pFileResolver(nullptr),
        m_pEnvironment(nullptr)
    {}

    HRESULT Init(_In_ UnifiedEnvironment* pEnvironment, _In_ UINT32 flags, _In_ PCWSTR pPath);

    HRESULT Init(_In_ PriFileManager* pPriFileManager, _In_ PCWSTR pFileName);

    HRESULT Init(_In_ UnifiedEnvironment* pEnvironment, _In_ UINT32 flags, _In_reads_bytes_(cbData) const BYTE* pData, _In_ size_t cbData);

    HRESULT Init(_In_ UnifiedEnvironment* pEnvironment, _In_ const BaseFile* pBaseFile);

    HRESULT InitSections();

    void ReleaseSections();

    HRESULT InitializeAndGetSection(_In_ BaseFile::SectionIndex sectionIndex, _Out_ MrmFileSection** result) const;

private:
    StringResult m_strRootFolder;
    StringResult m_strFilePath;
};

class UnifiedEnvironment;
class UnifiedDecisionInfo;

class IUnifiedResourceView : public ISchemaCollection, public IResourceMapCollection
{
public:
    virtual ~IUnifiedResourceView() {}
    virtual AtomPoolGroup* GetAtoms() const = 0;
    virtual UnifiedDecisionInfo* GetDefaultDecisionInfo() const = 0;
    virtual UnifiedEnvironment* GetUnifiedEnvironment() const = 0;

    virtual CoreProfile* GetProfile() const = 0;

    virtual bool TryGetReverseFileMap(_Outptr_opt_ const ReverseFileMap** ppMapOut) const = 0;
};

class PriFile : public IUnifiedResourceView
{
public:
    static HRESULT CreateInstance(_In_ const IMrmFile* pFile, _Outptr_ const PriFile** result);

    static HRESULT CreateInstance(_In_ const IMrmFile* pFile, _In_ IUnifiedResourceView* pView, _Outptr_ const PriFile** result);

    virtual ~PriFile();

    void SetPackageRoot(_In_ PCWSTR pPackageRoot);

    virtual AtomPoolGroup* GetAtoms() const;
    virtual UnifiedEnvironment* GetUnifiedEnvironment() const;
    virtual UnifiedDecisionInfo* GetDefaultDecisionInfo() const;

    virtual HRESULT GetFileDefaultEnvironment(
        _Inout_opt_ StringResult* fileEnvironmentName,
        _Inout_opt_ EnvironmentVersionInfo* fileEnvironmentVersion) const;

    HRESULT GetBaseFile(_Out_ const BaseFile** result) const;

    const IMrmFile* GetBaseMrmFile() const { return m_pFile; }
    const IUnifiedResourceView* GetBaseResourceView() const { return m_pView; }
    const PriDescriptor* GetPriDescriptor() const { return m_pDescriptor; }
    virtual CoreProfile* GetProfile() const { return ((m_pView != nullptr) ? m_pView->GetProfile() : nullptr); }

    int GetNumSchemas() const;

    virtual HRESULT GetSchema(_In_ int index, _Out_ const IHierarchicalSchema** result) const;

    virtual HRESULT GetPrimarySchema(_Out_ const IHierarchicalSchema** result) const;

    virtual HRESULT GetSchemaById(_In_ PCWSTR pSchemaId, _Out_ const IHierarchicalSchema** result) const;

    HRESULT FindSchema(_In_ const HierarchicalSchemaReference* pRef, _Out_ const IHierarchicalSchema** ppSchemaOut) const;

    int GetNumResourceMaps() const;

    HRESULT GetResourceMap(_In_ int index, _Out_ const IResourceMapBase** result) const;

    HRESULT GetPrimaryResourceMap(_Out_ const IResourceMapBase** result) const;

    HRESULT GetResourceMapById(_In_ PCWSTR pSchemaId, _Out_ const IResourceMapBase** result) const;

    bool TryFindResourceMap(_In_ const HierarchicalSchemaReference* pRef, __deref_opt_out_opt const IResourceMapBase** ppMapOut) const;

    int GetNumDecisionInfos() const;

    HRESULT GetDecisionInfo(_In_ int index, _Out_ const DecisionInfoFileSection** result) const;

    virtual HRESULT GetTargetOsVersion(_Inout_opt_ StringResult* pPlatformOut, _Inout_opt_ StringResult* pVersionOut) const
    {
        return m_pDescriptor->GetTargetOsVersion(m_pView->GetProfile(), pPlatformOut, pVersionOut);
    }

    bool GetAutoMergeEnabled() const { return m_pDescriptor->GetAutoMergeEnabled(); }
    virtual bool GetIsDeploymentMergeable() const { return m_pDescriptor->GetIsDeploymentMergeable(); }

    bool GetIsDeploymentMergeResult() const { return m_pDescriptor->GetIsDeploymentMergeResult(); }

    HRESULT GetFileList(_In_ int index, _Out_ const FileFileList** result) const;

    bool TryGetReverseFileMap(_Outptr_opt_ const ReverseFileMap** ppMapOut) const;

protected:
    HRESULT
    InitPriFile(_In_ const IMrmFile* pFile, _In_opt_ IUnifiedResourceView* pView, _In_opt_ const ISchemaCollection* pOverrideSchema);

    PriFile();

    const IMrmFile* m_pFile;
    IUnifiedResourceView* m_pView;

    const PriDescriptor* m_pDescriptor;
};

class StandalonePriFile : public MrmFile, public PriFile
{
public:
    static HRESULT CreateInstance(
        _In_ UINT32 flags,
        _In_ PCWSTR pFileName,
        _In_ CoreProfile* pProfile,
        _Outptr_ StandalonePriFile** result);

    static HRESULT CreateInstance(
        _In_ UINT32 flags,
        _In_ PCWSTR pFileName,
        _In_ CoreProfile* pProfile,
        _In_ const ISchemaCollection* overrideSchemas,
        _Outptr_ StandalonePriFile** result);

    static HRESULT CreateInstance(
        _In_ UINT32 flags,
        _In_reads_bytes_(cbData) const BYTE* pData,
        _In_ size_t cbData,
        _In_ CoreProfile* pProfile,
        _Outptr_ StandalonePriFile** result);

    static HRESULT CreateInstance(
        _In_ UINT32 flags,
        _In_reads_bytes_(cbData) const BYTE* pData,
        _In_ size_t cbData,
        _In_ CoreProfile* pProfile,
        _In_ const ISchemaCollection* overrideSchemas,
        _Outptr_ StandalonePriFile** result);

    virtual AtomPoolGroup* GetAtoms() const { return m_pAtoms; }
    virtual UnifiedEnvironment* GetUnifiedEnvironment() const { return m_pEnvironment; }
    virtual UnifiedDecisionInfo* GetDefaultDecisionInfo() const { return m_pDecisions; }

    bool GetAutoMergeEnabled() const { return m_pDescriptor->GetAutoMergeEnabled(); }
    bool GetIsDeploymentMergeable() const { return m_pDescriptor->GetIsDeploymentMergeable(); }

    HRESULT GetTargetOsVersion(_Inout_opt_ StringResult* pPlatformOut, _Inout_opt_ StringResult* pVersionOut) const
    {
        return m_pDescriptor->GetTargetOsVersion(GetProfile(), pPlatformOut, pVersionOut);
    }

    virtual CoreProfile* GetProfile() const { return m_pProfile; }
    const PriDescriptor* GetPriDescriptor() const { return m_pDescriptor; }

    HRESULT GetSchema(_In_ int index, _Out_ const IHierarchicalSchema** result) const override;

    HRESULT GetPrimarySchema(_Out_ const IHierarchicalSchema** result) const override;

    HRESULT GetSchemaById(_In_ PCWSTR pSchemaId, _Out_ const IHierarchicalSchema** result) const override;

    virtual ~StandalonePriFile();

protected:
    StandalonePriFile() : MrmFile(), PriFile(), m_pAtoms(nullptr), m_pEnvironment(nullptr), m_pDecisions(nullptr) {}

    HRESULT Init(_In_ CoreProfile* pProfile, _In_ const ISchemaCollection* overrideSchemas, _In_ UINT32 flags, _In_ PCWSTR pFileName);

    HRESULT Init(
        _In_ CoreProfile* pProfile,
        _In_ const ISchemaCollection* overrideSchemas,
        _In_ UINT32 flags,
        _In_reads_bytes_(cbData) const BYTE* pData,
        _In_ size_t cbData);

    HRESULT InitEnvironmentAndDecisions();

    HRESULT InitStandalonePriFile(_In_opt_ const ISchemaCollection* overrideSchemas);

    CoreProfile* m_pProfile;
    const ISchemaCollection* m_overrideSchemas;
    AtomPoolGroup* m_pAtoms;
    UnifiedEnvironment* m_pEnvironment;
    UnifiedDecisionInfo* m_pDecisions;
};

} // namespace Microsoft::Resources