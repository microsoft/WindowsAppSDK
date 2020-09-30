// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "mrm/Results.h"
#include "mrm/Atoms.h"
#include "mrm/build/AIDict.h"
#include "mrm/common/file/MrmFiles.h"
#include "mrm/build/DefList.h"
#include "mrm/readers/MrmReaders.h"
#include "mrm/build/filelistbuilder.h"
#include "mrm/build/SectionBuilders.h"
#include "mrm/build/HNamesBuilder.h"
#include "mrm/platform/WindowsCore.h"

namespace Microsoft::Resources
{

class MrmProfile;

namespace Build
{

class EnvironmentReferenceBuilder : public EnvironmentReference
{
protected:
    EnvironmentReferenceBuilder() : EnvironmentReference() {}

public:
    static HRESULT CreateInstance(_In_ const MRMFILE_ENVIRONMENT_REF* pFileRef, _Outptr_ EnvironmentReferenceBuilder** result);
    static HRESULT CreateInstance(_In_ const IEnvironment* pEnvironment, _Outptr_ EnvironmentReferenceBuilder** result);

    size_t GetMaxSizeInBytes() const { return sizeof(MRMFILE_ENVIRONMENT_REF); }

    HRESULT
    Build(_Out_writes_bytes_to_(cbBuffer, *pcbWrittenOut) void* pBuffer, _In_ size_t cbBuffer, _Out_opt_ size_t* pcbWrittenOut) const;
};

class EnvironmentMappingSectionBuilder : public ISectionBuilder
{
public:
    static HRESULT CreateInstance(
        _In_ const IEnvironment* currentEnvironment,
        _In_ const IEnvironment* baseEnvironment,
        _Outptr_ EnvironmentMappingSectionBuilder** result);

    virtual ~EnvironmentMappingSectionBuilder();

    static bool IsMappingRequired(_In_ const IEnvironment* currentEnvironment, _In_ const IEnvironment* baseEnvironment);

    bool IsValid() const;

    HRESULT Finalize();

    bool IsFinalized() const { return (m_finalizedSizeInBytes > 0); }

    UINT32 GetMaxSizeInBytes() const;

    HRESULT
    Build(
        _Out_writes_bytes_to_(bufferSizeInBytes, *numBytesWritten) VOID* buffer,
        _In_ UINT32 bufferSizeInBytes,
        _Out_opt_ UINT32* numBytesWritten) const;

    DEFFILE_SECTION_TYPEID GetSectionType() const { return gEnvironmentMappingSectionType; }
    UINT16 GetFlags() const { return 0; }
    UINT16 GetSectionFlags() const { return 0; }
    UINT32 GetSectionQualifier() const { return 0; }

    void SetSectionIndex(_In_ BaseFile::SectionIndex sectionIndex) { m_sectionIndex = sectionIndex; }
    BaseFile::SectionIndex GetSectionIndex() const { return m_sectionIndex; }

private:
    MRMFILE_ENVIRONMENT_MAPPING_HEADER m_header;

    _Field_size_(m_header.numNewQualifiers) PCWSTR* m_names;

    _Field_size_(m_header.namesPoolSizeInChars) PWSTR m_namesPool;

    UINT32 m_finalizedSizeInBytes;
    BaseFile::SectionIndex m_sectionIndex;

    EnvironmentMappingSectionBuilder() : m_names(nullptr), m_namesPool(nullptr), m_finalizedSizeInBytes(0) {}

    HRESULT Init(_In_ const IEnvironment* pSourceEnvironment, _In_ const IEnvironment* pTargetEnvironment);
};

typedef enum
{
    PriBuildFromScratch = 0x00,
    PriBuildFromPrevSchema = 0x01,
    PriBuildFromPrevReadOnlySchema = 0x02,
    PriBuildForDeploymentMerge = 0x04
} PriBuildType;

typedef enum
{
    PriUninitialized = 0x1,
    PriInitialized = 0x2,
    PriFinalizedSection = 0x3,
    PriFinalizedAll = 0x4,
    PriReleasedOwnership = 0x5
} PriBuilderPhase;

class HierarchicalSchemaVersionInfoBuilder : public IHierarchicalSchemaVersionInfo
{
public:
    static HRESULT CreateInstance(
        _In_ const IHierarchicalSchema* pSchema,
        _In_ int majorVersion,
        _In_ int minorVersion,
        _Outptr_ HierarchicalSchemaVersionInfoBuilder** result);

    size_t GetMaxSizeInBytes() const;

    HRESULT
    Build(_Out_writes_bytes_to_(cbBuffer, *pcbWrittenOut) void* pBuffer, _In_ size_t cbBuffer, _Out_opt_ UINT32* pcbWrittenOut) const;

    // IHierarchicalSchemaVersionInfo implementation
    UINT16 GetMajorVersion() const { return m_major; }
    UINT16 GetMinorVersion() const { return m_minor; }

    DEF_CHECKSUM GetVersionChecksum() const;

    int GetNumScopes() const { return m_pSchema->GetNumScopes(); }
    int GetNumItems() const { return m_pSchema->GetNumItems(); }

protected:
    UINT16 m_major;
    UINT16 m_minor;
    const IHierarchicalSchema* m_pSchema;

    HierarchicalSchemaVersionInfoBuilder(_In_ const IHierarchicalSchema* pSchema, _In_ UINT16 majorVersion, _In_ UINT16 minorVersion);
};

class PriSectionBuilder;

class HierarchicalSchemaSectionBuilder : public ISectionBuilder, public IHierarchicalSchema
{
public:
    // builds a new schema from scratch
    static HRESULT CreateInstance(
        _In_ PriSectionBuilder* pPriBuilder,
        _In_ PCWSTR pDisplayName,
        _In_ PCWSTR pUniqueName,
        _In_ UINT16 majorVersion,
        _Outptr_ HierarchicalSchemaSectionBuilder** result);

    // builds a new schema based on a previous schema
    static HRESULT CreateInstance(
        _In_ PriSectionBuilder* pPriBuilder,
        _In_ const IHierarchicalSchema* const pPreviousSchema,
        _In_ PriBuildType priBuildType,
        _Outptr_ HierarchicalSchemaSectionBuilder** result);

    // build a new schema based on raw data from a previous schema
    static HRESULT CreateInstanceFromDescription(
        _In_ PriSectionBuilder* pPriBuilder,
        _In_ const IHierarchicalSchemaDescription* pDescription,
        _In_ PriBuildType priBuildType,
        _Outptr_ HierarchicalSchemaSectionBuilder** result);

    virtual ~HierarchicalSchemaSectionBuilder();

    PCWSTR GetSimpleId() const { return m_pSimpleId; }
    PCWSTR GetUniqueId() const { return m_pUniqueId; }

    int GetNumVersionInfos() const { return 1; }

    const IHierarchicalSchemaVersionInfo* GetVersionInfo(_In_ int index = 0) const;

    UINT16 GetMajorVersion() const { return m_majorVersion; }
    UINT16 GetMinorVersion() const { return m_minorVersion; }

    int GetNumNames() const;
    int GetNumScopes() const;
    int GetNumItems() const;

    IAtomPool* GetScopeNames() const;
    IAtomPool* GetItemNames() const;

    bool Contains(_In_ PCWSTR path, _Out_opt_ int* pScopeIndexOut = nullptr, _Out_opt_ int* pItemIndexOut = nullptr) const;
    bool Contains(
        _In_ PCWSTR path,
        _In_ int relativeToPath,
        _Out_opt_ int* pScopeIndexOut = nullptr,
        _Out_opt_ int* pItemIndexOut = nullptr) const;
    bool ContainsScope(_In_ PCWSTR scopeName, _Out_opt_ int* foundScopeIndex = nullptr) const;
    bool ContainsItem(_In_ PCWSTR itemName, _Out_opt_ int* foundItemIndex = nullptr) const;

    HRESULT GetOrAddScope(_In_ PCWSTR pItemName, _Out_ int* index);
    HRESULT GetOrAddItem(_In_ PCWSTR pItemName, _Out_ int* index);

    bool TryGetScopeInfo(_In_ int scopeIndex, _Out_ StringResult* pNameOut, _Out_opt_ int* pNumChildrenOut = nullptr) const;
    bool TryGetScopeChild(_In_ int scopeIndex, _In_ int childIndex, _Out_opt_ int* pChildScopeIndexOut, _Out_opt_ int* pChildItemIndexOut)
        const;
    bool TryGetScopeChildName(_In_ int scopeIndex, _In_ int childIndex, _Inout_opt_ StringResult* pNameOut) const;
    bool TryGetItemInfo(_In_ int itemIndex, _Inout_ StringResult* pNameOut) const;
    bool TryGetItemLocalName(_In_ int itemIndex, _Inout_ StringResult* pNameOut) const;
    bool TryGetRelativeItemName(_In_ int relativeToScope, _Inout_ int itemIndex, _Inout_ StringResult* pNameOut) const;
    bool TryGetRelativeScopeName(_In_ int relativeToScope, _Inout_ int scopeIndex, _Inout_ StringResult* pNameOut) const;
    HRESULT GetNumDescendents(_In_ int scopeIndex, _Out_opt_ int* pNumScopes, _Out_opt_ int* pNumItems) const;

    HRESULT GetDescendents(
        _In_ int scopeIndex,
        _In_ int sizeScopes,
        _Out_writes_to_opt_(sizeScopes, *pNumScopesWritten) int* pScopesOut,
        _Out_opt_ int* pNumScopesWritten,
        _In_ int sizeItems,
        _Out_writes_to_opt_(sizeItems, *pNumItemsWritten) int* pItemsOut,
        _Out_opt_ int* pNumItemsWritten) const;

    HRESULT Clone(_Outptr_ IHierarchicalSchema** result) const;

