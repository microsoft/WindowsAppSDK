// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>

#include "M.W.AM.PackageContentGroups.h"

#include "Microsoft.Windows.ApplicationModel.PackageContentGroups.g.cpp"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    PackageContentGroups::PackageContentGroups(winrt::Microsoft::Windows::ApplicationModel::Package const& package) :
        m_package(package)
    {
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::ApplicationModel::PackageContentGroup> PackageContentGroups::GetContentGroupAsync(hstring name)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::ApplicationModel::PackageContentGroup>> PackageContentGroups::GetContentGroupsAsync()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::ApplicationModel::PackageContentGroup>> PackageContentGroups::StageContentGroups()
    {
        throw hresult_not_implemented();
    }
}
