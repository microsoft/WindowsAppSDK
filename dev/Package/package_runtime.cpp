// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "package_runtime.h"

namespace appmodel
{
inline GetPackageFilePathOptions package_properties_to_options(
    std::uint32_t packageInfoFlags)
{
    const auto hostRuntimeMatch{ WI_IsFlagSet(packageInfoFlags, PACKAGE_PROPERTY_HOSTRUNTIME) ?
                                   GetPackageFilePathOptions_SearchHostRuntimeDependencies :
                                   GetPackageFilePathOptions_None };
    if (WI_IsFlagSet(packageInfoFlags, PACKAGE_PROPERTY_FRAMEWORK))
    {
        return GetPackageFilePathOptions_SearchFrameworkPackages | hostRuntimeMatch;
    }
    else if (WI_IsFlagSet(packageInfoFlags, PACKAGE_PROPERTY_OPTIONAL))
    {
        return GetPackageFilePathOptions_SearchOptionalPackages | hostRuntimeMatch;
    }
    else if (WI_IsFlagSet(packageInfoFlags, PACKAGE_PROPERTY_RESOURCE))
    {
        return GetPackageFilePathOptions_SearchResourcePackages | hostRuntimeMatch;
    }
    else if (WI_IsFlagSet(packageInfoFlags, PACKAGE_PROPERTY_BUNDLE))
    {
        return GetPackageFilePathOptions_SearchBundlePackages | hostRuntimeMatch;
    }
    else
    {
        // PACKAGE_INFO.flags has no PACKAGE_PROPERTY_MAIN so we can only determine PackageType=Main
        // by first verifying it's not any other type of package (Bundle|Framework|Optional|Resource).
        // When all else is ruled out what we're left with must be a Main package
        return GetPackageFilePathOptions_SearchMainPackages | hostRuntimeMatch;
    }
}

inline GetPackageFilePathOptions get_package_properties(
    PCWSTR packageFullName,
    PACKAGE_INFO_REFERENCE packageInfoReference)
{
    // Fetch the package's properties
    constexpr auto flags{ PACKAGE_FILTER_BUNDLE | PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_RESOURCE | PACKAGE_FILTER_OPTIONAL | PACKAGE_FILTER_HOSTRUNTIME | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC | PACKAGE_INFORMATION_BASIC };
    std::uint32_t bufferLength{};
    std::uint32_t count{};
    auto rc{ ::GetPackageInfo(packageInfoReference, flags, &bufferLength, nullptr, &count) };
    if (rc != ERROR_INSUFFICIENT_BUFFER)
    {
        if (rc == ERROR_SUCCESS)
        {
            if (count == 0)
            {
                // Package not found
                return GetPackageFilePathOptions_None;
            }
            THROW_HR(E_UNEXPECTED); // This should never occur
        }
        THROW_WIN32_MSG(rc, "GetPackageInfo(...query...) %ls", packageFullName);
    }
    std::unique_ptr<BYTE[]> buffer{ std::make_unique<BYTE[]>(bufferLength) };
    THROW_IF_WIN32_ERROR_MSG(::GetPackageInfo(packageInfoReference, flags, &bufferLength, buffer.get(), &count),
                             "GetPackageInfo: %ls", packageFullName);
    THROW_HR_IF(E_UNEXPECTED, count == 0);  // This should never occur
    const auto& packageInfo{ *reinterpret_cast<PACKAGE_INFO*>(buffer.get()) };

    // Convert the package properties to options
    return package_properties_to_options(packageInfo.flags);
}

inline bool is_match_for_package_properties(
    PCWSTR packageFullName,
    _In_ GetPackageFilePathOptions options,
    PACKAGE_INFO_REFERENCE packageInfoReference)
{
    // Detect PackageType|HostRuntimeDependency
    //
    // If options = All or None specified then all packages are a match thus no need to fetch the package's properties
    constexpr auto maskMatchPackageType{ GetPackageFilePathOptions_SearchMainPackages |
                                         GetPackageFilePathOptions_SearchFrameworkPackages |
                                         GetPackageFilePathOptions_SearchOptionalPackages |
                                         GetPackageFilePathOptions_SearchResourcePackages |
                                         GetPackageFilePathOptions_SearchBundlePackages |
                                         GetPackageFilePathOptions_SearchHostRuntimeDependencies };
    const auto optionsToMatch{ options & maskMatchPackageType };
    if ((optionsToMatch == GetPackageFilePathOptions_None) || (optionsToMatch == maskMatchPackageType))
    {
        return true;
    }

    // Fetch the package's properties
    const auto packageProperties{ get_package_properties(packageFullName, packageInfoReference) };

    // Does this package meet the criteria?
    return WI_IsAnyFlagSet(packageProperties, optionsToMatch);
}

inline bool is_match_for_package_properties(
    _In_ GetPackageFilePathOptions options,
    std::uint32_t packageInfoFlags)
{
    // Detect PackageType|HostRuntimeDependency
    //
    // If options = All or None specified then all packages are a match thus no need to fetch the package's properties
    constexpr auto maskMatchPackageType{ GetPackageFilePathOptions_SearchMainPackages |
                                         GetPackageFilePathOptions_SearchFrameworkPackages |
                                         GetPackageFilePathOptions_SearchOptionalPackages |
                                         GetPackageFilePathOptions_SearchResourcePackages |
                                         GetPackageFilePathOptions_SearchBundlePackages |
                                         GetPackageFilePathOptions_SearchHostRuntimeDependencies };
    constexpr auto maskMatchAll{ maskMatchPackageType };
    const auto optionsToMatch{ options & maskMatchAll };
    if ((optionsToMatch == GetPackageFilePathOptions_None) || (optionsToMatch == maskMatchAll))
    {
        return true;
    }

    // Does this package meet the criteria?
    return WI_IsAnyFlagSet(packageInfoFlags, optionsToMatch);
}

inline std::filesystem::path get_package_file_for_location(
    PCWSTR packageFullName,
    _In_ PCWSTR filename,
    _In_ GetPackageFilePathOptions options,
    PackagePathType packagePathType)
{
    std::filesystem::path absoluteFilename;

    auto packagePath{ ::AppModel::Package::GetPath<std::wstring>(packageFullName, packagePathType) };
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
    // Search External location
    std::filesystem::path path;
    if (WI_IsFlagSet(options, GetPackageFilePathOptions_SearchUserExternalPath))
    {
        if (WI_IsFlagSet(options, GetPackageFilePathOptions_SearchMachineExternalPath))
        {
            // EffectiveExternal == UserExternal if package/user has one else MachineExternal
            path = get_package_file_for_location(packageFullName, filename, options, PackagePathType_EffectiveExternal);
        }
        else
        {
            path = get_package_file_for_location(packageFullName, filename, options, PackagePathType_UserExternal);
        }
    }
    else if (WI_IsFlagSet(options, GetPackageFilePathOptions_SearchMachineExternalPath))
    {
        path = get_package_file_for_location(packageFullName, filename, options, PackagePathType_MachineExternal);
    }
    if (path.empty())
    {
        // Search Mutable location
        if (WI_IsFlagSet(options, GetPackageFilePathOptions_SearchMutablePath))
        {
            path = get_package_file_for_location(packageFullName, filename, options, PackagePathType_Mutable);
        }
        if (path.empty())
        {
            // Search Install location
            if (WI_IsFlagSet(options, GetPackageFilePathOptions_SearchInstallPath))
            {
                path = get_package_file_for_location(packageFullName, filename, options, PackagePathType_Install);
            }
        }
    }
    return path;
}

inline std::filesystem::path get_package_file(
    PCWSTR packageFullName,
    _In_ PCWSTR filename,
    _In_ GetPackageFilePathOptions effectiveOptions,
    PACKAGE_INFO_REFERENCE packageInfoReference)
{
    // Does the package's properties match our search criteria?
    if (!is_match_for_package_properties(packageFullName, effectiveOptions, packageInfoReference))
    {
        return std::filesystem::path{};
    }

    // Search the package's locations for the file
    return get_package_file(packageFullName, filename, effectiveOptions);
}

inline GetPackageFilePathOptions ToEffectiveOptions(
    GetPackageFilePathOptions options)
{
    // If options == None then use default behavior (search everything)
    if (options == GetPackageFilePathOptions_None)
    {
        return GetPackageFilePathOptions_SearchInstallPath |
               GetPackageFilePathOptions_SearchMutablePath |
               GetPackageFilePathOptions_SearchMachineExternalPath |
               GetPackageFilePathOptions_SearchUserExternalPath |
               GetPackageFilePathOptions_SearchMainPackages |
               GetPackageFilePathOptions_SearchFrameworkPackages |
               GetPackageFilePathOptions_SearchOptionalPackages |
               GetPackageFilePathOptions_SearchResourcePackages |
               GetPackageFilePathOptions_SearchBundlePackages |
               GetPackageFilePathOptions_SearchHostRuntimeDependencies;
    }

    // If Search*Dependencies are all clear then search them all
    // where * = Main | Framework | Optional | Resource | Bundle | HostRuntime
    //
    // NOTE: HostRuntime isn't a PackageType but little white lie here for our filtering.
    //       For example, a Main package shouldn't be searched given options=SearchFrameworkDependnecies
    //       but it should be search if the Main package declares a <HostRuntimeDependency> and
    //       options=SearchFrameworkDependencies | SearchHostRuntimeDependencies.
    constexpr auto maskPackageTypes{ GetPackageFilePathOptions_SearchMainPackages |
                                     GetPackageFilePathOptions_SearchFrameworkPackages |
                                     GetPackageFilePathOptions_SearchOptionalPackages |
                                     GetPackageFilePathOptions_SearchResourcePackages |
                                     GetPackageFilePathOptions_SearchBundlePackages |
                                     GetPackageFilePathOptions_SearchHostRuntimeDependencies };
    if (WI_AreAllFlagsClear(options, maskPackageTypes))
    {
        return options | maskPackageTypes;
    }
    return options;
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
        std::uint32_t packageFullNameBufferLength{ ARRAYSIZE(packageFullNameBuffer) };
        RETURN_IF_WIN32_ERROR(::GetCurrentPackageFullName(&packageFullNameBufferLength, packageFullNameBuffer));
        packageFullName = packageFullNameBuffer;
    }

