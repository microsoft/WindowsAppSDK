# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Creates an ADO servicing bug work item for a cherry-pick.

.DESCRIPTION
    Uses the Azure CLI (az boards) to create a Bug work item in Azure DevOps
    with the servicing template fields populated from AI-generated content.

.PARAMETER Title
    The bug title (e.g., "[1.7.9 servicing] Fix reset activity data").

.PARAMETER Description
    HTML description for the bug body.

.PARAMETER ReproSteps
    Steps to reproduce the original issue.

.PARAMETER CustomerImpact
    Who is affected and how.

.PARAMETER RiskAssessment
    Risk level (Low/Medium/High) with justification.

.PARAMETER OriginalPrUrl
    URL of the original PR being cherry-picked.

.PARAMETER TargetBranch
    The release branch this bug targets.

.PARAMETER VersionString
    The servicing version (e.g., "1.7.9").

.PARAMETER EnumName
    The RuntimeCompatibilityChange enum name.

.PARAMETER ConfigPath
    Optional path to servicing-config.json.

.PARAMETER DryRun
    If set, shows what would be created without actually creating the work item.

.EXAMPLE
    $bug = ./New-AdoServicingBug.ps1 -Title "[1.7.9 servicing] Fix thing" `
        -Description "..." -OriginalPrUrl "https://..." -TargetBranch "release/1.7-stable"

.OUTPUTS
    PSCustomObject with BugId and Url properties.

.NOTES
    Requires Azure CLI (az) with 'azure-devops' extension. Must be authenticated via 'az login'.
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory)]
    [string]$Title,

    [Parameter(Mandatory)]
    [string]$Description,

    [Parameter()]
    [string]$ReproSteps,

    [Parameter()]
    [string]$CustomerImpact,

    [Parameter()]
    [string]$RiskAssessment,

    [Parameter()]
    [string]$OriginalPrUrl,

    [Parameter(Mandatory)]
    [string]$TargetBranch,

    [Parameter(Mandatory)]
    [string]$VersionString,

    [Parameter()]
    [string]$EnumName,

    [Parameter()]
    [string]$ConfigPath,

    [switch]$DryRun
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

. "$PSScriptRoot/ServicingLib.ps1"

$config = Get-ServicingConfig -ConfigPath $ConfigPath

# Build the full description HTML
$fullDescription = @"
<div>
<h3>Servicing Cherry-Pick</h3>
<p><strong>Original PR:</strong> <a href="$OriginalPrUrl">$OriginalPrUrl</a></p>
<p><strong>Target Branch:</strong> $TargetBranch</p>
<p><strong>Version:</strong> $VersionString</p>
$(if ($EnumName) { "<p><strong>Containment Enum:</strong> $EnumName</p>" })
<hr/>
$Description
$(if ($CustomerImpact) { "<h3>Customer Impact</h3><p>$CustomerImpact</p>" })
$(if ($RiskAssessment) { "<h3>Risk Assessment</h3><p>$RiskAssessment</p>" })
</div>
"@

if ($DryRun) {
    Write-Host "[DRY RUN] Would create ADO bug:" -ForegroundColor DarkGray
    Write-Host "  Organization: $($config.ado.organization)" -ForegroundColor DarkGray
    Write-Host "  Project:      $($config.ado.project)" -ForegroundColor DarkGray
    Write-Host "  Type:         $($config.ado.workItemType)" -ForegroundColor DarkGray
    Write-Host "  Area Path:    $($config.ado.areaPath)" -ForegroundColor DarkGray
    Write-Host "  Title:        $Title" -ForegroundColor DarkGray
    Write-Host "  Tags:         $($config.ado.tags)" -ForegroundColor DarkGray
    return [PSCustomObject]@{
        BugId  = 0
        Url    = 'https://dev.azure.com/dry-run'
        DryRun = $true
    }
}

Write-Verbose "Creating ADO bug: $Title"

# Build az boards work-item create arguments
$azArgs = @(
    'boards', 'work-item', 'create',
    '--org', $config.ado.organization,
    '--project', $config.ado.project,
    '--type', $config.ado.workItemType,
    '--title', $Title,
    '--description', $fullDescription,
    '--area', $config.ado.areaPath,
    '--output', 'json'
)

# Add fields
$fields = @()
if ($config.ado.tags) {
    $fields += "System.Tags=$($config.ado.tags)"
}
if ($ReproSteps) {
    $fields += "Microsoft.VSTS.TCM.ReproSteps=$ReproSteps"
}

foreach ($field in $fields) {
    $azArgs += @('--fields', $field)
}

$rawJson = & az @azArgs 2>&1
if ($LASTEXITCODE -ne 0) {
    Write-Error "Failed to create ADO work item. Error: $rawJson"
    exit 1
}

$workItem = $rawJson | ConvertFrom-Json
$bugId = $workItem.id
$bugUrl = $workItem._links.html.href

if (-not $bugUrl) {
    $bugUrl = "$($config.ado.organization)/$($config.ado.project)/_workitems/edit/$bugId"
}

Ok "ADO bug created: #$bugId - $bugUrl"

return [PSCustomObject]@{
    BugId  = $bugId
    Url    = $bugUrl
    DryRun = $false
}
