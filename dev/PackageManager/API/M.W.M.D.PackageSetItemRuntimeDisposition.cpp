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
}
