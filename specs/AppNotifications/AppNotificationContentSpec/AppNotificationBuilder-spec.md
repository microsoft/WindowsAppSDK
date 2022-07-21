# App Notification Content Builder

# Background

App Notifications are UI popups that contain rich text, controls and images to display a message to
the user. With the Windows App SDK, developers can define an XML payload and display an
AppNotification using the AppNotificationManager::Show API, but defining these XML payloads can be
tedious when written by hand.

To generate an AppNotification like this one:

![App Notification With Avatar Image](AppNotificationWithAvatarImage.png)

Developers have to write something like this:

```c++
int sequenceId {1234};
std::wstring pathToImage {LR"(path\to\my\image.png)"};

winrt::hstring xmlPayload{
    L"<toast launch = \"action=AppNotificationClick;sequence=" + to_wstring(sequenceId) + L"\">\
        <visual>\
            <binding template = \"ToastGeneric\">\
                <image placement = \"appLogoOverride\" hint-crop=\"circle\" src = \"" + pathToImage + L"\"/>\
                <text>App Notification with Avatar Image</text>\
                <text>This is an example message using XML</text>\
            </binding>\
        </visual>\
        <actions>\
            <action\
                content = \"Open App\"\
                arguments = \"action=OpenApp&amp;sequence=" + to_wstring(sequenceId) + L"\"/>\
        </actions>\
    </toast>" };

auto appNotification{ winrt::AppNotification(xmlPayload) };
winrt::AppNotificationManager::Default().Show(appNotification);
```

# Description

To improve the AppNotification construction experience, the Windows App SDK is introducing
AppNotificationContent, a builder that constructs simple or rich App Notifications for the
developer.

```c++
AppNotificationContent()
    .AddArgument(L"AppNotificationClick")
    .AddArgument(L"sequence", 1234)
    .SetAppLogoOverride(winrt::Windows::Foundation::Uri(L"http://www.contoso.com"), ImageCrop::Circle)
    .AddText(L"App Notification with Avatar Image")
    .AddText(L"This is an example message")
    .AddButton(AppNotificationButton(L"Open App")
        .AddArgument(L"action", "OpenAppButton")
        .AddArgument(L"sequence", sequenceId));
```

# API Components

# AppNotificationContent

The AppNotificationContent component sets up the xml for a `<toast>`. This is the wrapper content
that will include any component adding to the AppNotification UI.

### WinAppSDK 1.2 `<toast>` Schema

```xml
<toast
    launch? = string
    duration? = "long" | "short"
    displayTimeStamp? = string
    scenario? = "reminder" | "alarm" | "incomingCall" | "urgent"
    useButtonStyle? = boolean>
      <!-- Child elements -->
    visual, audio?, actions?
</toast>
```

These attributes are abstracted away through the AppNotificationContent component APIs:

-   AppNotificationContent();
-   AddArgument(String key, String value)
-   SetTimeStamp(Windows.Foundation.DateTime dateTime)
-   SetScenario(AppNotificationScenario Scenario)
    -   AppNotificationScenario::Reminder
    -   AppNotificationScenario::Alarm
    -   AppNotificationScenario::IncomingCall
    -   AppNotificationScenario::Urgent

useButtonStyle will only be set if Button::SetButtonColor is used.

You can append UI components through the AppNotificationContent component APIs:

-   AddText
-   AddButton
-   SetInlineImage
-   SetAppLogoOverrideImage
-   SetHeroImage
-   SetAudio
-   AddTextBox
-   AddComboBox

The main advantage as an API is to provide validation, type safety, and foremost intellisense.

Below is an example usage:

![AppNotification Example](AppNotificationExample.png)

AppNotificationContent code:

```cpp
AppNotificationContent()
    .AddArgument(L"action", L"openThread")
    .AddArgument(L"threadId", 92187)
    .SetTimeStamp(DateTime.now())
    .AddText(L"Jill Bender", AppNotificationTextProperties().SetMaxLines(1))
    .AddText(L"Checkout where we camped last weekend")
    .SetAppLogoOverride(winrt::Windows::Foundation::Uri(LR"(https://unsplash.it/64?image=1027)"), ImageCrop::Circle)
    .SetHeroImage(winrt::Windows::Foundation::Uri(LR"(https://unsplash.it/360/180?image=1043)"))
    .AddTextBox(L"textBox", L"reply")
    .AddButton(AppNotificationButton()
        .AddArgument(L"action", L"reply")
        .AddArgument(L"threadId", 92187)
        .SetIcon(winrt::Windows::Foundation::Uri(LR"(Assets/Icons/send.png)"))
        .SetInputId(L"textBox"))
    .GetXml();
```

