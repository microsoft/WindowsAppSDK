// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>

#include "M.W.AM.PackageApplications.h"

#include "Microsoft.Windows.ApplicationModel.PackageApplications.g.cpp"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    PackageApplications::PackageApplications(winrt::Microsoft::Windows::ApplicationModel::Package const& package) :
        m_package(package)
    {
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::ApplicationModel::Core::AppListEntry> PackageApplications::GetAppListEntries()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::ApplicationModel::Core::AppListEntry>> PackageApplications::GetAppListEntriesAsync()
    {
        throw hresult_not_implemented();
    }
}
