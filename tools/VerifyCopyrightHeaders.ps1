Param(
    [switch]$Fix = $false
)

$include = ('*.cs', '*.cpp', '*.h', '*.idl', '*.xaml')
$exclude = [RegEx]'\\packages\\|\\bin\\|\\BuildOutput\\.*\\MSIX\\|\\BuildOutput\\AppXContents\\|\\MsixContent\\'
$files = dir $PSScriptRoot\..\* -recurse -include $include | Where FullName -notmatch $exclude

$errorCount = 0
foreach ($file in $files) {
    $found = Select-String -Path $file.FullName -Pattern 'Copyright (c) Microsoft Corporation' -CaseSensitive -SimpleMatch
    if ([string]::IsNullOrEmpty($found)) {
        $errorCount++
        if ($Fix) {
            (Get-Content $PSScriptRoot\VerifyCopyrightHeaders.txt) + "`r" + (Get-Content $file.FullName) | Set-Content $file.FullName
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
        Exit 1
    }
}