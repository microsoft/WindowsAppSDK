// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"
#include "Helpers.h"
#include "mrm/build/Base.h"
#include "mrm/readers/MrmManagers.h"

#include "TestPri.h"
#include "TestHSchema.h"
#include "TestMap.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;

namespace UnitTests
{
class UnifiedResourceViewUnitTests : public WEX::TestClass<UnifiedResourceViewUnitTests>, public FileBasedTest
{
public:
    TEST_CLASS(UnifiedResourceViewUnitTests);

    TEST_CLASS_SETUP(ClassSetup);
    TEST_CLASS_CLEANUP(ClassCleanup);

    TEST_METHOD_SETUP(MethodSetup);
    TEST_METHOD_CLEANUP(MethodCleanup);

    TEST_METHOD(FailureTests);

    BEGIN_TEST_METHOD(ApplicationPriTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:UnifiedView.UnitTests.xml#SingleMapViewTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(NonApplicationPriTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:UnifiedView.UnitTests.xml#SingleMapViewTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(SimpleMultiMapPriTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:UnifiedView.UnitTests.xml#MultiMapPriTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(OutOfOrderMultiMapPriTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:UnifiedView.UnitTests.xml#MultiMapPriTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(NonApplicationMultiMapPriTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:UnifiedView.UnitTests.xml#MultiMapPriTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(DisjointAppFirstTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:UnifiedView.UnitTests.xml#MultipleFileTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(DisjointAppLastTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:UnifiedView.UnitTests.xml#MultipleFileTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(DisjointNoAppTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:UnifiedView.UnitTests.xml#MultipleFileTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(LoadUnloadTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:UnifiedView.UnitTests.xml#LoadUnloadTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(PackageRootTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:UnifiedView.UnitTests.xml#PackageRootTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(MapLookupTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:UnifiedView.UnitTests.xml#MapLookupTests")
    END_TEST_METHOD();

    TEST_METHOD(EnvironmentValidationTests);
};

bool UnifiedResourceViewUnitTests::ClassSetup()
{
    if (!SetupClassFolders(L"UnifiedResourceView"))
    {
        Log::Error(L"Unable to set up test data folders for UnifiedResourceView");
        return false;
    }
    return true;
}

bool UnifiedResourceViewUnitTests::ClassCleanup()
{
    if (!CleanupClassFolders())
    {
        Log::Warning(L"Unable to clean up class folders for UnifiedResourceView");
    }
    return true;
}

bool UnifiedResourceViewUnitTests::MethodSetup() { return true; }

bool UnifiedResourceViewUnitTests::MethodCleanup()
{
    // Always attempt to cleanup in case the method exited prematurely
    TryCleanupTestMethodOutputFolder();
    return true;
}

void UnifiedResourceViewUnitTests::FailureTests()
{
    String outputFolder;

    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));
    AutoDeletePtr<UnifiedResourceView> pView;
    VERIFY_SUCCEEDED(UnifiedResourceView::CreateInstance(pProfile, &pView));
    VERIFY(pView != NULL);

    const IResourceMapBase* pMap = NULL;
    VERIFY(pView->GetNumResourceMaps() == 0);

    HRESULT hr = pView->GetResourceMap(0, &pMap);
    VERIFY(pMap == NULL);
    VERIFY_IS_TRUE(hr == E_INVALIDARG);

    // Verify trying to get a non-existent PRI file
    const ManagedResourceMap* map;
    hr = pView->SetApplicationFile(L"non-existent.pri", L"", &map);
    pMap = map;
    VERIFY_IS_NULL(pMap);

    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND));

    VERIFY(pView->GetNumResourceMaps() == 0);

    // Not checking for file access failures
}

void UnifiedResourceViewUnitTests::ApplicationPriTests()
{
    TestHPri testPri;
    TestResourceMap testMap;
    String tmp;

    if (!SetupTestMethodOutputFolder(L"ApplicationPriTests"))
    {
        return;
    }

    String priFileName;
    if (FAILED(TestData::TryGetValue(L"PriPath", priFileName)))
    {
        priFileName = L"test.pri";
    }

    String priFilePath;
    if (GetOutputLongFilePath((PCWSTR)priFileName, priFilePath) == NULL)
    {
        Log::Error(tmp.Format(L"Unable to get output file path for \"%s\"", (PCWSTR)priFileName));
    }

    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));
    if (FAILED(testPri.Init(pProfile)))
    {
        Log::Error(L"Error initializing Test PRI");
        return;
    }

    if (FAILED(testPri.GetTestDI()->InitDataFromTestVars(L"")))
    {
        Log::Error(L"Error initializing Test Qualifiers");
        return;
    }

    if (FAILED(testMap.InitFromTestVars(
            testPri.GetPriSectionBuilder(), testPri.GetTestDI(), L"", GetTestOutputPath(), TestResourceMap::AddAllAsPrimary)))
    {
        Log::Error(L"Error initializing ResourceMap");
        return;
    }

    if (FAILED(testPri.WriteToFile((PCWSTR)priFilePath)))
    {
        Log::Error(L"Error building test PRI");
        return;
    }

    // Okay, we finally have our test data built.  Whew.  Now we can try to actually
    // test the ApplicationResourceManager.

    AutoDeletePtr<UnifiedResourceView> pView;
    VERIFY_SUCCEEDED(UnifiedResourceView::CreateInstance(pProfile, &pView));
    VERIFY(pView != NULL);

    const ManagedResourceMap* pMap;
    VERIFY_SUCCEEDED(pView->SetApplicationFile((PCWSTR)priFilePath, GetTestOutputPath(), &pMap));
    VERIFY(pMap != NULL);

    TestResourceMap::VerifyAllAgainstTestVars((const IResourceMapBase*)pMap, testPri.GetTestDI(), pView->GetUnifiedEnvironment(), L"");

    VERIFY(pView->GetNumResourceMaps() == 1);
    const IResourceMapBase* pMap2;
    VERIFY_SUCCEEDED(pView->GetResourceMap(0, &pMap2));
    VERIFY(pMap2 == (const IResourceMapBase*)pMap);

    VERIFY_SUCCEEDED(pView->GetResourceMapById(testMap.GetBuilderMapSimpleId(), &pMap2));
    VERIFY(pMap2 != NULL);
    VERIFY((pMap2 == (const IResourceMapBase*)pMap));

    // Misc other simple tests

    // verify we have the file name we expected
    // Not verifying time, date or package root
    StringResult appPriPath;
    VERIFY_SUCCEEDED(pView->GetApplicationFileInfo(&appPriPath, NULL, NULL, NULL));
    VERIFY_IS_TRUE(DefString_IEqual(appPriPath.GetRef(), (PCWSTR)priFilePath));

    // Nothing to verify with GetEnvironment currently.

    // Some basic negative tests
    HRESULT hr = pView->GetResourceMap(1, &pMap2);
    VERIFY_IS_TRUE(hr == E_INVALIDARG);
    VERIFY(pMap2 == NULL);

    hr = pView->GetResourceMap(-1, &pMap2);
    VERIFY_IS_TRUE(hr == E_INVALIDARG);
    VERIFY(pMap2 == NULL);

    hr = pView->GetResourceMapById(L"xyzzy", &pMap2);
    VERIFY(pMap2 == NULL);

