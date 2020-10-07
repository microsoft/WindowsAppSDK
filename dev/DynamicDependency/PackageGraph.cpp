// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "PackageGraph.h"

#include "PackageGraphNode.h"
#include "PackageDependencyManager.h"
#include "PackageId.h"

#include <wil/win32_helpers.h>

HRESULT MddCore::PackageGraph::Add(
    _In_ PCWSTR packageDependencyId,
    INT32 rank,
    MddAddPackageDependencyOptions options,
    MDD_PACKAGEDEPENDENCY_CONTEXT& packageDependencyContext,
    _Outptr_opt_result_maybenull_ PWSTR* packageFullName)
{
    wil::unique_process_heap_string fullName;
    RETURN_IF_FAILED(ResolvePackageDependency(packageDependencyId, options, fullName));
    MDD_PACKAGEDEPENDENCY_CONTEXT context{};
    RETURN_IF_FAILED(Add(fullName.get(), rank, options, context));

    packageDependencyContext = std::move(context);
    if (packageFullName)
    {
        *packageFullName = fullName.release();
    }
    return S_OK;
}

HRESULT MddCore::PackageGraph::Add(
    PCWSTR packageFullName,
    INT32 rank,
    MddAddPackageDependencyOptions options,
    MDD_PACKAGEDEPENDENCY_CONTEXT& context)
{
    // Load the package's information
    PackageGraphNode packageGraphNode(packageFullName, rank);

    // Find the insertion point where to add the new package graph node to the package graph
    int index{};
    for (; index < m_packageGraphNodes.size(); ++index)
    {
        auto& node = m_packageGraphNodes[index];
        if (node.Rank() < rank)
        {
            // Too soon. Keep looking
            continue;
        }
        else if (rank < node.Rank())
        {
            // Gotcha!
            break;
        }

        if (node.Rank() == rank)
        {
            // Match! Insert before items of the same rank?
            if (WI_IsFlagSet(options, MddAddPackageDependencyOptions::PrependIfRankCollision))
            {
                // Gotcha!
                break;
            }
            else
            {
                // Append to items of this rank
                for (int nextIndex=index+1; nextIndex < m_packageGraphNodes.size(); ++nextIndex)
                {
                    auto& nextNode = m_packageGraphNodes[nextIndex];
                    if (nextNode.Rank() > rank)
                    {
                        // Gotcha!
                        break;
                    }
                }
            }
        }
    }

    // Add the new node to the package graph
    if (index < m_packageGraphNodes.size())
    {
        // We'd like to 
        m_packageGraphNodes.insert(m_packageGraphNodes.begin() + index, std::move(packageGraphNode));
    }
    else
    {
        m_packageGraphNodes.push_back(std::move(packageGraphNode));
    }
#if defined(TODO_AddToPackageGraph_MoreConcise)
    auto packageInfoReference{ OpenPackageInfoByFullName(packageFullName) };
    auto node{ PackageGraphNode(packageInfoReference) };

    auto by_rank = [](auto&& left, auto&& right) { return left.rank < right.rank; });
    auto where = options.PrependIfRankCollision ?
        std::lower_bound(m_packageGraphNodes.begin(), m_packageGraphNodes.end(), node, by_rank) :
        std::upper_bound(m_packageGraphNodes.begin(), m_packageGraphNodes.end(), node, by_rank);
    m_packageGraphNodes.insert(where, node);
#endif

    // The DLL Search Order must be updated when we update the package graph
    auto& node = m_packageGraphNodes[index];
    AddToDllSearchOrder(node);

    context = node.Context();
    return S_OK;
}

