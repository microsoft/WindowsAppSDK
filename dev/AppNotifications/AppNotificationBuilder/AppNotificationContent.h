#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationContent.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct AppNotificationContent : AppNotificationContentT<AppNotificationContent>
    {
        AppNotificationContent();

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AddText(Text const& text);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AddButton(Button const& text);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AddImage(Image const& text);

        winrt::hstring GetXml();

    private:
        std::vector<Text> m_textList{};
        std::vector<Button> m_buttonList{};
        Image m_inlineImage{ nullptr };
        Image m_heroImage{ nullptr };
        Image m_appLogoOverrideImage{ nullptr };
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct AppNotificationContent : AppNotificationContentT<AppNotificationContent, implementation::AppNotificationContent>
    {
    };
}
