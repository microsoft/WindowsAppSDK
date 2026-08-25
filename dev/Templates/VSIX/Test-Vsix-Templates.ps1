# You must keep your mouse/keyboard still while script is running

$ErrorActionPreference = 'Stop'

$uiTimeout = 10000
$templateTimeout = 15000
$projectLoadTimeout = 60000
$deploymentTimeout = 120000
$exitCode = 0
$visualStudioProcess = $null
$appProcessIds = @()
$existingAppProcessIds = @()
$activeHWND = $null
$appName = $null

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
                $element = $searchResult.matches | Where-Object {
                    $_.type -eq 'ListItem' -and
                    $_.isEnabled -and
                    -not $_.isOffscreen -and
                    $_.isInvokable -and
                    $_.name -and
                    ($_.name -eq $Name -or $_.name.StartsWith("$Name,", [StringComparison]::Ordinal))
                } | Select-Object -First 1
                if ($element.selector)
                {
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

function Get-DevenvHWND
{
    $output = Invoke-WinAppRequired -Checkpoint 'List Visual Studio windows' -Arguments @('ui', 'list-windows', '-a', 'devenv') -PassThru
    Write-Host "List of windows for devenv: $output"
    $hwnd = $output | Select-String 'HWND (\d+):' | Select-Object -First 1 | ForEach-Object { $_.Matches[0].Groups[1].Value }
    if (-not $hwnd)
    {
        throw 'WinApp UI did not return an HWND for Visual Studio.'
    }

    return $hwnd
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

# Launch Visual Studio and get HWND for the first window of devenv
    Write-Host 'Launching Visual Studio...'
    $visualStudioProcess = Start-Process -FilePath $devenv -PassThru
    Write-Host 'Launching WinApp UI Inspect for devenv...'
    Wait-WinAppElement -Identifier 'TitleBar' -App 'devenv' -Timeout $uiTimeout
    $activeHWND = Get-DevenvHWND
    Write-Host "First HWND for devenv: $activeHWND"

# Create a new project menu
    Write-Host "Invoking 'Create a new project' menu in Visual Studio..."
    Wait-WinAppElement -Identifier 'Create a new project' -App 'devenv' -Window $activeHWND
    $rawJson = Invoke-WinAppRequired -Checkpoint "Inspect 'Create a new project'" -Arguments @('ui', 'inspect', '-a', 'devenv', '-i', 'Create a new project', '-w', $activeHWND, '--json') -PassThru
    $json = ($rawJson -join [Environment]::NewLine) | ConvertFrom-Json
    $button = $json.windows[0].elements[0].selector
    Invoke-WinAppRequired -Checkpoint "Invoke 'Create a new project'" -Arguments @('ui', 'invoke', $button, '-w', $activeHWND)
    Wait-WinAppElement -Identifier 'ListViewTemplates' -App 'devenv' -Timeout $uiTimeout

# Create a new project in Visual Studio using the invoked menu
    Write-Host 'Creating the C# template'
    $templateName = 'WinUI Blank App (Packaged)'
    $templateSelector = Wait-WinAppElementByNamePrefix -Name $templateName -Window $activeHWND -Timeout $templateTimeout
    Write-Host "Template selector for '$templateName': $templateSelector"
    Invoke-WinAppRequired -Checkpoint "Select '$templateName'" -Arguments @('ui', 'invoke', $templateSelector, '-w', $activeHWND)
    Wait-WinAppElement -Identifier 'Next' -App 'devenv' -Window $activeHWND -Timeout $uiTimeout

# Click the Next button to continue with the defaults selected
# Not sure if a wait is needed here because the window has already loaded
    $rawJson = Invoke-WinAppRequired -Checkpoint "Inspect 'Next'" -Arguments @('ui', 'inspect', '-a', 'devenv', '-i', 'Next', '-w', $activeHWND, '--json') -PassThru
    $nextButton = ($rawJson -join [Environment]::NewLine) | ConvertFrom-Json
    $nextButtonSelector = $nextButton.windows[0].elements[0].selector
    Invoke-WinAppRequired -Checkpoint "Invoke template selection 'Next'" -Arguments @('ui', 'invoke', $nextButtonSelector, '-w', $activeHWND)

# Create the new project
# button_Next appears to be an unchanging property
    Wait-WinAppElement -Identifier 'Next' -App 'devenv' -Window $activeHWND -Timeout $uiTimeout
    Invoke-WinAppRequired -Checkpoint 'Create the project' -Arguments @('ui', 'invoke', 'button_Next', '-w', $activeHWND)

# Let the project load
    Wait-WinAppElement -Identifier 'SolutionExplorer' -App 'devenv' -Timeout $projectLoadTimeout
    Write-Host 'Solution Explorer loaded'

# Get the new HWND
    $activeHWND = Get-DevenvHWND
    Write-Host "First HWND for devenv after project creation: $activeHWND"

# This ends the setup section

# Smoke test 1: F5 deployment
    Write-Host 'Starting F5 deployment...'
    Wait-WinAppElement -Identifier 'Debug Target' -App 'devenv' -Window $activeHWND -Timeout $uiTimeout
    $rawJson = Invoke-WinAppRequired -Checkpoint "Inspect 'Debug Target'" -Arguments @('ui', 'inspect', 'Debug Target', '-a', 'devenv', '-w', $activeHWND, '--json') -PassThru
    $debugButtonJson = ($rawJson -join [Environment]::NewLine) | ConvertFrom-Json
    $debugButtonSelector = $debugButtonJson.windows[0].elements[0].selector
    $windowTitle = $debugButtonJson.windows[0].title

# Now, assert the template app appears and there are no errors in the output or error list
# Grab the app title from Visual Studio and then find the app?
    if ($windowTitle -notmatch '(App\d+)')
    {
        throw "Failed to extract app name from window title: $windowTitle"
    }

    $appName = $matches[1]
    $existingAppProcessIds = @(Get-Process -Name $appName -ErrorAction SilentlyContinue | Select-Object -ExpandProperty Id)
    Write-Host "App name: $appName"
    Write-Host "Debug button selector: $debugButtonSelector"
    Invoke-WinAppRequired -Checkpoint 'Start F5 deployment' -Arguments @('ui', 'invoke', $debugButtonSelector, '-w', $activeHWND)
    Wait-WinAppElement -Identifier 'TitleBar' -App $appName -Timeout $deploymentTimeout

    $appProcessIds = @(Get-Process -Name $appName -ErrorAction SilentlyContinue | Where-Object { $_.Id -notin $existingAppProcessIds } | Select-Object -ExpandProperty Id)
    Write-Host "PASS: '$templateName' was created and '$appName' launched successfully."
}
catch
{
    $exitCode = 1
    Write-Error $_.Exception.Message -ErrorAction Continue
    if ($activeHWND)
    {
        Write-Host "Last known Visual Studio HWND: $activeHWND"
    }
    if ($appName)
    {
        Write-Host "App name: $appName"
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
    }
}

exit $exitCode
