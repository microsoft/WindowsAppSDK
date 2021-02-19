# Push Notifications in Project Reunion SDK

# Background

The Windows Push Notification Services (WNS) enable third-party developers to send toast, tile, badge, and raw updates from their own cloud service. This provides a mechanism to deliver new updates to your users in a power-efficient and dependable way. For example, the skype app service can triggering an incoming call toast by Pushing a Payload to the WNS service. Push is generally used for time critical events that require immediate user/developer action. 

* [The Push notification WinRT Public APIs](https://docs.microsoft.com/en-us/uwp/api/windows.networking.pushnotifications?view=winrt-19041)
  Defines the classes that encapsulate Push notifications. (UWP and Win32)
* [The Windows Push Notification Services (WNS) Overview](https://docs.microsoft.com/en-us/windows/uwp/design/shell/tiles-and-notifications/windows-push-notification-services--wns--overview)

## Push Flow:
In order to subscribe to Push Notifications, an app first needs to request a Push Channel with WPN client which is essentially an Http Endpoint that it can post notifications to. 
Channel Registration Process:
* App developer registers his application in Dev Centre portal and gets an AppSID and client secret tied to his Application’s identity
* The application is downloaded and installed from the Microsoft Store using MSIX
* During installation, MSIX registers the application’s identity with WPN client (AppUserModelId and PFN) in the WPN database.
* When the app requests a channel, WPN client looks up the PFN from the WPN database and sends it to WNS as part of the channel request payload.
* WNS encodes the PFN (or AppSID in this case derived from PFN) and a randomly generated channelId in the channel URL and sends it back down to the client.
* The client sends the channel URL to the app as part of the channel request in step 4)
* The app sends the channel URL to it’s app server and saves it.

The next step involves the application actually Pushing down a payload from the App Service to the device:
* The App Server requests an access token from MSA using the AppSID and client secret retrieved from the developer registration process with dev center.
* MSA returns a token to the app server
* App server posts a notification’s to WNS’s NW with the channel url retrieved from WPN client and the access token in step 2)
* NW verifies the app token against AppSID extracted from the channel URL
* NW sends the Post request to WNS’s NN which contains the persistent socket with the client
* WNS’s NN maps the channel URL to the correct deviceId by decoding the deviceId from the channel URL and sends an NFY to the correct client.
* WPN client receives the NFY and processes the channelId in the payload to retrieve the correct AppId from the WPN database.
* WPN client routes the notification to the appropriate app. If it needs to interface with the App, it uses BI, callbacks or WNF depending on the App Registration. If the payload is a toast, it gets directly routed to the Shell.

## The problems today

