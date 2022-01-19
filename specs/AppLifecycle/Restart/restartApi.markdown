# Restart API

# Contents

- [Restart API](#restart-api)
- [Contents](#contents)
- [Background](#background)
  - [Purpose](#purpose)
- [API](#api)
  - [Existing API](#existing-api)
    - [Summary](#summary)
  - [Existing API Details](#existing-api-details)
    - [Existing API](#existing-api-1)
  - [New API Details](#new-api-details)
    - [New API](#new-api)
    - [Description](#description)
    - [Mechanism](#mechanism)
    - [Examples](#examples)

# Background

This spec addresses the **Restart APIs** in the AppInstance component. At a high-level, Win32 apps
can register with the OS to restart in update/hang/reboot scenarios but cannot initiate an explicit
restart with specific arguments/state. This applies to packaged (Desktop Bridge) and unpackaged
apps. This API will address these gaps and provide the ability for any Win32 app to restart
immediately.

## Purpose

The goal of this feature is the new function: **Restart**, which will enable any packaged or
unpackaged Win32 app (including Console, WinMain, Windows Forms, WPFI) to terminate and restart
itself on command, and to provide an arbitrary command-line string for the restarted instance. 

This behavior (restarting an app immediately) is not currently available to Win32 applications. This
new method will fill the gap for Win32 applications and align with CoreApplication's existing
``CoreApplication.RequestRestartAsync``.

# API

## Existing API

1.  **Restart-me-now**. CoreApplication exposes the
    [RequestRestartAsync](https://docs.microsoft.com/en-us/uwp/api/windows.applicationmodel.core.coreapplication.requestrestartasync?view=winrt-18362)
    method, which allows an app to terminate and restart itself, and to provide an arbitrary
    command-line string for the restarted instance.

2.  **Restart-me-after-termination**. The Win32 API
    [RegisterApplicationRestart](https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-registerapplicationrestart)
    enables an app to register itself to be restarted after termination, and to provide an arbitrary
    command-line string for the restarted instance. The reasons for termination include app crash or
    hang, app update, or system update. There's also a matching
    [UnregisterApplicationRestart](https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-unregisterapplicationrestart)
    API.

There are 2 related Win32 APIs that focus on recovery prior to restart:

1.  **Let-me-do-something-before-termination**. An app can call
    [RegisterApplicationRecoveryCallback](https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-registerapplicationrecoverycallback)
    to register a callback for the system to call before terminating the app. If an application
    encounters an unhandled exception or becomes unresponsive, Windows Error Reporting (WER) calls
    the specified recovery callback, where the app can save state information. The system pings the
    app every n seconds to make sure that it hasn't hung in its callback. The app can specify the
    ping interval when it registers the callback. In its recovery callback, the app can call
    RegisterApplicationRestart a second time, to update the command-line.

2.  **Recovery-in-progress**. While the app is doing work in its recovery callback, the app must
    periodically call
    [ApplicationRecoveryInProgress](https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-applicationrecoveryinprogress)
    \-- if it doesn't call within the registered ping interval, WER will terminate the process.

### Summary

For Win32 apps (packaged or unpackaged):

- Applicable restart mechanism: **RegisterApplicationRestart** for OS + app update/restart/crash
  scenarios
- Gap: Apps can register with the OS to restart in specific app/OS states, but cannot initiate a
  restart from a healthy state


## Existing API Details

### Existing API

```cpp
HRESULT RegisterApplicationRestart(PCWSTR pwzCommandline, DWORD dwFlags)
```
Registers an app for restart. More details on the [MSDN
page](https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-registerapplicationrestart).

```cpp
HRESULT UnregisterApplicationRestart()
```
Unregisters the app for restart, where the app had previously called RegisterApplicationRestart.
More details on the [MSDN
page](https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-unregisterapplicationrestart).

```cpp
public static IAsyncOperation<AppRestartFailureReason> RequestRestartAsync(
string launchArguments)
```
Static function in CoreApplication. Requests immediate termination and restart. More details on the
[MSDN
page](https://docs.microsoft.com/en-us/uwp/api/windows.applicationmodel.core.coreapplication.requestrestartasync?view=winrt-22000).

```cpp
public enum AppRestartFailureReason
```
An existing enum with the following values:

- 0: RestartPending - a restart is already in progress.
- 1: NotInForeground - an app must be visible and in the foreground when it calls the restart API.
- 2: InvalidUser - could not restart for the specified user.
- 3: Other - unspecified failure.

```cpp
class LaunchActivatedEventArg
```
	
Relevant Properties:

- Arguments: gets the arguments that are passed to the app during its launch activation.
- Kind: Gets the reason that this app is being activated. This is of type enum ActivationKind
- PreviousExecutionState: Gets the execution state of the app before this activation.

## New API Details

### New API

```c#
static  AppRestartFailureReason Restart(String arguments)
```

```c#
namespace Microsoft.Windows.AppLifecycle
{
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
    };

    runtimeclass AppActivationArguments
    {
        ExtendedActivationKind Kind { get; };
        IInspectable Data{ get; };
    };

    runtimeclass AppInstance
    {
        static AppInstance GetCurrent();
        static Windows.Foundation.Collections.IVector<AppInstance> GetInstances();
        static AppInstance FindOrRegisterForKey(String key);
        
        // This is the new method exposed by this feature
        static Windows.ApplicationModel.Core.AppRestartFailureReason Restart(String arguments);

        void UnregisterKey();
        Windows.Foundation.IAsyncAction RedirectActivationToAsync(Microsoft.Windows.AppLifecycle.AppActivationArguments args);
        Microsoft.Windows.AppLifecycle.AppActivationArguments GetActivatedEventArgs();
        event Windows.Foundation.EventHandler<Microsoft.Windows.AppLifecycle.AppActivationArguments> Activated;

        String Key{ get; };
        Boolean IsCurrent{ get; };
        UInt32 ProcessId{ get; };
    }

    static runtimeclass ActivationRegistrationManager
    {
        static void RegisterForFileTypeActivation(String[] supportedFileTypes, String logo,
            String displayName, String[] supportedVerbs, String exePath);
        static void RegisterForProtocolActivation(String scheme, String logo, String displayName,
            String exePath);
        static void RegisterForStartupActivation(String taskId, String exePath);

        static void UnregisterForFileTypeActivation(String[] fileTypes, String exePath);
        static void UnregisterForProtocolActivation(String scheme, String exePath);
        static void UnregisterForStartupActivation(String taskId);
    };
}
```
There is no relevant RtCop output for this feature.

### Description

Equivalent to CoreApplication.RequestRestartAsync, except that it is *not* async.

- If the restart fails, but the user subsequently launches the app manually, the app will launch
  normally and no restart arguments will be passed.
- If the app has any in-process background tasks running when it calls this API, those tasks will be
  cancelled in the normal way. Out-of-process background tasks will not be affected.

The restarted instance will be activated with
Windows.ApplicationModel.Activation.LaunchActivatedEventArgs.

- When the app is restarted, LaunchActivatedEventArgs.PreviousExecutionState will have the value
  Terminated so that the app can distinguish between a resume and a restart.
- The elevation state of the app is also maintained in the new restarted process.

If the request to restart is successful, the application will be restarted immediately with no
return value. The user does not have to do anything else/handle a return value in any way.

If the request fails due to a nonfatal reason, a failure reason is returned for why the restart
didn’t successfully complete. This method leverages an existing enum (AppRestartFailureReason) which
has the following relevant return fields.

- InvalidUser: Could not restart for the specified user.
- RestartPending: A restart is already in progress.
- Other: Unspecified failure.

### Mechanism

When an application calls Restart, the mechanism for restart will be as follows:

1. Application calls Restart API.
2. The API calls CreateProcess to launch the agent (a helper EXE in the framework package containing
   the API)
3. The Agent will get the executable path of the application. The Agent will then then terminate the
   application and then call CreateProcess with the application (restarted).

### Examples

```c#
public class App 
{
    // Let's assume this method is run when an app updates assets.
    // The new assets have downloaded and installed, and now the app has to request a restart immediately
    protected void UpdateInstallComplete()
    {
        // Checking if the assets have updated successfully and there are no pending updates
        if (!CheckForUpdate())
        {
            AppRestartFailureReason reason = AppInstance.Restart("/RestartCalled");
            switch (reason)
            {
                case AppRestartFailureReason.RestartPending:
                    // In this case the restart could not be completed because another restart is
                    // pending and we can try to restart again after a period of time.
                    RetryRestartAfterXSeconds();
                    break;
                case AppRestartFailureReason.Other:
                    // In this case, a dialog box will appear informing of an error requesting restart
                    ShowErrorMessage("Something went wrong. Restart was not successful");
                    break;
            }
        }
    } 

    // In this scenario, assume the app encounters an error during initialization.
    // The app displays an error dialog, and after the user clicks OK on the dialog the app must restart.
    // This scenario simply displays logging for these use cases
    protected void HandleInitializationError()
    {   
        // Restart in safe mode to avoid whatever made initialization fail
        AppRestartFailureReason reason = AppInstance.Restart("/safemode");
        switch (reason)
        {
            case AppRestartFailureReason.RestartPending:
                Telemetry.WriteLine("Another restart is currently pending.");
                break;
            case AppRestartFailureReason.InvalidUser:
                Telemetry.WriteLine("Current user is not signed in or not a valid user.");
                break;
            case AppRestartFailureReason.Other:
                Telemetry.WriteLine("Failure restarting.");
                break;
        }
    }
}
```
