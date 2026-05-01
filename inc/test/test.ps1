# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Smoke-tests the AbiWinRT projection headers under inc/abi/ by
    invoking cl.exe to compile inc/test/reference_projection.cpp,
    which #includes every header.

.DESCRIPTION
    Locates the latest installed Visual Studio with C++ tools (via
    vswhere), invokes its VsDevCmd.bat to set up the environment for
    the requested architecture, and runs cl.exe to compile-only
    (no link) reference_projection.cpp.

    Exit code 0 indicates all headers compiled cleanly. Any non-zero
    exit code is a compilation failure; the cl.exe output above
    identifies the offending header(s).

.PARAMETER Architecture
    Target architecture passed to VsDevCmd.bat (-arch=). Defaults to
    x64. Valid values: x86, x64, arm, arm64.

.PARAMETER ExtraClArgs
    Optional extra arguments forwarded to cl.exe (e.g. additional
    /D defines, /I include paths).

.EXAMPLE
    pwsh ./inc/test/test.ps1

.EXAMPLE
    pwsh ./inc/test/test.ps1 -Architecture arm64
#>

[CmdletBinding()]
param(
    [ValidateSet('x86','x64','arm','arm64')]
    [string] $Architecture = 'x64',

    [string[]] $ExtraClArgs = @()
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

$here = Split-Path -Parent $MyInvocation.MyCommand.Path
$source = Join-Path $here 'reference_projection.cpp'
if (-not (Test-Path $source)) {
    throw "Source file not found: $source"
}

# ----------------------------------------------------------------------
# Provision a couple of small ecosystem nugets that several payload
# headers (decimal.h, WindowsAppRuntimeInsights.h, ...) take a hard
# dependency on. We install them once into a local cache next to this
# script and add their include dirs to cl.exe via /I.
# ----------------------------------------------------------------------
$pkgsDir = Join-Path $here '.packages'
New-Item -ItemType Directory -Force -Path $pkgsDir | Out-Null

function Get-NugetExe {
    $cmd = Get-Command nuget.exe -ErrorAction SilentlyContinue
    if ($cmd) { return $cmd.Source }
    throw "nuget.exe not found on PATH (needed to fetch wil/cppwinrt)."
}
$nugetExe = Get-NugetExe

function Install-Once {
    param([string] $Id)
    $existing = Get-ChildItem -Directory -LiteralPath $pkgsDir -Filter "$Id.*" -ErrorAction SilentlyContinue
    if ($existing) { return $existing[0].FullName }
    Write-Host "Installing $Id ..."
    & $nugetExe install $Id -OutputDirectory $pkgsDir -DependencyVersion Ignore -Verbosity quiet | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "nuget install $Id failed (exit $LASTEXITCODE)." }
    return (Get-ChildItem -Directory -LiteralPath $pkgsDir -Filter "$Id.*" | Select-Object -First 1).FullName
}

$wilRoot     = Install-Once 'Microsoft.Windows.ImplementationLibrary'
$cppwinrtRoot = Install-Once 'Microsoft.Windows.CppWinRT'
$wv2Root     = Install-Once 'Microsoft.Web.WebView2'
$abiToolRoot = Install-Once 'Microsoft.Windows.AbiWinRT'

# WinUI's Microsoft.UI.Xaml.Controls.h #includes "Microsoft.Web.WebView2.Core.h",
# which is the ABI projection of WebView2's winmd. The WebView2 nuget
# ships only the C/C++ headers (WebView2.h), not the ABI projection,
# so we generate it here using abi.exe.
$wv2Winmd = Get-ChildItem -Recurse -LiteralPath $wv2Root -Filter 'Microsoft.Web.WebView2.Core.winmd' |
    Where-Object { $_.FullName -notlike '*\tools\*' } | Select-Object -First 1
