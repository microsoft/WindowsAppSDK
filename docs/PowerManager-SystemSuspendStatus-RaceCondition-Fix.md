# PowerManager SystemSuspendStatus Race Condition Fix

## Problem

The `PowerManager.SystemSuspendStatus` property together with the `SystemSuspendStatusChanged` event had a race condition that made it unreliable.

### Root Cause

The original event signature was:
```csharp
static event Windows.Foundation.EventHandler<Object> SystemSuspendStatusChanged;
```

Because the event had no arguments, developers had to query the `SystemSuspendStatus` property separately within their event handler. However, between the time the event fired and when the handler queried the property, another event could occur on a different thread, overwriting the `m_systemSuspendStatus` value.

### Common Scenario

This commonly happened when waking from standby. According to the [Win32 API documentation](https://learn.microsoft.com/en-us/windows/win32/power/pbt-apmresumesuspend):

> If the system wakes due to user activity (such as pressing the power button) or if the system detects user interaction at the physical console (such as mouse or keyboard input) after waking unattended, the system first broadcasts the PBT_APMRESUMEAUTOMATIC event, then it broadcasts the PBT_APMRESUMESUSPEND event.

These two events fire in rapid succession on different threads, causing the race condition:

**Expected behavior:**
```
2025-03-12 21:20:19Z SystemSuspendStatusChanged: AutoResume (Thread 5)
2025-03-12 21:20:19Z SystemSuspendStatusChanged: ManualResume (Thread 6)
```

**Actual behavior (race condition):**
```
2025-03-12 21:21:46Z SystemSuspendStatusChanged: ManualResume (Thread 5)  // Wrong!
2025-03-12 21:21:47Z SystemSuspendStatusChanged: ManualResume (Thread 6)  // Correct
```

## Solution

A new event `SystemSuspendStatusChanged2` was added with a proper event args type that includes the status value:

```csharp
[contract(PowerNotificationsContract, 2)]
runtimeclass SystemSuspendStatusChangedEventArgs
{
    SystemSuspendStatus Status{ get; };
}

static event Windows.Foundation.TypedEventHandler<Object, SystemSuspendStatusChangedEventArgs> SystemSuspendStatusChanged2;
```

### Key Changes

1. **New Event Args Type**: `SystemSuspendStatusChangedEventArgs` includes a `Status` property that contains the exact status for that event.

2. **Modified Event Callback**: The internal `SystemSuspendStatusChanged_Callback` now:
   - Captures the status value before raising events
   - Raises both the old event (for backward compatibility) and the new event
   - Passes the captured status as event args to the new event

3. **Thread-Safe Status Delivery**: Since the status is captured at the time the OS callback fires and passed as part of the event args, each event handler receives the correct status regardless of timing.

### Implementation Details

```cpp
void SystemSuspendStatusChanged_Callback(ULONG PowerEvent)
{
    Power::SystemSuspendStatus newStatus;
    
    if (PowerEvent == PBT_APMSUSPEND)
        newStatus = SystemSuspendStatus::Entering;
    else if (PowerEvent == PBT_APMRESUMEAUTOMATIC)
        newStatus = SystemSuspendStatus::AutoResume;
    else if (PowerEvent == PBT_APMRESUMESUSPEND)
        newStatus = SystemSuspendStatus::ManualResume;
    else
        return; // Unknown event
    
    // Update stored status
    m_systemSuspendStatus = newStatus;
    
    // Raise both events with the captured status
    RaiseSystemSuspendStatusEvent(newStatus);
}

winrt::fire_and_forget RaiseSystemSuspendStatusEvent(Power::SystemSuspendStatus status)
{
    auto lifetime = get_strong();
    co_await winrt::resume_background();
    
    // Raise old event (without args)
    m_systemSuspendStatusChangedEvent(nullptr, nullptr);
    
    // Raise new event (with args)
    auto args = winrt::make<implementation::SystemSuspendStatusChangedEventArgs>(status);
    m_systemSuspendStatusChanged2Event(nullptr, args);
}
```

## Usage

### Old Event (Deprecated - Race Condition)

```csharp
// DO NOT USE - Subject to race condition
PowerManager.SystemSuspendStatusChanged += (sender, e) =>
{
    var status = PowerManager.SystemSuspendStatus; // May be wrong!
    Console.WriteLine($"Status: {status}");
};
```

### New Event (Recommended - Race-Free)

```csharp
// RECOMMENDED - Always correct
PowerManager.SystemSuspendStatusChanged2 += (sender, args) =>
{
    var status = args.Status; // Always correct for this event
    Console.WriteLine($"Status: {status}");
};
```

### C++ Example

```cpp
auto token = PowerManager::SystemSuspendStatusChanged2(
    [](auto const&, SystemSuspendStatusChangedEventArgs const& args)
    {
        auto status = args.Status();
        switch (status)
        {
            case SystemSuspendStatus::Entering:
                // System is about to suspend
                break;
            case SystemSuspendStatus::AutoResume:
                // System resumed automatically (e.g., wake timer)
                break;
            case SystemSuspendStatus::ManualResume:
                // System resumed due to user action
                break;
        }
    });
```

## Backward Compatibility

The original `SystemSuspendStatusChanged` event remains unchanged to maintain backward compatibility. Applications should migrate to `SystemSuspendStatusChanged2` to avoid race conditions.

Both events fire when a suspend/resume event occurs, so existing code continues to work (with the race condition), while new code can use the race-free API.

## Migration Guide

### Before (Race Condition)
```csharp
PowerManager.SystemSuspendStatusChanged += OnSystemSuspendStatusChanged;

private void OnSystemSuspendStatusChanged(object sender, object e)
{
    var status = PowerManager.SystemSuspendStatus; // RACE CONDITION!
    HandleSuspendStatus(status);
}
```

### After (Race-Free)
```csharp
PowerManager.SystemSuspendStatusChanged2 += OnSystemSuspendStatusChanged2;

private void OnSystemSuspendStatusChanged2(object sender, SystemSuspendStatusChangedEventArgs e)
{
    var status = e.Status; // Always correct!
    HandleSuspendStatus(status);
}
```

## Testing

The fix ensures that when multiple suspend/resume events fire in quick succession:

1. Each event handler receives the correct status for that specific event
2. `AutoResume` events are never lost or overwritten
3. The sequence of `AutoResume` followed by `ManualResume` is preserved

### Test Scenario

1. Put the computer into standby
2. Wake the computer by pressing the power button
3. Verify both `AutoResume` and `ManualResume` events fire with correct values

Expected output:
```
SystemSuspendStatusChanged2: Entering
SystemSuspendStatusChanged2: AutoResume
SystemSuspendStatusChanged2: ManualResume
```

### Unit Tests

Unit tests have been added in `test/PowerNotifications/APITests.cpp` and `test/PowerNotifications/FunctionalTests.cpp` to verify:

1. Event registration works correctly
2. Event args can be accessed and contain a valid status value
3. Both old and new events can be registered simultaneously without conflicts

**Note**: The unit tests only verify registration and type safety. Full integration testing requires:
- A Windows environment with the Windows App SDK build tools
- Physical or simulated system suspend/resume events
- Manual verification that both events fire with correct status values

## API Version

- `SystemSuspendStatus` enum: PowerNotificationsContract v1
- `SystemSuspendStatusChanged` event: PowerNotificationsContract v1
- `SystemSuspendStatusChangedEventArgs` class: PowerNotificationsContract v2
- `SystemSuspendStatusChanged2` event: PowerNotificationsContract v2

## References

- [Issue #4966](https://github.com/microsoft/WindowsAppSDK/issues/4966)
- [PBT_APMRESUMESUSPEND documentation](https://learn.microsoft.com/en-us/windows/win32/power/pbt-apmresumesuspend)
- [PBT_APMRESUMEAUTOMATIC documentation](https://learn.microsoft.com/en-us/windows/win32/power/pbt-apmresumeautomatic)
