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
PublishFile $OverrideDir\PushNotifications-Override.json $FullPublishDir\

PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\Microsoft.WindowsAppRuntime.dll $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\Microsoft.WindowsAppRuntime.lib $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.AppLifecycle.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.AppNotifications.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.PushNotifications.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.ApplicationModel.DynamicDependency.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.ApplicationModel.WindowsAppRuntime.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.System.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.System.Power.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\MsixDynamicDependency.h $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\wil_msixdynamicdependency.h $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\RestartAgent\RestartAgent.exe $FullPublishDir\Microsoft.WindowsAppRuntime\

#
PublishFile $FullBuildOutput\DynamicDependency.DataStore\DynamicDependency.DataStore.exe $FullPublishDir\DynamicDependency.DataStore\
PublishFile $FullBuildOutput\DynamicDependency.DataStore.ProxyStub\DynamicDependency.DataStore.ProxyStub.dll $FullPublishDir\DynamicDependency.DataStore\
#
PublishFile $FullBuildOutput\PushNotificationsLongRunningTask\PushNotificationsLongRunningTask.exe $FullPublishDir\PushNotificationsLongRunningTask\
#
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager\DynamicDependencyLifetimeManager.exe $FullPublishDir\DynamicDependencyLifetimeManager\
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager.ProxyStub\DynamicDependencyLifetimeManager.ProxyStub.dll $FullPublishDir\DynamicDependencyLifetimeManager\
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManagerShadow\DynamicDependencyLifetimeManagerShadow.exe $FullPublishDir\DynamicDependencyLifetimeManager\
#
PublishFile $FullBuildOutput\WindowsAppRuntime_BootstrapDLL\Microsoft.WindowsAppRuntime.Bootstrap.dll $FullPublishDir\Microsoft.WindowsAppRuntime.Bootstrap\
PublishFile $FullBuildOutput\WindowsAppRuntime_BootstrapDLL\Microsoft.WindowsAppRuntime.Bootstrap.lib $FullPublishDir\Microsoft.WindowsAppRuntime.Bootstrap\
PublishFile $FullBuildOutput\WindowsAppRuntime_BootstrapDLL\MddBootstrap.h $FullPublishDir\Microsoft.WindowsAppRuntime.Bootstrap\
PublishFile $FullBuildOutput\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.dll $FullPublishDir\Microsoft.WindowsAppRuntime.Bootstrap\
PublishFile $FullBuildOutput\Microsoft.WindowsAppRuntime.Bootstrap.Net\Microsoft.WindowsAppRuntime.Bootstrap.Net.pdb $FullPublishDir\Microsoft.WindowsAppRuntime.Bootstrap\

PublishFile -IfExists $FullBuildOutput\FrameworkPackage\*.* $FullPublishDir\FrameworkPackage

# Publish pdbs:
$symbolsOutputDir = "$($FullPublishDir)\Symbols\"
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\Microsoft.WindowsAppRuntime.pdb $symbolsOutputDir
PublishFile $FullBuildOutput\DynamicDependency.DataStore\DynamicDependency.DataStore.pdb $symbolsOutputDir
PublishFile $FullBuildOutput\PushNotificationsLongRunningTask\PushNotificationsLongRunningTask.pdb $symbolsOutputDir
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager\DynamicDependencyLifetimeManager.pdb $symbolsOutputDir
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManagerShadow\DynamicDependencyLifetimeManagerShadow.pdb $symbolsOutputDir
PublishFile $FullBuildOutput\WindowsAppRuntime_BootstrapDLL\Microsoft.WindowsAppRuntime.Bootstrap.pdb $symbolsOutputDir
PublishFile $FullBuildOutput\RestartAgent\RestartAgent.pdb $symbolsOutputDir

