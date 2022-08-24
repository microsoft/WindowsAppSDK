Param(
    [string]$Platform,
    [string]$Configuration,
    [string]$LocalPackagesPath = $null,
    [string]$UpdateVersionDetailsPath = $null
)

# do all the directory making before any building.
if(-not (test-path ".nuget"))
{
	 new-item -path ".nuget" -itemtype directory
}

if(-not (test-path ".nuget\nuget.exe"))
{
	Invoke-WebRequest https://dist.nuget.org/win-x86-commandline/latest/nuget.exe -OutFile .nuget\nuget.exe
}

$MRTSourcesDirectory = "dev\MRTCore"
$MRTBinariesDirectory = "BuildOutput"
# & .\build\Scripts\ConvertVersionDetailsToPackageConfig.ps1 -versionDetailsPath "eng\Version.Details.xml" -packageConfigPath "build\packages.config"

# & .\.nuget\nuget.exe restore "build\packages.config" -PackagesDirectory packages -ConfigFile "build\licensing.nuget.config"
# & .\.nuget\nuget.exe restore WindowsAppRuntime.sln -configfile nuget.config
# & .\.nuget\nuget.exe restore "dev\Bootstrap\CS\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.csproj" -configfile nuget.config
# & .\.nuget\nuget.exe restore "dev\WindowsAppRuntime_Insights\packages.config" -ConfigFile "dev\WindowsAppRuntime_Insights\nuget.config" -PackagesDirectory "dev\WindowsAppRuntime_Insights\packages"
# & .\.nuget\nuget.exe restore "$MRTSourcesDirectory\mrt\core\src\packages.config" -ConfigFile nuget.config -PackagesDirectory "$MRTSourcesDirectory\mrt\packages"
# & .\.nuget\nuget.exe restore "$MRTSourcesDirectory\mrt\Microsoft.Windows.ApplicationModel.Resources\src\packages.config" -ConfigFile nuget.config -PackagesDirectory "$MRTSourcesDirectory\mrt\packages"
# & .\.nuget\nuget.exe restore "$MRTSourcesDirectory\mrt\mrm\mrmex\packages.config" -ConfigFile nuget.config -PackagesDirectory "$MRTSourcesDirectory\mrt\packages"
# & .\.nuget\nuget.exe restore "$MRTSourcesDirectory\mrt\mrm\mrmmin\packages.config" -ConfigFile nuget.config -PackagesDirectory "$MRTSourcesDirectory\mrt\packages"
# & .\.nuget\nuget.exe restore "$MRTSourcesDirectory\mrt\mrm\unittests\packages.config" -ConfigFile nuget.config -PackagesDirectory "$MRTSourcesDirectory\mrt\packages"

$nuSpecsPath = "build\NuSpecs"
$fullNugetPath = "build\fullnuget"
$buildOverridePath = "build\override"
$windowsAppSdkBinariesPath = "build\windowsappsdk_binaries"

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

$builddate_yymm = Get-Date -Format "yyMM"
$builddate_dd = Get-Date -Format "dd"
$revision = Get-Date -Format "HHMM"

$VCToolsInstallDir = . "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -Latest -requires Microsoft.Component.MSBuild -property InstallationPath
write-host "VCToolsInstallDir: $VCToolsInstallDir"

 foreach($platformToRun in $platform.Split(","))
 {
   & $MRTSourcesDirectory\build\init.cmd /envonly $platformToRun\fre
 }

 # Build the solution
 foreach($configurationToRun in $configuration.Split(","))
 {
    foreach($platformToRun in $platform.Split(","))
    {
        # adding /m gives a circular depdency.  Keep the /m out until fixed.
        msbuild /restore WindowsAppRuntime.sln /p:Configuration=$configurationToRun,Platform=$platformToRun
		#,AppxSymbolPackageEnabled=false,WindowsAppSDKVersionBuild=$builddate_yymm,WindowsAppSDKVersionRevision=$builddate_dd$buildrevision,VCToolsInstallDir=$VCToolsInstallDir
        msbuild "$MRTSourcesDirectory\mrt\MrtCore.sln" /restore /p:Configuration=$configurationToRun,Platform=$platformToRun
    }
 }

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
msbuild /restore "dev\Bootstrap\CS\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.csproj" /p:Configuration=release,Platform=anycpu
copy-item -path "buildoutput\release\anycpu\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.dll"  -destination "$fullNugetPath\lib\net5.0-windows10.0.17763.0"

#generate overrides
.\tools\GenerateDynamicDependencyOverrides.ps1 -Path "$buildOverridePath"
.\tools\GeneratePushNotificationsOverrides.ps1 -Path "$buildOverridePath"


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

$workingDirectory = get-location
$manifestPath = "$fullNugetPath\manifests"
$newitem = New-Item -ItemType Directory -Force -Path $manifestPath
$xslt = New-Object System.Xml.Xsl.XslCompiledTransform
$xslt.Load("$workingDirectory\build\TransformAppxManifest.xslt")
$xslt.Transform("$workingDirectory\$fullNugetPath\AppxManifest.xml", "$workingDirectory\$manifestPath\Microsoft.WindowsAppSdk.Foundation.manifest")

$packageVersion = '1.1.1.1'
Write-Host $packageVersion
[xml]$publicNuspec = Get-Content -Path ".\build\NuSpecs\Microsoft.WindowsAppSDK.Foundation.nuspec"
$publicNuspec.package.metadata.version = $packageVersion
Set-Content -Value $publicNuspec.OuterXml ".\build\NuSpecs\Microsoft.WindowsAppSDK.Foundation.nuspec"

Copy-Item -Path "license" -destination "$fullNugetPath" -force
nuget pack ".\build\NuSpecs\Microsoft.WindowsAppSDK.Foundation.nuspec" -BasePath $fullNugetPath -OutputDirectory $LocalPackagesPath

$packageName = "Microsoft.WindowsAppSDK.Foundation.TransportPackage"
&"$UpdateVersionDetailsPath" -dependencyName $packageName -dependencyVersion $packageVersion

& .\.nuget\nuget.exe pack "$workingDirectory\$nuSpecsPath\Microsoft.WindowsAppSDK.Foundation.nuspec" -outputdirectory "$workingDirectory\$fullNugetPath" -BasePath "$workingDirectory\$fullNugetPath"