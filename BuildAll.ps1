<#
This script is to build the Foundation transport package that will be used to generate the windows app sdk package.
This script is called from BuildAll.ps1 from the aggregator repo and should not be called directly.

PackageVersion: NuGet Package Version that will be used in the packing of Foundation Transport Package
Platform: Comma delimited string of platforms to run.
Configuration: Comma delimited string of configurations to run.
AzureBuildStep: Only used by the pipeline to perform tasks such as signing in between the steps
OutputDirectory: Pack Location of the Nuget Package
UpdateVersionDetailsPath: Path to a ps1 or cmd that updates version.details.xml.
Clean: Performs a clean on BuildOutput, Obj, and build\override

Note about building in different environments.
The feed the nuget.config points to changes depending on the branch.
Develop branch points to the internal feed.
Main branch points to the external feed.

#>

Param(
    [string]$PackageVersion = "1.1.1.1",
    [string]$Platform = "x64",
    [string]$Configuration = "Release",
    [string]$AzureBuildStep = "all",
    [string]$OutputDirectory = "BuildOutput",
    [string]$PGOBuildMode = "Optimize",
    [string]$UpdateVersionDetailsPath = $null,
    [switch]$Clean = $false
)

$env:Build_SourcesDirectory = (Split-Path $MyInvocation.MyCommand.Path)
$buildOverridePath = "build\override"
$BasePath = "BuildOutput/FullNuget"

# FUTURE(YML2PS): Update build to no longer place generated files in sources directory
if ($Clean) 
{
    $CleanTargets = @(
      "BuildOutput",
      "obj",
      $buildOverridePath
    )
  
    foreach ($CleanTarget in $CleanTargets)
    {
      $CleanTargetPath = (Join-Path $env:Build_SourcesDirectory $CleanTarget)
  
      if (Test-Path ($CleanTargetPath)) {
        Remove-Item $CleanTargetPath -recurse
      }
    }
    
    Exit
}

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

$configurationForMrtAndAnyCPU = "Release"
$MRTSourcesDirectory = "dev\MRTCore"

$VCToolsInstallDir = . "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -Latest -requires Microsoft.Component.MSBuild -property InstallationPath
write-host "VCToolsInstallDir: $VCToolsInstallDir"

$msBuildPath = "$VCToolsInstallDir\MSBuild\Current\Bin\msbuild.exe"
write-host "msBuildPath: $msBuildPath"


# Generate overrides
# Make sure override directory exists.
if(-not (test-path "$buildOverridePath"))
{
    new-item -path "$buildOverridePath" -itemtype "directory"
}

