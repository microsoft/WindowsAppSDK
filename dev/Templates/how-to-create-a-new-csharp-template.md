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
    README.md                   (optional outline; see step 5)
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

### 5. (Optional) Per-template README

If the template should ship a README that users see in their new
project root, drop a README.md **outline** in the channel-specific
location:

| Channel    | Outline location                                                          |
| ---------- | ------------------------------------------------------------------------- |
| dotnet-new | `Dotnet/templates/<short-name>/README.md` (next to `.template.config/`)   |
| VSIX       | `VSIX/templates/Desktop/CSharp/<Name>/README.md`                          |

An outline mixes inline prose (title, intro, project-layout diagram)
with `####FileName.md####` placeholders that name section files in
[`Source/TemplateReadmeSections/`](Source/TemplateReadmeSections) **verbatim**:

```markdown
# WinUI 3 desktop MVVM app

A WinUI 3 desktop app pre-wired with the MVVM pattern...

## Project layout
...

####Prerequisites.md####
####BuildAndRun.app.vsix.md####
####CommonNextSteps.app.vsix.md####
####PublishGuide.app.vsix.md####
```

Reusable section files live under
[`Source/TemplateReadmeSections/`](Source/TemplateReadmeSections). Their
filenames bake the channel/shape suffix (`.app.vsix.md`,
`.library.dotnet.md`, `.wapproj.vsix.md`, …) so the outline can
pinpoint the exact file — no inference, no fallback chain.

At build / pack time the outline is merged into the final README that
ships in the produced template:

- **dotnet-new**: merged inside `ExpandProjectTemplatePackItems` and
  packed as `content/<short-name>/README.md`.
- **VSIX**: merged by `_GenerateMergedReadme`
  (in [`Source/Directory.Build.targets`](Source/Directory.Build.targets))
  directly next to the `.vstemplate` (i.e. into
  `$(MSBuildProjectDirectory)\README.md`) so the VS SDK packs it
  into the project-template `.zip`. The generated file is `.gitignore`d
  and removed by `Clean`.

For VSIX templates, the `.vstemplate` must also list the README so VS
copies it into the user's new project:

```xml
<ProjectItem ReplaceParameters="false" TargetFileName="README.md">README.md</ProjectItem>
```

