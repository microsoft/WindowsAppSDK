# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Generates and applies containment wrapping to cherry-picked code changes.

.DESCRIPTION
    Uses AI to analyze the cherry-picked diff and wrap code changes with
    IsChangeEnabled<> containment checks. Provides the AI with the original
    diff, current file contents, bug ID, and patch version symbol, along with
    containment pattern examples.

    The AI returns modified file contents. The script validates the output
    and optionally shows the diff for human review before applying.

.PARAMETER WorktreePath
    Path to the worktree with cherry-picked changes.

.PARAMETER OriginalDiff
    The diff from the original PR (for context).

.PARAMETER BugId
    The ADO bug ID for the containment macro.

.PARAMETER PatchVersionSymbol
    The WinAppSDK patch version symbol (e.g., "WinAppSDK_1_7_9").

.PARAMETER VersionString
    The version string (e.g., "1.7.9").

.PARAMETER PrTitle
    The original PR title (for the comment).

.PARAMETER SkipApproval
    If set, skips the human review of the containment diff.
    By default, the diff is shown for approval before applying.

.EXAMPLE
    ./Add-ContainmentWrapping.ps1 -WorktreePath "./worktree" `
        -OriginalDiff $diff -BugId 61124052 -PatchVersionSymbol "WinAppSDK_1_7_9" `
        -VersionString "1.7.9" -PrTitle "Fix reset activity data"

.NOTES
    This is the most complex script in the skill. It delegates to AI for
    semantic understanding of which code to wrap but validates the output.
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory)]
    [string]$WorktreePath,

    [Parameter(Mandatory)]
    [string]$OriginalDiff,

    [Parameter(Mandatory)]
    [int]$BugId,

    [Parameter(Mandatory)]
    [string]$PatchVersionSymbol,

    [Parameter(Mandatory)]
    [string]$VersionString,

    [Parameter(Mandatory)]
    [string]$PrTitle,

    [switch]$SkipApproval
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

. "$PSScriptRoot/ServicingLib.ps1"

# Load the containment pattern guide for AI context
$guideFile = Join-Path $PSScriptRoot '..\references\containment-pattern-guide.md'
$containmentGuide = ''
if (Test-Path $guideFile) {
    $containmentGuide = Get-Content -LiteralPath $guideFile -Raw
}

# Load the prompt template
$promptTemplate = Join-Path $PSScriptRoot '..\templates\containment-prompt.md'
if (-not (Test-Path $promptTemplate)) {
    Write-Error "Containment prompt template not found: $promptTemplate"
    exit 1
}
$promptText = Get-Content -LiteralPath $promptTemplate -Raw

# Get the current diff in the worktree (what the cherry-pick changed)
$cherryPickDiff = git -C $WorktreePath diff HEAD 2>&1
if ($LASTEXITCODE -ne 0) {
    Write-Error "Failed to get worktree diff: $cherryPickDiff"
    exit 1
}
$cherryPickDiff = $cherryPickDiff -join "`n"

# Identify changed source files (C/C++ only - these need containment)
$changedFiles = git -C $WorktreePath diff --name-only HEAD 2>$null
$sourceFiles = @()
if ($null -ne $changedFiles) {
    foreach ($f in $changedFiles) {
        $trimmed = $f.Trim()
        if ($trimmed -match '\.(cpp|h|c|hpp)$') {
            $sourceFiles += $trimmed
        }
    }
}

if ($sourceFiles.Count -eq 0) {
    Warn "No C/C++ source files changed. Containment wrapping may not be needed."
    return [PSCustomObject]@{
        Applied       = $false
        FilesModified = @()
        Reason        = 'No C/C++ source files in diff'
    }
}

# Collect current file contents for the AI
$fileContents = @{}
foreach ($sf in $sourceFiles) {
    $fullPath = Join-Path $WorktreePath $sf
    if (Test-Path $fullPath) {
        $fileContents[$sf] = Get-Content -LiteralPath $fullPath -Raw
    }
}

# Build the AI prompt by substituting template variables
$prompt = $promptText
$prompt = $prompt -replace '\{\{BUG_ID\}\}', $BugId
$prompt = $prompt -replace '\{\{PATCH_VERSION_SYMBOL\}\}', $PatchVersionSymbol
$prompt = $prompt -replace '\{\{VERSION_STRING\}\}', $VersionString
$prompt = $prompt -replace '\{\{PR_TITLE\}\}', $PrTitle
$prompt = $prompt -replace '\{\{CONTAINMENT_GUIDE\}\}', $containmentGuide
$prompt = $prompt -replace '\{\{ORIGINAL_DIFF\}\}', $OriginalDiff
$prompt = $prompt -replace '\{\{CHERRY_PICK_DIFF\}\}', $cherryPickDiff

