// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "AppNotificationBuilder.h"
#include <winrt/Windows.Globalization.h>
#include <winrt/Windows.Globalization.DateTimeFormatting.h>
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilder.g.cpp"
#include "AppNotificationBuilderUtility.h"
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace winrt::Windows::Globalization;
using namespace winrt::Windows::Globalization::DateTimeFormatting;

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    bool AppNotificationBuilder::IsUrgentScenarioSupported()
    {
        return GetBuildNumber() >= 19041;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::AddArgument(hstring const& key, hstring const& value)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, key.empty(), "You must provide a key when adding an argument.");

        m_arguments.Insert(key, value);
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetTimeStamp(winrt::Windows::Foundation::DateTime const& value)
    {
        auto seconds{ winrt::clock::to_time_t(value) };
        struct tm buf;
        gmtime_s(&buf, &seconds);

        std::wstringstream buffer;
        buffer << std::put_time(&buf, L"%FT%T");

        m_timeStamp = wil::str_printf<std::wstring>(L" displayTimestamp='%wsZ'", buffer.str().c_str());
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetScenario(AppNotificationScenario const& value)
    {
        m_scenario = value;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetDuration(AppNotificationDuration const& value)
    {
        m_duration = value;
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

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAudioUri(winrt::Windows::Foundation::Uri const& audioUri, AppNotificationAudioLooping const& loop)
    {
        m_audio = wil::str_printf<std::wstring>(L"<audio src='%ws' loop='%ws'/>", audioUri.ToString().c_str(), loop == AppNotificationAudioLooping::Loop ? L"true" : L"false");
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAudioEvent(AppNotificationSoundEvent const& soundEvent)
    {
        m_audio = wil::str_printf<std::wstring>(L"<audio src='%ws'/>", GetWinSoundEventString(soundEvent).c_str());
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAudioEvent(AppNotificationSoundEvent const& soundEvent, AppNotificationAudioLooping const& loop)
    {
        m_audio = wil::str_printf<std::wstring>(L"<audio src='%ws' loop='%ws'/>", GetWinSoundEventString(soundEvent).c_str(), loop == AppNotificationAudioLooping::Loop ? L"true" : L"false");
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::MuteAudio()
    {
        m_audio = L"<audio silent='true'/>";
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::AddProgressBar(AppNotificationProgressBar const& value)
    {
        m_progressBar = value;

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
        xmlResult.append(m_timeStamp);
        xmlResult.append(GetDuration());
        xmlResult.append(GetScenario());
        xmlResult.append(GetArguments());
        xmlResult.append(GetButtonStyle());
        xmlResult.append(L"><visual><binding template='ToastGeneric'>");
        xmlResult.append(GetText());
        xmlResult.append(m_attributionText);
        xmlResult.append(GetImages());
        xmlResult.append(m_progressBar.as<winrt::Windows::Foundation::IStringable>().ToString());
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
