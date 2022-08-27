// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "mrm/readers/SectionReaders.h"
#include "mrm/build/SectionBuilders.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;
using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTests
{

class TestSection
{
public:
    TestSection();
    virtual ~TestSection();

    ISectionBuilder* GetSectionBuilder() const { return m_pSectionBuilder; }
    BaseFile::SectionIndex GetBuilderSectionIndex() const { return m_pSectionBuilder->GetSectionIndex(); }

    IFileSection* GetSection() const { return m_pSection; }

    virtual HRESULT Build();
    virtual HRESULT CreateReader() = 0;

    virtual PCWSTR GetTestSectionType() const = 0;

protected:
    virtual void Release() { BaseRelease(); }
    void BaseRelease();

    bool BaseInit(__in_opt FileBuilder* pFileBuilder, __in_opt ISectionBuilder* pSectionBuilder, __in bool addToFile);

    BuildHelper m_build;
    FileBuilder* m_pFileBuilder;
    ISectionBuilder* m_pSectionBuilder;
    IFileSection* m_pSection;
};

class TestDataItemsSection : public TestSection
{
protected:
    int m_numDataItems;
    TestBlob** m_ppItemData;
    DataItemsSectionBuilder::PrebuildItemReference* m_pPrebuildItems;

public:
    TestDataItemsSection();

    // Creates a data section from test variables
    bool InitFromTestVars(__in_opt FileBuilder* pFileBuilder, __in PCWSTR pVarPrefix, __in bool addToFile);

    virtual ~TestDataItemsSection() { Release(); }

    virtual void Release();

    DataItemsSectionBuilder* GetDataItemsSectionBuilder() const { return static_cast<DataItemsSectionBuilder*>(m_pSectionBuilder); }
    FileDataItemsSection* GetDataItemsSection() const { return static_cast<FileDataItemsSection*>(m_pSection); }

    int GetNumItems() const { return m_numDataItems; }
    TestBlob* GetBlob(int index) const { return ((index >= 0) && (index < m_numDataItems) ? m_ppItemData[index] : NULL); }

    bool GetPrebuildItem(__in int index, __out DataItemsSectionBuilder::PrebuildItemReference* pRefOut) const
    {
        *pRefOut = m_pPrebuildItems[index];
        return true;
    }

    bool GetBuiltItem(__in int index, __out DataItemsSectionBuilder::BuiltItemReference* pRefOut) const
    {
        return SUCCEEDED(GetDataItemsSectionBuilder()->GetBuiltItemInfo(&m_pPrebuildItems[index], pRefOut));
    }

    int GetNumSmallItemsBuilt() const { return reinterpret_cast<const DEFFILE_DATAITEMS_HEADER*>(m_build.GetBuffer())->numSmallItems; }

    int GetNumLargeItemsBuilt() const { return reinterpret_cast<const DEFFILE_DATAITEMS_HEADER*>(m_build.GetBuffer())->numLargeItems; }

    static PCWSTR DataItemsSectionTypeName;

    virtual PCWSTR GetTestSectionType() const { return DataItemsSectionTypeName; }

    virtual HRESULT CreateReader();

    bool TryVerifyItems();

    static TestDataItemsSection* GetAs(__in TestSection* pTestSection)
    {
        if (pTestSection && (DefString_IEqual(pTestSection->GetTestSectionType(), DataItemsSectionTypeName)))
        {
            return static_cast<TestDataItemsSection*>(pTestSection);
        }
        return nullptr;
    }
};

} // namespace UnitTests
