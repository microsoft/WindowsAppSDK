// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "App.h"
#include "MainWindow.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Navigation;
using namespace winui_desktop_packaged_app_cpp;
using namespace winui_desktop_packaged_app_cpp::implementation;
using namespace winrt::Microsoft::ApplicationModel::Resources;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

/// <summary>
/// Initializes the singleton application object.  This is the first line of authored code
/// executed, and as such is the logical equivalent of main() or WinMain().
/// </summary>
App::App()
{
    InitializeComponent();
    Suspending({ this, &App::OnSuspending });

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
    UnhandledException([this](IInspectable const&, UnhandledExceptionEventArgs const& e)
    {
        if (IsDebuggerPresent())
        {
            auto errorMessage = e.Message();
            __debugbreak();
        }
    });
#endif
}

App::~App()
{
    //MrmDestroyResourceManager(m_resourceManagerMrm);
}

/// <summary>
/// Invoked when the application is launched normally by the end user.  Other entry points
/// will be used such as when the application is launched to open a specific file.
/// </summary>
/// <param name="e">Details about the launch request and process.</param>
void App::OnLaunched(LaunchActivatedEventArgs const&)
{
    m_resourceManagerWinRT = ResourceManager(L"resources.pri");
    //check_hresult(MrmCreateResourceManager(L"resources.pri", &m_resourceManagerMrm));

    m_resourceManagerWinRT.ResourceNotFound([](ResourceManager const&, ResourceNotFoundEventArgs const& args)
        {
            // There could be a resource in a legacy resource file that we retrieve using the corresponding legacy resource loader. For example, the C#
            // app in this repo uses the .NET resource loader as its fallback. Instead, we just hardcode a resource value here.
            if (args.Name() == L"Resources/LegacyString")
            {
                auto candidate = ResourceCandidate(ResourceCandidateKind::String, L"Legacy Sample");
                args.SetResolvedCandidate(candidate);
            }
        });

    m_window = make<MainWindow>();

    auto window = m_window.as<winrt::winui_desktop_packaged_app_cpp::implementation::MainWindow>();
    window->InitializeResourceLoaders(m_resourceManagerWinRT/*, m_resourceManagerMrm*/);

    m_window.Activate();
}

/// <summary>
/// Invoked when application execution is being suspended.  Application state is saved
/// without knowing whether the application will be terminated or resumed with the contents
/// of memory still intact.
/// </summary>
/// <param name="sender">The source of the suspend request.</param>
/// <param name="e">Details about the suspend request.</param>
void App::OnSuspending([[maybe_unused]] IInspectable const& sender, [[maybe_unused]] Windows::ApplicationModel::SuspendingEventArgs const& e)
{
    // Save application state and stop any background activity
}
