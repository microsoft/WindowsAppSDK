// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "EnvironmentManagerWin32Tests.h"
#include "EnvironmentVariableHelper.h"

using namespace winrt::Microsoft::ProjectReunion;

namespace ProjectReunionEnvironmentManagerTests
{
    void EnvironmentManagerWin32Tests::TestGetForProcess()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };
        VERIFY_IS_NOT_NULL(environmentManager);
    }

    void EnvironmentManagerWin32Tests::TestGetForUser()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };
        VERIFY_IS_NOT_NULL(environmentManager);
    }

    void EnvironmentManagerWin32Tests::TestGetForMachine()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };
        VERIFY_IS_NOT_NULL(environmentManager);
    }

    void EnvironmentManagerWin32Tests::TestGetEnvironmentVariablesForProcess()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };
        EnvironmentVariables environmentVariablesFromWinRTAPI{ environmentManager.GetEnvironmentVariables() };

        EnvironmentVariables environmentVariablesFromWindowsAPI{ GetEnvironmentVariablesForProcess() };

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerWin32Tests::TestGetEnvironmentVariablesForUser()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };
        EnvironmentVariables environmentVariablesFromWinRTAPI{ environmentManager.GetEnvironmentVariables() };

        EnvironmentVariables environmentVariablesFromWindowsAPI{ GetEnvironmentVariablesForUser() };

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerWin32Tests::TestGetEnvironmentVariablesForMachine()
    {
        EnvironmentVariables environmentVariablesFromWindowsAPI{ GetEnvironmentVariablesForMachine() };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };
        EnvironmentVariables environmentVariablesFromWinRTAPI{ environmentManager.GetEnvironmentVariables() };

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerWin32Tests::TestGetEnvironmentVariableForProcess()
    {
        ProcessSetup();

        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };
        winrt::hstring environmentValue{ environmentManager.GetEnvironmentVariable(c_evKeyName) };

        ProcessCleanup();

        VERIFY_ARE_EQUAL(std::wstring{ c_evValueName }, environmentValue);
    }

    void EnvironmentManagerWin32Tests::TestGetEnvironmentVariableForUser()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };
        winrt::hstring environmentValue{ environmentManager.GetEnvironmentVariable(c_evKeyNameForGet) };

        VERIFY_ARE_EQUAL(std::wstring{ c_evValueName }, environmentValue);
    }

    void EnvironmentManagerWin32Tests::TestGetEnvironmentVariableForMachine()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };
        winrt::hstring environmentValue{ environmentManager.GetEnvironmentVariable(c_evKeyNameForGet) };

        VERIFY_ARE_EQUAL(std::wstring{ c_evValueName }, environmentValue);
    }

    void EnvironmentManagerWin32Tests::TestSetEnvironmentVariableForProcess()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName, c_evValueName));

        std::wstring writtenEV = GetEnvironmentVariableForProcess(c_evKeyName);
        VERIFY_ARE_EQUAL(std::wstring{ c_evValueName }, writtenEV);

        // Update the environment variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName, c_evValueName2));
        writtenEV = GetEnvironmentVariableForProcess(c_evKeyName);
        VERIFY_ARE_EQUAL(std::wstring{ c_evValueName2 }, writtenEV);


        // Remove the value
        // setting the value to empty is the same as deleting the variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName, L""));
        VERIFY_ARE_EQUAL(0, ::GetEnvironmentVariable(c_evKeyName, nullptr, 0));
    }

    void EnvironmentManagerWin32Tests::TestSetEnvironmentVariableForUser()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };

        if (!IsILAtOrAbove(ProcessRunLevel::Standard))
        {
            VERIFY_THROWS(environmentManager.SetEnvironmentVariable(c_evKeyName, c_evValueName), winrt::hresult_access_denied);
            return;
        }

        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName, c_evValueName));

        std::wstring writtenEV = GetEnvironmentVariableForUser(c_evKeyName);
        VERIFY_ARE_EQUAL(std::wstring{ c_evValueName }, writtenEV);

        // Update the environment variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName, c_evValueName2));
        writtenEV = GetEnvironmentVariableForUser(c_evKeyName);
        VERIFY_ARE_EQUAL(std::wstring{ c_evValueName2 }, writtenEV);


        // Remove the value
        // setting the value to empty is the same as deleting the variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName, L""));
        VERIFY_ARE_EQUAL(L"", GetEnvironmentVariableForUser(c_evKeyName));
    }

    void EnvironmentManagerWin32Tests::TestSetEnvironmentVariableForMachine()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };

        if (!IsILAtOrAbove(ProcessRunLevel::Elevated))
        {
            VERIFY_THROWS(environmentManager.SetEnvironmentVariable(c_evKeyName, c_evValueName), winrt::hresult_access_denied);
            return;
        }

        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName, c_evValueName));

        std::wstring writtenEV{ GetEnvironmentVariableForMachine(c_evKeyName) };
        VERIFY_ARE_EQUAL(std::wstring{ c_evValueName }, writtenEV);

        // Update the environment variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName, c_evValueName2));
        writtenEV = GetEnvironmentVariableForMachine(c_evKeyName);
        VERIFY_ARE_EQUAL(std::wstring{ c_evValueName2 }, writtenEV);


        // Remove the value
        // setting the value to empty is the same as deleting the variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName, L""));
        VERIFY_ARE_EQUAL(L"", GetEnvironmentVariableForMachine(c_evKeyName));

    }

    void EnvironmentManagerWin32Tests::TestAppendToPathForProcess()
    {
        ProcessSetup();
        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForProcess(c_pathName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };

        VERIFY_NO_THROW(environmentManager.AppendToPath(c_evValueName));

        // Current path should have the semi-colon
        std::wstring currentPath{ GetEnvironmentVariableForProcess(c_pathName) };
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L";";
        }

        pathToManipulate += c_evValueName;
        pathToManipulate += L";";

        ProcessCleanup();

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_THROWS(environmentManager.AppendToPath(L""), winrt::hresult_invalid_argument);
    }

    void EnvironmentManagerWin32Tests::TestAppendToPathForUser()
    {
        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForUser(c_pathName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };

        if (!IsILAtOrAbove(ProcessRunLevel::Standard))
        {
            VERIFY_THROWS(environmentManager.AppendToPath(c_evValueName), winrt::hresult_access_denied);
            return;
        }

        VERIFY_NO_THROW(environmentManager.AppendToPath(c_evValueName));

        // Current path should have the semi-colon
        std::wstring currentPath{ GetEnvironmentVariableForUser(c_pathName) };
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L";";
        }

        pathToManipulate += c_evValueName;
        pathToManipulate += L";";

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_THROWS(environmentManager.AppendToPath(L""), winrt::hresult_invalid_argument);
    }

    void EnvironmentManagerWin32Tests::TestAppendToPathForMachine()
    {
        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForMachine(c_pathName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };

        if (!IsILAtOrAbove(ProcessRunLevel::Elevated))
        {
            VERIFY_THROWS(environmentManager.AppendToPath(c_evValueName), winrt::hresult_access_denied);
            return;
        }

        VERIFY_NO_THROW(environmentManager.AppendToPath(c_evValueName));

        // Current path should have the semi-colon
        std::wstring currentPath{ GetEnvironmentVariableForMachine(c_pathName) };
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L";";
        }

        pathToManipulate += c_evValueName;
        pathToManipulate += L";";;

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_THROWS(environmentManager.AppendToPath(L""), winrt::hresult_invalid_argument);
    }

    void EnvironmentManagerWin32Tests::TestRemoveFromPathForProcess()
    {
        ProcessSetup();

        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForProcess(c_pathName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };

        environmentManager.RemoveFromPath(c_evValueName);

        std::wstring currentPath{ GetEnvironmentVariableForProcess(c_pathName) };

        ProcessCleanup();

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_NO_THROW(environmentManager.RemoveFromPath(L"I do not exist"));

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);
    }

    void EnvironmentManagerWin32Tests::TestRemoveFromPathForUser()
    {
        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForUser(c_pathName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };

        if (!IsILAtOrAbove(ProcessRunLevel::LegacyLowIL))
        {
            std::wstring pathPart{ GetSecondValueFromPath(false, true) };
            VERIFY_THROWS(environmentManager.RemoveFromPath(c_evValueName), winrt::hresult_access_denied);
            return;
        }

        environmentManager.RemoveFromPath(c_evValueName);

        std::wstring currentPath{ GetEnvironmentVariableForUser(c_pathName) };

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_NO_THROW(environmentManager.RemoveFromPath(L"I do not exist"));

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);
    }

    void EnvironmentManagerWin32Tests::TestRemoveFromPathForMachine()
    {        
        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForMachine(c_pathName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };

        if (!IsILAtOrAbove(ProcessRunLevel::Elevated))
        {
            std::wstring pathPart{ GetSecondValueFromPath(false, false) };
            VERIFY_THROWS(environmentManager.RemoveFromPath(pathPart), winrt::hresult_access_denied);
            return;
        }

        environmentManager.RemoveFromPath(c_evValueName);

        std::wstring currentPath{ GetEnvironmentVariableForMachine(c_pathName) };

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_NO_THROW(environmentManager.RemoveFromPath(L"I do not exist"));

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);
    }

    void EnvironmentManagerWin32Tests::TestAppendToPathExtForProcess()
    {
        ProcessSetup();
        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForProcess(c_pathExtName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };

        VERIFY_NO_THROW(environmentManager.AddExecutableFileExtension(c_evValueName));

        // Current path should have the semi-colon
        std::wstring currentPath{ GetEnvironmentVariableForProcess(c_pathExtName) };
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L";";
        }

        pathToManipulate += c_evValueName;
        pathToManipulate += L";";

        ProcessCleanup();
        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_THROWS(environmentManager.AddExecutableFileExtension(L""), winrt::hresult_invalid_argument);
    }

    void EnvironmentManagerWin32Tests::TestAppendToPathExtForUser()
    {
        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForUser(c_pathExtName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };

        if (!IsILAtOrAbove(ProcessRunLevel::Standard))
        {
            VERIFY_THROWS(environmentManager.AddExecutableFileExtension(c_evValueName), winrt::hresult_access_denied);
            return;
        }

        VERIFY_NO_THROW(environmentManager.AddExecutableFileExtension(c_evValueName));

        // Current path should have the semi-colon
        std::wstring currentPath{ GetEnvironmentVariableForUser(c_pathExtName) };

        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L";";
        }

        pathToManipulate += c_evValueName;
        pathToManipulate += L";";

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_THROWS(environmentManager.AddExecutableFileExtension(L""), winrt::hresult_invalid_argument);
    }

    void EnvironmentManagerWin32Tests::TestAppendToPathExtForMachine()
    {
        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForMachine(c_pathExtName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };

        if (!IsILAtOrAbove(ProcessRunLevel::Elevated))
        {
            VERIFY_THROWS(environmentManager.AddExecutableFileExtension(c_evValueName), winrt::hresult_access_denied);
            return;
        }

        VERIFY_NO_THROW(environmentManager.AddExecutableFileExtension(c_evValueName));

        // Current path should have the semi-colon
        std::wstring currentPath{ GetEnvironmentVariableForMachine(c_pathExtName) };

        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L";";
        }

        pathToManipulate += c_evValueName;
        pathToManipulate += L";";

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_THROWS(environmentManager.AddExecutableFileExtension(L""), winrt::hresult_invalid_argument);
    }

    void EnvironmentManagerWin32Tests::TestRemoveFromPathExtForProcess()
    {
        ProcessSetup();

        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForProcess(c_pathExtName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };

        InjectIntoPath(true, false, c_evValueName, 5);
        environmentManager.RemoveExecutableFileExtension(c_evValueName);

        std::wstring currentPath{ GetEnvironmentVariableForProcess(c_pathExtName) };

        ProcessCleanup();

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_NO_THROW(environmentManager.RemoveExecutableFileExtension(L"I do not exist"));

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);
    }

    void EnvironmentManagerWin32Tests::TestRemoveFromPathExtForUser()
    {
        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForUser(c_pathExtName) };

        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L';';
        }

        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };

        if (!IsILAtOrAbove(ProcessRunLevel::Standard))
        {
            std::wstring pathPart{ GetSecondValueFromPathExt(false, true) };
            VERIFY_THROWS(environmentManager.RemoveExecutableFileExtension(pathPart), winrt::hresult_access_denied);
            return;
        }

        InjectIntoPathExt(false, true, c_evValueName, 5);
        environmentManager.RemoveExecutableFileExtension(c_evValueName);

        std::wstring currentPath{ GetEnvironmentVariableForUser(c_pathExtName) };

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_NO_THROW(environmentManager.RemoveExecutableFileExtension(L"I do not exist"));

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);
    }

    void EnvironmentManagerWin32Tests::TestRemoveFromPathExtForMachine()
    {
        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForMachine(c_pathExtName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };

        if (!IsILAtOrAbove(ProcessRunLevel::Elevated))
        {
            std::wstring pathPart{ GetSecondValueFromPathExt(false, false) };
            VERIFY_THROWS(environmentManager.RemoveExecutableFileExtension(pathPart), winrt::hresult_access_denied);
            return;
        }

        environmentManager.RemoveExecutableFileExtension(c_evValueName);

        std::wstring currentPath{ GetEnvironmentVariableForMachine(c_pathExtName) };

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_NO_THROW(environmentManager.RemoveExecutableFileExtension(L"I do not exist"));

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);
    }
}
