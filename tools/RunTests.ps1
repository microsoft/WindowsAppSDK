<#
#>

param(
    [string]$Output = "BuildOutput",

    [ValidateSet("x86", "x64", "arm64", IgnoreCase=$true)]
    [string]$Platform = "$($env:PROCESSOR_ARCHITECTURE)",

    [ValidateSet("Release", "Debug", IgnoreCase=$true)]
    [string]$Configuration = "Release",

    [switch]$RunDisabled = $false,

    [switch]$Build = $false,

    [string]$FilterTestDef,

    [string]$FilterDescription,

    [string]$FilterFilename,

    [string]$IgnoreFilename,

    [string]$FilterParameters,

    [string]$CustomParameters,

    [string]$LogFile,

    [switch]$EnableETWLogging = $false,

    [switch]$AppendWttLogging = $false,

    [string]$TestMode,

    [string]$WprProfile,

    [string]$EtwLoggerSavePoint,

    [string]$EtwLoggerRecordingScope,

    [string]$WprProfilePath
)

function Build-Tests
{
    param(
        $tests
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
    }
}

function Get-Tests
{
    param($baseFolder)

    $testDefs = Get-ChildItem -Recurse -Filter "*.testdef" $baseFolder -ErrorAction SilentlyContinue

    $allTests = foreach ($testDefFile in $testDefs)
    {
        $testJson = Get-Content -Raw $testDefFile.FullName | ConvertFrom-Json
        $count = 0

        foreach ($testConfig in $testJson.Tests)
        {
            $baseId = $testDefFile.BaseName
            $testType = if ($testConfig.PSObject.Properties['Type']) { $testConfig.Type } else { 'TAEF' }

            [PSCustomObject]@{
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

    return $allTests | Where-Object {
        (-not $FilterTestDef -or $_.TestDef -match $FilterTestDef) -and
        (-not $FilterDescription -or $_.Description -match $FilterDescription) -and
        (-not $FilterFilename -or $_.Filename -match $FilterFilename) -and
        (-not $FilterParameters -or $_.Parameters -match $FilterParameters) -and
        (-not $IgnoreFilename -or $_.Filename -notmatch $IgnoreFilename)
    }
}

function List-Tests
{
    param($tests)

    $tests | Sort-Object -Property Test | Format-Table Test,Description,Type,Filename,Parameters,Architectures,Status -AutoSize | Out-String -Width 512
}

function Run-TaefTest
{
    param($test)

    $testFolder = Split-Path -parent $test.TestDef
    $tePath = Join-Path $testFolder "te.exe"
    $dllFile = Join-Path $testFolder $test.Filename

    $teParams = @($dllFile)

    if ($CustomParameters) {
        $test.Parameters = $CustomParameters
    }

    if ($test.Parameters) {
        $teParams += $test.Parameters.Split(' ', [System.StringSplitOptions]::RemoveEmptyEntries)
    }

    $additionalParams = @()

    if ($LogFile) {
        $additionalParams += "/LogFile", $LogFile
    }

    if ($EnableETWLogging) {
        $additionalParams += "/enableEtwLogging"

        if ($WprProfile) {
            $additionalParams += "/EtwLogger:WprProfile=$WprProfile"
        }

        if ($EtwLoggerSavePoint) {
            $additionalParams += "/EtwLogger:SavePoint=$EtwLoggerSavePoint"
        }

        if ($EtwLoggerRecordingScope) {
            $additionalParams += "/EtwLogger:RecordingScope=$EtwLoggerRecordingScope"
        }

        if ($WprProfilePath) {
            $additionalParams += "/EtwLogger:WprProfileFile=$WprProfilePath"
        }
    }

    $allParams = $teParams + $additionalParams

    & $tePath @allParams
}

function Run-Tests
{
    param($tests)

    foreach ($test in $tests)
    {
        Write-Host ""
        Write-Host "$($test.Filename) - $($test.Description)"
        Write-Host ""

        $validPlatform = $test.Architectures.Contains($Platform)
        $testEnabled = $test.Status -eq "Enabled"

        if ($validPlatform -and ($testEnabled -or $RunDisabled))
        {
            Write-Host "Running test for platform $Platform..."
            if ($test.Type -eq 'TAEF')
            {
                Run-TaefTest $test
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

if ($Platform -eq "AMD64")
{
    $Platform = "x64"
}

Write-Host "Configuration: $Configuration, Platform: $Platform"

$scriptParent = Split-Path -parent $PSScriptRoot

if ($Build)
{
    Write-Host ""
    Write-Host "Building tests"
    Write-Host ""

    $testsSourceFolder = Join-Path $scriptParent "test"

    $tests = Get-Tests $testsSourceFolder
    Build-Tests $tests
}

Write-Host ""
Write-Host "Running tests for testdef: $TestDef" -ForegroundColor Yellow
Write-Host ""

$StartTime = Get-Date

$configPlat = Join-Path $Configuration $Platform
$outputFolder = Join-Path $scriptParent $Output $configPlat

$tests = Get-Tests $outputFolder
List-Tests $tests
Run-Tests $tests

$TotalTime = (Get-Date)-$StartTime
$TotalMinutes = $TotalTime.Minutes
$TotalSeconds = $TotalTime.Seconds
Write-Host ""
Write-Host "Total Running Time: $TotalMinutes minutes and $TotalSeconds seconds"
