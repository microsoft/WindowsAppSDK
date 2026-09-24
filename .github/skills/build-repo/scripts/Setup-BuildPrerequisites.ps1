# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Performs one-time setup prerequisites for building the Windows App SDK repo locally.

.DESCRIPTION
    This script automates the manual steps that the CI pipeline handles but BuildAll.ps1
    does not: generating packages.config from Version.Details.xml, restoring transport
    NuGet packages, and fixing the flat-to-nested directory layout that local nuget restore
    creates.

    Run this script once after cloning the repo or after running BuildAll.ps1 -Clean.

.PARAMETER SkipRestore
    Skip NuGet restore (useful if packages are already restored and you only need the
    directory layout fix).

.PARAMETER Force
    Overwrite existing nested package directories even if they already exist.

.EXAMPLE
    .\.github\skills\build-repo\scripts\Setup-BuildPrerequisites.ps1

.EXAMPLE
    .\.github\skills\build-repo\scripts\Setup-BuildPrerequisites.ps1 -SkipRestore

.EXAMPLE
    .\.github\skills\build-repo\scripts\Setup-BuildPrerequisites.ps1 -Force
#>

[CmdletBinding()]
param(
    [switch]$SkipRestore,
    [switch]$Force
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

# Resolve repo root (four levels up from this script: .github/skills/build-repo/scripts/)
$RepoRoot = (Resolve-Path (Join-Path $PSScriptRoot '..\..\..\..')).Path
Write-Host "Repo root: $RepoRoot" -ForegroundColor Cyan

$VersionDetailsPath = Join-Path $RepoRoot 'eng\Version.Details.xml'
$PackageConfigPath = Join-Path $RepoRoot 'build\packages.config'
$ConvertScript = Join-Path $RepoRoot 'build\scripts\ConvertVersionDetailsToPackageConfig.ps1'
$NuGetConfig = Join-Path $RepoRoot 'NuGet.config'
$PackagesDir = Join-Path $RepoRoot 'packages'

# ─── Step 1: Generate packages.config ────────────────────────────────────────
Write-Host ''
Write-Host '=== Step 1: Generate build\packages.config ===' -ForegroundColor Green

if (-not (Test-Path $VersionDetailsPath)) {
    Write-Error "eng\Version.Details.xml not found at $VersionDetailsPath"
}
if (-not (Test-Path $ConvertScript)) {
    Write-Error "ConvertVersionDetailsToPackageConfig.ps1 not found at $ConvertScript"
}

& $ConvertScript $VersionDetailsPath $PackageConfigPath
Write-Host "Generated: $PackageConfigPath" -ForegroundColor Green

# ─── Step 2: NuGet Restore ───────────────────────────────────────────────────
if (-not $SkipRestore) {
    Write-Host ''
    Write-Host '=== Step 2: Restore transport packages ===' -ForegroundColor Green

    $nugetCmd = Get-Command nuget -ErrorAction SilentlyContinue
    if (-not $nugetCmd) {
        Write-Error 'nuget.exe not found on PATH. Install from https://www.nuget.org/downloads'
    }

    & nuget restore $PackageConfigPath -ConfigFile $NuGetConfig -PackagesDirectory $PackagesDir
    if ($LASTEXITCODE -ne 0) {
        Write-Error "NuGet restore failed with exit code $LASTEXITCODE"
    }
    Write-Host 'NuGet restore completed.' -ForegroundColor Green
}
else {
    Write-Host ''
    Write-Host '=== Step 2: NuGet restore SKIPPED (-SkipRestore) ===' -ForegroundColor Yellow
}

# ─── Step 3: Fix flat-to-nested directory layout ─────────────────────────────
Write-Host ''
Write-Host '=== Step 3: Fix package directory layout (flat → nested) ===' -ForegroundColor Green

if (-not (Test-Path $PackagesDir)) {
    Write-Error "Packages directory not found at $PackagesDir. Run without -SkipRestore first."
}

$fixedCount = 0
$skippedCount = 0

Get-ChildItem $PackagesDir -Directory | ForEach-Object {
    $dirName = $_.Name
    # Match flat layout: PackageName.Major.Minor.Patch[-prerelease]
    # Use a greedy-then-lazy approach: the version starts with a digit sequence containing dots
    if ($dirName -match '^(.+?)\.(\d+\..+)$') {
        $packageName = $Matches[1]
        $packageVersion = $Matches[2]
        $nestedDir = Join-Path $PackagesDir "$packageName\$packageVersion"

        if ((Test-Path $nestedDir) -and -not $Force) {
            Write-Host "  SKIP: $packageName\$packageVersion (already exists)" -ForegroundColor DarkGray
            $skippedCount++
        }
        else {
            New-Item -Path $nestedDir -ItemType Directory -Force | Out-Null
            Copy-Item -Path (Join-Path $_.FullName '*') -Destination $nestedDir -Recurse -Force
            Write-Host "  FIXED: $packageName\$packageVersion" -ForegroundColor Green
            $fixedCount++
        }
    }
}

Write-Host ''
Write-Host "Directory layout fix complete: $fixedCount fixed, $skippedCount skipped." -ForegroundColor Cyan

# ─── Summary ─────────────────────────────────────────────────────────────────
Write-Host ''
Write-Host '=== Setup Complete ===' -ForegroundColor Green
Write-Host ''
Write-Host 'One-time prerequisites are ready. You can now build with:' -ForegroundColor Cyan
Write-Host '  .\BuildAll.ps1' -ForegroundColor White
Write-Host ''
Write-Host 'If you encounter certificate signing errors on first build,' -ForegroundColor Yellow
Write-Host 'BuildAll.ps1 will auto-create a test certificate in .user/.' -ForegroundColor Yellow
Write-Host 'See SKILL.md Part 1 Step 4 if you need to create one manually.' -ForegroundColor Yellow
