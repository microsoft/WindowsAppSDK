// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __APPMODEL_PACKAGEGRAPH_H
#define __APPMODEL_PACKAGEGRAPH_H

#include <appmodel.h>

namespace AppModel::PackageGraph
{
inline HRESULT GetCurrentPackageGraph(
    const UINT32 flags,
    uint32_t& packageInfoCount,
    const PACKAGE_INFO*& packageInfo,
    wil::unique_cotaskmem_ptr<BYTE[]>& buffer)
{
   packageInfoCount = 0;
    packageInfo = nullptr;

    uint32_t bufferLength{};
    LONG rc{ ::GetCurrentPackageInfo(flags, &bufferLength, nullptr, &packageInfoCount) };
    if ((rc == APPMODEL_ERROR_NO_PACKAGE) || (packageInfoCount == 0))
   {
        // No packages. We�re done
        return S_OK;
    }
    RETURN_HR_IF(HRESULT_FROM_WIN32(rc), rc != ERROR_INSUFFICIENT_BUFFER);

    buffer = wil::make_unique_cotaskmem<BYTE[]>(bufferLength);
    RETURN_IF_WIN32_ERROR(::GetCurrentPackageInfo(flags, &bufferLength, buffer.get(), &packageInfoCount));
    packageInfo = reinterpret_cast<PACKAGE_INFO*>(buffer.get());
    return S_OK;
}
}

#endif // __APPMODEL_PACKAGEGRAPH_H
