# 1. MSIX Package Management

This feature provides package management APIs comparable those in namespace
Windows.Management.Deployment but with additional functionality, improved
developer experience and performance optimizations.

- [1. MSIX Package Management](#1-msix-package-management)
- [2. Background](#2-background)
- [3. Description](#3-description)
- [4. Examples](#4-examples)
- [5. Remarks](#5-remarks)
- [6. API Details](#6-api-details)

# 2. Background

Windows sports the ability to deploy and manage software as MSIX packages via
WinRT APIs in the Windows.Management.Deployment namespace. These APIs provide
the means to install, update, uninstall, enumerate and otherwise manage
packages.

The package management APIs were originally introduced in Windows 8 and have
continuously expanded to meet MSIX's growing demands over the past decade.
However, as one of the earliest WinRT APIs they include some patterns out of
step with current API practices and recommendations. Windows App SDK offers
the opportunity to provide a new generation of package management APIs in line
with the latest patterns and recommendations for an improved developer
experience as well as functional enhancements and improved runtime efficiencies.

Microsoft-internal task [45952398](https://task.ms/45952398)

# 3. Description

This API provides enhanced access to Windows' package management
capabilities, focusing on the following scenarios:

* Stage a package
* Register a package
* Add/Update a package
* Remove a package
* Repair a package
* Reset a package
* Provision a package
* Deprovision a package

Additional functionality includes:

* IsReady -- Is a package ready for use?
* EnsureIsReady -- Is a package ready for use and, if not, make it so
* IsPendingRegistration -- Is there an update waiting to install?
* PackageSets -- Batch operations
* Usability -- Quality-of-Life enhancements

# 3.1. API Structure

Methods to drive deployment activity typically follows the pattern:

    <verb>Package[Set][By<Type>][Suffix]Async(target, options)

The following verbs are supported:

* Is...Ready
* Ensure...IsReady
* Add
* Stage
* Register
* Remove
* Repair
* Reset
* Provision
* Deprovision

These methods accept their target package(s) as their first parameter. This
parameter can be an various types of information including:

* Filename
* Path
* PackageFamilyName
* PackageFullName
* Uri

NOTE: Methods with a target of a URI are named ...ByUri....

NOTE: Methods with a target of a PackageFamilyName are named ...ByPackageFamilyName....

NOTE: Methods with a target of a PackageFamilyName are named ...ByPackageFullName....

NOTE: Methods with no ...By<Type>... qualifier accept a string which can
contain one or more types of identifiers. These can vary for different verbs.
See the per-method documentation for the specific target types supported by
each method.

These methods accept options as a matching `<verb>Package[Set]Options` type, e.g.
`AddPackageAsync(string packageUri, AddPackageOptions options)`.

The following table shows the supported permutations of verbs and targets:

|Verb         | Path | Filename | PackageFamilyName | PackageFullName | file:  | http(s): | ms-uup: | PackageSet |
|-------------|:-----|:---------|:------------------|:----------------|:-------|:---------|:--------|:-----------|
|IsReady      |  X   |    X     |       OS/WAS      |       WAS       |   X    |    X     |  WAS    |    WAS     |
|EnsureIsReady|  X   |    X     |         X         |        X        |   X    |    X     |  WAS    |    WAS     |
|Add          | WAS  |    X     |         X         |        X        | OS/WAS |  OS/WAS  | OS/WAS  |    WAS     |
|Stage        | WAS  |    X     |         X         |        X        | OS/WAS |  OS/WAS  | OS/WAS  |    WAS     |
|Register     | WAS  |  OS/WAS  |       OS/WAS      |      OS/WAS     | OS/WAS |    X     | OS/WAS  |    WAS     |
|Remove       |  X   |    X     |        WAS        |      OS/WAS     |   X    |    X     | OS/WAS  |    WAS     |
|Repair       |  X   |    X     |        WAS        |       WAS       |   X    |    X     |  WAS    |    WAS     |
|Reset        |  X   |    X     |        WAS        |       WAS       |   X    |    X     |  WAS    |    WAS     |
|Provision    |  X   |    X     |       OS/WAS      |        X        |   X    |    X     |  WAS    |    WAS     |
|Deprovision  |  X   |    X     |       OS/WAS      |        X        |   X    |    X     |  WAS    |    WAS     |

Legend:

* OS = Supported by Windows (OS) APIs in the Windows.Management.Deployment.PackageManager namespace.
* WAS = Supported by Windows App SDK APIs in the Microsoft.Windows.Management.Deployment.PackageDeploymentManager namespace.
* X = Not supported

# 3.2. Is*Ready()

Is*Ready() methods determine if the target is installed and ready for use. Reasons why a package is not ready can include:

* The package is not present on the machine
* The package is present on the machine but not registered for the user
* The package is registered for the user but is not in a healthy status e.g. it's Package.Status=Tampered

Is*Ready() methods are a quick test to determine if more (costly) work is needed before the target can be used.

# 3.3. Ensure*IsReady()

Ensure*IsReady() methods determine if the target is installed and ready for
use and, if not, makes it so. This can include downloading the target,
registering it for the user and remediating a package in an unhealthy state.

Thus `EnsurePackageIsReady(pkg, options)` is functionally equivalent to

```c#
var pdm = new PackageDeploymentManager();
if (!pdm.IsPackageReady(pkg))
{
    var options = new AddPackageOptions();
    var result = await pdm.AddPackageAsync(pkg, options);
}
endif
```

# 3.3.1. Why Is*Ready() Given Ensure*IsReady()?

Ensure*IsReady() performs an 'is ready' check and returns if all is ready.
There's no efficiency reasons to call Is*Ready() before
Ensure*IsReady() (in fact, it's less efficient as Is*Ready() would occur twice).

However, this can be useful if you need additional work
before potentially performing deployment operations. For example, if you need to prompt
the user for consent before installing the target e.g.

```c#
var pdm = new PackageDeploymentManager();
if (!pdm.IsPackageReady(pkg))
{
    bool ok = AskUserForContent(pkg);
    if (ok)
    {
        var options = new EnsureIsReadyOptions();
        var result = await pdm.EnsurePackageIsReadyAsync(pkg, options);
    }
}
```

# 4. Examples

Samples illustrating the package management APIs:

- [Sample 1](sample-1.md) - Fabrikam app installing Contoso's Muffin package

# 5. Remarks

TODO

# 6. API Details

```c# (but really MIDL3)
namespace Microsoft.Windows.Management.Deployment
{
    [contractversion(1)]
    apicontract PackageDeploymentContract{};

    /// Represents a package storage volume.
    /// @see https://learn.microsoft.com/uwp/api/windows.management.deployment.packagevolume
    [feature(Feature_PackageManager)]
    [contract(PackageDeploymentContract, 1)]
    runtimeclass PackageVolume
    {
        PackageVolume();

        /// @see https://learn.microsoft.com/uwp/api/windows.management.deployment.packagevolume.issystemvolume
        Boolean IsSystemVolume{ get; };

        /// @see https://learn.microsoft.com/uwp/api/windows.management.deployment.packagevolume.mountpoint
        String MountPoint{ get; };

        /// @see https://learn.microsoft.com/uwp/api/windows.management.deployment.packagevolume.name
        String Name{ get; };

        /// @see https://learn.microsoft.com/uwp/api/windows.management.deployment.packagevolume.packagestorepath
        String PackageStorePath{ get; };

        /// @see https://learn.microsoft.com/uwp/api/windows.management.deployment.packagevolume.supportshardlinks
        Boolean SupportsHardLinks{ get; };

        /// @see https://learn.microsoft.com/uwp/api/windows.management.deployment.packagevolume.isfulltrustpackagesupported
        Boolean IsFullTrustPackageSupported{ get; };

        /// @see https://learn.microsoft.com/uwp/api/windows.management.deployment.packagevolume.isappxinstallsupported
        Boolean IsAppxInstallSupported{ get; };

        /// Return true if the package volume is OK, else false if it needs to be repaired.
        bool VerifyIfOK();

        /// Repair the package volume (if necessary).
        void Repair();
    };

    /// Manages the storage volumes where packages can be installed.
    /// @see https://learn.microsoft.com/uwp/api/windows.management.deployment.packagevolume
    [feature(Feature_PackageManager)]
    [contract(PackageDeploymentContract, 1)]
    runtimeclass PackageVolumeManager
    {
        /// Gets all the known volumes, regardless of their current state.
        /// @see https://learn.microsoft.com/en-us/uwp/api/windows.management.deployment.packagemanager.findpackagevolumes
        static IVector<PackageVolume> FindPackageVolumes();

        /// Get the specified volume.
        /// @see https://learn.microsoft.com/en-us/uwp/api/windows.management.deployment.packagemanager.findpackagevolume
        static PackageVolume FindPackageVolumeByPath(String path);

        /// Get the specified volume.
        /// @see https://learn.microsoft.com/en-us/uwp/api/windows.management.deployment.packagemanager.findpackagevolume
        static PackageVolume FindPackageVolumeByMediaId(String mediaId);

        /// Get the specified volume.
        /// @see https://learn.microsoft.com/en-us/uwp/api/windows.management.deployment.packagemanager.findpackagevolume
        static PackageVolume FindPackageVolumeByName(String name);
    };

    /// The progress status of the deployment request.
    /// @see https://learn.microsoft.com/en-us/uwp/api/windows.management.deployment.deploymentprogress.state?view=winrt-22621
    [contract(PackageDeploymentContract, 1)]
    enum PackageDeploymentProgressStatus
    {
        Queued = 0,             // The request is queued
        InProgress = 1,         // The request is in progress
        CompletedSuccess = 2,   // The request completed successfully
        CompletedFailure = 3,   // The request failed with some critical internal error.
    };

    /// Contains progress information for the deployment request.
    /// https://learn.microsoft.com/en-us/uwp/api/windows.management.deployment.deploymentprogress?view=winrt-22621
    [contract(PackageDeploymentContract, 1)]
    runtimeclass PackageDeploymentProgress
    {
        PackageDeploymentProgressStatus status;

        /// The progress percentage of the deployment request.
        /// @note This is a double with values 0.0-1.0. Windows.Management.Deployment.DeploymentProgress.percentage is uint32 with values 0-100.
        Double percentage;
    }

    /// The status of the deployment request.
    /// @see PackageDeploymentResult.Status
    [contract(PackageDeploymentContract, 1)]
    enum PackageDeploymentStatus
    {
        InProgress = 0,         // The request is in progress
        CompletedSuccess = 1,   // The request completed successfully
        CompletedFailure = 2,   // The request failed with some critical internal error.
    };

    // Provides the result of a deployment request.
    // @see https://learn.microsoft.com/en-us/uwp/api/windows.management.deployment.deploymentresult
    [contract(PackageDeploymentContract, 1)]
    runtimeclass PackageDeploymentResult
    {
        PackageDeploymentStatus Status { get; };
        HRESULT ExtendedError { get; };
        Boolean IsRegistered{ get; };
        Guid ActivityId { get; };
    }

    /// Defines the stub behavior for an app package that is being added or staged.
    /// @see https://learn.microsoft.com/en-us/uwp/api/windows.management.deployment.stubpackageoption?view=winrt-22621
    [contract(PackageDeploymentContract, 1)]
    enum StubPackageOption
    {
        Default,
        InstallFull,
        InstallStub,
        UsePreference,
    };
}
```
