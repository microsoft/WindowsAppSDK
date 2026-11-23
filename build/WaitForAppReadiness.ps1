# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Waits for App Readiness to finish the work it deferred at the test user's first sign-in.

.DESCRIPTION
    At a user's first sign-in, the App Readiness service registers a few inbox apps, then suspends the rest of that
    work for about 16 minutes and logs when it will resume (event 216 in the Microsoft-Windows-AppReadiness/Admin log).
    When a test job starts right after a fresh VM signs in, App Readiness resumes in the middle of the tests. If it
    registers its apps while the tests install and launch the Dynamic Dependency Lifetime Manager (DDLM), Windows can
    reject every later activation of the DDLM with E_APPLICATION_NOT_REGISTERED (0x80270254) until the VM is
    recycled, so every test that uses the Bootstrapper fails.

    Run this just before the tests. If App Readiness has deferred work for the current user, the script waits until
    App Readiness logs that it completed the user's tasks (event 211) or stops, or until -TimeoutMinutes pass. On a VM
    that signed in long enough ago, there's nothing to wait for. The problem has only been seen on Windows 10 client,
    so by default the script does nothing on other versions. It never fails the job: problems are reported in the log.

    It sets the pipeline variable AppReadinessWaitEndTime to the time it finished (UTC, ISO 8601), which
    ShowAppReadinessActivity.ps1 uses after the tests.

.PARAMETER TimeoutMinutes
    The longest time to wait. The script also stops waiting 10 minutes after App Readiness was due to resume.

.PARAMETER AnyOS
    Check on any Windows version, not just Windows 10 client.
#>
[CmdletBinding()]
param(
    [double]$TimeoutMinutes = 25,
    [switch]$AnyOS
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

$timeFormat = "yyyy-MM-dd'T'HH:mm:ss'Z'"

# Returns when App Readiness last suspended the user's work and said it would resume, and whether it has finished that
# work since, or $null if it hasn't suspended any work for the user since the machine started.
function Get-DeferredWork([string]$Sid, [DateTime]$Since) {
    $entries = @(Get-WinEvent -FilterHashtable @{ LogName = 'Microsoft-Windows-AppReadiness/Admin'; Id = 101, 211, 216; StartTime = $Since } -ErrorAction SilentlyContinue |
        Sort-Object TimeCreated, RecordId)
    $userPattern = [regex]::Escape($Sid) + '(?!\d)'
    $suspended = @($entries | Where-Object { ($_.Id -eq 216) -and ([string]$_.Message -match $userPattern) }) | Select-Object -Last 1
    if (-not $suspended) {
        return $null
    }

    $suspendedAt = $suspended.TimeCreated.ToUniversalTime()
    $resumeAt = $null
    # The message has invisible direction marks around the parts of the date.
    if ((([string]$suspended.Message) -replace '[\u200e\u200f]', '') -match '(\d{4}-\d\d-\d\dT\d\d:\d\d:\d\d)') {
        $resumeAt = [DateTime]::SpecifyKind([DateTime]::ParseExact($Matches[1], "yyyy-MM-dd'T'HH:mm:ss", [Globalization.CultureInfo]::InvariantCulture), 'Utc')
    }

    # Only count completions after App Readiness resumed, not tasks it finished while the user's work was suspended.
    $threshold = $suspendedAt
    if ($resumeAt -and ($resumeAt.AddMinutes(-1) -gt $threshold)) {
        $threshold = $resumeAt.AddMinutes(-1)
    }
    $finished = @($entries | Where-Object {
            ($_.TimeCreated.ToUniversalTime() -gt $threshold) -and
            (($_.Id -eq 101) -or (($_.Id -eq 211) -and ([string]$_.Message -match $userPattern)))
        }) | Select-Object -First 1

    [pscustomobject]@{
        SuspendedAt = $suspendedAt
        ResumeAt = $resumeAt
        FinishedAt = if ($finished) { $finished.TimeCreated.ToUniversalTime() } else { $null }
    }
}

function Format-Time($time) {
    if ($time) { $time.ToString($timeFormat) } else { 'an unknown time' }
}

try {
    $os = Get-CimInstance -ClassName Win32_OperatingSystem
    $isWindows10Client = ($os.ProductType -eq 1) -and ([int]$os.BuildNumber -lt 22000)
    if (-not $isWindows10Client -and -not $AnyOS) {
        Write-Host 'Not Windows 10 client, so there is nothing to wait for.'
    }
    else {
        $user = "$env:USERDOMAIN\$env:USERNAME"
        $sid = [Security.Principal.WindowsIdentity]::GetCurrent().User.Value
        $work = Get-DeferredWork -Sid $sid -Since $os.LastBootUpTime
        if (-not $work) {
            Write-Host "App Readiness hasn't deferred any work for $user since the machine started."
        }
        elseif ($work.FinishedAt) {
            Write-Host ("App Readiness deferred work for {0} at {1} until {2}, and finished it at {3}." -f
                $user, (Format-Time $work.SuspendedAt), (Format-Time $work.ResumeAt), (Format-Time $work.FinishedAt))
        }
        else {
            Write-Host ("App Readiness deferred work for {0} at {1} until {2}. Waiting for it to finish before the tests start." -f
                $user, (Format-Time $work.SuspendedAt), (Format-Time $work.ResumeAt))
            $start = (Get-Date).ToUniversalTime()
            $lastReport = $start
            while ($true) {
                # Stop waiting after -TimeoutMinutes, or 10 minutes after App Readiness was due to resume. It normally
                # finishes within a minute or two of resuming.
                $deadline = $start.AddMinutes($TimeoutMinutes)
                if ($work.ResumeAt -and ($work.ResumeAt.AddMinutes(10) -lt $deadline)) {
                    $deadline = $work.ResumeAt.AddMinutes(10)
                }

                Start-Sleep -Seconds 10
                $now = (Get-Date).ToUniversalTime()
                $waited = ($now - $start).TotalSeconds
                $work = Get-DeferredWork -Sid $sid -Since $os.LastBootUpTime
                if (-not $work -or $work.FinishedAt) {
                    Write-Host ('App Readiness finished at {0}, after waiting {1:N0} s.' -f (Format-Time $(if ($work) { $work.FinishedAt })), $waited)
                    break
                }
                if ($now -ge $deadline) {
                    Write-Host ("App Readiness still hadn't finished at {0}, after waiting {1:N0} s, so the tests will start anyway." -f (Format-Time $now), $waited)
                    break
                }
                if (($now - $lastReport).TotalSeconds -ge 60) {
                    $lastReport = $now
                    Write-Host ('  Still waiting after {0:N0} s. App Readiness resumes at {1}.' -f $waited, (Format-Time $work.ResumeAt))
                }
            }
        }
    }
}
catch {
    Write-Host "Could not check App Readiness: $($_.Exception.Message)"
}
finally {
    Write-Host "##vso[task.setvariable variable=AppReadinessWaitEndTime]$((Get-Date).ToUniversalTime().ToString('o'))"
}

exit 0
