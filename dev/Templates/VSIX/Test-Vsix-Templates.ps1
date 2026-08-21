# Check VS 2026 is installed on the machine
# VS 2026 appears as "18". The alternative would be "2022", but the templates are only
# updated for VS 2026 unless it is a hot bug
$vs2026Path = "C:\Program Files\Microsoft Visual Studio\18"
if (-not (Test-Path $vs2026Path -PathType Container))
{
    Write-Host "Visual Studio 2026 is not installed. Please install it before running this script."
    exit
}
cd $vs2026Path

# LocalDev is installed per-user at $env:LocalAppData\Microsoft\VisualStudio\<version>\Extensions\<random>.ap0
$LocalDevVsixPath = $env:localappdata + "\Microsoft\VisualStudio"
if (-not (Test-Path $LocalDevVsixPath -PathType Container))
{
    Write-Host "LocalDev VSIX folder not found. Please ensure that the templates are installed."
    exit
}
cd $LocalDevVsixPath
Write-Host "LocalDev VSIX folder found at: $LocalDevVsixPath"

# Get the version number
# Options: 17, 18, and the specific version number of the user's install of Visual Studio (e.g. 17.0_acd2bae8)
# The extensions are in that full version
# We're using VS 2026, so we need to find the 18.x version
if (-not (Test-Path "$LocalDevVsixPath\18.*" -PathType Container))
{
    Write-Host "No Visual Studio 2026 LocalDev VSIX folder found. Please ensure that the templates are installed."
    exit
}

$vs2026LocalDataVersions = Get-ChildItem -Path $LocalDevVsixPath -Directory | Where-Object { $_.Name -like "18.*" } | Select-Object -First 2
$maximumVersion = [version]$vs2026LocalDataVersions[0].Name
$latestVs2026LocalDataVersion = $vs2026LocalDataVersions[0]

cd $latestVs2026LocalDataVersion
Write-Host "Latest Visual Studio 2026 LocalDev VSIX folder found at: $($latestVs2026LocalDataVersion.FullName)"

Get-ChildItem -Path . -Filter 'WindowsAppSDK*Dev17.LocalDev.dll' -File -Recurse -Force

# In the menu that begins, 

# View VS
# winapp ui inspect -a devenv