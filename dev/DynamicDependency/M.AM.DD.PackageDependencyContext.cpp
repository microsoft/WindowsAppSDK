// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "M.AM.DD.PackageDependencyContext.h"
#include "Microsoft.ApplicationModel.DynamicDependency.PackageDependencyContext.g.cpp"

namespace winrt::Microsoft::ApplicationModel::DynamicDependency::implementation
{
    PackageDependencyContext::PackageDependencyContext(Microsoft::ApplicationModel::DynamicDependency::PackageDependencyContextId const& contextId)
    {
        throw hresult_not_implemented();
    }
    Microsoft::ApplicationModel::DynamicDependency::PackageDependencyContextId PackageDependencyContext::ContextId()
    {
        throw hresult_not_implemented();
    }
    hstring PackageDependencyContext::PackageFullName()
    {
        throw hresult_not_implemented();
    }
    void PackageDependencyContext::Remove()
    {
        throw hresult_not_implemented();
    }
}
