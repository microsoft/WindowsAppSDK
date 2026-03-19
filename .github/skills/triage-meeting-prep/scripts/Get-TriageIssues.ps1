# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Fetch Needs-Triage issues from GitHub using the gh CLI.

.DESCRIPTION
    Retrieves all issues with the Needs-Triage label from the microsoft/WindowsAppSDK repository.
    This script uses the GitHub CLI (gh) for predictable, scriptable data fetching.
    
    The script fetches:
    - All open issues with Needs-Triage label
    - All closed issues with Needs-Triage label (optional)
    
    Results can be filtered to only include issues WITHOUT area-* labels (primary triage focus).

.PARAMETER Repository
    The repository to query in 'owner/repo' format. Defaults to 'microsoft/WindowsAppSDK'.

.PARAMETER State
    Issue state filter: 'open', 'closed', or 'all'. Defaults to 'all'.

.PARAMETER NoAreaOnly
    If specified, filters results to only include issues without area-* labels.

.PARAMETER Limit
    Maximum number of issues to fetch. Defaults to 200.

.PARAMETER OutputFormat
    Output format: 'json', 'summary', or 'table'. Defaults to 'json'.

.EXAMPLE
    # Get all Needs-Triage issues as JSON
    ./Get-TriageIssues.ps1

.EXAMPLE
    # Get only open issues without area labels, display as table
    ./Get-TriageIssues.ps1 -State open -NoAreaOnly -OutputFormat table

.EXAMPLE
    # Pipe to Save-TriageState for persistence
    ./Get-TriageIssues.ps1 -State open | ./Save-TriageState.ps1
#>

