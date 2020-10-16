// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <AppLifecycle.g.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct AppLifecycle
    {
        AppLifecycle() = default;

        static Windows::ApplicationModel::Activation::IActivatedEventArgs GetActivatedEventArgs();

        static bool RegisterForFileTypeActivation(hstring const& groupName, Microsoft::ProjectReunion::DesiredView const& desiredView, hstring const& logo,
            array_view<hstring const> supportedFileTypes, array_view<hstring const> supportedVerbs);
        static bool RegisterForProtocolActivation(hstring const& name, Microsoft::ProjectReunion::DesiredView const& desiredView);
        static bool RegisterForStartupActivation(hstring const& taskId, bool isEnabled, hstring const& displayName);
        static bool RegisterForToastActivation(hstring const& displayName);

        static bool UnregisterForFileTypeActivation(hstring const& groupName);
        static bool UnregisterForProtocolActivation(hstring const& name);
        static bool UnregisterForStartupActivation();
        static bool UnregisterForToastActivation();
    };
}

namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct AppLifecycle : AppLifecycleT<AppLifecycle, implementation::AppLifecycle>
    {
    };
}
