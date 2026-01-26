// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.A.PackageGraph.h"
#include "Microsoft.Windows.ApplicationModel.PackageGraph.g.cpp"

#include "package_runtime.h"

#include "PackageTelemetry.h"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    static_assert(static_cast<std::int32_t>(GetFilePathOptions::None) == static_cast<std::int32_t>(GetPackageFilePathOptions_None), "GetFilePathOptions::None != FindPackageFileOptions_None");
    static_assert(static_cast<std::int32_t>(GetFilePathOptions::SearchInstallPath) == static_cast<std::int32_t>(GetPackageFilePathOptions_SearchInstallPath), "GetFilePathOptions::SearchInstallPath != GetPackageFilePathOptions_SearchInstallPath");
    static_assert(static_cast<std::int32_t>(GetFilePathOptions::SearchMutablePath) == static_cast<std::int32_t>(GetPackageFilePathOptions_SearchMutablePath), "GetFilePathOptions::SearchMutablePath != GetPackageFilePathOptions_SearchMutablePath");
    static_assert(static_cast<std::int32_t>(GetFilePathOptions::SearchMachineExternalPath) == static_cast<std::int32_t>(GetPackageFilePathOptions_SearchMachineExternalPath), "GetFilePathOptions::SearchMachineExternalPath != GetPackageFilePathOptions_SearchMachineExternalPath");
    static_assert(static_cast<std::int32_t>(GetFilePathOptions::SearchUserExternalPath) == static_cast<std::int32_t>(GetPackageFilePathOptions_SearchUserExternalPath), "GetFilePathOptions::SearchUserExternalPath != GetPackageFilePathOptions_SearchUserExternalPath");
    static_assert(static_cast<std::int32_t>(GetFilePathOptions::SearchMainPackages) == static_cast<std::int32_t>(GetPackageFilePathOptions_SearchMainPackages), "GetFilePathOptions::SearchMainPackages!= GetPackageFilePathOptions_SearchMainPackages");
    static_assert(static_cast<std::int32_t>(GetFilePathOptions::SearchFrameworkPackages) == static_cast<std::int32_t>(GetPackageFilePathOptions_SearchFrameworkPackages), "GetFilePathOptions::SearchFrameworkPackages!= GetPackageFilePathOptions_SearchFrameworkPackages");
    static_assert(static_cast<std::int32_t>(GetFilePathOptions::SearchOptionalPackages) == static_cast<std::int32_t>(GetPackageFilePathOptions_SearchOptionalPackages), "GetFilePathOptions::SearchOptionalPackages!= GetPackageFilePathOptions_SearchOptionalPackages");
    static_assert(static_cast<std::int32_t>(GetFilePathOptions::SearchResourcePackages) == static_cast<std::int32_t>(GetPackageFilePathOptions_SearchResourcePackages), "GetFilePathOptions::SearchResourcePackages!= GetPackageFilePathOptions_SearchResourcePackages");
    static_assert(static_cast<std::int32_t>(GetFilePathOptions::SearchBundlePackages) == static_cast<std::int32_t>(GetPackageFilePathOptions_SearchBundlePackages), "GetFilePathOptions::SearchBundlePackages!= GetPackageFilePathOptions_SearchBundlePackages");
    static_assert(static_cast<std::int32_t>(GetFilePathOptions::SearchHostRuntimeDependencies) == static_cast<std::int32_t>(GetPackageFilePathOptions_SearchHostRuntimeDependencies), "GetFilePathOptions::SearchHostRuntimeDependencies!= GetPackageFilePathOptions_SearchHostRuntimeDependencies");
    static_assert(static_cast<std::int32_t>(GetFilePathOptions::SearchStaticDependencies) == static_cast<std::int32_t>(GetPackageFilePathOptions_SearchStaticDependencies), "GetFilePathOptions::SearchStaticDependencies!= GetPackageFilePathOptions_SearchStaticDependencies");
    static_assert(static_cast<std::int32_t>(GetFilePathOptions::SearchDynamicDependencies) == static_cast<std::int32_t>(GetPackageFilePathOptions_SearchDynamicDependencies), "GetFilePathOptions::SearchDynamicDependencies!= GetPackageFilePathOptions_SearchDynamicDependencies");

    hstring PackageGraph::GetFilePath(hstring const& filename)
    {
        return GetFilePath(filename, GetFilePathOptions::None);
    }
    hstring PackageGraph::GetFilePath(hstring const& filename, winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions const& options)
    {
        wil::unique_process_heap_ptr<WCHAR> packageFile;
        THROW_IF_FAILED_MSG(::GetPackageFilePathInPackageGraph(filename.c_str(), static_cast<::GetPackageFilePathOptions>(options), wil::out_param(packageFile)),
                            "Options=0x%X Filename=%ls", static_cast<std::int32_t>(options), filename.c_str());
        if (!packageFile)
        {
            return winrt::hstring{};
        }
        return winrt::hstring{ packageFile.get() };
    }
}
