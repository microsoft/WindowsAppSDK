# 1. MSIX Package Management

This feature provides package management APIs comparable to those in namespace
[Windows.Management.Deployment](https://learn.microsoft.com/uwp/api/windows.management.deployment)
but with additional functionality, improved developer experience and performance optimizations.

- [1. MSIX Package Management](#1-msix-package-management)
- [2. Background](#2-background)
- [3. Description](#3-description)
  - [3.1. API Structure](#31-api-structure)
  - [3.2. Is\*Ready()](#32-isready)
  - [3.3. Is\*ReadyOrNewerAvailable()](#33-isreadyorneweravailable)
  - [3.4. Ensure\*Ready()](#34-ensureready)
    - [3.4.1. Why Is\*Ready() Given Ensure\*Ready()?](#341-why-isready-given-ensureready)
    - [3.4.2. EnsureReadyOptions.RegisterNewerIfAvailable](#342-ensurereadyoptionsregisternewerifavailable)
  - [3.5. Repair](#35-repair)
  - [3.6. Reset](#36-reset)
  - [3.7. IsPackageRegistrationPending](#37-ispackageregistrationpending)
  - [3.8. PackageSet](#38-packageset)
    - [3.8.1. PackageSet Properties](#381-packageset-properties)
    - [3.8.2. PackageSetItem Properties](#382-packagesetitem-properties)
  - [3.9. PackageRuntimeManager](#39-packageruntimemanager)
  - [3.10. PackageVolume Repair](#310-packagevolume-repair)
  - [3.11. Usability](#311-usability)
  - [3.12. Is\*Provisioned()](#312-312-isprovisioned)
- [4. Examples](#4-examples)
  - [4.1. AddPackageAsync()](#41-addpackageasync)
  - [4.2. AddPackageByUriAsync()](#42-addpackagebyuriasync)
  - [4.3. AddPackageSetAsync()](#43-addpackagesetasync)
  - [4.4. EnsurePackageSetReadyAsync()](#44-ensurepackagesetreadyasync)
  - [4.5. IsPackageSetReady() and EnsurePackageSetReadyAsync()](#45-ispackagesetready-and-ensurepackagesetreadyasync)
  - [4.6. PackageRuntimeManager.AddPackageSet()](#46-packageruntimemanageraddpackageset)
  - [4.7. PackageRuntimeManager.RemovePackageset()](#47-packageruntimemanagerremovepackageset)
  - [4.8. PackageVolume.Repair()](#48-packagevolumerepair)
  - [4.9. IsPackageProvisioned()](#49-ispackageprovisioned)
- [5. Remarks](#5-remarks)
  - [5.1. Platform Support](#51-platform-support)
- [6. API Details](#6-api-details)

# 2. Background

Windows supports the ability to deploy and manage software as MSIX packages via WinRT APIs in the
Windows.Management.Deployment namespace. These APIs provide the means to install, update, uninstall,
enumerate and otherwise manage packages.

The package management APIs were originally introduced in Windows 8 and have continuously expanded
to meet MSIX's growing demands over the past decade. However, as one of the earliest WinRT APIs they
include some patterns out of step with current API practices and recommendations. Windows App SDK
offers the opportunity to provide a new generation of package management APIs in line with the
latest patterns and recommendations for an improved developer experience as well as functional
enhancements and improved runtime efficiencies.

Microsoft-internal task [45952398](https://task.ms/45952398)

# 3. Description

This API provides enhanced access to Windows' package management capabilities, focusing on the
following scenarios:

* Stage a package
* Register a package
* Add/Update a package
* Remove a package
* Repair a package
* Reset a package
* Provision a package
* Deprovision a package

Additional functionality includes:

* IsReady* -- Is a package ready for use?
* EnsureReady -- Is a package ready for use and, if not, make it so
* IsPackageRegistrationPending -- Is there an update waiting to register?
* PackageSets -- Batch operations
* PackageRuntimeManager -- Batch operations for use at runtime via Dynamic Dependencies
* Usability -- Quality-of-Life enhancements

## 3.1. API Structure

Methods to drive deployment activity typically follow the pattern:

    <verb>Package[Set][By<Type>][Suffix]Async(target, options)

The following verbs are supported:

* Is...Ready[OrNewerAvailable]
* Ensure...Ready
* Add
* Stage
* Register
* Remove
* Repair
* Reset
* Provision
* Deprovision

These methods accept their target package(s) as their first parameter. This parameter can be an
various types of information including:

* Filename
* Path
* PackageFamilyName
* PackageFullName
* Uri

**NOTE:** Methods with a target of a URI are named ...ByUri....

**NOTE:** Methods with a target of a PackageFamilyName are named ...ByPackageFamilyName....

**NOTE:** Methods with a target of a PackageFullName are named ...ByPackageFullName....

**NOTE:** Methods with no ...By<Type>... qualifier accept a string which can contain one or more types
of identifiers. These can vary for different verbs. See the per-method documentation for the
specific target types supported by each method.

These methods accept options as a matching `<verb>Package[Set]Options` type, e.g.
`AddPackageAsync(string packageUri, AddPackageOptions options)`.

The following table shows the supported permutations of verbs and targets:

|Verb                    | Path   | Filename | PackageFamilyName | PackageFullName | file:  | http(s): | ms-uup: | PackageSet |
|------------------------|:------:|:--------:|:-----------------:|:---------------:|:------:|:--------:|:-------:|:----------:|
|IsReady                 |   X    |    X     |       OS/WAS      |       WAS       |   X    |    X     |  WAS    |    WAS     |
|IsReadyOrNewerAvailable |   X    |    X     |       OS/WAS      |       WAS       |   X    |    X     |  WAS    |    WAS     |
|EnsureReady             |   X    |    X     |         X         |        X        |   X    |    X     |  WAS    |    WAS     |
|Add                     | OS/WAS |    X     |         X         |        X        | OS/WAS |  OS/WAS  | OS/WAS  |    WAS     |
|Stage                   | OS/WAS |    X     |         X         |        X        | OS/WAS |  OS/WAS  | OS/WAS  |    WAS     |
|Register                |  WAS   |  OS/WAS  |       OS/WAS      |      OS/WAS     | OS/WAS |    X     | OS/WAS  |    WAS     |
|Remove                  |   X    |    X     |        WAS        |      OS/WAS     |   X    |    X     | OS/WAS  |    WAS     |
|Repair                  |   X    |    X     |        WAS        |       WAS       |   X    |    X     |  WAS    |    WAS     |
|Reset                   |   X    |    X     |        WAS        |       WAS       |   X    |    X     |  WAS    |    WAS     |
|IsProvisioned           |   X    |    X     |       OS/WAS      |        X        |   X    |    X     |  WAS    |    WAS     |
|Provision               |   X    |    X     |       OS/WAS      |        X        |   X    |    X     |  WAS    |    WAS     |
|Deprovision             |   X    |    X     |       OS/WAS      |        X        |   X    |    X     |  WAS    |    WAS     |

Legend:

* **OS** = Supported by Windows (OS) APIs in the Windows.Management.Deployment.PackageManager namespace.
* **WAS** = Supported by Windows App SDK APIs in the
  Microsoft.Windows.Management.Deployment.PackageDeploymentManager namespace.
* **X** = Not supported

## 3.2. Is\*Ready()

Is\*Ready() methods determine if the target is installed (registered) and ready for use. Reasons why
a package is not ready can include:

* The package is not present on the machine
* The package is present on the machine but not registered for the user
* The package is registered for the user but is not in a healthy status e.g. its
  Package.Status=Tampered

Is\*Ready() methods are a quick test to determine if more (costly) work is needed before the target
can be used.

## 3.3. Is\*ReadyOrNewerAvailable()

Is\*ReadyOrNewerAvailable() methods determine if the target is installed (registered) and ready for
use AND if a newer version is locally available. Reasons why a package is ready but a newer version
is available can include:

* The package is registered for the user but a newer version is available locally on the machine
  e.g. a user has package v1 registered and Windows Update downloaded and staged v2 in the
  background while app(s) are running using v1.

Is\*ReadyOrNewerAvailable() methods are a quick test to determine if more (costly) work is needed
before the target can be used.

**NOTE:** Is\*ReadyOrNewerAvailable() can only determine a newer package is available than a package
installed (registered) and ready for use. If Is\*Ready() returns `false` then
Is\*ReadyOrNewerAvailable() will never return `NewerAvailable`.

**NOTE:** Is\*ReadyOrNewerAvailable() does not require admin privilege.
[PackageManager.FindPackages](https://learn.microsoft.com/en-us/uwp/api/windows.management.deployment.packagemanager.findpackages?view=winrt-22621)()
and
[PackageManager.FindPackagesForUser](https://learn.microsoft.com/en-us/uwp/api/windows.management.deployment.packagemanager.findpackagesforuser?view=winrt-22621)(user!=currentuser...)
can enumerate packages regardless if staged or registered for the user but requires admin privilege.

## 3.4. Ensure\*Ready()

Ensure\*Ready() methods determine if the target is installed and ready for use and, if not, makes
it so. This can include downloading the target, registering it for the user and remediating a
package in an unhealthy state.

Thus `EnsurePackageReady(pkg, options)` is functionally equivalent to

```c#
var pdm = PackageDeploymentManager().GetDefault();
if (!pdm.IsPackageReady(pkg))
{
    var result = await pdm.AddPackageAsync(pkg, options);
}
```

### 3.4.1. Why Is\*Ready() Given Ensure\*Ready()?

Ensure\*Ready() performs an 'is ready' check and returns if all is ready. There's no efficiency
reasons to call Is\*Ready() before Ensure\*Ready() (in fact, it's less efficient as Is\*Ready() would
occur twice).

However, this can be useful if you need additional work before potentially performing deployment
operations. For example, if you need to prompt the user for consent before installing the target
e.g.

```c#
var pdm = PackageDeploymentManager().GetDefault();
if (!pdm.IsPackageReady(pkg))
{
    bool ok = AskUserForConsent(pkg);
    if (ok)
    {
        var options = new EnsureReadyOptions();
        var result = await pdm.EnsurePackageReadyAsync(pkg, options);
    }
}
```

### 3.4.2. EnsureReadyOptions.RegisterNewerIfAvailable

Ensure\*Ready() performs an 'is ready' check via Is*ReadyOrNewerAvailable() if
`EnsureReadyOptions.RegisterNewerIfAvailable = true`.

There's no efficiency reasons to call Is\*ReadyOrNewerAvailable() before
Ensure\*Ready(...options.RegisterNewerIfAvailable=true) (in fact, it's
less efficient as Is\*ReadyOrNewerAvailable() would occur twice).

However, this can be useful if you need additional work before potentially performing deployment
operations. For example, if you need to prompt the user for consent before registering
('installing') or updating the package e.g.

```c#
var pdm = PackageDeploymentManager().GetDefault();
var status = pdm.IsPackageReadyOrNewerAvailable(pkg);
if (status != PackageReadyOrNewerAvailableStatus.Ready)
{
    bool ok = AskUserForConsent(pkg, status);
    if (ok)
    {
        var options = new EnsureReadyOptions();
        options.RegisterNewerIfAvailable = true;
        var result = await pdm.EnsurePackageReadyAsync(pkg, options);
    }
}
```

## 3.5. Repair

`PackageDeploymentManager` offers Repair APIs providing the same functionality as available
interactively via Settings' `Repair` button on the detail page for an app (via Apps &gt; Installed
Apps &gt; ... menu's Advanced options).

## 3.6. Reset

`PackageDeploymentManager` offers Reset APIs providing the same functionality as available
interactively via Settings' `Reset` button on the detail page for an app (via Apps &gt; Installed
Apps &gt; ... menu's Advanced options).

## 3.7. IsPackageRegistrationPending

`IsPackageRegistrationPending()` detects if package registration is pending for the specified target. For
example, if a package is in use and `AddPackageByUriAsync()` is called with a newer version and the
option
[DeferRegistrationWhenPackagesAreInUse](https://learn.microsoft.com/uwp/api/windows.management.deployment.addpackageoptions.deferregistrationwhenpackagesareinuse)=`true`
then the registration is delayed until the package is no longer in use and can be updated. In such
cases `IsPackageRegistrationPending()` returns `true`.

##  3.8. PackageSet

A `PackageSet` is a group of packages to be operated on with one request. Package sets provide a
convenient means to perform multiple operations.

NOTE: There is no ordering guarantee of items processed in a PackageSet.

For example, `IsPackageSetReady(ps)` returns `true` only if all packages referenced by the
`PackageSet` are ready for use. For another example, `AddPackageSetAsync(ps, options)` is
functionally equivalent to

```c#
var pdm = PackageDeploymentManager().GetDefault();
foreach (PackageSetItem psi in ps.Items)
{
    var result = await pdm.AddPackageAsync(psi.PackageUri, options)
    if (result.Status != PackageDeploymentStatus.CompletedSuccess)
    {
        return result;
    }
}
return new PackageDeploymentResult(PackageDeploymentStatus.CompletedSuccess);
```

### 3.8.1. PackageSet Properties

`Id` is optional. This is used primarily for logging and troubleshooting.

`Items` is required to contain 1+ item.

`PackageUri` is optional. This is used if a `PackageUri` is needed for a `PackageSetItem` but the
`PackageSetItem.PackageUri` is not specified.

### 3.8.2. PackageSetItem Properties

`Id` is required and used primarily for logging and troubleshooting.

`MinVersion` is optional. If not set the default value is 0.0.0.0. Some verbs use this property (see below).

`PackageFamilyName` is optional. Some verbs require this property (see below).

`PackageUri` is optional. If a `PackageUri` is needed and this is not set the `PackageSet`'s `PackageUri` property is used. Some verbs require this property (see below).

`ProcessorArchitectureFilter` is optional. If not set the default value is `Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyProcessorArchitectures.None`. Only some verbs use this property (see below).

|Verb                    | MinVersion |     PackageFamilyName     | PackageUri | ProcessorArchitectureFilter |
|------------------------|:----------:|:-------------------------:|:----------:|:---------------------------:|
|IsReady                 |    Used    |          Required         |    N/A     |           Optional          |
|IsReadyOrNewerAvailable |    Used    |          Required         |    N/A     |           Optional          |
|EnsureReady             |    Used    |          Required         |    Used    |           Optional          |
|Add                     |    N/A     |            N/A            |    Used    |             N/A             |
|Stage                   |    N/A     |            N/A            |    Used    |             N/A             |
|Register                |    N/A     |   Used-if-no-PackageUri   |  Optional  |             N/A             |
|Remove                  |    N/A     |   Used-if-no-PackageUri   |  Optional  |             N/A             |
|Repair                  |    N/A     |   Used-if-no-PackageUri   |  Optional  |             N/A             |
|Reset                   |    N/A     |   Used-if-no-PackageUri   |  Optional  |             N/A             |
|IsProvisioned           |    N/A     |            Used           |  Optional  |             N/A             |
|Provision               |    N/A     |   Used-if-no-PackageUri   |  Optional  |             N/A             |
|Deprovision             |    N/A     |   Used-if-no-PackageUri   |  Optional  |             N/A             |

**Legend:**

* **N/A** = Not applicable. This property is not used.
* **Optional** = This property is used, if specified.
* **Required** = This property is required.
* **Used** = This property is used; if not specified, the default value is used.

## 3.9. PackageRuntimeManager

The `PackageRuntimeManager` API provides Dynamic Dependency support for PackageSet operations,
especially when the caller may not know the exact package(s) involved (for instance, when targeting
packages via `ms-uup:`). `PackageRuntimeManager` determines the packages involved for a `PackageSet`
and dynamically adds them to the caller's package graph.

## 3.10. PackageVolume Repair

Packages are typically<sup>1</sup> installed to a
[PackageVolume](https://learn.microsoft.com/uwp/api/windows.management.deployment.packagevolume),
For example, `C:\Program Files\WindowsApps` is the default `PackageVolume` on a new Windows system.

Windows pairs a `PackageVolume` with the underlying storage volume's media ID to identify the
PackageVolume even when mount points change. For example, insert USB flash key and it's mount point
is E:, then remove the USB flash key and later reinsert it but now it's mounted as K:. The
`PackageVolume` is recognized at K: now because it volume K: has the media ID associated with the
`PackageVolume`.

It's possible this tracking information can be invalidated, e.g. backup a drive's content, replace
the drive with a new one and then restore the content. The packages installed on this drive's
PackageVolume(s) aren't recognized by Windows because the new drive has a different media ID.

The Windows App SDK's new `PackageVolume.Repair()` will attempt to detect these and other like
conditions and correct them.

`PackageVolume.IsRepairNeeded()` checks if the PackageVolume is OK or in need of repair.

**NOTE:** `Repair()` requires admin privilege (`IsRepairNeeded()` doesn't).

<sup>1</sup>
[RegisterPackageOptions.DevelopmentMode](https://learn.microsoft.com/uwp/api/windows.management.deployment.registerpackageoptions.developermode),
[AddPackageOptions.StageInPlace](https://learn.microsoft.com/uwp/api/windows.management.deployment.registerpackageoptions.stageinplace)
and other options canalter the typical behavior and install packages to a non-PackageVolume
location.

## 3.11. Usability

The package management API in Windows App SDK provides several quality-of-life enhancements over the
package management APIs in Windows (e.g. Windows.Management.Deployment.PackageManager) including:

* `PackageManager.AddPackageByUriAsync(p)` fails returning `ERROR_INSTALL_PACKAGE_DOWNGRADE` if a newer
  version of the package is already installed. `PackageDeploymentManager` succeeds as it treats the
  request as "install this package *or higher version*", as dependencies and other package
  references are routinely handled.
* `PackageManager.AddPackageByUriAsync(p)` fails returning `ERROR_PACKAGE_ALREADY_EXISTS` if that
  exact version of the package is already installed. `PackageDeploymentManager` succeeds as the
  requested package is installed.
* Many `PackageManager` operations accept a target package as a file but require it expressed as a
  `Uri`. `PackageDeploymentManager` provides overrides also accepting it as a `String`.
* `PackageManager.RemovePackageByFullNameAsync(p)` fails if the specified package isn't found.
  `PackageDeploymentManager` succeeds as the requested package is not present at the end of the
  operation.
  * This follows the core deployment principle "'Tis not the journey that matters but the
    destination". In short, it doesn't matter the current state of the system, only the desired end
    state is achieved.
* `PackageManager` methods accept inconsistent (and often inconvenient) permutations of expressing a
  target package. For example, `PackageManager` supports removing a package by PackageFullName but
  not PackageFamilyName. `PackageDeploymentManager` provides a richer API accepting additional
  identifiers.

## 3.12. Is*Provisioned()

Is\*Provisioned\*() methods determine if the target is provisioned.

These methods require administrative privileges.

# 4. Examples

## 4.1. AddPackageAsync()

Fabrikam app installing Contoso's Muffin package from a .msix file.

```c#
void Install()
{
    var package = "d:\\contoso\\muffin.msix";
    var packageDeploymentManager = PackageDeploymentManager.GetDefault();
    var options = new AddPackageOptions();
    var deploymentResult = await packageDeploymentManager.AddPackageAsync(package, options);
    if (deplymentResult.Status == PackageDeploymentStatus.CompletedSuccess)
    {
        Console.WriteLine("OK");
    }
    else
    {
        Console.WriteLine("Error:{} ExtendedError:{} {}",
            deploymentResult.Error.HResult, deploymentResult.ExtendedError.HResult, deploymentResult.ErrorText);
    }
}
```

## 4.2. AddPackageByUriAsync()

Fabrikam app installing Contoso's Muffin package from an https: source.

```c#
void Install()
{
    var package = new Uri("https://contoso.com/muffin.msix");
    var packageDeploymentManager = PackageDeploymentManager.GetDefault();
    var options = new AddPackageOptions();
    var deploymentResult = await packageDeploymentManager.AddPackageByUriAsync(package, options);
    if (deplymentResult.Status == PackageDeploymentStatus.CompletedSuccess)
    {
        Console.WriteLine("OK");
    }
    else
    {
        Console.WriteLine("Error:{} ExtendedError:{} {}",
            deploymentResult.Error.HResult, deploymentResult.ExtendedError.HResult, deploymentResult.ErrorText);
    }
}
```

**NOTE:** This differs from the AddPackageAsync() example by the method name
(`AddPackageByUriAsync()` instead of `AddPackageAsync()`) and the target type (https: source as URI
instead of filename as string).

## 4.3. AddPackageSetAsync()

Fabrikam app installing Contoso's Muffin and Waffle packages via a PackageSet.

```c#
void Install()
{
    var packageSet = new PackageSet() {
        Items = { new PackageSetItem() { PackageUri = new Uri("c:\\contoso\\muffin-1.2.3.4.msix") },
                { new PackageSetItem() { PackageUri = new Uri("https://contoso.com/waffle-2.4.6.8.msix") } };

    var packageDeploymentManager = PackageDeploymentManager.GetDefault();
    var options = new AddPackageOptions();
    var deploymentResult = await packageDeploymentManager.AddPackageByUriAsync(packageSet, options);
    if (deplymentResult.Status == PackageDeploymentStatus.CompletedSuccess)
    {
        Console.WriteLine("OK");
    }
    else
    {
        Console.WriteLine("Error:{} ExtendedError:{} {}",
            deploymentResult.Error.HResult, deploymentResult.ExtendedError.HResult, deploymentResult.ErrorText);
    }
}
```

**NOTE:** This differs from the AddPackageByUriAsync() example by the method name
(`AddPackageSetAsync` instead of `AddPackageByUriAsync()`), the target type (`PackageSet` containing
2 URIs instead of a URI), and installing 2 packages instead of 1.

## 4.4. EnsurePackageSetReadyAsync()

Fabrikam app installing Contoso's Muffin and Waffle packages if necessary via a PackageSet.

```c#
void Install()
{
    var packageSet = new PackageSet() {
        Items = { new PackageSetItem() { PackageFamilyName = "contoso.muffin_1234567890abc",
                                         MinVersion = ToVersion(1, 2, 3, 4),
                                         PackageUri = new Uri("c:\\contoso\\muffin-1.2.3.4.msix") },
                { new PackageSetItem() { PackageFamilyName = "contoso.waffle_1234567890abc",
                                         MinVersion = ToVersion(2, 4, 6, 8),
                                         PackageUri = new Uri("https://contoso.com/waffle-2.4.6.8.msix") } };

    var packageDeploymentManager = PackageDeploymentManager.GetDefault();
    var options = new EnsureReadyOptions();
    var deploymentResult = await packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options);
    if (deplymentResult.Status == PackageDeploymentStatus.CompletedSuccess)
    {
        Console.WriteLine("OK");
    }
    else
    {
        Console.WriteLine("Error:{} ExtendedError:{} {}",
            deploymentResult.Error.HResult, deploymentResult.ExtendedError.HResult, deploymentResult.ErrorText);
    }
}

PackageVersion ToVersion(uint major, uint minor, uint build, uint revision) =>
    new PackageVersion {
        Major = checked((ushort)major),
        Minor = checked((ushort)minor),
        Build = checked((ushort)build),
        Revision = checked((ushort)revision)
    };
```

**NOTE:** This differs from the AddPackageBySetAsync() example by the method name
(`EnsurePackageSetReadyAsync()` instead of `AddPackageSetAsync`), the addition of
PackageFamilyName and MinVersion for each item in the `PackageSet` and the packages will only be
installed if necessary.

## 4.5. IsPackageSetReady() and EnsurePackageSetReadyAsync()

Fabrikam app installing Contoso's Muffin and Waffle packages if necessary, and with explicit user
confirmation before the installation.

```c#
void Install()
{
    var packageSet = new PackageSet() {
        Items = { new PackageSetItem() { PackageFamilyName = "contoso.muffin_1234567890abc",
                                         MinVersion = ToVersion(1, 2, 3, 4),
                                         PackageUri = new Uri("c:\\contoso\\muffin-1.2.3.4.msix") },
                { new PackageSetItem() { PackageFamilyName = "contoso.waffle_1234567890abc",
                                         MinVersion = ToVersion(2, 4, 6, 8),
                                         PackageUri = new Uri("https://contoso.com/waffle-2.4.6.8.msix") } };

    var packageDeploymentManager = PackageDeploymentManager.GetDefault();
    if (!packageDeploymentManager.IsPackageSetReady(packageSet))
    {
        bool ok = PromptUserForConfirmation();
        if (!ok)
        {
            return;
        }
    }

    var options = new EnsureReadyOptions();
    var deploymentResult = await packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options);
    if (deplymentResult.Status == PackageDeploymentStatus.CompletedSuccess)
    {
        Console.WriteLine("OK");
    }
    else
    {
        Console.WriteLine("Error:{} ExtendedError:{} {}",
            deploymentResult.Error.HResult, deploymentResult.ExtendedError.HResult, deploymentResult.ErrorText);
    }
}

PackageVersion ToVersion(uint major, uint minor, uint build, uint revision) =>
    new PackageVersion {
        Major = checked((ushort)major),
        Minor = checked((ushort)minor),
        Build = checked((ushort)build),
        Revision = checked((ushort)revision)
    };
```

**NOTE:** This differs from the EnsurePackageSetReadyAsync() example checking if
`EnsurePackageSetReadyAsync()` will need to do any work and prompting the user to confirm it's OK
to proceed.

## 4.6. PackageRuntimeManager.AddPackageSet()

Fabrikam app uses Contoso's Muffin and Waffle packages via Dynamic Dependencies, installing them if
necessary. These packages are added to the package graph and not explicitly removed (they stay in
the package graph until process termination).

```c#
void AddMuffinsAndWafflesToThePackageGraph()
{
    var packageSet = new PackageSet() {
        Items = { new PackageSetItem() { PackageFamilyName = "contoso.muffin_1234567890abc",
                                         MinVersion = ToVersion(1, 2, 3, 4),
                                         PackageUri = new Uri("c:\\contoso\\muffin-1.2.3.4.msix") },
                { new PackageSetItem() { PackageFamilyName = "contoso.waffle_1234567890abc",
                                         MinVersion = ToVersion(2, 4, 6, 8),
                                         PackageUri = new Uri("https://contoso.com/waffle-2.4.6.8.msix") } };

    var packageDeploymentManager = PackageDeploymentManager.GetDefault();
    var options = new EnsureReadyOptions();
    var deploymentResult = await packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options);
    if (deplymentResult.Status == PackageDeploymentStatus.CompletedSuccess)
    {
        Console.WriteLine("OK");
    }
    else
    {
        Console.WriteLine("Error:{} ExtendedError:{} {}",
            deploymentResult.Error.HResult, deploymentResult.ExtendedError.HResult, deploymentResult.ErrorText);
    }

    var packageRuntimeManager = PackageRuntimeManager.GetDefault();
    var packageSetRuntimeDisposition = packageRuntimeManager.AddPackageSet(packageSet);
}

PackageVersion ToVersion(uint major, uint minor, uint build, uint revision) =>
    new PackageVersion {
        Major = checked((ushort)major),
        Minor = checked((ushort)minor),
        Build = checked((ushort)build),
        Revision = checked((ushort)revision)
    };
```

**NOTE:** This differs from the EnsurePackageSetReadyAsync() example adding the packages
referenced by the `PackageSet` to the process' package graph for subsequent access of the content.

## 4.7. PackageRuntimeManager.RemovePackageset()

Fabrikam app uses Contoso's Muffin and Waffle packages via Dynamic Dependencies, installing them if
necessary. These packages are added to the package graph and later removed when no longer needed.

```c#
void DoAwesomeStuffUsingMuffinsAndWaffles()
{
    var packageSet = new PackageSet() {
        Items = { new PackageSetItem() { PackageFamilyName = "contoso.muffin_1234567890abc",
                                         MinVersion = ToVersion(1, 2, 3, 4),
                                         PackageUri = new Uri("c:\\contoso\\muffin-1.2.3.4.msix") },
                { new PackageSetItem() { PackageFamilyName = "contoso.waffle_1234567890abc",
                                         MinVersion = ToVersion(2, 4, 6, 8),
                                         PackageUri = new Uri("https://contoso.com/waffle-2.4.6.8.msix") } };

    var packageDeploymentManager = PackageDeploymentManager.GetDefault();
    var options = new EnsureReadyOptions();
    var deploymentResult = await packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options);
    if (deplymentResult.Status == PackageDeploymentStatus.CompletedSuccess)
    {
        Console.WriteLine("OK");
    }
    else
    {
        Console.WriteLine("Error:{} ExtendedError:{} {}",
            deploymentResult.Error.HResult, deploymentResult.ExtendedError.HResult, deploymentResult.ErrorText);
    }

    var packageRuntimeManager = PackageRuntimeManager.GetDefault();
    var packageSetRuntimeDisposition = packageRuntimeManager.AddPackageSet(packageSet);
    DoAwesomeStuff();
    packageRuntimeManager.RemovePackageSet(packageSetRuntimeDisposition);
}

PackageVersion ToVersion(uint major, uint minor, uint build, uint revision) =>
    new PackageVersion {
        Major = checked((ushort)major),
        Minor = checked((ushort)minor),
        Build = checked((ushort)build),
        Revision = checked((ushort)revision)
    };
```

**NOTE:** This differs from the PackageRuntimeManager.AddPackageSet()() example by explicitly
removing the packages dynamically added to the package graph when no longer needed.

## 4.8. PackageVolume.Repair()

Fabrikam app checks if a PackageVolume is OK and if not, prompts the user to confirm it should
proceed to repair the PackageVolume.

```c#
void CheckAndFixPackageVolume(string packageStorePath)
{
    var packageVolume = PackageVolume.FindPackageVolumeByPath(packageStorePath);
    if (packageVolume.IsRepairNeeded())
    {
        bool ok = PromptUserForConfirmation();
        if (!ok)
        {
            return;
        }
    }
    packageVolume.Repair();
}
```

## 4.9. IsPackageProvisioned()

Fabrikam app installing Contoso's Muffin and Waffle packages for all users if necessary, and with explicit user confirmation before the installation.

```c#
void Install()
{
    // We want to check what's provisioned by PackageFamilyName. If something's
    // not provisioned we'll also need MinVersion and PackageUri to Stage and
    // Provision. But checking if a family is provisioned only supports some
    // URI schemes (notably, not the one we need for our staging work). So we'll
    // define the PackageSet with the families we want checked and if something's
    // not provisioned we'll add the additional properties needed.

    var packageSet = new PackageSet() {
        Items = { new PackageSetItem() { PackageFamilyName = "contoso.muffin_1234567890abc" },
                { new PackageSetItem() { PackageFamilyName = "contoso.waffle_1234567890abc" }
        }
    };

    var packageDeploymentManager = PackageDeploymentManager.GetDefault();
    if (packageDeploymentManager.IsPackageSetProvisioned(packageSet))
    {
        return;
    }

    bool ok = PromptUserForConfirmation();
    if (!ok)
    {
        return;
    }

    packageSet.Items()[0].MinVersion(ToVersion(1, 2, 3, 4));
    packageSet.Items()[0].PackageUri(new Uri("c:\\contoso\\muffin-1.2.3.4.msix"));
    packageSet.Items()[1].MinVersion(ToVersion(2, 4, 6, 8));
    packageSet.Items()[1].PackageUri(new Uri("https://contoso.com/waffle-2.4.6.8.msix"));

    var stageOptions = new StagePackageOptions();
    var deploymentResult = await packageDeploymentManager.StagePackageSetReadyAsync(packageSet, options);
    if (deplymentResult.Status == PackageDeploymentStatus.CompletedSuccess)
    {
        Console.WriteLine("Staged");
    }
    else
    {
        Console.WriteLine("Error:{} ExtendedError:{} {}",
            deploymentResult.Error.HResult, deploymentResult.ExtendedError.HResult, deploymentResult.ErrorText);
        return;
    }

    var options = new ProvisionPackageOptions();
    var deploymentResult = await packageDeploymentManager.ProvisionPackageSetReadyAsync(packageSet, options);
    if (deplymentResult.Status == PackageDeploymentStatus.CompletedSuccess)
    {
        Console.WriteLine("Provisioned");
    }
    else
    {
        Console.WriteLine("Error:{} ExtendedError:{} {}",
            deploymentResult.Error.HResult, deploymentResult.ExtendedError.HResult, deploymentResult.ErrorText);
    }
}

PackageVersion ToVersion(uint major, uint minor, uint build, uint revision) =>
    new PackageVersion {
        Major = checked((ushort)major),
        Minor = checked((ushort)minor),
        Build = checked((ushort)build),
        Revision = checked((ushort)revision)
    };
```

# 5. Remarks

## 5.1. Platform Support

This API is only available on Windows >= 10.0.19041.0 (aka 2004 aka 20H1).

A subset of functionality is available on newer releases, e.g. `AddPackageOptions.ExpectedDigests`
requires Windows >= 10.0.22621.0 (aka Win11 22H2). Any
functionality requiring newer releases of windows than then 20H1 baseline has affordances to detect at runtime if the current platform supports the feature e.g.

```c#
var options = new AddPackageOptions();
if (options.IsLimitToExistingPackagesSupported)
{
    options.LimitToExistingPackages = true;
}
```

# 6. API Details

```c# (but really MIDL3)
namespace Microsoft.Windows.Management.Deployment
{
    [contractversion(2)]
    apicontract PackageDeploymentContract{};

    /// Represents a package storage volume.
    /// @note A volume 'name' is the volume's media ID (you can treat 'Volume Name' == 'Volume Media ID').
    /// @see https://learn.microsoft.com/uwp/api/windows.management.deployment.packagevolume
    /// @see https://learn.microsoft.com/windows/win32/properties/props-system-volumeid
    /// @see https://learn.microsoft.com/sysinternals/downloads/volumeid
    /// @see https://learn.microsoft.com/windows/win32/api/fileapi/nf-fileapi-getvolumenameforvolumemountpointw
    [contract(PackageDeploymentContract, 1)]
    runtimeclass PackageVolume
    {
        /// Gets all the known volumes, regardless of their current state.
        /// @see https://learn.microsoft.com/uwp/api/windows.management.deployment.packagemanager.findpackagevolumes
        static IVector<PackageVolume> FindPackageVolumes();

        /// Get the specified volume.
        /// @see https://learn.microsoft.com/uwp/api/windows.management.deployment.packagemanager.findpackagevolume
        static PackageVolume FindPackageVolumeByPath(String packageStorePath);

        /// Get the specified volume.
        /// @name The volume media ID (a GUID value)
        /// @see https://learn.microsoft.com/uwp/api/windows.management.deployment.packagemanager.findpackagevolume
        static PackageVolume FindPackageVolumeByName(String name);

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

        /// Return true if the package volume is damaged and needs to be repaired.
        Boolean IsRepairNeeded();

        /// Repair the package volume (if necessary).
        void Repair();
    };

    /// Defines the stub behavior for an app package that is being added or staged.
    /// @see https://learn.microsoft.com/uwp/api/windows.management.deployment.stubpackageoption
    [contract(PackageDeploymentContract, 1)]
    enum StubPackageOption
    {
        Default,
        InstallFull,
        InstallStub,
        UsePreference,
    };

    /// Defines the stub behavior for an app package that is being added or staged.
    [contract(PackageDeploymentContract, 2)]
    enum PackageReadyOrNewerAvailableStatus
    {
        NotReady             = 0,
        Ready                = 1,
        NewerAvailable       = 2,
    };

    /// The progress status of the deployment request.
    /// @see https://learn.microsoft.com/uwp/api/windows.management.deployment.deploymentprogress.state
    [contract(PackageDeploymentContract, 1)]
    enum PackageDeploymentProgressStatus
    {
        Queued = 0,             // The request is queued
        InProgress = 1,         // The request is in progress
        CompletedSuccess = 2,   // The request completed successfully
        CompletedFailure = 3,   // The request failed with some critical internal error.
    };

    /// Contains progress information for the deployment request.
    /// @see https://learn.microsoft.com/uwp/api/windows.management.deployment.deploymentprogress
    [contract(PackageDeploymentContract, 1)]
    struct PackageDeploymentProgress
    {
        PackageDeploymentProgressStatus Status;

        /// The progress percentage of the deployment request.
        /// @note This is a double with values 0.0-1.0. Windows.Management.Deployment.DeploymentProgress.percentage is uint32 with values 0-100.
        Double Progress;
    };

    /// The status of the deployment request.
    /// @see PackageDeploymentResult.Status
    [contract(PackageDeploymentContract, 1)]
    enum PackageDeploymentStatus
    {
        InProgress = 0,         // The request is in progress
        CompletedSuccess = 1,   // The request completed successfully
        CompletedFailure = 2,   // The request failed with some critical internal error.
    };

    /// Provides the result of a deployment request.
    /// @see https://learn.microsoft.com/uwp/api/windows.management.deployment.deploymentresult
    [contract(PackageDeploymentContract, 1)]
    runtimeclass PackageDeploymentResult
    {
        PackageDeploymentStatus Status { get; };

        /// The extended error code can be used to distinguish a specific error condition which needs to be handled differently from the general error indicated by the return code. The extended error code may provide a more specific reason for the failure that caused the general error. Also, it usually corresponds directly to the specific message in the ErrorText.
        HRESULT Error { get; };

        /// The extended error code can be used to distinguish a specific error condition which needs to be handled differently from the general error indicated by the return code. The extended error code may provide a more specific reason for the failure that caused the general error. Also, it usually corresponds directly to the specific message in the ErrorText.
        /// @see https://learn.microsoft.com/uwp/api/windows.management.deployment.deploymentresult.extendederrorcode
        HRESULT ExtendedError { get; };

        /// Gets extended error text for the error if the deployment operation is not successful.
        /// @see https://learn.microsoft.com/uwp/api/windows.management.deployment.deploymentresult.errortext
        String ErrorText { get; };

        /// Gets the activity identifier used to look up an event in Windows Event Viewer. Gets the activity identifier used to look up an event. All events of a deployment operation are logged with the same activityId.
        /// @see https://learn.microsoft.com/uwp/api/windows.management.deployment.deploymentresult.activityid
        Guid ActivityId { get; };
    }

    [contract(PackageDeploymentContract, 1)]
    runtimeclass PackageSetItem
    {
        PackageSetItem();

        String Id;
        String PackageFamilyName;
        Windows.ApplicationModel.PackageVersion MinVersion;
        Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyProcessorArchitectures ProcessorArchitectureFilter;
        Windows.Foundation.Uri PackageUri;
    }

    [contract(PackageDeploymentContract, 1)]
    runtimeclass PackageSet
    {
        PackageSet();

        String Id;
        Windows.Foundation.Uri PackageUri;
        IVector<PackageSetItem> Items { get; };
    }

    // Requires Windows >= 10.0.19041.0 (aka 2004 aka 20H1)
    [contract(PackageDeploymentContract, 1)]
    runtimeclass AddPackageOptions
    {
        AddPackageOptions();

        PackageVolume TargetVolume;
        IVector<Windows.Foundation.Uri> DependencyPackageUris { get; };
        IVector<String> OptionalPackageFamilyNames { get; };
        IVector<Windows.Foundation.Uri> OptionalPackageUris { get; };
        IVector<Windows.Foundation.Uri> RelatedPackageUris { get; };
        Windows.Foundation.Uri ExternalLocationUri;
        StubPackageOption StubPackageOption;
        Boolean AllowUnsigned;
        Boolean DeveloperMode;
        Boolean ForceAppShutdown;
        Boolean ForceTargetAppShutdown;
        Boolean ForceUpdateFromAnyVersion;
        Boolean InstallAllResources;
        Boolean RequiredContentGroupOnly;
        Boolean RetainFilesOnFailure;
        Boolean StageInPlace;
        Boolean DeferRegistrationWhenPackagesAreInUse;

        Boolean IsExpectedDigestsSupported { get; };            // Requires Windows >= 10.0.22621.0 (aka Win11 22H2)
        IMap<Windows.Foundation.Uri, String> ExpectedDigests{ get; };

        Boolean IsLimitToExistingPackagesSupported { get; };    // Requires Windows >= 10.0.22621.0 (aka Win11 22H2)
        Boolean LimitToExistingPackages;
    }

    // Requires Windows >= 10.0.19041.0 (aka 2004 aka 20H1)
    [contract(PackageDeploymentContract, 1)]
    runtimeclass StagePackageOptions
    {
        StagePackageOptions();

        PackageVolume TargetVolume;
        IVector<Windows.Foundation.Uri> DependencyPackageUris { get; };
        IVector<String> OptionalPackageFamilyNames { get; };
        IVector<Windows.Foundation.Uri> OptionalPackageUris { get; };
        IVector<Windows.Foundation.Uri> RelatedPackageUris { get; };
        Windows.Foundation.Uri ExternalLocationUri;
        StubPackageOption StubPackageOption;
        Boolean DeveloperMode;
        Boolean ForceUpdateFromAnyVersion;
        Boolean InstallAllResources;
        Boolean RequiredContentGroupOnly;
        Boolean StageInPlace;
        Boolean AllowUnsigned;

        Boolean IsExpectedDigestsSupported { get; };            // Requires Windows >= 10.0.22621.0 (aka Win11 22H2)
        IMap<Windows.Foundation.Uri, String> ExpectedDigests{ get; };
    }

    // Requires Windows >= 10.0.19041.0 (aka 2004 aka 20H1)
    [contract(PackageDeploymentContract, 1)]
    runtimeclass RegisterPackageOptions
    {
        RegisterPackageOptions();

        PackageVolume AppDataVolume;
        IVector<String> DependencyPackageFamilyNames { get; };
        IVector<Windows.Foundation.Uri> DependencyPackageUris { get; };
        IVector<String> OptionalPackageFamilyNames { get; };
        Windows.Foundation.Uri ExternalLocationUri;
        Boolean AllowUnsigned;
        Boolean DeveloperMode;
        Boolean ForceAppShutdown;
        Boolean ForceTargetAppShutdown;
        Boolean ForceUpdateFromAnyVersion;
        Boolean InstallAllResources;
        Boolean StageInPlace;
        Boolean DeferRegistrationWhenPackagesAreInUse;

        Boolean IsExpectedDigestsSupported { get; };            // Requires Windows >= 10.0.22621.0 (aka Win11 22H2)
        IMap<Windows.Foundation.Uri, String> ExpectedDigests{ get; };
    }

    // Requires Windows >= 10.0.19041.0 (aka 2004 aka 20H1)
    [contract(PackageDeploymentContract, 1)]
    runtimeclass RemovePackageOptions
    {
        RemovePackageOptions();

        Boolean FailIfNotFound;
        Boolean PreserveApplicationData;
        Boolean PreserveRoamableApplicationData;
        Boolean RemoveForAllUsers;
    }

    [contract(PackageDeploymentContract, 1)]
    runtimeclass ProvisionPackageOptions
    {
        ProvisionPackageOptions();

        Boolean IsOptionalPackageFamilyNamesSupported{ get; };  // Requires Windows >= 10.0.22000.0 (aka Win11 21H2)
        IVector<String> OptionalPackageFamilyNames { get; };

        Boolean IsProjectionOrderPackageFamilyNamesSupported{ get; };   // Requires Windows >= 10.0.22000.0 (aka Win11 21H2)
        IVector<String> ProjectionOrderPackageFamilyNames { get; };
    }

    [contract(PackageDeploymentContract, 1)]
    runtimeclass EnsureReadyOptions
    {
        EnsureReadyOptions();

        AddPackageOptions AddPackageOptions { get; };

        [contractversion(2)]
        Boolean RegisterNewerIfAvailable;
    }

    [contract(PackageDeploymentContract, 1)]
    runtimeclass PackageDeploymentManager
    {
        // Get an instance of the manager
        static PackageDeploymentManager GetDefault();

        //-------------------------------------------------------------
        // IsReady

        // Return true if the package(s) are present and available for use

        Boolean IsPackageReady(String package);

        Boolean IsPackageReadyByUri(Windows.Foundation.Uri packageUri);

        Boolean IsPackageSetReady(PackageSet packageSet);

        //-------------------------------------------------------------
        // IsReadyOrNewerAvailable

        // Return true if the package(s) are present and available for use

        [contractversion(2)]
        PackageReadyOrNewerAvailableStatus IsPackageReadyOrNewerAvailable(String package);

        [contractversion(2)]
        PackageReadyOrNewerAvailableStatus IsPackageReadyOrNewerAvailableByUri(Windows.Foundation.Uri packageUri);

        [contractversion(2)]
        PackageReadyOrNewerAvailableStatus IsPackageSetReadyOrNewerAvailable(PackageSet packageSet);

        //-------------------------------------------------------------
        // EnsureReady

        // Check if the necessary package(s) are present
        // and available for use and if not then Make It So.
        // If the necessary packages(s) are not present on the system
        // then make them available (download, install, etc).
        // If the necessary packages are present and available this is equivalent to IsReady(id).

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        EnsurePackageReadyAsync(String package, EnsureReadyOptions options);

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        EnsurePackageReadyByUriAsync(Windows.Foundation.Uri packageUri, EnsureReadyOptions options);

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        EnsurePackageSetReadyAsync(PackageSet packageSet, EnsureReadyOptions options);

        //-------------------------------------------------------------
        // Add packages

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        AddPackageAsync(String package, AddPackageOptions options);

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        AddPackageByUriAsync(Windows.Foundation.Uri packageUri, AddPackageOptions options);

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        AddPackageSetAsync(PackageSet packageSet, AddPackageOptions options);

        //-------------------------------------------------------------
        // Stage packages

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        StagePackageAsync(String package, StagePackageOptions options);

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        StagePackageByUriAsync(Windows.Foundation.Uri packageUri, StagePackageOptions options);

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        StagePackageSetAsync(PackageSet packageSet, StagePackageOptions options);

        //-------------------------------------------------------------
        // Register packages

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        RegisterPackageAsync(String package, RegisterPackageOptions options);

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        RegisterPackageByUriAsync(Windows.Foundation.Uri packageUri, RegisterPackageOptions options);

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        RegisterPackageSetAsync(PackageSet packageSet, RegisterPackageOptions options);

        //-------------------------------------------------------------
        // Remove packages

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        RemovePackageAsync(String package, RemovePackageOptions options);

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        RemovePackageByFullNameAsync(String packageFullName, RemovePackageOptions options);

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        RemovePackageByFamilyNameAsync(String packageFamilyName, RemovePackageOptions options);

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        RemovePackageByUriAsync(Windows.Foundation.Uri packageUri, RemovePackageOptions options);

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        RemovePackageSetAsync(PackageSet packageSet, RemovePackageOptions options);

        //-------------------------------------------------------------
        // Reset packages

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        ResetPackageAsync(String package);

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        ResetPackageByUriAsync(Windows.Foundation.Uri packageUri);

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        ResetPackageSetAsync(PackageSet packageSet);

        //-------------------------------------------------------------
        // Repair packages

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        RepairPackageAsync(String package);

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        RepairPackageByUriAsync(Windows.Foundation.Uri packageUri);

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        RepairPackageSetAsync(PackageSet packageSet);

        //-------------------------------------------------------------
        // IsProvisioned

        // Return true if the package(s) are provisioned

        [contract(PackageDeploymentContract, 2)]
        Boolean IsPackageProvisioned(String package);

        [contract(PackageDeploymentContract, 2)]
        Boolean IsPackageProvisionedByUri(Windows.Foundation.Uri packageUri);

        /// @note packageSet[Item].PackageUri is optional
        [contract(PackageDeploymentContract, 2)]
        Boolean IsPackageSetProvisioned(PackageSet packageSet);

        //-------------------------------------------------------------
        // Provision packages

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        ProvisionPackageAsync(String package, ProvisionPackageOptions options);

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        ProvisionPackageByUriAsync(Windows.Foundation.Uri packageUri, ProvisionPackageOptions options);

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        ProvisionPackageSetAsync(PackageSet packageSet, ProvisionPackageOptions options);

        //-------------------------------------------------------------
        // Deprovision packages

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        DeprovisionPackageAsync(String package);

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        DeprovisionPackageByUriAsync(Windows.Foundation.Uri packageUri);

        Windows.Foundation.IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>
        DeprovisionPackageSetAsync(PackageSet packageSet);

        //-------------------------------------------------------------
        // IsRegistrationPending

        Boolean IsPackageRegistrationPending(String packageFullName);

        Boolean IsPackageRegistrationPendingForUser(String userSecurityId, String packageFullName);
    }

    [contract(PackageDeploymentContract, 1)]
    runtimeclass PackageSetItemRuntimeDisposition
    {
        PackageSetItemRuntimeDisposition();

        String PackageSetItemId{ get; };
        String PackageFullName{ get; };
        String PackageDependencyId{ get; };
        Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependencyContextId PackageDependencyContextId{ get; };
    }

    [contract(PackageDeploymentContract, 1)]
    runtimeclass PackageSetRuntimeDisposition
    {
        PackageSetRuntimeDisposition();

        String PackageSetId;
        IVector<PackageSetItemRuntimeDisposition> PackageSetItemRuntimeDispositions { get; };
    }

    [contract(PackageDeploymentContract, 1)]
    runtimeclass PackageRuntimeManager
    {
        // Get an instance of the manager
        static PackageRuntimeManager GetDefault();

        // Make the package(s) in the package set available to the calling process
        // i.e. dynamically add the package(s) in the package set to the caller's package graph.
        // This is equivalent to
        //   FOREACH psi IN packageSet.Items
        //       pd = TryCreatePackageDependency(psi)
        //       AddPackageDependency(pd)

        Microsoft.Windows.Management.Deployment.PackageSetRuntimeDisposition AddPackageSet(
            PackageSet packageSet);

        [method_name("AddPackageSetWithOptions")]
        Microsoft.Windows.Management.Deployment.PackageSetRuntimeDisposition AddPackageSet(
            PackageSet packageSet,
            Microsoft.Windows.ApplicationModel.DynamicDependency.CreatePackageDependencyOptions createOptions,
            Microsoft.Windows.ApplicationModel.DynamicDependency.AddPackageDependencyOptions addOptions);

        void RemovePackageSet(
            Microsoft.Windows.Management.Deployment.PackageSetRuntimeDisposition packageSetRuntimeDisposition);
    }
}
```
