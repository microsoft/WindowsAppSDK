# Adding a new WinUI **C#** template

The C# templates ship through two channels, both driven by the single
declarative manifest [`templates.props`](templates.props):

| Channel        | Output                                | Consumer csproj |
| -------------- | ------------------------------------- | --------------- |
| **dotnet-new** | NuGet `Microsoft.WindowsAppSDK.WinUI.CSharp.Templates` | [`Dotnet/WinAppSdk.CSharp.DotnetNewTemplates.csproj`](Dotnet/WinAppSdk.CSharp.DotnetNewTemplates.csproj) |
| **VSIX (C#)**  | VS extension (New Project / New Item) | [`VSIX/Extension/Cs/Dev17/WindowsAppSDK.Cs.Extension.Dev17.csproj`](VSIX/Extension/Cs/Dev17/WindowsAppSDK.Cs.Extension.Dev17.csproj) |

Adding a template means: drop the content under [`Source/`](Source),
add one entry to `templates.props`, and (if it ships in the VSIX) list
the template in [`VSIX/WindowsAppSDK.Extension.sln`](VSIX/WindowsAppSDK.Extension.sln).
Neither consumer csproj needs to change.

---

## TL;DR

### 1. Drop the template content under `Source/`

For a project template:

```
dev/Templates/Source/ProjectTemplates/Desktop/CSharp/<Name>/
    <Name>.csproj
    <Name>.ico                           (used by VSIX)
    <Name>.png                           (used by VSIX)
    <Name>.vstemplate                    (used by VSIX)
    App.xaml / MainWindow.xaml / ...
```

For an item template, use `Source/ItemTemplates/Neutral/CSharp/<Name>/`
with the same shape (no `.png`).

If the template ships in the VSIX, also add the `.csproj` to
[`VSIX/WindowsAppSDK.Extension.sln`](VSIX/WindowsAppSDK.Extension.sln)
so CI builds it.

### 2. If the template is a packaged WinUI app, add `Package-managed.appxmanifest`

Place it next to the `.csproj`. The pack task will rename it to
`Package.appxmanifest` in the produced template. See the FAQ for why
the non-reserved name in Source.

### 3. If the template ships to `dotnet new`, add the dotnet-new metadata folder

```
dev/Templates/Dotnet/templates/<short-name>/
    .template.config/
        template.json           (required)
        dotnetcli.host.json     (CLI parameter aliases)
        ide.host.json           (VS / VS Code metadata)
        icon.png                (shown in dialogs)
```

`<short-name>` must match the `Identity` you choose in step 4
(e.g. `templates/navigation-app/` ↔ `winui.navview`).

### 4. Add an entry to `templates.props`

Pick the item type by where the template should ship:

| Ships to dotnet-new | Ships to VSIX | Item type                       |
| :-----------------: | :-----------: | ------------------------------- |
|         ✅          |       ✅      | `ProjectTemplate`               |
|         ✅          |       ✅      | `ItemTemplate`                  |
|         ❌          |       ✅      | `VsixOnlyProjectTemplate`       |
|         ✅          |       ❌      | `DotnetNewOnlyProjectTemplate`  |
|         ❌          |       ✅      | `VsixOnlyItemTemplate`          |
|         ✅          |       ❌      | `DotnetNewOnlyItemTemplate`     |

Each entry is one MSBuild item element of the chosen type with this
shape:

```xml
<ProjectTemplate Include="winui.somename">
    <BaseName>WinUI.Desktop.Cs.SomeName</BaseName>
    <SourceDir>$(MSBuildThisFileDirectory)Source\ProjectTemplates\Desktop\CSharp\SomeName</SourceDir>
    <DotnetConfigDir>$(MSBuildThisFileDirectory)Dotnet\templates\some-name</DotnetConfigDir>
    <RenameManifestFrom>Package-managed.appxmanifest</RenameManifestFrom>
</ProjectTemplate>
```

| Metadata | Description | Required? |
| -------- | ----------- | --------- |
| `Identity` (the `Include` attribute) | For dotnet-new templates: the short name (also the `content/<id>/` subfolder in the NuGet). For VSIX-only templates: any unique name. | Always |
| `BaseName` | File-name stem of the source `.csproj` / `.ico` / `.png` / `.vstemplate`. | Always |
| `SourceDir` | Absolute path to the template's source tree. | Always |
| `DotnetConfigDir` | Absolute path to `Dotnet/templates/<short-name>/`. | When ships to dotnet-new |
| `RenameManifestFrom` | Source-side manifest filename, typically `Package-managed.appxmanifest`. Packed as `Package.appxmanifest`. | Packaged WinUI app templates only |

### 5. Local build for tests

1. dotnet new template:

    TL;DR
    ```pwsh
    # dotnet-new NuGet (inspect produced .nupkg under localpackages\)
    dotnet pack dev\Templates\Dotnet\WinAppSdk.CSharp.DotnetNewTemplates.csproj -c Debug
    
    # dotnet new uninstall Microsoft.WindowsAppSDK.WinUI.CSharp.Templates
    
    dotnet new install localpackages\Microsoft.WindowsAppSDK.WinUI.CSharp.Templates.*.nupkg
    ```

    read details in [build-local-VSIX-package.md](.\VSIX\build-local-VSIX-package\build-local-VSIX-package.md)

2. VSIX

    TL;DR
    ```pwsh
    dev\Templates\VSIX\build-local-VSIX-package\build-install-localdev-vsix.ps1
    ```

    read details in [build-local-VSIX-package.md](.\VSIX\build-local-VSIX-package\build-local-VSIX-package.md)

---

## How it works under the hood

### Single source of truth: `templates.props`

[`templates.props`](templates.props) is a plain MSBuild props file. It
declares six item collections (one per cell of the dotnet-new × VSIX
matrix above) and the per-template metadata for each entry. Default
metadata lives in `<ItemDefinitionGroup>`; per-entry metadata only
overrides what differs.

Both consuming csprojs `<Import>` this file, then partition the items by
their delivery channel:

```text
                       ProjectTemplate   ItemTemplate   VsixOnly*   DotnetNewOnly*
dotnet-new csproj           ✅                ✅            —            ✅
VSIX        csproj          ✅                ✅            ✅           —
```

Adding a template is an entry in `templates.props`. Neither csproj has to
know about it.

### dotnet-new packaging: `ExpandProjectTemplatePackItems`

`dotnet new` template packs are just NuGet packages where the template
content sits under `content/<short-name>/`. NuGet's `Pack` target
consumes `<None Pack="true" PackagePath="..." />` items. Building one
template by hand looks like this:

```xml
<!-- Repeat this for every template, hand-syncing 7 path occurrences each time -->
<None Include="..\Source\...\NavigationApp\**\*.*"
      Exclude="...\bin\**;...\obj\**;...\Package-managed.appxmanifest;
               ...\WinUI.Desktop.Cs.NavigationApp.csproj;
               ...\WinUI.Desktop.Cs.NavigationApp.ico;
               ...\WinUI.Desktop.Cs.NavigationApp.png;
               ...\WinUI.Desktop.Cs.NavigationApp.vstemplate"
      Pack="true"
      PackagePath="content/winui.navview/%(RecursiveDir)%(Filename)%(Extension)" />
<None Include="..\Source\...\NavigationApp\Package-managed.appxmanifest"
      Pack="true"
      PackagePath="content/winui.navview/Package.appxmanifest" />
<None Include="...\.template.config\**\*.*" Pack="true" PackagePath="..." />
<!-- ...and so on per template -->
```

That style is what the original PR shipped. It worked but had problems:
the dotnet csproj needed to know **every** template's exclude list, file
names, and rename rule — and adding one new template meant ~15 lines of
copy-paste with seven find-and-replace edits, none of which the compiler
or NuGet would warn about if you got one wrong.

We replaced it with an **inline C# MSBuild task** —
`ExpandProjectTemplatePackItems` in
[`WinAppSdk.CSharp.DotnetNewTemplates.csproj`](Dotnet/WinAppSdk.CSharp.DotnetNewTemplates.csproj).
It takes `@(ProjectTemplate)` (or `@(ItemTemplate)`, etc.) and per
template performs the same four-step packing recipe:

1. Pack everything under `SourceDir`, minus `bin/`, `obj/`, and the
   per-template sidecars (`.csproj` / `.ico` / `.png` / `.vstemplate`).
2. If `RenameManifestFrom` is set, re-pack that manifest under the
   reserved name `Package.appxmanifest`.
3. Pack everything under `DotnetConfigDir/.template.config/`.
4. Pack a copy of the shared `.gitignore` (project templates only).

### Why a C# task and not a pure-MSBuild `<None Include="...">` with batching

It would be more idiomatic to write something like:

```xml
<None Include="%(ProjectTemplate.SourceDir)\**\*.*"
      Exclude="%(ProjectTemplate.SourceDir)\bin\**;..."
      Pack="true"
      PackagePath="content/%(ProjectTemplate.Identity)/..." />
```

…and let MSBuild's task batching fan it out per template. Two MSBuild
rules block that path:

- **MSB5029** ("wildcard enumerates the whole drive") inspects
  `<Include>` patterns *before* batching resolves `%(...)` metadata, so
  the literal `\**\*.*` after the empty substitution is rejected.
- **MSB4191** forbids custom-metadata references in `<Condition>` at the
  top level (only inside `<Target>`), so we can't pre-filter the list
  with `Condition="'%(IncludeInVSIX)' != 'false'"` either.

An MSBuild task is opaque to both checks. The task walks the file
system with `System.IO` at run time, when all metadata has been
resolved.

### Manifest rename

Packaged WinUI apps need a file literally named `Package.appxmanifest`
for MSIX tooling to recognize them. But the Source-side template project
*itself* has to build (CI builds the whole `WindowsAppSDK.Extension.sln`
to verify templates don't bit-rot). If the file were named
`Package.appxmanifest` in the Source tree, MSIX tooling would try to
package the *template project* as a real app and fail.

The convention is therefore:

- Source tree stores it as `Package-managed.appxmanifest` (a
  non-reserved name).
- Packing renames it to `Package.appxmanifest`.

The `RenameManifestFrom` metadata is what tells the inline task to
perform that rename.

### VSIX consumption

The VSIX csproj converts the same manifest into `<ProjectReference>`
items via MSBuild item transforms:

```xml
<ProjectReference Include="@(ProjectTemplate->'%(SourceDir)\%(BaseName).csproj');@(VsixOnlyProjectTemplate->'%(SourceDir)\%(BaseName).csproj')">
    <Name>%(BaseName)</Name>
    <VSIXSubPath>ProjectTemplates</VSIXSubPath>
    <ReferenceOutputAssembly>false</ReferenceOutputAssembly>
    <IncludeOutputGroupsInVSIX>TemplateProjectOutputGroup;</IncludeOutputGroupsInVSIX>
</ProjectReference>
```

`IncludeOutputGroupsInVSIX="TemplateProjectOutputGroup"` is the VSSDK
hook each template project uses to publish its `.vstemplate` zip into
the VSIX container.

We intentionally do not specify the `<Project>` GUID hint. MSBuild
resolves ProjectReferences by path; the GUID was historically only a
hint for Solution Explorer.

### C++/WinRT isolation

The C++/WinRT VSIX project at
[`VSIX/Extension/Cpp/Dev17/WindowsAppSDK.Cpp.Extension.Dev17.csproj`](VSIX/Extension/Cpp/Dev17/WindowsAppSDK.Cpp.Extension.Dev17.csproj)
**does not** import [`templates.props`](templates.props) and is not
reached by it indirectly: neither [`Directory.Build.props`](Directory.Build.props)
nor any other auto-discovered props file injects the manifest into the
C++ side. Therefore none of the C# item collections
(`@(ProjectTemplate)`, `@(ItemTemplate)`, `@(VsixOnlyProjectTemplate)`,
`@(VsixOnlyItemTemplate)`, `@(DotnetNewOnlyProjectTemplate)`,
`@(DotnetNewOnlyItemTemplate)`) are visible to the C++ csproj, and
changes to `templates.props` cannot regress the C++ VSIX build.

If/when C++ templates are migrated to the same declarative manifest in
a follow-up, this isolation note should be updated accordingly.

---

## File / folder reference

```
dev/Templates/
├── templates.props                     ← the C# manifest (one entry per template)
├── Directory.Build.props               ← shared MSBuild props for the Templates folder
├── Dotnet/                             ← C# only: packs the dotnet-new NuGet
│   ├── WinAppSdk.CSharp.DotnetNewTemplates.csproj
│   ├── Directory.Build.props
│   └── templates/<short-name>/
│       └── .template.config/
│           ├── template.json
│           ├── dotnetcli.host.json
│           ├── ide.host.json
│           └── icon.png
├── Source/                             ← actual template content (C# and C++)
│   ├── ProjectTemplates/Desktop/CSharp/<TemplateName>/
│   │   ├── <TemplateName>.csproj
│   │   ├── <TemplateName>.{ico,png,vstemplate}
│   │   ├── Package-managed.appxmanifest    (if packaged)
│   │   └── ...source files...
│   ├── ProjectTemplates/Desktop/CppWinRT/<TemplateName>/   ← out of scope for this doc
│   ├── ItemTemplates/Neutral/CSharp/<TemplateName>/
│   └── ItemTemplates/Neutral/CppWinRT/<TemplateName>/      ← out of scope for this doc
└── VSIX/
    ├── WindowsAppSDK.Extension.sln
    ├── Extension/Cs/Dev17/WindowsAppSDK.Cs.Extension.Dev17.csproj    ← C# VSIX (consumes templates.props)
    ├── Extension/Cpp/Dev17/WindowsAppSDK.Cpp.Extension.Dev17.csproj  ← C++ VSIX (does NOT import templates.props)
    └── Directory.Build.props
```

---

## FAQ

**Q. Why is the manifest in `Source/` named `Package-managed.appxmanifest`
instead of `Package.appxmanifest`?**

The Source-side template project itself has to build cleanly — CI
builds [`VSIX/WindowsAppSDK.Extension.sln`](VSIX/WindowsAppSDK.Extension.sln)
to verify templates don't bit-rot. A file literally named
`Package.appxmanifest` would trigger MSIX tooling and try to package
the template *project itself* as a real app, breaking that build. The
Source tree therefore uses a non-reserved name and the pack task
renames it back to `Package.appxmanifest` in the produced template.

**Q. I want to add a C++/WinRT template.**

Currently, this doc and `templates.props` do not cover C++/WinRT. 

For C++ templates, add the template content under
 `Source/{Project,Item}Templates/.../CppWinRT/<Name>/` as usual, 
 then add a `<ProjectReference>` to the C++ extension csproj
([`VSIX/Extension/Cpp/Dev17/WindowsAppSDK.Cpp.Extension.Dev17.csproj`](VSIX/Extension/Cpp/Dev17/WindowsAppSDK.Cpp.Extension.Dev17.csproj))
and a corresponding `<Asset>` to the C++ vsixmanifest. 

There is no dotnet-new pack for C++/WinRT templates yet.

<!-- ci: trigger Templates PR pipeline (remove after validation) -->

