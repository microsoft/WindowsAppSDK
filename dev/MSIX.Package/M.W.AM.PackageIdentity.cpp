// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>

#include "M.W.AM.PackageIdentity.h"

#include "Microsoft.Windows.ApplicationModel.PackageIdentity.g.cpp"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    PackageIdentity::PackageIdentity(winrt::Microsoft::Windows::ApplicationModel::Package const& package) :
        m_package(package)
    {
    }
    hstring PackageIdentity::FormatPackageFullName(hstring const& packagename, winrt::Windows::ApplicationModel::PackageVersion const& version, winrt::Windows::System::ProcessorArchitecture const& architecture, hstring const& resourceId, hstring const& publisher)
    {
        throw hresult_not_implemented();
    }
    hstring PackageIdentity::FormatPackageFullNameGivenPublisherId(hstring const& packagename, winrt::Windows::ApplicationModel::PackageVersion const& version, winrt::Windows::System::ProcessorArchitecture const& architecture, hstring const& resourceId, hstring const& publisherId)
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::ApplicationModel::PackageIdentity PackageIdentity::ParsePackageFullName(hstring const& packageFullName)
    {
        throw hresult_not_implemented();
    }
    hstring PackageIdentity::FormatPackageFamilyName(hstring const& packageFullName)
    {
        throw hresult_not_implemented();
    }
    hstring PackageIdentity::FormatPackageFamilyName(hstring const& packagename, hstring const& publisher)
    {
        throw hresult_not_implemented();
    }
    hstring PackageIdentity::FormatPackageFamilyNameGivenPublisherId(hstring const& packagename, hstring const& publisherId)
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::ApplicationModel::PackageFamilyIdentity PackageIdentity::ParsePackageFamilyName(hstring const& packageFamilyName)
    {
        throw hresult_not_implemented();
    }
    bool PackageIdentity::VerifyPackageId(hstring const& packagename, winrt::Windows::ApplicationModel::PackageVersion const& version, winrt::Windows::System::ProcessorArchitecture const& architecture, hstring const& resourceId, hstring const& publisher)
    {
        throw hresult_not_implemented();
    }
    bool PackageIdentity::VerifyPackageIdGivenPublisherId(hstring const& packagename, winrt::Windows::ApplicationModel::PackageVersion const& version, winrt::Windows::System::ProcessorArchitecture const& architecture, hstring const& resourceId, hstring const& publisherId)
    {
        throw hresult_not_implemented();
    }
    bool PackageIdentity::VerifyPackageFullName(hstring const& packageFullName)
    {
        throw hresult_not_implemented();
    }
    bool PackageIdentity::VerifyPackageFamilyName(hstring const& packageFullName)
    {
        throw hresult_not_implemented();
    }
    hstring PackageIdentity::Name()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::ApplicationModel::PackageVersion PackageIdentity::Version()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::System::ProcessorArchitecture PackageIdentity::Architecture()
    {
        throw hresult_not_implemented();
    }
    hstring PackageIdentity::ResouceId()
    {
        throw hresult_not_implemented();
    }
    hstring PackageIdentity::Publisher()
    {
        throw hresult_not_implemented();
    }
    hstring PackageIdentity::PublisherId()
    {
        throw hresult_not_implemented();
    }
    hstring PackageIdentity::PackageFullName()
    {
        throw hresult_not_implemented();
    }
    hstring PackageIdentity::PackageFamilyName()
    {
        throw hresult_not_implemented();
    }
}
