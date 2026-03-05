# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Downloads a file from a URL to a local directory, skipping if already present.

.DESCRIPTION
    Shared download utility used by the Windows App SDK build scripts. Downloads a file
    from the specified URL to the output directory, creating the directory if needed.
    If the file already exists at the output path, the download is skipped.

.PARAMETER Url
    The URL to download the file from.

.PARAMETER OutputDirectory
    The directory to save the downloaded file to. Created if it does not exist.

.PARAMETER FileName
    The name of the output file within the output directory.

.EXAMPLE
    .\Download-Package.ps1 -Url "https://aka.ms/Microsoft.VCLibs.x64.14.00.Desktop.appx" -OutputDirectory ".\redist" -FileName "Microsoft.VCLibs.x64.14.00.Desktop.appx"
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [ValidateNotNullOrEmpty()]
    [string]$Url,

    [Parameter(Mandatory = $true)]
    [ValidateNotNullOrEmpty()]
    [string]$OutputDirectory,

    [Parameter(Mandatory = $true)]
    [ValidateNotNullOrEmpty()]
    [string]$FileName
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'
$ProgressPreference = 'SilentlyContinue'

try
{
    if (-not (Test-Path $OutputDirectory))
    {
        $null = New-Item -ItemType Directory -Path $OutputDirectory
    }

    $outputPath = Join-Path $OutputDirectory $FileName

    if (-not (Test-Path $outputPath))
    {
        Write-Verbose "Downloading $Url to $outputPath"
        Write-Host "Downloading $Url to $outputPath"
        Invoke-WebRequest $Url -OutFile $outputPath -UseBasicParsing
    }
    else
    {
        Write-Host "The file '$outputPath' already exists. Skipping download."
    }

    exit 0
}
catch
{
    Write-Error "Download failed: $_"
    exit 1
}
