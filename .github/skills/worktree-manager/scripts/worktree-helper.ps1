<#
.SYNOPSIS
    Unified Git worktree management helper for common operations.

.DESCRIPTION
    A single entry point for creating, listing, and deleting Git worktrees.
    Wraps the individual scripts in tools/git/ for convenience.

.PARAMETER Action
    The operation to perform: new-branch, new-issue, delete, list

.PARAMETER Branch
    Branch name for new-branch action.

.PARAMETER Number
    Work item number for new-issue action.

.PARAMETER Title
    Optional title for new-issue action.

.PARAMETER Pattern
    Pattern to match for delete action.

.PARAMETER Force
    Force delete with uncommitted changes.

.PARAMETER Help
    Show this help message.

.EXAMPLE
    ./worktree-helper.ps1 list

.EXAMPLE
    ./worktree-helper.ps1 new-branch -Branch feature/login

.EXAMPLE
    ./worktree-helper.ps1 new-issue -Number 1234 -Title "Fix crash"

.EXAMPLE
    ./worktree-helper.ps1 delete -Pattern feature/login -Force
#>

[CmdletBinding()]
param(
    [Parameter(Position=0)]
    [ValidateSet('new-branch', 'new-issue', 'delete', 'list', 'help')]
    [string] $Action = 'help',
    
    [string] $Branch,
    [int] $Number,
    [string] $Title,
    [string] $Pattern,
    [string] $Base = 'origin/main',
    [switch] $Force,
    [switch] $KeepBranch,
    [switch] $Help
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

# Locate the tools/git directory relative to repo root
function Get-ToolsGitPath {
    $repoRoot = git rev-parse --show-toplevel 2>$null
    if (-not $repoRoot) { throw 'Not inside a Git repository.' }
    $toolsGit = Join-Path $repoRoot 'tools/git'
    if (-not (Test-Path $toolsGit)) { throw "tools/git directory not found at: $toolsGit" }
    return $toolsGit
}

function Show-Help {
    Write-Host @"
Git Worktree Helper - Unified worktree management

USAGE:
    worktree-helper.ps1 <action> [options]

ACTIONS:
    list                    List all existing worktrees
    new-branch -Branch <n>  Create worktree from existing branch
    new-issue -Number <n>   Create worktree for work item branch
    delete -Pattern <p>     Delete a worktree by pattern match

OPTIONS:
    -Branch <name>          Branch name for new-branch
    -Number <int>           Work item number for new-issue
    -Title <text>           Optional title for new-issue (creates slug)
    -Base <ref>             Base ref for new-issue (default: origin/main)
    -Pattern <text>         Pattern to match worktree for delete
    -Force                  Force delete with uncommitted changes
    -KeepBranch             Don't delete branch after worktree removal

EXAMPLES:
    ./worktree-helper.ps1 list
    ./worktree-helper.ps1 new-branch -Branch feature/login
    ./worktree-helper.ps1 new-issue -Number 1234 -Title "Fix null ref"
    ./worktree-helper.ps1 delete -Pattern workitem/1234 -Force

For detailed help on each script, run them directly with -Help:
    tools/git/New-WorktreeFromBranch.ps1 -Help
    tools/git/New-WorktreeFromIssue.ps1 -Help
    tools/git/Delete-Worktree.ps1 -Help
"@
}

function Show-WorktreeList {
    $entries = git worktree list --porcelain 2>$null
    if (-not $entries) {
        Write-Host "No worktrees found." -ForegroundColor Yellow
        return
    }
    
    Write-Host "`nGit Worktrees:" -ForegroundColor Cyan
    Write-Host ("-" * 60)
    
    $current = @{}
    foreach ($line in $entries) {
        if ($line -eq '') {
            if ($current.path) {
                $branch = if ($current.branch) { $current.branch -replace '^refs/heads/', '' } else { '(detached)' }
                $marker = if ($current.path -eq (git rev-parse --show-toplevel 2>$null)) { ' [main]' } else { '' }
                Write-Host ("  {0,-40} -> {1}{2}" -f $branch, $current.path, $marker)
            }
            $current = @{}
            continue
        }
        if ($line -like 'worktree *') { $current.path = ($line -split ' ', 2)[1] }
        elseif ($line -like 'branch *') { $current.branch = ($line -split ' ', 2)[1] }
    }
    if ($current.path) {
        $branch = if ($current.branch) { $current.branch -replace '^refs/heads/', '' } else { '(detached)' }
        Write-Host ("  {0,-40} -> {1}" -f $branch, $current.path)
    }
    
    Write-Host ("-" * 60)
    Write-Host ""
}

# Main dispatch
if ($Help -or $Action -eq 'help') {
    Show-Help
    return
}

$toolsGit = Get-ToolsGitPath

switch ($Action) {
    'list' {
        Show-WorktreeList
    }
    'new-branch' {
        if (-not $Branch) { throw "new-branch requires -Branch parameter" }
        $script = Join-Path $toolsGit 'New-WorktreeFromBranch.ps1'
        & $script -Branch $Branch
    }
    'new-issue' {
        if (-not $Number) { throw "new-issue requires -Number parameter" }
        $script = Join-Path $toolsGit 'New-WorktreeFromIssue.ps1'
        $params = @{ Number = $Number; Base = $Base }
        if ($Title) { $params.Title = $Title }
        & $script @params
    }
    'delete' {
        if (-not $Pattern) { throw "delete requires -Pattern parameter" }
        $script = Join-Path $toolsGit 'Delete-Worktree.ps1'
        $params = @{ Pattern = $Pattern }
        if ($Force) { $params.Force = $true }
        if ($KeepBranch) { $params.KeepBranch = $true }
        & $script @params
    }
    default {
        Show-Help
    }
}

exit 0
