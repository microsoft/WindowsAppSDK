# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Determines the next patch version for a release branch by parsing the IDL.

.DESCRIPTION
    Reads RuntimeCompatibilityOptions.idl from the target release branch (via git show)
    and parses version comments (e.g., "// 1.7.3") to find the highest patch number.
    Returns the next patch version and the corresponding WinAppSDK symbol name.

.PARAMETER Branch
    The release branch to check (e.g., "release/1.7-stable").

.PARAMETER Major
    The major version number of the release branch.

.PARAMETER Minor
    The minor version number of the release branch.

.PARAMETER ConfigPath
    Optional path to servicing-config.json.

.EXAMPLE
    $version = ./Get-NextPatchVersion.ps1 -Branch "release/1.7-stable" -Major 1 -Minor 7
    # Returns: @{ Patch = 9; Symbol = "WinAppSDK_1_7_9"; VersionComment = "// 1.7.9" }

.NOTES
    Uses 'git show' to read the IDL from the remote branch without checking it out.
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory)]
    [string]$Branch,

    [Parameter(Mandatory)]
    [int]$Major,

    [Parameter(Mandatory)]
    [int]$Minor,

    [Parameter()]
    [string]$ConfigPath
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

. "$PSScriptRoot/ServicingLib.ps1"

$config = Get-ServicingConfig -ConfigPath $ConfigPath
$idlPath = $config.idl.relativePath

Write-Verbose "Reading IDL from origin/$Branch`:$idlPath..."

# Read IDL content from the remote branch
$idlContent = git show "origin/${Branch}:${idlPath}" 2>&1
if ($LASTEXITCODE -ne 0) {
    # The IDL might not exist on older branches - start from patch 1
    Warn "Could not read IDL from origin/${Branch}:${idlPath}. Assuming first patch version."
    $nextPatch = 1
}
else {
    # Parse version comments to find highest patch
    # Pattern: lines like "// 1.7.1", "// 1.7.2", etc.
    $highestPatch = 0
    $versionPattern = "//\s*$Major\.$Minor\.(\d+)"

    foreach ($line in ($idlContent -split "`n")) {
        if ($line -match $versionPattern) {
            $patchNum = [int]$Matches[1]
            if ($patchNum -gt $highestPatch) {
                $highestPatch = $patchNum
            }
        }
    }

    # Also check enum entries for version references in comments
    # Pattern: entries like "SomeFix = 12345, // 1.7.3"
    $entryPattern = "=\s*\d+.*//\s*$Major\.$Minor\.(\d+)"
    foreach ($line in ($idlContent -split "`n")) {
        if ($line -match $entryPattern) {
            $patchNum = [int]$Matches[1]
            if ($patchNum -gt $highestPatch) {
                $highestPatch = $patchNum
            }
        }
    }

    $nextPatch = $highestPatch + 1

    # If no version comments found at all, start from 1
    if ($highestPatch -eq 0) {
        Write-Verbose "No existing version comments found for $Major.$Minor. Starting at patch 1."
        $nextPatch = 1
    }
}

$symbol = Format-PatchVersionSymbol -Major $Major -Minor $Minor -Patch $nextPatch
$versionComment = "// $Major.$Minor.$nextPatch"

$result = [PSCustomObject]@{
    Major          = $Major
    Minor          = $Minor
    Patch          = $nextPatch
    Symbol         = $symbol
    VersionComment = $versionComment
    VersionString  = "$Major.$Minor.$nextPatch"
}

Write-Verbose "Next patch version for $Branch`: $($result.VersionString) (symbol: $($result.Symbol))"

return $result
