// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "EnvironmentReaderCentennialTests.h"
#include "EnvironmentVariableHelper.h"
#include "ChangeTrackerHelper.h"
#include "TestSetupAndTeardownHelper.h"

using namespace winrt::Microsoft::ProjectReunion;

namespace ProjectReunionEnvironmentReaderTests
{
    void EnvironmentReaderCentennialTests::CentennialTestGetForProcess()
    {
        EnvironmentReader environmentReader{ EnvironmentReader::GetForProcess() };
        VERIFY_IS_NOT_NULL(environmentReader);
    }

    void EnvironmentReaderCentennialTests::CentennialTestGetForUser()
    {
        EnvironmentReader environmentReader{ EnvironmentReader::GetForUser() };
        VERIFY_IS_NOT_NULL(environmentReader);
    }

    void EnvironmentReaderCentennialTests::CentennialTestGetForMachine()
    {
        EnvironmentReader environmentReader{ EnvironmentReader::GetForMachine() };
        VERIFY_IS_NOT_NULL(environmentReader);
    }

    void EnvironmentReaderCentennialTests::CentennialTestGetEnvironmentVariablesForProcess()
    {
        EnvironmentReader environmentReader = EnvironmentReader::GetForProcess();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentReader.GetEnvironmentVariables();

        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForProcess();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentReaderCentennialTests::CentennialTestGetEnvironmentVariablesForUser()
    {

        EnvironmentReader environmentReader = EnvironmentReader::GetForUser();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentReader.GetEnvironmentVariables();

        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForUser();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentReaderCentennialTests::CentennialTestGetEnvironmentVariablesForMachine()
    {
        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForMachine();

        EnvironmentReader environmentReader = EnvironmentReader::GetForMachine();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentReader.GetEnvironmentVariables();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentReaderCentennialTests::CentennialTestGetEnvironmentVariableForProcess()
    {
        WriteProcessEV();
        EnvironmentReader environmentReader = EnvironmentReader::GetForProcess();
        winrt::hstring environmentValue = environmentReader.GetEnvironmentVariable(c_evKeyName);

        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), environmentValue);
    }

    void EnvironmentReaderCentennialTests::CentennialTestGetEnvironmentVariableForUser()
    {
        EnvironmentReader environmentReader = EnvironmentReader::GetForUser();
        winrt::hstring environmentValue = environmentReader.GetEnvironmentVariable(c_evKeyName);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), environmentValue);
    }

    void EnvironmentReaderCentennialTests::CentennialTestGetEnvironmentVariableForMachine()
    {
        EnvironmentReader environmentReader = EnvironmentReader::GetForMachine();
        winrt::hstring environmentValue = environmentReader.GetEnvironmentVariable(c_evKeyName);

        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), environmentValue);
    }

    void EnvironmentReaderCentennialTests::CentennialTestSetEnvironmentVariableForProcess()
    {
        EnvironmentReader environmentReader = EnvironmentReader::GetForProcess();
        //VERIFY_NO_THROW(environmentReader.SetEnvironmentVariable(c_evKeyName2, c_evValueName));
        VERIFY_NO_THROW(environmentReader.SetEnvironmentVariable(c_evKeyName2, NULL));

        std::wstring writtenEV = GetEnvironmentVariableForProcess(c_evKeyName2);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), writtenEV);

        // Update the environment variable
        VERIFY_NO_THROW(environmentReader.SetEnvironmentVariable(c_evKeyName2, c_evValueName2));
        writtenEV = GetEnvironmentVariableForProcess(c_evKeyName2);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName2), writtenEV);


        // Remove the value
        // setting the value to empty is the same as deleting the variable
        VERIFY_NO_THROW(environmentReader.SetEnvironmentVariable(c_evKeyName2, L""));
        VERIFY_ARE_EQUAL(0, ::GetEnvironmentVariable(c_evKeyName2, nullptr, 0));
    }

    void EnvironmentReaderCentennialTests::CentennialTestSetEnvironmentVariableForUser()
    {
        // Set 1 value.
        EnvironmentReader environmentReader = EnvironmentReader::GetForUser();
        VERIFY_NO_THROW(environmentReader.SetEnvironmentVariable(c_evKeyName2, c_evValueName));
        std::wstring writtenEV = GetEnvironmentVariableForUser(c_evKeyName2);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), writtenEV);

        // Update the environment variable
        VERIFY_NO_THROW(environmentReader.SetEnvironmentVariable(c_evKeyName2, c_evValueName2));
        writtenEV = GetEnvironmentVariableForUser(c_evKeyName2);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName2), writtenEV);

        // Remove the value
        // setting the value to empty is the same as deleting the variable
        VERIFY_NO_THROW(environmentReader.SetEnvironmentVariable(c_evKeyName2, L""));
        VERIFY_ARE_EQUAL(L"", GetEnvironmentVariableForUser(c_evKeyName2));

        RemoveUserChangeTracking();
    }

    void EnvironmentReaderCentennialTests::CentennialTestSetEnvironmentVariableForMachine()
    {
        EnvironmentReader environmentReader = EnvironmentReader::GetForMachine();
        VERIFY_NO_THROW(environmentReader.SetEnvironmentVariable(c_evKeyName2, c_evValueName));

        std::wstring writtenEV = GetEnvironmentVariableForMachine(c_evKeyName2);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), writtenEV);

        // Update the environment variable
        VERIFY_NO_THROW(environmentReader.SetEnvironmentVariable(c_evKeyName2, c_evValueName2));
        writtenEV = GetEnvironmentVariableForMachine(c_evKeyName2);
        VERIFY_ARE_EQUAL(std::wstring(c_evValueName2), writtenEV);

        // Remove the value
        // setting the value to empty is the same as deleting the variable
        VERIFY_NO_THROW(environmentReader.SetEnvironmentVariable(c_evKeyName2, L""));
        VERIFY_ARE_EQUAL(L"", GetEnvironmentVariableForMachine(c_evKeyName2));

        RemoveMachineChangeTracking();
    }

    void EnvironmentReaderCentennialTests::CentennialTestAppendToPathForProcess()
    {
        std::wstring originalPath = GetEnvironmentVariableForProcess(c_pathName);
        EnvironmentReader environmentReader = EnvironmentReader::GetForProcess();
        VERIFY_NO_THROW(environmentReader.AppendToPath(c_evValueName));

        std::wstring alteredPath = GetEnvironmentVariableForProcess(c_pathName);

        if (originalPath.back() != L';')
        {
            originalPath += L';';
        }

        VERIFY_ARE_EQUAL(originalPath.append(c_evValueName).append(L";"), alteredPath);
    }

    void EnvironmentReaderCentennialTests::CentennialTestAppendToPathForUser()
    {
        std::wstring originalPath = GetEnvironmentVariableForUser(c_pathName);
        EnvironmentReader environmentReader = EnvironmentReader::GetForUser();
        VERIFY_NO_THROW(environmentReader.AppendToPath(c_evValueName));

        std::wstring alteredPath = GetEnvironmentVariableForUser(c_pathName);

        RestoreUserPath(originalPath);

        if (originalPath.back() != L';')
        {
            originalPath += L';';
        }

        VERIFY_ARE_EQUAL(originalPath.append(c_evValueName).append(L";"), alteredPath);

        RemoveUserChangeTracking();
    }

    void EnvironmentReaderCentennialTests::CentennialTestAppendToPathForMachine()
    {
        std::wstring originalPath = GetEnvironmentVariableForMachine(c_pathName);
        EnvironmentReader environmentReader = EnvironmentReader::GetForMachine();
        VERIFY_NO_THROW(environmentReader.AppendToPath(c_evValueName));

        std::wstring alteredPath = GetEnvironmentVariableForMachine(c_pathName);

        RestoreMachinePath(originalPath);

        if (originalPath.back() != L';')
        {
            originalPath += L';';
        }

        VERIFY_ARE_EQUAL(originalPath.append(c_evValueName).append(L";"), alteredPath);

        RemoveMachineChangeTracking();
    }
}
