// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationImageProperties.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct AppNotificationImageProperties : AppNotificationImagePropertiesT<AppNotificationImageProperties, winrt::Windows::Foundation::IStringable>
    {
        AppNotificationImageProperties() = default;

        // Properties
        void ImageQuery(bool const& value) { m_imageQuery = value; };
        bool ImageQuery() { return m_imageQuery; };

        void AlternateText(winrt::hstring const& value) { m_alternateText = value; };
        winrt::hstring AlternateText() { return m_alternateText; };

        void Crop(AppNotificationImageCrop const& value) { m_crop = value; };
        AppNotificationImageCrop Crop() { return m_crop; };

        // Fluent Setters
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationImageProperties SetImageQuery();
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationImageProperties SetAlternateText(winrt::hstring const& alternateText);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationImageProperties SetCrop(AppNotificationImageCrop const& crop);

        // IStringable
        winrt::hstring ToString();

    protected:
        bool m_imageQuery{};
        winrt::hstring m_alternateText{};
        AppNotificationImageCrop m_crop{};
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct AppNotificationImageProperties : AppNotificationImagePropertiesT<AppNotificationImageProperties, implementation::AppNotificationImageProperties>
    {
    };
}
