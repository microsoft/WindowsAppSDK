# AppLocal Deployment

## Overview

The default and preferred deployment model for the Windows App SDK is the Windows App SDK Framework Package which
provides a single shared dependency across apps that can be automatically kept up to date and secure.

However, developers sometimes prefer AppLocal deployment of their dependencies to minimize risk of
automatic updates breaking compatibility and to ensure their dependencies aren't pulled out from
under them unexpectedly. In some scenarios like xcopy deployment of apps, AppLocal deployment would
be required.

This spec captures the goals and requirements for supporting AppLocal deployment in the Windows App SDK
as well as the developer experience for choosing this model.

## Goals

* Support AppLocal deployment for both packaged and unpackaged scenarios
* Minimize effort required by Windows App SDK component owners to support all deployment and packaging models

## Functional Requirements

|ID|Requirement|Priority|
|-|-|-|
| 1 | Support packaged apps at runtime | P0 |
| 2 | Support unpackaged apps at runtime | P0 |
| 3 | Support [sparse package apps](https://docs.microsoft.com/windows/apps/desktop/modernize/grant-identity-to-nonpackaged-apps) at runtime | P0 |
| 4 | Support Windows App SDK deployed via MSIX | P0 |
| 5 | Support Windows App SDK deployed via AppLocal | P0 |
| 6 | Support all runtime and deployment permutations downlevel to RS5 | P0 |
| 7 | Windows App SDK components targeting stable releases MUST support all runtime and deployment permutations otherwise they are excluded from the release | P0 |
| 8 | Windows App SDK component owners author their component registrations for packaged runtime and MSIX deployment which is then translated automatically to support other runtime and deployment permutations as necessary (e.g. RegFreeWinRT) | P0 |
| 9 | Windows App SDK builds MUST produce artifacts required for packaged and unpackaged AppLocal deployment | P0 |
| 10 | Build documentation for all supported runtime and deployment permutations (see [Developer Experience](#Developer-Experience)) | P0 |
| 11 | Build samples for all supported runtime and deployment permutations (see [Developer Experience](#Developer-Experience)) | P0 |
| 12 | Samples MUST be provided for all supported languages (see [Developer Experience](#Developer-Experience)) | P0 |
| 13 | Build a test for each runtime and deployment permutation | P0 |

## Developer Experience

Project templates will only offer framework package deployment, as that is the recommended path. Developers must opt out to use AppLocal deployment.

The opt out mechanism(s) must be simple and documented and must support all WinUI 3 Desktop project templates in both packaged and unpackaged scenarios.

For v1.0, developers must specify the msbuild property `<WindowsAppSDKAppLocal>true</WindowsAppSDKAppLocal>` manually in their project file to switch to AppLocal deployment. Integration of this property into the Visual Studio Project Properties UI will be investigated in future releases.

The [Windows App SDK Main and Singleton Packages](MSIXPackages.md) are required for unpackaged scenarios as well as some features like Notifications whose implementation relies on that package. These MSIX packages will need to be installed as a prerequisite even for AppLocal scenarios. For AppLocal deployments, the expectation is apps can redistribute these MSIX packages within their app and register them on startup using `PackageManager.AddPackageAsync(...)`. These packages are considered an undocked part of the OS so are treated more like an OS dependency rather than an AppLocal dependency, with the same compatibility promises of OS updates.

## Design Guidelines for Windows App SDK Components

AppLocal deployment implies two things:

* Component binaries will be deployed locally within the app rather than within the shared MSIX framework package
* Multiple instances of those binaries can all be running at the same time with multiple apps using AppLocal deployment

Windows App SDK components need to support all runtime and deployment permutations so should not make assumptions that preclude any of these scenarios:

* DON'T assume an app has package identity
* DON'T assume an app has a package graph
* DON'T depend solely on MSIX-specific features like StartupTasks or DEHs
  * Features can depend on WARMain and still support all runtime and deployment permutations but must fail gracefully if WARMain is not installed
* DON'T depend on a single instance of your component running in the shared MSIX framework package
* DON'T depend on cross-process singleton resources
  * Constant named kernel objects (e.g. mutex, event, etc.)
  * Constant NT service name
  * Constant absolute filename
* DON'T depend on classic COM registration in HKCR
* DON'T depend on installation in a common location shared across apps

In addition to validating all runtime and deployment permutations within a single application, it is important to validate the following multiple application scenarios as well:

* DO validate that multiple applications using a Windows App SDK component via the shared MSIX framework package install and run concurrently without affecting each other
* DO validate that multiple applications using a Windows App SDK component via AppLocal deployment install and run concurrently without affecting each other
* DO validate that one application using a Windows App SDK component via the shared MSIX framework package and another application using that component via AppLocal deployment both install and run concurrently without affecting each other