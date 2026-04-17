---
name: verify-fix
description: Create a WinUI 3 verification app that demonstrates or reproduces a fix using the locally built SDK NuGet package. Use when asked to verify a fix, create a demo app for an issue, test a local SDK build, reproduce a bug with the built package, or create a verification application for a GitHub issue. Triggers on requests involving verify fix, demo app, test local build, reproduce issue, or verification app.
license: Complete terms in LICENSE.txt
---

# Verify Fix Skill

Create standalone WinUI 3 verification apps that reference the locally built Windows App SDK NuGet package (`BuildOutput/*.nupkg`) to demonstrate or reproduce a fix for a specific GitHub issue.

## Skill Contents

```
.github/skills/verify-fix/
├── SKILL.md                    # This file
├── LICENSE.txt                 # MIT License
├── scripts/
│   └── New-VerificationApp.ps1 # Creates and configures the verification app
└── references/
    └── nuget-local-source.md   # Guide for local NuGet source configuration
```

## When to Use This Skill

- Verify a bug fix works end-to-end in a real WinUI 3 app
- Demonstrate a new API or feature added by a fix
- Test that the locally built SDK NuGet package is consumable
- Provide a developer with a ready-to-run app to manually verify a fix

## When NOT to Use This Skill (Skip)

Write a skip signal instead when:

| Scenario | Example |
|----------|---------|
| Internal-only fix | Build scripts, CI pipeline YAML, signing config |
| Infrastructure change | NuGet spec updates, transport package versions |
| Non-observable internals | Telemetry plumbing, internal logging format |
| Different-repo fix | Issue belongs to microsoft-ui-xaml or another repo |
| Hardware-specific | ARM64-only or specific OS build required |
| Documentation-only | Markdown, comments, README changes |

## Prerequisites

- Windows App SDK repo built successfully (`BuildAll.ps1` exit code 0)
- `BuildOutput/Microsoft.WindowsAppSDK.Foundation.*.nupkg` exists
- Visual Studio 2022 with Windows App SDK workload
- .NET 8.0+
- The `create-windows-app-from-scratch` MCP tool available (for template scaffolding)

## Required Variables

| Variable | Description | Example |
|----------|-------------|---------|
| `{{IssueNumber}}` | GitHub issue number | `6075` |
| `{{BuildOutputPath}}` | Absolute path to BuildOutput folder | `C:\WindowsAppSDK\BuildOutput` |

## Output

- **App directory**: `Generated Files/verifyFix/{{IssueNumber}}/app/`
- **Signal file**: `Generated Files/verifyFix/{{IssueNumber}}/.signal`
- **README**: `Generated Files/verifyFix/{{IssueNumber}}/app/README.md`

The verification app is **never committed** to the PR branch. It exists only for local developer verification.

## Signal File

```json
{
  "status": "success|skipped|failure",
  "issueNumber": 6075,
  "timestamp": "2026-03-06T10:05:23Z",
  "appPath": "Generated Files/verifyFix/6075/app/",
  "nupkgUsed": "Microsoft.WindowsAppSDK.Foundation.1.8.0.nupkg",
  "reason": "(only for skipped/failure)"
}
```

## Workflow

### Step 1 — Locate the Built Package

```powershell
$nupkgs = Get-ChildItem "$env:REPO_ROOT\BuildOutput\*.nupkg" | Sort-Object LastWriteTime -Descending
$foundationPkg = $nupkgs | Where-Object { $_.Name -match 'Microsoft\.WindowsAppSDK\.Foundation\.' } | Select-Object -First 1
if (-not $foundationPkg) {
    Write-Error "No Foundation .nupkg found in BuildOutput. Run BuildAll.ps1 first."
    exit 1
}
# Extract version from filename: Microsoft.WindowsAppSDK.Foundation.1.8.0.nupkg → 1.8.0
$version = $foundationPkg.Name -replace 'Microsoft\.WindowsAppSDK\.Foundation\.|\.nupkg', ''
Write-Host "Found package: $($foundationPkg.Name) (version: $version)"
```

### Step 2 — Scaffold the App

Use the `create-windows-app-from-scratch` MCP tool with:

| Parameter | Value |
|-----------|-------|
| App name | `VerifyFix{{IssueNumber}}App` |
| Target directory | `Generated Files/verifyFix/{{IssueNumber}}/app/` |
| Template | C# + WinUI 3 + Sparse (default) |