#pragma prefast(suppress : 6309, "Testing illegal NULL parameter")
    hr = pView->GetResourceMapById(NULL, &pMap2);
    VERIFY_IS_TRUE(hr == E_INVALIDARG);
    VERIFY(pMap2 == NULL);

    // MethodCleanup() cleans up for us
}

void UnifiedResourceViewUnitTests::NonApplicationPriTests()
{
    TestHPri testPri;
    TestResourceMap testMap;
    String tmp;

    if (!SetupTestMethodOutputFolder(L"NonApplicationPriTests"))
    {
        return;
    }

    String priFileName;
    if (FAILED(TestData::TryGetValue(L"PriPath", priFileName)))
    {
        priFileName = L"test.pri";
    }

    String priFilePath;
    if (GetOutputFilePath((PCWSTR)priFileName, priFilePath) == NULL)
    {
        Log::Error(tmp.Format(L"Unable to get output file path for \"%s\"", (PCWSTR)priFileName));
    }

    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));
    if (FAILED(testPri.Init(pProfile)))
    {
        Log::Error(L"Error initializing Test PRI");
        return;
    }

    if (FAILED(testPri.GetTestDI()->InitDataFromTestVars(L"")))
    {
        Log::Error(L"Error initializing TestDecisionInfo");
        return;
    }

    if (FAILED(testMap.InitFromTestVars(
            testPri.GetPriSectionBuilder(), testPri.GetTestDI(), L"", GetTestOutputPath(), TestResourceMap::AddAll)))
    {
        Log::Error(L"Error initializing Test Index");
        return;
    }

    if (FAILED(testPri.WriteToFile((PCWSTR)priFilePath)))
    {
        Log::Error(L"Error building test PRI");
        return;
    }

    // Okay, we finally have our test data built.  Whew.  Now we can try to actually
    // test the ApplicationResourceManager.

    AutoDeletePtr<UnifiedResourceView> pView;
    VERIFY_SUCCEEDED(UnifiedResourceView::CreateInstance(pProfile, &pView));
    VERIFY(pView != NULL);

    const ManagedResourceMap* pMap;
    HRESULT hr = pView->SetApplicationFile((PCWSTR)priFilePath, GetTestOutputPath(), &pMap);
    VERIFY_IS_TRUE(hr == HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND));
    VERIFY(pMap == NULL);

    VERIFY_SUCCEEDED(pView->GetOrAddReferencedFile((PCWSTR)priFilePath, GetTestOutputPath(), &pMap, nullptr));
    VERIFY_IS_TRUE(pMap == NULL); // succeeds for non-app PRI but returns NULL

    const IResourceMapBase* pMap2 = NULL;
    VERIFY(pView->GetNumResourceMaps() == 1);
    VERIFY_SUCCEEDED(pView->GetResourceMap(0, &pMap2));
    VERIFY(pMap2 != NULL);

    TestResourceMap::VerifyAllAgainstTestVars((const IResourceMapBase*)pMap, testPri.GetTestDI(), pView->GetUnifiedEnvironment(), L"");

    VERIFY_SUCCEEDED(pView->GetResourceMapById(testMap.GetBuilderMapSimpleId(), &pMap2));
    VERIFY(pMap2 != NULL);

    // MethodCleanup() cleans up for us
}

