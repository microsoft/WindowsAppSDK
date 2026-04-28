<#
.SYNOPSIS
    Installs the locally-built LocalDev (per-user, AllUsers="false") Windows
    App SDK Templates VSIX into Visual Studio 2022 and/or 2026.

.DESCRIPTION
    THE FAST DEV LOOP. No admin required. No setup.exe. No workload removal.

    The LocalDev VSIX is identical in content to the Standalone VSIX except
    its manifest sets <Installation AllUsers="false">. That makes it a
    per-user install under
        %LOCALAPPDATA%\Microsoft\VisualStudio\<edhive>\Extensions\<guid>\
    instead of the per-machine
        C:\Program Files\Microsoft Visual Studio\<ed>\Common7\IDE\Extensions\
    location used by Standalone/Component.

    Why this works on a machine that already has the WinUI workload
    ===============================================================
    The workload ships the same extension Id (Microsoft.WindowsAppSDK.Cs.Dev17)
    per-machine. VS scans BOTH the per-machine and per-user extension hives
    at startup. When two installed extensions share the same Id, the higher
    Version wins. The locally-built VSIX uses version 99.<yyyy>.<MMdd>.<HHmm>
    and the workload-shipped one is 1.x.x.x, so the LocalDev build always
    wins for the current user. The workload copy stays untouched on disk
    (no admin needed to install OR uninstall LocalDev).

    Steps performed
    ---------------
      1. Discover all VS 17+ instances (vswhere)
      2. Refuse to run if any devenv.exe is open (templates are cached at
         startup; replacing the VSIX while VS is running has no effect)
      3. For each (VSIX, instance) pair: VSIXInstaller /quiet /instanceIds:<id>
         <vsix>     (no /admin, no elevation)
      4. Optionally invoke devenv /UpdateConfiguration to refresh the
         template cache so the new templates appear on the very next launch
         (VS would otherwise refresh on first launch anyway)

    What this script DELIBERATELY does NOT do
    -----------------------------------------
      * No setup.exe modify (we never touch VS Setup state)
      * No removal of workload components
      * No deletion of files under Program Files
      * No admin elevation required

.PARAMETER Language
    Which language template(s) to install. CSharp | Cpp | Both (default).

.PARAMETER VsixDir
    Directory containing LocalDev .vsix files. Default: .\publish\VSIX

.PARAMETER VsixPath
    Direct path to a single LocalDev .vsix. Overrides -VsixDir and -Language.

.PARAMETER VsVersionRange
    vswhere version range filter. Default '[17.0,)' = VS 2022 and VS 2026.
    Use '[17.0,18.0)' for VS 2022 only or '[18.0,19.0)' for VS 2026 only.

.PARAMETER UninstallFirst
    If set, run VSIXInstaller /uninstall:<extId> before installing. Useful
    when you've already installed a LocalDev build and want a clean reinstall.
    NOT required for normal use - VSIXInstaller will replace an existing
    per-user copy in place.

.PARAMETER SkipUpdateConfiguration
    Skip the post-install 'devenv /UpdateConfiguration' step. The new
    templates will still appear, but only on the next VS launch.

.EXAMPLE
    .\Install-LocalDev-VSIX.ps1
    # Install the latest LocalDev C# + C++ VSIX into every VS 17+ instance.

.EXAMPLE
    .\Install-LocalDev-VSIX.ps1 -Language CSharp -VsVersionRange '[18.0,19.0)'
    # Install only the C# VSIX into VS 2026.

.EXAMPLE
    .\Install-LocalDev-VSIX.ps1 -UninstallFirst
    # Force a clean reinstall (uninstall then install).
#>

