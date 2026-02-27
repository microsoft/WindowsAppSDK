# Windows App SDK .NET CLI Templates

This directory contains the assets that produce the `dotnet new` template pack for the
Windows App SDK C# Desktop templates. The templates are built directly from the
existing Visual Studio template sources under `dev/VSIX/ProjectTemplates/Desktop/CSharp`
and `dev/VSIX/ItemTemplates/Desktop/CSharp`, so we only maintain one copy of the XAML,
code-behind, and project files.

## Templates

| Short name            | Identity                                      | Type     | Description                                               |
|-----------------------|-----------------------------------------------|----------|-----------------------------------------------------------|
| `winui`               | `Microsoft.WindowsAppSDK.WinUI.CSharp.BlankApp`                    | Project  | WinUI 3 blank app that uses single-project MSIX tooling   |
| `winui-navview`       | `Microsoft.WindowsAppSDK.WinUI.CSharp.NavigationApp`               | Project  | WinUI 3 NavigationView starter app                        |
| `winui-lib`           | `Microsoft.WindowsAppSDK.WinUI.CSharp.ClassLibrary`                | Project  | WinUI 3 class library for sharing UI components           |
| `winui-unittest`      | `Microsoft.WindowsAppSDK.WinUI.CSharp.UnitTest`                    | Project  | WinUI 3 packaged test app configured for MSTest           |
| `winui-page`          | `Microsoft.WindowsAppSDK.WinUI.CSharp.Item.Page`                   | Item     | Adds a blank WinUI 3 Page                                 |
| `winui-window`        | `Microsoft.WindowsAppSDK.WinUI.CSharp.Item.Window`                 | Item     | Adds a blank WinUI 3 Window                               |
| `winui-usercontrol`   | `Microsoft.WindowsAppSDK.WinUI.CSharp.Item.UserControl.Legacy`     | Item     | Adds a WinUI 3 UserControl                                |
| `winui-templatedcontrol` | `Microsoft.WindowsAppSDK.WinUI.CSharp.Item.TemplatedControl`    | Item     | Adds a templated WinUI 3 control skeleton                 |
| `winui-resourcedictionary` | `Microsoft.WindowsAppSDK.WinUI.CSharp.Item.ResourceDictionary`| Item     | Adds a WinUI 3 ResourceDictionary                         |
| `winui-resw`          | `Microsoft.WindowsAppSDK.WinUI.CSharp.Item.Resw`                   | Item     | Adds a RESW resource file                                 |
| `winui-dialog`        | `Microsoft.WindowsAppSDK.WinUI.CSharp.Item.ContentDialog`          | Item     | Adds a WinUI 3 ContentDialog                              |

Run `dotnet new <short name> -n MyProject` to create a project from the pack once it
is installed. Item templates only surface when `dotnet new` is executed inside a
WinUI project folder (or when `--project` points to one) so that commands stay
context-aware.

### Choosing a Target Framework

All templates currently default to `net8.0` for compatibility with the widest
set of Windows App SDK tooling. To target a newer .NET version you can either:

1. Pass `--dotnet-version <tfm>` (for example `--dotnet-version net10.0`) when
	running `dotnet new ...`.
2. Edit the generated `.csproj` afterward and change `<TargetFramework>` (and
	any related `<RuntimeIdentifiers>` entries) to your preferred TFM.

`dotnet new winui --dotnet-version net10.0 -n MyApp` is the quickest way to spin
up a project that targets .NET 10 while still using the same template payload.

### CLI Quick Reference

- Create a blank WinUI app: `dotnet new winui -n MyApp`
- Add a page to an existing project: `dotnet new winui-page -n SettingsPage --project .\MyApp.csproj`
- Add a user control: `dotnet new winui-usercontrol -n ProfileCard --project .\MyApp.csproj`
- Launch the packaged app directly: `dotnet run -c Debug -p:Platform=$env:PROCESSOR_ARCHITECTURE`
- Launch with WinApp Runtime tooling (after building/registering): `winapp run .\MyApp\bin\x64\Debug\<TargetFramework>\MyApp.exe`

Whenever possible prefer the CLI scaffolding over hand authoring new files so
token replacements, namespaces, and resource wiring stay consistent.
Replace `<TargetFramework>` with the exact folder emitted by your build (for
example `net8.0-windows10.0.19041.0`).

## Local testing workflow

1. Pack the templates: `dotnet pack dev/VSIX/DotnetNewTemplates/WinAppSdk.CSharp.DotnetNewTemplates.csproj -c Release -o localpackages`.
2. If you already have an older version installed, remove it with `dotnet new uninstall Microsoft.WindowsAppSDK.WinUI.CSharp.Templates`.
3. Install the freshly packed nupkg: `dotnet new install .\localpackages\Microsoft.WindowsAppSDK.WinUI.CSharp.Templates.<version>.nupkg`. The `<version>` suffix (for example `0.0.1-experimental`) is controlled by the `<Version>` value in [WinAppSdk.CSharp.DotnetNewTemplates.csproj](WinAppSdk.CSharp.DotnetNewTemplates.csproj#L3-L38), so bump it there when needed.

## Building the NuGet package

The pack project lives at `dev/VSIX/DotnetNewTemplates/WinAppSdk.CSharp.DotnetNewTemplates.csproj`.
It links the Visual Studio template files into the template pack so there is a single
source of truth. The build produces a template NuGet package in `localpackages/`:

```powershell
cd <repo-root>
dotnet pack dev/VSIX/DotnetNewTemplates/WinAppSdk.CSharp.DotnetNewTemplates.csproj -c Release -o localpackages
```

`BuildAll.ps1` also runs the same packing step so official builds automatically emit
the template pack alongside the other Windows App SDK artifacts.

## Validation checklist

- Run `dotnet pack` locally (as shown above) and use `dotnet new install` to verify each template still scaffolds and runs.
- Execute `dotnet new --list | findstr winui` (PowerShell: `dotnet new --list | Select-String winui`) to confirm the pack metadata surfaces correctly.
- Open the generated projects in Visual Studio or VS Code, build them for x86/x64/ARM64, and ensure packaged deployments succeed on Windows 10 version 1809 or later.
- When contributing changes, note the updated template version in your PR description so downstream publishing systems pick up the new package.
