# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Shared library functions for the Issue Triage Report skill.

.DESCRIPTION
    Contains common functions used by multiple scripts in the skill.
#>

function Get-ScoringConfig {
    <#
    .SYNOPSIS
        Loads the scoring configuration from JSON file or returns defaults.
    #>
    param(
        [string]$ConfigPath
    )

    $defaultConfig = @{
        weights = @{
            reactions = 30
            age = 25
            comments = 20
            severity = 15
            blockers = 10
        }
        thresholds = @{
            hot_reactions = 10
            aging_days = 90
            trending_comments = 5
            trending_days = 14
            popular_reactions = 5
        }
        labelPriority = @(
            "regression"
            "blocker"
            "hot"
            "aging"
            "trending"
            "popular"
        )
        maxLabelsPerIssue = 2
    }

    if ($ConfigPath -and (Test-Path $ConfigPath)) {
        try {
            $loaded = Get-Content $ConfigPath -Raw | ConvertFrom-Json
            # Merge weights
            if ($loaded.weights) {
                $defaultConfig.weights.reactions = [int]$loaded.weights.reactions
                $defaultConfig.weights.age = [int]$loaded.weights.age
                $defaultConfig.weights.comments = [int]$loaded.weights.comments
                $defaultConfig.weights.severity = [int]$loaded.weights.severity
                $defaultConfig.weights.blockers = [int]$loaded.weights.blockers
            }
            # Merge thresholds
            if ($loaded.thresholds) {
                $defaultConfig.thresholds.hot_reactions = [int]$loaded.thresholds.hot_reactions
                $defaultConfig.thresholds.aging_days = [int]$loaded.thresholds.aging_days
                $defaultConfig.thresholds.trending_comments = [int]$loaded.thresholds.trending_comments
                $defaultConfig.thresholds.trending_days = [int]$loaded.thresholds.trending_days
                $defaultConfig.thresholds.popular_reactions = [int]$loaded.thresholds.popular_reactions
            }
            if ($loaded.maxLabelsPerIssue) {
                $defaultConfig.maxLabelsPerIssue = [int]$loaded.maxLabelsPerIssue
            }
        }
        catch {
            Write-Warning "Failed to load config from $ConfigPath, using defaults: $_"
        }
    }

    return $defaultConfig
}

function Get-AreaContacts {
    <#
    .SYNOPSIS
        Loads the area-to-contact mapping from JSON file.

    .DESCRIPTION
        Loads contacts from the specified path. If no contacts file is found,
        returns an empty hashtable and writes a warning.

        Users should create their own area-contacts.json file at:
        <repo-root>/.user/issue-triage-report/area-contacts.json

        See the template at:
        .github/skills/issue-triage-report/references/area-contacts.json
    #>
    param(
        [string]$ContactsPath
    )

    if ($ContactsPath -and (Test-Path $ContactsPath)) {
        try {
            $loaded = Get-Content $ContactsPath -Raw | ConvertFrom-Json
            if ($loaded.areaContacts) {
                # Convert PSObject to hashtable for PS 5.1 compatibility
                # (ConvertFrom-Json -AsHashtable is only available in PS 6.0+)
                $hashtable = @{}
                foreach ($prop in $loaded.areaContacts.PSObject.Properties) {
                    $hashtable[$prop.Name] = @{
                        primary = $prop.Value.primary
                        secondary = $prop.Value.secondary
                    }
                }
                return $hashtable
            }
        }
        catch {
            Write-Warning "Failed to load contacts from $ContactsPath`: $_"
        }
    }
    else {
        Write-Warning "Area contacts file not found at: $ContactsPath"
        Write-Warning "Please create your contacts file at: <repo-root>/.user/issue-triage-report/area-contacts.json"
        Write-Warning "See template at: .github/skills/issue-triage-report/references/area-contacts.json"
    }

    return @{}
}

