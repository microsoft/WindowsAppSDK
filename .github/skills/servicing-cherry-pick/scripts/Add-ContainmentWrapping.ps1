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

    For multi-file PRs, processes each file individually so:
    - Prompts stay small and focused (better AI quality)
    - Approval is per-file (reject one without losing the rest)
    - A failure on one file doesn't block the others

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
    Multi-file PRs are processed one file at a time for reliability.
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

Info "Found $($sourceFiles.Count) C/C++ file(s) to wrap with containment."

# ── Shared AI config ─────────────────────────────────────────────────────────

$systemPrompt = @"
You are a Windows App SDK servicing engineer. You wrap cherry-picked code changes with containment checks.
You MUST return the complete file contents in the exact format specified.
Do NOT add any commentary outside the file block. Only modify code that was changed by the cherry-pick.
"@

# ── Per-file processing function ─────────────────────────────────────────────

function Invoke-ContainmentForFile {
    param(
        [string]$FilePath,
        [string]$FileContent,
        [string]$FileDiff,
        [string]$OrigDiff,
        [int]$FileIndex,
        [int]$FileTotal
    )

    Write-Host ""
    Write-Host "  [$FileIndex/$FileTotal] Processing: $FilePath" -ForegroundColor White

    # Build per-file prompt
    $prompt = $promptText
    $prompt = $prompt -replace '\{\{BUG_ID\}\}', $BugId
    $prompt = $prompt -replace '\{\{PATCH_VERSION_SYMBOL\}\}', $PatchVersionSymbol
    $prompt = $prompt -replace '\{\{VERSION_STRING\}\}', $VersionString
    $prompt = $prompt -replace '\{\{PR_TITLE\}\}', $PrTitle
    $prompt = $prompt -replace '\{\{CONTAINMENT_GUIDE\}\}', $containmentGuide
    $prompt = $prompt -replace '\{\{ORIGINAL_DIFF\}\}', $OrigDiff
    $prompt = $prompt -replace '\{\{CHERRY_PICK_DIFF\}\}', $FileDiff
    $prompt = $prompt -replace '\{\{FILE_CONTENTS\}\}', "`n### File: $FilePath`n``````cpp`n$FileContent`n```````n"

    $aiArgs = @{
        Prompt           = $prompt
        SystemPrompt     = $systemPrompt
        MaxTokens        = 8192
        FallbackToManual = $true
        SkipApproval     = $true  # We handle approval ourselves per-file
    }

    $aiResponse = & "$PSScriptRoot/Get-AiCompletion.ps1" @aiArgs

    if (-not $aiResponse) {
        Warn "  AI returned empty response for $FilePath"
        return $null
    }

    # Parse the response - expect a single file block
    $filePattern = '(?s)=== FILE: (.+?) ===\r?\n(.*?)=== END FILE ==='
    $parsed = [regex]::Matches($aiResponse, $filePattern)

    if ($parsed.Count -eq 0) {
        # Try alternative format
        $altPattern = '(?s)```(?:cpp|c|h)?:?(?:.+?)?\r?\n(.*?)```'
        $altParsed = [regex]::Matches($aiResponse, $altPattern)
        if ($altParsed.Count -gt 0) {
            return $altParsed[0].Groups[1].Value
        }
        Warn "  Could not parse AI response for $FilePath"
        return $null
    }

    return $parsed[0].Groups[2].Value
}

# ── Process each file ────────────────────────────────────────────────────────

$modifiedFiles = @()
$skippedFiles = @()
$fileIndex = 0

foreach ($sf in $sourceFiles) {
    $fileIndex++

    $fullPath = Join-Path $WorktreePath $sf
    if (-not (Test-Path $fullPath)) {
        Warn "  File not found in worktree: $sf (skipping)"
        $skippedFiles += $sf
        continue
    }

    # Get per-file content and diff
    $fileContent = Get-Content -LiteralPath $fullPath -Raw
    $fileDiff = (git -C $WorktreePath diff HEAD -- $sf 2>$null) -join "`n"

    if (-not $fileDiff) {
        Warn "  No diff for $sf (skipping)"
        $skippedFiles += $sf
        continue
    }

    # For context, include the original diff but only the portion relevant to this file.
    # Extract the file's hunk from the original PR diff if possible.
    $origFileDiff = ''
    $escapedPath = [regex]::Escape($sf)
    $origFileMatch = [regex]::Match($OriginalDiff, "(?s)(diff --git a/$escapedPath.+?)(?=diff --git a/|$)")
    if ($origFileMatch.Success) {
        $origFileDiff = $origFileMatch.Value
    }
    else {
        # Fall back to abbreviated summary if we can't extract the specific file
        $origFileDiff = "(Full original diff not shown - see cherry-pick diff below for this file's changes)"
    }

    # Call AI for this file
    $newContent = Invoke-ContainmentForFile `
        -FilePath $sf `
        -FileContent $fileContent `
        -FileDiff $fileDiff `
        -OrigDiff $origFileDiff `
        -FileIndex $fileIndex `
        -FileTotal $sourceFiles.Count

    if ($null -eq $newContent) {
        Warn "  Failed to generate containment for $sf"
        $skippedFiles += $sf
        continue
    }

    # Validate: bracket balance
    $openBraces = ($newContent.ToCharArray() | Where-Object { $_ -eq '{' }).Count
    $closeBraces = ($newContent.ToCharArray() | Where-Object { $_ -eq '}' }).Count
    if ($openBraces -ne $closeBraces) {
        Warn "  Bracket imbalance in $sf (open: $openBraces, close: $closeBraces)"
    }

    # Validate: containment macro present
    if ($newContent -notmatch "WINAPPSDK_CHANGEID_$BugId") {
        Warn "  Expected WINAPPSDK_CHANGEID_$BugId not found in $sf"
    }

    # Write the modified content
    Set-Content -LiteralPath $fullPath -Value $newContent -Encoding UTF8 -NoNewline

    # Per-file approval
    if (-not $SkipApproval) {
        Write-Host ""
        Write-Host "  Containment diff for $sf`:" -ForegroundColor Yellow
        $fileDiffAfter = git -C $WorktreePath diff -- $sf 2>$null
        Write-Host ($fileDiffAfter -join "`n") -ForegroundColor White
        Write-Host ""
        Write-Host "  [A]pprove / [R]eject $sf`? " -ForegroundColor Yellow -NoNewline
        $choice = Read-Host
        if ($choice.ToUpper() -ne 'A') {
            # Revert just this file
            git -C $WorktreePath checkout HEAD -- $sf 2>$null | Out-Null
            Warn "  Reverted $sf"
            $skippedFiles += $sf
            continue
        }
    }

    $modifiedFiles += $sf
    Ok "  Accepted: $sf"
}

# ── Summary ──────────────────────────────────────────────────────────────────

if ($modifiedFiles.Count -gt 0) {
    Ok "Containment wrapping applied to $($modifiedFiles.Count) file(s)."
}
if ($skippedFiles.Count -gt 0) {
    Warn "Skipped $($skippedFiles.Count) file(s): $($skippedFiles -join ', ')"
}

return [PSCustomObject]@{
    Applied       = ($modifiedFiles.Count -gt 0)
    FilesModified = $modifiedFiles
    FilesSkipped  = $skippedFiles
}
