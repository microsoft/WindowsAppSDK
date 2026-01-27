# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Retrieves or updates area-to-contact mapping for Windows App SDK feature areas.

.DESCRIPTION
    This script provides access to the feature area contact directory.
    It can look up contacts for specific areas or display the full mapping.

.PARAMETER Area
    Specific area label to look up (e.g., "area-Notification").
    If omitted, returns all area contacts.

.PARAMETER Update
    Interactively update contact information for an area.

.PARAMETER OutputFormat
    Output format: 'table', 'json', or 'list'. Default: table

.EXAMPLE
    ./Get-AreaContacts.ps1

.EXAMPLE
    ./Get-AreaContacts.ps1 -Area "area-Notification"

.EXAMPLE
    ./Get-AreaContacts.ps1 -OutputFormat json
#>

[CmdletBinding()]
param(
    [Parameter()]
    [string]$Area,

    [Parameter()]
    [switch]$Update,

    [Parameter()]
    [ValidateSet("table", "json", "list")]
    [string]$OutputFormat = "table"
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

# Import shared functions
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
. "$ScriptDir\ReportLib.ps1"

# Load contacts
$ContactsPath = Join-Path (Split-Path $ScriptDir -Parent) "references\area-contacts.json"
$AreaContacts = Get-AreaContacts -ContactsPath $ContactsPath

function Format-ContactsTable {
    <#
    .SYNOPSIS
        Formats contacts as a table.
    #>
    param([hashtable]$Contacts)

    $data = @()
    foreach ($area in ($Contacts.Keys | Sort-Object)) {
        $contact = $Contacts[$area]
        $data += [PSCustomObject]@{
            Area = $area
            PrimaryContact = $contact.primary
            SecondaryContact = if ($contact.secondary) { $contact.secondary } else { "-" }
        }
    }

    return $data | Format-Table -AutoSize
}

function Format-ContactsList {
    <#
    .SYNOPSIS
        Formats contacts as a simple list.
    #>
    param([hashtable]$Contacts)

    $sb = [System.Text.StringBuilder]::new()

    foreach ($area in ($Contacts.Keys | Sort-Object)) {
        $contact = $Contacts[$area]
        $line = "$area : $($contact.primary)"
        if ($contact.secondary) {
            $line += ", $($contact.secondary)"
        }
        [void]$sb.AppendLine($line)
    }

    return $sb.ToString()
}

function Update-AreaContact {
    <#
    .SYNOPSIS
        Interactively updates contact for an area.
    #>
    param(
        [string]$AreaName,
        [hashtable]$Contacts,
        [string]$OutputPath
    )

    if (-not $Contacts.ContainsKey($AreaName)) {
        Write-Host "Area '$AreaName' not found. Create new entry? (y/n)" -ForegroundColor Yellow
        $response = Read-Host
        if ($response -ne 'y') {
            return
        }
    }

    $current = $Contacts[$AreaName]
    if ($current) {
        Write-Host "Current primary contact: $($current.primary)" -ForegroundColor Cyan
        if ($current.secondary) {
            Write-Host "Current secondary contact: $($current.secondary)" -ForegroundColor Cyan
        }
    }

    Write-Host ""
    $newPrimary = Read-Host "Enter new primary contact (or press Enter to keep)"
    $newSecondary = Read-Host "Enter new secondary contact (or press Enter to keep/clear)"

    if ($newPrimary -or $newSecondary) {
        $Contacts[$AreaName] = @{
            primary = if ($newPrimary) { $newPrimary } else { $current.primary }
            secondary = if ($newSecondary) { $newSecondary } elseif ($newSecondary -eq "") { $null } else { $current.secondary }
        }

        # Save to file using .NET for consistent UTF-8 without BOM across PS versions
        $json = @{ areaContacts = $Contacts; lastUpdated = (Get-Date -Format "yyyy-MM") }
        $jsonContent = $json | ConvertTo-Json -Depth 5
        [System.IO.File]::WriteAllText($OutputPath, $jsonContent, [System.Text.UTF8Encoding]::new($false))

        Write-Host "Contact updated successfully!" -ForegroundColor Green
    }
    else {
        Write-Host "No changes made." -ForegroundColor Gray
    }
}

# ============================================================================
# Main Execution
# ============================================================================

if ($Update) {
    if (-not $Area) {
        Write-Error "Please specify -Area when using -Update"
        exit 1
    }
    Update-AreaContact -AreaName $Area -Contacts $AreaContacts -OutputPath $ContactsPath
    exit 0
}

if ($Area) {
    # Look up specific area
    if ($AreaContacts.ContainsKey($Area)) {
        $contact = $AreaContacts[$Area]

        switch ($OutputFormat) {
            "json" {
                @{ $Area = $contact } | ConvertTo-Json
            }
            "list" {
                $line = "$Area : $($contact.primary)"
                if ($contact.secondary) {
                    $line += ", $($contact.secondary)"
                }
                Write-Output $line
            }
            default {
                Write-Host ""
                Write-Host "Feature Area: $Area" -ForegroundColor Cyan
                Write-Host "  Primary Contact: $($contact.primary)" -ForegroundColor Green
                if ($contact.secondary) {
                    Write-Host "  Secondary Contact: $($contact.secondary)" -ForegroundColor Green
                }
                Write-Host ""
            }
        }
    }
    else {
        Write-Warning "Area '$Area' not found in contact directory."
        Write-Host ""
        Write-Host "Available areas:" -ForegroundColor Yellow
        $AreaContacts.Keys | Sort-Object | ForEach-Object { Write-Host "  $_" }
        exit 1
    }
}
else {
    # Show all contacts
    switch ($OutputFormat) {
        "json" {
            $AreaContacts | ConvertTo-Json -Depth 5
        }
        "list" {
            Format-ContactsList -Contacts $AreaContacts
        }
        default {
            Write-Host ""
            Write-Host "Windows App SDK Feature Area Contacts" -ForegroundColor Cyan
            Write-Host "======================================" -ForegroundColor Cyan
            Write-Host ""
            Format-ContactsTable -Contacts $AreaContacts
        }
    }
}
