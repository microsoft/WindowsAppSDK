// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageSet.h"
#include "Microsoft.Windows.Management.Deployment.PackageSet.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    hstring PackageSet::Id()
    {
        return m_id;
    }
    void PackageSet::Id(hstring const& value)
    {
        m_id = value;
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Management::Deployment::PackageSetItem> PackageSet::PackageSetItems()
    {
        return m_packageSetItems;
    }
}
