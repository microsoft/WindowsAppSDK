// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationExtendedImageProperties.g.h"
#include "AppNotificationImageProperties.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct AppNotificationExtendedImageProperties : AppNotificationExtendedImagePropertiesT<AppNotificationExtendedImageProperties, implementation::AppNotificationImageProperties>
    {
        AppNotificationExtendedImageProperties() = default;

        // Properties
        void Align(AppNotificationImageAlign const& value) { m_align = value; };
        AppNotificationImageAlign Align() { return m_align; };

        void RemoveMargin(bool const& value) { m_removeMargin = value; };
        bool RemoveMargin() { return m_removeMargin; };

        // Fluent Setters
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedImageProperties SetAlign(AppNotificationImageAlign const& align);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedImageProperties SetRemoveMargin();

        // IStringable
        winrt::hstring ToString();

    private:
        //std::wstring AlignToString();

        AppNotificationImageAlign m_align{};
        bool m_removeMargin{};
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct AppNotificationExtendedImageProperties : AppNotificationExtendedImagePropertiesT<AppNotificationExtendedImageProperties, implementation::AppNotificationExtendedImageProperties>
    {
    };
}
