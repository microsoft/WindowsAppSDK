// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "mrm/Collections.h"
#include "mrm/build/MrmBuilders.h"

#define MRT_MERGE_KEY_NAME L"Software\\Microsoft\\Windows\\CurrentVersion\\Mrt\\_Merged"
#define MRT_MERGE_REDIRECTED_VALUE_NAME L"RedirectedStorageRoot"

namespace MrmBaseUnitTests
{
class NormalizedFilePathTests;
}

namespace Microsoft::Resources
{

class PriFileManager;

enum class LoadPriFlags
{
    Default = 0,
    LoadForDependentPackages = 0x1,
    ExcludeLogForFileNotFound = 0x2,
    Preload = 0x4,
};
DEFINE_ENUM_FLAG_OPERATORS(LoadPriFlags);

class UnifiedEnvironment : public EnvironmentCollectionBase, public DefObject
{
public:
    static HRESULT CreateInstance(_In_ CoreProfile* pProfile, _In_ AtomPoolGroup* pAtoms, _Outptr_ UnifiedEnvironment** result);

    virtual ~UnifiedEnvironment();

    CoreProfile* GetProfile() const { return m_pProfile; }

    const AtomPoolGroup* GetAtoms() const { return m_pAtoms; }

    int GetNumEnvironments() const;

    HRESULT GetEnvironment(_In_ int index, _Out_ const IEnvironment** result) const;

    const IEnvironment* GetDefaultEnvironment() const override { return m_pDefaultEnvironment; }

    HRESULT AddEnvironment(_In_ const IEnvironment* pEnvironment, _Inout_opt_ RemapUInt16* pPoolMapping);

    bool EnvironmentIsCompatible(
        _In_ PCWSTR wantName,
        _In_ const EnvironmentVersionInfo* wantVersion,
        _Outptr_opt_result_maybenull_ const RemapAtomPool** qualifierMapping) const;

    HRESULT AddCompatibleEnvironment(
        _In_ PCWSTR wantName,
        _In_ const EnvironmentVersionInfo* wantVersion,
        _In_ int numQualifiers,
        _In_reads_(numQualifiers) const PCWSTR* qualifierNames,
        _In_reads_opt_(numQualifiers) const Atom::SmallIndex* qualifierMappings,
        _Outptr_opt_result_maybenull_ const RemapAtomPool** qualifierRemap);

    HRESULT GetTypeOfQualifier(
        _In_ PCWSTR pQualifierName,
        _Out_ Atom* pTypeAtomOut,
        _Out_opt_ const IEnvironment** pEnvironmentOut = nullptr) const;

    HRESULT
    GetQualifierNameAtom(_In_ PCWSTR pQualifierName, _Out_ Atom* pNameAtomOut, _Out_opt_ const IEnvironment** pEnvironment = nullptr) const;

    HRESULT GetQualifierNameFromAtom(_In_opt_ Atom nameAtom, _Inout_ StringResult* pNameOut) const;

    HRESULT GetResourceQualifier(_In_ PCWSTR pQualifierName, _Out_ ResourceQualifier* pQualifierOut) const;

    HRESULT GetResourceQualifier(_In_ Atom name, _Out_ ResourceQualifier* pQualifierOut) const;

    HRESULT GetResourceValueTypeAtom(
        _In_ MrmEnvironment::ResourceValueType valueType,
        _Out_ Atom* pNameAtomOut,
        _Out_opt_ const IEnvironment** pEnvironmentOut = nullptr) const;

    HRESULT GetResourceValueLocatorAtom(
        _In_ PCWSTR pLocatorName,
        _Out_ Atom* pNameAtomOut,
        _Out_opt_ const IEnvironment** pEnvironmentOut = nullptr) const;

    HRESULT GetTypeOfQualifier(_In_ PCWSTR pQualifierName, _Outptr_ const IBuildQualifierType** ppTypeOut) const;

    HRESULT GetTypeOfQualifier(_In_ Atom name, _Outptr_ const IBuildQualifierType** ppTypeOut) const;

    HRESULT ValidateQualifierValue(_In_ PCWSTR pQualifierName, _In_ PCWSTR pQualifierValue) const;

    HRESULT ValidateQualifierValue(_In_ Atom qualifierName, _In_ PCWSTR pQualifierValue) const;

    HRESULT ValidateOrMakeCompatibleQualifierValue(
        _In_ PCWSTR qualifierName,
        _In_ PCWSTR qualifierValue,
        _Inout_ StringResult* compatibleValue) const;

    HRESULT
    ValidateQualifierComparison(_In_ PCWSTR pQualifierName, _In_ ICondition::ConditionOperator op, _In_ PCWSTR pQualifierValue) const;

    HRESULT ValidateQualifierComparison(_In_ PCWSTR pQualifierName, _In_ PCWSTR pQualifierValue) const
    {
        return ValidateQualifierComparison(pQualifierName, ICondition::MatchOp, pQualifierValue);
    }

    HRESULT ValidateQualifierComparison(_In_ Atom qualifierName, _In_ ICondition::ConditionOperator op, _In_ PCWSTR pQualifierValue) const;

    HRESULT ValidateQualifierComparison(_In_ Atom qualifierName, _In_ PCWSTR pQualifierValue) const
    {
        return ValidateQualifierComparison(qualifierName, ICondition::MatchOp, pQualifierValue);
    }

    typedef enum
    {
        QualifierNames,
        QualifierTypeNames,
        ResourceValueTypeNames,
        ResourceValueLocatorNames,
        ItemTypeNames
    } EnvironmentNamesType;

    bool IsValidAtom(_In_ EnvironmentNamesType which, _In_ Atom name) const { return SUCCEEDED(GetName(which, name, nullptr)); }

    bool IsValidName(_In_ EnvironmentNamesType which, _In_ PCWSTR pName) const { return SUCCEEDED(GetAtom(which, pName, nullptr)); }

    HRESULT GetAtom(_In_ EnvironmentNamesType which, _In_ PCWSTR pName, _Inout_opt_ Atom* pAtomOut) const;

    HRESULT GetName(_In_ EnvironmentNamesType which, _In_ Atom atom, _Inout_opt_ StringResult* pStringOut) const;

