// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "EnvironmentReaderCentennialTests.h"
#include "EnvironmentVariableHelper.h"
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
}
