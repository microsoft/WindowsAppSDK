<#
.SYNOPSIS
    Run tests from a specific .testdef file

.DESCRIPTION
    The RunTests script takes a testdef filename (without extension) and runs the tests defined in that
    specific .testdef file. This is useful for development when you want to run tests for a specific
    component rather than all tests.

    The script searches for the specified .testdef file in the BuildOutput directory structure and
    executes the tests according to the testdef configuration.

.PARAMETER TestDef
    The name of the .testdef file to run (without the .testdef extension)
    Example: "Deployment" to run "Deployment.testdef"

.PARAMETER Output
    Set the base folder for the script to look for testdefs. Default: BuildOutput

.PARAMETER Platform
    Only run tests for the selected platform (x86, x64, arm64). Default: x64

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

    [Parameter]
    [string]$Output = "BuildOutput",

    [Parameter]
    [ValidateSet("x86", "x64", "arm64", IgnoreCase=$true)]
    [string]$Platform = "$($env:PROCESSOR_ARCHITECTURE)",

    [Parameter]
    [ValidateSet("Release", "Debug", IgnoreCase=$true)]
    [string]$Configuration = "Release",

    [Parameter]
    [switch]$RunDisabled = $false
)

function Find-TestDefFile
{
    param($testDefName)

    $configPlat = Join-Path $Configuration $Platform
    $scriptParent = Split-Path -parent $PSScriptRoot
    $Output = Join-Path $scriptParent $Output
    $outputFolderPath = Join-Path $Output $configPlat
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

Write-Host "RunTests.ps1 - Running tests for testdef: $TestDef"
Write-Host "Configuration: $Configuration, Platform: $Platform"
Write-Host ""

$StartTime = Get-Date

# Find the testdef file
$testDefFile = Find-TestDefFile $TestDef

List-Tests $testDefFile
Run-Tests $testDefFile

$TotalTime = (Get-Date)-$StartTime
$TotalMinutes = $TotalTime.Minutes
$TotalSeconds = $TotalTime.Seconds
Write-Host ""
Write-Host "Total Running Time: $TotalMinutes minutes and $TotalSeconds seconds"
