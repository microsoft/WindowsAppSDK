// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "mrm/BaseInternal.h"

using namespace Microsoft::Resources;

namespace UnitTests
{

class FileBasedTest
{
public:
    enum WellKnownFolder
    {
        Current = 0,
        Source = 1,
        Output = 2
    };

protected:
    WellKnownFolder m_runFrom;
    PCWSTR m_pTestClassName;
    PCWSTR m_pTestMethodName;

    PCWSTR m_pClassDataSubfolder;

    WEX::Common::String m_testDataPath;
    WEX::Common::String m_classOutputPath;
    WEX::Common::String m_methodOutputPath;

    WCHAR m_originalDir[MAX_PATH];

public:
    FileBasedTest();

    static DWORD CreateDirectoryHierarchy(_In_ const WEX::Common::String& path);

    static DWORD DeleteDirectoryContents(_In_ const WEX::Common::String& path);

    static DWORD DeleteDirectoryAndContents(_In_ const WEX::Common::String& path);

    static bool GetTestDataDirectory(_In_opt_z_ PCWSTR pSubfolder, _Inout_ WEX::Common::String& dataDirPath);

    static bool GetTestDataDirectory(_Inout_ WEX::Common::String& dataDirPath);

    static bool GetTestOutputDirectory(
        _In_opt_z_ PCWSTR pTestClassName,
        _In_opt_z_ PCWSTR pTestName,
        _Inout_ WEX::Common::String& testOutputPath);

    static bool SetupDirectory(_In_z_ PCWSTR pPath);

    static bool SetupTestOutputDirectory(
        _In_z_ PCWSTR pTestClassName,
        _In_opt_z_ PCWSTR pTestName,
        _Inout_ WEX::Common::String& testOutputPath);

    static bool CleanupTestOutputDirectory(_In_ const WEX::Common::String& testOutputPath);

    static DWORD CopyDirectoryContents(_In_z_ PCWSTR pSrcDir, _In_z_ PCWSTR pDestDir);

    static HRESULT CopyDirectory(_In_z_ PCWSTR pSrcDir, _In_z_ PCWSTR pDestDir);

    bool SetupClassFolders(_In_z_ PCWSTR pName, _In_opt_z_ PCWSTR pSubFolder = nullptr, _In_ WellKnownFolder runFrom = Current);

    bool SetupTestMethodOutputFolder(_In_z_ PCWSTR pTestMethodName);

    bool TryCleanupTestMethodOutputFolder();

    bool CleanupClassFolders();

    PCWSTR GetTestDataPath();
    PCWSTR GetTestOutputPath();

    bool CreateOutputFile(_In_z_ PCWSTR pFileName, _Out_ HANDLE* pHandleOut);

    PCWSTR GetDataFilePath(_In_z_ PCWSTR pFileName, _Inout_ WEX::Common::String& path);

    PCWSTR GetOutputFilePath(_In_z_ PCWSTR pFileName, _Inout_ WEX::Common::String& path);

    PCWSTR GetOutputLongFilePath(_In_z_ PCWSTR pFileName, _Inout_ WEX::Common::String& path);

    HRESULT CopyTestData(_In_z_ PCWSTR pSrcDirName, _In_z_ PCWSTR pDestSubDir);
};

}; // namespace UnitTests
