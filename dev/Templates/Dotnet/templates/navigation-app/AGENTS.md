# WinUI 3 desktop app with navigation

A WinUI 3 desktop app pre-wired with `NavigationView` for top- or side-nav
patterns, packaged as MSIX and built on the Windows App SDK.

## Project layout

| Path                                          | Purpose                                                                                                  |
| --------------------------------------------- | -------------------------------------------------------------------------------------------------------- |
| `App.xaml`, `App.xaml.cs`                     | Application entry point and lifetime.                                                                    |
| `MainWindow.xaml`, `MainWindow.xaml.cs`       | Top-level window. Hosts a `TitleBar`, a `NavigationView`, and a `Frame` (`NavFrame`) that hosts pages.   |
| `Pages/HomePage.xaml`, `.xaml.cs`             | Default landing page navigated into `NavFrame`.                                                          |
| `Pages/AboutPage.xaml`, `.xaml.cs`            | About page wired to a `NavigationViewItem`.                                                              |
| `Pages/SettingsPage.xaml`, `.xaml.cs`         | Settings page wired to the `NavigationView` settings item.                                               |
| `Package.appxmanifest`                        | App identity, capabilities, visual assets, declarations.                                                 |
| `Assets/`                                     | App icons, tile logos, splash screen, `AppIcon.ico`.                                                     |
| `Properties/`                                 | `launchSettings.json` (Packaged / Unpackaged profiles) and per-arch publish profiles.                    |
| `app.manifest`                                | Native side-by-side manifest (DPI awareness, supported OS versions).                                     |
| `*.csproj`                                    | Target framework, platforms, runtime identifier, and SDK version live here.                              |

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
