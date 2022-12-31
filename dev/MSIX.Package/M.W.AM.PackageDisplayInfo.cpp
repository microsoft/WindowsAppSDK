// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>

#include "M.W.AM.PackageDisplayInfo.h"

#include "Microsoft.Windows.ApplicationModel.PackageDisplayInfo.g.cpp"

#include <shlwapi.h>

#include <filesystem>

// W.AM.Package localizable properties are fully functional only recently
// (as of 10.0.19041.0 aka 20H1 aka UniversalApiContract>=10). On older
// releases they're only functional when created via Package.Current.
// Instances created via Windows.Management.Deployment.PackageManager.FindPackage*()
// are non-functional e.g. package.DisplayName returns "". We can
// determine the same net result by loading the raw values out of
// AppxManifest.xml and calling SHLoadIndirectString(), albeit in
// obscure ways. There's a perf cost to find/load/parse appxmanifest.xml
// so we really only want to do the latter when necessary.

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    PackageDisplayInfo::PackageDisplayInfo(winrt::Microsoft::Windows::ApplicationModel::Package const& package) :
        m_package(package)
    {
        // W.AM.Package is functional for our needs as of 10.0.19041.0 aka 20H1 aka UniversalApiContract>=10
        auto contractName{ winrt::to_hstring(L"Windows.Foundation.UniversalApiContract") };
        m_isPackageFullyFunctionalForLocalization = winrt::Windows::Foundation::Metadata::ApiInformation::IsApiContractPresent(contractName, 10);
    }
    hstring PackageDisplayInfo::DisplayName()
    {
        if (m_localizedDisplayName.size() == 0)
        {
            if (!m_isPackageFullyFunctionalForLocalization)
            {
                if (m_manifestedDisplayName.size() == 0)
                {
                    m_manifestedDisplayName = FindLoadAndParseValueFromAppxManifest(winrt::to_hstring(L"/Package/Properties/DisplayName"));
                    m_localizedDisplayName = ToLocalizedString(m_manifestedDisplayName);
                }
            }
        }
        return m_localizedDisplayName;
    }
    hstring PackageDisplayInfo::PublisherDisplayName()
    {
        if (m_localizedPublisherDisplayName.size() == 0)
        {
            if (!m_isPackageFullyFunctionalForLocalization)
            {
                if (m_manifestedPublisherDisplayName.size() == 0)
                {
                    m_manifestedPublisherDisplayName = FindLoadAndParseValueFromAppxManifest(winrt::to_hstring(L"/Package/Properties/PublisherDisplayName"));
                    m_localizedPublisherDisplayName = ToLocalizedString(m_manifestedPublisherDisplayName);
                }
            }
        }
        return m_localizedPublisherDisplayName;
    }
    hstring PackageDisplayInfo::Description()
    {
        if (m_localizedDescription.size() == 0)
        {
            if (!m_isPackageFullyFunctionalForLocalization)
            {
                // Description is optional in appxmanifest.xml. We can't rely on
                // a string from the manifest indicating we've parsed the manifest
                if (m_descriptionIsParsedFromManifest && m_manifestedDescription.size() == 0)
                {
                    m_manifestedDescription = FindLoadAndParseValueFromAppxManifest(winrt::to_hstring(L"/Package/Properties/Description"));
                    m_localizedDescription = ToLocalizedString(m_manifestedDescription);
                }
            }
        }
        return m_localizedDescription;
    }
    hstring PackageDisplayInfo::LogoFilename()
    {
        if (m_localizedLogo.size() == 0)
        {
            if (!m_isPackageFullyFunctionalForLocalization)
            {
                if (m_manifestedLogo.size() == 0)
                {
                    auto string{ FindLoadAndParseValueFromAppxManifest(winrt::to_hstring("/Package/Properties/Description")) };
                    m_localizedLogo = ToLocalizedPath(string);
                }
            }
        }
        return m_localizedLogo;
    }
    winrt::Windows::Foundation::Uri PackageDisplayInfo::LogoUri()
    {
        if (!m_localizedLogoUri)
        {
            auto logoFilename{ LogoFilename() };
            winrt::Windows::Foundation::Uri uri{ logoFilename.c_str() };
            m_localizedLogoUri = uri;
        }
        return m_localizedLogoUri;
    }
    winrt::Windows::Storage::Streams::RandomAccessStreamReference PackageDisplayInfo::GetLogoStream(winrt::Windows::Foundation::Size const& /*size*/)
    {
        //TODO Use Mrm APIs to get the logo in the desired TargetSize=size per https://github.com/microsoft/ProjectReunion/issues/11
        auto logo{ LogoUri() };
        return winrt::Windows::Storage::Streams::RandomAccessStreamReference::CreateFromUri(logo);
    }

    hstring PackageDisplayInfo::FindLoadAndParseValueFromAppxManifest(hstring xpath)
    {
        auto doc{ FindLoadAndParseAppxManifest() };
        auto node{ doc.SelectSingleNode(xpath) };
        if (node)
        {
            return node.InnerText();
        }
        return winrt::hstring();
    }

    winrt::Windows::Data::Xml::Dom::XmlDocument& PackageDisplayInfo::FindLoadAndParseAppxManifest()
    {
        if (!m_appxManifest)
        {
            auto location{ m_package.Location() };
            auto effectivePath{ location.EffectivePath() };
            auto path{ std::filesystem::path(effectivePath.c_str()) };
            auto appxmanifest{ path / L"appxmanifest.xml" };
            auto appxmanifestFilename{ appxmanifest.c_str() };
            winrt::Windows::Foundation::Uri uri{ appxmanifestFilename };

            winrt::Windows::Data::Xml::Dom::XmlDocument doc;
            m_appxManifest = doc.LoadFromUriAsync(uri).get();
        }
        return m_appxManifest;
    }

    hstring PackageDisplayInfo::ToLocalizedString(const hstring& string)
    {
        // Per https://stackoverflow.com/questions/18219915/get-localized-friendly-names-for-all-winrt-metro-apps-installed-from-wpf-applica
        //
        // You'll have to transform the manifest string into the proper form, though.
        // It should be: ms-resource://PackageName/Resources/Id
        //
        // PackageName is the name rather than the full name. Resources isn't strictly
        // required but it's the default and it's usually there. I'd try to look up the
        // resource without inserting resources and then try again if that fails.
        //
        // For example, the camera app has "ms-resource:manifestDisplayName" in the manifest,
        // so first you should try(*): @{Microsoft.Camera_6.2.8376.0_x64__8wekyb3d8bbwe? ms-resource://Microsoft.Camera/manifestAppDescription}
        //
        // When that fails, insert "resources" and try: @{Microsoft.Camera_6.2.8376.0_x64__8wekyb3d8bbwe? ms-resource://Microsoft.Camera/resources/manifestAppDescription}
        //
        // That should work. You'll want to try both forms because blindly inserting
        // "resources" will break apps like skydrive, communications and photos which
        // insert the first part of the path directly.
        //
        // Still a bit of a pain, but better than dumping and parsing gigantic XML files.
        //
        // (*) "Microsoft.Camera_6.2.8376.0_x64__8wekyb3d8bbwe" is taken from an example.
        // You'll obviously want the FullName of the one that's actually present on your system.

        // Localized strings start with "ms-resource:"
        std::wstring prefix{ L"ms-resource:" };
        if (prefix.compare(0, prefix.length(), string.c_str()) != 0)
        {
            return string;
        }

        // SHLoadIndirectString() can resolve localized strings in appxmanifest.xml
        // if we convert the manifest string ms-resource:resource to @{PackageFullName?resource}
        // See https://docs.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-shloadindirectstring?redirectedfrom=MSDN

        // Given "ms-resource:resource" build the MRT fully-qualified reference @{pkgfullname?ms-resource://pkgname/resource}
        auto resource{ string.c_str() + prefix.length() };
        auto identity{ m_package.Identity() };
        std::wstring source{ L"@{" };
        source += identity.PackageFullName();
        source += L"?ms-resource://";
        source += identity.Name();
        source += L"/";
        const auto offsetToResource{ source.length() };
        source += resource;

        WCHAR localized[4096]{};
        UINT localizedSize{ static_cast<UINT>(std::size(localized)) };
        HRESULT hr{ SHLoadIndirectString(source.c_str(), localized, localizedSize, nullptr) };
        if (FAILED(hr))
        {
            // Try the alternative syntax .../resources/... i.e. @{pkgfullname?ms-resource://pkgname/resources/key}
            source.insert(offsetToResource, L"resources/");
            hr = SHLoadIndirectString(source.c_str(), localized, localizedSize, nullptr);
            if (FAILED(hr))
            {
                // Failure to match yields the MRT fully-qualified reference
                // (less likely to be confusd with a real answer as 'key' would be)
                // TODO: Should we return the original manifest'd value on failure? Raise an exception?
                return winrt::to_hstring(source.c_str());
            }
        }
        return winrt::to_hstring(localized);
    }

    hstring PackageDisplayInfo::ToLocalizedPath(const hstring& path)
    {
        // Unlike localizable strings in appxmanifest.xml, localizable paths have no ms-resource: prefix.
        // Localizable paths are always potentially localizable. The only way to know for sure is to try
        // (and compare if before vs after differs, if you care to know).

        // See ToLocalizedString() for more details.

        // Build the MRT fully-qualified reference @{pkgfullname?ms-resource://pkgname/resource}
        auto resource{ path.c_str() };
        auto identity{ m_package.Identity() };
        std::wstring source{ L"@{" };
        source += identity.PackageFullName();
        source += L"?ms-resource://";
        source += identity.Name();
        source += L"/";
        const auto offsetToResource{ source.length() };
        source += resource;

        WCHAR localized[4096]{};
        UINT localizedSize{ static_cast<UINT>(std::size(localized)) };
        HRESULT hr{ SHLoadIndirectString(source.c_str(), localized, localizedSize, nullptr) };
        if (FAILED(hr))
        {
            // Try the alternative syntax .../resources/... i.e. @{pkgfullname?ms-resource://pkgname/resources/key}
            source.insert(offsetToResource, L"resources/");
            hr = SHLoadIndirectString(source.c_str(), localized, localizedSize, nullptr);
            if (FAILED(hr))
            {
                // No match so it's a literal value; no localization needed
                return path;
            }
        }
        return winrt::to_hstring(localized);
    }
}