    HRESULT GetSchemaBlobFromFileSection(_Inout_opt_ DEFFILE_SECTION_TYPEID* pSectionTypeResult, _Inout_opt_ BlobResult* pBlobResult) const;

    bool IsValid() const;

    HRESULT Finalize();

    UINT32 GetMaxSizeInBytes() const;

    HRESULT Build(_Out_writes_bytes_(cbBuffer) VOID* pBuffer, _In_ UINT32 cbBuffer, _Out_opt_ UINT32* pcbWrittenOut) const;

    DEFFILE_SECTION_TYPEID GetSectionType() const;

    UINT16 GetFlags() const { return 0; }
    UINT16 GetSectionFlags() const { return 0; }
    UINT32 GetSectionQualifier() const { return 0; }

    void SetSectionIndex(_In_ BaseFile::SectionIndex sectionIndex) { m_sectionIndex = sectionIndex; }
    BaseFile::SectionIndex GetSectionIndex() const { return m_sectionIndex; }

private:
    bool IsFinalized() const;

    HRESULT ReadPreviousSchemaContents();

    HRESULT ReadSchemaDescription(_In_ const IHierarchicalSchemaDescription* pDescription);

    bool m_finalized;
    int m_numFinalizedScopes;
    int m_numFinalizedItems;
    int m_cchUniqueId;
    int m_cchSimpleId;
    int m_cbNamesBlob;

    BaseFile::SectionIndex m_sectionIndex;

    mutable HierarchicalSchemaVersionInfoBuilder* m_pVersionInfo;

    PriSectionBuilder* m_pPriBuilder;

    int m_numPreviousScopes;
    int m_numPreviousItems;
    int m_numPreviousMinorVersion;

    PWSTR m_pSimpleId;
    PWSTR m_pUniqueId;

    PriBuildType m_priBuildType;
    bool m_bIsVersionUpdated;
    UINT16 m_majorVersion;
    UINT16 m_minorVersion;

    HierarchicalNamesBuilder* m_pNames;
    const IAtomPool* m_pScopeNames;
    const IAtomPool* m_pItemNames;
    const IHierarchicalSchema* m_pPreviousSchema;

    UINT32 m_buildFlags;

    HierarchicalSchemaSectionBuilder();

    HRESULT Init(_In_ PriSectionBuilder* pPriBuilder, _In_ PCWSTR pSimpleId, _In_ PCWSTR pUniqueId, UINT16 majorVersion);

    HRESULT Init(_In_ PriSectionBuilder* pPriBuilder, _In_ const IHierarchicalSchema* const pPreviousSchema, PriBuildType priBuildType);
};

class HierarchicalSchemaReferenceSectionBuilder : public ISectionBuilder
{
public:
    static HRESULT CreateInstance(_In_ IHierarchicalSchema* schemaToReference, _Outptr_ HierarchicalSchemaReferenceSectionBuilder** result);

    HierarchicalSchemaReferenceSectionBuilder() {}

    bool IsValid() const;

    HRESULT Finalize() { return S_OK; }

    UINT32 GetMaxSizeInBytes() const;

    HRESULT
    Build(_Out_writes_bytes_to_(bufferSize, *bytesWritten) VOID* buffer, _In_ UINT32 bufferSize, _Out_opt_ UINT32* bytesWritten) const;

    DEFFILE_SECTION_TYPEID GetSectionType() const { return gHierarchicalSchemaSectionReferenceType; }

    UINT16 GetFlags() const { return 0; }
    UINT16 GetSectionFlags() const { return 0; }
    UINT32 GetSectionQualifier() const { return 0; }

    void SetSectionIndex(_In_ BaseFile::SectionIndex sectionIndex) { m_sectionIndex = sectionIndex; }
    BaseFile::SectionIndex GetSectionIndex() const { return m_sectionIndex; }

private:
    HierarchicalSchemaReferenceSectionBuilder(_In_ IHierarchicalSchema* schemaToReference);

    UINT32 GetUniqueIdLength() const;

    IHierarchicalSchema* m_schemaToReference;
    BaseFile::SectionIndex m_sectionIndex;
};

class ResourceMapSectionBuilder;

class ReverseFileMapSectionBuilder : public ISectionBuilder
{
public:
    static HRESULT CreateInstance(
        _In_ PriSectionBuilder* pPriBuilder,
        _In_ const UnifiedEnvironment* pEnvironment,
        _Outptr_ ReverseFileMapSectionBuilder** result);

    virtual ~ReverseFileMapSectionBuilder();

    HRESULT GenerateMap(_In_ DynamicArray<ResourceMapSectionBuilder*>* pResourceMapBuilders);

    bool IsValid() const;

    HRESULT Finalize();

    UINT32 GetMaxSizeInBytes() const;

    HRESULT Build(_Out_writes_bytes_(cbBuffer) VOID* pBuffer, _In_ UINT32 cbBuffer, _Out_opt_ UINT32* pcbWrittenOut) const;

    DEFFILE_SECTION_TYPEID GetSectionType() const { return ReverseFileMap::GetSectionTypeId(); }
    UINT16 GetFlags() const { return 0; }
    UINT16 GetSectionFlags() const { return 0; }
    UINT32 GetSectionQualifier() const { return 0; }

    void SetSectionIndex(_In_ BaseFile::SectionIndex sectionIndex) { m_sectionIndex = sectionIndex; }
    BaseFile::SectionIndex GetSectionIndex() const { return m_sectionIndex; }

private:
    bool IsMapGenerated() const { return m_mapGenerated; }

    bool IsFinalized() const;

    bool ChildIsScope(_In_ int scopeIndex, _In_ int childIndex);

    HRESULT AddEntry(_In_ int resourceId, _In_ int qualifierSetIndex, _Out_ int* index);

    HRESULT
    ReadCandidates(_In_ int itemIndex, _In_ DynamicArray<ResourceMapSectionBuilder*>* pResourceMapBuilders, _In_ ScopeInfo* pScopeInfo);

    HRESULT ReadSubTreeRecursive(
        _In_ int scopeIndex,
        _In_ DynamicArray<ResourceMapSectionBuilder*>* pResourceMapBuilders,
        _In_ ScopeInfo* pScopeInfo);

    bool m_mapGenerated;
    bool m_finalized;

    int m_numFileCandidates;
    int m_numFinalizedItems;
    UINT32 m_cbNamesBlob;

    BaseFile::SectionIndex m_sectionIndex;

    PriSectionBuilder* m_pPriSectionBuilder;
    HierarchicalSchemaSectionBuilder* m_pSchema;
    const UnifiedEnvironment* m_pEnvironment;
    HierarchicalNamesBuilder* m_pNames;
    DynamicArray<MRMFILE_REVERSEFILEMAP_ENTRY>* m_pEntries;

    UINT32 m_buildFlags;

    ReverseFileMapSectionBuilder(_In_ PriSectionBuilder* pPriBuilder, _In_ const UnifiedEnvironment* pEnvironment);

    HRESULT Init();
};

class IResourceLinkBuilder
{
public:
    virtual HierarchicalSchemaSectionBuilder* GetSchema() const = 0;

    virtual HRESULT AddResourceLink(_In_ PCWSTR linkFromResourceName, _In_ PCWSTR linkToResourceName) = 0;

    virtual HRESULT AddResourceLink(_In_ int linkFromResourceIndex, _In_ PCWSTR linkToResourceName) = 0;

    virtual HRESULT AddResourceLink(
        _In_ PCWSTR linkFromResourceName,
        _In_ const HierarchicalSchemaSectionBuilder* linkToSchema,
        _In_ PCWSTR linkToResourceName) = 0;

    virtual HRESULT AddResourceLink(
        _In_ int linkFromResourceIndex,
        _In_ const HierarchicalSchemaSectionBuilder* linkToSchema,
        _In_ PCWSTR linkToResourceName) = 0;
};

class ResourceLinkSectionBuilder : public ISectionBuilder, public IResourceLinkBuilder
{
public:
    static HRESULT CreateInstance(_In_ HierarchicalSchemaSectionBuilder* schema, _Outptr_ ResourceLinkSectionBuilder** result);

    virtual ~ResourceLinkSectionBuilder();

    bool TryGetResourceIndex(_In_ int schemaIndex, _In_ PCWSTR resourceName, _Out_ Atom::Index* resourceIndex) const;

    bool TryGetResourceLinkByResourceIndex(
        _In_ int resourceIndexInSchema,
        _Out_opt_ int* linksToSchemaIndex,
        _Out_opt_ int* linksToResourceIndex) const;

    HRESULT AddResourceLink(_In_ PCWSTR linkFromResourceName, _In_ PCWSTR linkToResourceName);

    HRESULT AddResourceLink(_In_ int linkFromResourceIndex, _In_ PCWSTR linkToResourceName);

    HRESULT AddResourceLink(
        _In_ PCWSTR linkFromResourceName,
        _In_ const HierarchicalSchemaSectionBuilder* linkToSchema,
        _In_ PCWSTR linkToResourceName);

    HRESULT AddResourceLink(
        _In_ int linkFromResourceIndex,
        _In_ const HierarchicalSchemaSectionBuilder* linkToSchema,
        _In_ PCWSTR linkToResourceName);

    HierarchicalSchemaSectionBuilder* GetSchema() const { return m_schema; }

    bool IsValid() const;

    HRESULT Finalize();

    UINT32 GetMaxSizeInBytes() const;

    HRESULT
    Build(_Out_writes_bytes_(bufferSizeInBytes) VOID* buffer, _In_ UINT32 bufferSizeInBytes, _Out_opt_ UINT32* numBytesWritten) const;

