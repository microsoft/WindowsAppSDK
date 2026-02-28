# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Fetches pull request metadata and diff from GitHub.

.DESCRIPTION
    Uses the GitHub CLI to retrieve PR title, body, merge commit SHA, changed files,
    and the full diff for a merged pull request.

.PARAMETER PullRequestNumber
    The PR number to fetch details for.

.PARAMETER Repository
    The GitHub repository in owner/repo format. Defaults to config value.

.EXAMPLE
    $pr = ./Get-PullRequestDetails.ps1 -PullRequestNumber 5865

.NOTES
    Requires GitHub CLI (gh) to be installed and authenticated.
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory)]
    [int]$PullRequestNumber,

    [Parameter()]
    [string]$Repository
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

. "$PSScriptRoot/ServicingLib.ps1"

# Load config for default repository
if (-not $Repository) {
    $config = Get-ServicingConfig
    $Repository = $config.repository
}

Write-Verbose "Fetching PR #$PullRequestNumber from $Repository..."

# Fetch PR metadata via gh CLI
$ghArgs = @(
    'pr', 'view', $PullRequestNumber,
    '--repo', $Repository,
    '--json', 'number,title,body,author,mergeCommit,state,baseRefName,headRefName,files,url'
)

$rawJson = & gh @ghArgs 2>&1
if ($LASTEXITCODE -ne 0) {
    Write-Error "Failed to fetch PR #$PullRequestNumber from $Repository. Error: $rawJson"
    exit 1
}

$prData = $rawJson | ConvertFrom-Json

# Validate PR is merged
if ($prData.state -ne 'MERGED') {
    Write-Error "PR #$PullRequestNumber is not merged (state: $($prData.state)). Only merged PRs can be cherry-picked."
    exit 1
}

# Extract merge commit SHA
$mergeCommitSha = $null
if ($null -ne $prData.mergeCommit -and $null -ne $prData.mergeCommit.oid) {
    $mergeCommitSha = $prData.mergeCommit.oid
}

if (-not $mergeCommitSha) {
    Write-Error "Could not determine merge commit SHA for PR #$PullRequestNumber."
    exit 1
}

# Fetch the diff
Write-Verbose "Fetching diff for PR #$PullRequestNumber..."
$diffArgs = @(
    'pr', 'diff', $PullRequestNumber,
    '--repo', $Repository
)

$diff = & gh @diffArgs 2>&1
if ($LASTEXITCODE -ne 0) {
    Warn "Could not fetch diff via gh pr diff, falling back to git diff..."
    $diff = git diff "$mergeCommitSha^..$mergeCommitSha" 2>&1
    if ($LASTEXITCODE -ne 0) {
        Write-Error "Failed to fetch diff for PR #$PullRequestNumber."
        exit 1
    }
}

# Build file list with paths and change types
$changedFiles = @()
if ($null -ne $prData.files) {
    foreach ($file in $prData.files) {
        $changedFiles += [PSCustomObject]@{
            Path      = $file.path
            Additions = if ($null -ne $file.additions) { $file.additions } else { 0 }
            Deletions = if ($null -ne $file.deletions) { $file.deletions } else { 0 }
        }
    }
}

# Build result object
$result = [PSCustomObject]@{
    Number         = $prData.number
    Title          = $prData.title
    Body           = $prData.body
    Author         = if ($null -ne $prData.author) { $prData.author.login } else { 'unknown' }
    MergeCommitSha = $mergeCommitSha
    BaseRefName    = $prData.baseRefName
    HeadRefName    = $prData.headRefName
    Url            = $prData.url
    State          = $prData.state
    Files          = $changedFiles
    Diff           = ($diff -join "`n")
}

Write-Verbose "PR #${PullRequestNumber}: '$($result.Title)' by $($result.Author)"
Write-Verbose "  Merge commit: $($result.MergeCommitSha)"
Write-Verbose "  Changed files: $($result.Files.Count)"

return $result
