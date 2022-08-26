// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"
#include "WexTestClass.h"
#include "TestFileUtils.h"

using namespace Microsoft::Resources;
using namespace Microsoft::Resources::Build;
using namespace WEX::Common;
using namespace WEX::TestExecution;
using namespace WEX::Logging;

namespace UnitTests
{

FileBasedTest::FileBasedTest() : m_runFrom(Current), m_pTestClassName(nullptr), m_pTestMethodName(nullptr), m_pClassDataSubfolder(nullptr)
{}

DWORD
FileBasedTest::CreateDirectoryHierarchy(_In_ const WEX::Common::String& path)
{
    DWORD dwRet = S_OK;

    if (CreateDirectory(path, nullptr))
    {
        return dwRet;
    }
    dwRet = GetLastError();
    if (dwRet != ERROR_PATH_NOT_FOUND)
    {
        return dwRet;
    }
    WEX::Common::String parent(path);
    int len, ndx;
    // use a loop here to trim any trailing slashes
    do
    {
        len = parent.GetLength();
        ndx = parent.ReverseFind(L'\\');
    } while ((ndx > 0) && (ndx == (len - 1)));

    if (ndx <= 0)
    {
        return dwRet;
    }
    dwRet = CreateDirectoryHierarchy(parent.Left(ndx));

    if (FAILED(dwRet))
    {
        return dwRet;
    }
    if (CreateDirectory(path, nullptr))
    {
        return S_OK;
    }
    return GetLastError();
}

DWORD
FileBasedTest::DeleteDirectoryContents(_In_ const WEX::Common::String& path)
{
    DWORD dwRet = ERROR_SUCCESS;
    HANDLE hFindFile = INVALID_HANDLE_VALUE;
    WEX::Common::String wildcardPath;
    WEX::Common::String childPath;
    WIN32_FIND_DATA findData;

    SetLastError(0);

    wildcardPath.Format(L"%s\\*", static_cast<PCWSTR>(path));

    hFindFile = FindFirstFile(wildcardPath, &findData);

    if (hFindFile == INVALID_HANDLE_VALUE)
    {
        dwRet = GetLastError();
        if (dwRet != ERROR_FILE_NOT_FOUND)
        {
            goto done;
        }
        dwRet = ERROR_SUCCESS;
        goto done;
    }
    do
    {
        if (wcscmp(findData.cFileName, L".") == 0 || wcscmp(findData.cFileName, L"..") == 0)
        {
            goto nextFile;
        }
        childPath.Format(L"%s\\%s", static_cast<PCWSTR>(path), findData.cFileName);

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            dwRet = DeleteDirectoryContents(childPath);
            if (dwRet != ERROR_SUCCESS)
            {
                goto done;
            }
            if (!RemoveDirectory(childPath))
            {
                dwRet = GetLastError();
                goto done;
            }
        }
        else
        {
            if (!DeleteFile(childPath))
            {
                dwRet = GetLastError();
                goto done;
            }
        }
    nextFile:;
    } while (FindNextFile(hFindFile, &findData));

    FindClose(hFindFile);
    hFindFile = INVALID_HANDLE_VALUE;

done:
    if (hFindFile != INVALID_HANDLE_VALUE)
    {
        FindClose(hFindFile);
    }

    return dwRet;
}

DWORD
FileBasedTest::DeleteDirectoryAndContents(_In_ const WEX::Common::String& path)
{
    DWORD dwRet = DeleteDirectoryContents(path);

    if ((dwRet == S_OK) && (!RemoveDirectory(path)))
    {
        dwRet = GetLastError();
    }
    return dwRet;
}

bool FileBasedTest::GetTestDataDirectory(_In_opt_z_ PCWSTR pSubfolder, _Inout_ WEX::Common::String& dataDirPath)
{
    if (!SUCCEEDED(RuntimeParameters::TryGetValue(L"TestDeploymentDir", dataDirPath)))
    {
        return false;
    }
    if (pSubfolder != nullptr)
    {
        dataDirPath.Append(L"\\data\\");
        dataDirPath.Append(pSubfolder);
    }
    else
    {
        dataDirPath.Append(L"\\data");
    }
    return true;
}

bool FileBasedTest::GetTestDataDirectory(_Inout_ WEX::Common::String& dataDirPath) { return GetTestDataDirectory(nullptr, dataDirPath); }

