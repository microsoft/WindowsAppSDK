# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

# Build script for external (open-source) contributors.
# Builds the subset of WindowsAppSDK that does not require internal Microsoft packages.
#
# Prerequisites:
#   1. Visual Studio 2022 with required workloads (see docs/Coding-Guidelines/GettingStarted.md)
#   2. Run DevCheck.cmd -CheckAll -FixAll (from an admin prompt) at least once
#
# Usage:
#   .\BuildOSS.ps1                              # Build Debug/x64 (default)
#   .\BuildOSS.ps1 -Configuration Release       # Build Release/x64
#   .\BuildOSS.ps1 -Platform ARM64              # Build Debug/ARM64
#   .\BuildOSS.ps1 -Clean                       # Clean before building

Param(
    [ValidateSet('Debug', 'Release')]
    [string]$Configuration = 'Debug',

    [ValidateSet('x86', 'x64', 'ARM64')]
    [string]$Platform = 'x64',

    [switch]$Clean
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

$RepoRoot = $PSScriptRoot

# --- Step 1: Generate build override files (if they don't exist) ---
$buildOverridePath = Join-Path $RepoRoot 'build\override'
if (-not (Test-Path "$buildOverridePath\DynamicDependency-Override.h"))
{
    Write-Host "Generating build override files..."
    & "$RepoRoot\tools\GenerateDynamicDependencyOverrides.ps1" -Path $buildOverridePath
    & "$RepoRoot\tools\GeneratePushNotificationsOverrides.ps1" -Path $buildOverridePath
}
else
{
    Write-Host "Build override files already exist, skipping generation."
}

# --- Step 2: NuGet restore using OSS config ---
Write-Host ""
Write-Host "Restoring NuGet packages (OSS config)..."
$nugetExe = Join-Path $RepoRoot '.nuget\nuget.exe'
if (-not (Test-Path $nugetExe))
{
    # Fall back to nuget on PATH
    $nugetExe = 'nuget'
}

$slnf = Join-Path $RepoRoot 'WindowsAppRuntime.OSS.slnf'
$nugetConfig = Join-Path $RepoRoot 'NuGet.OSS.config'

& $nugetExe restore $slnf -configfile $nugetConfig -NonInteractive
if ($LASTEXITCODE -ne 0)
{
    Write-Host "ERROR: NuGet restore failed. Make sure nuget.exe is available (run DevCheck.cmd -CheckNugetExe -FixAll)."
    exit 1
}

# --- Step 3: Build ---
Write-Host ""
if ($Clean)
{
    Write-Host "Cleaning $Configuration|$Platform..."
    msbuild $slnf /t:Clean /m /p:Configuration=$Configuration /p:Platform=$Platform /p:BuildForOSS=true
}

Write-Host "Building $Configuration|$Platform..."
msbuild $slnf /m /p:Configuration=$Configuration /p:Platform=$Platform /p:BuildForOSS=true
if ($LASTEXITCODE -ne 0)
{
    Write-Host ""
    Write-Host "ERROR: Build failed."
    exit 1
}

Write-Host ""
Write-Host "Build succeeded: $Configuration|$Platform"
Write-Host "Output: BuildOutput\$Configuration\$Platform\"
