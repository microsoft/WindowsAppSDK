<#
.SYNOPSIS
    Installs locally-built Windows App SDK VSIX extension packages into Visual Studio.

.DESCRIPTION
    Handles the full installation flow:
      1. Uninstalls conflicting dotnet new templates (if installed)
      2. Verifies prerequisites (VS workloads)
      3. Installs the VSIX into Visual Studio using VSIXInstaller /force /quiet

.PARAMETER Language
    Which language template(s) to install.
    "CSharp"  - Install only C# VSIX
    "Cpp"     - Install only C++/WinRT VSIX
    "Both"    - Install both (default)

.PARAMETER VsixDir
    Directory containing the .vsix files. Default: .\publish\VSIX

.PARAMETER VsixPath
    Direct path to a specific .vsix file to install. Overrides -VsixDir and -Language.

.PARAMETER SkipDotnetUninstall
    Skip uninstalling the conflicting dotnet new template package.

.EXAMPLE
    .\Install-VSIX.ps1

.EXAMPLE
    .\Install-VSIX.ps1 -Language CSharp

.EXAMPLE
    .\Install-VSIX.ps1 -Language Cpp -VsixDir "D:\my-vsix"

.EXAMPLE
    .\Install-VSIX.ps1 -VsixPath "C:\path\to\WindowsAppSDK.Cs.Extension.Dev17.Component.99.2026.0416.1640.vsix"
#>

