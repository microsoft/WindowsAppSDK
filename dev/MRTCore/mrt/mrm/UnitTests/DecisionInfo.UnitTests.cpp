// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "StdAfx.h"
#include "Helpers.h"
#include "mrm/build/Base.h"

#include "mrm/readers/MrmReaders.h"
#include "mrm/build/MrmBuilders.h"

#include "TestUtils.h"
#include "TestPri.h"
#include "TestQualifier.h"

using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;

namespace UnitTests
{
class DecisionInfoUnitTests : public WEX::TestClass<DecisionInfoUnitTests>
{
public:
    TEST_CLASS(DecisionInfoUnitTests);

    TEST_CLASS_SETUP(ClassSetup);
    TEST_CLASS_CLEANUP(ClassCleanup);

    TEST_METHOD_SETUP(MethodSetup);
    TEST_METHOD_CLEANUP(MethodCleanup);

    BEGIN_TEST_METHOD(SimpleBuilderTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:DecisionInfo.UnitTests.xml#SimpleBuilderTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(SimpleBuilderReaderTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:DecisionInfo.UnitTests.xml#SimpleBuilderTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(DecisionInfoMergeTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:DecisionInfo.UnitTests.xml#MergeTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(UnifiedDecisionInfoTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:DecisionInfo.UnitTests.xml#MergeTests")
    END_TEST_METHOD();
};

bool DecisionInfoUnitTests::ClassSetup() { return true; }

bool DecisionInfoUnitTests::ClassCleanup() { return true; }

bool DecisionInfoUnitTests::MethodSetup() { return true; }

bool DecisionInfoUnitTests::MethodCleanup() { return true; }

void DecisionInfoUnitTests::SimpleBuilderTests()
{
    TestDecisionInfo decisionInfo;

    // read test data
    if (FAILED(decisionInfo.InitDataFromTestVars(L"")))
    {
        Log::Error(L"[ Couldn't load test data ]");
        return;
    }

    // create builders
    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));
    AutoDeletePtr<AtomPoolGroup> pAtoms;
    VERIFY_SUCCEEDED(AtomPoolGroup::CreateInstance(&pAtoms));
    AutoDeletePtr<UnifiedEnvironment> pEnvironment;
    VERIFY_SUCCEEDED(UnifiedEnvironment::CreateInstance(pProfile, pAtoms, &pEnvironment));
    AutoDeletePtr<DecisionInfoBuilder> pBuilder;
    VERIFY_SUCCEEDED(DecisionInfoBuilder::CreateInstance(pEnvironment, &pBuilder));

    if (pBuilder == NULL)
    {
        Log::Error(L"[ Couldn't create builders ]");
        return;
    }

    // Add test data to builders
    // Although it is tempting to remove the '!' below to address the PREfast issue, doing that broke the build. 
    // OTOH, 2 instances of the same code pattern are also in OS.2020, therefore, we probably would want to have 
    // a "global" fix for all instances. Bug 50087117 has been filed for tracking the "global" fix.
#pragma warning(suppress: 6215) // C6215: Cast between semantically different integer types.
    if (FAILED(!decisionInfo.ApplyTestData(pBuilder)))
    {
        Log::Error(L"[ Error applying test data ]");
        return;
    }

    // verify results
    TestDecisionInfoValidator validate;
    if (FAILED(validate.InitDataFromTestVars(L"")))
    {
        Log::Error(L"[ Couldn't load test validation data ]");
        return;
    }

    validate.ValidateQualifiers(pBuilder, pEnvironment);
    validate.ValidateQualifierSets(pBuilder, pEnvironment);
    validate.ValidateDecisions(pBuilder, pEnvironment);
}

void DecisionInfoUnitTests::SimpleBuilderReaderTests()
{
    TestHPri pri;
    TestDecisionInfo decisionInfo;

    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));

    if (FAILED(pri.Init(pProfile)))
    {
        Log::Error(L"[ Couldn't set up test pri ]");
    }

    // read test data
    if (FAILED(decisionInfo.InitDataFromTestVars(L"")))
    {
        Log::Error(L"[ Couldn't load test data ]");
        return;
    }

    const UnifiedEnvironment* pEnvironment = pri.GetPriSectionBuilder()->GetEnvironment();
    AutoDeletePtr<DecisionInfoSectionBuilder> pBuilder;
    VERIFY_SUCCEEDED(DecisionInfoSectionBuilder::CreateInstance(pri.GetFileBuilder(), pEnvironment, &pBuilder));
    // create builders
    if (pBuilder == NULL)
    {
        Log::Error(L"[ Couldn't create builder ]");
        return;
    }

    // Add test data to builders
    if (FAILED(decisionInfo.ApplyTestData(pBuilder)))
    {
        Log::Error(L"[ Error applying test data ]");
        return;
    }

    BuildHelper build;

    VERIFY_SUCCEEDED(build.Build(pBuilder));

    AutoDeletePtr<DecisionInfoFileSection> pReader;
    VERIFY_SUCCEEDED(DecisionInfoFileSection::CreateInstance(build.GetBuffer(), build.GetWrittenSize(), nullptr, &pReader));
    VERIFY(pReader != NULL);

    // verify results
    TestDecisionInfoValidator validate;
    if (FAILED(validate.InitDataFromTestVars(L"")))
    {
        Log::Error(L"[ Couldn't load test validation data ]");
        return;
    }

    validate.ValidateQualifiers(pReader, pEnvironment);
    validate.ValidateQualifierSets(pReader, pEnvironment);
    validate.ValidateDecisions(pReader, pEnvironment);
}