# Append file contents
$filesSection = ""
foreach ($key in $fileContents.Keys) {
    $filesSection += "`n### File: $key`n``````cpp`n$($fileContents[$key])`n```````n"
}
$prompt = $prompt -replace '\{\{FILE_CONTENTS\}\}', $filesSection

# Call AI
Write-Verbose "Sending containment wrapping prompt to AI..."
$systemPrompt = @"
You are a Windows App SDK servicing engineer. You wrap cherry-picked code changes with containment checks.
You MUST return complete file contents for each modified file in the exact format specified.
Do NOT add any commentary outside the file blocks. Only modify files that need containment wrapping.
"@

$aiArgs = @{
    Prompt          = $prompt
    SystemPrompt    = $systemPrompt
    MaxTokens       = 8192
    FallbackToManual = $true
}
if ($SkipApproval) {
    $aiArgs['SkipApproval'] = $true
}

$aiResponse = & "$PSScriptRoot/Get-AiCompletion.ps1" @aiArgs

if (-not $aiResponse) {
    Write-Error "AI returned empty response for containment wrapping."
    exit 1
}

# Parse AI response - expect blocks like:
# === FILE: path/to/file.cpp ===
# <contents>
# === END FILE ===
$filePattern = '(?s)=== FILE: (.+?) ===\r?\n(.*?)=== END FILE ==='
$matches = [regex]::Matches($aiResponse, $filePattern)

if ($matches.Count -eq 0) {
    Warn "AI response did not contain expected file blocks. Attempting line-based parse..."

    # Try alternative format: ```cpp:path/to/file.cpp
    $altPattern = '(?s)```(?:cpp|c|h)?:(.+?)\r?\n(.*?)```'
    $matches = [regex]::Matches($aiResponse, $altPattern)
}

$modifiedFiles = @()

if ($matches.Count -eq 0) {
    Err "Could not parse AI response into file blocks."
    Err "AI response (first 500 chars): $($aiResponse.Substring(0, [Math]::Min(500, $aiResponse.Length)))"
    Write-Error "Failed to parse containment wrapping output from AI."
    exit 1
}

foreach ($match in $matches) {
    $filePath = $match.Groups[1].Value.Trim()
    $content = $match.Groups[2].Value

    # Validate: check for bracket balance (basic sanity)
    $openBraces = ($content.ToCharArray() | Where-Object { $_ -eq '{' }).Count
    $closeBraces = ($content.ToCharArray() | Where-Object { $_ -eq '}' }).Count
    if ($openBraces -ne $closeBraces) {
        Warn "Warning: Bracket imbalance in $filePath (open: $openBraces, close: $closeBraces)"
    }

    # Validate: check that the containment macro is present
    if ($content -notmatch "WINAPPSDK_CHANGEID_$BugId") {
        Warn "Warning: Expected WINAPPSDK_CHANGEID_$BugId not found in $filePath"
    }

    $fullPath = Join-Path $WorktreePath $filePath
    if (-not (Test-Path $fullPath)) {
        Warn "File not found in worktree: $filePath (skipping)"
        continue
    }

    # Write the modified content
    Set-Content -LiteralPath $fullPath -Value $content -Encoding UTF8 -NoNewline
    $modifiedFiles += $filePath
    Ok "  Updated: $filePath"
}

# Show the final diff for approval unless SkipApproval
if (-not $SkipApproval -and $modifiedFiles.Count -gt 0) {
    Write-Host ""
    Write-Host "Containment diff:" -ForegroundColor Yellow
    $containmentDiff = git -C $WorktreePath diff 2>$null
    Write-Host ($containmentDiff -join "`n") -ForegroundColor White

    Write-Host ""
    Write-Host "[A]pprove containment / [R]eject? " -ForegroundColor Yellow -NoNewline
    $choice = Read-Host
    if ($choice.ToUpper() -ne 'A') {
        # Revert changes
        git -C $WorktreePath checkout -- . 2>$null | Out-Null
        Write-Error "Containment wrapping rejected by user."
        exit 1
    }
}

Ok "Containment wrapping applied to $($modifiedFiles.Count) file(s)."

return [PSCustomObject]@{
    Applied       = $true
    FilesModified = $modifiedFiles
}
