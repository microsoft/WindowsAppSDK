# You must keep your mouse/keyboard still while script is running

param(
    [string[]]$TemplateId
)

$ErrorActionPreference = 'Stop'

$uiTimeout = 10000
$languageFilterTimeout = 30000
$templateTimeout = 15000
$projectLoadTimeout = 60000
$deploymentTimeout = 120000
$buildTimeout = 180000
$testTimeout = 180000
$exitCode = 0
$testResults = [System.Collections.Generic.List[object]]::new()

Add-Type -TypeDefinition @'
using System;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;

public static class RunningVisualStudio
{
    [DllImport("ole32.dll")]
    private static extern int CreateBindCtx(uint reserved, out IBindCtx bindContext);

    [DllImport("ole32.dll")]
    private static extern int GetRunningObjectTable(uint reserved, out IRunningObjectTable runningObjectTable);

    public static object GetDte(int processId)
    {
        GetRunningObjectTable(0, out IRunningObjectTable runningObjectTable);
        runningObjectTable.EnumRunning(out IEnumMoniker monikerEnumerator);
        monikerEnumerator.Reset();

        IMoniker[] monikers = new IMoniker[1];
        while (monikerEnumerator.Next(1, monikers, IntPtr.Zero) == 0)
        {
            CreateBindCtx(0, out IBindCtx bindContext);
            monikers[0].GetDisplayName(bindContext, null, out string displayName);
            if (displayName.StartsWith("!VisualStudio.DTE.", StringComparison.Ordinal) &&
                displayName.EndsWith(":" + processId, StringComparison.Ordinal))
            {
                runningObjectTable.GetObject(monikers[0], out object dte);
                return dte;
            }
        }

        return null;
    }
}
'@

function Invoke-WinAppRequired
{
    param(
        [Parameter(Mandatory)]
        [string]$Checkpoint,

        [Parameter(Mandatory)]
        [string[]]$Arguments,

        [switch]$PassThru
    )

    $output = & winapp @Arguments 2>&1
    $winAppExitCode = $LASTEXITCODE
    if ($winAppExitCode -ne 0)
    {
        $details = $output -join [Environment]::NewLine
        throw "WinApp UI checkpoint '$Checkpoint' failed with exit code $winAppExitCode.$([Environment]::NewLine)$details"
    }

    if ($PassThru)
    {
        return $output
    }

    $output | ForEach-Object { Write-Host $_ }
}

function Wait-WinAppElement
{
    param(
        [Parameter(Mandatory)]
        [string]$Identifier,

        [string]$App,

        [string]$Window,

        [int]$Timeout = $uiTimeout
    )

    $arguments = @('ui', 'wait-for', $Identifier)
    if ($App)
    {
        $arguments += @('-a', $App)
    }
    if ($Window)
    {
        $arguments += @('-w', $Window)
    }
    $arguments += @('--timeout', $Timeout)

    Invoke-WinAppRequired -Checkpoint "Wait for '$Identifier'" -Arguments $arguments
}

function Wait-WinAppElementByNamePrefix
{
    param(
        [Parameter(Mandatory)]
        [string]$Name,

        [Parameter(Mandatory)]
        [string]$Window,

        [int]$Timeout = $templateTimeout
    )

    $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
    $lastOutput = @()
    do
    {
        $lastOutput = & winapp ui search $Name -w $Window --json 2>&1
        $searchExitCode = $LASTEXITCODE
        if ($searchExitCode -eq 0)
        {
            try
            {
                $searchResult = ($lastOutput -join [Environment]::NewLine) | ConvertFrom-Json
                $elements = @($searchResult.matches | Where-Object {
                    $_.type -eq 'ListItem' -and
                    $_.isEnabled -and
                    $_.isInvokable -and
                    $_.name -and
                    ($_.name -eq $Name -or $_.name.StartsWith("$Name,", [StringComparison]::Ordinal))
                })
                $element = $elements | Where-Object {
                    $_.name -eq $Name -or $_.name.StartsWith("$Name, C#", [StringComparison]::Ordinal)
                } | Select-Object -First 1
                if ($element.selector)
                {
                    if ($element.isOffscreen)
                    {
                        Invoke-WinAppRequired -Checkpoint "Scroll template '$Name' into view" -Arguments @('ui', 'scroll-into-view', $element.selector, '-w', $Window)
                    }
                    Write-Host "Element '$($element.name)' found after $($stopwatch.ElapsedMilliseconds)ms"
                    return $element.selector
                }
            }
            catch
            {
                $lastOutput += $_.Exception.Message
            }
        }

        [System.Threading.Thread]::Sleep(100)
    }
    while ($stopwatch.ElapsedMilliseconds -lt $Timeout)

    $details = $lastOutput -join [Environment]::NewLine
    throw "WinApp UI checkpoint 'Wait for template '$Name'' failed after ${Timeout}ms.$([Environment]::NewLine)$details"
}

