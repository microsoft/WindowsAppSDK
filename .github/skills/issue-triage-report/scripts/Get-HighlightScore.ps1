# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Calculates the highlight score for a specific GitHub issue.

.DESCRIPTION
    This script fetches issue details and calculates a priority score (0-100)
    based on deterministic factors including reactions, age, and comments.
    Severity and blocker annotations are agent-assessed in Phase 1.

.PARAMETER IssueNumber
    The GitHub issue number to analyze.

.PARAMETER Repo
    Repository in 'owner/repo' format. Default: microsoft/WindowsAppSDK

.PARAMETER Verbose
    Show detailed scoring breakdown.

.EXAMPLE
    ./Get-HighlightScore.ps1 -IssueNumber 4651

.EXAMPLE
    ./Get-HighlightScore.ps1 -IssueNumber 2894 -Verbose
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [int]$IssueNumber,

    [Parameter()]
    [ValidatePattern('^[\w-]+/[\w.-]+$')]
    [string]$Repo = "microsoft/WindowsAppSDK",

    [Parameter()]
    [string]$ConfigPath
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

# Import shared functions
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
. "$ScriptDir\ReportLib.ps1"

# Load configuration
if (-not $ConfigPath) {
    $ConfigPath = Join-Path $ScriptDir "ScoringConfig.json"
}
$Config = Get-ScoringConfig -ConfigPath $ConfigPath

function Get-DetailedIssueScore {
    <#
    .SYNOPSIS
        Wraps Get-IssueScore with a detailed breakdown for diagnostic display.

    .DESCRIPTION
        Delegates all scoring math to Get-IssueScore (ReportLib.ps1) and adds
        presentation metadata (Reason strings, MaxScore) for the formatted output.
    #>
    param(
        [object]$Issue,
        [hashtable]$Config
    )

    $score = Get-IssueScore -Issue $issue -Config $Config
    $weights = $Config.weights
    $thresholds = $Config.thresholds

    # Build breakdown with presentation metadata on top of canonical scores
    $breakdown = @{
        Reactions = @{ Raw = $score.RawReactions; Score = $score.Reactions; MaxScore = $weights.reactions; Reason = "" }
        Age       = @{ Raw = $score.RawAge;       Score = $score.Age;       MaxScore = $weights.age;       Reason = "" }
        Comments  = @{ Raw = $score.RawComments;  Score = $score.Comments;  MaxScore = $weights.comments;  Reason = "" }
        Severity  = @{ Raw = $score.SeverityLabel; Score = $score.Severity; MaxScore = $weights.severity;  Reason = "" }
        Blockers  = @{ Raw = $score.IsBlocker;    Score = $score.Blockers;  MaxScore = $weights.blockers;  Reason = "" }
    }

    # Reason strings (presentation only — scoring math lives in Get-IssueScore)
    if ($score.RawReactions -ge $thresholds.popular_reactions) {
        $breakdown.Reactions.Reason = "🌟 Popular (community interest)"
    }

    $hasNeedsTriage = Test-HasLabel -Labels $Issue.labels -LabelName "needs-triage"
    if ($score.RawAge -gt $thresholds.aging_days -and $hasNeedsTriage) {
        $breakdown.Age.Reason = "⏰ Aging (needs triage for $($score.RawAge) days)"
    }
    elseif ($score.RawAge -gt $thresholds.aging_days) {
        $breakdown.Age.Reason = "Open for $($score.RawAge) days"
    }

    if ($score.RawComments -ge $thresholds.trending_comments -and $score.RawUpdateAgeDays -le $thresholds.trending_days) {
        $breakdown.Comments.Reason = "📈 Trending ($($score.RawComments) comments, updated within $($thresholds.trending_days) days)"
    }

    if ($score.SeverityLabel) {
        $severityLabels = $Config.severityLabels
        if ($severityLabels.critical -contains $score.SeverityLabel) {
            $breakdown.Severity.Reason = "🔴 Critical: $($score.SeverityLabel)"
        }
        elseif ($severityLabels.high -contains $score.SeverityLabel) {
            $breakdown.Severity.Reason = "🟠 High: $($score.SeverityLabel)"
        }
        elseif ($severityLabels.medium -contains $score.SeverityLabel) {
            $breakdown.Severity.Reason = "🟡 Medium: $($score.SeverityLabel)"
        }
        elseif ($severityLabels.low -contains $score.SeverityLabel) {
            $breakdown.Severity.Reason = "🟢 Low: $($score.SeverityLabel)"
        }
    }

    if ($score.IsBlocker -and $weights.blockers -gt 0) {
        $breakdown.Blockers.Reason = "🚧 Blocker issue"
    }

    return @{
        Breakdown = $breakdown
        TotalScore = $score.Total
        MaxPossible = 100
    }
}

