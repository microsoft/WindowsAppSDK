
# Background

This is the spec for proposal [Windows App Runtime Deployment API #1240](https://github.com/microsoft/WindowsAppSDK/issues/1240).

Windows App SDK (WAS) deployment consists of a Main package, multiple Framework packages, and for
unpackaged apps a set of Dynamic Dependency packages, all of which are published by Microsoft 
and are Store-Signed. Consumers of WAS will be both Microsoft and non-Microsoft publishers.
In order to have WAS fully present and functional, the WAS Framework and Main packages must be 
deployed to the system. While the Windows Application Model naturally supports framework
dependencies it does not have a means of declaring a dependency on Main packages. This API spec
and feature  proposal is to provide a means of identifying when the WAS dependencies are not
satisfied, and if that is the case, provide a means to resolve the missing dependency. 

The key scenario that is expected to have a missing dependency is for packaged MSIX which have
declared the WAS frameworks as a dependency. In this scenario it is likely the main package would
be missing because they cannot declare a dependency on the main package and it will not be
deployed by the Store. For MSIX packages with permissions, this dependency could be immediately
resolved online or offline if the package size is small and the framework carries the dependency.

A class of MSIX packages that are Full Trust or have package management capabilities, such as
Centennial MSIX packages will have the permissions to immediately resolve the dependency. These
packages are the target for this version of the API. These packages will have the capability
to deploy packages and satisfy the dependency. Since the Main Package for WAS is expected to be
very small, this API has a streamlined solution for this scenario, which is to carry the WAS
main packages inside the WAS framework, and leverage the full trust capability of the package
to deploy the main package. A later release will address how to resolve the missing packages
for UWPs when they become supported.


# Description

When a Windows App SDK (WAS) consuming Centennial package is deployed from the Store, it is
expected to only have the App package and frameworks, and the WAS main package may not be present,
or may not be at the desired version. This API enables a developer to detect when the required WAS
main and/or framework packages are not present and take corrective action.

Since this API is part of the WAS framework, the framework itself must be present.
For MSIX packages, the framework must be listed as a dependency in the application manifest and
will not be deployable without a min version being present. 

Developers must not assume that the WAS main package is present, or that the version
present is the minimum version required to support the feature set they expect. Instead, this API
should be used to validate the WAS is the correct version and all required packages are present.

The developer scenarios for this API is to answer the questions:
1. Does this system have the min version of the Windows App SDK I require?
2. What do I do to resolve this if it doesn't?

The API addresses #1 by a simple query of the version they seek and a possible check for OS
updates. #2 has two possible answers. First is direct resolution by the developer by acquiring and
installing the packages if possible. Since the main packages are small and the target developer
scenario will have permissions to deploy them, we will minimize developer and user pain by
including the main package MSIX packages within the framework, and this API will allow for the
deployment of that package if needed.

For this release, packages without permission to deploy are not supported, and future versions
will have solutions for such packages.

# Examples

## GetStatus

This is the means by which an app or program can call to verify the runtime packages is present to
a minimum version needed by the loaded framework. It should be called once after activation before
trying to use the Windows App Runtime. This method returns a WindowsAppRuntime object
that describes the current deployment state of the Windows App Runtime.

Developers call this method without parameters, as all information about the version, channel, and
architecture are derived from the current framework loaded and we assume any main packages needed
by those frameworks are included within those framework packages.

This method is good to identify if there is possible work required in the form of package install
which may take several seconds to complete.

```C++
auto status =
Windows::ApplicationModel::WindowsAppRuntime::Deployment::GetStatus();
if (!status.IsOK())
{
    ...
}
```

## Initialize

Does a status check and if any packages are required for install, attempts to register those packages
and get the WindowsAppRuntime into an OK state. This will perform package install if possible. The
returned WindowsAppRuntimeStatus will contain the first error if one occurs during package install.


```C++
auto status =
Windows::ApplicationModel::WindowsAppRuntime::Deployment::Initialize();
if (!status.IsOK())
{
    return status.ExtendedError();
}
```


# API Details

```c#
namespace Windows.ApplicationModel.WindowsAppRuntime
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