    HRESULT GetAllAtoms(_In_ EnvironmentNamesType which, _Outptr_ DynamicArray<Atom>** result) const;

protected:
    UnifiedEnvironment() :
        m_pAtoms(nullptr), m_pDefaultEnvironment(nullptr), m_pProfile(nullptr), m_pQualifierPool(nullptr), m_compatibleEnvironments(nullptr)
    {}

    HRESULT Init(_In_ CoreProfile* pProfile, _In_ AtomPoolGroup* pAtoms);

    AtomPoolGroup* m_pAtoms;
    IEnvironment* m_pDefaultEnvironment;
    CoreProfile* m_pProfile;

    class PerQualifierPoolInfo;
    PerQualifierPoolInfo* m_pQualifierPool;

    class CompatibleEnvironmentInfo;
    DynamicArray<CompatibleEnvironmentInfo*>* m_compatibleEnvironments;
};

class ManagedFile;

class UnifiedDecisionInfo : public IDecisionInfo
{
public:
    static HRESULT CreateInstance(
        _In_ const UnifiedEnvironment* pEnvironment,
        _In_opt_ const IDecisionInfo* pInitialDecisions,
        _Outptr_ UnifiedDecisionInfo** result);

    static HRESULT CreateInstance(
        _In_ const UnifiedEnvironment* pEnvironment,
        _In_opt_ const ManagedFile* pInitialFile,
        _In_opt_ const IDecisionInfo* pInitialDecisions,
        _Outptr_ UnifiedDecisionInfo** result);

    virtual ~UnifiedDecisionInfo();

    HRESULT Merge(
        _In_ const IDecisionInfo* pMerge,
        _Inout_opt_ RemapUInt16* pQualifierMap = nullptr,
        _Inout_opt_ RemapUInt16* pQualiferSetMap = nullptr,
        _Inout_opt_ RemapUInt16* pDecisionMap = nullptr);

    HRESULT Merge(
        _In_opt_ const ManagedFile* pInitialFile,
        _In_ const IDecisionInfo* pMerge,
        _Inout_opt_ RemapUInt16* pQualifierMap = nullptr,
        _Inout_opt_ RemapUInt16* pQualifierSetMap = nullptr,
        _Inout_opt_ RemapUInt16* pDecisionMap = nullptr);

    const IEnvironment* GetEnvironment() const { return m_pEnvironment->GetDefaultEnvironment(); }

    int GetNumQualifiers() const { return m_pDecisionInfo->GetNumQualifiers(); }

    HRESULT GetQualifier(_In_ int index, _Inout_ QualifierResult* pResult) const { return m_pDecisionInfo->GetQualifier(index, pResult); }

    int GetNumQualifierSets() const { return m_pDecisionInfo->GetNumQualifierSets(); }

    HRESULT GetQualifierSet(_In_ int index, _Inout_ QualifierSetResult* pResult) const
    {
        return m_pDecisionInfo->GetQualifierSet(index, pResult);
    }

    int GetNumDecisions() const { return m_pDecisionInfo->GetNumDecisions(); }

    HRESULT GetDecision(_In_ int index, _Inout_ DecisionResult* pResult) const { return m_pDecisionInfo->GetDecision(index, pResult); }

    HRESULT GetDecisionNumQualifierSets(_In_ int index, _Out_ int* pNumSetsOut) const
    {
        return m_pDecisionInfo->GetDecisionNumQualifierSets(index, pNumSetsOut);
    }

    HRESULT NoteFileUnloading(_In_ const ManagedFile* pFile, _Out_ bool* pbCancelUnloadOut);

protected:
    UnifiedDecisionInfo() : m_pEnvironment(nullptr), m_pDecisionInfo(nullptr), m_pBase(nullptr), m_pBaseFile(nullptr), m_pBuilder(nullptr)
    {}

    HRESULT Init(
        _In_ const UnifiedEnvironment* pEnvironment,
        _In_opt_ const ManagedFile* pInitialFile,
        _In_opt_ const IDecisionInfo* pInitialDecisions);

    const UnifiedEnvironment* m_pEnvironment;
    const IDecisionInfo* m_pDecisionInfo;
    const IDecisionInfo* m_pBase;
    const ManagedFile* m_pBaseFile;
    Microsoft::Resources::Build::DecisionInfoBuilder* m_pBuilder;
};

class NormalizedFilePath : protected StringResult
{
    friend class MrmBaseUnitTests::NormalizedFilePathTests;

public:
    // Inherited from StringResult
    // StringResult is partially exposed in order to prevent future abuse.
    // Specifically, we want to avoid the scenario where an unknowing dev
    // mutates the underlying buffer and assumes that this class normalizes
    // it for them. As a consequence of this need, NormalizedFilePath is immutable.
    using StringResult::Compare;
    using StringResult::CompareWithOptions;
    using StringResult::Contains;
    using StringResult::CopyToOutParams;
    using StringResult::GetCopy;
    using StringResult::GetLength;
    using StringResult::GetRef;
    using StringResult::GetSize;
    using StringResult::GetType;
    using StringResult::ICompare;
    using StringResult::Inspect;
    using StringResult::IsAbsolutePath;
    using StringResult::ReleaseContents;
    using StringResult::SetCopyInteger;
    using StringResult::TryFindFirstOf;
    using StringResult::TryFindLastOf;

    NormalizedFilePath();

    virtual ~NormalizedFilePath(void);

    HRESULT Init(_In_ PCWSTR str);
};

class ManagedFileSection;
class ManagedFile : public IMrmFile
{
public:
    static HRESULT CreateInstance(
        _In_ const PriFileManager* pManager,
        _In_ int globalIndex,
        _In_ PCWSTR pPath,
        _In_opt_ PCWSTR pPackageRoot,
        _In_ LoadPriFlags flags,
        _Outptr_ ManagedFile** result);

    static HRESULT CreateInstance(
        _In_ const PriFileManager* pManager,
        _In_ int globalIndex,
        _In_ const NormalizedFilePath* pNormalizedPath,
        _In_opt_ PCWSTR pPackageRoot,
        _In_ LoadPriFlags flags,
        _Outptr_ ManagedFile** result);

    // This New method is temporary scaffolding that makes it easier to slide
    // the updated infrastructure under the existing API surface.  It will go
    // away once we move fully to the new infrastructure.
    static HRESULT CreateInstance(_In_ const MrmFile* pBaseFile, _Outptr_ ManagedFile** result);

