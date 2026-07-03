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

## Prerequisites

See [Set up your dev environment for Windows App SDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/set-up-your-development-environment).

## Build and run

- `dotnet build` — compile.
- `dotnet run` — registers a loose-layout MSIX with AUMID activation and launches. No `Add-AppxPackage` / `MakeAppx` / `SignTool` needed.
- If you hit `REGDB_E_CLASSNOTREG` after editing `Package.appxmanifest`: `winapp unregister`, then `dotnet run`.

See [`Microsoft.Windows.SDK.BuildTools.WinApp`](https://www.nuget.org/packages/Microsoft.Windows.SDK.BuildTools.WinApp) for `WinAppRun*` MSBuild properties.

## Common next steps

- Add items: `dotnet new winui-page`, `winui-window`, `winui-usercontrol`, `winui-templatedcontrol`, `winui-dialog`, `winui-resourcedictionary`, `winui-resw` (full list: `dotnet new list winui`).
- Companion test project: `dotnet new winui-unittest -n MyApp.Tests`.
- Update SDK: `dotnet add package Microsoft.WindowsAppSDK`.

See [WinUI 3 docs](https://learn.microsoft.com/windows/apps/winui/winui3/).

## Publish guide

A redistributable MSIX requires a `.wapproj` alongside this app project (it owns `Package.appxmanifest`, signing, and bundle config).

- CLI: `winapp publish` — see [`winapp` CLI](https://github.com/microsoft/WinAppCli).

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

*Generated from the [`Microsoft.WindowsAppSDK.WinUI.CSharp.Templates`](https://www.nuget.org/packages/Microsoft.WindowsAppSDK.WinUI.CSharp.Templates/) dotnet-new template package.*

- Update: `dotnet new install Microsoft.WindowsAppSDK.WinUI.CSharp.Templates::*`
- List installed: `dotnet new list winui`
