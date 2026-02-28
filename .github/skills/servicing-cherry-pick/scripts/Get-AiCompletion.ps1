# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.

<#
.SYNOPSIS
    AI invocation wrapper that sends a prompt and returns the response.

.DESCRIPTION
    Single entry point for all AI calls in the servicing workflow. Tries AI
    providers in priority order:

      1. GitHub Copilot CLI (copilot) — preferred, most widely available
      2. Claude CLI (claude) — fallback
      3. Manual input — human provides the response interactively

    Supports -RequireApproval to let humans review/edit AI output before use.

.PARAMETER Prompt
    The prompt text to send to the AI.

.PARAMETER SystemPrompt
    Optional system prompt to set context for the AI.

.PARAMETER MaxTokens
    Maximum tokens in the response. Defaults to 4096.

.PARAMETER RequireApproval
    If set, displays the AI output and prompts the user to approve, edit, or reject.

.PARAMETER FallbackToManual
    If set, when no AI CLI is available, prompt the user for manual input
    instead of failing.

.PARAMETER Provider
    Force a specific provider instead of auto-detecting. Valid values:
    'copilot', 'claude', 'manual'.

.EXAMPLE
    $response = ./Get-AiCompletion.ps1 -Prompt "Name this enum entry..." -RequireApproval

.EXAMPLE
    $response = ./Get-AiCompletion.ps1 -Prompt "..." -Provider claude

.NOTES
    Provider priority: copilot → claude → manual.
    Set -Provider to skip auto-detection and force a specific backend.
#>

