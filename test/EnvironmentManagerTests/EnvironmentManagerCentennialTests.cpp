#include "pch.h"
#include "EnvironmentManagerCentennialTests.h"
#include "Helper.h"

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
        EnvironmentManager environmentmanager = EnvironmentManager::GetForProcess();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentmanager.GetEnvironmentVariables();

        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForProcess();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerCentennialTests::CentennialTestGetEnvironmentVariablesForUser()
    {

        EnvironmentManager environmentmanager = EnvironmentManager::GetForUser();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentmanager.GetEnvironmentVariables();

        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForUser();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerCentennialTests::CentennialTestGetEnvironmentVariablesForMachine()
    {
        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForMachine();

        EnvironmentManager environmentmanager = EnvironmentManager::GetForMachine();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentmanager.GetEnvironmentVariables();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }
}
