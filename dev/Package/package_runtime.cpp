// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "package_runtime.h"

namespace appmodel
{
inline std::wstring get_package_path(
    PCWSTR packageFullName,
    PackagePathType packagePathType)
{
    // Paths can be long but typically short(ish). We can use a quick fixed buffer
    // as an optimization and fallback to dynamic allocation if need be
    WCHAR path[MAX_PATH]{};
    uint32_t pathLength{ ARRAYSIZE(path) };
    const auto rc{ ::GetPackagePathByFullName2(packageFullName, packagePathType, &pathLength, path) };
    if (rc == ERROR_SUCCESS)
    {
        return path;
    }
    else if (rc == ERROR_NOT_FOUND)
    {
        return std::wstring{};
    }
    else if (rc != ERROR_INSUFFICIENT_BUFFER)
    {
        THROW_WIN32(rc);
    }

    // It's bigger than a breadbox. Allocate memory
    std::unique_ptr<WCHAR[]> pathBuffer{ std::make_unique<WCHAR[]>(pathLength) };
    THROW_IF_WIN32_ERROR_MSG(::GetPackagePathByFullName2(packageFullName, packagePathType, &pathLength, pathBuffer.get()),
                             "PackageFullName=%ls PackagePathType=%d", packageFullName ? packageFullName : L"<null>", static_cast<int>(packagePathType));
    return std::wstring{ pathBuffer.get() };
}

inline std::filesystem::path get_package_file(
    PCWSTR packageFullName,
    _In_ PCWSTR filename,
    _In_ GetPackageFilePathOptions options,
    PackagePathType packagePathType)
{
    std::filesystem::path absoluteFilename;

    auto packagePath{ appmodel::get_package_path(packageFullName, packagePathType) };
    if (!packagePath.empty())
    {
        absoluteFilename = packagePath;
        absoluteFilename /= filename;
        if (std::filesystem::exists(absoluteFilename))
        {
            return absoluteFilename;
        }
    }
    return std::filesystem::path{};
}

inline std::filesystem::path get_package_file(
    PCWSTR packageFullName,
    _In_ PCWSTR filename,
    _In_ GetPackageFilePathOptions options)
{
    std::filesystem::path path;

    // Search External location
    if (WI_IsFlagSet(options, GetPackageFilePathOptions_SearchUserExternalPath))
    {
        if (WI_IsFlagSet(options, GetPackageFilePathOptions_SearchMachineExternalPath))
        {
            // EffectiveExternal == UserExternal if package/user has one else MachineExternal
            path = get_package_file(packageFullName, filename, options, PackagePathType_EffectiveExternal);
        }
        else
        {
            path = get_package_file(packageFullName, filename, options, PackagePathType_UserExternal);
        }
    }
    else if (WI_IsFlagSet(options, GetPackageFilePathOptions_SearchMachineExternalPath))
    {
        path = get_package_file(packageFullName, filename, options, PackagePathType_MachineExternal);
    }
    if (path.empty())
    {
        // Search Mutable location
        if (WI_IsFlagSet(options, GetPackageFilePathOptions_SearchMutablePath))
        {
            path = get_package_file(packageFullName, filename, options, PackagePathType_Mutable);
        }
        if (path.empty())
        {
            // Search Install location
            if (WI_IsFlagSet(options, GetPackageFilePathOptions_SearchInstallPath))
            {
                path = get_package_file(packageFullName, filename, options, PackagePathType_Install);
            }
        }
    }

    // Not found
    return std::filesystem::path{};
}
}

STDAPI GetPackageFilePath(
    PCWSTR packageFullName,
    _In_ PCWSTR filename,
    _In_ GetPackageFilePathOptions options,
    _Outptr_result_maybenull_ PWSTR* packageFile) noexcept try
{
    *packageFile = nullptr;

    RETURN_HR_IF(E_INVALIDARG, ::Microsoft::Foundation::String::IsNullOrEmpty(filename));

    // If packageFullName = NULL or "" use the caller's package identity
    WCHAR packageFullNameBuffer[PACKAGE_FULL_NAME_MAX_LENGTH + 1]{};
    if (::Microsoft::Foundation::String::IsNullOrEmpty(packageFullName))
    {
        uint32_t packageFullNameBufferLength{ ARRAYSIZE(packageFullNameBuffer) };
        RETURN_IF_WIN32_ERROR(::GetCurrentPackageFullName(&packageFullNameBufferLength, packageFullNameBuffer));
        packageFullName = packageFullNameBuffer;
    }

    auto path{ appmodel::get_package_file(packageFullName, filename, options) };
    if (!path.empty())
    {
        auto absoluteFilename{ wil::make_process_heap_string(path.c_str()) };
        *packageFile = absoluteFilename.release();
    }
    return S_OK;
}
CATCH_RETURN();

