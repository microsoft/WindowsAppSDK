// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>

#include "M.W.AM.FindPackageOptions.h"

#include "Microsoft.Windows.ApplicationModel.FindPackageOptions.g.cpp"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    winrt::Windows::System::User FindPackageOptions::User()
    {
        throw hresult_not_implemented();
    }
    void FindPackageOptions::User(winrt::Windows::System::User const& value)
    {
        throw hresult_not_implemented();
    }
    hstring FindPackageOptions::PackageFullName()
    {
        return m_packageFullName;
    }
    void FindPackageOptions::PackageFullName(hstring const& value)
    {
        m_packageFullName = value;
    }
    hstring FindPackageOptions::PackageFamilyName()
    {
        return m_packageFamilyName;
    }
    void FindPackageOptions::PackageFamilyName(hstring const& value)
    {
        m_packageFamilyName = value;
    }
    hstring FindPackageOptions::PackageName()
    {
        return m_packageName;
    }
    void FindPackageOptions::PackageName(hstring const& value)
    {
        m_packageName = value;
    }
    hstring FindPackageOptions::PackagePublisher()
    {
        return m_packagePublisher;
    }
    void FindPackageOptions::PackagePublisher(hstring const& value)
    {
        m_packagePublisher = value;
    }
    hstring FindPackageOptions::PackagePublisherId()
    {
        return m_packagePublisherId;
    }
    void FindPackageOptions::PackagePublisherId(hstring const& value)
    {
        m_packagePublisherId = value;
    }
    bool FindPackageOptions::IsMain()
    {
        return m_isMain;
    }
    void FindPackageOptions::IsMain(bool value)
    {
        m_isMain = value;
    }
    bool FindPackageOptions::IsFramework()
    {
        return m_isFramework;
    }
    void FindPackageOptions::IsFramework(bool value)
    {
        m_isFramework = value;
    }
    bool FindPackageOptions::IsResource()
    {
        return m_isResource;
    }
    void FindPackageOptions::IsResource(bool value)
    {
        m_isResource = value;
    }
    bool FindPackageOptions::IsOptional()
    {
        return m_isOptional;
    }
    void FindPackageOptions::IsOptional(bool value)
    {
        m_isOptional = value;
    }
    bool FindPackageOptions::IsOptionalInRelatedSet()
    {
        return m_isOptionalInRelatedSet;
    }
    void FindPackageOptions::IsOptionalInRelatedSet(bool value)
    {
        m_isOptionalInRelatedSet = value;
    }
    bool FindPackageOptions::IsOptionalNotInRelatedSet()
    {
        return m_isOptionalNotInRelatedSet;
    }
    void FindPackageOptions::IsOptionalNotInRelatedSet(bool value)
    {
        m_isOptionalNotInRelatedSet = value;
    }
    bool FindPackageOptions::IsBundle()
    {
        return m_isBundle;
    }
    void FindPackageOptions::IsBundle(bool value)
    {
        m_isBundle = value;
    }
    bool FindPackageOptions::IsProvisioned()
    {
        return m_isProvisioned;
    }
    void FindPackageOptions::IsProvisioned(bool value)
    {
        m_isProvisioned = value;
    }
}
