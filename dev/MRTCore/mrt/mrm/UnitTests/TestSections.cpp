// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <windows.h>
#include <WexTestClass.h>
#include "mrm/build/Base.h"
#include "mrm/build/MrmBuilders.h"
#include "Helpers.h"
#include "TestSections.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;
using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTests
{

TestSection::TestSection() : m_pFileBuilder(NULL), m_pSectionBuilder(NULL), m_pSection(NULL) {}

bool TestSection::BaseInit(__in_opt FileBuilder* pFileBuilder, __in_opt ISectionBuilder* pSectionBuilder, __in bool addToFile)
{
    Release();

    m_pFileBuilder = pFileBuilder;
    m_pSectionBuilder = pSectionBuilder;

    if ((addToFile) && (FAILED(pFileBuilder->AddSection(pSectionBuilder))))
    {
        return false;
    }
    return true;
}

TestSection::~TestSection() { BaseRelease(); }

void TestSection::BaseRelease()
{
    delete m_pSectionBuilder;
    delete m_pSection;

    m_pFileBuilder = NULL;
    m_pSectionBuilder = NULL;
    m_pSection = NULL;
}

HRESULT
TestSection::Build() { return m_build.Build(m_pSectionBuilder); }

/*
     * TestDataItemsSection
     */

PCWSTR TestDataItemsSection::DataItemsSectionTypeName = L"DataItem";

TestDataItemsSection::TestDataItemsSection() : TestSection(), m_numDataItems(0), m_ppItemData(NULL), m_pPrebuildItems(NULL) {}

bool TestDataItemsSection::InitFromTestVars(__in_opt FileBuilder* pFileBuilder, __in PCWSTR pVarPrefix, __in bool addToPri)
{
    Release();

    DataItemsSectionBuilder* pBuilder;
    if (FAILED(DataItemsSectionBuilder::CreateInstance(&pBuilder)) || (!BaseInit(pFileBuilder, pBuilder, addToPri)))
    {
        Log::Warning(L"Couldn't create or initialized DataItemsSectionBuilder");
        delete pBuilder;
        return false;
    }

    m_ppItemData = TestBlob::CreateBlobsFromTestVars(pVarPrefix, &m_numDataItems);
    if (m_ppItemData == NULL)
    {
        Log::Warning(L"Error creating blobs from test variables");
        return false;
    }
    m_pPrebuildItems = new DataItemsSectionBuilder::PrebuildItemReference[m_numDataItems];

    for (int i = 0; i < m_numDataItems; i++)
    {
        HRESULT hr;
        if (m_ppItemData[i]->GetIsString())
        {
            size_t cchBlob = m_ppItemData[i]->GetBlobSizeInBytes() / sizeof(WCHAR);
            hr = pBuilder->AddDataString(m_ppItemData[i]->GetString(), static_cast<int>(cchBlob), &m_pPrebuildItems[i]);
        }
        else
        {
            hr = pBuilder->AddDataItem(
                m_ppItemData[i]->GetBlob(),
                static_cast<UINT32>(m_ppItemData[i]->GetBlobSizeInBytes()),
                m_ppItemData[i]->GetDestinationAlignment(),
                &m_pPrebuildItems[i]);
        }
        if (FAILED(hr))
        {
            String tmp;
            Log::Warning(tmp.Format(L"Error adding item %d (0x%x)", i, hr));
            return false;
        }
    }
    return true;
}

void TestDataItemsSection::Release()
{
    BaseRelease();

    if (m_ppItemData != NULL)
    {
        for (int i = 0; i < m_numDataItems; i++)
        {
            delete m_ppItemData[i];
            m_ppItemData[i] = NULL;
        }
        Def_Free(m_ppItemData);
        m_ppItemData = NULL;
    }
    m_numDataItems = 0;

    delete[] m_pPrebuildItems;
    m_pPrebuildItems = NULL;
}

HRESULT
TestDataItemsSection::CreateReader()
{
    return FileDataItemsSection::CreateInstance(m_build.GetBuffer(), m_build.GetBufferSize(), (FileDataItemsSection**)&m_pSection);
}

bool TestDataItemsSection::TryVerifyItems() { return true; }

} // namespace UnitTests
