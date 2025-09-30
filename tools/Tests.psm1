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

function List-Tests
{
    param([TestInfo[]]$tests)

    $tests | Sort-Object -Property Test | Format-Table Test,Description,Type,Filename,Parameters,Architectures,Status -AutoSize | Out-String -Width 512
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

