# Windows App SDK VSIX — Local Build & Test Guide

The fast inner-loop guide for building and testing the WinUI Templates VSIX on
a developer machine that already has Visual Studio 2022 and / or 2026 with the
WinUI workload installed.

## TL;DR

```powershell
# Build + install the LocalDev VSIX into every VS 17+ instance on the machine.
# No admin required. No setup.exe modify. No workload removal.
.\build-install-localdev-vsix.ps1

# Then in Visual Studio: File -> New -> Project -> filter C# -> search "WinUI"
```

That single command rebuilds your local source, installs to `%LOCALAPPDATA%`,
and refreshes the template cache. Do it after every code change you want to
see in real VS.

---

## Why LocalDev is the only locally installable flavor

The build can produce three flavors. **Only LocalDev is meant to be installed
on a developer box.** The other two are build-only artifacts.

| Flavor | `<Installation AllUsers>` | Extension Id | Locally installable? | Purpose |
|---|---|---|---|---|
| **LocalDev** ★ | `false` (per-user) | `Microsoft.WindowsAppSDK.Cs.Dev17.LocalDev` | **Yes — no admin** | Fast dev loop. Coexists peacefully with the workload-shipped per-machine copy. |
| Standalone | `true` (per-machine) | `Microsoft.WindowsAppSDK.Cs.Dev17` | **No** | Build-only artifact (e.g. for the VS Marketplace pipeline). On any machine that already has the WinUI workload, VSIXInstaller cannot install it because the same Id is owned by 5+ workload components. |
| Component | `true` (per-machine, `IsProductComponent`) | `Microsoft.WindowsAppSDK.Cs.Dev17` | **No** | Build-only artifact for the VS Installer build pipeline (gets picked up as part of the WinUI workload component). |

> If you really need to test the per-machine install path, do it inside a clean
> VM that does **not** have the WinUI workload installed. Don't try to
> side-load Standalone or Component on a workload-equipped machine — the
> "Uninstall failed; please uninstall all of the following components"
> failure cascade is documented in [investigation.md](investigation.md).

---

## Prerequisites (one-time)

| Requirement | Details |
|-------------|---------|
| **Visual Studio 2022 (17.0+)** or **2026** | Required for MSBuild and VSSDK targets |
| **Workloads** | `.NET desktop development` + `Visual Studio extension development` |
| **.NET 8 SDK** | Needed by the `WinAppSdk.CSharp.DotnetNewTemplates` project |
| **Internet access** | To restore NuGet packages from nuget.org |

Quick checks:

```powershell
& "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -latest -format json
dotnet --list-sdks
```

---

## Inner loop: build + install + reinstall

The recommended one-shot orchestrator:

```powershell
# Build LocalDev for both C# and C++; install into every VS 17+ instance.
.\build-install-localdev-vsix.ps1

# Reinstall after a code change (uninstalls old per-user copy first):
.\build-install-localdev-vsix.ps1 -UninstallFirst

# Skip the build step (reuse the latest .vsix in publish\VSIX):
.\build-install-localdev-vsix.ps1 -SkipBuild

# Limit to one language:
.\build-install-localdev-vsix.ps1 -Language CSharp

# Limit to one VS major version:
.\build-install-localdev-vsix.ps1 -VsVersionRange '[17.0,18.0)'   # VS 2022 only
.\build-install-localdev-vsix.ps1 -VsVersionRange '[18.0,19.0)'   # VS 2026 only
```

Or run the steps separately (same result):

```powershell
.\Build-VSIX.ps1                 # default = -Deployment LocalDev
.\Install-LocalDev-VSIX.ps1
```

### What the install script does
1. Refuses to run while any `devenv.exe` is open (templates are cached at
   startup).
2. `vswhere` discovers all VS 17+ instances.
3. `VSIXInstaller /quiet /instanceIds:<id>` per (VSIX, instance) pair. **No
   `/admin`, no elevation.** Output goes to
   `%LOCALAPPDATA%\Microsoft\VisualStudio\<edhive>\Extensions\<guid>\`.
4. `devenv /UpdateConfiguration` per instance to refresh
   `ProjectTemplatesCache`, `ItemTemplatesCache`, `ComponentModelCache`.

### What it deliberately does NOT do
- No `setup.exe modify` (never touches VS Setup state).
- No removal of workload components.
- No deletion of files under Program Files.
- No admin elevation.

### Uninstall the LocalDev copy

```powershell
& "<VSPath>\Common7\IDE\VSIXInstaller.exe" /uninstall:Microsoft.WindowsAppSDK.Cs.Dev17.LocalDev /quiet
& "<VSPath>\Common7\IDE\VSIXInstaller.exe" /uninstall:Microsoft.WindowsAppSDK.Cpp.Dev17.LocalDev /quiet
```

The workload-shipped per-machine copy is never touched and is reactivated
automatically once the LocalDev copy is gone.

### Verifying in Visual Studio

1. Launch Visual Studio (any installed VS 17+ instance).
2. File → New → Project. Filter Language=C#, search "WinUI". Expect these
   seven project templates in this order:

   | # | Template | SortOrder |
   |---|---|---|
   | 1 | WinUI Blank App | 10 |
   | 2 | WinUI Navigation App | 20 |
   | 3 | WinUI TabView App | 30 |
   | 4 | WinUI MVVM App | 40 |
   | 5 | WinUI Blank App (Packaged WAP) | 50 |
   | 6 | WinUI Class Library | 60 |
   | 7 | WinUI Unit Test App | 70 |

3. (Optional) Confirm VS picked up your local build, not the workload copy:
   Extensions → Manage Extensions → Installed → look for
   **"Windows App SDK C# VS Templates (LocalDev)"** — the `(LocalDev)`
   suffix is on the VSIX `<DisplayName>` and proves the per-user copy is
   active. The workload copy ("Windows App SDK C# VS Templates", no suffix)
   may also appear; that's fine — the higher-version per-user LocalDev
   registration shadows it for File → New → Project.

---

## Build-only flavors (Standalone, Component)

Use these only when you need an artifact for signing / publishing / pipeline
parity. **They cannot be installed locally on a workload-equipped machine.**

```powershell
# Build the Standalone artifact only:
.\Build-VSIX.ps1 -Deployment Standalone

