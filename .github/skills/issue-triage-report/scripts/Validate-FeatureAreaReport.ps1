# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Generates a live feature area report from GitHub data.

.DESCRIPTION
    Discovers all area labels in the microsoft/WindowsAppSDK repository via GitHub CLI,
    queries live issue counts per area label, and reports open, needs-triage,
    feature-proposal, and closed (30-day) counts for each area.

.PARAMETER Repository
    Repository in 'owner/repo' format. Defaults to 'microsoft/WindowsAppSDK'.

.EXAMPLE
    ./Validate-FeatureAreaReport.ps1

.NOTES
    Requires GitHub CLI (gh) to be installed and authenticated.
#>

[CmdletBinding()]
param(
    [Parameter()]
    [ValidatePattern('^[a-zA-Z0-9_-]+/[a-zA-Z0-9_.-]+$')]
    [string]$Repository = "microsoft/WindowsAppSDK"
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

# ── Helpers ──────────────────────────────────────────────────────────────────

function Assert-GhCli {
    try {
        $null = Get-Command gh -ErrorAction Stop
    }
    catch {
        Write-Error "GitHub CLI (gh) is not installed. Install: winget install GitHub.cli"
        exit 1
    }
    $null = gh auth status 2>&1
    if ($LASTEXITCODE -ne 0) {
        Write-Error "GitHub CLI is not authenticated. Run: gh auth login"
        exit 1
    }
}

function Get-AreaLabels {
    <#
    .SYNOPSIS
        Discovers all area-* labels in the repository via GitHub CLI.
    #>
    param(
        [string]$Repo
    )

    $labelsJson = gh label list --repo $Repo --search "area-" --limit 200 --json "name"
    $labels = @($labelsJson | ConvertFrom-Json)
    if ($null -eq $labels -or ($labels.Count -eq 1 -and $null -eq $labels[0])) {
        return @()
    }

    # Filter to labels starting with "area-" and sort alphabetically
    $areaLabels = @($labels |
        Where-Object { $_.name -like 'area-*' } |
        Sort-Object -Property name |
        ForEach-Object { $_.name })

    return $areaLabels
}

function Get-AreaIssueStats {
    <#
    .SYNOPSIS
        Fetches and categorises issues for a given area label.
    #>
    param(
        [string]$Repo,
        [string]$AreaLabel
    )

    # Open issues
    $openJson = gh issue list --repo $Repo --label $AreaLabel --state open --limit 500 `
        --json "number,labels"
    $openIssues = @($openJson | ConvertFrom-Json)
    # ConvertFrom-Json may return $null on empty set
    if ($null -eq $openIssues -or ($openIssues.Count -eq 1 -and $null -eq $openIssues[0])) {
        $openIssues = @()
    }

    $needsTriage = @($openIssues | Where-Object {
        @($_.labels | ForEach-Object { $_.name }) -contains 'needs-triage'
    })

    $proposals = @($openIssues | Where-Object {
        $names = @($_.labels | ForEach-Object { $_.name })
        ($names -contains 'feature proposal') -or ($names -contains 'feature-proposal')
    })

    # Closed issues (recent 30 days based on updatedAt)
    $closedJson = gh issue list --repo $Repo --label $AreaLabel --state closed --limit 500 `
        --json "number,updatedAt"
    $closedIssues = @($closedJson | ConvertFrom-Json)
    if ($null -eq $closedIssues -or ($closedIssues.Count -eq 1 -and $null -eq $closedIssues[0])) {
        $closedIssues = @()
    }

    $thirtyAgo = (Get-Date).AddDays(-30)
    $recentClosed = @($closedIssues | Where-Object {
        $null -ne $_ -and [datetime]$_.updatedAt -gt $thirtyAgo
    })

    return @{
        Open        = $openIssues.Count
        NeedsTriage = $needsTriage.Count
        Proposals   = $proposals.Count
        Closed      = $recentClosed.Count
    }
}

# ── Main ─────────────────────────────────────────────────────────────────────

try {
    Assert-GhCli

    # ── Discover area labels dynamically ─────────────────────────────────────
    Write-Host ""
    Write-Host "════════════════════════════════════════════════════════════════════════" -ForegroundColor Cyan
    Write-Host "  Feature Area Report (Live)" -ForegroundColor Cyan
    Write-Host "  Repository:    $Repository" -ForegroundColor Gray
    Write-Host "  Generated:     $(Get-Date -Format 'yyyy-MM-dd HH:mm:ss')" -ForegroundColor Gray
    Write-Host "════════════════════════════════════════════════════════════════════════" -ForegroundColor Cyan
    Write-Host ""

    Write-Verbose "Discovering area labels..."
    $areaLabels = Get-AreaLabels -Repo $Repository
    if ($areaLabels.Count -eq 0) {
        Write-Error "No area labels found in $Repository"
        exit 1
    }
    Write-Verbose "Found $($areaLabels.Count) area labels"

    $totalOpen = 0
    $totalTriage = 0
    $totalProposals = 0
    $totalClosed = 0
    $areasChecked = 0

    # Header
    Write-Host ("  {0,-30} {1,6} {2,8} {3,8} {4,10}" -f `
        "Area", "Open", "Triage", "Proposals", "Closed(30d)") -ForegroundColor White
    Write-Host ("  " + ("-" * 70)) -ForegroundColor DarkGray

    foreach ($area in $areaLabels) {
        Write-Verbose "Querying $area..."
        $stats = Get-AreaIssueStats -Repo $Repository -AreaLabel $area

        $color = if ($stats.NeedsTriage -gt 5) { 'Yellow' }
                 elseif ($stats.Open -eq 0 -and $stats.Closed -eq 0) { 'DarkGray' }
                 else { 'White' }

        Write-Host ("  {0,-30} {1,6} {2,8} {3,8} {4,10}" -f `
            $area, $stats.Open, $stats.NeedsTriage, $stats.Proposals, $stats.Closed) `
            -ForegroundColor $color

        $totalOpen += $stats.Open
        $totalTriage += $stats.NeedsTriage
        $totalProposals += $stats.Proposals
        $totalClosed += $stats.Closed
        $areasChecked++
    }

    # ── Summary ──────────────────────────────────────────────────────────────
    Write-Host ""
    Write-Host ("  " + ("-" * 70)) -ForegroundColor DarkGray
    Write-Host ("  {0,-30} {1,6} {2,8} {3,8} {4,10}" -f `
        "TOTAL", $totalOpen, $totalTriage, $totalProposals, $totalClosed) -ForegroundColor Cyan
    Write-Host ""
    Write-Host "  Areas queried: $areasChecked" -ForegroundColor White

    Write-Host ""
    Write-Host "════════════════════════════════════════════════════════════════════════" -ForegroundColor Cyan

    exit 0
}
catch {
    Write-Error "Validation failed: $_"
    exit 1
}
