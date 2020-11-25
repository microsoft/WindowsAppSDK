// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "Microsoft.ApplicationModel.DynamicDependency.PackageDependencyContext.g.h"

#include "winrt_namespaces.h"

#include <MsixDynamicDependency.h>

namespace winrt::Microsoft::ApplicationModel::DynamicDependency::implementation
{
    struct PackageDependencyContext : PackageDependencyContextT<PackageDependencyContext>
    {
        PackageDependencyContext() = default;

        PackageDependencyContext(MDD_PACKAGEDEPENDENCY_CONTEXT context);
        PackageDependencyContext(Microsoft::ApplicationModel::DynamicDependency::PackageDependencyContextId const& contextId);

        winrt::PackageDependencyContextId ContextId();
        hstring PackageDependencyId();
        hstring PackageFullName();
        void Remove();

    private:
        winrt::PackageDependencyContextId m_contextId;
    };
}
namespace winrt::Microsoft::ApplicationModel::DynamicDependency::factory_implementation
{
    struct PackageDependencyContext : PackageDependencyContextT<PackageDependencyContext, implementation::PackageDependencyContext>
    {
    };
}
