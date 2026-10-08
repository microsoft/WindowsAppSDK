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

.PARAMETER OutputFolder
    Set the base folder for the script to look for testdefs

.PARAMETER Platform
    Only run tests for the selected platform

.PARAMETER Configuration
    Only run tests the selected configuration

.PARAMETER List
    List the tests available in BuildOutput with their settings

.PARAMETER Test
    Runs the tests available in BuildOutput
#>

param(
        [Parameter(Mandatory=$true)]
        [string]$OutputFolder,

        [Parameter(Mandatory=$true)]
        [string]$Platform,

        [Parameter(Mandatory=$true)]
        [string]$Configuration,

        [Parameter(Mandatory=$false)]
        [Switch]$Test,

        [Parameter(Mandatory=$false)]
        [Switch]$List,

        [Parameter(Mandatory=$false)]
        [Switch]$ShowSystemInfo=$true,

        [Parameter(Mandatory=$true)]
        [string]$wprProfilePath,

        [Parameter(Mandatory=$false)]
        [string]$callingStage = ''
)

$StartTime = Get-Date
$lastexitcode = 0
Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

function Get-Tests
{
    $configPlat = Join-Path $Configuration $Platform
    $outputFolderPath = Join-Path $OutputFolder $configPlat

    $tests = @()
    foreach ($testdef in (Get-ChildItem -Recurse -Filter "*.testdef" $outputFolderPath))
    {
        $testJson = Get-Content -Raw $testdef.FullName | ConvertFrom-Json

        $count = 0
        $baseId = $testdef.BaseName
        foreach ($testConfig in $testJson.Tests)
        {
            $testConfig | Write-Host
            if ($testConfig.PSObject.Properties.Name -contains 'Type')
            {
                $testType = $testConfig.Type
            }
            else
            {
                $testType = 'TAEF'
            }

            $id = $baseId + "-Test$count"
            $t = [PSCustomObject]@{}
            $t | Add-Member -MemberType NoteProperty -Name 'Test' -Value $id
            $t | Add-Member -MemberType NoteProperty -Name 'Description' -Value $testConfig.Description
            $t | Add-Member -MemberType NoteProperty -Name 'Filename' -Value $testConfig.Filename
            $t | Add-Member -MemberType NoteProperty -Name 'Parameters' -Value $testConfig.Parameters
            $t | Add-Member -MemberType NoteProperty -Name 'Architectures' -Value $testConfig.Architectures
            $t | Add-Member -MemberType NoteProperty -Name 'Status' -Value $testConfig.Status
            $t | Add-Member -MemberType NoteProperty -Name 'TestDef' -Value $testdef.FullName
            $t | Add-Member -MemberType NoteProperty -Name 'Type' -Value $testType

            $tests += $t
            $count += 1
        }
    }

    if ($callingStage -eq 'TestSampleApps')
    {
        $tests = $tests | Where-Object { $_.Filename -like "WindowsAppSDK.Test.SampleTests.dll" }
    }
    else 
    {
        $tests = $tests | Where-Object { $_.Filename -notlike "WindowsAppSDK.Test.SampleTests.dll" }
    }

    $tests
}

function List-Tests
{
    $tests = Get-Tests
    $tests | Sort-Object -Property Test | Format-Table Test,Description,Type,Filename,Parameters,Architectures,Status -AutoSize | Out-String -Width 512
}

function Run-TaefTest
{
    param($test)

    $testFolder = Split-Path -parent $test.TestDef
    $tePath = Join-Path $testFolder "te.exe"
    $dllFile = Join-Path $testFolder $test.Filename

    $teLogFile = (Join-Path $env:Build_SourcesDirectory "BuildOutput\$Configuration\$Platform\Te.wtl")
    $teLogPathTo = (Join-Path $env:Build_SourcesDirectory "TestOutput\$Configuration\$Platform")

    & $tePath $dllFile $test.Parameters /enableWttLogging /appendWttLogging /screenCaptureOnError /logFile:$teLogFile /testMode:EtwLogger /EtwLogger:WprProfile=WDGDEPAdex /EtwLogger:SavePoint=TestFailure /EtwLogger:RecordingScope=Execution /EtwLogger:WprProfileFile=$wprProfilePath
}

function Run-PowershellTest
{
    param($test)

    Write-Host "Powershell tests not supported"
}

function Run-Tests
{
    $tests = Get-Tests
    foreach ($test in $tests)
    {
        Write-Host "$($test.Filename) - $($test.Description)"
        $validPlatform = $test.Architectures.Contains($Platform)
        $testEnabled = $test.Status -eq "Enabled"
        if ($validPlatform -and $testEnabled)
        {
            if ($test.Type -eq 'TAEF')
            {
                Run-TaefTest $test
            }
            elseif ($test.Type -eq 'Powershell')
            {
                Run-PowershellTest $test
            }
            else
            {
                Write-Host "Unknown test type '$test.Type'. Not running."
                Exit 1
            }
        }
        elseif (-not($validPlatform))
        {
            Write-Host "$Platform not listed in supported architectures."
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

$env:Build_Platform = $Platform.ToLower()
$env:Build_Configuration = $Configuration.ToLower()

if ($ShowSystemInfo -eq $true)
{
    Get-SystemInfo
}

if ($List -eq $true)
{
    List-Tests | Out-String
}

if ($Test -eq $true)
{
    $teLogFile = (Join-Path $env:Build_SourcesDirectory "BuildOutput\$Configuration\$Platform\Te.wtl")
    $teLogPathTo = (Join-Path $env:Build_SourcesDirectory "TestOutput\$Configuration\$Platform")
    remove-item -Path $teLogFile -ErrorAction Ignore
    remove-item -Path (Join-path $teLogPathTo "Te.wtl") -ErrorAction Ignore

    Run-Tests

    # copy test log to TestOutput folder
    if (Test-Path -Path $teLogFile) {
        Write-Host "Starting copy test log from '$teLogFile'"

        New-Item -ItemType Directory -Path $teLogPathTo -Force
        copy-item -Path $teLogFile -Destination $teLogPathTo -Force

        Write-Host "Test log copied to '$teLogPathTo'"
    }

    # copy screenshots to TestOutput folder
    $screenshotsFolder = Join-Path $env:Build_SourcesDirectory "WexLogFileOutput"
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

$TotalTime = (Get-Date)-$StartTime
$TotalMinutes = $TotalTime.Minutes
$TotalSeconds = $TotalTime.Seconds
Write-Host "Total Running Time: $TotalMinutes minutes and $TotalSeconds seconds"
