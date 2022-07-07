#include "pch.h"
#include "AppNotificationContent.h"
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationContent.g.cpp"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    winrt::hstring GetWinSoundEventString(MSWinSoundEvent msWinSoundEvent)
    {
        return L"";
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::AddArgument(hstring const& key, hstring const& value)
    {
        m_arguments.Insert(key, value);
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::SetTimeStamp(winrt::Windows::Foundation::DateTime const& timeStamp)
    {
        m_timeStamp = timeStamp;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::SetScenario(Scenario const& scenario)
    {
        THROW_HR_IF(E_INVALIDARG, m_scenario != Scenario::Default);

        m_scenario = scenario;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::SetDuration(Duration const& duration)
    {
        THROW_HR_IF(E_INVALIDARG, m_duration != Duration::Default);

        m_duration = duration;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::AddText(hstring const& text)
    {
        THROW_HR_IF(E_INVALIDARG, m_textLines.size() == 4u);

        m_textLines.push_back(L"<text>" + text + L"</text>");

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::AddText(hstring const& text, TextProperties const& props)
    {
        THROW_HR_IF(E_INVALIDARG, m_textLines.size() == 4u);

        m_textLines.push_back(props.GetXml() + text + L"</text>");
        if (props.GetCallScenarioAlign())
        {
            m_scenario = Scenario::IncomingCall;
        }
        return *this;
    }    

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::SetAttributionText(hstring const& text)
    {
        THROW_HR_IF(E_INVALIDARG, !m_attributionText.empty());

        m_attributionText = L"<text placement=\"attribution\">" + text + L"</text>";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::SetAttributionText(hstring const& text, hstring const& language)
    {
        THROW_HR_IF(E_INVALIDARG, !m_attributionText.empty());

        m_attributionText = L"<text placement=\"attribution\" lang=\"" + language + L"\">" + text + L"</text>";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::SetInlineImage(winrt::Windows::Foundation::Uri const& uri)
    {
        THROW_HR_IF(E_INVALIDARG, !m_inlineImage.empty());

        m_inlineImage = L"<image src=\"" + uri.ToString() + L"\" />";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::SetInlineImage(winrt::Windows::Foundation::Uri const& uri, winrt::hstring const& alternateText)
    {
        THROW_HR_IF(E_INVALIDARG, !m_inlineImage.empty());

        m_inlineImage = L"<image src=\"" + uri.ToString() + L"\" alt=\"" + alternateText + L"\" />";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::SetInlineImageWithCircleCrop(winrt::Windows::Foundation::Uri const& uri)
    {
        THROW_HR_IF(E_INVALIDARG, !m_inlineImage.empty());

        m_inlineImage = L"<image src=\"" + uri.ToString() + L"\" hint-crop=\"circle\" />";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::SetInlineImageWithCircleCrop(winrt::Windows::Foundation::Uri const& uri, winrt::hstring const& alternateText)
    {
        THROW_HR_IF(E_INVALIDARG, !m_inlineImage.empty());

        m_inlineImage = L"<image src=\"" + uri.ToString() + L"\" alt=\"" + alternateText + L"\" hint-crop=\"circle\" />";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::SetAppLogoOverride(winrt::Windows::Foundation::Uri const& uri)
    {
        THROW_HR_IF(E_INVALIDARG, !m_appLogoOverride.empty());

        m_appLogoOverride = L"<image placement=\"appLogoOverride\" src=\"" + uri.ToString() + L"\" />";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::SetAppLogoOverride(winrt::Windows::Foundation::Uri const& uri, winrt::hstring const& alternateText)
    {
        THROW_HR_IF(E_INVALIDARG, !m_appLogoOverride.empty());

        m_appLogoOverride = L"<image placement=\"appLogoOverride\" src=\"" + uri.ToString() + L"\" alt=\"" + alternateText + L"\" />";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::SetAppLogoOverrideWithCircleCrop(winrt::Windows::Foundation::Uri const& uri)
    {
        THROW_HR_IF(E_INVALIDARG, !m_appLogoOverride.empty());

        m_appLogoOverride = L"<image placement=\"appLogoOverride\" src=\"" + uri.ToString() + L"\" hint-crop=\"circle\" />";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::SetAppLogoOverrideWithCircleCrop(winrt::Windows::Foundation::Uri const& uri, winrt::hstring const& alternateText)
    {
        THROW_HR_IF(E_INVALIDARG, !m_appLogoOverride.empty());

        m_appLogoOverride = L"<image placement=\"appLogoOverride\" src=\"" + uri.ToString() + L"\" alt=\"" + alternateText + L"\" hint-crop=\"circle\" />";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::SetHeroImage(winrt::Windows::Foundation::Uri const& uri)
    {
        THROW_HR_IF(E_INVALIDARG, !m_inlineImage.empty());

        m_inlineImage = L"<image placement=\"hero\" src=\"" + uri.ToString() + L"\" />";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::SetHeroImage(winrt::Windows::Foundation::Uri const& uri, winrt::hstring const& alternateText)
    {
        THROW_HR_IF(E_INVALIDARG, !m_inlineImage.empty());

        m_inlineImage = L"<image placement=\"hero\" src=\"" + uri.ToString() + L"\" alt=\"" + alternateText + L"\" />";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::AddButton(Button button)
    {
        THROW_HR_IF(E_INVALIDARG, m_inputList.size() == 5u);

        m_inputList.push_back(button.GetXml());
        m_useButtonStyle = button.GetButtonStyle() != ButtonStyle::Default;

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::SetAudio(winrt::Windows::Foundation::Uri const& uri)
    {
        THROW_HR_IF(E_INVALIDARG, !m_audio.empty());

        m_audio = L"<audio src=\"" + uri.ToString() + L"\" />";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::SetAudio(MSWinSoundEvent const& msWinSoundEvent)
    {
        THROW_HR_IF(E_INVALIDARG, !m_audio.empty());

        // Need to map enums to strings :)
        m_audio = L"<audio src=\"" + GetWinSoundEventString(msWinSoundEvent) + L"\" />";

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::SetAudioWithLoop(winrt::Windows::Foundation::Uri const& uri, Duration const& loopDuration)
    {
        THROW_HR_IF(E_INVALIDARG, !m_audio.empty());
        THROW_HR_IF(E_INVALIDARG, m_duration != Duration::Default);

        m_audio = L"<audio src=\"" + uri.ToString() + L"\" loop=\"true\" />";
        m_duration = loopDuration;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::SetAudioWithLoop(MSWinSoundEvent const& msWinSoundEvent, Duration const& loopDuration)
    {
        THROW_HR_IF(E_INVALIDARG, !m_audio.empty());
        THROW_HR_IF(E_INVALIDARG, m_duration != Duration::Default);

        // Need to map enums to strings :)
        m_audio = L"<audio src=\"" + GetWinSoundEventString(msWinSoundEvent) + L"\" loop=\"true\" />";
        m_duration = loopDuration;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::MuteAudio()
    {
        THROW_HR_IF(E_INVALIDARG, !m_audio.empty());

        m_audio = L"<audio silent=\"true\" />";

        return *this;
    }

    winrt::hstring AppNotificationContent::GetXml()
    {
        winrt::hstring xmlResult{ L"<toast" };

        // Add duration attribute if set
        if (m_duration != Duration::Default)
        {
            if (m_duration == Duration::Short)
            {
                xmlResult = xmlResult + L" duration=\"short\"";
            }
            else
            {
                xmlResult = xmlResult + L" duration=\"long\"";
            }
        }

        // Add scenario attribute if set
        if (m_scenario != Scenario::Default)
        {
            winrt::hstring scenario{};
            switch (m_scenario)
            {
            case Scenario::Alarm:
                scenario = L"\"alarm\"";
                break;
            case Scenario::Reminder:
                scenario = L"\"reminder\"";
                break;
            case Scenario::IncomingCall:
                scenario = L"\"incomingCall\"";
                break;
            case Scenario::Urgent:
                scenario = L"\"urgent\"";
                break;
            }

            xmlResult = xmlResult + L" scenario=" + scenario;
        }

        // Add launch arguments if given arguments
        if (m_arguments.Size())
        {
            xmlResult = xmlResult + L" launch=";

            winrt::hstring arguments{};
            for (auto pair : m_arguments)
            {
                arguments = arguments + pair.Key();
                if (!pair.Value().empty())
                {
                    arguments = arguments + L"&" + pair.Value();
                }
                arguments = arguments + L";";
            }
            xmlResult = xmlResult + arguments;
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
        return xmlResult + L"</toast>";
    }
}
