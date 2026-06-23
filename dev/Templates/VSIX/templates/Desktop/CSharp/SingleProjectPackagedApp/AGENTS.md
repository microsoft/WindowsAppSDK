# WinUI 3 desktop app

A blank WinUI 3 desktop app packaged as MSIX, built on the Windows App SDK.

## Project layout

| Path                                    | Purpose                                                                                 |
| --------------------------------------- | --------------------------------------------------------------------------------------- |
| `App.xaml`, `App.xaml.cs`               | Application entry point and lifetime.                                                   |
| `MainWindow.xaml`, `MainWindow.xaml.cs` | Top-level window. Hosts a `TitleBar` and a `Frame` (`RootFrame`) that displays pages.   |
| `MainPage.xaml`, `MainPage.xaml.cs`     | First page navigated to inside `RootFrame`. Page-level UI goes here.                    |
| `Package.appxmanifest`                  | App identity, capabilities, visual assets, declarations.                                |
| `Assets/`                               | App icons, tile logos, splash screen, `AppIcon.ico`.                                    |
| `Properties/`                           | `launchSettings.json` (Packaged / Unpackaged profiles) and per-arch publish profiles.   |
| `app.manifest`                          | Native side-by-side manifest (DPI awareness, supported OS versions).                    |
| `*.csproj`                              | Target framework, platforms, runtime identifier, and SDK version live here.             |

####Prerequisites.md####

####BuildAndRun.app.vsix.md####

####CommonNextSteps.app.vsix.md####

####PublishGuide.app.vsix.md####

####AppArchitectureGuide.md####

####TestingGuide.md####

####PerformanceGuide.md####

####AccessibilityGuide.md####

####GlobalizationGuide.md####

####SecurityGuide.md####

####DocumentationGuide.md####

---

####FrameworkFooter.vsix.md####
