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

# Set Windows SDKs to check/install by -CheckWindowsSDK and -InstallWindowsSDK
$global:windows_sdks = (('10.0.17763.0', 'https://go.microsoft.com/fwlink/p/?LinkID=2033908'),
                        ('10.0.26100.4654', 'https://go.microsoft.com/fwlink/p/?LinkID=2327008'))

# END   Customization
#-----------------------------------------------------------------------
$me = (Get-Item $PSScriptRoot).FullName
Write-Verbose "$me END Customization"
