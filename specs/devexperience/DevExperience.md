# Reunion Developer Experience

## 1.0 - Overview
This spec will detail the design of how the Reunion developer experience will work. Through analysis of the current landscape of Windows development, there are a few important items that were found:
1.	The Windows Application Packaging (WAP) project increases build time by 40%
2.	Requiring the WAP creates a disjointed developer experience, where developers trying to create Win32 apps have a different workflow than UWP developers.
3.	Therefore, to provide our customers with the best inner-loop, and to unify the experience for Win32 and UWP developers, we must not require the WAP for our core user scenarios.

If we are to remove the WAP project, we then must ask ourselves the following questions:
1.	What kicks in the MSIX Package tooling?
2.	Can developers opt-out of the pri generation?
3.	How does building a Sparse Package look?
    - A Sparse Package is a Win32 app that has identity, but isn’t using MSIX.
    - This means there is a package.appxmanifest and a SxS manifest
4.	What to do with the Windows store /start menu assets that aren’t used in unpackaged applications
5.	How does an existing UWP developer move forward and use this?
6.	How does an existing WPF or WinForms developer move forward and use this?

## 2.0 – Definitions
- Reunion – The effort to unify the Win32 and UWP platforms
- Reunion Tooling – MSBuild and VisualStudio tooling used to build Reunion apps.
- Workflow – The steps a developer will take in Visual Studio to be successful using Reunion.
- WAP – A project used to generate an .msix or .msixbundle.
- Sparse Package – An unpackaged Win32 app with package Identity via registration of an .msix.

## 3.0 Guiding Principles
Below is a list of some guiding principles to ground this proposal
1.	Easy for developers to understand.
2.	Easy for developers to change between the four different app model types:
	- Unpackaged
    - Sparse Package
    - Packaged Desktop
    - UWP
3.	Easy for developers to migrate their existing Win32 and UWP apps.
a.	Maintain compat with Microsoft.AppxPackage.targets

## 4.0 Key Design Elements
In order to satisfy principles 2 and 3 above, there are some key design elements which need to be taken into account:
1.	A single MSBuild property, `WindowsPackageType`, will enable developers to easily change their application type. It is an enum value with the following four options: 
    - `None`
    - `Sparse`
    - `Desktop`
    - `Universal`
    - Potential future options: `Framework` (for framework package)
2.	The package.appxmanifest file cannot require changes between Sparse, Packaged Desktop, and UWP. The tooling will generate the appropriate appxmanifest.xml based on the project being built.
3.	There must be an Item Template for the package.appxmanifest
4.	The default splash screen and start menu assets will be provided by the tooling. The same behavior of preventing store submissions for apps which use these assets will still exist. 
5.	A migration tool will be provided for migrating projects
    - Work for this has started with the https://github.com/dotnet/try-convert tool.
    - This tool needs to be updated for .vcxproj.
    - This tool will update code, project files, and manifest files
    - Update nuget references to WinUI3 supported packages (i.e. Win2D & WCT)
6.	The existing Manifest designer tool in VS must work for these projects
7.	The existence of a Package.appxmanifest file will enable Packaged Desktop apps by default.
8.	The Reunion NuGet package will provide tooling for generating the Sparse Package and Dynamic Dependencies registration code. (link to existing issues)
a.	[.NET Only] A source generator will be provided to accomplish this
b.	[C++ only] A build task will be provided for this
9.	The Reunion meta package will provide tooling for generating typed access to Resource strings for resw resources, similar to how resx works in .NET
a.	[.NET Only] A source generator will be provided this.
b.	[C++ only] A build task will be provided for this
10.	The existing Publish UI will be enabled for creating and publishing app packages to the Microsoft Store.


## 5.0 - Developer Workflow
This section goes into more fine grain detail about the developer experience that will come with developers who are using Project Reunion. It will expand off the Key Design Elements and Principles sections, and articulate where each of those comes into play in the overall story of Reunion.

### 5.1 – Migration and Compat
This section will highlight the basic workflow for developers looking to use Reunion, as well as highlight some basic high-level requirements that the tooling must guarantee. The section on MSIX packaging will go into more detail on how we will simplify the developer story, while maintaining compat at the same time.

#### 5.1.1 - Migrating Existing Win32 Apps
App developers which are migrating existing Win32 Apps will do the following:
1.	Install Reunion VSIX
2.	Add package reference to Reunion
At this point, the developer can stop and have an unpackaged app, with the ability to use MRT. None of the MSIX package tooling will run, because there is no existence of a Package.appxmanifest file. If the developer would like to create a packaged Desktop app, then they do the following:
3.	Add Package.appxmanifest file to the project
After this step, if they’d prefer to create a Sparse Package, they would add this to their project file:
<WindowsPackageType>Sparse</WindowsPackageType>
Question: could we update try convert to give existing Win32 apps Sparse by default?

### 5.1.2 - Migrating Existing UWP Apps
Existing UWP applications will require being converted to WinUI3 applications first. The following are the steps a developer will run in order to migrate their apps:
1.	Run the try-convert tool
a.	If the user wants a desktop app, they will then update <WindowsPackageType> in their project file.
2.	Fix up any compilation errors that may exist

