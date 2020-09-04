// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>

#include <PackageGraph.h>

#include <PackageGraphNode.h>

static std::mutex g_lock;
std::vector<MddCore::PackageGraphNode> g_packageGraph;

std::unique_lock<std::mutex> MddCore::AcquirePackageGraphLock()
{
    return std::unique_lock<std::mutex>(g_lock);
}

HRESULT MddCore::ResolvePackageDependency(
    PCWSTR packageDependencyId,
    wil::unique_process_heap_string& packageFullName)
{
    RETURN_IF_FAILED(MddCore::ResolvePackageDependency(packageDependencyId, MddAddPackageDependencyOptions::None, packageFullName));
    return S_OK;
}

HRESULT MddCore::ResolvePackageDependency(
    PCWSTR /*packageDependencyId*/,
    MddAddPackageDependencyOptions /*options*/,
    wil::unique_process_heap_string& /*packageFullName*/)
{
#if defined(TODO_ResolvePackageDependency)
    string[] packageFullNames = FindPackagesByPackageFamily(packageFamilyName, packageTypeFilter=Framework, ...);
    count = packageFullNames.size();
    if (count == 0)
    {
        return ERROR;
    }

    string bestFit = null;
    for (packageFullName : packageFullNames)
    {
        // Do we already have a higher version under consideration?
        if (bestFit && bestFit.Version > packageFullName.Version)
        {
            continue;
        }

        // Package version must meet the minVersion filter
        if (packageFullName.Version < minVersion)
        {
            continue;
        }

        // Package architecture must meet the architecture filter
        if (architectureFilter == PackageDependencyArchitectureFilters.None)
        {
            if (!IsPackageABetterFitPerArchitecture(bestFit, packageFullName))
            {
                continue;
            }
        }
        else
        {
            if (packageFullName.Architecture not in architectureFilter)
            {
                continue;
            }
        }

        // Package status must be OK to use a package
        auto packageManager = ActivateInstance(Windows.Management.Deployment.PackageManager);
        auto currentUser = "";
        auto package = packageManager.FindPackageForUser(currentUser, packageFullName);
        if (!package.VerifyIsOK())
        {
            continue;
        }

        // The new candidate is better than the current champion
        bestFit = packageFullName;
    }
    return bestFit;
#endif
    RETURN_HR(E_NOTIMPL);
}

HRESULT MddCore::IsPackageABetterFitPerArchitecture(
    PCWSTR bestFit,
    PCWSTR packageFullName,
    bool& isBetterFit)
{
    auto bestFitArchitecture = MddCore::Architecture::Unknown;
    RETURN_IF_FAILED(PackageArchitectureFromFullName(bestFit, bestFitArchitecture));

    auto packageFullNameArchitecture = MddCore::Architecture::Unknown;
    RETURN_IF_FAILED(PackageArchitectureFromFullName(packageFullName, packageFullNameArchitecture));

    isBetterFit = IsPackageABetterFitPerArchitecture(bestFit, bestFitArchitecture, packageFullNameArchitecture);
    return S_OK;
}

bool MddCore::IsPackageABetterFitPerArchitecture(
    PCWSTR bestFit,
    MddCore::Architecture bestFitArchitecture,
    MddCore::Architecture packageFullNameArchitecture)
{
    // Is the package a contender?
    const auto currentArchitecture = GetCurrentArchitecture();
    if (packageFullNameArchitecture != MddCore::Architecture::Neutral && packageFullNameArchitecture != currentArchitecture)
    {
        return false;
    }

    // Do we have a best-fit candidate yet?
    if (!bestFit)
    {
        // We do now :-)
        return true;
    }

    // Is the new package a better fit than the current champion?

    // Architecture-specific is always better than architecture-neutral
    if (bestFitArchitecture == MddCore::Architecture::Neutral && packageFullNameArchitecture != MddCore::Architecture::Neutral)
    {
        return false;
    }

    // We have a new winner!
    return true;
}

HRESULT MddCore::PackageArchitectureFromFullName(
    PCWSTR packageFullName,
    MddCore::Architecture& architecture)
{
    BYTE buffer[sizeof(PACKAGE_ID) + (PACKAGE_NAME_MAX_LENGTH + 1 +
                                      PACKAGE_RESOURCEID_MAX_LENGTH + 1 +
                                      PACKAGE_PUBLISHERID_MAX_LENGTH + 1) * sizeof(WCHAR)];
    UINT32 bufferLength = ARRAYSIZE(buffer);
    RETURN_IF_WIN32_ERROR(PackageIdFromFullName(packageFullName, PACKAGE_INFORMATION_BASIC, &bufferLength, buffer));
    const auto packageId = reinterpret_cast<PACKAGE_ID*>(buffer);
    architecture = static_cast<MddCore::Architecture>(packageId->processorArchitecture);
    return S_OK;
}

MddCore::Architecture MddCore::GetCurrentArchitecture()
{
#if defined(_M_ARM)
    return Architecture::Arm;
#elif defined(_M_ARM64)
    return Architecture::Arm64;
#elif defined(_M_IX86)
    return Architecture::X86;
#elif defined(_M_X64)
    return Architecture::X64;
#else
#   error "Unknown processor architecture"
#endif
}