function Set-NewProjectLanguageFilter
{
    param(
        [Parameter(Mandatory)]
        [string]$Window
    )

    $searchOutput = Invoke-WinAppRequired -Checkpoint 'Find language filter' -Arguments @('ui', 'search', 'Language filter', '-a', 'devenv', '-w', $Window, '--json') -PassThru
    $searchResult = ($searchOutput -join [Environment]::NewLine) | ConvertFrom-Json
    $languageFilter = $searchResult.matches | Where-Object {
        $_.type -eq 'ComboBox' -and
        $_.name -eq 'Language filter' -and
        $_.isEnabled -and
        $_.selector
    } | Select-Object -First 1
    if (-not $languageFilter)
    {
        throw 'WinApp UI did not find the New Project language filter.'
    }

    Invoke-WinAppRequired -Checkpoint 'Open language filter' -Arguments @('ui', 'invoke', $languageFilter.selector, '-a', 'devenv', '-w', $Window)
    $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
    $csharpOption = $null
    do
    {
        $optionOutput = & winapp ui search 'C#' -a devenv -w $Window --json 2>&1
        if ($LASTEXITCODE -eq 0)
        {
            $optionResult = ($optionOutput -join [Environment]::NewLine) | ConvertFrom-Json
            $csharpOption = $optionResult.matches | Where-Object {
                $_.type -eq 'ListItem' -and
                $_.name -eq 'C#' -and
                $_.isEnabled -and
                $_.selector
            } | Select-Object -First 1
        }
        if (-not $csharpOption)
        {
            [System.Threading.Thread]::Sleep(100)
        }
    }
    while (-not $csharpOption -and $stopwatch.ElapsedMilliseconds -lt $languageFilterTimeout)

    if (-not $csharpOption)
    {
        throw "WinApp UI did not find the 'C#' language option within ${languageFilterTimeout}ms."
    }

    Invoke-WinAppRequired -Checkpoint "Select 'C#' language option" -Arguments @('ui', 'click', $csharpOption.selector, '-a', 'devenv', '-w', $Window)
}

function Get-DevenvHWND
{
    $output = Invoke-WinAppRequired -Checkpoint 'List Visual Studio windows' -Arguments @('ui', 'list-windows', '-a', 'devenv') -PassThru
    Write-Host "List of windows for devenv: $output"
    $windowLines = @($output | Select-String 'HWND (\d+):')
    $mainWindow = $windowLines | Where-Object { $_.Line -match 'Microsoft Visual Studio"' } | Select-Object -First 1
    $selectedWindow = if ($mainWindow) { $mainWindow } else { $windowLines | Select-Object -First 1 }
    $hwnd = $selectedWindow.Matches[0].Groups[1].Value
    if (-not $hwnd)
    {
        throw 'WinApp UI did not return an HWND for Visual Studio.'
    }

    return $hwnd
}

function Get-DevenvWindowByTitle
{
    param(
        [Parameter(Mandatory)]
        [string]$Title
    )

    $output = Invoke-WinAppRequired -Checkpoint "List Visual Studio windows for '$Title'" -Arguments @('ui', 'list-windows', '-a', 'devenv') -PassThru
    $titlePattern = 'HWND (\d+): "' + [regex]::Escape($Title) + '"'
    $window = $output | Select-String $titlePattern | Select-Object -First 1
    if (-not $window)
    {
        throw "WinApp UI did not return a Visual Studio-owned window titled '$Title'."
    }

    return $window.Matches[0].Groups[1].Value
}

function Get-WinAppHWND
{
    param(
        [Parameter(Mandatory)]
        [string]$App
    )

    $output = Invoke-WinAppRequired -Checkpoint "List '$App' windows" -Arguments @('ui', 'list-windows', '-a', $App) -PassThru
    $hwnd = $output | Select-String 'HWND (\d+):' | Select-Object -First 1 | ForEach-Object { $_.Matches[0].Groups[1].Value }
    if (-not $hwnd)
    {
        throw "WinApp UI did not return an HWND for '$App'."
    }

    return $hwnd
}