    DEFFILE_SECTION_TYPEID GetSectionType() const { return ResourceLinkSection::GetSectionTypeId(); }
    UINT16 GetFlags() const { return 0; }
    UINT16 GetSectionFlags() const { return 0; }
    UINT32 GetSectionQualifier() const { return 0; }

    void SetSectionIndex(_In_ BaseFile::SectionIndex sectionIndex) { m_sectionIndex = sectionIndex; }
    BaseFile::SectionIndex GetSectionIndex() const { return m_sectionIndex; }

private:
    struct SchemaRef
    {
        const HierarchicalSchemaSectionBuilder* section;
        const HierarchicalSchemaReference* ref;
    };

    enum FinalizedLinkType
    {
        SmallInternal = 0,
        LargeInternal = 1,
        SmallFull = 2,
        LargeFull = 3
    };

    struct ItemRef
    {
        int linksToSchemaIndex;
        int linksToResourceIndex;
        FinalizedLinkType finalizedLinkType;
        UINT32 finalizedLinkIndex;
        PWSTR linksToResourceName;
    };

    static bool IsInternal(_In_ const ItemRef* item) { return (item->linksToSchemaIndex == 0); }

    static bool IsLarge(_In_ const ItemRef* item) { return ((item->linksToResourceIndex & ~0xffff) != 0); }

    static bool IsLarge(_In_ UINT32 value) { return ((value & ~0xffff) != 0); }

    static bool IsResolved(_In_ const ItemRef* item) { return (item->linksToResourceIndex >= 0); }

    bool m_finalized;
    BaseFile::SectionIndex m_sectionIndex;

    HierarchicalSchemaSectionBuilder* m_schema;
    DefList<SchemaRef> m_schemas;
    AtomIndexedStructDictionary<ItemRef>* m_items;

    int m_numFinalizedSchemas;
    int m_finalizedSchemaDataSizeInBytes;

    int m_numFinalizedSmallInternalLinks;
    int m_numFinalizedLargeInternalLinks;

    int m_numFinalizedSmallFullLinks;
    int m_numFinalizedLargeFullLinks;

    int m_numFinalizedSmallLinksById;
    int m_numFinalizedLargeLinksById;

    HRESULT FinalizeSchemas();

    HRESULT FinalizeLinks();

    ResourceLinkSectionBuilder();

    HRESULT Init(_In_ HierarchicalSchemaSectionBuilder* schema);
};

class IBuildInstanceReference;
class DecisionInfoSectionBuilder;

typedef struct _BUILDER_CANDIDATE
{
    int qualifierSetIndex;
    int indexInDecision;
    IBuildInstanceReference* pBuildInstanceReference;
    MRMFILE_MAP_VALUE_LARGE value;
} BUILDER_CANDIDATE;

class BuilderCandidateResult : public DefObject
{
public:
    BuilderCandidateResult();

    void Set(
        _In_ const BUILDER_CANDIDATE* pBuilderCandidate,
        _In_ DecisionInfoSectionBuilder* pDecisionInfoBuilder,
        _In_ Atom instanceValueType);

    HRESULT GetQualifierSet(_Inout_ QualifierSetResult* pQualifierSetOut) const;

    int GetFileIndex() const;
    int GetSectionIndex() const;
    int GetItemIndex() const;

private:
    BUILDER_CANDIDATE m_builderCandidate;
    DecisionInfoSectionBuilder* m_pDecisionInfo;
    Atom m_instanceValueType;
};

class ResourceMapSectionBuilder : public ISectionBuilder, public IResourceLinkBuilder
{
public:
    // Creates a new, empty map based on a supplied schema
    static HRESULT CreateInstance(
        _In_ PriSectionBuilder* pPriBuilder,
        _In_ HierarchicalSchemaSectionBuilder* pSchemaBuilder,
        _In_ DecisionInfoSectionBuilder* pDecisionInfoBuilder,
        _In_ const UnifiedEnvironment* pEnvironment,
        _Outptr_ ResourceMapSectionBuilder** result);

    static HRESULT CreateInstance(
        _In_ PriSectionBuilder* pPriBuilder,
        _In_ HierarchicalSchemaSectionBuilder* pSchemaBuilder,
        _In_ DecisionInfoSectionBuilder* pDecisionInfoBuilder,
        _In_ const UnifiedEnvironment* pEnvironment,
        _In_ PriBuildType priBuildType,
        _Outptr_ ResourceMapSectionBuilder** result);

    virtual ~ResourceMapSectionBuilder();

    HierarchicalSchemaSectionBuilder* GetSchema() const { return m_pSchema; }
    DecisionInfoSectionBuilder* GetDecisionInfo() const { return m_pDecisionInfo; }
    const UnifiedEnvironment* GetEnvironment() const { return m_pEnvironment; }

    HRESULT GetResourceValueTypeAtom(_In_ MrmEnvironment::ResourceValueType valueType, _Out_ Atom* pAtomOut) const;

    HRESULT AddCandidateWithInternalString(
        _In_ PCWSTR pItemName,
        _In_ MrmEnvironment::ResourceValueType valueType,
        _In_ PCWSTR pValue,
        _In_opt_ IQualifierSet* pQualifiers);

    HRESULT
    AddCandidateWithInternalString(
        _In_ PCWSTR pItemName,
        _In_ MrmEnvironment::ResourceValueType valueType,
        _In_ PCWSTR pValue,
        _In_ int qualifierSetIndex);

    HRESULT
    AddCandidate(
        _In_ PCWSTR pItemName,
        _In_ MrmEnvironment::ResourceValueType valueType,
        _In_ IBuildInstanceReference* pBuildRef,
        _In_ int qualifierSetIndex);

    HRESULT AddCandidate(
        _In_ Atom::Index itemName,
        _In_ MrmEnvironment::ResourceValueType valueType,
        _In_ IBuildInstanceReference* pBuildInstanceReference,
        _In_ int qualifierSetIndex);

    ResourceLinkSectionBuilder* GetLinks() const { return m_links; }

    HRESULT AddResourceLink(_In_ PCWSTR linkFromResourceName, _In_ PCWSTR linkToResourceName);

    HRESULT AddResourceLink(_In_ int linkFromResourceIndex, _In_ PCWSTR linkToResourceName);

    HRESULT AddResourceLink(
        _In_ PCWSTR linkFromResourceName,
        _In_ const HierarchicalSchemaSectionBuilder* linkToSchema,
        _In_ PCWSTR linkToResourceName);

    HRESULT AddResourceLink(
        _In_ int linkFromResourceIndex,
        _In_ const HierarchicalSchemaSectionBuilder* linkToSchema,
        _In_ PCWSTR linkToResourceName);

    int GetTotalNumFinalizedValues() const;

    bool TryGetResourceInfo(_In_ int itemIndex, _Inout_opt_ StringResult* pNameOut, _Out_opt_ int* numCandidatesOut) const;

    bool TryGetResourceInfo(_In_ PCWSTR pResourceName, _Out_opt_ int* pIndexOut, _Out_opt_ int* numCandidatesOut) const;

    bool TryGetCandidateInfo(
        _In_ int itemIndex,
        _In_ int candidateIndex,
        _Inout_opt_ QualifierSetResult* pQualifierSetOut,
        _Out_opt_ MrmEnvironment::ResourceValueType* pTypeOut,
        _Inout_opt_ StringResult* pValueOut) const;

    bool TryGetCandidateInfo(
        _In_ PCWSTR pItemName,
        _In_ int candidateIndex,
        _Inout_opt_ QualifierSetResult* pQualifierSetOut,
        _Out_opt_ MrmEnvironment::ResourceValueType* pTypeOut,
        _Inout_opt_ StringResult* pValueOut,
        _Out_opt_ int* pItemIndexOut = nullptr) const;

    bool TryGetCandidateInfo(_In_ PCWSTR pItemName, _In_ int candidateIndex, _Inout_ BuilderCandidateResult* pBuilderCandidateResult) const;

    bool IsValid() const;

    HRESULT Finalize();

    UINT32 GetMaxSizeInBytes() const;

    virtual HRESULT Build(_Out_writes_bytes_(cbBuffer) VOID* pBuffer, _In_ UINT32 cbBuffer, _Out_opt_ UINT32* pcbWrittenOut) const;

    DEFFILE_SECTION_TYPEID GetSectionType() const;

    UINT16 GetFlags() const { return 0; }
    UINT16 GetSectionFlags() const { return 0; }
    UINT32 GetSectionQualifier() const { return 0; }

    void SetSectionIndex(_In_ BaseFile::SectionIndex sectionIndex) { m_sectionIndex = sectionIndex; }

    BaseFile::SectionIndex GetSectionIndex() const { return m_sectionIndex; }

    static const int MaxInternalDataSize = 0xffff;

protected:
    class MapBuilderItemData;
    class MapBuilderFileData;

    struct BuilderDirEntry
    {
        int itemIndexInSchema;
        int rangeInfoIndex;
        int itemInfoIndex;
        int length;
        int firstValueIndex;
    };

    HRESULT InitLinks();

    ResourceMapSectionBuilder(
        _In_ PriSectionBuilder* pPriBuilder,
        _In_ HierarchicalSchemaSectionBuilder* pSchemaBuilder,
        _In_ DecisionInfoSectionBuilder* pDecisionInfoBuilder,
        _In_ const UnifiedEnvironment* pEnvironment,
        _In_ PriBuildType priBuildType);

    HRESULT Init();

    HRESULT GetOrAddResourceValueTypeIndex(_In_ MrmEnvironment::ResourceValueType valueType, _Out_ int* pIndexOut);

    BaseFile::SectionIndex m_sectionIndex;
    bool m_finalized;

    PriSectionBuilder* m_pPriBuilder;
    HierarchicalSchemaSectionBuilder* m_pSchema;
    HierarchicalSchemaReferenceSectionBuilder* m_schemaReferenceBuilder;

