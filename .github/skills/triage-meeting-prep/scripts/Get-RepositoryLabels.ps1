# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Fetch all label definitions from a GitHub repository using the gh CLI.

.DESCRIPTION
    Retrieves all labels including their names, descriptions, and colors from the specified repository.
    This script uses the GitHub CLI (gh) for predictable, scriptable data fetching.
    
    The script fetches:
    - Label name
    - Label description (if available)
    - Label color (hex code)
    
    Results can be filtered by label name pattern (e.g., 'area-*' to get only area labels).

.PARAMETER Repository
    The repository to query in 'owner/repo' format. Defaults to 'microsoft/WindowsAppSDK'.

.PARAMETER Filter
    Optional filter pattern for label names (supports wildcards like 'area-*' or '*bug*').
    If not specified, all labels are returned.

.PARAMETER Limit
    Maximum number of labels to fetch. Defaults to 500 (should cover most repositories).

.PARAMETER OutputFormat
    Output format: 'json', 'summary', or 'table'. Defaults to 'json'.

.PARAMETER IncludeEmpty
    If specified, includes labels that have no description.
    By default, labels without descriptions are included but highlighted in summary view.

.EXAMPLE
    # Get all labels as JSON
    ./Get-RepositoryLabels.ps1

.EXAMPLE
    # Get only area-* labels, display as table
    ./Get-RepositoryLabels.ps1 -Filter "area-*" -OutputFormat table

.EXAMPLE
    # Get all labels with descriptions, show summary
    ./Get-RepositoryLabels.ps1 -OutputFormat summary

.EXAMPLE
    # Get labels from a different repository
    ./Get-RepositoryLabels.ps1 -Repository "microsoft/terminal" -OutputFormat table

.NOTES
    Requires GitHub CLI (gh) to be installed and authenticated.
    Install: winget install GitHub.cli
    Authenticate: gh auth login
#>

