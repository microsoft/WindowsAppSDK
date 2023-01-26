#Requires -RunAsAdministrator

Param(
    [string]$OutputFolder = "",
    [string]$AzureBuildStep = "all",
    [string]$Platform = "x64",
    [string]$Configuration = "release",
    [string]$ImageName = "",
    [switch]$AzurePipelineBuild = $false,
    [switch]$Help = $false
)

$StartTime = Get-Date

if ($help) {
  Write-Host @"
Copyright (C) Microsoft Corporation. All rights reserved.

Syntax:
      TestAll.cmd [options]

Description:
      Builds the WindowsAppSDK aggregate NuGet package.

Switches:

  -Platform <platform>
      Only test the selected platform.
      Example: -Platform x64

  -Configuration <configuration>
      Only build the selected configuration(s).
      Example: -Configuration debug
      Example: -Configuration "debug,release"

  -AzureBuildStep <step>
      Used by Azure to selectively run parts of the script in order to account for yaml-specific actions like signing.
      Example: -AzureBuildStep "CopyFilesFromTransportPackages"

  -ImageName <name>
      Used by Azure to specify which SKU is being tested.
      Example: -ImageName "Windows.10.Enterprise.RS5"

  -Help
      Display this usage message.
"@
  Exit
}
$lastexitcode = 0

if (($AzureBuildStep -eq "all") -Or ($AzureBuildStep -eq "DisplayInfo")) {
    # Display OS build/version info
    Get-Item -Path 'HKLM:\Software\Microsoft\Windows NT\CurrentVersion'
    # Display OS language settings
    Write-Host (reg query "HKLM\SYSTEM\CurrentControlSet\Control\MUI" /s)
    Write-Host (reg query "HKLM\SYSTEM\CurrentControlSet\Control\Nls" /s)
    Write-Host (reg query "HKCU\Control Panel\International" /s)

    Write-Host "Get-WmiObject -Class Win32_OperatingSystem" 
    $OSInfo = Get-WmiObject -Class Win32_OperatingSystem
    $languagePacks = $OSInfo.MUILanguages
    $languagePacks

    Write-Host "dism /online /Get-Intl" 
    dism /online /Get-Intl

    Write-Host "Get-WinUserLanguageList" 
    Get-WinUserLanguageList

    Write-Host "Get-WinUILanguageOverride"
    Get-WinUILanguageOverride

    Write-Host "Get-WinSystemLocale"
    Get-WinSystemLocale
}

if (($AzureBuildStep -eq "all") -Or ($AzureBuildStep -eq "RunTests")) {   
    foreach ($testmd in (Get-ChildItem -Recurse -Filter "*.testmd" $OutputFolder))
    {
        $testJson = Get-Content -Raw $testmd.FullName | ConvertFrom-Json
        Write-Host $testJson.Tests
        foreach($testConfig in $testJson.Tests)
        {
            Write-Host $testConfig.Description
            if($testConfig.Status -eq "Enabled")
            {
                $testFolder = Split-Path -parent $testmd.FullName
                $tePath = Join-Path $testFolder "te.exe"
                $dllFile = Join-Path $testFolder $testConfig.Filename
                & $tePath $dllFile
            }
            else
            {
                Write-Host "Test is disabled. Not running."
            }
        }
    }
}

$TotalTime = (Get-Date)-$StartTime
$TotalMinutes = $TotalTime.Minutes
$TotalSeconds = $TotalTime.Seconds
Write-Host @"

Total Running Time:
$TotalMinutes minutes and $TotalSeconds seconds

"@ -ForegroundColor CYAN