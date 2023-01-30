// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationSubgroup.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct AppNotificationSubgroup : AppNotificationSubgroupT<AppNotificationSubgroup, winrt::Windows::Foundation::IStringable>
    {
        AppNotificationSubgroup() = default;

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationSubgroup AddText(hstring const& text);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationSubgroup AddText(hstring const& text, AppNotificationTextProperties const& properties);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationSubgroup SetInlineImage(winrt::Windows::Foundation::Uri const& imageUri);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationSubgroup SetInlineImage(winrt::Windows::Foundation::Uri const& imageUri, AppNotificationImageCrop const& imageCrop);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationSubgroup SetInlineImage(winrt::Windows::Foundation::Uri const& imageUri, AppNotificationImageCrop const& imageCrop, winrt::hstring const& alternateText);

        // IStringable
        winrt::hstring ToString();

    private:
        std::wstring GetText();

        std::vector<winrt::hstring> m_textLines{};
    };
}

namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct AppNotificationSubgroup : AppNotificationSubgroupT<AppNotificationSubgroup, implementation::AppNotificationSubgroup>
    {
    };
}
