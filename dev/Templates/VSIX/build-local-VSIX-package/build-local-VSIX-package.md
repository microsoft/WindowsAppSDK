# Windows App SDK VSIX — Local Build Guide

## TL;NR

```powershell
# 1. Build.
.\Build-VSIX.ps1 -Deployment Component

# 2. Install.
.\Install-VSIX.ps1

# 3. Open Visual Studio -> File -> New -> Project -> search "WinUI"
```

> **Note**: `-OptionalVSIXVersion` defaults to `99.<yyyy>.<MMdd>.<HHmm>` (e.g., `99.2026.0416.1640`).
> Output files are named with the version, e.g., `WindowsAppSDK.Cs.Extension.Dev17.Component.99.2026.0416.1640.vsix`.

## Overview

This guide describes how to build the Windows App SDK Visual Studio extension
(VSIX) packages locally, without running the full Azure Pipelines build that
takes several hours.

The build produces up to **4 VSIX files**:

| VSIX | Description |
|------|-------------|
| `WindowsAppSDK.Cs.Extension.Dev17.Standalone.vsix` | C# project/item templates (standalone install) |
| `WindowsAppSDK.Cs.Extension.Dev17.Component.vsix` | C# project/item templates (VS component install) |
| `WindowsAppSDK.Cpp.Extension.Dev17.Standalone.vsix` | C++/WinRT project/item templates (standalone install) |
| `WindowsAppSDK.Cpp.Extension.Dev17.Component.vsix` | C++/WinRT project/item templates (VS component install) |

---

## Prerequisites

| Requirement | Details |
|-------------|---------|
| **Visual Studio 2022 (17.0+)** or later | Required for MSBuild and VSSDK targets |
| **Workloads** | `.NET desktop development` + `Visual Studio extension development` |
| **.NET 8 SDK** | Needed by the `DotnetNewTemplates` project (targets net8.0) |
| **Internet access** | To restore NuGet packages from nuget.org (or a local nupkg) |

### How to Check Prerequisites

```powershell
# Check Visual Studio installation
& "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -latest -format json

# Check .NET SDKs
dotnet --list-sdks

# Check MSBuild availability
& "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -latest -requires Microsoft.Component.MSBuild -find "MSBuild\**\Bin\MSBuild.exe"
```

---

## Quick Start (One-Liner)

```powershell
.\Build-VSIX.ps1 -WindowsAppSDKVersion "2.0.0-preview2" -Deployment Component
```

This will:
1. Locate MSBuild via vswhere
2. Auto-generate VSIX version as `99.<yyyy>.<MMdd>.<HHmm>`
3. Restore NuGet packages using nuget.org
4. Build the VSIX solution for Component deployment
5. Copy the versioned `.vsix` files to `.\publish\VSIX\`

---

## Usage Examples

### Build with a specific Windows App SDK version

```powershell
.\Build-VSIX.ps1 -WindowsAppSDKVersion "2.0.0-preview2" -Deployment Component
```

### Override the auto-generated VSIX version

```powershell
.\Build-VSIX.ps1 -WindowsAppSDKVersion "2.0.0-preview2" -OptionalVSIXVersion "99.2026.0416.1640" -Deployment Component
```

### Build only the Standalone VSIX

```powershell
.\Build-VSIX.ps1 -WindowsAppSDKVersion "2.0.0-preview2" -Deployment Standalone
```

### Build using a local .nupkg file

```powershell
# Place your Microsoft.WindowsAppSDK.*.nupkg in a directory
.\Build-VSIX.ps1 -NupkgSourceDir "C:\my-packages"
```

The script will:
- Automatically extract the version from the nupkg's embedded `.nuspec`
- Add the directory as a NuGet package source

### Build with experimental features enabled

```powershell
.\Build-VSIX.ps1 -WindowsAppSDKVersion "1.8.260317003" -EnableExperimentalVSIXFeatures
```

### Specify a custom output directory

```powershell
.\Build-VSIX.ps1 -WindowsAppSDKVersion "1.8.260317003" -OutputDir "D:\vsix-output"
```

### Point to a non-default repo location

```powershell
.\Build-VSIX.ps1 -WindowsAppSDKVersion "1.8.260317003" -RepoRoot "C:\repos\WindowsAppSDK"
```

---

## Manual Build Steps

If you prefer to run the commands manually (or need to debug issues), here are
the exact MSBuild invocations the script performs:

### Step 1: Find MSBuild

```powershell
$msbuild = & "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" `
    -latest -requires Microsoft.Component.MSBuild `
    -find "MSBuild\**\Bin\MSBuild.exe" | Select-Object -First 1
