#include "pch.h"
//#include "PowerTests.h"
#include "winrt/Microsoft.ProjectReunion.h"

using PowerEventHandle =
winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable>;

using namespace winrt::Microsoft::ProjectReunion;

namespace ProjectReunionPowerTests
{
    class PowerTests
    {
    public:
        BEGIN_TEST_CLASS(PowerTests)
            TEST_CLASS_PROPERTY(L"ActivationContext", L"PowerTests.dll.manifest")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            END_TEST_CLASS()

        TEST_METHOD(GetDisplayStatusTest)
        {
            auto stat = PowerManager::DisplayStatus();
            VERIFY_ARE_EQUAL(stat, DisplayStatus::Dimmed);
        }
        TEST_METHOD(DisplayStatusCallbackTest)
        {
            bool callbackSuccessful = false;
            auto token = PowerManager::DisplayStatusChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
                {
                    //auto value = obj.as<int>();
                    callbackSuccessful = true;
                });
            PowerManager::DisplayStatusChanged(token);
            VERIFY_ARE_EQUAL(callbackSuccessful, true);
        }

    };
}
