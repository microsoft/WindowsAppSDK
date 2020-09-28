// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"

namespace Microsoft::Resources
{

class MrmFileSection : public BaseFileSectionResult
{
public:
    MrmFileSection() : BaseFileSectionResult(), m_sectionType(SectionTypeUnknown), isInitialized(false) { u.pFileList = nullptr; }

    virtual ~MrmFileSection() { ResetSection(); }

    bool IsInitialized() { return isInitialized; }

    HRESULT Init(_In_ const BaseFile* pParent, _In_ BaseFile::SectionIndex index)
    {
        ResetSection();

        RETURN_IF_FAILED(pParent->GetFileSection(index, this));
        isInitialized = true;
        return S_OK;
    }

    HRESULT GetAtomPoolSection(_Out_ FileAtomPool** result)
    {
        *result = nullptr;
        if (m_sectionType == SectionTypeUnknown)
        {
            RETURN_IF_FAILED(FileAtomPool::CreateInstance(this, &u.pAtomPool));

            m_sectionType = SectionTypeAtomPool;
        }
        else if (m_sectionType != SectionTypeAtomPool)
        {
            u.pAtomPool = nullptr;
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }
        *result = u.pAtomPool;

        return S_OK;
    }

    HRESULT GetDecisionInfoSection(_In_ const IFileSectionResolver* pResolver, _Out_ DecisionInfoFileSection** result)
    {
        *result = nullptr;

        if (m_sectionType == SectionTypeUnknown)
        {
            // get default qualifier mapping for the file which contains the decision info
            const RemapAtomPool* pMapping;
            (void)pResolver->GetDefaultQualifierMapping(0, &pMapping);

            RETURN_IF_FAILED(DecisionInfoFileSection::CreateInstance(this, pMapping, &u.pDecisionInfo));

            m_sectionType = SectionTypeDecisionInfo;
        }
        else if (m_sectionType != SectionTypeDecisionInfo)
        {
            u.pDecisionInfo = nullptr;
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        *result = u.pDecisionInfo;
        return S_OK;
    }

    HRESULT GetSchemaSection(_Out_ HierarchicalSchema** result)
    {
        *result = nullptr;
        if (m_sectionType == SectionTypeUnknown)
        {
            RETURN_IF_FAILED(HierarchicalSchema::CreateFromSection(this, &u.pSchema));
            m_sectionType = SectionTypeSchema;
        }
        else if (m_sectionType != SectionTypeSchema)
        {
            u.pSchema = nullptr;
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }
        *result = u.pSchema;
        return S_OK;
    }

    HRESULT GetResourceMapSection(
        _In_ const IFileSectionResolver* pResolver,
        _In_ const ISchemaCollection* pSchemaCollection,
        _Out_ ResourceMapBase** result)
    {
        *result = nullptr;
        if (m_sectionType == SectionTypeUnknown)
        {
            RETURN_IF_FAILED(ResourceMapBase::CreateInstance(pResolver, pSchemaCollection, this, &u.pResourceMap));
            m_sectionType = SectionTypeResourceMap;
        }
        else if (m_sectionType != SectionTypeResourceMap)
        {
            u.pResourceMap = nullptr;
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }
        *result = u.pResourceMap;
        return S_OK;
    }

    HRESULT GetPriDescriptorSection(
        _In_ const IFileSectionResolver* pResolver,
        _In_ const ISchemaCollection* pSchemaCollection,
        _Out_ PriDescriptor** result)
    {
        *result = nullptr;
        if (m_sectionType == SectionTypeUnknown)
        {
            RETURN_IF_FAILED(PriDescriptor::CreateInstance(pResolver, pSchemaCollection, this, &u.pPriDescriptor));
            m_sectionType = SectionTypePriDescriptor;
        }
        else if (m_sectionType != SectionTypePriDescriptor)
        {
            u.pPriDescriptor = nullptr;
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }
        *result = u.pPriDescriptor;
        return S_OK;
    }

    HRESULT GetFileListSection(_Out_ FileFileList** result)
    {
        *result = nullptr;
        if (m_sectionType == SectionTypeUnknown)
        {
            RETURN_IF_FAILED(FileFileList::CreateInstance(this, &u.pFileList));
            m_sectionType = SectionTypeFileList;
        }
        else if (m_sectionType != SectionTypeFileList)
        {
            u.pFileList = nullptr;
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }
        *result = u.pFileList;
        return S_OK;
    }

    HRESULT GetDataSection(_Out_ FileDataSection** result)
    {
        *result = nullptr;
        if (m_sectionType == SectionTypeUnknown)
        {
            RETURN_IF_FAILED(FileDataSection::CreateInstance(this, &u.pData));
            m_sectionType = SectionTypeData;
        }
        else if (m_sectionType != SectionTypeData)
        {
            u.pData = nullptr;
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }
        *result = u.pData;
        return S_OK;
    }

    HRESULT GetDataItemsSection(_Out_ FileDataItemsSection** result)
    {
        *result = nullptr;
        if (m_sectionType == SectionTypeUnknown)
        {
            RETURN_IF_FAILED(FileDataItemsSection::CreateInstance(this, &u.pDataItems));
            m_sectionType = SectionTypeDataItems;
        }
        else if (m_sectionType != SectionTypeDataItems)
        {
            u.pDataItems = nullptr;
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }
        *result = u.pDataItems;
        return S_OK;
    }

    HRESULT GetReverseFileMapSection(_Out_ ReverseFileMap** result)
    {
        *result = nullptr;
        if (m_sectionType == SectionTypeUnknown)
        {
            RETURN_IF_FAILED(ReverseFileMap::CreateInstance(this, &u.pReverseMap));
            m_sectionType = SectionTypeReverseMap;
        }
        else if (m_sectionType != SectionTypeReverseMap)
        {
            u.pReverseMap = nullptr;
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }
        *result = u.pReverseMap;
        return S_OK;
    }

    HRESULT
    GetEnvironmentMappingSection(
        _In_ const CoreProfile* profile,
        _In_ const IEnvironmentCollection* environments,
        _Out_ const EnvironmentMapping** result)
    {
        bool typeMatch = BaseFile::SectionTypesEqual(GetSectionType(), gEnvironmentMappingSectionType);

        if ((m_sectionType == SectionTypeUnknown) && typeMatch)
        {
            RETURN_IF_FAILED(EnvironmentMapping::CreateInstance(profile, environments, GetData(), GetDataSize(), &u.pEnvironmentMap));
            m_sectionType = SectionTypeEnvironmentMapping;
        }
        else if ((m_sectionType != SectionTypeEnvironmentMapping) || (!typeMatch))
        {
            u.pEnvironmentMap = nullptr;
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }
        *result = u.pEnvironmentMap;
        return S_OK;
    }

    HRESULT
    GetResourceLinkSection(
        _In_opt_ const IFileSectionResolver* sections,
        _In_opt_ const ISchemaCollection* schemas,
        _Out_ const ResourceLinkSection** result)
    {
        bool typeMatch = BaseFile::SectionTypesEqual(GetSectionType(), ResourceLinkSection::GetSectionTypeId());

        if ((m_sectionType == SectionTypeUnknown) && typeMatch)
        {
            RETURN_IF_FAILED(ResourceLinkSection::CreateFromSection(sections, schemas, this, &u.pResourceLink));
            m_sectionType = SectionTypeResourceLink;
        }
        else if ((m_sectionType != SectionTypeResourceLink) || (!typeMatch))
        {
            u.pEnvironmentMap = nullptr;
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }
        *result = u.pResourceLink;
        return S_OK;
    }

protected:
    bool isInitialized;

    enum SectionType
    {
        SectionTypeUnknown = 0,
        SectionTypeAtomPool = 1,
        SectionTypeDecisionInfo = 2,
        SectionTypeSchema = 3,
        SectionTypeResourceMap = 4,
        SectionTypePriDescriptor = 5,
        SectionTypeFileList = 6,
        SectionTypeDataItems = 7,
        SectionTypeData = 8,
        SectionTypeReverseMap = 9,
        SectionTypeEnvironmentMapping = 10,
        SectionTypeResourceLink = 11
    };

    SectionType m_sectionType;
    union
    {
        IFileSection* pOther;
        FileAtomPool* pAtomPool;
        DecisionInfoFileSection* pDecisionInfo;
        HierarchicalSchema* pSchema;
        ResourceMapBase* pResourceMap;
        PriDescriptor* pPriDescriptor;
        FileFileList* pFileList;
        FileDataItemsSection* pDataItems;
        FileDataSection* pData;
        ReverseFileMap* pReverseMap;
        EnvironmentMapping* pEnvironmentMap;
        ResourceLinkSection* pResourceLink;
    } u;

    void ResetSection()
    {
        if (u.pFileList != nullptr)
        {
            switch (m_sectionType)
            {
            default:
                delete u.pOther;
                break;
            case SectionTypeAtomPool:
                delete u.pAtomPool;
                break;
            case SectionTypeDecisionInfo:
                delete u.pDecisionInfo;
                break;
            case SectionTypeSchema:
                delete u.pSchema;
                break;
            case SectionTypeResourceMap:
                delete u.pResourceMap;
                break;
            case SectionTypePriDescriptor:
                delete u.pPriDescriptor;
                break;
            case SectionTypeFileList:
                delete u.pFileList;
                break;
            case SectionTypeDataItems:
                delete u.pDataItems;
                break;
            case SectionTypeReverseMap:
                delete u.pReverseMap;
                break;
            case SectionTypeEnvironmentMapping:
                delete u.pEnvironmentMap;
                break;
            case SectionTypeData:
                delete u.pData;
                break;
            }
            u.pOther = nullptr;
        }
        m_sectionType = SectionTypeUnknown;
    }
};

class MrmFileResolver : DefObject
{
    // MrmFileResolver provides mapping index of FileList to global index of PriFileManager, and support add all files in the FileListSection
    // to the PriFileManager
public:
    using DefObject::operator delete;