function Invoke-VisualStudioCommand
{
    param(
        [Parameter(Mandatory)]
        [string]$Menu,

        [Parameter(Mandatory)]
        [string]$Command,

        [Parameter(Mandatory)]
        [string]$Window
    )

    $menuSearchOutput = Invoke-WinAppRequired -Checkpoint "Find '$Menu' menu" -Arguments @('ui', 'search', $Menu, '-a', 'devenv', '-w', $Window, '--json') -PassThru
    $menuSearchResult = ($menuSearchOutput -join [Environment]::NewLine) | ConvertFrom-Json
    $menuItem = $menuSearchResult.matches | Where-Object {
        $_.type -eq 'MenuItem' -and
        $_.name -eq $Menu -and
        $_.isEnabled -and
        $_.selector
    } | Select-Object -First 1
    if (-not $menuItem)
    {
        throw "WinApp UI did not find an enabled '$Menu' menu item."
    }

    Invoke-WinAppRequired -Checkpoint "Open '$Menu' menu" -Arguments @('ui', 'invoke', $menuItem.selector, '-a', 'devenv', '-w', $Window)
    $commandSearchOutput = Invoke-WinAppRequired -Checkpoint "Find '$Command' command" -Arguments @('ui', 'search', $Command, '-a', 'devenv', '-w', $Window, '--json') -PassThru
    $commandSearchResult = ($commandSearchOutput -join [Environment]::NewLine) | ConvertFrom-Json
    $commandItem = $commandSearchResult.matches | Where-Object {
        $_.type -eq 'MenuItem' -and
        ($_.name -eq $Command -or $_.name.StartsWith("$Command ", [StringComparison]::Ordinal)) -and
        $_.isEnabled -and
        $_.selector
    } | Select-Object -First 1
    if (-not $commandItem)
    {
        throw "WinApp UI did not find an enabled '$Command' command in the '$Menu' menu."
    }

    Invoke-WinAppRequired -Checkpoint "Invoke '$Command'" -Arguments @('ui', 'invoke', $commandItem.selector, '-a', 'devenv', '-w', $Window)
}

function Get-VisualStudioPaneText
{
    param(
        [Parameter(Mandatory)]
        [string]$Pane,

        [Parameter(Mandatory)]
        [string]$Window
    )

    $lines = [System.Collections.Generic.List[string]]::new()
    $searchOutput = & winapp ui search $Pane -a devenv -w $Window --json 2>&1
    if ($LASTEXITCODE -eq 0)
    {
        try
        {
            $searchResult = ($searchOutput -join [Environment]::NewLine) | ConvertFrom-Json
            foreach ($match in $searchResult.matches | Where-Object { $_.selector })
            {
                $value = & winapp ui get-value $match.selector -a devenv -w $Window 2>&1
                if ($LASTEXITCODE -eq 0 -and $value)
                {
                    $lines.Add(($value -join [Environment]::NewLine))
                }
            }
        }
        catch
        {
            $lines.Add("Unable to parse WinApp search results: $($_.Exception.Message)")
        }
    }

    $inspection = & winapp ui inspect $Pane -a devenv -w $Window 2>&1
    if ($inspection)
    {
        $lines.Add(($inspection -join [Environment]::NewLine))
    }

    return ($lines | Select-Object -Unique) -join [Environment]::NewLine
}

function Open-VisualStudioPane
{
    param(
        [Parameter(Mandatory)]
        [ValidateSet('Error List', 'Output', 'Test Explorer')]
        [string]$Pane,

        [Parameter(Mandatory)]
        [string]$Window
    )

    $menu = if ($Pane -eq 'Test Explorer') { 'Test' } else { 'View' }
    Invoke-VisualStudioCommand -Menu $menu -Command $Pane -Window $Window
}

function Get-TemplateFailureDiagnostics
{
    param(
        [Parameter(Mandatory)]
        [string]$Window
    )

    $diagnostics = [ordered]@{
        ErrorListText = ''
        OutputWindowText = ''
        CaptureErrors = [System.Collections.Generic.List[string]]::new()
    }

    try
    {
        Open-VisualStudioPane -Pane 'Error List' -Window $Window
        $diagnostics.ErrorListText = Get-VisualStudioPaneText -Pane 'Error List' -Window $Window
    }
    catch
    {
        $diagnostics.CaptureErrors.Add("Error List capture failed: $($_.Exception.Message)")
    }

    try
    {
        Open-VisualStudioPane -Pane 'Output' -Window $Window
        $diagnostics.OutputWindowText = Get-VisualStudioPaneText -Pane 'Output' -Window $Window
    }
    catch
    {
        $diagnostics.CaptureErrors.Add("Output window capture failed: $($_.Exception.Message)")
    }

    return $diagnostics
}