    DecisionInfoSectionBuilder* m_pDecisionInfo;
    const UnifiedEnvironment* m_pEnvironment;

    ResourceLinkSectionBuilder* m_links;

    DynamicArray<Atom>* m_pValueTypes;
    DataBlobBuilder* m_pDataBuilder;

    MapBuilderItemData* m_pItems;

    DynamicArray<BuilderDirEntry>* m_pFinalizedDir;
    int m_cbFinalizedSchemaRef;

    int m_cbFinalizedEnvironmentRefs;

    int m_numFinalizedTotalRanges;
    int m_numFinalizedTotalItems;
    int m_numFinalizedValues;
    bool m_hasLargeValues;

    int m_numFinalizedStandardDirEntries;
    int m_numFinalizedStandardRanges;
    int m_numFinalizedStandardItems;

    int m_numFinalizedLargeDirEntries;
    int m_numFinalizedLargeRanges;
    int m_numFinalizedLargeItems;

    UINT32 m_cbFinalizedLargeData;
    PriBuildType m_priBuildType;
};

class IBuildInstanceReference : public DefObject
{

public:
    virtual ~IBuildInstanceReference() {}

    virtual int GetInstanceLocatorTypeIndex() const = 0;

    virtual HRESULT GenerateInstance(_Out_ MRMFILE_INDEX_INSTANCE* pInstanceIndex) const = 0;

    virtual bool IsReferenceEqual(_In_ const IBuildInstanceReference* pBuildInstanceReference) const = 0;

    virtual HRESULT GetDataBlob(_Inout_ BlobResult* pBlobResult) const = 0;

    virtual UINT8 GetLocatorType() const = 0;
};

class DataItemsBuildInstanceReference : public IBuildInstanceReference
{

public:
    ~DataItemsBuildInstanceReference() {}

    static HRESULT CreateInstance(
        _In_ DataItemsSectionBuilder* pBuilder,
        _In_ DataItemsSectionBuilder::PrebuildItemReference* pPreBuildItemReference,
        _Outptr_ DataItemsBuildInstanceReference** result);

    int GetInstanceLocatorTypeIndex() const { return MrmEnvironment::ResourceValueLocatorType_DataItemsSection; }

    HRESULT GenerateInstance(_Out_ MRMFILE_INDEX_INSTANCE* pInstanceIndex) const;

    bool IsReferenceEqual(_In_ const IBuildInstanceReference* pBuildInstanceReference) const;

    HRESULT GetDataBlob(_Inout_ BlobResult* pBlobResult) const;

    UINT8 GetLocatorType() const { return MRMFILE_MAP_VALUE_LOCATOR_DATA_ITEM; }

    DataItemsSectionBuilder* GetDataItemsSectionBuilder() { return m_pDISBuilder; }

private:
    DataItemsBuildInstanceReference(
        _In_ DataItemsSectionBuilder* pBuilder,
        _In_ DataItemsSectionBuilder::PrebuildItemReference* pPreBuildItemReference);

    DataItemsSectionBuilder* m_pDISBuilder;
    DataItemsSectionBuilder::PrebuildItemReference m_PreBuildReference;
};

class FileSectionBuildInstanceReference : public IBuildInstanceReference
{

public:
    ~FileSectionBuildInstanceReference() {}

    static HRESULT CreateInstance(
        _In_ FileListBuilder* pBuilder,
        _In_ FileInfo* pFileInfo,
        _Outptr_ FileSectionBuildInstanceReference** result);

    int GetInstanceLocatorTypeIndex() const { return MrmEnvironment::ResourceValueLocatorType_FileList; }

    HRESULT GenerateInstance(_Out_ MRMFILE_INDEX_INSTANCE* pInstanceIndex) const;

    bool IsReferenceEqual(_In_ const IBuildInstanceReference* pBuildInstanceReference) const;

    HRESULT GetDataBlob(_Inout_ BlobResult* pBlobResult) const;

    UINT8 GetLocatorType() const { return MRMFILE_MAP_VALUE_LOCATOR_FILE_ITEM; }

private:
    FileSectionBuildInstanceReference(_In_ FileListBuilder* pBuilder, _In_ FileInfo* pFileInfo);

    FileListBuilder* m_pFileListBuilder;
    FileInfo* m_pFileInfo;
};

class ExternalFileStaticDataInstanceReference : public IBuildInstanceReference
{

public:
    ~ExternalFileStaticDataInstanceReference() {}

    static HRESULT CreateInstance(
        _In_ ResourceCandidateResult* pResourceCandidateResult,
        _In_ const FileInfo* pFileInfo,
        _Outptr_ ExternalFileStaticDataInstanceReference** result);

    int GetInstanceLocatorTypeIndex() const { return MrmEnvironment::ResourceValueLocatorType_DataItemsSection; }

    HRESULT GenerateInstance(_Out_ MRMFILE_INDEX_INSTANCE* pInstanceIndex) const;

    bool IsReferenceEqual(_In_ const IBuildInstanceReference* pBuildInstanceReference) const;

    HRESULT GetDataBlob(_Inout_ BlobResult* pBlobResult) const;

    UINT8 GetLocatorType() const { return MRMFILE_MAP_VALUE_LOCATOR_DATA_ITEM; }

private:
    ExternalFileStaticDataInstanceReference(_In_ ResourceCandidateResult* pResourceCandidateResult, _In_ const FileInfo* pFileInfo);

    HRESULT Init();

    MRMFILE_INDEX_INSTANCE m_mrmIndexInstance;
    const FileInfo* m_pFileInfo;
    ResourceCandidateResult m_resourceCandidateResult;
};

struct BuilderPrioritizedCondition : public DefObject
{
public:
    UINT16 baseConditionIndex;
    UINT16 conditionIndex;
    DEF_ATOM_SMALL attribute;
    DEF_ATOM_SMALL op;
    UINT32 valueOffset;
    UINT16 priority;
    UINT16 fallbackScore;
};

class DecisionInfoQualifierSetBuilder;
class DecisionBuilder;
class DecisionInfoBuilderData;

struct MrmBcQualifier
{
    PCWSTR QualifierName;
    PCWSTR QualifierValue;
    UINT32 Priority;
    double FallbackScore;
};

class DecisionInfoBuilder : public IDecisionInfo
{
public:
    static const UINT32 RejectUnknownQualifiersFlag = 0x00;
    static const UINT32 AllowUnknownQualifiersFlag = 0x01;

    static const UINT32 UnknownQualifiersMask = 0x01;
    static const UINT32 DefaultFlags = 0x00;

    static HRESULT CreateInstance(_In_ const UnifiedEnvironment* environment, _Outptr_ DecisionInfoBuilder** result)
    {
        return CreateInstance(DefaultFlags, environment, nullptr, result);
    }

    static HRESULT CreateInstance(
        _In_ const UnifiedEnvironment* environment,
        _In_opt_ const IDecisionInfo* baseDecisionInfo,
        _Outptr_ DecisionInfoBuilder** result)
    {
        return CreateInstance(DefaultFlags, environment, baseDecisionInfo, result);
    }

    static HRESULT CreateInstance(
        _In_ UINT32 flags,
        _In_ const UnifiedEnvironment* environment,
        _In_opt_ const IDecisionInfo* baseDecisionInfo,
        _Outptr_ DecisionInfoBuilder** result);

    virtual ~DecisionInfoBuilder();

    HRESULT Merge(
        _In_ const IDecisionInfo* pMerge,
        _Inout_opt_ RemapUInt16* pQualifierMap = nullptr,
        _Inout_opt_ RemapUInt16* pQualifierSetMap = nullptr,
        _Inout_opt_ RemapUInt16* pDecisionMap = nullptr);

    const UnifiedEnvironment* GetEnvironment() const;

    HRESULT GetOrAddQualifier(
        _In_ Atom qualifierName,
        _In_ ICondition::ConditionOperator op,
        _In_opt_ PCWSTR pQualifierValue,
        _In_ UINT16 priority,
        _In_ double fallbackScore,
        _Inout_opt_ QualifierResult* pQualifierOut = nullptr);

    HRESULT GetOrAddQualifier(
        _In_opt_ PCWSTR pQualifierName,
        _In_ ICondition::ConditionOperator op,
        _In_opt_ PCWSTR pQualifierValue,
        _In_ UINT16 priority,
        _In_ double fallbackScore,
        _Inout_opt_ QualifierResult* pQualifierOut = nullptr);

    HRESULT GetOrAddQualifier(
        _In_ PCWSTR pQualifierName,
        _In_ PCWSTR pQualifierValue,
        _In_ UINT16 priority,
        _In_ double fallbackScore,
        _Inout_opt_ QualifierResult* pQualifierOut = nullptr)
    {
        return GetOrAddQualifier(pQualifierName, ICondition::MatchOp, pQualifierValue, priority, fallbackScore, pQualifierOut);
    }

    // default priority, implied ICondition::MatchOp operator.
    HRESULT
    GetOrAddQualifier(
        _In_ PCWSTR pQualifierName,
        _In_ PCWSTR pQualifierValue,
        _In_ double fallbackScore,
        _Inout_opt_ QualifierResult* pQualifierOut = nullptr);

    HRESULT GetOrAddQualifier(_In_ const IQualifier* pQualifier, _Out_opt_ int* pIndexOut);

    int GetNumQualifiers() const;

    HRESULT GetQualifier(_In_ int index, _Inout_ QualifierResult* pConditionOut) const;

    HRESULT GetOrAddQualifierSet(_In_opt_ const IQualifierSet* pQualifierSet, _Out_opt_ int* pIndexOut = nullptr);

