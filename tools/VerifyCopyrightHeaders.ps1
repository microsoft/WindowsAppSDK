<#
.SYNOPSIS
    Verify copyright headers exist for Windows App SDK source files

.PARAMETER Fix
    Add copyright headers to files that are missing them

.EXAMPLE
    VerifyCopyrightHeaders -Fix
#>

Param(
    [switch]$Fix = $false
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

$copyrightHeaderText = (
    "Copyright (c) Microsoft Corporation and Contributors.",
    "Licensed under the MIT License."
)

$include = ('*.cs', '*.cpp', '*.h', '*.idl', '*.xaml')
$exclude = [RegEx]'\\dev\\Detours\\|\\BuildOutput\\|\\obj\\|\\localpackages\\|\\packages\\|\\specs\\|\\temp\\|\\Debug\\|\\Release\\|\\ItemTemplates\\|\\ProjectTemplates\\|\\WindowsAppSDKAggregator\\'
$files = dir $PSScriptRoot\..\* -recurse -include $include | Where FullName -notmatch $exclude

$errorCount = 0
foreach ($file in $files) {
    $found = Select-String -Path $file.FullName -Pattern 'Copyright (c) Microsoft Corporation' -CaseSensitive -SimpleMatch
    if ([string]::IsNullOrEmpty($found)) {
        $errorCount++
        if ($Fix) {
            $copyrightText = "";
            if ($file.Extension -eq ".xaml") {
                $copyrightText = "<!-- " + $copyrightHeaderText[0] + " -->" + [Environment]::NewLine `
                               + "<!-- " + $copyrightHeaderText[1] + " -->" + [Environment]::NewLine + [Environment]::NewLine
            } else {
                $copyrightText = "// " + $copyrightHeaderText[0] + [Environment]::NewLine `
                               + "// " + $copyrightHeaderText[1] + [Environment]::NewLine + [Environment]::NewLine
            }
            $copyrightText + ((Get-Content $file.FullName) -join [Environment]::NewLine) | Set-Content $file.FullName
            Write-Host $file.FullName -ForegroundColor green
        } else {
            Write-Host $file.FullName -ForegroundColor red
        }
    }
}

if ($errorCount -gt 0) {
    if ($Fix) {
        Write-Host "Added copyright text to $errorCount files." -ForegroundColor green
        Exit 0
    } else {
        Write-Host "Copyright missing from $errorCount files." -ForegroundColor red
        Write-Host "Run 'tools\\VerifyCopyrightHeaders.cmd -Fix' locally to update files."
        Exit 1
    }
}
