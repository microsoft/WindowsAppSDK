// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "PackageGraphManager.h"

#include "MddDetourPackageGraph.h"

std::recursive_mutex MddCore::PackageGraphManager::s_lock;
MddCore::PackageGraph MddCore::PackageGraphManager::s_packageGraph;
volatile ULONG MddCore::PackageGraphManager::s_packageGraphRevisionId{};

UINT32 MddCore::PackageGraphManager::GetPackageGraphRevisionId()
{
    return static_cast<UINT32>(ReadULongAcquire(&s_packageGraphRevisionId));
}

UINT32 MddCore::PackageGraphManager::IncrementPackageGraphRevisionId()
{
    return static_cast<UINT32>(InterlockedIncrement(&s_packageGraphRevisionId));
}

UINT32 MddCore::PackageGraphManager::SetPackageGraphRevisionId(const UINT32 value)
{
    return static_cast<UINT32>(InterlockedExchange(&s_packageGraphRevisionId, value));
}

HRESULT MddCore::PackageGraphManager::GetResolvedPackageDependency(
    PCWSTR packageDependencyId,
    wil::unique_process_heap_string& packageFullName)
{
    std::unique_lock<std::recursive_mutex> lock(s_lock);

    return s_packageGraph.GetResolvedPackageDependency(packageDependencyId, packageFullName);
}

HRESULT MddCore::PackageGraphManager::GetResolvedPackageDependency2(
    PCWSTR packageDependencyId,
    wil::unique_process_heap_string& packageFullName)
{
    std::unique_lock<std::recursive_mutex> lock(s_lock);

    return s_packageGraph.GetResolvedPackageDependency2(packageDependencyId, packageFullName);
}

HRESULT MddCore::PackageGraphManager::ResolvePackageDependency(
    PCWSTR packageDependencyId,
    MddAddPackageDependencyOptions options,
    wil::unique_process_heap_string& packageFullName)
{
    std::unique_lock<std::recursive_mutex> lock(s_lock);

    return s_packageGraph.ResolvePackageDependency(packageDependencyId, options, packageFullName);
}

HRESULT MddCore::PackageGraphManager::AddToPackageGraph(
    _In_ PCWSTR packageDependencyId,
    INT32 rank,
    MddAddPackageDependencyOptions options,
    _Out_ MDD_PACKAGEDEPENDENCY_CONTEXT* context,
    _Outptr_opt_result_maybenull_ PWSTR* packageFullName)
{
    std::unique_lock<std::recursive_mutex> lock(s_lock);

    RETURN_IF_FAILED(s_packageGraph.Add(packageDependencyId, rank, options, *context, packageFullName));

    IncrementPackageGraphRevisionId();
    return S_OK;
}

void MddCore::PackageGraphManager::RemoveFromPackageGraph(
    MDD_PACKAGEDEPENDENCY_CONTEXT context)
{
    if (!context)
    {
        return;
    }

    std::unique_lock<std::recursive_mutex> lock(s_lock);

    (void) LOG_IF_FAILED(s_packageGraph.Remove(context));

    IncrementPackageGraphRevisionId();
}

HRESULT MddCore::PackageGraphManager::GetPackageDependencyForContext(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT context,
    wil::unique_process_heap_string& packageDependencyId)
{
    std::unique_lock<std::recursive_mutex> lock(s_lock);

    return s_packageGraph.GetPackageDependencyForContext(context, packageDependencyId);
}

