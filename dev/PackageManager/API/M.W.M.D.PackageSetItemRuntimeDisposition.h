// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.PackageSetItemRuntimeDisposition.g.h"

#include "MsixDynamicDependency.h"
#include <winrt/Microsoft.Windows.ApplicationModel.DynamicDependency.h>

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageSetItemRuntimeDisposition : PackageSetItemRuntimeDispositionT<PackageSetItemRuntimeDisposition>
    {
        PackageSetItemRuntimeDisposition() = default;
        PackageSetItemRuntimeDisposition(winrt::hstring const& packageSetItemId,
                                         winrt::hstring const& packageFullName,
                                         winrt::hstring const& packageDependencyId,
                                         winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContextId packageDependencyContextId) :
            m_packageSetItemId(packageSetItemId),
            m_packageFullName(packageFullName),
            m_packageDependencyId(packageDependencyId),
            m_packageDependencyContextId(packageDependencyContextId)
        {
        }
        PackageSetItemRuntimeDisposition(winrt::hstring const& packageSetItemId,
                                         winrt::hstring const& packageFullName,
                                         winrt::hstring const& packageDependencyId,
                                         MDD_PACKAGEDEPENDENCY_CONTEXT mddPackageDependencyContext) :
            m_packageSetItemId(packageSetItemId),
            m_packageFullName(packageFullName),
            m_packageDependencyId(packageDependencyId),
            m_packageDependencyContextId(ToContextId(mddPackageDependencyContext))
        {
        }

        hstring PackageSetItemId();
        hstring PackageFullName();
        hstring PackageDependencyId();
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContextId PackageDependencyContextId();

    private:
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContextId ToContextId(MDD_PACKAGEDEPENDENCY_CONTEXT mddPackageDependencyContext);

    private:
        hstring m_packageSetItemId;
        hstring m_packageFullName;
        hstring m_packageDependencyId;
        winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContextId m_packageDependencyContextId;
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageSetItemRuntimeDisposition : PackageSetItemRuntimeDispositionT<PackageSetItemRuntimeDisposition, implementation::PackageSetItemRuntimeDisposition>
    {
    };
}