Result from GetXml():

```xml
<toast launch="action=openThread&amp;threadId=92187" displayTimestamp="2022-06-19T08:30:00Z">
    <visual>
        <binding template="ToastGeneric">
            <text hint-maxLines="1">Jill Bender</text>
            <text>Check out where we camped last weekend! It was incredible, wish you could have come on the backpacking trip!</text>
            <image placement="appLogoOverride" hint-crop="circle" src="https://unsplash.it/64?image=1027"/>
            <image placement="hero" src="https://unsplash.it/360/180?image=1043"/>
        </binding>
    </visual>
    <actions>
        <input id="textBox" type="text" placeHolderContent="reply"/>
        <action
          content="Send"
          imageUri="Assets/Icons/send.png"
          hint-inputId="textBox"
          arguments="action=reply&amp;threadId=92187"/>
    </actions>
</toast>
```

## Limitations

-   AppNotificationScenario::Urgent is only supported for to builds 19041 (20H1) and above. Using
    this attribute on lower builds will not prevent the AppNotification from being constructed, but
    developers will receive a debug warning that the attribute is not supported.

# Text

The Text component sets up the xml for a `<text>` element. Developers can define the content,
language, and placement of the text on the AppNotification.

**WinAppSDK 1.2 \<text\> Schema**:

```xml
<text lang? = string
      placement? = "attribution"
      hint-callScenarioCenterAlign? =
      hint-maxLines? = integer />
```

These attributes are abstracted with the AppNotificationTextProperties component APIs:

-   SetLanguage(String language)
-   SetHintMaxLines(Int32)
-   UseIncomingCallAlignment()

Below are some example usages:

![Text Example](TextExample.png)

AppNotificationContent Code:

```cpp
AppNotificationContent()
    .AddText(L"Content")
    .SetAttributionText(L"Attribution Text")
    .GetXml();
```

XML output:

```xml
<toast>
  <visual>
    <binding template="ToastGeneric">
      <text>Content</text>
      <text placement="attribution">Attribution Text</text>
    </binding>
  </visual>
</toast>
```

Developers can use UseIncomingCallAlignment() to center the text like an incoming call. This feature
will be ignored unless the AppNotification scenario is set to IncomingCall using
AppNotificationContent::SetScenario(enum AppNotificationScenario).

![IncomingCall Simple Example](IncomingCallSimpleExample.png)

AppNotificationContent code:

```cpp
AppNotificationContent()
    .SetScenario(AppNotificationScenario::IncomingCall)
    .AddText(L"Incoming Call", AppNotificationTextProperties()
        .UseIncomingCallAlignment())
    .AddText(L"Andrew Barnes", AppNotificationTextProperties()
        .UseIncomingCallAlignment())
    .AddInlineImage(winrt::Windows::Foundation::Uri(L"https://unsplash.it/100?image=883"), ImageCrop::Circle)
    .AddButton(AppNotificationButton()
        .SetIcon(winrt::Windows::Foundation::Uri(L"https://www.shareicon.net/data/256x256/2015/10/17/657571_video_512x512.png"))
        .SetButtonColor(ButtonColor::Green)
        .SetToolTip(L"Answer video call"))
    .GetXml();
```

XML output:

```xml
<toast scenario="incomingCall" useButtonStyle="true">
    <visual>
        <binding template="ToastGeneric">
            <text hint-callScenarioCenterAlign = "true">Incoming Call</text>
            <text hint-callScenarioCenterAlign = "true">Andrew Barnes</text>
            <image hint-crop="circle"  src="https://unsplash.it/100?image=883"/>
        </binding>
    </visual>

    <actions>
        <action
              arguments="videoCallId"
              content=""
              imageUri="https://www.shareicon.net/data/256x256/2015/10/17/657571_video_512x512.png"
              hint-buttonStyle = "Success"
              hint-toolTip = "Answer video call"/>
</toast>
```

Notice that the text is inserted into the xml the order that it was provided in the builder.

# AppNotificationButton

The AppNotificationButton component API sets up the xml for the `<action>` element.
AppNotificationButtons are user-clickable components meant to start an action from the app.

**WinAppSDK 1.2 \<action\> Schema**:

```xml
<action content = string
        arguments = string
        placement? = "contextMenu"
        imageUri? = string
        hint-inputid? = string
        hint-buttonStyle? = "success" | "critical"
        hint-toolTip? = string />
```

These attributes are abstracted with the AppNotificationButton component APIs:

-   AppNotificationButton()
-   AppNotificationButton(String content)
-   SetIcon(Windows.Foundation.Uri iconUri)
-   SetToolTip(String toolTip)
-   UseContextMenuPlacement()
-   SetInputId(String inputId)

Below are some example usages:

![Button Example](ButtonExample.png)

AppNotificationContent code:

```cpp
AppNotificationContent()
    .AddText(L"Content")
    .AddTextBox(L"textBox", L"Reply")
    .AddButton(AppNotificationButton(L"Send")
        .AddArgument(L"action", L"textReply")
        .SetIcon(winrt::Windows::Foundation::Uri(LR"(Assets/Icons/send.png)"))
        .SetInputId(L"textBox"))
    .GetXml();
```

XML output:

```xml
<toast>
  <visual>
    <binding template="ToastGeneric">
      <text>Content</text>
    </binding>
  </visual>

    <actions>
        <input id="textBox" type="text" placeHolderContent="Reply"/>
        <action
          content="Send"
          imageUri="Assets/Icons/send.png"
          hint-inputId="textBox"
          arguments="action=textReply"/>
    </actions>
</toast>
```

Developers can change the color of the button using SetButtonColor(ButtonColor). The two button
styles are ButtonColor::Green and ButtonColor::Red.

![Button Style Example](IncomingCallExample.png)

AppNotificationContent code:

```cpp
AppNotificationContent()
    .SetScenario(AppNotificationScenario::IncomingCall)
    .AddText(L"Incoming Call", AppNotificationTextProperties()
        .UseIncomingCallAlignment())
    .AddText(L"Andrew Barnes", AppNotificationTextProperties()
        .UseIncomingCallAlignment())
    .AddInlineImage(winrt::Windows::Foundation::Uri(L"https://unsplash.it/100?image=883"), ImageCrop::Circle)
    .AddButton(AppNotificationButton()
        .AddArgument(L"videoCall", L"938465")
        .SetIcon(winrt::Windows::Foundation::Uri(L"https://www.shareicon.net/data/256x256/2015/10/17/657571_video_512x512.png"))
        .SetButtonColor(ButtonColor::Green)
        .SetToolTip(L"Answer video call"))
    .AddButton(AppNotificationButton()
        .AddArgument(L"voiceCall", L"938465")
        .SetIcon(winrt::Windows::Foundation::Uri(L"https://www.nicepng.com/png/full/379-3794777_white-phone-icon-white-phone-call-icon.png"))
        .SetButtonColor(ButtonColor::Green)
        .SetToolTip(L"Answer voice call"))
    .AddButton(AppNotificationButton()
        .AddArgument(L"declineCall", L"938465")
        .SetIcon(winrt::Windows::Foundation::Uri(L"https://static.thenounproject.com/png/5012-200.png"))
        .SetButtonColor(ButtonColor::Red)
        .SetToolTip(L"Decline all"))
    .GetXml();
```

Xml result:

```xml
<toast scenario="incomingCall" useButtonStyle="true">
    <visual>
        <binding template="ToastGeneric">
            <text hint-callScenarioCenterAlign = "true">Incoming Call</text>
            <text hint-callScenarioCenterAlign = "true">Andrew Barnes</text>
            <image hint-crop="circle"  src="https://unsplash.it/100?image=883"/>
        </binding>
    </visual>

    <actions>
        <action
              arguments="videoCall=938465;action=accept"
              content=""
              imageUri="https://www.shareicon.net/data/256x256/2015/10/17/657571_video_512x512.png"
              hint-buttonStyle = "Success"
              hint-toolTip = "Answer video call"/>
        <action
              arguments="voiceCall=938465"
              content=""
              imageUri="https://www.nicepng.com/png/full/379-3794777_white-phone-icon-white-phone-call-icon.png"
              hint-buttonStyle = "Success"
              hint-toolTip = "Answer voice call"/>
        <action
              arguments="declineCall=938465"
              content=""
              imageUri="https://static.thenounproject.com/png/5012-200.png"
              hint-buttonStyle = "Critical"
              hint-toolTip = "Decline all"/>
      </actions>
</toast>
```

Notice that the AppNotificationButtons are inserted into the xml the order that it was provided in
the builder.

The ToolTip is useful for buttons with icons and no content. Users can hover over the button with
the cursor and a text will display describing what the button does.

![Button ToolTip Example](ButtonToolTipExample.png)

AppNotificationContent code:

```cpp
AppNotificationContent()
    .AddText(L"Content")
    .AddTextBox(L"textBox", L"Reply")
    .AddButton(AppNotificationButton()
        .AddArgument(L"action", L"textReply")
        .SetInputId(L"textBox")
        .SetToolTip(L"Send")
        .SetIcon(winrt::Windows::Foundation::Uri(LR"(Assets/Icons/message.png)")))
    .GetXml();
```