    HRESULT GetOrAddQualifierSet(
        _In_opt_ const IQualifierSet* pQualifierSet,
        _In_opt_ RemapUInt16* pQualifierMapRemapInfo,
        _Out_opt_ int* pIndexOut = nullptr);

    int GetNumQualifierSets() const;

    HRESULT GetQualifierSet(_In_ int index, _Inout_ QualifierSetResult* pSetOut) const;

    HRESULT GetOrAddDecision(_In_ const IDecision* pDecision, _Out_opt_ int* pIndexOut = nullptr);

    HRESULT GetOrAddDecision(
        _In_ const IDecision* pNewDecision,
        _In_opt_ RemapUInt16* pQualifierSetMapRemapInfo,
        _Out_opt_ int* pIndexOut = nullptr);

    int GetNumDecisions() const;

    HRESULT GetDecision(_In_ int index, _Inout_ DecisionResult* pDecisionOut) const;

    HRESULT GetDecisionNumQualifierSets(_In_ int index, _Out_ int* pNumSetsOut) const;

    void GetAlwaysTrueConditionIndex(_Out_ int* pIndexOut) const;

    void GetUnconditionalQualifierSetIndex(_Out_ int* pIndexOut) const;

    void GetEmptyDecisionIndex(_Out_ int* pIndexOut) const;

    void GetNeutralOnlyDecisionIndex(_Out_ int* pIndexOut) const;

    bool IsValidQualifierIndex(int i) const { return (i >= 0) && (i < GetNumQualifiers()); }
    bool IsValidQualifierSetIndex(int i) const { return (i >= 0) && (i < GetNumQualifierSets()); }
    bool IsValidDecisionIndex(int i) const { return (i >= 0) && (i < GetNumDecisions()); }

    bool AllowUnknownQualifiers() const { return ((m_flags & UnknownQualifiersMask) == AllowUnknownQualifiersFlag); }

protected:
    DecisionInfoBuilder() : m_pData(nullptr) {}
    HRESULT Init(_In_ UINT32 flags, _In_ const UnifiedEnvironment* environment);

    HRESULT InitDefaultContents();

    DecisionInfoBuilderData* m_pData;
    UINT32 m_flags;
};

class DecisionInfoSectionBuilder : public ISectionBuilder, public DecisionInfoBuilder
{
public:
    static HRESULT CreateInstance(
        _In_ FileBuilder* pFileBuilder,
        _In_ const UnifiedEnvironment* pEnvironment,
        _Outptr_ DecisionInfoSectionBuilder** result);

    bool IsValid() const { return true; }

    HRESULT Finalize();

    UINT32 GetMaxSizeInBytes() const;

    virtual HRESULT Build(_Out_writes_bytes_(cbBuffer) VOID* pBuffer, _In_ UINT32 cbBuffer, _Out_opt_ UINT32* pcbWrittenOut) const;

    DEFFILE_SECTION_TYPEID GetSectionType() const { return gDecisionInfoSectionType; }
    UINT16 GetFlags() const { return 0; }
    UINT16 GetSectionFlags() const { return 0; }
    UINT32 GetSectionQualifier() const { return 0; }

    void SetSectionIndex(_In_ BaseFile::SectionIndex sectionIndex) { m_sectionIndex = sectionIndex; }

    BaseFile::SectionIndex GetSectionIndex() const { return m_sectionIndex; }

private:
    DecisionInfoSectionBuilder() : m_pFileBuilder(nullptr), m_sectionIndex(BaseFile::SectionIndexNone), m_finalized(false) {}

    HRESULT Init(_In_ FileBuilder* pFileBuilder, _In_ const UnifiedEnvironment* pEnvironment);

    FileBuilder* m_pFileBuilder;
    BaseFile::SectionIndex m_sectionIndex;
    bool m_finalized;
};

class DecisionInfoQualifierSetBuilder : public IQualifierSet
{
public:
    static HRESULT CreateInstance(_In_ DecisionInfoBuilder* pDecisionInfoBuilder, _Outptr_ DecisionInfoQualifierSetBuilder** result);

    virtual ~DecisionInfoQualifierSetBuilder();

    HRESULT AddQualifier(
        _In_ PCWSTR pAttribute,
        _In_ PCWSTR pValue,
        _In_ int priority,
        _In_ double fallbackScore,
        _Out_opt_ int* pIndexInSetOut = nullptr)
    {
        return AddQualifier(pAttribute, ICondition::MatchOp, pValue, priority, fallbackScore, pIndexInSetOut);
    }

    // default priority, implied ICondition::MatchOp operator.
    HRESULT AddQualifier(_In_ PCWSTR pAttribute, _In_ PCWSTR pValue, _In_ double fallbackScore, _Out_opt_ int* pIndexInSetOut = nullptr);

    HRESULT AddQualifiers(_In_ int numQualifiers, _In_reads_(numQualifiers) MrmBcQualifier* pQualifiers, _In_ bool useDefaults);

    int GetNumQualifiers() const;

    HRESULT GetQualifier(_In_ int indexInSet, _Inout_ QualifierResult* pQualifierOut, _Out_opt_ int* pIndexInPoolOut = nullptr) const;

    HRESULT GetQualifierIndexInPool(_In_ int indexInSet, _Out_ int* pIndexInPoolOut) const;

    int GetIndex() const { return m_index; }
    HRESULT GetIndex(_Out_ int* index) const
    {
        *index = m_index;
        return S_OK;
    }
    void SetIndex(_In_ int index) { m_index = index; }

    const IDecisionInfo* GetPool() const { return m_pDecisionInfo; }
    HRESULT GetPool(_Out_ const IDecisionInfo** result) const
    {
        *result = m_pDecisionInfo;
        return S_OK;
    }

    void Reset();

    HRESULT AddQualifier(
        _In_opt_ PCWSTR pAttribute,
        _In_ ICondition::ConditionOperator conditionOp,
        _In_opt_ PCWSTR pValue,
        _In_ int priority,
        _In_ double fallbackScore,
        _Out_opt_ int* pIndexInSetOut);

    // default priority
    HRESULT AddQualifier(
        _In_opt_ PCWSTR pAttribute,
        _In_ ICondition::ConditionOperator conditionOp,
        _In_opt_ PCWSTR pValue,
        _In_ double fallbackScore,
        _Out_opt_ int* pIndexInSetOut);

private:
    static const int InitialQualifiersSize = 4;

    DecisionInfoQualifierSetBuilder() : m_pDecisionInfo(nullptr), m_pQualifierIndexes(nullptr), m_index(-1) {}

    HRESULT Init(_In_ DecisionInfoBuilder* pDecisionInfoBuilder);

    DecisionInfoBuilder* m_pDecisionInfo;
    DynamicArray<UINT16>* m_pQualifierIndexes;
    int m_index;
};

class DecisionBuilder : public IDecision
{
public:
    static HRESULT CreateInstance(_In_ DecisionInfoBuilder* pDecisionInfoBuilder, _Outptr_ DecisionBuilder** result);

    virtual ~DecisionBuilder();

    HRESULT AddQualifierSet(_In_ const IQualifierSet* pQualifierSet, _Out_opt_ int* pIndexInDecisionOut = nullptr);
    HRESULT AddQualifierSet(_In_ int qualifierSetIndexInPool, _Out_opt_ int* pIndexInDecisionOut = nullptr);
    HRESULT AddQualifierSetForMerge(_In_ int qualifierSetIndexInPool, _Out_ int* pIndexInDecisionOut = nullptr);

    int GetNumQualifierSets() const;

    HRESULT
    GetQualifierSet(_In_ int indexInDecision, _Inout_ QualifierSetResult* pQualifierSetOut, _Out_opt_ int* pIndexInPoolOut = nullptr) const;
    HRESULT GetQualifierSetIndexInPool(_In_ int indexInDecision, _Out_ int* pIndexInPoolOut) const;
    HRESULT GetQualifierSetIndexInDecision(_In_ int indexInPool, _Out_ int* pIndexInDecisionOut) const;

    int GetIndex() const { return m_index; }
    HRESULT GetIndex(_Out_ int* index) const
    {
        *index = m_index;
        return S_OK;
    }

    void SetIndex(_In_ int index) { m_index = index; }

    const IDecisionInfo* GetPool() const { return m_pDecisionInfo; }
    HRESULT GetPool(_Out_ const IDecisionInfo** result) const
    {
        *result = m_pDecisionInfo;
        return S_OK;
    }

    void Reset();

private:
    static const int InitialQualifierSetsSize = 4;

    DecisionBuilder() : m_pDecisionInfo(nullptr), m_pQualifierSetIndexes(nullptr), m_index(-1) {}

    HRESULT Init(_In_ DecisionInfoBuilder* pDecisionInfoBuilder);

    DecisionInfoBuilder* m_pDecisionInfo;
    DynamicArray<UINT16>* m_pQualifierSetIndexes;
    int m_index;
};

class OrchestratorDataReference : public IBuildInstanceReference
{
public:
    ~OrchestratorDataReference() { delete m_metadata; }

    static HRESULT CreateInstance(
        _In_ DEF_CHECKSUM valueHash,
        _In_reads_bytes_(valueSizeInBytes) const void* actualValue,
        _In_ size_t valueSizeInBytes,
        _In_ DataItemsSectionBuilder* pBuilder,
        _In_ DataItemsSectionBuilder::PrebuildItemReference* pPreBuildItemReference,
        _Out_ OrchestratorDataReference** result);

    static HRESULT CloneDataReference(_In_ OrchestratorDataReference* sourceDataRef, _Outptr_ OrchestratorDataReference** result);

    int GetInstanceLocatorTypeIndex() const { return MrmEnvironment::ResourceValueLocatorType_DataItemsSection; }

    HRESULT GenerateInstance(_Out_ MRMFILE_INDEX_INSTANCE* pInstanceIndex) const;

