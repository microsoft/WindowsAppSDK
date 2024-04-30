// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "mrm/common/file/FileBase.h"

namespace Microsoft::Resources::Build
{

enum BuildPhase
{
    Initializing = 0,
    Building = 1,
    Finalizing = 2,
    Generating = 3,
    Done = 4
};

class ISectionBuilder : public DefObject
{
public:
    virtual ~ISectionBuilder() {}

    /*!
            * Validates the object
            */
    virtual bool IsValid() const = 0;

    /*!
             * Finalizes the object in preparation for generating.  Once finalized,
             * objects are read-only and any generated indices must be stable.
             *
             * \return HRESULT
             * Returns S_OK on success, failure if an error occurs.
             */
    virtual HRESULT Finalize() = 0;

    /*!
             * Gets the maximum size in bytes for the serailized form of the object.
             */
    virtual UINT32 GetMaxSizeInBytes() const = 0;

    /*!
             * Builds the in-file structure into the provided buffer.
             *
             * \param pBuffer
             * The destination buffer into which the object will be generated.
             *
             * \param cbBuffer
             * Size of the destination buffer, in bytes.
             *
             * \param cbWrittenOut
             * If pcbWrittenOut is non-NULL, the Build method uses it to return
             * the number of bytes actually written.
             *
             * \return HRESULT
             * Returns S_OK on success, failure if an error occurs.
             */
    virtual HRESULT Build(__out_bcount(cbBuffer) VOID* pBuffer, UINT32 cbBuffer, __out_opt UINT32* pcbWrittenOut) const = 0;

    // Gets the section type id for this object. This will be included in the section header and TOC entry.
    virtual DEFFILE_SECTION_TYPEID GetSectionType() const = 0;

    // Gets the global flags for this object. This will be included in the TOC entry.
    virtual UINT16 GetFlags() const = 0;

    //  Gets the section flags for this object.  This will be included in the TOC entry.
    virtual UINT16 GetSectionFlags() const = 0;

    // Gets the section qualifier for this object. This will be included in the section header and TOC entry.
    virtual UINT32 GetSectionQualifier() const = 0;
    virtual void SetSectionIndex(BaseFile::SectionIndex sectionIndex) = 0;
    virtual BaseFile::SectionIndex GetSectionIndex() const = 0;
};

// Build a UID-formatted file.
class FileBuilder : public DefObject
{
public:
    typedef struct _SectionInfo
    {
        ISectionBuilder* m_pSectionBuilder;
        UINT32 m_maxDataSize;

        DEFFILE_TOC_ENTRY* m_pTocEntry;

        DEFFILE_SECTION_HEADER* m_pHeader;
        DEFFILE_SECTION_TRAILER* m_pTrailer;
        BYTE* m_pSectionData;
        UINT32 m_cbSectionData;
    } SectionInfo;

private:
    BuildPhase m_phase;
    DEFFILE_MAGIC m_magic;

    BaseFile::SectionCount m_sizeSections;
    BaseFile::SectionCount m_nSections;
    SectionInfo* m_pSections;

    BaseFile::SectionIndex m_descriptorIndex;

    VOID* m_pData;
    UINT32 m_cbData;

    DEFFILE_HEADER* m_pHeader;
    DEFFILE_TOC_ENTRY* m_pToc;
    BYTE* m_pSectionData;
    UINT32 m_cbSectionData;
    UINT32 m_nSectionDataUsed;

protected:
    FileBuilder(DEFFILE_MAGIC magic);

    SectionInfo* GetSections() { return m_pSections; }

    const VOID* GetData() { return m_pData; }

    UINT32 GetDataSize() { return m_cbData; }

public:
    static HRESULT CreateInstance(__in DEFFILE_MAGIC magic, __in BaseFile::SectionCount sizeSections, _Outptr_ FileBuilder** result);

    virtual ~FileBuilder();

    HRESULT AddSection(__in ISectionBuilder* pSection);

    BaseFile::SectionIndex GetDescriptorIndex() { return m_descriptorIndex; }

    HRESULT SetDescriptorIndex(__in BaseFile::SectionIndex index);

    HRESULT GetSectionData(__in INT32 sectionIndex, _Out_ const BYTE** data, _Out_ UINT32* pcbSectionData);

    HRESULT GenerateFileContents(__deref_out void** ppBufferOut, __out_opt UINT32* pBufferLenOut);

    HRESULT GenerateFileContents(__out_bcount(cbBufferOut) VOID* pBufferOut, UINT32 cbBufferOut, __out_opt UINT32* pcbWrittenSize);

    HRESULT WriteToFile(__in PCWSTR fileName);

    static FileBuilder* FromFile(__in PCWSTR fileName);

    UINT32 GetNumSections() { return m_nSections; }

    BuildPhase GetPhase() const { return m_phase; }

    bool SetPhase(BuildPhase phase)
    {
        if (m_phase > phase)
        {
            //can't go back to a previous phase
            return false;
        }
        m_phase = phase;
        return true;
    }

    HRESULT CheckSetPhase(__in BuildPhase phase)
    {
        if ((m_phase == phase) || SetPhase(phase))
        {
            return S_OK;
        }
        return HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION);
    }

    HRESULT CheckPhase(__in BuildPhase phase) const
    {
        if (m_phase != phase)
        {
            return HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION);
        }
        return S_OK;
    }

    DEFFILE_MAGIC GetMagic() { return m_magic; }

    virtual HRESULT GetMaxSize(_Out_ UINT32* size);

    virtual HRESULT FinalizeAllSections();

private:
    virtual HRESULT StartGenerating(__out_bcount(cbDataOut) VOID* pDataOut, __in UINT32 cbDataOut);

    virtual HRESULT StartSection(__in BaseFile::SectionIndex sectionIndex, _Out_ SectionInfo** result);

    virtual HRESULT FinishSection(BaseFile::SectionIndex sectionIndex, UINT32 cbGenerated);

    virtual HRESULT BuildAllSections();

    virtual HRESULT FinishGenerating();

    virtual HRESULT GenerateFileContentsInternal();
};

#define DefBuild_PhaseMismatch(GOT, WANT, STATUS) Def_Check0(((GOT) != (WANT)), E_DEFFILE_BUILD_BAD_PHASE, STATUS)
#define DefBuild_PhaseIsBefore(GOT, WANT, STATUS) Def_Check0(((GOT) < (WANT)), E_DEFFILE_BUILD_BAD_PHASE, STATUS)
#define DefBuild_PhaseIsAfter(GOT, WANT, STATUS) Def_Check0(((GOT) > (WANT)), E_DEFFILE_BUILD_BAD_PHASE, STATUS)

#define DefBuild_CheckElementsOverrun(COUNT, CURRENT, END, STATUS) \
    Def_Check0(reinterpret_cast<BYTE*>(&(CURRENT)[COUNT]) > reinterpret_cast<BYTE*>(END), E_DEFFILE_BUILD_SECTION_DATA_TOO_LARGE, STATUS)
#define DefBuild_CheckElementOverruns(CURRENT, END, STATUS) DefBuild_CheckElementsOverrun(1, CURRENT, END, STATUS)

} // namespace Microsoft::Resources::Build