void UnifiedResourceViewUnitTests::SimpleMultiMapPriTests()
{
    TestHPri testPri;
    TestResourceMap testMap1;
    TestResourceMap testMap2;
    String tmp;

    if (!SetupTestMethodOutputFolder(L"SimpleMultiMapPriTests"))
    {
        return;
    }

    String priFileName;
    if (FAILED(TestData::TryGetValue(L"PriPath", priFileName)))
    {
        priFileName = L"test.pri";
    }

    String priFilePath;
    if (GetOutputFilePath((PCWSTR)priFileName, priFilePath) == NULL)
    {
        Log::Error(tmp.Format(L"Unable to get output file path for \"%s\"", (PCWSTR)priFileName));
    }

    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));
    if (FAILED(testPri.Init(pProfile)))
    {
        Log::Error(L"Error initializing Test PRI");
        return;
    }

    if (FAILED(testPri.GetTestDI()->InitDataFromTestVars(L"")))
    {
        Log::Error(L"Error initializing TestDecsionInfo");
        return;
    }

    if (FAILED(testMap1.InitFromTestVars(
            testPri.GetPriSectionBuilder(), testPri.GetTestDI(), L"Primary_", GetTestOutputPath(), TestResourceMap::AddAllAsPrimary)))
    {
        Log::Error(L"Error initializing test Primary Index");
        return;
    }

    if (FAILED(testMap2.InitFromTestVars(
            testPri.GetPriSectionBuilder(), testPri.GetTestDI(), L"Secondary_", GetTestOutputPath(), TestResourceMap::AddAll)))
    {
        Log::Error(L"Error initializing test Secondary Index");
        return;
    }

    if (FAILED(testPri.WriteToFile((PCWSTR)priFilePath)))
    {
        Log::Error(L"Error building test PRI");
        return;
    }

    // Okay, we finally have our test data built.  Whew.  Now we can try to actually
    // test the UnifiedResourceView.

    AutoDeletePtr<UnifiedResourceView> pView;
    VERIFY_SUCCEEDED(UnifiedResourceView::CreateInstance(pProfile, &pView));
    VERIFY(pView != NULL);

    const ManagedResourceMap* pPrimaryMap;
    VERIFY_SUCCEEDED(pView->SetApplicationFile((PCWSTR)priFilePath, GetTestOutputPath(), &pPrimaryMap));
    VERIFY(pPrimaryMap != NULL);

    TestResourceMap::VerifyAllAgainstTestVars(
        (const IResourceMapBase*)pPrimaryMap, testPri.GetTestDI(), pView->GetUnifiedEnvironment(), L"Primary_");

    VERIFY(pView->GetNumResourceMaps() == 2);

    const IResourceMapBase* pMap1 = pPrimaryMap;
    const IResourceMapBase* pMap2;
    VERIFY_SUCCEEDED(pView->GetResourceMap(0, &pMap2));
    VERIFY(pMap2 == pMap1);

    VERIFY_SUCCEEDED(pView->GetResourceMapById(testMap1.GetBuilderMapSimpleId(), &pMap2));
    VERIFY(pMap2 == pMap1);

    // Now make sure we can get to the secondary index too
    VERIFY_SUCCEEDED(pView->GetResourceMap(1, &pMap1));
    TestResourceMap::VerifyAllAgainstTestVars(
        (const IResourceMapBase*)pMap1, testPri.GetTestDI(), pView->GetUnifiedEnvironment(), L"Secondary_");

    VERIFY_SUCCEEDED(pView->GetResourceMapById(testMap2.GetBuilderMapSimpleId(), &pMap2));
    VERIFY(pMap2 == pMap1);

    // MethodCleanup() cleans up for us
}

void UnifiedResourceViewUnitTests::OutOfOrderMultiMapPriTests()
{
    TestHPri testPri;
    TestResourceMap testMap1;
    TestResourceMap testMap2;
    String tmp;

    if (!SetupTestMethodOutputFolder(L"OutOfOrderMultiMapPriTests"))
    {
        return;
    }

    String priFileName;
    if (FAILED(TestData::TryGetValue(L"PriPath", priFileName)))
    {
        priFileName = L"test.pri";
    }

    String priFilePath;
    if (GetOutputFilePath((PCWSTR)priFileName, priFilePath) == NULL)
    {
        Log::Error(tmp.Format(L"Unable to get output file path for \"%s\"", (PCWSTR)priFileName));
    }

    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));
    if (FAILED(testPri.Init(pProfile)))
    {
        Log::Error(L"Error initializing Test PRI");
        return;
    }

    if (FAILED(testPri.GetTestDI()->InitDataFromTestVars(L"Expected")))
    {
        Log::Error(L"Error initializing TestDecisionInfo");
        return;
    }

    if (FAILED(testMap2.InitFromTestVars(
            testPri.GetPriSectionBuilder(), testPri.GetTestDI(), L"Secondary_", GetTestOutputPath(), TestResourceMap::AddAll)))
    {
        Log::Error(L"Error initializing test Secondary Index");
        return;
    }

    if (FAILED(testMap1.InitFromTestVars(
            testPri.GetPriSectionBuilder(), testPri.GetTestDI(), L"Primary_", GetTestOutputPath(), TestResourceMap::AddAllAsPrimary)))
    {
        Log::Error(L"Error initializing test Primary Index");
        return;
    }

    if (FAILED(testPri.WriteToFile((PCWSTR)priFilePath)))
    {
        Log::Error(L"Error building test PRI");
        return;
    }

    // Okay, we finally have our test data built.  Whew.  Now we can try to actually
    // test the UnifiedResourceView.

    AutoDeletePtr<UnifiedResourceView> pView;
    VERIFY_SUCCEEDED(UnifiedResourceView::CreateInstance(pProfile, &pView));
    VERIFY(pView != NULL);

    const ManagedResourceMap* pMap;
    VERIFY_SUCCEEDED(pView->SetApplicationFile((PCWSTR)priFilePath, GetTestOutputPath(), &pMap));
    VERIFY(pMap != NULL);

    TestResourceMap::VerifyAllAgainstTestVars(pMap, testPri.GetTestDI(), pView->GetUnifiedEnvironment(), L"Primary_");

    VERIFY(pView->GetNumResourceMaps() == 2);

    const IResourceMapBase* pMap2;
    VERIFY_SUCCEEDED(pView->GetResourceMap(1, &pMap2));
    VERIFY(pMap2 == pMap);

    VERIFY_SUCCEEDED(pView->GetResourceMapById(testMap1.GetBuilderMapSimpleId(), &pMap2));
    VERIFY(pMap2 == pMap);

    // Now make sure we can get to the secondary index too
    const IResourceMapBase* pMap1;
    VERIFY_SUCCEEDED(pView->GetResourceMap(0, &pMap1));
    TestResourceMap::VerifyAllAgainstTestVars(pMap1, testPri.GetTestDI(), pView->GetUnifiedEnvironment(), L"Secondary_");

    VERIFY_SUCCEEDED(pView->GetResourceMapById(testMap2.GetBuilderMapSimpleId(), &pMap2));

    VERIFY(pMap1 == pMap2);

    // MethodCleanup() cleans up for us
}

