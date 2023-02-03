# Snooze and Dismiss Buttons

Developers can use the AppNoticition APIs to post notifications that use the system snooze and dismiss actions.

![AppNotification Snooze / Dismiss Example](toast-content-snooze-dismiss.png)

With the current implementation developers must use xml as the AppNotificationBuilder doesn't support snooze and dismiss button. 
Below is the xml required to display the above notification.

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

Everything in the xml snippet above but the last two lines is currently supported in the AppNotificationBuilder.

Support for the Snooze and Dismiss System Actions ca be achieved by adding two new factory methods to the AppNotificationButton class. 
The snooze and dismiss buttons are simple variation on the standard buttons but would be somewhat ackward to construct using the current API. 
The two additional factory methods make constructing the new buttons easy and since they return an AppNotificationButton, developers can use the fluent API to further configure the buttons, just like for a standard button.

```idl
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

Since there are now 3 type of buttons: Standard, Snooze or Dismiss, it shhould be exposed publicly simmilarly to how other such properties are exposed throuhought the AppNotificationBuilder API.
The ButtonType property from above does that, and below is the corresponding enum.

```idl
[contract(AppNotificationBuilderContract, 2)]
enum AppNotificationButtonType
{
    Standard,
    Snooze,
    Dismiss,
};
```
These are the only changes to the API required to implement the feature.

Once support for snooze and dismiss buttons is added to the AppNotificationBuilder, developers will be able to create AppNotifications, like the one shown at the beginning of this document, using the code as shown below.

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
# Additional Notes
