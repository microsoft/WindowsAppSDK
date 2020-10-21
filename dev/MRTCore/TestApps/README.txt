Instructions for use of the Microsoft.ApplicationModel.Resources NuGet package in a WinUI 3.0 template app

1. Follow the instructions here to setup your local environment required by WinUI 3.0: https://docs.microsoft.com/en-us/windows/apps/winui/winui3/#install-winui-3-preview-2

2. Create an app using one of the WinUI 3.0 VS templates. For example, the C# "Blank App, Packaged (WinUI in Desktop)" template or the C# "Class Library (WinUI in Desktop)" template.

3. Temporary step:
Remove the script code below from the build\Microsoft.WinUI.AppX.targets file in the WinUI NuGet package**.

  <!-- In the case of a WinUI Desktop project, we want to include the AppxPackage targets file to get a PRI file generated,
        but since we aren't actually packaging ourselves in an AppX file, we'll empty out our AppX recipe file properties. -->
  <Import Project="$(MsAppxPackageTargets)" Condition="'$(WindowsAppContainer)' != 'true' and '$(MSBuildProjectExtension)'!='.wapproj'" />
  <PropertyGroup Condition="'$(WindowsAppContainer)' != 'true'">
    <AppxUploadPackageRecipe />
    <AppxPackageRecipe />
  </PropertyGroup>

** Depending on whether the app is a C# or C++ one, the package will be in different locations.
- In the case of C#, the app will use the package installed in the central location (e.g., C:\Users\rohanp.REDMOND\.nuget\packages).
- In the case of C++, the package will be installed in the solution folder.

Notes:
- The reason this is needed:
    - This script code imports the in-box APPX targets file for unpackaged app projects.
    - When the Microsoft.ApplicationModel.Resources NuGet package is installed, the Microsoft.ApplicationModel.Resources.targets file will be imported, and we want that used instead of the in-box APPX targets file.
- This will soon be changed in the WinUI 3.0 repo, after which this step will not be necessary (so long as you are using the new version of the NuGet package).

4. Install the Microsoft.ApplicationModel.Resources NuGet package.
    a. Connect to the following feed: https://mscodehub.visualstudio.com/mrtcore/_packaging?_a=feed&feed=MRTCore.
    b. Make sure you have the “Include prerelease” checkbox selected.
Note: nuget.config in the root dir of the Reunion repo does not contain this feed as it is internal. So, you need to add it by yourself.

Alternate, manual approach:
Download the desired .nupkg using the feed link above, place it in a local folder, add that local folder as a NuGet source and then install it in the app using VS UI by navigating to Tools --> NuGet Package Manager --> Manage NuGet packages for Solution…”.

5. Now, simply build and run!
- The app should build and run just as it would if the Microsoft.ApplicationModel.Resources package was not installed.
- Though the behavior is the same, now the PRI for the resources of the unpackaged app is being generated using the Microsoft.ApplicationModel.Resources.targets file in the NuGet package, not the SDK APPX targets file!

6. Now, use the Microsoft.ApplicationModel.Resources APIs! Sample code can be found at the bottom!
- For the C# WinRT APIs, you need:
    - using Microsoft.ApplicationModel.Resources;
- For the C++/WinRT APIs, you need:
    - #include "winrt/Microsoft.ApplicationModel.resources.h"
    - using namespace winrt::Microsoft::ApplicationModel::Resources;
- For the C APIs, you need:
    - #include "MRM.h" 

Microsoft.ApplicationModel.Resources API sample code

https://mscodehub.visualstudio.com/MRTCore/_git/MRTCore?path=%2FTestApps