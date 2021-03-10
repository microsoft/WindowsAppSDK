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

        private:
            Windows::ApplicationModel::Activation::IActivatedEventArgs m_activatedEventArgs;
            ActivationKindExtension m_kind2;

            static std::mutex s_mutex;
            static std::unique_lock<std::mutex> s_lock;
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct ActivatedEventArgsExtension : ActivatedEventArgsExtensionT<ActivatedEventArgsExtension, implementation::ActivatedEventArgsExtension>
    {
    };
}
