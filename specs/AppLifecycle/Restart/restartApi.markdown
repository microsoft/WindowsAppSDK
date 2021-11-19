# Restart API

# Contents

- [Restart API](#restart-api)
- [Contents](#contents)
- [Background](#background)
  - [Description](#description)
- [API](#api)
  - [Existing API Summary](#existing-api-summary)
  - [Existing API Details](#existing-api-details)
  - [New API Details](#new-api-details)
    - [RequestRestartNow](#requestrestartnow)
  - [Examples and Scenarios](#examples-and-scenarios)
- [Telemetry](#telemetry)

# Background

This spec addresses the **Restart APIs** in the AppLifecycle component. At a high-level, Win32 apps can
register with the OS to restart in update/hang/reboot scenarios but cannot restart immediately on-command 
with specific arguments/state. This applies to packaged (Centennial) and unpackaged apps. This API will address
these gaps and provide the ability for any Win32 app to restart immediately.

## Description

The goal of this feature is the new function: **RequestRestartNow**, which will enable any packaged or unpackaged Win32
app to terminate and restart itself on command, and to provide an arbitrary command-line string for the restarted instance.

# API

## Existing API Summary

1.  **Restart-me-now**. CoreApplication exposes the
    [RequestRestartAsync](https://docs.microsoft.com/en-us/uwp/api/windows.applicationmodel.core.coreapplication.requestrestartasync?view=winrt-18362)
    method, which allows an app to terminate and restart itself, and to
    provide an arbitrary command-line string for the restarted instance.

2.  **Restart-me-after-termination**. The Win32 API
    [RegisterApplicationRestart](https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-registerapplicationrestart)
    enables an app to register itself to be restarted after termination,
    and to provide an arbitrary command-line string for the restarted
    instance. The reasons for termination include app crash or hang, app
    update, or system update. There's also a matching
    [UnregisterApplicationRestart](https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-unregisterapplicationrestart)
    API.

There are 2 related Win32 APIs that focus on recovery prior to restart:

1.  **Let-me-do-something-before-termination**. An app can call
    [RegisterApplicationRecoveryCallback](https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-registerapplicationrecoverycallback)
    to register a callback for the system to call before terminating the
    app. If an application encounters an unhandled exception or becomes
    unresponsive, Windows Error Reporting (WER) calls the specified
    recovery callback, where the app can save state information. The
    system pings the app every n seconds to make sure that it hasn't
    hung in its callback. The app can specify the ping interval when it
    registers the callback. In its recovery callback, the app can call
    RegisterApplicationRestart a second time, to update the
    command-line.

2.  **Recovery-in-progress**. While the app is doing work in its
    recovery callback, the app must periodically call
    [ApplicationRecoveryInProgress](https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-applicationrecoveryinprogress)
    \-- if it doesn't call within the registered ping interval, WER will
    terminate the process.

| App Type                                                            | Applicable Restart Mechanism                                           | Gap                                                                                                                  |
| ------------------------------------------------------------------- | ---------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------- |
| Win32 (unpackaged), Win32/Centennial (packaged), WinUI (Centennial) | RegisterApplicationRestart for OS + app update/restart/crash scenarios | Apps can register with the OS to restart in specific app/OS states, but cannot restart on-command in a healthy state |

## Existing API Details

<table>
<colgroup>
<col style="width: 41%" />
<col style="width: 58%" />
</colgroup>
<thead>
<tr class="header">
<th>Existing API</th>
<th>Details</th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p>HRESULT <strong>RegisterApplicationRestart</strong>(PCWSTR pwzCommandline, DWORD dwFlags);</p></td>
<td><p>The pwzCommandline parameter is passed into the new instance as its command-line arguments string. The dwFlags can be 0 or one or more of the (flags) values:</p>
<ul>
<li>
<p>1: RESTART_NO_CRASH - Do not restart the process if it terminates due to an unhandled exception.</p>
</li>
<li>
<p>2: RESTART_NO_HANG - Do not restart the process if it terminates due to the application not responding.</p>
</li>
<li>
<p>4: RESTART_NO_PATCH - Do not restart the process if it terminates due to the installation of an OS update.</p>
</li>
<li>
<p>8: RESTART_NO_REBOOT - Do not restart the process if the computer is restarted as the result of an OS update.</p>
</li>
</ul></td>
</tr>
<tr class="even">
<td>HRESULT <strong>UnregisterApplicationRestart</strong>();</td>
<td>Unregisters the app for restart, where the app had previously called RegisterApplicationRestart.</td>
</tr>
<tr class="odd">
<td>public static IAsyncOperation&lt;AppRestartFailureReason&gt; <strong>RequestRestartAsync</strong>(<br />
string launchArguments);</td>
<td><p>Static function in CoreApplication. Requests immediate termination and restart.</p>
<ul>
<li>
<p>The launchArguments string is passed into the new instance as the Arguments property on LaunchActivatedEventArgs.</p>
</li>
<li>
<p>Also sets LaunchActivatedEventArgs.PreviousExecutionState to Terminated.</p>
</li>
</ul></td>
</tr>
<tr class="even">
<td>public enum <strong>AppRestartFailureReason</strong></td>
<td><ul>
<li>
<p>0: RestartPending - a restart is already in progress.</p>
</li>
<li>
<p>1: NotInForeground - an app must be visible and in the foreground when it calls the restart API.</p>
</li>
<li>
<p>2: InvalidUser - could not restart for the specified user.</p>
</li>
<li>
<p>3: Other - unspecified failure.</p>
</li>
</ul></td>
</tr>
<tr class="odd">
<td>class <strong>LaunchActivatedEventArg</strong></td>
<td><p>Relevant Properties:</p>
<ul>
<li><p>Arguments: gets the arguments that are passed to the app during its launch activation.</p></li>
<li><p>Kind: Gets the reason that this app is being activated. This is of type enum ActivationKind</p></li>
</ul>
<p>PreviousExecutionState: Gets the execution state of the app before this activation.</p></td>
</tr>
</tbody>
</table>

## New API Details

### RequestRestartNow

<table>
<colgroup>
<col style="width: 41%" />
<col style="width: 53%" />
<col style="width: 5%" />
</colgroup>
<thead>
<tr class="header">
<th>New API </th>
<th>Description</th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>static AppRestartFailureReason <strong>RequestRestartNow</strong>(string restartArguments)</td>
<td><p>Equivalent to CoreApplication.RequestRestartAsync, except that it is <em>not</em> async.
<ul>
<li>If the restart fails, but the user subsequently launches the app manually, the app will launch normally and no restart arguments will be passed. </li>
<li>If the app has any in-process background tasks running when it calls this API, those tasks will be cancelled in the normal way. Out-of-process background tasks will not be affected. </li>
</ul>
 The restarted instance will be activated with Windows.ApplicationModel.Activation.LaunchActivatedEventArgs.</p>
 <ul>
<li>When the app is restarted, LaunchActivatedEventArgs.PreviousExecutionState will have the value Terminated so that the app can distinguish between a resume and a restart. </li>
</ul>
<p>Returns a failure reason for why the restart didn’t successfully complete (AppRestartFailureReason).
<ul>
<li>This API does not require for the app to be in foreground, and so AppRestartFailureReason::NotInForeground will never be returned </li>
</ul>
</p></td>
</tr>
</tbody>
</table>

When an application calls RequestRestartNow, the mechanism for restart will be as follows:
1. Application calls RequestRestartNow API.
2. The API will CreateProcess with the Agent (a helper EXE in the framework package containing the API) and will then wait for an an acknowledgment (ACK) from the Agent.
3. The Agent will get the executable path of the application and signal an ACK to the API. The Agent will then wait for termination of the application.
4. The API will terminate the application.
5. The Agent will CreateProcess with the application (restarted).

## Examples and Scenarios

```c#
public class App {
       // Let's assume this method is run when an app updates assets.
       // The new assets have downloaded and installed, and now the app has to request a restart immediately
       protected void updateInstallComplete(){
           // Checking if the assets have updated successfully and there are no pending updates
           if (!CheckForUpdate()){
               AppRestartFailureReason result = AppLifecycle::RequestRestartNow("args for new instance");
               switch (result){
                    case AppRestartFailureReason::RestartPending:
                        // An example of how to handle this case is updating a progress bar to the user
                        // indicating immediate restart
                        UpdateProgressBar();
                        break;
                    case AppRestartFailureReason::Other:
                        // In this case, a dialog box will appear informing of an error requesting restart
                        ShowErrorMessage();
                        break;
               }
           }
       } 

    // In this scenario, assume the app encounters an error during initialization.
    // The app displays an error dialogue, and after the user clicks OK on the dialog the app must restart immediately.
    // This scenario simply displays logging for these use cases
    protected void handleInitializationError(){
        AppRestartFailureReason result = AppLifecycle::RequestRestartNow("args for new instance");
        switch (result){
            case AppRestartFailureReason::RestartPending:
                Telemetry::WriteLine("Restart request successful.");
                break;
            case AppRestartFailureReason::Other:
                Telemetry::WriteLine("Failure restarting.");
                break;
           }
    }
}
```

# Telemetry

This section explores the telemetry needs for the Restart feature in
four dimensions – Usage, Reliability, Performance and Failure
Investigation. The telemetry will include the metadata that are needed
not only for measuring quality but also for helping with investigations
of failures. Following is the event which can be used to capture
telemetry information:

Event Name: **AppRestart**

| Metadata                | Description                                                                                       | Data type |
| ----------------------- | ------------------------------------------------------------------------------------------------- | --------- |
| AppRestartFailureReason | Reason an app restart failed. This will be collected when an app requests a restart now but fails | Enum      |
| AppName                 | Name of the app which restarted                                                                   | String    |
| AppType                 | UWP App or Centennial App or Win32 app                                                            | String    |
