param([Parameter(Mandatory=$true)][string]$arch, [Parameter(Mandatory=$true)][string]$config, [Parameter(Mandatory=$true)][string]$task)

$currentLocation = Get-Location
$packagePath = "$currentLocation\BuildOutput\$config\$arch\"

if(!$task.CompareTo("i"))
{
	write-host "installing packages"
	add-appxpackage "$packagePath\Microsoft.WindowsAppRuntime.Framework\Microsoft.WindowsAppRuntime.Framework.msix"
	add-appxpackage "$packagePath\DynamicDependency.DataStore.Msix\DynamicDependency.DataStore.msix"
	add-appxpackage "$packagePath\DynamicDependencyLifetimeManager.Msix\DynamicDependencyLifetimeManager.msix"
	add-appxpackage "$packagePath\PushNotificationsLongRunningTask.Msix\PushNotificationsLongRunningTask.msix"
}
elseif(!$task.CompareTo("u"))
{
	taskkill /IM PushNotificationsLongRunningTask.exe /F
	taskkill /IM DynamicDependency.DataStore.exe /F
	taskkill /IM DynamicDependencyLifetimeManager.exe /F

	write-host "uninstalling packages"
	remove-appxpackage "WindowsAppRuntime.Test.DDLM-4.1.1967.333-$($arch)_4.1.1967.333_$($arch)__8wekyb3d8bbwe"
	remove-appxpackage "WindowsAppRuntime.Test.DynDep.DataStore_4.1.1967.333_neutral__8wekyb3d8bbwe"
	remove-appxpackage "WindowsAppRuntime.Test.PushNotificationsTask_4.1.1967.333_neutral__8wekyb3d8bbwe"
	remove-appxpackage "Microsoft.WindowsAppRuntime.Framework_4.1.1967.333_neutral__8wekyb3d8bbwe"
}
else
{
	write-host "invalid input"
}


