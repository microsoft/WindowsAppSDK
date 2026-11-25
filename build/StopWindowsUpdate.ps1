# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Stops Windows Update for the tests on Windows 10, after saving its settings so they can be restored.

.DESCRIPTION
    On Windows 10, Windows Update also installs Microsoft Store updates for the inbox apps (Xbox, Maps, Calculator, and
    so on). On a test VM that has been running for about two hours, it can start doing that in the middle of the tests.
    If it registers those apps while the tests install and launch the Dynamic Dependency Lifetime Manager (DDLM),
    Windows can reject every later activation of the DDLM with E_APPLICATION_NOT_REGISTERED (0x80270254), so every test
    that uses the Bootstrapper fails.

    Run this just before the tests. It disables and stops the Update Orchestrator service (UsoSvc), which starts update
    work, and the Windows Update service (wuauserv), which does it, so nothing starts them again during the tests. If
    Windows Update started deploying packages in the last 10 minutes, the script then waits, for up to -SettleMinutes,
    until the package deployment log has been quiet for 30 seconds, so those deployments finish before the tests start.

    The test VMs also run other pipelines' jobs, so the script first saves the services' settings to -StatePath, and
    RestoreWindowsUpdate.ps1 puts them back after the tests. The problem has only been seen on Windows 10 client, so by
    default the script does nothing on other versions. It never fails the job: problems are reported in the log.

.PARAMETER StatePath
    The file to save the services' settings to, for RestoreWindowsUpdate.ps1.

.PARAMETER SettleMinutes
    The longest time to wait for package deployments that Windows Update started to finish.

.PARAMETER AnyOS
    Stop Windows Update on any Windows version, not just Windows 10 client.
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string]$StatePath,
    [double]$SettleMinutes = 5,
    [switch]$AnyOS
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

# UsoSvc comes first, so it can't start wuauserv again while wuauserv is stopping.
$serviceNames = @('UsoSvc', 'wuauserv')
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

# Returns the package deployments that processes matching $Caller started since $Since, from the AppX deployment log.
function Get-PackageDeployment([datetime]$Since, [string]$Caller) {
    foreach ($entry in @(Get-WinEvent -FilterHashtable @{ LogName = $appxLog; Id = 603; StartTime = $Since } -ErrorAction SilentlyContinue)) {
        $data = @{}
        foreach ($item in ([xml]$entry.ToXml()).SelectNodes("//*[local-name()='Data']")) {
            $data[$item.GetAttribute('Name')] = $item.InnerText
        }
        if ([string]$data['CallingProcess'] -match $Caller) {
            [pscustomobject]@{ Time = $entry.TimeCreated.ToUniversalTime(); Caller = [string]$data['CallingProcess']; Package = [string]$data['Path'] }
        }
    }
}

try {
    $os = Get-CimInstance -ClassName Win32_OperatingSystem
    $isWindows10Client = ($os.ProductType -eq 1) -and ([int]$os.BuildNumber -lt 22000)
    if (-not $isWindows10Client -and -not $AnyOS) {
        Write-Host 'Not Windows 10 client, so Windows Update is left running.'
    }
    else {
        $states = @(foreach ($name in $serviceNames) {
                Get-ServiceState $name | Add-Member -NotePropertyName Disabled -NotePropertyValue $false -PassThru |
                    Add-Member -NotePropertyName Stopped -NotePropertyValue $false -PassThru
            })
        foreach ($state in $states) {
            Write-Host ('{0} is {1}, with startup type {2}.' -f $state.Name, $state.Status, $state.Start)
        }

        # Save the settings before changing anything, so RestoreWindowsUpdate.ps1 can undo whatever this script changes.
        $saved = [pscustomobject]@{ StoppedAt = (Get-Date).ToUniversalTime().ToString('o'); Services = $states }
        $saved | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath $StatePath -Encoding UTF8

        $recent = @(Get-PackageDeployment -Since (Get-Date).AddMinutes(-10) -Caller 'wuauserv' | Sort-Object Time)
        if ($recent.Count) {
            Write-Host ('Windows Update started {0} package deployments in the last 10 minutes, the last at {1}:' -f
                $recent.Count, $recent[-1].Time.ToString($timeFormat))
            foreach ($package in @($recent | ForEach-Object { $_.Package } | Sort-Object -Unique)) {
                Write-Host "  $package"
            }
        }

        foreach ($state in $states) {
            # Disable the service first, so nothing can start it again once it has stopped.
            if ($state.Start -ne 'disabled') {
                $output = & { $ErrorActionPreference = 'Continue'; & sc.exe config $state.Name start= disabled 2>&1 }
                if ($LASTEXITCODE -eq 0) {
                    $state.Disabled = $true
                    Write-Host "Disabled $($state.Name)."
                }
                else {
                    Write-Host "Could not disable $($state.Name) (sc.exe exit code $LASTEXITCODE): $(($output | Out-String).Trim())"
                }
            }

            $service = Get-Service -Name $state.Name
            if ($service.Status -ne 'Stopped') {
                try {
                    if ($service.Status -ne 'StopPending') {
                        $service.Stop()
                    }
                    $service.WaitForStatus('Stopped', (New-TimeSpan -Seconds 90))
                    $state.Stopped = $true
                    Write-Host "Stopped $($state.Name)."
                }
                catch {
                    $service.Refresh()
                    Write-Host "Could not stop $($state.Name), which is $($service.Status): $($_.Exception.Message)"
                }
            }
        }
        $saved | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath $StatePath -Encoding UTF8

        if ($recent.Count) {
            # Let the deployments Windows Update had started finish, so they don't overlap the tests.
            $start = Get-Date
            $deadline = $start.AddMinutes($SettleMinutes)
            while ($true) {
                $latest = @(Get-WinEvent -FilterHashtable @{ LogName = $appxLog; StartTime = (Get-Date).AddSeconds(-30) } -MaxEvents 1 -ErrorAction SilentlyContinue)
                $waited = ((Get-Date) - $start).TotalSeconds
                if (-not $latest.Count) {
                    Write-Host ('Package deployments had finished after {0:N0} s.' -f $waited)
                    break
                }
                if ((Get-Date) -ge $deadline) {
                    Write-Host ('Packages were still being deployed after {0:N0} s, so the tests will start anyway.' -f $waited)
                    break
                }
                Start-Sleep -Seconds 5
            }
        }
    }
}
catch {
    Write-Host "Could not stop Windows Update: $($_.Exception.Message)"
}

exit 0
