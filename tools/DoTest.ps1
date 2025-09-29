<#
#>

param(
    [ValidateSet("x86", "x64", "arm64", IgnoreCase=$true)]
    [Parameter(Mandatory=$true)]
    [string]$Platform,

    [ValidateSet("Release", "Debug", IgnoreCase=$true)]
    [Parameter(Mandatory=$true)]
    [string]$Configuration,

    [string]$OutputFolder = "BuildOutput",

    [string]$FilterTestDef,

    [string]$FilterDescription,

    [string]$FilterFilename,

    [string]$IgnoreFilename,

    [string]$FilterParameters,

    [string]$CustomParameters,

    [switch]$List = $true,

    [switch]$Test = $true,

    [switch]$EnableETWLogging = $false,

    [switch]$AppendWttLogging = $false,

    [switch]$ScreencaptureOnError = $false,

    [string]$LogFile,

    [string]$TestMode,

    [string]$WprProfile,

    [string]$EtwLoggerSavePoint,

    [string]$EtwLoggerRecordingScope,

    [string]$WprProfilePath,

    [switch]$RunDisabled = $false
)

function Get-Tests
{
    $configPlat = Join-Path $Configuration $Platform
    $outputFolderPath = Join-Path $OutputFolder $configPlat

    $tests = @()
    foreach ($testdef in (Get-ChildItem -Recurse -Filter "*.testdef" $outputFolderPath))
    {
        $testJson = Get-Content -Raw $testdef.FullName | ConvertFrom-Json

        $count = 0
        foreach ($testConfig in $testJson.Tests)
        {
            $testConfig | Write-Host

            # Apply filters
            # If a filter is set and the test property does not contain the filter regex, skip this test
            if ($FilterTestDef -and ($testdef.BaseName -notmatch $FilterTestDef))
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

            $baseId = $testdef.BaseName
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

    if($CustomParameters)
    {
        $test.Parameters = $CustomParameters
    }

    $TestParameters = ""

    if ($EnableETWLogging)
    {
        $TestParameters += " /enableEtwLogging"

        if ($WprProfile)
        {
            $TestParameters += " /EtwLogger:WprProfile=$WprProfile"
        }

        if ($EtwLoggerSavePoint)
        {
            $TestParameters += " /EtwLogger:SavePoint=$EtwLoggerSavePoint"
        }

        if ($EtwLoggerRecordingScope)
        {
            $TestParameters += " /EtwLogger:RecordingScope=$EtwLoggerRecordingScope"
        }

        if ($WprProfilePath)
        {
            $TestParameters += " /EtwLogger:WprProfileFile=$WprProfilePath"
        }
    }

    if ($AppendWttLogging)
    {
        $TestParameters += " /appendWttLogging"
    }

    if ($ScreencaptureOnError)
    {
        $TestParameters += " /screencaptureOnError"
    }

    if ($LogFile)
    {
        $TestParameters += " /logFile:$LogFile"
    }

    if ($TestMode)
    {
        $TestParameters += " /testMode:$TestMode"
    }


    & $tePath $dllFile $test.Parameters $TestParameters
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

$tests = Get-Tests

if ($List -eq $true)
{
    List-Tests $tests | Out-String
}

if ($Test -eq $true)
{
    Run-Tests $tests
}
