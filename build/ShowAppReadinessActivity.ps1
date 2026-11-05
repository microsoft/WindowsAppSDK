# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Shows what the App Readiness service did on this machine since it started.

.DESCRIPTION
    Prints the App Readiness admin log since the machine started, then lists the apps App Readiness worked on after
    -Since. Run it after the tests to check that App Readiness didn't work on apps while they ran (see
    WaitForAppReadiness.ps1). Like that script, it does nothing on versions other than Windows 10 client unless
    -AnyOS is set, and it never fails the job.

.PARAMETER Since
    The time (ISO 8601) after which to list the apps App Readiness worked on, such as when WaitForAppReadiness.ps1
    finished. Ignored if it isn't a valid time.

.PARAMETER AnyOS
    Show the activity on any Windows version, not just Windows 10 client.
#>
[CmdletBinding()]
param(
    [string]$Since = '',
    [switch]$AnyOS
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

try {
    $os = Get-CimInstance -ClassName Win32_OperatingSystem
    $isWindows10Client = ($os.ProductType -eq 1) -and ([int]$os.BuildNumber -lt 22000)
    if (-not $isWindows10Client -and -not $AnyOS) {
        Write-Host 'Not Windows 10 client, so there is nothing to show.'
    }
    else {
        $logName = 'Microsoft-Windows-AppReadiness/Admin'
        $entries = @(Get-WinEvent -FilterHashtable @{ LogName = $logName; StartTime = $os.LastBootUpTime } -ErrorAction SilentlyContinue |
            Sort-Object TimeCreated, RecordId)
        $timeFormat = "yyyy-MM-dd'T'HH:mm:ss.fff'Z'"
        Write-Host "$($entries.Count) events in $logName since the machine started at $($os.LastBootUpTime.ToUniversalTime().ToString($timeFormat)):"
        foreach ($entry in $entries) {
            $message = $entry.Message
            if ([string]::IsNullOrEmpty($message)) {
                $message = '(' + (($entry.Properties | ForEach-Object { $_.Value }) -join ', ') + ')'
            }
            Write-Host ('  {0} {1,4} {2}' -f $entry.TimeCreated.ToUniversalTime().ToString($timeFormat), $entry.Id, ($message -replace '\s+', ' '))
        }

        $sinceTime = [DateTime]::MinValue
        $styles = [Globalization.DateTimeStyles]::AdjustToUniversal -bor [Globalization.DateTimeStyles]::AssumeUniversal
        if ([DateTime]::TryParse($Since, [Globalization.CultureInfo]::InvariantCulture, $styles, [ref]$sinceTime)) {
            $later = @($entries | Where-Object { $_.TimeCreated.ToUniversalTime() -gt $sinceTime })
            $apps = @($later | ForEach-Object { [regex]::Matches([string]$_.Message, "'(?:\w+::)?([^'\s:]+_[a-z0-9]{13})'") } |
                ForEach-Object { $_.Groups[1].Value } | Sort-Object -Unique)
            Write-Host "After $($sinceTime.ToString($timeFormat)), App Readiness logged $($later.Count) events about $($apps.Count) apps."
            foreach ($app in $apps) {
                Write-Host "  $app"
            }
        }
        else {
            Write-Host "No valid -Since time ('$Since'), so the apps App Readiness worked on later aren't listed."
        }
    }
}
catch {
    Write-Host "Could not read the App Readiness log: $($_.Exception.Message)"
}

exit 0
