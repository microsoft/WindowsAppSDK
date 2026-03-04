# Windows App SDK WinUI 3 C# Templates

Official WinUI 3 project and item templates for the
[Windows App SDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/),
designed for use with the .NET CLI (`dotnet new`). This template pack provides
the same starting points available in Visual Studio — blank apps, navigation
views, class libraries, unit test projects, and common WinUI UI items — right
from the command line.

## Installation

```shell
dotnet new install Microsoft.WindowsAppSDK.WinUI.CSharp.Templates
```

## Available Templates

### Project Templates

| Short Name       | Description                                              |
|------------------|----------------------------------------------------------|
| `winui`          | WinUI 3 blank app with single-project MSIX packaging     |
| `winui-navview`  | WinUI 3 NavigationView starter app                       |
| `winui-lib`      | WinUI 3 class library for sharing UI components          |
| `winui-unittest` | WinUI 3 packaged test app configured for MSTest          |

### Item Templates

| Short Name                 | Description                        |
|----------------------------|------------------------------------|
| `winui-page`               | Blank WinUI 3 Page                 |
| `winui-window`             | Blank WinUI 3 Window               |
| `winui-usercontrol`        | WinUI 3 UserControl                |
| `winui-templatedcontrol`   | WinUI 3 templated control |
| `winui-resourcedictionary` | WinUI 3 ResourceDictionary         |
| `winui-resw`               | RESW resource file                 |
| `winui-dialog`             | WinUI 3 ContentDialog              |

Item templates are context-aware and only surface when `dotnet new` is executed
inside a WinUI project folder or when `--project` points to one.

## Quick Start

### Create a new WinUI 3 app

```shell
dotnet new winui -n MyApp
cd MyApp
dotnet build -p:Platform=x64
dotnet run -c Debug -p:Platform=x64
```

### Add items to an existing project

```shell
dotnet new winui-page -n SettingsPage --project .\MyApp.csproj
dotnet new winui-usercontrol -n ProfileCard --project .\MyApp.csproj
dotnet new winui-window -n SecondaryWindow --project .\MyApp.csproj
```

### Choosing a Target Framework

All templates default to `net8.0-windows10.0.19041.0`. To target a different
.NET version, pass `--dotnet-version` when creating the project:

```shell
dotnet new winui --dotnet-version net10.0 -n MyApp
```

You can also edit the generated `.csproj` afterward and change
`<TargetFramework>` (and any related `<RuntimeIdentifiers>` entries) to your
preferred TFM.

## Prerequisites

- [.NET 8 SDK](https://dotnet.microsoft.com/download/dotnet/8.0) or later
- Windows 10 version 1809 (build 17763) or later
- [Windows App SDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/)
  workload

## Resources

- [Windows App SDK documentation](https://learn.microsoft.com/windows/apps/windows-app-sdk/)
- [WinUI 3 documentation](https://learn.microsoft.com/windows/apps/winui/winui3/)
- [Release notes](https://github.com/microsoft/WindowsAppSDK/releases)
- [File an issue](https://github.com/microsoft/WindowsAppSDK/issues)

## Contributing

This template pack is built from the
[WindowsAppSDK](https://github.com/microsoft/WindowsAppSDK) repository under
`dev/VSIX/DotnetNewTemplates/`. The templates share the same XAML, code-behind,
and project files as the Visual Studio templates under
`dev/VSIX/ProjectTemplates/` and `dev/VSIX/ItemTemplates/`, so there is only one
copy to maintain.

### Local Testing

1. Pack the templates:
   ```shell
   dotnet pack dev/VSIX/DotnetNewTemplates/WinAppSdk.CSharp.DotnetNewTemplates.csproj -c Release -o localpackages
   ```
2. Uninstall any previous version:
   ```shell
   dotnet new uninstall Microsoft.WindowsAppSDK.WinUI.CSharp.Templates
   ```
3. Install the local package:
   ```shell
   dotnet new install ./localpackages/Microsoft.WindowsAppSDK.WinUI.CSharp.Templates.<version>.nupkg
   ```

### Validation Checklist

- Run `dotnet pack` locally and `dotnet new install` to verify each template scaffolds and builds.
- Run `dotnet new list | findstr winui` to confirm all templates are registered.
- Build generated projects for x64, x86, and ARM64 in Visual Studio or VS Code.
- Test packaged deployments on Windows 10 version 1809 or later.
