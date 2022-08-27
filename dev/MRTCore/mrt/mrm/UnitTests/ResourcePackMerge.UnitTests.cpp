// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "StdAfx.h"
#include "Helpers.h"
#include "mrm/build/Base.h"

#include "mrm/readers/MrmReaders.h"
#include "mrm/build/MrmBuilders.h"
#include "mrm/build/ResourcePackMerge.h"

#include "TestPri.h"
#include "TestMap.h"

using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;

namespace UnitTests
{

class ResourcePackMergeTests : public WEX::TestClass<ResourcePackMergeTests>
{
public:
    TEST_CLASS(ResourcePackMergeTests);

    BEGIN_TEST_METHOD(ThreeFilesMergeTest)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:ResourcePackMerge.UnitTests.xml#ThreeFilesMergeTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(LoadUnloadWithResourcePackTest)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:ResourcePackMerge.UnitTests.xml#LoadPriWitMergeTests")
    END_TEST_METHOD();

private:
    bool _BuildAndVerifyPri(_In_ TestHPri* pTestHPri, _In_ PCWSTR pVarPrefix, _In_ bool bAutoMerge, _In_ bool bResourcePackMerge);

    bool _CreatePriFile(
        _In_ PCWSTR pszPrefix,
        _In_opt_ PCWSTR pszFolder,
        _In_ PCWSTR pszFileName,
        _Inout_ TestHPri& testHPri,
        _Inout_ String& strOutPath,
        _In_ bool bAlwasyCreateClassFolder,
        _In_ bool bResourcePackMerge);

    bool _VerifyMergedFile(_In_ PCWSTR pszMergedFile, _In_ PCWSTR pszManifestClassName, _In_ TestHPri* pTestHPri);
};

/*
- SimpleTest
    -  Merge three files without preload flag
- PreloadSimpleTest
    -  Merge three files with preload the first file on
- 
*/

void ResourcePackMergeTests::ThreeFilesMergeTest()
{
    FileBasedTest fileBasedTestObj;
    String strPri3FilePath;
    String strPri4FilePath;
    String strPri5FilePath;
    TestHPri testHPri3;
    TestHPri testHPri4;
    TestHPri testHPri5;

    //StringResult   strMergedFilePath;
    VERIFY_IS_TRUE(fileBasedTestObj.SetupClassFolders(L"ResourcePackMergeTests"));

    // Build Pri1
    VERIFY_IS_TRUE(_CreatePriFile(
        L"Pri3_", L"ResourcePackMergeTests_ThreeFilesMerge", L"ResourcePackMergeTests_Main.pri", testHPri3, strPri3FilePath, true, true));

    // Build Pri2

    VERIFY_IS_TRUE(_CreatePriFile(
        L"Pri4_", L"ResourcePackMergeTests_ThreeFilesMerge", L"ResourcePackMergeTests_it-it.pri", testHPri4, strPri4FilePath, false, true));

    // Build Pri3
    VERIFY_IS_TRUE(_CreatePriFile(
        L"Pri5_", L"ResourcePackMergeTests_ThreeFilesMerge", L"ResourcePackMergeTests_ko-KR.pri", testHPri5, strPri5FilePath, false, true));

    // Call LoadPriFiles
    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));
    AutoDeletePtr<UnifiedResourceView> spUnifiedResourceView;
    VERIFY_SUCCEEDED(UnifiedResourceView::CreateInstance(pProfile, &spUnifiedResourceView));

    DynamicArray<PCWSTR> priPathsCollection;

    StringResult srPriFile3;
    VERIFY_SUCCEEDED(srPriFile3.Init(reinterpret_cast<PCWSTR>(strPri3FilePath.GetBuffer())));
    StringResult srPriFile4;
    VERIFY_SUCCEEDED(srPriFile4.Init(reinterpret_cast<PCWSTR>(strPri4FilePath.GetBuffer())));
    StringResult srPriFile5;
    VERIFY_SUCCEEDED(srPriFile5.Init(reinterpret_cast<PCWSTR>(strPri5FilePath.GetBuffer())));

    VERIFY_SUCCEEDED(priPathsCollection.Add(srPriFile3.GetRef()));
    VERIFY_SUCCEEDED(priPathsCollection.Add(srPriFile4.GetRef()));
    VERIFY_SUCCEEDED(priPathsCollection.Add(srPriFile5.GetRef()));

    AutoDeletePtr<ResourcePackMerge> spResourcePackMerge;
    VERIFY_SUCCEEDED(ResourcePackMerge::CreateInstance(pProfile, &spResourcePackMerge));
    VERIFY(spResourcePackMerge != NULL);

    //preload set
    PCWSTR path;
    VERIFY_SUCCEEDED(priPathsCollection.Get(0, &path));
    VERIFY_SUCCEEDED(spResourcePackMerge->AddPriFile(
        path, PriFileMerger::InPlaceMerge | PriFileMerger::SetPreLoad | PriFileMerger::DefaultPriMergeFlags));

    for (UINT i = 1; i < priPathsCollection.Count(); i++)
    {
        VERIFY_SUCCEEDED(priPathsCollection.Get(i, &path));
        VERIFY_SUCCEEDED(spResourcePackMerge->AddPriFile(path, PriFileMerger::InPlaceMerge | PriFileMerger::DefaultPriMergeFlags));
    }

    VERIFY_FAILED(spResourcePackMerge->AddPriFile(srPriFile5.GetRef(), PriFileMerger::InPlaceMerge | PriFileMerger::DefaultPriMergeFlags));

    priPathsCollection.Reset();

    String strOutPath;
    // Get the merged file path
    fileBasedTestObj.GetTestOutputDirectory(L"ResourcePackMergeTests_ThreeFilesMerge", NULL, strOutPath);
    strOutPath += L"\\";
    strOutPath += L"MergedPriFile.pri";

    VERIFY_SUCCEEDED(spResourcePackMerge->WriteToFile(strOutPath));
    _VerifyMergedFile(strOutPath, L"PriMerged_3_4_5_", &testHPri3);

    fileBasedTestObj.CleanupClassFolders();
}