/// Is a PACKAGE_INFO entry a Main package?
/// @note There's no direct propery to check indicating a Main package.
///       That's only detectable by the absence of any other type of package.
inline constexpr bool IsMainPackage(const UINT32 packageInfoFlags)
{
    return WI_AreAllFlagsClear(packageInfoFlags, PACKAGE_PROPERTY_BUNDLE | PACKAGE_PROPERTY_FRAMEWORK | PACKAGE_PROPERTY_OPTIONAL | PACKAGE_PROPERTY_RESOURCE);
}

STDAPI GetPackageFilePathInPackageGraph(
    _In_ PCWSTR filename,
    _In_ GetPackageFilePathOptions options,
    _Outptr_result_maybenull_ PWSTR* packageFile) noexcept try
{
    *packageFile = nullptr;

    RETURN_HR_IF(E_INVALIDARG, ::Microsoft::Foundation::String::IsNullOrEmpty(filename));

    // Ideally we'd pass our filtering needs down to package graph query API (e.g. GetCurrentPackageGraph)
    // but it doesn't quite give us the semantics we need, so we'll do it the hard way.
    //
    // We can (partially) optimize filtering checks for PackageType=Framework|Resource|Optional and HostRuntime|Static|Dynamic
    // by a simple bitmask check. We can only determine if PackageType=Main by the absence of other properties.
    const UINT32 flagsMask{ (WI_IsFlagSet(options, GetPackageFilePathOptions_SearchFrameworkPackages) ? PACKAGE_PROPERTY_FRAMEWORK : 0u) |
                            (WI_IsFlagSet(options, GetPackageFilePathOptions_SearchResourcePackages) ? PACKAGE_PROPERTY_RESOURCE : 0u) |
                            (WI_IsFlagSet(options, GetPackageFilePathOptions_SearchOptionalPackages) ? PACKAGE_PROPERTY_OPTIONAL : 0u) |
                            (WI_IsFlagSet(options, GetPackageFilePathOptions_SearchHostRuntimeDependencies) ? PACKAGE_PROPERTY_HOSTRUNTIME : 0u) |
                            (WI_IsFlagSet(options, GetPackageFilePathOptions_SearchStaticDependencies) ? PACKAGE_PROPERTY_STATIC : 0u) |
                            (WI_IsFlagSet(options, GetPackageFilePathOptions_SearchDynamicDependencies) ? PACKAGE_PROPERTY_DYNAMIC : 0u) };

    // Search the package graph
    UINT32 flags{ PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_RESOURCE | PACKAGE_FILTER_OPTIONAL | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC | PACKAGE_INFORMATION_BASIC };
    uint32_t packageGraphCount{};
    const PACKAGE_INFO* packageInfo{};
    wil::unique_cotaskmem_ptr<BYTE[]> buffer;
    RETURN_IF_FAILED(::AppModel::PackageGraph::GetCurrentPackageGraph(flags, packageGraphCount, packageInfo, buffer));
    for (uint32_t index=0; index < packageGraphCount; ++index)
    {
        const auto& pi{ packageInfo[index] };

        // Default behavior is search everything. Do we need to filter to a subset?
        if (options != GetPackageFilePathOptions_None)
        {
            // Does this package meet any of the simple filtering criteria: Framework|Resource|Optional|HostRuntime|Static|Dynamic
            if (WI_AreAllFlagsClear(pi.flags, flagsMask))
            {
                // Nope! Complex filtering time. Is this a Main package?
                if (IsMainPackage(pi.flags))
                {
                    // Are Main packages included in our search?
                    if (WI_IsFlagClear(options, GetPackageFilePathOptions::GetPackageFilePathOptions_SearchMainPackages))
                    {
                        // It's a Main package but we're not interested in Main packages. Skip it
                        continue;
                    }
                }
                else
                {
                    // It's not a Main package, and it doesn't meet any other filter criteria. Skip it
                    continue;
                }
            }
        }

        // This package is included in our search. Check for the file
        const auto packageFullName{ pi.packageFullName };
        auto path{ appmodel::get_package_file(packageFullName, filename, options) };
        if (!path.empty())
        {
            auto absoluteFilename{ wil::make_process_heap_string(path.c_str()) };
            *packageFile = absoluteFilename.release();
            break;
        }
    }
    return S_OK;
}
CATCH_RETURN();
