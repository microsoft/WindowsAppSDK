#include "pch.h"
#include "EnvironmentManagerUWPTests.h"
#include "Helper.h"

using namespace winrt::Microsoft::ProjectReunion;

namespace ProjectReunionEnvironmentManagerTests
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
        EnvironmentManager environmentmanager = EnvironmentManager::GetForProcess();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentmanager.GetEnvironmentVariables();

        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForProcess();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerUWPTests::UWPTestGetEnvironmentVariablesForUser()
    {

        EnvironmentManager environmentmanager = EnvironmentManager::GetForUser();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentmanager.GetEnvironmentVariables();

        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForUser();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }

    void EnvironmentManagerUWPTests::UWPTestGetEnvironmentVariablesForMachine()
    {
        EnvironmentVariables environmentVariablesFromWindowsAPI = GetEnvironmentVariablesForMachine();

        EnvironmentManager environmentmanager = EnvironmentManager::GetForMachine();
        EnvironmentVariables environmentVariablesFromWinRTAPI = environmentmanager.GetEnvironmentVariables();

        CompareIMapViews(environmentVariablesFromWinRTAPI, environmentVariablesFromWindowsAPI);
    }
}