HRESULT MddCore::AddToPackageGraph(
    PCWSTR /*packageFullName*/,
    INT32 /*rank*/,
    MddAddPackageDependencyOptions /*options*/,
    MDD_PACKAGEDEPENDENCY_CONTEXT& /*context*/)
{
#if defined(TODO_AddToPackageGraph)
    auto packageInfoReference = OpenPackageInfoByFullName(packageFullName);
    auto packageGraphNode = PackageGraphNode(packageInfoReference);

    // Find the insertion point where to add the new package graph node to the package graph
    int index = 0;
    for (; index < g_packageGraph.size(); ++index)
    {
        auto& node = g_packageGraph[index];
        if (node.rank() < rank)
        {
            // Too soon. Keep looking
            continue;
        }
        else if (rank < node.rank())
        {
            // Gotcha!
            break;
        }

        if (node.rank() == rank)
        {
            // Match! Insert before or after items of the same rank?
            if (options.PrependIfRankCollision)
            {
                // Gotcha!
                break;
            }
            else
            {
                // Append to items of this rank
                for (int nextIndex=index+1; nextIndex < g_packageGraph.size(); ++nextIndex)
                {
                    auto& nextNode = g_packageGraph[nextIndex];
                    if (nextNode.rank() > rank)
                    {
                        // Gotcha!
                        break;
                    }
                }
            }
        }
    }

    // Add the new node to the package graph
    if (index <> g_packageGraph.size())
    {
        g_packageGraph.insert(index, packageGraphNode);
    }
    else
    {
        g_packageGraph.append(packageGraphNode);
    }

    // The DLL Search Order must be updated when we update the package graph
    AddToDllSearchOrder(node);
#elif defined(TODO_AddToPackageGraph_MoreConcise)
    auto packageInfoReference = OpenPackageInfoByFullName(packageFullName);
    auto node = PackageGraphNode(packageInfoReference);

    auto by_rank = [](auto&& left, auto&& right) { return left.rank < right.rank; });
    auto where = options.PrependIfRankCollision ?
        std::lower_bound(g_packageGraph.begin(), g_packageGraph.end(), node, by_rank) :
        std::upper_bound(g_packageGraph.begin(), g_packageGraph.end(), node, by_rank);
    g_packageGraph.insert(where, node);
#endif
    RETURN_HR(E_NOTIMPL);
}

#if defined(TODO_AddToDllSearchOrderAndFriends)
void AddToDllSearchOrder(PackageGraphNode package)
{
    // Update the PATH environment variable
    UpdatePath();

    // Update the AddDllDirectory list
    auto cookie = AddDllDirectory(package.path());
    package.addDllDirectoryCookie(cookie);
}

void RemoveFromDllSearchOrder(PackageGraphNode package)
{
    // Update the PATH environment variable
    UpdatePath();

    // Update the AddDllDirectory list
    RemoveDllDirectory(package.addDllDirectoryCookie());
}

static string g_pathListLastAddedToPath;

void UpdatePath()
{
    // Build the package graph path list (semi-colon delimited)
    string pathList;
    for (PackageGraphNode node : g_packageGraph)
    {
        const auto flags = PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_OPTIONAL_IN_RELATED_SET;
        UINT32 count = 0;
        auto packageInfoReference = node.get();
        if (packageInfoReference)
        {
            PACKAGE_INFO[] packageInfos = GetPackageInfo(packageInfoReference, flags, ...);
        }
        else
        {
            PACKAGE_INFO[] packageInfos = TrueGetCurrentPackageInfo(packageInfoReference, flags, ...);
        }
        AppendPathsToList(pathList, packageInfos);
    }

    // Add the path list to the PATH enironment variable
    // If not present in PATH then add the path list to the front of PATH
    // If already present then replace it with the updated path list

    // package graph environment variable's at the fron ot the PATH environment variable
    string path = GetEnvironmentVariable("PATH");
    if (g_pathListLastAddedToPath.length() == 0)
    {
        // First time we're changing PATH. Prepend the path list to PATH
        path = pathList + ";" + path;
    }
    else
    {
        // Find the previous path list in PATH (if present)
        ...find g_pathg_pastListLastAddedToPath in path...
        if (found)
            ...path.replace(g_pastListLastAddedToPath, pathList)...
        else
            path = pathlist + ";" + path;
    }
    SetEnvironmentVariable("PATH", path);

    // Remember the path list we added to PATH for future updates
    g_pathListLastAddedToPath = pathList;
}

void AppendPathsToList(string& pathList, PACKAGE_INFO[] packageInfos)
{
    for (packageInfo : packageInfos)
    {
        if (pathList.size() > 0)
        {
            path += ";";
        }
        path += packageInfo.path;
    }
}
#endif

HRESULT MddCore::RemoveFromPackageGraph(
    MDD_PACKAGEDEPENDENCY_CONTEXT /*context*/)
{
#if defined(TODO_RemoveFromPackageGraph)
    std::unique_lock<std::mutex> lock(g_lock);

    for (int index=0; index < g_packageGraph.size(); ++index)
    {
        auto& node = g_packageGraph[index];
        if (node.context() == context)
        {
            // The DLL Search Order must be updated when we update the package graph
            RemoveFromDllSearchOrder(node);

            g_packageGraph.erase(index);

            return S_OK;
        }
    }
    return HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
#endif
    RETURN_HR(E_NOTIMPL);
}
