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
        Loads the scoring configuration from ScoringConfig.json (failfast, no defaults).

    .DESCRIPTION
        All required fields must be present in the JSON file. Throws if any
        required section or field is missing.
    #>
    param(
        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        [string]$ConfigPath
    )

    # Validate config file exists
    if (-not (Test-Path -LiteralPath $ConfigPath -PathType Leaf)) {
        throw "Scoring config file not found: $ConfigPath"
    }

    # Validate JSON structure and correct filename
    if ([System.IO.Path]::GetFileName($ConfigPath) -cne "ScoringConfig.json") {
        throw "ConfigPath must point to ScoringConfig.json. Got: $ConfigPath"
    }

    $loaded = Get-Content $ConfigPath -Raw | ConvertFrom-Json

    # --- Validate required top-level sections ---
    foreach ($section in @("weights", "thresholds", "maxLabelsPerIssue", "severityLabels")) {
        if ($null -eq $loaded.$section) {
            throw "ScoringConfig.json missing required section: '$section'"
        }
    }

    # --- Validate required weight fields ---
    foreach ($field in @("reactions", "age", "comments", "severity", "blockers")) {
        if ($null -eq $loaded.weights.$field) {
            throw "ScoringConfig.json 'weights' missing required field: '$field'"
        }
    }

    # --- Validate required threshold fields ---
    foreach ($field in @("aging_days", "trending_comments", "trending_days", "popular_reactions")) {
        if ($null -eq $loaded.thresholds.$field) {
            throw "ScoringConfig.json 'thresholds' missing required field: '$field'"
        }
    }

    # --- Validate required severity label levels ---
    foreach ($level in @("critical", "high", "medium", "low")) {
        if ($null -eq $loaded.severityLabels.$level) {
            throw "ScoringConfig.json 'severityLabels' missing required level: '$level'"
        }
    }

    # --- Build config hashtable entirely from loaded values (no defaults) ---
    $config = @{
        weights = @{
            reactions = [int]$loaded.weights.reactions
            age       = [int]$loaded.weights.age
            comments  = [int]$loaded.weights.comments
            severity  = [int]$loaded.weights.severity
            blockers  = [int]$loaded.weights.blockers
        }
        thresholds = @{
            aging_days        = [int]$loaded.thresholds.aging_days
            trending_comments = [int]$loaded.thresholds.trending_comments
            trending_days     = [int]$loaded.thresholds.trending_days
            popular_reactions = [int]$loaded.thresholds.popular_reactions
        }
        maxLabelsPerIssue = [int]$loaded.maxLabelsPerIssue
        severityLabels = @{
            critical = @($loaded.severityLabels.critical)
            high     = @($loaded.severityLabels.high)
            medium   = @($loaded.severityLabels.medium)
            low      = @($loaded.severityLabels.low)
        }
    }

    if ($loaded.labelPriority) {
        $config.labelPriority = @($loaded.labelPriority)
    }

    return $config
}