function Invoke-VisualStudioBuild
{
    param(
        [Parameter(Mandatory)]
        [int]$ProcessId
    )

    $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
    $dte = $null
    do
    {
        $dte = [RunningVisualStudio]::GetDte($ProcessId)
        if (-not $dte)
        {
            [System.Threading.Thread]::Sleep(250)
        }
    }
    while (-not $dte -and $stopwatch.ElapsedMilliseconds -lt $uiTimeout)

    if (-not $dte)
    {
        throw "Visual Studio DTE was not available for process $ProcessId within ${uiTimeout}ms."
    }

    $dte.Solution.SolutionBuild.Build($true)
    $failedProjects = $dte.Solution.SolutionBuild.LastBuildInfo
    if ($failedProjects -ne 0)
    {
        [System.Threading.Thread]::Sleep(1000)
        $dte.Solution.SolutionBuild.Build($true)
        $failedProjects = $dte.Solution.SolutionBuild.LastBuildInfo
        if ($failedProjects -ne 0)
        {
            throw "Visual Studio build failed for $failedProjects project(s) after two attempts."
        }
    }
}

function Stop-VisualStudioDebugging
{
    param(
        [Parameter(Mandatory)]
        [int]$ProcessId
    )

    $dte = [RunningVisualStudio]::GetDte($ProcessId)
    if (-not $dte)
    {
        throw "Visual Studio DTE was not available for process $ProcessId."
    }

    if ($dte.Debugger.CurrentMode -ne 1)
    {
        $dte.ExecuteCommand('Debug.StopDebugging')
    }
}

function Invoke-VisualStudioDteCommand
{
    param(
        [Parameter(Mandatory)]
        [int]$ProcessId,

        [Parameter(Mandatory)]
        [string]$Command
    )

    $dte = [RunningVisualStudio]::GetDte($ProcessId)
    if (-not $dte)
    {
        throw "Visual Studio DTE was not available for process $ProcessId."
    }

    $dte.ExecuteCommand($Command)
}

function Wait-ForUnitTestRun
{
    param(
        [Parameter(Mandatory)]
        [int]$ExpectedPassed,

        [Parameter(Mandatory)]
        [string]$Window
    )

    $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
    $lastOutput = @()
    do
    {
        $searchOutput = & winapp ui search 'tests' -a devenv -w $Window --json 2>&1
        if ($LASTEXITCODE -eq 0)
        {
            try
            {
                $searchResult = ($searchOutput -join [Environment]::NewLine) | ConvertFrom-Json
                $counterNames = @($searchResult.matches | Where-Object {
                    $_.type -eq 'Button' -and $_.name -match '^\d+ (passed|failed) tests? '
                } | Select-Object -ExpandProperty name)
                $lastOutput = $counterNames
                $failedCount = @($counterNames | Where-Object { $_ -match '^(\d+) failed tests? ' } | ForEach-Object { [int]$matches[1] } | Measure-Object -Maximum).Maximum
                if ($failedCount -gt 0)
                {
                    throw "$failedCount unit test(s) failed.$([Environment]::NewLine)$($counterNames -join [Environment]::NewLine)"
                }

                $passedCount = @($counterNames | Where-Object { $_ -match '^(\d+) passed tests? ' } | ForEach-Object { [int]$matches[1] } | Measure-Object -Maximum).Maximum
                if ($passedCount -eq $ExpectedPassed)
                {
                    return
                }
            }
            catch
            {
                if ($_.Exception.Message -like '*unit test(s) failed.*')
                {
                    throw
                }
                $lastOutput = @($_.Exception.Message)
            }
        }

        [System.Threading.Thread]::Sleep(250)
    }
    while ($stopwatch.ElapsedMilliseconds -lt $testTimeout)

    $runnerState = & winapp ui inspect -a devenv -w $Window --depth 12 2>&1
    throw "Unit tests did not report $ExpectedPassed passed within ${testTimeout}ms.$([Environment]::NewLine)$($lastOutput -join [Environment]::NewLine)$([Environment]::NewLine)$($runnerState -join [Environment]::NewLine)"
}

