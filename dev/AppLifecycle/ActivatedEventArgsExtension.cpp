#include "pch.h"
#include "ActivatedEventArgsExtension.h"
#include "ActivatedEventArgsExtension.g.cpp"


namespace winrt::Microsoft::ProjectReunion::implementation
{
    std::mutex ActivatedEventArgsExtension::s_mutex;
    std::unique_lock<std::mutex> ActivatedEventArgsExtension::s_lock(s_mutex, std::defer_lock); // Avoid locking during the constructor call

    ActivatedEventArgsExtension::ActivatedEventArgsExtension(Windows::ApplicationModel::Activation::IActivatedEventArgs const& activatedEventArgs, Microsoft::ProjectReunion::ActivationKindExtension const& kind2)
    {
        m_activatedEventArgs = activatedEventArgs;
        m_kind2 = kind2;
    }
    Microsoft::ProjectReunion::ActivationKindExtension ActivatedEventArgsExtension::Kind2()
    {
        s_lock.lock();
        return m_kind2;
    }
    Windows::ApplicationModel::Activation::IActivatedEventArgs ActivatedEventArgsExtension::ActivatedArgs()
    {
        s_lock.lock();
        return m_activatedEventArgs;
    }
}
