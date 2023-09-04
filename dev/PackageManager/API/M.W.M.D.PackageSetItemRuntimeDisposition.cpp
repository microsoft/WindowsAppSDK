// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.M.D.PackageSetItemRuntimeDisposition.h"
#include "Microsoft.Windows.Management.Deployment.PackageSetItemRuntimeDisposition.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    hstring PackageSetItemRuntimeDisposition::PackageSetItemId()
    {
        return m_packageSetItemId;
    }
    hstring PackageSetItemRuntimeDisposition::PackageFullName()
    {
        return m_packageFullName;
    }
    hstring PackageSetItemRuntimeDisposition::PackageDependencyId()
    {
        return m_packageDependencyId;
    }
    winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContextId PackageSetItemRuntimeDisposition::PackageDependencyContextId()
    {
        return m_packageDependencyContextId;
    }
    winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContextId PackageSetItemRuntimeDisposition::ToContextId(
        MDD_PACKAGEDEPENDENCY_CONTEXT mddPackageDependencyContext)
    {
        return winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContextId{ static_cast<uint64_t>(reinterpret_cast<INT_PTR>(mddPackageDependencyContext)) };
    }
}
