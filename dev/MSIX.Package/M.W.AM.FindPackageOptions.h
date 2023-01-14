// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.FindPackageOptions.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    struct FindPackageOptions : FindPackageOptionsT<FindPackageOptions>
    {
        FindPackageOptions() = default;

        winrt::Windows::System::User User();
        void User(winrt::Windows::System::User const& value);
        hstring PackageFullName();
        void PackageFullName(hstring const& value);
        hstring PackageFamilyName();
        void PackageFamilyName(hstring const& value);
        hstring PackageName();
        void PackageName(hstring const& value);
        hstring PackagePublisher();
        void PackagePublisher(hstring const& value);
        hstring PackagePublisherId();
        void PackagePublisherId(hstring const& value);
        bool IsMain();
        void IsMain(bool value);
        bool IsFramework();
        void IsFramework(bool value);
        bool IsResource();
        void IsResource(bool value);
        bool IsOptional();
        void IsOptional(bool value);
        bool IsOptionalInRelatedSet();
        void IsOptionalInRelatedSet(bool value);
        bool IsOptionalNotInRelatedSet();
        void IsOptionalNotInRelatedSet(bool value);
        bool IsBundle();
        void IsBundle(bool value);
        bool IsProvisioned();
        void IsProvisioned(bool value);

    private:
        //TODO winrt::Windows::System::User m_user;
        hstring m_packageFullName;
        hstring m_packageFamilyName;
        hstring m_packageName;
        hstring m_packagePublisher;
        hstring m_packagePublisherId;
        bool m_isMain{};
        bool m_isFramework{};
        bool m_isResource{};
        bool m_isOptional{};
        bool m_isOptionalInRelatedSet{};
        bool m_isOptionalNotInRelatedSet{};
        bool m_isBundle{};
        bool m_isProvisioned{};
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::factory_implementation
{
    struct FindPackageOptions : FindPackageOptionsT<FindPackageOptions, implementation::FindPackageOptions>
    {
    };
}
