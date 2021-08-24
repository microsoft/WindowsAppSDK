
# Background

This is the spec for proposal [Windows App Runtime Deployment API #1240](https://github.com/microsoft/WindowsAppSDK/issues/1240).

Windows App SDK (WinAppSDK) deployment consists of a multiple packages, one or more of which is a
mainpackage, all of which are signed and published by Microsoft. Consumers of WinAppSDK will be both
Microsoft and non-Microsoft publishers. In order to have WinAppSDK fully present and functional,
all the packages must be deployed to the system. While the Windows application 
model naturally supports framework dependencies it does not have a means of declaring a dependency
on main packages. This API spec and feature proposal is to provide a means of identifying when
the WinAppSDK dependencies are not satisfied, and if that is the case, provide a means to resolve the
missing dependency.

The key scenario that is expected to have a missing dependency is for packaged MSIX which have
declared the WinAppSDK frameworks as a dependency. In this scenario it is likely the main packages
would be missing because they cannot declare a dependency on main packages and it will not be
deployed by the Store or other mechanisms which only expect a single main package. For MSIX
packages with permissions, this dependency could be immediately resolved online or offline if the
package size is small and the framework carries the dependency.

A class of MSIX packages that are Full Trust or have the packageManagement capability will have
the permissions to immediately resolve the dependency. These packages are the target for this
API. These packages will have the capability to deploy packages and satisfy the dependency.
Since the main packages for the WinAppSDK are expected to be very small, this API has a
streamlined solution for this scenario, which is to carry the WinAppSDK main packages inside
the WinAppSDK frameworks, and leverage the full trust capability of the caller to deploy the main
packages.


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
auto status{Microsoft::Windows::ApplicationModel::WindowsAppRuntime::Deployment::GetStatus()};
if (!status.IsOK())
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
auto status{Microsoft::Windows::ApplicationModel::WindowsAppRuntime::Deployment::Initialize()};
if (!status.IsOK())
{
    return status.ExtendedError();
}
```


# API Details

```c#
namespace Microsoft.Windows.ApplicationModel.WindowsAppRuntime
{
    /// Represents the current Deployment status of the WindowsAppRuntime
    runtimeclass DeploymentStatus
    {
        /// Returns True if WindowsAppRuntime has all required packages at equal or greater version
	    /// than the current framework requires.
        Boolean IsOK{ get; };

        /// Returns True if a Package install is required the WindowsAppRuntime to be in a good
	    /// state.
        Boolean PackageInstallRequired{ get; };

        /// Returns the first encountered error if there was an error initializing or getting the status,
        /// or S_OK if no error.
        HRESULT ExtendedError{ get; };
    }

    /// Used to query deployment information for WindowsAppRuntime
    static runtimeclass DeploymentManager
    {
        /// Returns the current deployment status of Windows App Runtime.
        static DeploymentStatus GetStatus();

        /// Checks the status of the WindowsAppRuntime and attempts to register any packages
	    /// that can be registered. 
        static DeploymentStatus Initialize();
    }
}
```

# Appendix
