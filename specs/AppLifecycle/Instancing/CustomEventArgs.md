Custom Activated Event Args for App Redirection.
===

# Background

Each AppInstance can redirect its activation to another AppInstance and pass in an AppActivatedEventArgs
object via GetActivatedEventArgs.  This works if all you want to do is pass the arguments to
another instance.  This solution does not support the scenario of passing in different arguments because

  1. AppActivatedEventArgs does not have a projected constructor, and
  2. AppActivatedEventArgs can't be modified.

Custom arguments would allow apps to communicate "why" the instance was redirected.  For example
an app could redirect to another instance with the argument "/SafeMode" to tell the new instance
something is wrong and should start in safe mode.

The proposal is
  1. Add a new method `AddCustomArgs(IInspectable args)` That would change the activation kind to
  `UserDefined` and `Data` would be replaced with the passed in args.
  2. Add a new ExtendedActivationKind `UserDefined`
  

# Conceptual pages (How To)

_(This is conceptual documentation that will go to docs.microsoft.com "how to" page)_

A page for App Instancing [exists](https://docs.microsoft.com/windows/apps/windows-app-sdk/applifecycle/applifecycle-instancing).

This can be added to the section [How the Windows App SDK instancing differs from UWP instancing](https://docs.microsoft.com/windows/apps/windows-app-sdk/applifecycle/applifecycle-instancing#how-the-windows-app-sdk-instancing-differs-from-uwp-instancing)

## Passing arguments into the instance redirection target

 * _UWP_: Does not allow arguments to be passed into the activated instance.  To get the activated
    events the activated instance can call [GetActivatedEventArgs](https://docs.microsoft.com/uwp/api/windows.applicationmodel.appinstance.getactivatedeventargs)
 * _Windows App SDK_: Arguments can be passed in my calling [GetActivatedEventArgs](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appinstance.getactivatedeventargs#microsoft-windows-applifecycle-appinstance-getactivatedeventargs).
   `AddCustomArgs` can be called to pass in custom arguments.

# API Pages

_(Each of the following L2 sections correspond to a page that will be on docs.microsoft.com)_

## AppActivationArguments

A page for [AppActivationArguments exists] (https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appactivationarguments).

The following is added to the [Remarks](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appactivationarguments) section.

If an app wants to pass in custom arguments, the app can call the set methods on both `Data` and `Kind`.

## AppActivationArguments.Data

A page for [AppActivationArguments.Data exists](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appactivationarguments.data#microsoft-windows-applifecycle-appactivationarguments-data).

The following would be added to the table in the [Remarks](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.appactivationarguments.data#remarks) section.

|_ActivationKind_|_DataType_                             |
| `UserDefined`  |A custom object that is know to the app|

## Microsoft.Windows.AppLifecycle.ExtendedActivationKind

A page for [Microsoft.Windows.AppLifecycle.ExtendedActivationKind exists](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.extendedactivationkind).

The following would be added to [Fields](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.windows.applifecycle.extendedactivationkind).

|_Name_|_Contract_|_Description_|
|UserDefined| 1   | `Data` consists of a custom object.|


## AppActivationArguments.AddCustomArgs method

This is the class for AppActivationArguments.  The only change is adding AddCustomArgs

Example:

```c#
// rest of the class.

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

Other propsed solutions.
1. Making `Kind` and `Data` settable. Rejected because, if `Data` was only changed and redirect apps might try to cast `Data` to the object defined by `Kind`.
2. Add a new settable property. Rejected because a crash could happen if the object can't be value marshled.
3. Adding a public constructor to `AppActivationArguments`.  This is another good solution and can be swaped with the above solution.
