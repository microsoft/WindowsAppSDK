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

A newer generation of the package management APIs are provided via Windows App
SDK offering functional enhancements and optimizations.

The package management APIs were originally introduced in Windows 8 and have
continuously expanded to meet MSIX's growing demands over the past decade.
However, as one of the earliest WinRT APIs they include some patterns out of
step with current API practices and recommendations. Windows App SDK offers
the opportunity to provide a new generation of package management APIs in line
with the latest patterns and recommendations for an improved developer
experience as well as improved runtime efficiencies.

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

Methods accept options as a matching `<verb>Package[Set]Options` type, e.g.
`AddPackageAsync(string packageUri, AddPackageOptions options)`.

The following table shows the supported permutations of verbs and targets:

|Verb         | Path | Filename | PackageFamilyName | PackageFullName | file:  | http(s): | ms-uup: | PackageSet |
|-------------|:-----|:---------|:------------------|:----------------|:-------|:---------|:--------|:-----------|
|IsReady      |  X   |    X     |       OS/WAS      |       WAS       |   X    |    X     |  WAS    |    WAS     |
|EnsureIsReady|  X   |    X     |         X         |        X        |   X    |    X     |  WAS    |    WAS     |
|Add          |  X   |    X     |         X         |        X        | OS/WAS |  OS/WAS  | OS/WAS  |    WAS     |
|Stage        |  X   |    X     |         X         |        X        | OS/WAS |  OS/WAS  | OS/WAS  |    WAS     |
|Register     | WAS  |  OS/WAS  |       OS/WAS      |      OS/WAS     | OS/WAS |    X     | OS/WAS  |    WAS     |
|Remove       |  X   |    X     |        WAS        |      OS/WAS     |   X    |    X     | OS/WAS  |    WAS     |
|Repair       |  X   |    X     |        WAS        |       TODO      |   X    |    X     |  WAS    |    WAS     |
|Reset        |  X   |    X     |        WAS        |       TODO      |   X    |    X     |  WAS    |    WAS     |
|Provision    |  X   |    X     |       OS/WAS      |        X        |   X    |    X     |  WAS    |    WAS     |
|Deprovision  |  X   |    X     |       OS/WAS      |        X        |   X    |    X     |  WAS    |    WAS     |

Legend:
* OS = Supported by Windows.Management.Deployment.PackageManager
* WAS = Supported by Microsoft.Windows.Management.Deployment.PackageDeploymentManager
* X = Not supported


# 4. Examples

Samples illustrating the package management APIs:

- [Sample 1](sample-1.md) - Fabrikam app installing Contoso's Muffin package

# 5. Remarks

TODO

# 6. API Details

```c# (but really MIDL3)
namespace Microsoft.Windows.Management.Deployment
{
}
```
