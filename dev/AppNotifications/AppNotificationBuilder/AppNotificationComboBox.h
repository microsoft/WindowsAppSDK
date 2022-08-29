// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationComboBox.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct AppNotificationComboBox : AppNotificationComboBoxT<AppNotificationComboBox, winrt::Windows::Foundation::IStringable>
    {
        AppNotificationComboBox(winrt::hstring const& id);

        // Properties
        void Items(winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> const& value) { m_items = value; };
        winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> Items() { return m_items; };

        void Title(winrt::hstring const& value) { m_title = value; };
        winrt::hstring Title() { return m_title; };

        void SelectedItem(winrt::hstring const& value) { m_selectedItem = value; };
        winrt::hstring SelectedItem() { return m_selectedItem; };

        // Fluent Setters
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationComboBox AddItem(winrt::hstring const& id, winrt::hstring const& content);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationComboBox SetTitle(winrt::hstring const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationComboBox SetSelectedItem(winrt::hstring const& id);

        // IStringable
        winrt::hstring ToString();

    private:
        winrt::hstring m_id{};
        winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> m_items{ winrt::single_threaded_map<winrt::hstring, winrt::hstring>() };
        winrt::hstring m_title{};
        winrt::hstring m_selectedItem{};

        std::wstring GetSelectionItems();
    };
}

namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct AppNotificationComboBox : AppNotificationComboBoxT<AppNotificationComboBox, implementation::AppNotificationComboBox>
    {
    };
}