function Format-ScoreBreakdown {
    <#
    .SYNOPSIS
        Formats the score breakdown for display.
    #>
    param(
        [hashtable]$ScoreResult,
        [object]$Issue
    )

    $sb = [System.Text.StringBuilder]::new()

    [void]$sb.AppendLine("")
    [void]$sb.AppendLine("═══════════════════════════════════════════════════════════")
    [void]$sb.AppendLine("  Issue #$($Issue.number): $($Issue.title)")
    [void]$sb.AppendLine("═══════════════════════════════════════════════════════════")
    [void]$sb.AppendLine("")

    # Labels
    $labelNames = ($Issue.labels | ForEach-Object { $_.name }) -join ", "
    [void]$sb.AppendLine("  Labels: $labelNames")
    [void]$sb.AppendLine("  Author: @$($Issue.author.login)")
    [void]$sb.AppendLine("  Created: $($Issue.createdAt)")
    [void]$sb.AppendLine("")

    [void]$sb.AppendLine("  SCORE BREAKDOWN:")
    [void]$sb.AppendLine("  ───────────────────────────────────────────────────────")

    $breakdown = $ScoreResult.Breakdown

    foreach ($factor in @("Reactions", "Age", "Comments", "Severity", "Blockers")) {
        $data = $breakdown[$factor]
        $score = $data.Score
        $max = $data.MaxScore
        $raw = $data.Raw
        $reason = $data.Reason

        # Skip factors with 0 max score (disabled)
        if ($max -eq 0) { continue }

        $bar = "█" * [math]::Floor($score / $max * 10)
        $bar = $bar.PadRight(10, "░")

        $line = "  {0,-12} [{1}] {2,2}/{3,2}  (raw: {4})" -f $factor, $bar, $score, $max, $raw
        [void]$sb.AppendLine($line)

        if ($reason) {
            [void]$sb.AppendLine("               └─ $reason")
        }
    }

    [void]$sb.AppendLine("  ───────────────────────────────────────────────────────")
    [void]$sb.AppendLine("  TOTAL SCORE: $($ScoreResult.TotalScore) / $($ScoreResult.MaxPossible)")
    [void]$sb.AppendLine("")

    # Highlight recommendation
    $score = $ScoreResult.TotalScore
    $recommendation = if ($score -ge 60) {
        "🔴 HIGH PRIORITY - Should be highlighted in triage report"
    }
    elseif ($score -ge 40) {
        "🟡 MEDIUM PRIORITY - Consider for triage discussion"
    }
    elseif ($score -ge 20) {
        "🟢 NORMAL PRIORITY - Standard backlog item"
    }
    else {
        "⚪ LOW PRIORITY - Monitor but not urgent"
    }

    [void]$sb.AppendLine("  Recommendation: $recommendation")
    [void]$sb.AppendLine("")

    return $sb.ToString()
}

# ============================================================================
# Main Execution
# ============================================================================

Write-Host "Fetching issue #$($IssueNumber) from $Repo..." -ForegroundColor Cyan

# Verify GitHub CLI is available
try {
    $null = gh auth status 2>&1
}
catch {
    Write-Error "GitHub CLI not authenticated. Run 'gh auth login' first."
    exit 1
}

# Fetch issue details
$jsonFields = "number,title,createdAt,updatedAt,labels,reactionGroups,comments,author,state,body"
$issueJson = gh issue view $IssueNumber --repo $Repo --json $jsonFields 2>&1

if ($LASTEXITCODE -ne 0) {
    Write-Error "Failed to fetch issue #$($IssueNumber): $issueJson"
    exit 1
}

$issue = $issueJson | ConvertFrom-Json

if ($issue.state -ne "OPEN") {
    Write-Warning "Note: Issue #$($IssueNumber) is $($issue.state.ToLower()), not open."
}

# Calculate score
$scoreResult = Get-DetailedIssueScore -Issue $issue -Config $Config

# Output
if ($VerbosePreference -eq "Continue" -or $PSBoundParameters.ContainsKey('Verbose')) {
    $output = Format-ScoreBreakdown -ScoreResult $scoreResult -Issue $issue
    Write-Output $output
}
else {
    # Simple output
    Write-Host ""
    Write-Host "Issue #$($IssueNumber) Score: $($scoreResult.TotalScore)/100" -ForegroundColor Green
    Write-Host ""

    # Show top contributing factors
    $breakdown = $scoreResult.Breakdown
    $factors = @()
    foreach ($factor in @("Reactions", "Age", "Comments", "Severity", "Blockers")) {
        if ($breakdown[$factor].Reason) {
            $factors += $breakdown[$factor].Reason
        }
    }

    if ($factors.Count -gt 0) {
        Write-Host "Key factors:" -ForegroundColor Yellow
        foreach ($f in $factors) {
            Write-Host "  • $f"
        }
    }

    Write-Host ""
    Write-Host "Use -Verbose for detailed breakdown." -ForegroundColor Gray
}
