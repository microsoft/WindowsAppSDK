// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "EnvironmentManagerWin32Tests.h"
#include "EnvironmentVariableHelper.h"
#include <WindowsAppRuntime.Test.Metadata.h>
#include <WindowsAppRuntime.VersionInfo.h>
#include <WindowsAppRuntime.SelfContained.h>


using namespace winrt::Microsoft::Windows;

namespace WindowsAppSDKEnvironmentManagerTests
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

    void EnvironmentManagerWin32Tests::TestAreChangesTracked()
    {
        BEGIN_TEST_METHOD_PROPERTIES()
            TEST_METHOD_PROPERTY(L"Data:SelfContained", L"{true, false}")
            END_TEST_METHOD_PROPERTIES()

        bool isSelfContained{};
        VERIFY_SUCCEEDED(WEX::TestExecution::TestData::TryGetValue(L"SelfContained", isSelfContained));

        if (!isSelfContained)
        {
            ::WindowsAppRuntime::VersionInfo::TestInitialize(::TP::WindowsAppRuntimeFramework::c_PackageFamilyName, ::TP::WindowsAppRuntimeMain::c_PackageFamilyName);
            VERIFY_IS_FALSE(::WindowsAppRuntime::SelfContained::IsSelfContained());
        }
        else
        {
            ::WindowsAppRuntime::VersionInfo::TestInitialize(L"I_don't_exist_package!", L"I_don't_exist_package!");
            VERIFY_IS_TRUE(::WindowsAppRuntime::SelfContained::IsSelfContained());
        }

        EnvironmentManager forProcess{ EnvironmentManager::GetForProcess() };
        VERIFY_IS_FALSE(forProcess.AreChangesTracked());

        EnvironmentManager forUser{ EnvironmentManager::GetForUser() };
        VERIFY_IS_FALSE(forUser.AreChangesTracked());

        EnvironmentManager forMachine{ EnvironmentManager::GetForMachine() };
        VERIFY_IS_FALSE(forMachine.AreChangesTracked());
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
        winrt::hstring environmentValue{ environmentManager.GetEnvironmentVariable(c_EvKeyName) };

        ProcessCleanup();

        VERIFY_ARE_EQUAL(std::wstring{ c_EvValueName }, environmentValue);
    }

    void EnvironmentManagerWin32Tests::TestGetEnvironmentVariableForUser()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };
        winrt::hstring environmentValue{ environmentManager.GetEnvironmentVariable(c_EvKeyNameForGet) };

        VERIFY_ARE_EQUAL(std::wstring{ c_EvValueName }, environmentValue);
    }

    void EnvironmentManagerWin32Tests::TestGetEnvironmentVariableForMachine()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };
        winrt::hstring environmentValue{ environmentManager.GetEnvironmentVariable(c_EvKeyNameForGet) };

        VERIFY_ARE_EQUAL(std::wstring{ c_EvValueName }, environmentValue);
    }

    void EnvironmentManagerWin32Tests::TestSetEnvironmentVariableForProcess()
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
        VERIFY_ARE_EQUAL(0u, ::GetEnvironmentVariable(c_EvKeyName, nullptr, 0));
    }

    void EnvironmentManagerWin32Tests::TestSetEnvironmentVariableForUser()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };

        if (!IsILAtOrAbove(ProcessRunLevel::Standard))
        {
            VERIFY_THROWS(environmentManager.SetEnvironmentVariable(c_EvKeyName, c_EvValueName), winrt::hresult_access_denied);
            return;
        }

        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_EvKeyName, c_EvValueName));

        std::wstring writtenEV = GetEnvironmentVariableForUser(c_EvKeyName);
        VERIFY_ARE_EQUAL(std::wstring{ c_EvValueName }, writtenEV);

        // Update the environment variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_EvKeyName, c_EvValueName2));
        writtenEV = GetEnvironmentVariableForUser(c_EvKeyName);
        VERIFY_ARE_EQUAL(std::wstring{ c_EvValueName2 }, writtenEV);


        // Remove the value
        // setting the value to empty is the same as deleting the variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_EvKeyName, L""));
        VERIFY_ARE_EQUAL(L"", GetEnvironmentVariableForUser(c_EvKeyName));
    }

    void EnvironmentManagerWin32Tests::TestSetEnvironmentVariableForMachine()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };

        if (!IsILAtOrAbove(ProcessRunLevel::Elevated))
        {
            VERIFY_THROWS(environmentManager.SetEnvironmentVariable(c_EvKeyName, c_EvValueName), winrt::hresult_access_denied);
            return;
        }

        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_EvKeyName, c_EvValueName));

        std::wstring writtenEV{ GetEnvironmentVariableForMachine(c_EvKeyName) };
        VERIFY_ARE_EQUAL(std::wstring{ c_EvValueName }, writtenEV);

        // Update the environment variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_EvKeyName, c_EvValueName2));
        writtenEV = GetEnvironmentVariableForMachine(c_EvKeyName);
        VERIFY_ARE_EQUAL(std::wstring{ c_EvValueName2 }, writtenEV);


        // Remove the value
        // setting the value to empty is the same as deleting the variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_EvKeyName, L""));
        VERIFY_ARE_EQUAL(L"", GetEnvironmentVariableForMachine(c_EvKeyName));

    }

    void EnvironmentManagerWin32Tests::TestAppendToPathForProcess()
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

    void EnvironmentManagerWin32Tests::TestAppendToPathForUser()
    {
        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForUser(c_PathName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };

        if (!IsILAtOrAbove(ProcessRunLevel::Standard))
        {
            VERIFY_THROWS(environmentManager.AppendToPath(c_EvValueName), winrt::hresult_access_denied);
            return;
        }

        VERIFY_NO_THROW(environmentManager.AppendToPath(c_EvValueName));

        // Current path should have the semi-colon
        std::wstring currentPath{ GetEnvironmentVariableForUser(c_PathName) };
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L";";
        }

        pathToManipulate += c_EvValueName;
        pathToManipulate += L";";

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_THROWS(environmentManager.AppendToPath(L""), winrt::hresult_invalid_argument);
    }

    void EnvironmentManagerWin32Tests::TestAppendToPathForMachine()
    {
        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForMachine(c_PathName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };

        if (!IsILAtOrAbove(ProcessRunLevel::Elevated))
        {
            VERIFY_THROWS(environmentManager.AppendToPath(c_EvValueName), winrt::hresult_access_denied);
            return;
        }

        VERIFY_NO_THROW(environmentManager.AppendToPath(c_EvValueName));

        // Current path should have the semi-colon
        std::wstring currentPath{ GetEnvironmentVariableForMachine(c_PathName) };
        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L";";
        }

        pathToManipulate += c_EvValueName;
        pathToManipulate += L";";;

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_THROWS(environmentManager.AppendToPath(L""), winrt::hresult_invalid_argument);
    }

    void EnvironmentManagerWin32Tests::TestRemoveFromPathForProcess()
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

    void EnvironmentManagerWin32Tests::TestRemoveFromPathForUser()
    {
        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForUser(c_PathName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };

        if (!IsILAtOrAbove(ProcessRunLevel::LegacyLowIL))
        {
            std::wstring pathPart{ GetSecondValueFromPath(false, true) };
            VERIFY_THROWS(environmentManager.RemoveFromPath(c_EvValueName), winrt::hresult_access_denied);
            return;
        }

        environmentManager.RemoveFromPath(c_EvValueName);

        std::wstring currentPath{ GetEnvironmentVariableForUser(c_PathName) };

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_NO_THROW(environmentManager.RemoveFromPath(L"I do not exist"));

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);
    }

    void EnvironmentManagerWin32Tests::TestRemoveFromPathForMachine()
    {
        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForMachine(c_PathName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };

        if (!IsILAtOrAbove(ProcessRunLevel::Elevated))
        {
            std::wstring pathPart{ GetSecondValueFromPath(false, false) };
            VERIFY_THROWS(environmentManager.RemoveFromPath(pathPart), winrt::hresult_access_denied);
            return;
        }

        environmentManager.RemoveFromPath(c_EvValueName);

        std::wstring currentPath{ GetEnvironmentVariableForMachine(c_PathName) };

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_NO_THROW(environmentManager.RemoveFromPath(L"I do not exist"));

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);
    }

    void EnvironmentManagerWin32Tests::TestAppendToPathExtForProcess()
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

    void EnvironmentManagerWin32Tests::TestAppendToPathExtForUser()
    {
        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForUser(c_PathExtName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };

        if (!IsILAtOrAbove(ProcessRunLevel::Standard))
        {
            VERIFY_THROWS(environmentManager.AddExecutableFileExtension(c_EvValueName), winrt::hresult_access_denied);
            return;
        }

        VERIFY_NO_THROW(environmentManager.AddExecutableFileExtension(c_EvValueName));

        // Current path should have the semi-colon
        std::wstring currentPath{ GetEnvironmentVariableForUser(c_PathExtName) };

        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L";";
        }

        pathToManipulate += c_EvValueName;
        pathToManipulate += L";";

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_THROWS(environmentManager.AddExecutableFileExtension(L""), winrt::hresult_invalid_argument);
    }

    void EnvironmentManagerWin32Tests::TestAppendToPathExtForMachine()
    {
        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForMachine(c_PathExtName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };

        if (!IsILAtOrAbove(ProcessRunLevel::Elevated))
        {
            VERIFY_THROWS(environmentManager.AddExecutableFileExtension(c_EvValueName), winrt::hresult_access_denied);
            return;
        }

        VERIFY_NO_THROW(environmentManager.AddExecutableFileExtension(c_EvValueName));

        // Current path should have the semi-colon
        std::wstring currentPath{ GetEnvironmentVariableForMachine(c_PathExtName) };

        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L";";
        }

        pathToManipulate += c_EvValueName;
        pathToManipulate += L";";

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_THROWS(environmentManager.AddExecutableFileExtension(L""), winrt::hresult_invalid_argument);
    }

    void EnvironmentManagerWin32Tests::TestRemoveFromPathExtForProcess()
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

    void EnvironmentManagerWin32Tests::TestRemoveFromPathExtForUser()
    {
        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForUser(c_PathExtName) };

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

        InjectIntoPathExt(false, true, c_EvValueName, 5);
        environmentManager.RemoveExecutableFileExtension(c_EvValueName);

        std::wstring currentPath{ GetEnvironmentVariableForUser(c_PathExtName) };

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_NO_THROW(environmentManager.RemoveExecutableFileExtension(L"I do not exist"));

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);
    }

    void EnvironmentManagerWin32Tests::TestRemoveFromPathExtForMachine()
    {
        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForMachine(c_PathExtName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };

        if (!IsILAtOrAbove(ProcessRunLevel::Elevated))
        {
            std::wstring pathPart{ GetSecondValueFromPathExt(false, false) };
            VERIFY_THROWS(environmentManager.RemoveExecutableFileExtension(pathPart), winrt::hresult_access_denied);
            return;
        }

        environmentManager.RemoveExecutableFileExtension(c_EvValueName);

        std::wstring currentPath{ GetEnvironmentVariableForMachine(c_PathExtName) };

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_NO_THROW(environmentManager.RemoveExecutableFileExtension(L"I do not exist"));

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);
    }
}
