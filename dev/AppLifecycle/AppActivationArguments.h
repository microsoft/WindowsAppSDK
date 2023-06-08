// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once
#include "Microsoft.Windows.AppLifecycle.AppActivationArguments.g.h"

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{
    struct AppActivationArguments : AppActivationArgumentsT<AppActivationArguments>
    {
        AppActivationArguments() = delete;
        AppActivationArguments(const winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs& platformArgs)
        {
            m_kind = static_cast<ExtendedActivationKind>(platformArgs.Kind());
            m_data = platformArgs.as<IInspectable>();
        }

        AppActivationArguments(ExtendedActivationKind kind, IInspectable const& data)
        {
            m_kind = kind;
            m_data = data;
        }

        Microsoft::Windows::AppLifecycle::ExtendedActivationKind Kind() { return m_kind; }
        winrt::Windows::Foundation::IInspectable Data() { return m_data; }

    private:
        ExtendedActivationKind m_kind{};
        IInspectable m_data;
    };
}
