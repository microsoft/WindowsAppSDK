# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

# Extracts MSIX packages from any .nupkg found in the Source directory to the Dest directory.
# Looks specifically for certain named MSIX packages and renames them for consistently finding them as installer inputs.

param
(
    [String]$Source,
    [String]$Dest
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

Add-Type -AssemblyName System.IO.Compression.FileSystem

# Create Destination if not already existing.
if (!(Test-Path $Dest -PathType Container))
{
    New-Item -Path $Dest -ItemType Directory | Out-Null
}

# .NET methods resolve relative paths against the process directory, not the PowerShell location.
$Dest = (Get-Item -LiteralPath $Dest).FullName

# Process the archive and extract out and rename relevant files.
function Export-MSIXFromArchive ($Archive)
{
    foreach ($entry in $Archive.Entries)
    {
        $filename = $entry.FullName.Replace('/', '\')
        Write-Host $filename
        # For each item, see if we want to extract this item to a different filename.
        $DestFilename = $false

        # Basic MSIX filename pattern:
        #
        #      NamePrefix.Release[-VersionTag].msix
        #
        # where
        #  * NamePrefix = Microsoft.WindowsAppRuntime[.subname] (e.g. Microsoft.WindowsAppRuntime or Microsoft.WindowsAppRuntime.Main)
        #  * Release    = Major.Minor release (e.g. 1.0)
        #  * VersionTag = Channel# (e.g. Experimental1 or Preview2)
        #  * .msix      = MSIX packages are always named *.msix

        # Find the base Frameworks
        if ($filename -match '^.*(x86|x64|arm64)\\Microsoft\.WindowsAppRuntime[-.](\d+)(.\d+)?(-[A-Za-z.0-9]+)?(\.appx|\.msix)$')
        {
            $DestFilename = 'framework_' + $Matches[1] + '.msix'
        }

        # Find Main
        if ($filename -match '^.*(x86|x64|arm64)\\Microsoft\.WindowsAppRuntime\.Main([-.](\d+)(.\d+)?)?(-[A-Za-z.0-9]+)?(\.appx|\.msix)$')
        {
            $DestFilename = 'main_' + $Matches[1] + '.msix'
        }

        # Find Singleton
        if ($filename -match '^.*(x86|x64|arm64)\\Microsoft\.WindowsAppRuntime\.Singleton([-.](\d+)(.\d+)?)(-[A-Za-z.0-9]+)?(\.appx|\.msix)$')
        {
            $DestFilename = 'singleton_' + $Matches[1] + '.msix'
        }

        # Find DDLM
        if ($filename -match '^.*(x86|x64|arm64)\\Microsoft\.WindowsAppRuntime\.DDLM([-.](\d+)(.\d+)?)?(-[A-Za-z.0-9]+)?(\.appx|\.msix)$')
        {
            $DestFilename = 'ddlm_' + $Matches[1] + '.msix'
        }

        # If this item has a new destination name then do the extract and rename.
        if ($DestFilename)
        {
            $Destination = Join-Path $Dest -ChildPath $DestFilename
            [System.IO.Compression.ZipFileExtensions]::ExtractToFile($entry, $Destination, $true)
            Write-Host "Extracted file to:" $Destination
        }
    }
}

function Extract-MSIXFromNuget ($NugetPath)
{
    Write-Host "Extracting packages from $NugetPath"

    # Read the package in place instead of expanding all of it with Expand-Archive. When Expand-Archive failed partway
    # through, its cleanup failed too (PathNotFound on _rels\.rels), which hid the original error. Retry sharing and
    # lock violations, which another process can cause briefly. Any other failure stops the script with its own error.
    $maxAttempts = 3
    for ($attempt = 1; $attempt -le $maxAttempts; $attempt++)
    {
        try
        {
            $archive = [System.IO.Compression.ZipFile]::OpenRead($NugetPath)
            try
            {
                Export-MSIXFromArchive $archive
            }
            finally
            {
                $archive.Dispose()
            }
            return
        }
        catch
        {
            $exception = $_.Exception
            while ($null -ne $exception.InnerException)
            {
                $exception = $exception.InnerException
            }
            Write-Warning "Extracting from $NugetPath failed on attempt $attempt/${maxAttempts}: $($exception.ToString())"
            $isTransient = ($exception -is [System.IO.IOException]) -and (($exception.HResult -band 0xffff) -in @(32, 33))
            if (-not $isTransient -or ($attempt -eq $maxAttempts))
            {
                throw
            }
            Start-Sleep -Seconds $attempt
        }
    }
}

foreach($item in Get-ChildItem $Source -Recurse | Select FullName)
{
    if ($item.FullName -match '.*(\.nupkg)$')
    {
        Extract-MSIXFromNuget ($item.FullName)
    }
}
