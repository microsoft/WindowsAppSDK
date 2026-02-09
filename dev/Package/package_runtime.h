// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(PACKAGE_RUNTIME_H)
#define PACKAGE_RUNTIME_H

/// Options for GetPackageFilePath*() functions
typedef enum GetPackageFilePathOptions
{
    /// Default behavior
    GetPackageFilePathOptions_None = 0,

    /// Include the package's Install path in the file search order
    /// @note If GetPackageFilePathOptions_SearchInstallPath, GetPackageFilePathOptions_SearchMutablePath,
    ///        GetPackageFilePathOptions_SearchMachineExternalPath and GetPackageFilePathOptions_SearchUserExternalPath
    ///        are omitted then all locations are searched (i.e. specify all or none yields the same result).
    GetPackageFilePathOptions_SearchInstallPath = 0x0001,

    /// Include the package's Mutable path (if it has one) in the file search order
    /// @note If GetPackageFilePathOptions_SearchInstallPath, GetPackageFilePathOptions_SearchMutablePath,
    ///        GetPackageFilePathOptions_SearchMachineExternalPath and GetPackageFilePathOptions_SearchUserExternalPath
    ///        are omitted then all locations are searched (i.e. specify all or none yields the same result).
    GetPackageFilePathOptions_SearchMutablePath = 0x0002,

    /// Include the package's Machine External path (if it has one) in the file search order
    /// @note If GetPackageFilePathOptions_SearchInstallPath, GetPackageFilePathOptions_SearchMutablePath,
    ///        GetPackageFilePathOptions_SearchMachineExternalPath and GetPackageFilePathOptions_SearchUserExternalPath
    ///        are omitted then all locations are searched (i.e. specify all or none yields the same result).
    GetPackageFilePathOptions_SearchMachineExternalPath = 0x0004,

    /// Include the package's User External path (if it has one) in the file search order
    /// @note If GetPackageFilePathOptions_SearchInstallPath, GetPackageFilePathOptions_SearchMutablePath,
    ///        GetPackageFilePathOptions_SearchMachineExternalPath and GetPackageFilePathOptions_SearchUserExternalPath
    ///        are omitted then all locations are searched (i.e. specify all or none yields the same result).
    GetPackageFilePathOptions_SearchUserExternalPath = 0x0008,

    /// Include Main packages in the file search order
    /// @note If GetPackageFilePathOptions_SearchMainPackages, GetPackageFilePathOptions_SearchFrameworkPackages,
    ///       GetPackageFilePathOptions_SearchOptionalPackages, GetPackageFilePathOptions_SearchResourcePackages,
    ///       GetPackageFilePathOptions_SearchBundlePackages and GetPackageFilePathOptions_SearchHostRuntimeDependencies
    ///       are omitted then all package types are searched (i.e. specify all or none yields the same result).
    GetPackageFilePathOptions_SearchMainPackages = 0x0010,

    /// Include Framework packages in the file search order
    /// @note If GetPackageFilePathOptions_SearchMainPackages, GetPackageFilePathOptions_SearchFrameworkPackages,
    ///       GetPackageFilePathOptions_SearchOptionalPackages, GetPackageFilePathOptions_SearchResourcePackages,
    ///       GetPackageFilePathOptions_SearchBundlePackages and GetPackageFilePathOptions_SearchHostRuntimeDependencies
    ///       are omitted then all package types are searched (i.e. specify all or none yields the same result).
    GetPackageFilePathOptions_SearchFrameworkPackages = 0x0020,

    /// Include Optional packages in the file search order
    /// @note If GetPackageFilePathOptions_SearchMainPackages, GetPackageFilePathOptions_SearchFrameworkPackages,
    ///       GetPackageFilePathOptions_SearchOptionalPackages, GetPackageFilePathOptions_SearchResourcePackages,
    ///       GetPackageFilePathOptions_SearchBundlePackages and GetPackageFilePathOptions_SearchHostRuntimeDependencies
    ///       are omitted then all package types are searched (i.e. specify all or none yields the same result).
    GetPackageFilePathOptions_SearchOptionalPackages = 0x0040,

    /// Include Resource packages in the file search order
    /// @note If GetPackageFilePathOptions_SearchMainPackages, GetPackageFilePathOptions_SearchFrameworkPackages,
    ///       GetPackageFilePathOptions_SearchOptionalPackages, GetPackageFilePathOptions_SearchResourcePackages,
    ///       GetPackageFilePathOptions_SearchBundlePackages and GetPackageFilePathOptions_SearchHostRuntimeDependencies
    ///       are omitted then all package types are searched (i.e. specify all or none yields the same result).
    GetPackageFilePathOptions_SearchResourcePackages = 0x0080,

    /// Include Bundle packages in the file search order
    /// @note If GetPackageFilePathOptions_SearchMainPackages, GetPackageFilePathOptions_SearchFrameworkPackages,
    ///       GetPackageFilePathOptions_SearchOptionalPackages, GetPackageFilePathOptions_SearchResourcePackages,
    ///       GetPackageFilePathOptions_SearchBundlePackages and GetPackageFilePathOptions_SearchHostRuntimeDependencies
    ///       are omitted then all package types are searched (i.e. specify all or none yields the same result).
    GetPackageFilePathOptions_SearchBundlePackages = 0x0100,

    /// Include HostRuntime dependencies in the file search order
    /// @note If GetPackageFilePathOptions_SearchMainPackages, GetPackageFilePathOptions_SearchFrameworkPackages,
    ///       GetPackageFilePathOptions_SearchOptionalPackages, GetPackageFilePathOptions_SearchResourcePackages,
    ///       GetPackageFilePathOptions_SearchBundlePackages and GetPackageFilePathOptions_SearchHostRuntimeDependencies
    ///       are omitted then all package types are searched (i.e. specify all or none yields the same result).
    GetPackageFilePathOptions_SearchHostRuntimeDependencies = 0x0200,
} GetPackageFilePathOptions;
DEFINE_ENUM_FLAG_OPERATORS(GetPackageFilePathOptions)

