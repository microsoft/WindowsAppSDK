[CmdLetBinding()]
Param(
    [string]$BuildOutputDir,
    [string]$PublishDir,
    [string]$NugetDir,
    [string]$Platform,
    [string]$Configuration,
    [switch]$PublishAppxFiles=$false
)

$FullBuildOutput = "$($BuildOutputDir)\$($Configuration)\$($Platform)"
$FullPublishDir = "$($PublishDir)\$($Configuration)\$($Platform)"

if (!(Test-Path $FullPublishDir)) { mkdir $FullPublishDir }


function PublishFile {
    Param($source, $destinationDir, [switch]$IfExists = $false)

    if ((-not $IfExists) -or (Test-Path $source))
    {
        Write-Host "Copy from '$source' to '$destinationDir'"
        if (-not (Test-Path $destinationDir))
        {
            $ignore = New-Item -ItemType Directory $destinationDir
        }
        Copy-Item -Recurse -Force $source $destinationDir
    }
    else
    {
        Write-Host "Not copying '$source' to $destinationDir because it did not exist"
    }
}

PublishFile $FullBuildOutput\override\DynamicDependency-Override.json $FullPublishDir\

PublishFile $FullBuildOutput\ProjectReunion_DLL\Microsoft.ProjectReunion.dll $FullPublishDir\Microsoft.ProjectReunion\
PublishFile $FullBuildOutput\ProjectReunion_DLL\Microsoft.ProjectReunion.lib $FullPublishDir\Microsoft.ProjectReunion\
PublishFile $FullBuildOutput\ProjectReunion_DLL\Microsoft.ApplicationModel.Activation.winmd $FullPublishDir\Microsoft.ProjectReunion\
PublishFile $FullBuildOutput\ProjectReunion_DLL\Microsoft.ApplicationModel.DynamicDependency.winmd $FullPublishDir\Microsoft.ProjectReunion\
PublishFile $FullBuildOutput\ProjectReunion_DLL\MsixDynamicDependency.h $FullPublishDir\Microsoft.ProjectReunion\
PublishFile $FullBuildOutput\ProjectReunion_DLL\wil_msixdynamicdependency.h $FullPublishDir\Microsoft.ProjectReunion\
#
PublishFile $FullBuildOutput\DynamicDependency.DataStore\DynamicDependency.DataStore.exe $FullPublishDir\DynamicDependency.DataStore\
PublishFile $FullBuildOutput\DynamicDependency.DataStore.ProxyStub\DynamicDependency.DataStore.ProxyStub.dll $FullPublishDir\DynamicDependency.DataStore\
#
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager\DynamicDependencyLifetimeManager.exe $FullPublishDir\DynamicDependencyLifetimeManager\
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager.ProxyStub\DynamicDependencyLifetimeManager.ProxyStub.dll $FullPublishDir\DynamicDependencyLifetimeManager\
#
PublishFile $FullBuildOutput\ProjectReunion_BootstrapDLL\Microsoft.ProjectReunion.Bootstrap.dll $FullPublishDir\Microsoft.ProjectReunion.Bootstrap\
PublishFile $FullBuildOutput\ProjectReunion_BootstrapDLL\Microsoft.ProjectReunion.Bootstrap.lib $FullPublishDir\Microsoft.ProjectReunion.Bootstrap\
PublishFile $FullBuildOutput\ProjectReunion_BootstrapDLL\MddBootstrap.h $FullPublishDir\Microsoft.ProjectReunion.Bootstrap\

#PublishFile -IfExists $FullBuildOutput\ProjectReunion_DLL\Generic.xaml $FullPublishDir\Microsoft.ProjectReunion\
#PublishFile -IfExists $FullBuildOutput\Microsoft.ProjectReunion.Design\Microsoft.ProjectReunion.Design.dll $FullPublishDir\Microsoft.ProjectReunion.Design\
#PublishFile -IfExists $BuildOutputDir\$Configuration\AnyCPU\Microsoft.ProjectReunion.FrameworkPackagePRI\Microsoft.ProjectReunion.pri $FullPublishDir\Microsoft.ProjectReunion.FrameworkPackagePRI\

#UNDONE - PGO etc. later PR
# pgosweep and vcruntime are required to run pgo instrumented test run. They are placed from the
# cx test app instead of releasetest.dll since these are architecture specific and the ReleaseTest assembly is AnyCPU.
#PublishFile -IfExists $FullBuildOutput\NugetPackageTestAppCX\pgosweep.exe $FullPublishDir\Test\
#PublishFile -IfExists $FullBuildOutput\NugetPackageTestAppCX\vcruntime140.dll $FullPublishDir\Test\