void UnifiedResourceViewUnitTests::NonApplicationMultiMapPriTests()
{
    TestHPri testPri;
    TestResourceMap testMap1;
    TestResourceMap testMap2;
    String tmp;

    if (!SetupTestMethodOutputFolder(L"NonApplicationMultiMapPriTests"))
    {
        return;
    }

    String priFileName;
    if (FAILED(TestData::TryGetValue(L"PriPath", priFileName)))
    {
        priFileName = L"test.pri";
    }

    String priFilePath;
    if (GetOutputFilePath((PCWSTR)priFileName, priFilePath) == NULL)
    {
        Log::Error(tmp.Format(L"Unable to get output file path for \"%s\"", (PCWSTR)priFileName));
    }

    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));
    if (FAILED(testPri.Init(pProfile)))
    {
        Log::Error(L"Error initializing Test PRI");
        return;
    }

    if (FAILED(testPri.GetTestDI()->InitDataFromTestVars(L"Expected")))
    {
        Log::Error(L"Error initializing TestDecisionInfo");
        return;
    }

    if (FAILED(testMap1.InitFromTestVars(
            testPri.GetPriSectionBuilder(), testPri.GetTestDI(), L"Primary_", GetTestOutputPath(), TestResourceMap::AddAll)))
    {
        Log::Error(L"Error initializing test Primary map");
        return;
    }

    if (FAILED(testMap2.InitFromTestVars(
            testPri.GetPriSectionBuilder(), testPri.GetTestDI(), L"Secondary_", GetTestOutputPath(), TestResourceMap::AddAll)))
    {
        Log::Error(L"Error initializing test Secondary Index");
        return;
    }

    if (FAILED(testPri.WriteToFile((PCWSTR)priFilePath)))
    {
        Log::Error(L"Error building test PRI");
        return;
    }

    // Okay, we finally have our test data built.  Whew.  Now we can try to actually
    // test the ApplicationResourceManager.

    AutoDeletePtr<UnifiedResourceView> pView;
    VERIFY_SUCCEEDED(UnifiedResourceView::CreateInstance(pProfile, &pView));
    VERIFY(pView != NULL);

    const ManagedResourceMap* pMap;
    HRESULT hr = pView->SetApplicationFile((PCWSTR)priFilePath, GetTestOutputPath(), &pMap);
    VERIFY_IS_TRUE(hr == HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND));
    VERIFY(pMap == NULL);

    VERIFY_SUCCEEDED(pView->GetOrAddReferencedFile((PCWSTR)priFilePath, GetTestOutputPath(), &pMap, nullptr));
    VERIFY(pMap == NULL); // succeeds for non-app PRI but returns NULL

    VERIFY(pView->GetNumResourceMaps() == 2);

    const IResourceMapBase* pMap1;
    VERIFY_SUCCEEDED(pView->GetResourceMap(0, &pMap1));
    VERIFY(pMap1 != NULL);

    TestResourceMap::VerifyAllAgainstTestVars(pMap1, testPri.GetTestDI(), pView->GetUnifiedEnvironment(), L"Primary_");

    const IResourceMapBase* pMap2;
    VERIFY_SUCCEEDED(pView->GetResourceMapById(testMap1.GetBuilderMapSimpleId(), &pMap2));
    VERIFY(pMap2 == pMap1);

    VERIFY_SUCCEEDED(pView->GetResourceMap(1, &pMap1));
    VERIFY(pMap1 != NULL);

    TestResourceMap::VerifyAllAgainstTestVars(pMap1, testPri.GetTestDI(), pView->GetUnifiedEnvironment(), L"Secondary_");

    VERIFY_SUCCEEDED(pView->GetResourceMapById(testMap2.GetBuilderMapSimpleId(), &pMap2));
    VERIFY(pMap2 == pMap1);

    // MethodCleanup() cleans up for us
}

void UnifiedResourceViewUnitTests::DisjointAppFirstTests()
{
    String tmp;
    PCWSTR pVarPrefix = L"";
    TestDecisionInfo testDI;

    if (!SetupTestMethodOutputFolder(L"DisjointAppFirstTests"))
    {
        return;
    }

    String fileNamesString;
    TestStringArray fileNames;
    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));

    if (FAILED(TestHPri::BuildMultiplePriFilesFromTestVars(pVarPrefix, this, pProfile, &fileNames)))
    {
        return;
    }

    if (FAILED(testDI.InitDataFromTestVars(L"Expected")))
    {
        Log::Error(L"Couldn't load TestDecisionInfo");
        return;
    }

    // Test data built.  Let's try to load it.

    AutoDeletePtr<UnifiedResourceView> pView;
    VERIFY_SUCCEEDED(UnifiedResourceView::CreateInstance(pProfile, &pView));
    VERIFY(pView != NULL);

    for (int f = 0; f < fileNames.GetNumStrings(); f++)
    {
        PCWSTR pFileName = fileNames.GetString(f);

        String priFilePath;
        if (GetOutputFilePath(tmp.Format(L"%s.pri", pFileName), priFilePath) == NULL)
        {
            Log::Error(tmp.Format(L"Unable to get output file path for \"%s.pri\"", pFileName));
        }

        if (f == 0)
        {
            Log::Comment(tmp.Format(L"[ loading %s.pri as application PRI ]", pFileName));
            const ManagedResourceMap* pMap;
            VERIFY_SUCCEEDED(pView->SetApplicationFile(priFilePath, GetTestOutputPath(), &pMap));
            VERIFY(pMap != NULL);
        }
        else
        {
            Log::Comment(tmp.Format(L"[ loading %s.pri as referenced PRI ]", pFileName));
            const ManagedResourceMap* map;
            VERIFY_SUCCEEDED(pView->GetOrAddReferencedFile(priFilePath, GetTestOutputPath(), &map, nullptr));
        }

        TestStringArray mapNames;
        if (FAILED(TestHPri::GetPriFileMapNamesFromTestVars(pVarPrefix, pFileName, &mapNames)))
        {
            Log::Error(tmp.Format(L"Error getting list of maps for %s%s", pVarPrefix, pFileName));
            return;
        }

        for (int i = 0; i < mapNames.GetNumStrings(); i++)
        {
            const IResourceMapBase* pMap = NULL;
            PCWSTR pMapName = mapNames.GetString(i);

            VERIFY_SUCCEEDED(pView->GetResourceMapById(pMapName, &pMap));
            VERIFY(pMap != NULL);
            PCWSTR pPfx = tmp.Format(L"%s%s%s", pVarPrefix, pFileName, pMapName);
            TestResourceMap::VerifyAllAgainstTestVars(pMap, &testDI, pView->GetUnifiedEnvironment(), pPfx);
        }
    }
    // MethodCleanup() cleans up for us
}

