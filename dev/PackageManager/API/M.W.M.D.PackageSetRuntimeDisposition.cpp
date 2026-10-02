// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.M.D.PackageSetRuntimeDisposition.h"
#include "Microsoft.Windows.Management.Deployment.PackageSetRuntimeDisposition.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    hstring PackageSetRuntimeDisposition::PackageSetId()
    {
        return m_packageSetId;
    }
    void PackageSetRuntimeDisposition::PackageSetId(hstring const& value)
    {
        m_packageSetId = value;
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition> PackageSetRuntimeDisposition::PackageSetItemRuntimeDispositions()
    {
        if (!m_packageSetItemRuntimeDispositions)
        {
            m_packageSetItemRuntimeDispositions = winrt::single_threaded_vector<winrt::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition>();
        }
        return m_packageSetItemRuntimeDispositions;
    }
}
