// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <windows.h>
#include <WexTestClass.h>

#include "Helpers.h"

#include "mrm/build/Base.h"
#include "mrm/readers/SectionReaders.h"
#include "mrm/build/SectionBuilders.h"
#include "TestSections.h"

using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;

namespace UnitTests
{

/*!
     * DataItemsSection Unit Tests
     */
class DataItemsSectionUnitTests : public WEX::TestClass<DataItemsSectionUnitTests>
{
    TEST_CLASS(DataItemsSectionUnitTests);

    TEST_METHOD(New_ParamChecks);

    BEGIN_TEST_METHOD(SimpleBuilderReaderTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:DataItemsSection.UnitTests.xml#SimpleTests")
    END_TEST_METHOD()
};

void DataItemsSectionUnitTests::New_ParamChecks(void)
{
    BYTE buf[1000];
    FileDataItemsSection* pSection;

    SecureZeroMemory(buf, sizeof(buf));

#pragma prefast(suppress : 6309, "Testing illegal NULL parameter")
    HRESULT hr = FileDataItemsSection::CreateInstance(NULL, 0, &pSection);
    VERIFY(pSection == NULL);
    VERIFY_ARE_EQUAL(hr, E_INVALIDARG);
    delete pSection;

#pragma prefast(suppress : 6309, "Testing illegal NULL parameter")
    hr = FileDataItemsSection::CreateInstance((const void*)NULL, (UINT32)sizeof(buf), &pSection);
    VERIFY(pSection == NULL);
    VERIFY_ARE_EQUAL(hr, E_INVALIDARG);
    delete pSection;

    hr = FileDataItemsSection::CreateInstance(buf, 0, &pSection);
    VERIFY(pSection == NULL);
    VERIFY_ARE_EQUAL(hr, E_INVALIDARG);
    delete pSection;
}

void DataItemsSectionUnitTests::SimpleBuilderReaderTests(void)
{
    String tmp;
    PCWSTR pVarPrefix = L"Item";
    TestDataItemsSection testSection;

    VERIFY(testSection.InitFromTestVars(NULL, pVarPrefix, false));
    Log::Comment(tmp.Format(L"[ initialized %d blobs ]", testSection.GetNumItems()));

    VERIFY_SUCCEEDED(testSection.Build());
    VERIFY_SUCCEEDED(testSection.CreateReader());

    FileDataItemsSection* pSection = testSection.GetDataItemsSection();
    VERIFY(pSection != NULL);
    VERIFY(pSection->GetNumItems() == testSection.GetNumItems());

    int expected;
    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%s_ExpectedSmallItemCount", pVarPrefix), expected)))
    {
        VERIFY(testSection.GetNumSmallItemsBuilt() == expected);
    }
    else
    {
        Log::Comment(tmp.Format(L"[ no expected small item count for %s ]", pVarPrefix));
    }

    if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%s_ExpectedLargeItemCount", pVarPrefix), expected)))
    {
        VERIFY(testSection.GetNumLargeItemsBuilt() == expected);
    }
    else
    {
        Log::Comment(tmp.Format(L"[ no expected large item count for %s ]", pVarPrefix));
    }

    for (int i = 0; i < testSection.GetNumItems(); i++)
    {
        TestBlob* pBlob = testSection.GetBlob(i);
        DataItemsSectionBuilder::BuiltItemReference builtAs;

        VERIFY(testSection.GetBuiltItem(i, &builtAs));

        UINT32 cbBlobData = 0;
        const BYTE* pBlobData;
        VERIFY_SUCCEEDED(pSection->GetItemDataRef(builtAs.itemIndex, &pBlobData, &cbBlobData));

        VERIFY(pBlob->CheckCopy(pBlobData, cbBlobData, true));

        String expectedClass;
        if (SUCCEEDED(TestData::TryGetValue(tmp.Format(L"%s%d_ExpectedClass", pVarPrefix, i), expectedClass)))
        {
            if (DefString_ICompare((PCWSTR)expectedClass, L"small") == Def_Equal)
            {
                VERIFY(builtAs.itemIndex < testSection.GetNumSmallItemsBuilt());
            }
            else if (DefString_ICompare((PCWSTR)expectedClass, L"large") == Def_Equal)
            {
                VERIFY(builtAs.itemIndex >= testSection.GetNumSmallItemsBuilt());
            }
            else
            {
                Log::Warning(tmp.Format(L"Unknown class \"%s\" for %s%d", (PCWSTR)expectedClass, pVarPrefix, i));
            }
        }
    }
}

}; // namespace UnitTests
