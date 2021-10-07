
# Background

This is the spec for proposal [Windows App Runtime Deployment API #1240](https://github.com/microsoft/WindowsAppSDK/issues/1240).

The Windows App SDK (WinAppSDK) for packaged apps involves the framework, main, and singleton packages, which are all signed and published by Microsoft. The framework package contains the WinAppSDK binaries used at run time, and it is installed with the application. The main package contains out-of-process services that are brokered between apps, such as push notifications, and it is also needed for the framework to be serviced by the Microsoft Store. The singleton package supports a single long-running process that is brokered between apps for features like push notifications. 

If developers want to use features not included in the framework and prefer to have the framework automatically updated by the Store without needing to redistribute their packaged app, then the main and singleton packages are also required to be installed on the system. But while the Windows application model supports framework dependencies, it does not support a packaged app (a main package) to declare a dependency on other main packages (the Windows App SDK main and singleton packages), so the Store cannot install these with the app. The framework package that is installed with your app will have the main and singleton package embedded within it, and your packaged app must then use the **Deployment API** to get those packages installed on the machine, whether online or offline. 

Note that in Windows App SDK version 1.0, only MSIX packaged apps that are full trust or have the packageManagement restricted capability have the permission to use the Deployment API to install the main and singleton package dependencies. Support for partial trust packaged apps will be coming in later releases.


# Description

When a packaged app using the WinAppSDK is deployed from the Store, it is expected to only have
the application's main package and frameworks, and the WinAppSDK other main packages may not be
present, or may not be at the required version. This API enables a developer to detect when the
WinAppSDK is incomplete and take corrective action.

Since this API is part of the WinAppSDK framework, the framework itself must be present.
For MSIX packages, the framework must be listed as a dependency in the application manifest and
will not be deployable without a min version being present. 

Developers must not assume that the WinAppSDK main package is present, or that the version
present is the minimum version required to support the feature set they expect. Instead, this API
should be used to validate the WinAppSDK is the correct version and all required packages are present.

The developer scenarios for this API is to answer the questions:
1. Does this system have the min version of the Windows App SDK I require and are they usable?
2. What do I do to resolve this if it doesn't?

The API addresses #1 by a simple query of the version they seek and a possible check for OS
updates. #2 has two possible answers. First is direct resolution by the developer by acquiring and
installing the packages if possible. Since the main packages are small and the target developer
scenario will have permissions to deploy them, we will minimize developer and user pain by
including the main package MSIX packages within the framework, and this API will allow for the
deployment of that package if needed.

Processes lacking permission to deploy MSIX are out-of-scope at this time.

# Examples

## GetStatus

This is the means by which an app or program can call to verify all required packages are present
to a minimum version needed by the loaded framework.  A process should call GetStatus() after
process initialization and before using Windows App Runtime content (e.g. in main() or WinMain()).

Developers call this method without parameters, as all information about the version, channel, and
architecture are derived from the current WARfwk loaded. This method is good to identify if there
is possible work required in the form of package install which may take several seconds to
complete.

```C++
auto result{Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentManager::GetStatus()};
if (!result.Status() == Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentStatus::Ok)
{
    ...
}
```

## Initialize

This API performs a status check and if any packages are required for install, attempts to register
those packages and get the WindowsAppRuntime into an OK state. This will perform package install if
possible. It is possible multiple packages may be required for install, and this will attempt
to deploy all required packages. The returned WindowsAppRuntimeStatus will contain the first error
if one occurs during package install. There will be no rollback of successfully installed packages
if an error occurs on a subsequent package install.


```C++
auto result{Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentManager::Initialize()};
if (!result.Status() == Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentStatus::Ok)
{
    return result.ExtendedError();
}
```


# API Details

```c#

namespace Microsoft.Windows.ApplicationModel.WindowsAppRuntime
{
    /// Represents the current Deployment status of the WindowsAppRuntime
    [flags]
    enum DeploymentStatus
    {
        Unknown = 0,
        Ok,
        PackageInstallRequired,
        PackageInstallFailed,
    };

    /// Represents the a result of a Deploymen Manager method.
    runtimeclass DeploymentResult
    {
        DeploymentResult(DeploymentStatus status, HRESULT extendedError);

        /// Returns the DeploymentStatus of the result.
        DeploymentStatus Status { get; };

        /// Returns the first encountered error if there was an error or S_OK if no error.
        HRESULT ExtendedError{ get; };
    };

    /// Used to query deployment information for WindowsAppRuntime
    static runtimeclass DeploymentManager
    {
        /// Returns the current deployment status of the current package's Windows App Runtime.
        static DeploymentResult GetStatus();

        /// Checks the status of the WindowsAppRuntime of the current package and attempts to
        /// register any missing packages that can be registered.
        static DeploymentResult Initialize();
    };
}
```

# Appendix
