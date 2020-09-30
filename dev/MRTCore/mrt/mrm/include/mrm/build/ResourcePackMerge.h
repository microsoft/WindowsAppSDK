// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

namespace Microsoft::Resources
{

enum PriMergeState
{
    AutoMergeAddPriToMerger = 1,
    AutoMergeCheckCompatibilityResult,
    AutoMergeUnableToCheckCompatibility,
    AutoMergeTryPersist,
    AutoMergeCleanupOldFiles,

    PerformMergeMainSchemaName = 10,
    PerformMergeFailedToInit,
    PerformMergeInvalidMergeFlags,
    PerformMergeFailedToAddFile,
    PerformMergeFailedToPersistFile,
    PerformMergeFailedToAddResourceMap,
    PerformMergeFailedToAddCandiate,
    PerformMergeFailedToGetQualifiers,
    PerformMergeFailedToAddResource,
    PerformMergeIncompatibleSchemaVersion,
    PerformMergeAutoMergeFlagEnabled,
    PerformMergeDeploymentMergeFlagDisabled,
    PerformMergeSchemaNameMismatch,
    PerformMergeSchemaMajorVersionMismatch,
    PerformMergeSmallerSchemaMinorVersion,
    PerformMergeLargeSchemaMinorVersion,
};

class ResourcePackMerge : public DefObject
{
public:
    static HRESULT CreateInstance(_In_ CoreProfile* pProfile, _Outptr_ ResourcePackMerge** result);

    ~ResourcePackMerge();

    HRESULT AddPriFile(_In_ PCWSTR pszPriFileName, _In_ PriFileMerger::PriMergeFlags priMergeFlags);

    bool IsFinalized() const;

    HRESULT WriteToFile(_In_ PCWSTR pszOutputFile);

    static HRESULT GetPriFileChecksums(_In_ PCWSTR pPriFileName, _In_ CoreProfile* pProfile, _Out_ DEF_CHECKSUM* pContentChecksum);

private:
    ResourcePackMerge(_In_ CoreProfile* pProfile);

    HRESULT Init();

    HRESULT AddFileToFileList(_In_ PCWSTR pszFilePath, _In_ PriFileMerger::PriMergeFlags priMergeFlags, _Out_ FileInfo** ppFileInfo);

    HRESULT AddRootFolder(_In_ PWSTR pszLocalFilePath, _Out_ PWSTR* ppszFilePathNext, _Out_ FolderInfo** ppFolderInfo);

    HRESULT ValidateFilePath(_In_ PCWSTR pszFilePath) const;

    HRESULT
    GetFolderOrFileName(_In_ PWSTR pszFilePath, _Inout_ StringResult* pStringResult, _Out_ bool* pbFolder, _Out_ PWSTR* ppszFilePathNext)
        const;

    HRESULT AddResourceMap(
        _In_ const FileInfo* pFileInfo,
        _In_ const IResourceMapBase* pResourceMapBase,
        _In_ PriFileMerger::PriMergeFlags mergeFlags);

    HRESULT GetOrAddQualifierSet(
        _In_ DecisionInfoSectionBuilder* pMergedDecisions,
        _In_ IQualifierSet* pQualifierSet,
        _Inout_ DynamicArray<int>* pQualifierSetIndexes,
        _Out_ int* pNewQualifierSetIndex);

    bool ValidateResourceMap(
        _In_ const IResourceMapBase* pResourceMapBase,
        _In_ PriFileMerger::PriMergeFlags mergeFlags,
        _Inout_ PriFileMerger::PriMergeFlags* pUpdatedMergeFlags) const;

    bool ValidatePriFileMergeFlag(_In_ PriFileMerger::PriMergeFlags mergeFlags) const;

    bool ValidateInPlaceMergeEnabled(_In_ const PriFile* pPriFile) const;

    AtomPoolGroup* m_pAtoms;
    UnifiedEnvironment* m_pEnvironment;
    PriFileManager* m_pPriFileManager;
    PriFileBuilder* m_pFileBuilder;
    bool bFinalized;
    CoreProfile* m_pProfile;
    mutable const IHierarchicalSchema* m_pFirstEntrySchema;
    FileListBuilder* m_pFileListBuilder;
    DynamicArray<PriFile*>* m_pPriFileList;
};

} // namespace Microsoft::Resources