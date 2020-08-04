# Background

## Current Windows drag & drop API surface

Drag & drop is a feature that allows the user to "drag" data - text, images, files, hyperlinks, etc. from one point on the screen to another. This could be within the same or between different applications.

Today, the Windows platform provides two primary APIs to enable this functionality:

* [The OLE drag & drop API](https://docs.microsoft.com/en-us/windows/win32/api/ole2/nf-ole2-dodragdrop) ("OLE drag & drop) usually called by all classic Win32 apps.
* [The UWP drag & drop API](https://docs.microsoft.com/en-us/uwp/api/windows.applicationmodel.datatransfer.dragdrop.core?view=winrt-19041) ("UWP drag & drop") callable (today) by Window-based UWP apps.

A common way developers implement drag & drop functionality in their apps is via their app's UI framework which provides wrappers for the platform drag & drop APIs. For example, XAML/WinUI or WPF:

* XAML/WinUI - Wrapper around UWP drag & drop. [Blog post](https://docs.microsoft.com/en-us/archive/msdn-magazine/2015/august/windows-10-modern-drag-and-drop-for-windows-universal-applications). [Samples](https://github.com/microsoft/Windows-universal-samples/tree/master/Samples/XamlDragAndDrop).
* WPF - Wrapper around OLE drag & drop. [Documentation](https://docs.microsoft.com/en-us/dotnet/framework/wpf/advanced/drag-and-drop-overview).

NOTE: It is important to note that use of a UI framework is _not_ necessary to implement drag & drop functionality in an app. An app can implement drag & drop by directly calling either the OLE or UWP platform API.

## Motivation for Project Reunion drag & drop

1. **Bring modern drag & drop to all classic apps in an easy-to-incorporate package:** Foremost among the issues we want to address is that the existing drag & drop APIs can be cumbersome to use; especially the older OLE API, and its wrappers such as WPF. In addition, the OLE API has limited support for drag UI customization - showing, hiding, or changing the glyph of the object being dragged; adding a caption, or other visual aids to help the user understand the effect of a drag operation, etc. Modern drag & drop provides these customizations. With this Project Reunion API, we plan to bring access to the modern drag & drop experience for _all_ apps.

2. **Evolve the API to make it easier-to-use in general:** Drag & drop as a feature is something that is intuitive for users, and satisfying to use. Especially in a touch-first world, we believe there is a lot of value in empowering developers to make this feature easy-to-implement to build apps that delight customers. This Project Reunion API aims to do so by wrapping away even more of the decision-making, and so making it easier for developers.

3. **Incorporate feedback from the developer community:** Additionally, this will allow us to iterate on improvements/fixes a lot faster than shipping with the Windows SDK as well as incorporate suggestions from our developer community.

<!-- break out into two points 

Problems in gap between UWP and Win32.

1. Customer promise that touch drag & drop works (preferably) out of the box.
TODO: how much functionality exists for routing touch drag & drop on Desktop

-->

# Description

 Drag & drop is an intuitive feature that make for delightful app experiences for end users. When you use Windows' UI frameworks such as XAML/WinUI, you get their built-in support for drag & drop with minimal overhead. However, if you are not using those, implementing drag & drop can be challenging. This Project Reunion SDK API aims to alleviate that challenge by providing a feature-rich drag & drop experience in an easy-to-use set of APIs.

The Reunion SDK drag & drop API is very similar to Windows' built-in "UWP drag & drop" API in the `Windows.ApplicationModel.DataTransfer.DragDrop.` Windows Runtime namespace. In fact, in this initial version (as of mid-2020), the Reunion SDK drag & drop API is almost the same as `Windows.ApplicationModel.DataTransfer.DragDrop.`, except for these differences:

1. The namespace is now `Microsoft.ProjectReunion.ApplicationModel.DragDrop`.
2. `DragDropManager::GetForCurrentView()` has been renamed to `GetForCurrentWindow()` and has changes in its implementation to allow its construction from a UWP appmodel application that uses Window/AppWindow, as well as from a classic Win32 app that uses `USER32.dll` windows aka HWNDs.

# Examples

## Enabling your application's window to be a drop target

Let's say you are building the next greatest photo organizer app. To add photos to the library, you want to enable users to drag in files, for example from File Explorer to your app. To do this, you need to set your application's HWND/Window/AppWindow to be a drop target.

1. Construct `DragDropManager`:

This does a lot of initialization and basically informs the system that your app wants to register for drag & drop. Note that `DragDropManager` is *per window*.

```c#
var manager = DragDropManager.GetForCurrentWindow();
```

1. Implement `IDropOperationTarget`:

```c#
class DropTarget : IDropOperationTarget
{
    public IAsyncOperation<DataPackageOperation> EnterAsync(DragInfo dragInfo, DragUIOverride dragUIOverride)
    {
        // your code here
    }

    public IAsyncOperation<DataPackageOperation> OverAsync(DragInfo dragInfo, DragUIOverride dragUIOverride)
    {
        // your code here
    }

    public IAsyncAction LeaveAsync(DragInfo dragInfo)
    {
        // your code here
    }

    public IAsyncOperation<DataPackageOperation> DropAsync(DragInfo dragInfo)
    {
        // your code here
    }
}
```

3. Provide your new drop target to the `DragDropManager`:

```c#
var onDropTargetRequestedHandler = new TypedEventHandler<DragDropManager, DropOperationTargetRequestedEventArgs>(
    delegate (DragDropManager handlerManager, DropOperationTargetRequestedEventArgs handlerArgs)
    {
        handlerArgs.DropTarget = new DropTarget();
    }
);
manager.TargetRequested += onDropTargetRequestedHandler;
```

## Enabling your application to be a drag source (start drag & drop operations)

```c#
DragOperation dragOperation = new DragOperation();

// Set your data on the DataPackage provided in the DragOperation
DataPackage dataPackage = dragOperation.Data;
dataPackage.SetText("Hello from another app!");

// Set default operation
dataPackage.RequestedOperation = DataPackageOperation.Copy;

// Set allowed operations
dragOperation.AllowedOperations = DataPackageOperation.Copy | DataPackageOperation.Move;

DataPackageOperation result = await dragOperation.StartAsync();
```

# Remarks

Coming soon.

# API Notes

* `DragDropManager`: Initializes drag & drop environment to enable an application window to be set as a drop target.
  * `GetForCurrentWindow`: Static method that constructs a `DragDropManager` which allows you to set the window as a drop target.
  * `TargetRequested`: Construct a `DropOperationTargetRequestedEventArgs` to provide a `IDropOperationTarget` implementation for your window.
  * ...
* `DragInfo`
  * ...
* `DragOperation`: Object used to create and start a drag operation from your app.
  * `AllowedOperations`: Use this property to set the complete set of operations the source app wishes to allow in drag and drop scenarios. You can specify zero or more flags. To set a desired default operation, use the `DataPackage.RequestedOperation` property. Users can override this choices by using SHIFT and CTRL keys. In this case, the target app must inspect the key state to determine the operation the user selected.
  * ...
* `DragUIContentMode`: Use this to specify whether the `DragOperation` should wait for content load before starting, or run in parallel.
* `DragUIOverride`
  * ...
* `DropOperationTargetRequestedEventArgs`
  * `SetTarget`: Provide your implementation of `IDropOperationTarget` which specifies the actions your app should take when the user is hovering over your application's window.
* `IDropOperationTarget`
  * `DropAsync`
  * `EnterAsync`
  * `LeaveAsync`
  * `OverAsync`

# API Details

See [`dragdrop.idl`](dragdrop.idl) for a complete [MIDL 3.0](
https://docs.microsoft.com/uwp/midl-3/) description
of the Project Reunion SDK's drag & drop API.

# Appendix

Coming soon.
