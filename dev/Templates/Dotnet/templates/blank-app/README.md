# WinUI 3 desktop app

A blank WinUI 3 desktop application, packaged as MSIX and built on the
Windows App SDK. Generated from
`Microsoft.WindowsAppSDK.WinUI.CSharp.Templates`.

## Project layout

| Path                                     | Purpose                                                                                                                                                                                                       |
| ---------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `App.xaml`, `App.xaml.cs`                | Application entry point and lifetime.                                                                                                                                                                         |
| `MainWindow.xaml`, `MainWindow.xaml.cs`  | The app's first window.                                                                                                                                                                                       |
| `Package.appxmanifest`                   | App identity, capabilities, visual assets, and declarations.                                                                                                                                                  |
| `Assets/`                                | App icons, tile logos, splash screen.                                                                                                                                                                         |
| `app.manifest`                           | Native side-by-side manifest (DPI awareness, supported OS versions).                                                                                                                                          |
| `*.csproj`                               | Build configuration. The authoritative source for the target framework, supported platforms, runtime identifiers, and the `Microsoft.WindowsAppSDK` package version &mdash; prefer reading values from here. |

## Prerequisites

- Windows 10 version 1809 (build 17763) or newer.
- **Developer Mode** enabled: *Settings &rarr; System &rarr; For developers &rarr; Developer Mode*.
- A .NET SDK that matches the `<TargetFramework>` in the `.csproj`.

## Build and run

The project references
[`Microsoft.Windows.SDK.BuildTools.WinApp`](https://www.nuget.org/packages/Microsoft.Windows.SDK.BuildTools.WinApp),
which hooks `dotnet run` to register a loose-layout MSIX package via the
[`winapp` CLI](https://github.com/microsoft/WinAppCli) and launch the app
with full package identity. No manual `Add-AppxPackage`, `MakeAppx`, or
`SignTool` is required for inner-loop development.

```powershell
# Detect the current machine's architecture (x86, x64, or ARM64).
$arch = $env:PROCESSOR_ARCHITECTURE
$Platform = if ($arch -eq 'AMD64') { 'x64' } else { $arch }

# Build
dotnet build -c Debug -p:Platform=$Platform

# Run (registers a debug package and launches it via AUMID)
dotnet run -c Debug -p:Platform=$Platform
```

`-p:Platform=` is required: MSIX-packaged WinUI projects do not have an
`AnyCPU` configuration.

To opt out of the `dotnet run` integration, set
`<EnableWinAppRunSupport>false</EnableWinAppRunSupport>` in the `.csproj`.

## Common next steps

- **Add an item to the project** &mdash; run `dotnet new list winui` to list the
  available item templates (page, window, user control, content dialog,
  templated control, resource dictionary, .resw).
- **Update the Windows App SDK** &mdash; `dotnet add package Microsoft.WindowsAppSDK`.
- **Change the target framework** &mdash; edit `<TargetFramework>` in the `.csproj`.
  Keep `<RuntimeIdentifier>` and `<TargetPlatformMinVersion>` in sync.
- **Publish an MSIX** &mdash; build in `Release` and produce a signed package.
  See [Package and deploy](https://learn.microsoft.com/windows/apps/package-and-deploy/)
  on Microsoft Learn or the [`winapp` CLI usage docs](https://github.com/microsoft/WinAppCli/blob/main/docs/usage.md).

## Documentation and samples

- [Windows App SDK documentation](https://learn.microsoft.com/windows/apps/windows-app-sdk/)
- [WinUI 3 / Windows App SDK API reference](https://learn.microsoft.com/windows/windows-app-sdk/api/winrt/)
- [Windows App SDK samples](https://github.com/microsoft/WindowsAppSDK-Samples)
- [WinUI 3 Gallery &mdash; control showcase](https://github.com/microsoft/WinUI-Gallery)
- [`winapp` CLI](https://github.com/microsoft/WinAppCli)

## Using an AI coding assistant

If you use an AI coding assistant (for example GitHub Copilot, Cursor, or
Claude Code) in this project, the following notes help it generate accurate
code:

- The `.csproj` is the source of truth for `TargetFramework`,
  `TargetPlatformMinVersion`, `Platforms`, `RuntimeIdentifier`, and the
  `Microsoft.WindowsAppSDK` package version. These change between SDK
  releases &mdash; read them rather than hard-coding values.
- The [Windows App SDK API reference](https://learn.microsoft.com/windows/windows-app-sdk/api/winrt/)
  and the [samples repo](https://github.com/microsoft/WindowsAppSDK-Samples)
  are authoritative for API shapes.
- Every `dotnet build`, `dotnet test`, or `dotnet run` invocation needs
  `-c <Configuration>` and `-p:Platform=<x86|x64|ARM64>`.

This README is the only file the template ships specifically for assistant
context. You are free to delete this section, replace it, or add your own
assistant-configuration files (`.github/copilot-instructions.md`,
`AGENTS.md`, `.cursorrules`, &hellip;) to fit your team's conventions.
