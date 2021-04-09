// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "EnvironmentReaderWin32Tests.h"
#include "EnvironmentVariableHelper.h"

using namespace winrt::Microsoft::ProjectReunion;

namespace ProjectReunionEnvironmentReaderTests
{
    void EnvironmentReaderWin32Tests::TestGetForProcess()
    {
        EnvironmentReader environmentReader{ EnvironmentReader::GetForProcess() };
        VERIFY_IS_NOT_NULL(environmentReader);
    }

    void EnvironmentReaderWin32Tests::TestGetForUser()
    {
        EnvironmentReader environmentReader{ EnvironmentReader::GetForUser() };
        VERIFY_IS_NOT_NULL(environmentReader);
    }

    void EnvironmentReaderWin32Tests::TestGetForMachine()
    {
        EnvironmentReader environmentReader{ EnvironmentReader::GetForMachine() };
        VERIFY_IS_NOT_NULL(environmentReader);
    }

    void EnvironmentReaderWin32Tests::TestGetEnvironmentVariablesForProcess()
    {
        EnvironmentReader environmentReader = EnvironmentReader::GetForProcess();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentReader.GetEnvironmentVariables();

        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForProcess();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentReaderWin32Tests::TestGetEnvironmentVariablesForUser()
    {

        EnvironmentReader environmentReader = EnvironmentReader::GetForUser();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentReader.GetEnvironmentVariables();

        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForUser();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentReaderWin32Tests::TestGetEnvironmentVariablesForMachine()
    {
        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForMachine();

        EnvironmentReader environmentReader = EnvironmentReader::GetForMachine();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentReader.GetEnvironmentVariables();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentReaderWin32Tests::TestGetEnvironmentVariableForProcess()
    {
        WriteProcessEV();
        EnvironmentReader environmentReader = EnvironmentReader::GetForProcess();
        winrt::hstring environmentValue = environmentReader.GetEnvironmentVariable(c_evKeyName);

        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), environmentValue);
    }

    void EnvironmentReaderWin32Tests::TestGetEnvironmentVariableForUser()
    {
        EnvironmentReader environmentReader = EnvironmentReader::GetForUser();
        winrt::hstring environmentValue = environmentReader.GetEnvironmentVariable(c_evKeyName);

        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), environmentValue);
    }

    void EnvironmentReaderWin32Tests::TestGetEnvironmentVariableForMachine()
    {
        EnvironmentReader environmentReader = EnvironmentReader::GetForMachine();
        winrt::hstring environmentValue = environmentReader.GetEnvironmentVariable(c_evKeyName);

        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), environmentValue);
    }

    void EnvironmentReaderWin32Tests::TestSetEnvironmentVariableForProcess()
    {
        EnvironmentReader environmentReader = EnvironmentReader::GetForProcess();
        VERIFY_NO_THROW(environmentReader.SetEnvironmentVariable(c_evKeyName2, c_evValueName));

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

    void EnvironmentReaderWin32Tests::TestSetEnvironmentVariableForUser()
    {
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
    }

    void EnvironmentReaderWin32Tests::TestSetEnvironmentVariableForMachine()
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
    }

    void EnvironmentReaderWin32Tests::TestAppendToPathForProcess()
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

    void EnvironmentReaderWin32Tests::TestAppendToPathForUser()
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
    }

    void EnvironmentReaderWin32Tests::TestAppendToPathForMachine()
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
    }
}