Try {
    $WindowsAppSDKBuildPipeline = 0

    .\tools\GenerateDynamicDependencyOverrides.ps1 -Path "$buildOverridePath"
    .\tools\GeneratePushNotificationsOverrides.ps1 -Path "$buildOverridePath"

    if ($AzureBuildStep -ne "all")
    {
        # Some builds have "-branchname" appended, but when this happens the environment variable 
        # TFS_BUILDNUMBER has the un-modified version.
        if ($env:TFS_BUILDNUMBER)
        {
            $env:BUILD_BUILDNUMBER = $env:TFS_BUILDNUMBER
        }
        Write-Host "BuildNumber : " $env:BUILD_BUILDNUMBER
        $yymm = $env:BUILD_BUILDNUMBER.substring($env:BUILD_BUILDNUMBER.length - 10, 4)
        $dd = $env:BUILD_BUILDNUMBER.substring($env:BUILD_BUILDNUMBER.length - 5, 2)
        $revision = $env:BUILD_BUILDNUMBER.substring($env:BUILD_BUILDNUMBER.length - 3, 3)
        
        $WindowsAppSDKVersionProperty = "/p:WindowsAppSDKVersionBuild=$yymm /p:WindowsAppSDKVersionRevision=$dd$revision"
        
        # If $AzureBuildStep is not "all", that means we are in the pipeline
        $WindowsAppSDKBuildPipeline = 1
    }
    if (($AzureBuildStep -eq "all") -Or (($AzureBuildStep -eq "BuildBinaries") -Or ($AzureBuildStep -eq "BuildMRT"))) 
    {
        & .\.nuget\nuget.exe restore WindowsAppRuntime.sln -configfile nuget.config
        & .\.nuget\nuget.exe restore "dev\Bootstrap\CS\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.csproj" -configfile nuget.config

        if ($lastexitcode -ne 0)
        {
            exit 1
        }

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

        if ($lastexitcode -ne 0)
        {
            exit 1
        }
    }
    if (($AzureBuildStep -eq "all") -Or ($AzureBuildStep -eq "BuildBinaries")) 
    {
        foreach($configurationToRun in $configuration.Split(","))
        {
            foreach($platformToRun in $platform.Split(","))
            {
                write-host "Building WindowsAppRuntime.sln for configuration $configurationToRun and platform:$platformToRun"
                & $msBuildPath /restore `
                                WindowsAppRuntime.sln `
                                /p:Configuration=$configurationToRun,Platform=$platformToRun `
                                /binaryLogger:"BuildOutput/WindowsAppRuntime.$platformToRun.$configurationToRun.binlog" `
                                $WindowsAppSDKVersionProperty `
                                /p:PGOBuildMode=$PGOBuildMode `
                                /p:WindowsAppSDKCleanIntermediateFiles=true `
                                /p:AppxSymbolPackageEnabled=false `
                                /p:WindowsAppSDKBuildPipeline=$WindowsAppSDKBuildPipeline
                if ($lastexitcode -ne 0)
                {
                    exit 1
                }
            }
        }
    }
    if (($AzureBuildStep -eq "all") -Or ($AzureBuildStep -eq "BuildMRT")) 
    {
        #------------------
        #    Build mrtcore.sln and move output to staging.
        #------------------

        #Restore packages from mrt.
        & .\.nuget\nuget.exe restore "$MRTSourcesDirectory\mrt\MrtCore.sln" -ConfigFile nuget.config -PackagesDirectory "$MRTSourcesDirectory\mrt\packages"
        & .\.nuget\nuget.exe restore "$MRTSourcesDirectory\mrt\Microsoft.Windows.ApplicationModel.Resources\src\packages.config" -ConfigFile nuget.config -PackagesDirectory "$MRTSourcesDirectory\mrt\packages"
        & .\.nuget\nuget.exe restore "$MRTSourcesDirectory\mrt\mrm\mrmex\packages.config" -ConfigFile nuget.config -PackagesDirectory "$MRTSourcesDirectory\mrt\packages"
        & .\.nuget\nuget.exe restore "$MRTSourcesDirectory\mrt\mrm\mrmmin\packages.config" -ConfigFile nuget.config -PackagesDirectory "$MRTSourcesDirectory\mrt\packages"
        & .\.nuget\nuget.exe restore "$MRTSourcesDirectory\mrt\mrm\unittests\packages.config" -ConfigFile nuget.config -PackagesDirectory "$MRTSourcesDirectory\mrt\packages"

        if ($lastexitcode -ne 0)
        {
            exit 1
        }

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
                & $msBuildPath /restore "$MRTSourcesDirectory\mrt\MrtCore.sln" `
                                /p:Configuration=$configurationToRun,Platform=$platformToRun `
                                /p:PGOBuildMode=$PGOBuildMode `
                                /binaryLogger:"BuildOutput/mrtcore.$platformToRun.$configurationToRun.binlog"

                if ($lastexitcode -ne 0)
                {
                    exit 1
                }
            }
        }
    }
    if (($AzureBuildStep -eq "all") -Or ($AzureBuildStep -eq "BuildAnyCPU")) 
    {
        #------------------
        #    Build windowsAppRuntime.sln (anyCPU) and move output to staging.
        #------------------
        # build AnyCPU
        & $msBuildPath /restore "dev\Bootstrap\CS\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.csproj" /p:Configuration=$configurationForMrtAndAnyCPU,Platform=AnyCPU
        if ($lastexitcode -ne 0)
        {
            exit 1
        }
    }
    if (($AzureBuildStep -eq "all") -Or ($AzureBuildStep -eq "StageFiles")) 
    {
        #------------------
        #    Stage files for Packing
        #------------------    
        if(-not (test-path "$BasePath"))
        {    
            new-item -path "$BasePath" -itemtype "directory"
        }

        if(-not (test-path "$BasePath\build\native"))
        {
            new-item -path "$BasePath\build\native" -itemtype "directory"
        }

        # Copy WindowsAppRuntime.sln files
        foreach($configurationToRun in $configuration.Split(","))
        {
            foreach($platformToRun in $platform.Split(","))
            {
                .\build\CopyFilesToStagingDir.ps1 -BuildOutputDir 'BuildOutput' -OverrideDir "$buildOverridePath" -PublishDir "$windowsAppSdkBinariesPath" -NugetDir "$BasePath" -Platform $PlatformToRun -Configuration $ConfigurationToRun
                if ($lastexitcode -ne 0)
                {
                    exit 1
                }
            }
        }

        $nuSpecsPath = "build\NuSpecs"
        Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.targets" -Destination "$BasePath\build\native\Microsoft.WindowsAppSDK.Foundation.targets"
        Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.props" -Destination "$BasePath\build\native\Microsoft.WindowsAppSDK.Foundation.props"
        Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.C.props" -Destination "$BasePath\build\native"
        Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.WinRt.props" -Destination "$BasePath\build\native"
        Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.Bootstrap.targets" -Destination "$BasePath\build\native"
        Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.DeploymentManager.targets" -Destination "$BasePath\build\native"
        Copy-Item -Path "$nuSpecsPath\WindowsAppSDK-Nuget-Native.UndockedRegFreeWinRT.targets" -Destination "$BasePath\build\native"

        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Foundation.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Foundation.props" -Destination "$BasePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.Bootstrap.CS.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.BootstrapCommon.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.DeploymentManager.CS.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.DeploymentManagerCommon.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.UndockedRegFreeWinRT.CS.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$nuSpecsPath\Microsoft.WindowsAppSDK.UndockedRegFreeWinRTCommon.targets" -Destination "$BasePath\build"

        Copy-Item -Path "$nuSpecsPath\AppxManifest.xml" -Destination "$BasePath\AppxManifest.xml"

        # Copy over mrt files
        foreach($platformToRun in $platform.Split(","))
        {
            Copy-Item -path "BuildOutput\$configurationForMrtAndAnyCPU\$platformToRun\mrm\MRM.dll" -destination "$BasePath\runtimes\win10-$platformToRun\native" -force
            Copy-Item -path "BuildOutput\$configurationForMrtAndAnyCPU\$platformToRun\mrm\MRM.pdb" -destination "$BasePath\runtimes\win10-$platformToRun\native" -force
            Copy-Item -path "BuildOutput\$configurationForMrtAndAnyCPU\$platformToRun\Microsoft.Windows.ApplicationModel.Resources\Microsoft.Windows.ApplicationModel.Resources.pdb" -destination "$BasePath\runtimes\win10-$platformToRun\native" -force
            Copy-Item -path "BuildOutput\$configurationForMrtAndAnyCPU\$platformToRun\Microsoft.Windows.ApplicationModel.Resources\Microsoft.Windows.ApplicationModel.Resources.dll" -destination "$BasePath\runtimes\win10-$platformToRun\native" -force
            
            Copy-Item -path "BuildOutput\$configurationForMrtAndAnyCPU\$platformToRun\mrm\MRM.lib" -destination "$BasePath\lib\win10-$platformToRun" -force

            if($platformToRun -eq "x86")
            {
                Copy-Item -path "BuildOutput\$configurationForMrtAndAnyCPU\$platformToRun\Microsoft.Windows.ApplicationModel.Resources.Projection\Microsoft.Windows.ApplicationModel.Resources.Projection.dll" -destination "$BasePath\lib\net6.0-windows10.0.17763.0" -force
                Copy-Item -path "BuildOutput\$configurationForMrtAndAnyCPU\$platformToRun\Microsoft.Windows.ApplicationModel.Resources.Projection\Microsoft.Windows.ApplicationModel.Resources.Projection.pdb" -destination "$BasePath\lib\net6.0-windows10.0.17763.0" -force
                Copy-Item -path "BuildOutput\$configurationForMrtAndAnyCPU\$platformToRun\Microsoft.Windows.ApplicationModel.Resources\Microsoft.Windows.ApplicationModel.Resources.winmd" -destination "$BasePath\lib\uap10.0" -force
            }
        }

        # copy MRT IDL over.
        Copy-Item -path "$MRTSourcesDirectory\mrt\Microsoft.Windows.ApplicationModel.Resources\src\Microsoft.Windows.ApplicationModel.Resources.idl" -destination "$BasePath\include" -force

        # Copy MRT metadata files.
        Copy-Item -Path "$MRTSourcesDirectory\packaging\MrtCore.props" -Destination "$BasePath\build"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\MrtCore.PriGen.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\MrtCore.References.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\MrtCore.targets" -Destination "$BasePath\build"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\native\MrtCore.C.props" -Destination "$BasePath\build\native"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\native\MrtCore.props" -Destination "$BasePath\build\native"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\native\MrtCore.targets" -Destination "$BasePath\build\native"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\ProjectItemsSchema.xaml" -Destination "$BasePath\build"
        Copy-Item -Path "$MRTSourcesDirectory\packaging\README.md" -Destination "$BasePath\build"
        Copy-Item -Path "$MRTSourcesDirectory\mrt\core\src\MRM.h" -Destination "$BasePath\include"
        Copy-Item -Path "$MRTSourcesDirectory\mrt\Microsoft.Windows.ApplicationModel.Resources\src\Microsoft.Windows.ApplicationModel.Resources.idl" -Destination "$BasePath\include"

        # If AnyCPU generates another dll it needs to be added here.
        Copy-Item -path "BuildOutput\$configurationForMrtAndAnyCPU\anycpu\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.dll"  -destination "$BasePath\lib\net6.0-windows10.0.17763.0"

        #------------------
        #    Move other files and prepare manifest and appxmanifest.xml
        #------------------

        Copy-Item -Path "$nuSpecsPath\AppxManifest.xml" -Destination "$BasePath"
        Copy-Item -Path "LICENSE" -Destination "$BasePath" -force

        if ($lastexitcode -ne 0)
        {
            exit 1
        }

        # for some reason xslt.load changes the working directory to C:\windows\system32.
        # store the current working directory here.
        $workingDirectory = get-location
        $manifestPath = "$BasePath\manifests"

        # Make Microsoft.WindowsAppSDK.Foundation.manifest.
        $newitem = New-Item -ItemType Directory -Force -Path $manifestPath
        $xslt = New-Object System.Xml.Xsl.XslCompiledTransform
        $xslt.Load("$workingDirectory\build\TransformAppxManifest.xslt")
        $xslt.Transform("$workingDirectory\$BasePath\AppxManifest.xml", "$workingDirectory\$manifestPath\Microsoft.WindowsAppSdk.Foundation.manifest")

        if ($lastexitcode -ne 0)
        {
            exit 1
        }
    }
    if (($AzureBuildStep -eq "all") -Or ($AzureBuildStep -eq "PackNuget")) 
    {
        $nuspecPath = "BuildOutput\Microsoft.WindowsAppSDK.Foundation.nuspec" 
        Copy-Item -Path ".\build\NuSpecs\Microsoft.WindowsAppSDK.Foundation.nuspec" -Destination $nuspecPath

        # Add the version to the nuspec.
        [xml]$publicNuspec = Get-Content -Path $nuspecPath
        $publicNuspec.package.metadata.version = $PackageVersion
        Set-Content -Value $publicNuspec.OuterXml $nuspecPath

        # Make the foundation transport package.
        & .\.nuget\nuget.exe pack $nuspecPath -BasePath $BasePath -OutputDirectory $OutputDirectory

        if ($lastexitcode -ne 0)
        {
            exit 1
        }
    }
} 
Catch 
{
    $formatstring = "`n{0}`n`n{1}`n`n"
    $fields = $_, $_.ScriptStackTrace

    Write-Host ($formatstring -f $fields) -ForegroundColor RED
    exit 1
}