[CmdletBinding()]
param(
    [Parameter()]
    [ValidatePattern('^[a-zA-Z0-9_-]+/[a-zA-Z0-9_.-]+$')]
    [string]$Repository = "microsoft/WindowsAppSDK",

    [Parameter()]
    [string]$Filter,

    [Parameter()]
    [int]$Limit = 500,

    [Parameter()]
    [ValidateSet('json', 'summary', 'table')]
    [string]$OutputFormat = 'json',

    [Parameter()]
    [switch]$IncludeEmpty
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

# Helper function to convert hex color to RGB and create colored text
function Get-ColoredText {
    param(
        [string]$HexColor,
        [string]$Text
    )
    
    # Parse hex color to RGB
    $r = [Convert]::ToInt32($HexColor.Substring(0, 2), 16)
    $g = [Convert]::ToInt32($HexColor.Substring(2, 2), 16)
    $b = [Convert]::ToInt32($HexColor.Substring(4, 2), 16)
    
    # Calculate perceived brightness (0-255)
    # Using the formula: (0.299*R + 0.587*G + 0.114*B)
    $brightness = (0.299 * $r) + (0.587 * $g) + (0.114 * $b)
    
    # For very dark colors (brightness < 50), add a lighter background or use a marker
    $esc = [char]27
    if ($brightness -lt 50) {
        # Very dark color - show with light gray background
        "$esc[38;2;$r;$g;${b}m$esc[48;2;200;200;200m$Text$esc[0m"
    }
    else {
        # Normal color - show as foreground color
        "$esc[38;2;$r;$g;${b}m$Text$esc[0m"
    }
}

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

Write-Verbose "Fetching labels from $Repository..."

# Build the gh command
$ghArgs = @(
    'label', 'list'
    '--repo', $Repository
    '--limit', $Limit
    '--json', 'name,description,color'
)

# Execute gh CLI
$rawJson = & gh @ghArgs
if ($LASTEXITCODE -ne 0) {
    Write-Error "Failed to fetch labels from GitHub. Check your authentication and repository access."
    exit 1
}

try {
    $labels = $rawJson | ConvertFrom-Json
}
catch {
    Write-Error "Failed to parse GitHub response: $_"
    exit 1
}

Write-Verbose "  Retrieved $($labels.Count) labels"

# Apply filter if specified
if ($Filter) {
    $originalCount = $labels.Count
    $labels = @($labels | Where-Object { $_.name -like $Filter })
    Write-Verbose "  Filtered to $($labels.Count) labels matching '$Filter' (excluded $($originalCount - $labels.Count))"
}

# Sort labels alphabetically
$labels = @($labels | Sort-Object -Property name)

# Categorize labels
$labelsWithDescription = @($labels | Where-Object { $_.description })
$labelsWithoutDescription = @($labels | Where-Object { -not $_.description })

# Output based on format
switch ($OutputFormat) {
    'summary' {
        Write-Host ""
        Write-Host "═══════════════════════════════════════════════════════════" -ForegroundColor Cyan
        Write-Host "  REPOSITORY LABELS SUMMARY" -ForegroundColor Cyan
        Write-Host "═══════════════════════════════════════════════════════════" -ForegroundColor Cyan
        Write-Host ""
        Write-Host "  Repository: $Repository" -ForegroundColor Gray
        if ($Filter) {
            Write-Host "  Filter:     $Filter" -ForegroundColor Gray
        }
        Write-Host ""
        Write-Host "  📊 Totals:" -ForegroundColor White
        Write-Host "     Total:             $($labels.Count)" -ForegroundColor White
        Write-Host "     With description:  $($labelsWithDescription.Count)" -ForegroundColor Green
        Write-Host "     Without description: $($labelsWithoutDescription.Count)" -ForegroundColor Yellow
        Write-Host ""
        
        if ($labelsWithDescription.Count -gt 0) {
            Write-Host "  🏷️ Labels with Descriptions:" -ForegroundColor Green
            Write-Host ""
            foreach ($label in $labelsWithDescription) {
                $colorDisplay = Get-ColoredText -HexColor $label.color -Text "#$($label.color)"
                Write-Host "     [$($label.name)] " -ForegroundColor White -NoNewline
                Write-Host $colorDisplay
                Write-Host "        $($label.description)" -ForegroundColor Gray
                Write-Host ""
            }
        }
        
        if ($labelsWithoutDescription.Count -gt 0) {
            Write-Host "  ⚠️ Labels Without Descriptions:" -ForegroundColor Yellow
            Write-Host ""
            foreach ($label in $labelsWithoutDescription) {
                $colorDisplay = Get-ColoredText -HexColor $label.color -Text "#$($label.color)"
                Write-Host "     [$($label.name)] " -ForegroundColor White -NoNewline
                Write-Host $colorDisplay
                Write-Host "        (no description)" -ForegroundColor DarkGray
                Write-Host ""
            }
        }
        
        Write-Host "═══════════════════════════════════════════════════════════" -ForegroundColor Cyan
    }
    
    'table' {
        # Create custom table output with colored hex values
        # Calculate column widths
        $nameWidth = ($labels | ForEach-Object { $_.name.Length } | Measure-Object -Maximum).Maximum
        $nameWidth = [Math]::Max($nameWidth, 4) + 2  # At least "Name" width + padding
        
        $descWidth = ($labels | ForEach-Object { 
            $desc = if ($_.description) { $_.description } else { '(no description)' }
            $desc.Length 
        } | Measure-Object -Maximum).Maximum
        $descWidth = [Math]::Max($descWidth, 11) + 2  # At least "Description" width + padding
        $descWidth = [Math]::Min($descWidth, 60)  # Cap at 60 for readability
        
        $colorWidth = 9  # "#RRGGBB" = 7 chars + padding
        
        # Print header
        Write-Host ""
        Write-Host ("Name".PadRight($nameWidth)) -NoNewline -ForegroundColor Cyan
        Write-Host ("Description".PadRight($descWidth)) -NoNewline -ForegroundColor Cyan
        Write-Host "Color" -ForegroundColor Cyan
        
        # Print separator
        Write-Host ("-" * $nameWidth) -NoNewline -ForegroundColor DarkGray
        Write-Host ("-" * $descWidth) -NoNewline -ForegroundColor DarkGray
        Write-Host ("-" * $colorWidth) -ForegroundColor DarkGray
        
        # Print rows
        foreach ($label in $labels) {
            $desc = if ($label.description) { $label.description } else { '(no description)' }
            
            # Truncate description if too long
            if ($desc.Length -gt ($descWidth - 2)) {
                $desc = $desc.Substring(0, $descWidth - 5) + "..."
            }
            
            $colorDisplay = Get-ColoredText -HexColor $label.color -Text "#$($label.color)"
            
            Write-Host ($label.name.PadRight($nameWidth)) -NoNewline
            Write-Host ($desc.PadRight($descWidth)) -NoNewline -ForegroundColor Gray
            Write-Host $colorDisplay
        }
        Write-Host ""
    }
    
    default {
        # JSON output - pipe-friendly
        $labels | ConvertTo-Json -Depth 5
    }
}

exit 0
