# WinUI 3 desktop MVVM app

A WinUI 3 desktop app pre-wired with the
[CommunityToolkit.Mvvm](https://learn.microsoft.com/dotnet/communitytoolkit/mvvm/)
source generators (`ObservableObject`, `[ObservableProperty]`,
`[RelayCommand]`), packaged as MSIX and built on the Windows App SDK.

## Project layout

| Path                                          | Purpose                                                                                |
| --------------------------------------------- | -------------------------------------------------------------------------------------- |
| `App.xaml`, `App.xaml.cs`                     | Application entry point and lifetime.                                                  |
| `MainWindow.xaml`, `MainWindow.xaml.cs`       | Top-level window. Hosts a `TitleBar` and a `Frame` that loads `MainPage`.              |
| `MainPage.xaml`, `MainPage.xaml.cs`           | First page, bound to `MainPageViewModel` via `{x:Bind}`.                               |
| `ViewModels/MainPageViewModel.cs`             | Example view model deriving from `ObservableObject`, using `[ObservableProperty]` and `[RelayCommand]`. |
| `Package.appxmanifest`                        | App identity, capabilities, visual assets, declarations.                               |
| `Assets/`                                     | App icons, tile logos, splash screen, `AppIcon.ico`.                                   |
| `Properties/`                                 | `launchSettings.json` (Packaged / Unpackaged profiles) and per-arch publish profiles.  |
| `app.manifest`                                | Native side-by-side manifest (DPI awareness, supported OS versions).                   |
| `*.csproj`                                    | Target framework, platforms, runtime identifier, and SDK version live here.            |

####Prerequisites.md####

####BuildAndRun.app.dotnet.md####

####CommonNextSteps.app.dotnet.md####

####PublishGuide.app.dotnet.md####

####AppArchitectureGuide.md####

####TestingGuide.md####

####PerformanceGuide.md####

####AccessibilityGuide.md####

####GlobalizationGuide.md####

####SecurityGuide.md####

####DocumentationGuide.md####

---

####FrameworkFooter.dotnet.md####