void UnifiedResourceViewUnitTests::DisjointAppLastTests()
{
    String tmp;
    PCWSTR pVarPrefix = L"";

    if (!SetupTestMethodOutputFolder(L"DisjointAppLastTests"))
    {
        return;
    }

    String fileNamesString;
    TestStringArray fileNames;
    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));

    if (FAILED(TestHPri::BuildMultiplePriFilesFromTestVars(pVarPrefix, this, pProfile, &fileNames)))
    {
        return;
    }

    TestDecisionInfo testDI;
    if (FAILED(testDI.InitDataFromTestVars(L"Expected")))
    {
        Log::Error(L"[ Couldn't load TestDecisionInfo data ]");
        return;
    }

    // Test data built.  Let's try to load it.
    AutoDeletePtr<UnifiedResourceView> pView;
    VERIFY_SUCCEEDED(UnifiedResourceView::CreateInstance(pProfile, &pView));
    VERIFY(pView != NULL);

    for (int f = 0; f < fileNames.GetNumStrings(); f++)
    {
        PCWSTR pFileName = fileNames.GetString(f);

        String priFilePath;
        if (GetOutputFilePath(tmp.Format(L"%s.pri", pFileName), priFilePath) == NULL)
        {
            Log::Error(tmp.Format(L"Unable to get output file path for \"%s.pri\"", pFileName));
        }

        if (f == (fileNames.GetNumStrings() - 1))
        {
            Log::Comment(tmp.Format(L"[ loading %s.pri as application PRI ]", pFileName));
            const ManagedResourceMap* pMap;
            VERIFY_SUCCEEDED(pView->SetApplicationFile(priFilePath, GetTestOutputPath(), &pMap));
            VERIFY(pMap != NULL);
        }
        else
        {
            Log::Comment(tmp.Format(L"[ loading %s.pri as referenced PRI ]", pFileName));
            const ManagedResourceMap* map;
            VERIFY_SUCCEEDED(pView->GetOrAddReferencedFile(priFilePath, GetTestOutputPath(), &map, nullptr));
        }

        TestStringArray mapNames;
        if (FAILED(TestHPri::GetPriFileMapNamesFromTestVars(pVarPrefix, pFileName, &mapNames)))
        {
            Log::Error(tmp.Format(L"Error getting list of maps for %s%s", pVarPrefix, pFileName));
            return;
        }

        for (int i = 0; i < mapNames.GetNumStrings(); i++)
        {
            PCWSTR pMapName = mapNames.GetString(i);

            const IResourceMapBase* pMap;
            VERIFY_SUCCEEDED(pView->GetResourceMapById(pMapName, &pMap));
            VERIFY(pMap != NULL);

            PCWSTR pPfx = tmp.Format(L"%s%s%s", pVarPrefix, pFileName, pMapName);
            TestResourceMap::VerifyAllAgainstTestVars(pMap, &testDI, pView->GetUnifiedEnvironment(), pPfx);
        }
    }

    // MethodCleanup() cleans up for us
}

void UnifiedResourceViewUnitTests::DisjointNoAppTests()
{
    String tmp;
    PCWSTR pVarPrefix = L"";

    if (!SetupTestMethodOutputFolder(L"DisjointNoAppTests"))
    {
        return;
    }

    String fileNamesString;
    TestStringArray fileNames;
    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));

    if (FAILED(TestHPri::BuildMultiplePriFilesFromTestVars(pVarPrefix, this, pProfile, &fileNames)))
    {
        return;
    }

    TestDecisionInfo testDI;
    if (FAILED(testDI.InitDataFromTestVars(L"Expected")))
    {
        Log::Error(L"[ Couldn't initialize TestDecisionInfo ]");
        return;
    }

    // Test data built.  Let's try to load it.
    AutoDeletePtr<UnifiedResourceView> pView;
    VERIFY_SUCCEEDED(UnifiedResourceView::CreateInstance(pProfile, &pView));
    VERIFY(pView != NULL);

    for (int f = 0; f < fileNames.GetNumStrings(); f++)
    {
        PCWSTR pFileName = fileNames.GetString(f);

        String priFilePath;
        if (GetOutputFilePath(tmp.Format(L"%s.pri", pFileName), priFilePath) == NULL)
        {
            Log::Error(tmp.Format(L"Unable to get output file path for \"%s.pri\"", pFileName));
        }

        Log::Comment(tmp.Format(L"[ loading %s.pri as referenced PRI ]", pFileName));
        const ManagedResourceMap* map;
        VERIFY_SUCCEEDED(pView->GetOrAddReferencedFile(priFilePath, GetTestOutputPath(), &map, nullptr));

        TestStringArray mapNames;
        if (FAILED(TestHPri::GetPriFileMapNamesFromTestVars(pVarPrefix, pFileName, &mapNames)))
        {
            Log::Error(tmp.Format(L"Error getting list of maps for %s%s", pVarPrefix, pFileName));
            return;
        }

        for (int i = 0; i < mapNames.GetNumStrings(); i++)
        {
            PCWSTR pMapName = mapNames.GetString(i);

            const IResourceMapBase* pMap;
            VERIFY_SUCCEEDED(pView->GetResourceMapById(pMapName, &pMap));
            VERIFY(pMap != NULL);

            PCWSTR pPfx = tmp.Format(L"%s%s%s", pVarPrefix, pFileName, pMapName);
            TestResourceMap::VerifyAllAgainstTestVars(pMap, &testDI, pView->GetUnifiedEnvironment(), pPfx);
        }
    }

    // MethodCleanup() cleans up for us
}

