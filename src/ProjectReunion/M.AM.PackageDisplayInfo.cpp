#include "pch.h"

#include "M.AM.PackageDisplayInfo.h"

#include <shlwapi.h>

#include <filesystem>

namespace winrt::Microsoft::ApplicationModel::implementation
{
    PackageDisplayInfo::PackageDisplayInfo(Microsoft::ApplicationModel::Package const& package) :
        m_package(package)
    {
    }
    hstring PackageDisplayInfo::DisplayName()
    {
        // W.AM.Package is functional for our needs as of 10.0.19041.0 aka 20H1 aka UniversalApiContract>=10
        auto contractName = winrt::to_hstring(L"Windows.Foundation.UniversalApiContract");
        if (Windows::Foundation::Metadata::ApiInformation::IsApiContractPresent(contractName, 10))
        {
            return m_package.W_AM_Package().DisplayName();
        }
        else
        {
            auto string = FindLoadAndParseValueFromAppxManifest(winrt::to_hstring("/Package/Properties/DisplayName"));
            return ToLocalizedString(string);
        }
    }
    hstring PackageDisplayInfo::PublisherDisplayName()
    {
        // W.AM.Package is functional for our needs as of 10.0.19041.0 aka 20H1 aka UniversalApiContract>=10
        auto contractName = winrt::to_hstring(L"Windows.Foundation.UniversalApiContract");
        if (Windows::Foundation::Metadata::ApiInformation::IsApiContractPresent(contractName, 10))
        {
            return m_package.W_AM_Package().PublisherDisplayName();
        }
        else
        {
            auto string = FindLoadAndParseValueFromAppxManifest(winrt::to_hstring("/Package/Properties/PublisherDisplayName"));
            return ToLocalizedString(string);
        }
    }
    hstring PackageDisplayInfo::Description()
    {
        // W.AM.Package is functional for our needs as of 10.0.19041.0 aka 20H1 aka UniversalApiContract>=10
        auto contractName = winrt::to_hstring(L"Windows.Foundation.UniversalApiContract");
        if (Windows::Foundation::Metadata::ApiInformation::IsApiContractPresent(contractName, 10))
        {
            return m_package.W_AM_Package().Description();
        }
        else
        {
            auto string = FindLoadAndParseValueFromAppxManifest(winrt::to_hstring("/Package/Properties/Description"));
            return ToLocalizedString(string);
        }
    }
    hstring PackageDisplayInfo::LogoFilename()
    {
        // W.AM.Package is functional for our needs as of 10.0.19041.0 aka 20H1 aka UniversalApiContract>=10
        auto contractName = winrt::to_hstring(L"Windows.Foundation.UniversalApiContract");
        if (Windows::Foundation::Metadata::ApiInformation::IsApiContractPresent(contractName, 10))
        {
            auto uri = m_package.W_AM_Package().Logo();
            if (uri)
            {
                if (CompareStringOrdinal(uri.SchemeName().c_str(), -1, L"file", -1, TRUE) == CSTR_EQUAL)
                {
                    auto filename = uri.Path();
                    return filename;
                }
            }
            return winrt::hstring();
        }
        else
        {
            auto string = FindLoadAndParseValueFromAppxManifest(winrt::to_hstring("/Package/Properties/Description"));
            return ToLocalizedPath(string);
        }
    }
    Windows::Foundation::Uri PackageDisplayInfo::LogoUri()
    {
        // W.AM.Package is functional for our needs as of 10.0.19041.0 aka 20H1 aka UniversalApiContract>=10
        auto contractName = winrt::to_hstring(L"Windows.Foundation.UniversalApiContract");
        if (Windows::Foundation::Metadata::ApiInformation::IsApiContractPresent(contractName, 10))
        {
            return m_package.W_AM_Package().Logo();
        }
        else
        {
            auto filename = LogoFilename();
            Windows::Foundation::Uri uri{ filename.c_str() };
            return uri;
        }
    }
    Windows::Storage::Streams::RandomAccessStreamReference PackageDisplayInfo::GetLogoStream(Windows::Foundation::Size const& size)
    {
        auto logo = LogoUri();
        return Windows::Storage::Streams::RandomAccessStreamReference::CreateFromUri(logo);
    }

    hstring PackageDisplayInfo::FindLoadAndParseValueFromAppxManifest(hstring xpath)
    {
        auto doc = FindLoadAndParseAppxManifest();
        auto node = doc.SelectSingleNode(xpath);
        if (node)
        {
            return node.InnerText();
        }
        return winrt::hstring();
    }

    Windows::Data::Xml::Dom::XmlDocument& PackageDisplayInfo::FindLoadAndParseAppxManifest()
    {
        if (!m_appxManifest)
        {
            auto location = m_package.Location();
            auto effectivePath = location.EffectivePath();
            auto path = std::filesystem::path(effectivePath.c_str());
            auto appxmanifest = path / L"appxmanifest.xml";
            auto appxmanifestFilename = appxmanifest.c_str();
            Windows::Foundation::Uri uri{ appxmanifestFilename };

            Windows::Data::Xml::Dom::XmlDocument doc;
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
        std::wstring prefix = L"ms-resource:";
        if (prefix.compare(0, prefix.length(), string.c_str()) != 0)
        {
            return string;
        }

        // SHLoadIndirectString() can resolve localized strings in appxmanifest.xml
        // if we convert the manifest string ms-resource:resource to @{PackageFullName?resource}
        // See https://docs.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-shloadindirectstring?redirectedfrom=MSDN

        // Given "ms-resource:resource" build the MRT fully-qualified reference @{pkgfullname?ms-resource://pkgname/resource}
        auto resource = string.c_str() + prefix.length();
        auto identity = m_package.Identity();
        std::wstring source = L"@{";
        source += identity.PackageFullName();
        source += L"?ms-resource://";
        source += identity.Name();
        source += L"/";
        const auto offsetToResource = source.length();
        source += resource;

        WCHAR localized[4096]{};
        UINT localizedSize = static_cast<UINT>(std::size(localized));
        const HRESULT hr = SHLoadIndirectString(source, localized, localizedSize, nullptr);
        if (FAILED(hr))
        {
            // Try the alternative syntax .../resources/... i.e. @{pkgfullname?ms-resource://pkgname/resources/key}
            source.insert(offsetToResource, L"resources/");
            const HRESULT hr = SHLoadIndirectString(source, localized, localizedSize, nullptr);
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
        auto resource = path.c_str();
        auto identity = m_package.Identity();
        std::wstring source = L"@{";
        source += identity.PackageFullName();
        source += L"?ms-resource://";
        source += identity.Name();
        source += L"/";
        const auto offsetToResource = source.length();
        source += resource;

        WCHAR localized[4096]{};
        UINT localizedSize = static_cast<UINT>(std::size(localized));
        const HRESULT hr = SHLoadIndirectString(source, localized, localizedSize, nullptr);
        if (FAILED(hr))
        {
            // Try the alternative syntax .../resources/... i.e. @{pkgfullname?ms-resource://pkgname/resources/key}
            source.insert(offsetToResource, L"resources/");
            const HRESULT hr = SHLoadIndirectString(source, localized, localizedSize, nullptr);
            if (FAILED(hr))
            {
                // No match so it's a literal value; no localization needed
                return path;
            }
        }
        return winrt::to_hstring(localized);
    }
}
