# Overview
Dependencies between WindowsAppSDK components are handled by Maestro, a dependency manager 
developed by dotnet as part of the [Arcade Build System](https://github.com/dotnet/arcade). 
ProjectReunion uses the only other instance of maestro (we are the second to use this) and our 
instance is mostly decoupled from the Arcade build system. Maestro can make pull requests [example](https://dev.azure.com/microsoft/ProjectReunion/_git/ProjectReunionInternal/pullrequest/6073284) 
to update the versions of each dependency which is setup via the concept of [branches, channels, and subscriptions](https://github.com/dotnet/arcade/blob/main/Documentation/BranchesChannelsAndSubscriptions.md). The dependencies for the branch are expressed in version.details.xml; for more information on how it works, please take a look at [DependencyDescriptionFormat](https://github.com/dotnet/arcade/blob/main/Documentation/DependencyDescriptionFormat.md).

## Differences between WindowsAppSDK's Maestro and DotNet's Maestro
**Arcade Build System**
In DotNet, the arcade build system and Maestro are tightly coupled. However in WinAppSDK, the arcade build
system is not availble for use. Each of our repositories have their own unique ways to build and hence
using Maestro in WinAppSDK involves making post calls to WinAppSDK's Maestro. 
Templates such as eng\common\AzurePipelinesTemplates\Maestro-PublishBuildToMaestro-Steps.yml are provided
to facilitate posting builds to Maestro so that Maestro can notify dependencies of the incoming version updates.

**Eng\Common**
The eng/common directory is a directory that all of dotnet's repositories share and is maintaned 
automatically through Maestro updates. Updates on the toolset dependency 'Microsoft.DotNet.Arcade.Sdk' 
triggers the update of eng/common and the eng/common of the repository in uri that is referenced in the 
version.details.xml entry for 'Microsoft.DotNet.Arcade.Sdk' is used. 

WindowsAppSDK's Maestro also makes use of eng/common but the contents in this directory are completely 
different from that of dotnets. We use eng/common to store our yml templates and scripts that facilitates
the functions of Maestro between our repositories such as publishing to maestro or building WindowsAppSDk
for integration testing purposes. Furthermore, instead of 'Microsoft.DotNet.Arcade.Sdk', 
WinAppSDK's Maestro looks for 'Microsoft.WinAppSDK.EngCommon' to see whether eng/common needs to be updated.

To bring in updates to Eng/Common, an entry for 'Microsoft.WinAppSDK.EngCommon' is needed in the 
msbuild-sdks section of global.json at the root level directory and also version.details.xml
in ToolsetDependencies section where the uri will point to the ProjectReunionInternal repository.
Detail information in **Steps to onboard new repository to WindowsAppSDK Maestro**

**Coherency Updates are Disabled**
Coherency updates requires Maestro to travel down levels in the dependency tree. 
Since our instance of Maestro does not have permissions to every single repository that the 
original Maestro have and our instance of Maestro is onboarded to one of dotnet's 
repositories where the original Maestro is onboarded as well with many layers of dependencies,
it becomes infeasible and unmaintainable for our Maestro to have the same level of access to 
many different repositories as DotNet's Maestro. Hence Coherency Updates are disabled. 

## Steps to start using and configuring branches, channels, and subscriptions
Join the contributer group for https://github.com/orgs/microsoft/teams/project-reunion. 
You'll need this to login to https://reunion-maestro-prod.westus2.cloudapp.azure.com
Make sure you can login into this address before starting the next steps.

**Install darc client**
The darc client is a command line tool that lets you configure channels, branches, and subscriptions

To setup a darc client,
1) Clone the following repo: https://github.com/dotnet/arcade
2) Install the darc client
```
PS C:\enlistments\arcade> .\eng\common\darc-init.ps1

Tool 'microsoft.dotnet.darc' (version '1.1.0-beta.19057.9') was successfully uninstalled.
Installing Darc CLI version 1.1.0-beta.19081.1...
You may need to restart your command window if this is the first dotnet tool you have installed.
  Restoring packages for C:\Users\mmitche\AppData\Local\Temp\jlbo0wgo.ki2\restore.csproj...
  Installing Microsoft.DotNet.Darc 1.1.0-beta.19081.1.
  Restore completed in 13.12 sec for C:\Users\mmitche\AppData\Local\Temp\jlbo0wgo.ki2\restore.csproj.
You can invoke the tool using the following command: darc
Tool 'microsoft.dotnet.darc' (version '1.1.0-beta.19081.1') was successfully installed.
```
After your darc client is installed, you should be able to launch darc by simply typing in 'darc' in your command line.
If not, you may need to restart.

3) Call 'darc authenticate' with your darc client
This will open up a notepad where you'll be able to set build_asset_registry_base_uri and provide a PAT in three different ways (BAR, Github, AzureDevOps). 
Only one PAT token is needed and I using setting bar_password
Create a new tokens at https://reunion-maestro-prod.westus2.cloudapp.azure.com/Account/Tokens
Copy the new token and paste it to bar_password

build_asset_registry_base_uri will be pointed at the dotnet's maestro uri. We want this to point to WindowsAppSDK's Maestro Uri.
build_asset_registry_base_uri=https://reunion-maestro-prod.westus2.cloudapp.azure.com/

Once these steps are done and you are ready to use the darc client to configure your branches, channels, and subscriptions,
you may refer https://github.com/dotnet/arcade/blob/main/Documentation/Darc.md for more in-depth information on how to use it. 

## Steps to onboard new repository to WindowsAppSDK Maestro
Initial onboarding requirements

Add global.json to root level directory with the following contents.
```
{
  "tools": {
    "dotnet": "6.0.100"
  },
  "msbuild-sdks": {
    "Microsoft.WinAppSDK.EngCommon": "1.0.0-20211207.1-CI"
  }
}
```

Add (or copy) the Versions.props and Version.Details.xml files to your eng\ folder.
Copy the contents of eng\common to your repository.
This folder contains reunion's template that publishes the build to Maestro: Maestro-PublishBuildToMaestro.yml
Add ProjectReunionInternal feed and any other feeds that the repository restores NuGet packages from (This is how your repository will transfer packages between other repository once it recieves a version update from Maestro)
