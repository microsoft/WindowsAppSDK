#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.Button.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct Button : ButtonT<Button>
    {
        Button() = default;
        Button(winrt::hstring const& content);

        winrt::Microsoft::Windows::AppNotifications::Builder::Button AddArgument(winrt::hstring const& key, winrt::hstring const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::Button SetIconUri(winrt::Windows::Foundation::Uri const& iconUri);

        winrt::Microsoft::Windows::AppNotifications::Builder::Button SetToolTip(winrt::hstring const& toolTip);

        winrt::Microsoft::Windows::AppNotifications::Builder::Button SetInputId(winrt::hstring const& inputId);

        winrt::Microsoft::Windows::AppNotifications::Builder::Button SetProtocolActivation(winrt::Windows::Foundation::Uri const& protocolUri);
        winrt::Microsoft::Windows::AppNotifications::Builder::Button SetProtocolActivation(winrt::Windows::Foundation::Uri const& protocolUri, winrt::hstring const& targetApplicationPfn);

        winrt::Microsoft::Windows::AppNotifications::Builder::Button UseContextMenuPlacement();

        winrt::Microsoft::Windows::AppNotifications::Builder::Button SetButtonStyle(ButtonStyle const& buttonStyle);

        winrt::hstring GetXml();

    private:
        winrt::hstring m_content;
        winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> m_arguments { winrt::single_threaded_map<winrt::hstring, winrt::hstring>() };
        winrt::Windows::Foundation::Uri m_iconUri{ nullptr };
        winrt::Windows::Foundation::Uri m_protocolUri{ nullptr };
        winrt::hstring m_toolTip;
        winrt::hstring m_inputId;
        bool m_useContextMenuPlacement{};
        ButtonStyle m_buttonStyle { ButtonStyle::Default };
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct Button : ButtonT<Button, implementation::Button>
    {
    };
}
