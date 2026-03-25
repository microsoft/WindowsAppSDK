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
    # Load area keywords from area-keywords.json
    $scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
    $skillDir = Split-Path -Parent $scriptDir
    $keywordsFile = Join-Path $skillDir "area-keywords.json"

    if (-not (Test-Path $keywordsFile)) {
        Write-Error "Area keywords file not found: $keywordsFile"
        exit 1
    }

    $keywordsJson = Get-Content -Path $keywordsFile -Raw -ErrorAction Stop
    try {
        $keywordsData = $keywordsJson | ConvertFrom-Json -ErrorAction Stop
    }
    catch {
        Write-Error "Failed to parse area keywords file '$keywordsFile': $_"
        exit 1
    }

    if ($null -eq $keywordsData -or ($keywordsData | Get-Member -MemberType NoteProperty).Count -eq 0) {
        Write-Error "Area keywords file '$keywordsFile' is empty or contains no label entries."
        exit 1
    }

    # Convert parsed JSON object to hashtable
    $areaKeywords = @{}
    foreach ($prop in $keywordsData.PSObject.Properties) {
        if ($null -eq $prop.Value -or @($prop.Value).Count -eq 0) {
            Write-Error "Area keywords file '$keywordsFile' has no keywords for label '$($prop.Name)'."
            exit 1
        }
        $areaKeywords[$prop.Name] = @($prop.Value)
    }

    Write-Verbose "Loaded $($areaKeywords.Count) area keyword entries from $keywordsFile"
    
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
