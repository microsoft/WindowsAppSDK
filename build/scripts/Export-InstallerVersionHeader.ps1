# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
Stages the installer version header without expanding the runtime package.
.DESCRIPTION
Prefers the Runtime package, then Packages, then the legacy WindowsAppSDK package.
Retries sharing and lock violations up to three times. Other failures are fatal.
.PARAMETER SourceDirectory
Directory containing the Aggregate stage's NuGet packages.
.PARAMETER DestinationDirectory
Existing installer source directory that receives WindowsAppSDK-VersionInfo.h.
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [ValidateNotNullOrEmpty()]
    [string]$SourceDirectory,

    [Parameter(Mandatory = $true)]
    [ValidateNotNullOrEmpty()]
    [string]$DestinationDirectory
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

Add-Type -AssemblyName System.IO.Compression.FileSystem
$destination = (Get-Item -LiteralPath $DestinationDirectory).FullName
if (-not (Test-Path -LiteralPath $destination -PathType Container)) {
    throw "Installer destination is not a directory: $destination"
}

$packages = @(Get-ChildItem -LiteralPath $SourceDirectory -File -Filter '*.nupkg')
$package = $null
foreach ($packageId in @('Microsoft.WindowsAppSDK.Runtime', 'Microsoft.WindowsAppSDK.Packages', 'Microsoft.WindowsAppSDK')) {
    $pattern = '^' + [regex]::Escape($packageId) + '\.\d.*\.nupkg$'
    $candidates = @($packages | Where-Object { $_.Name -match $pattern })
    if ($candidates.Count -gt 1) {
        throw "Expected one $packageId package, found: $($candidates.Name -join ', ')"
    }
    if ($candidates.Count -eq 1) {
        $package = $candidates[0]
        break
    }
}
if ($null -eq $package) {
    throw "No WindowsAppSDK runtime package found in $SourceDirectory"
}

$headerName = 'WindowsAppSDK-VersionInfo.h'
$headerPath = Join-Path $destination $headerName
Write-Host "Staging $headerName from $($package.Name) ($($package.Length) bytes)"
for ($attempt = 1; $attempt -le 3; $attempt++) {
    $temporaryPath = Join-Path $destination ('.WindowsAppSDK-VersionInfo.' + [guid]::NewGuid().ToString('N') + '.tmp')
    try {
        $archive = [System.IO.Compression.ZipFile]::OpenRead($package.FullName)
        try {
            $entries = @($archive.Entries | Where-Object { $_.FullName -ceq "include/$headerName" })
            if ($entries.Count -ne 1 -or $entries[0].Length -eq 0) {
                throw "Package $($package.Name) must contain exactly one non-empty include/$headerName"
            }
            [System.IO.Compression.ZipFileExtensions]::ExtractToFile($entries[0], $temporaryPath)
        }
        finally {
            $archive.Dispose()
        }

        # Publish only a complete header, preserving any existing header if staging fails.
        if ([System.IO.File]::Exists($headerPath)) {
            # PS 5.1 converts $null to an empty string; File.Replace requires an actual null backup path.
            [System.IO.File]::Replace($temporaryPath, $headerPath, [System.Management.Automation.Language.NullString]::Value)
        }
        else {
            [System.IO.File]::Move($temporaryPath, $headerPath)
        }
        Write-Host "Staged $headerPath on attempt $attempt"
        exit 0
    }
    catch {
        $exception = $_.Exception
        while ($null -ne $exception.InnerException) {
            $exception = $exception.InnerException
        }
        Write-Warning "Header staging attempt $attempt/3 failed: $($exception.ToString())"
        $isTransient = $exception -is [System.IO.IOException] -and ($exception.HResult -band 0xffff) -in @(32, 33)
        if (-not $isTransient -or $attempt -eq 3) {
            throw
        }
        Start-Sleep -Seconds $attempt
    }
    finally {
        if ([System.IO.File]::Exists($temporaryPath)) {
            try {
                Remove-Item -LiteralPath $temporaryPath -Force
            }
            catch {
                Write-Warning "Could not remove temporary header '$temporaryPath': $_"
            }
        }
    }
}
