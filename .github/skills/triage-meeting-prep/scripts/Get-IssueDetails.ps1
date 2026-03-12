# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Get detailed information about a specific GitHub issue using gh CLI.

.DESCRIPTION
    Fetches comprehensive details about a single issue including:
    - Full issue body and metadata
    - All comments
    - Timeline events (optional)
    
    This is useful for generating detailed issue reviews.

.PARAMETER IssueNumber
    The issue number to fetch.

.PARAMETER Repository
    The repository in 'owner/repo' format. Defaults to 'microsoft/WindowsAppSDK'.

.PARAMETER IncludeComments
    Include all comments on the issue. Defaults to $true.

.PARAMETER IncludeTimeline
    Include timeline events (label changes, assignments, etc.). Defaults to $false.

.PARAMETER OutputFormat
    Output format: 'json' or 'summary'. Defaults to 'json'.

.EXAMPLE
    # Get issue details as JSON
    ./Get-IssueDetails.ps1 -IssueNumber 6147

.EXAMPLE
    # Get issue with timeline, display summary
    ./Get-IssueDetails.ps1 -IssueNumber 6147 -IncludeTimeline -OutputFormat summary
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory, Position = 0)]
    [int]$IssueNumber,

    [Parameter()]
    [ValidatePattern('^[a-zA-Z0-9_-]+/[a-zA-Z0-9_.-]+$')]
    [string]$Repository = "microsoft/WindowsAppSDK",

    [Parameter()]
    [bool]$IncludeComments = $true,

    [Parameter()]
    [switch]$IncludeTimeline,

    [Parameter()]
    [ValidateSet('json', 'summary')]
    [string]$OutputFormat = 'json'
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

# Verify gh CLI is available
try {
    $null = Get-Command gh -ErrorAction Stop
}
catch {
    Write-Error "GitHub CLI (gh) is not installed. Run: winget install GitHub.cli"
    exit 1
}

# Verify authentication
$authStatus = gh auth status 2>&1
if ($LASTEXITCODE -ne 0) {
    Write-Error "GitHub CLI is not authenticated. Run: gh auth login"
    exit 1
}

Write-Verbose "Fetching issue #$IssueNumber from $Repository..."

# Fetch issue details
$issueJson = gh issue view $IssueNumber --repo $Repository --json number,title,body,author,createdAt,updatedAt,closedAt,state,labels,milestone,comments,reactionGroups,url,assignees
if ($LASTEXITCODE -ne 0) {
    Write-Error "Failed to fetch issue #$IssueNumber"
    exit 1
}

$issue = $issueJson | ConvertFrom-Json

# Fetch comments if requested (gh issue view --json comments already includes them)
$comments = @()
if ($IncludeComments -and $issue.comments) {
    $comments = @($issue.comments)
    Write-Verbose "  Retrieved $($comments.Count) comments"
}

# Fetch timeline if requested
$timeline = @()
if ($IncludeTimeline) {
    Write-Verbose "  Fetching timeline events..."
    # gh doesn't have direct timeline support, use API
    $timelineJson = gh api "repos/$Repository/issues/$IssueNumber/timeline" --paginate 2>$null
    if ($LASTEXITCODE -eq 0 -and $timelineJson) {
        $timeline = $timelineJson | ConvertFrom-Json
        Write-Verbose "  Retrieved $($timeline.Count) timeline events"
    }
}

# Build result object
$result = @{
    number = $issue.number
    title = $issue.title
    body = $issue.body
    state = $issue.state
    author = if ($issue.author) { $issue.author.login } else { $null }
    createdAt = $issue.createdAt
    updatedAt = $issue.updatedAt
    closedAt = $issue.closedAt
    url = $issue.url
    labels = @($issue.labels | ForEach-Object { $_.name })
    milestone = if ($issue.milestone) { $issue.milestone.title } else { $null }
    assignees = @($issue.assignees | ForEach-Object { $_.login })
    reactions = $issue.reactionGroups
    commentCount = if ($comments) { $comments.Count } else { 0 }
    comments = @(if ($comments) { $comments | ForEach-Object {
        @{
            id = $_.id
            author = if ($_.author) { $_.author.login } else { 'unknown' }
            body = $_.body
            createdAt = $_.createdAt
            url = $_.url
            reactions = if ($_.reactionGroups) { $_.reactionGroups } else { @() }
        }
    } } else { @() })
}

