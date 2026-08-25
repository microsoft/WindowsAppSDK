# You must keep your mouse/keyboard still while script is running

# Check VS 2026 is installed on the machine
# VS 2026 appears as "18". The alternative would be "2022", but the templates are only
# updated for VS 2026 unless it is a hot bug
$vswhere = "C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe"

$installPath = & $vswhere -version "[18.0,19.0)" -latest -property installationPath
$devenv = Join-Path $installPath 'Common7\IDE\devenv.exe'

if (-not (Test-Path $devenv -PathType Leaf))
{
    Write-Host "Visual Studio 2026 is not installed. Please install it before running this script."
    exit
}
Write-Host "Visual Studio 2026 is installed at: $installPath"
Write-Host "Devenv path: $devenv"

# LocalDev is installed per-user at $env:LocalAppData\Microsoft\VisualStudio\<version>\Extensions\<random>
# TODO: Add C++ LocalDev VSIX DLL search
$localDevCsVsixDll = Get-ChildItem -Path "$env:localappdata" -Filter 'WindowsAppSDK.Cs.Extension.Dev17.dll' -File -Recurse | Select-Object -ExpandProperty FullName

if (-not (Test-Path $localDevCsVsixDll -PathType Leaf))
{
    Write-Host "LocalDev CS VSIX DLL is not installed. Please install it before running this script using dev/templates/VSIX/build-local-vsix-package/build-install-localdev-vsix.ps1."
    exit
}
Write-Host "LocalDev CS VSIX DLL is installed at: $localDevCsVsixDll"

# Verify the VSIX there is localdev (it should be by install path, but this proves it)
$vsixManifestPath = Get-ChildItem -Path (Split-Path $localDevCsVsixDll) -Filter 'extension.vsixmanifest' -File -Recurse | Select-Object -ExpandProperty FullName
if (-not (Test-Path $vsixManifestPath -PathType Leaf))
{
    Write-Host "VSIX manifest is not found. Please ensure the LocalDev VSIX is correctly installed."
    exit
}
Write-Host "VSIX manifest is located at: $vsixManifestPath"

if (-not (sls -Path $vsixManifestPath -Pattern 'LocalDev'))
{
    Write-Host "LocalDev is not referenced in the VSIX manifest. Please ensure the LocalDev VSIX is correctly installed."
    exit
}
Write-Host "LocalDev is referenced in the VSIX manifest."

# Ensure clean template space by removing any dotnet winui templates on the machine because they also appear in VS
$templatePackage = 'Microsoft.WindowsAppSDK.WinUI.CSharp.Templates'
$installedTemplates = dotnet new uninstall 2>$null

if ($installedTemplates -match [regex]::Escape($templatePackage))
{
    dotnet new uninstall $templatePackage
}

# Launch Visual Studio and get HWND for the first window of devenv
Write-Host "Launching Visual Studio..."
Start-Process -FilePath $devenv
Write-Host "Launching WinApp UI Inspect for devenv..."
winapp ui wait-for TitleBar -a devenv --timeout 10000
$output = winapp ui list-windows -a devenv
Write-Host "List of windows for devenv: $output"
$firstHWND = $output | Select-String 'HWND (\d+):' | Select-Object -First 1 | ForEach-Object { $_.Matches[0].Groups[1].Value }
Write-Host "First HWND for devenv: $firstHWND"

# Create a new project menu
Write-Host "Invoking 'Create a new project' menu in Visual Studio..."
winapp ui wait-for "Create a new project" -a devenv -w $firstHWND
$json = winapp ui inspect -a devenv -i "Create a new project" -w $firstHWND --json | ConvertFrom-Json
$button = $json.windows[0].elements | Select-Object -ExpandProperty selector
winapp ui invoke $button -w $firstHWND
Write-Host "firstHWND: $firstHWND"
winapp ui wait-for "ListViewTemplates" -a devenv

# Create a new project in Visual Studio using the invoked menu
Write-Host "Creating the C# template"
winapp ui wait-for "WinUI Blank App (Packaged)" -a devenv -w $firstHWND --timeout 5000
$templateName = "WinUI Blank App (Packaged)"
$templateItem = winapp ui inspect -a devenv -i $templateName -w $firstHWND
Write-Host "Template item for '$templateName': $templateItem"
$templateSelector = Select-String -Pattern '^\s*(\S+)' -InputObject $templateItem | ForEach-Object { $_.Matches[0].Groups[1].Value }
winapp ui invoke $templateSelector -w $firstHWND


# winapp ui invoke $templateSelector -w $firstHWND
#$singleProjectTemplateButton = winapp ui inspect -a devenv -i "(Packaged)" -w $firstHWND --json
#$singleProjectTemplateSelector = $singleProjectTemplateButton.windows[0].elements | Select-Object -ExpandProperty selector
#winapp ui invoke $singleProjectTemplateSelector -w $firstHWND

#$nextButton = winapp ui inspect -a devenv -i "Next" -w $firstHWND --json | ConvertFrom-Json
#$nextButtonSelector = $nextButton.windows[0].elements | Select-Object -ExpandProperty selector
#winapp ui invoke $nextButtonSelector -w $firstHWND

# Create the new project
# $createButton = winapp ui inspect -a devenv -i "Create" -w $firstHWND --json | ConvertFrom-Json
# $createButtonSelector = $createButton.windows[0].elements | Select-Object -ExpandProperty selector
# winapp ui invoke $createButtonSelector -w $firstHWND
