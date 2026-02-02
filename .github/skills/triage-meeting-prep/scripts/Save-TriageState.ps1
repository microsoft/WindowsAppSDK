# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Save the current triage state for future diff comparisons.

.DESCRIPTION
    Creates a JSON snapshot of all Needs-Triage issues for comparison in the next triage meeting.
    This script is called by the triage-meeting-prep skill after fetching issue data.

.PARAMETER IssuesJson
    JSON string containing the array of issues from gh CLI.

.PARAMETER OutputPath
    Path to save the state file. Defaults to 'Generated Files/triageMeeting/previous-state.json'.

.PARAMETER TriageDate
    Date of the triage meeting. Defaults to current date.

.EXAMPLE
    $issues | ConvertTo-Json | ./Save-TriageState.ps1 -OutputPath "Generated Files/triageMeeting/previous-state.json"

.EXAMPLE
    ./Save-TriageState.ps1 -IssuesJson $jsonString -TriageDate "2025-01-28"
#>

[CmdletBinding()]
param(
    [Parameter(ValueFromPipeline)]
    [string]$IssuesJson,

    [Parameter()]
    [string]$OutputPath = "Generated Files/triageMeeting/previous-state.json",

    [Parameter()]
    [string]$TriageDate = (Get-Date -Format "yyyy-MM-dd")
)

begin {
    Set-StrictMode -Version 2.0
    $ErrorActionPreference = 'Stop'
    
    $inputData = @()
}

process {
    if ($IssuesJson) {
        $inputData += $IssuesJson
    }
}

end {
    # Parse input JSON
    $fullJson = $inputData -join ""
    if (-not $fullJson) {
        Write-Error "No issues data provided. Pipe JSON or use -IssuesJson parameter."
        exit 1
    }

    try {
        $issues = $fullJson | ConvertFrom-Json
    }
    catch {
        Write-Error "Failed to parse issues JSON: $_"
        exit 1
    }

    # Build state object
    $state = @{
        triageDate = (Get-Date $TriageDate).ToUniversalTime().ToString("yyyy-MM-ddTHH:mm:ssZ")
        generatedAt = (Get-Date).ToUniversalTime().ToString("yyyy-MM-ddTHH:mm:ssZ")
        issueCount = $issues.Count
        issues = @{}
    }

    foreach ($issue in $issues) {
        $issueNumber = $issue.number.ToString()
        
        # Safely handle potentially null nested properties under strict mode
        $authorLogin = if ($null -ne $issue.author) { $issue.author.login } else { $null }
        $milestoneTitle = if ($null -ne $issue.milestone) { $issue.milestone.title } else { $null }
        
        # Calculate comment count safely
        $commentCount = 0
        if ($null -ne $issue.comments) {
            $commentCount = @($issue.comments).Count
        }
        
        # Calculate reaction count from reactionGroups (gh CLI format)
        $reactionCount = 0
        if ($null -ne $issue.reactionGroups) {
            foreach ($group in $issue.reactionGroups) {
                if ($null -ne $group.users -and $null -ne $group.users.totalCount) {
                    $reactionCount += $group.users.totalCount
                }
            }
        }
        
        $state.issues[$issueNumber] = @{
            title = $issue.title
            state = $issue.state
            author = $authorLogin
            createdAt = $issue.createdAt
            updatedAt = $issue.updatedAt
            closedAt = $issue.closedAt
            commentCount = $commentCount
            reactionCount = $reactionCount
            labels = @($issue.labels | ForEach-Object { $_.name })
            milestone = $milestoneTitle
        }
    }

    # Ensure output directory exists
    $outputDir = Split-Path -Parent $OutputPath
    if ($outputDir -and -not (Test-Path $outputDir)) {
        New-Item -ItemType Directory -Path $outputDir -Force | Out-Null
        Write-Host "Created directory: $outputDir" -ForegroundColor Green
    }

    # Save state
    $state | ConvertTo-Json -Depth 10 | Set-Content -Path $OutputPath -Encoding UTF8

    Write-Host "Saved triage state to: $OutputPath" -ForegroundColor Green
    Write-Host "  - Date: $($state.triageDate)" -ForegroundColor Cyan
    Write-Host "  - Issues: $($state.issueCount)" -ForegroundColor Cyan

    # Also save dated backup
    $backupPath = Join-Path (Split-Path -Parent $OutputPath) "$TriageDate/state-snapshot.json"
    $backupDir = Split-Path -Parent $backupPath
    if (-not (Test-Path $backupDir)) {
        New-Item -ItemType Directory -Path $backupDir -Force | Out-Null
    }
    $state | ConvertTo-Json -Depth 10 | Set-Content -Path $backupPath -Encoding UTF8
    Write-Host "Saved backup to: $backupPath" -ForegroundColor Green
    
    exit 0
}
