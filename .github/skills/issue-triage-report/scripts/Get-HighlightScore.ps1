# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Calculates the highlight score for a specific GitHub issue.

.DESCRIPTION
    This script fetches issue details and calculates a priority score (0-100)
    based on multiple factors including reactions, age, comments, severity,
    and external contributor status.

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
        Calculates detailed score breakdown for an issue.
    #>
    param(
        [object]$Issue,
        [hashtable]$Config
    )

    $weights = $Config.weights
    $thresholds = $Config.thresholds

    $breakdown = @{
        Reactions = @{ Raw = 0; Score = 0; MaxScore = $weights.reactions; Reason = "" }
        Age = @{ Raw = 0; Score = 0; MaxScore = $weights.age; Reason = "" }
        Comments = @{ Raw = 0; Score = 0; MaxScore = $weights.comments; Reason = "" }
        External = @{ Raw = $false; Score = 0; MaxScore = $weights.external; Reason = "" }
        Severity = @{ Raw = ""; Score = 0; MaxScore = $weights.severity; Reason = "" }
        Blockers = @{ Raw = $false; Score = 0; MaxScore = $weights.blockers; Reason = "" }
    }

    # 1. Reactions
    $totalReactions = Get-TotalReactions -ReactionGroups $Issue.reactionGroups
    $breakdown.Reactions.Raw = $totalReactions

    $breakdown.Reactions.Score = switch ($totalReactions) {
        { $_ -ge 50 } { $weights.reactions; break }
        { $_ -ge 20 } { [math]::Floor($weights.reactions * 0.8); break }
        { $_ -ge 10 } { [math]::Floor($weights.reactions * 0.6); break }
        { $_ -ge 5 }  { [math]::Floor($weights.reactions * 0.4); break }
        { $_ -ge 1 }  { [math]::Floor($weights.reactions * 0.2); break }
        default { 0 }
    }

    if ($totalReactions -ge $thresholds.hot_reactions) {
        $breakdown.Reactions.Reason = "🔥 Hot (high community interest)"
    }
    elseif ($totalReactions -ge 5) {
        $breakdown.Reactions.Reason = "Notable community interest"
    }

    # 2. Age
    $ageInDays = Get-IssueAgeInDays -CreatedAt $Issue.createdAt
    $breakdown.Age.Raw = $ageInDays

    $breakdown.Age.Score = switch ($ageInDays) {
        { $_ -ge 181 } { $weights.age; break }
        { $_ -ge 91 }  { [math]::Floor($weights.age * 0.75); break }
        { $_ -ge 61 }  { [math]::Floor($weights.age * 0.5); break }
        { $_ -ge 31 }  { [math]::Floor($weights.age * 0.25); break }
        default { 0 }
    }

    $hasNeedsTriage = Test-HasLabel -Labels $Issue.labels -LabelName "needs-triage"
    if ($ageInDays -gt $thresholds.aging_days -and $hasNeedsTriage) {
        $breakdown.Age.Reason = "⏰ Aging (needs triage for $ageInDays days)"
    }
    elseif ($ageInDays -gt $thresholds.aging_days) {
        $breakdown.Age.Reason = "Open for $ageInDays days"
    }

    # 3. Comments
    $commentCount = if ($Issue.comments) { $Issue.comments.Count } else { 0 }
    $breakdown.Comments.Raw = $commentCount

    $breakdown.Comments.Score = switch ($commentCount) {
        { $_ -ge 11 } { $weights.comments; break }
        { $_ -ge 6 }  { [math]::Floor($weights.comments * 0.67); break }
        { $_ -ge 3 }  { [math]::Floor($weights.comments * 0.4); break }
        { $_ -ge 1 }  { [math]::Floor($weights.comments * 0.2); break }
        default { 0 }
    }

    if ($commentCount -ge $thresholds.trending_comments) {
        $breakdown.Comments.Reason = "📈 Trending ($commentCount comments recently)"
    }

    # 4. External contributor
    $authorLogin = $Issue.author.login
    # Simple heuristic - in production, would check org membership via API
    $isExternal = -not ($authorLogin -match "^(microsoft|msft|azure|dotnet)-" -or $authorLogin -match "bot$")
    $breakdown.External.Raw = $isExternal

    if ($isExternal) {
        $breakdown.External.Score = [math]::Floor($weights.external * 0.67)
        $breakdown.External.Reason = "👥 External contributor (@$authorLogin)"
    }

    # 5. Severity
    $severityLabel = ""
    if (Test-HasLabel -Labels $Issue.labels -LabelName "regression") {
        $severityLabel = "regression"
        $breakdown.Severity.Score = $weights.severity
        $breakdown.Severity.Reason = "🐛 Regression"
    }
    elseif (Test-HasLabelMatching -Labels $Issue.labels -Pattern "crash|hang|data-loss") {
        $severityLabel = "crash/hang"
        $breakdown.Severity.Score = [math]::Floor($weights.severity * 0.8)
        $breakdown.Severity.Reason = "Critical: crash/hang/data-loss"
    }
    elseif (Test-HasLabel -Labels $Issue.labels -LabelName "bug") {
        $severityLabel = "bug"
        $breakdown.Severity.Score = [math]::Floor($weights.severity * 0.53)
        $breakdown.Severity.Reason = "Bug report"
    }
    elseif (Test-HasLabel -Labels $Issue.labels -LabelName "performance") {
        $severityLabel = "performance"
        $breakdown.Severity.Score = [math]::Floor($weights.severity * 0.4)
        $breakdown.Severity.Reason = "Performance issue"
    }
    $breakdown.Severity.Raw = $severityLabel

    # 6. Blockers
    $isBlocker = Test-HasLabelMatching -Labels $Issue.labels -Pattern "block|blocker|blocking"
    $breakdown.Blockers.Raw = $isBlocker

    if ($isBlocker) {
        $breakdown.Blockers.Score = $weights.blockers
        $breakdown.Blockers.Reason = "🚧 Blocker issue"
    }

    # Calculate total
    $totalScore = $breakdown.Reactions.Score + $breakdown.Age.Score +
                  $breakdown.Comments.Score + $breakdown.External.Score +
                  $breakdown.Severity.Score + $breakdown.Blockers.Score

    return @{
        Breakdown = $breakdown
        TotalScore = $totalScore
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

    foreach ($factor in @("Reactions", "Age", "Comments", "External", "Severity", "Blockers")) {
        $data = $breakdown[$factor]
        $score = $data.Score
        $max = $data.MaxScore
        $raw = $data.Raw
        $reason = $data.Reason

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

Write-Host "Fetching issue #$IssueNumber from $Repo..." -ForegroundColor Cyan

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
    Write-Error "Failed to fetch issue #$IssueNumber: $issueJson"
    exit 1
}

$issue = $issueJson | ConvertFrom-Json

if ($issue.state -ne "OPEN") {
    Write-Warning "Note: Issue #$IssueNumber is $($issue.state.ToLower()), not open."
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
    Write-Host "Issue #$IssueNumber Score: $($scoreResult.TotalScore)/100" -ForegroundColor Green
    Write-Host ""

    # Show top contributing factors
    $breakdown = $scoreResult.Breakdown
    $factors = @()
    foreach ($factor in @("Reactions", "Age", "Comments", "External", "Severity", "Blockers")) {
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