function Start-UnitTestRun
{
    param(
        [Parameter(Mandatory)]
        [string]$Window
    )

    $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
    $lastOutput = @()
    do
    {
        $lastOutput = & winapp ui search 'Run All Tests In View' -a devenv -w $Window --json 2>&1
        if ($LASTEXITCODE -eq 0)
        {
            try
            {
                $searchResult = ($lastOutput -join [Environment]::NewLine) | ConvertFrom-Json
                $runAllButton = $searchResult.matches | Where-Object {
                    $_.type -eq 'Button' -and
                    $_.name -eq 'Run All Tests In View' -and
                    $_.isEnabled -and
                    $_.selector
                } | Select-Object -First 1
                if ($runAllButton)
                {
                    Invoke-WinAppRequired -Checkpoint 'Run all unit tests' -Arguments @('ui', 'click', $runAllButton.selector, '-a', 'devenv', '-w', $Window)
                    return
                }
            }
            catch
            {
                $lastOutput = @($_.Exception.Message)
            }
        }

        [System.Threading.Thread]::Sleep(250)
    }
    while ($stopwatch.ElapsedMilliseconds -lt $uiTimeout)

    throw "The UnitTest runner's Run All button did not become enabled within ${uiTimeout}ms.$([Environment]::NewLine)$($lastOutput -join [Environment]::NewLine)"
}

