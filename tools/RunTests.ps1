<#
.SYNOPSIS
    Run WinAppSDK tests with filtering and configuration options

.DESCRIPTION
    The RunTests script discovers and executes tests from .testdef files in the specified directory.
    It supports building tests before execution, filtering tests by various criteria, and configuring
    test execution parameters including ETW logging and custom parameters.

    The script looks for .testdef files (JSON format) that define test configurations including:
    - Test descriptions and filenames
    - Supported architectures (x86, x64, arm64)
    - Test parameters and execution settings
    - Test type (TAEF, Powershell)
    - Status (Enabled, Disabled)

    Tests can be filtered by multiple criteria and the script supports both TAEF and PowerShell test types.
    When building is enabled, the script will compile test projects before execution.

.PARAMETER Output
    The output directory containing built test binaries. Defaults to "BuildOutput".

.PARAMETER Platform
    Target platform architecture for test execution. Valid values: x86, x64, arm64.
    Defaults to the current processor architecture.

.PARAMETER Configuration
    Build configuration for tests. Valid values: Release, Debug. Defaults to "Release".

.PARAMETER RunDisabled
    Switch to enable execution of tests marked as "Disabled" in their testdef files.

.PARAMETER Build
    Switch to build test projects before execution. Requires Visual Studio and MSBuild.

.PARAMETER FilterTestDef
    Filter tests by testdef file full name using regex pattern matching.

.PARAMETER FilterDescription
    Filter tests by description field using regex pattern matching.

.PARAMETER FilterDllFilename
    Filter tests by filename using regex pattern matching.

.PARAMETER FilterParameters
    Filter tests by parameters field using regex pattern matching.

.PARAMETER CustomParameters
    Override test parameters for all executed tests.

.PARAMETER LogFile
    Path to log file for TAEF test output.

.PARAMETER EnableETWLogging
    Switch to enable ETW (Event Tracing for Windows) logging during test execution.

.PARAMETER WprProfile
    WPR profile name to use with ETW logging.

.PARAMETER EtwLoggerSavePoint
    ETW logger save point configuration.

.PARAMETER EtwLoggerRecordingScope
    ETW logger recording scope setting.

.PARAMETER WprProfilePath
    Path to custom WPR profile file for ETW logging.

.EXAMPLE
    .\RunTests.ps1
    Run all enabled tests in BuildOutput\Release\x64 with default settings.

.EXAMPLE
    .\RunTests.ps1 -Platform x86 -Configuration Debug
    Run tests for x86 architecture in Debug configuration.

.EXAMPLE
    .\RunTests.ps1 -Build -FilterDescription "PackageManager.*Add"
    Build test projects and run only tests that match the regex "PackageManager.*Add" in their description.

.EXAMPLE
    .\RunTests.ps1 -FilterDllFilename "Notification"
    Run tests with "Notification" in its DLL filename .

.EXAMPLE
    .\RunTests.ps1 -EnableETWLogging -WprProfile "MyProfile.wprp" -LogFile "test.log"
    Run tests with ETW logging enabled using custom WPR profile and log file.

.EXAMPLE
    .\RunTests.ps1 -RunDisabled -CustomParameters "/select:@Priority=1"
    Run all tests including disabled ones, overriding parameters for TAEF priority selection.

.NOTES
    - Requires Visual Studio with MSBuild for building tests
    - TAEF (Test Authoring and Execution Framework) must be available for TAEF tests
    - PowerShell test execution is not currently implemented
    - AMD64 platform is automatically converted to x64 for compatibility
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

    [string]$FilterDllFilename,

    [string]$FilterParameters,

    [string]$CustomParameters,

    [string]$LogFile,

    [switch]$EnableETWLogging = $false,

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

if ($Platform -eq "AMD64")
{
    $Platform = "x64"
}

# Import the module containing the functions:
# List-Tests, Get-Tests, Run-Tests
Import-Module "$PSScriptRoot\Tests.psm1"

Write-Host "Configuration: $Configuration, Platform: $Platform"

$scriptParent = Split-Path -parent $PSScriptRoot

if ($Build)
{
    Write-Host ""
    Write-Host "Building tests" -ForegroundColor Yellow
    Write-Host ""

    $testsSourceFolder = Join-Path $scriptParent "test"

    $tests = Get-Tests $testsSourceFolder
    Build-Tests $tests
}

Write-Host ""
Write-Host "Running tests" -ForegroundColor Yellow
Write-Host ""

$StartTime = Get-Date

$configPlat = Join-Path $Configuration $Platform
$outputFolder = Join-Path $scriptParent $Output $configPlat

$tests = Get-Tests $outputFolder | Where-Object {
        (-not $FilterTestDef -or $_.TestDef -match $FilterTestDef) -and
        (-not $FilterDescription -or $_.Description -match $FilterDescription) -and
        (-not $FilterDllFilename -or $_.Filename -match $FilterDllFilename) -and
        (-not $FilterParameters -or $_.Parameters -match $FilterParameters)
    }

List-Tests $tests

$additionalParams = @()

if ($LogFile) {
    $additionalParams += "/LogFile:$LogFile"
}

if ($EnableETWLogging) {
    $additionalParams += "/enableEtwLogging"
    $additionalParams += "/appendWttLogging"
    $additionalParams += "/testMode:ETWLogger"

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

Write-Host "Additional parameters for all tests: $($additionalParams -join ' ')"

Run-Tests -tests $tests -platform $Platform -runDisabled:$RunDisabled -customParameters $CustomParameters -additionalParams $additionalParams

$TotalTime = (Get-Date)-$StartTime
$TotalMinutes = $TotalTime.Minutes
$TotalSeconds = $TotalTime.Seconds
Write-Host ""
Write-Host "Total Running Time: $TotalMinutes minutes and $TotalSeconds seconds"
