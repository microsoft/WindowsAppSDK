# Win32 registrations in Project Reunion SDK

# Background

Toast Notifications today are an important scenario for WNS client. Applications use the toast notification APIs today to surface intent to the user via the Action Centre UI. For example, messaging clients like whatsapp can pop a toast notification to the user to show that they received a new message from a friend or on a group chat. If the app chooses to, apps can define rich interactive toast templates where the user can action on notifications via input from the user. For example, a user can respond to a message in whatsapp by directly interacting with the toast rather than launching the app and doing it seperately there. This process is inferred to as toast background activation. There are also scenarios where the user expects to launch an app on tapping the toast body. We refer to this as toast foreground activation.

* [The notification WinRT Public APIs](https://docs.microsoft.com/en-us/uwp/api/windows.ui.notifications?view=winrt-19041)
  Defines the classes that encapsulate tile, toast and badge notifications. (UWP and Win32)

* [Win32 toasts](https://docs.microsoft.com/en-us/windows/uwp/design/shell/tiles-and-notifications/send-local-toast-desktop-cpp-wrl)
  Defines the process of using Toast Notifications APIs with Desktop applications and activating them.

* [UWP toasts](https://docs.microsoft.com/en-us/windows/uwp/design/shell/tiles-and-notifications/send-local-toast)
  Defines the process of using Toast Notifications APIs with UWP applications and activating them.
# Description

## The problems today

**Registration**: UWP and Win32 MSIX/sparse apps are already "registered" with the platform for sending toasts and don't have to do anything. Win32 apps, on the other hand, have to register with "Nitro" for toast notifications. Today, this requires using a Start menu shortcut which is very painful for developers (but we have an alternative registry approach that can help fix this). Ideally, we want Win32 apps to have to do nothing to register, just like UWP and Win32 MSIX/sparse apps.

**Sending**: UWP and Win32 MSIX/sparse apps simply call `CreateToastNotifier()`... Win32 apps have to call `CreateToastNotifier("MyAumid")`.

**Images**: UWP and Win32 MSIX/sparse apps can use HTTP images in toasts, Win32 apps cannot (they have to download the image to disk).

**Activation**: UWP apps are activated via their App.xaml.cs OnActivated. Win32 MSIX/sparse apps have two options... they can use Nitro activation and get an in-process COM activation (which when we talked to devs, most devs prefer), or they can receive an EXE activation (in a separate process) and call the GetCommandLine() API to obtain their activation args. Win32 apps can only use Nitro (in-process COM activation).

**Down-level support**: There are OS versioning complexities which add more confusion to the registration process: For example, Sparse Signed Packages are only supported in Vibranium and beyond while nitro is supported downlevel. This causes a lot of developer confusion, so we need to simplify the Registration process for Project Reunion with a shared set of APIs that would suffice for all app types: UWP, Centennial or Unpackaged Win32 irrespective of the OS version type.

## Summary

The Reunion toast APIs will follow familiar API constructs from it's WinRT Public API counterpart and remove all the complexities associated with Centennial, Nitro and Sparse Signed package registrations. This means that we will take constructs like ToastNotificationManager, ToastHistory and ToastNotifier from public WinRT and re-introduce them in Reunion as compat libraries. To make the registration experience seamless, we'll take on the heavy lifting of registering a Win32 app down-level, using their existing app assets (app name, icon). Developers simply have to call ToastNotificationManagerInterop, and regardless of their app type, toasts will automatically work!
For Activation, we will also do all the heavy lifting internally so that the developer can avoid steps to Register background triggers or nitro component with WNS client. All they would need to do is register a WinRT event handler hanging of ToastNotificationManagerInterop which is a simplistic and well defined process.

## API Experience

At a high level summary, to send toasts, app developers (regardless of app type) will...

Install Reunion SDK
Create a Windows.UI.Notifications.ToastNotification as usual with their desired content
Call Microsoft.UI.Notifications.ToastNotificationManagerInterop.CreateToastNotifier().Show(notif) to show the toast
Aside from the first and third bullet, this is identical to the UWP experience today. They simply use our Interop class to create the notifier, which for Win32 automatically registers their app and calls the correct CreateToastNotifier with their aumid.

To receive activation, we haven't been able to get a 100% converged experience...

* UWP apps: They would still use App.xaml.cs OnActivated as they do today
* Win32 MSIX/sparse apps: They would first have to add a COM server registration in their app manifest (maybe tooling can eliminate this somehow), and then they subscribe to ToastNotificationManagerInterop.OnActivated
* Win32 apps: They subscribe to ToastNotificationManagerInterop.OnActivated

# Examples

## Sending toast API experience

First, developers would install the Reunion NuGet package.

Then, developers construct a notification as usual, but call the Interop version of ToastNotificationManager to create the toast notifier. With that one change, toasts will work on Win32 without doing anything additional!

```cs
// Construct the content (same as today)
ToastContent content = new ToastContentBuilder()
    .AddToastActivationInfo("picOfHappyCanyon", ToastActivationType.Foreground)
    .AddText("Andrew sent you a picture")
    .AddText("Check this out, Happy Canyon in Utah!")
    .GetToastContent();

// Create the notification (same as today)
ToastNotification notification = new ToastNotification(content.GetXml());

// And send it (Interop is the only difference)
ToastNotificationManagerInterop.CreateToastNotifier().Show(notification);
```

## Receiving activation API experience

### UWP apps

UWP apps would receive activation as they do today, within their **App.xaml.cs** OnActivated method.

```cs
protected override void OnActivated(IActivatedEventArgs e)
{
    // Handle toast activation
    if (e is ToastNotificationActivatedEventArgs toastActivationArgs)
    {
        // Obtain the arguments from the toast
        string args = toastActivationArgs.Argument;

        // Obtain any user input (text boxes, menu selections) from the toast
        ValueSet userInput = toastActivationArgs.UserInput;
 
        // TODO: Show the corresponding content
    }
}
```

### Win32 MSIX/Sparse apps

First, in your Package.appxmanifest, add:

1. Declaration for xmlns:com
1. Declaration for xmlns:desktop
1. In the IgnorableNamespaces attribute, com and desktop
1. com:Extension for the COM activator using a new GUID of your choice. Be sure to include the Arguments="-ToastActivated" so that you know your launch was from a toast
1. desktop:Extension for windows.toastNotificationActivation to declare your toast activator CLSID (the GUID from #4 above).

Then, **in your app's startup code** (WinMain), subscribe to the **OnActivated** event.

```cs

[System.STAThreadAttribute()]
static void Main(string[] args)
{
    // Listen to notification activation
    ToastNotificationManagerInterop.OnActivated += Notification_OnActivated;

    // Only do stuff like rendering window and other business logic if WinMain activation was not due to Toast Activation
    if (!ToastNotificationManagerInterop.WasProcessToastActivated())
    {
        // code that invokes normal winmain startup logic
    }
    else
    {
        // Don't do anything since the event handler registration above handles activation
    }
}

private void Notification_OnActivated(ToastNotificationActivatedEventArgsInterop e)
{
    // Obtain the arguments from the toast
    string args = e.Argument;

    // Obtain any user input (text boxes, menu selections) from the toast
    ValueSet userInput = e.UserInput;
 
    // TODO: Perform the corresponding action
}
```

### Win32 apps (Unpackaged)

**In your app's startup code** (WinMain), subscribe to the **OnActivated** event.

```cs

[System.STAThreadAttribute()]
static void Main(string[] args)
{
    // Listen to notification activation
    ToastNotificationManagerInterop.OnActivated += Notification_OnActivated;

    // Only do stuff like rendering window and other business logic if WinMain activation was not due to Toast Activation
    if (!ToastNotificationManagerInterop.WasProcessToastActivated())
    {
        // code that invokes normal winmain startup logic
    }
    else
    {
        // Don't do anything since the event handler registration above handles activation
    }
}

private void Notification_OnActivated(ToastNotificationActivatedEventArgsInterop e)
{
    // Obtain the arguments from the toast
    string args = e.Argument;

    // Obtain any user input (text boxes, menu selections) from the toast
    ValueSet userInput = e.UserInput;
 
    // TODO: Perform the corresponding action
}
```

# Remarks

<!-- TEMPLATE

    Explanation and guidance that doesn't fit into the Examples section.

    APIs should only throw exceptions in exceptional conditions; basically,
    only when there's a bug in the caller, such as argument exception.  But if for some
    reason it's necessary for a caller to catch an exception from an API, call that
    out with an explanation either here or in the Examples
-->

# API Notes

Introduce a **new class**...

### Microsoft.UI.Notifications.ToastNotificationManagerInterop

#### Methods

Method | Description | Return type | Min supported build | Supported app types
--|--|--|--|--
CreateToastNotifier() | Creates and initializes a new instance of the ToastNotifier that lets you raise a toast notification. | `Windows.UI.Notifications.ToastNotifier` | 10240 | All three
WasProcessToastActivated() | This method returns true if the winmain activation is for toast activation. Otherwise erturns false. It serves a dual process of delaying WinMain code path execution in case the toast event handler is being invoked. It will throw an exception if called from a UWP app. | `Windows.UI.Notifications.ToastNotifier` | 10240 | All three
GetToastCollectionManager() | Creates a ToastCollectionManager that you can use to save, update, and clear notification groups. | `Windows.UI.Notifications.ToastCollectionManager` | 15063 | All three
CreateToastNotifierForToastCollectionAsync(string collectionId) | Creates and initializes a new instance of the ToastNotifier that lets you raise a toast notification within the specified toast collection. Note that the platform API is called GetToastNotifierForToastCollectionIdAsync, I changed "Get" to "Create" and dropped "Id" as it seems excessively verbose. | `IAsyncOperation<` `Windows.UI.Notifications.ToastNotifier>` | 15063 | All three
GetHistoryForToastCollectionAsync(string collectionId) | Gets the notification history for the specified toast collection. Note that I dropped the "Id" from the platform API since it seemed excessively verbose. | `IAsyncOperation<` `Microsoft.UI.Notifications.ToastNotificationHistoryInterop>` | 15063 | All three


#### Omitted methods

We're explicitly omitting a few methods from the platform [ToastNotificationManager](https://docs.microsoft.com/en-us/uwp/api/Windows.UI.Notifications.ToastNotificationManager?view=winrt-19041#properties) and [ToastNotificationManagerForUser](https://docs.microsoft.com/en-us/uwp/api/windows.ui.notifications.toastnotificationmanagerforuser?view=winrt-19041#properties)... 

Method | Reason
--|--
CreateToastNotifier(string appId) | Only used by multi-app packages, which are rare or non-existent anymore... if we have requests for this we can always easily add it at any point in time
GetDefault() | 99% of apps are single-user apps, making 99% of developers always call GetDefault() is annoying.
GetForUser(Windows.System.User user) | Do we need to support MUA apps?
GetTemplateContent(ToastTemplateType) | These toast templates are from Windows 8, Windows 10 now uses ToastGeneric which we have builder classes for and this method is meaningless.
GetToastCollectionManager(string appId) | Only used by multi-app packages


#### Properties

Property | Description | Return type | Min supported build | Supported app types
--|--|--|--|--
History | Gets the ToastNotificationHistoryInterop object. | `Microsoft.UI.Notifications.ToastNotificationHistoryInterop` | 10240 | All three


#### Events

Event | Description | Args type | Min supported build | Supported app types
--|--|--|--|--
OnActivated | Event that is fired when a toast notification or action on a toast is clicked. This is not supported on UWP apps and will throw an exception if called from UWP. Win32 MSIX/sparse apps must first add values in their app manifest before calling this. | `(Microsoft.UI.Notifications.` `ToastNotificationActivatedEventArgsInterop e)` | 10240 | Win32 MSIX/sparse and Win32 (not UWP)



And add another **new class**...

### Microsoft.UI.Notifications.ToastNotificationHistoryInterop

Method | Description | Return type | Min supported build | Supported app types
--|--|--|--|--
Clear() | Removes all notifications sent by this app from action center. | `void` | 10240 | All three
GetHistory() | Gets the collection of toasts currently in Action Center. *Note: Should we change the name History? It's wonky, implies it'd include dismissed toasts.* | `IReadOnlyList<` `Windows.UI.Notifications.ToastNotification>` | 10240 | All three
Remove(string tag) | Removes an individual toast, with the specified tag label, from action center. | `void` | 10240 | All three
Remove(string tag, string group) | Removes a toast notification from the action using the notification's tag and group labels. | `void` | 10240 | All three
RemoveGroup(string group) | Removes a group of toast notifications, identified by the specified group label, from action center. | `void` | 10240 | All three

#### Omitted methods

We're explicitly omitting a few methods from the platform [ToastNotificationHistory](https://docs.microsoft.com/en-us/uwp/api/windows.ui.notifications.toastnotificationhistory?view=winrt-19041)... 

Method | Reason
--|--
Clear(string appId) | Only used by multi-app packages
GetHistory(string appId) | Only used by multi-app packages
Remove(string tag, string group, string appId) | Only used by multi-app packages
Remove(string group, string appId) | Only used by multi-app packages



And one more **new class**... (unfortunately we can't just instantiate ToastNotificationActivatedEventArgs).

### Microsoft.UI.Notifications.ToastNotificationActivatedEventArgsInterop

This class will only be used by Win32 MSIX/sparse and Win32 apps... there's nothing stopping UWP apps from using it, but it just won't ever do anything or be sent to them.

Or ideally we should have a converged activation experience with the rest of Reunion...

#### Properties

Property | Description | Return type | Min supported build | Supported app types
--|--|--|--|--
Argument | Gets the arguments that were originally specified on the toast corresponding to which action was taken on the toast. | `string` | 10240 | All three
UserInput | Gets the user inputs the user provided on the toast notification | `ValueSet` | 10240 | All three


# API Details

```cpp (but really MIDL3)
    namespace Microsoft.UI.Notifications
    {
        [contractversion(1.0)]
        apicontract NotificationsContract { };

        runtimeclass ToastNotificationManagerInterop;
        runtimeclass ToastNotificationActivatedEventArgsInterop;
        runtimeclass ToastNotificationHistoryInterop;

        [contract(NotificationsContract, 1.0)]
        [marshaling_behavior(standard)]
        runtimeclass ToastNotificationActivatedEventArgsInterop
        {
            String Argument { get; };
            Windows.Foundation.Collections.IMap<String, String> UserInput { get; };
        }

        [contract(NotificationsContract, 1.0)]
        [marshaling_behavior(standard)]
        runtimeclass ToastNotificationHistoryInterop
        {
            void Clear();
            Windows.Foundation.Collections.IVector<Windows.UI.Notifications.ToastNotification> GetHistory();
            void Remove(String tag);
            void Remove(String tag, String group);
            void RemoveGroup(String group);
        }


        [contract(NotificationsContract, 1.0)]
        [marshaling_behavior(standard)]
        static runtimeclass ToastNotificationManagerInterop
        {
            static Boolean WasProcessToastActivated{ get; };
            static event Windows.Foundation.EventHandler<ToastNotificationActivatedEventArgsInterop> OnActivated;
            static Windows.UI.Notifications.ToastNotifier CreateToastNotifier();
            static Windows.UI.Notifications.ToastCollectionManager GetToastCollectionManager();
            static Windows.Foundation.IAsyncOperation<Windows.UI.Notifications.ToastNotifier> CreateToastNotifierForToastCollectionAsync(String collectionId);
            static Windows.Foundation.IAsyncOperation<ToastNotificationHistoryInterop> GetHistoryForToastCollectionAsync(String collectionId);
        }
    }
```
# Appendix

* When the developer calls ToastNotificationManagerInterop.CreateToastNotifier(), we'll handle the differences between UWP/Win32 MSIX/spase and Win32.

* If running with identity: We simply call CreateToastNotifier()

* If not running with identity (Win32): We'll first register the app by obtaining its display name and icon and using the EXE path for the AUMID, and then we'll call CreateToastNotifier(aumid).

* We'll do the same forking logic for when they access .History.

* We will support http image downloads for Win32 apps without identity that was not supported earlier by giving super capabilities to full trust applications (Toast and Internet capabilities)