void ResourcePackMergeTests::LoadUnloadWithResourcePackTest()
{
    FileBasedTest fileBasedTestObj;
    String strPri3FilePath;
    String strPri4FilePath;
    String strPri5FilePath;
    TestHPri testHPri3;
    TestHPri testHPri4;
    TestHPri testHPri5;

    //StringResult   strMergedFilePath;
    VERIFY_IS_TRUE(fileBasedTestObj.SetupClassFolders(L"LoadPriWithMergedFile"));

    // Build Pri3
    VERIFY_IS_TRUE(
        _CreatePriFile(L"Pri3_", L"LoadPriWithMergedFile", L"LoadPriWithMergedFile_Main.pri", testHPri3, strPri3FilePath, true, true));

    // Build Pri4
    VERIFY_IS_TRUE(
        _CreatePriFile(L"Pri4_", L"LoadPriWithMergedFile", L"LoadPriWithMergedFile_it-it.pri", testHPri4, strPri4FilePath, false, true));

    // Build Pri5
    VERIFY_IS_TRUE(
        _CreatePriFile(L"Pri5_", L"LoadPriWithMergedFile", L"LoadPriWithMergedFile_ko-KR.pri", testHPri5, strPri5FilePath, false, true));

    // Call LoadPriFiles
    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));

    StringResult srPriFile3;
    VERIFY_SUCCEEDED(srPriFile3.Init(reinterpret_cast<PCWSTR>(strPri3FilePath.GetBuffer())));
    StringResult srPriFile4;
    VERIFY_SUCCEEDED(srPriFile4.Init(reinterpret_cast<PCWSTR>(strPri4FilePath.GetBuffer())));
    StringResult srPriFile5;
    VERIFY_SUCCEEDED(srPriFile5.Init(reinterpret_cast<PCWSTR>(strPri5FilePath.GetBuffer())));

    AutoDeletePtr<ResourcePackMerge> spResourcePackMerge;
    VERIFY_SUCCEEDED(ResourcePackMerge::CreateInstance(pProfile, &spResourcePackMerge));
    VERIFY(spResourcePackMerge != NULL);

    //preload set
    VERIFY_SUCCEEDED(
        spResourcePackMerge->AddPriFile(srPriFile3.GetRef(), PriFileMerger::InPlaceMerge | PriFileMerger::DefaultPriMergeFlags));
    VERIFY_SUCCEEDED(spResourcePackMerge->AddPriFile(
        srPriFile4.GetRef(), PriFileMerger::InPlaceMerge | PriFileMerger::SetPreLoad | PriFileMerger::DefaultPriMergeFlags));

    String strOutPath;
    // Get the merged file path
    fileBasedTestObj.GetTestOutputDirectory(L"ResourcePackMergeTests_ThreeFilesMerge", NULL, strOutPath);
    strOutPath += L"\\";
    strOutPath += L"MergedPriFile.pri";

    // Merged file that has Pri3 and Pri4
    VERIFY_SUCCEEDED(spResourcePackMerge->WriteToFile(strOutPath));

    // LoadPriFiles Merged file as well as single resource PRI file.
    AutoDeletePtr<UnifiedResourceView> spUnifiedResourceView;
    VERIFY_SUCCEEDED(UnifiedResourceView::CreateInstance(pProfile, &spUnifiedResourceView));

    DynamicArray<StringResult*> priPathsCollection;

    DynamicArray<UnifiedResourceView::PriFileInfo*>* pLoadedPriFilesInfo = NULL;

    StringResult srMergedFile;
    VERIFY_SUCCEEDED(srMergedFile.Init(strOutPath));
    VERIFY_SUCCEEDED(priPathsCollection.Add(&srMergedFile)); // Merged file becom main pri package
    {
        // Load Merged file first
        VERIFY_SUCCEEDED(
            spUnifiedResourceView->LoadPriFiles(PACKAGE_INIT, &priPathsCollection, LoadPriFlags::Default, &pLoadedPriFilesInfo));
        for (UINT uItr = 0; uItr < pLoadedPriFilesInfo->Count(); uItr++)
        {
            UnifiedResourceView::PriFileInfo* pLoadedPriFileInfo;
            pLoadedPriFilesInfo->Get(uItr, &pLoadedPriFileInfo);
            delete pLoadedPriFileInfo;
        }
        delete pLoadedPriFilesInfo;
        pLoadedPriFilesInfo = NULL;

        priPathsCollection.Reset(); // remove merged pri file
        VERIFY_SUCCEEDED(srPriFile5.Init(reinterpret_cast<PCWSTR>(strPri5FilePath.GetBuffer())));
        priPathsCollection.Add(&srPriFile5);

        // Load additional PRI (deployment merge-able flag set) File with EXPLICIT_LOAD
        {
            VERIFY_SUCCEEDED(
                spUnifiedResourceView->LoadPriFiles(EXPLICIT_LOAD, &priPathsCollection, LoadPriFlags::Default, &pLoadedPriFilesInfo));
            for (UINT uItr = 0; uItr < pLoadedPriFilesInfo->Count(); uItr++)
            {
                UnifiedResourceView::PriFileInfo* pLoadedPriFileInfo;
                pLoadedPriFilesInfo->Get(uItr, &pLoadedPriFileInfo);
                delete pLoadedPriFileInfo;
            }
            delete pLoadedPriFilesInfo;
            pLoadedPriFilesInfo = NULL;
        }

        // Unload resource pack that is already loaded as part of Merged file
        HRESULT hr = spUnifiedResourceView->RemoveFileReference(srPriFile4.GetRef());
        VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_MRM_UNSUPPORTED_FILE_TYPE_FOR_LOAD_UNLOAD_PRI_FILE));
    }

    fileBasedTestObj.CleanupClassFolders();
}

