// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "StdAfx.h"
#include "mrm/build/Base.h"
#include "mrm/readers/MrmManagers.h"

#include "TestHSchema.h"
#include "TestMap.h"
#include "TestPri.h"
#include "TestSections.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;

namespace UnitTests
{
class PriFileManagerUnitTests : public WEX::TestClass<PriFileManagerUnitTests>, public FileBasedTest
{
public:
    TEST_CLASS(PriFileManagerUnitTests);

    TEST_CLASS_SETUP(ClassSetup);
    TEST_CLASS_CLEANUP(ClassCleanup);

    TEST_METHOD_SETUP(MethodSetup);
    TEST_METHOD_CLEANUP(MethodCleanup);

    TEST_METHOD(FailureTests);

    BEGIN_TEST_METHOD(BasicSingleFileTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:PriFileManager.UnitTests.xml#BasicSingleFileTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(BasicMultiFileTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:PriFileManager.UnitTests.xml#BasicMultiFileTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(SingleFileTypedSectionTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:PriFileManager.UnitTests.xml#SingleFileTypedSectionTests")
    END_TEST_METHOD();

    BEGIN_TEST_METHOD(SingleFileSectionDemandLoadTests)
        TEST_METHOD_PROPERTY(L"DataSource", L"Table:PriFileManager.UnitTests.xml#SingleFileTypedSectionTests")
    END_TEST_METHOD();
};

bool ModuleSetup() { return true; }

bool ModuleCleanup() { return true; }

bool PriFileManagerUnitTests::ClassSetup()
{
    if (!SetupClassFolders(L"PriFileManager"))
    {
        Log::Error(L"Unable to set up test data folders for PriFileManager");
        return false;
    }
    return true;
}

bool PriFileManagerUnitTests::ClassCleanup()
{
    if (!CleanupClassFolders())
    {
        Log::Warning(L"Unable to clean up class folders for PriFileManager");
    }
    return true;
}

bool PriFileManagerUnitTests::MethodSetup() { return true; }

bool PriFileManagerUnitTests::MethodCleanup()
{
    // Always attempt to cleanup in case the method exited prematurely
    TryCleanupTestMethodOutputFolder();
    return true;
}

void PriFileManagerUnitTests::FailureTests()
{
    String priFilePath;
    String tmp;

    if (!SetupTestMethodOutputFolder(L"FailureTests"))
    {
        return;
    }

    AutoDeletePtr<CoreProfile> pProfile;
    VERIFY_SUCCEEDED(CoreProfile::ChooseDefaultProfile(&pProfile));
    AutoDeletePtr<AtomPoolGroup> pAtoms;
    VERIFY_SUCCEEDED(AtomPoolGroup::CreateInstance(&pAtoms));
    AutoDeletePtr<UnifiedEnvironment> pEnvironment;
    VERIFY_SUCCEEDED(UnifiedEnvironment::CreateInstance(pProfile, pAtoms, &pEnvironment));
    AutoDeletePtr<PriFileManager> pManager;
    VERIFY_SUCCEEDED(PriFileManager::CreateInstance(pEnvironment, &pManager));
    VERIFY(pManager != NULL);

    ManagedFile* pPri;
    HRESULT hr = pManager->GetFile(0, &pPri);
    VERIFY(hr == E_INVALIDARG);
    VERIFY(pPri == NULL);

    hr = pManager->GetFile(-1, &pPri);
    VERIFY(hr == E_INVALIDARG);
    VERIFY(pPri == NULL);

    if (GetOutputLongFilePath(L"bogus.pri", priFilePath) == NULL)
    {
        Log::Error(L"Unable to get output file path for \"bogus.pri\"");
        return;
    }

    // bogus.pri doesn't exist
    hr = pManager->GetOrAddFile((PCWSTR)priFilePath, L"", LoadPriFlags::Default, &pPri);
    VERIFY(pPri == NULL);
    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND));

    VERIFY(pManager->GetNumFiles() == 0);

    // Now let's create a bogus.pri file
    HANDLE hFile = INVALID_HANDLE_VALUE;
    if (!CreateOutputFile(L"bogus.pri", &hFile))
    {
        Log::Error(L"Unable to create bogus.pri");
        return;
    }

    // write some bogus data
    DWORD cbBogusData = 0;
    UINT32 bogusData = 0xdeadbeef;
    if (!WriteFile(hFile, &bogusData, sizeof(bogusData), &cbBogusData, NULL))
    {
        CloseHandle(hFile);
        Log::Error(L"Couldn't write to bogus.pri");
        return;
    }
    VERIFY(cbBogusData == sizeof(bogusData));