/// Return the absolute path to the file in the package.
/// @param packageFullName the package, or NULL or "" to use the current process' package identity.
/// @param filename file to locate.
/// @param options options for the search.
/// @param packageFile absolute path to the packaged file, or NULL if not found. Allocated via HeapAlloc; use HeapFree to deallocate
/// @note The package path search order is External(User or Machine) -> Mutable -> Install.
/// @note If a package has a UserExternal location then MachineExternal location is not checked (even if the package has one).
/// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getpackagepathbyfullname2
/// @see GetPackageFilePathInPackageGraph()
/// @see GetPackageFilePathOptions
STDAPI GetPackageFilePath(
    PCWSTR packageFullName,
    _In_ PCWSTR filename,
    _In_ GetPackageFilePathOptions options,
    _Outptr_result_maybenull_ PWSTR* packageFile) noexcept;

/// Return the absolute path to the file in the caller's package graph.
/// @param filename file to locate.
/// @param options options for the search.
/// @param packageFile absolute path to the packaged file, or NULL if not found. Allocated via HeapAlloc; use HeapFree to deallocate
/// @note The search order is External(User or Machine) -> Mutable -> Install for each package in the package graph.
/// @note If a package has a UserExternal location then MachineExternal location is not checked (even if the package has one).
/// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getpackagepathbyfullname2
/// @see GetPackageFilePath()
/// @see GetPackageFilePathOptions
STDAPI GetPackageFilePathInPackageGraph(
    _In_ PCWSTR filename,
    _In_ GetPackageFilePathOptions options,
    _Outptr_result_maybenull_ PWSTR* packageFile) noexcept;

#endif // PACKAGE_RUNTIME_H
