#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"

#include "CppUnitTest.h"
#include <winrt/Microsoft.VisualStudio.TestPlatform.TestExecutor.WinRTCore.h>

using namespace winrt::Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::$safeprojectname$::implementation
{
    App::App(PWSTR argv)
    {
        m_args = argv;

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

    /// <summary>
    /// Invoked when the application is launched.
    /// </summary>
    /// <param name="e">Details about the launch request and process.</param>
    void App::OnLaunched([[maybe_unused]] LaunchActivatedEventArgs const& e)
    {
        winrt::Microsoft::VisualStudio::TestPlatform::TestExecutor::WinRTCore::UnitTestClient::CreateDefaultUI();

        window = make<MainWindow>();
        window.Activate();

        winrt::Microsoft::VisualStudio::TestPlatform::TestExecutor::WinRTCore::UnitTestClient::Run(m_args);
    }
}


#ifdef DISABLE_XAML_GENERATED_MAIN

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR argv, int)
{
    winrt::init_apartment(winrt::apartment_type::single_threaded);

    ::winrt::Microsoft::UI::Xaml::Application::Start(
        [argv](auto&&)
        {
            ::winrt::make<::winrt::$safeprojectname$::implementation::App>(argv);
        });

    return 0;
}

#endif