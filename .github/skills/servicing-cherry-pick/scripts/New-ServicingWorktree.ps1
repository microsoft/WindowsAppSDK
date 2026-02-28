# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Creates a git worktree for a servicing cherry-pick on a release branch.

.DESCRIPTION
    Creates a new branch based on the target release branch and sets up a worktree
    in the 'Generated Files/servicing/<PR>/' directory for making cherry-pick changes.

.PARAMETER Branch
    The target release branch (e.g., "release/1.7-stable").

.PARAMETER BranchName
    The name for the new cherry-pick branch (e.g., "user/author/cherry-pick-fix-name-1.7").

.PARAMETER PullRequestNumber
    The original PR number being cherry-picked (used for directory naming).

.PARAMETER RepoRoot
    The repository root path. Auto-detected if not provided.

.EXAMPLE
    $wt = ./New-ServicingWorktree.ps1 -Branch "release/1.7-stable" `
        -BranchName "user/myname/cherry-pick-fix-thing-1.7" -PullRequestNumber 5865

.OUTPUTS
    PSCustomObject with WorktreePath and BranchName properties.

.NOTES
    The worktree is created under 'Generated Files/servicing/<PR>/worktree-<version>/'.
    Requires git to be installed.
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory)]
    [string]$Branch,

    [Parameter(Mandatory)]
    [string]$BranchName,

    [Parameter(Mandatory)]
    [int]$PullRequestNumber,

    [Parameter()]
    [string]$RepoRoot
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

. "$PSScriptRoot/ServicingLib.ps1"

if (-not $RepoRoot) {
    $RepoRoot = Get-RepoRoot
}

# Extract version for directory naming (e.g., "1.7" from "release/1.7-stable")
$versionSuffix = 'unknown'
if ($Branch -match 'release/(\d+\.\d+)-stable') {
    $versionSuffix = $Matches[1]
}

$worktreeDir = Join-Path $RepoRoot "Generated Files/servicing/$PullRequestNumber/worktree-$versionSuffix"

# Clean up existing worktree at this path if present
if (Test-Path $worktreeDir) {
    Write-Verbose "Removing existing worktree at $worktreeDir..."
    git worktree remove --force $worktreeDir 2>$null | Out-Null
    if (Test-Path $worktreeDir) {
        Remove-Item -Recurse -Force $worktreeDir
    }
}

# Ensure the remote branch is fetched
Write-Verbose "Fetching origin/$Branch..."
git fetch origin $Branch 2>$null | Out-Null
if ($LASTEXITCODE -ne 0) {
    Write-Error "Failed to fetch origin/$Branch."
    exit 1
}

# Delete local branch if it already exists (from a previous failed run)
$existingBranch = git rev-parse --verify "refs/heads/$BranchName" 2>$null
if ($LASTEXITCODE -eq 0) {
    Write-Verbose "Cleaning up existing local branch $BranchName..."
    git branch -D $BranchName 2>$null | Out-Null
}

# Create worktree with a new branch based on the remote release branch
Write-Verbose "Creating worktree at $worktreeDir on branch $BranchName from origin/$Branch..."
$worktreeOutput = git worktree add -b $BranchName $worktreeDir "origin/$Branch" 2>&1
if ($LASTEXITCODE -ne 0) {
    Write-Error "Failed to create worktree: $worktreeOutput"
    exit 1
}

Ok "Worktree created at: $worktreeDir"
Write-Verbose "  Branch: $BranchName (based on origin/$Branch)"

return [PSCustomObject]@{
    WorktreePath = $worktreeDir
    BranchName   = $BranchName
    BaseBranch   = $Branch
}
