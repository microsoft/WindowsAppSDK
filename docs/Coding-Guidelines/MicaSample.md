# Using a SystemBackdropController with WinUI3 XAML

The `Microsoft.UI.Composition.SystemBackdrops.MicaController` and `Microsoft.UI.Composition.SystemBackdrops.DesktopAcrylicController` can be used with a `Microsoft.UI.Xaml.Window` as a compatible `Microsoft.UI.Composition.ICompositionSupportsSystemBackdrop` target. We just need to ensure that the following 3 pieces are wired up:

1. An available `Windows.System.DispatcherQueue` on the main XAML thread.
2. The `Microsoft.UI.Composition.SystemBackdrops.SystemBackdropConfiguration` object.
3. The `Microsoft.UI.Xaml.Window` as a target on the required SystemBackdropController.

Here's an example of how to set up Mica using C++/WinRT.

```c++
namespace winrt
{
    namespace Microsoft.UI.Composition = MUC;
    namespace Microsoft.UI.Composition.SystemBackdrops = MUCSB;
    namespace Microsoft.UI.Xaml = MUX;
    namespace Windows.System = WS;
}

namespace winrt::WinUICppDesktopSampleApp::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        winrt::MUCSB::SystemBackdropConfiguration m_configuration{ nullptr };
        winrt::MUCSB::MicaController m_micaController{ nullptr };
        winrt::MUX::Window::Activated_revoker m_activatedRevoker;
        winrt::MUX::Window::Closed_revoker m_closedRevoker;
        winrt::MUX::FrameworkElement::ActualThemeChanged_revoker m_themeChangedRevoker;
        winrt::MUX::FrameworkElement m_rootElement{ nullptr };
        winrt::WS::DispatcherQueueController m_dispatcherQueueController{ nullptr };

        MainWindow()
        {
            SetBackground();

            m_closedRevoker = this->Closed(winrt::auto_revoke, [&](auto&&, auto&&)
            {
                if (nullptr != m_micaController)
                {
                    m_micaController.Close();
                    m_micaController = nullptr;
                }

                if (nullptr != m_dispatcherQueueController)
                {
                    m_dispatcherQueueController.ShutdownQueueAsync();
                    m_dispatcherQueueController = nullptr;
                }
            });
        }

        void SetBackground()
        {
            if (winrt::MUCSB::MicaController::IsSupported())
            {
                // We ensure that there is a Windows.System.DispatcherQueue on the current thread.
                // Always check if one already exists before attempting to create a new one.
                if (nullptr != winrt::WS::DispatcherQueue::GetForCurrentThread() &&
                    nullptr == m_dispatcherQueueController)
                {
                    m_dispatcherQueueController = CreateSystemDispatcherQueueController();
                }

                // Setup the SystemBackdropConfiguration object.
                SetupSystemBackdropConfiguration();

                // Setup Mica on the current Window.
                m_micaController = winrt::MUCSB::MicaController();
                m_micaController.SetSystemBackdropConfiguration(m_configuration);
                m_micaController.AddSystemBackdropTarget(
                    this->as<winrt::MUC::ICompositionSupportsSystemBackdrop>());
            }
            else
            {
                // No Mica support.
            }
        }

        winrt::WS::DispatcherQueueController CreateSystemDispatcherQueueController()
        {
            DispatcherQueueOptions options
            {
                sizeof(DispatcherQueueOptions),
                DQTYPE_THREAD_CURRENT,
                DQTAT_COM_NONE
            };

            ::ABI::Windows::System::IDispatcherQueueController* ptr{ nullptr };
            winrt::check_hresult(CreateDispatcherQueueController(options, &ptr));
            return { ptr, take_ownership_from_abi };
        }

        void SetupSystemBackdropConfiguration()
        {
            m_configuration = winrt::MUCSB::SystemBackdropConfiguration();

            // Activation state.
            m_activatedRevoker = this->Activated(winrt::auto_revoke,
                                        [&](auto&&, MUX::WindowActivatedEventArgs const& args)
            {
                m_configuration.IsInputActive(
                    winrt::MUX::WindowActivationState::Deactivated != args.WindowActivationState());
            });

            // Initial state.
            m_configuration.IsInputActive(true);

            // Application theme.
            m_rootElement = this->Content().try_as<winrt::MUX::FrameworkElement>();
            if (nullptr != m_rootElement)
            {
                m_themeChangedRevoker = rootElement.ActualThemeChanged(winrt::auto_revoke,
                                                                [&](auto&&, auto&&)
                {
                    m_configuration.Theme(
                        ConvertToSystemBackdropTheme(m_rootElement.ActualTheme()));
                });

                // Initial state.
                m_configuration.Theme(
                        ConvertToSystemBackdropTheme(m_rootElement.ActualTheme()));
            }
        }

        winrt::MUCSB::SystemBackdropTheme ConvertToSystemBackdropTheme(
            winrt::MUX::ElementTheme const& theme)
        {
            switch (theme)
            {
            case winrt::MUX::ElementTheme::Dark:
                return winrt::MUCSB::SystemBackdropTheme::Dark;
            case winrt::MUX::ElementTheme::Light:
                return winrt::MUCSB::SystemBackdropTheme::Light;
            default:
                return winrt::MUCSB::SystemBackdropTheme::Default;
            }
        }
    }
}
```
