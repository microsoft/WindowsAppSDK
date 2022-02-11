# Toast Notifications in Windows App SDK

# Background

Toast Notifications are UI popups that are added that contain rich text, controls and images to display a message to the user. They are developer driven and originate from a target application that is installed by a user on the local device. It is not sufficient for a toast popup on the screen to simply be displayed to the user, it also needs to be actionable. For example, the user should be able to click on a toast popup to launch an app in the correct context. For example, a news article related toast is expected to launch the News app along  with the article in question in the foreground. Another actionable scenario is for the user to actually interact with the contents of the toast popup like a UI control button. For example, a messaging app like Teams that displays a message from another user could have a "Respond To" textbox and button so that the user can directly respond to the message in the popup without having to launch the application. This scenario triggers a background process on behalf of the application (with no UI) which inturn processes the "Reply To" message and forwards the response to the other device.

Toast messages could have a local or cloud based origin. In the case of local toasts, the message always originates from the app installed on the device. For cloud toasts, the message always originates from a remote application service that targets the locally installed app in question. 

Here is a visual representation of a Simple Toast with no interactive controls:

![Toast Simple](https://docs.microsoft.com/en-us/windows/apps/design/shell/tiles-and-notifications/images/send-toast-02.png)

Here is a visual representation of a Toast with simple button controls:

![Toast Interactive 1](https://docs.microsoft.com/en-us/windows/apps/design/shell/tiles-and-notifications/images/adaptivetoasts-structure.jpg)

Here is a visual representation of a Toast with a Message "Reply To" option:

![Toast Interactive 2](https://docs.microsoft.com/en-us/windows/apps/design/shell/tiles-and-notifications/images/toast-notification.png)

For more details see:


-   [Toast Notification WinRT APIs](https://docs.microsoft.com/en-us/uwp/api/Windows.UI.Notifications.ToastNotification?view=winrt-20348)
    Defines all the API constructs that we have for Toast Notifications in WinRT today using the Legacy Windows SDK.
-   [Toast Notification UX Guidance using Toolkit](https://docs.microsoft.com/en-us/windows/apps/design/shell/tiles-and-notifications/toast-ux-guidance)
    Defines the UX Guidance for developers who want to display toasts using the toolkit libraries.
-   [Sending Local Toasts using C# using Toolkit](https://docs.microsoft.com/en-us/windows/apps/design/shell/tiles-and-notifications/send-local-toast?tabs=uwp)
    Defines how an app developer can send interactive toasts to the user and setup activation handlers for these toasts using the Toolkit libraries.

## The problems today

**Cloud Toast integration with Windows SDK**: While we support Push scenarios for Raw notification on behalf of unpackaged applications in the Windows SDK 1.0, we do not support Cloud Toasts. We need to fill this gap for 1.1 and beyond.

**API fragmentation**: There are too many API technologies that are published today to simply Display toasts and setup their activation handlers: Windows Legacy SDK, Win32 Toast Activations via the Nitro Model and the Windows Toolkit which is a Nuget library. It gets overwhelming for a developer who does not understand all these technologies to ramp up and get toast support working for their app. 

**Support and Troubleshooting Toast Issues**: Because of the API fragmentation mentioned above, it is also very difficult to diagnose issues when developers hit them and a large portion of developer cycles are spent dignosing and troubleshooting problems in various API stacks instead of a single stack.

**Activation**: Setting up activation handlers using Background Toast Triggers is challenging for developers because we don't have downlevel support for all OS SKUs. Moreover, the steps for setting up activation handlers vary greatly for different app types MSIX Vs Unpackaged Vs UWP. We will need to abstract away the activation technology and simplify this process for developers for all supported downlevel OS SKUs. 

**Toast Composition**: There are well known gaps in the Legacy Windows SDK today in the area of composing the Toast content. The Windows Toolkit gets around this limitation by providing a well-defined object model to compose toasts but all developers don't use the Toolkit.

# Description

At a high level, we need to provide a way for all Win32 applications to display toasts irrespective of their app type. This includes unpackaged apps and packaged win32
(MSIX Desktop Bridge, MSIX Win32App, Sparse Signed Packages). Moreover, all Toast scenarios should
adhere to OS resource management policies like Power Saver, Network Attribution (amount of data an
app uses), enterprise group policies, etc. The Windows App SDK Push component will abstract away the
complexities of dealing with Toast delivery and toast related activations as much as
possible freeing the developer to focus on other app related challenges.

We will prioritize the following feature set for Toast Notifications in Windows App SDK:

-   Cloud sourced Toasts for Unpackaged Win32 apps.
-   Toast Registrations for Unpackaged apps.
-   Toast Registrations for Packaged apps
-   Local Toast delivery and CRUD operations for Packaged Win32 apps.
-   Local Toasts delivery and CRUD operations for unpackaged Win32 apps.

The following feature set will not be prioritized for the next release but will be prioritized for the second half of 2022:

-   Object Model to compose Toasts without having to rely on Xml templates.
-   Support for Granular toasts and toast collections.

# Examples

## Packaged App Toast Registration

This scenario is specifically geared towards Packaged apps and toasts. An app Developer Registers their app for Toast Notifications and sets it up for background\foreground activation depending on the launch arguments. 

```cpp
int main()
{
    auto activationInfo = ToastActivationInfo::CreateToastActivationInfoFromGuid(winrt::guid(c_comServerId));
    ToastNotificationManager::RegisterActivator(activationInfo);

    auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
    auto kind = args.Kind();

    if (kind == ExtendedActivationKind::Launch)
    {
        // App is launched in FG. So intercept toast activators via FG event
        const auto token = ToastNotificationManager::ToastActivated([](const auto&, ToastActivatedEventArgs const& toastActivatedEventArgs)
        {
                ProcessToastArgs(toastActivatedEventArgs);
        });

        // App does Foreground Stuff Here

        // Cleanup
        ToastNotificationManager::ToastActivated(token);
    }
    else if (kind == ExtendedActivationKind::ToastNotification)
    {
        auto toastActivatedEventArgs = args.Data().as<ToastActivatedEventArgs>();
        ProcessToastArgs(toastActivatedEventArgs);
    }

    return 0;
}
```

## Unpackaged app Toast Registration

Similarly unpackaged apps can also Register themselves to send and act as targets for toast notifications.

```cpp
int main()
{
        ToastDetails details = winrt::make<ToastDetails>(
        L"SampleApp",
        L"c:\test\icon.png",
        Windows::UI::Colors::LightGray());
    auto activationInfo = ToastActivationInfo::CreateToastActivationInfoFromToastDetails(details);
    ToastNotificationManager::RegisterActivator(activationInfo);

    auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
    auto kind = args.Kind();

    if (kind == ExtendedActivationKind::Launch)
    {
        // App is launched in FG. So intercept toast activators via FG event
        const auto token = ToastNotificationManager::ToastActivated([](const auto&, ToastActivatedEventArgs const& toastActivatedEventArgs)
            {
                ProcessToastArgs(toastActivatedEventArgs);
            });

        // App does Foreground Stuff Here

        // Cleanup
        ToastNotificationManager::ToastActivated(token);
    }
    else if (kind == ExtendedActivationKind::ToastNotification)
    {
        auto toastActivatedEventArgs = args.Data().as<ToastActivatedEventArgs>();
        ProcessToastArgs(toastActivatedEventArgs);
    }

    return 0;
}
```

## Displaying a Toast

The app will need to display a toast to the user. To do this we recommend that the developer always sets a tag and group field so that similar toasts can replace it in the future. They also have the option to delete the toast automatically from ActionCentre on subsequent reboots by setting the ExpiresOnReboot property to true.

```cpp
void DisplayToast(winrt::Windows::Data::Xml::Dom::XmlDocument doc)
{
    ToastNotification toast = winrt::make<ToastNotification>(doc);
    toast.Tag(L"Tag");
    toast.Group(L"Group");
    toast.ExpiresOnReboot(true);
    ToastNotificationManager::ShowToast(toast);
}
```

## Processing a Toast Activation

The app will need to process the activator in response to a User activating the toast. 2 common scenarios here are 
1) Have the app launch in the foreground in a specific UI context OR 
2) Have the app process a toast action (like a button press in the toast body) in the background. 

```cpp
void ProcessToastArgs(ToastActivatedEventArgs const& toastActivatedEventArgs)
{
    if (toastActivatedEventArgs.ActivationArgs() == c_toastLaunchAction)
    {
        // The user clicks on the toast: So use the launchAction to do stuff
        // Do LaunchAction Stuff
    }
    else if (toastActivatedEventArgs.ActivationArgs() == c_toastReplyButtonAction)
    {
        // The user clicked on the reply button on the toast. So query the input field
        auto input = toastActivatedEventArgs.UserInput();
        auto replyBoxText = input.Lookup(L"ReplyBox");

        // Process the reply text
        ProcessReply(replyBoxText);
    }
}
```
## Processing Toast History

The ToastHistory component is always used to perform Delete and Get operations on behalf of the app.

```cpp
// Get a List of all toasts from the Action Centre
winrt::Windows::Foundation::IAsyncOperation<Windows::Foundation::Collections::IVectorView<ToastNotification> > GetToastListASync()
{
    auto toastHistory = ToastNotificationManager::History();
    auto toasts = co_await toastHistory.GetAllAsync();
    co_return toasts;
}

// Remove a prior toast using tag and group
winrt::Windows::Foundation::IAsyncAction RemoveToast(const winrt::hstring& tag, const winrt::hstring& group)
{
    auto toastHistory = ToastNotificationManager::History();
    co_await toastHistory.RemoveWithTagGroupAsync(tag, group);
}
```

## Toast Progress Updates

Sometimes a developer would like to show progress bar related updates in a toast like this. To accomplish that, the developer will need to use the ToastProgressData construct.

```cpp
// Send first Toast Progress Update
void SendUpdatableToastWithProgress()
{
    winrt::hstring tag = L"weekly-playlist";
    winrt::hstring group = L"downloads";

    const winrt::hstring payload = L"<toast launch=\"action = viewDownload &amp; downloadId = 9438108\">"
                                L"<visual>"
                                    L"<binding template = \"ToastGeneric\">"
                                        L"<text>Downloading this week's new music...</text>"
                                        L"<progress"
                                            L"title = \"{progressTitle}\""
                                            L"value = \"{progressValue}\""
                                            L"valueStringOverride = \"{progressValueString}\""
                                            L"status = \"{progressStatus}\" />"
                                    L"</binding>"
                                L"</visual>"
                            L"</toast>";

    winrt::Windows::Data::Xml::Dom::XmlDocument doc = winrt::make<winrt::Windows::Data::Xml::Dom::XmlDocument>();
    doc.LoadXml(payload);
    ToastNotification toast = winrt::make<ToastNotification>(doc);
    toast.Tag(tag);
    toast.Group(group);

    // Assign initial values for first toast progress UI
    ToastProgressData data = winrt::make<ToastProgressData>();
    data.Title(L"Weekly playlist"); // Binds to {progressTitle} in xml payload
    data.Value(0.6); // Binds to {progressValue} in xml payload
    data.ValueStringOverride(L"15/26 songs"); // Binds to {progressValueString} in xml payload
    data.Status(L"Downloading..."); // Binds to {progressStatus} in xml payload
    data.SequenceNumber(1); // The sequence number has to be incremental for the platform to render progress

    toast.Data(data);
    ToastNotificationManager::ShowToast(toast);
}

// Send subsequent progress updates
winrt::Windows::Foundation::IAsyncAction UpdateProgressAsync()
{
    winrt::hstring tag = L"weekly-playlist";
    winrt::hstring group = L"downloads";

    // Assign new values
    // Note that you only need to assign values that changed. In this example we don't assign progressStatus since we don't need to change it
    ToastProgressData data = winrt::make<ToastProgressData>();
    data.Value(0.7); // Binds to {progressValue} in xml payload
    data.ValueStringOverride(L"18/26 songs"); // Binds to {progressValueString} in xml payload
    data.SequenceNumber(2);

    auto result = co_await ToastNotificationManager::UpdateToastProgressDataAsync(data, tag, group);
    if (result != ToastProgressResult::Succeeded)
    {
        LOG_HR_MSG(E_UNEXPECTED, "Toast Progress Update Failed!");
    }
}
```

# Remarks

## Registration

The developer should always call the Toast Registration API first to register the current process as the Activator target.

## Foreground API calls

The developer should always subscribe to toast activation foreground events to intercept toasts if the app happens to be running in the foreground.

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

## Manifest Registration

For MSIX, the COM activator GUID and the exe need to be registered in the manifest. The launch args
would need to be pre-set to a well-known string that defines Toast Activation Triggers.

```xml
<Extensions>
  <com:Extension Category="windows.comServer">
    <com:ComServer>
      <com:ExeServer Executable="SampleBackgroundApp\SampleBackgroundApp.exe" DisplayName="SampleBackgroundApp" Arguments="----ToastActivationServer">
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

namespace Microsoft.Windows.ToastNotifications
{
    [experimental]
    // The Shell asset details for Unpackaged App Registrations 
    runtimeclass ToastDetails
    {
        // Initialize using Shell assets like DisplayName and icons
        ToastDetails(String displayName, String iconPath, Windows.UI.Colors iconBackgroundColor);

        // The App friendly DisplayName for the toast in Action Centre 
        String DisplayName { get; };

        // The full file path for the icon image
        String IconPath { get; };

        // The icon color
        Windows.UI.Colors IconBackgroundColor{ get; };
    }

    [experimental]
    // The Registration Info for Packaged and Unpackaged Toast Activations
    runtimeclass ToastActivationInfo
    {
        // Initialize using a manifest defined COM Activator Id. Only applicable to Packaged Win32 applications
        static ToastActivationInfo CreateToastActivationInfoFromGuid(Guid taskClsid);

        // Initialize using an ActivationDetails context for Shell. Only applicable to Unpackaged Win32 applications which need to specify Shell assets.
        static ToastActivationInfo CreateToastActivationInfoFromToastDetails(ToastDetails details);

        // The CLSID associated with the Client COM server that Windows App SDK will activate
        Guid TaskClsid{ get; };

        // The Shell assets associated with the Unpackaged app
        ToastDetails Details{ get; };
    };

    [experimental]
    // Event args for the Toast Activation
    runtimeclass ToastActivatedEventArgs
    {
        // Arguments from the invoked button. Empty for Default Activation with no launch args specified in payload.
        String ActivationArgs{ get; };

        // The data from the input elements of a toast like a TextBox
        Windows.Foundation.Collections.IMapView<String, String> UserInput{ get; };
    };

    [experimental]
    // Toast Progress Data
    runtimeclass ToastProgressData
    {
        // Initializes a new Instance of ToastProgressData
        ToastProgressData();

        // Gets or sets the sequence number of this notification data.
        // When multiple ToastProgressData objects are received, the system displays the data with the greatest non-zero number. 
        UInt32 SequenceNumber;

        // Gets/Sets the value for the title. Binds to {progressTitle} in progress xml tag.
        String Title;

        // Gets/Sets the Value for the numerical Progress percentile: a number between 0 and 1. Binds to {progressValue} in progress xml tag.
        Double Value;

        // Gets/Sets the Value for the Progress String. Binds to {progressValueString} in progress xml tag
        String ValueStringOverride;

        // Gets/Sets the Value for the Status. Binds to {progressStatus} in progress xml tag
        String Status;
    };

    [experimental]
    [flags]
    // The Toast User Setting or Toast Group Policy Setting
    enum ToastNotificationSetting
    {
        Enabled, // Toast is not blocked by settings or group policy
        DisabledForApplication, // Toast is blocked by a user defined App Setting
        DisabledForUser, // Toast is blocked by a user defined Global Setting
        DisabledByGroupPolicy, // Toast is blocked by Group Policy
        DisabledByManifest, // Toast is blocked by a setting in the manifest. Only for packaged applications.
    };

    [experimental]
    [flags]
    // Some basic predefined Toast Payload Templates
    enum ToastTemplateType
    {
        ToastImageAndText01,
        ToastImageAndText02,
        ToastImageAndText03,
        ToastImageAndText04,
        ToastText01,
        ToastText02,
        ToastText03,
        ToastText04,
    };

    [experimental]
    [flags]
    // The Result for a Toast Progress related operation
    enum ToastProgressResult
    {
        Succeeded, // The progress operation succeeded
        Failed, // The progress operation failed
        NotificationNotFound, // The progress operation failed to find a toast to process updates
    };

    [experimental]
    [flags]
    enum ToastPriority
    {
        Default, // The notification should have default behavior in terms of delivery and display priority during connected standby mode.
        High, // The notification should be treated as high priority. For desktop PCs, this means during connected standby mode the incoming notification can turn on the screen for Surface-like devices if it doesn't have a closed lid detected.
    };

    [experimental]
    // Represent a toast Notification construct
    runtimeclass ToastNotification
    {
        // Initialize a new Toast using an XML Payload.
        ToastNotification(Windows.Data.Xml.Dom.XmlDocument payload);

        // Unique identifier used to replace a notification within a group.
        String Tag;

        // Unique identifier for a toast group in the app
        String Group;

        // A unique identifier for the Toast generated by the platform.
        UInt32 ToastIdentifier;

        // The notification Xml Payload
        Windows.Data.Xml.Dom.XmlDocument Payload{ get; };

        // Gets or sets additional information about the toast progress.
        ToastProgressData Data;

        // Gets or sets the time after which a toast notification should not be displayed.
        Windows.Foundation.DateTime ExpirationTime;

        // Indicates whether the toast will remain in the Action Center after a reboot.
        Boolean ExpiresOnReboot;

        // Gets or sets the priority for a Toast.
        // Hints on how and at what urgency level a notification should be presented to the user (whether to wake up the screen, etc).
        ToastPriority Priority;

        // Gets or sets whether a toast's pop-up UI is displayed on the user's screen.
        Boolean SuppressPopup;
    };

    [experimental]
    // Supports Toast related operations for all prior displayed Toasts in Action Centre
    runtimeclass ToastNotificationHistory
    {
        // Removes a specific toast with a specific toastIdentifier from Action Centre
        Windows.Foundation.IAsyncAction RemoveWithIdentiferAsync(UInt32 toastIdentifier);

        // Removes a toast having a specific tag
        Windows.Foundation.IAsyncAction RemoveWithTagAsync(String tag);

        // Removes a toast having a specific tag and group
        Windows.Foundation.IAsyncAction RemoveWithTagGroupAsync(String tag, String group);

        // Remove all toasts for a specific group
        Windows.Foundation.IAsyncAction RemoveGroupAllAsync(String group);

        // Removes all the toasts for the App from Action Centre
        Windows.Foundation.IAsyncAction RemoveAllAsync();

        // Gets all the toasts for the App from Action Centre
        Windows.Foundation.IAsyncOperation<Windows.Foundation.Collections.IVectorView<ToastNotification> > GetAllAsync();
    };

    [experimental]
    // The manager class which encompasses all Toast API Functionality
    static runtimeclass ToastNotificationManager
    {
        // Register an activator using an ActivationInfo context and caches the token for unregister
        static void RegisterActivator(ToastActivationInfo details);

        // Unregisters the activator and removes the cached Registration token.
        static void UnregisterActivator();

        // Event handler for Toast Activations
        static event Windows.Foundation.EventHandler<ToastActivatedEventArgs> ToastActivated;

        // Displays the Toast in Action Centre
        static void ShowToast(ToastNotification toast);

        // Updates the Toast for a Progress related operation using Tag and Group
        static Windows.Foundation.IAsyncOperation<ToastProgressResult> UpdateToastProgressDataAsync(ToastProgressData data, String tag, String group);

        // Updates the Toast for a Progress related operation using Tag
        static Windows.Foundation.IAsyncOperation<ToastProgressResult> UpdateToastProgressDataAsync(ToastProgressData data, String tag);

        // Get the Toast Setting status for the app
        static Windows.Foundation.IAsyncOperation<ToastNotificationSetting> Setting{ get; };

        // Gets an instance of ToastHistory
        static ToastNotificationHistory History{ get; };

        // Gets an Xml Payload based ona predefined Toast Template
        static Windows.Data.Xml.Dom.XmlDocument GetXmlTemplateContent(ToastTemplateType type);
    };
}

```

# Appendix

-   To support cloud toasts, the developer will need to Register the Toast Activator APIs. The Windows SDK will inturn figure out the complexity of mapping cloud based toasts with a specific Push Identifier to it's corresponding Toast Identifier.
-   Since building Toast XML payloads during runtime is non-trivial, we encourage developers to utilize the windows developer toolkit, more specifically the ToastContentBuilder APIs to construct the xml payload.
