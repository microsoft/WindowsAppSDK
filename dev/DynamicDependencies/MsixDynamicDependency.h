// Copyright (C) Microsoft. All rights reserved.

#if !defined(MSIXDYNAMICDEPENDENCY_H)
#define MSIXDYNAMICDEPENDENCY_H

enum class MddPinPackageDependencyFlags : uint32_t
{
    None = 0,

    /// Disable dependency resolution when pinning a package dependency.
    DoNotVerifyDependencyResolution = 0x00000001,

    /// Define the package dependency for the system, accessible to all users
    /// (default is the package dependency is defined for a specific user).
    /// This option requires the caller has adminitrative privileges.
    ScopeIsSystem = 0x00000002,
};
DEFINE_ENUM_FLAG_OPERATORS(MddPinPackageDependencyFlags);

enum class MddPinPackageDependencyLifetimeKind
{
    /// The current process is the lifetime artifact. The package dependency
    /// is implicitly unpinned when the process terminates.
    Process = 0,

    /// The lifetime artifact is an absolute filename or path.
    /// The package dependency is implicitly unpinned when this is deleted.
    FilePath = 1,

    /// The lifetime artifact is a registry key in the format
    /// 'root\\subkey' where root is one of the following: HKLM, HKCU, HKCR, HKU.
    /// The package dependency is implicitly unpinned when this is deleted.
    RegistryKey = 2,
};

enum class MddAddPackageDependencyFlags : uint32_t
{
    None                      = 0,
    OnlyUseFirstPackageFamily = 0x00000001,
    PrependIfRankCollision    = 0x00000002,
};
DEFINE_ENUM_FLAG_OPERATORS(MddAddPackageDependencyFlags);

#define MDD_PACKAGE_DEPENDENCY_RANK_DEFAULT 0

enum class MddPackageDependencyProcessorArchitectures : uint32_t
{
    None = 0,
    Neutral = 0x00000001,
    X86 = 0x00000002,
    X64 = 0x00000004,
    Arm = 0x00000008,
    Arm64 = 0x00000010,
    X86OnArm64 = 0x00000020,
};
DEFINE_ENUM_FLAG_OPERATORS(MddPackageDependencyProcessorArchitectures);

DECLARE_HANDLE(MDD_PACKAGEDEPENDENCY_CONTEXT);

/// Define a package dependency. The criteria for a PackageDependency
/// (package family name, minimum version, etc)
/// may match multiple packages, but ensures Deployment won't remove
/// a package if it's the only one satisfying the PackageDependency.
///
/// @note A package matching a PackageDependency pin can still be removed
///       as long as there's another that satisfies the PackageDependency.
///       For example, if Fwk-v1 is installed and a PackageDependency specifies
///       MinVersion=1 and then Fwk-v2 is installed, Deployment could remove
///       Fwk-v1 because Fwk-v2 will satisfy the PackageDependency. After Fwk-v1
///       is removed Deployment won't remove Fwk-v2 because it's the only package
///       satisfying the PackageDependency. Thus Fwk-v1 and Fwk-v2 (and any other
///       package matching the PackageDependency) are 'loosely pinned'. Deployment
///       guarantees it won't remove a package if it would make a PackageDependency
///       unsatisfied.
///
/// A PackageDependency specifies criteria (package family, minimum version, etc)
/// and not a specific package. Deployment reserves the right to use a different
/// package (e.g. higher version) to satisfy the PackageDependency if/when
/// one becomes available.
///
/// @param user the user scope of the package dependency. If NULL the caller's
///        user context is used. MUST be NULL if MddPinPackageDependency::ScopeIsSystem
///        is specified
/// @param lifetimeArtifact MUST be NULL if lifetimeKind=MddPinPackageDependencyLifetimeKind::Process
/// @param packageDependencyId allocated via LocalAlloc; use LocalFree to deallocate
///
/// @note MddPinPackageDependency() fails if the PackageDependency cannot be resolved to a specific
///       package. This package resolution check is skipped if
///       MddPinPackageDependency::DoNotVerifyDependencyResolution is specified. This is useful
///       for installers running as user contexts other than the target user (e.g. installers
///       running as LocalSystem).
STDAPI MddPinPackageDependency(
    PSID user,
    _In_ PCWSTR packageFamilyName,
    PACKAGE_VERSION minVersion,
    MddPackageDependencyProcessorArchitectures packageDependencyProcessorArchitectures,
    MddPinPackageDependencyLifetimeKind lifetimeKind,
    PCWSTR lifetimeArtifact,
    MddPinPackageDependencyFlags flags,
    _Outptr_result_maybenull_ PWSTR* packageDependencyId);

