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

## Prerequisites

See [Set up your dev environment for Windows App SDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/set-up-your-development-environment).

## Build and run

- VS: **F5**.
- CLI: `msbuild /restore /p:Configuration=Debug /p:Platform=x64`.

See [MSBuild properties for packaging projects](https://learn.microsoft.com/windows/msix/desktop/desktop-to-uwp-packaging-dot-net#build-the-package-from-the-command-line).

## Common next steps

- Add items: *Add → New Item → WinUI*.
- Companion test project: *Add → New Project → WinUI 3 Unit Test Project*.
- Update SDK: *Manage NuGet Packages → Updates → Microsoft.WindowsAppSDK*.

See [WinUI 3 docs](https://learn.microsoft.com/windows/apps/winui/winui3/).

## Publish guide

A redistributable MSIX requires a `.wapproj` alongside this app project (it owns `Package.appxmanifest`, signing, and bundle config).

- *Add → New Project → Windows Application Packaging Project*, then *Add → Reference* this app project.
- Right-click `.wapproj` → *Publish → Create App Packages*.

See [Package and deploy a WinUI 3 desktop app](https://learn.microsoft.com/windows/apps/package-and-deploy/).

## App architecture guide

External guides:

- [MVVM pattern](https://learn.microsoft.com/dotnet/architecture/maui/mvvm)
- [CommunityToolkit.Mvvm](https://learn.microsoft.com/dotnet/communitytoolkit/mvvm/) — source generators for properties and commands
- [Navigation design basics](https://learn.microsoft.com/windows/apps/design/basics/navigation-basics) — `Frame.Navigate`, `NavigationCacheMode`
- [Async/await in WinUI](https://learn.microsoft.com/windows/apps/develop/threading-async/)

## Testing guide

- Companion test template: `dotnet new winui-unittest -n MyApp.Tests` (or *Add → New Project → WinUI 3 Unit Test Project*).
- Mocking: [Moq](https://github.com/devlooped/moq), [NSubstitute](https://nsubstitute.github.io/).
- UI automation: [WinAppDriver](https://github.com/microsoft/WinAppDriver).

See [Unit testing with MSTest](https://learn.microsoft.com/dotnet/core/testing/unit-testing-mstest-intro).

## Performance guide

External guides:

- [`{x:Bind}` markup extension](https://learn.microsoft.com/windows/apps/develop/platform/xaml/x-bind-markup-extension) — compiled bindings
- [`x:Load` attribute](https://learn.microsoft.com/windows/apps/develop/platform/xaml/x-load-attribute) — deferred UI
- [Windows app performance overview](https://learn.microsoft.com/windows/apps/performance/)

Profilers: [Visual Studio Performance Profiler](https://learn.microsoft.com/visualstudio/profiling/), [PerfView](https://github.com/microsoft/perfview).

## Accessibility guide

External guides:

- [Accessibility in Windows apps](https://learn.microsoft.com/windows/apps/design/accessibility/accessibility-overview)

Tooling: [Accessibility Insights for Windows](https://accessibilityinsights.io/docs/windows/overview/).

## Globalization guide

External guides:

- [Globalize your WinUI app](https://learn.microsoft.com/windows/apps/design/globalizing/guidelines-and-checklist-for-globalizing-your-app)
- [Localize strings with the Resource Management System](https://learn.microsoft.com/windows/apps/windows-app-sdk/mrtcore/localize-strings)

## Security guide

External guides:

- [App capability declarations](https://learn.microsoft.com/windows/uwp/packaging/app-capability-declarations) — trim `Package.appxmanifest`
- [Credential Locker](https://learn.microsoft.com/windows/uwp/security/credential-locker) / [Azure Key Vault](https://learn.microsoft.com/azure/key-vault/general/overview) — secrets storage
- [Create a certificate for package signing](https://learn.microsoft.com/windows/msix/package/create-certificate-package-signing)
- [.NET secure coding guidelines](https://learn.microsoft.com/dotnet/standard/security/secure-coding-guidelines)

## Documentation and samples

- [Windows App SDK documentation](https://learn.microsoft.com/windows/apps/windows-app-sdk/)
- [WinUI 3 API reference](https://learn.microsoft.com/windows/windows-app-sdk/api/winrt/)
- [Windows Platform SDK API reference](https://learn.microsoft.com/uwp/api/) — `Windows.*` WinRT APIs (file pickers, geolocation, sensors, clipboard, …) not covered by WinUI 3.
- [Windows App SDK samples](https://github.com/microsoft/WindowsAppSDK-Samples)
- [WinUI 3 Gallery](https://github.com/microsoft/WinUI-Gallery) — control showcase
- [AI Dev Gallery](https://github.com/microsoft/ai-dev-gallery) — on-device AI/ML patterns
- [`winapp` CLI](https://github.com/microsoft/WinAppCli)

---

*Generated from the Visual Studio Windows App SDK C# project templates.*

- Update via the Visual Studio Installer (Windows App SDK C# Templates component).
- Browse all WinUI templates: *File → New → Project*, filter by *WinUI*. The parallel CLI templates: `dotnet new list winui`.
