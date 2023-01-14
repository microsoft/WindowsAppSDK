// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.PackageDisplayInfo.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    struct PackageDisplayInfo : PackageDisplayInfoT<PackageDisplayInfo>
    {
        PackageDisplayInfo() = default;

        PackageDisplayInfo(winrt::Microsoft::Windows::ApplicationModel::Package const& package);
        hstring DisplayName();
        hstring PublisherDisplayName();
        hstring Description();
        hstring LogoFilename();
        winrt::Windows::Foundation::Uri LogoUri();
        winrt::Windows::Storage::Streams::RandomAccessStreamReference GetLogoStream(winrt::Windows::Foundation::Size const& size);

    private:
        hstring FindLoadAndParseValueFromAppxManifest(hstring xpath);
        winrt::Windows::Data::Xml::Dom::XmlDocument& FindLoadAndParseAppxManifest();
        hstring ToLocalizedString(const hstring& string);
        hstring ToLocalizedPath(const hstring& path);

    private:
        winrt::Microsoft::Windows::ApplicationModel::Package m_package;
        winrt::Windows::Data::Xml::Dom::XmlDocument m_appxManifest;
        hstring m_manifestedDisplayName;
        hstring m_localizedDisplayName;
        hstring m_manifestedPublisherDisplayName;
        hstring m_localizedPublisherDisplayName;
        bool m_descriptionIsParsedFromManifest{};
        hstring m_manifestedDescription;
        hstring m_localizedDescription;
        hstring m_manifestedLogo;
        hstring m_localizedLogo;
        winrt::Windows::Foundation::Uri m_localizedLogoUri{ nullptr };bool m_isPackageFullyFunctionalForLocalization{};
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::factory_implementation
{
    struct PackageDisplayInfo : PackageDisplayInfoT<PackageDisplayInfo, implementation::PackageDisplayInfo>
    {
    };
}
