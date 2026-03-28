---
name: build-repo
description: Build the Windows App SDK repository from source. Use when asked to build the repo, compile the SDK, run BuildAll, restore NuGet transport packages, fix build errors related to missing packages or certificate signing, or set up a local development environment for the first time. Triggers on requests involving building, compiling, MSBuild, NuGet restore, transport packages, FrameworkUdk, or test certificate issues.
---

# Build the Windows App SDK Repository

This skill teaches you how to build the full Windows App SDK repo locally. The process has two distinct phases: **one-time setup** (prerequisites that persist across builds) and **every-build steps** (the actual build command).

## When to Use This Skill

**Primary triggers** — Use this skill when:

1. **First-time local build** — A developer clones the repo and needs to build it end-to-end.
2. **Build failures** — Errors mention missing transport packages (`Microsoft.FrameworkUdk`, `Microsoft.ProjectReunion.InteractiveExperiences.TransportPackage`, etc.) or certificate signing failures.
3. **CI-to-local translation** — Someone wants to reproduce what the CI pipeline does on a local machine.
4. **Clean rebuild** — After running `.\BuildAll.ps1 -Clean` or deleting `BuildOutput/`, `obj/`, `.user/`.

**Anti-patterns** — Do NOT use this skill when:
- Building a standalone app that *consumes* the Windows App SDK NuGet package (that is normal app development, not repo building).
- Running only unit tests (see `TestAll.ps1` instead).

## Prerequisites

| Requirement | Minimum Version | How to Verify |
|-------------|----------------|---------------|
| Visual Studio 2022 | 17.8+ with "Desktop development with C++" and ".NET desktop development" workloads | `& "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationVersion` |
| .NET SDK | 8.0+ | `dotnet --version` |
| NuGet CLI | 6.0+ | `nuget help` — install from https://www.nuget.org/downloads |
| Windows SDK | 10.0.17763.0+ | Included with VS C++ workload |
| PowerShell | 5.1+ | `$PSVersionTable.PSVersion` |
| Git | Any | `git --version` |
| OS | Windows 10 1809 (build 17763)+ | `[Environment]::OSVersion.Version` |

## Part 1: One-Time Setup

These steps only need to be performed once after cloning the repo (or after running `.\BuildAll.ps1 -Clean` which deletes the `.user/` folder and `build\override`).

### Step 1 — Authenticate to the Internal NuGet Feed

The repo depends on an internal Azure DevOps NuGet feed. On first access, NuGet will prompt a device-flow login.

```powershell
# This happens automatically during nuget restore below.
# When prompted, open the URL shown, enter the code, and sign in with your Microsoft account.
```

> **Tip**: If you have the Azure Artifacts Credential Provider installed, authentication may be automatic. See https://github.com/microsoft/artifacts-credprovider.

### Step 2 — Generate and Restore Transport Packages

The CI pipeline runs a script to generate `build\packages.config` from `eng\Version.Details.xml` and then restores the packages. `BuildAll.ps1` does **not** do this automatically.

```powershell
# Generate packages.config from version details
.\build\scripts\ConvertVersionDetailsToPackageConfig.ps1 `
    .\eng\Version.Details.xml `
    .\build\packages.config

# Restore transport packages into the packages/ directory
nuget restore .\build\packages.config -ConfigFile .\NuGet.config -PackagesDirectory .\packages
```

### Step 3 — Fix Package Directory Layout