    bool IsReferenceEqual(_In_ const IBuildInstanceReference* pBuildInstanceReference) const;

    HRESULT GetDataBlob(_Inout_ BlobResult* pBlobResult) const;

    UINT8 GetLocatorType() const { return MRMFILE_MAP_VALUE_LOCATOR_DATA_ITEM; }

    DEF_CHECKSUM GetValueHash() const { return m_valueHash; }

    const void* GetActualValue() const;

    size_t GetActualValueSize() const;

    DataItemsSectionBuilder::PrebuildItemReference GetInnerReference() const { return m_innerReference; }

private:
    OrchestratorDataReference(
        _In_ DEF_CHECKSUM valueHash,
        _In_ DataItemsSectionBuilder* pBuilder,
        _In_ DataItemsSectionBuilder::PrebuildItemReference* pPreBuildItemReference);

    HRESULT Init(_In_reads_bytes_(valueSizeInBytes) const void* actualValue, _In_ size_t valueSizeInBytes);

    DataItemsSectionBuilder* m_disBuilder;
    DataItemsSectionBuilder::PrebuildItemReference m_innerReference;

    DEF_CHECKSUM m_valueHash;
    BlobResult m_actualDataBlob;
    DynamicArray<UINT>* m_metadata;
};

class OrchestratorHashNode : public DefObject
{
public:
    static HRESULT CreateInstance(
        _In_ DEF_CHECKSUM valueHash,
        _In_ OrchestratorDataReference* dataReference,
        _Outptr_ OrchestratorHashNode** result);

    bool SetNext(_In_ OrchestratorHashNode* inputNode);

    ~OrchestratorHashNode() {}

    OrchestratorDataReference* GetDataReference() const { return m_dataReference; }
    DEF_CHECKSUM GetHash() const { return m_valueHash; }
    OrchestratorHashNode* GetNext() const { return m_nextOrchHashNode; }

private:
    OrchestratorHashNode(_In_ DEF_CHECKSUM valueHash, _In_ OrchestratorDataReference* dataReference);

    OrchestratorHashNode* m_nextOrchHashNode;
    DEF_CHECKSUM m_valueHash;
    OrchestratorDataReference* m_dataReference;
};

class OrchestratorHashMap : public DefObject
{
public:
    virtual ~OrchestratorHashMap();

    static HRESULT CreateInstance(_In_ int initCapacity, _In_ float loadFactor, _Outptr_ OrchestratorHashMap** result);

    int Count() const { return m_nodeCount; }

    HRESULT AddtoMap(_In_ DEF_CHECKSUM key, _In_ OrchestratorDataReference* value);

    int HashCode(_In_ DEF_CHECKSUM key);

    int HashCode(_In_ size_t newSize, _In_ DEF_CHECKSUM key);

    OrchestratorDataReference* TryGetFromMap(_In_ DEF_CHECKSUM key, _In_opt_ const void* value, _In_opt_ size_t valueSizeInBytes);

private:
    HRESULT ResizeMap();

    OrchestratorHashMap(_In_ int initCapacity, _In_ float loadFactor);

    HRESULT Init(int initCapacity);

    int m_nodeCount;
    int m_currentSize;
    float m_loadFactor;
    DynamicArray<OrchestratorHashNode*>* m_entries;
};

class DataItemOrchestrator : public DefObject
{
public:
    static HRESULT CreateInstance(
        _In_ FileBuilder* fileBuilder,
        _In_ CoreProfile* profile,
        _In_ DecisionInfoSectionBuilder* decisionInfo,
        _Outptr_ DataItemOrchestrator** result);

    virtual ~DataItemOrchestrator();
    virtual HRESULT Finalize();
    virtual int GetNumFinalizedDataItemSections() const;
    virtual HRESULT GetFinalizedDataItemSection(_In_ int index, _Out_ DataItemsSectionBuilder** result) const;

    void DisableDeduplication();

    HRESULT GetValueSize(_In_ PCWSTR value, _Out_ size_t* size);

    virtual HRESULT AddDataAndCreateInstanceReference(
        _In_reads_bytes_(valueSizeInBytes) const void* value,
        _In_ UINT valueSizeInBytes,
        _In_ int qualifierSetIndex,
        _Outptr_ IBuildInstanceReference** result);

    HRESULT AddDataAndCreateInstanceReference(
        _In_reads_bytes_(valueSizeInBytes) const void* value,
        _In_ UINT valueSizeInBytes,
        _In_ const IQualifierSet* qualifiers,
        _Outptr_ IBuildInstanceReference** result,
        _Out_ int* qualifierIndex);

    HRESULT AddStringAndCreateInstanceReference(
        _In_ PCWSTR value,
        _In_ const IQualifierSet* qualifiers,
        _Outptr_ IBuildInstanceReference** result,
        _Out_ int* qualifierIndex);

    virtual HRESULT AddStringAndCreateInstanceReference(
        _In_ PCWSTR value,
        _In_ int qualifierSetIndex,
        _Outptr_ IBuildInstanceReference** result);

    HRESULT OptimizeString(
        _Out_writes_bytes_to_(convertedStringSize, *writtenBytesIncludingNull) char* convertedString,
        _In_ PCWSTR value,
        _Inout_ size_t* writtenBytesIncludingNull,
        _In_ size_t convertedStringSize,
        _In_ MrmEnvironment::ResourceValueType* optimalType);

    virtual HRESULT AddOptimizedStringAndCreateInstanceReference(
        _In_ MrmEnvironment::ResourceValueType originalType,
        _In_ PCWSTR value,
        _In_ int qualifierSetIndex,
        _Outptr_ IBuildInstanceReference** result,
        _Out_ MrmEnvironment::ResourceValueType* optimalType);

    HRESULT AddOptimizedStringAndCreateInstanceReference(
        _In_ MrmEnvironment::ResourceValueType originalType,
        _In_ PCWSTR value,
        _In_ const IQualifierSet* qualifiers,
        _Outptr_ IBuildInstanceReference** result,
        _Out_ int* qualifierIndex,
        _Out_ MrmEnvironment::ResourceValueType* optimalType);

protected:
    HRESULT GetOrAddDataItemSectionBuilder(_In_ int qualifierSetIndex, _Out_ DataItemsSectionBuilder** result);

    DataItemOrchestrator(_In_ FileBuilder* fileBuilder, _In_ CoreProfile* profile, _In_ DecisionInfoSectionBuilder* decisionInfo);

    HRESULT Init();

    bool m_finalized;
    CoreProfile* m_profile;
    FileBuilder* m_fileBuilder;
    DecisionInfoSectionBuilder* m_decisionInfo;
    DynamicArray<DataItemsSectionBuilder*>* m_allBuilders;
    DynamicArray<DataItemsSectionBuilder*>* m_buildersByQualifierSet;
    MrmBuildConfiguration* m_buildConfiguration; // do not delete this here
    OrchestratorHashMap* m_OrchestratorHashMap;
};

class PriSectionBuilder : public ISectionBuilder, public IResourceLinkBuilder
{
public:
    static HRESULT CreateInstance(_In_ FileBuilder* pFileBuilder, _In_ CoreProfile* pProfile, _Outptr_ PriSectionBuilder** result);

    static HRESULT CreateInstance(
        _In_ FileBuilder* pFileBuilder,
        _In_ PCWSTR pPackageName,
        _In_ UINT16 majorVersion,
        _In_ CoreProfile* pProfile,
        _Outptr_ PriSectionBuilder** result);

    static HRESULT CreateInstance(
        _In_ FileBuilder* pFileBuilder,
        _In_ const IHierarchicalSchema* const pPreviousSchema,
        _In_ CoreProfile* pProfile,
        _In_ PriBuildType priBuildType,
        _Outptr_ PriSectionBuilder** result);

    static HRESULT CreateInstance(
        _In_ FileBuilder* pFileBuilder,
        _In_ PCWSTR pPackageName,
        _In_ CoreProfile* pProfile,
        _Outptr_ PriSectionBuilder** result);

    static HRESULT CreateInstance(
        _In_ FileBuilder* pFileBuilder,
        _In_ PCWSTR pNewSchemaName,
        _In_ PCWSTR pPriFilePath,
        _In_ CoreProfile* pProfile,
        _Outptr_ PriSectionBuilder** result);

    static HRESULT CreateForResourcePack(
        _In_ FileBuilder* pFileBuilder,
        _In_ PCWSTR pNewSchemaName,
        _In_ const IHierarchicalSchema* pPreviousSchema,
        _In_ CoreProfile* pProfile,
        _Outptr_ PriSectionBuilder** result);

    static HRESULT CreateInstance(
        _In_ FileBuilder* pFileBuilder,
        _In_reads_bytes_(cbPriData) const BYTE* pPriData,
        _In_ size_t cbPriData,
        _In_ CoreProfile* pProfile,
        _Outptr_ PriSectionBuilder** result);

    static HRESULT CreateInstance(
        _In_ FileBuilder* pFileBuilder,
        _In_ PCWSTR pNewSchemaName,
        _In_reads_bytes_(cbPriData) const BYTE* pPriData,
        _In_ size_t cbPriData,
        _In_ CoreProfile* pProfile,
        _Outptr_ PriSectionBuilder** result);

    // build configuration determines how the string is ultimately stored
    HRESULT AddCandidateWithString(
        _In_opt_ PCWSTR schemaName,
        _In_ PCWSTR resourceName,
        _In_ MrmEnvironment::ResourceValueType valueType,
        _In_opt_ PCWSTR value,
        _In_opt_ IQualifierSet* qualifiers);

