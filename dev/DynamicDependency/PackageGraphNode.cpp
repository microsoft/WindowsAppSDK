// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"

#include "PackageGraphNode.h"

volatile MDD_PACKAGEDEPENDENCY_CONTEXT MddCore::PackageGraphNode::s_lastContext{};

MddCore::PackageGraphNode::PackageGraphNode(
    _In_ PCWSTR packageFullName,
    INT32 rank,
    _In_ PCWSTR packageDependencyId) :
    m_rank(rank),
    m_id(packageDependencyId)
{
    THROW_IF_WIN32_ERROR(OpenPackageInfoByFullName(packageFullName, 0, &m_packageInfoReference));
    m_packageInfo = std::move(MddCore::PackageInfo::FromPackageInfoReference(m_packageInfoReference.get()));

    BuildPathList();
}

UINT32 MddCore::PackageGraphNode::CountMatchingPackages(
    const UINT32 flags,
    const PackagePathType packagePathType) const
{
    UINT32 bufferLength{};
    UINT32 count{};
    const LONG rc{ ::GetPackageInfo2(m_packageInfoReference.get(), flags, packagePathType, &bufferLength, nullptr, &count) };
    if ((rc != ERROR_SUCCESS) && (rc != ERROR_INSUFFICIENT_BUFFER))
    {
        THROW_WIN32(rc);
    }
    return count;
}

UINT32 MddCore::PackageGraphNode::GetMatchingPackages(
    const UINT32 flags,
    const PackagePathType packagePathType,
    wil::unique_cotaskmem_ptr<BYTE[]>& buffer) const
{
    UINT32 bufferLength{};
    const LONG rc{ ::GetPackageInfo2(m_packageInfoReference.get(), flags, packagePathType, &bufferLength, nullptr, nullptr) };
    if (rc == ERROR_SUCCESS)
    {
        // Success with no buffer can only mean count==0
        return 0;
    }
    else if (rc != ERROR_INSUFFICIENT_BUFFER)
    {
        THROW_WIN32(rc);
    }
    buffer = std::move(wil::make_unique_cotaskmem<BYTE[]>(bufferLength));
    UINT32 count{};
    THROW_IF_WIN32_ERROR(::GetPackageInfo2(m_packageInfoReference.get(), flags, packagePathType, &bufferLength, buffer.get(), &count));
    return count;
}

void MddCore::PackageGraphNode::GenerateContext()
{
#if defined(_WIN64)
    MDD_PACKAGEDEPENDENCY_CONTEXT context{ reinterpret_cast<MDD_PACKAGEDEPENDENCY_CONTEXT>(InterlockedIncrement64(reinterpret_cast<volatile LONG64*>(&s_lastContext))) };
#else
    MDD_PACKAGEDEPENDENCY_CONTEXT context{ reinterpret_cast<MDD_PACKAGEDEPENDENCY_CONTEXT>(InterlockedIncrement(reinterpret_cast<volatile LONG*>(&s_lastContext))) };
#endif

    m_context.reset(context);
}

void MddCore::PackageGraphNode::AddDllDirectories()
{
    for (size_t index=0; index < m_packageInfo.Count(); ++index)
    {
        const auto& package{ m_packageInfo.Package(index) };

        wil::unique_dll_directory_cookie cookie(AddDllDirectory(package.path));

        m_addDllDirectoryCookies.push_back(std::move(cookie));
    }
}

void MddCore::PackageGraphNode::RemoveDllDirectories()
{
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
        const auto& package{ m_packageInfo.Package(index) };
        if (index > 0)
        {
            pathList += L';';
        }
        pathList += package.path;
    }
    m_pathList = std::move(pathList);
}

HRESULT MddCore::PackageGraphNode::GetActivationFactory(
    HSTRING className,
    const std::wstring& activatableClassId,
    REFIID iid,
    MddCore::WinRTInprocModule::ThreadingModel& threadingModel,
    void** factory)
{
    for (size_t index = 0; index < m_inprocModules.size(); ++index)
    {
        auto& inprocModule{ m_inprocModules[index] };

        auto acidThreadingModel{ inprocModule.Find(activatableClassId) };
        if (acidThreadingModel != MddCore::WinRTInprocModule::ThreadingModel::Unknown)
        {
            RETURN_IF_FAILED(inprocModule.GetActivationFactory(className, iid, factory));
            threadingModel = acidThreadingModel;
            return S_OK;
        }
    }

    // Not found
    threadingModel = MddCore::WinRTInprocModule::ThreadingModel::Unknown;
    *factory = nullptr;
    return S_OK;
}
