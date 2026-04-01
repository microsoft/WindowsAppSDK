[CmdLetBinding()]
Param(
    [string]$BuildOutputDir,
    [string]$PublishDir,
    [string]$NugetDir,
    [string]$Platform,
    [string]$Configuration,
    [switch]$PublishAppxFiles=$false
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = 'Stop'

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

PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\Microsoft.WindowsAppRuntime.dll $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\Microsoft.WindowsAppRuntime.pdb $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\Microsoft.WindowsAppRuntime.lib $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\Microsoft.WindowsAppRuntime.pri $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_UniversalBGTaskDLL\Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.dll $FullPublishDir\Microsoft.Windows.ApplicationModel.Background.UniversalBGTask\
PublishFile $FullBuildOutput\WindowsAppRuntime_UniversalBGTaskDLL\Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.pdb $FullPublishDir\Microsoft.Windows.ApplicationModel.Background.UniversalBGTask\
PublishFile $FullBuildOutput\WindowsAppRuntime_UniversalBGTaskDLL\Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.lib $FullPublishDir\Microsoft.Windows.ApplicationModel.Background.UniversalBGTask\
PublishFile $FullBuildOutput\WindowsAppRuntime_UniversalBGTaskDLL\Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.winmd $FullPublishDir\WindowsAppRuntime_UniversalBGTaskDLL\

PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.ApplicationModel.Background.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.ApplicationModel.DynamicDependency.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.ApplicationModel.WindowsAppRuntime.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.AppLifecycle.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.AppNotifications.Builder.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.AppNotifications.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.BadgeNotifications.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.Foundation.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.Management.Deployment.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.Media.Capture.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.Storage.Pickers.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.PushNotifications.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.Security.AccessControl.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Security.Authentication.OAuth.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.Storage.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.System.Power.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.System.winmd $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\decimal.h $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\decimalcppwinrt.h $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\MsixDynamicDependency.h $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\wil_msixdynamicdependency.h $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\Security.AccessControl.h $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\RestartAgent\RestartAgent.exe $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\RestartAgent\RestartAgent.pdb $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\DeploymentAgent\DeploymentAgent.exe $FullPublishDir\Microsoft.WindowsAppRuntime\
PublishFile $FullBuildOutput\DeploymentAgent\DeploymentAgent.pdb $FullPublishDir\Microsoft.WindowsAppRuntime\

#
PublishFile $FullBuildOutput\DynamicDependency.DataStore\DynamicDependency.DataStore.exe $FullPublishDir\DynamicDependency.DataStore\
PublishFile $FullBuildOutput\DynamicDependency.DataStore\DynamicDependency.DataStore.pdb $FullPublishDir\DynamicDependency.DataStore\
PublishFile $FullBuildOutput\DynamicDependency.DataStore.ProxyStub\DynamicDependency.DataStore.ProxyStub.dll $FullPublishDir\DynamicDependency.DataStore\
PublishFile $FullBuildOutput\DynamicDependency.DataStore.ProxyStub\DynamicDependency.DataStore.ProxyStub.pdb $FullPublishDir\DynamicDependency.DataStore\
#
PublishFile $FullBuildOutput\PushNotificationsLongRunningTask\PushNotificationsLongRunningTask.exe $FullPublishDir\PushNotificationsLongRunningTask\
PublishFile $FullBuildOutput\PushNotificationsLongRunningTask\PushNotificationsLongRunningTask.pdb $FullPublishDir\PushNotificationsLongRunningTask\
#
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager\DynamicDependencyLifetimeManager.exe $FullPublishDir\DynamicDependencyLifetimeManager\
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager\DynamicDependencyLifetimeManager.pdb $FullPublishDir\DynamicDependencyLifetimeManager\
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager.ProxyStub\DynamicDependencyLifetimeManager.ProxyStub.dll $FullPublishDir\DynamicDependencyLifetimeManager\
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager.ProxyStub\DynamicDependencyLifetimeManager.ProxyStub.pdb $FullPublishDir\DynamicDependencyLifetimeManager\
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManagerShadow\DynamicDependencyLifetimeManagerShadow.exe $FullPublishDir\DynamicDependencyLifetimeManager\
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManagerShadow\DynamicDependencyLifetimeManagerShadow.pdb $FullPublishDir\DynamicDependencyLifetimeManager\

#
PublishFile $FullBuildOutput\WindowsAppRuntime_BootstrapDLL\Microsoft.WindowsAppRuntime.Bootstrap.dll $FullPublishDir\Microsoft.WindowsAppRuntime.Bootstrap\
PublishFile $FullBuildOutput\WindowsAppRuntime_BootstrapDLL\Microsoft.WindowsAppRuntime.Bootstrap.pdb $FullPublishDir\Microsoft.WindowsAppRuntime.Bootstrap\
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
PublishFile $FullBuildOutput\PushNotificationsLongRunningTask.ProxyStub\PushNotificationsLongRunningTask.ProxyStub.pdb $symbolsOutputDir
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManager\DynamicDependencyLifetimeManager.pdb $symbolsOutputDir
PublishFile $FullBuildOutput\DynamicDependencyLifetimeManagerShadow\DynamicDependencyLifetimeManagerShadow.pdb $symbolsOutputDir
PublishFile $FullBuildOutput\WindowsAppRuntime_BootstrapDLL\Microsoft.WindowsAppRuntime.Bootstrap.pdb $symbolsOutputDir
PublishFile $FullBuildOutput\RestartAgent\RestartAgent.pdb $symbolsOutputDir
PublishFile $FullBuildOutput\DeploymentAgent\DeploymentAgent.pdb $symbolsOutputDir

# Copy files to Full Nuget package (alphabetical by category)
#
# C#/WinRT Projections
PublishFile $FullBuildOutput\Microsoft.Windows.ApplicationModel.Background.Projection\Microsoft.Windows.ApplicationModel.Background.Projection.dll $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.ApplicationModel.Background.Projection\Microsoft.Windows.ApplicationModel.Background.Projection.pdb $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.ApplicationModel.DynamicDependency.Projection\Microsoft.Windows.ApplicationModel.DynamicDependency.Projection.dll $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.ApplicationModel.DynamicDependency.Projection\Microsoft.Windows.ApplicationModel.DynamicDependency.Projection.pdb $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.ApplicationModel.WindowsAppRuntime.Projection\Microsoft.Windows.ApplicationModel.WindowsAppRuntime.Projection.dll $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.ApplicationModel.WindowsAppRuntime.Projection\Microsoft.Windows.ApplicationModel.WindowsAppRuntime.Projection.pdb $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.AppLifecycle.Projection\Microsoft.Windows.AppLifecycle.Projection.dll $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.AppLifecycle.Projection\Microsoft.Windows.AppLifecycle.Projection.pdb $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.AppNotifications.Builder.Projection\Microsoft.Windows.AppNotifications.Builder.Projection.dll $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.AppNotifications.Builder.Projection\Microsoft.Windows.AppNotifications.Builder.Projection.pdb $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.AppNotifications.Projection\Microsoft.Windows.AppNotifications.Projection.dll $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.AppNotifications.Projection\Microsoft.Windows.AppNotifications.Projection.pdb $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.BadgeNotifications.Projection\Microsoft.Windows.BadgeNotifications.Projection.dll $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.BadgeNotifications.Projection\Microsoft.Windows.BadgeNotifications.Projection.pdb $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.Foundation.Projection\Microsoft.Windows.Foundation.Projection.dll $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.Foundation.Projection\Microsoft.Windows.Foundation.Projection.pdb $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.Management.Deployment.Projection\Microsoft.Windows.Management.Deployment.Projection.dll $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.Management.Deployment.Projection\Microsoft.Windows.Management.Deployment.Projection.pdb $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.Media.Capture.Projection\Microsoft.Windows.Media.Capture.Projection.dll $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.Media.Capture.Projection\Microsoft.Windows.Media.Capture.Projection.pdb $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.Storage.Pickers.Projection\Microsoft.Windows.Storage.Pickers.Projection.dll $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.Storage.Pickers.Projection\Microsoft.Windows.Storage.Pickers.Projection.pdb $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.PushNotifications.Projection\Microsoft.Windows.PushNotifications.Projection.dll $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.PushNotifications.Projection\Microsoft.Windows.PushNotifications.Projection.pdb $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.Security.AccessControl.Projection\Microsoft.Windows.Security.AccessControl.Projection.dll $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.Security.AccessControl.Projection\Microsoft.Windows.Security.AccessControl.Projection.pdb $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Security.Authentication.OAuth.Projection\Microsoft.Security.Authentication.OAuth.Projection.dll $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Security.Authentication.OAuth.Projection\Microsoft.Security.Authentication.OAuth.Projection.pdb $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.Storage.Projection\Microsoft.Windows.Storage.Projection.dll $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.Storage.Projection\Microsoft.Windows.Storage.Projection.pdb $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.System.Power.Projection\Microsoft.Windows.System.Power.Projection.dll $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.System.Power.Projection\Microsoft.Windows.System.Power.Projection.pdb $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.System.Projection\Microsoft.Windows.System.Projection.dll $NugetDir\lib\net6.0-windows10.0.17763.0
PublishFile $FullBuildOutput\Microsoft.Windows.System.Projection\Microsoft.Windows.System.Projection.pdb $NugetDir\lib\net6.0-windows10.0.17763.0

# Includes (*.h)
PublishFile $FullBuildOutput\WindowsAppRuntime_BootstrapDLL\MddBootstrap.h $NugetDir\include
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\decimal.h $NugetDir\include
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\decimalcppwinrt.h $NugetDir\include
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\MsixDynamicDependency.h $NugetDir\include
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\wil_msixdynamicdependency.h $NugetDir\include
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\WindowsAppRuntimeInsights.h $NugetDir\include\
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\Security.AccessControl.h $NugetDir\include\
#
# Libraries (*.lib)
PublishFile $FullBuildOutput\WindowsAppRuntime_BootstrapDLL\Microsoft.WindowsAppRuntime.Bootstrap.lib $NugetDir\lib\win10-$Platform
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\Microsoft.WindowsAppRuntime.lib $NugetDir\lib\win10-$Platform
#
# MSIX Framework package - DLLs/EXEs
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\Microsoft.WindowsAppRuntime.dll $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\Microsoft.WindowsAppRuntime.pdb $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\Microsoft.WindowsAppRuntime.pri $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\RestartAgent\RestartAgent.exe $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\RestartAgent\RestartAgent.pdb $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\DeploymentAgent\DeploymentAgent.exe $NugetDir\runtimes\win10-$Platform\native
PublishFile $FullBuildOutput\DeploymentAgent\DeploymentAgent.pdb $NugetDir\runtimes\win10-$Platform\native
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
PublishFile $FullBuildOutput\WindowsAppRuntime_BootstrapDLL\Microsoft.WindowsAppRuntime.Bootstrap.dll $NugetDir\runtimes\win-$Platform\native
PublishFile $FullBuildOutput\WindowsAppRuntime_BootstrapDLL\Microsoft.WindowsAppRuntime.Bootstrap.pdb $NugetDir\runtimes\win-$Platform\native
PublishFile $FullBuildOutput\WindowsAppRuntime_UniversalBGTaskDLL\Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.dll $NugetDir\runtimes\win-$Platform\native
PublishFile $FullBuildOutput\WindowsAppRuntime_UniversalBGTaskDLL\Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.pdb $NugetDir\runtimes\win-$Platform\native
#
# WinMD for UWP apps
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.ApplicationModel.DynamicDependency.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.ApplicationModel.WindowsAppRuntime.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.ApplicationModel.Background.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.AppLifecycle.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.AppNotifications.Builder.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.AppNotifications.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.BadgeNotifications.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.Foundation.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.Management.Deployment.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.Media.Capture.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.Storage.Pickers.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.PushNotifications.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.Security.AccessControl.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Security.Authentication.OAuth.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.Storage.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.System.Power.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\StrippedWinMD\Microsoft.Windows.System.winmd $NugetDir\lib\uap10.0
PublishFile $FullBuildOutput\WindowsAppRuntime_UniversalBGTaskDLL\Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.winmd $NugetDir\lib\uap10.0
#
# Common Auto-Initializer Files
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\WindowsAppRuntimeAutoInitializer.cpp $NugetDir\include
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\WindowsAppRuntimeAutoInitializer.cs $NugetDir\include
#
# Bootstrap Auto-Initializer Files
PublishFile $FullBuildOutput\WindowsAppRuntime_BootstrapDLL\MddBootstrapAutoInitializer.cpp $NugetDir\include
PublishFile $FullBuildOutput\WindowsAppRuntime_BootstrapDLL\MddBootstrapAutoInitializer.cs $NugetDir\include
#
# DeploymentManager Auto-Initializer Files
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\DeploymentManagerAutoInitializer.cpp $NugetDir\include
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\DeploymentManagerAutoInitializer.cs $NugetDir\include
#
# UndockedRegFreeWinRT (URFW) Auto-Initializer Files
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\UndockedRegFreeWinRT-AutoInitializer.cpp $NugetDir\include
PublishFile $FullBuildOutput\WindowsAppRuntime_DLL\UndockedRegFreeWinRT-AutoInitializer.cs $NugetDir\include