    // add embedded data candidate (qualifier set)
    HRESULT AddCandidateWithEmbeddedData(
        _In_opt_ PCWSTR schemaName,
        _In_ PCWSTR resourceName,
        _In_ MrmEnvironment::ResourceValueType valueType,
        _In_reads_bytes_(valueSizeInBytes) const BYTE* value,
        _In_ UINT valueSizeInBytes,
        _In_opt_ IQualifierSet* qualifiers);

    HRESULT AddCandidateByReference(
        _In_opt_ PCWSTR schemaName,
        _In_ PCWSTR resourceName,
        _In_ MrmEnvironment::ResourceValueType valueType,
        _In_ IBuildInstanceReference* buildInstanceReference,
        _In_opt_ IQualifierSet* qualifiers);

    HRESULT AddCandidateByReference(
        _In_opt_ PCWSTR schemaName,
        _In_ PCWSTR resourceName,
        _In_ MrmEnvironment::ResourceValueType valueType,
        _In_ IBuildInstanceReference* buildInstanceReference,
        _In_ int newQualifierSetIndex);

    HRESULT AddCandidateByReference(
        _In_opt_ PCWSTR schemaName,
        _In_ Atom::Index resourceIndex,
        _In_ MrmEnvironment::ResourceValueType valueType,
        _In_ IBuildInstanceReference* buildInstanceReference,
        _In_ int newQualifierSetIndex);

    HRESULT AddResourceLink(_In_ PCWSTR linkFromResourceName, _In_ PCWSTR linkToResourceName);

    HRESULT AddResourceLink(_In_ int linkFromResourceIndex, _In_ PCWSTR linkToResourceName);

    HRESULT AddResourceLink(
        _In_ PCWSTR linkFromResourceName,
        _In_ const HierarchicalSchemaSectionBuilder* linkToSchema,
        _In_ PCWSTR linkToResourceName);

    HRESULT AddResourceLink(
        _In_ int linkFromResourceIndex,
        _In_ const HierarchicalSchemaSectionBuilder* linkToSchema,
        _In_ PCWSTR linkToResourceName);

    virtual HierarchicalSchemaSectionBuilder* IResourceLinkBuilder::GetSchema() const { return m_pPrimarySchema; }

    ~PriSectionBuilder();

    FileBuilder* GetFileBuilder() const { return m_pFileBuilder; }
    MrmBuildConfiguration* GetBuildConfiguration() { return m_pBuilderConfiguration; }

    AtomPoolGroup* GetAtoms() const { return m_pAtoms; }

    const UnifiedEnvironment* GetEnvironment() const;

    HRESULT GetSchemaVersionInfo(_In_opt_ PCWSTR pSchemaName, _Out_ UINT16* pMajorVersion, _Out_ UINT16* pMinorVersion) const;

    int GetNumSchemas() const;

    HierarchicalSchemaSectionBuilder* GetSchemaBuilder(_In_ int index) const;

    HierarchicalSchemaSectionBuilder* GetSchemaBuilder(_In_opt_ PCWSTR pSchemaName) const;

    HRESULT AddSchemaBuilder(_In_ HierarchicalSchemaSectionBuilder* pSchema, _In_ bool isDefault, _Out_ int* index);

    DecisionInfoSectionBuilder* GetDecisionInfoBuilder() const { return m_pDecisionInfo; }

    HRESULT GetQualifierSetBuilder(_Outptr_ DecisionInfoQualifierSetBuilder** result) const;

    int GetNumResourceMaps() const;

    ResourceMapSectionBuilder* GetResourceMapBuilder(_In_ int index) const;

    ResourceMapSectionBuilder* GetResourceMapBuilder(_In_opt_ PCWSTR pSchemaName) const;

    HRESULT GetOrAddPrimaryResourceMapBuilder(_Out_opt_ ResourceMapSectionBuilder** result);

    HRESULT GetOrAddAlternateResourceMapBuilder(_Out_ ResourceMapSectionBuilder** result);

    DataItemOrchestrator* GetDataItemOrchestrator() const { return m_dataItems; }

    HRESULT AddResourceMapBuilder(_In_ ResourceMapSectionBuilder* pMap, _In_ bool isDefault, _Out_ int* index);

    HRESULT
    AddResourceMapBuilder(_In_ const IHierarchicalSchema* pSchema, _In_ bool bIsDefault, _In_ PriBuildType priBuildType, _Out_ int* index);

    HRESULT GetOrAddResourceLinkBuilder(_In_ ResourceMapSectionBuilder* mapBuilder, _Out_ ResourceLinkSectionBuilder** result);

    HRESULT SetPriFileFlags(_In_ UINT32 nFlags);

    HRESULT AddFileListSectionBuilder(_In_ FileListBuilder* pFileListSectionBuilder);

    bool IsValid() const;

    HRESULT Finalize();

    UINT32 GetMaxSizeInBytes() const;

    virtual HRESULT Build(_Out_writes_bytes_(cbData) VOID* pData, _In_ UINT32 cbData, _Out_opt_ UINT32* pcbWrittenOut) const;

    DEFFILE_SECTION_TYPEID GetSectionType() const { return gPriDescriptorExSectionType; }

    UINT16 GetFlags() const { return 0; }
    UINT16 GetSectionFlags() const { return 0; }
    UINT32 GetSectionQualifier() const { return 0; }

    void SetSectionIndex(_In_ BaseFile::SectionIndex sectionIndex) { m_sectionIndex = sectionIndex; }
    BaseFile::SectionIndex GetSectionIndex() const { return m_sectionIndex; }

private:
    PriSectionBuilder(_In_opt_ FileBuilder* pFileBuilder);

    HRESULT Init(_In_ CoreProfile* pProfile);

    HRESULT InitFromScratch(_In_ PCWSTR pPackageName, _In_ UINT16 majorVersion, _In_ CoreProfile* pProfile);

    HRESULT InitFromSchema(_In_ PCWSTR pPackageName, _In_ CoreProfile* pProfile);

    HRESULT InitFromReadOnlySchema(_In_ PCWSTR pNewSchemaName, _In_ PCWSTR pPriFilePath, _In_ CoreProfile* pProfile);

    HRESULT InitFromSchema(_In_reads_bytes_(cbPriData) const BYTE* pPriData, _In_ size_t cbPriData, _In_ CoreProfile* pProfile);

    HRESULT
    InitFromReadOnlySchema(
        _In_ PCWSTR pNewSchemaName,
        _In_reads_bytes_(cbPriData) const BYTE* pPriData,
        _In_ size_t cbPriData,
        _In_ CoreProfile* pProfile);

    HRESULT InitFromReadOnlySchema(_In_ PCWSTR pNewSchemaName, _In_ const IHierarchicalSchema* pPreviousSchema, _In_ CoreProfile* pProfile);

    HRESULT InitFromSchemaHelper(_In_ PCWSTR pPriFilePath, _In_ CoreProfile* pProfile);

    HRESULT InitFromSchemaHelper(_In_reads_bytes_(cbPriData) const BYTE* pPriData, _In_ size_t cbPriData, _In_ CoreProfile* pProfile);

    HRESULT InitFromSchemaHelper(_In_ const IHierarchicalSchema* pSchema);

    HRESULT AddPrimarySchemaBuilder(_In_ UINT16 majorVersion, _In_opt_ const IHierarchicalSchema* pPreviousSchema);

    HRESULT AddAlternateSchemaBuilder();

    HRESULT GetCanAddCandidate(_In_opt_ PCWSTR schemaName, _In_ PCWSTR resourceName) const;

    HRESULT GetMapBuilderForAddCandidate(_In_opt_ PCWSTR schemaName, _Out_ ResourceMapSectionBuilder** result);

private:
    FileBuilder* m_pFileBuilder;
    AtomPoolGroup* m_pAtoms;

    UnifiedEnvironment* m_pUnifiedEnvironment;
    DecisionInfoSectionBuilder* m_pDecisionInfo;
    DynamicArray<HierarchicalSchemaSectionBuilder*>* m_pSchemas;
    DynamicArray<ResourceMapSectionBuilder*>* m_pMaps;

    EnvironmentMappingSectionBuilder* m_environmentMapping;
    IEnvironment* m_environmentBaseline;

    PWSTR m_pPrimarySchemaName;
    HierarchicalSchemaSectionBuilder* m_pPrimarySchema;
    ResourceMapSectionBuilder* m_pPrimaryMap;

    PWSTR m_pAlternateSchemaName;
    HierarchicalSchemaSectionBuilder* m_pAlternateSchema;
    ResourceMapSectionBuilder* m_pAlternateMap;

    BaseFile::SectionIndex m_sectionIndex;
    PriBuilderPhase m_priBuilderPhase;
    PriBuildType m_priBuildType;

    bool m_bAllocFileBuilder;
    UINT32 m_nFlags;

    DataItemOrchestrator* m_dataItems;
    FileListBuilder* m_pFileListBuilder;

    DynamicArray<ResourceLinkSectionBuilder*>* m_linkBuilders;

    MrmBuildConfiguration* m_pBuilderConfiguration; // do not delete this here
};

class PriFileBuilder : public FileBuilder
{
public:
    static HRESULT CreateInstance(_In_ CoreProfile* pProfile, _Outptr_ PriFileBuilder** result);

    static HRESULT CreateInstance(
        _In_ PCWSTR pPackageName,
        _In_ UINT16 majorVersion,
        _In_ CoreProfile* pProfile,
        _Outptr_ PriFileBuilder** result);

    static HRESULT CreateInstance(
        _In_ const IHierarchicalSchema* const pPreviousSchema,
        _In_ CoreProfile* pProfile,
        _Outptr_ PriFileBuilder** result);

    static HRESULT CreateInstance(
        _In_ const IHierarchicalSchema* const pPreviousSchema,
        _In_ CoreProfile* pProfile,
        _In_ PriBuildType priBuildType,
        _Outptr_ PriFileBuilder** result);