bool FileBasedTest::GetTestOutputDirectory(
    _In_opt_z_ PCWSTR pTestClassName,
    _In_opt_z_ PCWSTR pTestName,
    _Inout_ WEX::Common::String& testOutputPath)
{
    if ((!SUCCEEDED(RuntimeParameters::TryGetValue(L"OutputBaseDir", testOutputPath))) &&
        (!SUCCEEDED(RuntimeParameters::TryGetValue(L"TestDeploymentDir", testOutputPath))))
    {
        return false;
    }

    if (testOutputPath[testOutputPath.GetLength() - 1] == '\\')
    {
        testOutputPath.Append(L"output");
    }
    else
    {
        testOutputPath.Append(L"\\output");
    }

    if (pTestClassName && pTestClassName[0])
    {
        testOutputPath.AppendFormat(L"\\%s", pTestClassName);
    }
    if (pTestName && pTestName[0])
    {
        testOutputPath.AppendFormat(L"\\%s", pTestName);
    }
    return true;
}

bool FileBasedTest::SetupDirectory(_In_z_ PCWSTR pPath)
{
    WEX::Common::String path(pPath);
    DWORD err = CreateDirectoryHierarchy(path);
    if (err == ERROR_ALREADY_EXISTS)
    {
        err = DeleteDirectoryContents(path);
    }
    return (err == S_OK);
}

bool FileBasedTest::SetupTestOutputDirectory(
    _In_z_ PCWSTR pTestClassName,
    _In_opt_z_ PCWSTR pTestName,
    _Inout_ WEX::Common::String& testOutputPath)
{
    if (!GetTestOutputDirectory(pTestClassName, pTestName, testOutputPath))
    {
        return false;
    }
    return SetupDirectory(testOutputPath);
}

bool FileBasedTest::CleanupTestOutputDirectory(_In_ const WEX::Common::String& testOutputPath)
{
    DWORD dwRet = S_OK;
    WEX::Common::String value;

    if ((!SUCCEEDED(RuntimeParameters::TryGetValue(L"KeepTestOutput", value))) || (value.CompareNoCase(L"false") == 0))
    {
        dwRet = DeleteDirectoryAndContents(testOutputPath);
    }
    return (dwRet == S_OK);
}

DWORD
FileBasedTest::CopyDirectoryContents(_In_z_ PCWSTR pSrcDir, _In_z_ PCWSTR pDestDir)
{
    DWORD dwRet = ERROR_SUCCESS;
    HANDLE hFindFile = INVALID_HANDLE_VALUE;

    WEX::Common::String srcPath(pSrcDir);
    WEX::Common::String destPath(pDestDir);
    WEX::Common::String wildcardPath;
    WEX::Common::String childPath;
    WEX::Common::String destChildPath;
    WIN32_FIND_DATA findData;

    SetLastError(0);

    wildcardPath.Format(L"%s\\*", srcPath.GetBuffer());

    hFindFile = FindFirstFile(wildcardPath, &findData);

    if (hFindFile == INVALID_HANDLE_VALUE)
    {
        dwRet = GetLastError();
        if (dwRet != ERROR_FILE_NOT_FOUND)
        {
            goto done;
        }
        dwRet = ERROR_SUCCESS;
        goto done;
    }

    if (!SetupDirectory(destPath))
    {
        dwRet = GetLastError();
        goto done;
    }

    do
    {
        if (wcscmp(findData.cFileName, L".") == 0 || wcscmp(findData.cFileName, L"..") == 0)
        {
            goto nextFile;
        }
        childPath.Format(L"%s\\%s", srcPath.GetBuffer(), findData.cFileName);
        destChildPath.Format(L"%s\\%s", destPath.GetBuffer(), findData.cFileName);

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            dwRet = CopyDirectoryContents(childPath, destChildPath);
            if (dwRet != ERROR_SUCCESS)
            {
                goto done;
            }
        }
        else
        {
            if (!CopyFileW(reinterpret_cast<PCWSTR>(childPath.GetBuffer()), reinterpret_cast<PCWSTR>(destChildPath.GetBuffer()), TRUE))
            {
                dwRet = GetLastError();
                goto done;
            }
        }
    nextFile:;
    } while (FindNextFile(hFindFile, &findData));

done:
    if (hFindFile != INVALID_HANDLE_VALUE)
    {
        FindClose(hFindFile);
    }

    return dwRet;
}

HRESULT
FileBasedTest::CopyDirectory(_In_z_ PCWSTR pSrcDir, _In_z_ PCWSTR pDestDir)
{
    if (!pSrcDir || !*pSrcDir || !pDestDir || !*pDestDir)
    {
        return E_INVALIDARG;
    }

    if (!SetupDirectory(pDestDir))
    {
        return E_FAIL;
    }
    return (CopyDirectoryContents(pSrcDir, pDestDir) == ERROR_SUCCESS) ? S_OK : E_FAIL;
}

