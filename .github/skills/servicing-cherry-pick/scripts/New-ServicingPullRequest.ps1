# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Commits changes in a servicing worktree and creates a GitHub pull request.

.DESCRIPTION
    Stages all changes in the worktree, creates a commit with a standardized message,
    pushes the branch to origin, and creates a GitHub PR targeting the release branch.

.PARAMETER WorktreePath
    Path to the worktree with the servicing changes.

.PARAMETER BranchName
    The branch name to push.

.PARAMETER TargetBranch
    The release branch to target (e.g., "release/1.7-stable").

.PARAMETER OriginalPrNumber
    The original PR number being cherry-picked.

.PARAMETER OriginalPrTitle
    The original PR title.

.PARAMETER BugId
    The ADO bug ID for the servicing work item.

.PARAMETER VersionString
    The servicing version (e.g., "1.7.9").

.PARAMETER EnumName
    The RuntimeCompatibilityChange enum name.

.PARAMETER PrBody
    The PR body markdown. If not provided, uses the template.

.PARAMETER Repository
    The GitHub repository in owner/repo format.

.PARAMETER ConfigPath
    Optional path to servicing-config.json.

.PARAMETER DryRun
    If set, shows what would be created without actually pushing or creating the PR.

.EXAMPLE
    $pr = ./New-ServicingPullRequest.ps1 -WorktreePath "./worktree" `
        -BranchName "user/me/cherry-pick-fix-1.7" -TargetBranch "release/1.7-stable" `
        -OriginalPrNumber 5865 -OriginalPrTitle "Fix thing" -BugId 61124052

.OUTPUTS
    PSCustomObject with PrNumber and PrUrl properties.

.NOTES
    Requires GitHub CLI (gh) authenticated with push access to the repository.
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory)]
    [string]$WorktreePath,

    [Parameter(Mandatory)]
    [string]$BranchName,

    [Parameter(Mandatory)]
    [string]$TargetBranch,

    [Parameter(Mandatory)]
    [int]$OriginalPrNumber,

    [Parameter(Mandatory)]
    [string]$OriginalPrTitle,

    [Parameter()]
    [int]$BugId,

    [Parameter()]
    [string]$VersionString,

    [Parameter()]
    [string]$EnumName,

    [Parameter()]
    [string]$PrBody,

    [Parameter()]
    [string]$Repository,

    [Parameter()]
    [string]$ConfigPath,

    [switch]$DryRun
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

. "$PSScriptRoot/ServicingLib.ps1"

$config = Get-ServicingConfig -ConfigPath $ConfigPath

if (-not $Repository) {
    $Repository = $config.repository
}

# Extract version label from target branch
$versionLabel = ''
if ($TargetBranch -match 'release/(\d+\.\d+)-stable') {
    $versionLabel = $Matches[1]
}

# Build commit message
$commitMessage = "[CP to $versionLabel] Cherry-pick PR#$OriginalPrNumber - $OriginalPrTitle"
if ($BugId) {
    $commitMessage += "`n`nBug $BugId`: [$VersionString servicing] $OriginalPrTitle"
    $commitMessage += "`nContainment: $EnumName"
}

# Build PR title
$prTitle = $config.naming.prTitlePattern -replace '\{originalTitle\}', $OriginalPrTitle
if ($versionLabel) {
    $prTitle = "[$versionLabel] $prTitle"
}

# Build PR body from template if not provided
if (-not $PrBody) {
    $templatePath = Join-Path $PSScriptRoot '..\templates\pr-body-template.md'
    if (Test-Path $templatePath) {
        $PrBody = Get-Content -LiteralPath $templatePath -Raw
        $PrBody = $PrBody -replace '\{\{ORIGINAL_PR_NUMBER\}\}', $OriginalPrNumber
        $PrBody = $PrBody -replace '\{\{ORIGINAL_PR_TITLE\}\}', $OriginalPrTitle
        $PrBody = $PrBody -replace '\{\{TARGET_BRANCH\}\}', $TargetBranch
        $PrBody = $PrBody -replace '\{\{VERSION_STRING\}\}', $VersionString
        $PrBody = $PrBody -replace '\{\{BUG_ID\}\}', $BugId
        $PrBody = $PrBody -replace '\{\{ENUM_NAME\}\}', $EnumName
        $PrBody = $PrBody -replace '\{\{REPOSITORY\}\}', $Repository
    }
    else {
        $PrBody = @"
## Cherry-Pick: #$OriginalPrNumber - $OriginalPrTitle

**Target:** $TargetBranch ($VersionString)
$(if ($BugId) { "**ADO Bug:** $BugId" })
$(if ($EnumName) { "**Containment:** ``$EnumName``" })

Cherry-pick of #$OriginalPrNumber to $TargetBranch with containment wrapping.
"@
    }
}

if ($DryRun) {
    Write-Host "[DRY RUN] Would create PR:" -ForegroundColor DarkGray
    Write-Host "  Title:  $prTitle" -ForegroundColor DarkGray
    Write-Host "  Base:   $TargetBranch" -ForegroundColor DarkGray
    Write-Host "  Branch: $BranchName" -ForegroundColor DarkGray
    Write-Host "  Commit: $commitMessage" -ForegroundColor DarkGray
    return [PSCustomObject]@{
        PrNumber = 0
        PrUrl    = 'https://github.com/dry-run'
        DryRun   = $true
    }
}

# Stage and commit changes
Write-Verbose "Staging changes in $WorktreePath..."
git -C $WorktreePath add -A 2>&1 | Out-Null
if ($LASTEXITCODE -ne 0) {
    Write-Error "Failed to stage changes."
    exit 1
}

# Check if there are changes to commit
$status = git -C $WorktreePath status --porcelain 2>$null
if (-not $status) {
    Warn "No changes to commit in worktree."
    return [PSCustomObject]@{
        PrNumber = 0
        PrUrl    = ''
        DryRun   = $false
        Reason   = 'No changes to commit'
    }
}

Write-Verbose "Committing: $commitMessage"
git -C $WorktreePath commit -m $commitMessage 2>&1 | Out-Null
if ($LASTEXITCODE -ne 0) {
    Write-Error "Failed to commit changes."
    exit 1
}

# Push branch to origin
Write-Verbose "Pushing $BranchName to origin..."
$pushOutput = git -C $WorktreePath push -u origin $BranchName 2>&1
if ($LASTEXITCODE -ne 0) {
    Write-Error "Failed to push branch: $pushOutput"
    exit 1
}

Ok "Branch pushed: $BranchName"

# Create PR via gh CLI
Write-Verbose "Creating PR..."
$ghArgs = @(
    'pr', 'create',
    '--repo', $Repository,
    '--base', $TargetBranch,
    '--head', $BranchName,
    '--title', $prTitle,
    '--body', $PrBody
)

$prUrl = & gh @ghArgs 2>&1
if ($LASTEXITCODE -ne 0) {
    Write-Error "Failed to create PR: $prUrl"
    exit 1
}

$prUrl = ($prUrl -join '').Trim()

# Extract PR number from URL
$prNumber = 0
if ($prUrl -match '/pull/(\d+)') {
    $prNumber = [int]$Matches[1]
}

Ok "PR created: $prUrl"

return [PSCustomObject]@{
    PrNumber = $prNumber
    PrUrl    = $prUrl
    DryRun   = $false
}
