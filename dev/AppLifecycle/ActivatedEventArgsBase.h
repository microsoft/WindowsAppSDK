// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
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

        ActivationKind m_kind{ ActivationKind::Launch };
        ApplicationExecutionState m_previousState{ ApplicationExecutionState::NotRunning };
        winrt::Windows::ApplicationModel::Activation::SplashScreen m_splashScreen{ nullptr };
    };
}
