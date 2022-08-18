Param(
    [string]$Platforms,
    [string]$Configurations,
    [string]$LocalPackagesPath = $null,
    [string]$UpdateVersionDetailsPath = $null
)

# do all the directory making before any building.
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

if(-not (test-path "$fullNugetPath\native"))
{
	new-item -path "$fullNugetPath\native" -itemtype "directory"
}

# Build the solution
foreach($configuration in $configurations)
{
	foreach($platform in $platforms)
	{
		msbuild /m /p:Configuration=$Configuration,Platform=$Platform WindowsAppRuntime.sln
	}
}

#generate overrides
.\tools\GenerateDynamicDependencyOverrides.ps1 -Path "$buildOverridePath"
.\tools\GeneratePushNotificationsOverrides.ps1 -Path "$buildOverridePath"

foreach($configuration in $configurations)
{
	foreach($platform in $platforms)
	{
		.\build\CopyFilesToStagingDir.ps1 -BuildOutputDir 'BuildOutput' -OverrideDir "$buildOverridePath" -PublishDir "$windowsAppSdkBinariesPath" -NugetDir "$fullNugetPath" -Platform $Platform -Configuration $Configuration
	}
}

 
Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.targets" -Destination "$fullNugetPath\build\native\Microsoft.WindowsAppSDK.Foundation.targets" -force
Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.props" -Destination "$fullNugetPath\build\native\Microsoft.WindowsAppSDK.Foundation.props" -force
Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.C.props" -Destination "$fullNugetPath\build\native\WindowsAppSDK-Nuget-Native.C.props" -force
Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.WinRt.props" -Destination "$fullNugetPath\build\native\WindowsAppSDK-Nuget-Native.WinRt.props" -force
Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Foundation.targets" -Destination "$fullNugetPath\build\Microsoft.WindowsAppSDK.Foundation.targets" -force
Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Foundation.props" -Destination "$fullNugetPath\build\Microsoft.WindowsAppSDK.Foundation.props" -force
Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Bootstrap.CS.targets" -Destination "$fullNugetPath\build\Microsoft.WindowsAppSDK.Bootstrap.CS.targets" -force
Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.Bootstrap.targets" -Destination "$fullNugetPath\build\native\WindowsAppSDK-Nuget-Native.Bootstrap.targets" -force
Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.BootstrapCommon.targets" -Destination "$fullNugetPath\build\Microsoft.WindowsAppSDK.BootstrapCommon.targets" -force
Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.UndockedRegFreeWinRT.CS.targets" -Destination "$fullNugetPath\build\Microsoft.WindowsAppSDK.UndockedRegFreeWinRT.CS.targets" -force
Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.UndockedRegFreeWinRT.targets" -Destination "$fullNugetPath\build\native\WindowsAppSDK-Nuget-Native.UndockedRegFreeWinRT.targets" -force
Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.UndockedRegFreeWinRTCommon.targets" -Destination "$fullNugetPath\build\Microsoft.WindowsAppSDK.UndockedRegFreeWinRTCommon.targets" -force
Copy-Item -Path "$nuSpecsPath\AppxManifest.xml" -Destination "$fullNugetPath\AppxManifest.xml"

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