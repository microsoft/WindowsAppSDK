# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Shows what Windows Update did during the tests, and restores the services StopWindowsUpdate.ps1 stopped.

.DESCRIPTION
    Run this after the tests, even if they failed. It reads the settings StopWindowsUpdate.ps1 saved to -StatePath, and
    reports whether anything enabled or started those services again during the tests. It lists the package deployments
    started since StopWindowsUpdate.ps1 ran, by the process that requested them, so each run shows whether Windows
    Update still deployed packages during the tests. It then restores each service's startup type and starts the
    services that were running, because the test VMs also run other pipelines' jobs.

    If StopWindowsUpdate.ps1 saved no settings, for example on Windows versions other than Windows 10 client, there's
    nothing to restore. The script never fails the job: problems are reported in the log.

.PARAMETER StatePath
    The file StopWindowsUpdate.ps1 saved the services' settings to.
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string]$StatePath
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

$appxLog = 'Microsoft-Windows-AppXDeploymentServer/Operational'
$timeFormat = "yyyy-MM-dd'T'HH:mm:ss'Z'"

# Returns a service's status, and its startup type as sc.exe names it: auto, delayed-auto, demand or disabled.
function Get-ServiceState([string]$Name) {
    $service = Get-Service -Name $Name
    $key = Get-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Services\$Name"
    $delayed = ($key.PSObject.Properties.Name -contains 'DelayedAutostart') -and ($key.DelayedAutostart -eq 1)
    $start = switch ([int]$key.Start) {
        2 { if ($delayed) { 'delayed-auto' } else { 'auto' } }
        3 { 'demand' }
        4 { 'disabled' }
        default { "unknown ($($key.Start))" }
    }
    [pscustomobject]@{ Name = $Name; Status = [string]$service.Status; Start = $start }
}

try {
    if (-not (Test-Path -LiteralPath $StatePath)) {
        Write-Host 'StopWindowsUpdate.ps1 saved no service settings, so there is nothing to restore.'
    }
    else {
        $saved = Get-Content -LiteralPath $StatePath -Raw | ConvertFrom-Json
        # PowerShell 7 turns the saved time back into a DateTime; Windows PowerShell leaves it a string.
        $stoppedAt = if ($saved.StoppedAt -is [datetime]) { $saved.StoppedAt } else {
            [DateTime]::Parse($saved.StoppedAt, [Globalization.CultureInfo]::InvariantCulture, [Globalization.DateTimeStyles]::RoundtripKind)
        }

        # The package deployments started since Windows Update was stopped, by the process that requested them.
        $deployments = @(foreach ($entry in @(Get-WinEvent -FilterHashtable @{ LogName = $appxLog; Id = 603; StartTime = $stoppedAt.ToLocalTime() } -ErrorAction SilentlyContinue)) {
                $data = @{}
                foreach ($item in ([xml]$entry.ToXml()).SelectNodes("//*[local-name()='Data']")) {
                    $data[$item.GetAttribute('Name')] = $item.InnerText
                }
                [pscustomobject]@{ Time = $entry.TimeCreated.ToUniversalTime(); Caller = [string]$data['CallingProcess']; Package = [string]$data['Path'] }
            })
        Write-Host ('{0} package deployments started after Windows Update was stopped at {1}:' -f $deployments.Count, $stoppedAt.ToUniversalTime().ToString($timeFormat))
        foreach ($group in @($deployments | Group-Object Caller | Sort-Object Count -Descending)) {
            Write-Host ('  {0,5} by {1}' -f $group.Count, $(if ($group.Name) { $group.Name } else { 'an unknown process' }))
        }
        $byWindowsUpdate = @($deployments | Where-Object { $_.Caller -match 'wuauserv' } | Sort-Object Time)
        if ($byWindowsUpdate.Count) {
            Write-Host "Windows Update deployed packages during the tests:"
            foreach ($deployment in $byWindowsUpdate) {
                Write-Host ('  {0} {1}' -f $deployment.Time.ToString($timeFormat), $deployment.Package)
            }
        }
        else {
            Write-Host 'Windows Update deployed no packages during the tests.'
        }

        foreach ($service in @($saved.Services)) {
            $current = Get-ServiceState $service.Name
            Write-Host ('{0} is {1}, with startup type {2}. Before the tests it was {3}, with startup type {4}.' -f
                $current.Name, $current.Status, $current.Start, $service.Status, $service.Start)
            if ($service.Disabled -and ($current.Start -ne 'disabled')) {
                Write-Host "  Something changed the startup type of $($service.Name) during the tests."
            }
            if (($service.Disabled -or $service.Stopped) -and ($current.Status -ne 'Stopped')) {
                Write-Host "  Something started $($service.Name) again during the tests."
            }

            if ($current.Start -ne $service.Start) {
                if ($service.Start -notin 'auto', 'delayed-auto', 'demand', 'disabled') {
                    Write-Host "  Can't restore the startup type of $($service.Name) to $($service.Start)."
                }
                else {
                    $output = & { $ErrorActionPreference = 'Continue'; & sc.exe config $service.Name start= $service.Start 2>&1 }
                    if ($LASTEXITCODE -eq 0) {
                        Write-Host "  Restored the startup type of $($service.Name) to $($service.Start)."
                    }
                    else {
                        Write-Host "  Could not restore the startup type of $($service.Name) (sc.exe exit code $LASTEXITCODE): $(($output | Out-String).Trim())"
                    }
                }
            }

            if ($service.Status -eq 'Running') {
                $controller = Get-Service -Name $service.Name
                if ($controller.Status -ne 'Running') {
                    try {
                        $controller.Start()
                        $controller.WaitForStatus('Running', (New-TimeSpan -Seconds 60))
                        Write-Host "  Started $($service.Name) again."
                    }
                    catch {
                        $controller.Refresh()
                        Write-Host "  Could not start $($service.Name), which is $($controller.Status): $($_.Exception.Message)"
                    }
                }
            }
        }
    }
}
catch {
    Write-Host "Could not restore Windows Update: $($_.Exception.Message)"
}

exit 0
