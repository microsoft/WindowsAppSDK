#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.Image.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct Image : ImageT<Image>
    {
        Image(winrt::Windows::Foundation::Uri const& imageUri);

        winrt::Microsoft::Windows::AppNotifications::Builder::Image SetAlternateText(winrt::hstring const& alternateText);

        winrt::Microsoft::Windows::AppNotifications::Builder::Image UseCircleCrop();

        winrt::Microsoft::Windows::AppNotifications::Builder::Image SetImagePlacement(ImagePlacement const& imagePlacement);

        ImagePlacement GetImagePlacement() { return m_imagePlacement;  };

        winrt::hstring GetXml();

    private:
        winrt::Windows::Foundation::Uri m_imageUri;
        winrt::hstring m_alternateText;
        bool m_useCircleCrop{};
        ImagePlacement m_imagePlacement{ ImagePlacement::Inline };
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct Image : ImageT<Image, implementation::Image>
    {
    };
}
