# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Generates a comprehensive GitHub Feature Area Status report for Windows App SDK.

.DESCRIPTION
    This script fetches all open issues from the specified GitHub repository,
    groups them by feature area labels, calculates highlight scores, and generates
    a formatted report showing issue counts and priority highlights.

.PARAMETER Repo
    Repository in 'owner/repo' format. Default: microsoft/WindowsAppSDK

.PARAMETER OutputFormat
    Output format: 'markdown', 'csv', or 'json'. Default: markdown

.PARAMETER HighlightCount
    Maximum number of highlighted issues per area. Default: 3

.PARAMETER IncludeClosed
    Include count of recently closed issues (last 30 days).

.PARAMETER ConfigPath
    Path to ScoringConfig.json. Default: script directory.

.EXAMPLE
    ./Generate-FeatureAreaReport.ps1 -OutputFormat markdown

.EXAMPLE
    ./Generate-FeatureAreaReport.ps1 -Repo "microsoft/WindowsAppSDK" -HighlightCount 5 -IncludeClosed
#>

[CmdletBinding()]
param(
    [Parameter()]
    [string]$Repo = "microsoft/WindowsAppSDK",

    [Parameter()]
    [ValidateSet("markdown", "csv", "json")]
    [string]$OutputFormat = "markdown",

    [Parameter()]
    [int]$HighlightCount = 3,

    [Parameter()]
    [switch]$IncludeClosed,

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

# Load area contacts
$ContactsPath = Join-Path (Split-Path $ScriptDir -Parent) "references\area-contacts.json"
$AreaContacts = Get-AreaContacts -ContactsPath $ContactsPath

function Get-AllAreaLabels {
    <#
    .SYNOPSIS
        Fetches all labels starting with "area-" from the repository.
    #>
    param([string]$Repository)

    Write-Verbose "Fetching area labels from $Repository..."
    $labels = gh label list --repo $Repository --search "area-" --json name --limit 100 | ConvertFrom-Json
    return $labels | ForEach-Object { $_.name } | Sort-Object
}

function Get-IssuesForArea {
    <#
    .SYNOPSIS
        Fetches all open issues for a specific area label.
    #>
    param(
        [string]$Repository,
        [string]$AreaLabel,
        [switch]$GetClosed
    )

    $state = if ($GetClosed) { "closed" } else { "open" }
    Write-Verbose "Fetching $state issues for $AreaLabel..."

    $jsonFields = "number,title,createdAt,updatedAt,labels,reactionGroups,comments,author,state"

    $issues = gh issue list --repo $Repository --label $AreaLabel --state $state --limit 500 --json $jsonFields 2>$null | ConvertFrom-Json

    return $issues
}

function Get-IssueStats {
    <#
    .SYNOPSIS
        Calculates statistics for a set of issues.
    #>
    param(
        [array]$Issues,
        [hashtable]$Config
    )

    $issueArray = @($Issues)
    $stats = @{
        Total = $issueArray.Count
        NeedsTriage = 0
        FeatureProposals = 0
        Bugs = 0
    }

    foreach ($issue in $issueArray) {
        if (-not $issue) { continue }
        $labelNames = @()
        if ($issue.labels) {
            $labelNames = @($issue.labels | ForEach-Object { $_.name })
        }

        if ($labelNames -contains "needs-triage") {
            $stats.NeedsTriage++
        }
        if ($labelNames -contains "feature proposal" -or $labelNames -contains "feature-proposal") {
            $stats.FeatureProposals++
        }
        if ($labelNames -contains "bug") {
            $stats.Bugs++
        }
    }

    return $stats
}

function Get-HighlightedIssues {
    <#
    .SYNOPSIS
        Identifies and scores the most important issues to highlight.
    #>
    param(
        [array]$Issues,
        [hashtable]$Config,
        [int]$MaxHighlights
    )

    $scoredIssues = @()

    foreach ($issue in $Issues) {
        $score = Get-IssueScore -Issue $issue -Config $Config
        $labels = Get-HighlightLabels -Issue $issue -Score $score -Config $Config

        $scoredIssues += @{
            Number = $issue.number
            Title = $issue.title
            Score = $score.Total
            Labels = $labels
            ScoreBreakdown = $score
        }
    }

    # Sort by score descending and take top N
    $highlights = $scoredIssues | Sort-Object { $_.Score } -Descending | Select-Object -First $MaxHighlights

    return $highlights
}

function Get-IssueScore {
    <#
    .SYNOPSIS
        Calculates the highlight score for a single issue.
    #>
    param(
        [object]$Issue,
        [hashtable]$Config
    )

    $weights = $Config.weights
    $thresholds = $Config.thresholds

    $score = @{
        Reactions = 0
        Age = 0
        Comments = 0
        External = 0
        Severity = 0
        Blockers = 0
        Total = 0
    }

    # 1. Reactions score
    $totalReactions = 0
    if ($Issue.reactionGroups -and $Issue.reactionGroups.Count -gt 0) {
        foreach ($rg in $Issue.reactionGroups) {
            if ($null -ne $rg.users) {
                if ($rg.users -is [System.Collections.ICollection]) {
                    $totalReactions += $rg.users.Count
                } elseif ($rg.users.totalCount) {
                    $totalReactions += [int]$rg.users.totalCount
                }
            }
        }
    }

    $score.Reactions = switch ([int]$totalReactions) {
        { $_ -ge 50 } { $weights.reactions; break }
        { $_ -ge 20 } { [math]::Floor($weights.reactions * 0.8); break }
        { $_ -ge 10 } { [math]::Floor($weights.reactions * 0.6); break }
        { $_ -ge 5 }  { [math]::Floor($weights.reactions * 0.4); break }
        { $_ -ge 1 }  { [math]::Floor($weights.reactions * 0.2); break }
        default { 0 }
    }

    # 2. Age score
    $createdAt = [datetime]$Issue.createdAt
    $ageInDays = ([datetime]::Now - $createdAt).Days

    $score.Age = switch ($ageInDays) {
        { $_ -ge 181 } { $weights.age; break }
        { $_ -ge 91 }  { [math]::Floor($weights.age * 0.75); break }
        { $_ -ge 61 }  { [math]::Floor($weights.age * 0.5); break }
        { $_ -ge 31 }  { [math]::Floor($weights.age * 0.25); break }
        default { 0 }
    }

    # 3. Comments score
    $commentCount = if ($Issue.comments) { $Issue.comments.Count } else { 0 }

    $score.Comments = switch ($commentCount) {
        { $_ -ge 11 } { $weights.comments; break }
        { $_ -ge 6 }  { [math]::Floor($weights.comments * 0.67); break }
        { $_ -ge 3 }  { [math]::Floor($weights.comments * 0.4); break }
        { $_ -ge 1 }  { [math]::Floor($weights.comments * 0.2); break }
        default { 0 }
    }

    # 4. External contributor score
    $authorLogin = if ($Issue.author) { $Issue.author.login } else { "" }
    $isExternal = -not (Test-IsMicrosoftMember -Login $authorLogin)
    if ($isExternal -and $authorLogin) {
        $score.External = [math]::Floor($weights.external * 0.67)
    }

    # 5. Severity score
    $labelNames = @()
    if ($Issue.labels) {
        $labelNames = @($Issue.labels | ForEach-Object { $_.name })
    }

    if ($labelNames -contains "regression") {
        $score.Severity = $weights.severity
    }
    else {
        $hasCrash = @($labelNames | Where-Object { $_ -match "crash|hang|data-loss" }).Count -gt 0
        if ($hasCrash) {
            $score.Severity = [math]::Floor($weights.severity * 0.8)
        }
        elseif ($labelNames -contains "bug") {
            $score.Severity = [math]::Floor($weights.severity * 0.53)
        }
        elseif ($labelNames -contains "performance") {
            $score.Severity = [math]::Floor($weights.severity * 0.4)
        }
    }

    # 6. Blocker score
    $hasBlocker = @($labelNames | Where-Object { $_ -match "block|blocker|blocking" }).Count -gt 0
    if ($hasBlocker) {
        $score.Blockers = $weights.blockers
    }

    # Calculate total
    $score.Total = [int]$score.Reactions + [int]$score.Age + [int]$score.Comments +
                   [int]$score.External + [int]$score.Severity + [int]$score.Blockers

    return $score
}

function Get-HighlightLabels {
    <#
    .SYNOPSIS
        Determines which highlight labels to apply based on score factors.
    #>
    param(
        [object]$Issue,
        [hashtable]$Score,
        [hashtable]$Config
    )

    $labels = @()
    $thresholds = $Config.thresholds
    $maxLabels = $Config.maxLabelsPerIssue

    $labelNames = @()
    if ($Issue.labels) {
        $labelNames = @($Issue.labels | ForEach-Object { $_.name })
    }
    
    $totalReactions = 0
    if ($Issue.reactionGroups -and $Issue.reactionGroups.Count -gt 0) {
        foreach ($rg in $Issue.reactionGroups) {
            if ($null -ne $rg.users) {
                if ($rg.users -is [System.Collections.ICollection]) {
                    $totalReactions += $rg.users.Count
                } elseif ($rg.users.totalCount) {
                    $totalReactions += [int]$rg.users.totalCount
                }
            }
        }
    }

    $createdAt = [datetime]$Issue.createdAt
    $ageInDays = ([datetime]::Now - $createdAt).Days

    $commentCount = 0
    if ($null -ne $Issue.comments) {
        if ($Issue.comments -is [System.Collections.ICollection]) {
            $commentCount = $Issue.comments.Count
        }
    }

    # Check conditions in priority order
    if ($labelNames -contains "regression") {
        $labels += "🐛 Regression"
    }
    $hasBlocker = @($labelNames | Where-Object { $_ -match "block|blocker|blocking" }).Count -gt 0
    if ($hasBlocker) {
        $labels += "🚧 Blocker"
    }
    if ($totalReactions -ge $thresholds.hot_reactions) {
        $labels += "🔥 Hot"
    }
    if ($ageInDays -gt $thresholds.aging_days -and $labelNames -contains "needs-triage") {
        $labels += "⏰ Aging"
    }
    if ($commentCount -ge $thresholds.trending_comments) {
        $labels += "📈 Trending"
    }

    $authorLogin = if ($Issue.author) { $Issue.author.login } else { "" }
    $isExternal = -not (Test-IsMicrosoftMember -Login $authorLogin)
    if ($isExternal -and $authorLogin) {
        $labels += "👥 External"
    }

    $hasFeatureProposal = $labelNames -contains "feature proposal" -or $labelNames -contains "feature-proposal"
    if ($hasFeatureProposal -and $totalReactions -ge $thresholds.popular_reactions) {
        $labels += "📢 Popular"
    }

    # Return only top N labels
    return $labels | Select-Object -First $maxLabels
}

function Test-IsMicrosoftMember {
    <#
    .SYNOPSIS
        Checks if a GitHub user is a Microsoft organization member.
        Note: This is a heuristic - may need refinement.
    #>
    param([string]$Login)

    # Simple heuristic: check if user is in known Microsoft users or has @microsoft email
    # In practice, you might query the GitHub API for org membership
    # For now, assume non-bot accounts might be external
    if ($Login -match "^(microsoft|msft|azure|dotnet)-") {
        return $true
    }
    if ($Login -match "bot$") {
        return $true
    }

    # Default: cannot determine, assume potentially external
    return $false
}

function Format-HighlightsMarkdown {
    <#
    .SYNOPSIS
        Formats highlighted issues as markdown links with labels.
    #>
    param(
        [array]$Highlights,
        [string]$Repository
    )

    if (-not $Highlights -or @($Highlights).Count -eq 0) {
        return "-"
    }

    $parts = @()
    foreach ($h in $Highlights) {
        $labelArray = @($h.Labels)
        $label = if ($labelArray.Count -gt 0) { $labelArray[0] } else { "" }
        $link = "[#$($h.Number)](https://github.com/$Repository/issues/$($h.Number))"
        if ($label) {
            $parts += "$label $link"
        } else {
            $parts += $link
        }
    }

    return $parts -join ", "
}

function Format-ReportMarkdown {
    <#
    .SYNOPSIS
        Generates the final markdown report.
    #>
    param(
        [array]$AreaReports,
        [string]$Repository,
        [switch]$IncludeClosed
    )

    $sb = [System.Text.StringBuilder]::new()

    [void]$sb.AppendLine("# GitHub Feature Area Status")
    [void]$sb.AppendLine()
    [void]$sb.AppendLine("> Generated: $(Get-Date -Format 'yyyy-MM-dd HH:mm') UTC")
    [void]$sb.AppendLine("> Repository: [$Repository](https://github.com/$Repository)")
    [void]$sb.AppendLine()

    # Table header
    $header = "| Feature Area | Area Contact | Open Issues | Needs Triage | Feature Proposals |"
    $separator = "|--------------|--------------|-------------|--------------|-------------------|"

    if ($IncludeClosed) {
        $header += " Closed (30d) |"
        $separator += "--------------|"
    }

    $header += " Additional Highlights |"
    $separator += "-----------------------|"

    [void]$sb.AppendLine($header)
    [void]$sb.AppendLine($separator)

    # Table rows
    foreach ($area in $AreaReports) {
        $row = "| [$($area.AreaLabel)](https://github.com/$Repository/labels/$([uri]::EscapeDataString($area.AreaLabel))) "
        $row += "| $($area.Contact) "
        $row += "| $($area.Stats.Total) "
        $row += "| $($area.Stats.NeedsTriage) "
        $row += "| $($area.Stats.FeatureProposals) "

        if ($IncludeClosed) {
            $row += "| $($area.ClosedCount) "
        }

        # Special case: zero bugs celebration
        if ($area.Stats.Total -eq 0 -and $area.Stats.Bugs -eq 0) {
            $row += "| 0️⃣🐛🥳 |"
        }
        # Special case: external area
        elseif ($area.AreaLabel -eq "area-External") {
            $row += "| N/A (redirect backlog) |"
        }
        else {
            $row += "| $($area.Highlights) |"
        }

        [void]$sb.AppendLine($row)
    }

    return $sb.ToString()
}

# ============================================================================
# Main Execution
# ============================================================================

Write-Host "Generating Feature Area Status Report for $Repo..." -ForegroundColor Cyan
Write-Host ""

# Verify GitHub CLI is available and authenticated
try {
    $null = gh auth status 2>&1
}
catch {
    Write-Error "GitHub CLI not authenticated. Run 'gh auth login' first."
    exit 1
}

# Get all area labels
$areaLabels = Get-AllAreaLabels -Repository $Repo
Write-Host "Found $($areaLabels.Count) feature area labels" -ForegroundColor Green

$areaReports = @()

foreach ($areaLabel in $areaLabels) {
    Write-Host "  Processing $areaLabel..." -ForegroundColor Gray

    # Get open issues
    $openIssues = Get-IssuesForArea -Repository $Repo -AreaLabel $areaLabel

    # Get closed issues if requested
    $closedCount = "-"
    if ($IncludeClosed) {
        $closedIssues = Get-IssuesForArea -Repository $Repo -AreaLabel $areaLabel -GetClosed
        # Filter to last 30 days
        $thirtyDaysAgo = (Get-Date).AddDays(-30)
        $recentlyClosed = $closedIssues | Where-Object {
            [datetime]$_.updatedAt -gt $thirtyDaysAgo
        }
        $closedCount = $recentlyClosed.Count
    }

    # Calculate stats
    $stats = Get-IssueStats -Issues $openIssues -Config $Config

    # Get highlights
    $highlights = Get-HighlightedIssues -Issues $openIssues -Config $Config -MaxHighlights $HighlightCount
    $highlightsFormatted = Format-HighlightsMarkdown -Highlights $highlights -Repository $Repo

    # Get contact
    $contact = if ($AreaContacts[$areaLabel]) {
        $c = $AreaContacts[$areaLabel]
        if ($c.secondary) { "$($c.primary), $($c.secondary)" } else { $c.primary }
    } else {
        "TBD"
    }

    $areaReports += @{
        AreaLabel = $areaLabel
        Contact = $contact
        Stats = $stats
        ClosedCount = $closedCount
        Highlights = $highlightsFormatted
    }
}

# Sort by area label
$areaReports = $areaReports | Sort-Object { $_.AreaLabel }

# Generate output
switch ($OutputFormat) {
    "markdown" {
        $report = Format-ReportMarkdown -AreaReports $areaReports -Repository $Repo -IncludeClosed:$IncludeClosed
        Write-Output $report
    }
    "json" {
        $areaReports | ConvertTo-Json -Depth 10
    }
    "csv" {
        $csvData = $areaReports | ForEach-Object {
            [PSCustomObject]@{
                FeatureArea = $_.AreaLabel
                Contact = $_.Contact
                OpenIssues = $_.Stats.Total
                NeedsTriage = $_.Stats.NeedsTriage
                FeatureProposals = $_.Stats.FeatureProposals
                Highlights = $_.Highlights
            }
        }
        $csvData | ConvertTo-Csv -NoTypeInformation
    }
}

Write-Host ""
Write-Host "Report generation complete!" -ForegroundColor Green
