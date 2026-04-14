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
    foreach ($section in @("weights", "thresholds", "maxLabelsPerIssue", "severityMultipliers")) {
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

    # --- Validate required severity multiplier levels ---
    foreach ($level in @("critical", "high", "medium", "low", "none")) {
        if ($null -eq $loaded.severityMultipliers.$level) {
            throw "ScoringConfig.json 'severityMultipliers' missing required level: '$level'"
        }
    }

    # --- Build config hashtable entirely from loaded values (no defaults) ---
    $config = @{
        weights = @{
            reactions = [double]$loaded.weights.reactions
            age       = [double]$loaded.weights.age
            comments  = [double]$loaded.weights.comments
            severity  = [double]$loaded.weights.severity
            blockers  = [double]$loaded.weights.blockers
        }
        thresholds = @{
            aging_days        = [int]$loaded.thresholds.aging_days
            trending_comments = [int]$loaded.thresholds.trending_comments
            trending_days     = [int]$loaded.thresholds.trending_days
            popular_reactions = [int]$loaded.thresholds.popular_reactions
        }
        maxLabelsPerIssue = [int]$loaded.maxLabelsPerIssue
        severityMultipliers = @{
            critical = [double]$loaded.severityMultipliers.critical
            high     = [double]$loaded.severityMultipliers.high
            medium   = [double]$loaded.severityMultipliers.medium
            low      = [double]$loaded.severityMultipliers.low
            none     = [double]$loaded.severityMultipliers.none
        }
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

function Get-IssueAssessmentsPath {
    <#
    .SYNOPSIS
        Returns the fixed IssueAssessments.json path for this skill.
    #>
    param(
        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        [string]$ScriptDirectory
    )

    $skillDir = Split-Path $ScriptDirectory -Parent
    return (Join-Path $skillDir "references\IssueAssessments.json")
}

function Get-AgentAssessmentsPath {
    <#
    .SYNOPSIS
        Returns the fixed AgentAssessments.json path for this skill.
    #>
    param(
        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        [string]$ScriptDirectory
    )

    $skillDir = Split-Path $ScriptDirectory -Parent
    return (Join-Path $skillDir "references\AgentAssessments.json")
}

function Read-IssueAssessments {
    <#
    .SYNOPSIS
        Loads IssueAssessments.json from the fixed skill path.

    .DESCRIPTION
        Returns an issue-number keyed hashtable. Missing file or malformed data
        does not terminate execution; the caller can safely fall back.
    #>
    param(
        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        [string]$ScriptDirectory,

        [switch]$EmitStatus
    )

    $assessmentsPath = Get-IssueAssessmentsPath -ScriptDirectory $ScriptDirectory

    if (-not (Test-Path -LiteralPath $assessmentsPath -PathType Leaf)) {
        if ($EmitStatus) {
            Write-ColoredStatus -Level "Warning" -Message "IssueAssessments.json not found at $assessmentsPath. Using fallback severity/blocker behavior."
        }
        return @{}
    }

    if ($EmitStatus) {
        Write-ColoredStatus -Level "Info" -Message "IssueAssessments.json found at $assessmentsPath"
    }

    try {
        $loaded = Get-Content -LiteralPath $assessmentsPath -Raw | ConvertFrom-Json
    }
    catch {
        Write-Warning "IssueAssessments.json could not be parsed at $assessmentsPath. Using fallback severity/blocker behavior. Error: $_"
        return @{}
    }

    if (-not $loaded) {
        return @{}
    }

    $hasAssessmentsProperty = $loaded.PSObject.Properties.Name -contains "assessments"
    if (-not $hasAssessmentsProperty -or -not $loaded.assessments) {
        Write-Warning "IssueAssessments.json has no 'assessments' object at $assessmentsPath. Using fallback severity/blocker behavior."
        return @{}
    }

    $result = @{}
    foreach ($issueProp in $loaded.assessments.PSObject.Properties) {
        $entry = @{}

        if ($issueProp.Value -and $issueProp.Value.PSObject.Properties.Name -contains "severityTier") {
            $entry.severityTier = $issueProp.Value.severityTier
        }

        if ($issueProp.Value -and $issueProp.Value.PSObject.Properties.Name -contains "isBlocker") {
            $entry.isBlocker = $issueProp.Value.isBlocker
        }

        if ($issueProp.Value -and $issueProp.Value.PSObject.Properties.Name -contains "reasoning") {
            $entry.reasoning = $issueProp.Value.reasoning
        }

        $result[[string]$issueProp.Name] = $entry
    }

    return $result
}

function Read-AgentAssessments {
    <#
    .SYNOPSIS
        Loads AgentAssessments.json from the fixed skill path.

    .DESCRIPTION
        Returns an issue-number keyed hashtable. Missing file or malformed data
        does not terminate execution; the caller can safely fall back.
    #>
    param(
        [Parameter(Mandatory=$true)]
        [ValidateNotNullOrEmpty()]
        [string]$ScriptDirectory,

        [switch]$EmitStatus
    )

    $assessmentsPath = Get-AgentAssessmentsPath -ScriptDirectory $ScriptDirectory

    if (-not (Test-Path -LiteralPath $assessmentsPath -PathType Leaf)) {
        if ($EmitStatus) {
            Write-ColoredStatus -Level "Warning" -Message "AgentAssessments.json not found at $assessmentsPath. Continuing without runtime agent overrides."
        }
        return @{}
    }

    if ($EmitStatus) {
        Write-ColoredStatus -Level "Info" -Message "AgentAssessments.json found at $assessmentsPath"
    }

    try {
        $loaded = Get-Content -LiteralPath $assessmentsPath -Raw | ConvertFrom-Json
    }
    catch {
        Write-Warning "AgentAssessments.json could not be parsed at $assessmentsPath. Continuing without runtime agent overrides. Error: $_"
        return @{}
    }

    if (-not $loaded) {
        return @{}
    }

    $hasAssessmentsProperty = $loaded.PSObject.Properties.Name -contains "assessments"
    if (-not $hasAssessmentsProperty -or -not $loaded.assessments) {
        Write-Warning "AgentAssessments.json has no 'assessments' object at $assessmentsPath. Continuing without runtime agent overrides."
        return @{}
    }

    $result = @{}
    foreach ($issueProp in $loaded.assessments.PSObject.Properties) {
        $entry = @{}

        if ($issueProp.Value -and $issueProp.Value.PSObject.Properties.Name -contains "severityTier") {
            $entry.severityTier = $issueProp.Value.severityTier
        }

        if ($issueProp.Value -and $issueProp.Value.PSObject.Properties.Name -contains "isBlocker") {
            $entry.isBlocker = $issueProp.Value.isBlocker
        }

        if ($issueProp.Value -and $issueProp.Value.PSObject.Properties.Name -contains "reasoning") {
            $entry.reasoning = $issueProp.Value.reasoning
        }

        $result[[string]$issueProp.Name] = $entry
    }

    return $result
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
        [hashtable]$Config,
        [hashtable]$IssueAssessments,
        [hashtable]$AgentAssessments
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

    $score.Reactions = [math]::Floor([double]$weights.reactions * [double]$totalReactions)

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

    $score.Age = [math]::Floor([double]$weights.age * [double]$ageInDays)

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

    $score.Comments = [math]::Floor([double]$weights.comments * [double]$commentCount)

    # 4-5. Severity and blocker score from assessments only (file and/or agent).
    $score.Severity = 0
    $score.SeverityLabel = ""
    $score.IsBlocker = $false
    $score.Blockers = 0

    $issueKey = $null
    if ($Issue -and $Issue.PSObject.Properties.Name -contains "number" -and $Issue.number) {
        $issueKey = [string]$Issue.number
    }

    $selectedAssessment = $null
    # Human-edited IssueAssessments are authoritative when both sources exist.
    if ($issueKey -and $IssueAssessments -and $IssueAssessments.ContainsKey($issueKey)) {
        $selectedAssessment = $IssueAssessments[$issueKey]
    }
    elseif ($issueKey -and $AgentAssessments -and $AgentAssessments.ContainsKey($issueKey)) {
        $selectedAssessment = $AgentAssessments[$issueKey]
    }

    if ($selectedAssessment) {
        $hasSeverityTier = $false
        $severityTier = $null
        if ($selectedAssessment -is [hashtable]) {
            if ($selectedAssessment.ContainsKey("severityTier")) {
                $severityTier = $selectedAssessment["severityTier"]
                $hasSeverityTier = $true
            }
        }
        elseif ($selectedAssessment.PSObject.Properties.Name -contains "severityTier") {
            $severityTier = $selectedAssessment.severityTier
            $hasSeverityTier = $true
        }

        if ($hasSeverityTier -and -not [string]::IsNullOrWhiteSpace([string]$severityTier)) {
            $normalizedTier = ([string]$severityTier).ToLowerInvariant()
            $severityMultipliers = $Config.severityMultipliers
            if ($severityMultipliers.ContainsKey($normalizedTier)) {
                $score.Severity = $weights.severity * $severityMultipliers[$normalizedTier]
                $score.SeverityLabel = $normalizedTier
            } else {
                Write-Warning "Issue #$issueKey has invalid severityTier '$severityTier' in assessments. Using fallback severity behavior."
            }
        }

        $hasIsBlocker = $false
        $isBlockerValue = $null
        if ($selectedAssessment -is [hashtable]) {
            if ($selectedAssessment.ContainsKey("isBlocker")) {
                $isBlockerValue = $selectedAssessment["isBlocker"]
                $hasIsBlocker = $true
            }
        }
        elseif ($selectedAssessment.PSObject.Properties.Name -contains "isBlocker") {
            $isBlockerValue = $selectedAssessment.isBlocker
            $hasIsBlocker = $true
        }

        if ($hasIsBlocker) {
            if ($isBlockerValue -is [bool]) {
                $score.IsBlocker = [bool]$isBlockerValue
            }
            elseif ($null -eq $isBlockerValue -or [string]::IsNullOrWhiteSpace([string]$isBlockerValue)) {
                # Empty field: keep fallback value ($false)
            }
            else {
                Write-Warning "Issue #$issueKey has non-boolean isBlocker value '$isBlockerValue' in assessments. Using fallback blocker behavior."
            }
        }

        if ($score.IsBlocker -and $weights.blockers -gt 0) {
            $score.Blockers = $weights.blockers
        }
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

