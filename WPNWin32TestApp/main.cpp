#include "pch.h"
#include <iostream>
using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Microsoft::ProjectReunion;

int main()
{
    auto args = AppLifecycle::GetActivatedEventArgs();
    std::cout << "Hello World!\n";
    return 0;
}
