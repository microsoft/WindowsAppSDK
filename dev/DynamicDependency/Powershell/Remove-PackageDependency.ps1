# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Remove a resolved package dependency from the current process' package graph.

.PARAMETER PackageDependencyContext
    The handle of the package dependency to remove.

.LINK
    https://learn.microsoft.com/windows/win32/api/appmodel/nf-appmodel-removepackagedependency
#>
[CmdletBinding(SupportsShouldProcess=$true)]
param(
    [Parameter(Mandatory=$true)]
    [int64]$PackageDependencyContext
)

Set-StrictMode -Version 3.0

$ErrorActionPreference = "Stop"

# Import the MSIX Dynamic Dependency module
if (-not (Get-Module | Where-Object {$_.Name -eq 'MsixDynamicDependency'}))
{
    $module = Join-Path $PSScriptRoot 'MsixDynamicDependency.psm1'
    Import-Module -Name $module -ErrorAction Stop
}

$context = [IntPtr]$PackageDependencyContext
$hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::Remove($context)
if ($hr -lt 0)
{
    $win32ex = [System.ComponentModel.Win32Exception]::new($hr)
    Write-Error "Error 0x$($hr.ToString('X')): $($win32ex.Message)" -ErrorAction Stop
}