void UnifiedResourceViewUnitTests::LoadUnloadTests()
{
    String tmp;
    PCWSTR pVarPrefix = L"";

    if (!SetupTestMethodOutputFolder(L"LoadUnloadTests"))
    {
        return;
    }

    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));

    String fileNamesString;
    TestStringArray fileNames;
    if (FAILED(TestHPri::BuildMultiplePriFilesFromTestVars(pVarPrefix, this, pProfile, &fileNames)))
    {
        return;
    }

    AutoDeletePtr<UnifiedResourceView> pView;
    VERIFY_SUCCEEDED(UnifiedResourceView::CreateInstance(pProfile, &pView));
    VERIFY(pView != NULL);

    TestDecisionInfo testDI;
    if (FAILED(testDI.InitDataFromTestVars(L"Expected")))
    {
        Log::Error(L"[ Couldn't initialize TestDecisionInfo ]");
        return;
    }

    String file1EnPath;
    if (GetOutputFilePath(L"File1En.pri", file1EnPath) == NULL)
    {
        Log::Error(L"Unable to get output file path for \"File1En.pri\"");
        return;
    }

    // Load and verify the base schema with English,
    Log::Comment(L"[ Loading File1En.pri as application PRI ]");
    const ManagedResourceMap* pFile1Map;
    VERIFY_SUCCEEDED(pView->SetApplicationFile(file1EnPath, GetTestOutputPath(), &pFile1Map));
    VERIFY(pFile1Map != NULL);

    StringResult file1EnPrefix;
    file1EnPrefix.SetCopy(tmp.Format(L"%s%s%s", pVarPrefix, L"File1En", pFile1Map->GetSchema()->GetSimpleId()));
    TestResourceMap::VerifyAllAgainstTestVars(pFile1Map, &testDI, pView->GetUnifiedEnvironment(), file1EnPrefix.GetRef());

    // Verified.  Now let's unload it and make sure the schema is still there but the items aren't
    Log::Comment(L"[ Unloading File1En.pri ]");
    VERIFY_SUCCEEDED(pView->RemoveFileReference(file1EnPath));

    Log::Comment(L"[ Verify schema with no values for File1Map ]");
    TestHierarchicalSchema::TryVerifySchema(pFile1Map->GetSchema(), file1EnPrefix.GetRef());
    VERIFY(pFile1Map->GetTotalNumResourceValues() == 0);
    TestResourceMap::VerifyAllAgainstTestVars(pFile1Map, &testDI, pView->GetUnifiedEnvironment(), L"Schema1Unloaded");

    String resToTest;
    if (SUCCEEDED(TestData::TryGetValue(L"Schema1UnloadedResourceToResolve", resToTest)))
    {
        Log::Comment(L"[ Verify resolution behavior for resource with no values ]");
        NamedResourceResult res;
        DecisionResult decision;
        int results[10];
        int resultSets[10];
        VERIFY_SUCCEEDED(pFile1Map->GetResource((PCWSTR)resToTest, &res));
        VERIFY(res.GetNumCandidates() == 0);
        VERIFY_SUCCEEDED(res.GetDecision(&decision));
        HRESULT hr = pView->GetDefaultResolver()->EvaluateDecision(&decision, ARRAYSIZE(results), results, resultSets);
        VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_MRM_NO_MATCH_OR_DEFAULT_CANDIDATE));

        int selectedIndex = -1;
        QualifierSetResult qs;
        hr = pView->GetDefaultResolver()->EvaluateDecision(&decision, &selectedIndex, &qs);
        VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_MRM_NO_MATCH_OR_DEFAULT_CANDIDATE));
    }
    else
    {
        Log::Warning(L"[ No resource to test resolve, Schema1UnloadedResourceToResolve not defined ]");
    }

    Log::Comment(L"[ Reload and verify File1En.pri ]");
    const ManagedResourceMap* map;
    VERIFY_SUCCEEDED(pView->GetOrAddReferencedFile(file1EnPath, GetTestOutputPath(), &map, NULL));
    VERIFY_IS_TRUE(map == pFile1Map);
    TestResourceMap::VerifyAllAgainstTestVars(pFile1Map, &testDI, pView->GetUnifiedEnvironment(), file1EnPrefix.GetRef());

    Log::Comment(L"[ Unload File1En.pri ]");
    VERIFY_SUCCEEDED(pView->RemoveFileReference(file1EnPath));

    String file1DePath;
    if (GetOutputFilePath(L"File1De.pri", file1DePath) == NULL)
    {
        Log::Error(L"Unable to get output file path for \"File1De.pri\"");
        return;
    }
    StringResult file1DePrefix;
    file1DePrefix.SetCopy(tmp.Format(L"%s%s%s", pVarPrefix, L"File1De", pFile1Map->GetSchema()->GetSimpleId()));

    Log::Comment(L"[ Load and verify File1De.pri ]");
    VERIFY_SUCCEEDED(pView->GetOrAddReferencedFile(file1DePath, GetTestOutputPath(), &map, NULL));
    VERIFY_IS_TRUE(map == pFile1Map);
    TestResourceMap::VerifyAllAgainstTestVars(pFile1Map, &testDI, pView->GetUnifiedEnvironment(), file1DePrefix.GetRef());

    Log::Comment(L"[ Unload File1De.pri ]");
    VERIFY_SUCCEEDED(pView->RemoveFileReference(file1DePath));

    String file1_1EnPath;
    StringResult file1_1EnPrefix;
    if (GetOutputFilePath(L"File1_1En.pri", file1_1EnPath) == NULL)
    {
        Log::Error(L"Unable to get output file path for \"File1_1En.pri\"");
        return;
    }
    file1_1EnPrefix.SetCopy(tmp.Format(L"%s%s%s", pVarPrefix, L"File1_1En", pFile1Map->GetSchema()->GetSimpleId()));

    Log::Comment(L"[ Load and verify File1_1En.pri ]");
    VERIFY_SUCCEEDED(pView->GetOrAddReferencedFile(file1_1EnPath, GetTestOutputPath(), &map, NULL));
    VERIFY_IS_TRUE(map == pFile1Map);
    TestResourceMap::VerifyAllAgainstTestVars(pFile1Map, &testDI, pView->GetUnifiedEnvironment(), file1_1EnPrefix.GetRef());

    Log::Comment(L"[ Unload File1_1En.pri and verify schema is still 1.1 ]");
    VERIFY_SUCCEEDED(pView->RemoveFileReference(file1_1EnPath));
    TestHierarchicalSchema::TryVerifySchema(pFile1Map->GetSchema(), file1_1EnPrefix.GetRef());
    VERIFY(pFile1Map->GetTotalNumResourceValues() == 0);

    StringResult file1DeUpgradedPrefix;
    file1DeUpgradedPrefix.SetCopy(tmp.Format(L"%s%s%s", pVarPrefix, L"File1DeUpgraded", pFile1Map->GetSchema()->GetSimpleId()));

    Log::Comment(L"[ Load and verify File1De.pri again ]");
    VERIFY_SUCCEEDED(pView->GetOrAddReferencedFile(file1DePath, GetTestOutputPath(), &map, NULL));
    VERIFY_IS_TRUE(map == pFile1Map);
    TestResourceMap::VerifyAllAgainstTestVars(pFile1Map, &testDI, pView->GetUnifiedEnvironment(), file1DeUpgradedPrefix.GetRef());

    // MethodCleanup() cleans up for us
}