HRESULT MddCore::PackageGraph::ResolvePackageDependency(
    PCWSTR packageDependencyId,
    MddAddPackageDependencyOptions /*options*/,
    wil::unique_process_heap_string& packageFullName) noexcept try
{
    packageFullName.reset();

    // Get the package dependency
    auto foundPackageDependency{ MddCore::PackageDependencyManager::GetPackageDependency(packageDependencyId) };
    THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), !foundPackageDependency);

    // Is the package dependency already resolved?
    const auto& packageDependency = *foundPackageDependency;
    if (!packageDependency.PackageFullName().empty())
    {
        packageFullName = wil::make_process_heap_string(packageDependency.PackageFullName().c_str());
        return S_OK;
    }

    // Determine the packages in the family
    const auto foundPackageFullNames{ packageDependency.FindPackagesByFamily() };

    // Find the best fit package in the family (if any)
    MddCore::PackageId bestFit;
    winrt::Windows::Management::Deployment::PackageManager packageManager;
    for (const auto& candidatePackageFullName : foundPackageFullNames)
    {
        auto candidate{ MddCore::PackageId::FromPackageFullName(candidatePackageFullName.c_str()) };

        // Do we already have a higher version under consideration?
        if (bestFit && (bestFit.Version().Version > candidate.Version().Version))
        {
            continue;
        }

        // Package version must meet the minVersion filter
        if (candidate.Version().Version < packageDependency.MinVersion().Version)
        {
            continue;
        }

        // Package architecture must meet the architecture filter
        if (packageDependency.Architectures() == MddPackageDependencyProcessorArchitectures::None)
        {
            if (!IsPackageABetterFitPerArchitecture(bestFit, candidate))
            {
                continue;
            }
        }
        else
        {
            if (!packageDependency.IsArchitectureInArchitectures(candidate.Architecture()))
            {
                continue;
            }
        }

        // Package status must be OK to use a package
        winrt::hstring currentUser;
        auto package{ packageManager.FindPackageForUser(currentUser, candidate.PackageFullName()) };
        auto status{ package.Status() };
        if (!status.VerifyIsOK())
        {
            continue;
        }

        // The new candidate is better than the current champion
        bestFit = std::move(candidate);
    }

    // Did we fail to find a match?
    THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), bestFit.PackageFullName().empty());

    // We have a winner!
    packageFullName = std::move(wil::make_process_heap_string(bestFit.PackageFullName().c_str()));
    return S_OK;
}
CATCH_RETURN();

HRESULT MddCore::PackageGraph::Remove(
    MDD_PACKAGEDEPENDENCY_CONTEXT context)
{
    for (int index=0; index < m_packageGraphNodes.size(); ++index)
    {
        auto& node = m_packageGraphNodes[index];
        if (node.Context() == context)
        {
            // The DLL Search Order must be updated when we update the package graph
            RemoveFromDllSearchOrder(node);

            m_packageGraphNodes.erase(m_packageGraphNodes.begin() + index);

            return S_OK;
        }
    }
    RETURN_WIN32(ERROR_INVALID_HANDLE);
}

bool MddCore::PackageGraph::IsPackageABetterFitPerArchitecture(
    const PackageId& bestFit,
    const PackageId& candidate)
{
    // Is the package a contender?
    const auto currentArchitecture{ GetCurrentArchitecture() };
    if ((candidate.Architecture() != MddCore::Architecture::Neutral) && (candidate.Architecture() != currentArchitecture))
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
    if ((bestFit.Architecture() == MddCore::Architecture::Neutral) && (candidate.Architecture() != MddCore::Architecture::Neutral))
    {
        return false;
    }

    // We have a new winner!
    return true;
}

void MddCore::PackageGraph::AddToDllSearchOrder(PackageGraphNode& package)
{
    // Update the PATH environment variable
    UpdatePath();

    // Update the AddDllDirectory list
    package.AddDllDirectories();
}

void MddCore::PackageGraph::RemoveFromDllSearchOrder(PackageGraphNode& package)
{
    // Update the AddDllDirectory list
    package.RemoveDllDirectories();

    // Update the PATH environment variable
    UpdatePath();
}

void MddCore::PackageGraph::UpdatePath()
{
    // Build the package graph path list (semi-colon delimited)
    std::wstring pathList{ BuildPathList() };

    // Add the path list to the PATH enironment variable
    // If not present in PATH then add the path list to the front of PATH
    // If already present then replace it with the updated path list

    // package graph environment variable's at the fron ot the PATH environment variable
    std::wstring newPath;
    auto path{ wil::TryGetEnvironmentVariableW(L"PATH") };
    if (m_pathListLastAddedToPath.length() == 0)
    {
        // First time we're changing PATH. Prepend the path list to PATH
        newPath = pathList;
        newPath += L';';
        newPath += path.get();
    }
    else
    {
        // Find the previous path list in PATH (if present)
#if defined(TODO_UpdatePath)
        ...find g_pathg_pastListLastAddedToPath in path...
        if (found)
            ...path.replace(g_pastListLastAddedToPath, pathList)...
        else
            path = pathlist + ";" + path;
#else
        newPath = pathList;
        newPath += L';';
        newPath += path.get();
#endif
    }
    THROW_IF_WIN32_BOOL_FALSE(SetEnvironmentVariableW(L"PATH", newPath.c_str()));

    // Remember the path list we added to PATH for future updates
    m_pathListLastAddedToPath = pathList;
}

std::wstring MddCore::PackageGraph::BuildPathList()
{
    std::wstring pathlist;
    for (size_t index=0; index < m_packageGraphNodes.size(); ++index)
    {
        const auto& node = m_packageGraphNodes[index];
        if (index > 0)
        {
            pathlist += L';';
        }
        pathlist += node.PathList();
    }
    return pathlist;
}
