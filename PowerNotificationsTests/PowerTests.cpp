#include "pch.h"
#include <iostream>

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
            bool callback_success = false;
            auto token = winrt::Microsoft::ProjectReunion::PowerManager::BatteryStatusChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
                {
                    callback_success = true;
                    std::cout << "Reached";
                });
            //Add a sleep and then check if the callback was successful

            //VERIFY_IS_TRUE(callback_success);

            winrt::Microsoft::ProjectReunion::PowerManager::BatteryStatusChanged(token);
            VERIFY_IS_NOT_NULL(token);
        }

        TEST_METHOD(GetDisplayStatus)
        {
            //insert additional code here
            PowerEventHandle hand;
            auto stat = winrt::Microsoft::ProjectReunion::PowerManager::DisplayStatus();
            //VERIFY_ARE_EQUAL(stat, 5);
            //std::cout << "\n Time : " << stat;
            VERIFY_IS_NOT_NULL(hand);
        }
    };
}
