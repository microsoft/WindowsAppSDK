# WinUI 3 desktop app with tabs

A WinUI 3 desktop app pre-wired with `TabView` for multi-document or
multi-workspace layouts, packaged as MSIX and built on the Windows App SDK.

## Project layout

| Path                                          | Purpose                                                                                            |
| --------------------------------------------- | -------------------------------------------------------------------------------------------------- |
| `App.xaml`, `App.xaml.cs`                     | Application entry point and lifetime.                                                              |
| `MainWindow.xaml`, `MainWindow.xaml.cs`       | Top-level window. Hosts a `TitleBar` and a `TabView` whose tabs host `Frame`-based content.        |
| `Pages/HomePage.xaml`, `.xaml.cs`             | Default page content for the first tab.                                                            |
| `Pages/AboutPage.xaml`, `.xaml.cs`            | Example secondary page; opened in another tab.                                                     |
| `Package.appxmanifest`                        | App identity, capabilities, visual assets, declarations.                                           |
| `Assets/`                                     | App icons, tile logos, splash screen, `AppIcon.ico`.                                               |
| `Properties/`                                 | `launchSettings.json` (Packaged / Unpackaged profiles) and per-arch publish profiles.              |
| `app.manifest`                                | Native side-by-side manifest (DPI awareness, supported OS versions).                               |
| `*.csproj`                                    | Target framework, platforms, runtime identifier, and SDK version live here.                        |

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
