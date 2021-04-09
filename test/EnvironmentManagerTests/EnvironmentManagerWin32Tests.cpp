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
        EnvironmentManager environmentManager = EnvironmentManager::GetForProcess();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentManager.GetEnvironmentVariables();

        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForProcess();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerWin32Tests::TestGetEnvironmentVariablesForUser()
    {

        EnvironmentManager environmentManager = EnvironmentManager::GetForUser();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentManager.GetEnvironmentVariables();

        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForUser();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerWin32Tests::TestGetEnvironmentVariablesForMachine()
    {
        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForMachine();

        EnvironmentManager environmentManager = EnvironmentManager::GetForMachine();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentManager.GetEnvironmentVariables();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerWin32Tests::TestGetEnvironmentVariableForProcess()
    {
        WriteProcessEV();
        EnvironmentManager environmentManager = EnvironmentManager::GetForProcess();
        winrt::hstring environmentValue = environmentManager.GetEnvironmentVariable(c_evKeyName);

        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), environmentValue);
    }

    void EnvironmentManagerWin32Tests::TestGetEnvironmentVariableForUser()
    {
        WriteUserEV();
        EnvironmentManager environmentManager = EnvironmentManager::GetForUser();
        winrt::hstring environmentValue = environmentManager.GetEnvironmentVariable(c_evKeyName);

        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), environmentValue);

        RemoveUserEV();
    }

    void EnvironmentManagerWin32Tests::TestGetEnvironmentVariableForMachine()
    {
        EnvironmentManager environmentManager = EnvironmentManager::GetForMachine();
        winrt::hstring environmentValue = environmentManager.GetEnvironmentVariable(c_evKeyName);

        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), environmentValue);
    }

    void EnvironmentManagerWin32Tests::TestSetEnvironmentVariableForProcess()
    {
        EnvironmentManager environmentManager = EnvironmentManager::GetForProcess();
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName, c_evValueName));

        std::wstring writtenEV = GetEnvironmentVariableForProcess(c_evKeyName);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), writtenEV);

        // Update the environment variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName, c_evValueName2));
        writtenEV = GetEnvironmentVariableForProcess(c_evKeyName);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName2), writtenEV);


        // Remove the value
        // setting the value to empty is the same as deleting the variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName, L""));
        VERIFY_ARE_EQUAL(0, ::GetEnvironmentVariable(c_evKeyName, nullptr, 0));
    }

    void EnvironmentManagerWin32Tests::TestSetEnvironmentVariableForUser()
    {
        EnvironmentManager environmentManager = EnvironmentManager::GetForUser();
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName, c_evValueName));

        std::wstring writtenEV = GetEnvironmentVariableForUser(c_evKeyName);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), writtenEV);

        // Update the environment variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName, c_evValueName2));
        writtenEV = GetEnvironmentVariableForUser(c_evKeyName);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName2), writtenEV);


        // Remove the value
        // setting the value to empty is the same as deleting the variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName, L""));
        VERIFY_ARE_EQUAL(L"", GetEnvironmentVariableForUser(c_evKeyName));
    }

    void EnvironmentManagerWin32Tests::TestSetEnvironmentVariableForMachine()
    {
        EnvironmentManager environmentManager = EnvironmentManager::GetForMachine();

        if (!IsElevated())
        {
            VERIFY_THROWS(environmentManager.SetEnvironmentVariable(c_evKeyName, c_evValueName), winrt::hresult_access_denied);
            return;
        }

        WriteMachineEV();
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName, c_evValueName));

        std::wstring writtenEV = GetEnvironmentVariableForMachine(c_evKeyName);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), writtenEV);

        // Update the environment variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName, c_evValueName2));
        writtenEV = GetEnvironmentVariableForMachine(c_evKeyName);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName2), writtenEV);


        // Remove the value
        // setting the value to empty is the same as deleting the variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName, L""));
        VERIFY_ARE_EQUAL(L"", GetEnvironmentVariableForMachine(c_evKeyName));

    }

    void EnvironmentManagerWin32Tests::TestAppendToPathForProcess()
    {
        std::wstring pathToRestore = GetEnvironmentVariableForProcess(c_pathName);
        std::wstring pathToManipulate(pathToRestore);
        EnvironmentManager environmentManager = EnvironmentManager::GetForProcess();

        VERIFY_NO_THROW(environmentManager.AppendToPath(c_evValueName));

        // Current path should have the semi-colon
        std::wstring currentPath = GetEnvironmentVariableForProcess(c_pathName);
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L";";
        }

        pathToManipulate += c_evValueName;
        pathToManipulate += L";";

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        RestoreProcessPath(pathToRestore);
    }

    void EnvironmentManagerWin32Tests::TestAppendToPathForUser()
    {
        std::wstring pathToRestore = GetEnvironmentVariableForUser(c_pathName);
        std::wstring pathToManipulate(pathToRestore);
        EnvironmentManager environmentManager = EnvironmentManager::GetForUser();

        VERIFY_NO_THROW(environmentManager.AppendToPath(c_evValueName));

        // Current path should have the semi-colon
        std::wstring currentPath = GetEnvironmentVariableForUser(c_pathName);
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L";";
        }

        pathToManipulate += c_evValueName;
        pathToManipulate += L";";

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        RestoreUserPath(pathToRestore);
    }

    void EnvironmentManagerWin32Tests::TestAppendToPathForMachine()
    {
        std::wstring pathToRestore = GetEnvironmentVariableForMachine(c_pathName);
        std::wstring pathToManipulate(pathToRestore);
        EnvironmentManager environmentManager = EnvironmentManager::GetForMachine();

        if (!IsElevated())
        {
            VERIFY_THROWS(environmentManager.AppendToPath(c_evValueName), winrt::hresult_access_denied);
            return;
        }

        VERIFY_NO_THROW(environmentManager.AppendToPath(c_evValueName));

        // Current path should have the semi-colon
        std::wstring currentPath = GetEnvironmentVariableForMachine(c_pathName);
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L";";
        }

        pathToManipulate += c_evValueName;
        pathToManipulate += L";";;

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        RestoreMachinePath(pathToRestore);
    }

    void EnvironmentManagerWin32Tests::TestRemoveFromPathForProcess()
    {
        // Get the PATH for Process.  Don't append any semi-colon
        std::wstring originalPath = GetEnvironmentVariableForProcess(c_pathName);
        std::wstring pathToRestore(originalPath);
        std::wstring pathToManipulate(originalPath);
        EnvironmentManager environmentManager = EnvironmentManager::GetForProcess();

        // This will append c_evValueName to the path with a semi-colon.
        VERIFY_NO_THROW(environmentManager.AppendToPath(c_evValueName));
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L';';
        }

        pathToManipulate += c_evValueName;
        pathToManipulate += L";";

        originalPath = GetEnvironmentVariableForProcess(c_pathName);

        VERIFY_ARE_EQUAL(originalPath, pathToManipulate);

        std::wstring pathPart(originalPath, 0, originalPath.find(L';') + 1);
        environmentManager.RemoveFromPath(pathPart);
        originalPath = GetEnvironmentVariableForProcess(c_pathName);

        pathToManipulate.erase(pathToManipulate.rfind(pathPart), pathPart.length());

        VERIFY_ARE_EQUAL(originalPath, pathToManipulate);

        VERIFY_NO_THROW(environmentManager.RemoveFromPath(L"I do not exist"));

        VERIFY_ARE_EQUAL(originalPath, pathToManipulate);

        RestoreProcessPath(pathToRestore);
    }

    void EnvironmentManagerWin32Tests::TestRemoveFromPathForUser()
    {
        // Get the PATH for Process.  Don't append any semi-colon
        std::wstring originalPath = GetEnvironmentVariableForUser(c_pathName);
        std::wstring pathToRestore(originalPath);
        std::wstring pathToManipulate(originalPath);
        EnvironmentManager environmentManager = EnvironmentManager::GetForUser();

        // This will append c_evValueName to the path with a semi-colon.
        VERIFY_NO_THROW(environmentManager.AppendToPath(c_evValueName));
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L';';
        }

        pathToManipulate += c_evValueName;
        pathToManipulate += L";";

        originalPath = GetEnvironmentVariableForUser(c_pathName);

        VERIFY_ARE_EQUAL(originalPath, pathToManipulate);

        std::wstring pathPart(originalPath, 0, originalPath.find(L';') + 1);
        environmentManager.RemoveFromPath(pathPart);
        originalPath = GetEnvironmentVariableForUser(c_pathName);

        pathToManipulate.erase(pathToManipulate.rfind(pathPart), pathPart.length());

        VERIFY_ARE_EQUAL(originalPath, pathToManipulate);

        VERIFY_NO_THROW(environmentManager.RemoveFromPath(L"I do not exist"));

        VERIFY_ARE_EQUAL(originalPath, pathToManipulate);

        RestoreUserPath(pathToRestore);
    }

    void EnvironmentManagerWin32Tests::TestRemoveFromPathForMachine()
    {
        // Get the PATH for Process.  Don't append any semi-colon
        std::wstring originalPath = GetEnvironmentVariableForMachine(c_pathName);
        std::wstring pathToRestore(originalPath);
        std::wstring pathToManipulate(originalPath);
        EnvironmentManager environmentManager = EnvironmentManager::GetForMachine();

        if (!IsElevated())
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

        originalPath = GetEnvironmentVariableForMachine(c_pathName);

        VERIFY_ARE_EQUAL(originalPath, pathToManipulate);

        std::wstring pathPart(originalPath, 0, originalPath.find(L';') + 1);
        environmentManager.RemoveFromPath(pathPart);
        originalPath = GetEnvironmentVariableForMachine(c_pathName);

        pathToManipulate.erase(pathToManipulate.rfind(pathPart), pathPart.length());

        VERIFY_ARE_EQUAL(originalPath, pathToManipulate);

        VERIFY_NO_THROW(environmentManager.RemoveFromPath(L"I do not exist"));

        VERIFY_ARE_EQUAL(originalPath, pathToManipulate);

        RestoreMachinePath(pathToRestore);
    }
}