`ReplaceParameters="false"` is intentional — the file is already in
its final shipping form at build time; VS must not re-scan it for
`$xxx$` substitution (which would corrupt example shell variables or
text that happens to contain `$...$` strings). See
[Per-template README assembly](#per-template-readme-assembly) below
for the full pipeline.

### 6. Local build for tests

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
template performs the same five-step packing recipe:

1. Pack everything under `SourceDir`, minus `bin/`, `obj/`, and the
   per-template sidecars (`.csproj` / `.ico` / `.png` / `.vstemplate`).
2. If `RenameManifestFrom` is set, re-pack that manifest under the
   reserved name `Package.appxmanifest`.
3. Pack everything under `DotnetConfigDir/.template.config/`.
4. If `DotnetConfigDir` contains a `README.md` outline, merge it
   (substituting `####FileName.md####` placeholders with files from
   [`Source/TemplateReadmeSections/`](Source/TemplateReadmeSections)) and pack
   the result as `content/<short-name>/README.md`. See
   [Per-template README assembly](#per-template-readme-assembly) below.
5. Pack a copy of the shared `.gitignore` (project templates only).

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

### Per-template README assembly

Per-template READMEs are not authored as monolithic files. Each
template ships a per-channel **outline** (short, template-specific
prose) that embeds `####FileName.md####` placeholders pointing at
shared **section files** in
[`Source/TemplateReadmeSections/`](Source/TemplateReadmeSections). At
build / pack time an MSBuild task expands those placeholders into the
final README that the produced template ships.

> **Design intent.** `Source/` is meant to be the **shared canonical
> content area** consumed by both the dotnet-new and the VSIX channels.
> The sections folder lives there for that reason. Today `Source/` also
> still contains VSIX-only sidecars (`.vstemplate`, `.ico`, `.png`, the
> twin `.csproj`) for legacy reasons; relocating those to `VSIX/` so
> `Source/` is purely shared is a known future cleanup.

#### Inputs

| Kind             | Path                                                              | Purpose                                                                                                                                       |
| ---------------- | ----------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------- |
| Outline (dotnet) | `Dotnet/templates/<short-name>/README.md`                         | Per-template prose; merged when packing the dotnet-new NuGet.                                                                                 |
| Outline (VSIX)   | `VSIX/templates/Desktop/CSharp/<Name>/README.md`                  | Per-template prose; merged when building the VSIX twin csproj under `Source/`.                                                                |
| Section files    | [`Source/TemplateReadmeSections/*.md`](Source/TemplateReadmeSections) | Reusable, shared prose consumed by both channels. Filename bakes the channel/shape suffix (`.app.vsix.md`, `.library.dotnet.md`, `.wapproj.vsix.md`, …). |

#### Placeholder syntax

Outlines reference sections by **literal filename**:

```text
####Prerequisites.md####
####BuildAndRun.app.vsix.md####
####CommonNextSteps.library.dotnet.md####
```

There is intentionally **no** shape/channel inference and **no**
fallback chain — the placeholder *is* the filename. A reader of any
outline can pinpoint the exact source of every embedded paragraph
without consulting resolver code.

#### Merge tasks

| Channel    | Task                                                                  | Where it lives                                                                                                                              | Output                                                                                                                                                       |
| ---------- | --------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| dotnet-new | `ExpandProjectTemplatePackItems` (step 4 of its packing recipe)       | [`Dotnet/WinAppSdk.CSharp.DotnetNewTemplates.csproj`](Dotnet/WinAppSdk.CSharp.DotnetNewTemplates.csproj)                                    | Merged file written under `$(IntermediateOutputPath)merged-readmes/<short-name>/README.md` and packed as `content/<short-name>/README.md`.                   |
| VSIX       | `GenerateMergedReadme` (invoked by `_GenerateMergedReadme` target)    | [`Source/Directory.Build.targets`](Source/Directory.Build.targets) (auto-imported by `Microsoft.Common.targets` for every Source twin csproj) | Merged file written to `$(MSBuildProjectDirectory)\README.md` (next to the `.vstemplate`, `.gitignore`d) so the VS SDK's `CreateProjectTemplateZipFile` task picks it up via the `.vstemplate`'s `<ProjectItem>README.md</ProjectItem>` reference. |

Both tasks are deliberately a **single** `Regex.Replace` pass over the
outline: read outline → for each `####File.md####` match, substitute
`File.ReadAllText(Source/TemplateReadmeSections/File.md).TrimEnd()` →
collapse runs of 3+ newlines → fail the build on any missing file or
leftover marker. There are no helpers and no conditional branches
around content massaging.

#### VSIX wiring

For VSIX templates the merged README must also be advertised in the
`.vstemplate` so VS copies it into the user's new project:

```xml
<ProjectItem ReplaceParameters="false" TargetFileName="README.md">README.md</ProjectItem>
```

`ReplaceParameters="false"` is intentional: the file is already in
its final shipping form, and VS must not rescan it for `$xxx$`
substitution (which could corrupt example shell variables, code
fragments, or text that happens to contain `$...$` strings).

#### Build-time guarantees

Both tasks fail the build if:

- An outline references a section file that does not exist.
- A `####...####` marker survives substitution (i.e. malformed
  placeholder).
- The merged content cannot be written.

A typo in an outline therefore cannot silently ship to users.

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
│       ├── README.md                   ← optional outline (dotnet channel)
│       └── .template.config/
│           ├── template.json
│           ├── dotnetcli.host.json
│           ├── ide.host.json
│           └── icon.png
├── Source/                             ← shared canonical content consumed by both channels
│   ├── Directory.Build.targets         ← merges per-template READMEs for VSIX twin csprojs
│   ├── TemplateReadmeSections/         ← reusable README section files (channel/shape suffixes baked into the filename)
│   │   ├── Prerequisites.md
│   │   ├── BuildAndRun.app.dotnet.md
│   │   ├── BuildAndRun.app.vsix.md
│   │   ├── ...                         (30 files total — see folder for full list)
│   │   └── FrameworkFooter.vsix.md
│   ├── ProjectTemplates/Desktop/CSharp/<TemplateName>/      ← currently also holds VSIX-only sidecars (see note below)
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
    ├── templates/Desktop/CSharp/<TemplateName>/
    │   └── README.md                   ← optional outline (VSIX channel)
    └── Directory.Build.props
```

> **Note on `Source/`.** The intent is that `Source/` holds **only**
> content that is shared by both the dotnet-new and the VSIX channels.
> Today the per-template VSIX sidecars (`.vstemplate`, `.ico`, `.png`,
> the twin `.csproj`) still live alongside the source files for legacy
> reasons. Moving those into `VSIX/` so `Source/` is purely shared is a
> known future cleanup.

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
