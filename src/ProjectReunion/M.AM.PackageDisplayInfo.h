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
    };
}
namespace winrt::Microsoft::ApplicationModel::factory_implementation
{
    struct PackageDisplayInfo : PackageDisplayInfoT<PackageDisplayInfo, implementation::PackageDisplayInfo>
    {
    };
}
