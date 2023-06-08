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
        m_id = EncodeXml(id).c_str();
    };

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationComboBox AppNotificationComboBox::AddItem(winrt::hstring const& id, winrt::hstring const& content)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, m_items.Size() >= c_maxSelectionElements, "Maximum number of items added");
        THROW_HR_IF_MSG(E_INVALIDARG, id.empty(), "You must provide an id for the item");

        m_items.Insert(EncodeXml(id).c_str(), EncodeXml(content).c_str());

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationComboBox AppNotificationComboBox::SetTitle(winrt::hstring const& value)
    {
        m_title = EncodeXml(value).c_str();

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationComboBox AppNotificationComboBox::SetSelectedItem(winrt::hstring const& id)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, id.empty(), "You must provide an id for the selected item");

        m_selectedItem = EncodeXml(id).c_str();

        return *this;
    }

    std::wstring AppNotificationComboBox::GetSelectionItems()
    {
        std::wstring items{};

        for (auto pair : m_items)
        {
            items.append(wil::str_printf<std::wstring>(L"<selection id='%ls' content='%ls'/>", pair.Key().c_str(), pair.Value().c_str()));
        }

        return items;
    }

    winrt::hstring AppNotificationComboBox::ToString()
    {
        auto logTelemetry{ AppNotificationBuilderTelemetry::ComboBoxToString::Start(g_telemetryHelper) };

        std::wstring xmlResult{ wil::str_printf<std::wstring>(L"<input id='%ls' type='selection'%ls%ls>%ls</input>",
            m_id.c_str(),
            m_title.empty() ? L"" : wil::str_printf<std::wstring>(L" title='%ls'", m_title.c_str()).c_str(),
            m_selectedItem.empty() ? L"" : wil::str_printf<std::wstring>(L" defaultInput='%ls'", m_selectedItem.c_str()).c_str(),
            GetSelectionItems().c_str()) };

        logTelemetry.Stop();

        return xmlResult.c_str();
    }
}