[CmdletBinding()]
param(
    [Parameter(Mandatory)]
    [string]$Prompt,

    [Parameter()]
    [string]$SystemPrompt,

    [Parameter()]
    [int]$MaxTokens = 4096,

    [switch]$RequireApproval,

    [switch]$FallbackToManual,

    [Parameter()]
    [ValidateSet('copilot', 'claude', 'manual')]
    [string]$Provider
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = 'Stop'

. "$PSScriptRoot/ServicingLib.ps1"

# ── Provider Detection ───────────────────────────────────────────────────────

function Test-CliAvailable {
    param([string]$Command)
    try {
        $null = Get-Command $Command -ErrorAction Stop
        return $true
    }
    catch {
        return $false
    }
}

# Detect available providers in priority order: copilot → claude
$hasCopilot = Test-CliAvailable 'copilot'
$hasClaude  = Test-CliAvailable 'claude'

# Determine which provider to use
$selectedProvider = $null

if ($Provider) {
    # User forced a specific provider
    $selectedProvider = $Provider
    if ($Provider -eq 'copilot' -and -not $hasCopilot) {
        Warn "Forced provider 'copilot' but copilot CLI not found in PATH."
    }
    elseif ($Provider -eq 'claude' -and -not $hasClaude) {
        Warn "Forced provider 'claude' but claude CLI not found in PATH."
    }
}
else {
    # Auto-detect in priority order
    if ($hasCopilot) {
        $selectedProvider = 'copilot'
    }
    elseif ($hasClaude) {
        $selectedProvider = 'claude'
    }
    else {
        $selectedProvider = 'manual'
    }
}

Write-Verbose "AI provider: $selectedProvider (copilot=$(if($hasCopilot){'yes'}else{'no'}), claude=$(if($hasClaude){'yes'}else{'no'}))"

# ── Provider Invocation ──────────────────────────────────────────────────────

$response = $null
$providerSucceeded = $false

# --- Copilot CLI ---
if ($selectedProvider -eq 'copilot') {
    Write-Verbose "Sending prompt to copilot CLI..."

    $copilotArgs = @('-p', $Prompt, '-s')

    if ($SystemPrompt) {
        # Prepend system prompt as context to the prompt itself since copilot
        # doesn't have a separate --system-prompt flag
        $copilotArgs = @('-p', "${SystemPrompt}`n`n${Prompt}", '-s')
    }

    $response = & copilot @copilotArgs 2>&1

    if ($LASTEXITCODE -ne 0) {
        Warn "Copilot CLI returned non-zero exit code: $LASTEXITCODE"
        # Fall through to next provider
        if ($hasClaude) {
            Warn "Falling back to claude CLI..."
            $selectedProvider = 'claude'
        }
        elseif ($FallbackToManual) {
            Warn "Falling back to manual input..."
            $selectedProvider = 'manual'
        }
        else {
            Write-Error "Copilot CLI failed and no fallback available. Output: $response"
            exit 1
        }
    }
    else {
        $response = $response -join "`n"
        $providerSucceeded = $true
    }
}

# --- Claude CLI ---
if ($selectedProvider -eq 'claude' -and -not $providerSucceeded) {
    Write-Verbose "Sending prompt to claude CLI..."

    $claudeArgs = @('--print')

    if ($SystemPrompt) {
        $claudeArgs += @('--system-prompt', $SystemPrompt)
    }

    $claudeArgs += @('--max-turns', '1')

    $response = $Prompt | & claude @claudeArgs 2>&1

    if ($LASTEXITCODE -ne 0) {
        Warn "Claude CLI returned non-zero exit code: $LASTEXITCODE"
        if ($FallbackToManual) {
            Warn "Falling back to manual input..."
            $selectedProvider = 'manual'
        }
        else {
            Write-Error "Claude CLI failed and no fallback available. Output: $response"
            exit 1
        }
    }
    else {
        $response = $response -join "`n"
        $providerSucceeded = $true
    }
}

# --- Manual Input ---
if ($selectedProvider -eq 'manual' -and -not $providerSucceeded) {
    if (-not $FallbackToManual -and -not $Provider) {
        Write-Error "No AI CLI available (copilot, claude) and -FallbackToManual not set."
        exit 1
    }

    Write-Host ""
    Write-Host ("=" * 70) -ForegroundColor Yellow
    Write-Host "  AI COMPLETION NEEDED (manual mode)" -ForegroundColor Yellow
    Write-Host ("=" * 70) -ForegroundColor Yellow
    Write-Host ""
    Write-Host "The following prompt requires an AI response. Please provide the output manually." -ForegroundColor White
    Write-Host ""
    Write-Host "--- PROMPT START ---" -ForegroundColor DarkGray
    Write-Host $Prompt -ForegroundColor White
    Write-Host "--- PROMPT END ---" -ForegroundColor DarkGray
    Write-Host ""

    Write-Host "Enter your response (type 'END' on a new line when done):" -ForegroundColor Yellow
    $lines = @()
    while ($true) {
        $line = Read-Host
        if ($line -eq 'END') { break }
        $lines += $line
    }
    $response = $lines -join "`n"
    $providerSucceeded = $true
}

# ── Approval Gate ────────────────────────────────────────────────────────────

if ($RequireApproval -and $response) {
    Write-Host ""
    Write-Host ("=" * 70) -ForegroundColor Yellow
    Write-Host "  AI OUTPUT - REVIEW REQUIRED" -ForegroundColor Yellow
    Write-Host ("=" * 70) -ForegroundColor Yellow
    Write-Host ""
    Write-Host $response -ForegroundColor White
    Write-Host ""
    Write-Host ("=" * 70) -ForegroundColor Yellow

    while ($true) {
        Write-Host "[A]pprove / [E]dit / [R]eject? " -ForegroundColor Yellow -NoNewline
        $choice = Read-Host

        switch ($choice.ToUpper()) {
            'A' {
                Ok "Output approved."
                break
            }
            'E' {
                Write-Host "Enter your edited response (type 'END' on a new line when done):" -ForegroundColor Yellow
                $lines = @()
                while ($true) {
                    $line = Read-Host
                    if ($line -eq 'END') { break }
                    $lines += $line
                }
                $response = $lines -join "`n"
                Ok "Edited response accepted."
                break
            }
            'R' {
                Write-Error "AI output rejected by user."
                exit 1
            }
            default {
                Warn "Please enter A, E, or R."
                continue
            }
        }
        break
    }
}

return $response
