<#
.SYNOPSIS
    Run tests from a specific .testdef file

.DESCRIPTION
    The RunTests script takes a testdef filename (without extension) and runs the tests defined in that
    specific .testdef file. This is useful for development when you want to run tests for a specific 
    component rather than all tests.

    The script searches for the specified .testdef file in the BuildOutput directory structure and
    executes the tests according to the testdef configuration.

    *.testdef are JSON files with the same schema as used by TestAll.ps1:
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

.PARAMETER TestDefName
    The name of the .testdef file to run (without the .testdef extension)
    Example: "Deployment" to run "Deployment.testdef"

.PARAMETER OutputFolder
    Set the base folder for the script to look for testdefs. Default: BuildOutput

.PARAMETER Platform
    Only run tests for the selected platform (x86, x64, arm64). Default: x64

.PARAMETER Configuration
    Only run tests for the selected configuration (Debug, Release). Default: Release

.PARAMETER List
    List the tests available in the specified testdef file with their settings

.PARAMETER Test
    Runs the tests available in the specified testdef file

.PARAMETER ShowSystemInfo
    Show system information before running tests (default: true)

.PARAMETER wprProfilePath
    Path to the WPR profile file for ETW logging (optional)

.EXAMPLE
    .\RunTests.ps1 -TestDefName "Deployment" -Test

.EXAMPLE
    .\RunTests.ps1 -TestDefName "PushNotifications" -List

.EXAMPLE
    .\RunTests.ps1 -TestDefName "Deployment" -Platform "x86" -Configuration "Debug" -Test
#>

param(
    [Parameter(Mandatory=$true)]
    [string]$TestDefName,

    [Parameter(Mandatory=$false)]
    [string]$OutputFolder = "BuildOutput",

    [Parameter(Mandatory=$false)]
    [string]$Platform = "x64",

    [Parameter(Mandatory=$false)]
    [string]$Configuration = "Release",

    [Parameter(Mandatory=$false)]
    [Switch]$Test,

    [Parameter(Mandatory=$false)]
    [Switch]$List,

    [Parameter(Mandatory=$false)]
    [Switch]$ShowSystemInfo=$true,

    [Parameter(Mandatory=$false)]
    [string]$wprProfilePath = ""
)

$StartTime = Get-Date
$lastexitcode = 0
Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

function Find-TestDefFile
{
    param($testDefName)
    
    $configPlat = Join-Path $Configuration $Platform
    $outputFolderPath = Join-Path $OutputFolder $configPlat
    
    $testDefFileName = "$testDefName.testdef"
    $testDefFile = Get-ChildItem -Recurse -Filter $testDefFileName $outputFolderPath -ErrorAction SilentlyContinue | Select-Object -First 1
    
    if ($null -eq $testDefFile)
    {
        Write-Error "Could not find testdef file '$testDefFileName' in '$outputFolderPath'"
        Exit 1
    }
    
    Write-Host "Found testdef file: $($testDefFile.FullName)"
    return $testDefFile
}

function Get-Tests
{
    param($testDefFile)

    $tests = @()
    $testJson = Get-Content -Raw $testDefFile.FullName | ConvertFrom-Json

    $count = 0
    $baseId = $testDefFile.BaseName
    foreach ($testConfig in $testJson.Tests)
    {
        $testConfig | Write-Host
        if ($testConfig -contains 'Type')
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
        $t | Add-Member -MemberType NoteProperty -Name 'TestDef' -Value $testDefFile.FullName
        $t | Add-Member -MemberType NoteProperty -Name 'Type' -Value $testType

        $tests += $t
        $count += 1
    }

    $tests
}