void DecisionInfoUnitTests::DecisionInfoMergeTests()
{
    String tmp;

    TestDecisionInfo testDI;

    // read initial decision info
    if (FAILED(testDI.InitDataFromTestVars(L"")))
    {
        Log::Error(L"[ Couldn't load test data ]");
        return;
    }

    // create builders
    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));
    AutoDeletePtr<AtomPoolGroup> pAtoms;
    VERIFY_SUCCEEDED(AtomPoolGroup::CreateInstance(&pAtoms));
    AutoDeletePtr<UnifiedEnvironment> pEnvironment;
    VERIFY_SUCCEEDED(UnifiedEnvironment::CreateInstance(pProfile, pAtoms, &pEnvironment));
    AutoDeletePtr<DecisionInfoBuilder> pBuilder;
    VERIFY_SUCCEEDED(DecisionInfoBuilder::CreateInstance(pEnvironment, &pBuilder));

    if (pBuilder == NULL)
    {
        Log::Error(L"[ Couldn't create builders ]");
        return;
    }

    // Add test data to builders
    if (FAILED(testDI.ApplyTestData(pBuilder)))
    {
        Log::Error(L"[ Error applying test data ]");
        return;
    }

    int numToMerge = 0;
    if (FAILED(TestData::TryGetValue(L"NumToMerge", numToMerge)))
    {
        Log::Error(L"[ NumToMerge not specified ]");
        return;
    }

    for (int i = 0; i < numToMerge; i++)
    {
        String prefix = tmp.Format(L"Merge%d", i + 1);
        TestDecisionInfo mergeDI;

        if (FAILED(mergeDI.InitDataFromTestVars((PCWSTR)prefix)))
        {
            Log::Error(tmp.Format(L"[ Couldn't load test data \"%s\" ]", (PCWSTR)prefix));
            return;
        }

        AutoDeletePtr<DecisionInfoBuilder> pMergeBuilder;
        VERIFY_SUCCEEDED(DecisionInfoBuilder::CreateInstance(pEnvironment, &pMergeBuilder));

        if (FAILED(mergeDI.ApplyTestData(pMergeBuilder)))
        {
            Log::Error(tmp.Format(L"[ Error applying test data \"%s\" ]", (PCWSTR)prefix));
            return;
        }

        AutoDeletePtr<RemapUInt16> pQualifierMap;
        VERIFY_SUCCEEDED(RemapUInt16::CreateInstance(pMergeBuilder->GetNumQualifiers(), &pQualifierMap));
        AutoDeletePtr<RemapUInt16> pQualifierSetMap;
        VERIFY_SUCCEEDED(RemapUInt16::CreateInstance(pMergeBuilder->GetNumQualifierSets(), &pQualifierSetMap));
        AutoDeletePtr<RemapUInt16> pDecisionMap;
        VERIFY_SUCCEEDED(RemapUInt16::CreateInstance(pMergeBuilder->GetNumDecisions(), &pDecisionMap));

        VERIFY_SUCCEEDED(pBuilder->Merge(pMergeBuilder, pQualifierMap, pQualifierSetMap, pDecisionMap));

        TestUtils::TryVerifyRemap(tmp.Format(L"%sExpectedQualifiersMap", (PCWSTR)prefix), pQualifierMap);
        TestUtils::TryVerifyRemap(tmp.Format(L"%sExpectedQualifierSetsMap", (PCWSTR)prefix), pQualifierSetMap);
        TestUtils::TryVerifyRemap(tmp.Format(L"%sExpectedDecisionsMap", (PCWSTR)prefix), pDecisionMap);
    }

    // verify results
    TestDecisionInfoValidator validate;
    if (FAILED(validate.InitDataFromTestVars(L"Merged")))
    {
        Log::Error(L"[ Couldn't load test validation data ]");
        return;
    }

    validate.ValidateQualifiers(pBuilder, pEnvironment);
    validate.ValidateQualifierSets(pBuilder, pEnvironment);
    validate.ValidateDecisions(pBuilder, pEnvironment);
}

