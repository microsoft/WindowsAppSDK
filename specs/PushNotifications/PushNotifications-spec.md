# Push Notifications in Windows App SDK SDK

# Background

The Windows Push Notification Service (WNS) enables third-party developers to send toast, tile,
badge, and raw updates from their own cloud service. This provides a mechanism to deliver new
updates to your users in a power-efficient and dependable way. For example, the Skype app service
can trigger an incoming call toast by Pushing a Payload to the WNS service. Push is generally used
for time critical events that require immediate user/developer action.

For more details see:

-   [The Push notification WinRT Public APIs](https://docs.microsoft.com/uwp/api/windows.networking.pushnotifications?view=winrt-19041)
    Defines the classes that encapsulate Push notifications. (UWP and Win32)
-   [The Windows Push Notification Services (WNS) Overview](https://docs.microsoft.com/windows/uwp/design/shell/tiles-and-notifications/windows-push-notification-services--wns--overview)
    Defines how an app can subscribe to Push Notifications and send a payload down to the
    corresponding client.

The below diagram is an illustration of the overall Push Flow that we have today:
![Legacy Flow For Windows App SDK](Legacy.png)

## The problems today

**Portal Registration**: The entire Registration flow for Push is dependent on registering an app in
the partner center portal by
[associating an app with the Microsoft Store](https://docs.microsoft.com/azure/notification-hubs/notification-hubs-windows-store-dotnet-get-started-wns-push-notification).
As a result, non-store provisioned apps cannot use this feature.

**Client Registration**: Unpackaged 3rd party applications cannot register themselves as a Push
target. The only way to get an implicit client side registration is to package the app as an MSIX
Desktop Bridge or sparse signed packages which may not satisfy 3rd party requirements.

**Push Channels**: All the channel APIs are dependent on the caller app having a Microsoft store
provisioned identity. This means that Win32 and unpackaged apps that are not store distributed
cannot use our Public APIs. Sideloaded UWP apps have exactly the same problem.

**Activation**: When the OS receives a Push over the WNS socket, it signals the Background
Infrastructure to trigger a task and run some code on the app's behalf. This flow is undefined for
Win32 apps that need to use Push today due to the limitations described above.

**Channel Request Error Handling**: The channel APIs exposed today can throw exceptions via their
Projections. Some errors can be critical errors while others are retryable errors. Published
guidance for retrying isn't very clear and has been the root cause of multiple app bugs in the past.
We want to abstract away the details of channel retry operations for developers in Windows App SDK.

# Description

At a high level, we need to provide a way for all Win32 applications to subscribe to and receive
Push notifications irrespective of their app type. This includes unpackaged apps and packaged win32
(MSIX Desktop Bridge, MSIX Win32App, Sparse Signed Packages). Moreover, all Push scenarios should
adhere to OS resource management policies like Power Saver, Network Attribution (amount of data an
app uses), enterprise group policies, etc. The Windows App SDK Push component will abstract away the
complexities of dealing with WNS channel registrations and Push related activations as much as
possible freeing the developer to focus on other app related challenges.

We will prioritize the following feature set for Windows App SDK:

-   Raw push for Packaged Win32 (MSIX Desktop Bridge)
-   Raw push for Unpackaged Win32
-   Visual Cloud Toasts for packaged Win32 apps
-   Visual Cloud Toasts for unpackaged Win32 apps

A Portal Registration flow through
[AAD (Azure Active Directory)](https://docs.microsoft.com/azure/active-directory/develop/quickstart-register-app)
will also be defined that removes the dependency of the Push Flow with the Partner Center Portal.
The RemoteIdentifier GUID in this spec maps to the ApplicationId in the AAD App Registration
process. Below is an illustration of the proposed flow through AAD:
![Push Flow For Windows App SDK](Push.png)

Phase 1 (Windows App SDK Preview): WNS Push APIs will only support Win32 Packaged app (MSIX Desktop
Bridge).

Phase 2 (Windows App SDK V1): WNS Push APIs will support unpackaged Win32 scenarios.

Link to the official Windows App SDK timeline can be found
[here](https://github.com/microsoft/WindowsAppSDK/blob/main/docs/roadmap.md).

# Examples

## In this scenario, the process that Registers the Push Activator and the process specified as the COM server are the same

The code in Main would follow the pattern below:

-   The Registration will take in a CLSID of the COM server as part of the Activator setup. The
    registration API will simply abstract away the COM details from the developer including
    registration of the in-process Windows App SDK component.
-   The app will query AppLifeCycle APIs to retrieve an ActivationKind. (Note: This is covered in a
    seperate AppLifeCycle API spec.)
-   If the Activation is Push, the app will QI the Arguments property to retrieve an instance of
    PushActivatedEventArgs and get the Push payload from it. Care needs to be taken to Get a
    Deferral and Complete the Deferral while processing the payload for Power Management compliance.
-   If the Activation is Foreground, the app will do 2 things:
    -   It will request a Push Channel Asynchronously with an implementation of Progress and
        Completed event handler.
        -   Expect Channel operations to take around 2-16 minutes in some rare cases (retryable
            errors). In the 90th percentile case, it should be fairly quick operation (in a few
            seconds).
    -   It will subscribe to a In-memory Push event handler hanging off the retrieved Push Channel
        component.
        -   The app should ideally handle the event by setting the Handled property to true to
            prevent Background Activation from launching a new process.
-   If the application is unpackaged, it will use the ProtocolActivator to register the activator
    instead. The app will also need to call into the bootstrapper API to have access to the Windows
    App SDK. Click
    [here](https://docs.microsoft.com/en-us/windows/apps/windows-app-sdk/tutorial-unpackaged-deployment?tabs=cpp)
    for information on how to build and deploy unpackaged applications with Windows App SDK.

```cpp
int main()
{
    PushNotificationActivationInfo info {};
    bool isComActivationSupported { PushNotificationManager::IsActivatorSupported(PushNotificationRegistrationActivators::PushTrigger |
                                        PushNotificationRegistrationActivators::ComActivator)};
    if (isComActivationSupported)
    {
        // Register the ComActivator guid
        info = PushNotificationActivationInfo(PushNotificationRegistrationActivators::PushTrigger | PushNotificationRegistrationActivators::ComActivator,
        winrt::guid("BACCFA91-F1DE-4CA2-xxxx-90BE66934EC6"));
    }
    else
    {
        info = PushNotificationActivationInfo(PushNotificationRegistrationActivators::ProtocolActivator);
    }

    // Registers the application to receive push notifications
    PushNotificationManager::RegisterActivator(info);

    // Check to see if the WinMain activation is due to a Push Activator
    auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
    auto kind { args.Kind() };

    if (kind == ExtendedActivationKind::Push)
    {
        auto pushArgs = args.Data().as<PushNotificationReceivedEventArgs>();

        // Call GetDeferral to ensure that code runs in low power
        auto deferral = pushArgs.GetDeferral();

        auto payload = pushArgs.Payload();

        // Do stuff to process the raw payload to be used for further app processing
        std::string payloadString(payload.begin(), payload.end());

        // Call Complete on the deferral as good practise: Needed mainly for low power usage
        deferral.Complete();
    }
    else if (kind == ExtendedActivationKind::Launch) // This indicates that the app is launching in the foreground
    {
        // Register the AAD RemoteIdentifier for the App to receive Push
        auto channelOperation = PushNotificationManager::CreateChannelAsync(
            winrt::guid("F80E541E-3606-48FB-xxxx-118A3C5F41F4"));

        // Setup the inprogress event handler
        channelOperation.Progress(
            [](
                IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& sender,
                PushNotificationCreateChannelStatus const& args)
            {
                if (args.status == PushNotificationChannelStatus::InProgress)
                {
                    // This is basically a noop since it isn't really an error state
                    printf("The first channel request is still in progress! \n");
                }
                else if (args.status == PushNotificationChannelStatus::InProgressRetry)
                {
                    LOG_HR_MSG(
                        args.extendedError,
                        "The channel request is in back-off retry mode because of a retryable error! Expect delays in acquiring it. RetryCount = %d",
                        args.retryCount);
                }
            });

        winrt::event_token pushToken;

        // Setup the completed event handler
        channelOperation.Completed(
            [&](
                IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& sender,
                AsyncStatus const asyncStatus)
            {
                auto result = sender.GetResults();
                if (result.Status() == PushNotificationChannelStatus::CompletedSuccess)
                {
                    auto channelUri = result.Channel().Uri();
                    auto channelExpiry = result.Channel().ExpirationTime();

                    // Register Push Event for Foreground
                    pushToken = result.Channel().PushReceived([&](const auto&, PushNotificationReceivedEventArgs args)
                    {
                        auto payload = args.Payload();

                        // Do stuff to process the raw payload

                        // Stop the subsequent background activation from launching process again with this payload
                        args.Handled(true);
                    });

                        // Persist the channelUri and Expiry in the App Service for subsequent Push operations
                }
                else if (result.Status() == PushNotificationChannelStatus::CompletedFailure)
                {
                    LOG_HR_MSG(result.ExtendedError(), "We hit a critical non-retryable error with channel request!");
                }
            });

        // Draw window and other foreground UI stuff here

        // Unregister the Push event for Foreground before exiting
        auto result = channelOperation.GetResults();
        if (result.Status() == PushNotificationChannelStatus::CompletedSuccess)
        {
            result.Channel().PushReceived(pushToken);
        }
    }

    if(isComActivationSupported)
    {
        // Unregister the ComActivator from inproc activation
        PushNotificationManager::UnregisterActivator(PushNotificationRegistrationActivators::ComActivator);
    }

    return 0;
}
```

## In this scenario, the process that Registers the Push Trigger and the process specified as the COM server are different.

This only works for packaged applications that support PushTrigger and ComActivator flags in
RegisterActivator. Out-of-process activation is not supported for unpackaged apps.

Process A (Registration of the Push Trigger only):

```cpp
int main()
{
    PushNotificationActivationInfo info = nullptr;
    if (PushNotificationManager::IsActivatorSupported(PushNotificationRegistrationActivators::PushTrigger))
    {
        // Register the ComActivator guid
        info = PushNotificationActivationInfo(PushNotificationRegistrationActivators::PushTrigger,
            winrt::guid("BACCFA91-F1DE-4CA2-xxxx-90BE66934EC6"));
    }
    else
    {
        return E_NOTIMPL;
    }

    // Registers a Push Trigger with the Background Infra component
    PushNotificationManager::RegisterActivator(info);

    // Some app code ....

    return 0;
}
```

Process B (Register the inproc COM server and handle the background activation):

```cpp
int main()
{
    PushNotificationActivationInfo info = nullptr;
    if (PushNotificationManager::IsActivatorSupported(PushNotificationRegistrationActivators::ComActivator))
    {
        // Register the ComActivator guid
        info = PushNotificationActivationInfo(PushNotificationRegistrationActivators::ComActivator,
            winrt::guid("BACCFA91-F1DE-4CA2-xxxx-90BE66934EC6"));
    }
    else
    {
        return E_NOTIMPL;
    }

    // Registers the current process as an InProc COM server
    PushNotificationManager::RegisterActivator(info);

    // Check to see if the WinMain activation is due to a Push Activator
    auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
    auto kind = args.Kind();

    if (kind == ExtendedActivationKind::Push)
    {
        // Do Push processing stuff
    }

    // Some code ....

    // Unregisters the inproc COM Activator
    PushNotificationManager::UnregisterActivator(PushNotificationRegistrationActivators::ComActivator);

    return 0;
}
```

## Registration of the Push Activator for LOW IL apps like UWP (Inproc)

The app will simply call into the Default implementation of PushNotificationActivationInfo for the
Registration Flow instead of the CLSID overload.

```cpp
PushNotificationActivationInfo info();
PushNotificationChannelManager::RegisterPushNotificationActivator(info);
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

## Registration

The developer should always call the Push Registration API first to register the current process as
the COM server before retrieving the PushActivationArgs. Order matters!

## Foreground API calls

It is recommended that the developer subscribes to channel requests and Push events if the app is
launched in foreground context. This is to ensure that subsequent Push and channel events can be
handled by the running process.

## Seperating Activator Registration flow from Channel Request flow

We decided to have the following 2 APIs to be seperate calls instead of a single combined API call:

```cpp
PushNotificationChannelManager::RegisterActivator(info)
PushNotificationChannelManager::CreatePushChannelAsync(remoteIdentifier)
```

Mainly for 2 reasons:

-   The app developer is expected to Register an activator for every WinMain app launch. Combining
    the channel request API with the registration call would force the developer to keep the client
    channel in sync with the App Service more frequently (both for foreground and background launch)
    which can cause potential synchronization bugs. The preference is for developers to request new
    channels only on Foreground launches triggered by the user.
-   It isn't required that developers Register a Push Activator for Visual Toast operations. In the
    case of Visual Toasts, payloads are directed to the Shell and not to the App.

## Handling Push ChannelFailures

PushNotification channel request calls are expected to fail since they go over the wire. We don't
want the developer to deal with the complexities of retryable failures and critical failures. We do
however expose in-progress states and internal error codes to developers if they prefer to track it
for debugging, settings user expectations etc.

For example, we have 2 different Progress states, one indicating basic progress and another
indicating retry progress.

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

For MSIX, the COM activator GUID and the exe need to be registered in the manifest. The launch args
would need to be pre-set to a well-known string that defines Push Triggers.

```xml
<Extensions>
  <com:Extension Category="windows.comServer">
    <com:ComServer>
      <com:ExeServer Executable="SampleBackgroundApp\SampleBackgroundApp.exe" DisplayName="SampleBackgroundApp" Arguments="----PushServer">
        <com:Class Id="{GUIDEntryPoint}" />
      </com:ExeServer>
    </com:ComServer>
  </com:Extension>
</Extensions>
```

# API Details

```c#

namespace Microsoft.Windows.PushNotifications
{
    // Event args for the Push payload.
    runtimeclass PushNotificationReceivedEventArgs
    {
        // Initialize using the IBackgroundInstance: used specifically for the Background Activation scenario
        static PushNotificationReceivedEventArgs CreateFromBackgroundTaskInstance(Windows.ApplicationModel.Background.IBackgroundTaskInstance backgroundTask);

        // Initialize using the PushNotificationEventArgs from Windows: used specifically for in-memory event handling when app is already in foreground
        static PushNotificationReceivedEventArgs CreateFromPushNotificationReceivedEventArgs(Windows.Networking.PushNotifications.PushNotificationReceivedEventArgs args);

        // The Push payload
        byte[] Payload { get; };

        // Gets a deferral to run under specific modes like low power mode
        Windows.ApplicationModel.Background.BackgroundTaskDeferral GetDeferral();

        // Subscribe to Cancelled event handler to be signalled when resource policies are no longer true like 30s wallclock timer
        event Windows.ApplicationModel.Background.BackgroundTaskCanceledEventHandler Canceled;

        // Set to true to prevent proceeding launch due to Background Activation: false by default
        Boolean Handled;
    };

    [flags]
    enum PushNotificationRegistrationActivators
    {
        Undefined = 0, // Default enum to catch nullptr case when no flag is defined
        PushTrigger = 0x1, // Registers a Push Trigger with Background Infrastructure
        ComActivator = 0x2, // Registers the Background Task component as an in-process COM server
        ProtocolActivator = 0x4, // Registers an application with the PushNotificationsLongRunningTask to be activated via protocol
    };

    // An abstraction over the activation Registration flow
    runtimeclass PushNotificationActivationInfo
    {
        // Initialize using a Registration option and optionally defined parameters like manifest defined activatorId
        // 1) If kind = PushTrigger is specified, only the Push Trigger will be Registered with Background Infra
        // 2) If kind = ComActivator is specified, the Background Task component will be Registered as an in-process COM server
        PushNotificationActivationInfo(PushNotificationRegistrationActivators activators, Guid taskClsid);

        // Applications that need to use ProtocolActivator will use this constructor
        PushNotificationActivationInfo(PushNotificationRegistrationActivators activators);

        // The CLSID associated with the Client COM server that Windows App SDK will activate
        Guid TaskClsid{ get; };

        PushNotificationRegistrationActivators Activators{ get; };

        // The conditions under which Push Triggers would execute
        Windows.ApplicationModel.Background.IBackgroundCondition[] GetConditions();
        void SetConditions(Windows.ApplicationModel.Background.IBackgroundCondition[] conditions);
    };

    enum PushNotificationChannelStatus
    {
        InProgress, // The request is in progress and there is no retry operation
        InProgressRetry, // The request is in progress and is in a backoff retry state. Check ExtendedError for HRESULT for retryable error.
        CompletedSuccess, // The request completed successfully
        CompletedFailure, // The request failed with some critical internal error. Check ExtendedError for HRESULT
    };

    // The PushNotificationChannel Progress result
    struct PushNotificationCreateChannelStatus
    {
        // The last extended error we failed Channel requests on that caused the inprogress retry status. S_OK if this is just progress status.
        HRESULT extendedError;

        // Either InProgress or InProgressRetry status
        PushNotificationChannelStatus status;

        // Total Retries so far
        UInt32 retryCount;
    };

    runtimeclass PushNotificationChannel
    {
        PushNotificationChannel(String uri, Windows.Foundation.DateTime expiration);

        // The Channel Uri for app to Post a notification to.
        String Uri { get; };

        // Expiration of the Channel
        Windows.Foundation.DateTime ExpirationTime { get; };

        // Unsubscribes the channel
        void Close();

        // In-memory Event handler for Push Notifications
        event Windows.Foundation.TypedEventHandler<PushNotificationChannel, PushNotificationReceivedEventArgs> PushReceived;
    }

    runtimeclass PushNotificationCreateChannelResult
    {
        PushNotificationCreateChannelResult(
            PushNotificationChannel channel,
            HRESULT extendedError,
            PushNotificationChannelStatus status);

        // The Push channel associated with the Result. Null if InProgress or completion failed
        PushNotificationChannel Channel { get; };

        // More detailed error code in addition to the ChannelStatus state.
        HRESULT ExtendedError{ get; };

        // The Status of the ChannelComplete operation
        PushNotificationChannelStatus Status { get; };
    };

    static runtimeclass PushNotificationManager
    {
        // Register an activator using an ActivationInfo context and cache the flag for unregister
        static void RegisterActivator(PushNotificationActivationInfo details);

        // Unregister any activator given PushNotificationRegistrationActivators
        // 1) If kind = PushTrigger is specified, the trigger itself will be removed
        // 2) If kind = ComActivator is specified, the Project Reunion Background Task component will no longer act as an InProc COM Server
        // 3) If kind = ProtocolActivator is specified, the application will be unregistered from the long running process that handles activation
        static void UnregisterActivator(PushNotificationRegistrationActivators activators);

        // Unregister all activators registered for the application
        static void UnregisterAllActivators();

        // Request a Push Channel with an encoded RemoteId from WNS. RemoteId is an AAD identifier GUID
        static Windows.Foundation.IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> CreateChannelAsync(Guid remoteId);

        // Applications will call this to check which flags are supported for RegisterActivator
        static Boolean IsActivatorSupported(PushNotificationRegistrationActivators activators);
    };
}



```

# Appendix

-   For all versions of Windows 10 prior to Version 21H1 (build 19043), the RemoteId is unused and
    the native platform will send the Package Family Name in the channel request protocol. The WNS
    server will maintain an internal mapping of PFN -> RemoteId and will return a channelUri with
    the encoded RemoteId after querying the map.
-   For Windows 10 version 21H1(build 19043) and beyond, the Windows App SDK component will call
    into newly added APIs in the OS pass a RemoteId in the Channel Request operation.
-   For unpackaged Win32 apps, the Windows App SDK component will call into Closed source APIs to
    register the unpackaged Win32 process with the RemoteId.
-   A long running Windows App SDK component will be needed to intercept Push payloads from the
    native platform and Launch the corresponding unpackaged Win32 app. We will be using Protocol
    Activation via WinMain to launch the unpackaged Win32 process from the long running service. The
    requirement is mainly because the native client today does not have support to launch Win32 apps
    directly in response to a Push payload unless they are already running in which case we simply
    marshal the payload back to the process via a registered callback sink.
-   For packaged applications, we build a thin wrapper around existing Background Manager APIs
    rather than re-inventing new Background Triggers. This is mainly because Background
    Infrastructure native client stack is built with Power Management and resourcing concerns
    already addressed. Building a new stack that addresses similar concerns is likely not the best
    use of our time or resources. Instead we should invest in Windows App SDK-izing the Background
    Infra stack itself.
