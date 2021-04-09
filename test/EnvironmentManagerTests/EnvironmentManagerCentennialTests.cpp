// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "EnvironmentManagerCentennialTests.h"
#include "EnvironmentVariableHelper.h"
#include "ChangeTrackerHelper.h"
#include "TestSetupAndTeardownHelper.h"

using namespace winrt::Microsoft::ProjectReunion;

namespace ProjectReunionEnvironmentManagerTests
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

    void EnvironmentManagerCentennialTests::CentennialTestGetEnvironmentVariablesForProcess()
    {
        EnvironmentManager environmentManager = EnvironmentManager::GetForProcess();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentManager.GetEnvironmentVariables();

        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForProcess();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerCentennialTests::CentennialTestGetEnvironmentVariablesForUser()
    {

        EnvironmentManager environmentManager = EnvironmentManager::GetForUser();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentManager.GetEnvironmentVariables();

        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForUser();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerCentennialTests::CentennialTestGetEnvironmentVariablesForMachine()
    {
        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForMachine();

        EnvironmentManager environmentManager = EnvironmentManager::GetForMachine();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentManager.GetEnvironmentVariables();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerCentennialTests::CentennialTestGetEnvironmentVariableForProcess()
    {
        WriteProcessEV();
        EnvironmentManager environmentManager = EnvironmentManager::GetForProcess();
        winrt::hstring environmentValue = environmentManager.GetEnvironmentVariable(c_evKeyName);

        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), environmentValue);
    }

    void EnvironmentManagerCentennialTests::CentennialTestGetEnvironmentVariableForUser()
    {
        WriteUserEV();
        EnvironmentManager environmentManager = EnvironmentManager::GetForUser();
        winrt::hstring environmentValue = environmentManager.GetEnvironmentVariable(c_evKeyName);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), environmentValue);
        RemoveUserEV();
    }

    void EnvironmentManagerCentennialTests::CentennialTestGetEnvironmentVariableForMachine()
    {
        EnvironmentManager environmentManager = EnvironmentManager::GetForMachine();
        winrt::hstring environmentValue = environmentManager.GetEnvironmentVariable(c_evKeyName);

        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), environmentValue);
    }

    void EnvironmentManagerCentennialTests::CentennialTestSetEnvironmentVariableForProcess()
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

    void EnvironmentManagerCentennialTests::CentennialTestSetEnvironmentVariableForUser()
    {
        // Set 1 value.
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

        // Check the values in Change Tracker.
        // Both values should be empty.
        // Previous Value is empty because the EV did not exist.
        // Current value is empty because it was deleted.
        wil::unique_hkey keyChangeTracker = GetKeyForEVTrackingChange(true, L"Microsoft.Process.Environment.Centennial.Tests_8wekyb3d8bbwe", c_evKeyName);
        VERIFY_ARE_EQUAL(L"", GetEnvironmentVariableFromRegistry(L"PreviousValue", keyChangeTracker.get()));
        VERIFY_ARE_EQUAL(L"", GetEnvironmentVariableFromRegistry(L"CurrentValue", keyChangeTracker.get()));

        RemoveUserChangeTracking();
    }

    void EnvironmentManagerCentennialTests::CentennialTestSetEnvironmentVariableForMachine()
    {
        EnvironmentManager environmentManager = EnvironmentManager::GetForMachine();

        if (!IsElevated())
        {
            VERIFY_THROWS(environmentManager.SetEnvironmentVariable(c_evKeyName, c_evValueName), winrt::hresult_access_denied);
            return;
        }

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

        // Check the values in Change Tracker.
        // Both values should be empty.
        // Previous Value is empty because the EV did not exist.
        // Current value is empty because it was deleted.
        wil::unique_hkey keyChangeTracker = GetKeyForEVTrackingChange(false, L"Microsoft.Process.Environment.Centennial.Tests_8wekyb3d8bbwe", c_evKeyName);
        VERIFY_ARE_EQUAL(L"", GetEnvironmentVariableFromRegistry(L"PreviousValue", keyChangeTracker.get()));
        VERIFY_ARE_EQUAL(L"", GetEnvironmentVariableFromRegistry(L"CurrentValue", keyChangeTracker.get()));

        RemoveMachineChangeTracking();
    }

    void EnvironmentManagerCentennialTests::CentennialTestAppendToPathForProcess()
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

    void EnvironmentManagerCentennialTests::CentennialTestAppendToPathForUser()
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

        wil::unique_hkey keyChangeTracker = GetKeyForEVTrackingChange(true, L"Microsoft.Process.Environment.Centennial.Tests_1.0.0.0_neutral_en-us_8wekyb3d8bbwe", L"Path");
        VERIFY_ARE_EQUAL(pathToManipulate, GetEnvironmentVariableFromRegistry(L"CurrentValue", keyChangeTracker.get()));

        RemoveUserChangeTracking();
    }

    void EnvironmentManagerCentennialTests::CentennialTestAppendToPathForMachine()
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
        pathToManipulate += L";";

        VERIFY_ARE_EQUAL(currentPath, pathToManipulate);

        RestoreMachinePath(pathToRestore);

        wil::unique_hkey keyChangeTracker = GetKeyForEVTrackingChange(false, L"Microsoft.Process.Environment.Centennial.Tests_1.0.0.0_neutral_en-us_8wekyb3d8bbwe", L"Path");
        VERIFY_ARE_EQUAL(pathToManipulate, GetEnvironmentVariableFromRegistry(L"CurrentValue", keyChangeTracker.get()));

        RemoveMachineChangeTracking();
    }

    void EnvironmentManagerCentennialTests::CentennialTestRemoveFromPathForProcess()
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

    void EnvironmentManagerCentennialTests::CentennialTestRemoveFromPathForUser()
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

        // Make sure the change tracker worked.
        wil::unique_hkey keyChangeTracker = GetKeyForEVTrackingChange(true, L"Microsoft.Process.Environment.Centennial.Tests_1.0.0.0_neutral_en-us_8wekyb3d8bbwe", L"Path");
        VERIFY_ARE_EQUAL(pathToManipulate, GetEnvironmentVariableFromRegistry(L"CurrentValue", keyChangeTracker.get()));

        RemoveUserChangeTracking();
    }

    void EnvironmentManagerCentennialTests::CentennialTestRemoveFromPathForMachine()
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

        // Make sure the change tracker worked.
        wil::unique_hkey keyChangeTracker = GetKeyForEVTrackingChange(false, L"Microsoft.Process.Environment.Centennial.Tests_1.0.0.0_neutral_en-us_8wekyb3d8bbwe", L"Path");
        VERIFY_ARE_EQUAL(pathToManipulate, GetEnvironmentVariableFromRegistry(L"CurrentValue", keyChangeTracker.get()));

        RemoveMachineChangeTracking();
    }
}
