#pragma once
#include "Microsoft.ApplicationModel.PackageDisplayInfo.g.h"

namespace winrt::Microsoft::ApplicationModel::implementation
{
    struct PackageDisplayInfo : PackageDisplayInfoT<PackageDisplayInfo>
    {
        PackageDisplayInfo() = default;

        PackageDisplayInfo(Microsoft::ApplicationModel::Package const& package);
        hstring DisplayName();
        hstring PublisherDisplayName();
        hstring Description();
        hstring LogoFilename();
        Windows::Foundation::Uri LogoUri();
        Windows::Storage::Streams::RandomAccessStreamReference GetLogoStream(Windows::Foundation::Size const& size);

    private:
        hstring FindLoadAndParseValueFromAppxManifest(hstring xpath);
        Windows::Data::Xml::Dom::XmlDocument& FindLoadAndParseAppxManifest();
        hstring ToLocalizedString(const hstring& string);
        hstring ToLocalizedPath(const hstring& path);

    private:
        Microsoft::ApplicationModel::Package m_package;
        Windows::Data::Xml::Dom::XmlDocument m_appxManifest;
        hstring m_manifestedDisplayName;
        hstring m_localizedDisplayName;
        hstring m_manifestedPublisherDisplayName;
        hstring m_localizedPublisherDisplayName;
        bool m_descriptionIsParsedFromManifest = false; 
        hstring m_manifestedDescription;
        hstring m_localizedDescription;
        hstring m_manifestedLogo;
        hstring m_localizedLogo;
        Windows::Foundation::Uri m_localizedLogoUri = nullptr;
        bool m_isPackageFullyFunctionalForLocalization = false;
    };
}
namespace winrt::Microsoft::ApplicationModel::factory_implementation
{
    struct PackageDisplayInfo : PackageDisplayInfoT<PackageDisplayInfo, implementation::PackageDisplayInfo>
    {
    };
}