/// Undefine a package dependency. Removing a pin on a PackageDependency is typically done at uninstall-time.
/// This implicitly occurs if the package dependency's 'lifetime artifact' (specified via MddPinPackageDependency)
/// is deleted. Packages that are not referenced by other packages and have no pins are elegible to be removed.
///
/// @warn MddUnpinPackageDependency() requires the caller have administrative privileges
///       if the package dependency was pinned with MddPinPackageDependency::ScopeIsSystem.
STDAPI_(void) MddUnpinPackageDependency(
    _In_ PCWSTR packageDependencyId);

/// Resolve a previously-pinned PackageDependency to a specific package and
/// add it to the invoking process' package graph. Once the dependency has
/// been added other code-loading methods (LoadLibrary, CoCreateInstance, etc)
/// can find the binaries in the resolved package.
///
/// Package resoution is specific to a user and can return different values
/// for different users on a system.
///
/// Each successful MddAddPackageDependency() adds the resolve packaged to the
/// calling process' package graph, even if already present. There is no
/// duplicate 'detection' or 'filtering' applied by the API (multiple
/// references from a package is not harmful). Once resolution is complete
/// the package stays resolved for that user until the last reference across
/// all processes for that user is removed via MddRemovePackageDependency (or
/// process termination).
///
/// MddAddPackageDependency() adds the resolved package to the caller's package graph,
/// per the rank specified. A process' package graph is a list of packages sorted by
/// rank in ascending order (-infinityâ€¦0â€¦+infinity). If package(s) are present in the
/// package graph with the same rank as the call to MddAddPackageDependency the resolved
/// package is (by default) added after others of the same rank. To add a package
/// before others o the same rank, specify MddAddPackageDependency::PrependIfRankCollision.
///
/// Every MddAddPackageDependency should be balanced by a MddRemovePackageDependency
/// to remove the entry from the package graph. If the process terminates all package
/// references are removed, but any pins stay behind.
///
/// MddAddPackageDependency adds the resulting package to the process' package
/// graph, per the rank and options/flags parameters. The process' package
/// graph is used to search for DLLs (per Dynamic-Link Library Search Order),
/// WinRT objects and other resources; the caller can now load DLLs, activate
/// WinRT objects and use other resources from the framework package until
/// MddRemovePackageDependency is called. The packageDependencyId parameter
/// must match a package dependency defined for the calling user or the
/// system (i.e. pinned with MddPinPackageDependency::ScopeIsSystem) else
/// an error is returned.
///
/// @param packageDependencyContext valid until passed to MddRemovePackageDependency()
/// @param packageFullName allocated via LocalAlloc; use LocalFree to deallocate
STDAPI MddAddPackageDependency(
    _In_ PCWSTR packageDependencyId,
    INT32 rank,
    MddAddPackageDependencyFlags flags,
    _Out_ MDD_PACKAGEDEPENDENCY_CONTEXT* packageDependencyContext,
    _Outptr_opt_result_maybenull_ PWSTR* packageFullName);

/// Remove a resolved PackageDependency from the current process' package graph
/// (i.e. undo MddAddPackageDependency). Used at runtime (i.e. the moral equivalent
/// of FreeLibrary).
///
/// @note This does not unload loaded resources (DLLs etc). After removing
///        a package dependency any files loaded from the package can continue
///        to be used; future file resolution will fail to see the removed
///        package dependency.
STDAPI_(void) MddRemovePackageDependency(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext);

/// Return the package full name that would be used if the
/// PackageDependency were to be resolved. Does not add the
/// package to the process graph.
///
/// @param packageFullName allocated via LocalAlloc; use LocalFree to deallocate
STDAPI MddGetResolvedPackageFullNameForPackageDependency(
    _In_ PCWSTR packageDependencyId,
    _Outptr_result_maybenull_ PWSTR* packageFullName);

/// Return TRUE if PackageDependency pins would produce the same package
/// when resolved e.g. whether they share the same packageFamilyName,
/// minVersion, and packageDependencyProcessorArchitectures values.
STDAPI_(BOOL) MddArePackageDependencyIdsEquivalent(
    _In_ PCWSTR packageDependencyId1,
    _In_ PCWSTR packageDependencyId2);

/// Return TRUE if context1 and contextId2
/// are associated with the same resolved package.
STDAPI_(BOOL) MddArePackageDependencyContextsEquivalent(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT context1,
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT context2);

#endif // MSIXDYNAMICDEPENDENCY_H
