// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "PackageGraphManager.h"

std::mutex MddCore::PackageGraphManager::s_lock;
MddCore::PackageGraph MddCore::PackageGraphManager::s_packageGraph;

HRESULT MddCore::PackageGraphManager::ResolvePackageDependency(
    PCWSTR packageDependencyId,
    MddAddPackageDependencyOptions options,
    wil::unique_process_heap_string& packageFullName)
{
    std::unique_lock<std::mutex> lock(s_lock);

    return s_packageGraph.ResolvePackageDependency(packageDependencyId, options, packageFullName);
}

HRESULT MddCore::PackageGraphManager::AddToPackageGraph(
    PCWSTR packageDependencyId,
    INT32 rank,
    MddAddPackageDependencyOptions options,
    _Out_ MDD_PACKAGEDEPENDENCY_CONTEXT* context,
    _Outptr_opt_result_maybenull_ PWSTR* packageFullName)
{
    std::unique_lock<std::mutex> lock(s_lock);

    return s_packageGraph.Add(packageDependencyId, rank, options, *context, packageFullName);
}

void MddCore::PackageGraphManager::RemoveFromPackageGraph(
    MDD_PACKAGEDEPENDENCY_CONTEXT context)
{
    std::unique_lock<std::mutex> lock(s_lock);

    (void) LOG_IF_FAILED(s_packageGraph.Remove(context));
}

HRESULT MddCore::PackageGraphManager::GetPackageDependencyForContext(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT context,
    wil::unique_process_heap_string& packageDependencyId)
{
    std::unique_lock<std::mutex> lock(s_lock);

    return s_packageGraph.GetPackageDependencyForContext(context, packageDependencyId);
}

// On success, buffer is a byte[] containing PACKAGE_INFO[count] followed by all variable length data.
// Pointers in PACKAGE_INFO (all PWSTR) are null or point to their value in the variable length data.
//
// On success but \c bufferLength is too small to hold all the data, we still set bufferLength to the
// size needed for all this data but return ERROR_INSUFFICIENT_BUFFER (as an HRESULT).
HRESULT MddCore::PackageGraphManager::GetCurrentPackageInfo2(
    const UINT32 flags,
    PackagePathType packagePathType,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count,
    GetCurrentPackageInfo2Function getCurrentPackageInfo2) noexcept try
{
    if (count)
    {
        *count = 0;
    }

    std::unique_lock<std::mutex> lock(s_lock);

    // Is the package graph empty?
    if (s_packageGraph.PackageGraphNodes().empty())
    {
        // No dynamic package data. Is there a static package graph?
        UINT32 length{};
        const LONG rc{ getCurrentPackageInfo2(flags, packagePathType, &length, nullptr, nullptr) };
        if (rc == APPMODEL_ERROR_NO_PACKAGE)
        {
            // No static package data either
            RETURN_WIN32(APPMODEL_ERROR_NO_PACKAGE);
        }
    }

    // We manage the package graph as a list of nodes, where each contain contains information about 1+ package.
    //
    // Find all the packages across the package graph that match our filter criteria (see flags in
    // https://docs.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getcurrentpackageinfo2).
    //
    // Then compute the size needed for all the data.
    //
    // The if the buffer's big enough, serialize the data into buffer.
    //
    // Either way, set bufferLength with the buffer size needed for all the data.

    std::vector<const MddCore::PackageGraphNode*> matchingPackageInfo;

    UINT32 staticPackageGraphBufferLength{};
    wil::unique_cotaskmem_ptr<BYTE[]> staticPackageGraphBuffer;
    const PACKAGE_INFO* staticPackageInfo{};
    UINT32 staticPackagesCount{};

    UINT32 dynamicPackagesCount{};
    for (auto& packageGraphNode : s_packageGraph.PackageGraphNodes())
    {
        if (packageGraphNode.IsDynamic())
        {
            // It's dynamic data we manage. Does the node have any matching packages?
            const auto countMatchingPackages{ packageGraphNode.CountMatchingPackages(flags, packagePathType) };
            if (countMatchingPackages > 0)
            {
                matchingPackageInfo.push_back(&packageGraphNode);
                dynamicPackagesCount += countMatchingPackages;
            }
        }
        else
        {
            // It's static data the OS manages. Does the node have any matching packages?
            LONG rc{ getCurrentPackageInfo2(flags, packagePathType, &staticPackageGraphBufferLength, nullptr, nullptr) };
            if (rc == APPMODEL_ERROR_NO_PACKAGE)
            {
                // The process has no static package info
                // Nothing to do
            }
            else if (rc == ERROR_INSUFFICIENT_BUFFER)
            {
                // We've got 1+ match! Get the data
                staticPackageGraphBuffer = wil::make_unique_cotaskmem<BYTE[]>(staticPackageGraphBufferLength);
                RETURN_IF_WIN32_ERROR(getCurrentPackageInfo2(flags, packagePathType, &staticPackageGraphBufferLength, staticPackageGraphBuffer.get(), &staticPackagesCount));
                staticPackageInfo = reinterpret_cast<PACKAGE_INFO*>(staticPackageGraphBuffer.get());
            }
            else
            {
                RETURN_WIN32(rc);
            }
        }
    }

    // Update the total 'count' (if any)
    const auto totalPackagesCount{ staticPackagesCount + dynamicPackagesCount };
    if (count)
    {
        *count = totalPackagesCount;
    }

    // Do we have anything to report?
    if (totalPackagesCount == 0)
    {
        // No matches!
        *bufferLength = 0;
        return S_OK;
    }

    // Compute the buffer length used/needed and fill buffer (if we can)
    auto bufferNeeded{ SerializePackageInfoToBuffer(flags, packagePathType, *bufferLength, buffer, matchingPackageInfo, dynamicPackagesCount, staticPackageInfo, staticPackagesCount) };
    const auto isInsufficientBuffer{ *bufferLength < bufferNeeded };
    *bufferLength = bufferNeeded;
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), isInsufficientBuffer);

    return S_OK;
}
CATCH_RETURN();

