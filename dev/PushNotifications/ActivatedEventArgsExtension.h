// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "ActivatedEventArgsExtension.g.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct ActivatedEventArgsExtension : ActivatedEventArgsExtensionT<ActivatedEventArgsExtension>
    {
        ActivatedEventArgsExtension() = default;

        ActivatedEventArgsExtension(Windows::ApplicationModel::Activation::IActivatedEventArgs const& activatedEventArgs, Microsoft::ProjectReunion::ActivationKindExtension const& kind2);
        Microsoft::ProjectReunion::ActivationKindExtension Kind2();
        Windows::ApplicationModel::Activation::IActivatedEventArgs ActivatedArgs();
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct ActivatedEventArgsExtension : ActivatedEventArgsExtensionT<ActivatedEventArgsExtension, implementation::ActivatedEventArgsExtension>
    {
    };
}