function Invoke-TemplateTest
{
    param(
        [Parameter(Mandatory)]
        [pscustomobject]$Template,

        [Parameter(Mandatory)]
        [string]$Devenv
    )

    $visualStudioProcess = $null
    $activeHWND = $null
    $appName = $null
    $appProcessIds = @()
    $existingAppProcessIds = @()
    $checkpoint = 'Launch Visual Studio'
    $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
    $result = [ordered]@{
        Template = $Template.Name
        TemplateId = $Template.Id
        Status = 'Failed'
        FailedCheckpoint = ''
        Load = 'Not run'
        Build = 'Not run'
        Deploy = if ($Template.CanDeploy) { 'Not run' } else { 'N/A' }
        Tests = if ($Template.RunUnitTests) { 'Not run' } else { 'N/A' }
        Duration = [TimeSpan]::Zero
        ErrorMessage = ''
        ErrorListText = ''
        OutputWindowText = ''
        DiagnosticCaptureErrors = ''
    }

    try
    {
        Write-Host "`n===== Testing '$($Template.Name)' =====" -ForegroundColor Cyan
        $visualStudioProcess = Start-Process -FilePath $Devenv -PassThru
        Wait-WinAppElement -Identifier 'TitleBar' -App 'devenv' -Timeout $uiTimeout
        $activeHWND = Get-DevenvHWND

        $checkpoint = 'Open Create a new project'
        Wait-WinAppElement -Identifier 'Create a new project' -App 'devenv' -Window $activeHWND
        Invoke-WinAppRequired -Checkpoint $checkpoint -Arguments @('ui', 'invoke', 'Create a new project', '-a', 'devenv', '-w', $activeHWND)
        Wait-WinAppElement -Identifier 'ListViewTemplates' -App 'devenv' -Timeout $uiTimeout
        Set-NewProjectLanguageFilter -Window $activeHWND

        $checkpoint = "Select template '$($Template.Name)'"
        $templateSelector = Wait-WinAppElementByNamePrefix -Name $Template.Name -Window $activeHWND -Timeout $templateTimeout
        Invoke-WinAppRequired -Checkpoint $checkpoint -Arguments @('ui', 'invoke', $templateSelector, '-w', $activeHWND)
        Wait-WinAppElement -Identifier 'Next' -App 'devenv' -Window $activeHWND -Timeout $uiTimeout
        $rawJson = Invoke-WinAppRequired -Checkpoint "Inspect 'Next'" -Arguments @('ui', 'inspect', 'Next', '-a', 'devenv', '-w', $activeHWND, '--json') -PassThru
        $nextButton = ($rawJson -join [Environment]::NewLine) | ConvertFrom-Json
        $nextButtonSelector = $nextButton.windows[0].elements[0].selector
        Invoke-WinAppRequired -Checkpoint 'Advance template selection' -Arguments @('ui', 'invoke', $nextButtonSelector, '-w', $activeHWND)

        $checkpoint = 'Create project'
        Wait-WinAppElement -Identifier 'Next' -App 'devenv' -Window $activeHWND -Timeout $uiTimeout
        Invoke-WinAppRequired -Checkpoint $checkpoint -Arguments @('ui', 'invoke', 'button_Next', '-w', $activeHWND)

        if ($Template.ConfirmTargetVersions)
        {
            $checkpoint = 'Confirm target platform versions'
            Wait-WinAppElement -Identifier 'New Windows Project' -App 'devenv' -Timeout $uiTimeout
            $targetVersionHWND = Get-DevenvWindowByTitle -Title 'New Windows Project'
            Wait-WinAppElement -Identifier 'OK' -App 'devenv' -Window $targetVersionHWND -Timeout $uiTimeout
            Invoke-WinAppRequired -Checkpoint $checkpoint -Arguments @('ui', 'invoke', 'OK', '-a', 'devenv', '-w', $targetVersionHWND)
        }

        $checkpoint = 'Load project'
        Wait-WinAppElement -Identifier 'SolutionExplorer' -App 'devenv' -Timeout $projectLoadTimeout
        $activeHWND = Get-DevenvHWND
        $result.Load = 'Passed'

        $checkpoint = 'Build solution'
        Invoke-VisualStudioDteCommand -ProcessId $visualStudioProcess.Id -Command 'View.Output'
        Invoke-VisualStudioBuild -ProcessId $visualStudioProcess.Id
        $result.Build = 'Passed'

        if ($Template.CanDeploy)
        {
            $checkpoint = 'Deploy application'
            Wait-WinAppElement -Identifier 'Debug Target' -App 'devenv' -Window $activeHWND -Timeout $uiTimeout
            $rawJson = Invoke-WinAppRequired -Checkpoint "Inspect 'Debug Target'" -Arguments @('ui', 'inspect', 'Debug Target', '-a', 'devenv', '-w', $activeHWND, '--json') -PassThru
            $debugButtonJson = ($rawJson -join [Environment]::NewLine) | ConvertFrom-Json
            $debugButtonSelector = $debugButtonJson.windows[0].elements[0].selector
            $windowTitle = $debugButtonJson.windows[0].title
            if ($windowTitle -notmatch '([^\\/:*?""<>|]+)\s+-\s+Microsoft Visual Studio')
            {
                throw "Failed to extract app name from Visual Studio window title: $windowTitle"
            }

            $appName = $matches[1].Trim()
            if ($Template.RunUnitTests)
            {
                $checkpoint = 'Open Test Explorer'
                Invoke-VisualStudioDteCommand -ProcessId $visualStudioProcess.Id -Command 'TestExplorer.ShowTestExplorer'
                Wait-WinAppElement -Identifier 'Test Explorer' -App 'devenv' -Timeout $uiTimeout
                $appHWND = Get-DevenvWindowByTitle -Title $appName
                $checkpoint = 'Start unit tests'
                Start-UnitTestRun -Window $appHWND
                $checkpoint = 'Confirm unit tests passed'
                Wait-ForUnitTestRun -ExpectedPassed 2 -Window $appHWND
                $result.Deploy = 'Passed'
                $result.Tests = '2/2 passed'
            }
            else
            {
                $existingAppProcessIds = @(Get-Process -Name $appName -ErrorAction SilentlyContinue | Select-Object -ExpandProperty Id)
                Invoke-WinAppRequired -Checkpoint $checkpoint -Arguments @('ui', 'invoke', $debugButtonSelector, '-w', $activeHWND)
                Wait-WinAppElement -Identifier 'TitleBar' -App $appName -Timeout $deploymentTimeout
                $appProcessIds = @(Get-Process -Name $appName -ErrorAction SilentlyContinue | Where-Object { $_.Id -notin $existingAppProcessIds } | Select-Object -ExpandProperty Id)
                $result.Deploy = 'Passed'
            }

            foreach ($appProcessId in $appProcessIds)
            {
                Stop-Process -Id $appProcessId -Force -ErrorAction SilentlyContinue
            }
            $appProcessIds = @()
            Stop-VisualStudioDebugging -ProcessId $visualStudioProcess.Id
        }

        $result.Status = 'Passed'
        Write-Host "PASS: '$($Template.Name)' completed all required checks." -ForegroundColor Green
    }
    catch
    {
        $result.FailedCheckpoint = $checkpoint
        $result.ErrorMessage = $_.Exception.Message
        Write-Error "FAIL: '$($Template.Name)' at '$checkpoint': $($_.Exception.Message)" -ErrorAction Continue

        if ($activeHWND)
        {
            $diagnostics = Get-TemplateFailureDiagnostics -Window $activeHWND
            $result.ErrorListText = $diagnostics.ErrorListText
            $result.OutputWindowText = $diagnostics.OutputWindowText
            $result.DiagnosticCaptureErrors = $diagnostics.CaptureErrors -join [Environment]::NewLine
        }
    }
    finally
    {
        if ($appName)
        {
            $appProcessIds = @(Get-Process -Name $appName -ErrorAction SilentlyContinue | Where-Object { $_.Id -notin $existingAppProcessIds } | Select-Object -ExpandProperty Id)
        }
        foreach ($appProcessId in $appProcessIds)
        {
            Stop-Process -Id $appProcessId -Force -ErrorAction SilentlyContinue
        }
        if ($visualStudioProcess -and -not $visualStudioProcess.HasExited)
        {
            Stop-Process -Id $visualStudioProcess.Id -Force -ErrorAction SilentlyContinue
            [void]$visualStudioProcess.WaitForExit(10000)
        }

        $stopwatch.Stop()
        $result.Duration = $stopwatch.Elapsed
    }

    return [pscustomobject]$result
}

