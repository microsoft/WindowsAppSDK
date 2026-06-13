# IssueReviewLib.ps1 - Minimal helpers for PR review workflow
# Shared helpers for GitHub Copilot/Claude Code issue review workflows
# This is a trimmed version - pr-review only needs console helpers and repo root

#region Console Output Helpers
function Info { param([string]$Message) Write-Host $Message -ForegroundColor Cyan }
function Warn { param([string]$Message) Write-Host $Message -ForegroundColor Yellow }
function Err  { param([string]$Message) Write-Host $Message -ForegroundColor Red }
function Success { param([string]$Message) Write-Host $Message -ForegroundColor Green }
function Get-RepoSlug {
    $slug = gh repo view --json nameWithOwner --jq .nameWithOwner 2>$null
    if (-not $slug) { throw 'Cannot detect repository. Ensure gh CLI is authenticated and you are in a git repo.' }
    return $slug
}
#endregion

#region Repository Helpers
function Get-RepoRoot {
    $root = git rev-parse --show-toplevel 2>$null
    if (-not $root) { throw 'Not inside a git repository.' }
    return (Resolve-Path $root).Path
}
function Get-RepoSlug {
    $slug = gh repo view --json nameWithOwner --jq .nameWithOwner 2>$null
    if (-not $slug) { throw 'Cannot detect repository. Ensure gh CLI is authenticated and you are in a git repo.' }
    return $slug
}
#endregion