// On success, bufferLength depends on packageInfoType:
//   * PackageInfoType_PackageInfo*Path
//     buffer is a byte[] containing PACKAGE_INFO[count] followed by all variable length data.
// Pointers in PACKAGE_INFO (all PWSTR) are null or point to their value in the variable length data.
//   * PackageInfoType_PackageInfoGeneration
//     buffer is a UINT32 containing the RevisionId (aka GenerationId). count is unused (always set to zero if not null).
//
// On success but \c bufferLength is too small to hold all the data, we still set bufferLength to the
// size needed for all this data but return ERROR_INSUFFICIENT_BUFFER (as an HRESULT).
HRESULT MddCore::PackageGraphManager::GetCurrentPackageInfo3(
    const UINT32 flags,
    PackageInfoType packageInfoType,
    UINT32* bufferLength,
    void* buffer,
    UINT32* count) noexcept try
{
    // Check parameter(s) per GetCurrentPackageInfo3 compatibility
    //   * bufferLength is required
    //   * buffer is required if bufferLength >0
    //   * count is required if buffer is not nullptr, unless caller is getting the revision (aka generation)
    RETURN_HR_IF(E_INVALIDARG, (bufferLength == nullptr) || (*bufferLength > 0 && buffer == nullptr) || ((count == nullptr) && (buffer != nullptr) && (packageInfoType != PackageInfoType_PackageInfoGeneration)));

    if (count)
    {
        *count = 0;
    }

    std::unique_lock<std::recursive_mutex> lock(s_lock);

    // Do we need Static and/or Dynamic items? NOTE: If neither are specified we need both
    const bool filterStatic{ WI_IsFlagSet(flags, PACKAGE_FILTER_STATIC) };
    const bool filterDynamic{ WI_IsFlagSet(flags, PACKAGE_FILTER_DYNAMIC) };

    // If an unpackaged process has no dynamic packages in its package graph
    // Then GetCurrentPackageInfo3() always returns APPMODEL_ERROR_NO_PACKAGE.
    //
    // If an unpackaged process has dynamic packages in its package graph
    // But flags specifies Static filter AND not Dynamic filter
    // Then GetCurrentPackageInfo3() always returns APPMODEL_ERROR_NO_PACKAGE
    //
    // Preserve these behaviors for compatibility reasons.
    if (s_packageGraph.PackageGraphNodes().empty() || (filterStatic && !filterDynamic))
    {
        return HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE);
    }

    // Are we asked for the RevisionId (aka GenerationId)?
    if (packageInfoType == PackageInfoType_PackageInfoGeneration)
    {
        const bool insufficientSpace{ *bufferLength < sizeof(UINT32) };
        *bufferLength = sizeof(UINT32);
        RETURN_HR_IF_EXPECTED(HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), insufficientSpace);

        UINT32* revisionId{ reinterpret_cast<UINT32*>(buffer) };
        *revisionId = GetPackageGraphRevisionId();
        return S_OK;
    }
    else if ((packageInfoType != PackageInfoType_PackageInfoInstallPath) &&
               (packageInfoType != PackageInfoType_PackageInfoMutablePath) &&
               (packageInfoType != PackageInfoType_PackageInfoEffectivePath) &&
               (packageInfoType != PackageInfoType_PackageInfoMachineExternalPath) &&
               (packageInfoType != PackageInfoType_PackageInfoUserExternalPath) &&
               (packageInfoType != PackageInfoType_PackageInfoEffectiveExternalPath))
    {
        // packageInfoType isn't a value we recognize and/or handle
        // Pass the call on down to Windows to handle the request
        RETURN_IF_FAILED(MddTrueGetCurrentPackageInfo3(flags, packageInfoType, bufferLength, buffer, count));
        return S_OK;
    }

    // We manage the package graph as a list of nodes, where each contain contains information about 1+ package.
    //
    // Find all the packages across the package graph that match our filter criteria (see flags in
    // https://docs.microsoft.com/windows/win32/api/appmodel/nf-appmodel-getcurrentpackageinfo2).
    //
    // Then compute the size needed for all the data.
    //
    // The if the buffer's big enough, serialize the data into buffer.
    //
    // Either way, set bufferLength with the buffer size needed for all the data.

    wil::unique_cotaskmem_ptr<BYTE[]> staticPackageGraphBuffer;
    const PACKAGE_INFO* staticPackageInfo{};
    UINT32 staticPackagesCount{};
    UINT32 dynamicPackagesCount{};

    std::vector<const MddCore::PackageGraphNode*> matchingPackageInfo;

    for (auto& packageGraphNode : s_packageGraph.PackageGraphNodes())
    {
        // Does the node have any matching packages?
        const auto countMatchingPackages{ packageGraphNode.CountMatchingPackages(flags, packageInfoType) };
        if (countMatchingPackages > 0)
        {
            matchingPackageInfo.push_back(&packageGraphNode);
            dynamicPackagesCount += countMatchingPackages;
        }
    }

    // Update the total 'count' (if any)
    const auto totalPackagesCount{ staticPackagesCount + dynamicPackagesCount };
    if (count)
    {
        *count = totalPackagesCount;
    }

    // Return code needs special handling if we match zero packages (i.e. #Static=0, #Dynamic=0, *bufferLength=0):
    //
    // If there is no static or dynamic packages (i.e. unpackaged process with no DynamicDependencies)
    // Then GetCurrentPackageInfo* returns APPMODEL_ERROR_NO_PACKAGE. Preserve this behavior.
    //
    // If there's dynamic packages but we match none AND there's no static packages AND PACKAGE_FILTER_STATIC was specified but not PACKAGE_FILTER_DYNAMIC
    // Then GetCurrentPackageInfo* returns APPMODEL_ERROR_NO_PACKAGE.
    //
    // If there's dynamic packages but we match none AND PACKAGE_FILTER_STATIC was not specified
    // or both PACKGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC were specified
    // Then GetCurrentPackageInfo* returns ERROR_SUCCESS.
    //
    // In all cases we're returning zero packages. Our return code depends on why we're returning none.
    //
    // Preserve these behaviors.
    if (totalPackagesCount == 0)
    {
        // No matches!
        *bufferLength = 0;

        // Do we need to tell our caller AppmodelErrorNoPackage?
        if (filterStatic && !filterDynamic)
        {
            return HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE);
        }
        return S_OK;
    }

    // Compute the buffer length used/needed and fill buffer (if we can)
    auto bufferNeeded{ SerializePackageInfoToBuffer(flags, packageInfoType, *bufferLength, buffer, matchingPackageInfo, dynamicPackagesCount, staticPackageInfo, staticPackagesCount) };
    const auto isInsufficientBuffer{ *bufferLength < bufferNeeded };
    *bufferLength = bufferNeeded;
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), isInsufficientBuffer);

    return S_OK;
}
CATCH_RETURN();

UINT32 MddCore::PackageGraphManager::SerializePackageInfoToBuffer(
    const UINT32 flags,
    const PackageInfoType packageInfoType,
    const UINT32 bufferLength,
    void* buffer,
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
            fromPackagesCount = std::move(matchingPackageGraphNode->GetMatchingPackages(flags, packageInfoType, dynamicPackagesBuffer));
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
    void*& buffer,
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
			BYTE* bufferAsBytes{ static_cast<BYTE*>(buffer) };
            memcpy(bufferAsBytes + bufferUsed, from, size);
            to = reinterpret_cast<PWSTR>(bufferAsBytes + bufferUsed);
        }
    }
}
