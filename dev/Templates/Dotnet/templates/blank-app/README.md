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

## Accessibility guide

For accessibility, make your app usable with a keyboard alone, expose accessible names to
screen readers, and respect High Contrast and system text scaling.

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
- **Culture-aware formatting and layout**:
  [Globalize your WinUI app](https://learn.microsoft.com/windows/apps/design/globalizing/guidelines-and-checklist-for-globalizing-your-app)
  (covers `CultureInfo`, `DateTimeFormatter`, and designing for text expansion).

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
