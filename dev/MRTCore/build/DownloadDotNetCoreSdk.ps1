$dotnetInstallScript = "$PSScriptRoot\dotnet-install.ps1"
$dotnetInstallDir  = [System.IO.Path]::GetFullPath("$PSScriptRoot\..\.dotnet")
$x86dotnetInstallDir  = "$dotnetInstallDir\x86"

$versionPropsFilePropertyGroup = ([xml](Get-Content -Raw "$PSScriptRoot\versions.props")).Project.PropertyGroup[0]
$dotNetSdkVersion = $versionPropsFilePropertyGroup.DotNetCoreSdkVersion
$dotNetSdkVersionLkg = $versionPropsFilePropertyGroup.DotNetCoreSdkLkgVersion
$dotNetSdkVersionString = "rtm"

if (-not $dotNetSdkVersionString)
{
    Write-Error "The .NET SDK version $dotNetSdkVersion does not have an installer associated with it.  Please update the version number to one matching a release at https://github.com/dotnet/installer."
    exit 1
}

[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.SecurityProtocolType]'Ssl3,Tls,Tls11,Tls12'

Write-Host "Installing .NET SDK..."

. $dotnetInstallScript -Channel Master -Version $dotNetSdkVersion -InstallDir $dotnetInstallDir -Architecture x64
Write-Host "Installed SDK (x64) version $dotNetSdkVersion to $dotnetInstallDir."

. $dotnetInstallScript -Channel Master -Version $dotNetSdkVersion -InstallDir $x86dotnetInstallDir -Architecture x86
Write-Host "Installed SDK (x86) version $dotNetSdkVersion to $x86dotnetInstallDir."

Write-Host -ForegroundColor Green Done.
