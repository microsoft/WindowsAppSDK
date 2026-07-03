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

## Prerequisites

See [Set up your dev environment for Windows App SDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/set-up-your-development-environment).

## Build and run tests

- `dotnet test` — builds the test container, registers it as a loose-layout MSIX, runs MSTest.
- Filter: `dotnet test --filter "FullyQualifiedName~MyTestClass"` or `... "TestCategory=Smoke"`.

See [Filter MSTest tests](https://learn.microsoft.com/dotnet/core/testing/selective-unit-tests).

## Common next steps

- Add a test class: any `.cs` with `[TestClass]` / `[TestMethod]` is discovered by MSTest.
- Reference code under test: `dotnet add reference ../MyApp/MyApp.csproj` (or `dotnet add package <library>`).
- Update SDK: `dotnet add package Microsoft.WindowsAppSDK`.

See [Unit testing with MSTest](https://learn.microsoft.com/dotnet/core/testing/unit-testing-mstest-intro).

## Writing tests guide

- Reference code under test: `dotnet add reference ..\MyApp\MyApp.csproj` (or `dotnet add package <library>`). For internal types, add `[assembly: InternalsVisibleTo("MyApp.Tests")]`.
- Mocking: [Moq](https://github.com/devlooped/moq), [NSubstitute](https://nsubstitute.github.io/).

See [Unit testing with MSTest](https://learn.microsoft.com/dotnet/core/testing/unit-testing-mstest-intro) for `[TestMethod]`, `[DataTestMethod]`, `[TestInitialize]`, etc.

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
