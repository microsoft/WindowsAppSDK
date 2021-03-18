#include "pch.h"

using PowerEventHandle =
winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable>;

namespace PowerMangerTest
{
    class Mocked
    {
    public:
        BEGIN_TEST_CLASS(Mocked)
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(Setup)
        {
            ::Test::Bootstrap::Setup();
            //insert additional code here
            return true;
        }

        TEST_CLASS_CLEANUP(Cleanup)
        {
            //insert additional code here
            ::Test::Bootstrap::Cleanup();
            return true;
        }

        TEST_METHOD(Foo)
        {
            //insert additional code here
            PowerEventHandle handle;
            auto token = winrt::Microsoft::ProjectReunion::PowerManager::BatteryStatusChanged(handle);
            winrt::Microsoft::ProjectReunion::PowerManager::BatteryStatusChanged(token);
            VERIFY_IS_NOT_NULL(handle);
        }
    };
}
