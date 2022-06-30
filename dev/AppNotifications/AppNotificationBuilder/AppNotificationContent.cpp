#include "pch.h"
#include "AppNotificationContent.h"
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationContent.g.cpp"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    AppNotificationContent::AppNotificationContent()
    {
        m_textList = std::vector<Text>();
        m_textList.reserve(4);

        m_buttonList = std::vector<Button>();
        m_buttonList.reserve(5);
    }

    /// <exception cref="InvalidOperationException">Throws when attempting to add/reserve more than 4 lines on a single toast. </exception>
    /// <exception cref="ArgumentOutOfRangeException">Throws when <paramref name="hintMaxLines"/> value is larger than 2. </exception>
    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::AddText(Text const& text)
    {
        THROW_HR_IF(E_FAIL, m_textList.size() == 4u);
        m_textList.push_back(text);

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::AddImage(Image const& image)
    {
        switch (image.GetImagePlacement())
        {
        case ImagePlacement::Inline:
            m_inlineImage = image;
            break;
        case ImagePlacement::Hero:
            m_heroImage = image;
            break;
        case ImagePlacement::AppLogoOverride:
            m_appLogoOverrideImage = image;
            break;
        }

        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationContent AppNotificationContent::AddButton(Button const& button)
    {
        THROW_HR_IF(E_FAIL, m_textList.size() == 5u);
        m_buttonList.push_back(button);

        return *this;
    }

    winrt::hstring AppNotificationContent::GetXml()
    {
        winrt::hstring xml{ L"" };
        return xml;
    }
}
