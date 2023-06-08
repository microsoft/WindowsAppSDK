// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "StdAfx.h"
#include "Helpers.h"
#include "mrm/build/Base.h"

#include "mrm/readers/MrmReaders.h"
#include "mrm/build/MrmBuilders.h"

#include "TestPri.h"
#include "TestMap.h"

using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;

namespace UnitTests
{
class PriBuilderUnitTests : public WEX::TestClass<PriBuilderUnitTests>
{
public:
    TEST_CLASS(PriBuilderUnitTests);

    BEGIN_TEST_METHOD(SimpleBuilderReaderTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:PriBuilder.UnitTests.xml#SimpleBuildTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(DeduplicationTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:PriBuilder.UnitTests.xml#DeduplicationTests")
    END_TEST_METHOD();
};

void PriBuilderUnitTests::SimpleBuilderReaderTests()
{
    String tmp;

    TestHPri pri;
    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));

    Log::Comment(L"[ Setting up test PRI ]");
    if (FAILED(pri.InitFromTestVars(L"", NULL, pProfile, NULL)))
    {
        Log::Error(L"[ Couldn't init TestPri ]");
    }

    // Okay, we're ready to build.
    Log::Comment(L"[ Building test PRI ]");
    if (FAILED(pri.Build()))
    {
        Log::Error(L"[ Couldn't build test PRI ]");
        return;
    }

    // Now we have to read the PRI file back into something we can use...
    Log::Comment(L"[ Reading back test PRI ]");
    if (FAILED(pri.CreateReader(pProfile)))
    {
        Log::Error(L"Couldn't read back test PRI");
    }

    Log::Comment(L"[ Verifying test PRI ]");
    TestHPri::VerifyAgainstTestVars(pri.GetPriFile(), L"", pri.GetTestDI(), L"");
}

