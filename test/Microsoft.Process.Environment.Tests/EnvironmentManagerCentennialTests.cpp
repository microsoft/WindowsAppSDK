#include <pch.h>
#include <EnvironmentManagerCentennialTests.h>

using namespace winrt::Microsoft::ProjectReunion;

namespace ProjectReunionCppTest
{
    void EnvironmentManagerCentennialTests::CentennialTestGetForProcess()
    {
        EnvironmentManager environmentManager = EnvironmentManager::GetForProcess();
        VERIFY_IS_NOT_NULL(environmentManager);
    }

    void EnvironmentManagerCentennialTests::CentennialTestGetForUser()
    {
        EnvironmentManager environmentManager = EnvironmentManager::GetForUser();
        VERIFY_IS_NOT_NULL(environmentManager);
    }


    void EnvironmentManagerCentennialTests::CentennialTestGetForMachine()
    {
        EnvironmentManager environmentManager = EnvironmentManager::GetForMachine();
        VERIFY_IS_NOT_NULL(environmentManager);
    }
}
