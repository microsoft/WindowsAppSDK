Custom Activated Event Args for App Redirection.
===

# Background

Each AppInstance can redirect its activation to another AppInstance and pass in an [AppActivationArguments](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appactivationarguments)
object obtained [GetActivatedEventArgs](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appinstance.getactivatedeventargs).  This works if all you want to do is pass the arguments to
another instance.  However, the arguments can't be changed.  This is because

  1. [AppActivationArguments](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appactivationarguments) does not have a projected constructor, and
  2. [AppActivationArguments](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appactivationarguments) can't be modified.

Custom arguments would allow apps to communicate "why" the instance was redirected.  For example
an app could redirect to another instance with the argument "/SafeMode" to tell the new instance
something is wrong and should start in safe mode.

The proposal is
  1. Add a new method `AddCustomArgs(IInspectable newArgs)` That would change the [activation kind](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appactivationarguments.kind#microsoft-windows-applifecycle-appactivationarguments-kind) to
  `UserDefined` and [Data](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appactivationarguments.data#microsoft-windows-applifecycle-appactivationarguments-data) would be replaced with the passed in `newArgs`.
  2. Add a new ExtendedActivationKind `UserDefined`
  

# Conceptual pages (How To)
A page for [App Instancing](https://docs.microsoft.com/windows/apps/windows-app-sdk/applifecycle/applifecycle-instancing) exists.

The below section can be added to the section [How the Windows App SDK instancing differs from UWP instancing](https://docs.microsoft.com/windows/apps/windows-app-sdk/applifecycle/applifecycle-instancing#how-the-windows-app-sdk-instancing-differs-from-uwp-instancing)

## Passing arguments into the instance redirection target

 * _UWP_: Does not allow arguments to be passed into the activated instance.  To get the activated
    events call [GetActivatedEventArgs](https://docs.microsoft.com/uwp/api/windows.applicationmodel.appinstance.getactivatedeventargs) 
 * _Windows App SDK_: Custom arguments can be passed into the new instance by first calling [GetActivatedEventArgs](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appinstance.getactivatedeventargs#microsoft-windows-applifecycle-appinstance-getactivatedeventargs)
   then `AddCustomArgs` on the returned object from [GetActivatedEventArgs](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appinstance.getactivatedeventargs#microsoft-windows-applifecycle-appinstance-getactivatedeventargs).
   The modified [AppActivationArguments](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appactivationarguments) object can be passed into [RedirectActivationToAsync](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appinstance.redirectactivationtoasync#microsoft-windows-applifecycle-appinstance-redirectactivationtoasync(microsoft-windows-applifecycle-appactivationarguments)).

# API Pages

## AppActivationArguments

A page for [AppActivationArguments](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appactivationarguments) exists.

The following is added to the [Remarks](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appactivationarguments#remarks) section.

If an app wants to pass in custom arguments, the app can call `AddCustomArgs(IInspectable newArgs)` on the [AppActivationArguments](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appactivationarguments)
object returned from [GetActivatedEventArgs](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appinstance.getactivatedeventargs).

## AppActivationArguments.Data

A page for [AppActivationArguments.Data](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appactivationarguments.data#microsoft-windows-applifecycle-appactivationarguments-data) exists.

The following would be added to the table in the [Remarks](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appactivationarguments.data#remarks) section.

|_ActivationKind_|_DataType_                             |
|----------------|---------------------------------------|
| `UserDefined`  |A custom object that is known to the app|

## Microsoft.Windows.AppLifecycle.ExtendedActivationKind

A page for [Microsoft.Windows.AppLifecycle.ExtendedActivationKind](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.extendedactivationkind) exists.

The following would be added to [Fields](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.extendedactivationkind).

|_Name_|_Contract_|_Description_                       |
|------|----------|------------------------------------|
|UserDefined| 1   | `Data` consists of a custom object.|


## AppActivationArguments.AddCustomArgs method

This is the class for [AppActivationArguments](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appactivationarguments).  The only change is adding AddCustomArgs

Example:

```c#
// The rest of AppActivationArguments here.

public void AddCustomArgs(IInspectable newArguments) 
{
	m_Kind = Microsoft.Windows.AppLifecycle.ExtendedActivationKind.UserDefined;
	m_Data = newArguments;
}
```

# API Details

```c# (but really MIDL3)
namespace Microsoft.Windows.AppLifecycle
{
    [contractversion(3)]
    apicontract AppLifecycleContract {};

    [contract(AppLifecycleContract, 1)]
    enum ExtendedActivationKind
    {
        Launch = 0,
        Search,
        ShareTarget,
        File,
        Protocol,
        FileOpenPicker,
        FileSavePicker,
        CachedFileUpdater,
        ContactPicker,
        Device,
        PrintTaskSettings,
        CameraSettings,
        RestrictedLaunch,
        AppointmentsProvider,
        Contact,
        LockScreenCall,
        VoiceCommand,
        LockScreen,
        PickerReturned = 1000,
        WalletAction,
        PickFileContinuation,
        PickSaveFileContinuation,
        PickFolderContinuation,
        WebAuthenticationBrokerContinuation,
        WebAccountProvider,
        ComponentUI,
        ProtocolForResults = 1009,
        ToastNotification,
        Print3DWorkflow,
        DialReceiver,
        DevicePairing,
        UserDataAccountsProvider,
        FilePickerExperience,
        LockScreenComponent,
        ContactPanel,
        PrintWorkflowForegroundTask,
        GameUIProvider,
        StartupTask,
        CommandLineLaunch,
        BarcodeScannerProvider,
        PrintSupportJobUI,
        PrintSupportSettingsUI,
        PhoneCallActivation,
        VpnForeground,
        // NOTE: Values below 5000 are designated for the platform.  The above list is kept in sync with
        // Windows.ApplicationModel.Activation.ActivationKind.

        Push = 5000,

        [contract(AppLifecycleContract, 2)]
        AppNotification,
		
        [contract(AppLifecycleContract, 3)]
        UserDefined,
    };

    [contract(AppLifecycleContract, 1)]
    runtimeclass AppActivationArguments
    {
        ExtendedActivationKind Kind { get; };
        IInspectable Data{ get; };
		
        [contract(AppLifecycleContract, 3)]
        void AddCustomArgs(IInspectable newArguments);
    };
}
```

# Appendix

The open issue for this is [here](https://github.com/microsoft/WindowsAppSDK/discussions/2568).

Other proposed solutions.
1. Making `Kind` and `Data` settable. Rejected because, if `Data` was only changed and redirect apps might try to cast `Data` to the object defined by `Kind`.
2. Add a new settable property. Rejected because a crash could happen if the object can't be value marshaled.
3. Adding a public constructor to `AppActivationArguments`.  This is another good solution and can be swapped with the above solution.
