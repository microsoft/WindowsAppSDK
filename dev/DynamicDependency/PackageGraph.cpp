// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>

#include <PackageGraph.h>

#include <PackageGraphNode.h>

static std::mutex g_lock;
std::vector<Microsoft::ApplicationModel::DynamicDependency::PackageGraphNode> g_packageGraph;

std::unique_lock<std::mutex> AcquirePackageGraphLock()
{
    return std::unique_lock<std::mutex>(g_lock);
}

HRESULT ResolvePackageDependency(
    PCWSTR packageDependencyId,
    wil::unique_process_heap_string& packageFullName)
{
    RETURN_IF_FAILED(ResolvePackageDependency(packageDependencyId, MddAddPackageDependencyOptions::None, packageFullName));
    return S_OK;
}

HRESULT ResolvePackageDependency(
    PCWSTR /*packageDependencyId*/,
    MddAddPackageDependencyOptions /*options*/,
    wil::unique_process_heap_string& /*packageFullName*/)
{
    RETURN_HR(E_NOTIMPL);
}

HRESULT AddToPackageGraph(
    PCWSTR /*packageFullName*/,
    INT32 /*rank*/,
    MddAddPackageDependencyOptions /*options*/,
    MDD_PACKAGEDEPENDENCY_CONTEXT& /*context*/)
{
    RETURN_HR(E_NOTIMPL);
}

HRESULT RemoveFromPackageGraph(
    MDD_PACKAGEDEPENDENCY_CONTEXT /*context*/)
{
    RETURN_HR(E_NOTIMPL);
}