    static HRESULT CreateInstance(_In_ PriFileManager* pPriFileManager, _Outptr_ MrmFileResolver** result)
    {
        *result = nullptr;

        MrmFileResolver* pRtrn = new MrmFileResolver(pPriFileManager);
        RETURN_IF_NULL_ALLOC(pRtrn);
        *result = pRtrn;

        return S_OK;
    }

    MrmFileResolver(_In_opt_ PriFileManager* pPriFileManager) : m_pPriFileManager(pPriFileManager), m_pFileInfoToGlobalIndex(nullptr) {}

    ~MrmFileResolver()
    {
        delete m_pFileInfoToGlobalIndex;
        m_pFileInfoToGlobalIndex = nullptr;
    }

    HRESULT AddReferencedFileInFileList(_In_ const FileFileList* pFileFileList)
    {
        RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pPriFileManager);

        if (!m_pFileInfoToGlobalIndex)
        {
            RETURN_IF_FAILED(RemapUInt16::CreateInstance(pFileFileList->GetTotalNumFiles(), &m_pFileInfoToGlobalIndex));
        }

        StringResult strFilePath;
        int numFiles = pFileFileList->GetTotalNumFiles() + 1;
        for (int fileInfoIndex = 1; fileInfoIndex < numFiles; fileInfoIndex++)
        {
            UINT16 flags = 0;
            RETURN_IF_FAILED(pFileFileList->GetFilePath(fileInfoIndex, &strFilePath, &flags));

            StringResult strPackageRoot;
            bool preLoad = ((flags & INPLACE_MERGE_PRELOAD) != 0);
            ManagedFile* pManagedFile;
            RETURN_IF_FAILED(m_pPriFileManager->GetOrAddFile(
                strFilePath.GetRef(), strPackageRoot.GetRef(), preLoad ? LoadPriFlags::Preload : LoadPriFlags::Default, &pManagedFile));

            RETURN_IF_FAILED(m_pFileInfoToGlobalIndex->SetOrChangeMapping(
                static_cast<UINT16>(fileInfoIndex), static_cast<UINT16>(pManagedFile->GetGlobalIndex())));
        }

