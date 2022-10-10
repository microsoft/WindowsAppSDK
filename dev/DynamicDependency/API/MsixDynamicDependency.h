// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(MSIXDYNAMICDEPENDENCY_H)
#define MSIXDYNAMICDEPENDENCY_H

#include <appmodel.h>

#include <stdint.h>

/// MSIX Dynamic Dependency HRESULT: Windows App Runtime is not in the package graph.
#define MDD_E_WINDOWSAPPRUNTIME_NOT_IN_PACKAGE_GRAPH    _HRESULT_TYPEDEF_(0x80040001L)

/// MSIX Dynamic Dependency HRESULT: Data Store not found (Windows App Runtime's Main package not registered?)
#define MDD_E_WINDOWSAPPRUNTIME_DATASTORE_NOT_FOUND     _HRESULT_TYPEDEF_(0x80040002L)

/// MSIX Dynamic Dependency: Bootstrap initialization is scanning for an applicable DynamicDependencyLifetimeManager (DDLM) package
#define MDD_E_BOOTSTRAP_INITIALIZE_SCAN_FOR_DDLM        _HRESULT_TYPEDEF_(0x80040010L)

/// MSIX Dynamic Dependency: Bootstrap initialization found a DynamicDependencyLifetimeManager (DDLM) but doesn't match the criteria
#define MDD_E_BOOTSTRAP_INITIALIZE_DDLM_SCAN_NO_MATCH   _HRESULT_TYPEDEF_(0x80040011L)

/// MSIX Dynamic Dependency: Bootstrap initialization found a DynamicDependencyLifetimeManager (DDLM) that does match the criteria
#define MDD_E_BOOTSTRAP_INITIALIZE_DDLM_SCAN_MATCH      _HRESULT_TYPEDEF_(0x80040012L)

/// MSIX Dynamic Dependency: Bootstrap initialization found an applicable DynamicDependencyLifetimeManager (DDLM) best matching the criteria
#define MDD_E_BOOTSTRAP_INITIALIZE_DDLM_FOUND           _HRESULT_TYPEDEF_(0x80040013L)

/// MSIX Dynamic Dependency: Bootstrap initialization request is incompatible with current Bootstrap initialization state.
#define MDD_E_BOOTSTRAP_INITIALIZE_INCOMPATIBLE         _HRESULT_TYPEDEF_(0x80040014L)

#if defined(__cplusplus)

enum class MddCreatePackageDependencyOptions : uint32_t
{
    None = 0,

    /// Disable dependency resolution when pinning a package dependency.
    DoNotVerifyDependencyResolution = 0x00000001,

    /// Define the package dependency for the system, accessible to all users
    /// (default is the package dependency is defined for a specific user).
    /// This option requires the caller has adminitrative privileges.
    ScopeIsSystem = 0x00000002,
};
DEFINE_ENUM_FLAG_OPERATORS(MddCreatePackageDependencyOptions)

enum class MddPackageDependencyLifetimeKind
{
    /// The current process is the lifetime artifact. The package dependency
    /// is implicitly deleted when the process terminates.
    Process = 0,

    /// The lifetime artifact is an absolute filename or path.
    /// The package dependency is implicitly deleted when this is deleted.
    FilePath = 1,

    /// The lifetime artifact is a registry key in the format
    /// 'root\\subkey' where root is one of the following: HKLM, HKCU, HKCR, HKU.
    /// The package dependency is implicitly deleted when this is deleted.
    RegistryKey = 2,
};

enum class MddAddPackageDependencyOptions : uint32_t
{
    None                   = 0,
    PrependIfRankCollision = 0x00000001,
};
DEFINE_ENUM_FLAG_OPERATORS(MddAddPackageDependencyOptions)

#define MDD_PACKAGE_DEPENDENCY_RANK_DEFAULT 0

enum class MddPackageDependencyProcessorArchitectures : uint32_t
{
    None       = 0,
    Neutral    = 0x00000001,
    X86        = 0x00000002,
    X64        = 0x00000004,
    Arm        = 0x00000008,
    Arm64      = 0x00000010,
    X86OnArm64 = 0x00000020,
};
DEFINE_ENUM_FLAG_OPERATORS(MddPackageDependencyProcessorArchitectures)

DECLARE_HANDLE(MDD_PACKAGEDEPENDENCY_CONTEXT);

/// Define a package dependency. The criteria for a PackageDependency
/// (package family name, minimum version, etc)
/// may match multiple packages, but ensures Deployment won't remove
/// a package if it's the only one satisfying the PackageDependency.
///
/// @note A package matching a PackageDependency pin can still be removed
///       as long as there's another package that satisfies the PackageDependency.
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
///        user context is used. MUST be NULL if MddCreatePackageDependencyOptions::ScopeIsSystem
///        is specified
/// @param lifetimeArtifact MUST be NULL if lifetimeKind=MddPackageDependencyLifetimeKind::Process
/// @param packageDependencyId allocated via HeapAlloc; use HeapFree to deallocate
///
/// @note MddTryCreatePackageDependency() fails if the PackageDependency cannot be resolved to a specific
///       package. This package resolution check is skipped if
///       MddCreatePackageDependencyOptions::DoNotVerifyDependencyResolution is specified. This is useful
///       for installers running as user contexts other than the target user (e.g. installers
///       running as LocalSystem).
STDAPI MddTryCreatePackageDependency(
    PSID user,
    _In_ PCWSTR packageFamilyName,
    PACKAGE_VERSION minVersion,
    MddPackageDependencyProcessorArchitectures packageDependencyProcessorArchitectures,
    MddPackageDependencyLifetimeKind lifetimeKind,
    PCWSTR lifetimeArtifact,
    MddCreatePackageDependencyOptions options,
    _Outptr_result_maybenull_ PWSTR* packageDependencyId) noexcept;

