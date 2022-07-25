#include "pch.h"
#include "Image.h"
#include "Microsoft.Windows.AppNotifications.Builder.Image.g.cpp"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    Image::Image(winrt::Windows::Foundation::Uri const& imageUri) : m_imageUri(imageUri) { };

    winrt::Microsoft::Windows::AppNotifications::Builder::Image Image::SetAlternateText(winrt::hstring const& alternateText)
    {
        m_alternateText = alternateText;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::Image Image::UseCircleCrop()
    {
        m_useCircleCrop = true;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::Image Image::SetImagePlacement(ImagePlacement const& imagePlacement)
    {
        m_imagePlacement = imagePlacement;
        return *this;
    }

    winrt::hstring Image::GetXml()
    {
        winrt::hstring xml{ L"<image src=" + m_imageUri.ToString() };
        if (!m_alternateText.empty())
        {
            xml = xml + L" alt=" + m_alternateText;
        }

        if (m_useCircleCrop)
        {
            xml = xml + LR"( hint-crop="circle")";
        }

        if (m_imagePlacement == ImagePlacement::AppLogoOverride)
        {
            xml = xml + LR"( placement="appLogoOverride")";
        }
        else if (m_imagePlacement == ImagePlacement::Hero)
        {
            xml = xml + LR"( placement="hero")";
        }

        xml = xml + L" />";
        return xml;
    }
}
