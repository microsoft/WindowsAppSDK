// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "externs.h"
#include "AppNotificationComboBox.h"
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationComboBox.g.cpp"
#include "AppNotificationBuilderUtility.h"
#include "AppNotificationBuilderTelemetry.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    AppNotificationComboBox::AppNotificationComboBox(hstring const& id)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, id.empty(), "You must provide an id for the ComboBox");
        m_id = id;
    };

    void AppNotificationComboBox::Items(winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> const& value)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, value.Size() >= c_maxSelectionElements, "Can't excceed the maximum number of items");
        THROW_HR_IF_MSG(E_INVALIDARG, value.HasKey(L""), "You must provide an id for every item");

        m_items = value;
    }

    void AppNotificationComboBox::SelectedItem(winrt::hstring const& value)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, value.empty(), "You must provide an id for the selected item");

        m_selectedItem = value;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationComboBox AppNotificationComboBox::AddItem(winrt::hstring const& id, winrt::hstring const& content)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, m_items.Size() >= c_maxSelectionElements, "Maximum number of items added");
        THROW_HR_IF_MSG(E_INVALIDARG, id.empty(), "You must provide an id for the item");

        m_items.Insert(id, content);

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationComboBox AppNotificationComboBox::SetTitle(winrt::hstring const& value)
    {
        m_title = value;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationComboBox AppNotificationComboBox::SetSelectedItem(winrt::hstring const& id)
    {
        SelectedItem(id);

        return *this;
    }

    std::wstring AppNotificationComboBox::GetSelectionItems()
    {
        std::wstring items{};

        for (auto pair : m_items)
        {
            items.append(wil::str_printf<std::wstring>(L"<selection id='%ls' content='%ls'/>", EncodeXml(pair.Key().c_str()).c_str(), EncodeXml(pair.Value().c_str()).c_str()));
        }

        return items;
    }

    winrt::hstring AppNotificationComboBox::ToString()
    {
        auto logTelemetry{ AppNotificationBuilderTelemetry::ComboBoxToString::Start(g_telemetryHelper) };

        std::wstring xmlResult{ wil::str_printf<std::wstring>(L"<input id='%ls' type='selection'%ls%ls>%ls</input>",
            EncodeXml(m_id.c_str()).c_str(),
            m_title.empty() ? L"" : wil::str_printf<std::wstring>(L" title='%ls'", EncodeXml(m_title.c_str()).c_str()).c_str(),
            m_selectedItem.empty() ? L"" : wil::str_printf<std::wstring>(L" defaultInput='%ls'", EncodeXml(m_selectedItem.c_str()).c_str()).c_str(),
            GetSelectionItems().c_str()) };

        logTelemetry.Stop();

        return xmlResult.c_str();
    }
}