    virtual ~ManagedFile();

    UnifiedEnvironment* GetUnifiedEnvironment() const { return m_pEnvironment; };
    CoreProfile* GetProfile() const { return m_pEnvironment->GetProfile(); }

    const PriFileManager* GetFileManager() const { return m_pManager; }

    int GetGlobalIndex() const { return m_globalIndex; }
    void SetGlobalIndex(int index) { m_globalIndex = index; }

    PCWSTR GetPath() const { return m_pPath; }

    PCWSTR GetPackageRoot() const { return m_pPackageRoot; }

    HRESULT SetPackageRoot(_In_ PCWSTR pPackageRoot);

    HRESULT GetBaseMrmFile(_Out_ const IMrmFile** result) const;

    HRESULT GetBaseFile(_Out_ const BaseFile** result) const;

    UINT64 GetLastModifiedDate() const { return m_fileLastModifiedDate; }
    size_t GetSizeInBytes() const { return m_fileSizeInBytes; }

    bool IsLoaded() const { return (m_pBaseFile != nullptr); }

    HRESULT Load() { return InnerLoad(); }

    HRESULT Unload() { return InnerUnload(); }

    int GetNumFiles() const { return m_pBaseFile->GetNumFiles(); }

    bool LoadFailed() const { return m_loadFailed; }

    HRESULT
    GetSection(
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_ int fileIndex,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ const IFileSection** result) const;

    _Success_(return == true)
    const bool TryGetSectionIndexByType(
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

    HRESULT GetFileDefaultEnvironment(
        _In_ int fileIndex,
        _Inout_opt_ StringResult* fileEnvironmentName,
        _Inout_opt_ EnvironmentVersionInfo* fileEnvironmentVersion) const override;

    HRESULT GetDefaultQualifierMapping(_In_ int fileIndex, _Out_ const RemapAtomPool** result) const;

    HRESULT ResolveFileFileList(_In_ const FileFileList* pFileFileList);

    HRESULT GetAbsoluteFolderPath(_In_ int fileIndex, _Inout_ StringResult* pStringResult) const;

    HRESULT GetFilePath(_In_ int fileIndex, _Inout_ StringResult* pStringResult) const;

    static HRESULT NormalizeFilePath(_In_ PCWSTR pFilePath, _Inout_ StringResult* pPathOut);

    static HRESULT NormalizePackageRoot(_In_ PCWSTR pPriFile, _In_opt_ PCWSTR pPackageRoot, _Inout_ StringResult* pPathOut);

protected:
    UnifiedEnvironment* m_pEnvironment;
    const PriFileManager* m_pManager;
    int m_globalIndex;

    mutable bool m_loadFailed;
    mutable const IMrmFile* m_pBaseFile;
    mutable IMrmFile* m_pMyBaseFile;

    PWSTR m_pPath;
    size_t m_fileSizeInBytes;
    UINT64 m_fileLastModifiedDate;

    PWSTR m_pPackageRoot;

    ManagedFile(_In_ const PriFileManager* pManager, _In_ int globalIndex);

    ManagedFile(_In_ const MrmFile* pBaseFile);

    HRESULT Initialize(_In_ const PriFileManager* pManager, _In_ const NormalizedFilePath* pNormalizedPath, _In_opt_ PCWSTR pPackageRoot);

    // InnerLoad & InnerUnload are used internally by
    // the various "const" methods to load on demand.
    // External callers only have access to Load & Unload,
    // which require a non-const pointer.
    virtual HRESULT InnerLoad() const;

    virtual HRESULT InnerUnload() const;
};

class PriFileManager : public IFileSectionResolver
{
public:
    /*!
         * Gets a new, empty PriFileManager.
         *
         * \param pStatus
         * Reports extended status if an error occurs.
         *
         * \return PriFileManager*
         * The new file manager, or nullptr if an error occurs.
         */
    static HRESULT CreateInstance(_In_ UnifiedEnvironment* pEnvironment, _Outptr_ PriFileManager** result);

    virtual ~PriFileManager();

    UnifiedEnvironment* GetUnifiedEnvironment() const { return m_pEnvironment; }
    CoreProfile* GetProfile() const { return m_pEnvironment->GetProfile(); }

    int GetNumFiles() const { return ((m_pFiles != nullptr) ? m_pFiles->Count() : 0); }

    HRESULT GetFile(_In_ int index, _Out_ ManagedFile** result) const;

    HRESULT GetFile(_In_ PCWSTR pFilePath, _Out_ ManagedFile** result) const;

    HRESULT GetFile(_In_ const NormalizedFilePath* pNormalizedPath, _Out_ ManagedFile** result) const;

    HRESULT GetOrAddFile(_In_ PCWSTR pPath, _In_opt_ PCWSTR pPackageRoot, _In_ LoadPriFlags flags, _Out_ ManagedFile** result) const;

    HRESULT
    GetOrAddFile(
        _In_ const NormalizedFilePath* pNormalizedPath,
        _In_opt_ PCWSTR pPackageRoot,
        _In_ LoadPriFlags flags,
        _Out_ ManagedFile** result) const;

    HRESULT AddFile(_In_ PCWSTR pPath, _In_opt_ PCWSTR pPackageRoot, _In_ bool fPreload, _Out_ ManagedFile** result);

    HRESULT
    AddFile(_In_ const NormalizedFilePath* pNormalizedPath, _In_opt_ PCWSTR pPackageRoot, _In_ bool fPreload, _Out_ ManagedFile** result);

    HRESULT InsertFile(_In_ int newIndex, _In_ PCWSTR pPath, _In_opt_ PCWSTR pPackageRoot, _In_ bool fPreload, _Out_ ManagedFile** result);

    HRESULT LoadFile(_In_ const ManagedFile* pFile);

    HRESULT UnloadFile(_In_ const ManagedFile* pFile);

    HRESULT RemoveFile(_In_ const ManagedFile* pFile);

    UINT32 GetDefaultFileFlags() const { return m_defaultFileFlags; }

    HRESULT SetDefaultFileFlags(_In_ UINT32 flags);