function Get-TotalReactions {
    <#
    .SYNOPSIS
        Calculates total reactions from GitHub reaction groups.
    #>
    param(
        [object]$ReactionGroups
    )

    $total = 0
    if ($ReactionGroups) {
        foreach ($rg in $ReactionGroups) {
            if ($rg.users -and $rg.users.totalCount) {
                $total += $rg.users.totalCount
            } elseif ($rg.users -is [array]) {
                $total += $rg.users.Count
            }
        }
    }
    return $total
}

function Get-IssueAgeInDays {
    <#
    .SYNOPSIS
        Calculates the age of an issue in days.
    #>
    param(
        [string]$CreatedAt
    )

    if (-not $CreatedAt) { return 0 }

    try {
        $created = [datetime]$CreatedAt
        return ([datetime]::UtcNow - $created).Days
    }
    catch {
        return 0
    }
}

function Test-HasLabel {
    <#
    .SYNOPSIS
        Checks if an issue has a specific label.
    #>
    param(
        [array]$Labels,
        [string]$LabelName
    )

    if (-not $Labels) { return $false }

    foreach ($label in $Labels) {
        if ($label.name -eq $LabelName) {
            return $true
        }
    }
    return $false
}

function Test-HasLabelMatching {
    <#
    .SYNOPSIS
        Checks if an issue has a label matching a pattern.
    #>
    param(
        [array]$Labels,
        [string]$Pattern
    )

    if (-not $Labels) { return $false }

    foreach ($label in $Labels) {
        if ($label.name -match $Pattern) {
            return $true
        }
    }
    return $false
}

function Format-IssueLink {
    <#
    .SYNOPSIS
        Formats an issue number as a markdown link.
    #>
    param(
        [int]$IssueNumber,
        [string]$Repository
    )

    return "[#$($IssueNumber)](https://github.com/$Repository/issues/$IssueNumber)"
}

function Write-ColoredStatus {
    <#
    .SYNOPSIS
        Writes status message with appropriate color coding.
    #>
    param(
        [string]$Message,
        [ValidateSet("Info", "Success", "Warning", "Error")]
        [string]$Level = "Info"
    )

    $color = switch ($Level) {
        "Info" { "Cyan" }
        "Success" { "Green" }
        "Warning" { "Yellow" }
        "Error" { "Red" }
    }

    Write-Host $Message -ForegroundColor $color
}

