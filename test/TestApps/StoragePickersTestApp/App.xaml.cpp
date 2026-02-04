#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"
#include <windows.h>
#include <sstream>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::StoragePickersTestApp::implementation
{
    /// <summary>
    /// Initializes the singleton application object.  This is the first line of authored code
    /// executed, and as such is the logical equivalent of main() or WinMain().
    /// </summary>
    App::App()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

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
        try
        {
            window = make<MainWindow>();
            window.Activate();
        }
        catch (winrt::hresult_error const& ex)
        {
            std::wstringstream ss;
            ss << L"OnLaunched failed!\n\nHRESULT: 0x" << std::hex << static_cast<uint32_t>(ex.code()) 
               << L"\n\nMessage: " << ex.message().c_str();
            MessageBoxW(nullptr, ss.str().c_str(), L"StoragePickersTestApp Error", MB_OK | MB_ICONERROR);
        }
        catch (std::exception const& ex)
        {
            std::wstringstream ss;
            ss << L"OnLaunched failed!\n\nstd::exception: " << ex.what();
            MessageBoxW(nullptr, ss.str().c_str(), L"StoragePickersTestApp Error", MB_OK | MB_ICONERROR);
        }
        catch (...)
        {
            MessageBoxW(nullptr, L"OnLaunched failed with unknown exception!", L"StoragePickersTestApp Error", MB_OK | MB_ICONERROR);
        }
    }
}
