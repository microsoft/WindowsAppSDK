# Windows App SDK .NET CLI Templates

This directory contains the assets that produce the `dotnet new` template pack for the
Windows App SDK C# Desktop templates. The templates are built directly from the
existing Visual Studio template sources under `dev/VSIX/ProjectTemplates/Desktop/CSharp`
and `dev/VSIX/ItemTemplates/Desktop/CSharp`, so we only maintain one copy of the XAML,
code-behind, and project files.

## Templates

| Short name            | Identity                                        | Description                                |
|-----------------------|-------------------------------------------------|--------------------------------------------|
| `wasdk-packaged`      | `Microsoft.WindowsAppSDK.CSharp.Packaged`       | WinUI 3 packaged app + MSIX packaging proj |
| `wasdk-single`        | `Microsoft.WindowsAppSDK.CSharp.SingleProject`  | Single-project MSIX WinUI 3 app            |
| `wasdk-classlib`      | `Microsoft.WindowsAppSDK.CSharp.ClassLibrary`   | WinUI 3 class library                      |
| `wasdk-unittest`      | `Microsoft.WindowsAppSDK.CSharp.UnitTest`       | WinUI 3 packaged test app                  |
| `wasdk-item-blankwin` | `Microsoft.WindowsAppSDK.CSharp.Item.BlankWindow` | WinUI 3 Blank Window item template      |

Run `dotnet new <short name> -n MyProject` to create a project from the pack once it
is installed.

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