# Build the Component artifact only:
.\Build-VSIX.ps1 -Deployment Component

# Build both:
.\Build-VSIX.ps1 -Deployment Both

# Build with a specific Windows App SDK version:
.\Build-VSIX.ps1 -Deployment Standalone -WindowsAppSDKVersion "1.8.260317003"

# Build using a local .nupkg directory (auto-extracts the WindowsAppSDK version
# from the embedded .nuspec):
.\Build-VSIX.ps1 -Deployment Standalone -NupkgSourceDir "C:\my-packages"

# Override the auto-generated VSIX version (default is 99.<yyyy>.<MMdd>.<HHmm>):
.\Build-VSIX.ps1 -Deployment Standalone -OptionalVSIXVersion "99.2026.0428.1640"
```

The output `.vsix` files land in `.\publish\VSIX\` named with the version, e.g.
`WindowsAppSDK.Cs.Extension.Dev17.Standalone.99.2026.0428.1640.vsix`.

---

## File reference

| File | Purpose |
|------|---------|
| `Build-VSIX.ps1` | Builds VSIXes. Default `-Deployment LocalDev`. |
| `Install-LocalDev-VSIX.ps1` | Per-user install of the LocalDev VSIX into VS 17+ instances. No admin. |
| `build-install-localdev-vsix.ps1` | One-shot orchestrator: Build-VSIX (LocalDev) + Install-LocalDev-VSIX. |
| `vsix-nuget.config` | NuGet config the build script passes via `/p:RestoreConfigFile`. |
| `investigation.md` | Historical findings about why per-machine install is broken on workload-equipped machines. Read this before trying to "fix" Standalone install. |

---

## Troubleshooting

### Visual Studio shows the old templates after rebuild

You launched VS while it had the old per-user extension cached. Either:

- close VS, run `.\build-install-localdev-vsix.ps1 -UninstallFirst`, then
  relaunch VS, OR
- open Tools → Get Tools and Features (or `devenv /UpdateConfiguration` from a
  shell) to force the template cache rebuild.

### "Visual Studio is running" error from the install script

Per-user VSIX installs only take effect on the next VS startup, so the script
refuses to run while any `devenv.exe` exists. Close all VS instances and
re-run.

### NuGet restore fails with "Unable to find version..."

The repo's root `NuGet.config` uses `<clear/>` and points at Microsoft
internal feeds only. `Build-VSIX.ps1` works around this by passing
`vsix-nuget.config` via `/p:RestoreConfigFile`. If you're invoking MSBuild
yourself, use the same parameter.

### `Microsoft.VsSDK.targets was not found`

Open Visual Studio Installer → Modify → check the **Visual Studio extension
development** workload.

### `DotnetNewTemplates` fails to build

The `WinAppSdk.CSharp.DotnetNewTemplates.csproj` targets `net8.0`. Install the
[.NET 8 SDK](https://dotnet.microsoft.com/download/dotnet/8.0).

### `VSSDK1300: Could not find a part of the path...`

The VSSDK extracts template ZIPs into deeply nested paths and the .NET
Framework APIs it uses do not honor `LongPathsEnabled`. `Build-VSIX.ps1`
already redirects build output to `C:\tmp\vsixbo\` to keep paths short. If
you're invoking MSBuild yourself, pass `/p:BuildOutput=C:\tmp\vsixbo\`.

### "Version 1.0.0-preview1 of package Microsoft.WindowsAppSDK not found"

You ran `Build-VSIX.ps1` without `-WindowsAppSDKVersion` or `-NupkgSourceDir`,
so the build fell back to the placeholder version baked into
`Directory.Build.props`. The VSIX file still builds and installs (the inner
templates carry token placeholders that are rewritten at template-instantiation
time), but `dotnet new`-style restore against the published nupkg won't work.
Pass a real version when you need package-realistic testing:

```powershell
.\Build-VSIX.ps1 -Deployment LocalDev -WindowsAppSDKVersion "1.8.260317003"
```

### Want to install the Standalone or Component VSIX locally

Don't. They share an extension Id with the workload-shipped copy and
VSIXInstaller refuses to side-load over a workload-managed extension. See
[investigation.md](investigation.md) for the gory details. Use the LocalDev
flavor for local testing, or test inside a clean VM without the WinUI
workload.
