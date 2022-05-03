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

To makes updates to Eng/Common, please do not make them in the non parent repo. Our parent repo for eng/common
is the ProjectReunionInternal repository.
To publish changes, please run the Maestro-UpdateEngCommon pipeline on the main branch. 

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
After your darc client is installed, you should be able to launch darc by simply typing in 'darc' 
in your command line.
If not, you may need to restart.

NOTE: many of the default values you see next when using the darc commands are dotnet related. 
Please ignore or replace those values with our own such as for the build_asset_registry_base_uri

3) Call 'darc authenticate' with your darc client
This will open up a notepad where you'll be able to set build_asset_registry_base_uri and provide
three different PATs (BAR, Github, AzureDevOps). 
Each respective PAT is required to make configuration changes to AzureDevOps or Github repo

For GitHub:
The PAT can be retrived from "Personal access tokens" section on the Developer settings in GitHUB
There is an extra step where you must configure SSO especially for the "Microsoft" organization so that you can make maestro config changes for the Foundation repositories. This will prevent 403 (Forbidden) errors when. 

For AzureDevOps
The PAT can be retrived from "Personal access tokens" section on the settings dropdown menu. 
NOTE: To make maestro config changes on azure devops repositories, you'll need the corresponding
PAT from the correct organization that the repositories are under. 

For BAR:
Create a new tokens at https://reunion-maestro-prod.westus2.cloudapp.azure.com/Account/Tokens
Copy the new token and paste it to bar_password

build_asset_registry_base_uri will be pointed at the dotnet's maestro uri. We want this to point to 
WindowsAppSDK's Maestro Uri.
build_asset_registry_base_uri=https://reunion-maestro-prod.westus2.cloudapp.azure.com/

Once these steps are done and you are ready to use the darc client to configure your branches, 
channels, and subscriptions.
You may refer https://github.com/dotnet/arcade/blob/main/Documentation/Darc.md for more in-depth 
information on how to use it. 

## Steps to onboard new repository to WindowsAppSDK Maestro
Initial onboarding requirements
These can be done in any particular order. 

** Basic requirements **
Add (or copy) the Versions.props and Version.Details.xml files to your eng\ folder.

Get access to ProjectReunionInternal feed and any other feeds that the repository restores NuGet packages
from. ProjectReunionInternal feed is the main feed that WindowsAppSDK repositories uses to restore packages from. 

** Eng/Common Onboarding **
Copy the contents of eng\common from ProjectReunionInternal to the root of the repository keeping the same folder paths.
This folder contains reunion's template that publishes the build to Maestro: Maestro-PublishBuildToMaestro.yml

To get automatic updates to eng/common
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
Add Microsoft.WindowsAppSDK.EngCommon dependency to ToolsetDependencies where the uri is the link to
ProjectReunionInternal repo
```
<ToolsetDependencies>
  <Dependency Name="Microsoft.WinAppSDK.EngCommon" Version="1.0.0-20211213.0-CI">
    <Uri>https://dev.azure.com/microsoft/ProjectReunion/_git/ProjectReunionInternal</Uri>
    <Sha>c29bc59c779108f3818a0efb0e467c2b4bb6cb47</Sha>
  </Dependency>
</ToolsetDependencies>
```

** GitHub Repositories **
Install the github App https://github.com/apps/reunion-maestro on your org/repository

** AzureDevOps Repositories **
Give reunion-maestro-bot@microsoft.com contributers permissions.
For automatic completion, in branch securities, "ByPass Policies when completing pull requests" should be allowed.

If the azure devops repositories is in a new organization that has not been onboarded, please contact the 
ProjectReunionES team to onboard the org to the Maestro service. 
This involves adding a new entry in the WindowsAppSDK's equivalent of 
https://github.com/dotnet/arcade-services/blob/main/src/Maestro/SubscriptionActorService/.config/settings.json
with the PAT from reunion-maestro-bot@microsoft.com

## Creating subscriptions with automatic completions ##
When adding a new subscription, please include the Merge Policies below with all the ignoreChecks 
```
Merge Policies:
- Name: AllChecksSuccessful
  Properties:
    ignoreChecks:
    - Require a merge strategy
    - Required reviewers
    - Minimum number of reviewers
    - Comment requirements
    - Work item linking
```
Note: At least one required check on the pull request must run successfully for Maestro to auto complete. 

