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

$vs2026LocalDataVersions = Get-ChildItem -Path $LocalDevVsixPath -Directory | Where-Object { $_.Name -like "18.*" } | Select-Object -First 2
$maximumVersion = [version]$vs2026LocalDataVersions[0].Name
$latestVs2026LocalDataVersion = $vs2026LocalDataVersions[0]

cd $latestVs2026LocalDataVersion
Write-Host "Latest Visual Studio 2026 LocalDev VSIX folder found at: $($latestVs2026LocalDataVersion.FullName)"

Get-ChildItem -Path . -Filter 'WindowsAppSDK*Dev17.LocalDev.dll' -File -Recurse -Force

# In the menu that begins, 

# View VS
# winapp ui inspect -a devenv