# WinUI 3 desktop app (two-project packaged)

A two-project WinUI 3 desktop app: a `.csproj` for code and a `.wapproj`
for MSIX packaging. Built on the Windows App SDK.

> [!TIP]
> If you're starting a new app, prefer the single-project **WinUI 3
> desktop app** template — it packages itself directly from the `.csproj`,
> no `.wapproj` required. Use this two-project shape only when you need
> the `.wapproj` indirection (for example, to package multiple processes
> together or to interop with existing `.wapproj`-based build flows).

## Project layout

```
MySolution.sln
├── MyApp/                       # The code project
│   ├── App.xaml, App.xaml.cs
│   ├── MainWindow.xaml, MainWindow.xaml.cs
│   ├── Properties/
│   ├── app.manifest
│   └── MyApp.csproj
└── MyApp.Package/               # The packaging project
    ├── Images/                  # Tile, splash, store logos
    ├── Package.appxmanifest     # App identity and capabilities
    └── MyApp.Package.wapproj
```

The `.wapproj` references the `.csproj` and owns the manifest, visual
assets, and MSIX output. The `.csproj` owns code, XAML, and target
framework.

## Prerequisites

See [Set up your dev environment for Windows App SDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/set-up-your-development-environment).

## Build and run

- VS: **F5** with the `.wapproj` set as the startup project (builds both projects, deploys loose-layout MSIX, launches via AUMID).
- CLI: `msbuild MyApp.Package\MyApp.Package.wapproj /restore /p:Platform=x64 /p:Configuration=Debug`.
- `dotnet run` does **not** work on `.wapproj`. For a CLI-driven flow, switch to the single-project blank-app template.

See [MSBuild properties for packaging projects](https://learn.microsoft.com/windows/msix/desktop/desktop-to-uwp-packaging-dot-net#build-the-package-from-the-command-line) for `.wapproj` flags.

## Common next steps

- Edit `Package.appxmanifest` (lives in the `.wapproj`) via the manifest designer or as XML.
- Add a project to the package: right-click `.wapproj` → *Add → Reference*.
- WinUI items go on the **app project**, not the `.wapproj`: *Add → New Item → WinUI*.
- Update SDK: *Manage NuGet Packages* on the app project → *Updates*.

See [Package and deploy a WinUI 3 desktop app](https://learn.microsoft.com/windows/apps/package-and-deploy/).

## Publish guide

This two-project shape **is** the redistributable-MSIX shape — the `.wapproj` already owns `Package.appxmanifest`, signing, and bundle config.

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