PublishFile -IfExists $FullBuildOutput\FrameworkPackage\*.* $FullPublishDir\FrameworkPackage

if($PublishAppxFiles)
{
    $AppxPackagesDir = "$FullPublishDir\AppxPackages"

#    PublishFile -IfExists $FullBuildOutput\MUXControlsTestApp.TAEF\AppPackages\MUXControlsTestApp_Test\ $AppxPackagesDir
#    PublishFile -IfExists $FullBuildOutput\IXMPTestApp.TAEF\AppPackages\IXMPTestApp_Test\ $AppxPackagesDir
#    PublishFile -IfExists $FullBuildOutput\MUXControlsTestAppWPFPackage\AppPackages\MUXControlsTestAppWPFPackage_Test\ $AppxPackagesDir

#    PublishFile -IfExists $FullBuildOutput\NugetPackageTestApp\AppPackages\NugetPackageTestApp_Test\ $AppxPackagesDir
#    PublishFile -IfExists $FullBuildOutput\NugetPackageTestAppCX\AppPackages\NugetPackageTestAppCX_Test\ $AppxPackagesDir
#    PublishFile -IfExists $FullBuildOutput\AppThatUsesMUXIndirectly\AppPackages\AppThatUsesMUXIndirectly_Test\ $AppxPackagesDir
}

# Publish pdbs:
$symbolsOutputDir = "$($FullPublishDir)\Symbols\"
PublishFile $FullBuildOutput\ProjectReunion_DLL\Microsoft.ProjectReunion.pdb $symbolsOutputDir
PublishFile $FullBuildOutput\DynamicDependency.DataStore\DynamicDependency.DataStore.pdb $symbolsOutputDir
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager\DynamicDependencyLifetimeManager.pdb $symbolsOutputDir
PublishFile $FullBuildOutput\ProjectReunion_BootstrapDLL\Microsoft.ProjectReunion.Bootstrap.pdb $symbolsOutputDir

# Copy files to Full Nuget package
PublishFile $FullBuildOutput\ProjectReunion_DLL\Microsoft.ProjectReunion.dll $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\ProjectReunion_DLL\Microsoft.ProjectReunion.pdb $NugetDir\runtimes\win10-$Platform\native\
PublishFile $FullBuildOutput\ProjectReunion_DLL\Microsoft.ProjectReunion.lib $NugetDir\lib\win10-$Platform
PublishFile $FullBuildOutput\ProjectReunion_DLL\Microsoft.ApplicationModel.Activation.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\ProjectReunion_DLL\Microsoft.ApplicationModel.DynamicDependency.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\ProjectReunion_DLL\MsixDynamicDependency.h $NugetDir\inc\uap10.0
PublishFile $FullBuildOutput\ProjectReunion_DLL\wil_msixdynamicdependency.h $NugetDir\inc\uap10.0
#
PublishFile $FullBuildOutput\DynamicDependency.DataStore\DynamicDependency.DataStore.exe $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\DynamicDependency.DataStore\DynamicDependency.DataStore.pdb $NugetDir\runtimes\win10-$Platform\native\
PublishFile $FullBuildOutput\DynamicDependency.DataStore.ProxyStub\DynamicDependency.DataStore.ProxyStub.dll $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\DynamicDependency.DataStore.ProxyStub\DynamicDependency.DataStore.ProxyStub.pdb $NugetDir\runtimes\win10-$Platform\native\
#
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager\DynamicDependencyLifetimeManager.exe $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager\DynamicDependencyLifetimeManager.pdb $NugetDir\runtimes\win10-$Platform\native\
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager.ProxyStub\DynamicDependencyLifetimeManager.ProxyStub.dll $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager.ProxyStub\DynamicDependencyLifetimeManager.ProxyStub.pdb $NugetDir\runtimes\win10-$Platform\native\
#
PublishFile $FullBuildOutput\ProjectReunion_BootstrapDLL\Microsoft.ProjectReunion.Bootstrap.dll $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\ProjectReunion_BootstrapDLL\Microsoft.ProjectReunion.Bootstrap.pdb $NugetDir\runtimes\win10-$Platform\native\
PublishFile $FullBuildOutput\ProjectReunion_BootstrapDLL\Microsoft.ProjectReunion.Bootstrap.lib $NugetDir\lib\win10-$Platform
PublishFile $FullBuildOutput\ProjectReunion_BootstrapDLL\MddBootstrap.h $NugetDir\inc\win10-$Platform
