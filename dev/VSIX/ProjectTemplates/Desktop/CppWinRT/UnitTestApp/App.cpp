#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::$safeprojectname$::implementation
{
    /// <summary>
    /// Initializes the singleton application object.  This is the first line of authored code
    /// executed, and as such is the logical equivalent of main() or WinMain().
    /// </summary>
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
        winrt::Microsoft::VisualStudio::TestPlatform::WinRTTestExecutor::UnitTestClient::CreateDefaultUI();

        window = make<MainWindow>();
        window.Activate();

        winrt::Microsoft::VisualStudio::TestPlatform::WinRTTestExecutor::UnitTestClient::Run(m_args);
    }
}


#ifdef DISABLE_XAML_GENERATED_MAIN

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR argv, int)
{
    winrt::init_apartment(winrt::apartment_type::single_threaded);

    ::winrt::Microsoft::UI::Xaml::Application::Start(
        [argv](auto&&)
        {
            ::winrt::make<::winrt::WinUI3CppWinRTApp1::implementation::App>(argv);
        });

    return 0;
}

#endif