function Get-AreaContacts {
    <#
    .SYNOPSIS
        Loads the area-to-contact mapping from JSON file (failfast, no defaults).

    .DESCRIPTION
        Loads contacts from the specified path. Throws if the file is missing,
        malformed, or if any area entry lacks a required 'contact' field.

        Users should create their own area-contacts.json file at:
        <repo-root>/.user/issue-triage-report/area-contacts.json

        See the template at:
        .github/skills/issue-triage-report/references/area-contacts.json

        Schema uses a single "contact" field per area.
    #>
    param(
        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        [string]$ContactsPath
    )

    # Validate contacts file exists
    if (-not (Test-Path -LiteralPath $ContactsPath -PathType Leaf)) {
        throw "Area contacts file not found: $ContactsPath. Please create your contacts file at: <repo-root>/.user/issue-triage-report/area-contacts.json. See template at: .github/skills/issue-triage-report/references/area-contacts.json"
    }

    $loaded = Get-Content $ContactsPath -Raw | ConvertFrom-Json

    if (-not $loaded.areaContacts) {
        throw "Area contacts file missing required 'areaContacts' section: $ContactsPath"
    }

    # Convert PSObject to hashtable for PS 5.1 compatibility
    # (ConvertFrom-Json -AsHashtable is only available in PS 6.0+)
    $hashtable = @{}
    foreach ($prop in $loaded.areaContacts.PSObject.Properties) {
        if (-not $prop.Value.contact) {
            throw "Area '$($prop.Name)' missing required 'contact' field in: $ContactsPath"
        }

        $notes = $null
        if ($prop.Value.PSObject.Properties.Name -contains "notes") {
            $notes = $prop.Value.notes
        }

        $hashtable[$prop.Name] = @{
            contact = $prop.Value.contact
            notes = $notes
        }
    }
    return $hashtable
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
        RawUpdateAgeDays = 0
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

    # Days since last update (for trending recency check)
    if ($Issue.updatedAt) {
        try {
            $updated = [datetime]$Issue.updatedAt
            $score.RawUpdateAgeDays = ([datetime]::UtcNow - $updated).Days
        } catch {
            $score.RawUpdateAgeDays = [int]::MaxValue
        }
    } else {
        $score.RawUpdateAgeDays = [int]::MaxValue
    }

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

    # 4. Severity score - use configurable severity labels
    $labelNames = @()
    if ($Issue.labels) {
        $labelNames = @($Issue.labels | ForEach-Object { $_.name })
    }

    # Severity labels must be provided by config (no defaults)
    if (-not $Config.severityLabels) {
        throw "Config missing required 'severityLabels'. Ensure ScoringConfig.json is loaded via Get-ScoringConfig."
    }
    $severityLabels = $Config.severityLabels

    # Check for critical severity labels (100% of severity weight)
    $hasCritical = $false
    foreach ($critLabel in $severityLabels.critical) {
        if ($labelNames -contains $critLabel) {
            $score.Severity = $weights.severity
            $score.SeverityLabel = $critLabel
            $hasCritical = $true
            break
        }
    }

    if (-not $hasCritical) {
        # Check for high severity labels (80% of severity weight)
        $hasHigh = $false
        foreach ($highLabel in $severityLabels.high) {
            if ($labelNames -contains $highLabel) {
                $score.Severity = [math]::Floor($weights.severity * 0.8)
                $score.SeverityLabel = $highLabel
                $hasHigh = $true
                break
            }
        }

        if (-not $hasHigh) {
            # Check for medium severity labels (50% of severity weight)
            $hasMedium = $false
            foreach ($medLabel in $severityLabels.medium) {
                if ($labelNames -contains $medLabel) {
                    $score.Severity = [math]::Floor($weights.severity * 0.5)
                    $score.SeverityLabel = $medLabel
                    $hasMedium = $true
                    break
                }
            }

            if (-not $hasMedium) {
                # Check for low severity labels (20% of severity weight)
                foreach ($lowLabel in $severityLabels.low) {
                    if ($labelNames -contains $lowLabel) {
                        $score.Severity = [math]::Floor($weights.severity * 0.2)
                        $score.SeverityLabel = $lowLabel
                        break
                    }
                }
            }
        }
    }

    # 5. Blocker score (only if weight > 0)
    $hasBlocker = @($labelNames | Where-Object { $_ -match "block" }).Count -gt 0
    $score.IsBlocker = $hasBlocker
    if ($hasBlocker -and $weights.blockers -gt 0) {
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
        [array] Array of highlight label strings (e.g., "🌟 Popular", "⏰ Aging").
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
    # Consolidated Popular label (replaces both Hot and old Popular)
    if ($Score.RawReactions -ge $thresholds.popular_reactions) {
        $labels += "🌟 Popular"
    }
    if ($Score.RawAge -gt $thresholds.aging_days -and $labelNames -contains "needs-triage") {
        $labels += "⏰ Aging"
    }
    if ($Score.RawComments -ge $thresholds.trending_comments -and $Score.RawUpdateAgeDays -le $thresholds.trending_days) {
        $labels += "📈 Trending"
    }

    # Return only top N labels
    return $labels | Select-Object -First $maxLabels
}

