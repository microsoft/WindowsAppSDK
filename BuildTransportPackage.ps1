<#
This script is to build the framework transport package that will be used to generate the windows app sdk framework package.
This script is called from BuildAll.ps1 from the aggregator repo and should not be called directly.

Platform: Comma delimited string of platforms to run.
Configuration: Comma delimited string of configurations to run.
LocalPackagesPath: The path that the generated transport package needs to be saved.
UpdateVersionDetailsPath: Path to a ps1 or cmd that updates version.details.xml.

Note about building in different environments.
The feed the nuget.config points to changes depending on the branch.
Develop branch points to the internal feed.
Main branch points to the external feed.

#>

Param(
    [string]$Platform,
    [string]$Configuration,
    [string]$LocalPackagesPath = $null,
    [string]$UpdateVersionDetailsPath = $null
)

$MRTSourcesDirectory = "dev\MRTCore"
$MRTBinariesDirectory = "BuildOutput"
$nuSpecsPath = "build\NuSpecs"
$fullNugetPath = "build\fullnuget"
$buildOverridePath = "build\override"
$windowsAppSdkBinariesPath = "build\windowsappsdk_binaries"

$builddate_yymm = Get-Date -Format "yyMM"
$builddate_dd = Get-Date -Format "dd"
$revision = Get-Date -Format "HHMM"

$VCToolsInstallDir = . "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -Latest -requires Microsoft.Component.MSBuild -property InstallationPath
write-host "VCToolsInstallDir: $VCToolsInstallDir"

$msBuildPath = "$VCToolsInstallDir\MSBuild\Current\Bin\msbuild.exe"

# do all the directory making before any building.
if(-not (test-path ".nuget"))
{
    new-item -path ".nuget" -itemtype directory
}

if(-not (test-path ".nuget\nuget.exe"))
{
    Invoke-WebRequest https://dist.nuget.org/win-x86-commandline/latest/nuget.exe -OutFile .nuget\nuget.exe
}

if(-not (test-path "$buildOverridePath"))
{
    new-item -path "$buildOverridePath" -itemtype "directory"
}

if(-not (test-path "$windowsAppSdkBinariesPath"))
{
    new-item -path "$windowsAppSdkBinariesPath" -itemtype "directory"    
}

if(-not (test-path "$fullNugetPath"))
{    
    new-item -path "$fullNugetPath" -itemtype "directory"
}

if(-not (test-path "$fullNugetPath\build\native"))
{
    new-item -path "$fullNugetPath\build\native" -itemtype "directory"
}

if(-not (test-path "$fullNugetPath\lib\net5.0-windows10.0.17763.0"))
{
    new-item -path "$fullNugetPath\lib\net5.0-windows10.0.17763.0" -itemtype "directory"
}


# Restore any nuget packages.
& .\build\Scripts\ConvertVersionDetailsToPackageConfig.ps1 -versionDetailsPath "eng\Version.Details.xml" -packageConfigPath "build\packages.config"

& .\.nuget\nuget.exe restore "build\packages.config" -PackagesDirectory packages -ConfigFile "build\licensing.nuget.config"
& .\.nuget\nuget.exe restore WindowsAppRuntime.sln -configfile nuget.config
& .\.nuget\nuget.exe restore "dev\Bootstrap\CS\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.csproj" -configfile nuget.config
& .\.nuget\nuget.exe restore "dev\WindowsAppRuntime_Insights\packages.config" -ConfigFile "dev\WindowsAppRuntime_Insights\nuget.config" -PackagesDirectory "dev\WindowsAppRuntime_Insights\packages"
& .\.nuget\nuget.exe restore "$MRTSourcesDirectory\mrt\core\src\packages.config" -ConfigFile nuget.config -PackagesDirectory "$MRTSourcesDirectory\mrt\packages"
& .\.nuget\nuget.exe restore "$MRTSourcesDirectory\mrt\Microsoft.Windows.ApplicationModel.Resources\src\packages.config" -ConfigFile nuget.config -PackagesDirectory "$MRTSourcesDirectory\mrt\packages"
& .\.nuget\nuget.exe restore "$MRTSourcesDirectory\mrt\mrm\mrmex\packages.config" -ConfigFile nuget.config -PackagesDirectory "$MRTSourcesDirectory\mrt\packages"
& .\.nuget\nuget.exe restore "$MRTSourcesDirectory\mrt\mrm\mrmmin\packages.config" -ConfigFile nuget.config -PackagesDirectory "$MRTSourcesDirectory\mrt\packages"
& .\.nuget\nuget.exe restore "$MRTSourcesDirectory\mrt\mrm\unittests\packages.config" -ConfigFile nuget.config -PackagesDirectory "$MRTSourcesDirectory\mrt\packages"

