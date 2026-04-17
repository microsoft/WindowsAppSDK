<#
.SYNOPSIS
    Builds the Windows App SDK VSIX extension packages locally.

.DESCRIPTION
    Reproduces the Azure Pipelines "CreateVsix" stage on a local machine.
    Builds up to 4 VSIX files:
      - WindowsAppSDK.Cs.Extension.Dev17.Standalone.vsix
      - WindowsAppSDK.Cs.Extension.Dev17.Component.vsix
      - WindowsAppSDK.Cpp.Extension.Dev17.Standalone.vsix
      - WindowsAppSDK.Cpp.Extension.Dev17.Component.vsix

.PARAMETER WindowsAppSDKVersion
    The version of the Microsoft.WindowsAppSDK NuGet package to use.
    Example: "1.8.260317003"
    If not specified, defaults to the version in Directory.Build.props (1.0.0-preview1).

.PARAMETER Configuration
    Build configuration. Default: Release.

.PARAMETER Deployment
    Which deployment type(s) to build.
    "Standalone"  - Build only the standalone VSIX
    "Component"   - Build only the component VSIX
    "Both"        - Build both (default)

.PARAMETER EnableExperimentalVSIXFeatures
    When set, marks the VSIX as experimental (adds .Experimental suffix, sets Preview=true).

.PARAMETER OutputDir
    Where to copy the final .vsix files. Default: .\publish\VSIX (relative to script dir).

.PARAMETER NupkgSourceDir
    Optional path to a directory containing pre-downloaded Microsoft.WindowsAppSDK*.nupkg.
    This directory will be added as a NuGet package source.

.PARAMETER RepoRoot
    Path to the WindowsAppSDK repository root. Default: auto-detected relative to this script.

