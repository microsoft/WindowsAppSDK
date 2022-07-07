#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationContent.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct AppNotificationContent : AppNotificationContentT<AppNotificationContent>
    {
        AppNotificationContent() = default;

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AddArgument(hstring const& key, hstring const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent SetTimeStamp(winrt::Windows::Foundation::DateTime const& timeStamp);
        
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent SetScenario(Scenario const& scenario);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent SetDuration(Duration const& duration);
        // Text component APIs
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AddText(hstring const& text);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AddText(hstring const& text, TextProperties const& props);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent SetAttributionText(hstring const& text);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent SetAttributionText(hstring const& text, hstring const& language);

        // Inline image component APIs
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent SetInlineImage(winrt::Windows::Foundation::Uri const& uri);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent SetInlineImage(winrt::Windows::Foundation::Uri const& uri, winrt::hstring const& alternateText);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent SetInlineImageWithCircleCrop(winrt::Windows::Foundation::Uri const& uri);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent SetInlineImageWithCircleCrop(winrt::Windows::Foundation::Uri const& uri, winrt::hstring const& alternateText);

        // AppLogoOverride component APIs
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent SetAppLogoOverride(winrt::Windows::Foundation::Uri const& uri);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent SetAppLogoOverride(winrt::Windows::Foundation::Uri const& uri, winrt::hstring const& alternateText);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent SetAppLogoOverrideWithCircleCrop(winrt::Windows::Foundation::Uri const& uri);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent SetAppLogoOverrideWithCircleCrop(winrt::Windows::Foundation::Uri const& uri, winrt::hstring const& alternateText);

        // Hero image component APIs
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent SetHeroImage(winrt::Windows::Foundation::Uri const& uri);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent SetHeroImage(winrt::Windows::Foundation::Uri const& uri, winrt::hstring const& alternateText);

        // SetAudio
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent SetAudio(winrt::Windows::Foundation::Uri const& audioUri);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent SetAudio(MSWinSoundEvent const& msWinSoundEvent);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent SetAudioWithLoop(winrt::Windows::Foundation::Uri const& audioUri, Duration const& loopDuration);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent SetAudioWithLoop(MSWinSoundEvent const& msWinSoundEvent, Duration const& loopDuration);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent MuteAudio();

        // Adds a button to the AppNotificationContent
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AddButton(Button button);

        winrt::hstring GetXml();

    private:
        winrt::Windows::Foundation::DateTime m_timeStamp{};
        Duration m_duration{ Duration::Default };
        Scenario m_scenario{ Scenario::Default };
        bool m_useButtonStyle{};
        std::vector<winrt::hstring> m_textLines{};
        winrt::hstring m_attributionText{};
        winrt::hstring m_inlineImage{};
        winrt::hstring m_appLogoOverride{};
        winrt::hstring m_heroImage{};
        winrt::hstring m_audio{};
        winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> m_arguments{ winrt::single_threaded_map<winrt::hstring, winrt::hstring>() };
        std::vector<winrt::hstring> m_inputList{};
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct AppNotificationContent : AppNotificationContentT<AppNotificationContent, implementation::AppNotificationContent>
    {
    };
}
