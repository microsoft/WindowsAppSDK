[CmdLetBinding()]
Param(
    [string]$BuildOutputDir,
    [string]$OverrideDir,
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

PublishFile $OverrideDir\DynamicDependency-Override.json $FullPublishDir\

#
PublishFile $FullBuildOutput\DynamicDependency.DataStore\DynamicDependency.DataStore.exe $FullPublishDir\DynamicDependency.DataStore\
PublishFile $FullBuildOutput\DynamicDependency.DataStore.ProxyStub\DynamicDependency.DataStore.ProxyStub.dll $FullPublishDir\DynamicDependency.DataStore\
#
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager\DynamicDependencyLifetimeManager.exe $FullPublishDir\DynamicDependencyLifetimeManager\
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager.ProxyStub\DynamicDependencyLifetimeManager.ProxyStub.dll $FullPublishDir\DynamicDependencyLifetimeManager\

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
PublishFile $FullBuildOutput\DynamicDependency.DataStore\DynamicDependency.DataStore.pdb $symbolsOutputDir
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager\DynamicDependencyLifetimeManager.pdb $symbolsOutputDir

# Copy files to Full Nuget package
#
# MSIX Main package
PublishFile $FullBuildOutput\DynamicDependency.DataStore\DynamicDependency.DataStore.exe $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\DynamicDependency.DataStore\DynamicDependency.DataStore.pdb $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\DynamicDependency.DataStore.ProxyStub\DynamicDependency.DataStore.ProxyStub.dll $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\DynamicDependency.DataStore.ProxyStub\DynamicDependency.DataStore.ProxyStub.pdb $NugetDir\runtimes\win10-$Platform\native
#
# MSIX DDLM package
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager\DynamicDependencyLifetimeManager.exe $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager\DynamicDependencyLifetimeManager.pdb $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager.ProxyStub\DynamicDependencyLifetimeManager.ProxyStub.dll $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager.ProxyStub\DynamicDependencyLifetimeManager.ProxyStub.pdb $NugetDir\runtimes\win10-$Platform\native
#
# C#/WinRT Projections
#
# Dynamic Dependency build overrides
PublishFile $OverrideDir\DynamicDependency-Override.json $NugetDir\runtimes\win10-$Platform\native
