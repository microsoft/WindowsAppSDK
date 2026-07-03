# WinUI 3 unit test project

A WinUI 3 unit test project — an MSIX-packaged MSTest container that can
exercise WinUI 3 code in-process, with full access to
`Microsoft.UI.Xaml.*` types and a real `DispatcherQueue`.

The test process is itself a WinUI 3 app (`UnitTestApp.xaml`) that hosts
the MSTest runner. Tests can construct controls, raise events, and await
dispatcher work the way real app code does.

## Project layout

| Path                                              | Purpose                                                                                |
| ------------------------------------------------- | -------------------------------------------------------------------------------------- |
| `UnitTestApp.xaml`, `UnitTestApp.xaml.cs`         | Test host application. Bootstraps the MSTest runner.                                   |
| `UnitTestAppWindow.xaml`, `UnitTestAppWindow.xaml.cs` | Hidden window the host application uses for runner UI / dispatcher.                |
| `UnitTests.cs`                                    | Starter `[TestClass]` with example `[TestMethod]`s. Add more test classes alongside.   |
| `Package.appxmanifest`                            | Test container identity. MSIX is required so WinUI 3 types can be exercised.           |
| `Assets/`                                         | Test container icons and visual assets.                                                |
| `Properties/`                                     | `launchSettings.json` and per-arch publish profiles for the test container.            |
| `app.manifest`                                    | Native side-by-side manifest (DPI awareness, supported OS versions).                   |
| `*.csproj`                                        | Target framework, platforms, runtime identifier, MSTest references, and SDK version.   |

####Prerequisites.md####

####BuildAndRun.unittest.vsix.md####

####CommonNextSteps.unittest.vsix.md####

####TestingGuide.unittest.md####

####PerformanceGuide.md####

####AccessibilityGuide.md####

####GlobalizationGuide.md####

####SecurityGuide.md####

####DocumentationGuide.md####

---

####FrameworkFooter.vsix.md####
