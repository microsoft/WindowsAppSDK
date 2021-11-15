# Reunion Restart API Spec

## Contents

[1. Overview](#overview)
- [Reunion Restart API components](#reunion-restart-api-components)

[2. API](#api)

- [Existing API Summary](#existing-api-summary)

- [All Existing Scenarios](#all-existing-scenarios)

- [Existing API Details](#existing-api-details)

- [New API Details](#new-api-details)

- [API Sample Code](#api-sample-code)

[3. Telemetry](##restartApi\telemetry)

[4. Resources](#resources)

## Overview 

This spec addresses the **Restart APIs** in the AppLifecycle component. The main
goals of this specific API are the following:

Addressing the gaps that exist today: at a high-level, Win32 apps can
register with the OS to restart in update/hang/reboot scenarios but
cannot restart immediately on-command with specific arguments/state. This applies to packaged (Centennial) and unpackaged apps. These are the gaps we need to address.

### Reunion Restart API components 

1.  Expose a new function: **RequestRestartNow** function to enable any packaged or unpackaged Win32
    app to terminate and restart itself on command, and to provide an
    arbitrary command-line string for the restarted instance.


## API

### Existing API Summary

1.  **Restart-me-now**. UWP CoreApplication exposes the
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
    -- if it doesn't call within the registered ping interval, WER will
    terminate the process.


<table>
<colgroup>
<col style="width: 24%" />
<col style="width: 45%" />
<col style="width: 30%" />
</colgroup>
<thead>
<tr class="header">
<th>App Type</th>
<th>Applicable Restart Mechanism</th>
<th>Gap</th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>Win32 (unpackaged)</td>
<td><ul>
<li><p>RegisterApplicationRestart for OS + app update/restart/crash scenarios </p></li>
</ul></td>
<td><ul>
<li><p>Apps can register with the OS to restart in specific app/OS states, but cannot restart on-command in a healthy state </p></li>
</ul></td>
</tr>
<tr class="even">
<td>Win32/Centennial (packaged)</td>
<td><ul>
<li><p>RegisterApplicationRestart for OS + app update/restart/crash scenarios </p></li>
</ul></td>
<td><ul>
<li><p>Apps can register with the OS to restart in specific app/OS states, but cannot restart on-command in a healthy state <br />
 </p></li>
</ul></td>
</tr>
<tr class="odd">
<td>UWP</td>
<td><ul>
<li>
<p>RequestRestartAsync for restarting on demand in a healthy state </p>
</li>
</ul>
<ul>
<li><p>Automatically registered to restart in restart scenario by Explorer/shell using RestartUwpApp </p></li>
</ul></td>
<td><ul>
<li>
<p>Apps can restart on-command asynchronously when healthy/active but do not have the ability to ensure restart in app crash/hang scenarios </p>
</li>
</ul>
</tr>
<tr class="even">
<td>WinUI (UWP)</td>
<td><ul>
<li>
<p>RequestRestartAsync for restarting on demand in a healthy state </p>
</li>
</ul>
<ul>
<li><p>Automatically registered to restart in restart scenario by Explorer/shell using RestartUwpApp </p></li>
</ul></td>
<td><ul>
<li>
<p>Apps can restart on-command asynchronously when healthy/active but do not have the ability to ensure restart in app crash/hang scenarios </p>
</li>
</ul>
</td>
</tr>
<tr class="odd">
<td>WinUI (Centennial)</td>
<td><ul>
<li><p>RegisterApplicationRestart for OS + app update/restart/crash scenarios </p></li>
</ul></td>
<td><ul>
<li><p>Apps can register with the OS to restart in specific app/OS states, but cannot restart on-command in a healthy state </p></li>
</ul></td>
</tr>
</tbody>
</table>

## Existing API Details

<table>
<colgroup>
<col style="width: 41%" />
<col style="width: 58%" />
</colgroup>
<thead>
<tr class="header">
<th>Existing API for Win32 Apps</th>
<th>Details</th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p>HRESULT <strong>RegisterApplicationRestart</strong>(</p>
<p>PCWSTR pwzCommandline,</p>
<p>DWORD dwFlags);</p></td>
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
</tbody>
</table>

<table>
<colgroup>
<col style="width: 41%" />
<col style="width: 58%" />
</colgroup>
<thead>
<tr class="header">
<th>Existing API for UWP Apps</th>
<th>Details</th>
</tr>
</thead>
<tbody>
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
<td>void <strong>RestartUwpApp</strong>(const wchar_t* const appUserModelId)</td>
<td>Internal-only function in shell/explorer added as of 20H1 allowing UWP apps to be restarted in a minimized state</td>
</tr>
<tr class="even">
<td>public enum <strong>AppRestartFailureReason</strong></td>
<td><p>Enum which will be used in the new API detailed below to indicate the reason for a failed restart <em>now.</em></p>
<ul>
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

### New API Details

#### RequestRestartNow

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
<th>Priority</th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>static AppRestartFailureReason RequestRestartNow(string restartArguments)</td>
<td><p>Equivalent to CoreApplication.RequestRestartAsync, except that it is <em>not</em> async.
<ul>
<li>The app must be visible and foreground when it calls this API.</li>
<li>If the restart fails, but the user subsequently launches the app manually, the app will launch normally and no restart arguments will be passed. </li>
<li>If the app has any in-process background tasks running when it calls this API, those tasks will be cancelled in the normal way. Out-of-process background tasks will not be affected. </li>
</ul>
 The restarted instance will be activated with Windows.ApplicationModel.Activation.LaunchActivatedEventArgs.</p>
 <ul>
<li>When the app is restarted, LaunchActivatedEventArgs.PreviousExecutionState will have the value Terminated so that the app can distinguish between a resume and a restart. </li>
</ul>
<p>Returns a failure reason for why the restart didn’t successfully complete.</p></td>
<td>P1</td>
</tr>
</tbody>
</table>

### API Sample Code

### RequestRestartNow Sample

```c#
public class App {
       // Let's assume this method is run when an app updates assets.
       // The new assets have downloaded and installed, and now the app has to restart immediately
       protected void updateInstallComplete(){
           // code here that checks the app update has installed

           WCHAR buffer\[1024\]; 
           AppRestartFailureReason result = AppLifecycle::RequestRestartNow("args for new instance");

           switch (result){
                case AppRestartFailureReason::RestartPending:
                    Telemetry::WriteLine("Restart request successful.");
                    break;
                case AppRestartFailureReason::NotInForeground:
                    wcscpy_s(buffer, L"App must be in the foreground to request restart.");
                    break;
                case AppRestartFailureReason::InvalidUser:
                    wcscpy_s(buffer, L"Cannot restart for this user.");
                    break;
                case AppRestartFailureReason::Other:
                    wcscpy_s(buffer, L"Unknown failure.");
                    break;
           }
       }               
}
```

## Telemetry 

This section explores the telemetry needs for the Restart feature in
four dimensions – Usage, Reliability, Performance and Failure
Investigation. The telemetry will include the metadata that are needed
not only for measuring quality but also for helping with investigations
of failures. Following is the event which can be used to capture
telemetry information:

Event Name: **AppRestart**

| Metadata                | Description                                                                                       | Data type |
|-------------------------|---------------------------------------------------------------------------------------------------|-----------|
| AppRestartFailureReason | Reason an app restart failed. This will be collected when an app requests a restart now but fails | Enum      |
| AppName                 | Name of the app which restarted                                                                   | String    |
| AppType                 | UWP App or Centennial App or Win32 app                                                            | String    |
