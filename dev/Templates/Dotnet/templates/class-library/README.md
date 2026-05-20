# WinUI 3 class library

A WinUI 3 class library — a reusable component (controls, helpers,
services, resources) that other WinUI 3 desktop apps can reference.

A class library has **no app shell**: no `App.xaml`, no
`Package.appxmanifest`, no entry point. It's consumed by an app project,
which is what gives it identity at runtime.

## Project layout

| Path                    | Purpose                                                                       |
| ----------------------- | ----------------------------------------------------------------------------- |
| `Class1.cs`             | Starter type. Rename it or delete it as you add real types.                   |
| `*.csproj`              | Target framework, platforms, runtime identifier, and SDK version live here.   |

XAML controls, styles, and resource dictionaries can be added with
`dotnet new winui-templatedcontrol`, `winui-usercontrol`,
`winui-resourcedictionary`, and friends.

####Prerequisites.md####

####BuildAndRun.library.dotnet.md####

####CommonNextSteps.library.dotnet.md####

####AppArchitectureGuide.library.md####

####TestingGuide.library.md####

####PerformanceGuide.md####

####AccessibilityGuide.md####

####GlobalizationGuide.md####

####SecurityGuide.md####

####DocumentationGuide.md####

---

####FrameworkFooter.dotnet.md####