/// Undefine a package dependency. Removing a pin on a PackageDependency is typically done at uninstall-time.
/// This implicitly occurs if the package dependency's 'lifetime artifact' (specified via MddTryCreatePackageDependency)
/// is deleted. Packages that are not referenced by other packages and have no pins are elegible to be removed.
///
/// @warn MddDeletePackageDependency() requires the caller have administrative privileges
///       if the package dependency was pinned with MddCreatePackageDependencyOptions::ScopeIsSystem.
STDAPI_(void) MddDeletePackageDependency(
    _In_ PCWSTR packageDependencyId) noexcept;

/// Resolve a previously-pinned PackageDependency to a specific package and
/// add it to the invoking process' package graph. Once the dependency has
/// been added other code-loading methods (LoadLibrary, CoCreateInstance, etc)
/// can find the binaries in the resolved package.
///
/// Package resolution is specific to a user and can return different values
/// for different users on a system.
///
/// Each successful MddAddPackageDependency() adds the resolved packaged to the
/// calling process' package graph, even if already present. There is no
/// duplicate 'detection' or 'filtering' applied by the API (multiple
/// references from a package is not harmful). Once resolution is complete
/// the package dependency stays resolved for that user until the last reference across
/// all processes for that user is removed via MddRemovePackageDependency (or
/// process termination).
///
/// MddAddPackageDependency() adds the resolved package to the caller's package graph,
/// per the rank specified. A process' package graph is a list of packages sorted by
/// rank in ascending order (-infinity...0...+infinity). If package(s) are present in the
/// package graph with the same rank as the call to MddAddPackageDependency the resolved
/// package is (by default) added after others of the same rank. To add a package
/// before others o the same rank, specify MddAddPackageDependencyOptions::PrependIfRankCollision.
///
/// Every MddAddPackageDependency can be balanced by a MddRemovePackageDependency
/// to remove the entry from the package graph. If the process terminates all package
/// references are removed, but any pins stay behind.
///
/// MddAddPackageDependency adds the resolved package to the process' package
/// graph, per the rank and options parameters. The process' package
/// graph is used to search for DLLs (per Dynamic-Link Library Search Order),
/// WinRT objects and other resources; the caller can now load DLLs, activate
/// WinRT objects and use other resources from the framework package until
/// MddRemovePackageDependency is called. The packageDependencyId parameter
/// must match a package dependency defined for the calling user or the
/// system (i.e. pinned with MddCreatePackageDependencyOptions::ScopeIsSystem) else
/// an error is returned.
///
/// @param packageDependencyContext valid until passed to MddRemovePackageDependency()
/// @param packageFullName allocated via HeapAlloc; use HeapFree to deallocate
STDAPI MddAddPackageDependency(
    _In_ PCWSTR packageDependencyId,
    INT32 rank,
    MddAddPackageDependencyOptions options,
    _Out_ MDD_PACKAGEDEPENDENCY_CONTEXT* packageDependencyContext,
    _Outptr_opt_result_maybenull_ PWSTR* packageFullName) noexcept;

/// Remove a resolved PackageDependency from the current process' package graph
/// (i.e. undo MddAddPackageDependency). Used at runtime (i.e. the moral equivalent
/// of Windows' RemoveDllDirectory()).
///
/// @note This does not unload loaded resources (DLLs etc). After removing
///        a package dependency any files loaded from the package can continue
///        to be used; future file resolution will fail to see the removed
///        package dependency.
STDAPI_(void) MddRemovePackageDependency(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext) noexcept;

/// Return the package full name that would be used if the
/// PackageDependency were to be resolved. Does not add the
/// package to the process graph.
///
/// @param packageFullName allocated via HeapAlloc; use HeapFree to deallocate.
///                        If the package dependency cannot be resolved the function
///                        succeeds but packageFullName is nullptr.
STDAPI MddGetResolvedPackageFullNameForPackageDependency(
    _In_ PCWSTR packageDependencyId,
    _Outptr_result_maybenull_ PWSTR* packageFullName) noexcept;

/// Return the package dependency for the context.
///
/// @param packageDependencyId allocated via HeapAlloc; use HeapFree to deallocate.
///                            If the package dependency context cannot be resolved
///                            the function succeeds but packageDependencyId is nullptr.
STDAPI MddGetIdForPackageDependencyContext(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext,
    _Outptr_result_maybenull_ PWSTR* packageDependencyId) noexcept;

/// Return the package graph's current revision id.
STDAPI_(UINT32) MddGetPackageGraphRevisionId() noexcept;

/// Return the package graph's current revision id.
///
/// @note This API is deprecated and will be removed in a future release.
///       Use MddGetPackageGraphRevisionId().
STDAPI_(UINT32) MddGetGenerationId() noexcept;

#endif // defined(__cplusplus)

#endif // MSIXDYNAMICDEPENDENCY_H
