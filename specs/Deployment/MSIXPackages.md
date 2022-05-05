- [1. Background](#1-background)
- [2. MSIX Packages](#2-msix-packages)
  - [2.1. Roles](#21-roles)
    - [2.1.1. Role - Framework](#211-role---framework)
    - [2.1.2. Role - Main](#212-role---main)
    - [2.1.3. Role - Singleton](#213-role---singleton)
    - [2.1.4. Dynamic Dependency Lifetime Manager (DDLM)](#214-dynamic-dependency-lifetime-manager-ddlm)
- [3. Package Naming](#3-package-naming)
  - [3.1. Package Naming - SubName](#31-package-naming---subname)
  - [3.2. Package Naming - Singleton](#32-package-naming---main)
  - [3.3. Package Naming - Singleton](#33-package-naming---singleton)
  - [3.4. Package Naming - DDLM](#34-package-naming---ddlm)
- [4. Package Versioning](#4-package-versioning)

# 1. Background

Windows App SDK supports deployment as a set of MSIX packages for use at runtime.
This document outlines the list of packages and their rules and roles.

# 2. MSIX Packages

Windows App SDK is distributed as multiple MSIX packages:

1. Framework
2. Main
3. Singleton
4. Dynamic Dependency Lifetime Manager (DDLM)

## 2.1. Roles

### 2.1.1. Role - Framework

The Framework package is the API delivery vehicle for Windows App SDK. The vast majority of code in
the project is found here.

Framework packages support concurrent behavior. A user may have multiple versions of a framework
package in use across processes (process1 using 1.0.1.0, process2 using 1.0.2.0, ...). Updates can
be registered for a user without disrupting running apps. Windows points running apps to updated
Framework packages non-disruptively (e.g. when an app's not running), colaescing apps to newer
versions over time (not necessarily instaneously). This provides for a very flexible servicing
model.

### 2.1.2. Role - Main

The Main package supplements the Framework package, for when functionality is needed but can't be
delivered via the Framework package. Mechanisms include [Packaged COM](https://blogs.windows.com/windowsdeveloper/2017/04/13/com-server-ole-document-support-desktop-bridge/),
[app services](https://docs.microsoft.com/windows/uwp/launch-resume/how-to-create-and-consume-an-app-service),
[app extensions](https://docs.microsoft.com/uwp/api/Windows.ApplicationModel.AppExtensions.AppExtension),
[background tasks](https://docs.microsoft.com/windows/uwp/launch-resume/create-and-register-a-background-task),
[startup tasks](https://docs.microsoft.com/uwp/api/Windows.ApplicationModel.StartupTask) executing
on user login, [ApplicationData](https://docs.microsoft.com/uwp/api/Windows.Storage.ApplicationData)
for data storage scoped to Windows App SDK (not any particular app using Windows App SDK), and
more.

The primary scenarios include:

* Brokered Access -- processes running in an [AppContainer](https://docs.microsoft.com/windows/win32/secauthz/appcontainer-isolation)
                     requiring access to resources that cannot be access from within the
                     AppContainer can use a 'helper process' running at MediumIL and doing work on
                     the API's behalf. cannot do for itself (i.e. brokered access to a resource).
* Long-Running Process (aka user service) -- functionality requiring a long-running process
                                             (especially if its lifetime isn't directly coupled to
                                             an app's lifetime).

Main packages don't support side-by-side behavior for a user. A user can only have 1 (or 0) Main
packages in a package family registered at a time. Thus if a user has v1.0.0.0 registered when
1.0.0.1 is registered it's an *update*, ending with the user having v1.0.0.1 registered instead of
v1.0.0.0. This poses servicing challenges, as updating the Main package requires any running
processes from the existing Main package to be terminated.

For these reasons Windows App SDK developers are strongly encouraged to only rely on the Main package when
necessary.

If a process from the Main package is necessary, it should be short-lived or support a save/restore
execution model. The former shrinks the possibility a running process when a servicing event
occurs. The latter ensures if Main package processes are running when a servicing event occurs, the
running processes can be terminated (e.g. via [DeploymentOptions.ForceTargetApplicationShutdown](https://docs.microsoft.com/uwp/api/windows.management.deployment.deploymentoptions))
to allow the servicing event to occur and restarted upon its completion, with only a transient (and
possibly unnoticed) interruption of service.

Further, if/when the Main package is necessary, Windows App SDK developers are encouraged to put as
little as practical in the Main package and use the Framework package as much as possible. For
example, if a StartupTask is needed you can declare the StartupTask in the Main package's
`appxmanifest.xml` and provide an executable with a trivial 1% implementation e.g.

```c
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    return MyFeatureWinMain(hInstance, hPrevInstance, pCmdLine, nCmdShow);
}
```

and export `MyFeatureWinMain` from a DLL in the Framework package to get the implementation's
other 99%.

### 2.1.3. Role - Singleton

The Singleton package supplements the Main package, for when functionality is needed by a single
process spanning all versions of Windows App SDK.

The Singleton package is a main package so the same guidance applies to the Singleton as to the Main
package -- Windows App SDK developers are strongly encouraged to only rely on the Singleton package
when necessary. See (2.1.2. Role- Main) for more details.

The Singleton package's content is used by ALL versions of Windows App SDK registered to the user so
additional caution is advised.

Only the highest version of the Singleton package will be installed for a user, e.g. if Windows App
SDK 1.0, 1.1 and 2.0 (Stable) are installed on an x86 system, the user will have registered...

* Microsoft.WindowsAppRuntime.1.0
* Microsoft.WindowsAppRuntime.1.1
* Microsoft.WindowsAppRuntime.2.0
* MicrosoftCorporationII.WinAppRuntime.Main.1.0
* MicrosoftCorporationII.WinAppRuntime.Main.1.1
* MicrosoftCorporationII.WinAppRuntime.Main.2.0
* MicrosoftCorporationII.WinAppRuntime.Singleton (version 2.0)
* Microsoft.WinAppRuntime.DDLM.0.146.711.0-x8
* Microsoft.WinAppRuntime.DDLM.1000.328.1510.0-x8
* Microsoft.WinAppRuntime.DDLM.0.510.333.0-x8

Singleton package content MUST be backwards compatible across all releases due to the Singleton
package's singular <g> nature

### 2.1.4. Dynamic Dependency Lifetime Manager (DDLM)

The [Dynamic Dependency API](https://github.com/microsoft/WindowsAppSDK/blob/main/specs/dynamicdependencies/DynamicDependencies.md)
resolves a package dependency to a specific framework package and make it available for a process,
but Windows doesn't know the package is in use by this process. Lacking this "package in use"
knowledge, Windows could service the package (remove, remediate, repair, ...) in negatively
impactful ways. To prevent this (without servicing Windows) we need...

1. ...a running process running with package identity...
2. ...with an `appxmanifest.xml` declaring a `<PackageDependnecy>` on the framework package...
3. ...running for as long as the framework package is used by the app.

This is accomplished for the Microsoft.WindowsAppRuntime framework package via a Packaged COM
out-of-process (OOP) server in a DDLM package, selected and managed via the Bootstrap API. See the
[Dynamic Dependency spec](https://github.com/microsoft/WindowsAppSDK/blob/main/specs/dynamicdependencies/DynamicDependencies.md)
for more details.

# 3. Package Naming

Windows App SDK's MSIX packages use the following naming rules for package identity:

* Name = Microsoft.WindowsAppRuntime[.SubName].\<Major\>.\<Minor\>[-VersionTag]
* Publisher = "CN=Microsoft Corporation, O=Microsoft Corporation, L=Redmond, S=Washington, C=US"

where

* SubName -- optional package sub-name. Use to distinguish amongst the different packages
* Major -- major version of the release, e.g. "1" for Windows App SDK 1.0
* Minor -- minor version of the release, e.g. "0" for Windows App SDK 1.0
* VersionTag -- optional version tag to distinguish amongst channels and releases of a channel, e.g. "-preview2" for Windows App SDK 1.0 Preview 2

## 3.1. Package Naming - SubName

The following SubName values are used:

| SubName | Package | Example |
|-|-|-|
| | Framework | Microsoft.WindowsAppRuntime.1.0-experimental1 |
| Main | Main | MicrosoftCorporationII.WinAppRuntime.Main.1.0-e1 |
| Singleton | Singleton | MicrosoftCorporationII.WinAppRuntime.Singleton-e1 |
| DDLM | Dynamic Dependency Lifetime Manager (DDLM) | Microsoft.WinAppRuntime.DDLM.0.146.711.0-x6-e1 |

## 3.2. Package Naming - Main

The Main package follows a different naming scheme

* Name = MicrosoftCcorporationII.WinAppRuntime.Main.\<ReleaseMajorMinor\>[-ShortVersionTag]

where

* ReleaseMajorMinor = project release major.minor version number. See the [MSIX Package Versioning](https://github.com/microsoft/WindowsAppSDK/blob/main/specs/deployment/MSIXPackageVersioning.md) for more details.
* ShortVersionTag = short form of the VersionTag

ShortVersionTag is derived from a VersionTag by combining the 1st letter and the last digit (if any) for non-Stable channels (ShortVeresionTag is blank for the Stable channel, just like VersionTag).

## 3.3. Package Naming - Singleton

The Singleton package follows a naming scheme similar to the Main package:

* Name = MicrosoftCorporationII.WinAppRuntime.Singleton[-ShortVersionTag]

The package family is the same across all versions of Windows App SDK. As a main package, only one
Singleton package can be registered at a time for a user and by its nature it's meant to be used
with all versions of Windows App SDK registered for a user. Thus its package Name is rather simple
compared to other package Names, lacking any version information.

See [2.1.3. Role - Singleton](#213-role---singleton) for more information.

## 3.4. Package Naming - DDLM

DDLM packages follow a different naming scheme

* Name = Microsoft.WinAppRuntime.DDLM.\<Version\>-\<ShortArchitecture\>[-ShortVersionTag]

where

* Version = MSIX version number (not the project release version). See the [MSIX Package Versioning](https://github.com/microsoft/WindowsAppSDK/blob/main/specs/deployment/MSIXPackageVersioning.md) for more details.
* ShortArchitecture = short form of the Architecture (x6=x64, x8=x86, a6=arm64)
* ShortVersionTag = short form of the VersionTag

ShortVersionTag is derived from a VersionTag by combining the 1st letter and the last digit (if any) for non-Stable channels (ShortVeresionTag is blank for the Stable channel, just like VersionTag).

```C#
string ToShortVersionTag(string versionTag)
{
    if (String.IsNullOrEmpty(versionTag))
    {
        return versionTag;
    }
    string prefix = versionTag.substr(0, 1);
    if (versionTag.length > 1)
    {
        char lastChar = versionTag.substr(versionTag.length - 1, 1);
        if (('0' <= lastChar) && (lastChar <= '9'))
        {
            suffix = lastChar.ToString();
            return prefix + suffix;
        }
    }
    return prefix;
}
```

# 4. Package Versioning

See the [MSIX Package Versioning](https://github.com/microsoft/WindowsAppSDK/blob/main/specs/Deployment/MSIXPackageVersioning.md)
decision document for more details.
