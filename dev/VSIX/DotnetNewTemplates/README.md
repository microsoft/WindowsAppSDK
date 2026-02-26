# Windows App SDK .NET CLI Templates

This directory contains the assets that produce the `dotnet new` template pack for the
Windows App SDK C# Desktop templates. The templates are built directly from the
existing Visual Studio template sources under `dev/VSIX/ProjectTemplates/Desktop/CSharp`
and `dev/VSIX/ItemTemplates/Desktop/CSharp`, so we only maintain one copy of the XAML,
code-behind, and project files.

## Templates

| Short name          | Identity                                           | Description                                |
|---------------------|----------------------------------------------------|--------------------------------------------|
| `winui3`            | `Microsoft.WindowsAppSDK.CSharp.SingleProject`     | New blank WinUI 3 app                      |
| `winui3-lib`        | `Microsoft.WindowsAppSDK.CSharp.ClassLibrary`      | New WinUI 3 class library                  |
| `winui3-unittest`   | `Microsoft.WindowsAppSDK.CSharp.UnitTest`          | New WinUI 3 unit test app                  |
| `winui3-window`     | `Microsoft.WindowsAppSDK.CSharp.Item.BlankWindow`  | New window in an existing app              |
| `winui3-page`       | `Microsoft.WindowsAppSDK.CSharp.Item.BlankPage`    | New page in an existing app                |
| `winui3-usercontrol`| `Microsoft.WindowsAppSDK.CSharp.Item.UserControl`  | New user control in an existing app        |
| `winui3-dialog`     | `Microsoft.WindowsAppSDK.CSharp.Item.ContentDialog`| New content dialog in an existing app      |

Run `dotnet new <short name> -n MyProject` to create a project from the pack once it
is installed.

## Local testing workflow

1. Pack the templates: `dotnet pack dev/VSIX/DotnetNewTemplates/WinAppSdk.CSharp.DotnetNewTemplates.csproj -c Release -o localpackages`.
2. If you already have an older version installed, remove it with `dotnet new uninstall Microsoft.WindowsAppSDK.CSharp.Templates`.
3. Install the freshly packed nupkg: `dotnet new install .\localpackages\Microsoft.WindowsAppSDK.CSharp.Templates.<version>.nupkg`. The `<version>` suffix (for example `0.0.1-experimental`) is controlled by the `<Version>` value in [WinAppSdk.CSharp.DotnetNewTemplates.csproj](WinAppSdk.CSharp.DotnetNewTemplates.csproj#L3-L38), so bump it there when needed.

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

## Azure Pipelines validation

- Windows builds run through [ProjectReunion Template Pack](https://dev.azure.com/microsoft/ProjectReunion/_build?definitionId=186691). To trigger it, first mirror your changes into the internal Foundation repo, then queue the pipeline manually.
- Before running the pipeline, bump the `<Version>` in [WinAppSdk.CSharp.DotnetNewTemplates.csproj](WinAppSdk.CSharp.DotnetNewTemplates.csproj#L3-L38) to avoid conflicts when the “publish to internal feed” option is enabled.
- Successful runs publish the resulting `.nupkg` both as a pipeline artifact and (if that option is selected) to the internal feed [Project.Reunion.nuget.internal](https://dev.azure.com/microsoft/ProjectReunion/_artifacts/feed/Project.Reunion.nuget.internal/NuGet/Microsoft.WindowsAppSDK.CSharp.Templates).