# Copy files to Full Nuget package (alphabetical by category)
#
# C#/WinRT Projections
PublishFile $FullBuildOutput\Microsoft.Windows.ApplicationModel.DynamicDependency.Projection\Microsoft.Windows.ApplicationModel.DynamicDependency.Projection.dll $NugetDir\lib\net5.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.ApplicationModel.DynamicDependency.Projection\Microsoft.Windows.ApplicationModel.DynamicDependency.Projection.pdb $NugetDir\lib\net5.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.ApplicationModel.WindowsAppRuntime.Projection\Microsoft.Windows.ApplicationModel.WindowsAppRuntime.Projection.dll $NugetDir\lib\net5.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.ApplicationModel.WindowsAppRuntime.Projection\Microsoft.Windows.ApplicationModel.WindowsAppRuntime.Projection.pdb $NugetDir\lib\net5.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.AppLifecycle.Projection\Microsoft.Windows.AppLifecycle.Projection.dll $NugetDir\lib\net5.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.AppLifecycle.Projection\Microsoft.Windows.AppLifecycle.Projection.pdb $NugetDir\lib\net5.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.AppNotifications.Projection\Microsoft.Windows.AppNotifications.Projection.dll $NugetDir\lib\net5.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.AppNotifications.Projection\Microsoft.Windows.AppNotifications.Projection.pdb $NugetDir\lib\net5.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.PushNotifications.Projection\Microsoft.Windows.PushNotifications.Projection.dll $NugetDir\lib\net5.0-windows10.0.17763.0 
PublishFile $FullBuildOutput\Microsoft.Windows.PushNotifications.Projection\Microsoft.Windows.PushNotifications.Projection.pdb $NugetDir\lib\net5.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.System.Projection\Microsoft.Windows.System.Projection.dll $NugetDir\lib\net5.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.System.Projection\Microsoft.Windows.System.Projection.pdb $NugetDir\lib\net5.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.System.Power.Projection\Microsoft.Windows.System.Power.Projection.dll $NugetDir\lib\net5.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.System.Power.Projection\Microsoft.Windows.System.Power.Projection.pdb $NugetDir\lib\net5.0-windows10.0.17763.0
#
# Dynamic Dependency build overrides
PublishFile $OverrideDir\DynamicDependency-Override.json $NugetDir\runtimes\win10-$Platform\native
#
# Push Notifications build overrides
PublishFile $OverrideDir\PushNotifications-Override.json $NugetDir\runtimes\win10-$Platform\native
#
# Includes (*.h)
PublishFile $FullBuildOutput\WindowsAppRuntime_BootstrapDLL\MddBootstrap.h $NugetDir\include
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\MsixDynamicDependency.h $NugetDir\include
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\wil_msixdynamicdependency.h $NugetDir\include
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\WindowsAppRuntimeInsights.h $NugetDir\include\
#
# Libraries (*.lib)
PublishFile $FullBuildOutput\WindowsAppRuntime_BootstrapDLL\Microsoft.WindowsAppRuntime.Bootstrap.lib $NugetDir\lib\win10-$Platform
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\Microsoft.WindowsAppRuntime.lib $NugetDir\lib\win10-$Platform
#
# MSIX Framework package - DLLs/EXEs
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\Microsoft.WindowsAppRuntime.dll $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\Microsoft.WindowsAppRuntime.pdb $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\RestartAgent\RestartAgent.exe $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\RestartAgent\RestartAgent.pdb $NugetDir\runtimes\win10-$Platform\native
#
# MSIX Main package
PublishFile $FullBuildOutput\DynamicDependency.DataStore\DynamicDependency.DataStore.exe $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\DynamicDependency.DataStore\DynamicDependency.DataStore.pdb $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\DynamicDependency.DataStore.ProxyStub\DynamicDependency.DataStore.ProxyStub.dll $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\DynamicDependency.DataStore.ProxyStub\DynamicDependency.DataStore.ProxyStub.pdb $NugetDir\runtimes\win10-$Platform\native
#
# PushNotifications LRP
PublishFile $FullBuildOutput\PushNotificationsLongRunningTask\PushNotificationsLongRunningTask.exe $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\PushNotificationsLongRunningTask\PushNotificationsLongRunningTask.pdb $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\PushNotificationsLongRunningTask.StartupTask\PushNotificationsLongRunningTask.StartupTask.exe $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\PushNotificationsLongRunningTask.StartupTask\PushNotificationsLongRunningTask.StartupTask.pdb $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\PushNotificationsLongRunningTask.ProxyStub\PushNotificationsLongRunningTask.ProxyStub.dll $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\PushNotificationsLongRunningTask.ProxyStub\PushNotificationsLongRunningTask.ProxyStub.pdb $NugetDir\runtimes\win10-$Platform\native
#
# MSIX DDLM package
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager\DynamicDependencyLifetimeManager.exe $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager\DynamicDependencyLifetimeManager.pdb $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManagerShadow\DynamicDependencyLifetimeManagerShadow.exe $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManagerShadow\DynamicDependencyLifetimeManagerShadow.pdb $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager.ProxyStub\DynamicDependencyLifetimeManager.ProxyStub.dll $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager.ProxyStub\DynamicDependencyLifetimeManager.ProxyStub.pdb $NugetDir\runtimes\win10-$Platform\native
#
# Native (not managed, AppLocal / no MSIX)
PublishFile $FullBuildOutput\WindowsAppRuntime_BootstrapDLL\Microsoft.WindowsAppRuntime.Bootstrap.dll $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\WindowsAppRuntime_BootstrapDLL\Microsoft.WindowsAppRuntime.Bootstrap.pdb $NugetDir\runtimes\win10-$Platform\native
#
# Tools
PublishFile $FullBuildOutput\WindowsAppRuntime_MSIXInstallFromPath\WindowsAppRuntime_MSIXInstallFromPath.exe $NugetDir\tools\$Platform
#
# WinMD for UWP apps
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.AppLifecycle.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.AppNotifications.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.PushNotifications.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.ApplicationModel.DynamicDependency.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.ApplicationModel.WindowsAppRuntime.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.System.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.System.Power.winmd $NugetDir\lib\uap10.0
#
# Bootstrap Static Helper Files
PublishFile $FullBuildOutput\WindowsAppRuntime_BootstrapDLL\MddBootstrapAutoInitializer.cs $NugetDir\include
PublishFile $FullBuildOutput\WindowsAppRuntime_BootstrapDLL\MddBootstrapAutoInitializer.cpp $NugetDir\include
#
# Build overrides
PublishFile $OverrideDir\DynamicDependency-Override.json $NugetDir\runtimes\win10-$Platform\native
PublishFile $OverrideDir\PushNotifications-Override.json $NugetDir\runtimes\win10-$Platform\native
