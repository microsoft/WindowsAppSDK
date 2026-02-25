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

param(
        [string]$BuildOutputFolder = (Join-Path $PSScriptRoot "BuildOutput"),

        [string]$TestOutputFolder,

        [string]$Platform = "$($env:PROCESSOR_ARCHITECTURE)",

        [string]$Configuration = "Release",

        [Switch]$Test,

        [Switch]$List,

        [Switch]$BuildTests,

        [Switch]$ShowSystemInfo = $true,

        [switch]$SaveScreenshots,

        [string]$wprProfilePath,

        [string]$callingStage,

        [string]$CustomParameters,

        [string]$FilterTestDef,

        [string]$FilterDescription,

        [string]$FilterDllFilename,

        [string]$FilterParameters
)

if ($Platform -eq "AMD64")
{
    $Platform = "x64"
}

$StartTime = Get-Date
Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

class TestInfo
{
    [string]$Test
    [string]$Description
    [ValidateSet("TAEF", "Powershell", IgnoreCase=$true)]
    [string]$Type
    [ValidateNotNullOrEmpty()][string]$Filename
    [string]$Parameters
    [string[]]$Architectures
    [string]$Status
    [ValidateNotNullOrEmpty()][string]$TestDef
}

function Build-Tests
{
    param(
        [TestInfo[]]$tests,
        [ValidateSet("Debug", "Release", IgnoreCase=$true)]
        [string]$Configuration,
        [ValidateSet("x86", "x64", "arm64", IgnoreCase=$true)]
        [string]$Platform
    )

    $VCToolsInstallDir = . "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -latest -prerelease -requires Microsoft.Component.MSBuild -property installationPath
    Write-Host "VCToolsInstallDir: $VCToolsInstallDir"

    $msbuildPath = Join-Path $VCToolsInstallDir "MSBuild\Current\Bin\msbuild.exe"
    Write-Host "MSBuild Path: $msbuildPath"

    # Build each test project once
    $projectsBuilt = @{}

    foreach ($test in $tests)
    {
        $testDefFile = $test.TestDef
        Write-Host "Building tests for testdef: $testDefFile"

        $testFolder = Split-Path -parent $testDefFile
        Write-Host "Building tests in folder: $testFolder"
        $projFile = Get-ChildItem -Filter "*.vcxproj" -Path $testFolder | Select-Object -First 1

        if ($null -eq $projFile)
        {
            Write-Error "Could not find a .vcxproj file in $testFolder"
            Exit 1
        }

        Write-Host "Found project file: $projFile"

        if ($projectsBuilt.ContainsKey($projFile.FullName))
        {
            Write-Host "Project already built. Skipping."
            continue
        }

        & $msbuildPath $projFile.FullName /p:Configuration=$Configuration /p:Platform=$Platform /v:minimal
        $projectsBuilt[$projFile.FullName] = $true

        if ($lastexitcode -ne 0)
        {
            Write-Error "Build failed for project $($projFile.FullName)"
            Exit 1
        }
    }
}


function Get-Tests
{
    param([string]$baseFolder)

    $testDefs = Get-ChildItem -Recurse -Filter "*.testdef" $baseFolder -ErrorAction SilentlyContinue

    $allTests = foreach ($testDefFile in $testDefs)
    {
        $testJson = Get-Content -Raw $testDefFile.FullName | ConvertFrom-Json
        $count = 0

        foreach ($testConfig in $testJson.Tests)
        {
            $baseId = $testDefFile.BaseName
            $testType = if ($testConfig.PSObject.Properties['Type']) { $testConfig.Type } else { 'TAEF' }

            [TestInfo]@{
                Test = "$baseId-Test$count"
                Description = $testConfig.Description
                Filename = $testConfig.Filename
                Parameters = $testConfig.Parameters
                Architectures = $testConfig.Architectures
                Status = $testConfig.Status
                TestDef = $testDefFile.FullName
                Type = $testType
            }

            $count++
        }
    }

    return $allTests
}

function List-Tests
{
    param([TestInfo[]]$tests)

    $tests | Sort-Object -Property Test | Format-Table Test,Description,Type,Filename,Parameters,Architectures,Status -AutoSize | Out-String -Width 512
}

function Run-TaefTest
{
    param(
        [TestInfo]$test,
        [string]$customParameters = "",
        [string]$additionalParams = ""
    )

    $testFolder = Split-Path -parent $test.TestDef
    $tePath = Join-Path $testFolder "te.exe"
    $dllFile = Join-Path $testFolder $test.Filename

    $teParams = @($dllFile)

    if ($customParameters) {
        $test.Parameters = $customParameters
    }

    if ($test.Parameters) {
        $teParams += $test.Parameters.Split(' ', [System.StringSplitOptions]::RemoveEmptyEntries)
    }

    $allParams = $teParams + $additionalParams.Split(' ', [System.StringSplitOptions]::RemoveEmptyEntries)

    & $tePath @allParams
}

function Run-Tests
{
    param(
        [TestInfo[]]$tests,
        [ValidateSet("x86", "x64", "arm64", IgnoreCase=$true)]
        [string]$platform,
        [switch]$runDisabled = $false,
        [string]$customParameters = "",
        [string]$additionalParams = ""
    )

    Write-Host "Run disabled tests: $runDisabled"
    Write-Host "Custom parameters: $customParameters"
    Write-Host "Additional parameters: $additionalParams"


    foreach ($test in $tests)
    {
        Write-Host ""
        Write-Host "$($test.Filename) - $($test.Description)"
        Write-Host ""

        $validPlatform = $test.Architectures.Contains($platform)
        $testEnabled = $test.Status -eq "Enabled"

        if ($validPlatform -and ($testEnabled -or $runDisabled))
        {
            Write-Host "Running test for platform $platform..."
            if ($test.Type -eq 'TAEF')
            {
                Run-TaefTest $test $customParameters $additionalParams
            }
            elseif ($test.Type -eq 'Powershell')
            {
                Write-Host "Powershell tests not supported."
                Exit 1
            }
            else
            {
                Write-Host "Unknown test type '$($test.Type)'. Not running."
                Exit 1
            }
        }
        elseif (-not($validPlatform))
        {
            Write-Host "$Platform not listed in supported architectures: $($test.Architectures -join ', ')"
        }
        elseif (-not($testEnabled))
        {
            Write-Host "Test is disabled. Not running."
        }
    }
}

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

function Select-Tests
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

if ($ShowSystemInfo)
{
    Get-SystemInfo
}

if ($BuildTests)
{
    Write-Host ""
    Write-Host "Building tests" -ForegroundColor Yellow
    Write-Host ""

    $testsSourceFolder = Join-Path $PSScriptRoot "test"

    $tests = Select-Tests (Get-Tests $testsSourceFolder)
    Build-Tests $tests -Platform $Platform -Configuration $Configuration
}

$outputFolderPath = Join-Path $BuildOutputFolder "$Configuration\$Platform"

$allTests = Select-Tests (Get-Tests $outputFolderPath)

if ($List)
{
    List-Tests $allTests | Out-String
}

if ($Test)
{
    $additionalParams = @()

    $teLogFile = Join-Path $outputFolderPath "Te.wtl"
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
