# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

<#
.SYNOPSIS
    Delete the package dependency.

.PARAMETER
    The ID of the package dependency to remove.

.LINK
    https://learn.microsoft.com/windows/win32/api/appmodel/nf-appmodel-deletepackagedependency
#>
[CmdletBinding(SupportsShouldProcess=$true)]
param(
    [Parameter(Mandatory=$true)]
    [string]$PackageDependencyId
)

Set-StrictMode -Version 3.0

$ErrorActionPreference = "Stop"

# Import the MSIX Dynamic Dependency module
if (-not (Get-Module | Where-Object {$_.Name -eq 'MsixDynamicDependency'}))
{
    $module = Join-Path $PSScriptRoot 'MsixDynamicDependency.psm1'
    Import-Module -Name $module -ErrorAction Stop
}

$hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::Delete($PackageDependencyId)
if ($hr -lt 0)
{
    $win32ex = [System.ComponentModel.Win32Exception]::new($hr)
    Write-Error "Error 0x$($hr.ToString('X')): $($win32ex.Message)" -ErrorAction Stop
}