bool ResourcePackMergeTests::_VerifyMergedFile(_In_ PCWSTR pszMergedFile, _In_ PCWSTR pszManifestClassName, _In_ TestHPri* pTestHPri)
{
    // Load the merged PRI file with official API
    DynamicArray<StringResult*> priPathsCollection;
    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));

    AutoDeletePtr<UnifiedResourceView> spUnifiedResourceView;
    VERIFY_SUCCEEDED(UnifiedResourceView::CreateInstance(pProfile, &spUnifiedResourceView));

    StringResult strFilePath;
    VERIFY_SUCCEEDED(strFilePath.Init(pszMergedFile));

    priPathsCollection.Add(&strFilePath);

    DynamicArray<UnifiedResourceView::PriFileInfo*>* pLoadedPriFilesInfo = nullptr;
    VERIFY_SUCCEEDED(spUnifiedResourceView->LoadPriFiles(EXPLICIT_LOAD, &priPathsCollection, LoadPriFlags::Default, &pLoadedPriFilesInfo));

    // Test Managed Resource Map of the Merged Pri file
    UnifiedResourceView::PriFileInfo* pLoadedPriFileInfo;
    pLoadedPriFilesInfo->Get(0, &pLoadedPriFileInfo);
    VERIFY(pLoadedPriFileInfo != nullptr);

    const ManagedResourceMap* pManagedResourceMap = pLoadedPriFileInfo->GetManagedResourceMap();
    TestResourceMap::VerifyAllAgainstTestVars(
        (const IResourceMapBase*)pManagedResourceMap,
        pTestHPri->GetTestDI(),
        spUnifiedResourceView->GetUnifiedEnvironment(),
        pszManifestClassName);

    for (UINT uItr = 0; uItr < pLoadedPriFilesInfo->Count(); uItr++)
    {
        pLoadedPriFilesInfo->Get(uItr, &pLoadedPriFileInfo);
        delete pLoadedPriFileInfo;
    }

    delete pLoadedPriFilesInfo;

    return true;
}
bool ResourcePackMergeTests::_CreatePriFile(
    _In_ PCWSTR pszPrefix,
    _In_opt_ PCWSTR pszClassName,
    _In_ PCWSTR pszFileName,
    _Inout_ TestHPri& testHPri,
    _Inout_ String& strOutPath,
    _In_ bool bAlwasyCreateClassFolder,
    _In_ bool bResourcePackMerge)
{
    FileBasedTest fileBasedTestObj;
    String strVarPrefix;
    bool bRetVal = true;
    String strOutputFile;

    strVarPrefix = pszPrefix;

    if (bAlwasyCreateClassFolder)
    {
        bRetVal = fileBasedTestObj.SetupClassFolders(pszClassName);
        fileBasedTestObj.GetOutputFilePath(pszFileName, strOutPath);
    }
    else
    {
        fileBasedTestObj.GetTestOutputDirectory(pszClassName, nullptr, strOutPath);
        strOutPath += L"\\";
        strOutPath += pszFileName;
    }

    bRetVal = bRetVal ? _BuildAndVerifyPri(&testHPri, strVarPrefix, false, bResourcePackMerge) : bRetVal;

    VERIFY(bRetVal);

    if (FAILED(testHPri.GetPriFileBuilder()->WriteToFile(strOutPath)))
    {
        Log::Error(L"Error building test PRI 1");
        bRetVal = false;
    }
    return bRetVal;
}