        return S_OK;
    }

    HRESULT GetGlobalIndex(_In_ int fileIndex, _Out_ int* pGlobalIndex)
    {
        *pGlobalIndex = -1;

        RETURN_HR_IF(E_INVALIDARG, fileIndex == 0);
        RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pFileInfoToGlobalIndex);

        UINT16 globalIndex = -1;

        if (!m_pFileInfoToGlobalIndex->TryGetMapping(static_cast<UINT16>(fileIndex), &globalIndex))
        {
            RETURN_HR(E_INVALIDARG);
        }

        *pGlobalIndex = globalIndex;
        return S_OK;
    }

private:
    PriFileManager* m_pPriFileManager;
    RemapUInt16* m_pFileInfoToGlobalIndex;
};

HRESULT MrmFile::CreateInstance(_In_ UnifiedEnvironment* pEnvironment, _In_ UINT32 flags, _In_ PCWSTR pFileName, _Outptr_ MrmFile** result)
{
    *result = nullptr;
    AutoDeletePtr<MrmFile> pRtrn = new MrmFile();
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->Init(pEnvironment, flags, pFileName));
    *result = pRtrn.Detach();

    return S_OK;
}

HRESULT MrmFile::CreateInstance(_In_ PriFileManager* pManager, _In_ PCWSTR pFileName, _Outptr_ MrmFile** result)
{
    *result = nullptr;
    AutoDeletePtr<MrmFile> pRtrn = new MrmFile();
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->Init(pManager, pFileName));
    *result = pRtrn.Detach();

    return S_OK;
}

HRESULT MrmFile::CreateInstance(
    _In_ UnifiedEnvironment* pEnvironment,
    _In_ UINT32 flags,
    _In_reads_bytes_(cbData) const BYTE* pData,
    _In_ size_t cbData,
    _Outptr_ MrmFile** result)
{
    *result = nullptr;
    AutoDeletePtr<MrmFile> pRtrn = new MrmFile();
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->Init(pEnvironment, flags, pData, cbData));
    *result = pRtrn.Detach();

    return S_OK;
}

