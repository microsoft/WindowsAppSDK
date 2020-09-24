// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"

#include "PackageGraphNode.h"

UINT32 MddCore::PackageGraphNode::CountMatchingPackages(
    const UINT32 flags,
    const PackagePathType packagePathType) const
{
    UINT32 bufferLength{};
    UINT32 count{};
    const LONG rc = ::GetPackageInfo2(m_packageInfoReference.get(), flags, packagePathType, &bufferLength, nullptr, &count);
    if ((rc == ERROR_SUCCESS) || (rc == ERROR_INSUFFICIENT_BUFFER))
    {
        return count;
    }
    THROW_WIN32(rc);
}

UINT32 MddCore::PackageGraphNode::GetMatchingPackages(
    const UINT32 flags,
    const PackagePathType packagePathType,
    wil::unique_cotaskmem_ptr<BYTE[]>& buffer) const
{
    UINT32 bufferLength{};
    UINT32 count{};
    const LONG rc = ::GetPackageInfo2(m_packageInfoReference.get(), flags, packagePathType, &bufferLength, nullptr, &count);
    if (rc == ERROR_SUCCESS)
    {
        // Success with no buffer can only mean count==0
        return 0;
    }
    else if (rc == ERROR_INSUFFICIENT_BUFFER)
    {
        buffer = std::move(wil::make_unique_cotaskmem<BYTE[]>(bufferLength));
        THROW_IF_WIN32_ERROR(::GetPackageInfo2(m_packageInfoReference.get(), flags, packagePathType, &bufferLength, buffer.get(), nullptr));
        return count;
    }
    else
    {
        THROW_WIN32(rc);
    }
}
