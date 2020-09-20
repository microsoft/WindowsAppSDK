#pragma once

#pragma push_macro("GetCurrentTime")
#undef GetCurrentTime

#include "MainWindow.g.h"

#pragma pop_macro("GetCurrentTime")

#include <MRM.h>
#include <winrt/Microsoft.ApplicationModel.Resources.h>

namespace winrt::winui_desktop_packaged_app_cpp::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();
        ~MainWindow();

        void InitializeResourceLoaders(winrt::Microsoft::ApplicationModel::Resources::ResourceManager resourceManagerWinRT, MrmManagerHandle resourceManagerMrm);        

        void defaultWinrtApi_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void overrideWinrtApi_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void fallbackWinrt_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

        void defaultCApi_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void overrideCApi_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

    private:
        winrt::Microsoft::ApplicationModel::Resources::ResourceContext m_overrideResourceContext{ nullptr };
        winrt::Microsoft::ApplicationModel::Resources::ResourceManager m_resourceManagerWinRT{ nullptr };

        MrmManagerHandle m_resourceManagerMrm{ nullptr };
        MrmContextHandle m_overrideResourceContextMrm{ nullptr };
    };
}

namespace winrt::winui_desktop_packaged_app_cpp::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
