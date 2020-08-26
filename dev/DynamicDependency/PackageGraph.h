// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if !defined(PACKAGEGRAPH_H)
#define PACKAGEGRAPH_H

#include <MsixDynamicDependency.h>

std::unique_lock<std::mutex> AcquirePackageGraphLock();

HRESULT ResolvePackageDependency(
    PCWSTR packageDependencyId,
    wil::unique_process_heap_string& packageFullName);

HRESULT ResolvePackageDependency(
    PCWSTR packageDependencyId,
    MddAddPackageDependencyOptions options,
    wil::unique_process_heap_string& packageFullName);

HRESULT AddToPackageGraph(
    PCWSTR packageFullName,
    INT32 rank,
    MddAddPackageDependencyOptions options,
    MDD_PACKAGEDEPENDENCY_CONTEXT& context);

HRESULT RemoveFromPackageGraph(MDD_PACKAGEDEPENDENCY_CONTEXT context);

#endif // PACKAGEGRAPH_H
