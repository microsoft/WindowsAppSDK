# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

# ServicingLib.ps1 - Shared helpers for servicing cherry-pick automation
# This is the shared library for the servicing-cherry-pick skill

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

# ── Logging ──────────────────────────────────────────────────────────────────

function Info  { param([string]$Message) Write-Host $Message -ForegroundColor Cyan }
function Warn  { param([string]$Message) Write-Host $Message -ForegroundColor Yellow }
function Err   { param([string]$Message) Write-Host $Message -ForegroundColor Red }
function Ok    { param([string]$Message) Write-Host $Message -ForegroundColor Green }
function Step  { param([string]$Message) Write-Host "  >> $Message" -ForegroundColor White }

function Write-StepHeader {
    <#
    .SYNOPSIS
        Displays a formatted step header for orchestrator progress tracking.
    #>
    param(
        [Parameter(Mandatory)][string]$StepNumber,
        [Parameter(Mandatory)][string]$Description
    )
    Write-Host ""
    Write-Host ("=" * 70) -ForegroundColor Cyan
    Write-Host "  [$StepNumber] $Description" -ForegroundColor Cyan
    Write-Host ("=" * 70) -ForegroundColor Cyan
}

# ── Configuration ────────────────────────────────────────────────────────────

function Get-ServicingConfig {
    <#
    .SYNOPSIS
        Loads the servicing configuration from the default or specified path.

    .PARAMETER ConfigPath
        Optional path to a servicing-config.json file. If not provided, uses the
        default config from the skill's config/ directory.

    .OUTPUTS
        PSCustomObject. The parsed configuration object.
    #>
    param([string]$ConfigPath)

    if (-not $ConfigPath) {
        $ConfigPath = Join-Path $PSScriptRoot '..\config\servicing-config.json'
    }

    if (-not (Test-Path $ConfigPath)) {
        throw "Servicing config not found at: $ConfigPath"
    }

    $config = Get-Content -LiteralPath $ConfigPath -Raw | ConvertFrom-Json
    return $config
}

# ── State Persistence ────────────────────────────────────────────────────────

function Get-ServicingStateDir {
    <#
    .SYNOPSIS
        Returns the state directory path for a given PR number.

    .DESCRIPTION
        State is stored under 'Generated Files/servicing/<PR>/' relative to the
        repository root.
    #>
    param(
        [Parameter(Mandatory)][int]$PullRequestNumber,
        [Parameter(Mandatory)][string]$RepoRoot
    )

    $dir = Join-Path $RepoRoot "Generated Files/servicing/$PullRequestNumber"
    if (-not (Test-Path $dir)) {
        $null = New-Item -ItemType Directory -Path $dir -Force
    }
    return $dir
}

function Get-ServicingState {
    <#
    .SYNOPSIS
        Loads the persisted servicing state for a PR, or returns a fresh state object.

    .OUTPUTS
        PSCustomObject with properties: pullRequest, branches (hashtable of branch states),
        startedAt, lastUpdatedAt.
    #>
    param(
        [Parameter(Mandatory)][int]$PullRequestNumber,
        [Parameter(Mandatory)][string]$RepoRoot
    )

    $dir = Get-ServicingStateDir -PullRequestNumber $PullRequestNumber -RepoRoot $RepoRoot
    $stateFile = Join-Path $dir 'state.json'

    if (Test-Path $stateFile) {
        $state = Get-Content -LiteralPath $stateFile -Raw | ConvertFrom-Json
        Info "Resuming from saved state (last updated: $($state.lastUpdatedAt))"
        return $state
    }

    return [PSCustomObject]@{
        pullRequestNumber = $PullRequestNumber
        branches          = @{}
        startedAt         = (Get-Date -Format 'o')
        lastUpdatedAt     = (Get-Date -Format 'o')
    }
}

function Save-ServicingState {
    <#
    .SYNOPSIS
        Persists the servicing state to disk after each branch operation.
    #>
    param(
        [Parameter(Mandatory)][PSCustomObject]$State,
        [Parameter(Mandatory)][string]$RepoRoot
    )

    $State.lastUpdatedAt = (Get-Date -Format 'o')
    $dir = Get-ServicingStateDir -PullRequestNumber $State.pullRequestNumber -RepoRoot $RepoRoot
    $stateFile = Join-Path $dir 'state.json'
    $State | ConvertTo-Json -Depth 10 | Set-Content -LiteralPath $stateFile -Encoding UTF8
    Write-Verbose "State saved to $stateFile"
}

# ── Prerequisites ────────────────────────────────────────────────────────────

function Test-Prerequisite {
    <#
    .SYNOPSIS
        Checks that a CLI tool is installed and optionally authenticated.

    .PARAMETER Command
        The command name to check (e.g., 'gh', 'az', 'git', 'claude').

    .PARAMETER AuthCheck
        Optional script block to verify authentication. Should return $true if authenticated.

    .OUTPUTS
        Boolean. $true if the prerequisite is met.
    #>
    param(
        [Parameter(Mandatory)][string]$Command,
        [scriptblock]$AuthCheck
    )

    try {
        $null = Get-Command $Command -ErrorAction Stop
    }
    catch {
        Err "'$Command' is not installed or not in PATH."
        return $false
    }

    if ($AuthCheck) {
        $authResult = & $AuthCheck
        if (-not $authResult) {
            Err "'$Command' is installed but not authenticated."
            return $false
        }
    }

    return $true
}