[CmdletBinding()]
param(
    [ValidateSet("CSharp", "Cpp", "Both")]
    [string]$Language = "Both",

    [string]$VsixDir = "",

    [string]$VsixPath = "",

    [switch]$SkipDotnetUninstall
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = "Stop"

#region --- Helpers ---

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

#endregion

#region --- Setup ---

Write-Banner "Windows App SDK VSIX Installer"

$scriptDir = $PSScriptRoot
if (-not $scriptDir) { $scriptDir = (Get-Location).Path }

#endregion

#region --- Find VSIX files ---

Write-Banner "Locating VSIX Files"

$toInstall = @()

if ($VsixPath -ne "") {
    # Direct path to a specific VSIX file
    if (-not (Test-Path $VsixPath)) {
        Write-Err "VSIX file not found: $VsixPath"
        exit 1
    }
    $vsixFile = Get-Item $VsixPath
    Write-Step "VSIX: $($vsixFile.Name)"
    $toInstall += $vsixFile
} else {
    # Search in VsixDir
    if ($VsixDir -eq "") {
        $VsixDir = Join-Path $scriptDir "publish\VSIX"
    }

    if (-not (Test-Path $VsixDir)) {
        Write-Err "VSIX directory not found: $VsixDir"
        Write-Err "Run Build-VSIX.ps1 first, or specify -VsixDir / -VsixPath."
        exit 1
    }

    $csVsix = Get-ChildItem $VsixDir -Filter "WindowsAppSDK.Cs.Extension.Dev17.*.vsix" -ErrorAction SilentlyContinue |
        Sort-Object LastWriteTime -Descending | Select-Object -First 1
    $cppVsix = Get-ChildItem $VsixDir -Filter "WindowsAppSDK.Cpp.Extension.Dev17.*.vsix" -ErrorAction SilentlyContinue |
        Sort-Object LastWriteTime -Descending | Select-Object -First 1

    if ($Language -eq "CSharp" -or $Language -eq "Both") {
        if ($csVsix) {
            Write-Step "C# VSIX:  $($csVsix.Name)"
            $toInstall += $csVsix
        } else {
            Write-Err "No C# VSIX found in $VsixDir (WindowsAppSDK.Cs.Extension.Dev17.*.vsix)"
            if ($Language -eq "CSharp") { exit 1 }
        }
    }

    if ($Language -eq "Cpp" -or $Language -eq "Both") {
        if ($cppVsix) {
            Write-Step "C++ VSIX: $($cppVsix.Name)"
            $toInstall += $cppVsix
        } else {
            Write-Err "No C++ VSIX found in $VsixDir (WindowsAppSDK.Cpp.Extension.Dev17.*.vsix)"
            if ($Language -eq "Cpp") { exit 1 }
        }
    }
}

if ($toInstall.Count -eq 0) {
    Write-Err "No VSIX files to install."
    exit 1
}

#endregion

#region --- Check VS is closed ---

Write-Banner "Checking Visual Studio Status"

$vsProcs = Get-Process -Name "devenv" -ErrorAction SilentlyContinue
if ($vsProcs) {
    Write-Err "Visual Studio is running. Please close all VS instances before installing."
    Write-Err "Running processes:"
    $vsProcs | ForEach-Object { Write-Err "  devenv.exe (PID: $($_.Id))" }
    exit 1
}
Write-Step "No Visual Studio instances running."

#endregion

#region --- Find VS Installation ---

Write-Banner "Checking Prerequisites"

$vswherePath = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
if (-not (Test-Path $vswherePath)) {
    Write-Err "vswhere.exe not found. Please install Visual Studio 2022 or later."
    exit 1
}

$vsPath = & $vswherePath -latest -property installationPath 2>$null
$vsVersion = & $vswherePath -latest -property installationVersion 2>$null
$vsDisplayName = & $vswherePath -latest -property displayName 2>$null

if (-not $vsPath) {
    Write-Err "No Visual Studio installation found."
    exit 1
}

Write-Step "$vsDisplayName (v$vsVersion)"
Write-Step "Path: $vsPath"

$vsixInstaller = Join-Path $vsPath "Common7\IDE\VSIXInstaller.exe"
if (-not (Test-Path $vsixInstaller)) {
    Write-Err "VSIXInstaller.exe not found at: $vsixInstaller"
    exit 1
}
Write-Step "VSIXInstaller: $vsixInstaller"

# Check required workloads
$vssdkSearch = Get-ChildItem -Path (Join-Path $vsPath "MSBuild") -Recurse -Filter "Microsoft.VsSDK.targets" -ErrorAction SilentlyContinue | Select-Object -First 1
if ($vssdkSearch) {
    Write-Step "VS SDK workload: installed"
} else {
    Write-Warn "VS SDK workload not detected. The extension may still work if installed via NuGet."
}

#endregion

#region --- Uninstall conflicting dotnet new templates ---

if (-not $SkipDotnetUninstall) {
    Write-Banner "Checking for Conflicting dotnet new Templates"

    $dotnetCmd = Get-Command dotnet -ErrorAction SilentlyContinue
    if ($dotnetCmd) {
        $uninstallList = & dotnet new uninstall 2>$null
        $hasConflict = $uninstallList | Select-String "Microsoft.WindowsAppSDK.WinUI.CSharp.Templates" -SimpleMatch

        if ($hasConflict) {
            Write-Warn "Found conflicting dotnet new template package:"
            Write-Warn "  Microsoft.WindowsAppSDK.WinUI.CSharp.Templates"
            Write-Warn "This package overrides VSIX templates in VS's New Project dialog."
            Write-Step "Uninstalling..."

            & dotnet new uninstall Microsoft.WindowsAppSDK.WinUI.CSharp.Templates 2>&1 | Out-Null

            # Verify
            $verify = & dotnet new uninstall 2>$null | Select-String "Microsoft.WindowsAppSDK.WinUI.CSharp.Templates" -SimpleMatch
            if ($verify) {
                Write-Warn "Template package may still be installed. You can manually run:"
                Write-Warn "  dotnet new uninstall Microsoft.WindowsAppSDK.WinUI.CSharp.Templates"
            } else {
                Write-Step "Successfully uninstalled conflicting template package."
            }
        } else {
            Write-Step "No conflicting dotnet new templates found."
        }
    } else {
        Write-Step "dotnet CLI not available, skipping template check."
    }
}

#endregion

#region --- Install VSIX ---

Write-Banner "Installing VSIX Extensions"

$failed = @()
foreach ($vsix in $toInstall) {
    Write-Step "Installing $($vsix.Name)..."
    Write-Host "  > VSIXInstaller /force /quiet `"$($vsix.FullName)`"" -ForegroundColor DarkGray

    & $vsixInstaller /force /quiet $vsix.FullName 2>&1 | Out-Null
    $exitCode = $LASTEXITCODE

    # Wait for VSIXInstaller processes to finish
    $waitCount = 0
    while (Get-Process -Name "VSIXInstaller" -ErrorAction SilentlyContinue) {
        Start-Sleep -Seconds 5
        $waitCount++
        if ($waitCount % 6 -eq 0) {
            Write-Host "  Still installing... ($($waitCount * 5)s elapsed)" -ForegroundColor DarkGray
        }
    }

    # Check latest log for errors
    $latestLog = Get-ChildItem "$env:TEMP\dd_VSIXInstaller_*.log" -ErrorAction SilentlyContinue |
        Sort-Object LastWriteTime -Descending | Select-Object -First 1
    $hasError = $false
    if ($latestLog) {
        $logTail = Get-Content $latestLog.FullName -Tail 20 -ErrorAction SilentlyContinue
        $errorLines = $logTail | Select-String "Install Error|InvalidOperationException.*Uninstall.*failed" -SimpleMatch:$false
        if ($errorLines) {
            $hasError = $true
            $failed += $vsix.Name
            Write-Err "Installation failed for $($vsix.Name)"
            Write-Err "Log: $($latestLog.FullName)"
            foreach ($e in $errorLines) { Write-Err "  $($e.Line.Trim())" }
        }
    }

    if (-not $hasError) {
        Write-Step "Successfully installed $($vsix.Name)"
    }
}

#endregion

#region --- Summary ---

Write-Banner "Installation Summary"

if ($failed.Count -eq 0) {
    Write-Step "All extensions installed successfully!"
    Write-Host ""
    Write-Step "Next steps:"
    Write-Host "  1. Open Visual Studio" -ForegroundColor White
    Write-Host "  2. File -> New -> Project" -ForegroundColor White
    Write-Host "  3. Search for 'WinUI' to find the templates" -ForegroundColor White
    Write-Host ""
    Write-Step "To verify: Extensions -> Manage Extensions -> look for"
    Write-Host "  'Windows App SDK C# VS Templates'" -ForegroundColor White
    Write-Host "  'Windows App SDK C++ VS Templates'" -ForegroundColor White
} else {
    Write-Err "Some installations failed:"
    foreach ($f in $failed) { Write-Err "  - $f" }
    Write-Host ""
    Write-Warn "Tips:"
    Write-Warn "  - Make sure all VS instances are closed"
    Write-Warn "  - Use Component VSIX if VS has WinUI workload installed"
    Write-Warn "  - Check logs in: $env:TEMP\dd_VSIXInstaller_*.log"
}

Write-Host ""

#endregion
