// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationExtendedImageProperties.g.h"
#include "AppNotificationImageProperties.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct AppNotificationExtendedImageProperties : AppNotificationExtendedImagePropertiesT<AppNotificationExtendedImageProperties, winrt::Windows::Foundation::IStringable>
    {
        AppNotificationExtendedImageProperties();

        // AppNotificationExtendedImageProperties Properties
        void Align(AppNotificationImageAlign const& value) { m_align = value; };
        AppNotificationImageAlign Align() { return m_align; };

        void RemoveMargin(bool const& value) { m_removeMargin = value; };
        bool RemoveMargin() { return m_removeMargin; };

        // AppNotificationImageProperties Properties
        void ImageQuery(bool const& value) { m_basicImageProperties->ImageQuery(value); };
        bool ImageQuery() { return m_basicImageProperties->ImageQuery(); };

        void AlternateText(winrt::hstring const& value) { m_basicImageProperties->AlternateText(value); };
        winrt::hstring AlternateText() { return m_basicImageProperties->AlternateText(); };

        void Crop(AppNotificationImageCrop const& value) { m_basicImageProperties->Crop(value); };
        AppNotificationImageCrop Crop() { return m_basicImageProperties->Crop(); };

        // AppNotificationExtendedImageProperties Fluent Setters
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedImageProperties SetAlign(AppNotificationImageAlign const& align);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedImageProperties SetRemoveMargin();

        // AppNotificationImageProperties Fluent Setters
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedImageProperties SetImageQuery();
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedImageProperties SetAlternateText(winrt::hstring const& alternateText);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedImageProperties SetCrop(AppNotificationImageCrop const& crop);

        // IStringable
        winrt::hstring ToString();

    private:
        //std::wstring AlignToString();

        winrt::com_ptr<AppNotificationImageProperties> m_basicImageProperties;

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