$abiExe   = Get-ChildItem -Recurse -LiteralPath $abiToolRoot -Filter 'abi.exe' | Select-Object -First 1
$wv2AbiInc = Join-Path $here '.packages\_wv2_abi'
if ($wv2Winmd -and $abiExe -and -not (Test-Path (Join-Path $wv2AbiInc 'Microsoft.Web.WebView2.Core.h'))) {
    New-Item -ItemType Directory -Force -Path $wv2AbiInc | Out-Null
    Write-Host "Generating WebView2 ABI projection ..."
    & $abiExe.FullName -input $wv2Winmd.FullName -reference sdk -output $wv2AbiInc -lowercase-include-guard -ns-prefix always | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "abi.exe (WebView2) failed (exit $LASTEXITCODE)." }
}

$includes = @(
    (Join-Path $wilRoot     'include')
    $wv2AbiInc
)

# All projection-header directories under inc/abi/ — cross-component
# headers reference each other via plain "Foo.h" (no relative path),
# so each component dir must be on the include path. We skip "winrt"
# subdirs (C++/WinRT projections that need cppwinrt's base.h).
$abiRoot = Resolve-Path (Join-Path $here '..' 'abi')
$includes += $abiRoot.Path
foreach ($d in Get-ChildItem -Directory -Recurse $abiRoot.Path) {
    if (($d.FullName.Substring($abiRoot.Path.Length+1) -split '[\\/]') -notcontains 'winrt') {
        $includes += $d.FullName
    }
}

# CppWinRT just provides the build targets; its base headers come from
# winmd projection at build time, so we don't add it here. We install
# the package only so future expansion (e.g., generating projections at
# test time) is one step away.

# ----------------------------------------------------------------------
# Locate Visual Studio + VsDevCmd.bat via vswhere.
# ----------------------------------------------------------------------
$vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
if (-not (Test-Path $vswhere)) {
    $vswhere = Join-Path $env:ProgramFiles 'Microsoft Visual Studio\Installer\vswhere.exe'
}
if (-not (Test-Path $vswhere)) {
    throw "vswhere.exe not found. Install Visual Studio (any edition) with the C++ workload."
}

$vsInstall = & $vswhere -latest `
    -products * `
    -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 `
    -property installationPath
if (-not $vsInstall) {
    throw "No Visual Studio installation with the C++ tools workload found."
}

$vsDevCmd = Join-Path $vsInstall 'Common7\Tools\VsDevCmd.bat'
if (-not (Test-Path $vsDevCmd)) {
    throw "VsDevCmd.bat not found at: $vsDevCmd"
}

Write-Host "Visual Studio:    $vsInstall"
Write-Host "Source:           $source"
Write-Host "Architecture:     $Architecture"
Write-Host ""

# ----------------------------------------------------------------------
# Run VsDevCmd.bat in a child cmd, then invoke cl.exe in the same
# session so the cl/include/lib environment is set.
# ----------------------------------------------------------------------
$tempObj = Join-Path $env:TEMP "wasdk_projection_test_$([System.Guid]::NewGuid().ToString('N'))"
New-Item -ItemType Directory -Force -Path $tempObj | Out-Null

try {
    $clBaseArgs = @(
        '/nologo'
        '/c'                       # compile only, no link
        '/TP'                      # treat as C++
        '/EHsc'
        '/std:c++17'
        '/W3'
        '/permissive-'
        '/Zc:wchar_t'
        '/Zc:__cplusplus'
        "/Fo$tempObj\"
    )
    foreach ($inc in $includes) {
        $clBaseArgs += "/I`"$inc`""
    }
    if ($ExtraClArgs) { $clBaseArgs += $ExtraClArgs }
    $clBaseArgs += "`"$source`""

    $clCmd = "cl.exe " + ($clBaseArgs -join ' ')
    $cmdLine = "`"$vsDevCmd`" -arch=$Architecture -no_logo && $clCmd"

    Write-Host "Invoking: $clCmd"
    Write-Host ""
    & cmd.exe /d /c $cmdLine
    $exit = $LASTEXITCODE
} finally {
    Remove-Item -Recurse -Force $tempObj -ErrorAction SilentlyContinue
}

Write-Host ""
if ($exit -eq 0) {
    Write-Host "PASS: all headers compiled cleanly." -ForegroundColor Green
} else {
    Write-Host "FAIL: cl.exe exited with code $exit" -ForegroundColor Red
}
exit $exit