```

### Step 2: Set Variables

```powershell
$repoRoot       = "C:\path\to\WindowsAppSDK"
$solution       = "$repoRoot\dev\Templates\VSIX\WindowsAppSDK.Extension.sln"
$configuration  = "Release"
$version        = "1.8.260317003"                           # Set your desired version
$nugetConfig    = "C:\path\to\build_solution\vsix-nuget.config"   # The provided config
$buildOutput    = "C:\tmp\vsixbo\"                            # Short path to avoid MAX_PATH
```

### Step 3: Restore + Build Standalone

```powershell
# Restore
& $msbuild $solution /t:restore `
    /p:Configuration=$configuration `
    "/p:Platform=Any CPU" `
    /p:Deployment=Standalone `
    /p:WindowsAppSDKVersion=$version `
    /p:RestoreConfigFile=$nugetConfig `
    /p:BuildOutput=$buildOutput `
    /p:EnableExperimentalVSIXFeatures=false `
    /verbosity:minimal /nologo

# Build
& $msbuild $solution `
    /p:Configuration=$configuration `
    "/p:Platform=Any CPU" `
    /p:Deployment=Standalone `
    /p:WindowsAppSDKVersion=$version `
    /p:BuildOutput=$buildOutput `
    /p:EnableExperimentalVSIXFeatures=false `
    /verbosity:minimal /nologo
```

### Step 4: Restore + Build Component

```powershell
# Restore
& $msbuild $solution /t:restore `
    /p:Configuration=$configuration `
    "/p:Platform=Any CPU" `
    /p:Deployment=Component `
    /p:WindowsAppSDKVersion=$version `
    /p:RestoreConfigFile=$nugetConfig `
    /p:BuildOutput=$buildOutput `
    /p:EnableExperimentalVSIXFeatures=false `
    /verbosity:minimal /nologo

# Build
& $msbuild $solution `
    /p:Configuration=$configuration `
    "/p:Platform=Any CPU" `
    /p:Deployment=Component `
    /p:WindowsAppSDKVersion=$version `
    /p:BuildOutput=$buildOutput `
    /p:EnableExperimentalVSIXFeatures=false `
    /verbosity:minimal /nologo
```

### Step 5: Collect Output

```powershell
Get-ChildItem -Path $buildOutput -Recurse -Filter "WindowsAppSDK.*.vsix"
```

Expected output locations:
```
dev\Templates\VSIX\BuildOutput\obj\AnyCPURelease\Standalone\WindowsAppSDK.Cs.Extension.Dev17\WindowsAppSDK.Cs.Extension.Dev17.Standalone.vsix
dev\Templates\VSIX\BuildOutput\obj\AnyCPURelease\Standalone\WindowsAppSDK.Cpp.Extension.Dev17\WindowsAppSDK.Cpp.Extension.Dev17.Standalone.vsix
dev\Templates\VSIX\BuildOutput\obj\AnyCPURelease\Component\WindowsAppSDK.Cs.Extension.Dev17\WindowsAppSDK.Cs.Extension.Dev17.Component.vsix
dev\Templates\VSIX\BuildOutput\obj\AnyCPURelease\Component\WindowsAppSDK.Cpp.Extension.Dev17\WindowsAppSDK.Cpp.Extension.Dev17.Component.vsix
```

---

## Installing the VSIX

### Using the Install Script (Recommended)

```powershell
# Install both C# and C++ templates (default)
.\Install-VSIX.ps1

# Install only C# templates
.\Install-VSIX.ps1 -Language CSharp

# Install only C++ templates
.\Install-VSIX.ps1 -Language Cpp

# Install a specific VSIX file by path
.\Install-VSIX.ps1 -VsixPath ".\publish\VSIX\WindowsAppSDK.Cs.Extension.Dev17.Component.99.2026.0417.1426.vsix"

# Install from a custom directory
.\Install-VSIX.ps1 -VsixDir "D:\my-vsix"