    /*
         * IFileSectionResolver methods
         */
    HRESULT
    GetSection(
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_ int fileIndex,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ const IFileSection** result) const;

    _Success_(return == true)
    const bool TryGetSectionIndexByType(
        _In_ const DEFFILE_SECTION_TYPEID& sectionType,
        _In_ int fileIndex,
        _In_ int startAtSectionIndex,
        _Out_ int* nextSectionIndex) const;

    HRESULT GetAtomPoolSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileAtomPool** result) const;

    HRESULT
    GetDecisionInfoSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ DecisionInfoFileSection** result) const;

    HRESULT GetSchemaSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ HierarchicalSchema** result) const;

    HRESULT GetResourceMapSection(
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_ int fileIndex,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ ResourceMapBase** result) const;

    HRESULT GetPriDescriptorSection(
        _In_ const ISchemaCollection* pSchemaCollection,
        _In_ int fileIndex,
        _In_ BaseFile::SectionIndex sectionIndex,
        _Out_ PriDescriptor** result) const;

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

    HRESULT GetFilePath(_In_ int fileIndex, _Inout_ StringResult* pStringResult) const;

    HRESULT GetAbsoluteFolderPath(_In_ int fileIndex, _Inout_ StringResult* pStringResult) const;

    virtual HRESULT GetFileDefaultEnvironment(
        _In_ int fileIndex,
        _Inout_opt_ StringResult* fileEnvironmentName,
        _Inout_opt_ EnvironmentVersionInfo* fileEnvironmentVersion) const override;

    HRESULT GetDefaultQualifierMapping(_In_ int fileIndex, _Out_ const RemapAtomPool** result) const;

private:
    static const int DefaultInitialFilesSize = 4;

    typedef struct FileManagerFileInfo
    {
        ManagedFile* pFile;
    } FileManagerFileInfo;

    UINT32 m_defaultFileFlags = 0;
    mutable DynamicArray<FileManagerFileInfo>* m_pFiles;
    mutable MrmFileResolver* m_pFileResolver;

    UnifiedEnvironment* m_pEnvironment;

    PriFileManager() : m_pFiles(nullptr), m_pFileResolver(nullptr), m_pEnvironment(nullptr) {}

    HRESULT Init(_In_ UnifiedEnvironment* pEnvironment);
};

class ManagedSchema : public IHierarchicalSchema
{
public:
    static HRESULT CreateInstance(
        _In_ const ManagedFile* pInitialFile,
        _In_ const IHierarchicalSchema* pInitialSchema,
        _Outptr_ ManagedSchema** result);

    virtual ~ManagedSchema();

    UINT64 GetCurrentGeneration() const { return m_generation; }
    const IHierarchicalSchema* GetCurrentSchema() const { return m_pCurrentSchema; }

    HRESULT NoteFileAdded(_In_ const ManagedFile* pNewFile, _In_ const IHierarchicalSchema* pNewSchema);

    HRESULT NoteFileUnloading(_In_ const ManagedFile* pFile, _Out_ bool* pbCancelUnloadOut);

    HRESULT NoteFileRemoving(_In_ const ManagedFile* pFile, _Out_ bool* pbCancelRemovalOut);

    // IHierarchicalSchema implementation

    PCWSTR GetUniqueId() const { return m_pCurrentSchema->GetUniqueId(); }
    PCWSTR GetSimpleId() const { return m_pCurrentSchema->GetSimpleId(); }

    int GetNumVersionInfos() const;

    const IHierarchicalSchemaVersionInfo* GetVersionInfo(_In_ int index = 0) const;

    UINT16 GetMajorVersion() const { return m_pCurrentSchema->GetMajorVersion(); }
    UINT16 GetMinorVersion() const { return m_pCurrentSchema->GetMinorVersion(); }

    int GetNumNames() const { return m_pCurrentSchema->GetNumNames(); }

    int GetNumScopes() const { return m_pCurrentSchema->GetNumScopes(); }
    IAtomPool* GetScopeNames() const { return m_pCurrentSchema->GetScopeNames(); }

    int GetNumItems() const { return m_pCurrentSchema->GetNumItems(); }
    IAtomPool* GetItemNames() const { return m_pCurrentSchema->GetItemNames(); }

    bool Contains(_In_ PCWSTR pPath, _Out_opt_ int* pScopeIndexOut = nullptr, _Out_opt_ int* pItemIndexOut = nullptr) const
    {
        return m_pCurrentSchema->Contains(pPath, pScopeIndexOut, pItemIndexOut);
    }

    bool Contains(
        _In_ PCWSTR pPath,
        _In_ int relativeToScope,
        _Out_opt_ int* pScopeIndexOut = nullptr,
        _Out_opt_ int* pItemIndexOut = nullptr) const
    {
        return m_pCurrentSchema->Contains(pPath, relativeToScope, pScopeIndexOut, pItemIndexOut);
    }

    bool TryGetScopeInfo(_In_ int scopeIndex, _Inout_ StringResult* pNameOut, _Out_opt_ int* pNumChildrenOut = nullptr) const
    {
        return m_pCurrentSchema->TryGetScopeInfo(scopeIndex, pNameOut, pNumChildrenOut);
    }

    bool TryGetScopeChild(_In_ int scopeIndex, _In_ int childIndex, _Out_opt_ int* pChildScopeIndexOut, _Out_opt_ int* pChildItemIndexOut)
        const
    {
        return m_pCurrentSchema->TryGetScopeChild(scopeIndex, childIndex, pChildScopeIndexOut, pChildItemIndexOut);
    }

    bool TryGetScopeChildName(_In_ int scopeIndex, _In_ int childIndex, _Inout_ StringResult* pNameOut) const
    {
        return m_pCurrentSchema->TryGetScopeChildName(scopeIndex, childIndex, pNameOut);
    }

    bool TryGetItemInfo(_In_ int itemIndex, _Inout_ StringResult* pNameOut) const
    {
        return m_pCurrentSchema->TryGetItemInfo(itemIndex, pNameOut);
    }

    bool TryGetRelativeItemName(_In_ int relativeToScope, _Inout_ int itemIndex, _Inout_ StringResult* pNameOut) const
    {
        return m_pCurrentSchema->TryGetRelativeItemName(relativeToScope, itemIndex, pNameOut);
    }