    CloseHandle(hFile);

    // Now we'll try to add it with preload.   Since it's a bogus empty
    // file, preload should fail.
    hr = pManager->GetOrAddFile((PCWSTR)priFilePath, L"", LoadPriFlags::Preload, &pPri);
    VERIFY(pPri == NULL);
    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE));

    // verify that it didn't halfway add the file
    VERIFY(pManager->GetNumFiles() == 0);

    // Now lets add it without preload.   This time it should succeed, since
    // it doesn't peek into the contents.
    VERIFY_SUCCEEDED(pManager->GetOrAddFile((PCWSTR)priFilePath, L"", LoadPriFlags::Default, &pPri));
    VERIFY(pPri != NULL);
    VERIFY(pManager->GetNumFiles() == 1);
    VERIFY(!pPri->IsLoaded());

    // Verify that the path & size are correct.
    //  and that the file
    VERIFY_IS_TRUE(DefString_IEqual(pPri->GetPath(), (PCWSTR)priFilePath));
    VERIFY(pPri->GetSizeInBytes() == cbBogusData);

    // verify the file is less than 30 seconds old
    FILETIME ftNow;
    GetSystemTimeAsFileTime(&ftNow);
    ULARGE_INTEGER now;
    now.u.LowPart = ftNow.dwLowDateTime;
    now.u.HighPart = ftNow.dwHighDateTime;
    UINT64 delta = now.QuadPart - pPri->GetLastModifiedDate();
    Log::Comment(tmp.Format(L"Now= %I64d, file= %I64d, delta = %I64d", now.QuadPart, pPri->GetLastModifiedDate(), delta));
    VERIFY((now.QuadPart >= pPri->GetLastModifiedDate()));
    if (delta > 3000000)
    {
        Log::Warning(tmp.Format(L"More than 30 seconds from file creation to now!"));
    }

    // Now verify that we can't force it to load
    hr = pManager->LoadFile(pPri);
    VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE));

    // and that trying to load it didn't change the number of times it's there
    VERIFY(pManager->GetNumFiles() == 1);

    // Let's try to load it a second time
    ManagedFile* pPri2;
    VERIFY_SUCCEEDED(pManager->GetOrAddFile((PCWSTR)priFilePath, L"", LoadPriFlags::Default, &pPri2));
    VERIFY(pPri2 == pPri);
    VERIFY(pManager->GetNumFiles() == 1);

    // Now let's create a bogus ManagedFile and pretend it belongs to our manager
    AutoDeletePtr<ManagedFile> pBogusPri;
    VERIFY_SUCCEEDED(ManagedFile::CreateInstance(pManager, pPri->GetGlobalIndex(), priFilePath, L"", LoadPriFlags::Default, &pBogusPri));
    VERIFY(pBogusPri != NULL);

    // Now verify that we can't load, unload or remove it
    hr = pManager->LoadFile(pBogusPri);
    VERIFY_ARE_EQUAL(hr, E_MRM_PRI_MANAGER_MISMATCH);

    hr = pManager->UnloadFile(pBogusPri);
    VERIFY_ARE_EQUAL(hr, E_MRM_PRI_MANAGER_MISMATCH);

    hr = pManager->RemoveFile(pBogusPri);
    VERIFY_ARE_EQUAL(hr, E_MRM_PRI_MANAGER_MISMATCH);

    // Now verify that we can still unload our original file (no-op because it isn't loaded but it shouldn't error)
    VERIFY_SUCCEEDED(pManager->UnloadFile(pPri));

    // MethodCleanup() cleans up our data
}

