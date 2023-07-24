# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

<#
.SYNOPSIS
TODO
#>
[CmdletBinding(SupportsShouldProcess=$true)]
param(
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

[Microsoft.Windows.ApplicationModel.DynamicDependency.PackageGraph]::RevisionId
