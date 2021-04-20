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

        if (ValidateTokenRunLevel(ProcessRunLevel::LegacyLowIL) || ValidateTokenRunLevel(ProcessRunLevel::UntrustedIL))
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

        if (!ValidateTokenRunLevel(ProcessRunLevel::Elevated))
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
        // Store PATH so it can be restored
        std::wstring pathToRestore{ GetEnvironmentVariableForProcess(c_pathName) };

        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ pathToRestore };

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

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_THROWS(environmentManager.AppendToPath(L""), winrt::hresult_invalid_argument);

        RestoreProcessPath(pathToRestore);
    }

    void EnvironmentManagerWin32Tests::TestAppendToPathForUser()
    {
        // Store PATH so it can be restored
        std::wstring pathToRestore{ GetEnvironmentVariableForUser(c_pathName) };

        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ pathToRestore };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };

        if (ValidateTokenRunLevel(ProcessRunLevel::LegacyLowIL) || ValidateTokenRunLevel(ProcessRunLevel::UntrustedIL))
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

        RestoreUserPath(pathToRestore);
    }

    void EnvironmentManagerWin32Tests::TestAppendToPathForMachine()
    {
        // Store PATH so it can be restored
        std::wstring pathToRestore{ GetEnvironmentVariableForMachine(c_pathName) };

        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate(pathToRestore);

        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };

        if (!ValidateTokenRunLevel(ProcessRunLevel::Elevated))
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

        RestoreMachinePath(pathToRestore);
    }

    void EnvironmentManagerWin32Tests::TestRemoveFromPathForProcess()
    {
        // Store PATH so it can be restored
        std::wstring pathToRestore{ GetEnvironmentVariableForProcess(c_pathName) };

        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate(pathToRestore);

        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };

        // This will append c_evValueName to the path with a semi-colon.
        VERIFY_NO_THROW(environmentManager.AppendToPath(c_evValueName));
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L';';
        }

        pathToManipulate += c_evValueName;
        pathToManipulate += L";";

        std::wstring currentPath{ GetEnvironmentVariableForProcess(c_pathName) };

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        std::wstring pathPart{ currentPath, 0, currentPath.find(L';') + 1 };
        environmentManager.RemoveFromPath(pathPart);
        currentPath = GetEnvironmentVariableForProcess(c_pathName);

        pathToManipulate.erase(pathToManipulate.rfind(pathPart), pathPart.length());

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_NO_THROW(environmentManager.RemoveFromPath(L"I do not exist"));

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_THROWS(environmentManager.AppendToPath(L""), winrt::hresult_invalid_argument);

        RestoreProcessPath(pathToRestore);
    }

    void EnvironmentManagerWin32Tests::TestRemoveFromPathForUser()
    {
        // Store PATH so it can be restored
        std::wstring pathToRestore{ GetEnvironmentVariableForUser(c_pathName) };

        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate(pathToRestore);

        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };

        if (ValidateTokenRunLevel(ProcessRunLevel::LegacyLowIL) || ValidateTokenRunLevel(ProcessRunLevel::UntrustedIL))
        {
            VERIFY_THROWS(environmentManager.AppendToPath(c_evValueName), winrt::hresult_access_denied);
            return;
        }

        // This will append c_evValueName to the path with a semi-colon.
        VERIFY_NO_THROW(environmentManager.AppendToPath(c_evValueName));
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L';';
        }

        pathToManipulate += c_evValueName;
        pathToManipulate += L";";

        std::wstring currentPath{ GetEnvironmentVariableForUser(c_pathName) };

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        std::wstring pathPart{ currentPath, 0, currentPath.find(L';') + 1 };
        environmentManager.RemoveFromPath(pathPart);
        currentPath = GetEnvironmentVariableForUser(c_pathName);

        pathToManipulate.erase(pathToManipulate.rfind(pathPart), pathPart.length());

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_NO_THROW(environmentManager.RemoveFromPath(L"I do not exist"));

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_THROWS(environmentManager.AppendToPath(L""), winrt::hresult_invalid_argument);

        RestoreUserPath(pathToRestore);
    }

    void EnvironmentManagerWin32Tests::TestRemoveFromPathForMachine()
    {        
        // Store PATH so it can be restored
        std::wstring pathToRestore{ GetEnvironmentVariableForMachine(c_pathName) };

        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate(pathToRestore);

        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };

        if (!ValidateTokenRunLevel(ProcessRunLevel::Elevated))
        {
            VERIFY_THROWS(environmentManager.AppendToPath(c_evValueName), winrt::hresult_access_denied);
            return;
        }


        // This will append c_evValueName to the path with a semi-colon.
        VERIFY_NO_THROW(environmentManager.AppendToPath(c_evValueName));
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L';';
        }

        pathToManipulate += c_evValueName;
        pathToManipulate += L";";

        std::wstring currentPath{ GetEnvironmentVariableForMachine(c_pathName) };

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        std::wstring pathPart{ currentPath, 0, currentPath.find(L';') + 1 };
        environmentManager.RemoveFromPath(pathPart);
        currentPath = GetEnvironmentVariableForMachine(c_pathName);

        pathToManipulate.erase(pathToManipulate.rfind(pathPart), pathPart.length());

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_NO_THROW(environmentManager.RemoveFromPath(L"I do not exist"));

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_THROWS(environmentManager.AppendToPath(L""), winrt::hresult_invalid_argument);

        RestoreMachinePath(pathToRestore);
    }
}
