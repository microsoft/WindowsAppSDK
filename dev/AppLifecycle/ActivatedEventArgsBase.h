// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

namespace winrt::Microsoft::ApplicationModel::Activation::implementation
{
    using namespace winrt::Windows::ApplicationModel::Activation;

    class ActivatedEventArgsBase : public winrt::implements<ActivatedEventArgsBase,
        IActivatedEventArgs>
    {
    public:
        // IActivatedEventArgs
        ActivationKind Kind()
        {
            return m_kind;
        }

        ApplicationExecutionState PreviousExecutionState()
        {
            return m_previousState;
        }

        SplashScreen SplashScreen()
        {
            return m_splashScreen;
        }

    protected:
        ActivatedEventArgsBase() = default;

        ActivationKind m_kind = ActivationKind::Launch;
        ApplicationExecutionState m_previousState;
        winrt::Windows::ApplicationModel::Activation::SplashScreen m_splashScreen{ nullptr };
    };
}

