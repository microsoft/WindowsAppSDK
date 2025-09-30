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

    [string]$CustomParameters
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

    $tests = @()

    $testDefs = Get-ChildItem -Recurse -Filter "*.testdef" $baseFolder -ErrorAction SilentlyContinue

    foreach ($testDefFile in $testDefs)
    {
        $testJson = Get-Content -Raw $testDefFile.FullName | ConvertFrom-Json
        $count = 0
        foreach ($testConfig in $testJson.Tests)
        {
            # Apply filters
            # If a filter is set and the test property does not contain the filter regex, skip this test
            if ($FilterTestDef -and ($testDefFile.FullName -notmatch $FilterTestDef))
            {
                continue
            }

            if ($FilterDescription -and ($testConfig.Description -notmatch $FilterDescription))
            {
                continue
            }

            if ($FilterFilename -and ($testConfig.Filename -notmatch $FilterFilename))
            {
                continue
            }

            if ($IgnoreFilename -and ($testConfig.Filename -match $IgnoreFilename))
            {
                continue
            }

            if ($FilterParameters -and ($testConfig.Parameters -notmatch $FilterParameters))
            {
                continue
            }

            if ($testConfig -contains 'Type')
            {
                $testType = $testConfig.Type
            }
            else
            {
                $testType = 'TAEF'
            }

            $baseId = $testDefFile.BaseName
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
    }

    $tests
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

    & $tePath $dllFile $test.Parameters
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
