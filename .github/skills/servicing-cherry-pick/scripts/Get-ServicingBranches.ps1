# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Lists active release branches eligible for servicing cherry-picks.

.DESCRIPTION
    Discovers remote branches matching the release/X.Y-stable pattern and filters
    to those at or above the configured minimum version.

.PARAMETER MinVersion
    Minimum major.minor version to include. Defaults to config value (e.g., "1.7").

.PARAMETER Repository
    The GitHub repository in owner/repo format. Used for config defaults.

.PARAMETER ConfigPath
    Optional path to servicing-config.json.

.EXAMPLE
    $branches = ./Get-ServicingBranches.ps1
    # Returns: @("release/1.7-stable", "release/1.8-stable")

.EXAMPLE
    $branches = ./Get-ServicingBranches.ps1 -MinVersion "1.8"
    # Returns only branches >= 1.8

.NOTES
    Runs 'git fetch' to ensure remote branches are up-to-date before listing.
#>

[CmdletBinding()]
param(
    [Parameter()]
    [string]$MinVersion,

    [Parameter()]
    [string]$ConfigPath
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

. "$PSScriptRoot/ServicingLib.ps1"

# Load config for defaults
$config = Get-ServicingConfig -ConfigPath $ConfigPath

if (-not $MinVersion) {
    $MinVersion = $config.branches.minVersion
}

# Parse minimum version
if ($MinVersion -notmatch '^(\d+)\.(\d+)$') {
    Write-Error "MinVersion must be in 'major.minor' format (e.g., '1.7'). Got: $MinVersion"
    exit 1
}
$minMajor = [int]$Matches[1]
$minMinor = [int]$Matches[2]

Write-Verbose "Fetching remote branches..."
git fetch --prune 2>$null | Out-Null

# List remote branches matching release/X.Y-stable pattern
$remoteBranches = git branch -r --list 'origin/release/*-stable' 2>$null
if (-not $remoteBranches) {
    Write-Error "No release branches found matching 'origin/release/*-stable'."
    exit 1
}

$eligibleBranches = @()

foreach ($rawBranch in $remoteBranches) {
    $branch = $rawBranch.Trim()

    # Parse version from branch name (e.g., origin/release/1.7-stable -> 1.7)
    if ($branch -match 'origin/release/(\d+)\.(\d+)-stable$') {
        $branchMajor = [int]$Matches[1]
        $branchMinor = [int]$Matches[2]

        # Compare version: include if >= minVersion
        $branchVersion = $branchMajor * 1000 + $branchMinor
        $minVersionNum = $minMajor * 1000 + $minMinor

        if ($branchVersion -ge $minVersionNum) {
            # Return without the origin/ prefix
            $branchName = $branch -replace '^origin/', ''
            $eligibleBranches += [PSCustomObject]@{
                Branch = $branchName
                Major  = $branchMajor
                Minor  = $branchMinor
            }
        }
    }
}

if ($eligibleBranches.Count -eq 0) {
    Write-Error "No release branches found at or above version $MinVersion."
    exit 1
}

# Sort by version ascending
$eligibleBranches = $eligibleBranches | Sort-Object { $_.Major * 1000 + $_.Minor }

Write-Verbose "Found $($eligibleBranches.Count) eligible release branch(es):"
foreach ($b in $eligibleBranches) {
    Write-Verbose "  $($b.Branch) (v$($b.Major).$($b.Minor))"
}

return $eligibleBranches
