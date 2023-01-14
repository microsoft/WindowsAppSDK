// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>

#include "M.W.AM.PackageInstallInfo.h"

#include "Microsoft.Windows.ApplicationModel.PackageInstallInfo.g.cpp"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    PackageInstallInfo::PackageInstallInfo(winrt::Microsoft::Windows::ApplicationModel::Package const& package) :
        m_package(package)
    {
    }
    winrt::Windows::Foundation::DateTime PackageInstallInfo::WhenFirstRegisteredForUser()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::DateTime PackageInstallInfo::WhenLastRegisteredForUser()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::ApplicationModel::AppInstallerInfo PackageInstallInfo::GetAppInstallerInfo()
    {
        throw hresult_not_implemented();
    }
    hstring PackageInstallInfo::SourceUriSchemeName()
    {
        throw hresult_not_implemented();
    }
}