# Skip uninstalling conflicting dotnet new templates
.\Install-VSIX.ps1 -SkipDotnetUninstall
```

The script defaults to `.\publish\VSIX` and picks the **most recently built**
`.vsix` file for each language (by file modification time). If multiple versioned
files exist (e.g. from different builds), it always selects the latest one.

> **Warning**: The auto-selection does not distinguish between Standalone and
> Component VSIX files — it picks whichever has the newest timestamp. If you have
> both types in the publish folder, use `-VsixPath` to explicitly select the
> correct one. Most VS installations with the WinUI workload require the
> **Component** version.

The script will:
1. Check that Visual Studio is closed (exits if not)
2. Uninstall conflicting `dotnet new` template packages (if found)
3. Verify VS installation and prerequisites
4. Install the VSIX using `VSIXInstaller /force /quiet`
5. Wait for installation to complete and check logs for errors

### Via Double-Click
Simply double-click any `.vsix` file. The VSIX Installer will open and guide
you through the installation.

### Via Command Line
```powershell
# Close all VS instances first!
$vsixInstaller = "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\Common7\IDE\VSIXInstaller.exe"
& $vsixInstaller /force /quiet "path\to\WindowsAppSDK.Cs.Extension.Dev17.Component.99.2026.0416.1640.vsix"
```

> **Important**: Use `Component` VSIX when VS has the extension installed via a workload
> (e.g., ".NET WinUI app development tools"). Use `Standalone` only for clean VS installs.

### Verify Installation
In Visual Studio: **Extensions → Manage Extensions** — look for
"Windows App SDK C# VS Templates" or "Windows App SDK C++ VS Templates".

---

## Troubleshooting

### NuGet restore fails with "Unable to find version..."

**Cause**: The root `NuGet.config` in the WindowsAppSDK repo uses `<clear/>`
and only has Microsoft internal feeds. Public packages can't be resolved.

**Fix**: The `Build-VSIX.ps1` script handles this by passing a custom
`vsix-nuget.config` via `/p:RestoreConfigFile`. If running manually, make sure
you use the same parameter.

### "The imported project ... Microsoft.VsSDK.targets was not found"

**Cause**: The VS SDK workload is not installed.

**Fix**: Open Visual Studio Installer → Modify → check
**Visual Studio extension development** workload.

### DotnetNewTemplates build fails

**Cause**: The `WinAppSdk.CSharp.DotnetNewTemplates.csproj` targets `net8.0`.

**Fix**: Install the [.NET 8 SDK](https://dotnet.microsoft.com/download/dotnet/8.0).

### "Version 1.0.0-preview1 of package Microsoft.WindowsAppSDK not found"

**Cause**: No `-WindowsAppSDKVersion` was specified, and the default
`1.0.0-preview1` in `Directory.Build.props` doesn't exist on nuget.org.

**Fix**: Pass a real version:
```powershell
.\Build-VSIX.ps1 -WindowsAppSDKVersion "1.8.260317003"
```

Check [nuget.org](https://www.nuget.org/packages/Microsoft.WindowsAppSDK/) for
available versions.

### Build succeeds but no .vsix files in output

**Cause**: The VSIX output location depends on the `Deployment` property.

**Fix**: Check `dev\Templates\VSIX\BuildOutput\obj\` recursively:
```powershell
Get-ChildItem -Path "dev\Templates\VSIX\BuildOutput" -Recurse -Filter "*.vsix"
```

### VSIX install fails: "lower version than required by Visual Studio"

**Cause**: VS bundles a version of this extension via the ".NET WinUI app
development tools" workload. Your built VSIX version is lower.

**Fix**: The script auto-generates a high version (`99.yyyy.MMdd.HHmm`).
If you need to override, use `-OptionalVSIXVersion "99.2026.0416.1640"`.

### VSIX install fails: "Uninstall of ... failed" or "Modifications of multiple extensions"

**Cause**: VS's built-in extension was installed as a **Component** (via workload).
A Standalone VSIX cannot replace a Component extension.

**Fix**: Build with `-Deployment Component`:
```powershell
.\Build-VSIX.ps1 -WindowsAppSDKVersion "2.0.0-preview2" -Deployment Component
```
Then install with VS closed:
```powershell
& "<VS-path>\Common7\IDE\VSIXInstaller.exe" /force /quiet <path-to-Component.vsix>
```

### VSSDK1300: "Could not find a part of the path..."

**Cause**: The VSSDK extracts template ZIP files into deeply nested paths.
When the repo is in a deep directory, the combined path exceeds Windows'
260-character MAX_PATH limit. The .NET Framework APIs used by the VSSDK do
not support long paths even when `LongPathsEnabled` is set.

**Fix**: The `Build-VSIX.ps1` script automatically redirects build output to
`C:\tmp\vsixbo\` to keep paths short. If running manually, pass:
```powershell
/p:BuildOutput=C:\tmp\vsixbo\
```

---

## How This Maps to the Pipeline

| Pipeline Step | Local Equivalent |
|---------------|-----------------|
| `DownloadPipelineArtifact@2` (get nupkg) | `-NupkgSourceDir` parameter or nuget.org |
| `Extract WindowsAppSDKVersion` (PowerShell) | `-WindowsAppSDKVersion` parameter or auto-extract from nupkg |
| `VSBuild /t:restore` (Standalone) | `MSBuild /t:restore /p:Deployment=Standalone ...` |
| `VSBuild` build (Standalone) | `MSBuild /p:Deployment=Standalone ...` |
| `VSBuild /t:restore` (Component) | `MSBuild /t:restore /p:Deployment=Component ...` |
| `VSBuild /p:Deployment=Component` | `MSBuild /p:Deployment=Component ...` |
| `CopyFiles@2` (stage output) | Script copies `.vsix` to output dir |
| Signing steps | **Skipped** (local builds are unsigned) |
| SDL analysis steps | **Skipped** (not needed for local builds) |

---

## File Reference

| File | Purpose |
|------|---------|
| `Build-VSIX.ps1` | Main build script |
| `Install-VSIX.ps1` | Install/uninstall script for built VSIX |
| `vsix-nuget.config` | NuGet config with nuget.org source |
| `build-local-VSIX-package.md` | This document |