HRESULT MrmFile::CreateInstance(_In_ UnifiedEnvironment* pEnvironment, _In_ const BaseFile* pBaseFile, _Outptr_ MrmFile** result)
{
    *result = nullptr;
    AutoDeletePtr<MrmFile> pRtrn = new MrmFile();
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->Init(pEnvironment, pBaseFile));
    *result = pRtrn.Detach();

    return S_OK;
}

HRESULT MrmFile::Init(_In_ UnifiedEnvironment* pEnvironment, _In_ const BaseFile* pBaseFile)
{
    m_pBaseFile = pBaseFile;
    m_pEnvironment = pEnvironment;

    RETURN_IF_FAILED(InitSections());

    return S_OK;
}

HRESULT MrmFile::Init(_In_ UnifiedEnvironment* pEnvironment, _In_ UINT32 flags, _In_ PCWSTR pPath)
{
    RETURN_IF_FAILED(BaseFile::CreateInstance(flags, pPath, (BaseFile**)&m_pBaseFile));

    m_pMyBaseFile = m_pBaseFile;
    m_pEnvironment = pEnvironment;
    RETURN_IF_FAILED(InitSections());

    return S_OK;
}

HRESULT MrmFile::Init(_In_ PriFileManager* pManager, _In_ PCWSTR pPath)
{
    m_pPriFileManager = pManager;
    m_pEnvironment = pManager->GetUnifiedEnvironment();

    RETURN_IF_FAILED(BaseFile::CreateInstance(m_pPriFileManager->GetDefaultFileFlags(), pPath, (BaseFile**)&m_pBaseFile));

    m_pMyBaseFile = m_pBaseFile;

    RETURN_IF_FAILED(InitSections());
    RETURN_IF_FAILED(MrmFileResolver::CreateInstance(m_pPriFileManager, &m_pFileResolver));

    PCWSTR pFileName = wcsrchr(pPath, L'\\');
    if (pFileName != nullptr)
    {
        wchar_t wszFolder[MAX_PATH] = {};
        errno_t err = wcsncpy_s(wszFolder, _countof(wszFolder), pPath, pFileName - pPath);
        RETURN_IF_FAILED(ErrnoToHResult(err));

        RETURN_IF_FAILED(m_strRootFolder.SetCopy(wszFolder));
    }

    RETURN_IF_FAILED(m_strFilePath.SetCopy(pPath)); // copy the path

    return S_OK;
}

HRESULT
MrmFile::Init(_In_ UnifiedEnvironment* pEnvironment, _In_ UINT32 flags, _In_reads_bytes_(cbData) const BYTE* pData, _In_ size_t cbData)
{
    m_pEnvironment = pEnvironment;

    RETURN_IF_FAILED(BaseFile::CreateInstance(flags, pData, cbData, (BaseFile**)&m_pBaseFile));

    m_pMyBaseFile = m_pBaseFile;
    (void)InitSections();

    return S_OK;
}

MrmFile::~MrmFile()
{
    (void)ReleaseSections();
    delete m_pFileResolver;
}

CoreProfile* MrmFile::GetProfile() const { return m_pEnvironment->GetProfile(); }

HRESULT MrmFile::InitSections()
{
    if (m_pSections != nullptr)
    {
        return S_OK;
    }

    m_pSections = new MrmFileSection[m_pBaseFile->GetNumSections()];
    if (m_pSections == nullptr)
    {
        ReleaseSections();
        return E_OUTOFMEMORY;
    }

    // We do not initialize the various sections here. Rather, we initialize them on demand
    // when they are actually used to avoid excessive I/O on initialization.
    return S_OK;
}

void MrmFile::ReleaseSections()
{
    delete[] m_pSections;
    m_pSections = nullptr;

    delete m_pMyBaseFile;
    m_pMyBaseFile = nullptr;
    m_pBaseFile = nullptr;
}

HRESULT MrmFile::InitializeAndGetSection(_In_ BaseFile::SectionIndex sectionIndex, _Out_ MrmFileSection** result) const
{
    *result = nullptr;

    if ((sectionIndex < 0) || (sectionIndex >= m_pBaseFile->GetNumSections()))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    if (!m_pSections[sectionIndex].IsInitialized())
    {
        RETURN_IF_FAILED(m_pSections[sectionIndex].Init(m_pBaseFile, sectionIndex));
    }

    *result = &m_pSections[sectionIndex];
    return S_OK;
}

HRESULT MrmFile::GetSection(
    _In_ const ISchemaCollection* /* pSchemaCollection */,
    _In_ int fileIndex,
    _In_ BaseFile::SectionIndex sectionIndex,
    _Out_ const IFileSection** result) const
{
    *result = nullptr;
    RETURN_HR_IF(E_DEF_NOT_READY, fileIndex != 0);

    if ((sectionIndex < 0) || (sectionIndex >= m_pBaseFile->GetNumSections()))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    RETURN_IF_FAILED(InitializeAndGetSection(sectionIndex, (MrmFileSection**)result));
    return S_OK;
}

