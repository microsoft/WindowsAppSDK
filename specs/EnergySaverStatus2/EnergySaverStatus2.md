# EnergySaverStatus2 API

# Background

The existing `Microsoft.Windows.System.Power.PowerManager.EnergySaverStatus` property reports
only two states: `Off` and `On`. 
Starting with the [Windows 11, 24H2]() release, the [Energy Saver](https://learn.microsoft.com/en-us/windows-hardware/design/component-guidelines/energy-saver)
feature was updated to support three distinct operating modes: **Off**, **Standard**, and
**High Savings** which are now visible to users in the Windows Settings app.

The original two-state API has an inconsistency : when Energy Saver is active in **Standard** mode, `EnergySaverStatus` incorrectly reports `Off`. Only the **High Savings** state correctly maps to `On`.

This spec introduces `EnergySaverStatus2`, a new enum and associated APIs on
`Microsoft.Windows.System.Power.PowerManager`, that accurately reflects all three energy saver
states. The legacy `EnergySaverStatus` API is unchanged for backward compatibility.

> ⚠️ **Deprecation notice:** `PowerManager.EnergySaverStatus`, `PowerManager.EnergySaverStatusChanged`,
> and the `EnergySaverStatus` enum are deprecated. Use `PowerManager.EnergySaverStatus2`,
> `PowerManager.EnergySaverStatus2Changed`, and the `EnergySaverStatus2` enum instead.

> **Minimum OS requirement:** These APIs require a Windows 11, 24H2 build. On earlier OS versions,
> `EnergySaverStatus2` returns `Unknown`.

# Conceptual pages 

## Responding to Energy Saver state changes in your app

Energy Saver helps extend battery life by signaling apps to reduce resource consumption.
Energy Saver has three states that your app can respond to
with varying levels of optimization:

| State | Meaning | Recommended app behavior |
|---|---|---|
| `Off` | Energy Saver is inactive | Normal operation |
| `Standard` | Energy Saver active; mild performance impact acceptable | Reduce background sync frequency, defer non-critical work |
| `HighSavings` | Energy Saver active; maximum power savings preferred | Pause background sync, defer all non-critical work, reduce UI refresh rates |

Use `PowerManager.EnergySaverStatus2` to read the current state and subscribe to
`PowerManager.EnergySaverStatus2Changed` to respond to transitions at runtime.

On unsupported systems, the property
returns `Unknown` and the changed event is never raised.

# API Pages
## PowerManager.EnergySaverStatus2 property

Gets the current Energy Saver v2 status for the device.

```csharp
public static EnergySaverStatus2 EnergySaverStatus2 { get; }
```

Use this property together with `EnergySaverStatus2Changed` to monitor power-state transitions
and adjust your app's resource usage accordingly. When Energy Saver is in `Standard` mode your
app should reduce non-critical background work; in `HighSavings` mode it should defer or pause
background operations entirely.

### Example – Reading the current status (C#)

```csharp
/*
Example: An app or service that periodically sends a heartbeat (ping/pong)
to a server to maintain connectivity and monitor health. The interval can
be adjusted based on the system's energy saver level to reduce power/battery usage
*/

using Microsoft.Windows.System.Power;

// Default heartbeat interval (Normal operation)
TimeSpan heartbeatInterval = TimeSpan.FromSeconds(10);

EnergySaverStatus2 status = PowerManager.EnergySaverStatus2;

switch (status)
{
    case EnergySaverStatus2.Off:
        // Normal operation: maintain default heartbeat interval (e.g., 10 sec)
        break;
    case EnergySaverStatus2.Standard:
        // Moderate savings: reduce background network activity
        // (e.g., increase heartbeat interval to reduce frequency)
        heartbeatInterval = TimeSpan.FromSeconds(20);
        break;
    case EnergySaverStatus2.HighSavings:
        // Aggressive savings: reduce ping/pong traffic to the server by ~50%+
        // (e.g., double or triple the interval between heartbeats to conserve power)
        heartbeatInterval = TimeSpan.FromSeconds(30);
        break;
    case EnergySaverStatus2.Unknown:
        //  State is explicitly unknown
        //  Maintain default heartbeat interval (e.g., 10 sec)
        break;
     default:
        // Unexpected state
        // Default to normal operation heartbeat interval (e.g., 10 sec)
        // or have a conservative fallback TimeSpan.FromSeconds(20);         
        break;
}
```

## PowerManager.EnergySaverStatus2Changed event

Occurs when the `EnergySaverStatus2` value changes.

```csharp
public static event System.EventHandler<object> EnergySaverStatus2Changed;
```

Subscribe to this event to receive notifications when the device transitions between Energy Saver
states. When the event fires, call `PowerManager.EnergySaverStatus2` to retrieve the new value.

### Example – Subscribing to status changes (C#)

```csharp
using Microsoft.Windows.System.Power;

// Subscribe
PowerManager.EnergySaverStatus2Changed += OnEnergySaverStatus2Changed;

// Handler
private static void OnEnergySaverStatus2Changed(object sender, object e)
{
    EnergySaverStatus2 status = PowerManager.EnergySaverStatus2;
    switch (status)
    {
        case EnergySaverStatus2.Standard:
            ReduceBackgroundActivity();
            break;
        case EnergySaverStatus2.HighSavings:
            PauseBackgroundActivity();
            break;
        case EnergySaverStatus2.Off:
            ResumeNormalActivity();
            break;
       case EnergySaverStatus2.Unknown:
            // State is explicitly unknown
            // Default to normal operation
            ResumeNormalActivity();
            break;
       default:
            // Unexpected state
            // Default to normal operation  ResumeNormalActivity();
            // or have a conservative fallback  ReduceBackgroundActivity();         
            break;
    }
}

// Unsubscribe when done
PowerManager.EnergySaverStatus2Changed -= OnEnergySaverStatus2Changed;
```

## EnergySaverStatus2 enum

Represents the current Energy Saver mode of the device using the expanded v2 state.

```csharp
public enum EnergySaverStatus2
{
    Unknown     = 0,
    Off         = 1,
    Standard    = 2,
    HighSavings = 3
}
```

| Value | Description |
|---|---|
| `Unknown` | The Energy Saver v2 status is unavailable. |
| `Off` | Energy Saver is inactive. Apps should operate normally. |
| `Standard` | Energy Saver is active with mild performance impact acceptable. Energy saving behaviors that have mild performance impact are encouraged (for example, a sync client might reduce sync frequency). This state is returned when the user has opted into Energy Saver but battery life is not critical. |
| `HighSavings` | Energy Saver is active and maximum battery savings are preferred, even at the cost of performance. This state is returned when battery level is low and the device is not plugged in. |

### Remarks

- `EnergySaverStatus2` may be extended with additional values in future OS releases. Your code
  should handle unknown enum values gracefully (for example, with a `default` case in a `switch`).
- The legacy `EnergySaverStatus` enum, `PowerManager.EnergySaverStatus` property, and
  `PowerManager.EnergySaverStatusChanged` event are deprecated. Migrate to `EnergySaverStatus2`,
  `PowerManager.EnergySaverStatus2`, and `PowerManager.EnergySaverStatus2Changed`.
- The enum values map to the legacy `EnergySaverStatus` as follows:

| `EnergySaverStatus2` | Legacy `EnergySaverStatus` |
|---|---|
| `Off` | `Off` |
| `Standard` | `Off` _(legacy API does not distinguish this state)_ |
| `HighSavings` | `On` |

---

## Other PowerManager members

For the full list of existing `PowerManager` members see
[Microsoft.Windows.System.Power.PowerManager](https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/microsoft.windows.system.power.powermanager?view=windows-app-sdk-1.7).

# API Details
```
namespace Microsoft.Windows.System.Power
{
    [contractversion(3)]
    apicontract PowerNotificationsContract{};

    [contract(PowerNotificationsContract, 1)]
    enum EnergySaverStatus
    {
        Uninitialized = 0,
        Disabled,
        Off,
        On
    };

    /// Represents the current energy saver mode of the device using the expanded v2 state.
    [contract(PowerNotificationsContract, 3)]
    enum EnergySaverStatus2
    {
        Unknown     = 0,
        Off         = 1,
        Standard    = 2,
        HighSavings = 3
    };

    [contract(PowerNotificationsContract, 1)]
    static runtimeclass PowerManager
    {
        // ... existing members (unchanged) ...
 
        [contract(PowerNotificationsContract, 3)]
        static EnergySaverStatus2 EnergySaverStatus2{ get; }; // Gets the current Energy Saver v2 status for the device.
        static event Windows.Foundation.EventHandler<Object> EnergySaverStatus2Changed; // Occurs when the EnergySaverStatus2 value changes.
    };
}
```

# Appendix

## Legacy API compatibility and mapping

> ⚠️ **Deprecation notice:** `PowerManager.EnergySaverStatus`, `PowerManager.EnergySaverStatusChanged`,
> and the `EnergySaverStatus` enum are deprecated. Use `PowerManager.EnergySaverStatus2`,
> `PowerManager.EnergySaverStatus2Changed`, and the `EnergySaverStatus2` enum instead.

The legacy `EnergySaverStatus` has a known limitation: when Energy Saver is active in **Standard**
mode, it reports `Off`, meaning apps using the legacy API cannot distinguish
"Energy Saver Standard active" from "Energy Saver disabled". `EnergySaverStatus2` fixes this.

