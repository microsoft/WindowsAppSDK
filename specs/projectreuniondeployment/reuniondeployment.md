
# Background

This is the spec for proposal [Project Reunion Deployment Information API #155](https://github.com/microsoft/ProjectReunion/issues/https://github.com/microsoft/ProjectReunion/issues/155).

Reunion consists of a Main package and framework published by Microsoft while consumers of Reunion will often be non-Microsoft publishers. In order to have Reunion fully present and functional, the Reunion Framework and Main packages must both be deployed, and depending on the operating system, OS updates may also be required.  While the Windows Application Model naturally supports framework dependencies, it does not have a means of declaring a dependency across Main packages of different publishers. This API spec and feature proposal is to provide a means of identifying when the Reunion dependencies are not satisfied, and if that is the case, provide URIs for where the missing dependencies could be satisifed by the user and/or the developer.

It is expected that we may be operating under conditions in which the user may not have permissions for the program or app package to resolve the dependency on its own, or such dependencies may require operating system updates in order to deploy. While this may be disruptive to the user to have to resolve this issue, it can be mitigated by usage of AppInstaller and Store updates to keep the Reunion packages up-to-date to minimize the likelihood and frequency of the user requiring direct action. The ideal situation is that
the user needs to do this at most once, and auto-update mechanisms take care of future updates. It can be completely mitigated on newer operating systems that can have the updates and Reunion packages already pre-installed. Still, the developer of programs and app packages can never assume that the version of Reunion they require is already available, so this feature will provide an API to check that availability and provide links for resolving any deployment issues. This API could be expanded in the future to wrap deployment behavior for software capable of deploying packages and/or OS updates to reduce the end-user friction and minimize potential for developers to lose customers due to dropoff during the acquistion of Project Reunion.

# Description

When a Reunion-consuming package or app is deployed, it is expected to only
have the App package or installer itself, and the Reunion main and framework
packages may not be present, or may not be at the desired version. This API
enables a developer to detect when the required Reunion main and/or
framework packages are present, and to direct the user to the appropriate
resources to acquire or update Reunion if it is absent or requires updates.

Since this API is part of the Reunion framework, the framework itself must be
present. For MSIX packages, the framework must be listed as a dependency in
the application manifest and will not be deployable without a min version being
present. For Win32 programs and installers the Reunion bootstrapper
will try to load the framework and error out with a similar instruction on
how to resolve the missing dependencies for Reunion.

Developers must not assume that the Reunion main package is present, or that the version present is the minimum version required to support the feature set they expect. Instead, this API should be used to validate any
Reunion requirements and direct the user to resolve any missing dependencies.

The developer scenarios for this API is to answer the questions:
1. Does this system have the min version of Reunion I require?
2. What do I do to resolve this if it doesn't?

The API addresses #1 by a simple query of the version they seek and a possible check for OS updates. #2 has two possible answers. First is direct resolution by the developer by acquiring and installing the packages if possible. Some programs will not have permission or motivation to do this, so the second answer is providing a link up to the user where the user can take action to install the package. The API will address this scenario by providing an answer as to what is required, where to get it, and where to go for instruction.


# Examples

## GetProjectReunionStatus

This is the means by which an app or program can call to verify Reunion is present to a minimum version. It should
be called once after activation before trying to use Reunion functionality. This method returns a ProjectReunionStatus object that describes the current deployment state of Project Reunion.

```C++
Windows::ApplicationModel::PackageVersion version{1, 0, 0, 0};
auto status = Microsoft::Management::Deployment::ProjectReunionDeployment::GetProjectReunionStatus(version);
if (!status.IsOK())
{
    ...
}
```

## GetProjectReunionPackageLink

Provides a direct install link to deploy the latest version of ProjectReunion. If no OS Updates are required and the program or app has permissions to deploy packages, this can directly resolve the missing dependency without burdening the user.

```C++
Windows::Foundation::Uri packageLink = Microsoft::Management::Deployment::ProjectReunionDeployment::GetProjectReunionPackageLink();
```

## GetProjectReunionInstallInformationLink

Provides a user-friendly link to acquire the latest version of Reunion and any OS updates that may be required. This can be used to guide the user to where they can resolve the missing dependency.

```C++
Windows::Foundation::Uri installInformationLink = Microsoft::Management::Deployment::ProjectReunionDeployment::GetProjectReunionInstallInformationLink();
```

# API Details

```c#
namespace Microsoft.Management.Deployment
{
    /// Represents the current Deployment status of Project Reunion
    runtimeclass ProjectReunionDeploymentStatus
    {
        /// Returns True if Reunion is the desired Version and no updates or packages
        /// are required.
        Boolean IsOK { get; };

        // Returns True if Windows Updates are required for Project Reunion.
        Boolean WindowsUpdatesRequired { get; };

        // Returns True if a Package install is required for Project Reunion.
        Boolean PackageInstallRequired { get; };
    }

    /// Used to query deployment information for Project Reunion
    static runtimeclass ProjectReunionDeployment
    {
        /// Returns the current deployment status of Project Reunion and whether it meets the 
        /// minimum package version specified.
        static ProjectReunionDeploymentStatus GetStatus(Windows.ApplicationModel.PackageVersion packageVersion);

        /// Returns a URI for the direct install link for the latest Project Reunion Package.
        static Windows.Foundation.Uri GetProjectReunionPackageLink();

        /// Returns a URI for a user-friendly install instruction for Project Reunion and any
        /// OS updates that may be required.
        static Windows.Foundation.Uri GetProjectReunionInstallInformationLink();
    }
}
```

# Appendix