void UnifiedResourceViewUnitTests::PackageRootTests()
{
    String tmp;
    PCWSTR pVarPrefix = L"";

    if (!SetupTestMethodOutputFolder(L"LoadUnloadTests"))
    {
        return;
    }

    String fileNamesString;
    TestStringArray fileNames;
    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));

    if (FAILED(TestHPri::BuildMultiplePriFilesFromTestVars(pVarPrefix, this, pProfile, &fileNames)))
    {
        return;
    }

    TestDecisionInfo testDI;
    if (FAILED(testDI.InitDataFromTestVars(L"Expected")))
    {
        Log::Error(L"[ Couldn't initialize TestDecisionInfo ]");
        return;
    }

    AutoDeletePtr<UnifiedResourceView> pView;
    VERIFY_SUCCEEDED(UnifiedResourceView::CreateInstance(pProfile, &pView));
    VERIFY(pView != NULL);

    String file1EnPath;
    if (GetOutputFilePath(L"File1En.pri", file1EnPath) == NULL)
    {
        Log::Error(L"[ Unable to get output file path for \"File1En.pri\" ]");
        return;
    }

    // Load and verify the base schema with English,
    Log::Comment(L"[ Loading File1En.pri as application PRI ]");
    if (FAILED(TestData::TryGetValue(L"File1EnPackageRoot", tmp)))
    {
        Log::Error(L"[ Couldn't get File1EnPackageRoot ]");
        return;
    }
    const ManagedResourceMap* pFile1Map;
    VERIFY_SUCCEEDED(pView->SetApplicationFile(file1EnPath, (PCWSTR)tmp, &pFile1Map));
    VERIFY(pFile1Map != NULL);

    StringResult file1EnPrefix;
    file1EnPrefix.SetCopy(tmp.Format(L"%s%s%s", pVarPrefix, L"File1En", pFile1Map->GetSchema()->GetSimpleId()));
    TestResourceMap::VerifyAllAgainstTestVars(pFile1Map, &testDI, pView->GetUnifiedEnvironment(), file1EnPrefix.GetRef());

    Log::Comment(L"[ Unload and reload with a different root ]");
    if (FAILED(TestData::TryGetValue(L"File1EnAltPackageRoot", tmp)))
    {
        Log::Error(L"[ Couldn't get File1EnAltPackageRoot ]");
        return;
    }

    VERIFY_SUCCEEDED(pView->RemoveFileReference(file1EnPath));
    const ManagedResourceMap* map;
    VERIFY_SUCCEEDED(pView->GetOrAddReferencedFile(file1EnPath, (PCWSTR)tmp, &map, NULL));
    VERIFY_IS_TRUE(map == pFile1Map);

    StringResult file1EnAltPrefix;
    file1EnAltPrefix.SetCopy(tmp.Format(L"%s%s%s", pVarPrefix, L"File1EnAlt", pFile1Map->GetSchema()->GetSimpleId()));
    TestResourceMap::VerifyCandidates(pFile1Map, &testDI, pView->GetUnifiedEnvironment(), file1EnAltPrefix.GetRef());

    Log::Comment(L"[ Unload and reload with default root ]");
    VERIFY_SUCCEEDED(pView->RemoveFileReference(file1EnPath));
    VERIFY_SUCCEEDED(pView->GetOrAddReferencedFile(file1EnPath, NULL, &map, NULL));
    VERIFY_IS_TRUE(map == pFile1Map);

    String resName;
    String expectedSuffix;
    if (FAILED(TestData::TryGetValue(L"File1EnDfltResourceToCheck", resName)) ||
        FAILED(TestData::TryGetValue(L"File1EnDfltExpectedSuffix", expectedSuffix)))
    {
        Log::Error(L"[ Couldn't get File1EnDflt test data ]");
        return;
    }

    NamedResourceResult res;
    ResourceCandidateResult candidate;
    StringResult candidateValue;
    VERIFY_SUCCEEDED(pFile1Map->GetResource((PCWSTR)resName, &res));
    VERIFY(res.GetNumCandidates() == 1);
    VERIFY_SUCCEEDED(res.GetCandidate(0, &candidate));
    VERIFY(candidate.TryGetStringValue(&candidateValue));

    String prefix;
    PCWSTR pPrefix;
    pPrefix = GetOutputFilePath(L"", prefix);
    VERIFY(pPrefix != NULL);
    int cchPrefix = static_cast<int>(wcslen(pPrefix));

    VERIFY(DefString_CchCompareWithOptions(candidateValue.GetRef(), pPrefix, cchPrefix, DefCompare_CaseInsensitive) == Def_Equal);
    PCWSTR pSuffix = &candidateValue.GetRef()[cchPrefix];
    VERIFY(DefString_ICompare(pSuffix, (PCWSTR)expectedSuffix) == Def_Equal);
}