const bool MrmFile::TryGetSectionIndexByType(
    _In_ const DEFFILE_SECTION_TYPEID& sectionType,
    _In_ int fileIndex,
    _In_ int startAtSectionIndex,
    _Out_ int* nextSectionIndex) const
{
    if (fileIndex == 0)
    {
        if ((startAtSectionIndex < 0) || (startAtSectionIndex >= m_pBaseFile->GetNumSections()))
        {
            return false;
        }

        for (int i = startAtSectionIndex; i < m_pBaseFile->GetNumSections(); i++)
        {
            const DEFFILE_TOC_ENTRY* toc;
            m_pBaseFile->GetTocEntry(i, &toc);
            if ((toc != nullptr) && BaseFile::SectionTypesEqual(sectionType, toc->type))
            {
                *nextSectionIndex = i;
                return true;
            }
        }

        *nextSectionIndex = -1;

        return false;
    }

    if (m_pPriFileManager != nullptr)
    {
        int globalFileIndex;
        if (FAILED(m_pFileResolver->GetGlobalIndex(fileIndex, &globalFileIndex)))
        {
            return false;
        }

        return m_pPriFileManager->TryGetSectionIndexByType(sectionType, globalFileIndex, startAtSectionIndex, nextSectionIndex);
    }

    return false;
}

HRESULT MrmFile::GetAtomPoolSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileAtomPool** result) const
{
    *result = nullptr;

    if (fileIndex == 0)
    {
        if ((sectionIndex < 0) || (sectionIndex >= m_pBaseFile->GetNumSections()))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        MrmFileSection* pSection;
        RETURN_IF_FAILED(InitializeAndGetSection(sectionIndex, &pSection));

        RETURN_IF_FAILED(pSection->GetAtomPoolSection(result));

        return S_OK;
    }

    if (m_pPriFileManager)
    {
        int globalFileIndex;
        RETURN_IF_FAILED(m_pFileResolver->GetGlobalIndex(fileIndex, &globalFileIndex));

        RETURN_IF_FAILED(m_pPriFileManager->GetAtomPoolSection(globalFileIndex, sectionIndex, result));
    }
    else
    {
        return E_INVALIDARG;
    }

    return S_OK;
}

HRESULT
MrmFile::GetDecisionInfoSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ DecisionInfoFileSection** result) const
{
    *result = nullptr;

    if (fileIndex == 0)
    {
        if ((sectionIndex < 0) || (sectionIndex >= m_pBaseFile->GetNumSections()))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        MrmFileSection* pSection;
        RETURN_IF_FAILED(InitializeAndGetSection(sectionIndex, &pSection));

        RETURN_IF_FAILED(pSection->GetDecisionInfoSection(this, result));

        return S_OK;
    }

    if (m_pPriFileManager != nullptr)
    {
        int globalFileIndex;
        RETURN_IF_FAILED(m_pFileResolver->GetGlobalIndex(fileIndex, &globalFileIndex));

        RETURN_IF_FAILED(m_pPriFileManager->GetDecisionInfoSection(globalFileIndex, sectionIndex, result));
    }
    else
    {
        return E_INVALIDARG;
    }

    return S_OK;
}

HRESULT MrmFile::GetSchemaSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ HierarchicalSchema** result) const
{
    *result = nullptr;

    if (fileIndex == 0)
    {
        if ((sectionIndex < 0) || (sectionIndex >= m_pBaseFile->GetNumSections()))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        MrmFileSection* pSection;
        RETURN_IF_FAILED(InitializeAndGetSection(sectionIndex, &pSection));

        if (FAILED(pSection->GetSchemaSection(result)))
        {
            // The most common way to get here is to try and load a schema-free resource pack without supplying the schema.
            // Set a distinct error code so that we can handle this case gracefully higher up the stream where appropriate.
            return HRESULT_FROM_WIN32(ERROR_MRM_UNSUPPORTED_FILE_TYPE_FOR_LOAD_UNLOAD_PRI_FILE);
        }

        return S_OK;
    }

    if (m_pPriFileManager)
    {
        int globalFileIndex;
        RETURN_IF_FAILED(m_pFileResolver->GetGlobalIndex(fileIndex, &globalFileIndex));

        RETURN_IF_FAILED(m_pPriFileManager->GetSchemaSection(globalFileIndex, sectionIndex, result));
    }
    else
    {
        return E_INVALIDARG;
    }

    return S_OK;
}

