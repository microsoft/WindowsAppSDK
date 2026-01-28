param
(
    [String]$SourceFolder,
    [String]$DestinationFolder
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

$overrideHeaderName = "windowsappruntime_definitions_override.h"

# Mapping of filenames to identifiers
$packageMapping = @(
    [pscustomobject]@{
        Package='framework_x86.msix';
        Identifier='MSIX_FRAMEWORK_X86_PATH'
    }
    [pscustomobject]@{
        Package='framework_x64.msix';
        Identifier='MSIX_FRAMEWORK_X64_PATH'
    }
    [pscustomobject]@{
        Package='framework_arm64.msix';
        Identifier='MSIX_FRAMEWORK_ARM64_PATH'
    }
    [pscustomobject]@{
        Package='main_x86.msix';
        Identifier='MSIX_MAIN_X86_PATH'
    }
    [pscustomobject]@{
        Package='main_x64.msix';
        Identifier='MSIX_MAIN_X64_PATH'
    }
    [pscustomobject]@{
        Package='main_arm64.msix';
        Identifier='MSIX_MAIN_ARM64_PATH'
    }
    [pscustomobject]@{
        Package='main_license.xml';
        Identifier='MSIX_MAIN_LICENSE_PATH'
    }
    [pscustomobject]@{
        Package='singleton_x86.msix';
        Identifier='MSIX_SINGLETON_X86_PATH'
    }
    [pscustomobject]@{
        Package='singleton_x64.msix';
        Identifier='MSIX_SINGLETON_X64_PATH'
    }
    [pscustomobject]@{
        Package='singleton_arm64.msix';
        Identifier='MSIX_SINGLETON_ARM64_PATH'
    }
    [pscustomobject]@{
        Package='singleton_license.xml';
        Identifier='MSIX_SINGLETON_LICENSE_PATH'
    }
    [pscustomobject]@{
        Package='ddlm_x86.msix';
        Identifier='MSIX_DDLM_X86_PATH'
    }
    [pscustomobject]@{
        Package='ddlm_x64.msix';
        Identifier='MSIX_DDLM_X64_PATH'
    }
    [pscustomobject]@{
        Package='ddlm_arm64.msix';
        Identifier='MSIX_DDLM_ARM64_PATH'
    }
    [pscustomobject]@{
        Package='ml_framework_x64.msix';
        Identifier='MSIX_MLFRAMEWORK_X64_PATH'
    }
    [pscustomobject]@{
        Package='ml_framework_arm64.msix';
        Identifier='MSIX_MLFRAMEWORK_ARM64_PATH'
    }
)


function Remove-ItemIfExists ($Item)
{
    if (Test-Path $Item)
    {
        Write-Host("Removing " + $Item)
        Remove-Item $Item -Recurse -Force
    }
}

function Add-Text ($Text)
{
    Add-Content $Destination $Text
}

function Add-RedefineIfExists
{
    param(
        [pscustomobject]$Object
    )
    process {
        $Package = $Object.Package
        $Identifier = $Object.Identifier
        $Path = Join-Path $SourceFolder -ChildPath $Package
        if ((Test-Path $Path -PathType Leaf) -and $Identifier)
        {
            $FullPath = $Path | Resolve-Path
            $FullPath = $FullPath -replace '\\', '\\'
            Add-Text "#undef $Identifier"
            Add-Text "#define $Identifier `"$FullPath`"`n"
            Write-Host "Added override for $Identifier"
        }
    }
}

$Destination = Join-Path $DestinationFolder -ChildPath $overrideHeaderName
Write-Host("Destination File: " + $Destination)
Remove-ItemIfExists ($Destination)
New-Item $Destination | Out-Null

Add-Text "#pragma once`n"

# Iterate over known identifiers and add entries for all that exist in the source
foreach($entry in $packageMapping)
{
    Add-RedefineIfExists $entry
}

$header = Get-Content $Destination
Write-Host "$Destination content"
$header