    bool TryGetRelativeScopeName(_In_ int relativeToScope, _Inout_ int scopeIndex, _Inout_ StringResult* pNameOut) const
    {
        return m_pCurrentSchema->TryGetRelativeScopeName(relativeToScope, scopeIndex, pNameOut);
    }

    HRESULT GetNumDescendents(_In_ int scopeIndex, _Out_opt_ int* pNumScopes, _Out_opt_ int* pNumItems) const
    {
        return m_pCurrentSchema->GetNumDescendents(scopeIndex, pNumScopes, pNumItems);
    }

    bool TryGetItemLocalName(_Inout_ int itemIndex, _Inout_ StringResult* pNameOut) const
    {
        return m_pCurrentSchema->TryGetItemLocalName(itemIndex, pNameOut);
    }

    HRESULT GetDescendents(
        _In_ int scopeIndex,
        _In_ int sizeScopes,
        _Out_writes_to_opt_(sizeScopes, *pNumScopesWritten) int* pScopesOut,
        _Out_opt_ int* pNumScopesWritten,
        _In_ int sizeItems,
        _Out_writes_to_opt_(sizeItems, *pNumItemsWritten) int* pItemsOut,
        _Out_opt_ int* pNumItemsWritten) const
    {
        return m_pCurrentSchema->GetDescendents(
            scopeIndex, sizeScopes, pScopesOut, pNumScopesWritten, sizeItems, pItemsOut, pNumItemsWritten);
    }

    HRESULT Clone(_Outptr_ IHierarchicalSchema**) const;

    HRESULT GetSchemaBlobFromFileSection(
        _Inout_opt_ DEFFILE_SECTION_TYPEID* /*pSectionTypeResult*/,
        _Inout_opt_ BlobResult* /*pBlobResult*/
    ) const;

private:
    ManagedSchema(_In_ const ManagedFile* pInitialFile, _In_ const IHierarchicalSchema* pInitialMap);

    UINT64 m_generation{ 0 };
    const IHierarchicalSchema* m_pCurrentSchema{ nullptr };
    const ManagedFile* m_pCurrentFile{ nullptr };

    typedef struct _SchemaPerFileInfo
    {
        const ManagedFile* pFile;
        const IHierarchicalSchema* pSchema;
    } SchemaPerFileInfo;

    const PriFileManager* m_pFileManager;
    DynamicArray<SchemaPerFileInfo>* m_pFiles;

    IHierarchicalSchema* m_pMySchema;
};

class UnifiedResourceView;

class ManagedResourceMap : public IResourceMapBase, public ResourceMapSubtree
{
public:
    using IResourceMapBase::operator delete;

    static HRESULT CreateInstance(
        _In_ const ManagedFile* pInitialFile,
        _In_ const IResourceMapBase* pInitialMap,
        _In_ const ManagedSchema* pSchema,
        _In_ UnifiedDecisionInfo* pDecisions,
        _In_ UnifiedResourceView* pUnifiedResourceView,
        _Outptr_ ManagedResourceMap** result);

    virtual ~ManagedResourceMap();

    UINT64 GetCurrentGeneration() const { return m_generation; }

    const IResourceMapBase* GetCurrentResourceMap() const;

    const ManagedSchema* GetManagedSchema() const { return m_pSchema; }

    HRESULT SetPackageRootPath(_In_ PCWSTR pPath) const { return m_packageRootPath.SetCopy(pPath); }

    PCWSTR GetPackageRootPath() const { return m_packageRootPath.GetRef(); }

    HRESULT NoteFileAdded(_In_ const ManagedFile* pNewFile, _In_opt_ const IResourceMapBase* pNewMap);

    HRESULT NoteFileUnloading(_In_ const ManagedFile* pFile, _Out_ bool* pbCancelUnloadOut);

    HRESULT NoteFileRemoving(_In_ const ManagedFile* pFile, _Out_ bool* pbCancelRemovalOut);

    const IHierarchicalSchema* GetSchema() const;
    const IHierarchicalSchema* GetOriginalSchema() const;
    const IDecisionInfo* GetDecisionInfo() const;

    const ResourceMapSubtree* GetRootSubtree() const;

    int GetNumResources() const;

    HRESULT GetResourceByIndex(_In_ int indexInSchema, _Inout_ NamedResourceResult* pItemOut) const;

    HRESULT GetResource(_In_ PCWSTR pPath, _Inout_ NamedResourceResult* pItemOut) const;

    int GetTotalNumResourceValues() const;

    HRESULT SetDecisionInfoOverride(_In_ const IDecisionInfo* pOverrideDecisionInfo, _In_ const RemapUInt16* pOverrideDecisionMap) const;

    void ResetDecisionInfoOverride() const;

    HRESULT SetSchemaOverride(_In_ const IHierarchicalSchema* pOverrideSchema) const;

    HRESULT
    GetFiles(_Inout_opt_ DynamicArray<const IResourceMapBase*>* pMapsOut, _Inout_opt_ DynamicArray<const ManagedFile*>* pFilesOut) const;

private:
    ManagedResourceMap() :
        m_generation(0),
        m_pCurrentMap(nullptr),
        m_pCurrentFile(nullptr),
        m_pSchema(nullptr),
        m_pDecisions(nullptr),
        m_pUnifiedResourceView(nullptr),
        m_pFileManager(nullptr),
        m_pFiles(nullptr)
    {}

    HRESULT Init(
        _In_ const ManagedFile* pInitialFile,
        _In_ const IResourceMapBase* pInitialMap,
        _In_ const ManagedSchema* pSchema,
        _In_ UnifiedDecisionInfo* pDecisions,
        _In_ UnifiedResourceView* pUnifiedResourceView);

    HRESULT GetOrCreateFilesList() const;

    HRESULT UpdateCurrent() const;

    mutable UINT64 m_generation;

    mutable const ManagedFile* m_pCurrentFile;
    mutable const IResourceMapBase* m_pCurrentMap;

    const ManagedSchema* m_pSchema;
    UnifiedDecisionInfo* m_pDecisions;
    UnifiedResourceView* m_pUnifiedResourceView;

    typedef struct _MapPerFileInfo
    {
        bool loaded;
        const ManagedFile* pFile;
        const IResourceMapBase* pMap;
        StringResult* pPackageRootPath;
    } MapPerFileInfo;

