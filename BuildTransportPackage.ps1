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
    [string]$PackageVersion = "1.1.1.1",
    [string]$Platform,
    [string]$Configuration,
    [string]$AzureBuildStep = "all",
    [string]$LocalPackagesPath = $null,
    [string]$UpdateVersionDetailsPath = $null
)

# Make sure nuget directory exists.
if(-not (test-path ".nuget"))
{
    new-item -path ".nuget" -itemtype directory
}

# Make sure nuget is on the system
if(-not (test-path ".nuget\nuget.exe"))
{
    Invoke-WebRequest https://dist.nuget.org/win-x86-commandline/latest/nuget.exe -OutFile .nuget\nuget.exe
}


Try {
    if (($AzureBuildStep -eq "all") -Or ($AzureBuildStep -eq "BuildBinaries")) 
    {
        # Restore nuget packages for everything in WIndowsAppRuntime.sln and other files.
        & .\.nuget\nuget.exe restore "build\packages.config" -PackagesDirectory packages -ConfigFile "build\licensing.nuget.config"
        & .\.nuget\nuget.exe restore WindowsAppRuntime.sln -configfile nuget.config
        & .\.nuget\nuget.exe restore "dev\Bootstrap\CS\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.csproj" -configfile nuget.config

        # If the call to restore WindowsAppRuntime_Insights fails check to make sure all Window SDK's from 17760 are installed.
        & .\.nuget\nuget.exe restore "dev\WindowsAppRuntime_Insights\packages.config" -ConfigFile "dev\WindowsAppRuntime_Insights\nuget.config" -PackagesDirectory "dev\WindowsAppRuntime_Insights\packages"


        $VCToolsInstallDir = . "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -Latest -requires Microsoft.Component.MSBuild -property InstallationPath
        write-host "VCToolsInstallDir: $VCToolsInstallDir"

        $msBuildPath = "$VCToolsInstallDir\MSBuild\Current\Bin\msbuild.exe"
        write-host "msBuildPath: $msBuildPath"
        #------------------
        #    Build windowsAppRuntime.sln and move output to staging.
        #------------------

        # Generate package config and copy over misc files.
        & .\build\Scripts\ConvertVersionDetailsToPackageConfig.ps1 -versionDetailsPath "eng\Version.Details.xml" -packageConfigPath "build\packages.config"

        # Generate overrides
        # Make sure override directory exists.
        $buildOverridePath = "build\override"
        if(-not (test-path "$buildOverridePath"))
        {
            new-item -path "$buildOverridePath" -itemtype "directory"
        }

        .\tools\GenerateDynamicDependencyOverrides.ps1 -Path "$buildOverridePath"
        .\tools\GeneratePushNotificationsOverrides.ps1 -Path "$buildOverridePath"

        $srcPath = Get-Childitem -Path 'dev\WindowsAppRuntime_Insights\packages' -File 'MicrosoftTelemetry.h' -Recurse

        if (($srcPath -ne $null)){
        $destinationPaths = Get-Childitem -Path 'packages' -File 'Traceloggingconfig.h' -Recurse

        if (($destinationPaths -ne $null)) {
            foreach ($destPath in $destinationPaths) {
            Write-Host 'SourcePath:' $srcPath.FullName
            Write-Host 'DestinationPath:' $destPath.FullName
            Copy-Item -Force $srcPath.FullName $destPath.FullName
            }
        }
        }

        foreach($configurationToRun in $configuration.Split(","))
        {
            foreach($platformToRun in $platform.Split(","))
            {
                write-host "Building WindowsAppRuntime.sln for configuration $configurationToRun and platform:$platformToRun"
                & $msBuildPath /restore WindowsAppRuntime.sln /p:Configuration=$configurationToRun,Platform=$platformToRun
            }
        }

        # Make sure fullnuget path exists.
        $fullNugetPath = "build\fullnuget"
        if(-not (test-path "$fullNugetPath"))
        {    
            new-item -path "$fullNugetPath" -itemtype "directory"
        }

        if(-not (test-path "$fullNugetPath\build\native"))
        {
            new-item -path "$fullNugetPath\build\native" -itemtype "directory"
        }

        # Copy WindowsAppRuntime.sln files
        foreach($configurationToRun in $configuration.Split(","))
        {
            foreach($platformToRun in $platform.Split(","))
            {
                .\build\CopyFilesToStagingDir.ps1 -BuildOutputDir 'BuildOutput' -OverrideDir "$buildOverridePath" -PublishDir "$windowsAppSdkBinariesPath" -NugetDir "$fullNugetPath" -Platform $PlatformToRun -Configuration $ConfigurationToRun
            }
        }

        $nuSpecsPath = "build\NuSpecs"
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
        Copy-Item -Path "$nuSpecsPath\AppxManifest.xml" -Destination "$fullNugetPath\AppxManifest.xml"

        #------------------
        #    Build mrtcore.sln and move output to staging.
        #------------------

        #Restore packages from mrt.
        $MRTSourcesDirectory = "dev\MRTCore"
        & .\.nuget\nuget.exe restore "$MRTSourcesDirectory\mrt\core\src\packages.config" -ConfigFile nuget.config -PackagesDirectory "$MRTSourcesDirectory\mrt\packages"
        & .\.nuget\nuget.exe restore "$MRTSourcesDirectory\mrt\Microsoft.Windows.ApplicationModel.Resources\src\packages.config" -ConfigFile nuget.config -PackagesDirectory "$MRTSourcesDirectory\mrt\packages"
        & .\.nuget\nuget.exe restore "$MRTSourcesDirectory\mrt\mrm\mrmex\packages.config" -ConfigFile nuget.config -PackagesDirectory "$MRTSourcesDirectory\mrt\packages"
        & .\.nuget\nuget.exe restore "$MRTSourcesDirectory\mrt\mrm\mrmmin\packages.config" -ConfigFile nuget.config -PackagesDirectory "$MRTSourcesDirectory\mrt\packages"
        & .\.nuget\nuget.exe restore "$MRTSourcesDirectory\mrt\mrm\unittests\packages.config" -ConfigFile nuget.config -PackagesDirectory "$MRTSourcesDirectory\mrt\packages"

        # Init mrtcore
        foreach($platformToRun in $platform.Split(","))
        {
        & $MRTSourcesDirectory\build\init.cmd /envonly $platformToRun\fre
        }

        # Build mrt core.
        foreach($configurationToRun in $configuration.Split(","))
        {
            foreach($platformToRun in $platform.Split(","))
            {
                write-host "Building MrtCore.sln for configuration $configurationToRun and platform:$platformToRun"
                & $msBuildPath /restore "$MRTSourcesDirectory\mrt\MrtCore.sln" /p:Configuration=$configurationToRun,Platform=$platformToRun
            }
        }

        $configurationForMrtAndAnyCPU = "release"

        $MRTBinariesDirectory = "BuildOutput"
        # Copy over mrt files
        foreach($platformToRun in $platform.Split(","))
        {
            copy-item -path "$MRTBinariesDirectory\$configurationForMrtAndAnyCPU\$platformToRun\mrm\mrm.dll" -destination "$fullNugetPath\runtimes\win10-$platformToRun\native" -force
            copy-item -path "$MRTBinariesDirectory\$configurationForMrtAndAnyCPU\$platformToRun\mrm\mrm.pdb" -destination "$fullNugetPath\runtimes\win10-$platformToRun\native" -force
            copy-item -path "$MRTBinariesDirectory\$configurationForMrtAndAnyCPU\$platformToRun\Microsoft.Windows.ApplicationModel.Resources\Microsoft.Windows.ApplicationModel.Resources.pdb" -destination "$fullNugetPath\runtimes\win10-$platformToRun\native" -force
            copy-item -path "$MRTBinariesDirectory\$configurationForMrtAndAnyCPU\$platformToRun\Microsoft.Windows.ApplicationModel.Resources\Microsoft.Windows.ApplicationModel.Resources.dll" -destination "$fullNugetPath\runtimes\win10-$platformToRun\native" -force
            
            copy-item -path "$MRTBinariesDirectory\$configurationForMrtAndAnyCPU\$platformToRun\mrm\mrm.lib" -destination "$fullNugetPath\lib\win10-$platformToRun" -force

            if($platformToRun -eq "x86")
            {
                copy-item -path "$MRTBinariesDirectory\$configurationForMrtAndAnyCPU\$platformToRun\Microsoft.Windows.ApplicationModel.Resources.Projection\Microsoft.Windows.ApplicationModel.Resources.Projection.dll" -destination "$fullNugetPath\lib\net6.0-windows10.0.17763.0" -force
                copy-item -path "$MRTBinariesDirectory\$configurationForMrtAndAnyCPU\$platformToRun\Microsoft.Windows.ApplicationModel.Resources.Projection\Microsoft.Windows.ApplicationModel.Resources.Projection.pdb" -destination "$fullNugetPath\lib\net6.0-windows10.0.17763.0" -force
                copy-item -path "$MRTBinariesDirectory\$configurationForMrtAndAnyCPU\$platformToRun\Microsoft.Windows.ApplicationModel.Resources\Microsoft.Windows.ApplicationModel.Resources.winmd" -destination "$fullNugetPath\lib\uap10.0" -force
            }
        }

        # copy MRT IDL over.
        copy-item -path "$MRTSourcesDirectory\mrt\Microsoft.Windows.ApplicationModel.Resources\src\Microsoft.Windows.ApplicationModel.Resources.idl" -destination "$fullNugetPath\include" -force

        # Copy MRT metadata files.
        Copy-Item -Path "$MRTSourcesDirectory\packaging\MrtCore.props" -Destination "$fullNugetPath\build"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\MrtCore.PriGen.targets" -Destination "$fullNugetPath\build"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\MrtCore.References.targets" -Destination "$fullNugetPath\build"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\MrtCore.targets" -Destination "$fullNugetPath\build"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\native\MrtCore.C.props" -Destination "$fullNugetPath\build\native"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\native\MrtCore.props" -Destination "$fullNugetPath\build\native"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\native\MrtCore.targets" -Destination "$fullNugetPath\build\native"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\ProjectItemsSchema.xaml" -Destination "$fullNugetPath\build"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\README.md" -Destination "$fullNugetPath\build"
        Copy-Item -Path "$MRTSourcesDirectory\mrt\core\src\mrm.h" -Destination "$fullNugetPath\include"
        Copy-Item -Path "$MRTSourcesDirectory\mrt\Microsoft.Windows.ApplicationModel.Resources\src\Microsoft.Windows.ApplicationModel.Resources.idl" -Destination "$fullNugetPath\include"


        #------------------
        #    Build windowsAppRuntime.sln (anyCPU) and move output to staging.
        #------------------
        # build AnyCPU
        msbuild /restore "dev\Bootstrap\CS\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.csproj" /p:Configuration=$configurationForMrtAndAnyCPU,Platform=anycpu

        # If AnyCPU generates another dll it needs to be added here.
        copy-item -path "buildoutput\$configurationToUseForSingleConfiguration\anycpu\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.dll"  -destination "$fullNugetPath\lib\net6.0-windows10.0.17763.0"

        #------------------
        #    Move other files and prepare manifest and appxmanifest.xml
        #------------------

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
    }
    if (($AzureBuildStep -eq "all") -Or ($AzureBuildStep -eq "PackNuget")) 
    {
        # Add the version to the nuspec.
        [xml]$publicNuspec = Get-Content -Path ".\build\NuSpecs\Microsoft.WindowsAppSDK.Foundation.nuspec"
        $publicNuspec.package.metadata.version = $PackageVersion
        Set-Content -Value $publicNuspec.OuterXml ".\build\NuSpecs\Microsoft.WindowsAppSDK.Foundation.nuspec"

        # Make the foundation transport package.
        nuget pack ".\build\NuSpecs\Microsoft.WindowsAppSDK.Foundation.nuspec" -BasePath $fullNugetPath -OutputDirectory $LocalPackagesPath

        # # Update the details in eng/version.details.xml
        # $packageName = "Microsoft.WindowsAppSDK.Foundation.TransportPackage"
        # &"$UpdateVersionDetailsPath" -dependencyName $packageName -dependencyVersion $PackageVersion

        # if(test-path("$env:Build_SourcesDirectory\build\packages\Microsoft.WindowsAppSDK.Foundation.TransportPackage.$PackageVersion"))
        # {
        #     remove-item "$env:Build_SourcesDirectory\build\packages\Microsoft.WindowsAppSDK.Foundation.TransportPackage.$PackageVersion" -force -recurse
        # }
    }
} 
Catch 
{
    $formatstring = "`n{0}`n`n{1}`n`nBuild can be resumed by running:`nBuildAll -resume`n- or -`nBuildAll -Checkpoint <COMING SOON>"
    $fields = $_, $_.ScriptStackTrace

    Write-Host ($formatstring -f $fields) -ForegroundColor RED
    exit 1
}
