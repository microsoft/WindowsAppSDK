// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationComboBox2.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct AppNotificationComboBox2 : AppNotificationComboBox2T<AppNotificationComboBox2, winrt::Windows::Foundation::IStringable>
    {
        AppNotificationComboBox2(winrt::hstring const& id);

        // Properties
        void Title(winrt::hstring const& value) { m_title = value; };
        winrt::hstring Title() { return m_title; };

        void SelectedItem(winrt::hstring const& value) { m_selectedItem = value; };
        winrt::hstring SelectedItem() { return m_selectedItem; };

        // Fluent Setters
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationComboBox2 AddItem(winrt::hstring const& id, winrt::hstring const& content);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationComboBox2 SetTitle(winrt::hstring const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationComboBox2 SetSelectedItem(winrt::hstring const& id);

        // IStringable
        winrt::hstring ToString();

    private:
        winrt::hstring m_id{};
        winrt::Windows::Foundation::Collections::IVector<winrt::hstring> m_ids{ winrt::single_threaded_vector<winrt::hstring>() };
        winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> m_items{ winrt::single_threaded_map<winrt::hstring, winrt::hstring>() };
        winrt::hstring m_title{};
        winrt::hstring m_selectedItem{};

        std::wstring GetSelectionItems();
    };
}

namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct AppNotificationComboBox2 : AppNotificationComboBox2T<AppNotificationComboBox2, implementation::AppNotificationComboBox2>
    {
    };
}
