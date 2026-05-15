# EnergySaverStatus2 API

| | |
|-|-|
| **Area** | OS\Windows Client and Services\Fundamentals\PH-Platform Health\Sustainability |
| **Product/Program Manager** | Ugochi Nweze (nwezeugochi) |
| **Developer** | Tobi Adebisi (adebisitobi), Ruth Waiganjo (ruthwaiganjo) |
| **API Design Representative** | Minsang Kim (mikim) |
| **ADO – Implementation** | Task 60383995 |
| **ADO – Testing** | Task 61020635 |
| **ADO – Sample** | Task 61020638 |
| **ADO – Documentation** | Task 61020649 |

# Background

The existing `Microsoft.Windows.System.Power.PowerManager.EnergySaverStatus` property reports
only two states: `Off` and `On`. Starting with the Windows Germanium release, the OS Energy Saver
feature was updated to support three distinct operating modes — **Off**, **Standard**, and
**High Savings** — which are now visible to users in the Windows Settings app.

The original two-state API contains a bug: when Energy Saver is active in **Standard** mode
(battery above 20%), `EnergySaverStatus` incorrectly reports `Off`. Only the **High Savings**
state (battery at or below 20%) correctly maps to `On`.

This spec introduces `EnergySaverStatus2`, a new enum and associated APIs on
`Microsoft.Windows.System.Power.PowerManager`, that accurately reflects all three energy saver
states. The legacy `EnergySaverStatus` API is unchanged for backward compatibility.

> **Minimum OS requirement:** These APIs require a Germanium+ OS build. On earlier OS versions,
> `IsEnergySaverStatus2Supported` returns `false` and `EnergySaverStatus2` returns `Unknown`.

# Conceptual pages (How To)

_(This is conceptual documentation that will go to docs.microsoft.com "how to" page)_

## Responding to Energy Saver state changes in your app

Energy Saver helps extend battery life by signaling apps to reduce resource consumption.
Starting with Windows Germanium, Energy Saver has three states that your app can respond to
with varying levels of optimization:

| State | Meaning | Recommended app behavior |
|---|---|---|
| `Off` | Energy Saver is disabled | Normal operation |
| `Standard` | Energy Saver active; mild performance impact acceptable | Reduce background sync frequency, defer non-critical work |
| `HighSavings` | Energy Saver active; maximum power savings preferred | Pause background sync, defer all non-critical work, reduce UI refresh rates |

Use `PowerManager.EnergySaverStatus2` to read the current state and subscribe to
`PowerManager.EnergySaverStatus2Changed` to respond to transitions at runtime.

Always call `PowerManager.IsEnergySaverStatus2Supported()` first if your app targets systems
that may run on OS versions earlier than Germanium. On unsupported systems, the property
returns `Unknown` and the changed event is never raised.

# API Pages

_(Each of the following L2 sections correspond to a page that will be on docs.microsoft.com)_

## PowerManager.EnergySaverStatus2 property

Gets the current Energy Saver v2 status for the device.

```csharp
public static EnergySaverStatus2 EnergySaverStatus2 { get; }
```

```cppwinrt
static EnergySaverStatus2 EnergySaverStatus2();
```

Use this property together with `EnergySaverStatus2Changed` to monitor power-state transitions
and adjust your app's resource usage accordingly. When Energy Saver is in `Standard` mode your
app should reduce non-critical background work; in `HighSavings` mode it should defer or pause
background operations entirely.

### Example – Reading the current status (C#)

```csharp
using Microsoft.Windows.System.Power;

EnergySaverStatus2 status = PowerManager.EnergySaverStatus2;
switch (status)
{
    case EnergySaverStatus2.Off:
        // Normal operation
        break;
    case EnergySaverStatus2.Standard:
        // Reduce background activity
        break;
    case EnergySaverStatus2.HighSavings:
        // Pause background activity
        break;
    case EnergySaverStatus2.Unknown:
    default:
        // API not supported on this OS build
        break;
}
```

### Example – Reading the current status (C++/WinRT)

```cpp
#include <winrt/Microsoft.Windows.System.Power.h>

using namespace winrt::Microsoft::Windows::System::Power;

EnergySaverStatus2 status = PowerManager::EnergySaverStatus2();
switch (status)
{
    case EnergySaverStatus2::Off:
        // Normal operation
        break;
    case EnergySaverStatus2::Standard:
        // Reduce background activity
        break;
    case EnergySaverStatus2::HighSavings:
        // Pause background activity
        break;
    case EnergySaverStatus2::Unknown:
    default:
        // API not supported on this OS build
        break;
}
```

### Remarks

- Returns `Unknown` if `IsEnergySaverStatus2Supported()` returns `false`.
- This property is safe to call from background tasks and non-foreground windows.
- Does not require any special app capabilities.

---

## PowerManager.EnergySaverStatus2Changed event

Occurs when the `EnergySaverStatus2` value changes.

```csharp
public static event System.EventHandler<object> EnergySaverStatus2Changed;
```

```cppwinrt
static winrt::event_token EnergySaverStatus2Changed(
    winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable> const& handler);

static void EnergySaverStatus2Changed(winrt::event_token const& token) noexcept;
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
    }
}

// Unsubscribe when done
PowerManager.EnergySaverStatus2Changed -= OnEnergySaverStatus2Changed;
```

### Example – Subscribing to status changes (C++/WinRT)