void PriFileManagerUnitTests::BasicSingleFileTests()
{
    TestHPri pri;
    TestResourceMap testMap;
    String tmp;

    if (!SetupTestMethodOutputFolder(L"BasicSingleFileTests"))
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

    Log::Comment(L"[ Initializing ]");
    if (FAILED(pri.InitFromTestVars(L"", NULL, pProfile, NULL)))
    {
        Log::Error(L"Error initializing Test PRI");
        return;
    }

    Log::Comment(L"[ Building test PRI ]");
    if (FAILED(pri.Build()))
    {
        Log::Error(L"[ Couldn't build test PRI ]");
        return;
    }

    Log::Comment(tmp.Format(L"[ Writing PRI to %s ]", (PCWSTR)priFilePath));
    if (FAILED(pri.WriteToFile((PCWSTR)priFilePath)))
    {
        Log::Error(L"Error building test PRI");
        return;
    }

    // Okay, we finally have our test data built.  Whew.  Now we can try to actually
    // test the PriFileManager.

    Log::Comment(L"[ Creating PriFileManager and adding test PRI ]");
    AutoDeletePtr<AtomPoolGroup> pAtoms;
    VERIFY_SUCCEEDED(AtomPoolGroup::CreateInstance(&pAtoms));
    AutoDeletePtr<UnifiedEnvironment> pEnvironment;
    VERIFY_SUCCEEDED(UnifiedEnvironment::CreateInstance(pProfile, pAtoms, &pEnvironment));
    AutoDeletePtr<PriFileManager> pManager;
    VERIFY_SUCCEEDED(PriFileManager::CreateInstance(pEnvironment, &pManager));
    VERIFY(pManager != NULL);

    ManagedFile* pFile;
    VERIFY_SUCCEEDED(pManager->GetOrAddFile((PCWSTR)priFilePath, L"", LoadPriFlags::Preload, &pFile));
    VERIFY(pFile != NULL);

    // verify we have the file name we expected
    // Not verifying time or size
    Log::Comment(L"[ Verifying path ]");
    VERIFY_IS_TRUE(DefString_IEqual(pFile->GetPath(), (PCWSTR)priFilePath));

    Log::Comment(L"[ Creating Standalone PRI for verification ]");
    BlobResult blob;
    const BaseFile* pBaseFile;
    VERIFY_SUCCEEDED(pFile->GetBaseFile(&pBaseFile));
    VERIFY_IS_NOT_NULL(pBaseFile);

    VERIFY_SUCCEEDED(pBaseFile->GetFileData(&blob));

    size_t cbBuf = 0;
    const BYTE* pBuf = (const BYTE*)blob.GetRef(&cbBuf);

    AutoDeletePtr<StandalonePriFile> pPri;
    VERIFY_SUCCEEDED(StandalonePriFile::CreateInstance(0, pBuf, cbBuf, pProfile, &pPri));
    VERIFY(pPri != NULL);

    TestHPri::VerifyAgainstTestVars(pPri, L"", pri.GetTestDI(), L"");

    // MethodCleanup cleans up our data
}

void PriFileManagerUnitTests::BasicMultiFileTests()
{
    String tmp;
    PCWSTR pVarPrefix = L"";

    if (!SetupTestMethodOutputFolder(L"BasicMultiFileTests"))
    {
        return;
    }

    pVarPrefix;
#ifdef notyet
    String fileNamesString;
    TestStringArray fileNames;
    if (FAILED(TestHPri::BuildMultiplePriFilesFromTestVars(pVarPrefix, this, &fileNames)))
    {
        return;
    }

    // Okay, our test data is built.
    // Now we can try to actually test the PriFileManager.
    AutoDeletePtr<PriFileManager> pManager;
    VERIFY_SUCCEEDED(PriFileManager::CreateInstance(&pManager));
    VERIFY(pManager != NULL);

    for (int f = 0; f < fileNames.GetNumStrings(); f++)
    {
        PCWSTR pFileName = fileNames.GetString(f);

        String priFilePath;
        if (GetOutputFilePath(tmp.Format(L"%s.pri", pFileName), priFilePath) == NULL)
        {
            Log::Error(tmp.Format(L"Unable to get output file path for \"%s.pri\"", pFileName));
        }

        const ManagedFile* pManagedPri;
        VERIFY_SUCCEEDED(pManager->GetOrAddFile((PCWSTR)priFilePath, L"", LoadPriFlags::Preload, &pManagedPri));
        VERIFY(pManagedPri != NULL));

        const PackageResources* pPri;
        VERIFY_SUCCEEDED(pManagedPri->GetPri(&pPri));
        VERIFY(pPri != NULL);

        String indexNamesList;
        TestStringArray indexNames;
        if (FAILED(TestData::TryGetValue(tmp.Format(L"%s%s_IndexNames", pVarPrefix, pFileName), indexNamesList)) ||
            FAILED(indexNames.InitFromList((PCWSTR)indexNamesList)))
        {
            Log::Error(tmp.Format(L"Error getting list of indexes for %s%s", pVarPrefix, pFileName));
        }

        VERIFY(pPri->GetNumResourceIndexes() == indexNames.GetNumStrings());

        for (int i = 0; i < indexNames.GetNumStrings(); i++)
        {
            PCWSTR pIndexName = indexNames.GetString(i);
            const ResourceIndex* pIndex;
            VERIFY_SUCCEEDED(pPri->GetResourceIndex(pIndexName, &pIndex));
            VERIFY(pIndex != NULL);

            VERIFY(TestSchema::TryVerifySchema(pIndex->GetSchema(pStatus), pIndexName));
        }
    }
