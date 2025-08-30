# Copyright (c) Microsoft Corporation and Contributors.
# Licensed under the MIT License.

# DevCheck Settings

# Do not alter contents except in the Customization block
# Everything else is owned by DevCheck and subject to change without warning

$me = (Get-Item $PSScriptRoot).FullName
Write-Verbose "$me BEGIN Customization"
#-----------------------------------------------------------------------
# BEGIN Customization

# Set paths to scan by -CheckDependencies and -SyncDependencies
$global:dependency_paths = ('dev', 'test', 'installer', 'tools')

# END   Customization
#-----------------------------------------------------------------------
$me = (Get-Item $PSScriptRoot).FullName
Write-Verbose "$me END Customization"
