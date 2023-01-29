# Snooze and Dismiss Buttons

## Problem Definition

Developers can use the AppNoticition APIs to post notifications that use the system snooze and dismiss actions.

![AppNotification Snooze / Dismiss Example](toast-content-snooze-dismiss.png)

With the current implementation developers must use xml as the AppNotificationBuilder doesn't support snooze and dismiss button. 
Bellow is the xml required to display the above notification.

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

## Proposal

Adding support for snooze and dismiss buttons, developers will be able to create the same notifications using the AppNotificationBuilder instead of raw xml, as shown bellow.

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

Everything but the last two lines in the code snippet above already exists and is supported  in the current builder.

We propose the following:

1. Add an emuration for button type to allow the builder to distinguish between standard buttons and the likes of snooze and dismiss which are tied to system actions. 
The builder needs that information in order to crete the proper xml.

    ```idl
    enum AppNotificationButtonType
    {
        Standard,
        Snooze,
        Dismiss,
    };
    ```

2. Add two factory methods to the AppNotificationButton class. 
The snooze and dismiss buttons are simple variation on the standard buttons but would be somewhat ackward to construct using the current API. 
The two addinional factory methods make constructing the new buttons easy and since they return a AppNotificationButton, developers can use the fluent API to further configure the buttons, just like for a standard button.

    ```idl
    runtimeclass AppNotificationButton
    {
        AppNotificationButton();
        AppNotificationButton(String content);

        static AppNotificationButton MakeSnoozeButton(String inputId);
        static AppNotificationButton MakeDismissButton();

        String Content;
        AppNotificationButtonType ButtonType;
        Windows.Foundation.Collections.IMap<String, String> Arguments;
        .
        .
        .
    ```

    The code snippet above, shows the beginning of the AppNotificationButton runtimeclass declaration in AppNotificationBuilder IDL with the new AppNotificationButtonType added along with the two new factory methods for creating the snooze and dismiss buttons.

    These are the only changes to the API required to implement the feature.

# FAQ
