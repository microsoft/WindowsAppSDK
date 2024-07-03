param(
    [Parameter(Mandatory=$true)] [string] $installDir,
    [string]$Verbosity = 'quiet',
    [string]$logsDir
)

Import-Module -Name $PSScriptRoot\MSBuildFunctions.psm1 -DisableNameChecking

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

# Check if the VS cmd prompt is a valid one
$msbuildUpToDate = Test-MSBuild (Join-Path $env:VSINSTALLDIR "MSBuild\Current\Bin\msbuild.exe")
if (-not $msbuildUpToDate)
{
    $msbuildUpToDate = Test-MSBuild (Join-Path $installDir "MSBuild\Current\Bin\msbuild.exe")
}

$vs_buildtools = Join-Path $env:TEMP "vs_buildtools.exe"
$hasAtl = (Test-Path (Join-Path $env:VSINSTALLDIR "VC\Tools\MSVC\14.28.29304\atlmfc")) -or (Test-Path (Join-Path $installDir "VC\Tools\MSVC\14.28.29304\atlmfc"))
$needsDownload = -not $msbuildUpToDate -or -not $hasAtl

if ($needsDownload)
{
    Download-MSBuild -OutFile $vs_buildtools
}

if (-not $msbuildUpToDate)
{
    Install-MSBuild $installDir $vs_buildtools $logsDir
}
elseif (-not $hasAtl)
{
    Modify-MSBuild $installDir $vs_buildtools $logsDir
}

if ($needsDownload)
{
    Remove-Item $vs_buildtools
}
else
{
    Write-Host "VS build tools are already up-to-date. No installation required."
}