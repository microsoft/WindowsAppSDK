Instructions for building the sample apps in this folder

1. Temporary step:
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

2. Install the Microsoft.ApplicationModel.Resources NuGet package.
    a. Connect to the following feed: https://mscodehub.visualstudio.com/mrtcore/_packaging?_a=feed&feed=MRTCore.
    b. Make sure you have the “Include prerelease” checkbox selected.
Note: nuget.config in the root dir of the Reunion repo does not contain this feed as it is internal. So, you need to add it by yourself.

3. Now, simply build and run!


Instructions for use of the Microsoft.ApplicationModel.Resources NuGet package in a WinUI 3.0 template app

1. Follow the instructions here to setup your local environment required by WinUI 3.0: https://docs.microsoft.com/en-us/windows/apps/winui/winui3/#install-winui-3-preview-2

2. Create an app using one of the WinUI 3.0 VS templates. For example, the C# "Blank App, Packaged (WinUI in Desktop)" template or the C# "Class Library (WinUI in Desktop)" template.

3. Follow steps 1 to 2 in "Instructions for building the sample apps in this folder" above.

4. Now, use the Microsoft.ApplicationModel.Resources APIs! Sample code can be found in this folder!
- For the C# WinRT APIs, you need:
    - using Microsoft.ApplicationModel.Resources;
- For the C++/WinRT APIs, you need:
    - #include "winrt/Microsoft.ApplicationModel.resources.h"
    - using namespace winrt::Microsoft::ApplicationModel::Resources;
- For the C APIs, you need:
    - #include "MRM.h"
