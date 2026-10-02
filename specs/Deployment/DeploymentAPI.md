# Background

This is the spec for proposal
[Windows App Runtime Deployment API #1240](https://github.com/microsoft/WindowsAppSDK/issues/1240).

The Windows App SDK (WinAppSDK) for packaged apps involves the framework, main, and singleton
packages, which are all signed and published by Microsoft. The framework package contains the
WinAppSDK binaries used at run time, and it is installed with the application. The main package
contains out-of-process services that are brokered between apps, such as push notifications, and it
is also needed for the framework to be serviced by the Microsoft Store. The singleton package
supports a single long-running process that is brokered between apps for features like push
notifications.

Currently, packaged apps can only declare dependencies on WinAppSDK framework package. In order to
get the other WinAppSDK packages (main, singleton) deployed, the packaged apps can use the mechanism
described here as part of their first-run experience.

> **Note that in Windows App SDK version 1.0**, only unpackaged apps that are full trust or MSIX
> packaged apps that have the packageManagement restricted capability have the permission to use the
> Deployment API to install the main and singleton package dependencies. Support for partial trust
> MSIX packaged apps will be coming in later releases. Additionally, support for main and singleton
> package deployment through the Microsoft Store will be coming in later releases.

# Description

When a packaged app using the WinAppSDK is deployed from the Store, it will be installed with the
application's main package and the WinAppSDK framework package. The WinAppSDK main and singleton
packages may not already be present on the system, or may not be at the version required by the
application. The Deployment API enables a developer to check when the required WinAppSDK main and
singleton packages are missing and get them installed.

Since the Deployment API is part of the WinAppSDK framework package, the framework itself must be
present to use the API. To deploy the WinAppSDK framework package with the MSIX packaged
application, the framework must be declared as a dependency in the application manifest with a min
version specified. For instructions on deploying the framework package, see the
[developer docs](https://docs.microsoft.com/windows/apps/windows-app-sdk/deploy-packaged-apps#deploy-the-windows-app-sdk-framework-package).

If a developer prefers to have the Microsoft Store automatically service the WinAppSDK framework
package and if features like push notifications are desired, then the WinAppSDK main and singleton
should also be deployed. Developers must not assume that the WinAppSDK main and singleton packages
are already present on the system, or that the version present is the minimum version required by
the application. Instead, the Deployment API should be used to validate that the WinAppSDK is at the
correct version and that all required packages are present.

The Deployment API addresses the following two developer scenarios:

1. Does this system have the min version of the WinAppSDK main and singleton packages required by my
   app?
2. How do I install the WinAppSDK main and singleton packages, if they are not already present on
   the system?

The API addresses #1 by a simple query of the version needed and a check for OS updates.

#2 has two possible answers.

-   First, the developer can install these packages directly through the app, if possible. These
    MSIX packages can be acquired through
    [Downloads page](https://docs.microsoft.com/windows/apps/windows-app-sdk/downloads).
-   Alternatively, unpackaged apps that are full trust or MSIX packaged apps that have the
    packageManagement restricted capability can use the Deployment API to get these packages
    installed.

# Examples

## GetStatus

This is the means by which an app or program can call to verify that all required WinAppSDK packages
are present to a minimum version needed by the framework loaded with the app. A process should call
GetStatus() after process initialization and before using Windows App Runtime content (e.g. in
main() or WinMain()).

Developers call this method without parameters, as all information about the version, channel, and
architecture are derived from the current framework package loaded.

```C#
    DeploymentResult result = DeploymentManager.GetStatus();
    if (result.Status == DeploymentStatus.Ok)
    {
        // WindowsAppRuntime is in a good state and ready for use.
    }
    else
    {
        // WindowsAppRuntime is not in a good state.
        // Should call Initialize on another thread, or not use features that require the
        // WindowsAppRuntime. result.ExtendedError has the error code that has the reason
        // for the Status.
    }
```

## Initialize

This API performs a status check, and if the main and/or singleton packages are missing or not at
the required version, it will attempt to deploy those packages and get the WindowsAppRuntime into an
OK state. All information about the version, channel, and architecture needed are derived from the
current WinAppSDK framework package.

Since both the main _and_ the singleton packages may need to be installed, it is possible that one
package is installed successfully but not the other. If so, the returned WindowsAppRuntimeStatus
will contain the error, if one occurs during package install. There will be no rollback of any
successfully installed packages. See the
[developer docs](https://docs.microsoft.com/windows/apps/windows-app-sdk/deploy-packaged-apps#address-installation-errors)
for instructions on how to handle errors.

The install of the packages may take a couple seconds to complete, which may be a performance
concern to some developers. To address these concerns, developers can instead call GetStatus() first
and verify that the required packages are missing. If so, then call Initialize() on another thread
to handle the time delay more elegantly.

Once the main and singleton packages have been deployed, they generally do not need to be deployed
again. If a user were to remove the main or singleton package, the API can be used to reinstall them
again.

```C#
    if (DeploymentManager.GetStatus().Status != DeploymentStatus.Ok)
    {
        // Initialize does a status check, and if the status is not OK it will attempt to get
        // the WindowsAppRuntime into a good state. Unlike a simple status check, Initialize can
        // sometimes take several seconds to deploy the packages.
        // These should be run on a separate thread so as not to hang your app while the
        // packages deploy.
        var initializeTask = Task.Run(() => DeploymentManager.Initialize());
        initializeTask.Wait();

        // Check the result.
        if (initializeTask.Result.Status != DeploymentStatus.Ok)
        {
            // The WindowsAppRuntime is in a bad state which Initialize() did not fix.
            // Do error reporting or gather information for submitting a bug.
            // Gracefully exit the program or carry on without using the WindowsAppRuntime.
        }
    }
```

### DeploymentInitializeOptions

#### ForceDeployment

When this API may install newer version of one or more of the WinAppSDK packages (i.e. an update)
and if there are any currently running process(es) associated with these WinAppSDK package(s) (in
other words, if any of the WinAppSDK packages to be updated are currently in use), then this API
will fail installing that WinAppSDK package. But this update to the WinAppSDK packages can be forced
by using DeploymentInitializeOptions object and setting ForceDeployment option before passing it to
this API. This option when set will shut down the application(s) associated with WinAppSDK packages,
update the WinAppSDK packages and restart the application(s).

// OPENISSUE: If this option is set when updating main package, then whether the out of process com
server from the main package such as push Notifications needs to be explicitly restarted needs to be
understood. If restart it is needed, then the API will handle explicitly restarting it. This is
under investigation.

When the API is updating framework package and ForceDeployment option is set, then all dependent
packages that are NOT currently in use will be immediately re-installed to refer to the updated
framework package and all dependent packages that are currently in use will be re-installed, after
they shut down, to refer to the updated framework package.

```C#
    if (DeploymentManager.GetStatus().Status != DeploymentStatus.Ok)
    {
        // Create DeploymentInitializeOptions object and set ForceDeployment option
        // to allow for force updating of the WinAppSDK packages even if they are currently in use.
        var deploymentInitializeOptions = new DeploymentInitializeOptions();
        deploymentInitializeOptions.ForceDeployment = true;

        // Initialize does a status check, and if the status is not OK it will attempt to get
        // the WindowsAppRuntime into a good state by deploying packages. Unlike a simple
        // status check, Initialize can sometimes take several seconds to deploy the packages.
        // These should be run on a separate thread so as not to hang your app while the
        // packages deploy.
        var initializeTask = Task.Run(() => DeploymentManager.Initialize(deploymentInitializeOptions));
        initializeTask.Wait();

        // Check the result.
        if (initializeTask.Result.Status != DeploymentStatus.Ok)
        {
            // The WindowsAppRuntime is in a bad state which Initialize() did not fix.
            // Do error reporting or gather information for submitting a bug.
            // Gracefully exit the program or carry on without using the WindowsAppRuntime.
        }
    }
```

#### OnError

Additional behavior is available if an error occurs in `DeploymentManager.Initialize()`,
per the following logic:

```
DeploymentManager::Initialize(...)
{
    // Only needed supported in packaged processes
    IF IsPackagedProcess()
    {
        // We're not a packaged process. Don't call Initialize
        return OK
    }

    // Do the initialization work
    hr = _Initialize(...)
    if FAILED(hr)
    {
        LogToEventLog(hr, ...)

        // Should we pop the debugger?
        IF IsDebuggerPresent()
        {
            DebugBreak()
        }

        // Should we pop some UI?
        if options.OnError_ShowUI
        {
            MessageBox(...)
        }
    }
    return hr
}
```

Here's the previous example extended with the `Show UI on error` option:

```C#
    if (DeploymentManager.GetStatus().Status != DeploymentStatus.Ok)
    {
        // Create DeploymentInitializeOptions object and set ForceDeployment option
        // to allow for force updating of the WinAppSDK packages even if they are currently in use.
        // Also enable UI if an error occurs so a user can be told about the problem.
        var deploymentInitializeOptions = new DeploymentInitializeOptions();
        deploymentInitializeOptions.ForceDeployment = true;
        deploymentInitializeOptions.OnErrorShowUI = true;

        // Initialize does a status check, and if the status is not OK it will attempt to get
        // the WindowsAppRuntime into a good state by deploying packages. Unlike a simple
        // status check, Initialize can sometimes take several seconds to deploy the packages.
        // These should be run on a separate thread so as not to hang your app while the
        // packages deploy.
        var initializeTask = Task.Run(() => DeploymentManager.Initialize(deploymentInitializeOptions));
        initializeTask.Wait();

        // Check the result.
        if (initializeTask.Result.Status != DeploymentStatus.Ok)
        {
            // The WindowsAppRuntime is in a bad state which Initialize() did not fix.
            // Do error reporting or gather information for submitting a bug.
            // Gracefully exit the program or carry on without using the WindowsAppRuntime.
        }
    }
```

# API Details

```C# (but really MIDL3)
namespace Microsoft.Windows.ApplicationModel.WindowsAppRuntime
{
    [contractversion(3)]
    apicontract DeploymentContract{};

    /// Represents the current Deployment status of the WindowsAppRuntime
    [contract(DeploymentContract, 1)]
    enum DeploymentStatus
    {
        Unknown = 0,
        Ok,
        PackageInstallRequired,
        PackageInstallFailed,
    };

    /// Represents the result of a Deployment Manager method.
    [contract(DeploymentContract, 1)]
    runtimeclass DeploymentResult
    {
        DeploymentResult(DeploymentStatus status, HRESULT extendedError);

        /// Returns the DeploymentStatus of the result.
        DeploymentStatus Status { get; };

        /// Returns the first encountered error if there was an error or S_OK if no error.
        HRESULT ExtendedError{ get; };
    };

    /// This object is used to specify deployment options to apply when using DeploymentManager's
    /// Initialize method
    [contract(DeploymentContract, 2)]
    runtimeclass DeploymentInitializeOptions
    {
        DeploymentInitializeOptions();

        /// Gets or sets a value that indicates whether the processes associated with the
        /// WindowsAppSDK main and singleton packages will be shut down forcibly if they are
        /// currently in use, when registering the WinAppSDK packages.
        Boolean ForceDeployment;

        /// If not successful show UI
        [contract(DeploymentContract, 3)]
        Boolean OnErrorShowUI;
    };

    /// Used to query deployment information for WindowsAppRuntime
    [contract(DeploymentContract, 1)]
    static runtimeclass DeploymentManager
    {
        /// Returns the current deployment status of the current package's Windows App Runtime.
        static DeploymentResult GetStatus();

        /// Checks the status of the WindowsAppRuntime of the current package and attempts to
        /// register any missing WinAppSDK packages.
        [overload("Initialize")]
        static DeploymentResult Initialize();

        /// Checks the status of the WindowsAppRuntime of the current package and attempts to
        /// register any missing WinAppSDK packages, while applying the DeploymentInitializeOptions
        /// passed in.
        [contract(DeploymentContract, 2)]
        [overload("Initialize")]
        static DeploymentResult Initialize(Microsoft.Windows.ApplicationModel.WindowsAppRuntime.DeploymentInitializeOptions deploymentInitializeOptions);
    };
}
```
