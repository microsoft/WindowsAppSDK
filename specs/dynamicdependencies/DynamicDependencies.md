# Background

MSIX supports the ability for packaged applications to access components and other files distributed as Framework packages. However this functionality provides a rather 'static' world view, where dependencies are known at development time and resolved at install-time. There is no support for runtime to define a Framework dependency based on machine state, user interface or other post-development factors. Access to Framework package content is also limited access to packaged applications; non-packaged applications cannot use content provided via Framework packages.

Microsoft-internal task [23447728](https://task.ms/23447728)

This is the spec for proposal [MSIX Dynamic Dependencies - allow any process to use MSIX Framework packages #89](https://github.com/microsoft/ProjectReunion/issues/89).

# Description

This feature providse APIs to enable access to packaged content at runtime, regardless if the caller is packaged or not. This supplements the MSIX appmodel's current static dependency support (via in appxmanifest.xml) with a dynamic runtime equivalent. It also allows non-packaged processes (which have no appxmanifest.xml) to use packaged content.

# Examples

Samples illustrating the DynamicDependency APIs
* [Sample 1](sample-1.md) - Fabrikam app using Contosso's Muffins package [\[Win32\]](sample-1.md#win32) [\[WinRT\]](sample-1.md#winrt)
* [Sample 2](sample-2.md) - Fabrikam app using Contosso's Muffins package with smart class helpers [\[Win32\]](sample-2.md#win32)
* [Sample 3](sample-3.md) - LolzKitten app using Contosso's Muffins package via transient package dependency [\[Win32\]](sample-3.md#win32) [\[WinRT\]](sample-3.md#winrt)
* [Sample 4](sample-4.md) - LolzKitten Installer / Uninstaller with File+Registry LifetimeArtifacts [\[Win32\]](sample-4.md#win32) [\[WinRT\]](sample-4.md#winrt)
* [Sample 5](sample-5.md) - LolzKitten app using PackageDependency pinned by LolzKitten Installer [\[Win32\]](sample-5.md#win32) [\[WinRT\]](sample-5.md#winrt)
* [Sample 6](sample-6.md) - LolzKitten Installer / Uninstaller defining a 32bit PackageDependency [\[Win32\]](sample-6.md#win32) [\[WinRT\]](sample-6.md#winrt)
* [Sample 7](sample-7.md) - LolzKitten app ordering Packages in PackageGraph [\[Win32\]](sample-7.md#win32) [\[WinRT\]](sample-7.md#winrt)
* [Sample 8](sample-8.md) - LolzKitten app ordering Packages in PackageGraph with prepend [\[Win32\]](sample-8.md#win32) [\[WinRT\]](sample-8.md#winrt)

# Remarks

All processes have a package graph. A process may be created with entries in its package graph; this is referred to as the 'static package graph'.

Packaged processes (i.e. a process with package identity) are created with a static package graph per their AppxManifest.xml. A process' static package graph cannot be altered, but it can be supplemented at runtime via the Dynamic Dependency API.

Processes without package identity have an no static package graph. They can modify their package graph using the Dynamic Dependency API.

```MddPinPackageDependency``` defines a package dependency.

```MddAddPackageDependency``` determines a package that satisfies a package dependency and updates the caller's process. This includes adding the resolved package to the process' package graph, updating the Loader to include the resolved package in the DLL Search Order, etc. The package dependency is resolved to a specific package if not already resolved.

A resolved PackageDependency is represented by ```MDD_PACKAGE_DEPENDENCY_CONTEXT```.

Once a PackageDependency is resolved to a package all further ```MddAddPackageDependency``` calls yield the same result until the package dependency is unresolved. Resolved package dependencies are tracked by User + PackageDependencyId. This ensures multiple overlapping calls to ```MddAddPackageDependency``` yield the same result. A package dependency is unresolved when the last ```MDD_PACKAGE_DEPENDENCY_CONTEXT``` is closed (via ```MddRemovePackageDependency``` or process termination).

```MddRemovePackageDependency``` removes the resolved PackageDependency from the calling process' package graph.

```MddUnpinPackageDependency``` undefines a package dependency previously defined via ```MddPinPackageDependency```.

PackageDependency definitions and usage are tracked and managed on a per-user basis.

PackageDependency definitions are not persisted or tracked across reboots if ```MddPinPackageDependency``` is called with ```MddMddPinPackageDependency::LifecycleHint_Process```. Specify ```MddPinPackageDependency::LifecycleHint_FileOrPath``` or ```MddPinPackageDependency::LifecycleHint_RegistrySubkey``` for ```MddPinPackageDependency``` to persist the definition until explicitly removed via ```MddUnpinPackageDependency``` or the specified lifetime artifact is deleted.

If concurrent processes need the same package resolution for a defined criteria they should share the packageDependencyId returned by ```MddPinPackageDependency```. Concurrent processes running as the same user calling ```MddAddPackageDependency``` with the same packageDependencyId get the same resolved package added to their package graph. This enables multiple concurrent processes needing the same package resolution get a consistent answer.

Package dependencies can only be resolved to packages registered for a user. As packages cannot be registered for LocalSystem the Dynamic Dependencies feature is not available to callers running as LocalSystem.

# API Notes

<!-- TEMPLATE

    Option 1: Give a one or two line description of each API (type and member),
        or at least the ones that aren't obvious from their name. These
        descriptions are what show up in IntelliSense. For properties, specify
        the default value of the property if it isn't the type's default (for
        example an int-typed property that doesn't default to zero.)

    Option 2: Put these descriptions in the below API Details section,
        with a "///" comment above the member or type.
-->

# API Details

## Win32 API - MsixDynamicDependency.hpp

All Win32 APIs are prefixed with Mdd/MDD for MSIX Dynamic Dependencies.
```c++
enum class MddPinPackageDependency : uint32_t
{
    None                               0,
    DoNotVerifyDependencyResolution    0x00000001,
    LifecycleHint_Process              0,
    LifecycleHint_FileOrPath           0x00000002,
    LifecycleHint_RegistrySubkey       0x00000004,

     /// Define the package dependency for the system, accessible to all users
     /// (default is the package dependency is defined for a specific user).
     /// This option requires the caller has adminitrative privileges.
    ScopeIsSystem                      0x00000008,
};
DEFINE_ENUM_FLAG_OPERATORS(MddPinPackageDependency)

enum class MddAddPackageDependency : uint32_t
{
    None                       0,
    OnlyUseFirstPackageFamily  0x00000001,
    PrependIfRankCollision     0x00000002,
};
DEFINE_ENUM_FLAG_OPERATORS(MddAddPackageDependency)

#define PACKAGE_DEPENDENCY_RANK_DEFAULT 0

enum class MddPackageDependencyProcessorArchitectures : uint32_t
{
    None = 0,
    Neutral = 0x00000001,
    X86     = 0x00000002,
    X64     = 0x00000004,
    Arm     = 0x00000008,
    Arm64   = 0x00000010,
    X86A64  = 0x00000020,
};
DEFINE_ENUM_FLAG_OPERATORS(MddPackageDependencyProcessorArchitectures)

DECLARE_HANDLE(MDD_PACKAGEDEPENDENCY_CONTEXT);

// Define a package dependency. The criteria for a PackageDependency
// (package family name, minimum version, etc)
// may match multiple packages, but ensures Deployment won't remove
// a package if it's the only one satisfying the PackageDependency.
//
// @note A package matching a PackageDependency pin can still be removed
//       as long as there's another that satisfies the PackageDependency.
//       For example, if Fwk-v1 is installed and a PackageDependency specifies
//       MinVersion=1 and then Fwk-v2 is installed, Deployment could remove
//       Fwk-v1 because Fwk-v2 will satisfy the PackageDependency. After Fwk-v1
//       is removed Deployment won't remove Fwk-v2 because it's the only package
//       satisfying the PackageDependency. Thus  Fwk-v1 and Fwk-v2 (and any other
//       package matching the PackageDependency) are 'loosely pinned' â€“ Deployment
//       guarantees it won't remove a package if it would make a PackageDependency
//       unsatisfied.
//
// A PackageDependency specifies criteria (package family, minimum version, etc)
// and not a specific package. Deployment reserves the right to use a different
// package (e.g. higher version) to satisfy the PackageDependency if/when
// one becomes available.
//
// @param user the user scope of the package dependency. If NULL the caller's
//        user context is used. MUST be NULL if MddPinPackageDependency::ScopeIsSystem
//        is specified
// @param lifetimeArtifact MUST be NULL if MddMddPinPackageDependency::LifecycleHint_Process (default)
// @param packageDependencyId allocated via LocalAlloc; use LocalFree to deallocate
//
// @note MddPinPackageDependency() fails if the PackageDependency cannot be resolved to a specific
//       package. This package resolution check is skipped if
//       MddPinPackageDependency::DoNotVerifyDependencyResolution is specified. This is useful
//       for installers running as user contexts other than the target user (e.g. installers
//       running as LocalSystem).
STDAPI MddPinPackageDependency(
    PSID user,
    _In_ PCWSTR packageFamilyName,
    PACKAGE_VERSION minVersion,
    MddPackageDependencyProcessorArchitectures packageDependencyProcessorArchitectures,
    PCWSTR lifetimeArtifact,
    MddPinPackageDependency flags,
    _Outptr_result_maybenull_ PWSTR* packageDependencyId);

// Undefine a package dependency. Removing a pin on a PackageDependency is typically done at uninstall-time.
// This implicitly occurs if the package dependency's 'lifetime artifact' (specified via MddPinPackageDependency)
// is deleted. Packages that are not referenced by other packages and have no pins are elegible to be removed.
//
// @warn MddUnpinPackageDependency() requires the caller have administrative privileges
//       if the package dependency was pinned with MddPinPackageDependency::ScopeIsSystem.
STDAPI MddUnpinPackageDependency(
    _In_ PCWSTR packageDependencyId);

// Resolve a previously-pinned PackageDependency to a specific package and
// add it to the invoking process' package graph. Once the dependency has
// been added other code-loading methods (LoadLibrary, CoCreateInstance, etc)
// can find the binaries in the resolved package.
//
// Package resoution is specific to a user and can return different values
// for different users on a system.
//
// Each successful MddAddPackageDependency() adds the resolve packaged to the
// calling process' package graph, even if already present. There is no
// duplicate 'detection' or 'filtering' applied by the API (multiple
// references from a package is not harmful). Once resolution is complete
// the package stays resolved for that user until the last reference across
// all processes for that user is removed via MddRemovePackageDependency (or
// process termination).
//
// MddAddPackageDependency() adds the resolved package to the caller's package graph,
// per the rank specified. A process' package graph is a list of packages sorted by
// rank in ascending order (-infinityâ€¦0â€¦+infinity). If package(s) are present in the
// package graph with the same rank as the call to MddAddPackageDependency the resolved
// package is (by default) added after others of the same rank. To add a package
// before others o the same rank, specify MddAddPackageDependency::PrependIfRankCollision.
//
// Every MddAddPackageDependency should be balanced by a MddRemovePackageDependency
// to remove the entry from the package graph. If the process terminates all package
// references are removed, but any pins stay behind.
//
// MddAddPackageDependency adds the resulting package to the process' package
// graph, per the rank and options/flags parameters. The process' package
// graph is used to search for DLLs (per Dynamic-Link Library Search Order),
// WinRT objects and other resources; the caller can now load DLLs, activate
// WinRT objects and use other resources from the framework package until
// MddRemovePackageDependency is called. The packageDependencyId parameter
// must match a package dependency defined for the calling user or the
// system (i.e. pinned with MddPinPackageDependency::ScopeIsSystem) else
// an error is returned.
//
// @param packageDependencyContext valid until passed to MddRemovePackageDependency()
// @param packageFullName allocated via LocalAlloc; use LocalFree to deallocate
STDAPI MddAddPackageDependency(
    _In_ PCWSTR packageDependencyId,
    INT32 rank,
    MddMddAddPackageDependency flags,
    _Out_ MDD_PACKAGEDEPENDENCY_CONTEXT* packageDependencyContext,
    _Outptr_opt_result_maybenull_ PWSTR* packageFullName);

// Remove a resolved PackageDependency from the current process' package graph
// (i.e. undo MddAddPackageDependency). Used at runtime (i.e. the moral equivalent
// of FreeLibrary).
//
// @note This does not unload loaded resources (DLLs etc). After removing
//        a package dependency any files loaded from the package can continue
//        to be used; future file resolution will fail to see the removed
//        package dependency.
STDAPI MddRemovePackageDependency(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext);

// Return the package full name that would be used if the
// PackageDependency were to be resolved. Does not add the
// package to the process graph.
//
// @param packageFullName allocated via LocalAlloc; use LocalFree to deallocate
STDAPI MddGetResolvedPackageFullNameForPackageDependency(
    _In_ PCWSTR packageDependencyId,
    _Outptr_result_maybenull_ PWSTR* packageFullName);

// Return TRUE if PackageDependency pins would produce the same package
// when resolved e.g. whether they share the same packageFamilyName,
// minVersion, and packageDependencyProcessorArchitectures values.
STDAPI_(BOOL) MddArePackageDependencyIdsEquivalent(
    _In_ PCWSTR packageDependencyId1,
    _In_ PCWSTR packageDependencyId2);

// Return TRUE if packageDependencyIdContext1 and packageDependencyContextId2
// are associated with the same resolved package.
STDAPI_(BOOL) MddArePackageDependencyContextsEquivalent(
    _In_ const MDD_PACKAGEDEPENDENCY_CONTEXT* packageDependencyContext1,
    _In_ const MDD_PACKAGEDEPENDENCY_CONTEXT* packageDependencyContext2);
```

## WinRT API
```c# (but really MIDL3)
namespace Microsoft.ApplicationModel
{
/// CPU architectures to optionally filter available packages against a package dependency.
/// These generally correspond to processor architecture types supported by MSIX.
/// @see Windows.System.ProcessorArchitecture
enum PackageDependencyProcessorArchitectures
{
    None    = 0,
    Neutral = 0x00000001,
    X86     = 0x00000002,
    X64     = 0x00000004,
    Arm     = 0x00000008,
    Arm64   = 0x00000010,
    X86A64  = 0x00000020,
};

/// Options when 'pinning' a package dependency
runtimeclass PinPackageDependencyOptions
{
    PinPackageDependencyOptions();

    /// Optional filtering by cpu architecture(s)
    PackageDependencyProcessorArchitectures Architectures;

    /// Do not verify at least 1 matching package exists when pinning a package dependency
    boolean DoNotVerifyDependencyResolution;

    /// An absolute filename or path to use as a lifetime artifact when pinning a package dependency.
    /// If set, the package dependency is implicitly unpinned when this is deleted.
    String LifetimeArtifactFileOrPath;

    /// A registry key to use as a lifetime artifact when pinning pinning a package dependency.
    /// If set, the package dependency is implicitly unpinned when this is deleted.
    String LifetimeArtifactRegistrySubkey;
}

/// Options when adding a package dependency
runtimeclass AddPackageDependencyOptions
{
    AddPackageDependencyOptions();

    /// The rank when adding the package dependency to a a package graph.
    /// @note A package graph is sorted in ascending order from -infinity...0...+infinity
    /// @note The default value is zero
    int Rank;

    /// If a package dependency resolves to a package with dependencies and this option is true
    /// the dependencies are ignored; only the package is added to the package graph. By default
    /// a resolved package and its dependencies are added to the package graph.
    boolean OnlyUseFirstPackageFamily;

    /// If a package is added to a package graph with a package of the same rank (aka a collision on rank)
    /// and this option is true the package is prepended to the set of packages of the same rank.
    /// By default packages are appended to the set of packages with the same rank.
    boolean PrependIfRankCollision;
}

/// TBD
runtimeclass PackageDependency
{
    /// Create an intstance of the package dependency identified by id.
    PackageDependency(String id);

    /// Return the package dependency id.
    String Id { get; }

    /// Return true if the package dependencies would produce the same
    /// package when resolved e.g. whether they share the same packageFamilyName,
    /// minVersion, and packageDependencyProcessorArchitectures values.
    static boolean AreEquivalent(String packageDependencyId1, String packageDependencyId2);

    /// Return true if this and otherPackageDependency would produce the same
    /// package when resolved e.g. whether they share the same packageFamilyName,
    /// minVersion, and packageDependencyProcessorArchitectures values.
    boolean AreEquivalent(PackageDependency otherPackageDependency);

    /// Define a package dependency for the current user. The criteria for a PackageDependency
    /// (package family name, minimum version, etc) may match multiple
    /// packages, but ensures Deployment won't remove a package if it's
    /// the only one satisfying the PackageDependency.
    ///
    /// @note A package matching a PackageDependency pin can still be removed
    ///       as long as there's another that satisfies the PackageDependency.
    ///       For example, if Fwk-v1 is installed and a PackageDependency specifies
    ///       MinVersion=1 and then Fwk-v2 is installed, Deployment could remove
    ///       Fwk-v1 because Fwk-v2 will satisfy the PackageDependency. After Fwk-v1
    ///       is removed Deployment won't remove Fwk-v2 because it's the only package
    ///       satisfying the PackageDependency. Thus  Fwk-v1 and Fwk-v2 (and any other
    ///       package matching the PackageDependency) are 'loosely pinned' â€“ Deployment
    ///       guarantees it won't remove a package if it would make a PackageDependency
    ///       unsatisfied.
    ///
    /// A PackageDependency specifies criteria (package family, minimum version, etc)
    /// and not a specific package. Deployment reserves the right to use a different
    /// package (e.g. higher version) to satisfy the PackageDependency if/when
    /// one becomes available.
    ///
    /// This method is equivalent to PinForUser(null,...).
    ///
    /// @param packageFamilyName the package family to pin
    /// @param minVerrsion the minimum version to pin
    /// @param options additional options affecting the package dependency
    ///
    /// @note This fails if the package dependency cannot be resolved to a specific package.
    ///       This package resolution check is skipped if MddPinPackageDependency.DoNotVerifyDependencyResolution
    ///       is specified. This is useful if a package satisfying the dependency
    ///       will be installed after the package dependency is defined.
    ///
    /// @see PinForUser
    /// @see PinForSystem
    static PackageDependency Pin(
        String packageFamilyName,
        PackageVersion minVersion,
        PinPackageDependencyOptions options);

    /// Define a package dependency for a user. The criteria for a PackageDependency
    /// (package family name, minimum version, etc) may match multiple
    /// packages, but ensures Deployment won't remove a package if it's
    /// the only one satisfying the PackageDependency.
    ///
    /// @note A package matching a PackageDependency pin can still be removed
    ///       as long as there's another that satisfies the PackageDependency.
    ///       For example, if Fwk-v1 is installed and a PackageDependency specifies
    ///       MinVersion=1 and then Fwk-v2 is installed, Deployment could remove
    ///       Fwk-v1 because Fwk-v2 will satisfy the PackageDependency. After Fwk-v1
    ///       is removed Deployment won't remove Fwk-v2 because it's the only package
    ///       satisfying the PackageDependency. Thus  Fwk-v1 and Fwk-v2 (and any other
    ///       package matching the PackageDependency) are 'loosely pinned' â€“ Deployment
    ///       guarantees it won't remove a package if it would make a PackageDependency
    ///       unsatisfied.
    ///
    /// A PackageDependency specifies criteria (package family, minimum version, etc)
    /// and not a specific package. Deployment reserves the right to use a different
    /// package (e.g. higher version) to satisfy the PackageDependency if/when
    /// one becomes available.
    ///
    /// @param user the user scope of the package dependency. If null the caller's user context is used
    /// @param packageFamilyName the package family to pin
    /// @param minVerrsion the minimum version to pin
    /// @param options additional options affecting the package dependency
    ///
    /// @note This fails if the package dependency cannot be resolved to a specific package.
    ///       This package resolution check is skipped if MddPinPackageDependency.DoNotVerifyDependencyResolution
    ///       is specified. This is useful for installers running as user contexts other than the target user
    ///       (e.g. installers running as LocalSystem) or if a package satisfying the dependency
    ///       will be installed after the package dependency is defined.
    static PackageDependency PinForUser(
        Windows.System.User user,
        String packageFamilyName,
        PackageVersion minVersion,
        PinPackageDependencyOptions options);

    /// Define a package dependency for the system (i.e. all users). The criteria for a PackageDependency
    /// (package family name, minimum version, etc) may match multiple
    /// packages, but ensures Deployment won't remove a package if it's
    /// the only one satisfying the PackageDependency.
    ///
    /// @note A package matching a PackageDependency pin can still be removed
    ///       as long as there's another that satisfies the PackageDependency.
    ///       For example, if Fwk-v1 is installed and a PackageDependency specifies
    ///       MinVersion=1 and then Fwk-v2 is installed, Deployment could remove
    ///       Fwk-v1 because Fwk-v2 will satisfy the PackageDependency. After Fwk-v1
    ///       is removed Deployment won't remove Fwk-v2 because it's the only package
    ///       satisfying the PackageDependency. Thus  Fwk-v1 and Fwk-v2 (and any other
    ///       package matching the PackageDependency) are 'loosely pinned' â€“ Deployment
    ///       guarantees it won't remove a package if it would make a PackageDependency
    ///       unsatisfied.
    ///
    /// A PackageDependency specifies criteria (package family, minimum version, etc)
    /// and not a specific package. Deployment reserves the right to use a different
    /// package (e.g. higher version) to satisfy the PackageDependency if/when
    /// one becomes available.
    ///
    /// @param user the user scope of the package dependency. If null the caller's user context is used
    /// @param packageFamilyName the package family to pin
    /// @param minVerrsion the minimum version to pin
    /// @param options additional options affecting the package dependency
    ///
    /// @note This fails if the package dependency cannot be resolved to a specific package.
    ///       This package resolution check is skipped if MddPinPackageDependency.DoNotVerifyDependencyResolution
    ///       is specified. This is useful for installers pinning a package dependency for all users on a system.
    static PackageDependency PinForSystem(
        String packageFamilyName,
        PackageVersion minVersion,
        PinPackageDependencyOptions options);

    void Unpin();

    /// Resolve a previously pinned PackageDependency to a specific package and
    /// add it to the calling process' package graph. Once the dependency has
    /// been added other code-loading methods (LoadLibrary, CoCreateInstance, etc)
    /// can find the binaries in the resolved package.
    ///
    /// Package resoution is specific to a user. The same package dependency can
    /// resolve to different packages for different users on a system.
    ///
    /// This adds the resulting package to the process' package graph.
    /// A process' package graph is used to search for DLLs (per Dynamic-Link Library Search Order),
    /// WinRT objects and other resources; the caller can now load DLLs, activate
    /// WinRT objects and use other resources from the framework package until
    /// PackageDependencyContext.Remove() is called (or the process ends).
    /// The package dependency Id must match a package dependency defined
    /// for the calling user or the system (via PinForSystem) or an exception is raised.
    ///
    /// Each successful call adds the resolve packaged to the
    /// calling process' package graph, even if already present. There is no
    /// duplicate 'detection' or 'filtering' applied by the API (multiple
    /// references to a package is not harmful). Once resolution is complete
    /// the package stays resolved for that user until the last reference across
    /// all processes for that user is removed via PackageDependencyContext.Remove()
    /// (or process termination).
    ///
    /// Calls to Add() can be balanced by a PackageDependencyContext.Remove()
    /// to remove the entry from the package graph.
    PackageDependencyContext Add();

    /// Resolve a previously pinned PackageDependency to a specific package and
    /// add it to the calling process' package graph. Once the dependency has
    /// been added other code-loading methods (LoadLibrary, CoCreateInstance, etc)
    /// can find the binaries in the resolved package.
    ///
    /// Package resoution is specific to a user. The same package dependency can
    /// resolve to different packages for different users on a system.
    ///
    /// This adds the resulting package to the process' package graph.
    /// A process' package graph is used to search for DLLs (per Dynamic-Link Library Search Order),
    /// WinRT objects and other resources; the caller can now load DLLs, activate
    /// WinRT objects and use other resources from the framework package until
    /// PackageDependencyContext.Remove() is called (or the process ends).
    /// The package dependency Id must match a package dependency defined
    /// for the calling user or the system (via PinForSystem) or an exception is raised.
    ///
    /// Each successful call adds the resolve packaged to the
    /// calling process' package graph, even if already present. There is no
    /// duplicate 'detection' or 'filtering' applied by the API (multiple
    /// references to a package is not harmful). Once resolution is complete
    /// the package stays resolved for that user until the last reference across
    /// all processes for that user is removed via PackageDependencyContext.Remove()
    /// (or process termination).
    ///
    /// This adds the resolved package to the caller's package graph, per rank.
    /// A process' package graph is a list of packages sorted by rank in ascending
    /// order (-infinity...0...+infinity). If package(s) are present in the
    /// package graph with the same rankrank the resolved package is
    /// (by default) added after others of the same rank. To add a package
    /// before others of the same rank, specify PackageDependency.PrependIfRankCollision.
    ///
    /// Calls to Add() can be balanced by a PackageDependencyContext.Remove()
    /// to remove the entry from the package graph.
    PackageDependencyContext Add(AddPackageDependencyOptions options);
}

/// A unique identifier for a resolved package dependency
struct PackageDependencyContextId
{
    UInt64 Id;
};

///TBD
runtimeclass PackageDependencyContext : ICloseable
{
    /// Create an intstance of the package dependency context identified by context
    PackageDependencyContext(PackageDependencyContextId);

    /// Returns the package dependency context
    PackageDependencyContextId Context { get; }

    /// Returns the package full name of the resolved package for this context
    String PackageFullName { get; }

    /// Return true if packageDependencyContext1 and packageDependencyContext2
    /// are associated with the same resolved package.
    static boolean AreEquivalent(
        PackageDependencyContextId packageDependencyContextId1,
        PackageDependencyContextId packageDependencyContextId2);

    /// Return true if this and otherPackageDependencyContext
    /// are associated with the same resolved package.
    boolean AreEquivalent(PackageDependencyContext otherPackageDependencyContext);

    /// Remove the resolved package dependency from the current process' package graph
    /// (i.e. undo PackageDependency.Add()).
    ///
    /// This is the moral equivalent of FreeLibrary.
    ///
    /// @note This does not unload loaded resources (DLLs etc). After removing
    ///        a package dependency any files loaded from the package can continue
    ///        to be used; future package dependency resolution (via new calls to Add)
    ///        will fail to see the removed package dependency.
    void Remove();
}
}
```

# Appendix

TODO: Answer and delete

Q: Package dependencies are only resolved for Framework packages. Should other package types (Main, Resource, Optional) be supported?

Q:WinRT: How should 'lifetimeArtifact' and MddPinPackageDependency_LifecycleHint* be expressed in the WinRT API? Some ideas:
* String file; String regkey; if both null then it's Process
* String lifetimeArtifact; boolean isFile; boolean isReg; boolean isProcess; and only 1 can be true
* ILifetimeArtifact property with multiple implementations e.g. FileLifetimeArtifact = { string file; } vs * RegistryLifetimeArtifact = { HKEY root; string subkey; } vs Process=null
* ?

Q:WinRT: How to express equivalent of PACKAGE_DEPENDENCY_RANK_DEFAULT?