# init MRT
 foreach($platformToRun in $platform.Split(","))
 {
   write-host "Intilizing MRT for $platformToRun"
   & $MRTSourcesDirectory\build\init.cmd /envonly $platformToRun\fre
 }

 # Build windows app runtime and mrt
 foreach($configurationToRun in $configuration.Split(","))
 {
    foreach($platformToRun in $platform.Split(","))
    {
        write-host "Building windowsappruntime.sln for Configuration:$configurationToRun and Platform:$platformToRun"
        & $msBuildPath /restore /p:Configuration=$configurationToRun,Platform=$platformToRun WindowsAppRuntime.sln
        
        write-host "Building $MRTSourcesDirectory\mrt\MrtCore.sln for Configuration:$configurationToRun and Platform:$platformToRun"
        & $msBuildPath /restore /p:Configuration=$configurationToRun,Platform=$platformToRun "$MRTSourcesDirectory\mrt\MrtCore.sln"
    }
 }

$mrtConfiguration = "Release"
 foreach($configurationToRun in $configuration.Split(","))
 {
     if($configurationToRun -eq "debug")
     {
         $mrtConfiguration = "debug"
     }
 }

# Copy over platform files
foreach($platformToRun in $platform.Split(","))
{
    write-host "Copying platform files for Platform:$platformToRun and for configuration:$mrtConfiguration"
    write-host "Copying $MRTBinariesDirectory\$mrtConfiguration\$platformToRun\mrm\mrm.dll to $fullNugetPath\runtimes\win10-$platformToRun\native"
    copy-item -path "$MRTBinariesDirectory\$mrtConfiguration\$platformToRun\mrm\mrm.dll" -destination "$fullNugetPath\runtimes\win10-$platformToRun\native"
    
    write-host "Copying $MRTBinariesDirectory\$mrtConfiguration\$platformToRun\mrm\mrm.lib to $fullNugetPath\runtimes\win10-$platformToRun\native"
    copy-item -path "$MRTBinariesDirectory\$mrtConfiguration\$platformToRun\mrm\mrm.lib" -destination "$fullNugetPath\runtimes\win10-$platformToRun\native"
    
    write-host "Copying $MRTBinariesDirectory\$mrtConfiguration\$platformToRun\mrm\mrm.pdb to $fullNugetPath\runtimes\win10-$platformToRun\native"
    copy-item -path "$MRTBinariesDirectory\$mrtConfiguration\$platformToRun\mrm\mrm.pdb" -destination "$fullNugetPath\runtimes\win10-$platformToRun\native"
    
    write-host "Copying $MRTBinariesDirectory\$mrtConfiguration\$platformToRun\Microsoft.Windows.ApplicationModel.Resources\Microsoft.Windows.ApplicationModel.Resources.dll to $fullNugetPath\runtimes\win10-$platformToRun\native"
    copy-item -path "$MRTBinariesDirectory\$mrtConfiguration\$platformToRun\Microsoft.Windows.ApplicationModel.Resources\Microsoft.Windows.ApplicationModel.Resources.dll" -destination "$fullNugetPath\runtimes\win10-$platformToRun\native"
    
    write-host "Copying $MRTBinariesDirectory\$mrtConfiguration\$platformToRun\Microsoft.Windows.ApplicationModel.Resources\Microsoft.Windows.ApplicationModel.Resources.pdb to $fullNugetPath\runtimes\win10-$platformToRun\nativen"
    copy-item -path "$MRTBinariesDirectory\$mrtConfiguration\$platformToRun\Microsoft.Windows.ApplicationModel.Resources\Microsoft.Windows.ApplicationModel.Resources.pdb" -destination "$fullNugetPath\runtimes\win10-$platformToRun\native"

    if($ploatformToRun -eq "x86")
    {
        write-host "Copying $MRTBinariesDirectory\$mrtConfiguration\$platformToRun\Microsoft.Windows.ApplicationModel.Resources.Projection\Microsoft.Windows.ApplicationModel.Resources.Projection.dll to $fullNugetPath\lib\net5.0-windows10.0.17763.0"
        copy-item -path    "$MRTBinariesDirectory\$mrtConfiguration\$platformToRun\Microsoft.Windows.ApplicationModel.Resources.Projection\Microsoft.Windows.ApplicationModel.Resources.Projection.dll" -destination "$fullNugetPath\lib\net5.0-windows10.0.17763.0"
        
        write-host "Copying $MRTBinariesDirectory\$mrtConfiguration\$platformToRun\Microsoft.Windows.ApplicationModel.Resources.Projection\Microsoft.Windows.ApplicationModel.Resources.Projection.pdb to $fullNugetPath\lib\net5.0-windows10.0.17763.0"
        copy-item -path "$MRTBinariesDirectory\$mrtConfiguration\$platformToRun\Microsoft.Windows.ApplicationModel.Resources.Projection\Microsoft.Windows.ApplicationModel.Resources.Projection.pdb" -destination "$fullNugetPath\lib\net5.0-windows10.0.17763.0"
        
        write-host "Copying $MRTBinariesDirectory\$mrtConfiguration\$platformToRun\Microsoft.Windows.ApplicationModel.Resources\Microsoft.Windows.ApplicationModel.Resources.winmd to $fullNugetPath\lib\net5.0-windows10.0.17763.0"
        copy-item -path "$MRTBinariesDirectory\$mrtConfiguration\$platformToRun\Microsoft.Windows.ApplicationModel.Resources\Microsoft.Windows.ApplicationModel.Resources.winmd" -destination "$fullNugetPath\lib\net5.0-windows10.0.17763.0"
    }
}