UINT32 MddCore::PackageGraphManager::SerializePackageInfoToBuffer(
    const UINT32 flags,
    const PackagePathType packagePathType,
    const UINT32 bufferLength,
    BYTE* buffer,
    const std::vector<const MddCore::PackageGraphNode*>& matchingPackageInfo,
    const UINT32 dynamicPackagesCount,
    const PACKAGE_INFO* staticPackageInfo,
    const UINT32 staticPackagesCount)
{
    // Setup our initial pointers to write the PACKAGE_INFO[] and the variable length data
    const auto totalPackagesCount{ dynamicPackagesCount + staticPackagesCount };
    UINT32 bufferNeeded{ sizeof(PACKAGE_INFO) * totalPackagesCount };
    auto toPackageInfo{ reinterpret_cast<PACKAGE_INFO*>(buffer) };

    // Let's do it...
    for (auto& matchingPackageGraphNode : matchingPackageInfo)
    {
        UINT32 fromPackagesCount{};
        const void* fromPackagesBuffer{};
        wil::unique_cotaskmem_ptr<BYTE[]> dynamicPackagesBuffer;

        if (matchingPackageGraphNode)
        {
            // It's dynamic package data
            fromPackagesCount = std::move(matchingPackageGraphNode->GetMatchingPackages(flags, packagePathType, dynamicPackagesBuffer));
            fromPackagesBuffer = dynamicPackagesBuffer.get();
        }
        else
        {
            // It's static package data
            fromPackagesCount = staticPackagesCount;
            fromPackagesBuffer = staticPackageInfo;
        }
        auto fromPackageInfo{ static_cast<const PACKAGE_INFO*>(fromPackagesBuffer) };

        // Copy the package info to the buffer
        for (UINT32 index=0; index < fromPackagesCount; ++index, ++fromPackageInfo, ++toPackageInfo)
        {
            // Copy over the fixed length data
            if (bufferNeeded <= bufferLength)
            {
                memset(toPackageInfo, 0, sizeof(*toPackageInfo));
                toPackageInfo->flags = fromPackageInfo->flags;
                toPackageInfo->packageId.processorArchitecture = fromPackageInfo->packageId.processorArchitecture;
                toPackageInfo->packageId.version = fromPackageInfo->packageId.version;
            }
            SerializeStringToBuffer(bufferLength, buffer, bufferNeeded, toPackageInfo->path, fromPackageInfo->path);
            SerializeStringToBuffer(bufferLength, buffer, bufferNeeded, toPackageInfo->packageFullName, fromPackageInfo->packageFullName);
            SerializeStringToBuffer(bufferLength, buffer, bufferNeeded, toPackageInfo->packageFamilyName, fromPackageInfo->packageFamilyName);
            SerializeStringToBuffer(bufferLength, buffer, bufferNeeded, toPackageInfo->packageId.name, fromPackageInfo->packageId.name);
            SerializeStringToBuffer(bufferLength, buffer, bufferNeeded, toPackageInfo->packageId.publisher, fromPackageInfo->packageId.publisher);
            SerializeStringToBuffer(bufferLength, buffer, bufferNeeded, toPackageInfo->packageId.resourceId, fromPackageInfo->packageId.resourceId);
            SerializeStringToBuffer(bufferLength, buffer, bufferNeeded, toPackageInfo->packageId.publisherId, fromPackageInfo->packageId.publisherId);
        }
    }

    return bufferNeeded;
}

void MddCore::PackageGraphManager::SerializeStringToBuffer(
    const UINT32 bufferLength,
    BYTE*& buffer,
    UINT32& bufferNeeded,
    PWSTR& to,
    PCWSTR from)
{
    if (from)
    {
        const auto bufferUsed{ bufferNeeded };
        const auto size{ wcssize(from) };
        bufferNeeded += size;
        if (bufferNeeded <= bufferLength)
        {
            memcpy(buffer + bufferUsed, from, size);
            to = reinterpret_cast<PWSTR>(buffer + bufferUsed);
            //buffer += size;
        }
    }
}

HRESULT MddCore::PackageGraphManager::GetActivationFactory(
    HSTRING className,
    REFIID iid,
    MddCore::WinRTInprocModule::ThreadingModel& threadingModel,
    void** factory)
{
    std::unique_lock<std::mutex> lock(s_lock);

    return s_packageGraph.GetActivationFactory(className, iid, threadingModel, factory);
}
