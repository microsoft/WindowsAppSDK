# Adding a new WinUI C# template

C# templates share their sources in a self-contained `dotnet new` template
under `Dotnet\templates\<template-name>`. The NuGet package
`Microsoft.WindowsAppSDK.WinUI.CSharp.Templates` ships both to the CLI and inside
the C# VSIX. VSIX item templates use adjacent `.vstemplate` metadata instead of
the JSON template engine until [microsoft/microsoft-ui-xaml#12758](https://github.com/microsoft/microsoft-ui-xaml/issues/12758)
is fixed. The VSIX-only separate-packaging template
retains its `.vstemplate` implementation under
`Source\ProjectTemplates\Desktop\CSharp\PackagedApp`.

## Template layout

```text
Dotnet\templates\
    gitignore.txt                   (shared; packed into each project template)
    <template-name>\
        .template.config\
            template.json
            dotnetcli.host.json
            ide.host.json
            icon.png
            localize\
                templatestrings.<locale>.json
        ProjectTemplate.csproj
        Package.appxmanifest
        .vscode\launch.json          (VS Code debugging; app templates only)
        .vscode\extensions.json      (VS Code extension; app templates only)
        AGENTS.md                   (WinApp CLI guidance; app templates only)
        App.xaml / MainWindow.xaml / ...
```

For item templates, include the item sources, `.template.config`, and a
`.vstemplate` for Visual Studio. Preserve the existing `ItemType="Page"` and
`CustomTool="MSBuild:Compile"` metadata on XAML project items. Use localized
VS package resource IDs for classic template names and descriptions.
Use neighboring templates as examples. Define a unique `identity` and
`groupIdentity`, CLI aliases in `shortName`, and `language: C#` and `type:
project` (or `item`) tags. Declare the generated project or item files in
`primaryOutputs` so Visual Studio can open them.

Keep all template content together, including the reserved
`Package.appxmanifest` filename for packaged apps. These files are packed as
content, not compiled or packaged as an app during the template build.
Project templates rename `gitignore.txt` to `.gitignore` in `template.json`.
Don't add per-template copies; instead, add the new template's
`content\<template-name>\gitignore.txt` to the `PackagePath` list of the shared
`templates\gitignore.txt` item in `WinAppSdk.CSharp.DotnetNewTemplates.csproj`.

Visual Studio metadata, icons and parameter visibility belong in
`ide.host.json`; translated names and descriptions belong in
`.template.config\localize\templatestrings.<locale>.json`. To keep a template
CLI-only, use `"unsupportedHosts": [ { "id": "vs" } ]` in `ide.host.json`,
as the experimental Reactor templates do.

## Build and verify

```powershell
dotnet pack dev\Templates\Dotnet\WinAppSdk.CSharp.DotnetNewTemplates.csproj -c Release -o localpackages
dotnet new install .\localpackages\Microsoft.WindowsAppSDK.WinUI.CSharp.Templates.<version>.nupkg
.\dev\Templates\Dotnet\Test-DotnetNewTemplates.ps1 -SkipAppLaunch
.\dev\Templates\VSIX\build-local-VSIX-package\build-install-localdev-vsix.ps1
```

The pack project includes every template directory automatically. Apart from the
`.gitignore` path list for project templates, adding a template requires no
changes to the pack project, the VSIX project, or the VSIX solution.

## Visual Studio installation

The C# VSIX references the pack project and embeds its exact NuGet output under
`ProjectTemplates`, excluding Reactor and item templates. A `Templates.pkgdef`
generated at build time registers that
directory with Visual Studio's template engine, keyed to the VSIX version so
Visual Studio rescans the templates after every update. Each deployment
flavor's VSIX manifest declares the pkgdef as a
`Microsoft.VisualStudio.VsPackage` asset. Visual Studio 2022 and
later discover the templates directly, following
[the templateSamples approach](https://github.com/phenning/templateSamples).

Item templates are staged from the same source directories and packaged through
VSSDK using their `.vstemplate` files. The staging target resolves
`__WINUI_USERCONTROL__` and `__WINUI_RESOURCE_DICTIONARY__` to literal type names:
these are CLI template-engine constants, not classic template parameters.
Shipping them unchanged would reintroduce #6968. Each VSIX manifest registers
the classic templates with a `Microsoft.VisualStudio.ItemTemplate` asset.
The standalone CLI pack retains its JSON-based items and excludes `.vstemplate`
files.

Run `VSIX\Test-ItemTemplates.ps1 -VsixPath <C# VSIX> -CliTemplatePackagePath <standalone nupkg>`
to check the packaged item build actions, source tokens, and CLI/VSIX separation.

VSIX installation registers templates for Visual Studio; CLI users still run
`dotnet new install`. The two-project `.csproj` + `.wapproj` template remains
available only in Visual Studio through its existing template project, localized
VS package resources, and `Microsoft.VisualStudio.ProjectTemplate` asset. It is
not included in the NuGet template pack.

C++/WinRT templates remain under `Source` and continue using their existing
`.vstemplate` build and packaging path.
