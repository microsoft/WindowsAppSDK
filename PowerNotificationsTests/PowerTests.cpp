#include "pch.h"
#include <Mock.h>
#include <winrt/Microsoft.ProjectReunion.h>
#include <iostream>

using PowerEventHandle =
winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable>;
using namespace Mock10;

namespace PowerMangerTest
{
    class MockedClass
    {
    public:
        BEGIN_TEST_CLASS(MockedClass)
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

            auto stat = winrt::Microsoft::ProjectReunion::PowerManager::BatteryStatus();
            
            //Add a sleep and then check if the callback was successful
            //VERIFY_IS_TRUE(callback_success);

            winrt::Microsoft::ProjectReunion::PowerManager::BatteryStatusChanged(token);
            VERIFY_IS_NOT_NULL(token);
        }

        TEST_METHOD(GetDisplayStatus)
        {            
            auto stat = winrt::Microsoft::ProjectReunion::PowerManager::DisplayStatus();            
            VERIFY_ARE_EQUAL(stat, 5);

            //auto mock = Mock::Function<Prototype>(L"MyProduct.dll", L"*Product::TargetFunction*");
            //MockFunction<Prototype> mock1 = Mock::Function<Prototype>(L"User32.dll", L"MessageBoxW");
            //mock1.Set(MyMessageBox1);

            auto stat2 = winrt::Microsoft::ProjectReunion::PowerManager::DisplayStatus();
            VERIFY_ARE_EQUAL(stat2, 0);
        }

        TEST_METHOD(GetDischargeTime)
        {
            auto time = winrt::Microsoft::ProjectReunion::PowerManager::RemainingDischargeTime().count();
            VERIFY_ARE_SAME(time, 7);
        }
    };
}