If the MCP tool is unavailable, create a minimal app manually — see [manual scaffolding](#manual-app-scaffolding) below.

### Step 3 — Configure Local NuGet Source

Create or overwrite `nuget.config` in the app's solution root:

```xml
<?xml version="1.0" encoding="utf-8"?>
<configuration>
  <packageSources>
    <clear />
    <add key="LocalSDKBuild" value="{{BuildOutputPath}}" />
    <add key="nuget.org" value="https://api.nuget.org/v3/index.json" />
  </packageSources>
</configuration>
```

**Key point**: `<clear />` ensures the app uses the local build first, falling back to nuget.org only for non-SDK packages.

### Step 4 — Pin SDK Package Version

In the `.csproj` file, set an explicit `PackageReference`:

```xml
<ItemGroup>
  <PackageReference Include="Microsoft.WindowsAppSDK" Version="{{version}}" />
</ItemGroup>
```

Remove or override any `<WindowsAppSDKSelfContained>`, `<WindowsPackageType>`, or version ranges that might pull a different package.

### Step 5 — Add Verification Code

Based on the issue type:

**Bug Fix Verification** — reproduce the original bug scenario:
```csharp
// MainWindow.xaml.cs
// Exercises the code path that was broken, expects it to work now
private void VerifyFix()
{
    try
    {
        // Call the API or trigger the scenario from the issue
        // ...
        StatusText.Text = "✅ Fix verified — issue #{{IssueNumber}} resolved";
    }
    catch (Exception ex)
    {
        StatusText.Text = $"❌ Fix NOT working — {ex.Message}";
    }
}
```

**New Feature Verification** — exercise the new API:
```csharp
// MainWindow.xaml.cs
// Calls the new API added by the feature
private void DemonstrateFeature()
{
    // Use the new API
    // ...
    StatusText.Text = "✅ New feature works — issue #{{IssueNumber}}";
}
```

### Step 6 — Build & Write Signal

Build the app, then write the signal file based on the result.

## Manual App Scaffolding

If the MCP tool is unavailable, create these files manually:

### Solution File

```
Generated Files/verifyFix/{{IssueNumber}}/app/VerifyFix{{IssueNumber}}App.sln
```

### Project File

```xml
<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <OutputType>WinExe</OutputType>
    <TargetFramework>net8.0-windows10.0.19041.0</TargetFramework>
    <TargetPlatformMinVersion>10.0.17763.0</TargetPlatformMinVersion>
    <RootNamespace>VerifyFix{{IssueNumber}}App</RootNamespace>
    <ApplicationManifest>app.manifest</ApplicationManifest>
    <Platforms>x86;x64;ARM64</Platforms>
    <RuntimeIdentifiers>win-x86;win-x64;win-arm64</RuntimeIdentifiers>
    <UseWinUI>true</UseWinUI>
    <WindowsPackageType>None</WindowsPackageType>
  </PropertyGroup>
  <ItemGroup>
    <PackageReference Include="Microsoft.WindowsAppSDK" Version="{{version}}" />
    <PackageReference Include="Microsoft.Windows.SDK.BuildTools" Version="10.0.26100.1742" />
  </ItemGroup>
</Project>
```

### App.xaml / MainWindow.xaml

Standard WinUI 3 boilerplate with a `TextBlock` named `StatusText` for verification output.

## NuGet Troubleshooting

| Problem | Solution |
|---------|----------|
| Package not found | Verify `BuildOutput/*.nupkg` exists; check `nuget.config` path is absolute |
| Version mismatch | Extract exact version from `.nupkg` filename; don't guess |
| Restore fails | Run `dotnet nuget locals all --clear` then restore again |
| Wrong package used | Ensure `<clear />` is in `nuget.config` to prevent global feed override |
| Build error in SDK | The local SDK build may have pre-existing issues; note in signal |

## References

- [Local NuGet Source Configuration](./references/nuget-local-source.md)
- [Windows App SDK NuGet Package Structure](https://learn.microsoft.com/windows/apps/windows-app-sdk/downloads)
- [Build Repo Skill](../build-repo/SKILL.md) — how to build the SDK and produce `.nupkg`