bool ResourcePackMergeTests::_BuildAndVerifyPri(
    __in TestHPri* pTestHPri,
    __in PCWSTR strVarPrefix,
    __in bool bAutoMerge,
    _In_ bool bResourcePackMerge)
{
    UINT32 nPriFileFlags = bAutoMerge ? MRMFILE_PRI_FLAGS_AUTO_MERGE : 0;
    nPriFileFlags |= bResourcePackMerge ? MRMFILE_PRI_FLAGS_DEPLOYMENT_MERGEABLE : 0;
    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));

    Log::Comment(L"[ Setting up test PRI ]");
    if (FAILED(pTestHPri->InitFromTestVars(strVarPrefix, NULL, pProfile, NULL)))
    {
        Log::Error(L"[ Couldn't init TestPri ]");
    }

    // Set auto merge flag
    if (FAILED(pTestHPri->GetPriSectionBuilder()->SetPriFileFlags(nPriFileFlags)))
    {
        Log::Error(L"[ Error in setting auto merge flag ]");
        return false;
    }

    // Okay, we're ready to build.
    Log::Comment(L"[ Building test PRI ]");
    if (FAILED(pTestHPri->Build()))
    {
        Log::Error(L"[ Couldn't build test PRI ]");
        return false;
    }

    // Now we have to read the PRI file back into something we can use...
    Log::Comment(L"[ Reading back test PRI ]");
    if (FAILED(pTestHPri->CreateReader(pProfile)))
    {
        Log::Error(L"Couldn't read back test PRI");
        return false;
    }

    Log::Comment(L"[ Verifying test PRI ]");
    return SUCCEEDED(TestHPri::VerifyAgainstTestVars(pTestHPri->GetPriFile(), L"", pTestHPri->GetTestDI(), strVarPrefix));
}

} // namespace UnitTests
