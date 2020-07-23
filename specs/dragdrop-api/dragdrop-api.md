# Background

## Current Windows drag & drop API surface

Drag & drop is a feature that allows the user to "drag" data - text, images, files, hyperlinks, etc. from one point on the screen to another. This could be within the same or between different applications.

Today, Windows platform provides two primary APIs to enable this functionality:

* [The OLE drag & drop API](https://docs.microsoft.com/en-us/windows/win32/api/ole2/nf-ole2-dodragdrop) ("OLE drag & drop) usually called by all classic Win32 apps.
* [The UWP drag & drop API](https://docs.microsoft.com/en-us/uwp/api/windows.applicationmodel.datatransfer.dragdrop.core?view=winrt-19041) ("UWP drag & drop") callable (today) by CoreWindow-based UWP apps.

A common way developers implement drag & drop functionality in their apps is via the UI framework which provides wrappers for the platform drag & drop APIs in the UI elements. For example, XAML/WinUI or WPF:

* XAML/WinUI - Wrapper around UWP drag & drop. [Blog post](https://docs.microsoft.com/en-us/archive/msdn-magazine/2015/august/windows-10-modern-drag-and-drop-for-windows-universal-applications). [Samples](https://github.com/microsoft/Windows-universal-samples/tree/master/Samples/XamlDragAndDrop).
* WPF - Wrapper around OLE drag & drop. [Documentation](https://docs.microsoft.com/en-us/dotnet/framework/wpf/advanced/drag-and-drop-overview).

NOTE: It is important to note that use of a UI framework is _not_ necessary to implement drag & drop functionality in an app. An app can implement drag & drop by directly calling one of the two OLE or UWP APIs.

## Motivation for Project Reunion drag & drop

1. **Bring modern drag & drop to all classic apps in an easy-to-incorporate package:** Foremost among the issues we want to address is that the existing drag & drop APIs can be cumbersome to use; especially the older OLE API, and its wrappers such as WPF. In addition, the OLE API is lacking in modern, illustrative UI. With this Project Reunion API, we plan to bring the ability to access modern drag & drop for _all_ apps.

2. **Evolve the API to make it easier-to-use in general, and incorporate feedback from the community:** Drag & drop as a feature is something that is intuitive for users, and satisfying to use. Especially in a touch-first world, we belive there is a lot of value in empowering developers to make this feature easy-to-implement to build apps that delight customers. Additionally, this will allow us to iterate on improvements/fixes a lot faster than shipping with the Windows SDK.

# Description

 Drag & drop is an intuitive feature that make for delightful app experiences for end users. When you use Windows' UI frameworks such as XAML/WinUI, you get their built-in support for drag & drop with minimal overhead. However, if you are not using those, implementing drag & drop can be challenging. This Project Reunion SDK API aims to alleviate that challenge by providing a feature-rich drag & drop experience in an easy-to-use set of APIs.

The Reunion SDK drag & drop API is very similar to Windows' built-in "UWP drag & drop" API in the `Windows.ApplicationModel.DataTransfer.DragDrop.Core` Windows Runtime namespace. In fact, in this initial version (as of mid-2020), the Reunion SDK drag & drop API is almost the same as `Windows.ApplicationModel.DataTransfer.DragDrop.Core`, except for these differences:

1. The namespace is now `Microsoft.Reunion.DragDrop`.
2. The addition of `GetForHWND()` API to register any Windows app as a drop target.

# Examples

## Enabling your application's window to be a drop target

Let's say you are building the next greatest photo organizer app. To add photos to the library, you want to enable users to drag in files, for example from File Explorer to your app. To do this, you need to set your application's HWND/CoreWindow/AppWindow to be a drop target.

1. Get `CoreDragDropManager`:

This does a lot of initialization and basically informs the system that your app wants to register for drag & drop. Note that `CoreDragDropManager` is *per window*.

1a. If you have **classic HWND-based** application:

```c#
// C#
HWND hwnd; // HWND you got from CreateWindow or CreateWindowEx
var manager = CoreDragDropManager.GetForWindow(hwnd);
```
```c++
// C++/WinRT

HWND hwnd; // HWND you got from CreateWindow or CreateWindowEx
CoreDragDropManager manager{ CoreDragDropManager::GetForWindow(hwnd) };
```

1b. If you have a **CoreWindow/AppWindow-based** application:

```c#
// C#

var manager = CoreDragDropManager.GetForCurrentView();
```
```c++
// C++/WinRT

CoreDragDropManager manager{ CoreDragDropManager::GetForCurrentView() };
```

2. Implement `ICoreDropOperationTarget`:

```c#
// C#

class DropTarget : ICoreDropOperationTarget
{
    public IAsyncOperation<DataPackageOperation> EnterAsync(CoreDragInfo dragInfo, CoreDragUIOverride dragUIOverride)
    {
        throw new NotImplementedException();
    }

    public IAsyncOperation<DataPackageOperation> OverAsync(CoreDragInfo dragInfo, CoreDragUIOverride dragUIOverride)
    {
        throw new NotImplementedException();
    }

    public IAsyncAction LeaveAsync(CoreDragInfo dragInfo)
    {
        throw new NotImplementedException();
    }

    public IAsyncOperation<DataPackageOperation> DropAsync(CoreDragInfo dragInfo)
    {
        throw new NotImplementedException();
    }
}
```

3. Provide your new drop target to the `CoreDragDropManager`:

```c#
// C#

var onDropTargetRequestedHandler = new TypedEventHandler<CoreDragDropManager, CoreDropOperationTargetRequestedEventArgs>(
    delegate (CoreDragDropManager handlerManager, CoreDropOperationTargetRequestedEventArgs handlerArgs)
    {
        handlerArgs.SetTarget(new DropTarget());
    }
);
manager.TargetRequested += onDropTargetRequestedHandler;
```

## Enabling your application to be a drag source (start drag & drop operations)

```c#
// C#

CoreDragOperation dragOperation = new CoreDragOperation();

// Set your data on the DataPackage on the CoreDragOperation
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

* `CoreDragDropManager`: Initializes drag & drop environment to enable an application window to be set as a drop target.
  * `GetForCurrentView`: Static method that constructs a `CoreDragDropManager` for a CoreWindow/AppWindow app.
  * `GetForHWND`: Static method that constructs a `CoreDragDropManager` for a classic HWND-based windowing app.
  * `TargetRequested`: Construct a `CoreDropOperationTargetRequestedEventArgs` to provide a `ICoreDropOperationTarget` implementation for your window.
  * ...
* `CoreDragInfo`
  * ...
* `CoreDragOperation`: Object used to create and start a drag operation from your app.
  * `AllowedOperations`: Use this property to set the complete set of operations the source app wishes to allow in drag and drop scenarios. You can specify zero or more flags. To set a desired default operation, use the `DataPackage.RequestedOperation` property. Users can override this choices by using SHIFT and CTRL keys. In this case, the target app must inspect the key state to determine the operation the user selected.
  * ...
* `CoreDragUIContentMode`: Use this to specify whether the `CoreDragOperation` should wait for content load before starting, or run in parallel.
* `CoreDragUIOverride`
  * ...
* `CoreDropOperationTargetRequestedEventArgs`
  * `SetTarget`: Provide your implementation of `ICoreDropOperationTarget` which specifies the actions your app should take when the user is hovering over your application's window.
* `ICoreDropOperationTarget`
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
