# App Notifications in Windows App SDK

# Background

App Notifications are UI popups that that contain rich text, controls and images to
display a message to the user. They are developer driven and originate from a target application
that is installed by a user on the local device. It is not sufficient for a notification popup on the
screen to simply be displayed to the user, it also needs to be actionable. For example, the user
should be able to click on a notification popup to launch an app in the correct context. For example, a
news article related notification is expected to launch the News app along with the article in question in
the foreground. Another actionable scenario is for the user to actually interact with the contents
of the notification popup like a UI control button. For example, a messaging app like Teams that displays a
message from another user could have a "Respond To" textbox and button so that the user can directly
respond to the message in the popup without having to launch the application. This scenario triggers
a background process on behalf of the application (with no UI) which inturn processes the "Reply To"
message and forwards the response to the other device.

Notification messages could have a local or cloud based origin. In the case of local notifications, the message
always originates from the app installed on the device. For cloud notifications, the message always
originates from a remote application service that targets the locally installed app in question.

Here is a visual representation of a simple notification with no interactive controls:

![Notification Simple](https://docs.microsoft.com/windows/apps/design/shell/tiles-and-notifications/images/send-toast-02.png)

Here is a visual representation of a notification with simple button controls:

![Notification Interactive 1](https://docs.microsoft.com/windows/apps/design/shell/tiles-and-notifications/images/adaptivetoasts-structure.jpg)

Here is a visual representation of a notification with a Message "Reply To" option:

![Toast Interactive 2](https://docs.microsoft.com/windows/apps/design/shell/tiles-and-notifications/images/toast-notification.png)

For more details see:

-   [Toast Notification WinRT APIs](https://docs.microsoft.com//uwp/api/Windows.UI.Notifications.ToastNotification?view=winrt-20348)
    Defines all the API constructs that we have for notifications in WinRT today using the
    Windows SDK.
-   [Toast Notification UX Guidance using Toolkit](https://docs.microsoft.com/windows/apps/design/shell/tiles-and-notifications/toast-ux-guidance)
    Defines the UX Guidance for developers who want to display notifications using the toolkit libraries.
-   [Sending Local Toasts using C# using Toolkit](https://docs.microsoft.com/windows/apps/design/shell/tiles-and-notifications/send-local-toast?tabs=uwp)
    Defines how an app developer can send interactive notifications to the user and setup activation
    handlers for these notifications using the Toolkit libraries.

## The problems today

**Cloud Notifications integration with Windows App SDK**: While we support Push scenarios for Raw notification
on behalf of unpackaged applications, we do not support Cloud sourced App Notifications. We need
to fill this feature gap.

**API fragmentation**: There are too many API technologies that are published today to simply
Display notifications and setup their activation handlers: Windows SDK, Win32 Notification Activations via the
Nitro Model and the Windows Toolkit which is a Nuget library. It gets overwhelming for a developer
who does not understand all these technologies to ramp up and get notifications working for their
app.

**Support and Troubleshooting Notifcation Issues**: Because of the API fragmentation mentioned above, it
is also very difficult to diagnose issues when developers hit them and a large portion of developer
cycles are spent diagnosing and troubleshooting problems in various API stacks instead of a single
stack.

**Registration**: The Windows SDK today provides AppId overloads to developers who can specify their
own Identifier for Unpackaged apps. The platform is currently designed to create an explicit
Registration for this overloaded AppId which causes all sorts of problems (string size limits being
hit, Personally Identifiable Information stored as part of AppIds, Registrations tagged with
incorrect App Type etc). The WinApp SDK gets rid of the AppId overloads in the Public APIs.

**Activation**: Setting up activation handlers using Background Triggers is challenging for
developers because we don't have downlevel support for all OS SKUs. Moreover, the steps for setting
up activation handlers vary greatly for different app types MSIX Vs Unpackaged Vs UWP. We will need
to abstract away the activation technology and simplify this process for developers for all
supported downlevel OS SKUs.

# Description

This API enables all Win32 applications to display app notifications irrespective
of their app type. This includes unpackaged apps and packaged win32 (MSIX Desktop Bridge, MSIX
Win32App, Sparse Signed Packages). Moreover, all scenarios should adhere to OS resource
management policies like Power Saver, Network Attribution (amount of data an app uses), enterprise
group policies, etc. The WinAppSDK will abstract away the complexities of
dealing with Notification delivery and related activations as much as possible freeing the developer
to focus on other app related challenges.

The App Notification API does the following:

-   Allow Unpackaged apps to register for notifications.
-   Allow Packaged apps to register for notifications.
-   Allow Unpackaged apps to display cloud sourced notifications.
-   Allow packaged apps to display cloud sourced notifications.
-   Allow packaged apps to display local notifications
-   Allow unpackaged apps to display local notifications
-   Allow packaged apps to Update/Delete their local notifications.
-   Allow unpackaged apps to Update/Delete their local notifications.
-   Allow packaged applications to process notification activators.
-   Allow unpackaged apps to process notification activators.

# Examples

## Packaged App Registering and handling a notification

This scenario is specifically geared towards Packaged apps that need to send an app notification. An app
Developer Registers their app for notifications and sets it up for background\foreground
activation. Adding a AppNotificationActivated event handler signals that the app is ready to accept and handle
an action in the foreground where the user clicks on a Notification in the action centre or a UI element in
the payload body (like a Button). The developer can inturn run some business logic in their app in
response to the UI Action.

```cpp

CLSID const c_comServerId = { 0x43136EB5,0xD36C,0x11CF,{0xAD,0xBC,0x00,0xAA,0x00,0xA8,0x00,0x33} };

int main()
{
    AppNotificationActivationInfo activationInfo{ winrt::guid(c_comServerId) };
    AppNotificationManager::Default().RegisterActivator(activationInfo);

    auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
    auto kind = args.Kind();

    if (kind == ExtendedActivationKind::Launch)
    {
        // App is launched in Foreground. So intercept toast activators via Foreground event
        const auto token = AppNotificationManager::Default().AppNotificationActivated([](const auto&, const AppNotificationActivatedEventArgs& notificationActivatedEventArgs)
        {
            ProcessNotificationArgs(notificationActivatedEventArgs);
        });

        // App does Foreground Stuff Here

        // Cleanup
        AppNotificationManager::Default().AppNotificationActivated(token);
    }
    else if (kind == ExtendedActivationKind::AppNotification)
    {
        auto notificationActivatedEventArgs = args.Data().as<AppNotificationActivatedEventArgs>();
        ProcessNotificationArgs(notificationActivatedEventArgs);
    }

    return 0;
}
```

## Unpackaged app Registering and handling a notification

Similar to packaged apps, unpackaged apps can also Register to send app notifications and act as
targets for activation events. There is one basic difference in the Registration for
Unpackaged apps versus their packaged counterparts: they will need to specify their own friendly App
DisplayName and IconUri since they don't have an app manifest file that contains the same.

```cpp
int main()
{
    PCWSTR const c_iconName = L"icon.png";
    std::filesystem::path binaryPath = wil::GetModuleFileNameW<std::wstring>(nullptr);
    std::filesystem::path directoryPath = binaryPath.parent_path();
    std::filesystem::path iconPath = directoryPath / std::filesystem::path(c_iconName);

    Uri iconUri(iconPath.wstring().c_str());
    AppNotificationActivationInfo activationInfo(L"SampleApp", iconUri);
    AppNotificationManager::Default().RegisterActivator(activationInfo);

    auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
    auto kind = args.Kind();

    if (kind == ExtendedActivationKind::Launch)
    {
        // App is launched in FG. So intercept toast activators via FG event
        const auto token = AppNotificationManager::Default().AppNotificationActivated([](const auto&, const AppNotificationActivatedEventArgs& notificationActivatedEventArgs)
            {
                ProcessNotificationArgs(notificationActivatedEventArgs);
            });

        // App does Foreground Stuff Here

        // Cleanup
        AppNotificationManager::Default().AppNotificationActivated(token);
    }
    else if (kind == ExtendedActivationKind::AppNotification)
    {
        auto notificationActivatedEventArgs = args.Data().as<AppNotificationActivatedEventArgs>();
        ProcessNotificationArgs(notificationActivatedEventArgs);
    }

    return 0;
}
```

## Displaying an App Notification

To display a notification, an app needs to define a payload using an xml schema. In addition, the developer can set a tag and group property which allows the app to replace a prior notification with the same tag and group with an updated version of the payload.
Finally, the ExpiresOnReboot property can also be set to ensure that the notification is automatically deleted from
the Action Centre after device reboots.

```cpp
// Display a notification in action centre using a tag and group
void DisplayNotification(const winrt::Windows::Data::Xml::Dom::XmlDocument& doc)
{
    AppNotification notification(doc);
    // Setting Tag, Group and ExpiresOnReboot properties are optional
    notification.Tag(L"Tag");
    notification.Group(L"Group");
    notification.ExpiresOnReboot(true);
    AppNotificationManager::Default().Show(notification);
}
```
## Processing an Activation

The app will need to process the activator in response to a User interacting with the notification in Action Centre. 2 common
scenarios here are

1. Have the app launch in the foreground in a specific UI context OR
2. Have the app process an action specific behavior (like a button press in the payload body) in the background.

```cpp
//<toast launch="action=openThread&amp;threadId=92187">
//  <visual>
//      <binding template="ToastGeneric">
//          <text hint-maxLines="1">Jill Bender</text>
//          <text>Check out where we camped last weekend! Incredible!!</text>
//          <image placement="hero" src="https://unsplash.it/360/180?image=1043" />
//      </binding>
//  </visual>
//  <actions>
//      <input id="textBox" type="text" placeHolderContent="reply" / >
//      <action
//          content="Send"
//          imageUri="Assets/Icons/send.png"
//          hint-inputId="textBox"
//          activationType="background"
//          arguments="action=reply&amp;threadId=92187" />
//  </actions>
//</toast>

const winrt::hstring c_notificationLaunchAction = L"action=openThread&amp;threadId=92187";
const winrt::hstring c_notificationReplyButtonAction = L"action=reply&amp;threadId=92187";

void ProcessNotificationArgs(const AppNotificationActivatedEventArgs& notificationActivatedEventArgs)
{
    if (notificationActivatedEventArgs.ActivationArgs() == c_notificationLaunchAction)
    {
        // The user clicks on the notification: So use the launchAction to do stuff
        // Do LaunchAction Stuff
    }
    else if (notificationActivatedEventArgs.ActivationArgs() == c_notificationReplyButtonAction)
    {
        // The user clicked on the reply button on the notification. So query the input field
        auto input = notificationActivatedEventArgs.UserInput();
        auto replyBoxText = input.Lookup(L"ReplyBox");

        // Process the reply text
        ProcessReply(replyBoxText);
    }
}
```

## Processing Active Notifications

We define active notifications as payloads that have already been displayed by the app and show up in the
Action Centre. We can perform a number of operations on these notifications such as retrieval and
deletion.

```cpp
// Get a List of all active notifications displayed in the Action Centre
winrt::Windows::Foundation::IAsyncOperation<Windows::Foundation::Collections::IVector<AppNotification>> GetNotificationListASync()
{
    auto notifications = co_await AppNotificationManager::Default().GetAllAsync();
    co_return notifications;
}

// Remove a notification from action centre using tag and group
winrt::Windows::Foundation::IAsyncAction RemoveNotification(const winrt::hstring tag, const winrt::hstring group)
{
    co_await AppNotificationManager::Default().RemoveWithTagGroupAsync(tag, group);
}
```

## Notification Progress Updates

Sometimes a developer would like to show progress bar related updates in a notification:

![Notification Progress](https://docs.microsoft.com/windows/apps/design/shell/tiles-and-notifications/images/toast-progressbar-annotated.png)

To accomplish that, the developer will need to use the AppNotificationProgressData construct to update the progress bar on the screen.

```cpp
// Send first Notification Progress Update
void SendUpdatableNotificationWithProgress()
{
    winrt::hstring tag = L"weekly-playlist";
    winrt::hstring group = L"downloads";

    winrt::hstring payload =
    LR"(<toast launch="action = viewDownload &amp; downloadId = 9438108">
        <visual>
            <binding template = "ToastGeneric">
                <text>Downloading this week's new music...</text>
                <progress
                    title = "{progressTitle}
                    value = "{progressValue}"
                    valueStringOverride = "{progressValueString}"
                    status = "{progressStatus}" />
            </binding>
        </visual>
    </toast>)";

    XmlDocument doc;
    doc.LoadXml(payload);
    AppNotification notification(doc);
    notification.Tag(tag);
    notification.Group(group);

    // Assign initial values for first notification progress UI
    AppNotificationProgressData data;
    data.Title(L"Weekly playlist"); // Binds to {progressTitle} in xml payload
    data.Value(0.6); // Binds to {progressValue} in xml payload
    data.ValueStringOverride(L"15/26 songs"); // Binds to {progressValueString} in xml payload
    data.Status(L"Downloading..."); // Binds to {progressStatus} in xml payload
    data.SequenceNumber(1);

    notification.Progress(data);
    AppNotificationManager::Default().Show(notification);
}

// Send subsequent progress updates
winrt::Windows::Foundation::IAsyncAction UpdateProgressAsync()
{
    winrt::hstring tag = L"weekly-playlist";
    winrt::hstring group = L"downloads";

    // Assign new values
    // Note that you only need to assign values that changed. In this example we don't assign progressStatus since we don't need to change it
    AppNotificationProgressData data;
    data.Value(0.7); // Binds to {progressValue} in xml payload
    data.ValueStringOverride(L"18/26 songs"); // Binds to {progressValueString} in xml payload
    data.SequenceNumber(2);

    auto result = co_await AppNotificationManager::Default().UpdateProgressDataAsync(data, tag, group);
    if (result == AppNotificationProgressResult::AppNotificationNotFound)
    {
        LOG_HR_MSG(E_NOT_SET, "Toast Progress Update Failed since the previous notification update is missing or has been cleared by the user!");
    }
}
```
# Remarks

## Registration

The developer should always call the Notification Registration API first to register the current process as
the Activator target.

## Foreground API calls

The developer should always subscribe to AppNotification activation foreground events to intercept notification related actions if
the app happens to be running in the foreground.

## Manifest Registration

For MSIX, the COM activator GUID and the exe need to be registered in the manifest. The launch args
would need to be pre-set to a well-known string that defines Activation Triggers.

```xml
<Extensions>
  <com:Extension Category="windows.comServer">
    <com:ComServer>
      <com:ExeServer Executable="SampleBackgroundApp\SampleBackgroundApp.exe" DisplayName="SampleBackgroundApp" Arguments="----AppNotificationActivationServer">
        <com:Class Id="{GUIDEntryPoint}" />
      </com:ExeServer>
    </com:ComServer>
  </com:Extension>
</Extensions>
```

# API Details

```c#
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

import "..\AppLifecycle\AppLifecycle.idl";

namespace Microsoft.Windows.AppNotifications
{
    // The Registration Info for Packaged and Unpackaged Notification Activations
    runtimeclass AppNotificationActivationInfo
    {
        // Initialize using a manifest defined COM Activator Id. Only applicable to Packaged Win32 applications
        AppNotificationActivationInfo(Guid taskClsid);

        // Initialize using Notification Assets. Only applicable to Unpackaged Win32 applications which need to specify their own assets like DisplayName and Icon.
        AppNotificationActivationInfo(String displayName, Windows.Foundation.Uri iconUri);

        // The CLSID associated with the Client COM server that Windows App SDK will activate
        Guid TaskClsid{ get; };

        // The App friendly DisplayName for the Notification in Action Centre 
        String DisplayName{ get; };

        // The full file path for the icon image
        Windows.Foundation.Uri IconUri{ get; };
    }

    // Event args for the Notification Activation
    runtimeclass AppNotificationActivatedEventArgs
    {
        // Arguments from the invoked button. Empty for Default Activation with no launch args specified in payload.
        String ActivationArgs{ get; };

        // The data from the input elements of a Notification like a TextBox
        Windows.Foundation.Collections.IMapView<String, String> UserInput{ get; };
    }

    // Notification Progress Data
    runtimeclass AppNotificationProgressData
    {
        // Initializes a new Instance of NotificationProgressData
        AppNotificationProgressData();

        // Gets or sets the sequence number of this notification data.
        // When multiple NotificationProgressData objects are received, the system displays the data with the greatest non-zero number. 
        UInt32 SequenceNumber;

        // Gets/Sets the value for the title. Binds to {progressTitle} in progress xml tag.
        String Title;

        // Gets/Sets the Value for the numerical Progress percentile: a number between 0 and 1. Binds to {progressValue} in progress xml tag.
        Double Value;

        // Gets/Sets the Value for the Progress String. Binds to {progressValueString} in progress xml tag
        String ValueStringOverride;

        // Gets/Sets the Value for the Status. Binds to {progressStatus} in progress xml tag
        String Status;
    }

    // The Notification User Setting or Notification Group Policy Setting
    enum AppNotificationSetting
    {
        Enabled, // Notification is not blocked by settings or group policy
        DisabledForApplication, // Notification is blocked by a user defined App Setting
        DisabledForUser, // Notification is blocked by a user defined Global Setting
        DisabledByGroupPolicy, // Notification is blocked by Group Policy
        DisabledByManifest, // Notification is blocked by a setting in the manifest. Only for packaged applications.
    };

    // The Result for a Notification Progress related operation
    enum AppNotificationProgressResult
    {
        Succeeded, // The progress operation succeeded
        AppNotificationNotFound, // The progress operation failed to find a Notification to process updates
    };

    // The Priority of the Notification UI associated with it's popup in the Action Centre
    enum AppNotificationPriority
    {
        Default, // The notification should have default behavior in terms of delivery and display priority during connected standby mode.
        High, // The notification should be treated as high priority. For desktop PCs, this means during connected standby mode the incoming notification can turn on the screen for Surface-like devices if it doesn't have a closed lid detected.
    };

    runtimeclass AppNotification
    {
        AppNotification(Windows.Data.Xml.Dom.XmlDocument payload);

        // Unique identifier used to replace a notification within a group.
        String Tag;

        // Unique identifier for a Notification group in the app
        String Group;

        // A unique identifier for the Notification generated by the platform.
        UInt32 Id { get; };

        // The notification Xml Payload
        Windows.Data.Xml.Dom.XmlDocument Payload{ get; };

        // Gets or sets additional information about the Notification progress.
        AppNotificationProgressData Progress;

        // Gets or sets the time after which a Notification should not be displayed.
        Windows.Foundation.DateTime Expiration;

        // Indicates whether the Notification will remain in the Action Center after a reboot.
        Boolean ExpiresOnReboot;

        // Gets or sets the priority for a Notification.
        // Hints on how and at what urgency level a notification should be presented to the user (whether to wake up the screen, etc).
        AppNotificationPriority Priority;

        // Gets or sets whether a Notification's pop-up UI is displayed on the user's screen.
        Boolean SuppressDisplay;
    }

    // The manager class which encompasses all App Notification API Functionality
    [experimental]
    runtimeclass AppNotificationManager
    {
        // Gets a Default instance of a AppNotificationManager
        static AppNotificationManager Default{ get; };

        // Register an activator using an ActivationInfo context and caches the token for unregister
        void RegisterActivator(AppNotificationActivationInfo details);

        // Unregisters the activator and removes the cached Registration token.
        void UnregisterActivator();

        // Event handler for Notification Activations
        event Windows.Foundation.TypedEventHandler<Microsoft.Windows.AppLifecycle.ExtendedActivationKind, AppNotificationActivatedEventArgs> AppNotificationActivated;

        // Displays the Notification in Action Center
        void Show(AppNotification notification);

        // Updates the Notification for a Progress related operation using Tag and Group
        Windows.Foundation.IAsyncOperation<AppNotificationProgressResult> UpdateProgressDataAsync(AppNotificationProgressData data, String tag, String group);

        // Updates the Notification for a Progress related operation using Tag
        Windows.Foundation.IAsyncOperation<AppNotificationProgressResult> UpdateProgressDataAsync(AppNotificationProgressData data, String tag);

        // Get the Notification Setting status for the app
        AppNotificationSetting Enablement { get; };

        // Removes a specific Notification with a specific NotificationIdentifier from Action Centre
        Windows.Foundation.IAsyncAction RemoveByIdAsync(UInt32 notificationId);

        // Removes a Notification having a specific tag
        Windows.Foundation.IAsyncAction RemoveWithTagAsync(String tag);

        // Removes a Notification having a specific tag and group
        Windows.Foundation.IAsyncAction RemoveWithTagGroupAsync(String tag, String group);

        // Remove all Notifications for a specific group
        Windows.Foundation.IAsyncAction RemoveGroupAsync(String group);

        // Removes all the Notifications for the App from Action Centre
        Windows.Foundation.IAsyncAction RemoveAllAsync();

        // Gets all the Notifications for the App from Action Centre
        Windows.Foundation.IAsyncOperation<Windows.Foundation.Collections.IVector<AppNotification> > GetAllAsync();
    }
}

```

# Appendix

-   To support cloud sourced app notifications, the developer will need to register the Notification Activator in addition to
    the Push Activator registrations that are already being done. The Windows App SDK will in turn
    figure out the complexity of mapping these cloud based notifications to the correct App Notification Activator.
-   Since building XML payloads at runtime is non-trivial, we encourage developers to utilize
    the [Windows Community Toolkit](https://docs.microsoft.com/windows/communitytoolkit/),
    specifically the
    [ToastContentBuilder](https://docs.microsoft.com/dotnet/api/microsoft.toolkit.uwp.notifications.toastcontentbuilder)
    APIs to construct the XML payload in the short term.
