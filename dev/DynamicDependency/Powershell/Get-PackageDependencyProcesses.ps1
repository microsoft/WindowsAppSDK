# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Return the process ids of processes using the package dependency.

.DESCRIPTION
    Return the process ids of processes using the package dependency.

    This does not add the package to the invoking process' package graph.

.PARAMETER PackageDependencyId
    The ID of the resolved package dependency.

.LINK
    https://learn.microsoft.com/windows/win32/api/appmodel/nf-appmodel-getprocessesusingpackagedependency
#>
[CmdletBinding(SupportsShouldProcess=$true)]
param(
    [Parameter(Mandatory=$true)]
    [string]$PackageDependencyId,

    [switch]$ScopeIsSystem
)

Set-StrictMode -Version 3.0

$ErrorActionPreference = "Stop"

# Import the MSIX Dynamic Dependency module
if (-not (Get-Module | Where-Object {$_.Name -eq 'MsixDynamicDependency'}))
{
    $module = Join-Path $PSScriptRoot 'MsixDynamicDependency.psm1'
    Import-Module -Name $module -ErrorAction Stop
}

[uint32]$processIdsCount = 0
[uint32[]]$processIds = $null
$hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::GetProcesses(
        $PackageDependencyId, $ScopeIsSystem, [ref] $processIdsCount, [ref] $processIds)
if ($hr -lt 0)
{
    $win32ex = [System.ComponentModel.Win32Exception]::new($hr)
    Write-Error "Error 0x$($hr.ToString('X')): $($win32ex.Message)" -ErrorAction Stop
}
else
{
    Write-Host "Processes: $processIdsCount"
}

$processIds
