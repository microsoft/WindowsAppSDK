#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilder.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct AppNotificationBuilder : AppNotificationBuilderT<AppNotificationBuilder>
    {
        AppNotificationBuilder() = default;

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AddArgument(hstring const& key, hstring const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetTimeStamp(winrt::Windows::Foundation::DateTime const& timeStamp);
        
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetScenario(AppNotificationScenario const& scenario);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetDuration(AppNotificationDuration const& duration);
        // Text component APIs
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AddText(hstring const& text);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AddText(hstring const& text, AppNotificationTextProperties const& props);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetAttributionText(hstring const& text);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetAttributionText(hstring const& text, hstring const& language);

        // Inline image component APIs
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetInlineImage(winrt::Windows::Foundation::Uri const& uri);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetInlineImage(winrt::Windows::Foundation::Uri const& uri, ImageCrop const& crop);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetInlineImage(winrt::Windows::Foundation::Uri const& uri, winrt::hstring const& alternateText);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetInlineImage(winrt::Windows::Foundation::Uri const& uri, winrt::hstring const& alternateText, ImageCrop const& crop);

        // AppLogoOverride component APIs
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetAppLogoOverride(winrt::Windows::Foundation::Uri const& uri);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetAppLogoOverride(winrt::Windows::Foundation::Uri const& uri, ImageCrop const& crop);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetAppLogoOverride(winrt::Windows::Foundation::Uri const& uri, winrt::hstring const& alternateText);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetAppLogoOverride(winrt::Windows::Foundation::Uri const& uri, winrt::hstring const& alternateText, ImageCrop const& crop);

        // Hero image component APIs
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetHeroImage(winrt::Windows::Foundation::Uri const& uri);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetHeroImage(winrt::Windows::Foundation::Uri const& uri, winrt::hstring const& alternateText);

        // SetAudio
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetAudio(winrt::Windows::Foundation::Uri const& audioUri);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetAudio(AppNotificationSoundEvent const& soundEvent);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetAudio(winrt::Windows::Foundation::Uri const& audioUri, AppNotificationDuration const& loopDuration);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetAudio(AppNotificationSoundEvent const& soundEvent, AppNotificationDuration const& loopDuration);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder MuteAudio();

        // Adds a button to the AppNotificationBuilder
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AddButton(AppNotificationButton const& button);

        winrt::hstring GetXml();

    private:
        std::wstring GetWinSoundEventString(AppNotificationSoundEvent soundEvent);

        winrt::Windows::Foundation::DateTime m_timeStamp{};
        AppNotificationDuration m_duration{ AppNotificationDuration::Default };
        AppNotificationScenario m_scenario{ AppNotificationScenario::Default };
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
    struct AppNotificationBuilder : AppNotificationBuilderT<AppNotificationBuilder, implementation::AppNotificationBuilder>
    {
    };
}