HRESULT MrmFile::GetResourceMapSection(
    _In_ const ISchemaCollection* pSchemaCollection,
    _In_ int fileIndex,
    _In_ BaseFile::SectionIndex sectionIndex,
    _Out_ ResourceMapBase** result) const
{
    *result = nullptr;

    if (fileIndex == 0)
    {
        if ((sectionIndex < 0) || (sectionIndex >= m_pBaseFile->GetNumSections()))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        MrmFileSection* pSection;
        RETURN_IF_FAILED(InitializeAndGetSection(sectionIndex, &pSection));

        RETURN_IF_FAILED(pSection->GetResourceMapSection(this, pSchemaCollection, result));

        return S_OK;
    }

    if (m_pPriFileManager)
    {
        int globalFileIndex;
        RETURN_IF_FAILED(m_pFileResolver->GetGlobalIndex(fileIndex, &globalFileIndex));

        RETURN_IF_FAILED(m_pPriFileManager->GetResourceMapSection(pSchemaCollection, globalFileIndex, sectionIndex, result));
    }
    else
    {
        return E_INVALIDARG;
    }

    return S_OK;
}

HRESULT MrmFile::GetPriDescriptorSection(
    _In_ const ISchemaCollection* pSchemaCollection,
    _In_ int fileIndex,
    _In_ BaseFile::SectionIndex sectionIndex,
    _Out_ PriDescriptor** result) const
{
    *result = nullptr;

    if (fileIndex == 0)
    {
        if ((sectionIndex < 0) || (sectionIndex >= m_pBaseFile->GetNumSections()))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        MrmFileSection* pSection;
        RETURN_IF_FAILED(InitializeAndGetSection(sectionIndex, &pSection));

        RETURN_IF_FAILED(pSection->GetPriDescriptorSection(this, pSchemaCollection, result));

        return S_OK;
    }

    if (m_pPriFileManager)
    {
        int globalFileIndex;
        RETURN_IF_FAILED(m_pFileResolver->GetGlobalIndex(fileIndex, &globalFileIndex));

        RETURN_IF_FAILED(m_pPriFileManager->GetPriDescriptorSection(pSchemaCollection, globalFileIndex, sectionIndex, result));
    }
    else
    {
        return E_INVALIDARG;
    }

    return S_OK;
}

HRESULT MrmFile::GetFileListSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileFileList** result) const
{
    *result = nullptr;

    if (fileIndex == 0)
    {
        if ((sectionIndex < 0) || (sectionIndex >= m_pBaseFile->GetNumSections()))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        MrmFileSection* pSection;
        RETURN_IF_FAILED(InitializeAndGetSection(sectionIndex, &pSection));

        RETURN_IF_FAILED(pSection->GetFileListSection(result));

        return S_OK;
    }

    if (m_pPriFileManager)
    {
        int globalFileIndex;
        RETURN_IF_FAILED(m_pFileResolver->GetGlobalIndex(fileIndex, &globalFileIndex));

        RETURN_IF_FAILED(m_pPriFileManager->GetFileListSection(globalFileIndex, sectionIndex, result));
    }
    else
    {
        return E_INVALIDARG;
    }

    return S_OK;
}

HRESULT
MrmFile::GetDataItemsSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileDataItemsSection** result) const
{
    *result = nullptr;

    if (fileIndex == 0)
    {
        if ((sectionIndex < 0) || (sectionIndex >= m_pBaseFile->GetNumSections()))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        MrmFileSection* pSection;
        RETURN_IF_FAILED(InitializeAndGetSection(sectionIndex, &pSection));

        RETURN_IF_FAILED(pSection->GetDataItemsSection(result));

        return S_OK;
    }

    if (m_pPriFileManager)
    {
        int globalFileIndex;
        RETURN_IF_FAILED(m_pFileResolver->GetGlobalIndex(fileIndex, &globalFileIndex));

        RETURN_IF_FAILED(m_pPriFileManager->GetDataItemsSection(globalFileIndex, sectionIndex, result));
    }
    else
    {
        return E_INVALIDARG;
    }

    return S_OK;
}

HRESULT MrmFile::GetDataSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileDataSection** result) const
{
    *result = nullptr;

    if (fileIndex == 0)
    {
        if ((sectionIndex < 0) || (sectionIndex >= m_pBaseFile->GetNumSections()))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        MrmFileSection* pSection;
        RETURN_IF_FAILED(InitializeAndGetSection(sectionIndex, &pSection));

        RETURN_IF_FAILED(pSection->GetDataSection(result));

        return S_OK;
    }

    if (m_pPriFileManager)
    {
        int globalFileIndex;
        RETURN_IF_FAILED(m_pFileResolver->GetGlobalIndex(fileIndex, &globalFileIndex));

        RETURN_IF_FAILED(m_pPriFileManager->GetDataSection(globalFileIndex, sectionIndex, result));
    }
    else
    {
        return E_INVALIDARG;
    }

    return S_OK;
}