[CmdletBinding()]
param(
    [Parameter()]
    [ValidatePattern('^[a-zA-Z0-9_-]+/[a-zA-Z0-9_.-]+$')]
    [string]$Repository = "microsoft/WindowsAppSDK",

    [Parameter()]
    [ValidateSet('open', 'closed', 'all')]
    [string]$State = 'all',

    [Parameter()]
    [switch]$NoAreaOnly,

    [Parameter()]
    [int]$Limit = 200,

    [Parameter()]
    [ValidateSet('json', 'summary', 'table')]
    [string]$OutputFormat = 'json'
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

# Verify gh CLI is available
try {
    $null = Get-Command gh -ErrorAction Stop
}
catch {
    Write-Error @"
GitHub CLI (gh) is not installed or not in PATH.

Install options:
  - Windows: winget install GitHub.cli
  - Or download from: https://cli.github.com/

After installation, authenticate with: gh auth login
"@
    exit 1
}

# Verify authentication
$authStatus = gh auth status 2>&1
if ($LASTEXITCODE -ne 0) {
    Write-Error @"
GitHub CLI is not authenticated.

Run: gh auth login
And follow the prompts to authenticate.
"@
    exit 1
}

Write-Verbose "Fetching Needs-Triage issues from $Repository..."

# Build the gh command
$ghArgs = @(
    'issue', 'list'
    '--repo', $Repository
    '--label', 'Needs-Triage'
    '--limit', $Limit
    '--json', 'number,title,body,author,createdAt,updatedAt,closedAt,state,labels,milestone,comments,reactionGroups,url,assignees'
)

if ($State -ne 'all') {
    $ghArgs += '--state', $State
}

# Execute gh CLI
$rawJson = & gh @ghArgs
if ($LASTEXITCODE -ne 0) {
    Write-Error "Failed to fetch issues from GitHub. Check your authentication and repository access."
    exit 1
}

try {
    $issues = $rawJson | ConvertFrom-Json
}
catch {
    Write-Error "Failed to parse GitHub response: $_"
    exit 1
}

Write-Verbose "  Retrieved $($issues.Count) issues with Needs-Triage label"

# Filter to no-area issues if requested
if ($NoAreaOnly) {
    $originalCount = $issues.Count
    $issues = @($issues | Where-Object {
        $hasAreaLabel = $false
        foreach ($label in $_.labels) {
            if ($label.name -like 'area-*') {
                $hasAreaLabel = $true
                break
            }
        }
        -not $hasAreaLabel
    })
    Write-Verbose "  Filtered to $($issues.Count) issues WITHOUT area-* labels (excluded $($originalCount - $issues.Count))"
}

# Categorize issues
$openIssues = @($issues | Where-Object { $_.state -eq 'OPEN' -or $_.state -eq 'open' })
$closedIssues = @($issues | Where-Object { $_.state -eq 'CLOSED' -or $_.state -eq 'closed' })

# Output based on format
switch ($OutputFormat) {
    'summary' {
        Write-Host ""
        Write-Host "═══════════════════════════════════════════════════════════" -ForegroundColor Cyan
        Write-Host "  NEEDS-TRIAGE ISSUES SUMMARY" -ForegroundColor Cyan
        Write-Host "═══════════════════════════════════════════════════════════" -ForegroundColor Cyan
        Write-Host ""
        Write-Host "  Repository: $Repository" -ForegroundColor Gray
        Write-Host "  Filter:     Needs-Triage label" -ForegroundColor Gray
        if ($NoAreaOnly) {
            Write-Host "  Scope:      Issues WITHOUT area-* labels only" -ForegroundColor Gray
        }
        Write-Host ""
        Write-Host "  📊 Totals:" -ForegroundColor White
        Write-Host "     Total:  $($issues.Count)" -ForegroundColor White
        Write-Host "     Open:   $($openIssues.Count)" -ForegroundColor Green
        Write-Host "     Closed: $($closedIssues.Count)" -ForegroundColor Yellow
        Write-Host ""
        
        if ($openIssues.Count -gt 0) {
            Write-Host "  🏷️ Open Issues Needing Triage:" -ForegroundColor Green
            foreach ($issue in $openIssues | Sort-Object -Property createdAt -Descending | Select-Object -First 10) {
                $labels = ($issue.labels | ForEach-Object { $_.name }) -join ', '
                Write-Host "     #$($issue.number): $($issue.title)" -ForegroundColor White
                Write-Host "        Created: $($issue.createdAt) | Labels: $labels" -ForegroundColor DarkGray
            }
            if ($openIssues.Count -gt 10) {
                Write-Host "     ... and $($openIssues.Count - 10) more" -ForegroundColor DarkGray
            }
            Write-Host ""
        }
        
        if ($closedIssues.Count -gt 0) {
            Write-Host "  ✅ Closed Issues (still has Needs-Triage):" -ForegroundColor Yellow
            foreach ($issue in $closedIssues | Sort-Object -Property updatedAt -Descending | Select-Object -First 5) {
                Write-Host "     #$($issue.number): $($issue.title)" -ForegroundColor White
                Write-Host "        Closed: $($issue.closedAt)" -ForegroundColor DarkGray
            }
            if ($closedIssues.Count -gt 5) {
                Write-Host "     ... and $($closedIssues.Count - 5) more" -ForegroundColor DarkGray
            }
            Write-Host ""
        }
        
        Write-Host "═══════════════════════════════════════════════════════════" -ForegroundColor Cyan
    }
    
    'table' {
        $issues | ForEach-Object {
            $labels = ($_.labels | ForEach-Object { $_.name }) -join ', '
            $authorName = if ($_.author) { $_.author.login } else { 'unknown' }
            $commentCount = if ($_.comments) { @($_.comments).Count } else { 0 }
            [PSCustomObject]@{
                Number    = $_.number
                State     = $_.state
                Title     = if ($_.title.Length -gt 50) { $_.title.Substring(0, 47) + '...' } else { $_.title }
                Author    = $authorName
                Created   = ([datetime]$_.createdAt).ToString('yyyy-MM-dd')
                Comments  = $commentCount
                Labels    = if ($labels.Length -gt 30) { $labels.Substring(0, 27) + '...' } else { $labels }
            }
        } | Format-Table -AutoSize
    }
    
    default {
        # JSON output - pipe-friendly
        $issues | ConvertTo-Json -Depth 10
    }
}

exit 0
