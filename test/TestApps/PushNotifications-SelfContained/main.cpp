#include "pch.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace winrt::Microsoft::Windows::AppLifecycle;

int main()
{
    auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
    return 0;
}
