AppWindow Placement APIs
===

# Background

Windows App SDK 2.0 Experimental introduces placement APIs on the
[AppWindow](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.ui.windowing.appwindow)
class. These APIs allow developers to save, restore, and manage window placement
(position, size, and state) across application sessions.

Previously, developers had to manually call Win32
[GetWindowPlacement](https://learn.microsoft.com/windows/win32/api/winuser/nf-winuser-getwindowplacement)
and
[SetWindowPlacement](https://learn.microsoft.com/windows/win32/api/winuser/nf-winuser-setwindowplacement)
and handle serialization and persistence themselves. These new APIs provide a
higher-level, WinRT-friendly way to accomplish window placement persistence,
including built-in registry-backed storage keyed by a developer-specified
identifier.

# Conceptual pages (How To)

_(This is conceptual documentation that will go to docs.microsoft.com "how to" page)_

## Save and restore window placement across sessions

You can use the AppWindow placement APIs to automatically save and restore your
application's window position, size, and state (minimized, maximized, normal)
across sessions.

### Setting up persisted placement

To enable automatic placement persistence, assign a `PersistedStateId` to your
AppWindow and set the desired `PlacementRestorationBehavior`:

```csharp
using Microsoft.UI.Windowing;

// In your window initialization
var appWindow = AppWindow.GetFromWindowId(myWindowId);

// Assign a unique identifier for this window's placement data
appWindow.PersistedStateId = "MainWindow";

// Enable automatic restoration on launch
appWindow.PlacementRestorationBehavior = PlacementRestorationBehavior.Automatic;
```

When `PlacementRestorationBehavior` is set to `Automatic` and a
`PersistedStateId` is assigned, the system will automatically restore the
window to its last saved position and state when the application is launched.

### Manually saving and restoring placement

You can also manually control when placement is saved and restored:

```csharp
using Microsoft.UI.Windowing;

// Save the current placement
appWindow.PersistedStateId = "MainWindow";
appWindow.SaveCurrentPlacement();

// Retrieve current placement details
AppWindowPlacementDetails details = appWindow.GetCurrentPlacement();

// Restore placement with specific parameters
appWindow.SetCurrentPlacement(placementInfo);
```

### Saving placement for all windows

If your application manages multiple windows, each with its own
`PersistedStateId`, you can save all of their placements at once:

```csharp
AppWindow.SaveCurrentPlacementForAllPersistedStateIds();
```

This is useful when handling application shutdown, to persist the state of all
tracked windows in a single call.

### Getting display metrics for a window

The `DisplayArea.GetMetricsFromWindowId` method retrieves display metrics for
the monitor that a given window is on:

```csharp
using Microsoft.UI.Windowing;

var metrics = DisplayArea.GetMetricsFromWindowId(myWindowId);
```

# API Pages

## AppWindow.PersistedStateId property

Gets or sets a string identifier used as the key for persisting window placement
data in the Windows registry.

You must set this property before calling `SaveCurrentPlacement()` or enabling
`PlacementRestorationBehavior`. The identifier should be unique per window
within your application.

```csharp
appWindow.PersistedStateId = "MainWindow";
```

**Remarks**: Placement data is stored in the Windows registry, keyed by this
identifier. If you change the identifier, previously saved placement data under
the old key will no longer be associated with this window.

## AppWindow.PlacementRestorationBehavior property

Gets or sets the behavior for automatic window placement restoration.

When set to `Automatic`, the system restores the window to its previously saved
position and state on launch, provided a `PersistedStateId` has been set.

```csharp
appWindow.PlacementRestorationBehavior = PlacementRestorationBehavior.Automatic;
```

**Remarks**: This property is only meaningful when `PersistedStateId` is set.
If no persisted state exists for the given identifier, the window uses its
default placement.

## AppWindow.GetCurrentPlacement method

Retrieves the current placement details of the window, including its position,
size, and window state.

```csharp
AppWindowPlacementDetails details = appWindow.GetCurrentPlacement();
```

This is a WinRT wrapper around the Win32
[GetWindowPlacement](https://learn.microsoft.com/windows/win32/api/winuser/nf-winuser-getwindowplacement)
function, with DPI awareness handled automatically via
[GetDpiForWindow](https://learn.microsoft.com/windows/win32/api/winuser/nf-winuser-getdpiforwindow).

## AppWindow.SetCurrentPlacement method

Sets the window's placement using the provided placement information.

```csharp
appWindow.SetCurrentPlacement(placementInfo);
```

This is a WinRT wrapper around the Win32
[SetWindowPlacement](https://learn.microsoft.com/windows/win32/api/winuser/nf-winuser-setwindowplacement)
function.

## AppWindow.SaveCurrentPlacement method

Saves the current window placement to the registry under the key specified by
`PersistedStateId`.

```csharp
appWindow.PersistedStateId = "MainWindow";
appWindow.SaveCurrentPlacement();
```

**Remarks**: `PersistedStateId` must be set before calling this method.

## AppWindow.SaveCurrentPlacementForAllPersistedStateIds static method

Saves the current placement of all AppWindow instances that have a
`PersistedStateId` assigned.

```csharp
AppWindow.SaveCurrentPlacementForAllPersistedStateIds();
```

This is useful during application shutdown to batch-save all window states.

## DisplayArea.GetMetricsFromWindowId static method

Returns display metrics for the monitor associated with the specified window.

```csharp
var metrics = DisplayArea.GetMetricsFromWindowId(myWindowId);
```

## PlacementRestorationBehavior enum

Specifies how a window's placement should be restored.

| Member | Description |
|-|-|
| None | No automatic restoration. Placement must be managed manually. |
| Automatic | The system automatically restores placement from persisted state on launch. |

## AppWindowPlacementDetails class

Contains detailed information about a window's current placement, including
position, size, and window state (normal, minimized, maximized).

Returned by `AppWindow.GetCurrentPlacement()`.

## PlacementInfo class

Contains placement parameters that can be applied to a window via
`AppWindow.SetCurrentPlacement()`.

# API Details

```c# (but really MIDL3)
namespace Microsoft.UI.Windowing
{
    enum PlacementRestorationBehavior
    {
        None = 0,
        Automatic = 1,
    };

    runtimeclass AppWindowPlacementDetails
    {
        // Contains position, size, display area, and window state details
    };

    runtimeclass PlacementInfo
    {
        // Contains placement parameters for SetCurrentPlacement
    };

    runtimeclass AppWindow
    {
        // New members for placement support
        String PersistedStateId;
        PlacementRestorationBehavior PlacementRestorationBehavior;

        AppWindowPlacementDetails GetCurrentPlacement();
        void SetCurrentPlacement(PlacementInfo placementInfo);
        void SaveCurrentPlacement();

        static void SaveCurrentPlacementForAllPersistedStateIds();
    }

    runtimeclass DisplayArea
    {
        // New member for display metrics
        static DisplayAreaMetrics GetMetricsFromWindowId(
            Microsoft.UI.WindowId windowId);
    }
}
```

# Appendix

These APIs are wrappers around Win32 window placement functions
(`GetWindowPlacement`, `SetWindowPlacement`) with additional features:

- **DPI awareness**: Automatically handles DPI via `GetDpiForWindow`.
- **Registry persistence**: Placement data is serialized and stored in the
  Windows registry, keyed by `PersistedStateId`.
- **Multi-monitor support**: Works with `DisplayArea` to handle placement
  across multiple monitors.

The APIs were introduced as experimental in Windows App SDK 2.0 Experimental 1.
