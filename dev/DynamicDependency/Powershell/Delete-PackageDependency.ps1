# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

<#
.SYNOPSIS
TODO
#>
[CmdletBinding(SupportsShouldProcess=$true)]
param(
    [Parameter(Mandatory=$true)]
    [string]$PackageDependencyId
)

Set-StrictMode -Version 3.0

$ErrorActionPreference = "Stop"

Write-Host $PSScriptRoot
ForEach ($path in $env:PSModulePath -Split ';')
{
    Write-Host $path
}

# Import the MSIX Dynamic Dependency module
$module = Join-Path $PSScriptRoot 'MsixDynamicDependency.psm1'
Import-Module -Name $module -Verbose:$false -ErrorAction Stop

$hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::Delete($PackageDependencyId)
if ($hr -lt 0)
{
    $win32ex = [System.ComponentModel.Win32Exception]::new($hr)
    Write-Error "Error 0x$($hr.ToString('X')): $($win32ex.Message)" -ErrorAction Stop
}
