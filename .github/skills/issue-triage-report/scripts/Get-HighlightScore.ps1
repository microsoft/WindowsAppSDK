# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Calculates the highlight score for a specific GitHub issue.

.DESCRIPTION
    This script fetches issue details and calculates a priority score (unbounded)
    based on deterministic factors including reactions, age, and comments.
    Severity and blocker values are sourced from IssueAssessments.json
    (fixed path) and optional runtime agent assessments, with fallback behavior.

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

# Load optional IssueAssessments from fixed path before scoring calculations.
$IssueAssessments = Read-Assessments -ScriptDirectory $ScriptDir -AssessmentType Issue -EmitStatus

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
        [hashtable]$Config,
        [hashtable]$IssueAssessments,
        [hashtable]$AgentAssessments
    )

    $score = Get-IssueScore -Issue $issue -Config $Config -IssueAssessments $IssueAssessments -AgentAssessments $AgentAssessments
    $weights = $Config.weights
    $thresholds = $Config.thresholds

    # Build breakdown with presentation metadata on top of canonical scores.
    $breakdown = @{
        Reactions = @{ Raw = $score.RawReactions; Score = $score.Reactions; MaxScore = ([math]::Round($weights.reactions * 100, 1)); Rank = $score.ReactionsRank; Reason = "" }
        Age       = @{ Raw = $score.RawAge;       Score = $score.Age;       MaxScore = ([math]::Round($weights.age       * 100, 1)); Rank = $score.AgeRank;       Reason = "" }
        Comments  = @{ Raw = $score.RawComments;  Score = $score.Comments;  MaxScore = ([math]::Round($weights.comments  * 100, 1)); Rank = $score.CommentsRank;  Reason = "" }
        Severity  = @{ Raw = $score.SeverityLabel; Score = $score.Severity; MaxScore = ([math]::Round($weights.severity  * 100, 1)); Rank = 0;                    Reason = "" }
        Blockers  = @{ Raw = $score.IsBlocker;    Score = $score.Blockers;  MaxScore = ([math]::Round($weights.blockers  * 100, 1)); Rank = 0;                    Reason = "" }
    }

    # Reason strings (presentation only — scoring math lives in Get-IssueScore)
    if ($score.RawReactions -ge $thresholds.popular_reactions) {
        $reactionPercent = [math]::Round(($score.ReactionsRank * 100), 0)
        $breakdown.Reactions.Reason = "🌟 Popular ($($score.RawReactions) reactions, $reactionPercent% of scoring ceiling)"
    }

    $hasNeedsTriage = Test-HasLabel -Labels $Issue.labels -LabelName "needs-triage"
    if ($score.RawAge -gt $thresholds.aging_days -and $hasNeedsTriage) {
        $agePercent = [math]::Round(($score.AgeRank * 100), 0)
        $breakdown.Age.Reason = "⏰ Aging (needs triage for $($score.RawAge) days, $agePercent% of scoring ceiling)"
    }
    elseif ($score.RawAge -gt 0) {
        $breakdown.Age.Reason = "Open for $($score.RawAge) days"
    }

    if ($score.RawComments -ge $thresholds.trending_comments -and $score.RawUpdateAgeDays -le $thresholds.trending_days) {
        $commentPercent = [math]::Round(($score.CommentsRank * 100), 0)
        $breakdown.Comments.Reason = "📈 Trending ($($score.RawComments) comments, $commentPercent% of scoring ceiling; updated within $($thresholds.trending_days) days)"
    }

    if ($score.SeverityLabel) {
        switch ($score.SeverityLabel) {
            "critical" { $breakdown.Severity.Reason = "🔴 Critical (assessment)" }
            "high"     { $breakdown.Severity.Reason = "🟠 High (assessment)" }
            "medium"   { $breakdown.Severity.Reason = "🟡 Medium (assessment)" }
            "low"      { $breakdown.Severity.Reason = "🟢 Low (assessment)" }
            "none"     { $breakdown.Severity.Reason = "⚪ None (assessment)" }
        }
    }

    if ($score.IsBlocker -and $weights.blockers -gt 0) {
        $breakdown.Blockers.Reason = "🚧 Blocker issue"
    }

    $maxPossible = [math]::Round((
        $weights.reactions + $weights.age + $weights.comments +
        $weights.severity + $weights.blockers) * 100, 1)
    $bands = $Config.recommendationBands

    return @{
        Breakdown = $breakdown
        TotalScore = $score.Total
        MaxPossible = $maxPossible
        RecommendationThresholds = @{
            High   = [math]::Round($maxPossible * $bands.high, 1)
            Medium = [math]::Round($maxPossible * $bands.medium, 1)
            Normal = [math]::Round($maxPossible * $bands.normal, 1)
        }
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
        $score = [double]$data.Score
        $max = [double]$data.MaxScore
        $raw = $data.Raw
        $reason = $data.Reason
        $rank = [double]$data.Rank

        # Skip factors with 0 max score (disabled)
        if ($max -eq 0) { continue }

        $barFill = [math]::Min(10, [math]::Floor(($score / $max) * 10))
        $bar = "█" * $barFill
        $bar = $bar.PadRight(10, "░")

        $line = "  {0,-12} [{1}] {2}/{3}  (raw: {4})" -f $factor, $bar, $score.ToString('0.0'), $max.ToString('0.0'), $raw
        [void]$sb.AppendLine($line)

        if ($rank -gt 0) {
            [void]$sb.AppendLine("               ├─ normalized rank: $(([math]::Round(($rank * 100), 0)).ToString('0'))%")
        }

        if ($reason) {
            [void]$sb.AppendLine("               └─ $reason")
        }
    }

    [void]$sb.AppendLine("  ───────────────────────────────────────────────────────")
    [void]$sb.AppendLine("  TOTAL SCORE: $($ScoreResult.TotalScore.ToString('0.0')) / $($ScoreResult.MaxPossible.ToString('0.0'))")
    [void]$sb.AppendLine("")
    [void]$sb.AppendLine("  Scale: Normalized composite (0 to $($ScoreResult.MaxPossible) points)")
    [void]$sb.AppendLine("")

    # Highlight recommendation
    $score = $ScoreResult.TotalScore
    $rec = $ScoreResult.RecommendationThresholds
    $recommendation = if ($score -ge $rec.High) {
        "🔴 HIGH PRIORITY - Should be highlighted in triage report"
    }
    elseif ($score -ge $rec.Medium) {
        "🟡 MEDIUM PRIORITY - Consider for triage discussion"
    }
    elseif ($score -ge $rec.Normal) {
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
$scoreResult = Get-DetailedIssueScore -Issue $issue -Config $Config -IssueAssessments $IssueAssessments

# Output
if ($VerbosePreference -eq "Continue" -or $PSBoundParameters.ContainsKey('Verbose')) {
    $output = Format-ScoreBreakdown -ScoreResult $scoreResult -Issue $issue
    Write-Output $output
}
else {
    # Simple output
    Write-Host ""
    Write-Host "Issue #$($IssueNumber) Score: $($scoreResult.TotalScore.ToString('0.0')) / $($scoreResult.MaxPossible.ToString('0.0')) (normalized)" -ForegroundColor Green
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
