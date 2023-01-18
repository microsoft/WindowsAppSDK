#Requires -RunAsAdministrator

Param(
    [string]$OutputFolder = "",
    [string]$AzureBuildStep = "all",
    [string]$Platform = "x64",
    [string]$Configuration = "release",
    [string]$ImageName = "",
    [Alias('Select')]
    [string]$TaefSelect = "*",
    [Alias('Name')]
    [string]$TaefName = "*",
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

  -Select <query>
      The selection criteria to be used when selecting tests from each test binary.
      Example: -Select "@Name='WindowsAppSDK.Test.AppTests.TestClass1.Test1'"

  -Name <testname>
      Alternative to "-Select "@Name='<testname>'".
      Example: -Name "WindowsAppSDK.Test.AppTests.TestClass1.Test1"

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

$ErrorActionPreference = "Stop"

.\BuildAll.ps1 -Platform $Platform -Configuration $Configuration


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

$ConfigPlat = Join-Path $Configuration $Platform
$OutputFolderPath = Join-Path $OutputFolder $ConfigPlat
$tePath = (Join-Path $OutputFolderPath "PushNotificationTests\TE.exe")
if (($AzureBuildStep -eq "all") -Or ($AzureBuildStep -eq "RunTests")) {
    .\DevCheck.ps1 -NoInteractive -Offline -Verbose -CertPassword 'BuildPipeline' -CheckTestPfx -Clean -CheckTAEFService
    .\DevCheck.ps1 -NoInteractive -Offline -Verbose -CertPassword 'BuildPipeline' -CheckTestPfx -Clean -CheckTAEFService
    

    $dllFile = (Join-Path $OutputFolder "Release\x86\PushNotificationTests\PushNotificationTests.dll")
    Write-Host "$tePath $dllFile"
    & $tePath $dllFile
}

$TotalTime = (Get-Date)-$StartTime
$TotalMinutes = $TotalTime.Minutes
$TotalSeconds = $TotalTime.Seconds
Write-Host @"

Total Running Time:
$TotalMinutes minutes and $TotalSeconds seconds

"@ -ForegroundColor CYAN