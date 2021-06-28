#include "pch.h"
#include <winrt/Microsoft.ProjectReunion.h>
#include <winrt/Windows.System.Power.h>
#include <iostream>
#include <mutex>
#include <Windows.h>

using namespace winrt;
using namespace std;
using namespace Windows::Foundation;
using namespace winrt::Microsoft::ProjectReunion;
using namespace Windows;

std::mutex mtx;

void Pr(string st, int val)
{
    std::scoped_lock<std::mutex> lock(mtx);
    cout << st << val << endl;
}

int main()
{
    init_apartment();
    //auto val = PowerManager::BatteryStatus();
    //PowerManager::PowerSourceKindChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
    //    {
    //        cout << "Callback!";
    //    });
    //Pr("BatteryStatus Get() ", static_cast<int>(val));
    //Pr("BatteryStatus Get() ", static_cast<int>(PowerManager::RemainingChargePercent()));
    //Pr("BatteryStatus Get() ", static_cast<int>(PowerManager::PowerSupplyStatus()));

    auto def = System::Power::PowerManager::EnergySaverStatus();
    Pr("Org ", static_cast<int>(def));    
    //Pr("Query ", static_cast<int>(PowerManager::EnergySaverStatus()));
    PowerManager::EnergySaverStatusChanged([&](const auto&, winrt::Windows::Foundation::IInspectable obj)
    {
            Pr("CB ", static_cast<int>(PowerManager::EnergySaverStatus()));
    });
    //Sleep(500);
    getchar();
    auto def2 = System::Power::PowerManager::EnergySaverStatus();
    Pr("Org ", static_cast<int>(def2));
    Pr("Query ", static_cast<int>(PowerManager::EnergySaverStatus()));
    Sleep(3000);
}