bool FileBasedTest::SetupClassFolders(_In_z_ PCWSTR pName, _In_opt_z_ PCWSTR pSubFolder, _In_ WellKnownFolder runFrom)
{
    bool ok = true;

    m_runFrom = runFrom;
    m_pTestClassName = pName;
    m_pClassDataSubfolder = pSubFolder;

    ok = GetTestDataDirectory(m_pClassDataSubfolder, m_testDataPath) &&
         SetupTestOutputDirectory(m_pTestClassName, nullptr, m_classOutputPath);

    if (ok && (m_runFrom != Current))
    {
        PCWSTR pRunFrom = reinterpret_cast<PCWSTR>(((m_runFrom == Source) ? m_testDataPath.GetBuffer() : m_classOutputPath.GetBuffer()));

        ok = GetCurrentDirectoryW(MAX_PATH, m_originalDir) && (SetCurrentDirectoryW(pRunFrom) != 0);
    }
    return ok;
}

bool FileBasedTest::SetupTestMethodOutputFolder(_In_z_ PCWSTR pTestMethodName)
{
    m_pTestMethodName = nullptr;
    if (!SetupTestOutputDirectory(m_pTestClassName, pTestMethodName, m_methodOutputPath))
    {
        String tmp;
        Log::Error(tmp.Format(L"Couldn't set up output directory for %s::%s", m_pTestClassName, pTestMethodName));
        return false;
    }
    m_pTestMethodName = pTestMethodName;
    return true;
}

bool FileBasedTest::TryCleanupTestMethodOutputFolder()
{
    if (m_pTestMethodName != nullptr)
    {
        m_pTestMethodName = nullptr;
        if (!CleanupTestOutputDirectory(m_methodOutputPath))
        {
            String tmp;
            Log::Error(tmp.Format(L"Couldn't clean up output directory %s", static_cast<PCWSTR>(m_methodOutputPath)));
            return false;
        }
    }
    return true;
}

bool FileBasedTest::CleanupClassFolders()
{
    bool ok = true;
    if (m_runFrom != Current)
    {
        ok = (SetCurrentDirectoryW(m_originalDir) != 0);
    }
    return CleanupTestOutputDirectory(m_classOutputPath) && ok;
}

PCWSTR
FileBasedTest::GetTestDataPath() { return reinterpret_cast<PCWSTR>(m_testDataPath.GetBuffer()); }

PCWSTR
FileBasedTest::GetTestOutputPath()
{
    return ((m_pTestMethodName != nullptr) ? static_cast<PCWSTR>(m_methodOutputPath) : static_cast<PCWSTR>(m_classOutputPath));
}

bool FileBasedTest::CreateOutputFile(_In_z_ PCWSTR pFileName, _Out_ HANDLE* pHandleOut)
{
    if (pHandleOut != nullptr)
    {
        String tmp;
        PCWSTR pPath = GetOutputFilePath(pFileName, tmp);
        *pHandleOut = CreateFile(pPath, (GENERIC_READ | GENERIC_WRITE), 0, nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);
        return ((*pHandleOut) != INVALID_HANDLE_VALUE);
    }
    return false;
}

PCWSTR
FileBasedTest::GetDataFilePath(_In_z_ PCWSTR pFileName, _Inout_ WEX::Common::String& path)
{
    path = m_testDataPath + "\\" + pFileName;
    return reinterpret_cast<PCWSTR>(path.GetBuffer());
}

PCWSTR
FileBasedTest::GetOutputFilePath(_In_z_ PCWSTR pFileName, _Inout_ WEX::Common::String& path)
{
    if (m_pTestMethodName != nullptr)
    {
        path = m_methodOutputPath + "\\" + pFileName;
    }
    else
    {
        path = m_classOutputPath + "\\" + pFileName;
    }
    return reinterpret_cast<PCWSTR>(path.GetBuffer());
}

PCWSTR
FileBasedTest::GetOutputLongFilePath(_In_z_ PCWSTR pFileName, _Inout_ WEX::Common::String& path)
{
    WEX::Common::String tempPath;
    path += MrmWindowsCoreConstDefs::LongFilePathPrefix;
    path += GetOutputFilePath(pFileName, tempPath);
    return reinterpret_cast<PCWSTR>(path.GetBuffer());
}

HRESULT
FileBasedTest::CopyTestData(_In_z_ PCWSTR pSrcDirName, _In_z_ PCWSTR pDestSubDir)
{
    WEX::Common::String srcPath;
    WEX::Common::String destPath;

    PCWSTR pFullSrcPath = (pSrcDirName ? GetDataFilePath(pSrcDirName, srcPath) : GetTestDataPath());
    PCWSTR pFullDestPath = (pDestSubDir ? GetOutputFilePath(pDestSubDir, destPath) : GetTestOutputPath());

    return CopyDirectory(pFullSrcPath, pFullDestPath);
}

}; // namespace UnitTests
