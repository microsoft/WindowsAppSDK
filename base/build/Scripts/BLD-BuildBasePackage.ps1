param (
  [string]$Channel = "dev"
)

if (Checkpoint("Update WindowsAppSDK base nuspec [Version]")) {
    $WindowsAppSDKNugetPackageVersion = $global:Build_Info.WindowsAppSDKPackageVersion
    Write-Host "Update version to $WindowsAppSDKNugetPackageVersion..."
    [xml]$publicNuspec = Get-Content -Encoding utf8 -Path (Join-Path $BuildOutput 'NuSpecs\base\Microsoft.WindowsAppSDK.Base.nuspec')
    $publicNuspec.package.metadata.version = $WindowsAppSDKNugetPackageVersion
    
    [xml]$versionsXml = Get-Content (Join-Path $env:Build_SourcesDirectory 'eng\Versions.props')
    $buildToolsMSIXPackageVersion = $versionsXml.DocumentElement.PropertyGroup.MicrosoftWindowsSDKBuildToolsMSIXPackageVersion
    if (!$buildToolsMSIXPackageVersion)
    {
        throw "Failed to get Microsoft.Windows.SDK.BuildTools.MSIX Version from Versions.props"
    }
    
    # Update BuildTools.MSIX version number
    $dependencies = $publicNuspec.package.metadata.dependencies
    $dependency = $dependencies.dependency | Where-Object { $_.id -eq "Microsoft.Windows.SDK.BuildTools.MSIX" }
    $dependency.version = $buildToolsMSIXPackageVersion
    Write-host $publicNuspec.OuterXml
    Set-Content -Encoding utf8 -Value $publicNuspec.OuterXml (Join-Path $BuildOutput 'NuSpecs\base\Microsoft.WindowsAppSDK.Base.nuspec')
}

if (Checkpoint("Add license to WindowsAppSDK NugetPackage")) {
    $LicenseSourceFolder = (Join-Path $env:Build_SourcesDirectory 'build\NuSpecs\license\preview\')
    if ($Channel -eq 'stable')
    {
        $LicenseSourceFolder = (Join-Path $env:Build_SourcesDirectory 'build\NuSpecs\license\release\')
    }
        
    build\scripts\CopyContents.ps1 `
        -SourceDir $LicenseSourceFolder `
        -ContentsList @('license.txt') `
        -TargetDir $BaseNugetContentFolder
        
    build\scripts\CopyContents.ps1 `
        -SourceDir (Join-Path $env:Build_SourcesDirectory 'build\NuSpecs\') `
        -ContentsList @('NOTICE.txt', 'Icon.png') `
        -TargetDir $BaseNugetContentFolder
}

if (Checkpoint("Copy nuget build files to WindowsAppSDK Base NugetPackage")) 
{
    build\scripts\CopyContents.ps1 `
        -SourceDir (Join-Path $BuildOutput 'NuSpecs\base') `
        -ContentsList @('build') `
        -TargetDir $BaseNugetContentFolder

    build\scripts\CopyContents.ps1 `
        -SourceDir (Join-Path $BuildOutput 'NuSpecs\build') `
        -ContentsList @(
            'Microsoft.WindowsAppSDK.arm64ec.targets',
            'Microsoft.WindowsAppSDK.SelfContained.targets',
            'Microsoft.WindowsAppSDK.SingleFile.targets',
            'Microsoft.WindowsAppSDK.SingleProject.targets') `
        -TargetDir (Join-Path $BaseNugetContentFolder 'build')
}

if (Checkpoint("Copy build to buildTransitive")) 
{
    build\Scripts\RobocopyWrapper.ps1 `
        -Source (Join-Path $BaseNugetContentFolder 'build') `
        -dest (Join-Path $BaseNugetContentFolder 'buildTransitive')
}

if (Checkpoint("Pack Windows App SDK WindowsAppSDK NugetPackage")) 
{
    nuget pack (Join-Path $BuildOutput 'NuSpecs\base\Microsoft.WindowsAppSDK.Base.nuspec') -BasePath $BaseNugetContentFolder -OutputDirectory $PackageStore
}