    static HRESULT CreateInstance(
        _In_ PCWSTR pPackageName,
        _In_ PCWSTR pPriFilePath,
        _In_ CoreProfile* pProfile,
        _Outptr_ PriFileBuilder** result);

    static HRESULT CreateForResourcePack(
        _In_ PCWSTR pPackageName,
        _In_ const IHierarchicalSchema* pPreviousSchema,
        _In_ CoreProfile* pProfile,
        _Outptr_ PriFileBuilder** result);

    static HRESULT CreateInstance(_In_ PCWSTR pPackageName, _In_ CoreProfile* pProfile, _Outptr_ PriFileBuilder** result);

    static HRESULT CreateInstance(
        _In_reads_bytes_(cbPriData) const BYTE* pPriData,
        _In_ size_t cbPriData,
        _In_ CoreProfile* pProfile,
        _Outptr_ PriFileBuilder** result);

    virtual ~PriFileBuilder();

    PriSectionBuilder* GetDescriptor() { return m_pDescriptor; }

    static HRESULT VerifyFilePath(_In_ PCWSTR pszFilePath);

    static HRESULT VerifyPriFilePath(_In_ PCWSTR pPriFilePath);

    static HRESULT VerifyFileNotEmpty(_In_ PCWSTR pszFilePath);

    static HRESULT VerifyPriFileNotEmpty(_In_ PCWSTR pPriFilePath);

protected:
    PriFileBuilder(DEFFILE_MAGIC magic);

    PriSectionBuilder* m_pDescriptor;

private:
    static HRESULT GetFileMagic(_In_ CoreProfile* pProfile, _Out_ DEFFILE_MAGIC* magic);
};

class PriMapMerger;

class PriFileMerger : public DefObject
{
public:
    typedef enum
    {
        MergeDefaultFlags = 0x0001,
        AcceptCompatiblePriorVersion = 0x0002,
        BlockCompatibleNewerVersion = 0x0004,
        SuppressErrors = 0x0008,
        ForceTempFolder = 0x0010,
        InPlaceMerge = 0x0020,
        FatMerge = 0x0040,
        SetPreLoad = 0x0080,
        AddItemToSchema = 0x0100,
        InPlaceMergeForAutoMerge = 0x0200,
        // A candidate is a dupe of another if they have the same resource URI and qualifier set.
        // A PRI cannot have dupe candidates.
        // With the following flag set, if callers try to add dupe candiates to the merger,
        // we will drop the dupe and continue, instead of erroring out.
        DropDuplicateCandidates = 0x0400,

    } PriMergeFlags;

    static PriMergeFlags DefaultPriMergeFlags;

    class PriFileInfo : public DefObject
    {
    public:
        static HRESULT CreateInstance(
            _In_ PCWSTR pFileName,
            _In_ DWORD dwFileAttr,
            _In_ DWORD nFileSizeHigh,
            _In_ DWORD nFileSizeLow,
            _In_ FILETIME ftFileLastWriteTime,
            _Outptr_ PriFileMerger::PriFileInfo** result);

        ~PriFileInfo();

        static HRESULT ComputeChecksum(_In_ PCWSTR pFilePath, _Inout_ DEF_CHECKSUM* pCrcChecksum);

        HRESULT ComputeChecksum(_Inout_ DEF_CHECKSUM* pCrcChecksum) const;

        HRESULT SetFileName(_In_ PCWSTR pFileName);

        bool SetFileAttributes(_In_ DWORD dwFileAttr);
        bool SetFileSizeHigh(_In_ DWORD nFileSizeHigh);
        bool SetFileSizeLow(_In_ DWORD nFileSizeLow);

        bool SetFileLastWriteTime(_In_ FILETIME ftFileLastWriteTime);

        StringResult* GetFileName() const;

        DWORD GetFileAttributes() const;
        DWORD GetFileSizeHigh() const;
        DWORD GetFileSizeLow() const;

        FILETIME GetFileLastWriteTime() const;

    private:
        PriFileInfo();

        HRESULT Init(
            _In_ PCWSTR pFileName,
            _In_ DWORD dwFileAttr,
            _In_ DWORD nFileSizeHigh,
            _In_ DWORD nFileSizeLow,
            _In_ FILETIME ftFileLastWriteTime);

    private:
        StringResult* m_pStrFileName;
        DWORD m_dwFileAttributes;
        FILETIME m_ftLastWriteTime;
        DWORD m_nFileSizeHigh;
        DWORD m_nFileSizeLow;
    };

    typedef bool (*HashFuncPriFileInfoCollectionType)(const PriFileInfo** ppPriFileInfo1, INT* pHashOut);

    typedef int (*CompareFuncPriFileInfoCollectionType)(PriFileInfo** ppPriFileInfo1, PriFileInfo** ppPriFileInfo2);

    typedef DefList<const PriFileInfo*, CompareFuncPriFileInfoCollectionType, HashFuncPriFileInfoCollectionType> PriFileInfoCollection;

    typedef DefPointerList<const PriFileInfo, CompareFuncPriFileInfoCollectionType, HashFuncPriFileInfoCollectionType>
        PriFileInfoPointerCollection;

    static int CompareFuncPriFileInfoCollection(_In_ PriFileInfo** ppPriFileInfo1, _In_ PriFileInfo** ppPriFileInfo2);

    static bool HashFuncPriFileInfoCollection(_In_ const PriFileInfo** ppPriFileInfo1, _In_ INT* pHashOut);

    static int CompareFuncStringResult(_In_ const StringResult** ppStringResult1, _In_ const StringResult** ppStringResult2);

    static bool HashFuncStringResult(_In_ const StringResult** ppStringResult1, _In_ INT* pHashOut);

public:
    static HRESULT CreateInstance(_In_ CoreProfile* pProfile, _Outptr_ PriFileMerger** result);

    virtual ~PriFileMerger();

    HRESULT InitWithPri(
        _In_reads_bytes_(cbPriData) const BYTE* pPriData,
        _In_ size_t cbPriData,
        _In_ PriFileMerger::PriMergeFlags mergeFlags,
        _In_opt_ PCWSTR pPackageRootFolder,
        _In_ CoreProfile* pProfile);

    HRESULT MergeMap(
        _In_ const IResourceMapBase* pResMap,
        _In_ bool bIsPrimary,
        _In_ PriFileMerger::PriMergeFlags mergeFlags,
        _In_opt_ PCWSTR pRootFolder);

    PriFileBuilder* GetPriFileBuilder();

    HRESULT SetPriFileFlags(_In_ UINT32 nFlags);

    HRESULT WriteToFile(_In_ PCWSTR pFilePath);

    HRESULT WriteToUniqueTempDirectory(_In_ PCWSTR pFileName, _Inout_ StringResult* pStrOutputTempPath);

    HRESULT ReleasePriBuilder(_Out_ PriFileBuilder** ppPriBuilder);

    static HRESULT CleanupMergeFolder(_In_ PCWSTR pszMergeFolder, _In_ PCWSTR pszPattern, _In_ PCWSTR pszFilePathNotToDelete);

    static HRESULT CreateUniqueTempDirectory(_In_ DWORD nUniqueTempDirLength, _Out_writes_(nUniqueTempDirLength) PWSTR pszUniqueTempDir);

    static HRESULT GetOrCreateSubDirectory(_In_ PCWSTR pszSubDirName, _Inout_ StringResult* pStrRootDir);

    static HRESULT AddAllApplicationPackagesSid(_In_ PCWSTR pszFilePath, _In_ bool bPathIsFolder);

    static HRESULT GetRelativeFolderFromPriFilePath(_In_ PCWSTR pPriFilePath, _Inout_ StringResult* pRelativeFolderPath);

protected:
    HRESULT Init(_In_ CoreProfile* pProfile);

    PriFileMerger();

    static HRESULT DeleteOldMergedFiles(
        _In_ PCWSTR pszMergeFolder,
        _In_ PCWSTR pszPattern,
        _In_ UINT nMinDaysOlder,
        _In_ UINT nMaxFilesToDelete,
        _In_ PCWSTR pszFilePathNotToDelete);

private:
    PriFileBuilder* m_pPriFileBuilder;
    PriMapMerger* m_pPriMapMerger;
    PriBuilderPhase m_priBuilderPhase;
    CoreProfile* m_pProfile;
    static const int CLEANUP_MIN_DAYS;
    static const int CLEANUP_MAX_FILES;
};

DEFINE_ENUM_FLAG_OPERATORS(PriFileMerger::PriMergeFlags);

class PriMapMerger : public DefObject
{
public:
    static HRESULT MergeMap(
        _In_ const IResourceMapBase* pResMap,
        _In_ bool bIsPrimary,
        _In_ PriFileMerger::PriMergeFlags mergeFlags,
        _In_opt_ PCWSTR pPackageRootFolder,
        _Inout_ PriSectionBuilder* pMergedPriSectionBuilder);

    static HRESULT CheckIsCompatible(
        _In_ const IHierarchicalSchema* pHSchema,
        _In_ const IHierarchicalSchema* pNewHSchema,
        _In_ PriFileMerger::PriMergeFlags mergeFlags);
};

#define DefBuilder_PhaseMismatch(GOT, WANT, STATUS) Def_Check0(((GOT) != (WANT)), E_DEFFILE_BUILD_BAD_PHASE, STATUS)
#define DefBuilder_PhaseIsBefore(GOT, WANT, STATUS) Def_Check0(((GOT) < (WANT)), E_DEFFILE_BUILD_BAD_PHASE, STATUS)
#define DefBuilder_PhaseIsAfter(GOT, WANT, STATUS) Def_Check0(((GOT) > (WANT)), E_DEFFILE_BUILD_BAD_PHASE, STATUS)

} // namespace Build
} // namespace Microsoft::Resources