// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// Custom entry point for StoragePickersTestApp.
// This replaces the auto-generated wWinMain (disabled via DISABLE_XAML_GENERATED_MAIN).

#include "pch.h"
#include "App.xaml.h"

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    winrt::init_apartment(winrt::apartment_type::single_threaded);

    ::winrt::Microsoft::UI::Xaml::Application::Start(
        [](auto&&)
        {
            ::winrt::make<::winrt::StoragePickersTestApp::implementation::App>();
        });

    return 0;
}
