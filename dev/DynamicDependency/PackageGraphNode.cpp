// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"

#include "PackageGraphNode.h"

MddCore::PackageGraphNode::PackageGraphNode(
    PCWSTR packageFullName,
    INT32 rank) :
    m_rank(rank)
{
    THROW_IF_WIN32_ERROR(OpenPackageInfoByFullName(packageFullName, 0, &m_packageInfoReference));
    m_packageInfo = std::move(MddCore::PackageInfo::FromPackageInfoReference(m_packageInfoReference.get()));

    BuildPathList();
}

UINT32 MddCore::PackageGraphNode::CountMatchingPackages(
    const UINT32 flags,
    const PackagePathType packagePathType) const
{
    //TODO Replace with m_packageInfo.Count()
    UINT32 bufferLength{};
    UINT32 count{};
    const LONG rc{ ::GetPackageInfo2(m_packageInfoReference.get(), flags, packagePathType, &bufferLength, nullptr, &count) };
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
    //TODO Replace with m_packageInfo ?
    UINT32 bufferLength{};
    UINT32 count{};
    const LONG rc{ ::GetPackageInfo2(m_packageInfoReference.get(), flags, packagePathType, &bufferLength, nullptr, &count) };
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

void MddCore::PackageGraphNode::AddDllDirectories()
{
    for (size_t index=0; index < m_packageInfo.Count(); ++index)
    {
        const auto& package = m_packageInfo.Package(index);

        wil::unique_dll_directory_cookie cookie(AddDllDirectory(package.path));

        m_addDllDirectoryCookies.push_back(std::move(cookie));
    }
}

void MddCore::PackageGraphNode::RemoveDllDirectories()
{
    for (auto& cookie : m_addDllDirectoryCookies)
    {
        RemoveDllDirectory(cookie.get());
    }
    m_addDllDirectoryCookies.clear();
}

void MddCore::PackageGraphNode::BuildPathList()
{
    // Should only be called if we have package info
    FAIL_FAST_HR_IF(E_UNEXPECTED, m_packageInfo.Count() == 0);

    // Build a semi-colon delimited list of paths for the packages in the package info
    std::wstring pathList;
    for (size_t index=0; index < m_packageInfo.Count(); ++index)
    {
        const auto& package = m_packageInfo.Package(index);
        if (index > 0)
        {
            pathList += L';';
        }
        pathList += package.path;
    }
    m_pathList = std::move(pathList);
}
