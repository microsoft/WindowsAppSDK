// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

// suppress macro redifinition.  This is needed to declare tests inline.
#pragma warning(suppress: 4005)
#define INLINE_TEST_METHOD_MARKUP
#include "pch.h"
#include "EnvironmentManagerCentennialTests.h"
#include "EnvironmentVariableHelper.h"
#include "ChangeTrackerHelper.h"
#include "TestSetupAndTeardownHelper.h"
#include <TE.Common.h>
#include <WexTestClass.h>
#include <WindowsAppRuntime.VersionInfo.h>
#include <WindowsAppRuntime.SelfContained.h>

using namespace winrt::Microsoft::Windows;

namespace WindowsAppSDKEnvironmentManagerTests
{
    void EnvironmentManagerCentennialTests::CentennialTestGetForProcess()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };
        VERIFY_IS_NOT_NULL(environmentManager);
    }

    void EnvironmentManagerCentennialTests::CentennialTestGetForUser()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };
        VERIFY_IS_NOT_NULL(environmentManager);
    }

    void EnvironmentManagerCentennialTests::CentennialTestGetForMachine()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };
        VERIFY_IS_NOT_NULL(environmentManager);
    }

    void EnvironmentManagerCentennialTests::CentennialTestAreChangesTracked()
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

            EnvironmentManager forUser{ EnvironmentManager::GetForUser() };
            VERIFY_IS_TRUE(forUser.AreChangesTracked());

            EnvironmentManager forMachine{ EnvironmentManager::GetForMachine() };
            VERIFY_IS_TRUE(forMachine.AreChangesTracked());
        }
        else
        {
            ::WindowsAppRuntime::VersionInfo::TestInitialize(L"I_don't_exist_package!", L"I_don't_exist_package!");
            VERIFY_IS_TRUE(::WindowsAppRuntime::SelfContained::IsSelfContained());

            EnvironmentManager forUser{ EnvironmentManager::GetForUser() };
            VERIFY_IS_FALSE(forUser.AreChangesTracked());

            EnvironmentManager forMachine{ EnvironmentManager::GetForMachine() };
            VERIFY_IS_FALSE(forMachine.AreChangesTracked());
        }

        EnvironmentManager forProcess{ EnvironmentManager::GetForProcess() };
        VERIFY_IS_FALSE(forProcess.AreChangesTracked());
    }

    void EnvironmentManagerCentennialTests::CentennialTestGetEnvironmentVariablesForProcess()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };
        EnvironmentVariables environmentVariablesFromWinRTAPI{ environmentManager.GetEnvironmentVariables() };

        EnvironmentVariables environmentVariablesFromWindowsAPI{ GetEnvironmentVariablesForProcess() };

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerCentennialTests::CentennialTestGetEnvironmentVariablesForUser()
    {

        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };
        EnvironmentVariables environmentVariablesFromWinRTAPI{ environmentManager.GetEnvironmentVariables() };

        EnvironmentVariables environmentVariablesFromWindowsAPI{ GetEnvironmentVariablesForUser() };

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerCentennialTests::CentennialTestGetEnvironmentVariablesForMachine()
    {
        EnvironmentVariables environmentVariablesFromWindowsAPI{ GetEnvironmentVariablesForMachine() };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };
        EnvironmentVariables environmentVariablesFromWinRTAPI{ environmentManager.GetEnvironmentVariables() };

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerCentennialTests::CentennialTestGetEnvironmentVariableForProcess()
    {
        ProcessSetup();
        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };
        winrt::hstring environmentValue{ environmentManager.GetEnvironmentVariable(c_EvKeyName) };

        VERIFY_ARE_EQUAL(std::wstring{ c_EvValueName }, environmentValue);

        ProcessCleanup();
    }

    void EnvironmentManagerCentennialTests::CentennialTestGetEnvironmentVariableForUser()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };
        winrt::hstring environmentValue{ environmentManager.GetEnvironmentVariable(c_EvKeyNameForGet) };

        VERIFY_ARE_EQUAL(std::wstring{ c_EvValueName }, environmentValue);
    }

    void EnvironmentManagerCentennialTests::CentennialTestGetEnvironmentVariableForMachine()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForMachine() };
        winrt::hstring environmentValue{ environmentManager.GetEnvironmentVariable(c_EvKeyNameForGet) };

        VERIFY_ARE_EQUAL(std::wstring{ c_EvValueName }, environmentValue);
    }

    void EnvironmentManagerCentennialTests::CentennialTestSetEnvironmentVariableForProcess()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_EvKeyName, c_EvValueName));

        std::wstring writtenEV{ GetEnvironmentVariableForProcess(c_EvKeyName) };
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

    void EnvironmentManagerCentennialTests::CentennialTestSetEnvironmentVariableForUser()
    {
        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };

        if (!IsILAtOrAbove(ProcessRunLevel::Standard))
        {
            VERIFY_THROWS(environmentManager.SetEnvironmentVariable(c_EvKeyName, c_EvValueName), winrt::hresult_access_denied);
            return;
        }

        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_EvKeyName, c_EvValueName));
        std::wstring writtenEV{ GetEnvironmentVariableForUser(c_EvKeyName) };
        VERIFY_ARE_EQUAL(std::wstring{ c_EvValueName }, writtenEV);

        // Update the environment variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_EvKeyName, c_EvValueName2));
        writtenEV = GetEnvironmentVariableForUser(c_EvKeyName);
        VERIFY_ARE_EQUAL(std::wstring{ c_EvValueName2 }, writtenEV);

        // Remove the value
        // setting the value to empty is the same as deleting the variable
        VERIFY_NO_THROW(environmentManager.SetEnvironmentVariable(c_EvKeyName, L""));
        VERIFY_ARE_EQUAL(L"", GetEnvironmentVariableForUser(c_EvKeyName));

        // Check the values in Change Tracker.
        // Both values should be empty.
        // Previous Value is empty because the EV did not exist.
        // Current value is empty because it was deleted.
        wil::unique_hkey keyChangeTracker{ GetKeyForEVTrackingChange(true, GetPackageFullName(), c_EvKeyName) };
        VERIFY_ARE_EQUAL(L"", GetEnvironmentVariableFromRegistry(L"PreviousValue", keyChangeTracker.get()));
        VERIFY_ARE_EQUAL(L"", GetEnvironmentVariableFromRegistry(L"CurrentValue", keyChangeTracker.get()));
    }

    void EnvironmentManagerCentennialTests::CentennialTestSetEnvironmentVariableForMachine()
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

        // Check the values in Change Tracker.
        // Both values should be empty.
        // Previous Value is empty because the EV did not exist.
        // Current value is empty because it was deleted.
        wil::unique_hkey keyChangeTracker{ GetKeyForEVTrackingChange(false, GetPackageFullName(), c_EvKeyName) };
        VERIFY_ARE_EQUAL(c_EvValueName2, GetEnvironmentVariableFromRegistry(L"PreviousValue", keyChangeTracker.get()));
        VERIFY_ARE_EQUAL(L"", GetEnvironmentVariableFromRegistry(L"CurrentValue", keyChangeTracker.get()));
    }

    void EnvironmentManagerCentennialTests::CentennialTestAppendToPathForProcess()
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

    void EnvironmentManagerCentennialTests::CentennialTestAppendToPathForUser()
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

        std::wstring expectedValue{ c_EvValueName };
        expectedValue += L';';

        wil::unique_hkey keyChangeTracker{ GetKeyForPathTrackingChange(true, GetPackageFullName()) };
        VERIFY_ARE_EQUAL(expectedValue, GetEnvironmentVariableFromRegistry(L"AppendedValues", keyChangeTracker.get()));
    }

    void EnvironmentManagerCentennialTests::CentennialTestAppendToPathForMachine()
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
        std::wstring currentPath{ GetEnvironmentVariableForUser(c_PathName) };

        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L";";
        }

        pathToManipulate += c_EvValueName;
        pathToManipulate += L";";

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_THROWS(environmentManager.AppendToPath(L""), winrt::hresult_invalid_argument);

        std::wstring expectedValue{ c_EvValueName };
        expectedValue += L';';

        wil::unique_hkey keyChangeTracker{ GetKeyForPathTrackingChange(false, GetPackageFullName()) };
        VERIFY_ARE_EQUAL(expectedValue, GetEnvironmentVariableFromRegistry(L"AppendedValues", keyChangeTracker.get()));
    }

    void EnvironmentManagerCentennialTests::CentennialTestRemoveFromPathForProcess()
    {
        ProcessSetup();

        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForProcess(c_PathName) };

        if (!pathToManipulate.empty() && pathToManipulate.back() != L';')
        {
            pathToManipulate += L';';
        }

        EnvironmentManager environmentManager{ EnvironmentManager::GetForProcess() };

        InjectIntoPath(true, false, c_EvValueName, 5);
        environmentManager.RemoveFromPath(c_EvValueName);

        std::wstring currentPath{ GetEnvironmentVariableForProcess(c_PathName) };

        ProcessCleanup();

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_NO_THROW(environmentManager.RemoveFromPath(L"I do not exist"));

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);
    }

    void EnvironmentManagerCentennialTests::CentennialTestRemoveFromPathForUser()
    {
        // Keep a local string to match all operations to PATH
        std::wstring pathToManipulate{ GetEnvironmentVariableForUser(c_PathName) };

        EnvironmentManager environmentManager{ EnvironmentManager::GetForUser() };

        if (!IsILAtOrAbove(ProcessRunLevel::Standard))
        {
            std::wstring pathPart{ GetSecondValueFromPath(false, true) };
            VERIFY_THROWS(environmentManager.RemoveFromPath(pathPart), winrt::hresult_access_denied);
            return;
        }

        InjectIntoPath(false, true, c_EvValueName, 5);
        environmentManager.RemoveFromPath(c_EvValueName);

        std::wstring currentPath{ GetEnvironmentVariableForUser(c_PathName) };

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_NO_THROW(environmentManager.RemoveFromPath(L"I do not exist"));

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        std::wstring expectedValue{ c_EvValueName };
        expectedValue += L";,5\t";

        wil::unique_hkey keyChangeTracker{ GetKeyForPathTrackingChange(true, GetPackageFullName()) };
        VERIFY_ARE_EQUAL(expectedValue, GetEnvironmentVariableFromRegistry(L"RemovedValues", keyChangeTracker.get()));
    }

    void EnvironmentManagerCentennialTests::CentennialTestRemoveFromPathForMachine()
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

        std::wstring expectedValue{ c_EvValueName };
        expectedValue += L";,5\t";

        wil::unique_hkey keyChangeTracker{ GetKeyForPathTrackingChange(false, GetPackageFullName()) };
        VERIFY_ARE_EQUAL(expectedValue, GetEnvironmentVariableFromRegistry(L"RemovedValues", keyChangeTracker.get()));
    }

    void EnvironmentManagerCentennialTests::CentennialTestAppendToPathExtForProcess()
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

    void EnvironmentManagerCentennialTests::CentennialTestAppendToPathExtForUser()
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

        std::wstring expectedValue{ c_EvValueName };
        expectedValue += L';';

        wil::unique_hkey keyChangeTracker{ GetKeyForPathExtTrackingChange(true, GetPackageFullName()) };
        VERIFY_ARE_EQUAL(expectedValue, GetEnvironmentVariableFromRegistry(L"AppendedValues", keyChangeTracker.get()));
    }

    void EnvironmentManagerCentennialTests::CentennialTestAppendToPathExtForMachine()
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
        std::wstring currentPath{ GetEnvironmentVariableForUser(c_PathExtName) };

        if (pathToManipulate.back() != L';')
        {
            pathToManipulate += L";";
        }

        pathToManipulate += c_EvValueName;
        pathToManipulate += L";";

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        VERIFY_THROWS(environmentManager.AddExecutableFileExtension(L""), winrt::hresult_invalid_argument);

        std::wstring expectedValue{ c_EvValueName };
        expectedValue += L';';

        wil::unique_hkey keyChangeTracker{ GetKeyForPathExtTrackingChange(false, GetPackageFullName()) };
        VERIFY_ARE_EQUAL(expectedValue, GetEnvironmentVariableFromRegistry(L"AppendedValues", keyChangeTracker.get()));
    }

    void EnvironmentManagerCentennialTests::CentennialTestRemoveFromPathExtForProcess()
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

    void EnvironmentManagerCentennialTests::CentennialTestRemoveFromPathExtForUser()
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

        std::wstring expectedValue{ c_EvValueName };
        expectedValue += L";,5\t";

        wil::unique_hkey keyChangeTracker{ GetKeyForPathExtTrackingChange(true, GetPackageFullName()) };
        VERIFY_ARE_EQUAL(expectedValue, GetEnvironmentVariableFromRegistry(L"RemovedValues", keyChangeTracker.get()));
    }

    void EnvironmentManagerCentennialTests::CentennialTestRemoveFromPathExtForMachine()
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

        std::wstring expectedValue{ c_EvValueName };
        expectedValue += L";,5\t";

        wil::unique_hkey keyChangeTracker{ GetKeyForPathExtTrackingChange(false, GetPackageFullName()) };
        VERIFY_ARE_EQUAL(expectedValue, GetEnvironmentVariableFromRegistry(L"RemovedValues", keyChangeTracker.get()));
    }
}