void DecisionInfoUnitTests::UnifiedDecisionInfoTests()
{
    String tmp;

    TestHPri pri;
    TestDecisionInfo testDI;

    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));

    if (FAILED(pri.Init(pProfile)))
    {
        Log::Error(L"[ Couldn't set up test pri ]");
    }

    // read initial decision info
    if (FAILED(testDI.InitDataFromTestVars(L"")))
    {
        Log::Error(L"[ Couldn't load test data ]");
        return;
    }

    // create builders
    const UnifiedEnvironment* pBuilderEnvironment = pri.GetPriSectionBuilder()->GetEnvironment();
    AutoDeletePtr<DecisionInfoSectionBuilder> pBuilder;
    VERIFY_SUCCEEDED(DecisionInfoSectionBuilder::CreateInstance(pri.GetFileBuilder(), pBuilderEnvironment, &pBuilder));

    if (pBuilder == NULL)
    {
        Log::Error(L"[ Couldn't create builders ]");
        return;
    }

    // Add test data to builders
    if (FAILED(testDI.ApplyTestData(pBuilder)))
    {
        Log::Error(L"[ Error applying test data ]");
        return;
    }

    BuildHelper build;
    VERIFY_SUCCEEDED(build.Build(pBuilder));

    Log::Comment(L"[ Build initial decision info ]");
    AutoDeletePtr<DecisionInfoFileSection> pReader;
    VERIFY_SUCCEEDED(DecisionInfoFileSection::CreateInstance(build.GetBuffer(), build.GetWrittenSize(), nullptr, &pReader));
    VERIFY(pReader != NULL);

    Log::Comment(L"[ Create UnifiedDecisionInfo ]");
    AutoDeletePtr<AtomPoolGroup> pMergedAtoms;
    VERIFY_SUCCEEDED(AtomPoolGroup::CreateInstance(10, &pMergedAtoms));
    AutoDeletePtr<UnifiedEnvironment> pReaderEnvironment;
    VERIFY_SUCCEEDED(UnifiedEnvironment::CreateInstance(pProfile, pMergedAtoms, &pReaderEnvironment));
    AutoDeletePtr<UnifiedDecisionInfo> pMergedDI;
    VERIFY_SUCCEEDED(UnifiedDecisionInfo::CreateInstance(pReaderEnvironment, pReader, &pMergedDI));
    VERIFY(pMergedDI != NULL);

    int numToMerge = 0;
    if (FAILED(TestData::TryGetValue(L"NumToMerge", numToMerge)))
    {
        Log::Error(L"[ NumToMerge not specified ]");
        return;
    }

    for (int i = 0; i < numToMerge; i++)
    {
        String prefix = tmp.Format(L"Merge%d", i + 1);
        TestDecisionInfo mergeDI;

        if (SUCCEEDED(mergeDI.InitDataFromTestVars((PCWSTR)prefix)))
        {
            AutoDeletePtr<DecisionInfoSectionBuilder> pMergeBuilder;
            VERIFY_SUCCEEDED(DecisionInfoSectionBuilder::CreateInstance(pri.GetFileBuilder(), pBuilderEnvironment, &pMergeBuilder));

            if (FAILED(mergeDI.ApplyTestData(pMergeBuilder)))
            {
                Log::Error(tmp.Format(L"[ Error applying test data \"%s\" ]", (PCWSTR)prefix));
                return;
            }

            BuildHelper mergeBuild;
            VERIFY_SUCCEEDED(mergeBuild.Build(pMergeBuilder));
            AutoDeletePtr<DecisionInfoFileSection> pMergeReader;
            VERIFY_SUCCEEDED(
                DecisionInfoFileSection::CreateInstance(mergeBuild.GetBuffer(), mergeBuild.GetWrittenSize(), nullptr, &pMergeReader));
            VERIFY(pMergeReader != NULL);

            AutoDeletePtr<RemapUInt16> pQualifierMap;
            VERIFY_SUCCEEDED(RemapUInt16::CreateInstance(pMergeReader->GetNumQualifiers(), &pQualifierMap));
            AutoDeletePtr<RemapUInt16> pQualifierSetMap;
            VERIFY_SUCCEEDED(RemapUInt16::CreateInstance(pMergeReader->GetNumQualifierSets(), &pQualifierSetMap));
            AutoDeletePtr<RemapUInt16> pDecisionMap;
            VERIFY_SUCCEEDED(RemapUInt16::CreateInstance(pMergeReader->GetNumDecisions(), &pDecisionMap));

            VERIFY_SUCCEEDED(pMergedDI->Merge(pMergeReader, pQualifierMap, pQualifierSetMap, pDecisionMap));

            TestUtils::TryVerifyRemap(tmp.Format(L"%sExpectedQualifiersMap", (PCWSTR)prefix), pQualifierMap);
            TestUtils::TryVerifyRemap(tmp.Format(L"%sExpectedQualifierSetsMap", (PCWSTR)prefix), pQualifierSetMap);
            TestUtils::TryVerifyRemap(tmp.Format(L"%sExpectedDecisionsMap", (PCWSTR)prefix), pDecisionMap);
        }
        else
        {
            Log::Error(tmp.Format(L"[ Couldn't load test data \"%s\" ]", (PCWSTR)prefix));
            return;
        }
    }

    // verify results
    TestDecisionInfoValidator validate;
    if (FAILED(validate.InitDataFromTestVars(L"Merged")))
    {
        Log::Error(L"[ Couldn't load test validation data ]");
        return;
    }

    validate.ValidateQualifiers(pMergedDI, pBuilderEnvironment);
    validate.ValidateQualifierSets(pMergedDI, pBuilderEnvironment);
    validate.ValidateDecisions(pMergedDI, pBuilderEnvironment);
}

} // namespace UnitTests
