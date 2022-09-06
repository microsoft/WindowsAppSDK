// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyContext.g.h"

#include "winrt_namespaces.h"

#include <MsixDynamicDependency.h>

namespace winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::implementation
{
    struct PackageDependencyContext : PackageDependencyContextT<PackageDependencyContext>
    {
        PackageDependencyContext() = default;

        PackageDependencyContext(MDD_PACKAGEDEPENDENCY_CONTEXT context);
        PackageDependencyContext(Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContextId const& contextId);

        winrt::PackageDependencyContextId ContextId();
        hstring PackageDependencyId();
        hstring PackageFullName();
        void Remove();

    private:
        winrt::PackageDependencyContextId m_contextId;
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::factory_implementation
{
    struct PackageDependencyContext : PackageDependencyContextT<PackageDependencyContext, implementation::PackageDependencyContext>
    {
    };
}
