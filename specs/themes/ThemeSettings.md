ThemeSettings 
===

# Background
_This section is only for internal use, it should not be part of the public documentation._

In UWP, apps can use the
[AccessibilitySettings](https://learn.microsoft.com/en-us/uwp/api/windows.ui.viewmanagement.accessibilitysettings?view=winrt-22621)
API to query the system's high-contrast setting, and detect when it changes.  But in a Win32/non-UWP context, the
**AccessibilitySettings.HighContrastChanged** event never fires.

The API described in this doc, **ThemeSettings**, is a WinAppSDK WinRT API that provides functionality of **AccessibilitySettings**, but for a Win32
environment.  We expect to add other APIs to this type over time.

**AccessibilitySettings** uses the **CoreWindow** on the thread to notify it that the system theme has changed, by
subscribing to an internal **ThemeChanged** event on the **CoreWindow**. The **CoreWindow** fires this event in resposne to a
**WM_THEMECHANGED** window message.

This GIF shows how a user can change the HighContrast theme in the Settings app today, and a System Xaml app that displays the current **HighContrastScheme**:

![Choosing high contast themes in the settings app](HighContrastThemes.gif)

This API requires a **WindowId** object because the implementation listens for a `WM_THEMECHANGED` event.  An alternative option is for the API
to create and manage its own top-level window, but we decided to use an existing window so we could have better control over the order in which
these kinds of WinAppSDK events are fired.

# API Pages

## ThemeSettings class
The **ThemeSettings** API allows Win32 WinRT apps to detect that the system's High Contrast setting
has changed.  

In this sample code, an app uses a **ThemeSettings** object to listen for high contrast changes
on the system:

```c++
void MyApp::ListenForHighContrastChange(XamlRoot& xamlRoot) 
{
  const auto myWindowId = xamlRoot.ContentEnvironment().AppWindowId();
  m_themeSettings = ThemeSettings::CreateForWindowId(myWindowId);

  m_themeSettings.Changed([xamlRoot](const ThemeSettings& ts, const auto&) {
    if (ts.HighContrast())
    {
      ::OutputDebugString(L"High contrast is ON, scheme is: ");
      ::OutputDebugString(ts.HighContrastScheme().c_str());
    }
    else
    {
      ::OutputDebugString(L"High contrast is OFF.\n");
    }
  });
}
```

When the app releases all its references to a **ThemeSettings** object, the object will be destroyed and the **Changed** event will
no longer fire.

### Methods
|Name|Description|
|-|-|
|static CreateForWindowId(WindowId)|Creates a ThemeSettings object that will provide theme information for the given WindowId.|

### Events
|Name|Description|
|-|-|
|Changed|Fired when one of the object's properties has changed.|

### Properties
| Name | Description |
|-|-|
| Boolean HighContrast | True if High Contrast mode is enabled on the system. |
| String HighContrastScheme | If HighContrast is true, a string from the system representing the High Contrast scheme, or style. |

## ThemeSettings.CreateForWindowId static method

``` c#
static CreateForWindowId(WindowId windowId)
```

Creates a **ThemeSettings** object that will provide theme information for the given **WindowId**.

The given **WindowId** must represent a window that:
* is a top-level window,
* AND is on the same process and thread as the caller.

For example, you can get a **WindowId** from the **ContentEnvironment.AppWindowId** property.  You can get a **ContentEnvironment**
object from a **XamlRoot** object.

## ThemeSettings.Changed event

```c#
event TypedEventHandler<ThemeSettings, Object> Changed
```

Fired when one of the object's properties has changed.

The **Changed** event will only fire while the **ThemeSettings** object is alive, so apps must ensure
they hold a reference to the object as long as they want to receive the event.

The **Changed** event will only fire as long as the window represented by **WindowId** is alive (has not yet received `WM_NCDESTROY`).

# API Details

``` c# (really midl3)
namespace Microsoft.UI.System
{
  runtimeclass ThemeSettings 
  {
    static ThemeSettings CreateForWindowId(WindowId windowId);

    event TypedEventHandler<ThemeSettings, Object> Changed;

    Boolean HighContrast { get; }
    String HighContrastScheme { get; } 
  }
}
```

# Appendix

## Open Issues and Implementation Issues
In the experimental API today, HighContrastScheme returns a stale value if HighContrast is off.  We should change this to return
the empty string.

It seems easy to misuse this API by accidentally allowing the ThemeSettings object to go out of scope, which will mean the event
never fires.

In the original plan we weren't going to add HighContrast or HighContrastScheme.  Do we need them?  Should we remove?

Note that today in the code the **Changed** object is called **HighContrastChanged** because it currently only applies to HighContrast.

## Future Directions
In the future, when we support cross-process and/or cross-thread islands, a WindowId won't be sufficient anymore.  We'll need
a static method that allows the app to create a ThemeSettings object for a given island.


## Similar APIs
Note in .net there is a
[SystemEvents](https://learn.microsoft.com/en-us/dotnet/api/microsoft.win32.systemevents?view=dotnet-plat-ext-7.0) type
that provides related APIs.  This is implemented by creating a top-level window to receive `WM_THEMECHANGED` and other
messages.  That implementation is
[here](https://github.com/microsoft/referencesource/blob/5697c29004a34d80acdaf5742d7e699022c64ecd/System/compmod/microsoft/win32/SystemEvents.cs).
