# Windows App SDK WinUI 3 C# Templates

Official WinUI 3 project and item templates for the
[Windows App SDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/),
designed for use with the .NET CLI (`dotnet new`). This template pack provides
the same starting points available in Visual Studio — blank apps, navigation
views, MVVM scaffolding, tab-view shells, class libraries, unit test projects,
and common WinUI UI items — right from the command line.

`dotnet run` launches the generated app with full MSIX package identity, so
features that require it (notifications, background tasks, Windows AI APIs,
etc.) work the same as they would in a Visual Studio F5 deploy.

## Installation

```shell
dotnet new install Microsoft.WindowsAppSDK.WinUI.CSharp.Templates
```

## Available Templates

### Project Templates

Get below list via `dotnet new list winui`

| Short Name        | Description                                                              |
|-------------------|--------------------------------------------------------------------------|
| `winui`           | Minimal WinUI 3 blank app with single-project MSIX packaging. Start here if unsure |
| `winui-mvvm`      | WinUI 3 MVVM app using `CommunityToolkit.Mvvm`                           |
| `winui-navview`   | WinUI 3 NavigationView starter app with single-project MSIX packaging    |
| `winui-tabview`   | WinUI 3 TabView starter app with single-project MSIX packaging           |
| `winui-lib`       | WinUI 3 class library for sharing UI components                          |
| `winui-unittest`  | WinUI 3 packaged test app configured for MSTest                          |

Each `winui-*` short name also has a `winui3-*` alias (e.g. `winui3-mvvm`).

### Item Templates

| Short Name                 | Description                                              |
|----------------------------|----------------------------------------------------------|
| `winui-page`               | WinUI 3 Page (XAML + code-behind)                        |
| `winui-window`             | WinUI 3 Window (XAML + code-behind)                      |
| `winui-usercontrol`        | WinUI 3 UserControl (XAML + code-behind)                 |
| `winui-templatedcontrol`   | WinUI 3 templated control                                |
| `winui-resourcedictionary` | WinUI 3 ResourceDictionary                               |
| `winui-resw`               | RESW resources file for localized strings                |
| `winui-dialog`             | WinUI 3 ContentDialog (XAML + code-behind)               |

Item templates are context-aware and only surface when `dotnet new` is executed
inside a WinUI project folder or when `--project` points to one.

## Quick Start

### Quickstart a new WinUI 3 APP

```powershell
dotnet new winui -n MyApp
cd MyApp

# dotnet build
dotnet run
```

`dotnet run` registers a loose-layout MSIX, gives the app package identity,
and launches it via AUMID activation — equivalent to F5 in Visual Studio.

### Add items to an existing project

```powershell
dotnet new winui-page         -n SettingsPage      --project .\MyApp.csproj
dotnet new winui-usercontrol  -n ProfileCard       --project .\MyApp.csproj
dotnet new winui-window       -n SecondaryWindow   --project .\MyApp.csproj
dotnet new winui-dialog       -n ConfirmDialog     --project .\MyApp.csproj
```

### Choosing a Target Framework

Generated projects target `net{N}.0-windows10.0.26100.0`, where `{N}` is
selected at scaffold time via `--dotnet-version`:

```shell
dotnet new winui --dotnet-version net8.0  -n MyApp
dotnet new winui --dotnet-version net9.0  -n MyApp
dotnet new winui --dotnet-version net10.0 -n MyApp
```

Supported choices: `net8.0`, `net9.0`, `net10.0`. If you omit
`--dotnet-version`, most templates default to `net10.0`; `winui-mvvm` matches
your installed .NET SDK. You can also edit `<TargetFramework>` in the
generated `.csproj` afterward.

### Customizing `dotnet run` behavior

Set any of these MSBuild properties inside a `<PropertyGroup>` in the
generated `.csproj` to tweak how `dotnet run` launches the app:

| Property                       | Default | Effect                                                                                         |
|--------------------------------|---------|------------------------------------------------------------------------------------------------|
| `EnableWinAppRunSupport`       | `true`  | Set to `false` to disable the packaged-launch integration and run unpackaged instead           |
| `WinAppRunUseExecutionAlias`   | `false` | For console apps — launches via `uap5:ExecutionAlias` so stdin/stdout stay in the terminal     |
| `WinAppRunNoLaunch`            | `false` | Register the package but don't launch (useful when attaching a different debugger first)       |
| `WinAppRunDebugOutput`         | `false` | Capture `OutputDebugString` and crash dumps; cannot be combined with another debugger          |
| `WinAppLaunchArgs`             | (empty) | Arguments passed to the app on launch (e.g. `--my-flag value`)                                 |

These properties are provided by the
[`Microsoft.Windows.SDK.BuildTools.WinApp`](https://www.nuget.org/packages/Microsoft.Windows.SDK.BuildTools.WinApp)
NuGet package, which is referenced automatically by the project templates.

### AI agent instructions

The `winui` blank app template also unpacks an `AGENTS.md` plus a
`.github/instructions/` set so AI coding agents (GitHub Copilot, Claude Code,
etc.) follow the project's WinUI / accessibility / testing conventions out of
the box. Remove or edit them if they don't fit your project.

## Prerequisites

- [.NET SDK](https://dotnet.microsoft.com/download) — `net8.0`, `net9.0`, or `net10.0`
- Windows 10 version 1809 (build 17763) or later
- **Developer Mode enabled** — required for `dotnet run` to register the loose-layout package.
  Settings → System → For developers → Developer Mode → On.

## Resources

- [Windows App SDK documentation](https://learn.microsoft.com/windows/apps/windows-app-sdk/)
- [WinUI 3 documentation](https://learn.microsoft.com/windows/apps/winui/winui3/)
- [Release notes](https://github.com/microsoft/WindowsAppSDK/releases)
- [File an issue](https://github.com/microsoft/WindowsAppSDK/issues)

## Contributing

This template pack is built from the
[WindowsAppSDK](https://github.com/microsoft/WindowsAppSDK) repository under
`dev/Templates/Dotnet/`. The templates share the same XAML, code-behind,
and project files as the Visual Studio templates under
`dev/Templates/Source/ProjectTemplates/` and
`dev/Templates/Source/ItemTemplates/`, so there is only one copy to maintain.

### Local Testing

1. Pack the templates:
   ```shell
   dotnet pack dev/Templates/Dotnet/WinAppSdk.CSharp.DotnetNewTemplates.csproj -c Release -o localpackages
   ```
2. Uninstall any previous version:
   ```shell
   dotnet new uninstall Microsoft.WindowsAppSDK.WinUI.CSharp.Templates
   ```
3. Install the local package:
   ```shell
   dotnet new install ./localpackages/Microsoft.WindowsAppSDK.WinUI.CSharp.Templates.<version>.nupkg
   ```

For an automated end-to-end run that scaffolds, builds, and (optionally)
launches every template, use the included script:

```powershell
.\dev\Templates\Dotnet\Test-DotnetNewTemplates.ps1                      # full run
.\dev\Templates\Dotnet\Test-DotnetNewTemplates.ps1 -SkipAppLaunch       # CI-friendly
```

### Validation Checklist

- Run `dotnet pack` locally and `dotnet new install` to verify the local build.
- Run `dotnet new winui` to review and confirm all templates are registered.
- Build generated projects for x64, x86, and ARM64 in Visual Studio or `dotnet build`.
- Test packaged deployments on Windows 10 version 1809 or later.