if ($IncludeTimeline) {
    $result.timeline = $timeline
}

# Analyze labels
$areaLabels = @($issue.labels | Where-Object { $_.name -like 'area-*' })
$triageLabels = @($issue.labels | Where-Object { $_.name -eq 'Needs-Triage' })
$result.hasAreaLabel = $areaLabels.Count -gt 0
$result.areaLabels = @($areaLabels | ForEach-Object { $_.name })
$result.needsTriage = $triageLabels.Count -gt 0

# Calculate area suggestion confidence if no area label
if (-not $result.hasAreaLabel) {
    # Fetch available area labels from the repository using Get-RepositoryLabels.ps1
    $scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
    $getLabelsScript = Join-Path $scriptDir "Get-RepositoryLabels.ps1"
    
    $availableAreaLabels = @()
    if (Test-Path $getLabelsScript) {
        try {
            $rawLabels = & $getLabelsScript -Repository $Repository -Filter "area-*" -OutputFormat json 2>$null
            if ($LASTEXITCODE -eq 0 -and $rawLabels) {
                $labelData = $rawLabels | ConvertFrom-Json
                $availableAreaLabels = @($labelData | ForEach-Object { $_.name })
                Write-Verbose "Fetched $($availableAreaLabels.Count) area labels from repository"
            }
        }
        catch {
            Write-Verbose "Could not fetch area labels: $_"
        }
    }
    
    # Build keyword map - use fetched labels or fall back to common ones
    # Keywords are derived from label names (strip 'area-' prefix and expand)
    $areaKeywords = @{}
    
    # Default keywords for common areas (fallback and enhancement)
    # area-Notifications covers all notification types (toast, badge, push, app notifications)
    $defaultKeywords = @{
        'area-Notifications' = @('notification', 'toast', 'badge', 'push', 'appnotification', 'pushnotification', 'wns')
        'area-Packaging' = @('msix', 'package', 'deploy', 'install', 'appx', 'deployment')
        'area-Windowing' = @('window', 'appwindow', 'titlebar', 'backdrop', 'presenter')
        'area-Widgets' = @('widget', 'dashboard')
        'area-AppLifecycle' = @('lifecycle', 'activation', 'restart', 'single instance', 'appinstance')
        'area-PowerManagement' = @('power', 'battery', 'suspend', 'resume', 'powermanager')
        'area-MRTCore' = @('resource', 'mrt', 'localization', 'pri', 'resourcemanager')
        'area-DWriteCore' = @('font', 'dwrite', 'text', 'typography')
        'area-AccessControl' = @('access', 'security', 'token', 'permission')
        'area-Environment' = @('environment', 'variable', 'env')
    }
    
    # Use fetched labels if available, otherwise use default set
    $labelsToUse = if ($availableAreaLabels.Count -gt 0) { $availableAreaLabels } else { $defaultKeywords.Keys }
    
    foreach ($areaLabel in $labelsToUse) {
        # Start with default keywords if we have them
        if ($defaultKeywords.ContainsKey($areaLabel)) {
            $areaKeywords[$areaLabel] = $defaultKeywords[$areaLabel]
        }
        else {
            # Generate keywords from label name (e.g., area-SomeFeature -> @('some', 'feature', 'somefeature'))
            $labelBase = $areaLabel -replace '^area-', ''
            $keywords = @($labelBase.ToLower())
            # Split PascalCase into words
            $words = [regex]::Matches($labelBase, '[A-Z][a-z]+') | ForEach-Object { $_.Value.ToLower() }
            if ($words) {
                $keywords += $words
            }
            $areaKeywords[$areaLabel] = $keywords
        }
    }
    
    # Extract text to search for keywords
    $text = "$($issue.title) $($issue.body)"
    
    $suggestedAreas = @()
    foreach ($area in $areaKeywords.Keys) {
        $keywordMatches = 0
        foreach ($keyword in $areaKeywords[$area]) {
            if ($text -match $keyword) {
                $keywordMatches++
            }
        }
        if ($keywordMatches -gt 0) {
            # Calculate confidence based on keyword matches
            $confidence = 25  # Base
            $confidence += [math]::Min($keywordMatches * 15, 45)  # Up to 45 for keywords
            $confidence = [math]::Min($confidence, 100)
            
            $suggestedAreas += @{
                area = $area
                keywordMatches = $keywordMatches
                confidence = $confidence
            }
        }
    }
    
    # Sort by confidence descending
    $result.suggestedAreas = @($suggestedAreas | Sort-Object { $_.confidence } -Descending | Select-Object -First 3)
    
    # Flag if multiple candidates (reduces confidence)
    if ($suggestedAreas.Count -gt 1) {
        foreach ($sa in $result.suggestedAreas) {
            $sa.confidence = [math]::Max(0, $sa.confidence - 15)
        }
    }
}

