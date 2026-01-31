# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Compare current issues against previous triage state to identify changes.

.DESCRIPTION
    Loads the previous triage state and compares against current issues to categorize them as:
    - New: Issues not in previous state
    - Updated: Issues with changed updatedAt, commentCount, or reactionCount
    - Closed: Issues that changed from open to closed
    - Reopened: Issues that changed from closed to open
    - Unchanged: No detected changes

.PARAMETER CurrentIssuesJson
    JSON string containing the current array of issues from GitHub API/MCP.

.PARAMETER PreviousStatePath
    Path to the previous state file. Defaults to 'Generated Files/triageMeeting/previous-state.json'.

.PARAMETER OutputFormat
    Output format: 'json' or 'summary'. Defaults to 'json'.

.EXAMPLE
    $issues | ConvertTo-Json | ./Compare-TriageState.ps1

.EXAMPLE
    ./Compare-TriageState.ps1 -CurrentIssuesJson $jsonString -OutputFormat summary
#>

[CmdletBinding()]
param(
    [Parameter(ValueFromPipeline)]
    [string]$CurrentIssuesJson,

    [Parameter()]
    [string]$PreviousStatePath = "Generated Files/triageMeeting/previous-state.json",

    [Parameter()]
    [ValidateSet('json', 'summary')]
    [string]$OutputFormat = 'json'
)

begin {
    Set-StrictMode -Version 2.0
    $ErrorActionPreference = 'Stop'
    
    $inputData = @()
}

process {
    if ($CurrentIssuesJson) {
        $inputData += $CurrentIssuesJson
    }
}

end {
    # Parse current issues
    $fullJson = $inputData -join ""
    if (-not $fullJson) {
        Write-Error "No issues data provided. Pipe JSON or use -CurrentIssuesJson parameter."
        exit 1
    }

    try {
        $currentIssues = $fullJson | ConvertFrom-Json
    }
    catch {
        Write-Error "Failed to parse current issues JSON: $_"
        exit 1
    }

    # Load previous state
    $previousState = $null
    $isFirstRun = $false

    if (Test-Path $PreviousStatePath) {
        try {
            $previousState = Get-Content -Path $PreviousStatePath -Raw | ConvertFrom-Json
            Write-Host "Loaded previous state from: $PreviousStatePath" -ForegroundColor Cyan
            Write-Host "  - Previous triage date: $($previousState.triageDate)" -ForegroundColor Cyan
        }
        catch {
            Write-Warning "Failed to load previous state: $_"
            $isFirstRun = $true
        }
    }
    else {
        Write-Host "No previous state found. This is the first triage run." -ForegroundColor Yellow
        $isFirstRun = $true
    }

    # Categorize issues
    $result = @{
        previousTriageDate = if ($previousState) { $previousState.triageDate } else { $null }
        isFirstRun = $isFirstRun
        categories = @{
            new = @()
            updated = @()
            closed = @()
            reopened = @()
            unchanged = @()
        }
        summary = @{
            total = $currentIssues.Count
            new = 0
            updated = 0
            closed = 0
            reopened = 0
            unchanged = 0
        }
    }

    foreach ($issue in $currentIssues) {
        $issueNumber = $issue.number.ToString()
        $category = $null
        $changes = @()

        if ($isFirstRun -or -not $previousState.issues.PSObject.Properties[$issueNumber]) {
            # New issue
            $category = 'new'
        }
        else {
            $prev = $previousState.issues.$issueNumber

            # Check for state changes
            if ($prev.state -eq 'open' -and $issue.state -eq 'closed') {
                $category = 'closed'
                $changes += "State: open → closed"
            }
            elseif ($prev.state -eq 'closed' -and $issue.state -eq 'open') {
                $category = 'reopened'
                $changes += "State: closed → open"
            }
            else {
                # Check for updates
                if ($issue.updatedAt -ne $prev.updatedAt) {
                    $changes += "Updated: $($prev.updatedAt) → $($issue.updatedAt)"
                }
                
                $currentCommentCount = $issue.comments.Count
                if ($currentCommentCount -gt $prev.commentCount) {
                    $changes += "Comments: $($prev.commentCount) → $currentCommentCount (+$($currentCommentCount - $prev.commentCount))"
                }

                $currentReactionCount = (($issue.reactions.PSObject.Properties | Where-Object { $_.Name -ne 'url' } | ForEach-Object { $_.Value } | Measure-Object -Sum).Sum -as [int])
                if ($currentReactionCount -gt $prev.reactionCount) {
                    $changes += "Reactions: $($prev.reactionCount) → $currentReactionCount (+$($currentReactionCount - $prev.reactionCount))"
                }

                if ($changes.Count -gt 0) {
                    $category = 'updated'
                }
                else {
                    $category = 'unchanged'
                }
            }
        }

        # Add to result
        $authorLogin = $null
        if ($null -ne $issue.author -and $issue.author.PSObject.Properties['login']) {
            $authorLogin = $issue.author.login
        }
        
        $issueEntry = @{
            title = $issue.title
            state = $issue.state
            author = $authorLogin
            url = $issue.url
            createdAt = $issue.createdAt
            updatedAt = $issue.updatedAt
            changes = $changes
            labels = @($issue.labels | ForEach-Object { $_.name })
        }

        $result.categories[$category] += $issueEntry
        $result.summary[$category]++
    }

    # Output
    if ($OutputFormat -eq 'summary') {
        Write-Host ""
        Write-Host "═══════════════════════════════════════════════════════════" -ForegroundColor Cyan
        Write-Host "  TRIAGE DIFF SUMMARY" -ForegroundColor Cyan
        Write-Host "═══════════════════════════════════════════════════════════" -ForegroundColor Cyan
        Write-Host ""
        
        if ($previousState) {
            Write-Host "  Previous triage: $($previousState.triageDate)" -ForegroundColor Gray
        }
        Write-Host "  Current date:    $(Get-Date -Format 'yyyy-MM-ddTHH:mm:ssZ')" -ForegroundColor Gray
        Write-Host ""
        
        Write-Host "  📊 Summary:" -ForegroundColor White
        Write-Host "     Total issues:   $($result.summary.total)" -ForegroundColor White
        Write-Host "     🆕 New:         $($result.summary.new)" -ForegroundColor Green
        Write-Host "     📝 Updated:     $($result.summary.updated)" -ForegroundColor Yellow
        Write-Host "     ✅ Closed:      $($result.summary.closed)" -ForegroundColor Blue
        Write-Host "     🔓 Reopened:    $($result.summary.reopened)" -ForegroundColor Magenta
        Write-Host "     ⏸️ Unchanged:   $($result.summary.unchanged)" -ForegroundColor Gray
        Write-Host ""
        
        if ($result.categories.new.Count -gt 0) {
            Write-Host "  🆕 New Issues:" -ForegroundColor Green
            foreach ($issue in $result.categories.new) {
                Write-Host "     #$($issue.number): $($issue.title)" -ForegroundColor Green
            }
            Write-Host ""
        }
        
        if ($result.categories.updated.Count -gt 0) {
            Write-Host "  📝 Updated Issues:" -ForegroundColor Yellow
            foreach ($issue in $result.categories.updated) {
                Write-Host "     #$($issue.number): $($issue.title)" -ForegroundColor Yellow
                foreach ($change in $issue.changes) {
                    Write-Host "        → $change" -ForegroundColor DarkYellow
                }
            }
            Write-Host ""
        }
        
        Write-Host "═══════════════════════════════════════════════════════════" -ForegroundColor Cyan
    }
    else {
        $result | ConvertTo-Json -Depth 10
    }
    
    exit 0
}
