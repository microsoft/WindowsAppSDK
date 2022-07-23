#include "pch.h"
#include "AppNotificationBuilder.h"
#include "ITextProperties.h"
#include "IAppNotificationButton.h"
#include <winrt/Windows.Globalization.h>
#include <winrt/Windows.Globalization.DateTimeFormatting.h>
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilder.g.cpp"

using namespace winrt::Windows::Globalization;
using namespace winrt::Windows::Globalization::DateTimeFormatting;
namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    

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
        THROW_HR_IF(E_INVALIDARG, key.empty());

        m_arguments.Insert(key, value);
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetTimeStamp(winrt::Windows::Foundation::DateTime const& timeStamp)
    {
        //winrt::hstring currentLanguage { ApplicationLanguages::Languages().First().Current() };
        //// DateTimeFormatter dateTimeFormatter{ "longtime" };
        //winrt::Windows::Foundation::DateTime::
        //winrt::Windows::Foundation::DateTime { 2022, 1, 13, 16, 25, 30,  }
        //m_timeStamp = timeStamp;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetScenario(AppNotificationScenario const& scenario)
    {
        m_scenario = scenario;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetDuration(AppNotificationDuration const& duration)
    {
        m_duration = duration;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::AddText(hstring const& text)
    {
        THROW_HR_IF(E_INVALIDARG, m_textLines.size() == 3u);

        m_textLines.push_back(L"<text>" + text + L"</text>");

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::AddText(hstring const& text, AppNotificationTextProperties const& props)
    {
        THROW_HR_IF(E_INVALIDARG, m_textLines.size() == 3u);

        m_textLines.push_back(props.GetXml() + text + L"</text>");

        if (props.as<ITextProperties>()->GetCallScenarioAlign())
        {
            m_scenario = AppNotificationScenario::IncomingCall;
        }
        return *this;
    }    

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAttributionText(hstring const& text)
    {
        THROW_HR_IF(E_INVALIDARG, !m_attributionText.empty());

        m_attributionText = L"<text placement=\"attribution\">" + text + L"</text>";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAttributionText(hstring const& text, hstring const& language)
    {
        THROW_HR_IF(E_INVALIDARG, !m_attributionText.empty());
        THROW_HR_IF(E_INVALIDARG, language.empty());

        m_attributionText = L"<text placement=\"attribution\" lang=\"" + language + L"\">" + text + L"</text>";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetInlineImage(winrt::Windows::Foundation::Uri const& uri)
    {
        THROW_HR_IF(E_INVALIDARG, !m_inlineImage.empty());

        m_inlineImage = L"<image src=\"" + uri.ToString() + L"\"/>";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetInlineImage(winrt::Windows::Foundation::Uri const& uri, ImageCrop const& crop)
    {
        THROW_HR_IF(E_INVALIDARG, !m_inlineImage.empty());

        m_inlineImage = { L"<image src=\"" + uri.ToString() + L"\""};
        if (crop == ImageCrop::Circle)
        {
            m_inlineImage = m_inlineImage + L" hint-crop=\"circle\"";
        }
        m_inlineImage = m_inlineImage + L"/>";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetInlineImage(winrt::Windows::Foundation::Uri const& uri, ImageCrop const& crop, winrt::hstring const& alternateText)
    {
        THROW_HR_IF(E_INVALIDARG, !m_inlineImage.empty());

        m_inlineImage = L"<image src=\"" + uri.ToString() + L"\" alt=\"" + alternateText + L"\"";
        if (crop == ImageCrop::Circle)
        {
            m_inlineImage = m_inlineImage + L" hint-crop=\"circle\"";
        }
        m_inlineImage = m_inlineImage + L"/>";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAppLogoOverride(winrt::Windows::Foundation::Uri const& uri)
    {
        THROW_HR_IF(E_INVALIDARG, !m_appLogoOverride.empty());

        m_appLogoOverride = L"<image placement=\"appLogoOverride\" src=\"" + uri.ToString() + L"\"/>";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAppLogoOverride(winrt::Windows::Foundation::Uri const& uri, ImageCrop const& crop)
    {
        THROW_HR_IF(E_INVALIDARG, !m_appLogoOverride.empty());

        m_appLogoOverride = L"<image placement=\"appLogoOverride\" src=\"" + uri.ToString() + L"\"";
        if (crop == ImageCrop::Circle)
        {
            m_appLogoOverride = m_appLogoOverride + L" hint-crop=\"circle\"";
        }

        m_appLogoOverride = m_appLogoOverride + L"/>";
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAppLogoOverride(winrt::Windows::Foundation::Uri const& uri, ImageCrop const& crop, winrt::hstring const& alternateText)
    {
        THROW_HR_IF(E_INVALIDARG, !m_appLogoOverride.empty());

        m_appLogoOverride = L"<image placement=\"appLogoOverride\" src=\"" + uri.ToString() + L"\" alt=\"" + alternateText + L"\"";
        if (crop == ImageCrop::Circle)
        {
            m_appLogoOverride = m_appLogoOverride + L" hint-crop=\"circle\"";
        }

        m_appLogoOverride = m_appLogoOverride + L"/>";
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetHeroImage(winrt::Windows::Foundation::Uri const& uri)
    {
        THROW_HR_IF(E_INVALIDARG, !m_heroImage.empty());

        m_heroImage = L"<image placement=\"hero\" src=\"" + uri.ToString() + L"\"/>";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetHeroImage(winrt::Windows::Foundation::Uri const& uri, winrt::hstring const& alternateText)
    {
        THROW_HR_IF(E_INVALIDARG, !m_heroImage.empty());

        m_heroImage = L"<image placement=\"hero\" src=\"" + uri.ToString() + L"\" alt=\"" + alternateText + L"\"/>";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::AddButton(AppNotificationButton const& button)
    {
        THROW_HR_IF(E_INVALIDARG, m_inputList.size() == 5u);

        m_inputList.push_back(button.GetXml());
        m_useButtonStyle = button.as<IAppNotificationButton>()->GetButtonStyle() != AppNotificationButtonStyle::Default;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAudioUri(winrt::Windows::Foundation::Uri const& uri)
    {
        THROW_HR_IF(E_INVALIDARG, !m_audio.empty());

        m_audio = L"<audio src=\"" + uri.ToString() + L"\"/>";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAudioUri(winrt::Windows::Foundation::Uri const& uri, AppNotificationDuration const& duration)
    {
        THROW_HR_IF(E_INVALIDARG, !m_audio.empty());

        m_audio = L"<audio src=\"" + uri.ToString() + L"\" loop=\"true\"/>";
        m_duration = duration;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAudioEvent(AppNotificationSoundEvent const& soundEvent)
    {
        THROW_HR_IF(E_INVALIDARG, !m_audio.empty());

        // Need to map enums to strings :)
        m_audio = L"<audio src=\"" + GetWinSoundEventString(soundEvent) + L"\"/>";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::SetAudioEvent(AppNotificationSoundEvent const& soundEvent, AppNotificationDuration const& duration)
    {
        THROW_HR_IF(E_INVALIDARG, !m_audio.empty());

        // Need to map enums to strings :)
        m_audio = L"<audio src=\"" + GetWinSoundEventString(soundEvent) + L"\" loop=\"true\"/>";
        m_duration = duration;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder AppNotificationBuilder::MuteAudio()
    {
        THROW_HR_IF(E_INVALIDARG, !m_audio.empty());

        m_audio = L"<audio silent=\"true\"/>";

        return *this;
    }

    winrt::hstring AppNotificationBuilder::GetXml()
    {
        winrt::hstring xmlResult{ L"<toast" };

        // Add duration attribute if set
        if (m_duration != AppNotificationDuration::Default)
        {
            xmlResult = xmlResult + L" duration=\"long\"";
        }

        // Add scenario attribute if set
        if (m_scenario != AppNotificationScenario::Default)
        {
            winrt::hstring scenario{};
            switch (m_scenario)
            {
            case AppNotificationScenario::Alarm:
                scenario = L"\"alarm\"";
                break;
            case AppNotificationScenario::Reminder:
                scenario = L"\"reminder\"";
                break;
            case AppNotificationScenario::IncomingCall:
                scenario = L"\"incomingCall\"";
                break;
            case AppNotificationScenario::Urgent:
                scenario = L"\"urgent\"";
                break;
            }

            xmlResult = xmlResult + L" scenario=" + scenario;
        }

        // Add launch arguments if given arguments
        if (m_arguments.Size())
        {
            xmlResult = xmlResult + L" launch=\"";

            std::wstring arguments{};
            for (auto pair : m_arguments)
            {
                arguments = arguments + pair.Key();
                if (!pair.Value().empty())
                {
                    arguments = arguments + L"=" + pair.Value();
                }
                arguments = arguments + L";";
            }

            xmlResult = xmlResult + arguments.substr(0, arguments.size() - 1) + L"\"";
        }

        // Add button style attribute to <toast> element if any button uses a ButtonStyle
        if (m_useButtonStyle)
        {
            xmlResult = xmlResult + L" useButtonStyle=\"true\"";
        }

        // Add the binding/visual elements to put UI components
        xmlResult = xmlResult + L"><visual><binding template=\"ToastGeneric\">";

        // Insert all the <text> elements
        for (auto text : m_textLines)
        {
            xmlResult = xmlResult + text;
        }

        // Add the attribution text
        xmlResult = xmlResult + m_attributionText;

        // Adds all the image components
        xmlResult = xmlResult + m_inlineImage + m_heroImage + m_appLogoOverride;

        // Close the binding/visual tags
        xmlResult = xmlResult + L"</binding></visual>";

        // Set the audio
        xmlResult = xmlResult + m_audio;

        // Add the inputs
        if (m_inputList.size())
        {
            xmlResult = xmlResult + L"<actions>";
            for (auto input : m_inputList)
            {
                xmlResult = xmlResult + input;
            }
            xmlResult = xmlResult + L"</actions>";
        }
        
        return xmlResult + L"</toast>";
    }
}
