// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "StdAfx.h"
#include "Helpers.h"
#include "mrm/build/Base.h"

#include "mrm/readers/MrmReaders.h"
#include "mrm/build/MrmBuilders.h"

#include "TestPri.h"
#include "TestReverseMap.h"

using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;

namespace UnitTests
{
class ReverseFileMapUnitTests : public WEX::TestClass<ReverseFileMapUnitTests>
{
public:
    TEST_CLASS(ReverseFileMapUnitTests);

    BEGIN_TEST_METHOD(SimpleBuilderTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:ReverseFileMap.UnitTests.xml#SimpleBuildTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(SimpleBuilderReaderTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:ReverseFileMap.UnitTests.xml#SimpleBuildTests")
    END_TEST_METHOD();
};

void ReverseFileMapUnitTests::SimpleBuilderTests()
{
    String tmp;

    TestHPri pri;
    TestReverseFileMap testReverseMap;

    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));
    AutoDeletePtr<AtomPoolGroup> pAtoms;
    VERIFY_SUCCEEDED(AtomPoolGroup::CreateInstance(4, &pAtoms));
    AutoDeletePtr<UnifiedEnvironment> pEnvironment;
    VERIFY_SUCCEEDED(UnifiedEnvironment::CreateInstance(pProfile, pAtoms, &pEnvironment));
    VERIFY(pEnvironment != NULL);

    Log::Comment(L"[ Setting up test PRI ]");
    if (FAILED(pri.InitFromTestVars(L"", NULL, pProfile, NULL)))
    {
        Log::Error(L"[ Couldn't init TestPri ]");
    }

    if (FAILED(testReverseMap.InitFromTestVars(pri.GetPriSectionBuilder(), pEnvironment, L"")))
    {
        Log::Error(L"[ Couldn't load reverse map test data ]");
        return;
    }

    VERIFY_SUCCEEDED(testReverseMap.Finalize());
}

void ReverseFileMapUnitTests::SimpleBuilderReaderTests()
{
    String tmp;

    TestHPri pri;
    TestReverseFileMap testReverseMap;

    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));
    AutoDeletePtr<AtomPoolGroup> pAtoms;
    VERIFY_SUCCEEDED(AtomPoolGroup::CreateInstance(4, &pAtoms));
    AutoDeletePtr<UnifiedEnvironment> pEnvironment;
    VERIFY_SUCCEEDED(UnifiedEnvironment::CreateInstance(pProfile, pAtoms, &pEnvironment));
    VERIFY(pEnvironment != NULL);

    Log::Comment(L"[ Setting up test PRI ]");
    if (FAILED(pri.InitFromTestVars(L"", NULL, pProfile, NULL)))
    {
        Log::Error(L"[ Couldn't init TestPri ]");
    }

    if (FAILED(testReverseMap.InitFromTestVars(pri.GetPriSectionBuilder(), pEnvironment, L"")))
    {
        Log::Error(L"[ Couldn't load reverse map test data ]");
        return;
    }

    // Finalize
    VERIFY_SUCCEEDED(testReverseMap.Finalize());

    // Okay, we're ready to build.  First build the rest of the PRI.
    if (FAILED(pri.Build()))
    {
        Log::Error(L"[ Couldn't build test PRI ]");
        return;
    }

    // Now build Reverse Map
    VERIFY_SUCCEEDED(testReverseMap.Build());

    // Now we have to read the package resources back into something we can use...
    if (FAILED(pri.CreateReader(pProfile)))
    {
        Log::Error(L"Couldn't read back test PRI");
    }

    // ...to read back the map we just built.
    VERIFY_SUCCEEDED(testReverseMap.CreateReader());

    // Validate contents
    const IResourceMapBase* map;
    VERIFY_SUCCEEDED(pri.GetPriFile()->GetPrimaryResourceMap(&map));
    TestReverseFileMap::VerifyAllAgainstTestVars(
        testReverseMap.GetReverseFileMap(), pEnvironment, map, testReverseMap.GetTestDI(), testReverseMap.GetDecisionInfo(), L"");
}

} // namespace UnitTests
