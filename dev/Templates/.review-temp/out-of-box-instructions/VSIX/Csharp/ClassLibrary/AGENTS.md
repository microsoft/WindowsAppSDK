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

XAML controls, styles, and resource dictionaries can be added through the
Visual Studio **Add → New Item** dialog (templated control, user control,
resource dictionary, and friends).

## Prerequisites

See [Set up your dev environment for Windows App SDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/set-up-your-development-environment).

## Build

- VS: *Build → Build Solution* (`Ctrl+Shift+B`).
- CLI: `msbuild /restore /p:Configuration=Debug /p:Platform=x64`.
- No Start-Debugging target: class libraries have no entry point. Reference from an app or unit-test project in the same solution.

See [MSBuild command-line reference](https://learn.microsoft.com/visualstudio/msbuild/msbuild-command-line-reference).

## Common next steps

- Add items: *Add → New Item → WinUI* (user controls, templated controls, resource dictionaries, `.resw`).
- Consume from an app project in the same solution: *Add → Project Reference*.
- Update SDK: *Manage NuGet Packages → Updates → Microsoft.WindowsAppSDK*.

See [WinUI 3 docs](https://learn.microsoft.com/windows/apps/winui/winui3/).

## Library design guide

- Custom XAML controls: derive from `Control` and ship `Themes/Generic.xaml` (`Default` / `Light` / `HighContrast` resource dictionaries). For composing existing controls, use `UserControl`.

External guides:

- [Dependency properties overview](https://learn.microsoft.com/windows/apps/develop/platform/dependency-properties-overview)
- [Microsoft.CodeAnalysis.PublicApiAnalyzers](https://github.com/dotnet/roslyn-analyzers/blob/main/src/PublicApiAnalyzers/PublicApiAnalyzers.Help.md) — lock the public API surface
- [Create a NuGet package with the dotnet CLI](https://learn.microsoft.com/nuget/create-packages/creating-a-package-dotnet-cli)

## Testing guide

- Companion test template: `dotnet new winui-unittest -n MyLibrary.Tests`, then `dotnet add reference ../MyLibrary/MyLibrary.csproj`.
- Tests run inside an MSIX, so dependency-property and `INotifyPropertyChanged` plumbing works in test cases.
- API-break detection: [Microsoft.DotNet.ApiCompat.Tool](https://www.nuget.org/packages/Microsoft.DotNet.ApiCompat.Tool).
- Mocking: [Moq](https://github.com/devlooped/moq), [NSubstitute](https://nsubstitute.github.io/).

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
