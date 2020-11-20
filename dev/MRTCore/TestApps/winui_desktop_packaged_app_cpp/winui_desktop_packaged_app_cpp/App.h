// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#pragma push_macro("GetCurrentTime")
#undef GetCurrentTime

#include "App.xaml.g.h"

#pragma pop_macro("GetCurrentTime")

#ifdef MRM_C_API_AVAILABLE // This API is not present in the current release package.
#include "MRM.h"
#endif

#include "winrt/Microsoft.ApplicationModel.resources.h"

namespace winrt::winui_desktop_packaged_app_cpp::implementation
{
    struct App : AppT<App>
    {
        App();

        ~App();

        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);
        void OnSuspending(IInspectable const&, Windows::ApplicationModel::SuspendingEventArgs const&);

    private:
        winrt::Microsoft::UI::Xaml::Window m_window{ nullptr };

        winrt::Microsoft::ApplicationModel::Resources::ResourceManager m_resourceManagerWinRT{ nullptr };

#ifdef MRM_C_API_AVAILABLE // This API is not present in the current release package.
        MrmManagerHandle m_resourceManagerMrm{ nullptr };
#endif

        void SetWindowSize(const HWND& hwnd, int width, int height);
    };
}