# build AnyCPU
write-host "Building anyCPU"
& $msBuildPath /restore /p:Configuration=release,Platform=anycpu "dev\Bootstrap\CS\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.csproj"

# If AnyCPU generates another dll it needs to be added here.
copy-item -path "buildoutput\release\anycpu\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.dll"  -destination "$fullNugetPath\lib\net5.0-windows10.0.17763.0" -recurse

# Generate overrides
.\tools\GenerateDynamicDependencyOverrides.ps1 -Path "$buildOverridePath"
.\tools\GeneratePushNotificationsOverrides.ps1 -Path "$buildOverridePath"

# Copy more files.
foreach($configurationToRun in $configuration.Split(","))
{
    foreach($platformToRun in $platform.Split(","))
    {
        write-host "Moving items to staging directory for Configuration:$configurationToRun and Platform:$platformToRun"
        .\build\CopyFilesToStagingDir.ps1 -BuildOutputDir 'BuildOutput' -OverrideDir "$buildOverridePath" -PublishDir "$windowsAppSdkBinariesPath" -NugetDir "$fullNugetPath" -Platform $PlatformToRun -Configuration $ConfigurationToRun
    }
}

Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.targets" -Destination "$fullNugetPath\build\native"
Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.props" -Destination "$fullNugetPath\build\native"
Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.C.props" -Destination "$fullNugetPath\build\native"
Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.WinRt.props" -Destination "$fullNugetPath\build\native"
Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Foundation.targets" -Destination "$fullNugetPath\build"
Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Foundation.props" -Destination "$fullNugetPath\build"
Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Bootstrap.CS.targets" -Destination "$fullNugetPath\build"
Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.Bootstrap.targets" -Destination "$fullNugetPath\build\native"
Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.BootstrapCommon.targets" -Destination "$fullNugetPath\build"
Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.DeploymentManager.CS.targets" -Destination "$fullNugetPath\build"
Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.DeploymentManager.targets" -Destination "$fullNugetPath\build\native"
Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.DeploymentManagerCommon.targets" -Destination "$fullNugetPath\build"
Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.UndockedRegFreeWinRT.CS.targets" -Destination "$fullNugetPath\build"
Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.UndockedRegFreeWinRT.targets" -Destination "$fullNugetPath\build"
Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.UndockedRegFreeWinRTCommon.targets" -Destination "$fullNugetPath\build"
Copy-Item -Path "$nuSpecsPath\AppxManifest.xml" -Destination "$fullNugetPath"
Copy-Item -Path "LICENSE" -Destination "$fullNugetPath" -recurse

# for some reason xslt.load changes the working directory to C:\windows\system32.
# store the current working directory here.
$workingDirectory = get-location
$manifestPath = "$fullNugetPath\manifests"

# Make Microsoft.WindowsAppSDK.Foundation.manifest.
$newitem = New-Item -ItemType Directory -Force -Path $manifestPath
$xslt = New-Object System.Xml.Xsl.XslCompiledTransform
$xslt.Load("$workingDirectory\build\TransformAppxManifest.xslt")
$xslt.Transform("$workingDirectory\$fullNugetPath\AppxManifest.xml", "$workingDirectory\$manifestPath\Microsoft.WindowsAppSdk.Foundation.manifest")

# any version will do here.
$packageVersion = '1.1.1.1'

# Add the version to the nuspec.
[xml]$publicNuspec = Get-Content -Path ".\build\NuSpecs\Microsoft.WindowsAppSDK.Foundation.nuspec"
$publicNuspec.package.metadata.version = $packageVersion
Set-Content -Value $publicNuspec.OuterXml ".\build\NuSpecs\Microsoft.WindowsAppSDK.Foundation.nuspec"

# Make the foundation transport package.
nuget pack ".\build\NuSpecs\Microsoft.WindowsAppSDK.Foundation.nuspec" -BasePath $fullNugetPath -OutputDirectory $LocalPackagesPath

# Update the details in eng/version.details.xml
$packageName = "Microsoft.WindowsAppSDK.Foundation.TransportPackage"
&"$UpdateVersionDetailsPath" -dependencyName $packageName -dependencyVersion $packageVersion

# Remove the directory.  If the directory is not removed then nuget restore won't restore the transport package because the versions are the same.
write-host "Removing $env:Build_SourcesDirectory\build\packages\Microsoft.WindowsAppSDK.Foundation.TransportPackage.$packageVersion"
remove-item "$env:Build_SourcesDirectory\build\packages\Microsoft.WindowsAppSDK.Foundation.TransportPackage.$packageVersion" -recurse -force
