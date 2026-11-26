// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <testdef.h>
#include <string>
#include <wil/win32_helpers.h>
#include <winrt/Microsoft.Windows.Security.AccessControl.h>

#include <Security.AccessControl.h>

using namespace winrt;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::Foundation;


int APIENTRY wWinMain(
    _In_ HINSTANCE,
    _In_opt_ HINSTANCE,
    _In_ LPWSTR,
    _In_ int) try
{
    winrt::init_apartment();

    auto packageId = Windows::ApplicationModel::Package::Current().Id();
    auto familyName = packageId.FamilyName();
    OutputDebugStringW((L"Family name: " + std::wstring(familyName) + L"\n").c_str());

    wil::unique_event win32_event;

    DWORD lastError = ERROR_TIMEOUT;
    for (int i = 0; i < 100 && !win32_event.is_valid(); ++i)
    {
        if (win32_event.try_open(L"AccessControlTest_Event", SYNCHRONIZE | EVENT_MODIFY_STATE))
        {
            break;
        }
        lastError = ::GetLastError();
        OutputDebugStringW(L"Waiting to open event...\n");
        ::Sleep(100);
    }
    if (!win32_event.is_valid())
    {
        OutputDebugStringW(L"Timed out opening event.\n");
        THROW_WIN32(lastError);
    }
    win32_event.SetEvent();

    return 0;
}
catch (...)
{
    OutputDebugStringW((std::wstring(winrt::to_message()) + L"\n").c_str());
    return 1; // in the event of unhandled test crash
}