function Write-TestReport
{
    param(
        [Parameter(Mandatory)]
        [AllowEmptyCollection()]
        [object[]]$Results,

        [Parameter(Mandatory)]
        [string]$ReportPath
    )

    $report = [System.Text.StringBuilder]::new()
    [void]$report.AppendLine('LocalDev C# VSIX Template Test Report')
    [void]$report.AppendLine("Generated: $(Get-Date -Format 'yyyy-MM-dd HH:mm:ss K')")
    [void]$report.AppendLine()
    [void]$report.AppendLine(($Results | Select-Object Template, Load, Build, Deploy, Tests, Status, FailedCheckpoint, Duration | Format-Table -AutoSize | Out-String).TrimEnd())

    foreach ($result in $Results | Where-Object Status -eq 'Failed')
    {
        [void]$report.AppendLine()
        [void]$report.AppendLine("===== FAILURE: $($result.Template) =====")
        [void]$report.AppendLine("Checkpoint: $($result.FailedCheckpoint)")
        [void]$report.AppendLine("Error: $($result.ErrorMessage)")
        [void]$report.AppendLine()
        [void]$report.AppendLine('--- Visual Studio Error List ---')
        [void]$report.AppendLine($(if ($result.ErrorListText) { $result.ErrorListText } else { '<no text captured>' }))
        [void]$report.AppendLine()
        [void]$report.AppendLine('--- Visual Studio Output Window ---')
        [void]$report.AppendLine($(if ($result.OutputWindowText) { $result.OutputWindowText } else { '<no text captured>' }))
        if ($result.DiagnosticCaptureErrors)
        {
            [void]$report.AppendLine()
            [void]$report.AppendLine('--- Diagnostic Capture Errors ---')
            [void]$report.AppendLine($result.DiagnosticCaptureErrors)
        }
    }

    $reportDirectory = Split-Path $ReportPath
    if (-not (Test-Path $reportDirectory))
    {
        New-Item -Path $reportDirectory -ItemType Directory -Force | Out-Null
    }
    [IO.File]::WriteAllText($ReportPath, $report.ToString())
    Write-Host $report.ToString()
}

# Check VS 2026 is installed on the machine
# VS 2026 appears as "18". The alternative would be "2022", but the templates are only
# updated for VS 2026 unless it is a hot bug
$vswhere = "C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe"

$installPath = & $vswhere -version "[18.0,19.0)" -latest -property installationPath
$devenv = Join-Path $installPath 'Common7\IDE\devenv.exe'