    const PriFileManager* m_pFileManager;
    mutable DynamicArray<MapPerFileInfo>* m_pFiles;

    mutable StringResult m_packageRootPath;
};

class ProviderResolver;

class UnifiedResourceView : public IUnifiedResourceView
{
protected:
    class UnifiedViewFileInfo;

public:
    class PriFileInfo : public DefObject
    {
    public:
        static HRESULT CreateInstance(
            _In_ PCWSTR pszPriFilePath,
            _In_ PCWSTR pszPriFileRoot,
            _In_ bool bFileLoaded,
            _Outptr_ UnifiedResourceView::PriFileInfo** result);
        ~PriFileInfo();

        void SetFileLoadedStatus(_In_ bool bFileLoaded);
        void SetLoadedFileIndex(_In_ int nLoadedFileIndex);
        void SetInputFilesIndex(_In_ UINT uInputFilesIndex);
        void SetManagedResourceMap(_In_ const ManagedResourceMap* pManagedResourceMap);
        void SetAppFile();
        PCWSTR GetPriFilePath() const;
        PCWSTR GetPriFileRoot() const;
        bool GetFileLoaded() const;
        int GetLoadedFileIndex() const;
        UINT GetInputFilesIndex() const;
        const ManagedResourceMap* GetManagedResourceMap() const;
        bool GetAppFile() const;

    private:
        friend UnifiedResourceView;
        void SetUnifiedViewFileInfo(_In_ UnifiedResourceView::UnifiedViewFileInfo* pUnifiedViewFileInfo);
        UnifiedResourceView::UnifiedViewFileInfo* GetUnifiedViewFileInfo() const;
        PriFileInfo(_In_ PCWSTR pszPriFilePath, _In_ PCWSTR pszPriFileRoot, _In_ bool bFileLoaded);
        UnifiedViewFileInfo* m_pUnifiedViewFileInfo;
        StringResult m_strPriFilePath;
        StringResult m_strPriFileRoot;
        int m_nLoadedFileIndex;
        UINT m_uInputFilesIndex;
        bool m_bFileLoaded;
        bool m_bIsAppFile;
        const ManagedResourceMap* m_pManagedResourceMap;
    };

    static HRESULT CreateInstance(_In_ CoreProfile* pProfile, _Outptr_ UnifiedResourceView** result);

    virtual ~UnifiedResourceView();

    const PriFileManager* GetFileManager() const { return m_pFileManager; }
    CoreProfile* GetProfile() const { return m_pProfile; }

    HRESULT SetApplicationFile(_In_ PCWSTR pPriPath, _In_opt_ PCWSTR pPackageRoot, _Out_ const ManagedResourceMap** result);

    HRESULT SetApplicationPriFile(_In_ PCWSTR pPriPath, _In_opt_ PCWSTR pPackageRoot, _Out_ const PriFile** result);

    HRESULT GetApplicationFileInfo(
        _Inout_opt_ StringResult* pPriFilePathOut,
        _Inout_opt_ StringResult* pPackageRootOut,
        _Out_opt_ size_t* pSizeOut,
        _Out_opt_ UINT64* pDateOut) const;

    HRESULT GetApplicationPriFile(_Out_ const PriFile** result) const;

    int GetNumReferencedFiles() const { return (m_pReferencedFiles ? m_pReferencedFiles->Count() : 0); }

    HRESULT GetReferencedFileInfo(
        _In_ int index,
        _Inout_opt_ StringResult* pPriFilePathOut,
        _Inout_opt_ StringResult* pPackageRootOut,
        _Out_opt_ size_t* pSizeOut,
        _Out_opt_ UINT64* pDateOut) const;

    HRESULT GetOrAddReferencedFile(
        _In_ PCWSTR pPriPath,
        _In_opt_ PCWSTR pPackageRoot,
        _Out_ const ManagedResourceMap** result,
        _Out_opt_ int* pIndex);

    HRESULT LoadPriFiles(
        _In_ MRMPROFILE_PHASE mrmProfilePhase,
        _In_ DynamicArray<StringResult*>* pFilePathsCollection,
        _In_ LoadPriFlags flags,
        _Out_ DynamicArray<PriFileInfo*>** ppLoadedPriFilesInfo);

    HRESULT RemoveFileReference(_In_ PCWSTR pPriPath);

    UINT32 GetDefaultFileFlags() const { return m_pFileManager->GetDefaultFileFlags(); }

    HRESULT SetDefaultFileFlags(_In_ UINT32 flags) { return m_pFileManager->SetDefaultFileFlags(flags); }

    // UnifiedResourceView
    AtomPoolGroup* GetAtoms() const { return m_pAtoms; }
    UnifiedDecisionInfo* GetDefaultDecisionInfo() const { return m_pDecisions; }
    UnifiedEnvironment* GetUnifiedEnvironment() const { return m_pEnvironment; }
    ProviderResolver* GetDefaultResolver() const { return m_pResolver; }

    // Schema Collection
    int GetNumSchemas() const;

    HRESULT GetSchema(_In_ int index, _Out_ const IHierarchicalSchema** result) const;

    HRESULT GetPrimarySchema(_Out_ const IHierarchicalSchema** result) const;

    HRESULT GetSchemaById(_In_ PCWSTR pSchemaId, _Out_ const IHierarchicalSchema** result) const;

    HRESULT FindSchema(_In_ const HierarchicalSchemaReference* pRef, _Outptr_ const IHierarchicalSchema** ppSchemaOut) const;

    // ResourceMapCollection
    int GetNumResourceMaps() const;

    HRESULT GetResourceMap(_In_ int index, _Out_ const IResourceMapBase** result) const;

    HRESULT GetManagedResourceMap(_In_ int index, _Out_ const ManagedResourceMap** result) const;

    HRESULT GetPrimaryResourceMap(_Out_ const IResourceMapBase** result) const;

    HRESULT GetResourceMapById(_In_ PCWSTR pSchemaId, _Out_ const IResourceMapBase** result) const;

    bool TryFindResourceMap(_In_ const HierarchicalSchemaReference* pRef, _Outptr_opt_ const IResourceMapBase** ppSchemaOut) const;