`nuget restore` creates a **flat** directory layout (`packages\PackageName.Version\`), but the `.vcxproj` files expect a **nested** layout (`packages\PackageName\Version\`). Run the [Setup-BuildPrerequisites.ps1](./scripts/Setup-BuildPrerequisites.ps1) script to fix this automatically:

```powershell
.\.github\skills\build-repo\scripts\Setup-BuildPrerequisites.ps1
```

Or fix manually — the script does the equivalent of:

```powershell
Get-ChildItem .\packages -Directory | ForEach-Object {
    if ($_.Name -match '^(.+?)\.(\d+\..+)$') {
        $nested = "packages\$($Matches[1])\$($Matches[2])"
        if (-not (Test-Path $nested)) {
            New-Item $nested -ItemType Directory -Force | Out-Null
            Copy-Item "$($_.FullName)\*" $nested -Recurse -Force
        }
    }
}
```

### Step 4 — Test Certificate (Usually Automatic)

`BuildAll.ps1` auto-creates a self-signed test certificate on first build (stored in `.user/`). If it fails or the certificate expires, recreate it:

```powershell
$cert = New-SelfSignedCertificate `
    -Type Custom `
    -Subject "CN=Microsoft Corporation, O=Microsoft Corporation, L=Redmond, S=Washington, C=US" `
    -KeyUsage DigitalSignature `
    -FriendlyName "Windows App SDK Test Certificate" `
    -CertStoreLocation "Cert:\CurrentUser\My" `
    -TextExtension @("2.5.29.37={text}1.3.6.1.5.5.7.3.3","2.5.29.19={text}Subject Type:End Entity") `
    -NotAfter (Get-Date).AddYears(5)

# Export and save to .user/
New-Item -Path ".user" -ItemType Directory -Force | Out-Null
Export-Certificate -Cert $cert -FilePath ".user\winappsdk.certificate.test.cer" | Out-Null
$pwd = [System.Guid]::NewGuid().ToString()
Set-Content -Path ".user\winappsdk.certificate.test.pwd" -Value $pwd -NoNewline
Export-PfxCertificate -Cert $cert -FilePath ".user\winappsdk.certificate.test.pfx" -Password (ConvertTo-SecureString $pwd -AsPlainText -Force) | Out-Null
Set-Content -Path ".user\winappsdk.certificate.test.thumbprint" -Value $cert.Thumbprint -NoNewline
```

### Verify One-Time Setup

After completing setup, verify:

```powershell
# Transport packages exist in nested layout
Test-Path "packages\Microsoft.FrameworkUdk"           # True
Test-Path "packages\Microsoft.ProjectReunion.InteractiveExperiences.TransportPackage" # True

# Certificate files exist
Test-Path ".user\winappsdk.certificate.test.cer"      # True
Test-Path ".user\winappsdk.certificate.test.pfx"      # True
```

## Part 2: Every Build

Once the one-time setup is done, building is a single command:

```powershell
.\BuildAll.ps1
```

This defaults to **x64 Release**. Common variations:

| Scenario | Command |
|----------|---------|
| Default (x64 Release) | `.\BuildAll.ps1` |
| Specific platform + config | `.\BuildAll.ps1 -Platform x64 -Configuration Debug` |
| Multiple platforms | `.\BuildAll.ps1 -Platform "x64,x86,arm64"` |
| Clean first | `.\BuildAll.ps1 -Clean` then `.\BuildAll.ps1` |

### What BuildAll.ps1 Does

| Step | Action |
|------|--------|
| 1 | Generates version override files in `build\override\` |
| 2 | NuGet restore for `WindowsAppRuntime.sln` |
| 3 | MSBuild `WindowsAppRuntime.sln` (native C++/WinRT DLLs) |
| 4 | MSBuild `dev\MRTCore\mrt\MrtCore.sln` (MRT resource system) |
| 5 | MSBuild AnyCPU Bootstrap (.NET projections) |
| 6 | Stages files and packs `.nupkg` output |

### Build Output

| Artifact | Location |
|----------|----------|
| Binaries | `BuildOutput\Release\x64\` (varies by config/platform) |
| Foundation Transport NuPkg | `BuildOutput\` |
| Component NuPkg | `BuildOutput\` |
| Intermediate files | `obj\` |

### Expected Warnings (Safe to Ignore)

| Warning Code | Description |
|--------------|-------------|
| NU5100 / NU5128 | NuGet packaging layout warnings |
| NETSDK1138 | Target framework `net6.0-windows` is out of support |
| MSB3245 | Could not resolve assembly (for optional interop types like `Windows.Media.Capture`) |
| CS8002 | Referenced assembly does not have a strong name |
| NETSDK1201 | RuntimeIdentifier warning for .NET projects |

## Part 3: Component-Level Builds (Fast Iteration)

After a successful full build, you can rebuild only the component you changed instead of the whole solution. This is **much faster** for iterative development.

### Locating MSBuild

`msbuild.exe` is not on `PATH` by default. Resolve it via `vswhere`:

```powershell
$msbuild = "$(& "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -latest -prerelease -requires Microsoft.Component.MSBuild -property installationPath)\MSBuild\Current\Bin\MSBuild.exe"
```

Then use `& $msbuild` for all commands below.

### Architecture: Shared Items vs Standalone Projects

Most component folders under `dev\` are `.vcxitems` **shared-items projects** — they have no build output of their own. Their source files compile directly into `WindowsAppRuntime_DLL`. A few components are standalone `.vcxproj` files that produce their own binaries.

### Quick Reference: What to Build When You Change a Component

| Changed folder | Project type | Fast rebuild command |
|---|---|---|
| `dev\AccessControl\` | `.vcxitems` → main DLL | `& $msbuild dev\WindowsAppRuntime_DLL\WindowsAppRuntime_DLL.vcxproj /p:Configuration=Release /p:Platform=x64` |
| `dev\AppLifecycle\` | `.vcxitems` → main DLL | *(same as above)* |
| `dev\ApplicationData\` | `.vcxitems` → main DLL | *(same as above)* |
| `dev\AppNotifications\` | `.vcxitems` → main DLL | *(same as above)* |
| `dev\BackgroundTask\` | `.vcxitems` → main DLL | *(same as above)* |
| `dev\Common\` | `.vcxitems` → main DLL | *(same as above)* |
| `dev\Decimal\` | `.vcxitems` → main DLL | *(same as above)* |
| `dev\Deployment\` | `.vcxitems` → main DLL | *(same as above)* |
| `dev\DynamicDependency\API\` | `.vcxitems` → main DLL | *(same as above)* |
| `dev\EnvironmentManager\` | `.vcxitems` → main DLL | *(same as above)* |
| `dev\Interop\CameraCaptureUI\` | `.vcxitems` → main DLL | *(same as above)* |
| `dev\Interop\StoragePickers\` | `.vcxitems` → main DLL | *(same as above)* |
| `dev\Licensing\` | `.vcxitems` → main DLL | *(same as above)* |
| `dev\Notifications\` | `.vcxitems` → main DLL | *(same as above)* |
| `dev\OAuth\` | `.vcxitems` → main DLL | *(same as above)* |
| `dev\PackageManager\API\` | `.vcxitems` → main DLL | *(same as above)* |
| `dev\PowerNotifications\` | `.vcxitems` → main DLL | *(same as above)* |
| `dev\PushNotifications\` (vcxitems) | `.vcxitems` → main DLL | *(same as above)* |
| `dev\RuntimeCompatibilityOptions\` | `.vcxitems` → main DLL | *(same as above)* |
| `dev\UndockedRegFreeWinRT\` | `.vcxitems` → main DLL | *(same as above)* |
| `dev\VersionInfo\` | `.vcxitems` → main DLL | *(same as above)* |
| `dev\Detours\` | Standalone `.vcxproj` | `& $msbuild dev\Detours\Detours.vcxproj /p:Configuration=Release /p:Platform=x64` |
| `dev\WindowsAppRuntime_BootstrapDLL\` | Standalone `.vcxproj` | `& $msbuild dev\WindowsAppRuntime_BootstrapDLL\WindowsAppRuntime_BootstrapDLL.vcxproj /p:Configuration=Release /p:Platform=x64` |
| `dev\PushNotifications\PushNotificationsLongRunningTask\` | Standalone `.vcxproj` | `& $msbuild dev\PushNotifications\PushNotificationsLongRunningTask\PushNotificationsLongRunningTask.vcxproj /p:Configuration=Release /p:Platform=x64` |
| `dev\DeploymentAgent\` | Standalone `.vcxproj` | `& $msbuild dev\DeploymentAgent\DeploymentAgent.vcxproj /p:Configuration=Release /p:Platform=x64` |
| `dev\RestartAgent\` | Standalone `.vcxproj` | `& $msbuild dev\RestartAgent\RestartAgent.vcxproj /p:Configuration=Release /p:Platform=x64` |
| `dev\MRTCore\` | Separate solution | `& $msbuild dev\MRTCore\mrt\MrtCore.sln /p:Configuration=Release /p:Platform=x64` |
| `dev\Projections\CS\*` | C# `.csproj` | `& $msbuild dev\Projections\CS\<Name>\<Name>.csproj /p:Configuration=Release /p:Platform=AnyCPU` |
| `dev\Bootstrap\CS\` | C# `.csproj` | `& $msbuild dev\Bootstrap\CS\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.csproj /p:Configuration=Release /p:Platform=AnyCPU` |

### How It Works

MSBuild is **incremental** — it only recompiles files whose timestamps have changed. When you build `WindowsAppRuntime_DLL.vcxproj` after changing one `.cpp` file in `dev\AppLifecycle\`, it will:

1. Skip all up-to-date dependencies
2. Recompile only the changed `.cpp` file(s)
3. Re-link the DLL

This typically takes **seconds** instead of the full solution's minutes.

> **Note**: The very first single-project build may take longer because MSBuild builds all project dependencies that haven't been built yet. Subsequent builds are fast.

## Troubleshooting

| Symptom | Cause | Fix |
|---------|-------|-----|
| `msbuild: The term 'msbuild' is not recognized` | MSBuild is not on `PATH` | Use `vswhere` to locate it (see "Locating MSBuild" in Part 3) |
| `EnsureNuGetPackageBuildImports` error mentioning a transport package `.targets` file | Transport packages not restored or flat-vs-nested directory mismatch | Run Part 1 Steps 2–3 |
| `error APPX0104: Certificate file not found` or signing errors | Missing or expired test certificate | Run Part 1 Step 4 |
| `401 Unauthorized` on NuGet restore | Internal feed authentication expired | Re-authenticate via Azure DevOps device flow (Part 1 Step 1) |
| `BuildAll.ps1 -Clean` then build fails | `-Clean` deletes `.user/`, `build\override/`, and `BuildOutput/` | Re-run Part 1 Steps 2–4, then build |
| `.wapproj` test packaging projects show `FAILED` | Test packaging projects use `ContinueOnError`; not a core build failure | Safe to ignore unless running tests |
| Build exit code 1 with 0 errors | Often a NuGet restore or post-build script issue | Check the full console output for the first failure |

## References

- [BuildAll.ps1](../../../BuildAll.ps1) — Main build entry point
- [build/scripts/ConvertVersionDetailsToPackageConfig.ps1](../../../build/scripts/ConvertVersionDetailsToPackageConfig.ps1) — Transport package manifest generator
- [eng/Version.Details.xml](../../../eng/Version.Details.xml) — Source-of-truth for transport package versions
- [NuGet.config](../../../NuGet.config) — NuGet feed configuration
- [AGENTS.md](../../../AGENTS.md) — AI contributor guide
- [Setup-BuildPrerequisites.ps1](./scripts/Setup-BuildPrerequisites.ps1) — Automated one-time setup script