function Get-IssueScore {
    <#
    .SYNOPSIS
        Calculates the highlight score for a single issue.

    .DESCRIPTION
        This is the canonical scoring implementation used by both Generate-FeatureAreaReport.ps1
        and Get-HighlightScore.ps1 to ensure consistent scoring across the skill.

    .PARAMETER Issue
        The GitHub issue object with properties: reactionGroups, createdAt, comments, author, labels.

    .PARAMETER Config
        The scoring configuration hashtable containing weights and thresholds.

    .OUTPUTS
        [hashtable] Score breakdown with individual factor scores and total.
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
        Severity = 0
        Blockers = 0
        Total = 0
        # Additional metadata for detailed reporting
        RawReactions = 0
        RawAge = 0
        RawComments = 0
        SeverityLabel = ""
        IsBlocker = $false
    }

    # 1. Reactions score
    $totalReactions = Get-TotalReactions -ReactionGroups $Issue.reactionGroups
    $score.RawReactions = $totalReactions

    $score.Reactions = switch ([int]$totalReactions) {
        { $_ -ge 50 } { $weights.reactions; break }
        { $_ -ge 20 } { [math]::Floor($weights.reactions * 0.8); break }
        { $_ -ge 10 } { [math]::Floor($weights.reactions * 0.6); break }
        { $_ -ge 5 }  { [math]::Floor($weights.reactions * 0.4); break }
        { $_ -ge 1 }  { [math]::Floor($weights.reactions * 0.2); break }
        default { 0 }
    }

    # 2. Age score (use UTC for consistency)
    $ageInDays = Get-IssueAgeInDays -CreatedAt $Issue.createdAt
    $score.RawAge = $ageInDays

    $score.Age = switch ($ageInDays) {
        { $_ -ge 181 } { $weights.age; break }
        { $_ -ge 91 }  { [math]::Floor($weights.age * 0.75); break }
        { $_ -ge 61 }  { [math]::Floor($weights.age * 0.5); break }
        { $_ -ge 31 }  { [math]::Floor($weights.age * 0.25); break }
        default { 0 }
    }

    # 3. Comments score
    $commentCount = 0
    if ($Issue.comments) {
        if ($Issue.comments -is [System.Collections.ICollection]) {
            $commentCount = $Issue.comments.Count
        } elseif ($Issue.comments.totalCount) {
            $commentCount = [int]$Issue.comments.totalCount
        }
    }
    $score.RawComments = $commentCount

    $score.Comments = switch ($commentCount) {
        { $_ -ge 11 } { $weights.comments; break }
        { $_ -ge 6 }  { [math]::Floor($weights.comments * 0.67); break }
        { $_ -ge 3 }  { [math]::Floor($weights.comments * 0.4); break }
        { $_ -ge 1 }  { [math]::Floor($weights.comments * 0.2); break }
        default { 0 }
    }

    # 4. Severity score
    $labelNames = @()
    if ($Issue.labels) {
        $labelNames = @($Issue.labels | ForEach-Object { $_.name })
    }

    if ($labelNames -contains "regression") {
        $score.Severity = $weights.severity
        $score.SeverityLabel = "regression"
    }
    else {
        $hasCrash = @($labelNames | Where-Object { $_ -match "crash|hang|data-loss" }).Count -gt 0
        if ($hasCrash) {
            $score.Severity = [math]::Floor($weights.severity * 0.8)
            $score.SeverityLabel = "crash/hang"
        }
        elseif ($labelNames -contains "bug") {
            $score.Severity = [math]::Floor($weights.severity * 0.53)
            $score.SeverityLabel = "bug"
        }
        elseif ($labelNames -contains "performance") {
            $score.Severity = [math]::Floor($weights.severity * 0.4)
            $score.SeverityLabel = "performance"
        }
    }

    # 5. Blocker score
    $hasBlocker = @($labelNames | Where-Object { $_ -match "block|blocker|blocking" }).Count -gt 0
    $score.IsBlocker = $hasBlocker
    if ($hasBlocker) {
        $score.Blockers = $weights.blockers
    }

    # Calculate total
    $score.Total = [int]$score.Reactions + [int]$score.Age + [int]$score.Comments +
                   [int]$score.Severity + [int]$score.Blockers

    return $score
}

function Get-HighlightLabels {
    <#
    .SYNOPSIS
        Determines which highlight labels to apply based on score factors.

    .DESCRIPTION
        This is the canonical label assignment implementation used across the skill.

    .PARAMETER Issue
        The GitHub issue object.

    .PARAMETER Score
        The score hashtable from Get-IssueScore.

    .PARAMETER Config
        The scoring configuration hashtable.

    .OUTPUTS
        [array] Array of highlight label strings (e.g., "🔥 Hot", "⏰ Aging").
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

    # Check conditions in priority order
    if ($labelNames -contains "regression") {
        $labels += "🐛 Regression"
    }
    if ($Score.IsBlocker) {
        $labels += "🚧 Blocker"
    }
    if ($Score.RawReactions -ge $thresholds.hot_reactions) {
        $labels += "🔥 Hot"
    }
    if ($Score.RawAge -gt $thresholds.aging_days -and $labelNames -contains "needs-triage") {
        $labels += "⏰ Aging"
    }
    if ($Score.RawComments -ge $thresholds.trending_comments) {
        $labels += "📈 Trending"
    }

    $hasFeatureProposal = $labelNames -contains "feature proposal" -or $labelNames -contains "feature-proposal"
    if ($hasFeatureProposal -and $Score.RawReactions -ge $thresholds.popular_reactions) {
        $labels += "📢 Popular"
    }

    # Return only top N labels
    return $labels | Select-Object -First $maxLabels
}
