// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include "Microsoft.ApplicationModel.Activation.ActivationArguments.g.h"

namespace winrt::Microsoft::ApplicationModel::Activation::implementation
{
    struct ActivationArguments : ActivationArgumentsT<ActivationArguments>
    {
        ActivationArguments(Windows::ApplicationModel::Activation::IActivatedEventArgs platformArgs)
        {
            m_kind = static_cast<ExtendedActivationKind>(platformArgs.Kind());
            m_data = platformArgs.as<IInspectable>();
        }

        ActivationArguments(ExtendedActivationKind kind, IInspectable const& data)
        {
            m_kind = kind;
            m_data = data;
        }

        Microsoft::ApplicationModel::Activation::ExtendedActivationKind Kind() { return m_kind; }
        Windows::Foundation::IInspectable Data() { return m_data; }

    private:
        ActivationArguments() = default;

        ExtendedActivationKind m_kind{};
        IInspectable m_data;
    };
}
