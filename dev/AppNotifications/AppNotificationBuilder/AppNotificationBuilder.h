// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilder.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct AppNotificationBuilder : AppNotificationBuilderT<AppNotificationBuilder>
    {
        AppNotificationBuilder() = default;

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AddArgument(hstring const& key, hstring const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetTimeStamp(winrt::Windows::Foundation::DateTime const& value);
        
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetScenario(AppNotificationScenario const& value);

        // Text component APIs
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AddText(hstring const& text);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AddText(hstring const& text, AppNotificationTextProperties const& properties);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetAttributionText(hstring const& text);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetAttributionText(hstring const& text, hstring const& language);

        // Inline image component APIs
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetInlineImage(winrt::Windows::Foundation::Uri const& imageUri);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetInlineImage(winrt::Windows::Foundation::Uri const& imageUri, AppNotificationImageCrop const& imageCrop);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetInlineImage(winrt::Windows::Foundation::Uri const& imageUri, AppNotificationImageCrop const& imageCrop, winrt::hstring const& alternateText);

        // AppLogoOverride component APIs
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetAppLogoOverride(winrt::Windows::Foundation::Uri const& imageUri);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetAppLogoOverride(winrt::Windows::Foundation::Uri const& imageUri, AppNotificationImageCrop const& imageCrop);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetAppLogoOverride(winrt::Windows::Foundation::Uri const& imageUri, AppNotificationImageCrop const& imageCrop, winrt::hstring const& alternateText);

        // Hero image component APIs
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetHeroImage(winrt::Windows::Foundation::Uri const& imageUri);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetHeroImage(winrt::Windows::Foundation::Uri const& imageUri, winrt::hstring const& alternateText);

        // SetAudio
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetAudioUri(winrt::Windows::Foundation::Uri const& audioUri);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetAudioUri(winrt::Windows::Foundation::Uri const& audioUri, AppNotificationDuration const& duration);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetAudioEvent(AppNotificationSoundEvent const& soundEvent);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetAudioEvent(AppNotificationSoundEvent const& soundEvent, AppNotificationDuration const& duration);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder MuteAudio();

        // Adds a button to the AppNotificationBuilder
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AddButton(AppNotificationButton const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetTag(winrt::hstring const& value);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder SetGroup(winrt::hstring const& value);

        winrt::Microsoft::Windows::AppNotifications::AppNotification BuildNotification();

    private:
        std::wstring GetWinSoundEventString(AppNotificationSoundEvent soundEvent);
        std::wstring GetDuration();
        std::wstring GetScenario();
        std::wstring GetArguments();
        std::wstring GetButtonStyle();
        std::wstring GetText();
        std::wstring GetImages();
        std::wstring GetInput();


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
        winrt::hstring m_tag{};
        winrt::hstring m_group{};
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct AppNotificationBuilder : AppNotificationBuilderT<AppNotificationBuilder, implementation::AppNotificationBuilder>
    {
    };
}
