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

if(-not (test-path "$fullNugetPath\mrt_raw"))
{
	new-item -path "$fullNugetPath\mrt_raw" -itemtype "directory"
}

if(-not (test-path "$fullNugetPath\mrt_raw\lib"))
{
	new-item -path "$fullNugetPath\mrt_raw\lib" -itemtype "directory"
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
   & $MRTSourcesDirectory\build\init.cmd /envonly $platformToRun\fre
 }

 # Build windows app runtime and mrt
 foreach($configurationToRun in $configuration.Split(","))
 {
    foreach($platformToRun in $platform.Split(","))
    {
        msbuild /restore /m WindowsAppRuntime.sln /p:Configuration=$configurationToRun,Platform=$platformToRun
        msbuild /restore /m "$MRTSourcesDirectory\mrt\MrtCore.sln" /p:Configuration=$configurationToRun,Platform=$platformToRun
    }
 }

# Copy over platform files
foreach($platformToRun in $platform.Split(","))
{
    copy-item -path "$MRTBinariesDirectory\Release\$platformToRun\mrm\mrm.dll" -destination "$fullNugetPath\mrt_raw\lib\$platformToRun" -force
	copy-item -path "$MRTBinariesDirectory\Release\$platformToRun\mrm\mrm.lib" -destination "$fullNugetPath\mrt_raw\lib\$platformToRun" -force
	copy-item -path "$MRTBinariesDirectory\Release\$platformToRun\mrm\mrm.pdb" -destination "$fullNugetPath\mrt_raw\lib\$platformToRun" -force
	copy-item -path "$MRTBinariesDirectory\Release\$platformToRun\Microsoft.Windows.ApplicationModel.Resources\Microsoft.Windows.ApplicationModel.Resources.dll" -destination "$fullNugetPath\mrt_raw\lib\$platformToRun" -force
	copy-item -path "$MRTBinariesDirectory\Release\$platformToRun\Microsoft.Windows.ApplicationModel.Resources\Microsoft.Windows.ApplicationModel.Resources.pdb" -destination "$fullNugetPath\mrt_raw\lib\$platformToRun" -force

	if($ploatformToRun -eq "x86")
	{
		copy-item -path "$MRTBinariesDirectory\Release\$platformToRun\Microsoft.Windows.ApplicationModel.Resources.Projection\Microsoft.Windows.ApplicationModel.Resources.Projection.dll" -destination "$fullNugetPath\mrt_raw\lib\anycpu\net5.0" -force
		copy-item -path "$MRTBinariesDirectory\Release\$platformToRun\Microsoft.Windows.ApplicationModel.Resources.Projection\Microsoft.Windows.ApplicationModel.Resources.Projection.pdb" -destination "$fullNugetPath\mrt_raw\lib\anycpu\net5.0" -force
		copy-item -path "$MRTBinariesDirectory\Release\$platformToRun\Microsoft.Windows.ApplicationModel.Resources\Microsoft.Windows.ApplicationModel.Resources.winmd" -destination "$fullNugetPath\mrt_raw\lib\anycpu" -force
	}
}

# build AnyCPU
msbuild /restore /m "dev\Bootstrap\CS\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.csproj" /p:Configuration=release,Platform=anycpu

# If AnyCPU generates another dll it needs to be added here.
copy-item -path "buildoutput\release\anycpu\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.dll"  -destination "$fullNugetPath\lib\net5.0-windows10.0.17763.0"

# Generate overrides
.\tools\GenerateDynamicDependencyOverrides.ps1 -Path "$buildOverridePath"
.\tools\GeneratePushNotificationsOverrides.ps1 -Path "$buildOverridePath"

# Copy more files.
foreach($configurationToRun in $configuration.Split(","))
{
	foreach($platformToRun in $platform.Split(","))
	{
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
Copy-Item -Path "LICENSE" -Destination "$fullNugetPath" -force

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