    // Let's do it...
    const auto effectiveOptions{ appmodel::ToEffectiveOptions(options) };
    wil::unique_package_info_reference packageInfoReference;
    auto rc{ ::OpenPackageInfoByFullName(packageFullName, 0, wil::out_param(packageInfoReference)) };
    if (rc != ERROR_SUCCESS)
    {
        THROW_WIN32_MSG(rc, "OpenPackageInfoByFullName(%ls,...)", packageFullName);
    }
    auto path{ appmodel::get_package_file(packageFullName, filename, effectiveOptions, packageInfoReference.get()) };
    if (!path.empty())
    {
        auto absoluteFilename{ wil::make_process_heap_string(path.c_str()) };
        *packageFile = absoluteFilename.release();
    }
    return S_OK;
}
CATCH_RETURN();

STDAPI GetPackageFilePathInPackageGraph(
    _In_ PCWSTR filename,
    _In_ GetPackageFilePathOptions options,
    _Outptr_result_maybenull_ PWSTR* packageFile) noexcept try
{
    *packageFile = nullptr;

    RETURN_HR_IF(E_INVALIDARG, ::Microsoft::Foundation::String::IsNullOrEmpty(filename));

    // Compute the effective options
    const auto effectiveOptions{ appmodel::ToEffectiveOptions(options) };

    // Search the package graph
    //
    // Ideally we'd pass our filtering needs down to package graph query API (e.g. GetCurrentPackageGraph)
    // but it doesn't quite give us the semantics we need, so we'll do it the hard way
    constexpr std::uint32_t flags{ PACKAGE_FILTER_BUNDLE | PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_RESOURCE | PACKAGE_FILTER_OPTIONAL | PACKAGE_FILTER_HOSTRUNTIME | PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC | PACKAGE_INFORMATION_BASIC };
    std::uint32_t packageGraphCount{};
    const PACKAGE_INFO* packageInfos{};
    wil::unique_cotaskmem_ptr<BYTE[]> buffer;
    RETURN_IF_FAILED(::AppModel::PackageGraph::GetCurrentPackageGraph(flags, packageGraphCount, packageInfos, buffer));
    for (std::uint32_t index=0; index < packageGraphCount; ++index)
    {
        const auto& packageInfo{ packageInfos[index] };

        // Does the package's properties match our search criteria?
        const auto packageInfoFlags{ appmodel::package_properties_to_options(packageInfo.flags) };
        if (!appmodel::is_match_for_package_properties(effectiveOptions, packageInfoFlags))
        {
            continue;
        }

        // This package is included in our search. Check for the file
        const auto packageFullName{ packageInfo.packageFullName };
        auto path{ appmodel::get_package_file(packageFullName, filename, effectiveOptions) };
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