HRESULT MrmFile::GetReverseFileMapSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ ReverseFileMap** result) const
{
    *result = nullptr;

    if (fileIndex == 0)
    {
        if ((sectionIndex < 0) || (sectionIndex >= m_pBaseFile->GetNumSections()))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        MrmFileSection* pSection;
        RETURN_IF_FAILED(InitializeAndGetSection(sectionIndex, &pSection));

        RETURN_IF_FAILED(pSection->GetReverseFileMapSection(result));

        return S_OK;
    }

    if (m_pPriFileManager)
    {
        int globalFileIndex;
        RETURN_IF_FAILED(m_pFileResolver->GetGlobalIndex(fileIndex, &globalFileIndex));

        RETURN_IF_FAILED(m_pPriFileManager->GetReverseFileMapSection(globalFileIndex, sectionIndex, result));
    }
    else
    {
        return E_INVALIDARG;
    }

    return S_OK;
}

HRESULT MrmFile::GetEnvironmentMappingSection(
    _In_ int fileIndex,
    _In_ BaseFile::SectionIndex sectionIndex,
    _Out_ const EnvironmentMapping** result) const
{
    *result = nullptr;

    if (fileIndex == 0)
    {
        if ((sectionIndex < 0) || (sectionIndex >= m_pBaseFile->GetNumSections()))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        MrmFileSection* pSection;
        RETURN_IF_FAILED(InitializeAndGetSection(sectionIndex, &pSection));

        RETURN_IF_FAILED(pSection->GetEnvironmentMappingSection(GetProfile(), GetUnifiedEnvironment(), result));

        return S_OK;
    }

    if (m_pPriFileManager != nullptr)
    {
        int globalFileIndex;
        RETURN_IF_FAILED(m_pFileResolver->GetGlobalIndex(fileIndex, &globalFileIndex));

        RETURN_IF_FAILED(m_pPriFileManager->GetEnvironmentMappingSection(globalFileIndex, sectionIndex, result));
    }
    else
    {
        return E_INVALIDARG;
    }

    return S_OK;
}

HRESULT MrmFile::GetResourceLinkSection(
    _In_opt_ const ISchemaCollection* schemas,
    _In_ int fileIndex,
    _In_ BaseFile::SectionIndex sectionIndex,
    _Out_ const ResourceLinkSection** result) const
{
    *result = nullptr;

    if (fileIndex == 0)
    {
        if ((sectionIndex < 0) || (sectionIndex >= m_pBaseFile->GetNumSections()))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        MrmFileSection* pSection;
        RETURN_IF_FAILED(InitializeAndGetSection(sectionIndex, &pSection));

        RETURN_IF_FAILED(pSection->GetResourceLinkSection(this, schemas, result));

        return S_OK;
    }

    if (m_pPriFileManager != nullptr)
    {
        int globalFileIndex;
        RETURN_IF_FAILED(m_pFileResolver->GetGlobalIndex(fileIndex, &globalFileIndex));

        RETURN_IF_FAILED(m_pPriFileManager->GetResourceLinkSection(schemas, globalFileIndex, sectionIndex, result));
    }
    else
    {
        return E_INVALIDARG;
    }

    return S_OK;
}

HRESULT MrmFile::GetFileDefaultEnvironment(
    _In_ int fileIndex,
    _Inout_opt_ StringResult* fileEnvironmentName,
    _Inout_opt_ EnvironmentVersionInfo* fileEnvironmentVersion) const
{
    if (fileIndex == 0)
    {
        const BaseFile* basefile;
        RETURN_IF_FAILED(GetBaseFile(&basefile));

        BaseFile::SectionIndex environmentSectionIndex = basefile->GetFirstSectionIndex(gEnvironmentMappingSectionType);
        const EnvironmentMapping* mappingSection = nullptr;

        if (environmentSectionIndex != BaseFile::SectionIndexNone)
        {
            RETURN_IF_FAILED(GetEnvironmentMappingSection(0, environmentSectionIndex, &mappingSection));
            RETURN_IF_FAILED(mappingSection->GetEnvironmentInfo(fileEnvironmentName, fileEnvironmentVersion));
        }
        else
        {
            RETURN_IF_FAILED(GetProfile()->GetDefaultEnvironmentForFileMagic(
                m_pBaseFile->GetFileHeader()->magic, fileEnvironmentName, fileEnvironmentVersion));
        }

        return S_OK;
    }

    if (m_pPriFileManager != nullptr)
    {
        int globalFileIndex;
        RETURN_IF_FAILED(m_pFileResolver->GetGlobalIndex(fileIndex, &globalFileIndex));

        RETURN_IF_FAILED(m_pPriFileManager->GetFileDefaultEnvironment(globalFileIndex, fileEnvironmentName, fileEnvironmentVersion));
    }
    else
    {
        return E_INVALIDARG;
    }

    return S_OK;
}

