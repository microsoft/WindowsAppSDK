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
}
