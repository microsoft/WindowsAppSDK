# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

<#
.SYNOPSIS
TODO
#>
[CmdletBinding(SupportsShouldProcess=$true)]
param(
    [Parameter(Mandatory=$true)]
    [string]$PackageDependencyId,

    [int]$Rank=0,

    [switch]$PrependIfRankCollision
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

$options = [Microsoft.Windows.ApplicationModel.DynamicDependency.AddPackageDependencyOptions]::None
if ($PrependIfRankCollision -eq $true)
{
    $options = $options -bor [Microsoft.Windows.ApplicationModel.DynamicDependency.AddPackageDependencyOptions]::PrependIfRankCollision
}

$packageDependencyContext = [IntPtr]0
$packageFullName = ""
$hr = [Microsoft.Windows.ApplicationModel.DynamicDependency.PackageDependency]::Add(
        $PackageDependencyId, $Rank, $options, [ref] $packageDependencyContext, [ref] $packageFullName)
if ($hr -lt 0)
{
    $win32ex = [System.ComponentModel.Win32Exception]::new($hr)
    Write-Error "Error 0x$($hr.ToString('X')): $($win32ex.Message)" -ErrorAction Stop
}

$o = New-Object System.Object
$o | Add-Member -type NoteProperty -name "PackageDependencyContext" -value $packageDependencyContext
$o | Add-Member -type NoteProperty -name "PackageFullName" -value $packageFullName
$o
