// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "App.xaml.h"
#include <windows.h>
#include <sstream>
#include <iomanip>

std::wstring FormatHResult(HRESULT hr)
{
    std::wstringstream ss;
    ss << L"0x" << std::hex << std::setfill(L'0') << std::setw(8) << static_cast<unsigned int>(hr);
    return ss.str();
}

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    try
    {
        winrt::init_apartment(winrt::apartment_type::single_threaded);
    }
    catch (winrt::hresult_error const& ex)
    {
        std::wstring msg = L"init_apartment failed!\n\nHRESULT: " + FormatHResult(ex.code()) +
            L"\n\nMessage: " + ex.message().c_str();
        MessageBoxW(nullptr, msg.c_str(), L"StoragePickersTestApp - Startup Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    try
    {
        ::winrt::Microsoft::UI::Xaml::Application::Start(
            [](auto&&)
            {
                try
                {
                    ::winrt::make<::winrt::StoragePickersTestApp::implementation::App>();
                }
                catch (winrt::hresult_error const& ex)
                {
                    std::wstring msg = L"App creation failed!\n\nHRESULT: " + FormatHResult(ex.code()) +
                        L"\n\nMessage: " + ex.message().c_str();
                    MessageBoxW(nullptr, msg.c_str(), L"StoragePickersTestApp - App Error", MB_OK | MB_ICONERROR);
                    throw;
                }
            });
    }
    catch (winrt::hresult_error const& ex)
    {
        std::wstring msg = L"Application::Start failed!\n\nHRESULT: " + FormatHResult(ex.code()) +
            L"\n\nMessage: " + ex.message().c_str();
        MessageBoxW(nullptr, msg.c_str(), L"StoragePickersTestApp - Start Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    catch (std::exception const& ex)
    {
        std::wstringstream ss;
        ss << L"Application::Start failed!\n\nstd::exception: " << ex.what();
        MessageBoxW(nullptr, ss.str().c_str(), L"StoragePickersTestApp - Start Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    catch (...)
    {
        MessageBoxW(nullptr, L"Application::Start failed with unknown exception!", 
            L"StoragePickersTestApp - Start Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    return 0;
}