**Portal Registration**: The entire Registration flow for Push is dependent on registering an app in the partner centre portal by [associating an app with the Windows Store](https://docs.microsoft.com/en-us/azure/notification-hubs/notification-hubs-windows-store-dotnet-get-started-wns-push-notification). As a result, non-store provisioned apps like Win32 cannot avail of this feature even if they want to.

**Client Registration**: Unpackaged 3rd party applications do not have a way today to register with the client because the API is private. The only way to get an implicit client side registration is to package the app as an MSIX or SSP which may not satisfy 3rd party requirements.

**Push Channels**: All the Push APIs are dependent on the caller app having an identity at the minimal. However, even packaged Win32 apps that have an identity cannot use our Public APIs to subscribe to Push Channels because they may not be store provisioned. Sideloaded UWPs that aren't store distributed have exactly the same problem.

**Activation**: When the native OS client receives a Push payload over the WNS socket, it signals the Background Infrastructure to trigger a task and run some code on the app's behalf. This flow is undefined for Win32 apps that need to use Push today mainly because of the Registration and API limitations described above. 

**Channel Request Issues**: The channel APIs exposed today can throw exceptions via their Projections in the case of errors. Some errors can be critical errors while others are retryable errors. The msdn guidance for retrying isn't very clear and has been the root cause of multiple app bugs in the past. We want to abstract away the details of channel retry operations for developers in reunion.

# Description

At a high level, we need to provide a way for all Win32 applications to subscribe to and receive Push notifications irrespective of their app type. This includes unpackaged apps and packaged win32 (MSIX, Sparse Signed Packages). Moreover, all Push scenarios should adher to OS resource management policies like Power Saver, Network Attribution, Enterprise group policies etc. The Reunion Push component will abstract away the complexities of dealing with WNS channel registrations and Push related activations as much as possible freeing the developer to focus on other app related challenges. 

We will priorirtize the following feature set for Reunion:
* Supporting raw push for Packaged Win32(MSIX)
* Supporting raw push for Unpackaged Win32.
* Supporting Visual Cloud Toasts for packaged Win32 apps.
* Supporting Visual Cloud Toasts for unpackaged Win32 apps.

A Portal Registration flow through [AAD (Azure Active Directory)](https://docs.microsoft.com/en-us/azure/active-directory/develop/quickstart-register-app) will also be defined that decouples the dependence of the Push Flow with the Partner Centre Portal. 
The following are the main steps in the Push flow with AAD:
* The developer will first obtain a Remote Identifer GUID and a client secret as part of this Portal Registration flow. This is a one time operation by the developer to provision an app. 
* When requesting a channel using client Reunion APIs, the developer will pass in a remoteId and the WNS service will return a specially encoded Channel URL with that Remote Identifier. 
* When the application service Pushes a notification down to the client, it will retrieve an access token with AAD using the client secret provisioned above. 
* The application service will then pass that access token along with the payload in a Http POST operation to the channel URL. 
* WNS will ensure that the payload is ultimately delivered to the app residing on the client device.

Phase 1 (Reunion Preview):
Our Push APIs will only support MSIX apps.

Phase 2 (Reunion V1):
Our Push APIs will add support for Unpackaged Win32.

# Examples

## Registration of the Push Activator for Win32 (Inproc)
If a Win32 app needs to subscribe to Push triggers inproc, the code in Main would follow the pattern below:
* The Registration will take in a CLSID of the COM server as part of the Activator setup. The registration API will simply be a thin wrapper around the BackgroundInfra WinRT APIs and abstract away the COM details from the developer.
* The app will next query the ActivationEventArgs to check if the ActivationKind is of type Push
* If the Activation is Push, the app will retrieve the IActivatedEventArgs and retrieve the Push payload from it. Care needs to be taken to Take a Deferral and Release the Deferral while processing the payload for Power Management compliance.
* If the Activation is Foreground, the app will do 2 things:
* * It will subscribe to a Foreground In-memory Push event
* * It will request a Push Channel Asynchronously with an implementation of Progress and Completed event handler. 

```cpp
int main()
{
    // Always Register the Push trigger as the first step: It sets up the Inproc COM server for subsequent Push operations
    std::wstring activatorGuid = L"{B8E58D9D-A229-44A8-B923-2823C3791BCE}";
    InProcActivatorDetails details(activatorGuid);
    PushNotificationChannelManager::RegisterPushNotificationActivator(details);

    // Check to see if the WinMain activation is due to a Push Activator
    auto args = AppLifecycle2::GetActivatedEventArgs();
    auto kind = args.Kind2();

    if (kind == ActivationKindExtension::Push)
    {
        auto activatedEventArgs = args.ActivatedArgs();
        auto pushArgs = args.as<IPushNotificationActivatedEventArgs>();

        // Call TakeDeferral to ensure that code runs in low power
        pushArgs.GetDeferral();

        auto payload = pushArgs.Payload();

        // Do stuff to process the raw payload

        // Call CompleteDeferral as good practise: Needed mainly for low power usage
        pushArgs.CompleteDeferral();
    }
    else if (kind == ActivationKindExtension::Launch) // This indicates that the app is launching in the foreground
    {
        // Register an event to Intercept Push payloads
        auto eventToken = details.PushActivated([](const auto&, PushNotificationActivatedEventArgs args)
        {
                // Call TakeDeferral to ensure that code runs in low power
                args.GetDeferral();

                auto payload = args.Payload();

                // Do stuff to process the raw payload

                // Call CompleteDeferral as good practise: Needed mainly for low power usage
                args.CompleteDeferral();
        });

        auto remoteId = L"{5AB838FB-B64B-4FCD-B25F-B09781D56DD5}";
        auto channelOperation = PushNotificationChannelManager::CreatePushNotificationChannelAsync(remoteId);

        // Setup the inprogress event handler
        channelOperation.Progress(
            [](
                IAsyncOperationWithProgress<PushNotificationChannelResult, PushNotificationChannelResult> const& /* sender */,
                PushNotificationChannelResult const& args)
            {
                if (args.Status() == ChannelStatus::InProgress)
                {
                    // This is basically a noop since it isn't really an error state
                    printf("The first channel request is still in progress! \n");
                }
                else if (args.Status() == ChannelStatus::InProgressRetry)
                {
                    LOG_HR_MSG(args.ExtendedError(), "The channel request is in back-off retry mode because of a retryable error! Expect delays in acquiring it.");
                }
            });

        // Setup the completed event handler
        channelOperation.Completed(
            [](
                IAsyncOperationWithProgress<PushNotificationChannelResult, PushNotificationChannelResult> const& sender,
                AsyncStatus const /* asyncStatus */)
            {
                auto result = sender.GetResults();
                if (result.Status() == ChannelStatus::CompletedSuccess)
                {
                    auto channelUri = result.Channel().Uri();
                    auto channelExpiry = result.Channel().ExpirationTime();

                    // Persist the channelUri and Expiry in the App Service
                }
                else if (result.Status() == ChannelStatus::CompletedFailure)
                {
                    LOG_HR_MSG(result.ExtendedError(), "We hit a critical non-retryable error with channel request!");
                }
            });

        // Draw window and other foreground UI stuff here

        // Unsubscribe the foreground event
        details.PushActivated(eventToken);
    }

    return 0;
}
```

## Unregistering Push Activations
In some certain rare cases, we may want to disable the activator for Push. For example, the user disables a toggle exposed by the app. To accomplish that, we would need to call into the UnRegister API
```cpp
int main()
{
    // Always Register the Push trigger as the first step: It sets up the Inproc COM server for subsequent Push operations
    std::wstring activatorGuid = L"{B8E58D9D-A229-44A8-B923-2823C3791BCE}";
    PushNotificationActivatorDetails details(activatorGuid);
    PushNotificationChannelManager::RegisterPushNotificationActivator(details);

    // Some code resides here

    // This unregisters the Activator above
    if (removePush)
    {
        PushNotificationChannelManager::UnregisterPushNotificationActivator(details.Registration());
    }
    return 0;
}
```

## Registration of the Push Activator for LOW IL apps like UWP (Inproc)
The app will simply call into the Default implementation of InProcActivatorDetails for the Registration Flow instead of the CLSID overload.
```cpp
InProcActivatorDetails details();
PushNotificationChannelManager::RegisterPushNotificationActivator(details);
```

To intercept the payload, OnBackgroundActivated will have to be implemented by the app.
```cpp
sealed partial class App : Application
{
  ...

  protected override void OnBackgroundActivated(BackgroundActivatedEventArgs args)
  {
      base.OnBackgroundActivated(args);
      IBackgroundTaskInstance taskInstance = args.TaskInstance;
      DoYourBackgroundWork(taskInstance);  
  }
}
```

# Remarks

## Foreground and Background API calls
The developer should always call Activator Registration APIs and LaunchArgument APIs irrespective of the foreground or background context of the Win32 app. Order matters and Registration should always be the first call.

## Foreground API calls
It is recommended that the developer subscribes to channel requests and Push events if the app is launched in foreground context.

## Background API calls
It is recommended that the developer calls into the ActivateArgs API to retrieve the relevant PushArgs if launched in the Background context.

## Seperating Activator Registration flow from Channel Request flow
We decided to have the following 2 APIs to be seperate calls instead of a single combined API call:
```cpp
PushNotificationChannelManager::RegisterPushNotificationActivator(details)
PushNotificationChannelManager::CreatePushNotificationChannel(remoteIdentifier)
```
Mainly for 2 reasons:
* The app developer is expected to Register an activator for every WinMain app launch. Combining the channel request API with the registration call would force the developer to keep the client channel in sync with the App Service more frequently (both for foreground and background launch) which can cause potential synchronization bugs. The preference is for developers to request new channels only on Foreground launches triggered by the user.
* It isn't required that developers Register a Push Activator for Visual Toast operations. In the case of Visual Toasts, payloads are directed to the Shell and not to the App.

## Handling Push ChannelFailures
PushNotification channel request calls are expected to fail since they go over the wire. We don't want the developer to deal with the complexities of retryable failures and critical failures. So we expose in-progress states and internal error codes for developers to action on.

For example, we have 2 different Progress states, one indicating basic progress and another indicating retry progress.
```cpp
if (args.Status() == ChannelStatus::InProgress)
{
    // This is basically a noop since it isn't really an error state
    printf("The first channel request is still in progress! \n");
}
else if (args.Status() == ChannelStatus::InProgressRetry)
{
    LOG_HR_MSG(args.ExtendedError(), "The channel request is in back-off retry mode because of a retryable error! Expect delays in acquiring it.");
}
```

Similarly, operations are expected to fail or succeed on completion.
```cpp
if (result.Status() == ChannelStatus::CompletedSuccess)
{
    auto channelUri = result.Channel().Uri();
    auto channelExpiry = result.Channel().ExpirationTime();

    // Persist the channelUri and Expiry in the App Service
}
else if (result.Status() == ChannelStatus::CompletedFailure)
{
    LOG_HR_MSG(result.ExtendedError(), "We hit a critical non-retryable error with channel request!");
}
```

## Manifest Registration
For MSIX, the COM activator GUID and the exe path need to be registered in the manifest. The launch args would need to be pre set to a well-known string that defines Push Triggers. 
```xml
<Extensions>
  <com:Extension Category="windows.comServer">
    <com:ComServer>
      <com:ExeServer Executable="SampleBackgroundApp\SampleBackgroundApp.exe" DisplayName="SampleBackgroundApp" Arguments="-ReunionPushServer">
        <com:Class Id="{GUIDEntryPoint}" DisplayName="Reunion Push" />
      </com:ExeServer>
    </com:ComServer>
  </com:Extension>
</Extensions>
```

## UWP InProc activator
The UWP inproc activator flow differs from the Win32 inproc activator flow since there is technically no WinMain activation associated with UWPs. Instead the App will have to  override and implement OnBackgroundActivated which is tightly coupled to Windows.UI.Xaml workstreams.

# API Details
```c# (but really MIDL3)
    namespace Microsoft.ProjectReunion
    {
        // The legacy ActivationKind does not support operations like Push. So we need to define an extension set
        enum ActivationKindExtension
        {
            Launch = 0,
            Search = 1,
            ShareTarget = 2,
            File = 3,
            Protocol = 4,
            FileOpenPicker = 5,
            FileSavePicker = 6,
            CachedFileUpdater = 7,
            ContactPicker = 8,
            Device = 9,
            PrintTaskSettings = 10,
            CameraSettings = 11,
            RestrictedLaunch = 12,
            AppointmentsProvider = 13,
            Contact = 14,
            LockScreenCall = 15,
            VoiceCommand = 16,
            LockScreen = 17,
            PickerReturned = 1000,
            WalletAction = 1001,
            PickFileContinuation = 1002,
            PickSaveFileContinuation = 1003,
            PickFolderContinuation = 1004,
            WebAuthenticationBrokerContinuation = 1005,
            WebAccountProvider = 1006,
            ComponentUI = 1007,
            ProtocolForResults = 1009,
            ToastNotification = 1010,
            Print3DWorkflow = 1011,
            DialReceiver = 1012,
            DevicePairing = 1013,
            UserDataAccountsProvider = 1014,
            FilePickerExperience = 1015,
            LockScreenComponent = 1016,
            ContactPanel = 1017,
            PrintWorkflowForegroundTask = 1018,
            GameUIProvider = 1019,
            StartupTask = 1020,
            CommandLineLaunch = 1021,
            BarcodeScannerProvider = 1022,
            Push = 1023,
        };

        // Simply a wrapper around IActivatedEventArgs to support new Kind extensions like Push which aren't a part of Foundations today
        runtimeclass ActivatedEventArgsExtension
        {
            ActivatedEventArgsExtension(Windows.ApplicationModel.Activation.IActivatedEventArgs activatedEventArgs, ActivationKindExtension kind2);
            ActivationKindExtension Kind2 { get; };
            Windows.ApplicationModel.Activation.IActivatedEventArgs ActivatedArgs{ get; };
        }

        // This is an overload of the existing GetActivatedEventArgs in Reunion which supports new Activation Kinds
        static runtimeclass AppLifecycle2
        {
            // Called during process launch in Main to determine whether the launch is in response to Protocol/Foreground/Push etc.
            static ActivatedEventArgsExtension GetActivatedEventArgs();
        }

        // Event args in WinMain activation payload. It wraps around the BackgroundInstance construct and manages the task lifetime.
        runtimeclass PushNotificationActivatedEventArgs : Windows.ApplicationModel.Activation.IActivatedEventArgs
        {
            // Initialize using the raw byte payload
            PushNotificationActivatedEventArgs(Windows.ApplicationModel.Background.IBackgroundTaskInstance backgroundTask);

            // The Push payload
            byte[] Payload { get; };

            // Takes a deferral to run under specific modes like low power mode
            void GetDeferral();

            // Closes the Deferral taken on a Push Trigger. If this is not called by the developer, the deferral will automatically be invoked on destruction.
            void CompleteDeferral();

            // Subscribe to Cancelled event handler to be signalled when resource policies are no longer true like 30s wallclock timer
            event Windows.ApplicationModel.Background.BackgroundTaskCanceledEventHandler Canceled;

            // The number of times Resource management suspended the Task
            UInt32 SuspendedCount { get; };
        }

        // An abstraction over the inproc activation Registration flow
        runtimeclass InProcActivatorDetails
        {
            // Initialize using a manifest defined activatorId to Activate the InProc COM server
            InProcActivatorDetails(String taskClsid);

            // Initialize an inproc activator for LOW-IL apps like UWP with no COM Server specified in manifest
            InProcActivatorDetails();

            // The CLSID associated with the Client COM server that reunion will adopt
            String TaskClsid{ get; };

            // The conditions under which Push Triggers would execute
            Windows.ApplicationModel.Background.IBackgroundCondition Condition;

            // The in-memory Event handler to subscribe to if the app is in the foreground
            event Windows.Foundation.EventHandler<PushNotificationActivatedEventArgs> PushActivated;

            // The backgroundRegistration that gets populated on successful registration
            Windows.ApplicationModel.Background.IBackgroundTaskRegistration Registration;
        };

        enum ChannelStatus
        {
            InProgress, // The request is in progress and there is no retry operation
            InProgressRetry, // The request is in progress and is in a backoff retry state
            CompletedSuccess, // The request completed successfully
            CompletedFailure, // The request failed with some critical internal error. Check ExtendedError for HRESULT
        };

        runtimeclass PushNotificationChannelResult
        {
            PushNotificationChannelResult(
                Windows.Networking.PushNotifications.PushNotificationChannel channel,
                HRESULT extendedError,
                ChannelStatus status);

            // The Push channel associated with the Result. Null if InProgress or completion failed
            Windows.Networking.PushNotifications.PushNotificationChannel Channel { get; };

            // Low-level information about why the operation might not
            // have worked. Apps generally do not take action based on
            // this value, in part because the value may not be stable.
            HRESULT ExtendedError{ get; };

            // The Status of the ChannelComplete operation
            ChannelStatus Status { get; };
        };

        static runtimeclass PushNotificationChannelManager
        {
            // Register an activator using a Details context
            static void RegisterPushNotificationActivator(InProcActivatorDetails details);

            // Unregister any activator if present
            static void UnregisterPushNotificationActivator(Windows.ApplicationModel.Background.IBackgroundTaskRegistration registration);

            // Request a Push Channel with an encoded RemoteId from WNS. RemoteId is an AAD identifier GUID
            static Windows.Foundation.IAsyncOperationWithProgress<PushNotificationChannelResult, PushNotificationChannelResult> CreatePushNotificationChannelAsync(String remoteId);
        };
    }
```
# Appendix
* For all OS images before Cobalt, the RemoteId will be a noop and the native platform will send the PFN (PackageFamilyName) in the channel request protocol. The WNS server will maintain an internal mapping of PFN -> RemoteId and will return a channelUri with the encoded RemoteId after querying the map.
* For OS images after Cobalt, the Reunion component will call into newly added Closed source APIs in the OS to actually pass a RemoteId in the Channel Request operation.
* For unpackaged Win32 apps, the Reunion component will call into Closed source APIs to register the unpackaged Win32 process with the RemoteId.
* A long running Reunion component will be needed to intercept Push payloads from the native platform and Launch the corresponding unpackaged Win32 app. We will be using Protocol Activation via WinMain to launch the unpackaged Win32 process from the long running service. The requirement is mainly because the native client today does not have support to launch Win32 apps directly in response to a Push payload unless they are already running in which case we simply marshall the payload back to the process via a registered callback sink.
* For packaged applications like MSIX, we buid a thin wrapper around existing Background Manager APIs rather than re-inventing new Background Triggers. This is mainly because Background Infrastructure native client stack is built with Power Management and resourcing concerns already addressed. Building a new stack that addresses similar concerns is likely not the best use of our time or resources. Instead we should invest in Reunioninzing the Background Infra stack itself.