.PARAMETER SkipRestore
    Skip NuGet restore (useful if you've already restored).

.EXAMPLE
    .\Build-VSIX.ps1 -WindowsAppSDKVersion "1.8.260317003"

.EXAMPLE
    .\Build-VSIX.ps1 -WindowsAppSDKVersion "1.8.260317003" -Deployment Standalone

.EXAMPLE
    .\Build-VSIX.ps1 -NupkgSourceDir "C:\packages" -Deployment Both
#>

[CmdletBinding()]
param(
    [string]$WindowsAppSDKVersion = "",

    [ValidateSet("Debug", "Release")]
    [string]$Configuration = "Release",

    [ValidateSet("Standalone", "Component", "Both")]
    [string]$Deployment = "Both",

    [switch]$EnableExperimentalVSIXFeatures,

    [string]$OutputDir = "",

    [string]$NupkgSourceDir = "",

    [string]$RepoRoot = "",

    [string]$OptionalVSIXVersion = "",

    [switch]$SkipRestore
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = "Stop"

#region --- Helper Functions ---

function Write-Banner {
    param([string]$Message)
    $line = "=" * 70
    Write-Host ""
    Write-Host $line -ForegroundColor Cyan
    Write-Host "  $Message" -ForegroundColor Cyan
    Write-Host $line -ForegroundColor Cyan
    Write-Host ""
}

function Write-Step {
    param([string]$Message)
    Write-Host "[*] $Message" -ForegroundColor Green
}

function Write-Warn {
    param([string]$Message)
    Write-Host "[!] $Message" -ForegroundColor Yellow
}

function Write-Err {
    param([string]$Message)
    Write-Host "[X] $Message" -ForegroundColor Red
}

function Find-MSBuild {
    $vswherePath = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    if (-not (Test-Path $vswherePath)) {
        Write-Err "vswhere.exe not found. Please install Visual Studio 2022 or later."
        exit 1
    }

    $msbuildPath = & $vswherePath -latest -requires Microsoft.Component.MSBuild -find "MSBuild\**\Bin\MSBuild.exe" 2>$null | Select-Object -First 1
    if (-not $msbuildPath -or -not (Test-Path $msbuildPath)) {
        Write-Err "MSBuild.exe not found. Please install Visual Studio 2022+ with the '.NET desktop development' workload."
        exit 1
    }

    return $msbuildPath
}

function Find-VSInstallPath {
    $vswherePath = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
    $installPath = & $vswherePath -latest -property installationPath 2>$null
    return $installPath
}

function Extract-VersionFromNupkg {
    param([string]$NupkgDir)

    $nupkgFiles = Get-ChildItem -Path $NupkgDir -Filter "Microsoft.WindowsAppSDK.*.nupkg" |
        Where-Object { $_.Name -match "Microsoft\.WindowsAppSDK\.[0-9].*\.nupkg" }

    if ($nupkgFiles.Count -eq 0) {
        Write-Err "No Microsoft.WindowsAppSDK*.nupkg files found in '$NupkgDir'."
        exit 1
    }

    if ($nupkgFiles.Count -gt 1) {
        Write-Err "Multiple Microsoft.WindowsAppSDK nupkg files found in '$NupkgDir'. Please keep only one."
        foreach ($f in $nupkgFiles) { Write-Err "  - $($f.Name)" }
        exit 1
    }

    $nupkg = $nupkgFiles[0]
    Write-Step "Found nupkg: $($nupkg.Name)"

    # Extract version from nuspec inside the nupkg
    $tempExtract = Join-Path $env:TEMP "vsix-nupkg-extract-$(Get-Random)"
    try {
        $zipCopy = Join-Path $env:TEMP "$($nupkg.BaseName).zip"
        Copy-Item $nupkg.FullName $zipCopy -Force
        Expand-Archive -Path $zipCopy -DestinationPath $tempExtract -Force
        Remove-Item $zipCopy -Force

        $nuspecFiles = Get-ChildItem -Path $tempExtract -Recurse -Filter "*.nuspec"
        foreach ($nuspecFile in $nuspecFiles) {
            [xml]$nuspec = Get-Content -Path $nuspecFile.FullName
            if ($nuspec.package.metadata.id -eq "Microsoft.WindowsAppSDK") {
                $version = $nuspec.package.metadata.version
                Write-Step "Extracted version from nuspec: $version"
                return $version
            }
        }
        Write-Err "Could not find Microsoft.WindowsAppSDK nuspec in the nupkg."
        exit 1
    }
    finally {
        if (Test-Path $tempExtract) { Remove-Item $tempExtract -Recurse -Force -ErrorAction SilentlyContinue }
    }
}

#endregion

#region --- Setup ---

Write-Banner "Windows App SDK VSIX Local Build"

$scriptDir = $PSScriptRoot
if (-not $scriptDir) { $scriptDir = (Get-Location).Path }

# Resolve repo root
if ($RepoRoot -eq "") {
    $RepoRoot = Join-Path $scriptDir "..\..\..\"
}
$RepoRoot = (Resolve-Path $RepoRoot -ErrorAction SilentlyContinue).Path
if (-not $RepoRoot -or -not (Test-Path $RepoRoot)) {
    Write-Err "WindowsAppSDK repo root not found. Use -RepoRoot to specify."
    exit 1
}
Write-Step "Repo root: $RepoRoot"

# Resolve paths
$vsixDir = Join-Path $RepoRoot "dev\Templates\VSIX"
$solutionFile = Join-Path $vsixDir "WindowsAppSDK.Extension.sln"

if (-not (Test-Path $solutionFile)) {
    Write-Err "Solution file not found: $solutionFile"
    exit 1
}
Write-Step "Solution: $solutionFile"

# Resolve output directory
if ($OutputDir -eq "") {
    $OutputDir = Join-Path $scriptDir "publish\VSIX"
}
if (-not (Test-Path $OutputDir)) {
    New-Item -ItemType Directory -Path $OutputDir -Force | Out-Null
}
$OutputDir = (Resolve-Path $OutputDir).Path
Write-Step "Output dir: $OutputDir"

#endregion

#region --- Prerequisites ---

Write-Banner "Checking Prerequisites"

# 1. Find MSBuild
$msbuild = Find-MSBuild
Write-Step "MSBuild: $msbuild"

# 2. Check VS installation
$vsPath = Find-VSInstallPath
if ($vsPath) {
    Write-Step "Visual Studio: $vsPath"
} else {
    Write-Warn "Could not detect VS installation path."
}

# 3. Check VSSDK targets
$vssdkTargets = Join-Path $vsPath "MSBuild\Microsoft\VisualStudio\v17.0\VSSDK\Microsoft.VsSDK.targets"
if (-not (Test-Path $vssdkTargets)) {
    # Try generic version path
    $vssdkSearch = Get-ChildItem -Path (Join-Path $vsPath "MSBuild") -Recurse -Filter "Microsoft.VsSDK.targets" -ErrorAction SilentlyContinue | Select-Object -First 1
    if ($vssdkSearch) {
        Write-Step "VSSDK targets: $($vssdkSearch.FullName)"
    } else {
        Write-Warn "Microsoft.VsSDK.targets not found. Install the 'Visual Studio extension development' workload."
        Write-Warn "The build may still succeed if VSSDK is restored via NuGet (Microsoft.VSSDK.BuildTools)."
    }
} else {
    Write-Step "VSSDK targets: $vssdkTargets"
}

# 4. Check .NET SDK
$dotnetPath = Get-Command dotnet -ErrorAction SilentlyContinue
if ($dotnetPath) {
    $sdkVersions = & dotnet --list-sdks 2>$null
    $hasNet8 = $sdkVersions | Where-Object { $_ -match "^8\." }
    if ($hasNet8) {
        Write-Step ".NET 8 SDK: found"
    } else {
        Write-Warn ".NET 8 SDK not found. The DotnetNewTemplates project requires it."
        Write-Warn "Install from https://dotnet.microsoft.com/download/dotnet/8.0"
    }
} else {
    Write-Warn "dotnet CLI not found. The DotnetNewTemplates project may fail to build."
}

#endregion

#region --- Version Resolution ---

Write-Banner "Resolving Package Version"

if ($NupkgSourceDir -ne "" -and $WindowsAppSDKVersion -eq "") {
    $NupkgSourceDir = (Resolve-Path $NupkgSourceDir).Path
    Write-Step "Extracting version from nupkg in: $NupkgSourceDir"
    $WindowsAppSDKVersion = Extract-VersionFromNupkg -NupkgDir $NupkgSourceDir
}

if ($WindowsAppSDKVersion -eq "") {
    Write-Warn "No -WindowsAppSDKVersion specified and no -NupkgSourceDir provided."
    Write-Warn "Falling back to the default in Directory.Build.props (1.0.0-preview1)."
    Write-Warn "This version likely does not exist on nuget.org."
    Write-Warn "Specify -WindowsAppSDKVersion to use a real version (e.g., '1.8.260317003')."
    $WindowsAppSDKVersion = ""
}

if ($WindowsAppSDKVersion -ne "") {
    Write-Step "WindowsAppSDKVersion = $WindowsAppSDKVersion"
}

if ($OptionalVSIXVersion -eq "") {
    $now = Get-Date
    $OptionalVSIXVersion = "99.$($now.ToString('yyyy')).$($now.ToString('MMdd')).$($now.ToString('HHmm'))"
    Write-Step "OptionalVSIXVersion = $OptionalVSIXVersion (auto-generated from current time)"
} else {
    Write-Step "OptionalVSIXVersion = $OptionalVSIXVersion (user-specified)"
}

#endregion

#region --- NuGet Config ---

Write-Banner "Configuring NuGet Sources"

$nugetConfig = Join-Path $scriptDir "vsix-nuget.config"
if (-not (Test-Path $nugetConfig)) {
    Write-Err "vsix-nuget.config not found at: $nugetConfig"
    Write-Err "This file should be alongside Build-VSIX.ps1."
    exit 1
}

# If a local nupkg source is provided, create a temp config with that source added
$effectiveNugetConfig = $nugetConfig
if ($NupkgSourceDir -ne "") {
    $tempConfig = Join-Path $env:TEMP "vsix-nuget-temp-$(Get-Random).config"
    [xml]$configXml = Get-Content $nugetConfig
    $newSource = $configXml.CreateElement("add")
    $newSource.SetAttribute("key", "LocalNupkg")
    $newSource.SetAttribute("value", $NupkgSourceDir)
    $configXml.configuration.packageSources.AppendChild($newSource) | Out-Null
    $configXml.Save($tempConfig)
    $effectiveNugetConfig = $tempConfig
    Write-Step "Added local nupkg source: $NupkgSourceDir"
}

Write-Step "NuGet config: $effectiveNugetConfig"

# Use a short build output path to avoid MAX_PATH issues with the VSSDK.
# The VSSDK extracts template ZIPs into deeply nested paths; if the repo
# is in a deep directory the combined path can exceed 260 characters.
$shortBuildOutput = "C:\tmp\vsixbo\"
if (-not (Test-Path $shortBuildOutput)) {
    New-Item -ItemType Directory -Path $shortBuildOutput -Force | Out-Null
}
Write-Step "Build output (short path): $shortBuildOutput"

#endregion

#region --- Build Functions ---

function Invoke-MSBuildRestore {
    param(
        [string]$DeploymentType
    )

    Write-Step "Restoring ($DeploymentType)..."

    $args = @(
        $solutionFile
        "/t:restore"
        "/p:Configuration=$Configuration"
        "/p:Platform=Any CPU"
        "/p:Deployment=$DeploymentType"
        "/p:RestoreConfigFile=$effectiveNugetConfig"
        "/p:EnableExperimentalVSIXFeatures=$($EnableExperimentalVSIXFeatures.IsPresent.ToString().ToLower())"
        "/p:BuildOutput=$shortBuildOutput"
        "/verbosity:minimal"
        "/nologo"
    )

    if ($WindowsAppSDKVersion -ne "") {
        $args += "/p:WindowsAppSDKVersion=$WindowsAppSDKVersion"
    }

    if ($NupkgSourceDir -ne "") {
        $args += "/p:RestoreAdditionalProjectSources=$NupkgSourceDir"
    }

    if ($OptionalVSIXVersion -ne "") {
        $args += "/p:OptionalVSIXVersion=$OptionalVSIXVersion"
    }

    Write-Host "  > MSBuild $($args -join ' ')" -ForegroundColor DarkGray
    & $msbuild @args
    if ($LASTEXITCODE -ne 0) {
        Write-Err "NuGet restore failed for $DeploymentType deployment."
        exit $LASTEXITCODE
    }
}

function Invoke-MSBuildBuild {
    param(
        [string]$DeploymentType
    )

    Write-Step "Building ($DeploymentType)..."

    $args = @(
        $solutionFile
        "/p:Configuration=$Configuration"
        "/p:Platform=Any CPU"
        "/p:Deployment=$DeploymentType"
        "/p:EnableExperimentalVSIXFeatures=$($EnableExperimentalVSIXFeatures.IsPresent.ToString().ToLower())"
        "/p:BuildOutput=$shortBuildOutput"
        "/verbosity:minimal"
        "/nologo"
    )

    if ($WindowsAppSDKVersion -ne "") {
        $args += "/p:WindowsAppSDKVersion=$WindowsAppSDKVersion"
    }

    if ($OptionalVSIXVersion -ne "") {
        $args += "/p:OptionalVSIXVersion=$OptionalVSIXVersion"
    }

    Write-Host "  > MSBuild $($args -join ' ')" -ForegroundColor DarkGray
    & $msbuild @args
    if ($LASTEXITCODE -ne 0) {
        Write-Err "Build failed for $DeploymentType deployment."
        exit $LASTEXITCODE
    }
}

function Copy-VsixOutput {
    param(
        [string]$DeploymentType
    )

    # Search both the short build output and the default BuildOutput location
    $searchPaths = @($shortBuildOutput)
    $defaultBuildOutput = Join-Path $vsixDir "BuildOutput"
    if (Test-Path $defaultBuildOutput) { $searchPaths += $defaultBuildOutput }

    $vsixFiles = @()
    foreach ($searchPath in $searchPaths) {
        $found = Get-ChildItem -Path $searchPath -Recurse -Filter "WindowsAppSDK.*.$DeploymentType.vsix" -ErrorAction SilentlyContinue
        $vsixFiles += $found
    }

    if ($vsixFiles.Count -eq 0) {
        Write-Warn "No VSIX files found for $DeploymentType deployment."
        return
    }

    # Deduplicate by filename (same VSIX may appear in multiple locations)
    $seen = @{}
    foreach ($vsix in $vsixFiles) {
        if (-not $seen.ContainsKey($vsix.Name)) {
            $seen[$vsix.Name] = $vsix
            # Rename to include version: WindowsAppSDK.Cs.Extension.Dev17.Component.vsix
            #   -> WindowsAppSDK.Cs.Extension.Dev17.Component.99.2026.0416.1640.vsix
            $newName = $vsix.BaseName + ".$OptionalVSIXVersion.vsix"
            $dest = Join-Path $OutputDir $newName
            Copy-Item $vsix.FullName $dest -Force
            Write-Step "  -> $dest"
        }
    }
}

#endregion

#region --- Execute Build ---

$deployments = @()
if ($Deployment -eq "Both") {
    $deployments = @("Standalone", "Component")
} else {
    $deployments = @($Deployment)
}

foreach ($deploy in $deployments) {
    Write-Banner "Building VSIX — $deploy"

    if (-not $SkipRestore) {
        Invoke-MSBuildRestore -DeploymentType $deploy
    }
    Invoke-MSBuildBuild -DeploymentType $deploy

    Write-Step "Copying $deploy VSIX output..."
    Copy-VsixOutput -DeploymentType $deploy
}

#endregion

#region --- Cleanup ---

if ($NupkgSourceDir -ne "" -and $effectiveNugetConfig -ne $nugetConfig) {
    Remove-Item $effectiveNugetConfig -Force -ErrorAction SilentlyContinue
}

#endregion

#region --- Summary ---

Write-Banner "Build Complete"

$outputVsix = Get-ChildItem -Path $OutputDir -Filter "*.vsix" -ErrorAction SilentlyContinue
if ($outputVsix.Count -gt 0) {
    Write-Step "VSIX files produced:"
    foreach ($v in $outputVsix) {
        $sizeMB = [math]::Round($v.Length / 1MB, 2)
        Write-Host "  $($v.Name)  ($sizeMB MB)" -ForegroundColor White
    }
    Write-Host ""
    Write-Step "To install in Visual Studio, double-click the .vsix file or run:"
    Write-Host "  VSIXInstaller.exe <path-to-vsix>" -ForegroundColor White
} else {
    Write-Warn "No .vsix files found in $OutputDir."
    Write-Warn "Check the build output above for errors."
}

Write-Host ""

#endregion
