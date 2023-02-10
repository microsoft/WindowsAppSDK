// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationSubgroup.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct AppNotificationSubgroup : AppNotificationSubgroupT<AppNotificationSubgroup, winrt::Windows::Foundation::IStringable>
    {
        AppNotificationSubgroup() = default;

        void TextStacking(AppNotificationTextStacking const& value) { m_textStacking = value; };
        AppNotificationTextStacking TextStacking() { return m_textStacking; };

        void Weight(int const& value) { m_weight = value; };
        int Weight() { return m_weight; };

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationSubgroup SetTextStacking(AppNotificationTextStacking const& textStacking);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationSubgroup SetWeight(int weight);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationSubgroup AddText(hstring const& text);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationSubgroup AddText(hstring const& text, AppNotificationExtendedTextProperties const& properties);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationSubgroup SetImage(winrt::Windows::Foundation::Uri const& imageUri);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationSubgroup SetImage(winrt::Windows::Foundation::Uri const& imageUri, AppNotificationExtendedImageProperties const& imageCrop);

        // IStringable
        winrt::hstring ToString();

    private:
        std::wstring GetText();

        AppNotificationTextStacking m_textStacking{};
        int m_weight{};

        std::vector<winrt::hstring> m_textLines{};
    };
}

namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct AppNotificationSubgroup : AppNotificationSubgroupT<AppNotificationSubgroup, implementation::AppNotificationSubgroup>
    {
    };
}