# Output
switch ($OutputFormat) {
    'summary' {
        Write-Host ""
        Write-Host "═══════════════════════════════════════════════════════════" -ForegroundColor Cyan
        Write-Host "  ISSUE #$($issue.number)" -ForegroundColor Cyan
        Write-Host "═══════════════════════════════════════════════════════════" -ForegroundColor Cyan
        Write-Host ""
        Write-Host "  Title:   $($issue.title)" -ForegroundColor White
        Write-Host "  State:   $($issue.state)" -ForegroundColor $(if ($issue.state -eq 'OPEN') { 'Green' } else { 'Yellow' })
        Write-Host "  Author:  @$($result.author)" -ForegroundColor Gray
        Write-Host "  Created: $($issue.createdAt)" -ForegroundColor Gray
        Write-Host "  Updated: $($issue.updatedAt)" -ForegroundColor Gray
        Write-Host "  URL:     $($issue.url)" -ForegroundColor Blue
        Write-Host ""
        Write-Host "  Labels:  $($result.labels -join ', ')" -ForegroundColor Magenta
        if ($result.milestone) {
            Write-Host "  Milestone: $($result.milestone)" -ForegroundColor Cyan
        }
        if ($result.assignees.Count -gt 0) {
            Write-Host "  Assignees: $($result.assignees -join ', ')" -ForegroundColor Gray
        }
        Write-Host ""
        Write-Host "  📊 Analysis:" -ForegroundColor White
        Write-Host "     Has area label: $(if ($result.hasAreaLabel) { '✅ Yes' } else { '❌ No' })" -ForegroundColor $(if ($result.hasAreaLabel) { 'Green' } else { 'Red' })
        Write-Host "     Needs triage:   $(if ($result.needsTriage) { '⚠️ Yes' } else { '✅ No' })" -ForegroundColor $(if ($result.needsTriage) { 'Yellow' } else { 'Green' })
        Write-Host "     Comments:       $($result.commentCount)" -ForegroundColor Gray
        Write-Host ""
        
        # Show suggested areas if no area label
        if (-not $result.hasAreaLabel -and $result.suggestedAreas.Count -gt 0) {
            Write-Host "  🏷️ Suggested Areas:" -ForegroundColor Yellow
            foreach ($sa in $result.suggestedAreas) {
                Write-Host "     $($sa.area) [confidence:$($sa.confidence)]" -ForegroundColor Yellow
            }
            Write-Host ""
        }
        
        if ($result.body) {
            Write-Host "  📝 Issue Body (first 500 chars):" -ForegroundColor White
            $preview = if ($result.body.Length -gt 500) { $result.body.Substring(0, 500) + '...' } else { $result.body }
            Write-Host "     $preview" -ForegroundColor DarkGray
            Write-Host ""
        }
        
        Write-Host "═══════════════════════════════════════════════════════════" -ForegroundColor Cyan
    }
    
    default {
        $result | ConvertTo-Json -Depth 10
    }
}

exit 0
