# Decoupled API for Windows clipboard in Project Reunion SDK

## Background

The Windows clipboard is the component that's responsible for implementing
the "cut", "copy", and "paste" system for moving and copying data from one
Windows application to another. Windows maintains one clipboard per
interactively signed-in user (more precisely, one clipboard per Remote Desktop/
Terminal Services session), which can hold any number of data "formats"
which are all intended to represent the same data value.

This specification defines the API for the Windows clipboard within the
Project Reunion SDK. This Windows Runtime API is a [converged API interface](
  ../../docs/README.md#converged-apis) in the Project Reunion SDK,
which is intended to replace the following 3 clipboard APIs within Windows:

* [The classic clipboard API](https://docs.microsoft.com/windows/win32/dataxchg/clipboard),
  including GetClipboardData() and friends in windows.h.

* [The OLE data transfer API](https://docs.microsoft.com/windows/win32/com/data-transfer),
  including OleGetClipboard() and friends in ole2.h.

* [Windows.ApplicationModel.DataTransfer.Clipboard](https://docs.microsoft.com/windows/uwp/app-to-app/copy-and-paste)
  and friends.

Although this API will be based closely on Windows.ApplicationModel.DataTransfer,
its implementation will be delivered as an open-source part of the
Project Reunion SDK decoupled from Windows. It will _not_ be added to Windows
as part of the [Reunion Subset API Family](../../docs/README.md#subset-api-family).

### Motivation: reasons to create a new clipboard API

The first version of this spec creates a new clipboard API but does not
make any changes that add substantial value. However, creating a new
clipboard API in the Reunion SDK will let us make future improvements
to the clipboard developer and user experiences, like these:

* **Improve clipboard reliability by removing traps in the clipboard APIs:**
  People encounter a lot of problems with unexpected clipboard behavior that
  they blame Windows for and that Windows could theoretically solve, even
  though the problems are typically caused by applications misusing the
  clipboard. The new clipboard API makes breaking changes from the previous
  APIs that solve some of these problems:

  * _No clipboard lock_: Often, attempts to cut or copy data are seemingly
    ignored - the previous data value on the clipboard gets pasted instead,
    if there was one. This can happen when the previous source app uses the
    classic clipboard API, since apps using that API obtain a lock on the
    clipboard with OpenClipboard() that they must manually release with
    CloseClipboard(). The new clipboard API in the Reunion SDK will solve
    this problem by omitting the clipboard lock as a caller-visible concept.

  * _No need to flush clipboard_: Sometimes, a cut or copied data value is lost and the clipboard is cleared when the source app exits or crashes. This is likely to happen for clipboard source apps that use the OLE data transfer API or Windows.ApplicationModel.DataTransfer, since those APIs require an explicit "flush clipboard" call to make data set on clipboard persist after the source app exits. The Reunion SDK's new clipboard API will solve this problem by omitting this requirement as a caller-visible concept.

  The new clipboard API could make more breaking changes to fix other
  design errors and discourage other error-prone usage patterns
  after a deprecation period.

* **Bring new clipboard features to all versions of Windows that support
  Project Reunion:**
  Since the Windows clipboard has historically been considered an integrated
  Windows component, improvements to the clipboard have only been for the
  latest Windows version. However, with the Reunion SDK, we have the
  opportunity to implement these improvements in the SDK and let all
  apps that use it benefit, and even (in some cases) apps that don't
  build against the Reunion SDK at all.
  These features could include:

  * _Paste as plain text_: We've seen several suggestions from
    Windows users to let you paste a formatted text fragment with all the
    formatting stripped out. Many applications let you do this, but some
    don't, especially when the app from which the formatted text was cut
    or copied only provides the formatted version to the clipboard APIs.
    We could implement a "to plain text" feature to automatically create
    plain text from formatted HTML or RTF text when needed on either cut/copy
    or paste, then update the edit controls in Microsoft.UI.Xaml
    to use the Reunion clipboard API and therefore take advantage of
    this feature.

  * _Clipboard history:_ Windows 10 version 1809 (October/November 2018 update)
    introduced a new built-in clipboard history manager. Using the same "main
    package" as the [Project Reunion brokering system](
    ../../docs/README.md#brokering), we could install a Windows process
    to host the shared memory for the clipboard history, allowing us
    to bring the APIs and user interface
    for clipboard history to older Windows versions.
    (We could also consider using [PowerToys](
      https://github.com/microsoft/PowerToys) as the delivery vehicle
    for the clipboard history UI, while keeping the shared memory store
    and API implementations as part of the Reunion SDK.)
  
  * _Cloud clipboard sync and roaming:_ Windows 10 version 1809 also
    introduced cloud clipboard sync to other Windows devices you sign in to
    with the same personal Microsoft account or work or school Azure
    Active Directory account. We could also use the Reunion SDK main package
    to bring the sync client to older versions.
  
  * _Copy append/paste multiple_: We've also seen several suggestions from
    Windows users for a way to cut or copy multiple separate items,
    then paste them all at once in the same order that they were
    originally cut or copied. If we did implement this feature,
    we could put its memory store in the Reunion SDK main package
    to bring it to older Windows releases.

## Description

When you use Windows' built-in user interface controls, you get their
built-in support for copying and pasting data for free. However,
when you use your own controls or controls from a third-party vendor,
you might need to implement copying and pasting yourself.
You can do this with the clipboard API in the Project Reunion SDK.

The Reunion SDK clipboard API is very similar to Windows' built-in
clipboard API in the Windows.ApplicationModel.DataTransfer WinRT namespace.
In fact, in this initial version (as of mid-2020), the Reunion
SDK clipboard API is exactly the same as Windows.ApplicationModel.DataTransfer,
except for these differences:

1. The namespace is now Microsoft.ProjectReunion.ApplicationModel.DataTransfer.

1. Types in Windows.ApplicationModel.DataTransfer that are irrelevant
   to the clipboard are not included. For the exact set of types that are
   included, see the [API Details section](#api-details).

1. Your app will no longer ever need to call [Clipboard.Flush()](
  https://docs.microsoft.com/uwp/api/windows.applicationmodel.datatransfer.clipboard.flush)
  after setting the clipboard data on cut or copy. All formats for the
  clipboard data item set by your app will be available after your
  app exits normally or is automatically shut down by Windows,
  as if the app called Clipboard.Flush() before exiting.

## Examples

Because the Reunion SDK clipboard API is a near-copy of
Windows.ApplicationModel.DataTransfer, these examples are copied from the
guide to coding copy and paste in a Universal Windows Platform app using
Windows.ApplicationModel.DataTransfer:
https://docs.microsoft.com/windows/uwp/app-to-app/copy-and-paste

### Get set up to access the clipboard

First, include the **Microsoft.ProjectReunion.ApplicationModel.DataTransfer**
namespace in your app. Then, create an instance of the **DataPackage** class.
This object contains both the data the user wants to copy and any properties
(such as a description) that you want to include.

```csharp
DataPackage dataPackage = new DataPackage();
```

### Copy and cut

Copy and cut (also referred to as *move*) work almost exactly the same.
Choose which operation you want by using the **RequestedOperation** property
of **DataPackage**.

```csharp
// copy
dataPackage.RequestedOperation = DataPackageOperation.Copy;
// or cut
dataPackage.RequestedOperation = DataPackageOperation.Move;
```

### Set the copied content

Next, you can add the data value that a user has selected to the **DataPackage**
object. If all formats for this data value are supported by the **DataPackage**
class, you can use one of **DataPackage**'s corresponding methods.
Here's how to add text by using the **SetText** method:

```csharp
dataPackage.SetText("Hello World!");
```

The last step is to add the **DataPackage** to the clipboard by calling the
static **Clipboard.SetContent** method.

```csharp
Clipboard.SetContent(dataPackage);
```

### Paste

To get the data value currently on the clipboard, call the static
**Clipboard.GetContent** method. This method returns a **DataPackageView**
that contains the current clipboard data value. This object is almost
identical to a **DataPackage** object, except that its contents are read-only.
With a **DataPackageView** object, you can use either the **AvailableFormats**
property or the **Contains** method to identify what formats are available.
Then, you can call the corresponding **DataPackageView** method to get the
data in the format or formats your app needs.

```csharp
async void OutputClipboardText()
{
  DataPackageView dataPackageView = Clipboard.GetContent();
  if (dataPackageView.Contains(StandardDataFormats.Text))
  {
    string text = await dataPackageView.GetTextAsync();
    // To output the text from this example, you need a TextBlock control
    TextOutput.Text = "Clipboard now contains: " + text;
  }
}
```

### Track changes to the clipboard

In addition to copy and paste commands, you may also want to track clipboard
changes. Do this by handling the clipboard's **ContentChanged** event.

```csharp
Clipboard.ContentChanged += async (s, e) =>
{
  DataPackageView dataPackageView = Clipboard.GetContent();
  if (dataPackageView.Contains(StandardDataFormats.Text))
  {
    string text = await dataPackageView.GetTextAsync();
    // To output the text from this example, you need a TextBlock control
    TextOutput.Text = "Clipboard now contains: " + text;
  }
}
```

## Remarks

\[None at this time\]

## API Notes

\[To be added\]

## API Details

The syntactic interface of the Project Reunion SDK's clipboard API
is an exact subset of [Windows.ApplicationModel.DataTransfer](
https://docs.microsoft.com/uwp/api/windows.applicationmodel.datatransfer),
apart from a different name (Microsoft.ProjectReunion.ApplicationModel.DataTransfer).

The set of types from Windows.ApplicationModel.DataTransfer that
will be copied into the clipboard API is the following:

* `Clipboard` - Top level for the clipboard API. Provides "static" methods
  (methods implemented by the class's activation factory) to read and write
  the current clipboard item and clipboard history, along with methods
  to read settings for clipboard history and cloud clipboard sync.

* `Clipboard`-related types:
  * `ClipboardContentOptions`
  * `ClipboardHistoryItem`
  * `ClipboardHistoryItemsResult`
  * `ClipboardHistoryItemsResultStatus`
  * `ClipboardHistoryChangedEventArgs`
  * `OperationCompletedEventArgs`
  * `SetHistoryItemAsContentStatus`

* `DataPackage` - Unit of data transfer for the clipboard API.

* `DataPackage`-related types:
  * `DataPackageView`
  * `DataPackageOperation`
  * `DataPackagePropertySet`
  * `DataPackagePropertySetView`
  * `DataProviderDeferral`
  * `DataProviderHandler`
  * `DataProviderRequest`
  * `HtmlFormatHelper`
  * `StandardDataFormats`

\[To be expanded with IDL\]

## Appendix

Initially, the implementation of the Project Reunion SDK's clipboard APi
will be a set of very thin wrappers around the same-named codes in
Windows.ApplicationModel.DataTransfer.

The only exception will be the change to make Clipboard.Flush()
a completely optional operation.
(TO CONSIDER: Should Clipboard.Flush() be removed entirely?)
This will be implemented by Clipboard.SetContent(), which will register
callbacks that call the underlying Clipboard.Flush() in
Windows.ApplicationModel.DataTransfer when the application is about
to exit or be suspended:

* For apps that follow the [UWP app lifecycle](
  https://docs.microsoft.com/windows/uwp/launch-resume/app-lifecycle),
  a function that calls Clipboard.Flush() will be added as a handler for the
  [`CoreApplication.EnteredBackground`](
  https://docs.microsoft.com/uwp/api/windows.applicationmodel.core.coreapplication.enteredbackground)
  event if that event is available, and
  [`CoreApplication.Suspending`](
  https://docs.microsoft.com/uwp/api/windows.applicationmodel.core.coreapplication.suspending)
  otherwise.

* For other apps, a worker thread will initialize COM in STA
  and create a message-only user32.dll window, whose window procedure
  handles WM_DESTROY by calling Clipboard.Flush(). When the application
  exits normally, the window will receive WM_DESTROY.

