<#
.SYNOPSIS
    Build and run tests from a specific .testdef file

.DESCRIPTION
    The BuildAndRunTests script takes a testdef filename (without extension) and build then runs
    the tests defined in that specific .testdef file. This is useful for development when you want
    to run tests for a specific component rather than all tests.

    The script searches for the specified .testdef file in the test directory structure and
    builds the associated test project. It then finds the .testdef file in the output directory,
    lists the tests defined in the .testdef file and executes the tests according to the testdef configuration.

.PARAMETER TestDef
    The name of the .testdef file to run (without the .testdef extension)
    Example: "Deployment" to run "Deployment.testdef"

.PARAMETER Output
    Set the base folder for the script to look for testdefs. Default: BuildOutput

.PARAMETER Platform
    Only run tests for the selected platform (x86, x64, arm64). Default: the current architecture

.PARAMETER Configuration
    Only run tests for the selected configuration (Debug, Release). Default: Release

.PARAMETER RunDisabled
    If set, will run tests that are marked as "Disabled" in the testdef file. Default: false

.EXAMPLE
    .\RunTests.ps1 -TestDef "DeploymentTests"

.EXAMPLE
    .\RunTests.ps1 -TestDef "Deployment" -Platform "x86" -Configuration "Debug"
#>

param(
    [Parameter(Mandatory=$true)]
    [string]$TestDef,

    [string]$Output = "BuildOutput",

    [ValidateSet("x86", "x64", "arm64", IgnoreCase=$true)]
    [string]$Platform = "$($env:PROCESSOR_ARCHITECTURE)",

    [ValidateSet("Release", "Debug", IgnoreCase=$true)]
    [string]$Configuration = "Release",

    [switch]$RunDisabled = $false
)

function Find-TestDefFile
{
    param(
        $testDefName,
        $baseFolder
    )

    $testDefFileName = "$testDefName.testdef"

    Write-Host "Searching for testdef file '$testDefFileName' in '$baseFolder'..."

    $testDefFile = Get-ChildItem -Recurse -Filter $testDefFileName $baseFolder -ErrorAction SilentlyContinue | Select-Object -First 1

    if ($null -eq $testDefFile)
    {
        Write-Error "Could not find testdef file '$testDefFileName' in '$baseFolder'"
        Exit 1
    }

    Write-Host "Found testdef file: $($testDefFile.FullName)"
    return $testDefFile
}

function Build-Tests
{
    param(
        $testDefFile
    )

    $VCToolsInstallDir = . "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -latest -prerelease -requires Microsoft.Component.MSBuild -property installationPath
    Write-Host "VCToolsInstallDir: $VCToolsInstallDir"

    $msbuildPath = Join-Path $VCToolsInstallDir "MSBuild\Current\Bin\msbuild.exe"
    Write-Host "MSBuild Path: $msbuildPath"

    $testFolder = Split-Path -parent $testDefFile
    Write-Host "Building tests in folder: $testFolder"
    $projFile = Get-ChildItem -Filter "*.vcxproj" -Path $testFolder | Select-Object -First 1

    if ($null -eq $projFile)
    {
        Write-Error "Could not find a .vcxproj file in $testFolder"
        Exit 1
    }

    Write-Host "Found project file: $projFile"

    # & $msbuildPath $projFile.FullName /p:Configuration=$Configuration /p:Platform=$Platform /v:minimal
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

    & $tePath $dllFile $test.Parameters
}

function Run-Tests
{
    param($testDefFile)

    $tests = Get-Tests $testDefFile
    Write-Host "Running tests from $($testDefFile.Name)..."

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

Write-Host ""
Write-Host "Building tests from testdef: $TestDef" -ForegroundColor Yellow
Write-Host ""

$testsSourceFolder = Join-Path $scriptParent "test"

$sourceTestDefFile = Find-TestDefFile $TestDef $testsSourceFolder
Build-Tests $sourceTestDefFile

Write-Host ""
Write-Host "Running tests for testdef: $TestDef" -ForegroundColor Yellow
Write-Host ""

$StartTime = Get-Date

& $PSSCriptRoot\DoTest.ps1 -FilterTestDef $TestDef -Platform $Platform -Configuration $Configuration -List

$TotalTime = (Get-Date)-$StartTime
$TotalMinutes = $TotalTime.Minutes
$TotalSeconds = $TotalTime.Seconds
Write-Host ""
Write-Host "Total Running Time: $TotalMinutes minutes and $TotalSeconds seconds"
