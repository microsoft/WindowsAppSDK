DisplayArea API update to facilitate easier use for developers working with DisplayIds
===

# Background
Up until WinAppSDK 1.1, the only easy mapping between a
[Microsoft.UI.DisplayId](https://docs.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/microsoft.ui.displayid?view=windows-app-sdk-1.1_)
and a
[Microsoft.UI.Windowing.DisplayArea](https://docs.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/microsoft.ui.windowing.displayarea?view=windows-app-sdk-1.1_)
was if the developer started with a DisplayArea and wanted to find the DisplayId it maps to. If a
developer wanted to find out what DisplayArea is configured for a given DisplayId they would have
to enumerate **all** DisplayAreas using the static method
[DisplayArea.FindAll()](https://docs.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/microsoft.ui.windowing.displayarea.findall?view=windows-app-sdk-1.1)
and then compare each DisplayArea returned with the DisplayId for the display they were interested in.

This feature is remedying that complexity by introducing another static method on the DisplayArea
class. `DisplayArea.GetFromDisplayId(DisplayId)` returns a DisplayArea that corresponds to the
specified DisplayId, if one exists. If more than one such DisplayArea exists, the system chooses
one to return. This choice will remain consistent until the next display topology change.

This matches the pattern we already have in place for the following apis:
1. DisplayArea given a WindowId -
 [DisplayArea.GetFromWindowId(WindowId, DisplayAreaFallBack)](https://docs.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/microsoft.ui.windowing.displayarea.getfromwindowid?view=windows-app-sdk-1.1)

2. AppWindow given a WindowId -
[AppWindow.GetFromWindowId(WindowId)](https://docs.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/microsoft.ui.windowing.appwindow.getfromwindowid?view=windows-app-sdk-1.1)

# API Pages

## DisplayArea.GetFromDisplayId static method

This is the new static method added to WinAppSdk 1.2.

The following example shows how an AppWindow could be configured to fully occupy the DisplayArea
associated with the passed hmonitor/displayId:

```csharp
using Microsoft.UI;
using Microsoft.UI.Windowing;
using Windows.Graphics;

void ExampleUsage_GetDisplayAreaForDisplay(AppWindow appWindow, IntPtr hmonitor)
{
    DisplayId displayId = Win32Interop.GetDisplayIdFromMonitor(hmonitor);
    DisplayArea displayArea = DisplayArea.GetFromDisplayId(displayId);

    if(displayArea != null)
    {
        RectInt32 rect = new RectInt32()
        {
            X = 0,
            Y = 0,
            Width = displayArea.WorkArea.Width,
            Height = displayArea.WorkArea.Height
        };
        appWindow.MoveAndResize(rect, displayArea);
    }
}
```

# API Details

```csharp
namespace Microsoft.UI.Windowing
{
    [contract(Microsoft.Foundation.WindowsAppSDKContract, 1)]
    runtimeclass DisplayArea
    {
        [contract(Microsoft.Foundation.WindowsAppSDKContract, 1.2)]
        {
            // Queries what DisplayArea is configured for the display identified by displayId.
            static DisplayArea GetFromDisplayId(Microsoft.UI.DisplayId displayId);
        }
    }
}
```