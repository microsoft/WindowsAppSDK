# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Cherry-picks a merge commit into a servicing worktree.

.DESCRIPTION
    Applies the specified merge commit to the worktree using git cherry-pick.
    Handles merge commits (using -m 1 to pick the mainline parent) and reports
    any conflicts for manual or AI-assisted resolution.

.PARAMETER WorktreePath
    The path to the worktree where the cherry-pick should be applied.

.PARAMETER MergeCommitSha
    The SHA of the merge commit to cherry-pick.

.EXAMPLE
    $result = ./Invoke-CherryPick.ps1 -WorktreePath "./worktree" -MergeCommitSha "abc123"

.OUTPUTS
    PSCustomObject with Success (bool), HasConflicts (bool), and ConflictFiles (string[]).

.NOTES
    For merge commits, uses '-m 1' to cherry-pick from the first parent (mainline).
    If conflicts occur, the worktree is left in a conflicted state for resolution.
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory)]
    [string]$WorktreePath,

    [Parameter(Mandatory)]
    [string]$MergeCommitSha
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

. "$PSScriptRoot/ServicingLib.ps1"

if (-not (Test-Path $WorktreePath)) {
    Write-Error "Worktree path does not exist: $WorktreePath"
    exit 1
}

Write-Verbose "Cherry-picking commit $MergeCommitSha into $WorktreePath..."

# Determine if this is a merge commit (has multiple parents)
$parentCount = git -C $WorktreePath rev-list --parents -n 1 $MergeCommitSha 2>$null
$isMergeCommit = $false
if ($null -ne $parentCount) {
    $parts = ($parentCount -split '\s+')
    # Merge commits have the commit SHA + 2+ parent SHAs
    $isMergeCommit = ($parts.Count -gt 2)
}

# Build cherry-pick arguments
$cpArgs = @('-C', $WorktreePath, 'cherry-pick', '--no-commit')
if ($isMergeCommit) {
    # -m 1 selects the first parent (the mainline branch)
    $cpArgs += @('-m', '1')
    Write-Verbose "Detected merge commit, using -m 1 for mainline parent."
}
$cpArgs += $MergeCommitSha

# Execute cherry-pick
$cpOutput = git @cpArgs 2>&1
$cpExitCode = $LASTEXITCODE

if ($cpExitCode -eq 0) {
    Ok "Cherry-pick applied successfully (no conflicts)."
    return [PSCustomObject]@{
        Success       = $true
        HasConflicts  = $false
        ConflictFiles = @()
    }
}

# Check for conflicts
$conflictFiles = @()
$statusOutput = git -C $WorktreePath status --porcelain 2>$null
if ($null -ne $statusOutput) {
    foreach ($line in $statusOutput) {
        # Unmerged paths show as UU, AA, DD, etc.
        if ($line -match '^(UU|AA|DD|AU|UA|DU|UD)\s+(.+)$') {
            $conflictFiles += $Matches[2].Trim()
        }
    }
}

if ($conflictFiles.Count -gt 0) {
    Warn "Cherry-pick has conflicts in $($conflictFiles.Count) file(s):"
    foreach ($cf in $conflictFiles) {
        Warn "  - $cf"
    }

    return [PSCustomObject]@{
        Success       = $false
        HasConflicts  = $true
        ConflictFiles = $conflictFiles
    }
}

# Cherry-pick failed for a non-conflict reason
Err "Cherry-pick failed: $cpOutput"
return [PSCustomObject]@{
    Success       = $false
    HasConflicts  = $false
    ConflictFiles = @()
}
