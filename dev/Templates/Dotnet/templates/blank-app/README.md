# WinUI 3 desktop app

A blank WinUI 3 desktop app packaged as MSIX, built on the Windows App SDK.
Generated from `Microsoft.WindowsAppSDK.WinUI.CSharp.Templates`.

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

## Prerequisites

- Windows 10 version 1809 (build 17763) or newer.
- **Developer Mode** enabled: *Settings → System → For developers*.
- A .NET SDK matching `<TargetFramework>` in the `.csproj`.

## Build and run

```powershell
dotnet build
dotnet run
```

`dotnet run` is the equivalent of F5 in Visual Studio: it registers a
loose-layout MSIX, gives the app package identity, and launches it via
AUMID activation. No `Add-AppxPackage`, `MakeAppx`, or `SignTool` step is
needed.

The packaged-launch integration comes from
[`Microsoft.Windows.SDK.BuildTools.WinApp`](https://www.nuget.org/packages/Microsoft.Windows.SDK.BuildTools.WinApp).
See its package page for the full set of `WinAppRun*` MSBuild properties
(opt-out, console alias, no-launch, debug output, launch args).

## Common next steps

- **Add an item**: `dotnet new winui-page`, `winui-window`, `winui-usercontrol`,
  `winui-templatedcontrol`, `winui-dialog`, `winui-resourcedictionary`, or
  `winui-resw`. `dotnet new list winui` shows every available template.
- **Add a unit test project**: `dotnet new winui-unittest -n MyApp.Tests`
  (pre-wired for MSTest with MSIX packaging).
- **Update the SDK**: `dotnet add package Microsoft.WindowsAppSDK`.

## Publish a signed app

Production MSIX packages must be signed by a certificate from a trusted
certificate authority. Never ship a development certificate in a released
build.

For day-to-day signing workflows, the
[`winapp` CLI usage docs](https://github.com/microsoft/WinAppCli/blob/main/docs/usage.md)
cover generating a development cert, signing an existing MSIX, and
building and signing in one step (`cert`, `sign`, and `pack` commands).
For the broader publishing story, see
[Package and deploy](https://learn.microsoft.com/windows/apps/package-and-deploy/).

## Performance guide

For a responsive, fluid app, it helps to prefer compiled bindings, defer UI
you don't need at startup, virtualize long lists, and keep heavy work off the
UI thread. Small choices made early tend to compound as the app grows.

It is recommended to measure before and after any optimization, ideally with
the [Visual Studio Performance Profiler](https://learn.microsoft.com/visualstudio/profiling/)
or [PerfView](https://github.com/microsoft/perfview). Real measurements are
far more reliable than intuition.

For per-task guidance:

- **Compiled bindings**:
  [`{x:Bind}` markup extension](https://learn.microsoft.com/windows/apps/develop/platform/xaml/x-bind-markup-extension)
  is compiled and type-safe; prefer it over `{Binding}` in new XAML.
- **Deferred element loading**:
  [`x:Load` attribute](https://learn.microsoft.com/windows/apps/develop/platform/xaml/x-load-attribute)
  (or `x:DeferLoadStrategy`) keeps off-screen UI out of the initial visual
  tree until it's needed.
- **Long lists and grids**:
  [Optimize ListView and GridView performance](https://learn.microsoft.com/windows/apps/develop/performance/optimize-gridview-and-listview)
  — use virtualizing controls (`ListView`, `GridView`, or `ItemsRepeater`
  with `StackLayout`) rather than a plain `StackPanel`, and stream items in
  with `ISupportIncrementalLoading` when the data set is large.
- **UI thread responsiveness**:
  [Windows app performance overview](https://learn.microsoft.com/windows/apps/performance/)
  — `async`/`await` for I/O, `Task.Run` for CPU-bound work, and steer clear
  of `.Result` or `.GetAwaiter().GetResult()` on the UI thread.
- **Reused resources**: share an `HttpClient` (via `IHttpClientFactory`) and
  cache HTTP responses or computed values when it makes sense.
- **Shallow visual trees**:
  [Optimize your XAML layout](https://learn.microsoft.com/windows/apps/develop/performance/optimize-xaml-layout)
  — deep panel nesting compounds layout cost.

A couple of common pitfalls to watch for: flooding
`DispatcherQueue.TryEnqueue` from background threads, and calling `FindName`
or walking the visual tree in tight loops — both can erode the gains from
everything above.

## Accessibility guide

For accessibility, make your app usable with a keyboard alone, expose
accessible names to screen readers, and respect High Contrast and system
text scaling. Reaching for semantic controls (`Button`, `HyperlinkButton`,
`ListView`) instead of click-handled `Border`/`Grid` covers most of this
without extra work, since those controls already provide focus, keyboard
activation, and automation peers. Avoiding color-only signals — pair
color with an icon, label, or pattern — keeps the UI usable for
color-blind users too.

It is recommended to run [Accessibility Insights for Windows](https://accessibilityinsights.io/docs/windows/overview/)
against your build. It runs 60+ automated checks, inspects the live UI
Automation tree, and verifies tab order, keyboard traps, and color
contrast.

For per-task guidance:

- **Labeling controls**:
  [Expose basic accessibility information](https://learn.microsoft.com/windows/apps/design/accessibility/basic-accessibility-information)
  (covers `AutomationProperties.Name`, `LabeledBy`, automation IDs).
- **Tab order, access keys, shortcuts**:
  [Keyboard accessibility](https://learn.microsoft.com/windows/apps/design/accessibility/keyboard-accessibility).
- **Custom styles or colors**:
  [High Contrast themes](https://learn.microsoft.com/windows/apps/design/accessibility/high-contrast-themes).
- **Custom controls and broader concepts**:
  [Accessibility overview](https://learn.microsoft.com/windows/apps/design/accessibility/accessibility-overview)
  (UI Automation, custom automation peers, captioning).

## Globalization guide

For globalization, keep user-facing strings in `.resw` resource files,
format dates, numbers, and currencies through culture-aware APIs, and
design layouts that tolerate text expansion.

It is recommended to verify localization early by adding a second locale
(e.g., `Strings/de-DE/Resources.resw` alongside `Strings/en-US/Resources.resw`)
and switching the Windows display language. Layout overflow and missing
strings show up immediately.

For per-task guidance:

- **Adding UI text**:
  [Localize strings in XAML with `x:Uid`](https://learn.microsoft.com/windows/apps/windows-app-sdk/mrtcore/localize-strings#refer-to-a-string-resource-identifier-from-xaml)
  (covers `x:Uid` markup and matching `.resw` keys).
- **Loading strings from code**:
  [Localize strings with the Resource Management System](https://learn.microsoft.com/windows/apps/windows-app-sdk/mrtcore/localize-strings)
  (covers `ResourceLoader.GetString` and per-locale `.resw` layout).
- **Composing translated text**: use positional placeholders (`{0}`,
  `{1}`) with `string.Format` rather than concatenating fragments, because the grammatical word-order varies between languages, and concatenation
  often produces awkward translations.
- **Culture-aware formatting and layout**:
  [Globalize your WinUI app](https://learn.microsoft.com/windows/apps/design/globalizing/guidelines-and-checklist-for-globalizing-your-app)
  (covers `CultureInfo`, `DateTimeFormatter`, and designing for text expansion).

## Security guide

For security, it helps to treat secrets, external input, and capabilities
with the same care as the rest of the codebase — mistakes here have a
much larger blast radius than elsewhere.

It is recommended to keep `Package.appxmanifest` capabilities trimmed to
exactly what the app needs — see
[App capability declarations](https://learn.microsoft.com/windows/uwp/packaging/app-capability-declarations)
— and to keep dependencies fresh with `dotnet list package --outdated`.
Removing an unused capability or upgrading a stale package is one of the
cheapest security wins available.

For per-task guidance:

- **Secrets**: keep API keys, tokens, and connection strings out of
  source control. Prefer environment variables, the
  [Windows Credential Manager / `PasswordVault`](https://learn.microsoft.com/windows/uwp/security/credential-locker),
  or [Azure Key Vault](https://learn.microsoft.com/azure/key-vault/general/overview)
  over committing them to `appsettings.json`.
- **External input**: validate and sanitize anything that crosses a
  trust boundary (user input, file contents, network responses) before
  using it in queries, file paths, or `Process.Start` arguments.
- **Networking**: stick with `HttpClient` over HTTPS and the default
  TLS validation. If you have to relax certificate validation while
  debugging, guard it with `#if DEBUG` so it can't slip into a release
  build.
- **Logging and error handling**: keep tokens, passwords, and personal
  data out of logs, and avoid silent
  `try { … } catch (Exception) { }` blocks — at minimum, log what
  failed so future-you can diagnose it.
- **Signing**: the development certificate flow lives in
  [Publish a signed app](#publish-a-signed-app) above; production
  releases need a certificate from a trusted authority.

For a broader treatment, see
[.NET secure coding guidelines](https://learn.microsoft.com/dotnet/standard/security/secure-coding-guidelines).
## Documentation and samples

- [Windows App SDK documentation](https://learn.microsoft.com/windows/apps/windows-app-sdk/)
- [WinUI 3 API reference](https://learn.microsoft.com/windows/windows-app-sdk/api/winrt/)
- [Windows Platform SDK API reference](https://learn.microsoft.com/uwp/api/):
  `Windows.*` WinRT APIs (file pickers, geolocation, sensors, clipboard, …)
  not covered by WinUI 3.
- [Windows App SDK samples](https://github.com/microsoft/WindowsAppSDK-Samples)
- [WinUI 3 Gallery](https://github.com/microsoft/WinUI-Gallery): control showcase
- [AI Dev Gallery](https://github.com/microsoft/ai-dev-gallery): on-device AI/ML patterns
- [`winapp` CLI](https://github.com/microsoft/WinAppCli)
