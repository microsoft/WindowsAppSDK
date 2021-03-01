#include <pch.h>
#include <EnvironmentManagerWin32Tests.h>

using namespace winrt::Microsoft::ProjectReunion;

namespace ProjectReunionCppTest
{
    bool EnvironmentManagerWin32Tests::TestSetup()
    {
        winrt::init_apartment(winrt::apartment_type::single_threaded);
        return true;
    }

    void EnvironmentManagerWin32Tests::TestGetForProcess()
    {
        winrt::Microsoft::ProjectReunion::EnvironmentManager environmentManager = winrt::Microsoft::ProjectReunion::EnvironmentManager::GetForProcess();
        VERIFY_IS_NOT_NULL(environmentManager);
    }

    void EnvironmentManagerWin32Tests::TestGetForUser()
    {
        EnvironmentManager environmentManager = EnvironmentManager::GetForUser();
        VERIFY_IS_NOT_NULL(environmentManager);
    }


    void EnvironmentManagerWin32Tests::TestGetForMachine()
    {
        EnvironmentManager environmentManager = EnvironmentManager::GetForMachine();
        VERIFY_IS_NOT_NULL(environmentManager);
    }
}