    bool TryGetReverseFileMap(_Outptr_opt_ const ReverseFileMap** ppMapOut) const;

protected:
    CoreProfile* m_pProfile{ nullptr };

    PriFileManager* m_pFileManager{ nullptr };
    AtomPoolGroup* m_pAtoms{ nullptr };
    UnifiedEnvironment* m_pEnvironment{ nullptr };
    UnifiedDecisionInfo* m_pDecisions{ nullptr };
    ProviderResolver* m_pResolver{ nullptr };

    DynamicArray<UnifiedViewFileInfo*>* m_pReferencedFiles{ nullptr };

    DynamicArray<ManagedSchema*>* m_pSchemas{ nullptr };
    DynamicArray<ManagedResourceMap*>* m_pMaps{ nullptr };

    UnifiedViewFileInfo* m_pAppFile{ nullptr };

    UnifiedResourceView(_In_ CoreProfile* pProfile);

    HRESULT Init();

    bool TryFindReferencedFile(
        _In_ PCWSTR pPath,
        _In_opt_ PCWSTR pPackageRoot,
        _Outptr_opt_result_maybenull_ UnifiedViewFileInfo** ppFileInfoOut,
        _Out_opt_ int* pFileIndexOut);

    HRESULT AddReferencedFile(_In_ UnifiedViewFileInfo* pFile, _Out_opt_ int* pFileIndexOut);

    HRESULT RemoveReferencedFile(_In_ UnifiedViewFileInfo* pFile);

    HRESULT
    GetOrAddManagedSchema(
        _In_ const ManagedFile* pFile,
        _In_ const IHierarchicalSchema* pSchema,
        _Outptr_opt_result_maybenull_ ManagedSchema** ppSchemaOut);

    HRESULT
    GetOrAddManagedResourceMap(
        _In_ const ManagedFile* pFile,
        _In_ const IResourceMapBase* pMap,
        _Outptr_opt_result_maybenull_ ManagedResourceMap** ppMapOut);

    HRESULT RemoveFileResourceInfo(_In_ UnifiedViewFileInfo* pFileInfo);
};

class IResolver : public DefObject
{
public:
    virtual ~IResolver() {}

    virtual const UnifiedEnvironment* GetEnvironment() const = 0;
    virtual const IDecisionInfo* GetDecisions() const = 0;

    virtual const IResolver* GetParent() const = 0;

    virtual void Reset() = 0;

    virtual HRESULT Reset(_In_reads_(numQualifiers) Atom* pQualifiers, _In_ int numQualifiers) = 0;

    virtual HRESULT SetQualifier(_In_ PCWSTR pQualifierValue, _In_ PCWSTR pNewValue) = 0;

    virtual UINT64 GetGeneration() const = 0;

    virtual HRESULT GetQualifierValue(_In_ PCWSTR pQualifier, _Inout_ StringResult* pValue) const = 0;

    virtual HRESULT GetQualifierValue(_In_ Atom qualifier, _Inout_ StringResult* pValue) const = 0;

    virtual HRESULT EvaluateQualifier(_In_ const IQualifier* pQualifier, _Out_ double* pScoreOut, _Out_ double* pFallbackScoreOut)
        const = 0;

    virtual HRESULT EvaluateQualifierSet(
        _In_ const IQualifierSet* pQualifierSet,
        _Out_ bool* pbIsMatchOut,
        _Out_ bool* pbIsDefaultOut,
        _Out_ bool* pbIsMatchAsDefaultOut,
        _Out_opt_ UINT16* pScoreOut) const = 0;

    virtual HRESULT EvaluateDecision(_In_ const IDecision* pDecision, _Out_ int* pResultIndexOut, _Inout_ QualifierSetResult* pResultSetOut)
        const = 0;

    virtual HRESULT EvaluateDecision(
        _In_ const IDecision* pDecision,
        _In_ int numResults,
        _Out_writes_(numResults) int* pResultIndexesOut,
        _Out_writes_(numResults) int* pResultSetIndexesOut) const = 0;

    virtual HRESULT GetQualifierProvider(_In_ PCWSTR qualifierName, _Out_ const IQualifierValueProvider** provider) const = 0;
};

class ResolverBase : public IResolver
{
public:
    virtual ~ResolverBase();

    const UnifiedEnvironment* GetEnvironment() const { return m_pEnvironment; }
    const IDecisionInfo* GetDecisions() const { return m_pDecisions; }

    virtual const IResolver* GetParent() const = 0;

    virtual void Reset();

    virtual HRESULT Reset(_In_reads_(numQualifierNames) Atom* pQualifierNames, _In_ int numQualifierNames);

    UINT64 GetGeneration() const { return m_generation; }

    virtual HRESULT GetQualifierValue(_In_ PCWSTR pQualifier, _Inout_ StringResult* pValue) const = 0;

    virtual HRESULT GetQualifierValue(_In_ Atom qualifier, _Inout_ StringResult* pValue) const = 0;

    HRESULT EvaluateQualifier(_In_ const IQualifier* pQualifier, _Out_ double* pScoreOut, _Out_ double* pFallbackScoreOut) const;

    HRESULT EvaluateQualifierSet(
        _In_ const IQualifierSet* pQualifierSet,
        _Out_ bool* pbIsMatchOut,
        _Out_ bool* pbIsDefaultOut,
        _Out_ bool* pbIsMatchAsDefaultOut,
        _Out_opt_ UINT16* pScoreOut) const;

    HRESULT EvaluateDecision(_In_ const IDecision* pDecision, _Out_ int* pResultIndexOut, _Inout_ QualifierSetResult* pResultSetOut) const;

    HRESULT EvaluateDecision(
        _In_ const IDecision* pDecision,
        _In_ int numResults,
        _Out_writes_(numResults) int* pResultIndexesOut,
        _Out_writes_(numResults) int* pResultSetIndexesOut) const;

    virtual HRESULT GetQualifierProvider(_In_ PCWSTR qualifierName, _Out_ const IQualifierValueProvider** provider) const override = 0;

protected:
    ResolverBase(_In_ const UnifiedEnvironment* pEnvironment, _In_ const IDecisionInfo* pDecisions);

    HRESULT Init();

    HRESULT EvaluateQualifier(_In_ const IQualifier* pQualifier, _Out_ UINT16* pScoreOut, _Out_ UINT16* pFallbackScoreOut) const;

