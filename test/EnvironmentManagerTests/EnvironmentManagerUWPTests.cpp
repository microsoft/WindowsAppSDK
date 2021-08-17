// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "EnvironmentManagerUWPTests.h"
#include "EnvironmentVariableHelper.h"
#include "TestSetupAndTeardownHelper.h"

using namespace winrt::Microsoft::Windows;

namespace WindowsAppSDKEnvironmentManagerTests
{
    void EnvironmentManagerUWPTests::UWPTestGetForProcess()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };
        VERIFY_IS_NOT_NULL(environmentManager);
    }

    void EnvironmentManagerUWPTests::UWPTestGetForUser()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };
        VERIFY_IS_NOT_NULL(environmentManager);
    }

    void EnvironmentManagerUWPTests::UWPTestGetForMachine()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };
        VERIFY_IS_NOT_NULL(environmentManager);
    }


    void EnvironmentManagerUWPTests::UWPTestGetEnvironmentVariablesForProcess()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };
        EnvironmentVariables environmentVariablesFromWinRTAPI{ environmentManager.GetEnvironmentVariables() };

        EnvironmentVariables environmentVariablesFromWindowsAPI{ GetEnvironmentVariablesForProcess() };

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerUWPTests::UWPTestGetEnvironmentVariablesForUser()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };
        EnvironmentVariables environmentVariablesFromWinRTAPI{ environmentManager.GetEnvironmentVariables() };

        EnvironmentVariables environmentVariablesFromWindowsAPI{ GetEnvironmentVariablesForUser() };

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerUWPTests::UWPTestGetEnvironmentVariablesForMachine()
    {
        EnvironmentVariables environmentVariablesFromWindowsAPI{ GetEnvironmentVariablesForMachine() };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };
        EnvironmentVariables environmentVariablesFromWinRTAPI{ environmentManager.GetEnvironmentVariables() };

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerUWPTests::UWPTestGetEnvironmentVariableForProcess()
    {
        ProcessSetup();
        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };
        winrt::hstring environmentValue{ environmentManager.GetEnvironmentVariable(c_EvKeyName) };

        ProcessCleanup();

        VERIFY_ARE_EQUAL(std::wstring{ c_EvValueName }, environmentValue);
    }

    void EnvironmentManagerUWPTests::UWPTestGetEnvironmentVariableForUser()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };
        winrt::hstring environmentValue{ environmentManager.GetEnvironmentVariable(c_EvKeyNameForGet) };

        VERIFY_ARE_EQUAL(std::wstring{ c_EvValueName }, environmentValue);
    }

    void EnvironmentManagerUWPTests::UWPTestGetEnvironmentVariableForMachine()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };
        winrt::hstring environmentValue{ environmentManager.GetEnvironmentVariable(c_EvKeyNameForGet) };

        VERIFY_ARE_EQUAL(std::wstring{ c_EvValueName }, environmentValue);
    }


    void EnvironmentManagerUWPTests::UWPTestSetEnvironmentVariableForProcess()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_EvKeyName, c_EvValueName));

        std::wstring writtenEV = GetEnvironmentVariableForProcess(c_EvKeyName);
        VERIFY_ARE_EQUAL(std::wstring{ c_EvValueName }, writtenEV);

        // Update the environment variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_EvKeyName, c_EvValueName2));
        writtenEV = GetEnvironmentVariableForProcess(c_EvKeyName);
        VERIFY_ARE_EQUAL(std::wstring{ c_EvValueName2 }, writtenEV);


        // Remove the value
        // setting the value to empty is the same as deleting the variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_EvKeyName, L""));
        VERIFY_ARE_EQUAL(0, ::GetEnvironmentVariable(c_EvKeyName, nullptr, 0));
        VERIFY_ARE_EQUAL(ERROR_ENVVAR_NOT_FOUND, GetLastError());
    }

    void EnvironmentManagerUWPTests::UWPTestSetEnvironmentVariableForUser()
    {
        EnvironmentManager environmentMananger{ EnvironmentManager::GetForUser() };
        VERIFY_THROWS(environmentMananger.SetEnvironmentVariable(c_EvKeyName, c_EvValueName), winrt::hresult_access_denied);
    }

    void EnvironmentManagerUWPTests::UWPTestSetEnvironmentVariableForMachine()
    {
        EnvironmentManager environmentMananger{ EnvironmentManager::GetForMachine() };
        VERIFY_THROWS(environmentMananger.SetEnvironmentVariable(c_EvKeyName, c_EvValueName), winrt::hresult_access_denied);
    }

    void EnvironmentManagerUWPTests::UWPTestAppendToPathForProcess()
    {
        ProcessSetup();

        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForProcess(c_PathName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };

        VERIFY_NO_THROW(environmentManager.AppendToPath(c_EvValueName));

        // Current path should have the semi-colon
        std::wstring currentPath{ GetEnvironmentVariableForProcess(c_PathName) };
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L";";
        }

        pathToManipulate += c_EvValueName;
        pathToManipulate += L";";

        ProcessCleanup();

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_THROWS(environmentManager.AppendToPath(L""), winrt::hresult_invalid_argument);
    }

    void EnvironmentManagerUWPTests::UWPTestAppendToPathForUser()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };
        VERIFY_THROWS(environmentManager.AppendToPath(c_EvValueName), winrt::hresult_access_denied);
    }

    void EnvironmentManagerUWPTests::UWPTestAppendToPathForMachine()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };
        VERIFY_THROWS(environmentManager.AppendToPath(c_EvValueName), winrt::hresult_access_denied);
    }

    void EnvironmentManagerUWPTests::UWPTestRemoveFromPathForProcess()
    {
        ProcessSetup();

        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForProcess(c_PathName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };

        environmentManager.RemoveFromPath(c_EvValueName);

        std::wstring currentPath{ GetEnvironmentVariableForProcess(c_PathName) };

        ProcessCleanup();

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_NO_THROW(environmentManager.RemoveFromPath(L"I do not exist"));

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

    }

    void EnvironmentManagerUWPTests::UWPTestRemoveFromPathForUser()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };
        VERIFY_THROWS(environmentManager.AppendToPath(c_EvValueName), winrt::hresult_access_denied);
    }

    void EnvironmentManagerUWPTests::UWPTestRemoveFromPathForMachine()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };
        VERIFY_THROWS(environmentManager.AppendToPath(c_EvValueName), winrt::hresult_access_denied);
    }

    void EnvironmentManagerUWPTests::UWPTestAppendToPathExtForProcess()
    {
        ProcessSetup();
        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForProcess(c_PathExtName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };

        VERIFY_NO_THROW(environmentManager.AddExecutableFileExtension(c_EvValueName));

        // Current path should have the semi-colon
        std::wstring currentPath{ GetEnvironmentVariableForProcess(c_PathExtName) };
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L";";
        }

        pathToManipulate += c_EvValueName;
        pathToManipulate += L";";

        ProcessCleanup();
        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_THROWS(environmentManager.AddExecutableFileExtension(L""), winrt::hresult_invalid_argument);
    }

    void EnvironmentManagerUWPTests::UWPTestAppendToPathExtForUser()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };

        VERIFY_THROWS(environmentManager.AddExecutableFileExtension(c_EvValueName), winrt::hresult_access_denied);
    }

    void EnvironmentManagerUWPTests::UWPTestAppendToPathExtForMachine()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };

        VERIFY_THROWS(environmentManager.AddExecutableFileExtension(c_EvValueName), winrt::hresult_access_denied);
    }

    void EnvironmentManagerUWPTests::UWPTestRemoveFromPathExtForProcess()
    {
        ProcessSetup();

        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForProcess(c_PathExtName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };

        InjectIntoPath(true, false, c_EvValueName, 5);
        environmentManager.RemoveExecutableFileExtension(c_EvValueName);

        std::wstring currentPath{ GetEnvironmentVariableForProcess(c_PathExtName) };

        ProcessCleanup();

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_NO_THROW(environmentManager.RemoveExecutableFileExtension(L"I do not exist"));

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);
    }

    void EnvironmentManagerUWPTests::UWPTestRemoveFromPathExtForUser()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };
        std::wstring pathPart{ GetSecondValueFromPathExt(false, true) };
        VERIFY_THROWS(environmentManager.RemoveExecutableFileExtension(pathPart), winrt::hresult_access_denied);
    }

    void EnvironmentManagerUWPTests::UWPTestRemoveFromPathExtForMachine()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };
        std::wstring pathPart{ GetSecondValueFromPathExt(false, false) };
        VERIFY_THROWS(environmentManager.RemoveExecutableFileExtension(pathPart), winrt::hresult_access_denied);
    }
}
