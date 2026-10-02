// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "M.W.M.D.PackageSetRuntimeDisposition.h"
#include "Microsoft.Windows.Management.Deployment.PackageSetRuntimeDisposition.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageSetRuntimeDisposition : PackageSetRuntimeDispositionT<PackageSetRuntimeDisposition>
    {
        PackageSetRuntimeDisposition() = default;
#if 0
        PackageSetRuntimeDisposition(winrt::hstring const& packageSetId) :
            m_packageSetId(packageSetId)
        {
        }
        PackageSetRuntimeDisposition(winrt::hstring const& packageSetId, winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition>& packageSetItemRuntimeDispositions) :
            m_packageSetId(packageSetId),
            m_packageSetItemRuntimeDispositions(packageSetItemRuntimeDispositions)
        {
        }
#endif

        hstring PackageSetId();
        void PackageSetId(hstring const& value);
        winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition> PackageSetItemRuntimeDispositions();
    private:
        hstring m_packageSetId;
        winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition> m_packageSetItemRuntimeDispositions{};
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageSetRuntimeDisposition : PackageSetRuntimeDispositionT<PackageSetRuntimeDisposition, implementation::PackageSetRuntimeDisposition>
    {
    };
}