### 5.1.3 - Other Compat/Migration Concerns
None of the tooling will be WinUI/Reunion specific, and the tooling could be used for all existing UWP apps. However, the hypothesis is that trying to move existing UWP apps to the new tooling pipeline would result in noise and over-complicate the story, as well as require more documentation updates. Therefore, we will not be advertising it as such. However, one of the key components of the tooling will be that it is easily migratable, and therefore we cannot require users to make any changes to their existing build customizations. By design, this forces the tooling to maintain compatibility.

With that being said, one thing that will be supported is users having a mix of old UWP and newer Reunion projects in the same .sln file or repository. This will allow developers to migrate slowly at their own pace. In order to do this, the task assemblies that ship as part of Reunion must be renamed. Otherwise, MSBuild will mistakenly use the wrong assemblies.

### 5.1.4 – Helping Developers call the right APIs
Many WinRT APIs do not work in certain scenarios. Whether they don’t work because of the difference in App model, or whether they require Package Identity, we will help developers where possible, to make the right API calls in their application. We will generate a list of API calls that don’t work in Win32, as well as APIs that require Package identity, and provide tooling for .NET developers through a Roslyn Analyzer.
Here is the list of APIs that we can use as a starting point: [Windows Runtime APIs available to a packaged desktop app (Desktop Bridge)](https://docs.microsoft.com/en-us/windows/apps/desktop/modernize/desktop-to-uwp-supported-api)

Prior Art: We started on a Roslyn Analyzer for [incompatible WinUI3 APIs](https://github.com/dotnet/try-convert/blob/feature/winui/src/WinUI.Analyzer/Analyzer/DeprecatedUseAnalyzer.cs).

#### 5.1.4.1 – Analyzer for App Authors
With the WindowsPackageType property, we can expose the exact type of application the customer is building, and therefore provide the exact type of information that they need.

#### 5.1.4.2 – Analyzer for Library authors
Since library authors won’t set the WindowsPackageType property, the analyzer for library authors should be general purpose, and provide messages such as “this API behaves differently in Desktop vs UWP, add a runtime check or use <replacement API>”.

### 5.2 – New Apps and WinUI3

#### 5.2.1 - New WinUI3 Apps
Creating new WinUI3 apps will have the proper manifest files included, and project files by design. Developers will use Visual Studio to create new projects, and .NET developers will have the options of using the .NET CLI. There will be a separate doc more specifically focused on the new project experience for Windows developers that will go into more detail.

##### 5.2.1.1 - Manifest Files
All new WinUI3 apps will have a package.appxmanifest file, but the SxS manifest should be removed. The tooling will supply default manifest files, which it can use mt.exe to merge. The “default” manifests include:
-	WinRT registrations for WinUI (and Reunion ) types
-	PerMonV2 (and other DPI awareness) settings
The reason for this is that over time, we want to consolidate on a single manifest. This certainly won’t be possible today, and we won’t try to tell that story yet. There are things that can only be accomplished with a SxS manifest, and those scenarios will absolutely still work. Note, that in order to consolidate on a single manifest, we don’t need to change the OS or runtime implementation. We could use the package.appxmanifest format to produce a SxS manifest for unpackaged apps, just like we produce an appxmanifest.xml file for packaged/sparse apps today.
Another reason for having a default package.appxmanifest is that we want to lead developers down the pit of success, and give them easy and non-intrusive updates to using the latest Windows tech. Sparse win32 packages allow unpackaged apps to have Identity, and use Windows features like the Share target and notifications.

#### 5.2.2 - WinUI3 Specific Tooling Requirements
Since WinUI3 is the only UI framework which will support all the Windows app models, the templates for WinUI3 must work in both UWP and Desktop applications. This means that an app developer can just toggle the WindowsPackageType property, to change the app they are building.
Since WinUI has C++ customers, a special tool for generating the main method (i.e. Xaml compiler), which registers the Sparse Package and Dynamic Dependencies registration will be required.

#### 5.2.3 - Choosing your Windows APIs
The UWP target platform selector is problematic with Reunion. The Reunion APIs are designed to ship out of band with the OS, and with this, users are able to select Windows versions that are not compatible with their Reunion packages. This UI should just be disabled, since we hard code the TargetPlatformVersion (TPV) in the project file to match what reunion supports. The default TargetPlatformMinVersion (TPMV) if not specified, will match the TPV, and developers can change it by setting the TPMV property. When migrating existing UWP apps, they will likely have TPMV set, and the existing property will be respected.

### 5.3 – MSIX Packaging
This section will go into more detail for the MSIX packaging story, and the steps that users will take in Visual Studio, or from the command line, in order to successfully build MSIX packages.

#### 5.3.1 – Single-Exe Packages
Single-exe packages are the default, and like UWP projects today, won't require the Windows Application Packaging (WAP) project. Developers will be able to build and debug these apps directly in Visual Studio.

#### 5.3.2 - Multi-Exe packages
Many apps, like the Windows terminal, package multiple exes into their msix. For this reason, the .wapproj will not be fully retired. However, this project can solely be used for packaging their app for distribution, and not get in the way of their inner-loop.

#### 5.3.3 - Creating App Bundles and Publishing to the Microsoft Store
In this section, we’ll be using command line interface (cli) examples for simplicity and greater articulation of how the technology works. While all these actions are accomplishable through the VS UI, developers still require cli workflows in their day-to-day, and especially for Continuous Integration (CI) environments. The VS UI will be a nice wrapper around these tasks.

Today, in order to build app bundles from the cli, there is a complicated incantation that you need to specify on the command line:

>msbuild WindowXamlAppCs.sln /m /p:Platform=x64 /p:UapAppxPackageBuildMode=StoreOnly /p:AppxBundle=Always /p:AppxBundlePlatforms="x64|arm64" /p:Configuration=Release

This invokes MSBuild in a recursive manner which rebuilds the project for multiple architectures. This behavior adds enormous complexity to the build and is difficult to maintain. Furthermore, a complex build is a slow build, and so this behavior *will not* be carried forward. Instead, we will only build individual .msix files per architecture, and we will enable developers to submit their apps to the store either by using the [Windows Store Azure DevOps task](https://marketplace.visualstudio.com/items?itemName=MS-RDX-MRO.windows-store-publish), and the VS `Publish->Create App Packages` UI will be updated to handle individual .msix files.

TODO: More details about the steps the developer takes using Azure DevOps pipeline.

#### 5.3.4 - C++ Developer Experience
We want to make sure any improved experience is still familiar. And since there is an existing `GenerateAppxPackageOnBuild` property, we’ll utilize that, and build off of it, to make a simplified story for building an .msix.                                                                                                                                                                                                                                                                                 > msbuild WinUI3AppCpp.sln /m /p:Platform=x64 /p:Configuration=Release /p:GenerateAppxPackageOnBuild=true 

#### 5.3.5 - .NET Developer Experience
With .NET Core, there is the new SDK-style project format, which presents greatly simplified project format and improved experience for developers. Because of this, we want the Reunion workflow to be familiar to .NET developers.
While the above MSBuild properties (GenerateAppx*OnBuild) will work for .NET developers, “Build” is not the verb used for preparing your app for distribution. The verb for .NET is “Publish”, and the Publish stage of the Build is the only place where you can do certain things like AOT compile, assembly trimming, and self-contained deployment. Because of this, we will introduce two new properties, which are similarly named:

For helpful links that go into more detail on this, see [Application publishing - .NET](https://docs.microsoft.com/en-us/dotnet/core/deploying/). One key aspect of this that we will be promoting, is the use of [Publish Profiles](https://docs.microsoft.com/en-us/aspnet/core/host-and-deploy/visual-studio-publish-profiles?view=aspnetcore-5.0), which enable developers to configure how they deploy their application.

Here is the new, simplified incantation for .NET developers that will work for Reunion:
> dotnet publish WinUI3AppCs.sln /p:PublishProfile=win10-x86.pubxml 

**Example: Contents of a PublishProfile**
Here is an example of a publish profile that would generate an .msix that runs in the UWP sandbox:

```xml
<?xml version="1.0" encoding="utf-8"?>
<!--
https://go.microsoft.com/fwlink/?LinkID=208121. 
-->
<Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <PropertyGroup>
    <PublishProtocol>FileSystem</PublishProtocol>
    <Platform>arm64</Platform>
    <RuntimeIdentifier>win10-arm64</RuntimeIdentifier>
    <PublishDir>bin\$(Configuration)\$(TargetFramework)\$(RuntimeIdentifier)\publish\</PublishDir>
    <SelfContained>true</SelfContained>
    <PublishSingleFile>False</PublishSingleFile>
    <PublishReadyToRun>True</PublishReadyToRun>
    <PublishAppxPackage>true</PublishAppxPackage>
    <WindowsPackageType>Universal</WindowsPackageType>
  </PropertyGroup>
</Project>
```

It would deploy the .msix to a location on disk, where the VS tooling pipeline would pick it up and publish it to the store. Future improvements can be made to introduce a new `<PublishProtocol>WindowsStore</PublishProtocol>`, but are not required for V1.

##### 5.3.5.1 - Publish UI for .NET6 Apps
As described above, .NET has a different, albeit very similar, definition of Publish. There is a specific UI that developers can use to publish to an Azure service or Folder location. This action implies you are building an unpackaged app. This context menu in VS is similar to the existing UWP `Publish->Create App Packages`, but just says `Publish`. Having both UIs enabled at the same time may not be ideal and could possibly be confusing, but it has the advantage of being familiar to existing UWP devs who are migrating to WinUI3. The amount of work to design and build a whole new UI to avoid this possible confusion is not worth the effort, especially since we don’t know for certain that it will be a problem. 
The proposal is to first re-enable the existing UI, which has been investigated and should be a simple change. We’ve proven the UI works, because there is actually a way to enable it today, but it involves hand crafting your own appx manifest. That is not a scenario we want to tell customers about, but it gives us confidence that the investment will be worthwhile. Once this scenario is enabled, we can get feedback from customers.
