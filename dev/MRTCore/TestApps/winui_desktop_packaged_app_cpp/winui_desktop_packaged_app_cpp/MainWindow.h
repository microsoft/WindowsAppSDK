// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#pragma push_macro("GetCurrentTime")
#undef GetCurrentTime

#include "MainWindow.g.h"

#pragma pop_macro("GetCurrentTime")

#ifdef MRM_C_API_AVAILABLE // This API is not present in the current release package.
#include <MRM.h>
#endif

#include <winrt/Microsoft.ApplicationModel.Resources.h>

namespace winrt::winui_desktop_packaged_app_cpp::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();
        ~MainWindow();

#ifdef MRM_C_API_AVAILABLE // This API is not present in the current release package.
        void InitializeResourceLoaders(winrt::Microsoft::ApplicationModel::Resources::ResourceManager resourceManagerWinRT, MrmManagerHandle resourceManagerMrm);
#else
        void InitializeResourceLoaders(winrt::Microsoft::ApplicationModel::Resources::ResourceManager resourceManagerWinRT);
#endif

        void defaultWinrtApi_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void overrideWinrtApi_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void fallbackWinrt_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

        void defaultCApi_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void overrideCApi_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

    private:
        winrt::Microsoft::ApplicationModel::Resources::ResourceContext m_overrideResourceContext{ nullptr };
        winrt::Microsoft::ApplicationModel::Resources::ResourceManager m_resourceManagerWinRT{ nullptr };

#ifdef MRM_C_API_AVAILABLE // This API is not present in the current release package.
        MrmManagerHandle m_resourceManagerMrm{ nullptr };
        MrmContextHandle m_overrideResourceContextMrm{ nullptr };
#endif
    };
}

namespace winrt::winui_desktop_packaged_app_cpp::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