    class DecisionInfoCache;

    const UnifiedEnvironment* m_pEnvironment{ nullptr };
    const IDecisionInfo* m_pDecisions{ nullptr };
    UINT64 m_generation = 0;

    mutable DecisionInfoCache* m_pCache{ nullptr };
    mutable SRWLOCK m_srwLock{ nullptr };
    mutable SRWLOCK m_srwQualifierSetLock{ nullptr };
    mutable SRWLOCK m_srwQualifierLock{ nullptr };
};

class ProviderResolver : public ResolverBase
{
public:
    static HRESULT CreateInstance(
        _In_ CoreProfile* pProfile,
        _In_ const UnifiedEnvironment* pEnvironment,
        _In_ const IDecisionInfo* pDecisions,
        _Outptr_ ProviderResolver** result);

    virtual ~ProviderResolver();

    HRESULT SetProvider(_In_ PCWSTR pQualifier, _In_opt_ IQualifierValueProvider* pProvider, _In_ bool bTakeOwnership);

    HRESULT SetProvider(_In_ Atom qualifierName, _In_opt_ IQualifierValueProvider* pProvider, _In_ bool bTakeOwnership);

    HRESULT InitAllQualifierProviders(_In_ CoreProfile* pProfile);

    const IResolver* GetParent() const { return nullptr; }

    void Reset();

    HRESULT Reset(_In_reads_(numQualifierNames) Atom* pQualifierNames, _In_ int numQualifierNames);

    HRESULT GetQualifierValue(_In_ PCWSTR pQualifier, _Inout_ StringResult* pValue) const;

    HRESULT GetQualifierValue(_In_ Atom qualifier, _Inout_ StringResult* pValue) const;

    HRESULT SetQualifier(_In_ Atom qualifier, _In_ PCWSTR pNewValue);

    HRESULT SetQualifier(_In_ PCWSTR pQualifierValue, _In_ PCWSTR pNewValue);

    virtual HRESULT GetQualifierProvider(_In_ PCWSTR qualifierName, _Out_ const IQualifierValueProvider** provider) const override;

protected:
    ProviderResolver(_In_ const UnifiedEnvironment* pEnvironment, _In_ const IDecisionInfo* pDecisions);

    HRESULT Init();

    class PerQualifierPoolInfo;

    mutable IProviderDataSources* m_pDataSources{ nullptr };
    mutable PerQualifierPoolInfo* m_pQualifiers{ nullptr };
};

class PerThreadQualifier;
class OverrideResolver : public ResolverBase
{
public:
    static HRESULT CreateInstance(_In_ const IResolver* pParent, _Outptr_ OverrideResolver** result);

    static HRESULT CreateInstance(
        _In_ CoreProfile* pProfile,
        _In_ const UnifiedEnvironment* pEnvironment,
        _In_ const IResolver* pParent,
        _In_ bool bCloned,
        _Outptr_ OverrideResolver** result);

    virtual ~OverrideResolver();

    HRESULT SetQualifier(_In_ Atom qualifier, _In_ PCWSTR pNewValue);

    HRESULT SetQualifier(_In_ PCWSTR pQualifierValue, _In_ PCWSTR pNewValue);

    HRESULT OverrideToMatch(_In_ const IQualifierSet* pQualifiers);

    const IResolver* GetParent() const { return m_pParent; }

    void Reset();

    HRESULT Reset(_In_reads_(numQualifiers) Atom* pQualifiers, _In_ int numQualifiers);

    HRESULT GetQualifierValue(_In_ PCWSTR pQualifierName, _Inout_ StringResult* pValue) const;

    HRESULT GetQualifierValue(_In_ Atom qualifier, _Inout_ StringResult* pValue) const;

    bool IsQualifierValueOverriden(_In_ PCWSTR pQualifierName) const;

    bool IsQualifierValueOverriden(_In_ Atom qualifier) const;

    HRESULT EvaluateDecision(_In_ const IDecision* pDecision, _Out_ int* pResultIndexOut, _Inout_ QualifierSetResult* pResultSetOut) const;

    HRESULT EvaluateDecision(
        _In_ const IDecision* pDecision,
        _In_ int numResults,
        _Out_writes_(numResults) int* pResultIndexesOut,
        _Out_writes_(numResults) int* pResultSetIndexesOut) const;

    HRESULT EvaluateQualifierSet(
        _In_ const IQualifierSet* pQualifierSet,
        _Out_ bool* pbIsMatchOut,
        _Out_ bool* pbIsDefaultOut,
        _Out_ bool* pbIsMatchOrDefaultOut,
        _Out_opt_ UINT16* pScoreOut = nullptr) const;

    HRESULT EvaluateQualifier(_In_ const IQualifier* pQualifier, _Out_ double* pScoreOut, _Out_ double* pFallbackScoreOut) const;

    HRESULT EvaluateDecisionForQualiferSetResult(
        _In_ const IDecision* pDecision,
        _In_ bool bMultiInstances,
        _Out_ int* pResultIndexOut,
        _Out_ bool* pbIsMatchOut,
        _Out_ bool* pbIsDefaultOut,
        _Out_ bool* pbIsMatchOrDefaultOut,
        _Out_opt_ UINT16* pScoreOut) const;

    virtual HRESULT GetQualifierProvider(_In_ PCWSTR qualifierName, _Out_ const IQualifierValueProvider** provider) const override;

protected:
    class PerQualifierPoolInfo;

    const IResolver* m_pParent{ nullptr };
    mutable PerQualifierPoolInfo* m_pQualifiers{ nullptr };
    bool m_bHasScoreCache{ false };
    bool m_bIsDifferentQualifierValueFromParent{ false };
    PerThreadQualifier* m_pPerThreadQualifier{ nullptr };
    bool m_bClonedResolver{ false };
    mutable SRWLOCK m_srwQualifierValuesLock{ nullptr };

    OverrideResolver(_In_ const IResolver* pParent);

    OverrideResolver(_In_ const IResolver* pParent, _In_ bool bCloned);

    HRESULT Init();
    HRESULT Init(_In_ CoreProfile* pProfile, _In_ const UnifiedEnvironment* pEnvironment);
};

} // namespace Microsoft::Resources