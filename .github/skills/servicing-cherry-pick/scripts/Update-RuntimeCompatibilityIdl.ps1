# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Inserts a new enum entry into RuntimeCompatibilityOptions.idl.

.DESCRIPTION
    Deterministically adds a new RuntimeCompatibilityChange enum entry to the IDL file
    in the worktree. Inserts the entry with a version comment before the closing '};'
    of the enum block.

.PARAMETER WorktreePath
    The path to the worktree containing the IDL file.

.PARAMETER EnumName
    The name for the new enum entry (e.g., "DeploymentManager_ResetActivityDataFix").

.PARAMETER BugId
    The ADO bug ID that becomes the enum value.

.PARAMETER VersionString
    The version string for the comment (e.g., "1.7.9").

.PARAMETER IdlRelativePath
    Relative path to the IDL file within the repo. Defaults to config value.

.EXAMPLE
    ./Update-RuntimeCompatibilityIdl.ps1 -WorktreePath "./worktree" `
        -EnumName "FileTypeChoices_InsertionOrderFix" -BugId 61124052 `
        -VersionString "1.7.9"

.NOTES
    This is a deterministic operation - no AI needed. The script finds the
    RuntimeCompatibilityChange enum and inserts the new entry before the closing '};'.
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory)]
    [string]$WorktreePath,

    [Parameter(Mandatory)]
    [string]$EnumName,

    [Parameter(Mandatory)]
    [int]$BugId,

    [Parameter(Mandatory)]
    [string]$VersionString,

    [Parameter()]
    [string]$IdlRelativePath,

    [Parameter()]
    [string]$ConfigPath
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

. "$PSScriptRoot/ServicingLib.ps1"

if (-not $IdlRelativePath) {
    $config = Get-ServicingConfig -ConfigPath $ConfigPath
    $IdlRelativePath = $config.idl.relativePath
}

$idlFullPath = Join-Path $WorktreePath $IdlRelativePath

if (-not (Test-Path $idlFullPath)) {
    Write-Error "IDL file not found at: $idlFullPath"
    exit 1
}

Write-Verbose "Updating IDL at: $idlFullPath"
Write-Verbose "  Adding: $EnumName = $BugId (version $VersionString)"

# Read the IDL content
$lines = Get-Content -LiteralPath $idlFullPath

# Find the RuntimeCompatibilityChange enum and its closing '};'
$enumStartIndex = -1
$enumEndIndex = -1
$inEnum = $false

for ($i = 0; $i -lt $lines.Count; $i++) {
    if ($lines[$i] -match 'enum\s+RuntimeCompatibilityChange') {
        $enumStartIndex = $i
        $inEnum = $true
    }
    if ($inEnum -and $lines[$i] -match '^\s*\};') {
        $enumEndIndex = $i
        break
    }
}

if ($enumStartIndex -eq -1 -or $enumEndIndex -eq -1) {
    Write-Error "Could not find RuntimeCompatibilityChange enum in $idlFullPath"
    exit 1
}

# Check if this version comment already exists
$versionCommentExists = $false
$lastVersionCommentIndex = -1
for ($i = $enumStartIndex; $i -lt $enumEndIndex; $i++) {
    if ($lines[$i] -match "//\s*$([regex]::Escape($VersionString))\s*$") {
        $versionCommentExists = $true
        $lastVersionCommentIndex = $i
    }
}

# Check if this enum entry already exists
for ($i = $enumStartIndex; $i -lt $enumEndIndex; $i++) {
    if ($lines[$i] -match "$EnumName\s*=\s*$BugId") {
        Warn "Enum entry '$EnumName = $BugId' already exists in IDL. Skipping."
        return [PSCustomObject]@{
            Updated  = $false
            FilePath = $idlFullPath
            Reason   = 'Already exists'
        }
    }
}

# Build the new lines to insert
$newLines = @()
if (-not $versionCommentExists) {
    # Add a blank line separator before the version comment (if there's content above)
    $prevLine = $lines[$enumEndIndex - 1].Trim()
    if ($prevLine -ne '' -and $prevLine -ne '{') {
        $newLines += ''
    }
    $newLines += "        // $VersionString"
}

$newLines += "        $EnumName = $BugId,"

# Insert before the closing '};'
$result = @()
$result += $lines[0..($enumEndIndex - 1)]
$result += $newLines
$result += $lines[$enumEndIndex..($lines.Count - 1)]

# Write back
$result | Set-Content -LiteralPath $idlFullPath -Encoding UTF8

Ok "IDL updated: $EnumName = $BugId (// $VersionString)"

return [PSCustomObject]@{
    Updated  = $true
    FilePath = $idlFullPath
    Entry    = "$EnumName = $BugId"
}
