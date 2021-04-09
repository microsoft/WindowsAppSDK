// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "EnvironmentReaderUWPTests.h"
#include "EnvironmentVariableHelper.h"
#include "TestSetupAndTeardownHelper.h"

using namespace winrt::Microsoft::ProjectReunion;

namespace ProjectReunionEnvironmentReaderTests
{
    void EnvironmentReaderUWPTests::UWPTestGetForProcess()
    {
        EnvironmentReader environmentReader{ EnvironmentReader::GetForProcess() };
        VERIFY_IS_NOT_NULL(environmentReader);
    }

    void EnvironmentReaderUWPTests::UWPTestGetForUser()
    {
        EnvironmentReader environmentReader{ EnvironmentReader::GetForUser() };
        VERIFY_IS_NOT_NULL(environmentReader);
    }

    void EnvironmentReaderUWPTests::UWPTestGetForMachine()
    {
        EnvironmentReader environmentReader{ EnvironmentReader::GetForMachine() };
        VERIFY_IS_NOT_NULL(environmentReader);
    }

    void EnvironmentReaderUWPTests::UWPTestGetEnvironmentVariablesForProcess()
    {
        EnvironmentReader environmentReader = EnvironmentReader::GetForProcess();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentReader.GetEnvironmentVariables();

        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForProcess();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentReaderUWPTests::UWPTestGetEnvironmentVariablesForUser()
    {

        EnvironmentReader environmentReader = EnvironmentReader::GetForUser();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentReader.GetEnvironmentVariables();

        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForUser();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentReaderUWPTests::UWPTestGetEnvironmentVariablesForMachine()
    {
        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForMachine();

        EnvironmentReader environmentReader = EnvironmentReader::GetForMachine();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentReader.GetEnvironmentVariables();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentReaderUWPTests::UWPTestGetEnvironmentVariableForProcess()
    {
        WriteProcessEV();
        EnvironmentReader environmentReader = EnvironmentReader::GetForProcess();
        winrt::hstring environmentValue = environmentReader.GetEnvironmentVariable(c_evKeyName);

        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), environmentValue);
    }

    void EnvironmentReaderUWPTests::UWPTestGetEnvironmentVariableForUser()
    {
        EnvironmentReader environmentReader = EnvironmentReader::GetForUser();
        winrt::hstring environmentValue = environmentReader.GetEnvironmentVariable(c_evKeyName);

        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), environmentValue);
    }

    void EnvironmentReaderUWPTests::UWPTestGetEnvironmentVariableForMachine()
    {
        EnvironmentReader environmentReader = EnvironmentReader::GetForUser();
        winrt::hstring environmentValue = environmentReader.GetEnvironmentVariable(c_evKeyName);

        VERIFY_ARE_EQUAL(std::wstring(c_evValueName), environmentValue);
    }
}