XML output:

```xml
<toast>
  <visual>
    <binding template="ToastGeneric">
      <text>Content</text>
    </binding>
  </visual>

    <actions>
            <input id="textBox" type="text" placeHolderContent="Reply"/>
            <action
            content=""
            imageUri="Assets/Icons/message.png"
            hint-inputId="textBox"
            hint-toolTip="Send"
            arguments="action=textReply"/>
    </actions>
</toast>
```

The placement attribute defines action for a user to interact with when the AppNotification is
right-clicked. This would typically be used by developers to ask the user for setting changes.

![Button ContextMenu Example](ButtonContextMenuExample.png)

AppNotificationContent code:

```cpp
AppNotificationContent()
    .AddText(L"Content")
    .AddTextBox(L"textBox", L"Reply")
    .AddButton(AppNotificationButton(L"Modify app settings")
        .AddArgument(L"action", L"textReply")
        .UseContextMenuPlacement())
    .GetXml();
```

XML output:

```xml
<toast>
  <visual>
    <binding template="ToastGeneric">
      <text>Content</text>
    </binding>
  </visual>

    <actions>
            <input id="textBox" type="text" placeHolderContent="Reply"/>
            <action
            placement="contextMenu"
            content="Modify app settings"
            imageUri="Assets/Icons/message.png"
            arguments="action=textReply"/>
    </actions>
</toast>
```

## Limitations

-   hint-toolTip and hint-buttonStyle are only supported for builds 19041 (20H1) and above. Using
    these attributes on lower builds will not prevent the AppNotification from being constructed,
    but developers will receive a debug warning that the attributes are not supported.

# Image

The Image component API sets up the xml for the `<image>` element. Images are visual elements that
are used to enhance an AppNotification.

The image source can be pulled using one of these protocol handlers:

-   http:// or https:// (A web-based image) (unavailable for unpackaged application on build 22000)
-   ms-appx:/// (An image included in the app package) (only for packaged applications)
-   ms-appdata:///local/ (An image saved to local storage) (only for packaged applications)
-   file:/// (A local image) (only for unpackaged)

**WinAppSDK 1.2 \<image\> Schema**:

```xml
<image src = string
       alt? = string
       placement? = "appLogoOverride" | "hero"
       hint-crop? = "circle" />
```

Images can be displayed in three different ways:

## Inline

A full-width inline-image that appears when you expand the AppNotification.

![Inline Image Example](InlineImageExample.png)

AppNotificationContent code:

```cpp
AppNotificationContent()
    .AddText(L"Below is an inline image")
    .SetInlineImage(winrt::Windows::Foundation::Uri(LR"(https://unsplash.it/360/202?image=883)"))
    .GetXml();
```

XML output:

```xml
<toast>
  <visual>
    <binding template="ToastGeneric">
      <text>Below is an inline image</text>
      <image src="https://unsplash.it/360/202?image=883">
    </binding>
  </visual>
</toast>
```

## AppLogoOverride

An image that is left-aligned with notification text.

![AppLogoOverride Image Example](AppLogoOverrideImageExample.png)

AppNotificationContent code:

```cpp
AppNotificationContent()
    .AddText(L"To the left is an AppLogoOverride")
    .SetAppLogoOverride(winrt::Windows::Foundation::Uri(LR"(https://unsplash.it/64?image=669)"))
    .GetXml();
```

XML output:

```xml
<toast>
  <visual>
    <binding template="ToastGeneric">
      <text>To the left is an AppLogoOverride</text>
      <image src="https://unsplash.it/64?image=669"
                placement="appLogoOverride" />
    </binding>
  </visual>
</toast>
```

## Hero

Prominently displays image within the AppNotification banner and while inside Notification Center.

![Hero Image Example](HeroImageExample.png)

AppNotificationContent code:

```cpp
AppNotificationContent()
    .AddText(Text(L"Above is a Hero image"))
    .SetHeroImage(winrt::Windows::Foundation::Uri(LR"(https://unsplash.it/360/180?image=1043)"))
    .GetXml();
```

XML output:

```xml
<toast>
  <visual>
    <binding template="ToastGeneric">
      <text>Above is a Hero image</text>
      <image src="https://unsplash.it/360/180?image=1043"
                placement="hero" />
    </binding>
  </visual>
</toast>
```

## Cropped AppLogoOverride

For both Inline and AppLogoOverride, developers can set how the image will be cropped.

![Cropped AppLogoOverride Image Example](CroppedAppLogoOverrideExample.png)