#endif
    TryCleanupTestMethodOutputFolder();
}

void PriFileManagerUnitTests::SingleFileTypedSectionTests()
{
    String tmp;
    PCWSTR pVarPrefix = L"";

    TestHPri pri;

    if (!SetupTestMethodOutputFolder(L"SingleFileTypedSectionTests"))
    {
        return;
    }

    String priFileName;
    if (FAILED(TestData::TryGetValue(L"PriName", priFileName)))
    {
        priFileName = L"Typed";
    }
    pVarPrefix;
#ifdef notyet
    String priFilePath;
    if (FAILED(TestHPri::BuildPriFileFromTestVars(pVarPrefix, (PCWSTR)priFileName, &pri, this, priFilePath, NULL)))
    {
        return;
    }

    // Okay, we finally have our test data built.  Whew.  Now we can try to actually
    // test the PriFileManager.

    AutoDeletePtr<PriFileManager> pManager;
    VERIFY_SUCCEEDED(PriFileManager::CreateInstance(&pManager));
    VERIFY(pManager != NULL);

    const ManagedFile* pManagedPri;
    VERIFY_SUCCEEDED(pManager->GetOrAddFile((PCWSTR)priFilePath, L"", LoadPriFlags::Preload, &pManagedPri));
    VERIFY(pManagedPri != NULL);

    const PackageResources* pPri;
    VERIFY_SUCCEEDED(pManagedPri->GetPri(&pPri));
    VERIFY(pPri != NULL);
    // verify we have the file name we expected
    // Not verifying time or size
    VERIFY_IS_TRUE(DefString_IEqual(pManagedPri->GetPath(), (PCWSTR)priFilePath));

    // Verify any indexes defined by the test data
    VERIFY(pPri->GetNumResourceIndexes() == pri.GetNumIndexes());
    for (int i = 0; i < pri.GetNumIndexes(); i++)
    {
        TestIndex* pTestIndex = pri.GetIndex(i);

        const ResourceIndex* pIndex;
        VERIFY_SUCCEEDED(pPri->GetResourceIndex(i, &pIndex));
        VERIFY(pIndex != NULL);
        VERIFY(TestSchema::TryVerifySchema(pIndex->GetSchema(), pVarPrefix));

        const ResourceIndex* pIndex2;
        VERIFY_SUCCEEDED(pPri->GetResourceIndex(pTestIndex->GetBuilderIndexDisplayName(), &pIndex2));
        VERIFY(pIndex == pIndex2);
    }

    // Verify any "other" sections defined by the test data
    for (int i = 0; i < pri.GetNumSections(); i++)
    {
        TestSection* pSection = pri.GetSection(i);

        if (DefString_IEqual(pSection->GetTestSectionType(), TestDataItemsSection::DataItemsSectionTypeName))
        {
            const FileDataItemsSection* pDataItemsSection;
            VERIFY_SUCCEEDED(pManagedPri->GetDataItemsSection(0, pSection->GetBuilderSectionIndex(), &pDataItemsSection));
            VERIFY(pDataItemsSection != NULL);

            const FileDataItemsSection* pDataItemsSection2;
            VERIFY_SUCCEEDED(
                pManager->GetDataItemsSection(pManagedPri->GetGlobalIndex(), pSection->GetBuilderSectionIndex(), &pDataItemsSection2));
            VERIFY(pDataItemsSection2 == pDataItemsSection);
        }
        else
        {
            Log::Warning(tmp.Format(L"Unknown type %s for section %d", pSection->GetTestSectionType(), i));
        }
    }
#endif
    TryCleanupTestMethodOutputFolder();
}

void PriFileManagerUnitTests::SingleFileSectionDemandLoadTests()
{
    String tmp;
    PCWSTR pVarPrefix = L"";

    TestHPri pri;

    if (!SetupTestMethodOutputFolder(L"SingleFileSectionDemandLoadTests"))
    {
        return;
    }

    String priFileName;
    if (FAILED(TestData::TryGetValue(L"PriName", priFileName)))
    {
        priFileName = L"Typed";
    }

    pVarPrefix;
    TryCleanupTestMethodOutputFolder();
}

} // namespace UnitTests
