<#
.SYNOPSIS
    End-to-end LocalDev (per-user, AllUsers="false") build + install for the
    Windows App SDK Templates VSIX.

.DESCRIPTION
    The fast dev loop. No admin. No setup.exe. No workload removal.

      1. Build the LocalDev flavor of the C# (and optionally C++) VSIX
      2. Install it per-user into every VS 17+ instance found by vswhere
      3. Refresh the template cache via 'devenv /UpdateConfiguration'

    See Install-LocalDev-VSIX.ps1 for the full theory of operation.

.PARAMETER Language
    CSharp | Cpp | Both (default).

.PARAMETER SkipBuild
    Reuse the most recently built LocalDev .vsix in publish\VSIX without
    rebuilding.

.PARAMETER VsVersionRange
    vswhere version range filter. Default '[17.0,)' (VS 2022 + VS 2026).
    Use '[17.0,18.0)' for VS 2022 only, '[18.0,19.0)' for VS 2026 only.

.PARAMETER UninstallFirst
    Run VSIXInstaller /uninstall before installing for a clean reinstall.

.EXAMPLE
    .\build-install-localdev-vsix.ps1
    # Build + install LocalDev C# + C++ to all VS 17+.

.EXAMPLE
    .\build-install-localdev-vsix.ps1 -Language CSharp -VsVersionRange '[18.0,19.0)'
    # Build only C# LocalDev and install to VS 2026 only.
#>

[CmdletBinding()]
param(
    [ValidateSet("CSharp", "Cpp", "Both")]
    [string]$Language = "Both",

    [switch]$SkipBuild,

    [string]$VsVersionRange = '[17.0,)',

    [switch]$UninstallFirst
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

function Write-Banner {
    param([string]$Message)
    $line = '=' * 70
    Write-Host ''
    Write-Host $line -ForegroundColor Cyan
    Write-Host "  $Message" -ForegroundColor Cyan
    Write-Host $line -ForegroundColor Cyan
    Write-Host ''
}
function Write-Step { param([string]$M) Write-Host "[*] $M" -ForegroundColor Green }
function Write-Err  { param([string]$M) Write-Host "[X] $M" -ForegroundColor Red }

$scriptDir = $PSScriptRoot
if (-not $scriptDir) { $scriptDir = (Get-Location).Path }

$buildScript   = Join-Path $scriptDir 'Build-VSIX.ps1'
$installScript = Join-Path $scriptDir 'Install-LocalDev-VSIX.ps1'
$publishDir    = Join-Path $scriptDir 'publish\VSIX'

Write-Banner 'LocalDev: Build + Install (per-user, no admin)'
Write-Step "Script directory : $scriptDir"
Write-Step "Language         : $Language"
Write-Step "VS range filter  : $VsVersionRange"
Write-Step "SkipBuild        : $($SkipBuild.IsPresent)"

# --- Build ---
if ($SkipBuild) {
    Write-Banner 'Build (SKIPPED via -SkipBuild)'
} else {
    Write-Banner 'Build LocalDev VSIX'
    if (-not (Test-Path $buildScript)) {
        Write-Err "Build-VSIX.ps1 not found at: $buildScript"
        exit 1
    }
    Push-Location $scriptDir
    try {
        & $buildScript -Deployment LocalDev
        if ($LASTEXITCODE -ne 0) {
            Write-Err "Build-VSIX.ps1 exited with code $LASTEXITCODE"
            exit $LASTEXITCODE
        }
    } finally {
        Pop-Location
    }
}

# --- Install ---
Write-Banner 'Install LocalDev VSIX'
if (-not (Test-Path $installScript)) {
    Write-Err "Install-LocalDev-VSIX.ps1 not found at: $installScript"
    exit 1
}

$installArgs = @{
    Language       = $Language
    VsVersionRange = $VsVersionRange
}
if ($UninstallFirst) { $installArgs['UninstallFirst'] = $true }

Push-Location $scriptDir
try {
    & $installScript @installArgs
    $exit = $LASTEXITCODE
} finally {
    Pop-Location
}

exit $exit