try
{
    if (-not (Test-Path $devenv -PathType Leaf))
    {
        throw 'Visual Studio 2026 is not installed. Please install it before running this script.'
    }
    Write-Host "Visual Studio 2026 is installed at: $installPath"
    Write-Host "Devenv path: $devenv"

    if (Get-Process -Name 'devenv' -ErrorAction SilentlyContinue)
    {
        throw 'Visual Studio is already running. Close all Visual Studio instances so this test can target and clean up only the instance it launches.'
    }

# LocalDev is installed per-user at $env:LocalAppData\Microsoft\VisualStudio\<version>\Extensions\<random>
# TODO: Add C++ LocalDev VSIX DLL search
$localDevCsVsixDll = Get-ChildItem -Path "$env:localappdata" -Filter 'WindowsAppSDK.Cs.Extension.Dev17.dll' -File -Recurse | Select-Object -ExpandProperty FullName

    if (-not (Test-Path $localDevCsVsixDll -PathType Leaf))
    {
        throw 'LocalDev CS VSIX DLL is not installed. Please install it before running this script using dev/templates/VSIX/build-local-vsix-package/build-install-localdev-vsix.ps1.'
    }
    Write-Host "LocalDev CS VSIX DLL is installed at: $localDevCsVsixDll"

# Verify the VSIX there is localdev (it should be by install path, but this proves it)
$vsixManifestPath = Get-ChildItem -Path (Split-Path $localDevCsVsixDll) -Filter 'extension.vsixmanifest' -File -Recurse | Select-Object -ExpandProperty FullName
    if (-not (Test-Path $vsixManifestPath -PathType Leaf))
    {
        throw 'VSIX manifest is not found. Please ensure the LocalDev VSIX is correctly installed.'
    }
    Write-Host "VSIX manifest is located at: $vsixManifestPath"

    if (-not (Select-String -Path $vsixManifestPath -Pattern 'LocalDev'))
    {
        throw 'LocalDev is not referenced in the VSIX manifest. Please ensure the LocalDev VSIX is correctly installed.'
    }
    Write-Host 'LocalDev is referenced in the VSIX manifest.'

# Ensure clean template space by removing any dotnet winui templates on the machine because they also appear in VS
$templatePackage = 'Microsoft.WindowsAppSDK.WinUI.CSharp.Templates'
$installedTemplates = dotnet new uninstall 2>$null

    if ($installedTemplates -match [regex]::Escape($templatePackage))
    {
        dotnet new uninstall $templatePackage
        if ($LASTEXITCODE -ne 0)
        {
            throw "Failed to uninstall dotnet template package '$templatePackage'."
        }
    }

    $templates = @(
        [pscustomobject]@{ Name = 'WinUI Class Library'; Id = 'Microsoft.WinUI.Desktop.Cs.ClassLibrary'; CanDeploy = $false; RunUnitTests = $false }
        [pscustomobject]@{ Name = 'WinUI MVVM App'; Id = 'Microsoft.WinUI.Desktop.Cs.MvvmApp'; CanDeploy = $true; RunUnitTests = $false }
        [pscustomobject]@{ Name = 'WinUI Navigation App'; Id = 'Microsoft.WinUI.Desktop.Cs.NavigationApp'; CanDeploy = $true; RunUnitTests = $false }
        [pscustomobject]@{ Name = 'WinUI Blank App (Packaged with Windows Application Packaging Project)'; Id = 'Microsoft.WinUI.Desktop.Cs.PackagedApp'; CanDeploy = $true; RunUnitTests = $false; ConfirmTargetVersions = $true }
        [pscustomobject]@{ Name = 'WinUI Blank App (Packaged)'; Id = 'Microsoft.WinUI.Desktop.Cs.SingleProjectPackagedApp'; CanDeploy = $true; RunUnitTests = $false }
        [pscustomobject]@{ Name = 'WinUI TabView App'; Id = 'Microsoft.WinUI.Desktop.Cs.TabViewApp'; CanDeploy = $true; RunUnitTests = $false }
        [pscustomobject]@{ Name = 'WinUI Unit Test App'; Id = 'Microsoft.WinUI.Desktop.Cs.UnitTestApp'; CanDeploy = $true; RunUnitTests = $true }
    )
    if ($TemplateId)
    {
        $unknownTemplateIds = @($TemplateId | Where-Object { $_ -notin $templates.Id })
        if ($unknownTemplateIds)
        {
            throw "Unknown template ID(s): $($unknownTemplateIds -join ', ')"
        }
        $templates = @($templates | Where-Object Id -in $TemplateId)
    }

    Write-Warning 'UI automation is about to begin. Stop all manual keyboard and mouse activity until the final test report is displayed.'
    Write-Host 'Tests run one at a time. Each failed template stops immediately, captures diagnostics, and the suite continues.'
    [System.Threading.Thread]::Sleep(3000)

    foreach ($template in $templates)
    {
        $testResults.Add((Invoke-TemplateTest -Template $template -Devenv $devenv))
    }
}
catch
{
    $exitCode = 1
    Write-Error $_.Exception.Message -ErrorAction Continue
    $testResults.Add([pscustomobject]@{
        Template = 'Suite prerequisites'
        TemplateId = 'N/A'
        Status = 'Failed'
        FailedCheckpoint = 'Suite setup'
        Load = 'Not run'
        Build = 'Not run'
        Deploy = 'Not run'
        Tests = 'Not run'
        Duration = [TimeSpan]::Zero
        ErrorMessage = $_.Exception.Message
        ErrorListText = ''
        OutputWindowText = ''
        DiagnosticCaptureErrors = ''
    })
}
finally
{
    $reportPath = Join-Path $PSScriptRoot "TestResults\Test-Vsix-Templates-$(Get-Date -Format 'yyyyMMdd-HHmmss').txt"
    Write-TestReport -Results $testResults.ToArray() -ReportPath $reportPath
    Write-Host "Report written to: $reportPath"

    if ($testResults | Where-Object Status -eq 'Failed')
    {
        $exitCode = 1
    }
}

exit $exitCode