```cpp
#include <winrt/Microsoft.Windows.System.Power.h>

using namespace winrt::Microsoft::Windows::System::Power;

auto revoker = PowerManager::EnergySaverStatus2Changed(
    winrt::auto_revoke,
    [](auto, winrt::Windows::Foundation::IInspectable const&)
    {
        EnergySaverStatus2 status = PowerManager::EnergySaverStatus2();
        // Respond to new state
    });
```

### Remarks

- The event is never raised on OS builds where `IsEnergySaverStatus2Supported()` returns `false`.
- The event is raised on the thread that registered, unless the implementation routes it through a
  dispatcher — subscribe and unsubscribe on the same thread.

---

## PowerManager.IsEnergySaverStatus2Supported method

Returns a value indicating whether the current OS supports `EnergySaverStatus2`.

```csharp
public static bool IsEnergySaverStatus2Supported();
```

```cppwinrt
static bool IsEnergySaverStatus2Supported();
```

Call this method before using `EnergySaverStatus2` or `EnergySaverStatus2Changed` when your app
may run on OS versions earlier than Germanium. On unsupported builds, the property returns
`Unknown` and the event is never raised.

### Example (C#)

```csharp
using Microsoft.Windows.System.Power;

if (!PowerManager.IsEnergySaverStatus2Supported())
{
    // Fall back to legacy EnergySaverStatus
    return;
}

EnergySaverStatus2 status = PowerManager.EnergySaverStatus2;
```

### Remarks

- Calling this method is optional. You can use `EnergySaverStatus2` without it; if the feature is
  unsupported the property safely returns `Unknown`.
- Returns `true` only on Germanium+ OS builds.

---

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
| `Unknown` | The Energy Saver v2 status is unavailable, either because the OS does not support it or because the status has not yet been initialized. |
| `Off` | Energy Saver is disabled. Apps should operate normally. |
| `Standard` | Energy Saver is active with mild performance impact acceptable. Energy saving behaviors that have mild performance impact are encouraged (for example, a sync client might reduce sync frequency). This state is returned when the user has opted into Energy Saver but battery life is not critical. |
| `HighSavings` | Energy Saver is active and maximum battery savings are preferred, even at the cost of performance. This state is returned when battery level is low and the device is not plugged in. |

### Remarks

- `EnergySaverStatus2` may be extended with additional values in future OS releases. Your code
  should handle unknown enum values gracefully (for example, with a `default` case in a `switch`).
- The enum values map to the legacy `EnergySaverStatus` as follows:

| `EnergySaverStatus2` | Legacy `EnergySaverStatus` |
|---|---|
| `Off` | `Off` |
| `Standard` | `Off` _(legacy API does not distinguish this state)_ |
| `HighSavings` | `On` |

---

## Other PowerManager members

For the full list of existing `PowerManager` members see
[Microsoft.Windows.System.Power.PowerManager](https://learn.microsoft.com/windows/apps/api-reference/).

# API Details

```csharp (but really MIDL3)
namespace Microsoft.Windows.System.Power
{
    [contractversion(3)]
    apicontract PowerNotificationsContract{};

    // Existing EnergySaverStatus enum (unchanged)
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
        /// The status is unavailable or unsupported on this OS build.
        Unknown     = 0,
        /// Energy Saver is disabled.
        Off         = 1,
        /// Energy Saver is active; mild performance impact is acceptable.
        Standard    = 2,
        /// Energy Saver is active; maximum battery savings are preferred.
        HighSavings = 3
    };

    [contract(PowerNotificationsContract, 1)]
    static runtimeclass PowerManager
    {
        // ... existing members (unchanged) ...

        /// Gets the current Energy Saver v2 status for the device.
        [contract(PowerNotificationsContract, 3)]
        static EnergySaverStatus2 EnergySaverStatus2{ get; };

        /// Occurs when the EnergySaverStatus2 value changes.
        [contract(PowerNotificationsContract, 3)]
        static event Windows.Foundation.EventHandler<Object> EnergySaverStatus2Changed;

        /// Returns true if this OS build supports EnergySaverStatus2; false otherwise.
        [contract(PowerNotificationsContract, 3)]
        static Boolean IsEnergySaverStatus2Supported();
    };
}
```

# Appendix

## Legacy API compatibility and mapping

`EnergySaverStatus2` is an additive API and does not replace `EnergySaverStatus`. Apps that
currently use `EnergySaverStatus` will continue to work unchanged. The legacy API's behavior
is not modified.

The legacy `EnergySaverStatus` has a known limitation: when Energy Saver is active in **Standard**
mode (battery above 20%), it reports `Off`, meaning apps using the legacy API cannot distinguish
"Energy Saver Standard active" from "Energy Saver disabled". `EnergySaverStatus2` fixes this.

## Alternative designs considered

- **Extend the existing enum** – Adding `Standard` and `HighSavings` values to `EnergySaverStatus`
  was rejected because it would be a breaking change for existing switch statements that do not
  handle new enum values.
- **New PowerManager class** – Rejected in favor of additive members on the existing
  `PowerManager` static class to maintain API surface consistency.

## Related ADO tasks

| Task | Description |
|---|---|
| 60383995 | Energy Saver on UWP: New 3P API Development and SDK Updates |
| 61020635 | Testing: Energy Saver on UWP |
| 61020638 | Sample Application(s): Energy Saver on UWP |
| 61020649 | Documentation: Energy Saver on UWP |