AppNotificationContent code:

```cpp
AppNotificationContent()
    .AddText(L"To the left is a cropped AppLogoOverride")
    .SetAppLogoOverride(winrt::Windows::Foundation::Uri(LR"(https://unsplash.it/64?image=669)"), ImageCrop::Circle);
```

XML output:

```xml
<toast>
  <visual>
    <binding template="ToastGeneric">
      <text>To the left is a cropped AppLogoOverride</text>
      <image src="https://unsplash.it/64?image=669"
                hint-crop="circle"
                placement="appLogoOverride" />
    </binding>
  </visual>
</toast>
```

# Audio

The Audio component allows the developer to define a custom audio to play when an AppNotification is
displayed. The audio file can be defined by string value pointing to an app asset or one of the
[ms-winsoundevents](https://docs.microsoft.com/uwp/schemas/tiles/toastschema/element-audio).

**WinAppSDK 1.2 `<audio>` Schema**:

```xml
<audio src? = string
       loop? = boolean
       silent? = boolean />
```

These attributes are abstracted with the Audio component APIs:

-   SetAudio(Windows.Foundation.Uri audioUri)
-   SetAudio(AppNotficiationSoundEvent appNotficiationSoundEvent)
-   SetAudio(Windows.Foundation.Uri audioUri, AppNotificationDuration duration)
-   SetAudio(AppNotficiationSoundEvent appNotficiationSoundEvent, AppNotificationDuration duration)
-   MuteAudio()

Below are some example usages:

```cpp
AppNotificationContent()
    .SetAudio(AppNotficiationSoundEvent::Reminder)
    GetXml();
```

XML output:

```xml
<toast>
  <visual>
    <binding template="ToastGeneric">
    </binding>
  </visual>
  <audio src="ms-winsoundevent:Notification.Reminder" />
</toast>
```

Developers can define if the audio should be looped using SetAudio(Uri, AppNotificationDuration),
which can be short or long.

```cpp
AppNotificationContent()
    .AddText(L"Content")
    .SetAudio(AppNotficiationSoundEvent::Alarm, AppNotificationDuration::Long)
    .GetXml();
```

XML output:

```xml
<toast duration="long">
  <visual>
    <binding template="ToastGeneric">
        <text>Above is a Hero image</text>
    </binding>
  </visual>
  <audio src="ms-winsoundevent:Notification.Looping.Alarm" loop="true" />
</toast>
```

An AppNotification that does not want to play any audio including the default, can use MuteAudio to
mute the audio.

```cpp
AppNotificationContent()
    .AddText(L"Content")
    .MuteAudio()
    .GetXml();
```

XML output:

```xml
<toast duration="long">
  <visual>
    <binding template="ToastGeneric">
        <text>Content</text>
    </binding>
  </visual>
  <audio silent="true" />
</toast>
```

# TextBox

TextBox is an `<input>` component that allows users to type custom responses on an AppNotification.

**WinAppSDK 1.2 TextBox Schema**:

```xml
<input id = string
        type="text"
        placeHolderContent? = string>
</input>
```

These attributes are abstracted with the TextBox component APIs:

-   TextBox(String id)
-   TextBox(String id, String placeHolderContent)

Below is an example use:

![TextBox Example](TextBoxExample.png)

AppNotificationContent code:

```cpp
AppNotificationContent()
    .AddTextBox(L"textBox", L"reply")
    .AddButton(AppNotificationButton(L"Send")
        .AddArguments(L"action", L"Send")
        .SetInputId(L"textBox"))
    .GetXml();
```

XML output:

```xml
<toast>
  <visual>
    <binding template="ToastGeneric">
    </binding>
  </visual>

  <actions>
    <input id="textBox" type="text" />
    <action
      arguments="action=Send"
      content="Send"
      hint-inputId="textBox" />
  </actions>
</toast>
```

You can have up to 5 input components (TextBox/AppNotificationComboBox) total in the builder. The
order in the result xml will be the order it was added to the builder.

# AppNotificationComboBox

AppNotificationComboBox is an `<input>` component that allows users to pick from a dropdown menu of
values on an AppNotification.

**WinAppSDK 1.2 AppNotificationComboBox Schema**:

```xml
<input id = string
        type="selection"
        defaultInput? = string>
    <!-- Child elements -->
    selection{0,5}
</input>
```

These attributes are abstracted with the AppNotificationComboBox component APIs:

-   AppNotificationComboBox(String id)
-   SetDefaultSelection(String id)
-   AddSelection(String id, String content)

Below is an example use:

![ComboBox Example](ComboBoxExample.png)

```cpp
AppNotificationContent()
    .AddComboBox(AppNotificationComboBox(L"ComboBox")
        .SetDefaultSelection(L"yes")
        .AddSelection(L"yes", L"Going")
        .AddSelection(L"maybe", L"Maybe")
        .AddSelection(L"no", L"Decline"))
    .AddButton(AppNotificationButton(L"Send")
        .AddArgument(L"action", L"Send"))
        .SetInputId(L"ComboBox")
    .GetXml();
```

XML output:

```xml
<toast>
  <visual>
    <binding template="ToastGeneric">
    </binding>
  </visual>

  <actions>
    <input id="ComboBox" type="selection" defaultInput="yes">
      <selection id="yes" content="Going" />
      <selection id="maybe" content="Maybe" />
      <selection id="no" content="Decline" />
    </input>
    <action
      arguments="action=Send"
      hint-inputId="ComboBox"
      content="Send"/>

  </actions>
</toast>
```

# AppNotificationProgressBar

AppNotificationProgressBar is a component that builds the `<progress>` xml.
AppNotificationProgressBar is used to update an AppNotification that is currently displayed. This
allows developers to inform users about the status of certain operations such as download or
install.

**WinAppSDK 1.2 `<progress>` Schema**:

```xml
<progress title? = string
    status = string
    value = string
    valueStringOverride? = string
/>
```

AppNotificationProgressBar uses data binding to update the active UI. In the WindowsAppSDK, this is
done by using AppNotificationProgressData. Click
[Here](https://github.com/microsoft/WindowsAppSDK/blob/main/specs/AppNotifications/AppNotifications-spec.md#notification-progress-updates)
for an example.

All the attributes have static data binding constants:

-   Status = "{progressStatus}"
-   Value = "{progressValue}"
-   Title = "{progressTitle}"
-   ValueStringOverride = "{progressValueString}

Every AppNotificationProgressBar component will have the bound status and value. Title and
ValueStringOverride are not required so those constants will not be added unless you call
the AppNotificationProgressBar component APIs

-   UseTitleForLabel(String title)
-   BindTitleForLabel()
-   BindValueStringOverride()

Below is an example use:

```cpp
// Using AppNotificationContent, build the Xml payload with AppNotificationProgressBar.
winrt::hstring xmlPayload { AppNotificationContent()
    .AddText(L"Downloading this week's new music...")
    .AddProgressBar(AppNotificationProgressBar()
        .BindTitleForLabel()
        .BindValueStringOverride())
    .GetXml() };
```

Xml result:

```xml
<toast>
  <visual>
    <binding template="ToastGeneric">
      <text>Downloading this week's new music...</text>
      <progress
        title="{progressTitle}"
        value="{progressValue}"
        valueStringOverride="{progressValueString}"
        status="{progressStatus}"/>
    </binding>
  </visual>
</toast>
```

Construct an AppNotification with the string xml payload from AppNotificationContent

```cpp
winrt::Microsoft::Windows::AppNotifications::AppNotification notification(xmlPayload);
notification.Tag(L"Tag");
notification.Group(L"Group");
```

Assign initial values for first notification progress UI:

```cpp
winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData data(1 /* Sequence number */);
data.Title(L"Katy Perry"); // Binds to {progressTitle} in xml payload
data.Value(0.5); // Binds to {progressValue} in xml payload
data.ValueStringOverride(L"1/2 songs"); // Binds to {progressValueString} in xml payload
data.Status(L"Downloading..."); // Binds to {progressStatus} in xml payload

notification.Progress(data); // Updates the AppNotification values
winrt::AppNotificationManager::Default().Show(notification);
```

![Progress Bar Example 1](ProgressBarExample1.png)

Then update the AppNotificationProgressBar using AppNotificationProgressData:

```cpp
data.SequenceNumber(2);
data.Title(L"Katy Perry"); // Binds to {progressTitle} in xml payload
data.Value(1.0); // Binds to {progressValue} in xml payload
data.ValueStringOverride(L"2/2 songs"); // Binds to {progressValueString} in xml payload
data.Status(L"Downloaded!"); // Binds to {progressStatus} in xml payload

auto result = co_await winrt::Microsoft::Windows::AppNotifications::AppNotificationManager::Default().UpdateAsync(data, L"Tag", L"Group");
```

![Progress Bar Example 2](ProgressBarExample2.png)

# Retrieving Arguments

AppNotificationContent and Button return arguments to the activated application when the user clicks
on the component. Developers can add multiple key/value pairs and Windows App SDK will serialize
them into a string.

Below is an example with AppNotificationContent and Button:

```cpp
AppNotificationContent()
    .AddArgument(L"action", L"appNotificationBodyTouch")
    .AddArgument(L"user", 938163)
    .AddButton(AppNotificationButton(L"Send")
        .AddArgument(L"action", L"buttonTouch")
        .AddArgument(L"user", 938163));
```

When the user clicks on the AppNotification body, the resulting argument string is:

-   "action=appNotificationBodyTouch;user=938163"

When the user clicks on the Button, the result argument string is:

-   "action=buttonTouch;callId=938163"

Notice that ';' is used as the delimiter between each argument.

To retrieve the arguments from the serialized string, developers will use
AppNotificationReceivedEventArgs::Arguments to get the values from the argument string as a map.

Below is an example usage:

```cpp
using namespace winrt::Microsoft::Windows::AppLifecycle;
using namespace winrt::Microsoft::Windows::AppNotifications;

// Retrieve the activation args using Windows App SDK AppLifecycle functions
AppActivationArguments args { AppLifecycle::AppInstance::GetCurrent().GetActivatedEventArgs() };
ExtendedActivationKind kind { args.Kind() };

// Check the activation kind
if (kind == ExtendedActivationKind::AppNotification)
{
    AppNotificationActivatedEventArgs appActivatedArgs { args.Data().as<AppNotificationActivatedEventArgs>() };

    // Retrieve the serialized arguments from AppNotificationActivatedEventArgs
    winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> argumentMap { appActivatedArgs.Argument() };
}
```

# Full API Details

```cpp
namespace Microsoft.Windows.AppNotifications.Builder
{
    runtimeclass AppNotificationTextProperties
    {
        // Contains the set of <text> attributes
        AppNotificationTextProperties();

        AppNotificationTextProperties SetLanguage(String value);
        AppNotificationTextProperties UseIncomingCallAlignment();
        AppNotificationTextProperties SetMaxLines(Int32 value);

        String GetXml();
    }

    enum ButtonColor
    {
        Red, // The button will be green
        Green, // The button will be red
    };

    runtimeclass AppNotificationButton
    {
        // Button can use ToolTip instead of content which requires empty content.
        // Argument attribute is required and uses the ArgumentSerializer construct
        // to add arguments to the button.
        AppNotificationButton();
        AppNotificationButton(String buttonText);

        AppNotificationButton AddArgument(String key, String value);

        // Sets the IconUri for the button.
        AppNotificationButton SetIcon(Windows.Foundation.Uri value);

        // The tooltip for a button, if the button has an empty content string.
        AppNotificationButton SetToolTip(String value);

        // Sets the Button as context menu action.
        AppNotificationButton UseContextMenuPlacement();

        // Sets the ButtonColor to Green or Red
        AppNotificationButton SetButtonColor(ButtonColor value);

        // Sets the ID of an existing TextBox in order to have this button display to the right of the input.
        AppNotificationButton SetInputId(String value);

        // Launches the URI passed into the button when activated.
        AppNotificationButton SetInvokeUri(Windows.Foundation.Uri protocolUri);
        AppNotificationButton SetInvokeUri(Windows.Foundation.Uri protocolUri, String targetAppId);

        // Retrieves the XML content of the button.
        String GetXml();
    };

    runtimeclass AppNotificationComboBox
    {
        AppNotificationComboBox(String id);

        // Add a selection item to the AppNotificationComboBox if InputType is AppNotificationComboBox. The id parameter is used to retrieve the user input when the app is activated
        // and content is the displayed text for the item.
        AppNotificationComboBox AddItem(String id, String content);

        // Adds a title to display on top
        AppNotificationComboBox SetTitle(String value);

        // Sets the default selection to be displayed by the AppNotificationComboBox
        AppNotificationComboBox SetSelectedItem(String id);

        // Retrieves the XML content of the input.
        String GetXml();
    };

    runtimeclass AppNotificationProgressBar
    {
        // AppNotificationProgressBar binds to AppNotificationProgressData so the AppNotification will
        // receive every update to the status and value. In the WinAppSDK, these binding
        // values are static, so developers won't need to define these binding values
        // themselves.
        AppNotificationProgressBar();

        // Adds a static title to the progress bar
        AppNotificationProgressBar UseTitleForLabel(String value);

        // Adds the title binding value to be used with AppNotificationProgressData
        AppNotificationProgressBar BindTitleForLabel();

        // Adds the valueStringOverride value.
        AppNotificationProgressBar BindValueStringOverride();

        // Retrieves the XML content of the AppNotificationProgressBar
        String GetXml();
    };

    enum
    {
        Default,
        IM,
        Mail,
        Reminder,
        SMS,
        Alarm,
        Alarm2,
        Alarm3,
        Alarm4,
        Alarm5,
        Alarm6,
        Alarm7,
        Alarm8,
        Alarm9,
        Alarm10,
        Call,
        Call2,
        Call3,
        Call4,
        Call5,
        Call6,
        Call7,
        Call8,
        Call9,
        Call10,
    };

    enum AppNotificationScenario
    {
        Default, // The normal AppNotification behavior. The AppNotification appears for a short duration, and then automatically dismisses into Notification Center.
        Reminder, // The notification will stay on screen until the user dismisses it or takes action.
        Alarm,    // Alarms behave like Reminder, but alarms will additionally loop audio with a default alarm sound.
        IncomingCall, // Incoming call notifications are displayed pre-expanded in a special call format and stay on the user's screen till dismissed.
        Urgent, // Important notifications allow users to have more control over what 1st party and 3rd party apps can send them high-priority AppNotifications (urgent/important) that can break through Focus Assist.
    };

    enum AppNotificationDuration
    {
        Short, // Default value. AppNotification appears for a short while and then goes into Notification Center.
        Long, // AppNotification stays on-screen for longer, and then goes into Notification Center.
    };

    enum ImageCrop
    {
        Default, // Uses the default renderer to display the image
        Circle, // Crops the image as a circle.
    }

    runtimeclass AppNotificationContent
    {
        AppNotificationContent();

        // Adds arguments to the launch attribute to return when AppNotification is clicked.
        AppNotificationContent AddArgument(String key, String value);

        // Sets the timeStamp of the AppNotification to when it was constructed instead of when it was sent.
        AppNotificationContent SetTimeStamp(Windows.Foundation.DateTime value);

        // Sets the scenario of the AppNotification.
        AppNotificationContent SetScenario(AppNotificationScenario value);

        // Adds text to the AppNotification.
        AppNotificationContent AddText(String text);
        AppNotificationContent AddText(String text, AppNotificationTextProperties properties);

        AppNotificationContent SetAttributionText(String text);
        AppNotificationContent SetAttributionText(String text, String language);

        // Sets the full-width inline-image that appears when you expand the AppNotification
        AppNotificationContent SetInlineImage(Windows.Foundation.Uri imageUri);
        [default_overload]
        AppNotificationContent SetInlineImage(Windows.Foundation.Uri imageUri, ImageCrop imageCrop);
        AppNotificationContent SetInlineImage(Windows.Foundation.Uri imageUri, String alternateText);
        AppNotificationContent SetInlineImage(Windows.Foundation.Uri imageUri, String alternateText, ImageCrop imagecrop);

        // Sets the image that is left-aligned with notification text
        AppNotificationContent SetAppLogoOverride(Windows.Foundation.Uri imageUri);
        AppNotificationContent SetAppLogoOverride(Windows.Foundation.Uri imageUri, String alternateText);
        AppNotificationContent SetAppLogoOverride(Windows.Foundation.Uri imageUri, ImageCrop imageCrop);
        AppNotificationContent SetAppLogoOverride(Windows.Foundation.Uri imageUri, String alternateText, ImageCrop imageCrop);

        // Sets the image that displays within the banner of the AppNotification.
        AppNotificationContent SetHeroImage(Windows.Foundation.Uri imageUri);
        AppNotificationContent SetHeroImage(Windows.Foundation.Uri imageUri, String alternateText);

        // SetAudio
        [default_overload]
        AppNotificationContent SetAudio(Windows.Foundation.Uri audioUri);
        AppNotificationContent SetAudio(AppNotficiationSoundEvent appNotficiationSoundEvent);

        [default_overload]
        AppNotificationContent SetAudio(Windows.Foundation.Uri audioUri, AppNotificationDuration duration);
        AppNotificationContent SetAudio(AppNotficiationSoundEvent appNotficiationSoundEvent, AppNotificationDuration duration);

        AppNotificationContent MuteAudio();

        // Add an input textbox to retrieve user input.
        AppNotificationContent AddTextBox(String id);
        AppNotificationContent AddTextBox(String id, String placeHolderText, String title);

        // Adds a button to the AppNotificationContent
        AppNotificationContent AddButton(AppNotificationButton value);

        // Add an input ComboBox to retrieve user input.
        AppNotificationContent AddComboBox(AppNotificationComboBox value);

        AppNotificationContent AddProgressBar(AppNotificationProgressBar value);

        // Retrieves the notification XML content so that it can be used with a local
        // AppNotification constructor.
        String GetXml();
    };
}
```