function Test-AllPrerequisites {
    <#
    .SYNOPSIS
        Validates all required tools are installed and authenticated.

    .PARAMETER SkipAdoBugs
        If set, skips checking for 'az' CLI.

    .OUTPUTS
        Boolean. $true if all prerequisites are met.
    #>
    param([switch]$SkipAdoBugs)

    $allGood = $true

    # git
    if (-not (Test-Prerequisite -Command 'git')) {
        Err "  Install from: https://git-scm.com/"
        $allGood = $false
    }

    # gh (GitHub CLI)
    if (-not (Test-Prerequisite -Command 'gh' -AuthCheck {
        $null = gh auth status 2>&1
        return ($LASTEXITCODE -eq 0)
    })) {
        Err "  Install: https://cli.github.com/ then run: gh auth login"
        $allGood = $false
    }

    # az (Azure CLI) - only if ADO bugs are needed
    if (-not $SkipAdoBugs) {
        if (-not (Test-Prerequisite -Command 'az' -AuthCheck {
            $account = az account show 2>&1
            return ($LASTEXITCODE -eq 0)
        })) {
            Err "  Install: https://aka.ms/installazurecli then run: az login"
            $allGood = $false
        }
    }

    return $allGood
}

# ── Git Helpers ──────────────────────────────────────────────────────────────

function Get-RepoRoot {
    <#
    .SYNOPSIS
        Gets the root directory of the current Git repository.

    .OUTPUTS
        System.String. The absolute path to the repository root.
    #>
    $root = git rev-parse --show-toplevel 2>$null
    if (-not $root) { throw 'Not inside a git repository.' }
    return $root
}

function Get-CurrentBranch {
    <#
    .SYNOPSIS
        Returns the name of the currently checked-out branch.
    #>
    $branch = git rev-parse --abbrev-ref HEAD 2>$null
    if (-not $branch) { throw 'Cannot determine current branch.' }
    return $branch
}

# ── String Helpers ───────────────────────────────────────────────────────────

function ConvertTo-BranchSlug {
    <#
    .SYNOPSIS
        Converts a PR title to a safe branch name slug.

    .EXAMPLE
        ConvertTo-BranchSlug -Title "Fix FileTypeChoices in Storage Pickers"
        # Returns: fix-filetypechoices-in-storage-pickers
    #>
    param([Parameter(Mandatory)][string]$Title)

    $slug = $Title.ToLower()
    $slug = $slug -replace '[^a-z0-9\s-]', ''
    $slug = $slug -replace '\s+', '-'
    $slug = $slug -replace '-+', '-'
    $slug = $slug.Trim('-')
    if ($slug.Length -gt 50) { $slug = $slug.Substring(0, 50).TrimEnd('-') }
    return $slug
}

function Format-BranchName {
    <#
    .SYNOPSIS
        Formats a cherry-pick branch name from a template pattern.

    .PARAMETER Pattern
        The branch name pattern with {placeholders}.

    .PARAMETER Values
        Hashtable of placeholder values.
    #>
    param(
        [Parameter(Mandatory)][string]$Pattern,
        [Parameter(Mandatory)][hashtable]$Values
    )

    $result = $Pattern
    foreach ($key in $Values.Keys) {
        $result = $result -replace "\{$key\}", $Values[$key]
    }
    return $result
}

function Format-PatchVersionSymbol {
    <#
    .SYNOPSIS
        Formats a WinAppSDK patch version symbol (e.g., WinAppSDK_1_7_9).
    #>
    param(
        [Parameter(Mandatory)][int]$Major,
        [Parameter(Mandatory)][int]$Minor,
        [Parameter(Mandatory)][int]$Patch
    )

    return "WinAppSDK_${Major}_${Minor}_${Patch}"
}

# ── Dry Run Support ──────────────────────────────────────────────────────────

function Invoke-WithDryRun {
    <#
    .SYNOPSIS
        Executes a script block, or logs what would happen in dry-run mode.

    .PARAMETER Description
        What the action does (for logging).

    .PARAMETER ScriptBlock
        The code to execute if not in dry-run mode.

    .PARAMETER DryRun
        If set, only logs the description without executing.

    .OUTPUTS
        The return value of the script block, or $null in dry-run mode.
    #>
    param(
        [Parameter(Mandatory)][string]$Description,
        [Parameter(Mandatory)][scriptblock]$ScriptBlock,
        [switch]$DryRun
    )

    if ($DryRun) {
        Write-Host "  [DRY RUN] Would: $Description" -ForegroundColor DarkGray
        return $null
    }

    Step $Description
    return (& $ScriptBlock)
}
