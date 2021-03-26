#pragma once
#include <NotificationActivationArguments.g.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct NotificationActivationArguments : NotificationActivationArgumentsT<NotificationActivationArguments>
    {
        NotificationActivationArguments(Windows::ApplicationModel::Activation::IActivatedEventArgs platformArgs)
        {
            m_kind = static_cast<NotificationActivationKind>(platformArgs.Kind());
            m_data = platformArgs.as<IInspectable>();
        }

        NotificationActivationArguments(NotificationActivationKind kind, IInspectable const& data)
        {
            m_kind = kind;
            m_data = data;
        }

        Microsoft::ProjectReunion::NotificationActivationKind Kind() { return m_kind; }
        Windows::Foundation::IInspectable Data() { return m_data; }

    private:
        NotificationActivationArguments() = default;

        NotificationActivationKind m_kind{};
        IInspectable m_data;
    };
}