[CmdletBinding()]
param(
    [ValidateSet("CSharp", "Cpp", "Both")]
    [string]$Language = "Both",

    [string]$VsixDir = "",

    [string]$VsixPath = "",

    [string]$VsVersionRange = '[17.0,)',

    [switch]$UninstallFirst,

    [switch]$SkipUpdateConfiguration
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

#region --- Helpers ---

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
function Write-Warn { param([string]$M) Write-Host "[!] $M" -ForegroundColor Yellow }
function Write-Err  { param([string]$M) Write-Host "[X] $M" -ForegroundColor Red }

function Get-VsixExtId {
    param([string]$Name)
    # LocalDev VSIX uses Ids with a ".LocalDev" suffix so they don't collide
    # with the workload-shipped per-machine copy (see manifest comments).
    if ($Name -match '\.Cs\.')  { return 'Microsoft.WindowsAppSDK.Cs.Dev17.LocalDev' }
    if ($Name -match '\.Cpp\.') { return 'Microsoft.WindowsAppSDK.Cpp.Dev17.LocalDev' }
    return $null
}

function Wait-VsixInstaller {
    $waited = 0
    while (Get-Process -Name 'VSIXInstaller' -ErrorAction SilentlyContinue) {
        Start-Sleep -Seconds 2
        $waited += 2
        if ($waited % 30 -eq 0) {
            Write-Host "    Still installing... (${waited}s elapsed)" -ForegroundColor DarkGray
        }
    }
}

function Get-LatestVsixInstallerLog {
    Get-ChildItem "$env:TEMP\dd_VSIXInstaller_*.log" -ErrorAction SilentlyContinue |
        Sort-Object LastWriteTime -Descending | Select-Object -First 1
}

#endregion

#region --- Setup ---

Write-Banner 'Windows App SDK LocalDev VSIX Installer (per-user, no admin)'

$scriptDir = $PSScriptRoot
if (-not $scriptDir) { $scriptDir = (Get-Location).Path }

#endregion

#region --- Locate VSIX files ---

Write-Banner 'Locating LocalDev VSIX Files'

$toInstall = @()

if ($VsixPath -ne "") {
    if (-not (Test-Path $VsixPath)) {
        Write-Err "VSIX file not found: $VsixPath"
        exit 1
    }
    $toInstall += Get-Item $VsixPath
} else {
    if ($VsixDir -eq "") {
        $VsixDir = Join-Path $scriptDir 'publish\VSIX'
    }
    if (-not (Test-Path $VsixDir)) {
        Write-Err "VSIX directory not found: $VsixDir"
        Write-Err "Run '.\Build-VSIX.ps1 -Deployment LocalDev' first."
        exit 1
    }

    $csVsix  = Get-ChildItem $VsixDir -Filter 'WindowsAppSDK.Cs.Extension.Dev17.LocalDev.*.vsix'  -ErrorAction SilentlyContinue | Sort-Object LastWriteTime -Descending | Select-Object -First 1
    $cppVsix = Get-ChildItem $VsixDir -Filter 'WindowsAppSDK.Cpp.Extension.Dev17.LocalDev.*.vsix' -ErrorAction SilentlyContinue | Sort-Object LastWriteTime -Descending | Select-Object -First 1

    if ($Language -in @('CSharp','Both') -and $csVsix)  { $toInstall += $csVsix }
    if ($Language -in @('Cpp',   'Both') -and $cppVsix) { $toInstall += $cppVsix }
}

if (-not $toInstall) {
    Write-Err "No matching LocalDev VSIX files found."
    Write-Err "Expected names: WindowsAppSDK.{Cs,Cpp}.Extension.Dev17.LocalDev.<version>.vsix"
    Write-Err "Run: .\Build-VSIX.ps1 -Deployment LocalDev"
    exit 1
}

foreach ($v in $toInstall) {
    Write-Step "VSIX: $($v.Name)"
}

#endregion

#region --- Refuse to run while VS is open ---

Write-Banner 'Checking Visual Studio Status'

$vsProcs = Get-Process -Name 'devenv' -ErrorAction SilentlyContinue
if ($vsProcs) {
    Write-Err 'Visual Studio is running. Per-user VSIX installs apply at VS startup;'
    Write-Err 'replacing the VSIX while VS is running has no effect on this VS session.'
    Write-Err 'Close all devenv.exe processes and re-run this script.'
    foreach ($p in $vsProcs) { Write-Err "  devenv.exe (PID: $($p.Id))" }
    exit 1
}
Write-Step 'No Visual Studio instances running.'

#endregion

#region --- Discover VS instances ---

Write-Banner "Discovering Visual Studio Installations (range $VsVersionRange)"

$vswherePath = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
if (-not (Test-Path $vswherePath)) {
    Write-Err 'vswhere.exe not found. Install Visual Studio 2022 or later.'
    exit 1
}

$vsInstancesJson = & $vswherePath -products '*' -prerelease -version $VsVersionRange -format json 2>$null
if (-not $vsInstancesJson) {
    Write-Err "No Visual Studio installation found matching version range '$VsVersionRange'."
    exit 1
}
$vsInstancesAll = $vsInstancesJson | ConvertFrom-Json

$vsInstances = @()
foreach ($inst in $vsInstancesAll) {
    $vsixExe = Join-Path $inst.installationPath 'Common7\IDE\VSIXInstaller.exe'
    if (-not (Test-Path $vsixExe)) {
        Write-Warn "Skipping $($inst.displayName) - VSIXInstaller.exe not found."
        continue
    }
    $vsInstances += [PSCustomObject]@{
        InstanceId    = $inst.instanceId
        DisplayName   = $inst.displayName
        Version       = $inst.installationVersion
        Path          = $inst.installationPath
        VsixInstaller = $vsixExe
        Devenv        = Join-Path $inst.installationPath 'Common7\IDE\devenv.exe'
    }
    Write-Step "$($inst.displayName) (v$($inst.installationVersion))  [$($inst.instanceId)]"
}
if (-not $vsInstances) { Write-Err 'No usable VS installations found.'; exit 1 }

#endregion

#region --- Optional uninstall (per-user only) ---

if ($UninstallFirst) {
    Write-Banner 'Uninstalling Existing Per-User Copy'
    foreach ($vsix in $toInstall) {
        $extId = Get-VsixExtId -Name $vsix.Name
        if (-not $extId) { continue }
        foreach ($inst in $vsInstances) {
            Write-Step "[$($inst.DisplayName)] VSIXInstaller /uninstall:$extId ..."
            # No /admin flag here - we are intentionally only touching the
            # per-user (current user) install. VSIXInstaller will refuse to
            # silently uninstall a per-machine extension without /admin, so
            # any per-machine workload-shipped copy is left alone (which is
            # exactly what we want).
            & $inst.VsixInstaller "/uninstall:$extId" '/quiet' "/instanceIds:$($inst.InstanceId)" 2>&1 | Out-Null
            Wait-VsixInstaller
            $log = Get-LatestVsixInstallerLog
            if ($log) {
                $tail = Get-Content $log.FullName -Tail 20 -ErrorAction SilentlyContinue
                if ($tail | Select-String 'Uninstall.*completed|successfully uninstalled') {
                    Write-Step "[$($inst.DisplayName)] Per-user copy uninstalled (or none was present)."
                } else {
                    Write-Warn "[$($inst.DisplayName)] Uninstall returned no clear success line."
                    Write-Warn "  Log: $($log.FullName)"
                }
            }
        }
    }
}

#endregion

#region --- Install (per-user, no admin) ---

Write-Banner 'Installing LocalDev VSIX (per-user)'

$failed = @()
$succeeded = @()

foreach ($vsix in $toInstall) {
    foreach ($inst in $vsInstances) {
        Write-Step "[$($inst.DisplayName)] Installing $($vsix.Name)..."
        $args = @('/quiet', "/instanceIds:$($inst.InstanceId)", $vsix.FullName)
        Write-Host "  > VSIXInstaller $($args -join ' ')" -ForegroundColor DarkGray
        & $inst.VsixInstaller @args 2>&1 | Out-Null
        Wait-VsixInstaller

        $log = Get-LatestVsixInstallerLog
        $hasError = $false
        if ($log) {
            $tail = Get-Content $log.FullName -Tail 80 -ErrorAction SilentlyContinue
            $errLines = $tail | Select-String 'Install Error|InvalidOperationException.*(Uninstall|Installation).*failed'
            if ($errLines) {
                $hasError = $true
                $failed += "$($vsix.Name) -> $($inst.DisplayName)"
                Write-Err "[$($inst.DisplayName)] VSIXInstaller failed."
                Write-Err "  Log: $($log.FullName)"
                foreach ($e in $errLines) { Write-Err "    $($e.Line.Trim())" }
            }
        }
        if (-not $hasError) {
            Write-Step "[$($inst.DisplayName)] Installed (per-user)."
            $succeeded += [PSCustomObject]@{ Vsix = $vsix.Name; Instance = $inst }
        }
    }
}

#endregion

#region --- Refresh template cache ---

if (-not $SkipUpdateConfiguration -and $succeeded) {
    Write-Banner 'Refreshing Template Cache (devenv /UpdateConfiguration)'
    # /UpdateConfiguration forces VS to re-scan extensions and rebuild caches
    # (incl. ProjectTemplatesCache, ItemTemplatesCache, ComponentModelCache).
    # This makes the new templates show up immediately on next File -> New
    # without waiting for the next interactive launch to discover them.
    $instancesTouched = $succeeded | ForEach-Object { $_.Instance } | Sort-Object InstanceId -Unique
    foreach ($inst in $instancesTouched) {
        Write-Step "[$($inst.DisplayName)] devenv /UpdateConfiguration ..."
        & $inst.Devenv '/UpdateConfiguration' 2>&1 | Out-Null
        Write-Step "[$($inst.DisplayName)] Cache refreshed."
    }
}

#endregion

#region --- Summary ---

Write-Banner 'Installation Summary'

if (-not $failed) {
    Write-Step 'All LocalDev VSIX(es) installed successfully.'
    Write-Host ''
    Write-Step 'Verify in Visual Studio:'
    Write-Host '  1. Launch Visual Studio (any installed VS 17+ instance).'    -ForegroundColor White
    Write-Host '  2. File -> New -> Project.'                                  -ForegroundColor White
    Write-Host '  3. Filter Language=C#, Search "WinUI".'                      -ForegroundColor White
    Write-Host '  4. You should see the 7 project templates with SortOrder'    -ForegroundColor White
    Write-Host '     10 -> 70:'                                                 -ForegroundColor White
    Write-Host '       1) Blank App                  (10)'                      -ForegroundColor White
    Write-Host '       2) NavigationView App         (20)'                      -ForegroundColor White
    Write-Host '       3) TabView App                (30)'                      -ForegroundColor White
    Write-Host '       4) MVVM App                   (40)'                      -ForegroundColor White
    Write-Host '       5) Blank App (Packaged WAP)   (50)'                      -ForegroundColor White
    Write-Host '       6) Class Library              (60)'                      -ForegroundColor White
    Write-Host '       7) Unit Test App              (70)'                      -ForegroundColor White
    Write-Host ''
    Write-Step 'To uninstall later (no admin needed):'
    Write-Host '  .\Install-LocalDev-VSIX.ps1 -UninstallFirst'                  -ForegroundColor White
    Write-Host '  # then Ctrl+C to skip the reinstall, or just let it reinstall' -ForegroundColor DarkGray
    Write-Host '  # alternatively:'                                             -ForegroundColor DarkGray
    Write-Host '  & "<VSPath>\Common7\IDE\VSIXInstaller.exe" /uninstall:Microsoft.WindowsAppSDK.Cs.Dev17.LocalDev /quiet' -ForegroundColor White
    exit 0
} else {
    Write-Err 'Failed installs:'
    foreach ($f in $failed) { Write-Err "  - $f" }
    exit 1
}

#endregion
