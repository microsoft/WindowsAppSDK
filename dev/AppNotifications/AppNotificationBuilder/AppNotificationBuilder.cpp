// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "AppNotificationBuilder.h"
#include <winrt/Windows.Globalization.h>
#include <winrt/Windows.Globalization.DateTimeFormatting.h>
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilder.g.cpp"

using namespace winrt::Windows::Globalization;
using namespace winrt::Windows::Globalization::DateTimeFormatting;

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    inline const size_t c_maxAppNotificationPayload{ 5120 };
    inline const uint8_t c_maxTextElements{ 3 };
    inline const uint8_t c_maxButtonElements{ 5 };

    std::wstring AppNotificationBuilder::GetWinSoundEventString(AppNotificationSoundEvent soundEvent)
    {
        static std::map<AppNotificationSoundEvent, std::wstring> c_soundEventMap
        {
            { AppNotificationSoundEvent::Default, L"ms-winsoundevent:Notification.Default"},
            { AppNotificationSoundEvent::IM, L"ms-winsoundevent:Notification.IM"},
            { AppNotificationSoundEvent::Mail, L"ms-winsoundevent:Notification.Mail"},
            { AppNotificationSoundEvent::Reminder, L"ms-winsoundevent:Notification.Reminder"},
            { AppNotificationSoundEvent::SMS, L"ms-winsoundevent:Notification.SMS"},
            { AppNotificationSoundEvent::Alarm, L"ms-winsoundevent:Notification.Looping.Alarm"},
            { AppNotificationSoundEvent::Alarm2, L"ms-winsoundevent:Notification.Looping.Alarm2"},
            { AppNotificationSoundEvent::Alarm3, L"ms-winsoundevent:Notification.Looping.Alarm3"},
            { AppNotificationSoundEvent::Alarm4, L"ms-winsoundevent:Notification.Looping.Alarm4"},
            { AppNotificationSoundEvent::Alarm5, L"ms-winsoundevent:Notification.Looping.Alarm5"},
            { AppNotificationSoundEvent::Alarm6, L"ms-winsoundevent:Notification.Looping.Alarm6"},
            { AppNotificationSoundEvent::Alarm7, L"ms-winsoundevent:Notification.Looping.Alarm7"},
            { AppNotificationSoundEvent::Alarm8, L"ms-winsoundevent:Notification.Looping.Alarm8"},
            { AppNotificationSoundEvent::Alarm9, L"ms-winsoundevent:Notification.Looping.Alarm9"},
            { AppNotificationSoundEvent::Alarm10, L"ms-winsoundevent:Notification.Looping.Alarm10"},
            { AppNotificationSoundEvent::Call, L"ms-winsoundevent:Notification.Looping.Call"},
            { AppNotificationSoundEvent::Call2, L"ms-winsoundevent:Notification.Looping.Call2"},
            { AppNotificationSoundEvent::Call3, L"ms-winsoundevent:Notification.Looping.Call3"},
            { AppNotificationSoundEvent::Call4, L"ms-winsoundevent:Notification.Looping.Call4"},
            { AppNotificationSoundEvent::Call5, L"ms-winsoundevent:Notification.Looping.Call5"},
            { AppNotificationSoundEvent::Call6, L"ms-winsoundevent:Notification.Looping.Call6"},
            { AppNotificationSoundEvent::Call7, L"ms-winsoundevent:Notification.Looping.Call7"},
            { AppNotificationSoundEvent::Call8, L"ms-winsoundevent:Notification.Looping.Call8"},
            { AppNotificationSoundEvent::Call9, L"ms-winsoundevent:Notification.Looping.Call9"},
            { AppNotificationSoundEvent::Call10, L"ms-winsoundevent:Notification.Looping.Call10"},
        };

        return c_soundEventMap[soundEvent];
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::AddArgument(hstring const& key, hstring const& value)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, key.empty(), "You must provide a key when adding an argument.");

        m_arguments.Insert(key, value);
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetTimeStamp(winrt::Windows::Foundation::DateTime const& value)
    {
        
        //winrt::std::wstring currentLanguage { ApplicationLanguages::Languages().First().Current() };
        //// DateTimeFormatter dateTimeFormatter{ "longtime" };
        //winrt::Windows::Foundation::DateTime::
        //winrt::Windows::Foundation::DateTime { 2022, 1, 13, 16, 25, 30,  }
        //m_timeStamp = timeStamp;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetScenario(AppNotificationScenario const& value)
    {
        m_scenario = value;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::AddText(hstring const& text)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, m_textLines.size() >= c_maxTextElements, "Maximum number of text elements added.");

        m_textLines.push_back(wil::str_printf<std::wstring>(L"<text>%ws</text>", text.c_str()).c_str());
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::AddText(hstring const& text, AppNotificationTextProperties const& properties)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, m_textLines.size() >= c_maxTextElements, "Maximum number of text elements added.");

        std::wstring props{ properties.as<winrt::Windows::Foundation::IStringable>().ToString() };
        m_textLines.push_back(wil::str_printf<std::wstring>(L"%ws%ws</text>", props.c_str(), text.c_str()).c_str());

        if (properties.IncomingCallAlignment())
        {
            m_scenario = AppNotificationScenario::IncomingCall;
        }
        return *this;
    }    

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAttributionText(hstring const& text)
    {
        m_attributionText = wil::str_printf<std::wstring>(L"<text placement='attribution'>%ws</text>", text.c_str());
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAttributionText(hstring const& text, hstring const& language)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, language.empty(), "You must provide a language calling SetAttributionText.");

        m_attributionText = wil::str_printf<std::wstring>(L"<text placement='attribution' lang='%ws'>%ws</text>", language.c_str(), text.c_str());
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetInlineImage(winrt::Windows::Foundation::Uri const& imageUri)
    {
        m_inlineImage = wil::str_printf<std::wstring>(L"<image src='%ws'/>", imageUri.ToString().c_str());
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetInlineImage(winrt::Windows::Foundation::Uri const& imageUri, AppNotificationImageCrop const& imageCrop)
    {
        if (imageCrop == AppNotificationImageCrop::Circle)
        {
            m_inlineImage = wil::str_printf<std::wstring>(L"<image src='%ws' hint-crop='circle'/>", imageUri.ToString().c_str());
        }
        else
        {
            SetInlineImage(imageUri);
        }

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetInlineImage(winrt::Windows::Foundation::Uri const& imageUri, AppNotificationImageCrop const& imageCrop, hstring const& alternateText)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, alternateText.empty(), "You must provide an alternate text string calling SetInlineImage.");

        std::wstring hintCrop { imageCrop == AppNotificationImageCrop::Circle ? L" hint-crop='circle'" : L"" };
        m_inlineImage = wil::str_printf<std::wstring>(L"<image src='%ws' alt='%ws'%ws/>", imageUri.ToString().c_str(), alternateText.c_str(), hintCrop.c_str());

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAppLogoOverride(winrt::Windows::Foundation::Uri const& imageUri)
    {
        m_appLogoOverride = wil::str_printf<std::wstring>(L"<image placement='appLogoOverride' src='%ws'/>", imageUri.ToString().c_str());
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAppLogoOverride(winrt::Windows::Foundation::Uri const& imageUri, AppNotificationImageCrop const& imageCrop)
    {
        if (imageCrop == AppNotificationImageCrop::Circle)
        {
            m_appLogoOverride = wil::str_printf<std::wstring>(L"<image placement='appLogoOverride' src='%ws' hint-crop='circle'/>", imageUri.ToString().c_str());
        }
        else
        {
            SetAppLogoOverride(imageUri);
        }

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAppLogoOverride(winrt::Windows::Foundation::Uri const& imageUri, AppNotificationImageCrop const& imageCrop, hstring const& alternateText)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, alternateText.empty(), "You must provide an alternate text string calling SetAppLogoOverride.");

        std::wstring hintCrop{ imageCrop == AppNotificationImageCrop::Circle ? L" hint-crop='circle'" : L"" };
        m_appLogoOverride = wil::str_printf<std::wstring>(L"<image placement='appLogoOverride' src='%ws' alt='%ws'%ws/>", imageUri.ToString().c_str(), alternateText.c_str(), hintCrop.c_str());

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetHeroImage(winrt::Windows::Foundation::Uri const& imageUri)
    {
        m_heroImage = wil::str_printf<std::wstring>(L"<image placement='hero' src='%ws'/>", imageUri.ToString().c_str());
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetHeroImage(winrt::Windows::Foundation::Uri const& imageUri, hstring const& alternateText)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, alternateText.empty(), "You must provide an alternate text string calling SetHeroImage.");

        m_heroImage = wil::str_printf<std::wstring>(L"<image placement='hero' src='%ws' alt='%ws'/>", imageUri.ToString().c_str(), alternateText.c_str());
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAudioUri(winrt::Windows::Foundation::Uri const& audioUri)
    {
        m_audio = wil::str_printf<std::wstring>(L"<audio src='%ws'/>", audioUri.ToString().c_str());
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAudioUri(winrt::Windows::Foundation::Uri const& audioUri, AppNotificationDuration const& duration)
    {
        m_audio = wil::str_printf<std::wstring>(L"<audio src='%ws' loop='true'/>", audioUri.ToString().c_str());
        m_duration = duration;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAudioEvent(AppNotificationSoundEvent const& soundEvent)
    {
        m_audio = wil::str_printf<std::wstring>(L"<audio src='%ws'/>", GetWinSoundEventString(soundEvent).c_str());
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAudioEvent(AppNotificationSoundEvent const& soundEvent, AppNotificationDuration const& duration)
    {
        m_audio = wil::str_printf<std::wstring>(L"<audio src='%ws' loop='true'/>", GetWinSoundEventString(soundEvent).c_str());
        m_duration = duration;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::MuteAudio()
    {
        m_audio = L"<audio silent='true'/>";
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::AddButton(AppNotificationButton const& value)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, m_buttonList.size() >= c_maxButtonElements, "Maximum number of buttons added.");

        m_buttonList.push_back(value);
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetTag(hstring const& value)
    {
        m_tag = value;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetGroup(hstring const& value)
    {
        m_group = value;
        return *this;
    }

    std::wstring AppNotificationBuilder::GetDuration()
    {
        return m_duration == AppNotificationDuration::Default ? L"" : L" duration='long'";
    }

    std::wstring AppNotificationBuilder::GetScenario()
    {
        // Add scenario attribute if set
        switch (m_scenario)
        {
        case AppNotificationScenario::Alarm:
            return L" scenario='alarm'";
        case AppNotificationScenario::Reminder:
            return L" scenario='reminder'";
        case AppNotificationScenario::IncomingCall:
            return L" scenario='incomingCall'";
        case AppNotificationScenario::Urgent:
            return L" scenario='urgent'";
        default:
            return {};
        }
    }

    std::wstring AppNotificationBuilder::GetArguments()
    {
        // Add launch arguments if given arguments
        if (m_arguments.Size())
        {
            std::wstring arguments{ };
            for (auto pair : m_arguments)
            {
                if (!pair.Value().empty())
                {
                    arguments.append(wil::str_printf<std::wstring>(L"%ws=%ws;", pair.Key().c_str(), pair.Value().c_str()));
                }
                else
                {
                    arguments.append(wil::str_printf<std::wstring>(L"%ws;", pair.Key().c_str()));
                }
            }
            arguments.pop_back();

            return wil::str_printf<std::wstring>(L" launch='%ws'", arguments.c_str());
        }
        else
        {
            return {};
        }
    }

    std::wstring AppNotificationBuilder::GetText()
    {
        std::wstring result{};
        for (auto text : m_textLines)
        {
            result.append(text);
        }

        return result;
    }

    std::wstring AppNotificationBuilder::GetImages()
    {
        return wil::str_printf<std::wstring>(L"%ws%ws%ws", m_inlineImage.c_str(), m_heroImage.c_str(), m_appLogoOverride.c_str());
    }

    std::wstring AppNotificationBuilder::GetButtons()
    {
        if (m_buttonList.size())
        {
            std::wstring result{};
            for (auto input : m_buttonList)
            {
                if (input.ButtonStyle() != AppNotificationButtonStyle::Default)
                {
                    m_useButtonStyle = true;
                }

                result.append(input.as<winrt::Windows::Foundation::IStringable>().ToString().c_str());
            }

            return wil::str_printf<std::wstring>(L"<actions>%ws</actions>", result.c_str());
        }
        else
        {
            return {};
        }
    }

    // You must call GetButtons first to retrieve this value.
    std::wstring AppNotificationBuilder::GetButtonStyle()
    {
        return m_useButtonStyle ? L" useButtonStyle='true'" : L"";
    }

    winrt::Microsoft::Windows::AppNotifications::AppNotification AppNotificationBuilder::BuildNotification()
    {
        std::wstring xmlResult{};
        xmlResult.reserve(c_maxAppNotificationPayload);

        // Build the button string and fill m_useButtonStyle
        std::wstring buttons{ GetButtons() };

        xmlResult.append(L"<toast");
        xmlResult.append(GetDuration());
        xmlResult.append(GetScenario());
        xmlResult.append(GetArguments());
        xmlResult.append(GetButtonStyle());
        xmlResult.append(L"><visual><binding template='ToastGeneric'>");
        xmlResult.append(GetText());
        xmlResult.append(m_attributionText);
        xmlResult.append(GetImages());
        xmlResult.append(L"</binding></visual>");
        xmlResult.append(m_audio.c_str());
        xmlResult.append(buttons);
        xmlResult.append(L"</toast>");

        winrt::Microsoft::Windows::AppNotifications::AppNotification appNotification{ xmlResult };
        appNotification.Tag(m_tag);
        appNotification.Group(m_group);
        
        return appNotification;
    }
}
