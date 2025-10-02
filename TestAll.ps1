<#
.SYNOPSIS
    Run the WinAppSDK tests

.DESCRIPTION
    The TestAll script will take the folder input and look for subfolders containing a .testdef file. WinAppSDK
    components define a testdef with the following schema and runs the test in the subfolder.

    *.testdef are JSON files with the schema per JSON Schema 2020-12 (https://json-schema.org):
        {
          "$id": "https://microsoft.com/windowsappsdk/schemas/testdef/2023/08",

          "type": "object",
          "properties": {
            "Description": { "type": "string" },
            "Type": { "enum": ["TAEF", "Powershell"], "default": "TAEF" },
            "Filename": { "type": "string" },
            "Parameters": { "type": "string" },
            "Architectures": { "type": "array", "items": { "type": "string" } },
            "Status": { "enum": ["Enabled", "Disabled"] },
          },
          "required": ["Description", "Filename", "Architectures", "Status"]
        }

    Example:
    {
        "Tests": [
            {
                "Description": "This module tests the push notifications component in WinAppSDK.",
                "Type": "TAEF",
                "Filename": "PushNotificationTests.dll",
                "Parameters": "",
                "Architectures": ["x86", "x64", "arm64"],
                "Status": "Enabled"
            }
        ]
    }

.PARAMETER BuildOutputFolder
    Set the base folder for the script to look for testdefs

.PARAMETER TestOutputFolder
    If set, the test log and screenshots will be copied to this folder after running the tests

.PARAMETER Platform
    Only run tests for the selected platform

.PARAMETER Configuration
    Only run tests the selected configuration

.PARAMETER List
    List the tests available in BuildOutput with their settings

.PARAMETER BuildTests
    Builds the tests from source before running them

.PARAMETER Test
    Runs the tests available in BuildOutput

.PARAMETER ShowSystemInfo
    Show system information before running the tests

.PARAMETER wprProfilePath
    WPR profile to use for ETW logging

.PARAMETER callingStage
    If set to 'TestSampleApps', only tests from WindowsAppSDK.Test.SampleTests.dll

.PARAMETER CustomParameters
    Override test parameters for all executed tests

.PARAMETER FilterTestDef
    Filter tests by testdef file full name using regex pattern matching

.PARAMETER FilterDescription
    Filter tests by description field using regex pattern matching

.PARAMETER FilterDllFilename
    Filter tests by Dll filename using regex pattern matching

.PARAMETER FilterParameters
    Filter tests by parameters field using regex pattern matching

#>

# Import the module containing the functions:
# List-Tests, Get-Tests, Run-Tests, Build-Tests
# And the class TestInfo
using module .\tools\Tests.psm1

param(
        [Parameter(Mandatory=$false)]
        [string]$BuildOutputFolder = (Join-Path $PSScriptRoot "BuildOutput"),

        [Parameter(Mandatory=$false)]
        [string]$TestOutputFolder = "",

        [Parameter(Mandatory=$false)]
        [string]$Platform = "$($env:PROCESSOR_ARCHITECTURE)",

        [Parameter(Mandatory=$false)]
        [string]$Configuration = "Release",

        [Parameter(Mandatory=$false)]
        [Switch]$Test,

        [Parameter(Mandatory=$false)]
        [Switch]$List,

        [Parameter(Mandatory=$false)]
        [Switch]$BuildTests,

        [Parameter(Mandatory=$false)]
        [Switch]$ShowSystemInfo = $true,

        [switch]$SaveScreenshots,

        [Parameter(Mandatory=$false)]
        [string]$wprProfilePath,

        [Parameter(Mandatory=$false)]
        [string]$callingStage,

        [string]$CustomParameters = "",

        [string]$FilterTestDef = "",

        [string]$FilterDescription = "",

        [string]$FilterDllFilename = "",

        [string]$FilterParameters = ""
)

if ($Platform -eq "AMD64")
{
    $Platform = "x64"
}

$StartTime = Get-Date
$lastexitcode = 0
Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

function Get-SystemInfo
{
    $regkey = 'HKLM:\SOFTWARE\Microsoft\Windows NT\CurrentVersion'
    $productname = $(Get-Item -Path $regkey).GetValue('ProductName')
    $displayversion = $(Get-Item -Path $regkey).GetValue('DisplayVersion')
    $currentmajor = $(Get-Item -Path $regkey).GetValue('CurrentMajorVersionNumber')
    $currentminor = $(Get-Item -Path $regkey).GetValue('CurrentMinorVersionNumber')
    $currentbuild = $(Get-Item -Path $regkey).GetValue('CurrentBuild')
    Write-Host "Product         : $($productname) $($displayversion) $($currentmajor).$($currentminor).$($currentbuild)"

    $installationtype = $(Get-Item -Path $regkey).GetValue('InstallationType')
    Write-Host "InstallationType: $($installationtype)"

    $editionid = $(Get-Item -Path $regkey).GetValue('EditionId')
    $compositioneditionid = $(Get-Item -Path $regkey).GetValue('CompositionEditionID')
    if ($editionid -eq $compositioneditionid)
    {
        Write-Host "Edition         : $($editionid)"
    }
    else
    {
        Write-Host "Edition         : $($editionid) [$($compositioneditionid)]"
    }

    $buildlabex = $(Get-Item -Path $regkey).GetValue('BuildLabEx')
    Write-Host "Build           : $($buildlabex)"

    $lcuver = $(Get-Item -Path $regkey).GetValue('LCUVer')
    Write-Host "LCU Version     : $($lcuver)"

    Write-Host "Powershell      : $($PSVersionTable.PSEdition) $($PSVersionTable.PSVersion)"
}

function FilterTests
{
    param(
        [TestInfo[]]$tests
    )

    $filteredTests = $tests | Where-Object {
        (-not $FilterTestDef -or $_.TestDef -match $FilterTestDef) -and
        (-not $FilterDescription -or $_.Description -match $FilterDescription) -and
        (-not $FilterDllFilename -or $_.Filename -match $FilterDllFilename) -and
        (-not $FilterParameters -or $_.Parameters -match $FilterParameters)
    }

    if ($callingStage -eq 'TestSampleApps')
    {
        $filteredTests = $filteredTests | Where-Object { $_.Filename -like "WindowsAppSDK.Test.SampleTests.dll" }
    }
    else
    {
        $filteredTests = $filteredTests | Where-Object { $_.Filename -notlike "WindowsAppSDK.Test.SampleTests.dll" }
    }

    return $filteredTests
}

$env:Build_Platform = $Platform.ToLower()
$env:Build_Configuration = $Configuration.ToLower()

if ($ShowSystemInfo -eq $true)
{
    Get-SystemInfo
}

if ($BuildTests)
{
    Write-Host ""
    Write-Host "Building tests" -ForegroundColor Yellow
    Write-Host ""

    $testsSourceFolder = Join-Path $PSScriptRoot "test"

    $tests = Get-Tests $testsSourceFolder
    $tests = FilterTests $tests
    Build-Tests $tests -Platform $Platform -Configuration $Configuration
}

$configPlat = Join-Path $Configuration $Platform
$outputFolderPath = Join-Path $BuildOutputFolder $configPlat

$allTests = Get-Tests $outputFolderPath
$allTests = FilterTests $allTests

if ($List -eq $true)
{
    List-Tests $allTests | Out-String
}

if ($Test -eq $true)
{
    $additionalParams = @()

    $teLogFile = Join-Path $BuildOutputFolder "$Configuration\$Platform\Te.wtl"
    remove-item -Path $teLogFile -ErrorAction Ignore
    $additionalParams += "/logFile:$teLogFile"

    if ($wprProfilePath -ne '')
    {
        $additionalParams += "/enableWttLogging"
        $additionalParams += "/appendWttLogging"
        $additionalParams += "/testMode:ETWLogger"
        $additionalParams += "/EtwLogger:WprProfile=WDGDEPAdex"
        $additionalParams += "/EtwLogger:SavePoint=TestFailure"
        $additionalParams += "/EtwLogger:RecordingScope=Execution"
        $additionalParams += "/EtwLogger:WprProfileFile=$WprProfilePath"
    }

    if ($SaveScreenshots)
    {
        $additionalParams += "/screenCaptureOnError"
    }

    Run-Tests $allTests -additionalParams $additionalParams -customParameters $CustomParameters -platform $Platform.ToLower()

    if ($TestOutputFolder -ne '')
    {
        $teLogPathTo = Join-Path $TestOutputFolder "$Configuration\$Platform"
        remove-item -Path (Join-path $teLogPathTo "Te.wtl") -ErrorAction Ignore

        # copy test log to TestOutput folder
        if (Test-Path -Path $teLogFile) {
            Write-Host "Starting copy test log from '$teLogFile'"

            New-Item -ItemType Directory -Path $teLogPathTo -Force
            copy-item -Path $teLogFile -Destination $teLogPathTo -Force

            Write-Host "Test log copied to '$teLogPathTo'"
        }

        # copy screenshots to TestOutput folder
        $screenshotsFolder = Join-Path (Split-Path $BuildOutputFolder -parent) "WexLogFileOutput"
        if (Test-Path -Path $screenshotsFolder) {
            Write-Host "Starting copy screenshots from '$screenshotsFolder'"

            # Copy at most 50 screenshots to the upload path.
            # In the cases where a large number of tests failed, there is little value in uploading dozens of screenshots
            $files = Get-ChildItem -Path $screenshotsFolder -Filter *.jpg |Select-Object -First 50
            foreach($file in $files)
            {
                Copy-Item $file.FullName $teLogPathTo -Force
            }

            # Copy at most 20 tracelogging files to the upload path.
            $files = Get-ChildItem -Path $screenshotsFolder -Filter *.etl |Select-Object -First 20
            foreach($file in $files)
            {
                Copy-Item $file.FullName $teLogPathTo -Force
            }

            Write-Host "Test results copied to '$teLogPathTo'"
        }
        else
        {
            Write-Host "WexLogFileOutput not found"
        }
    }
}

$TotalTime = (Get-Date)-$StartTime
$TotalMinutes = $TotalTime.Minutes
$TotalSeconds = $TotalTime.Seconds
Write-Host "Total Running Time: $TotalMinutes minutes and $TotalSeconds seconds"