HRESULT MrmFile::GetDefaultQualifierMapping(_In_ int fileIndex, _Out_ const RemapAtomPool** result) const
{
    *result = nullptr;

    if (fileIndex == 0)
    {
        const RemapAtomPool* existingMapping = nullptr;
        StringResult name;

        AutoDeletePtr<EnvironmentVersionInfo> version;
        RETURN_IF_FAILED(EnvironmentVersionInfo::CreateEmpty(&version));

        const BaseFile* basefile;
        RETURN_IF_FAILED(GetBaseFile(&basefile));

        BaseFile::SectionIndex environmentSectionIndex = basefile->GetFirstSectionIndex(gEnvironmentMappingSectionType);
        const EnvironmentMapping* mappingSection = nullptr;

        if (environmentSectionIndex != BaseFile::SectionIndexNone)
        {
            RETURN_IF_FAILED(GetEnvironmentMappingSection(0, environmentSectionIndex, &mappingSection));
            RETURN_IF_FAILED(mappingSection->GetEnvironmentInfo(&name, version));
        }
        else
        {
            RETURN_IF_FAILED(GetProfile()->GetDefaultEnvironmentForFileMagic(m_pBaseFile->GetFileHeader()->magic, &name, version));
        }

        if (!GetUnifiedEnvironment()->EnvironmentIsCompatible(name.GetRef(), version, &existingMapping))
        {
            int numQualifiers;
            const PCWSTR* qualifierNames;
            const Atom::SmallIndex* qualifierMappings;

            if (mappingSection != nullptr)
            {
                RETURN_IF_FAILED(mappingSection->GetQualifierInfo(&numQualifiers, &qualifierNames, &qualifierMappings));
            }
            else
            {
                RETURN_IF_FAILED(GetProfile()->GetQualifierInfoForEnvironment(
                    name.GetRef(),
                    version,
                    GetUnifiedEnvironment()->GetDefaultEnvironment(),
                    &numQualifiers,
                    &qualifierNames,
                    &qualifierMappings));
            }

            RETURN_IF_FAILED(GetUnifiedEnvironment()->AddCompatibleEnvironment(
                name.GetRef(), version, numQualifiers, qualifierNames, qualifierMappings, &existingMapping));
        }

        *result = existingMapping;

        return S_OK;
    }

    if (m_pPriFileManager != nullptr)
    {
        int globalFileIndex;
        RETURN_IF_FAILED(m_pFileResolver->GetGlobalIndex(fileIndex, &globalFileIndex));

        RETURN_IF_FAILED(m_pPriFileManager->GetDefaultQualifierMapping(globalFileIndex, result));
    }
    else
    {
        return E_INVALIDARG;
    }

    return S_OK;
}

HRESULT MrmFile::ResolveFileFileList(_In_ const FileFileList* pFileFileList)
{
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pFileResolver);

    RETURN_IF_FAILED(m_pFileResolver->AddReferencedFileInFileList(pFileFileList));

    return S_OK;
}

HRESULT MrmFile::GetAbsoluteFolderPath(_In_ int fileIndex, _Inout_ StringResult* pStringResult) const
{
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pFileResolver);

    int globalFileIndex;
    if (fileIndex == 0)
    {
        // Every merged file has 0 file index and if there is more than 1 merged filles,
        // same 0 file index cannot be indexed to multiple files (global index). so it copied
        // 0 file index's folder path and use it instead of getting from global index.
        if (m_strRootFolder.GetRef() != nullptr)
        {
            return pStringResult->SetCopy(m_strRootFolder.GetRef());
        }
        else
        {
            globalFileIndex = 0;
        }
    }
    else
    {
        RETURN_IF_FAILED(m_pFileResolver->GetGlobalIndex(fileIndex, &globalFileIndex));
    }

    RETURN_IF_FAILED(m_pPriFileManager->GetAbsoluteFolderPath(globalFileIndex, pStringResult));

    return S_OK;
}

HRESULT MrmFile::GetFilePath(_In_ int fileIndex, _Inout_ StringResult* pStringResult) const
{
    RETURN_HR_IF_NULL(E_DEF_NOT_READY, m_pFileResolver);

    int globalFileIndex;
    if (fileIndex == 0)
    {
        // The main pacakge has 0 file index, and its global index also 0.
        // However, framework package has 0 fileIndex as well, but their global index isn't 0 so MrmFile
        // store the filepath for framework package
        if (m_strFilePath.GetRef() != nullptr)
        {
            return pStringResult->SetCopy(m_strFilePath.GetRef());
        }
        else
        {
            globalFileIndex = 0;
        }
    }
    else
    {
        RETURN_IF_FAILED(m_pFileResolver->GetGlobalIndex(fileIndex, &globalFileIndex));
    }

    RETURN_IF_FAILED(m_pPriFileManager->GetFilePath(globalFileIndex, pStringResult));

    return S_OK;
}

int MrmFile::GetNumFiles() const { return m_pPriFileManager->GetNumFiles(); }

} // namespace Microsoft::Resources
