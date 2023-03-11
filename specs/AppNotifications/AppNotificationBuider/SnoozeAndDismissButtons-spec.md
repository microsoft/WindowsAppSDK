
App Notification Snooze and Dismiss Buttons
===

# Background

[App notifications](https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/notifications/app-notifications/app-notifications-quickstart?tabs=cs)
in the Windows App SDK are messages that your app can construct and deliver to
your user while they are not currently inside your app, for example:

![App notification example](app-notification-example.jpg)

App notifications are defined in XML, and the
[AppNotificationBuilder](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilder)
API provides a programattic way to build that XML.

The `AppNotificationBuilder` though does not support the 
[`Snooze and Dismiss`](toast-content-snooze-dismiss.png)
feature of the XML.

Snooze and Dismiss let developers post notifications that use the system snooze and dismiss actions.

With the current implementation developers must use xml as the AppNotificationBuilder doesn't support snooze and dismiss button. 

The above notification is defined by:

```xml
<toast scenario="reminder">
  <visual>
    <binding template="ToastGeneric">
      <text hint-maxLines="1">Adaptive Tiles Meeting</text>
      <text>Conf Room 2001 / Building 135</text>
      <text>10:00 AM - 10:30 AM</text>
    </binding>
  </visual>
  <actions>
    <input id="snoozeTime" type="selection" defaultInput="15">
      <selection id="1" content="1 minute"/>
      <selection id="15" content="15 minutes"/>
      <selection id="60" content="1 hour"/>
      <selection id="240" content="4 hours"/>
      <selection id="1440" content="1 day"/>
    </input>
    <action activationType="system" arguments="snooze" hint-inputId="snoozeTime" content="" />
    <action activationType="system" arguments="dismiss" content=""/>
  </actions>
</toast>
```

The new API in this spec provides a way to build this with the `AppNotificationBuilder`.

# API Pages

## AppNotificationButton class

In the following example, `AppNotificationBuilder` uses the MakeSnoozeButton and MakeDismissButton factory functions to create a Snooze and Dismiss notification [AppNotification](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/Microsoft.Windows.AppNotifications.AppNotification).

```c++
auto builder{ winrt::AppNotificationBuilder()
    .SetScenario(winrt::AppNotificationScenario::Reminder)
    .AddText(L"Adaptive Tiles Meeting", winrt::AppNotificationTextProperties()
        .SetMaxLines(1))
    .AddText(L"Conf Room 2001 / Building 135")
    .AddText(L"10:00 AM - 10:30 AM")
    .AddComboBox(winrt::AppNotificationComboBox(L"snoozeTime")
        .AddItem(L"1", L"1 minute")
        .AddItem(L"15", L"15 minutes")
        .AddItem(L"60", L"1 hour")
        .AddItem(L"240", L"4 hours")
        .AddItem(L"1440", L"1 day")
        .SetSelectedItem(L"15"))
    .AddButton(winrt::AppNotificationButton::MakeSnoozeButton(L"snoozeTime"))
    .AddButton(winrt::AppNotificationButton::MakeDismissButton())
};
```

The above usage produces the results bellow.

![AppNotification Snooze and Dismiss Example](toast-content-snooze-dismiss.png)

# API Details

```idl
[contract(AppNotificationBuilderContract, 2)]
enum AppNotificationButtonType
{
    Custom,
    Snooze,
    Dismiss,
};

runtimeclass AppNotificationButton
{
    AppNotificationButton();
    AppNotificationButton(String content);

    [contract(AppNotificationBuilderContract, 2)]
    static AppNotificationButton MakeSnoozeButton(String inputId);
    [contract(AppNotificationBuilderContract, 2)]
    static AppNotificationButton MakeDismissButton();

    String Content;
    [contract(AppNotificationBuilderContract, 2)]
    AppNotificationButtonType ButtonType;
    Windows.Foundation.Collections.IMap<String, String> Arguments;
  
    ...
};
```

# Appendix

* The snooze and dismiss buttons are simple variations on the standard buttons but would be somewhat awkward to construct using the current API.

* We have considered adding the new MakeSoozeButton and MakeDismissButton factory method directly to the AppNotificationBuilder runtime class but found that it is too limiting as it prevents any form of customization on the part of the developer.

* The two additional factory methods make constructing the new buttons easy and, since they return an AppNotificationButton, developers can use the fluent API to further configure the buttons, just like for a standard button.

* Most developers will never have to explicitely set the AppNotificationButtonType as it is implicitely set at the time a button is created. It is provided for advanced situations where a greater level of customization is required.
