// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <ActivationRegistrationManager.g.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct ActivationRegistrationManager
    {
        ActivationRegistrationManager() = default;

        static void RegisterForFileTypeActivation(hstring const& groupName, hstring const& logo,
            array_view<hstring const> supportedFileTypes, array_view<hstring const> supportedVerbs);
        static void RegisterForProtocolActivation(hstring const& scheme, hstring const& displayName);

        static void UnregisterForFileTypeActivation(hstring const& groupName, hstring const& fileType);
        static void UnregisterForProtocolActivation(hstring const& scheme);
    };
}

namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct ActivationRegistrationManager : ActivationRegistrationManagerT<ActivationRegistrationManager,
        implementation::ActivationRegistrationManager>
    {
    };
}