function List-Tests
{
    param($testDefFile)
    
    $tests = Get-Tests $testDefFile
    Write-Host "Tests in $($testDefFile.Name):"
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

    # Build the command arguments
    $teArgs = @($dllFile, $test.Parameters, "/enableWttLogging", "/appendWttLogging", "/screenCaptureOnError", "/logFile:$teLogFile", "/testMode:EtwLogger")
    
    # Add ETW logging parameters only if WPR profile is provided
    if (-not [string]::IsNullOrEmpty($wprProfilePath)) {
        $teArgs += "/EtwLogger:WprProfile=WDGDEPAdex"
        $teArgs += "/EtwLogger:SavePoint=TestFailure" 
        $teArgs += "/EtwLogger:RecordingScope=Execution"
        $teArgs += "/EtwLogger:WprProfileFile=$wprProfilePath"
    }
    
    & $tePath $teArgs
}

function Run-PowershellTest
{
    param($test)

    $testFolder = Split-Path -parent $test.TestDef
    $scriptFile = Join-Path $testFolder $test.Filename
    
    Write-Host "Running PowerShell test: $scriptFile"
    if (Test-Path $scriptFile)
    {
        & $scriptFile $test.Parameters
    }
    else
    {
        Write-Error "PowerShell test file not found: $scriptFile"
    }
}

function Run-Tests
{
    param($testDefFile)
    
    $tests = Get-Tests $testDefFile
    Write-Host "Running tests from $($testDefFile.Name)..."
    
    foreach ($test in $tests)
    {
        Write-Host ""
        Write-Host "=" * 80
        Write-Host "$($test.Filename) - $($test.Description)"
        Write-Host "=" * 80
        
        $validPlatform = $test.Architectures.Contains($Platform)
        $testEnabled = $test.Status -eq "Enabled"
        
        if ($validPlatform -and $testEnabled)
        {
            Write-Host "Running test for platform $Platform..."
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

# Main script execution
Write-Host "RunTests.ps1 - Running tests for testdef: $TestDefName"
Write-Host "Configuration: $Configuration, Platform: $Platform"
Write-Host ""

$env:Build_Platform = $Platform.ToLower()
$env:Build_Configuration = $Configuration.ToLower()

if ($ShowSystemInfo -eq $true)
{
    Get-SystemInfo
    Write-Host ""
}

# Find the testdef file
$testDefFile = Find-TestDefFile $TestDefName

if ($List -eq $true)
{
    List-Tests $testDefFile | Out-String
}

if ($Test -eq $true)
{
    $teLogFile = (Join-Path $env:Build_SourcesDirectory "BuildOutput\$Configuration\$Platform\Te.wtl")
    $teLogPathTo = (Join-Path $env:Build_SourcesDirectory "TestOutput\$Configuration\$Platform")
    remove-item -Path $teLogFile -ErrorAction Ignore
    remove-item -Path (Join-path $teLogPathTo "Te.wtl") -ErrorAction Ignore

    Run-Tests $testDefFile

    # Copy test log to TestOutput folder
    if (Test-Path -Path $teLogFile) {
        Write-Host "Starting copy test log from '$teLogFile'"

        New-Item -ItemType Directory -Path $teLogPathTo -Force
        copy-item -Path $teLogFile -Destination $teLogPathTo -Force

        Write-Host "Test log copied to '$teLogPathTo'"
    }

    # Copy screenshots to TestOutput folder
    $screenshotsFolder = Join-Path $env:Build_SourcesDirectory "WexLogFileOutput"
    if (Test-Path -Path $screenshotsFolder) {
        Write-Host "Starting copy screenshots from '$screenshotsFolder'"

        # Copy at most 50 screenshots to the upload path.
        # In the cases where a large number of tests failed, there is little value in uploading dozens of screenshots
        $files = Get-ChildItem -Path $screenshotsFolder -Filter *.jpg | Select-Object -First 50
        foreach($file in $files)
        {
            Copy-Item $file.FullName $teLogPathTo -Force
        }

        # Copy at most 20 tracelogging files to the upload path.
        $files = Get-ChildItem -Path $screenshotsFolder -Filter *.etl | Select-Object -First 20
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
Write-Host ""
Write-Host "Total Running Time: $TotalMinutes minutes and $TotalSeconds seconds"
