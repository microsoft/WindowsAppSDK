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
            reactions = 25
            age = 20
            comments = 15
            external = 15
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
            "external"
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
                $defaultConfig.weights.external = [int]$loaded.weights.external
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
    #>
    param(
        [string]$ContactsPath
    )

    $defaultContacts = @{
        "area-Activation" = @{ primary = "Tim Kurtzman"; secondary = $null }
        "area-AOT" = @{ primary = "Scott Jones"; secondary = "Manodasan Wignarajah" }
        "area-AppContainer" = @{ primary = "Alex Lam"; secondary = $null }
        "area-AppExtension" = @{ primary = "Carl Russell"; secondary = $null }
        "area-ApplicationData" = @{ primary = "Carl Russell"; secondary = $null }
        "area-BackgroundTask" = @{ primary = "Godly Alias"; secondary = $null }
        "area-Decimal" = @{ primary = "Carl Russell"; secondary = $null }
        "area-DeveloperTools" = @{ primary = "James Pike"; secondary = $null }
        "area-dotnet" = @{ primary = "Scott Jones"; secondary = "Manodasan Wignarajah" }
        "area-DWriteCore" = @{ primary = "Leonardo Blanco"; secondary = $null }
        "area-DynamicDependencies" = @{ primary = "Carl Russell"; secondary = $null }
        "area-Elevation" = @{ primary = "Sarah Paracha"; secondary = $null }
        "area-External" = @{ primary = "Sarah Paracha"; secondary = $null }
        "area-File access" = @{ primary = "Gordon Lam"; secondary = "Dinah Gao, Xiang Hong" }
        "area-Graphics" = @{ primary = "Zachary Northrup"; secondary = "Saharsh Jaiswal" }
        "area-Infrastructure" = @{ primary = "Alex Lam"; secondary = "Felipe da Conceicao Guimaraes" }
        "area-Installer" = @{ primary = "Sarah Paracha"; secondary = $null }
        "area-Lifecycle" = @{ primary = "Tim Kurtzman"; secondary = $null }
        "area-Metapackage" = @{ primary = "Scott Jones"; secondary = "Manodasan Wignarajah" }
        "area-MRTCore" = @{ primary = "Kent Shipley"; secondary = $null }
        "area-Notification" = @{ primary = "Vivek Khare"; secondary = $null }
        "area-PackageManagement" = @{ primary = "Carl Russell"; secondary = $null }
        "area-Packaging" = @{ primary = "James Pike"; secondary = $null }
        "area-Power" = @{ primary = "Anis Mohammed Khaja Mohideen"; secondary = $null }
        "area-Projections" = @{ primary = "Scott Jones"; secondary = "Manodasan Wignarajah" }
        "area-Security" = @{ primary = "Steve Syfuhs"; secondary = $null }
        "area-SelfContained" = @{ primary = "Scott Jones"; secondary = "Manodasan Wignarajah" }
        "area-Shell UX" = @{ primary = "Sarah Paracha"; secondary = $null }
        "area-UndockedRegFreeWinRT" = @{ primary = "Carl Russell"; secondary = $null }
        "area-VersionInfo" = @{ primary = "Chris Wall"; secondary = $null }
        "area-WCR" = @{ primary = "Connor Al-Joundi"; secondary = "Aditi Narvekar" }
        "area-WebView" = @{ primary = "Sandeep Chadda"; secondary = "Hemant Kumar" }
        "area-Widgets" = @{ primary = "Pranav Gupta"; secondary = $null }
        "area-WinAppSDK:Templates" = @{ primary = "Lauren Ciha"; secondary = $null }
        "area-WinAppSDKDeployment" = @{ primary = "James Pike"; secondary = $null }
        "area-Windowing" = @{ primary = "Chris Raubecher"; secondary = $null }
        "area-WinML" = @{ primary = "Andrew Leader"; secondary = "Aditya Rastogi, Jason Holmes, Nick Eubanks" }
        "area-WinUI" = @{ primary = "Ajit Surana"; secondary = "Snigdha" }
    }

    if ($ContactsPath -and (Test-Path $ContactsPath)) {
        try {
            $loaded = Get-Content $ContactsPath -Raw | ConvertFrom-Json -AsHashtable
            if ($loaded.areaContacts) {
                return $loaded.areaContacts
            }
        }
        catch {
            Write-Warning "Failed to load contacts from $ContactsPath, using defaults: $_"
        }
    }

    return $defaultContacts
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

    return "[#$IssueNumber](https://github.com/$Repository/issues/$IssueNumber)"
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
