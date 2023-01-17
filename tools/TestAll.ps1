#Requires -RunAsAdministrator

Param(
    [string]$WindowsAppSDKPackageVersion = "",
    [string]$AzureBuildStep = "all",
    [string]$Platform = "x64",
    [string]$Configuration = "release,debug",
    [string]$ImageName = "",
    [Alias('Select')]
    [string]$TaefSelect = "*",
    [Alias('Name')]
    [string]$TaefName = "*",
    [switch]$AzurePipelineBuild = $false,
    [switch]$SelfContained = $false,
    [switch]$BinaryCompat = $false,
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

  -WindowsAppSDKPackageVersion <version>
      Specifies which WindowsAppSDK package to test.
      This defaults to the last package built by the BuildAll script.
      Example: -WindowsAppSDKPackageVersion "1.0.20211201-1312-stable-dev"

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

  -SelfContained
      Run the tests with test apps built in Self Contained mode.

  -BinaryCompat
      Run the tests with test apps built in the version specified in WindowsAppSDKPackageVersion 
      but installs and runs against the WindowsAppSDK package built from BuildAll.ps1
      Currently only works if WindowsAppSDKPackageVersion is 1.0.0

  -AzurePipelineBuild
      Used by Azure to specify this as an Azure build.

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

$env:Build_SourcesDirectory = (Split-Path $MyInvocation.MyCommand.Path)

$env:AzurePipelineBuild = $AzurePipelineBuild;

. build\Scripts\BLD-LocalDevInfoManager.ps1
if (-Not [string]::IsNullOrWhiteSpace($WindowsAppSDKPackageVersion)) {
    # If version is passed in, overwrite version from last build
    $global:Build_Info.WindowsAppSDKPackageVersion = $WindowsAppSDKPackageVersion
}
if (($AzureBuildStep -eq "all") -And ([string]::IsNullOrWhiteSpace($global:Build_Info.WindowsAppSDKPackageVersion))) {
    Write-Host "`nWindowsAppSDKPackageVersion is not set.  Either set it with -WindowsAppSDKPackageVersion or run BuildAll script first." -ForegroundColor RED
    Exit
}

. build\Scripts\BLD-WindowsAppSdkVersions.ps1

$env:Build_Platform = $Platform.ToLower()

$env:Build_Configuration = $Configuration.ToLower()

$ErrorActionPreference = "Stop"

if (($AzureBuildStep -eq "all") -Or ($AzureBuildStep -eq "BuildTests")) 
{
    # The versions in $WinAppSDKTestNupkgVersionMap are produced in the pipeline:
    # https://dev.azure.com/microsoft/ProjectReunion/_build?definitionId=78948
    # Please see build\WindowsAppSDK-BuildBinaryCompatTest.yml for more details
    $WinAppSDKTestNupkgVersionMap = @{ 
        "1.0.0" = "1.0.0-20220202.9-CI"; 
        "1.1.0" = "1.1.0-220803.4"
    }
    # NugetRestoreTests restore WinAppSDKTest Nupkg which contains the BuildOutput from the BuildTests yaml step 
    # of the version found in the $WinAppSDKTestNupkgVersionMap's key
    if ($BinaryCompat -and $AzurePipelineBuild) {
        . build\scripts\BLD-NugetRestoreTests.ps1 -NugetVersion $WinAppSDKTestNupkgVersionMap[$WindowsAppSDKPackageVersion]
    } 
    else {
        . build\scripts\BLD-BuildTests.ps1 -SelfContained $SelfContained -AzurePipelineBuild $AzurePipelineBuild
    }
}

if (($AzureBuildStep -eq "all" -and $BinaryCompat) -Or ($AzureBuildStep -eq "MotifyTestsToBinaryCompat")) {
    . build\scripts\BLD-MotifyTestsToBinaryCompat.ps1
}

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
    . build\scripts\BLD-RunTests.ps1 -TaefSelect $TaefSelect -TaefName $TaefName -BinaryCompat $BinaryCompat
}

$TotalTime = (Get-Date)-$StartTime
$TotalMinutes = $TotalTime.Minutes
$TotalSeconds = $TotalTime.Seconds
Write-Host @"

Total Running Time:
$TotalMinutes minutes and $TotalSeconds seconds

"@ -ForegroundColor CYAN