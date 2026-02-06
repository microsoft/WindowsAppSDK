// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"

#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Windows.Graphics.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::StoragePickersTestApp::implementation
{
    App::App()
    {
#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
        UnhandledException([](IInspectable const&, UnhandledExceptionEventArgs const& e)
        {
            if (IsDebuggerPresent())
            {
                auto errorMessage = e.Message();
                __debugbreak();
            }
        });
#endif
    }

    void App::OnLaunched([[maybe_unused]] LaunchActivatedEventArgs const& e)
    {
        window = make<MainWindow>();
        window.as<MainWindow>()->InitializeDefaults();

        if (auto appWindow = window.AppWindow())
        {
            appWindow.Resize(winrt::Windows::Graphics::SizeInt32{ 1800, 1220 });
        }

        window.Activate();
    }
}
