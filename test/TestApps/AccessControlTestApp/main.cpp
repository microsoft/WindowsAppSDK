// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <testdef.h>
#include <iostream>
#include <sstream>
#include <wil/win32_helpers.h>
#include <winrt/Microsoft.Windows.Security.AccessControl.h>

#include <Security.AccessControl.h>

using namespace winrt;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::Foundation;


int main() try
{
    winrt::init_apartment();

    auto packageId = Windows::ApplicationModel::Package::Current().Id();
    auto familyName = packageId.FamilyName();
    std::wcout << L"Family name: " << familyName.data() << L"\n";

    wil::unique_event win32_event;

    for (int i = 0; i < 100 && !win32_event.is_valid(); ++i)
    {
        win32_event.try_open(L"AccessControlTest_Event", SYNCHRONIZE | EVENT_MODIFY_STATE);
        std::cout << "Waiting to open event...\n";
        ::Sleep(100);
    }
    if (!win32_event.is_valid())
    {
        std::cout << "Timed out creating event.\n";
        THROW_LAST_ERROR();
    }
    win32_event.SetEvent();

    return 0;
}
catch (...)
{
    std::cout << winrt::to_string(winrt::to_message()) << std::endl;
    return 1; // in the event of unhandled test crash
}
