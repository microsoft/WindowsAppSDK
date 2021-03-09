// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <Microsoft.ApplicationModel.Activation.ActivationRegistrationManager.g.h>

namespace winrt::Microsoft::ApplicationModel::Activation::implementation
{
    struct ActivationRegistrationManager
    {
        ActivationRegistrationManager() = default;

        static void RegisterForFileTypeActivation(array_view<hstring const> supportedFileTypes,
            array_view<hstring const> supportedVerbs, hstring const& applicationDisplayName,
            hstring const& logo);
        static void RegisterForProtocolActivation(hstring const& scheme,
            hstring const& applicationDisplayName, hstring const& logo);

        static void UnregisterForFileTypeActivation(hstring const& fileType);
        static void UnregisterForProtocolActivation(hstring const& scheme);
    };
}

namespace winrt::Microsoft::ApplicationModel::Activation::factory_implementation
{
    struct ActivationRegistrationManager : ActivationRegistrationManagerT<ActivationRegistrationManager,
        implementation::ActivationRegistrationManager>
    {
    };
}
