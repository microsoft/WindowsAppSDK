# AppLifecycle - State Notifications

Reunion introduces a new AppLifecycle component that provides a core set of
functionality related to app activation and lifecycle. Much of this
functionality is directly equivalent - or very similar - to existing
functionality within the platform. However, there is value in abstracting this
functionality so that all app types can use it, delivering it out-of-band from
the OS, and making it available as open-source. The totality of AppLifecycle
features in v1 is as follows (additional features may be added in later
releases):

- Rich activation objects
- Selective single/multi-instancing
- System state and power notifications.

This spec addresses the System State and Power Notifications APIs in the
component.

## Background

There are several existing APIs which apps can use to detect changes in system
state, in order to participate in improved power usage and battery life. These
APIs cover most if not all of the battery/power state change scenarios that apps
would care about - but there's no single API that is easily consumable by all
app types. There's also no single API that's undocked from the OS.

This spec describes new APIs that address these issues by incorporating a
comprehensive set of the
[Windows.System.Power.PowerManager](https://docs.microsoft.com/en-us/uwp/api/Windows.System.Power.PowerManager)
WinRT API in the Reunion AppLifecycle component, and include additional
low-level notifications based on the Win32
[PowerSettingRegisterNotification](https://docs.microsoft.com/en-us/windows/win32/api/powersetting/nf-powersetting-powersettingregisternotification)
and matching
[PowerSettingUnregisterNotification](https://docs.microsoft.com/en-us/windows/win32/api/powersetting/nf-powersetting-powersettingunregisternotification)
APIs.

<br>

## Description

Providing a Reunion version of PowerManager is relatively straightforward, in
that we aim to bring across the entire existing API in its current form. For the
Win32 APIs, the situation is a little murkier. It boils down to a choice between
2 usage patterns:

- [RegisterPowerSettingNotification](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerpowersettingnotification)
  uses a Windows message-based model. When the app registers for notifications,
  the system will send out WM_POWERBROADCAST messages.
- [PowerSettingRegisterNotification](https://docs.microsoft.com/en-us/windows/win32/api/powersetting/nf-powersetting-powersettingregisternotification)
  uses a callback model. When the app registers for notifications, it supplies a
  pointer to a callback function, and the system will call back to this function
  instead of sending messages.

Classic Win32 apps can use either the WM model and/or the callback model. The
callback model is more consistent with other app types - including not only
modern UWP apps, but also traditional MFC, Winforms and WPF apps. Also, the
callback model does not prescribe a windowing or threading model, which is
better for headless/background components. Given this, since all app types can
work with the callback model, but only classic Win32 apps use the WM model, the
Reunion API will use the callback model for Cobalt. Additional WM-based behavior
can be added in a later release, if customer demand indicates it would provide
significant benefit.

The net is that the Reunion PowerManager API will be a combination of WinRT
PowerManager and Win32 PowerSettingRegisterNotification. We will define new
WinRT types (in Microsoft.ApplicationModel.PowerManager) that provide event
handlers for apps to use.

 <br>

## Examples

### Subscribing and responding to events

The power notifications are relatively simple. The app provides a callback
function for each notification it wants to receive, and when the event is raised
the system invokes that callback. The app could start listening for the
notifications at any time; it would most often do this early in its life,
perhaps in WinMain - but the AppLifecycle mechanism does not impose any
constraints on this, and the app is free to subscribe or unsubscribe at any
time.

```c++
int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    // Optionally, register callbacks for power/battery state changes.
    PowerManager::BatteryStatusChanged([](IInspectable sender, auto args)
        { OnBatteryStateChange(sender, args); });
    PowerManager::PowerSupplyStatusChanged([](IInspectable sender, auto args)
        { OnPowerStateChange(sender, args); });
    PowerManager::EnergySaverStatusChanged([](IInspectable sender, auto args)
        { OnEnergySaverStateChange(sender, args); });
    PowerManager::RemainingChargePercentChanged([](IInspectable sender, auto args)
        { OnRemainingChargePercentChange(sender, args); });
    PowerManager::RemainingDischargeTimeChanged([](IInspectable sender, auto args)
        { OnRemainingDischargeTimeChange(sender, args); });

    ///////////////////////////////////////////////////////////////////////////
    // Standard Win32 window configuration/creation and message pump:
    // ie, whatever the app would normally do - nothing new here.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLASSIC, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
```

In the app-defined callback, the app can do whatever it likes. Typically, it
would fetch the current status of the particular feature (that is, the battery
status, power supply status, energy saver status, and so on), and use that
information to form its decision. For example, if battery is at a low power
state and discharging, the app might choose to defer any non-critical background
work, in the interests of being a good power/battery citizen.

```c++
template<class T> void OnBatteryStateChange(IInspectable const& sender, T const& args)
{
    BatteryStatus batteryState = PowerManager::BatteryStatus();
    int remainingCharge = PowerManager::RemainingChargePercent();


    if (batteryState == BatteryStatus::Discharging && remainingCharge < 25)
    {
        // We're in a bad battery state, we should pause any non-critical work.
        PauseNonCriticalWork();
    }
    else if (batteryState == BatteryStatus::Charging && remainingCharge > 75)
    {
        // Battery is in great shape, let's kick of some high-power work.
        StartPowerIntensiveWork();
    }
}
```

### App logic based on multiple status values

The individual notifications are relatively low-level, and in some scenarios
each notification in itself might not provide enough information for the app to
make sensible decisions. More likely, the app will use multiple PowerManager
properties and methods to factor into its decision. For example, when it
receives a power supply state change notification, it might also want to check
the battery status before proceeding.

```c++
template<class T> void OnPowerStateChange(IInspectable const& sender, T const& args)
{
    PowerSupplyStatus powerState = PowerManager::PowerSupplyStatus();
    BatteryStatus batteryState = PowerManager::BatteryStatus();
    int remainingCharge = PowerManager::RemainingChargePercent();

    if (batteryState == BatteryStatus::Discharging
        && remainingCharge < 25
        && powerState != PowerSupplyStatus::Adequate)
    {
        // We're in a bad power/battery state: let's pause any non-critical work.
        PauseNonCriticalWork();
    }
    else if (powerState == PowerSupplyStatus::Adequate ||
        (batteryState == BatteryStatus::Charging && remainingCharge > 75))
    {
        // Power/battery is in great shape, let's kick of some high-power work.
        StartPowerIntensiveWork();
    }
}
```

### New API combines multiple old APIs

The additional enums, properties and events brought forward for the
PowerSettingRegisterNotification functionality should be completely seamless and
indistinguishable from the existing PowerManager members, such that the app can
consume these in exactly the same way.

```c++
    PowerManager::ConsoleStatusChanged([](IInspectable sender, auto args)
        { OnConsoleStatusChange(sender, args); });

template<class T> void OnDisplayStateChange(IInspectable const& sender, T const& args)
{
    DisplayStatus displayState = PowerManager::DisplayStatus;
    if (displayState == DisplayStatus::Off)
    {
        // The screen is off, let's stop rendering foreground graphics,
        // and instead kick off some background work now.
        StopRenderingGraphics();
        StartDoingBackgroundWork();
    }
}
```

### Unsubscribing

The main goal of the power notifications is to give apps more tools to enable
them to be power/battery-aware and to reduce their resource usage when they can,
and factoring in the current system state. So, in many cases, it will make sense
for the app to subscribe to the events for much if not all of its lifetime.
Nonetheless, apps should also have a way to unsubscribe from any of the
notifications, and re-subscribe at any time that suits them.

A C# app that consumes WinRT events can subscribe via the += operator and
unsubscribe via the -= operator. A C++ app can subscribe via the registration
method that is projected for the event (which returns a token), and unsubscribe
via the revoker method (which takes in a token).

```c++
winrt::event_token batteryToken;
winrt::event_token powerToken;

void MyRegisterPowerManagerCallbacks()
{
    batteryToken = PowerManager::BatteryStatusChanged([](IInspectable sender, auto args)
        { OnBatteryStateChange(sender, args); });
    powerToken = PowerManager::PowerSupplyStatusChanged([](IInspectable sender, auto args)
        { OnPowerStateChange(sender, args); });
    //...etc
}

void MyUnregisterPowerManagerCallbacks()
{
    PowerManager::BatteryStatusChanged(batteryToken);
    PowerManager::PowerSupplyStatusChanged(powerToken);
    //...etc
}
```

<br>

## API Details

### Existing APIs

This set of APIs is a subset of the union of the existing WinRT PowerManager
class and the existing PowerSettingRegisterNotification API.

The existing PowerSettingRegisterNotification API takes 4 parameters:

| PowerSettingRegisterNotification parameter | Description                                                                                                                                               |
| ------------------------------------------ | --------------------------------------------------------------------------------------------------------------------------------------------------------- |
| LPCGUID SettingGuid                        | A GUID that represents the specific power setting in which the app is interested.                                                                         |
| DWORD Flags                                | This is either DEVICE_NOTIFY_SERVICE_HANDLE if the Recipient is a service, or DEVICE_NOTIFY_CALLBACK if the Recipient is a callback function.             |
| HANDLE Recipient                           | A handle to the recipient of the notifications.                                                                                                           |
| PHPOWERNOTIFY RegistrationHandle           | Out parameter: a handle to the registration, which the app can later use to unregister for notifications, via the PowerSettingUnregisterNotification API. |

Reunion AppLifecycle will not bring this function forward in its current form.
Instead, AppLifecycle will bring the functionality forward using the
PowerManager pattern for the additional PowerSettingRegisterNotification
notifications:

- Instead of a single register function that takes a GUID, the new API will
  expose multiple new events, mapping to each of the GUIDs that are brought
  forward. Not all GUIDs will be brought forward, as some of them are already
  covered by PowerManager events.
- For Reunion v1, the target consumers of the new APIs are scoped to apps not
  services - this eliminates the need for the Flags parameter.
- The new API will adopt the PowerManager pattern for registering and
  unregistering callbacks, which eliminates the need for the register/unregister
  handles.

The notification pattern for PowerSettingRegisterNotification is to send
additional data on the updated state along with the notification. Conversely,
the pattern for PowerManager is to send no additional data, and the app is
expected to query the current state via the enum-based PowerManager properties
instead. This means that along with the new events, the new API will also expose
new properties where appropriate. The well-known
[power-setting GUIDs](https://docs.microsoft.com/en-us/windows/win32/power/power-setting-guids)
are listed below, along with the proposed mappings to new PowerManager events
and enum-based properties.

| Existing GUID                     | Description                                                                                                                                                                                                            | New event/property                                                                              |
| --------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------- |
| GUID_ACDC_POWER_SOURCE            | The system power source has changed.                                                                                                                                                                                   | PowerSourceStatusChanged, PowerSourceStatus {AC, DC, ShortTerm}.                                |
| GUID_BATTERY_PERCENTAGE_REMAINING | The remaining battery capacity has changed.                                                                                                                                                                            | Equivalent to PowerManager. RemainingChargePercentChanged, RemainingChargePercent.              |
| GUID_CONSOLE_DISPLAY_STATE        | The current monitor's display state has change. Apps should stop rendering graphics content when the monitor is off to reduce system power consumption.                                                                | DisplayStatusChanged, DisplayStatus {Off, On, Dimmed}.                                          |
| GUID_GLOBAL_USER_PRESENCE         | The user status associated with any session has changed. This notification is only to services and other programs running in session 0. User-mode applications should register for GUID_SESSION_USER_PRESENCE instead. | NOT IMPLEMENTED IN REUNION v1                                                                   |
| GUID_IDLE_BACKGROUND_TASK         | The system is busy: now is a good time for apps to perform background or idle tasks that would otherwise prevent the computer from entering an idle state.                                                             | SystemIdleStatusChanged, SystemIdleStatus { Idle, Busy}.                                        |
| GUID_MONITOR_POWER_ON             | The monitor has been powered on or off. From Windows 8 and Windows Server 2012, apps should use GUID_CONSOLE_DISPLAY_STATE instead.                                                                                    | NOT IMPLEMENTED IN REUNION v1                                                                   |
| GUID_POWER_SAVING_STATUS          | Battery saver has been turned on or off.                                                                                                                                                                               | Equivalent to PowerManager. EnergySaverStatusChanged, EnergySaverStatus.                        |
| GUID_POWERSCHEME_PERSONALITY      | The active power scheme personality has changed. All power schemes map to one of these personalities.                                                                                                                  | PowerSchemePersonalityChanged, PowerSchemePersonality { HighPerformance, PowerSaver, Balanced}. |
| GUID_SESSION_DISPLAY_STATUS       | The display associated with the application's session has been powered on or off.                                                                                                                                      | Covered by GUID_CONSOLE_DISPLAY_STATE.                                                          |
| GUID_SESSION_USER_PRESENCE        | The user status associated with the application's session has changed.                                                                                                                                                 | UserPresenceStatusChanged, UserPresenceStatus {Present, Absent}.                                |
| GUID_SYSTEM_AWAYMODE              | The system is entering or exiting away mode.                                                                                                                                                                           | SystemAwayModeStatusChanged, SystemAwayModeStatus {Entering, Exiting}.                          |

The existing PowerManager class exposes only static properties and events: all
members are valid to be brought over to the Reunion version. The top-level
classes and enums are listed in the following table:

| New Classes and Enums                                               | Description                                                          |
| ------------------------------------------------------------------- | -------------------------------------------------------------------- |
| enum BatteryStatus {NotPresent, Discharging, Idle, Charging}        | Clone of Windows.System.Power.BatteryStatus.                         |
| enum EnergySaverStatus {Disabled, Off, On}                          | Clone of Windows.System.Power.EnergySaverStatus.                     |
| enum PowerSupplyStatus {NotPresent, Inadequate, Adequate}           | Clone of Windows.System.Power.PowerSupplyStatus.                     |
| class PowerManager                                                  | Clone of Windows.System.Power.PowerManager.                          |
| enum PowerSourceStatus {AC, DC, ShortTerm}                          | New enum, for the status of the device's power source.               |
| enum DisplayStatus {Off, On, Dimmed}                                | New enum, for the current display state.                             |
| enum SystemIdleStatus {Idle, Busy}                                  | New enum, for whether the system is busy or idle.                    |
| enum PowerSchemePersonality {HighPerformance, PowerSaver, Balanced} | New enum for the active power scheme personality.                    |
| enum UserPresenceStatus {Present, Absent}                           | New enum for whether the user is present or absent (active or idle). |
| enum SystemAwayModeStatus {Entering, Exiting}                       | New enum for whether the system is entering or exiting away mode.    |

The combined set of members for the Reunion PowerManager class is listed below.

| PowerManager Class Members                                      | Description                                                                                                  |
| --------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------ |
| static BatteryStatus BatteryStatus                              | Readonly property, gets the device's battery status.                                                         |
| static EnergySaverStatus EnergySaverStatus                      | Readonly property, gets the device's energy-saver status.                                                    |
| static PowerSupplyStatus PowerSupplyStatus                      | Readonly property, gets the device's power supply status.                                                    |
| static int RemainingChargePercent                               | Readonly property, gets the total percentage of charge remaining from all batteries connected to the device. |
| static TimeSpan RemainingDischargeTime                          | Readonly property, gets the total runtime remaining from all batteries connected to the device.              |
| static event EventHandler<object> BatteryStatusChanged          | Event raised when the BatteryStatus changes.                                                                 |
| static event EventHandler<object> EnergySaverStatusChanged      | Event raised when the EnergySaverStatus changes.                                                             |
| static event EventHandler<object> PowerSupplyStatusChanged      | Event raised when the PowerSupplyStatus changes.                                                             |
| static event EventHandler<object> RemainingChargePercentChanged | Event raised when the RemainingChargePercent changes.                                                        |
| static event EventHandler<object> RemainingDischargeTimeChanged | Event raised when the RemainingDischargeTime changes.                                                        |
| static PowerSourceStatus PowerSourceStatus                      | Readonly property, gets the device's current power source.                                                   |
| static event EventHandler<object> PowerSourceStatusChanged      | Event raised when the system power source has changed.                                                       |
| static DisplayStatus DisplayStatus                              | Readonly property, gets the current display state.                                                           |
| static event EventHandler<object> DisplayStatusChanged          | Event raised when the current display state has changed.                                                     |
| static SystemIdleStatus SystemIdleStatus                        | Readonly property, gets the current system idle status.                                                      |
| static event EventHandler<object> SystemIdleStatusChanged       | Event raised when the system's idle state has changed.                                                       |
| static PowerSchemePersonality PowerSchemePersonality            | Readonly property, gets the active power scheme personality.                                                 |
| static event EventHandler<object> PowerSchemePersonalityChanged | Event raised when the active power scheme personality has changed.                                           |
| static UserPresenceStatus UserPresenceStatus                    | Readonly property, gets the user's present/absent status.                                                    |
| static event EventHandler<object> UserPresenceStatusChanged     | Event raised when the user's presence status has changed.                                                    |
| static SystemAwayModeStatus SystemAwayModeStatus                | Readonly property, gets the entering/exiting status of the system away mode.                                 |
| static event EventHandler<object> SystemAwayModeStatusChanged   | Event raised when the system is entering or exiting away mode.                                               |

<br>
<br>
