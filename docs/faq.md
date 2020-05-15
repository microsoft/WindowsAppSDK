# Frequently Asked Questions
We will update this page often.

### 1. When can I start using components in Project Reunion?
Right away.

These components are available for you to use now and adhere to the “Project Reunion Family Promise” 
that they have a single API for use in all kinds of applications.
- **[WinUI 3 for XAML](https://github.com/microsoft/microsoft-ui-xaml)** in your Win32 app helps you 
build fluent UX with the ease of XAML. This component is part of the Project Reunion 
Family of functionality, building on the identity + packaging + deployment transparent ideas that
Project Reunion supports for your app as well.
- **[C++/WinRT](https://github.com/microsoft/cppwinrt)**, 
**[RUST/WinRT](https://github.com/microsoft/winrt-rs)**, 
and **[C#/WinRT](https://github.com/microsoft/cswinrt)** 
provide language-native projections of Windows, Project Reunion, 
and your own custom types defined in metadata. Consume APIs from the Windows Kit, produce them for 
use by other supported projections, create your own new language projections.
- **[MSIX](https://docs.microsoft.com/en-us/windows/msix/overview)** and 
**[MSIX-Core](https://github.com/microsoft/msix-packaging)** 
let you package your application for distribution to Windows Desktop machines 
via the store or your own delivery pipeline. MSIX-Core lets you use the reuse parts of the MSIX 
packaging story on older versions of Windows.

  _Coming soon_
- **[Microsoft Edge’s WebView2](https://docs.microsoft.com/en-us/microsoft-edge/webview2)**

[Tell us what other components you'd like to see as part of the Project reunion Family](https://github.com/microsoft/ProjectReunion/issues/new/choose)

### 2. Do I need to be packaged to use Project Reunion?
Your app does not need to be packaged to use Project Reunion functionality.
If you are packaged using either a Universal Windows Application package or a Desktop Bridge package, 
referencing the NuGet package is enough to start using Project Reunion right away.
If you have your own installer, we’ll have instructions to carry the Project Reunion components with your app 
and how to install them using some common installers.

### 3. How will I start using Project Reunion?
Add a reference to the Project Reunion NuGet Package when it’s available and rebuild.
For some functionality all you have to do is change your namespace references from “Windows.Thing” to 
“Microsoft.Thing” as the API surfaces are the same.
See the per-area functionality guides for how to turn on additional Project Reunion features.
More advanced Project Reunion features might require changes to your existing code to take full advantage of 
the implementation. Certain features might require additional items like identity or API keys.

### 4. What is a framework package?
Framework packages are ways for apps to share code from a common source, rather than carrying it within the app itself.
Framework packages can be updated automatically on Windows as other apps bring new versions. We’ll use a modified form of Semantic Versioning to make sure your app is never broken due to an interface or behavioral change when using these shared components.

### 5. How do I contribute?
Use this repo’s GitHub Issues to [ask questions, start a discussion or make a feature proposal](https://github.com/microsoft/ProjectReunion/issues/new/choose).
