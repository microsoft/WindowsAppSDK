# Adding a new WinUI C# template

C# templates have one implementation: a self-contained `dotnet new` template
under `Dotnet\templates\<template-name>`. The NuGet package
`Microsoft.WindowsAppSDK.WinUI.CSharp.Templates` ships both to the CLI and inside
the C# VSIX. The only exception is the VSIX-only separate-packaging template,
which retains its `.vstemplate` implementation under
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
        App.xaml / MainWindow.xaml / ...
```

For item templates, include only the item sources and `.template.config`.
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
`ProjectTemplates`. A `Templates.pkgdef` generated at build time registers that
directory with Visual Studio's template engine, keyed to the VSIX version so
Visual Studio rescans the templates after every update. Each deployment
flavor's VSIX manifest declares the pkgdef as a
`Microsoft.VisualStudio.VsPackage` asset. Visual Studio 2022 and
later discover the templates directly, following
[the templateSamples approach](https://github.com/phenning/templateSamples).

VSIX installation registers templates for Visual Studio; CLI users still run
`dotnet new install`. The two-project `.csproj` + `.wapproj` template remains
available only in Visual Studio through its existing template project, localized
VS package resources, and `Microsoft.VisualStudio.ProjectTemplate` asset. It is
not included in the NuGet template pack.

C++/WinRT templates remain under `Source` and continue using their existing
`.vstemplate` build and packaging path.