void UnifiedResourceViewUnitTests::MapLookupTests()
{
    String tmp;
    PCWSTR pVarPrefix = L"";
    String filesSpec;
    TestStringArray files;
    String expectedMapsSpec;
    TestStringArray expectedMaps;
    String unexpectedMapsSpec;
    TestStringArray unexpectedMaps;

    if (!SetupTestMethodOutputFolder(L"MapLookupTests"))
    {
        return;
    }

    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));

    String fileNamesString;
    TestStringArray fileNames;
    if (FAILED(TestHPri::BuildMultiplePriFilesFromTestVars(pVarPrefix, this, pProfile, &fileNames)))
    {
        return;
    }

    AutoDeletePtr<UnifiedResourceView> pView;
    VERIFY_SUCCEEDED(UnifiedResourceView::CreateInstance(pProfile, &pView));
    VERIFY(pView != NULL);

    // Load all of the files
    if (FAILED(TestData::TryGetValue(L"FilesToLoad", filesSpec)) || !files.InitFromList(filesSpec))
    {
        Log::Error(L"[ Couldn't load FilesToLoad ]");
        return;
    }

    for (int i = 0; i < files.GetNumStrings(); i++)
    {
        String fullPath;
        if (GetOutputFilePath(files.GetString(i), fullPath) == NULL)
        {
            Log::Error(tmp.Format(L"[ Unable to get output file path for \"%s\" ]", files.GetString(i)));
            return;
        }
        Log::Comment(tmp.Format(L"[ Loading file \"%s\" ]", (PCWSTR)fullPath));
        const ManagedResourceMap* map;
        VERIFY_SUCCEEDED(pView->GetOrAddReferencedFile((PCWSTR)fullPath, NULL, &map, NULL));
    }

    // Now make sure that we find all of the names we're expecting
    if (FAILED(TestData::TryGetValue(L"ExpectedMapNames", expectedMapsSpec)) || !expectedMaps.InitFromList(expectedMapsSpec))
    {
        Log::Warning(L"[ Couldn't load ExpectedMapNames ]");
    }
    else
    {
        for (int i = 0; i < expectedMaps.GetNumStrings(); i++)
        {
            Log::Comment(tmp.Format(L"[ Looking for resource map \"%s\" ]", expectedMaps.GetString(i)));
            const IResourceMapBase* pMap;
            VERIFY_SUCCEEDED(pView->GetResourceMapById(expectedMaps.GetString(i), &pMap));
            VERIFY(pMap != NULL);
        }
    }

    // Finally, make sure that we don't find any of the names that shouldn't be there
    if (FAILED(TestData::TryGetValue(L"UnexpectedMapNames", unexpectedMapsSpec)) || !unexpectedMaps.InitFromList(unexpectedMapsSpec))
    {
        Log::Warning(L"[ UnexpectedMapNames not specified ]");
    }
    else
    {
        for (int i = 0; i < unexpectedMaps.GetNumStrings(); i++)
        {
            Log::Comment(tmp.Format(L"[ Verifying that resource map \"%s\" doesn't exist ]", unexpectedMaps.GetString(i)));
            const IResourceMapBase* pMap;
            HRESULT hr = pView->GetResourceMapById(unexpectedMaps.GetString(i), &pMap);
            VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_NOT_FOUND));
            VERIFY(pMap == NULL);
        }
    }
}

void UnifiedResourceViewUnitTests::EnvironmentValidationTests()
{
    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));

    AutoDeletePtr<UnifiedResourceView> pView;
    VERIFY_SUCCEEDED(UnifiedResourceView::CreateInstance(pProfile, &pView));

    UnifiedEnvironment* pEnvironment = pView->GetUnifiedEnvironment();

    Atom atom = Atom::NullAtom;
    HRESULT hr = pEnvironment->GetResourceValueTypeAtom(static_cast<MrmEnvironment::ResourceValueType>(-1), &atom);
    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_MRM_RESOURCE_TYPE_MISMATCH));

    hr = pEnvironment->GetResourceValueLocatorAtom(L"bogus", &atom);
    VERIFY_ARE_EQUAL(hr, E_MRM_BAD_NAME);

    hr = pEnvironment->GetTypeOfQualifier(L"bogus", &atom);
    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER));

    hr = pEnvironment->GetTypeOfQualifier(L"bogus", &atom);
    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER));

    const IBuildQualifierType* pType;
    hr = pEnvironment->GetTypeOfQualifier(L"bogus", &pType);
    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER));

    hr = pEnvironment->ValidateQualifierValue(L"bogus", L"!!!");
    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER));

    hr = pEnvironment->ValidateQualifierValue(atom, L"!!!");
    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER));

    hr = pEnvironment->ValidateQualifierComparison(L"bogus", ICondition::MatchOp, L"!!!");
    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER));

    hr = pEnvironment->ValidateQualifierComparison(atom, ICondition::MatchOp, L"!!!");
    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_MRM_UNKNOWN_QUALIFIER));
}

} // namespace UnitTests
