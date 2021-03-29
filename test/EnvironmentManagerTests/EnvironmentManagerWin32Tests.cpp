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
        EnvironmentManager environmentmanager = EnvironmentManager::GetForProcess();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentmanager.GetEnvironmentVariables();

        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForProcess();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerWin32Tests::TestGetEnvironmentVariablesForUser()
    {

        EnvironmentManager environmentmanager = EnvironmentManager::GetForUser();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentmanager.GetEnvironmentVariables();

        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForUser();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerWin32Tests::TestGetEnvironmentVariablesForMachine()
    {
        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForMachine();

        EnvironmentManager environmentmanager = EnvironmentManager::GetForMachine();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentmanager.GetEnvironmentVariables();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerWin32Tests::TestGetEnvironmentVariableForProcess()
    {
        EnvironmentManager environmentManager = EnvironmentManager::GetForProcess();
        winrt::hstring environmentValue = environmentManager.GetEnvironmentVariable(c_evKeyName);

        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), environmentValue);
    }

    void EnvironmentManagerWin32Tests::TestGetEnvironmentVariableForUser()
    {
        EnvironmentManager environmentManager = EnvironmentManager::GetForUser();
        winrt::hstring environmentValue = environmentManager.GetEnvironmentVariable(c_evKeyName);

        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), environmentValue);
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
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName2, c_evValueName));

        std::wstring writtenEV = GetEnvironmentVariableForProcess(c_evKeyName2);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), writtenEV);

        // Update the environment variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName2, c_evValueName2));
        writtenEV = GetEnvironmentVariableForProcess(c_evKeyName2);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName2), writtenEV);


        // Remove the value
        // setting the value to empty is the same as deleting the variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName2, L""));
        VERIFY_ARE_EQUAL(0, ::GetEnvironmentVariable(c_evKeyName2, nullptr, 0));
        VERIFY_ARE_EQUAL(ERROR_ENVVAR_NOT_FOUND, GetLastError());
    }

    void EnvironmentManagerWin32Tests::TestSetEnvironmentVariableForUser()
    {
        EnvironmentManager environmentManager = EnvironmentManager::GetForUser();
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName2, c_evValueName));

        std::wstring writtenEV = GetEnvironmentVariableForUser(c_evKeyName2);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), writtenEV);

        // Update the environment variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName2, c_evValueName2));
        writtenEV = GetEnvironmentVariableForUser(c_evKeyName2);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName2), writtenEV);


        // Remove the value
        // setting the value to empty is the same as deleting the variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName2, L""));
        VERIFY_ARE_EQUAL(L"", GetEnvironmentVariableForUser(c_evKeyName2));
        VERIFY_ARE_EQUAL(ERROR_ENVVAR_NOT_FOUND, GetLastError());
    }

    void EnvironmentManagerWin32Tests::TestSetEnvironmentVariableForMachine()
    {
        EnvironmentManager environmentManager = EnvironmentManager::GetForMachine();
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName2, c_evValueName));

        std::wstring writtenEV = GetEnvironmentVariableForMachine(c_evKeyName2);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), writtenEV);

        // Update the environment variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName2, c_evValueName2));
        writtenEV = GetEnvironmentVariableForMachine(c_evKeyName2);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName2), writtenEV);


        // Remove the value
        // setting the value to empty is the same as deleting the variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_evKeyName2, L""));
        VERIFY_ARE_EQUAL(L"", GetEnvironmentVariableForMachine(c_evKeyName2));
        VERIFY_ARE_EQUAL(ERROR_ENVVAR_NOT_FOUND, GetLastError());
    }

    void EnvironmentManagerWin32Tests::TestAppendToPathForProcess()
    {
        std::wstring originalPath = GetEnvironmentVariableForProcess(c_pathName);
        EnvironmentManager environmentManager = EnvironmentManager::GetForProcess();
        VERIFY_NO_THROW(environmentManager.AppendToPath(c_evValueName));

        std::wstring alteredPath = GetEnvironmentVariableForProcess(c_pathName);

        VERIFY_ARE_EQUAL(originalPath.append(c_evValueName).append(L";"), alteredPath);
    }

    void EnvironmentManagerWin32Tests::TestAppendToPathForUser()
    {
        std::wstring originalPath = GetEnvironmentVariableForUser(c_pathName);
        EnvironmentManager environmentManager = EnvironmentManager::GetForUser();
        VERIFY_NO_THROW(environmentManager.AppendToPath(c_evValueName));

        std::wstring alteredPath = GetEnvironmentVariableForUser(c_pathName);

        RestoreUserPath(originalPath);

        VERIFY_ARE_EQUAL(originalPath.append(c_evValueName).append(L";"), alteredPath);
    }

    void EnvironmentManagerWin32Tests::TestAppendToPathForMachine()
    {
        std::wstring originalPath = GetEnvironmentVariableForMachine(c_pathName);
        EnvironmentManager environmentManager = EnvironmentManager::GetForMachine();
        VERIFY_NO_THROW(environmentManager.AppendToPath(c_evValueName));

        std::wstring alteredPath = GetEnvironmentVariableForMachine(c_pathName);

        RestoreMachinePath(originalPath);

        VERIFY_ARE_EQUAL(originalPath.append(c_evValueName).append(L";"), alteredPath);
    }
}