void PriBuilderUnitTests::DeduplicationTests()
{
    String tmp;
    int qualifierSetIndex;
    const void* actualDataValue1 = nullptr;
    const void* actualDataValue2 = nullptr;
    size_t actualDataValueSize1 = 0;
    size_t actualDataValueSize2 = 0;
    TestHPri pri;
    AutoDeletePtr<CoreProfile> profile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&profile));
    Microsoft::Resources::Build::DataItemOrchestrator* dataItemOrchestrator = nullptr;
    Microsoft::Resources::Build::OrchestratorDataReference* dataReference1 = nullptr;
    Microsoft::Resources::Build::OrchestratorDataReference* dataReference2 = nullptr;

    Log::Comment(L"[ Setting up test PRI ]");
    if (FAILED(pri.InitFromTestVars(L"", NULL, profile, NULL)))
    {
        Log::Error(L"[ Couldn't init TestPri ]");
    }

    Log::Comment(L"[ buid qualifier set ]");
    DecisionInfoBuilder* pDecisions = pri.GetPriSectionBuilder()->GetDecisionInfoBuilder();
    AutoDeletePtr<DecisionInfoQualifierSetBuilder> qualifierSetBuilder;
    VERIFY_SUCCEEDED(DecisionInfoQualifierSetBuilder::CreateInstance(pDecisions, &qualifierSetBuilder));
    if (!qualifierSetBuilder)
    {
        Log::Error(L"[ Couldn't create QualifierSetBuilder ]");
        return;
    }

    // Make a QualifierSet to use for our tests
    Log::Comment(L"[  Make a QualifierSet ]");
    qualifierSetBuilder->Reset();
    VERIFY_SUCCEEDED(qualifierSetBuilder->AddQualifier(L"Language", L"en-US", 0.0));

    // 1.) Add two InstanceReference with duplicate string value.
    // Expected result: 1) The addresses of the two data references returned should be different
    //                  2) The actual values are the same
    //                  3) the indice of the inner reference are the same.
    // Actual result:   VERIFY PASS
    Log::Comment(L"[ Deduplication: 1 - Add two strings with the same values ]");
    dataItemOrchestrator = pri.GetPriSectionBuilder()->GetDataItemOrchestrator();

    VERIFY_SUCCEEDED(dataItemOrchestrator->AddStringAndCreateInstanceReference(
        L"Value1", qualifierSetBuilder, (IBuildInstanceReference**)&dataReference1, &qualifierSetIndex));

    VERIFY_SUCCEEDED(dataItemOrchestrator->AddStringAndCreateInstanceReference(
        L"Value1", qualifierSetBuilder, (IBuildInstanceReference**)&dataReference2, &qualifierSetIndex));

    actualDataValue1 = dataReference1->GetActualValue();
    actualDataValue2 = dataReference2->GetActualValue();
    actualDataValueSize1 = dataReference1->GetActualValueSize();
    actualDataValueSize2 = dataReference2->GetActualValueSize();

    Log::Comment(L"[ DeduplicationTests 1 : Verify the datareferences]");
    VERIFY(dataReference1 != dataReference2);

    Log::Comment(L"[ DeduplicationTests 1 : Verify the actual values]");
    VERIFY((actualDataValueSize1 == actualDataValueSize2) && (memcmp(actualDataValue1, actualDataValue2, actualDataValueSize1) == 0));

    Log::Comment(L"[ DeduplicationTests 1 : Verify the inner reference index ]");
    VERIFY(dataReference1->GetInnerReference().index == dataReference2->GetInnerReference().index);

    // 2.) Add two InstanceReference with different string value.
    // Expected result: 1) The addresses of the two data references returned should be different
    //                  2) The actual values are the same
    //                  3) the indice of the inner reference are different.
    // Actual result:   VERIFY PASS
    Log::Comment(L"[ Deduplication: 2) : Add two strings with the different value ]");
    dataItemOrchestrator = pri.GetPriSectionBuilder()->GetDataItemOrchestrator();

    VERIFY_SUCCEEDED(dataItemOrchestrator->AddStringAndCreateInstanceReference(
        L"Value1", qualifierSetBuilder, (IBuildInstanceReference**)&dataReference1, &qualifierSetIndex));

    VERIFY_SUCCEEDED(dataItemOrchestrator->AddStringAndCreateInstanceReference(
        L"Value2", qualifierSetBuilder, (IBuildInstanceReference**)&dataReference2, &qualifierSetIndex));

    actualDataValue1 = dataReference1->GetActualValue();
    actualDataValue2 = dataReference2->GetActualValue();
    actualDataValueSize1 = dataReference1->GetActualValueSize();
    actualDataValueSize2 = dataReference2->GetActualValueSize();

    Log::Comment(L"[ DeduplicationTests 2) : Verify the datareferences]");
    VERIFY(dataReference1 != dataReference2);

    Log::Comment(L"[ DeduplicationTests 2) : Verify the actual values]");
    VERIFY((actualDataValueSize1 == actualDataValueSize2) && (memcmp(actualDataValue1, actualDataValue2, actualDataValueSize1) != 0));

    Log::Comment(L"[ DeduplicationTests 2) : Verify the inner reference index ]");
    VERIFY(dataReference1->GetInnerReference().index != dataReference2->GetInnerReference().index);

    // 3.) Add two InstanceReference with different embedded data.
    // Expected result: 1) The addresses of the two data references returned should be different
    //                  2) The actual values are the same
    //                  3) the indice of the inner reference are the same.
    // Actual result:   VERIFY PASS
    size_t blobSize;
    BlobResult embeddedData;
    PCWSTR const seedString = L"This is an embedded data blob.";
    embeddedData.SetRef(seedString, (wcslen(seedString) + 1) * sizeof(WCHAR));
    auto blob = embeddedData.GetRef(&blobSize);
    Log::Comment(L"[ Deduplication: 3 - Add two data items with the same value ]");
    dataItemOrchestrator = pri.GetPriSectionBuilder()->GetDataItemOrchestrator();

    VERIFY_SUCCEEDED(dataItemOrchestrator->AddDataAndCreateInstanceReference(
        static_cast<const BYTE*>(blob),
        static_cast<UINT>(blobSize),
        qualifierSetBuilder,
        (IBuildInstanceReference**)&dataReference1,
        &qualifierSetIndex));

    VERIFY_SUCCEEDED(dataItemOrchestrator->AddDataAndCreateInstanceReference(
        static_cast<const BYTE*>(blob),
        static_cast<UINT>(blobSize),
        qualifierSetBuilder,
        (IBuildInstanceReference**)&dataReference2,
        &qualifierSetIndex));
    actualDataValue1 = dataReference1->GetActualValue();
    actualDataValue2 = dataReference2->GetActualValue();
    actualDataValueSize1 = dataReference1->GetActualValueSize();
    actualDataValueSize2 = dataReference2->GetActualValueSize();

    Log::Comment(L"[ DeduplicationTests 3 : Verify the datareferences]");
    VERIFY(dataReference1 != dataReference2);

    Log::Comment(L"[ DeduplicationTests 3 : Verify the actual values]");
    VERIFY((actualDataValueSize1 == actualDataValueSize2) && (memcmp(actualDataValue1, actualDataValue2, actualDataValueSize1) == 0));

    VERIFY(dataReference1->GetInnerReference().index == dataReference2->GetInnerReference().index);

    // 4.) Add two InstanceReference with different embedded data.
    // Expected result: 1) The addresses of the two data references returned should be different
    //                  2) The actual values are different
    //                  3) the indice of the inner reference are different.
    // Actual result:   VERIFY PASS
    size_t blobSize1;
    size_t blobSize2;
    BlobResult embeddedData1;
    BlobResult embeddedData2;
    PCWSTR const seedString1 = L"First data : This is an embedded data blob.";
    PCWSTR const seedString2 = L"Second data : This is another embedded data blob.";
    embeddedData1.SetRef(seedString1, (wcslen(seedString1) + 1) * sizeof(WCHAR));
    embeddedData2.SetRef(seedString2, (wcslen(seedString2) + 1) * sizeof(WCHAR));
    auto blob1 = embeddedData1.GetRef(&blobSize1);
    auto blob2 = embeddedData2.GetRef(&blobSize2);
    Log::Comment(L"[ Deduplication: 4 - Add two data items with the different embedded data ]");
    dataItemOrchestrator = pri.GetPriSectionBuilder()->GetDataItemOrchestrator();

    VERIFY_SUCCEEDED(dataItemOrchestrator->AddDataAndCreateInstanceReference(
        static_cast<const BYTE*>(blob1),
        static_cast<UINT>(blobSize1),
        qualifierSetBuilder,
        (IBuildInstanceReference**)&dataReference1,
        &qualifierSetIndex));

    VERIFY_SUCCEEDED(dataItemOrchestrator->AddDataAndCreateInstanceReference(
        static_cast<const BYTE*>(blob2),
        static_cast<UINT>(blobSize2),
        qualifierSetBuilder,
        (IBuildInstanceReference**)&dataReference2,
        &qualifierSetIndex));
    actualDataValue1 = dataReference1->GetActualValue();
    actualDataValue2 = dataReference2->GetActualValue();
    actualDataValueSize1 = dataReference1->GetActualValueSize();
    actualDataValueSize2 = dataReference2->GetActualValueSize();

    Log::Comment(L"[ DeduplicationTests 4 : Verify the datareferences]");
    VERIFY(dataReference1 != dataReference2);

    Log::Comment(L"[ DeduplicationTests 4 : Verify the actual values]");
    VERIFY((actualDataValueSize1 != actualDataValueSize2) && (memcmp(actualDataValue1, actualDataValue2, actualDataValueSize1) != 0));

    Log::Comment(L"[ DeduplicationTests 4 : Verify the actual values]");
    VERIFY(dataReference1->GetInnerReference().index != dataReference2->GetInnerReference().index);

    // 5.) Add two InstanceReference with same strings that could be optimized.
    // Expected result: 1) The addresses of the two data references returned should be different
    //                  2) The actual values are the same
    //                  3) the indice of the inner reference are the same.
    //                  4) The lenth of the optimized string should be exactly twice as the original length
    // Actual result:   VERIFY PASS
    PCWSTR const utf16String = L"This is a UTF16 string that can be optimized to UTF8";

    MrmEnvironment::ResourceValueType oringinalType = MrmEnvironment::ResourceValueType::ResourceValueType_Utf16String;
    MrmEnvironment::ResourceValueType optimalType = oringinalType;

    Log::Comment(L"[ Deduplication: 5 - Add two same strings and optimize them, then get the data references ]");
    dataItemOrchestrator = pri.GetPriSectionBuilder()->GetDataItemOrchestrator();

    VERIFY_SUCCEEDED(dataItemOrchestrator->AddOptimizedStringAndCreateInstanceReference(
        oringinalType, utf16String, qualifierSetBuilder, (IBuildInstanceReference**)&dataReference1, &qualifierSetIndex, &optimalType));

    VERIFY_SUCCEEDED(dataItemOrchestrator->AddOptimizedStringAndCreateInstanceReference(
        oringinalType, utf16String, qualifierSetBuilder, (IBuildInstanceReference**)&dataReference2, &qualifierSetIndex, &optimalType));

    actualDataValue1 = dataReference1->GetActualValue();
    actualDataValue2 = dataReference2->GetActualValue();
    actualDataValueSize1 = dataReference1->GetActualValueSize();
    actualDataValueSize2 = dataReference2->GetActualValueSize();

    Log::Comment(L"[ DeduplicationTests 5 : Verify the datareferences, should not be the same]");
    VERIFY(dataReference1 != dataReference2);

    Log::Comment(L"[ DeduplicationTests 5 : Verify the actual values, should be the same]");
    VERIFY((actualDataValueSize1 == actualDataValueSize2) && (memcmp(actualDataValue1, actualDataValue2, actualDataValueSize1) == 0));

    Log::Comment(L"[ DeduplicationTests 5 : Verify the actual values ,should be the same ]");
    VERIFY(dataReference1->GetInnerReference().index == dataReference2->GetInnerReference().index);

    Log::Comment(L"[ DeduplicationTests 5 : Verify the value size, should be exactly twice as the original string length ]");
    VERIFY(
        (actualDataValueSize1 * 2 == ((wcslen(utf16String) + 1) * sizeof(wchar_t))) &&
        (actualDataValueSize2 * 2 == ((wcslen(utf16String) + 1) * sizeof(wchar_t))));

    // 6.) Add two InstanceReference with different strings that could be optimized.
    // Expected result: 1) The addresses of the two data references returned should be different
    //                  2) The actual values are different
    //                  3) The indice of the inner reference are different.
    //                  4) The lenth of the optimized string should be exactly twice as the original length
    // Actual result:   VERIFY PASS
    PCWSTR const utf16String1 = L"First data : This is a string.";
    PCWSTR const utf16String2 = L"Second data : This is a UTF16 string. 2nd string.";

    Log::Comment(L"[ Deduplication: 6 - Add two different strings and optimize them, then get the data references ]");
    dataItemOrchestrator = pri.GetPriSectionBuilder()->GetDataItemOrchestrator();

    VERIFY_SUCCEEDED(dataItemOrchestrator->AddOptimizedStringAndCreateInstanceReference(
        oringinalType, utf16String1, qualifierSetBuilder, (IBuildInstanceReference**)&dataReference1, &qualifierSetIndex, &optimalType));

    VERIFY_SUCCEEDED(dataItemOrchestrator->AddOptimizedStringAndCreateInstanceReference(
        oringinalType, utf16String2, qualifierSetBuilder, (IBuildInstanceReference**)&dataReference2, &qualifierSetIndex, &optimalType));

    actualDataValue1 = dataReference1->GetActualValue();
    actualDataValue2 = dataReference2->GetActualValue();
    actualDataValueSize1 = dataReference1->GetActualValueSize();
    actualDataValueSize2 = dataReference2->GetActualValueSize();

    Log::Comment(L"[ DeduplicationTests 6 : Verify the datareferences, should not be the same]");
    VERIFY(dataReference1 != dataReference2);

    Log::Comment(L"[ DeduplicationTests 6 : Verify the actual values, should not be the same]");
    VERIFY((actualDataValueSize1 != actualDataValueSize2) && (memcmp(actualDataValue1, actualDataValue2, actualDataValueSize1) != 0));

    Log::Comment(L"[ DeduplicationTests 6 : Verify the actual values ,should not be the same ]");
    VERIFY(dataReference1->GetInnerReference().index != dataReference2->GetInnerReference().index);

    Log::Comment(L"[ DeduplicationTests 6 : Verify the value size, should be exactly twice as the original string length ]");
    VERIFY(
        (actualDataValueSize1 * 2 == ((wcslen(utf16String1) + 1) * sizeof(wchar_t))) &&
        (actualDataValueSize2 * 2 == ((wcslen(utf16String2) + 1) * sizeof(wchar_t))));
}

} // namespace UnitTests