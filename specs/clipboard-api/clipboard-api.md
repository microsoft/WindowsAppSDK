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

When you use Windows' built-in user interface controls, you get their built-in support for copying and pasting data for free. However, when you use your own controls or controls from a third-party vendor, you might need to implement copying and pasting yourself. You can do this with the clipboard API in the Project Reunion SDK, 

T, described in the examples of this document, is very similar to those of Windows.ApplicationModel.DataTransfer, with only 2 differences. We'll call out these differences in the following examples. For the rest of the information, start here to refer to the existing documentation: https://docs.microsoft.com/windows/uwp/app-to-app/copy-and-paste

## Examples

### Get set up to access the clipboard

First, include the [**Windows.ApplicationModel.DataTransfer**](https://docs.microsoft.com/uwp/api/Windows.ApplicationModel.DataTransfer) namespace in your app. Then, add an instance of the [**DataPackage**](https://docs.microsoft.com/uwp/api/Windows.ApplicationModel.DataTransfer.DataPackage) object. This object contains both the data the user wants to copy and any properties (such as a description) that you want to include.

```csharp
DataPackage dataPackage = new DataPackage();
```

### Copy and cut

Copy and cut (also referred to as *move*) work almost exactly the same. Choose which operation you want by using the [**RequestedOperation**](https://docs.microsoft.com/uwp/api/windows.applicationmodel.datatransfer.datapackage.requestedoperation) property.

```csharp
// copy
dataPackage.RequestedOperation = DataPackageOperation.Copy;
// or cut
dataPackage.RequestedOperation = DataPackageOperation.Move;
```

### Set the copied content

Next, you can add the data that a user has selected to the [**DataPackage**](https://docs.microsoft.com/uwp/api/Windows.ApplicationModel.DataTransfer.DataPackage) object. If this data is supported by the **DataPackage** class, you can use one of the corresponding [methods](https://docs.microsoft.com/uwp/api/windows.applicationmodel.datatransfer.datapackage#methods) of the **DataPackage** object. Here's how to add text by using the [**SetText**](https://docs.microsoft.com/uwp/api/windows.applicationmodel.datatransfer.datapackage.settext) method:

```csharp
dataPackage.SetText("Hello World!");
```

The last step is to add the [**DataPackage**](https://docs.microsoft.com/uwp/api/Windows.ApplicationModel.DataTransfer.DataPackage) to the clipboard by calling the static [**SetContent**](https://docs.microsoft.com/uwp/api/windows.applicationmodel.datatransfer.clipboard.setcontent) method.

```csharp
Clipboard.SetContent(dataPackage);
```

### Paste

To get the contents of the clipboard, call the static [**GetContent**](https://docs.microsoft.com/uwp/api/windows.applicationmodel.datatransfer.clipboard.getcontent) method. This method returns a [**DataPackageView**](https://docs.microsoft.com/uwp/api/Windows.ApplicationModel.DataTransfer.DataPackageView) that contains the content. This object is almost identical to a [**DataPackage**](https://docs.microsoft.com/uwp/api/Windows.ApplicationModel.DataTransfer.DataPackage) object, except that its contents are read-only. With that object, you can use either the [**AvailableFormats**](https://docs.microsoft.com/uwp/api/windows.applicationmodel.datatransfer.datapackageview.availableformats) or the [**Contains**](https://docs.microsoft.com/uwp/api/windows.applicationmodel.datatransfer.datapackageview.contains) method to identify what formats are available. Then, you can call the corresponding [**DataPackageView**](https://docs.microsoft.com/uwp/api/Windows.ApplicationModel.DataTransfer.DataPackageView) method to get the data.

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

In addition to copy and paste commands, you may also want to track clipboard changes. Do this by handling the clipboard's [**ContentChanged**](https://docs.microsoft.com/uwp/api/windows.applicationmodel.datatransfer.clipboard.contentchanged) event.

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

<!-- TEMPLATE
    Explanation and guidance that doesn't fit into the Examples section.
    APIs should only throw exceptions in exceptional conditions; basically,
    only when there's a bug in the caller, such as argument exception.  But if for some
    reason it's necessary for a caller to catch an exception from an API, call that
    out with an explanation either here or in the Examples
-->

## API Notes

<!-- TEMPLATE
    Option 1: Give a one or two line description of each API (type and member),
        or at least the ones that aren't obvious from their name. These
        descriptions are what show up in IntelliSense. For properties, specify
        the default value of the property if it isn't the type's default (for
        example an int-typed property that doesn't default to zero.) 
        
    Option 2: Put these descriptions in the below API Details section,
        with a "///" comment above the member or type. 
-->

## API Details

<!-- TEMPLATE
    The exact API, in MIDL3 format (https://docs.microsoft.com/en-us/uwp/midl-3/)
    when possible, or in C# if starting with an API sketch.  GitHub's markdown
    syntax formatter does not (yet) know about MIDL3, so use ```c# instead even
    when writing MIDL3.
    Example:
    ```c# (but really MIDL3)
    namespace Microsoft.AppModel
    {
        /// Represents a package on the host system. See Windows.ApplicationModel.Package for more details
        runtimeclass Package
        {
            /// Returns the current package, or null if the current process is not packaged
            static Package Current { get; };
            /// Returns the package from the system store with this full name or null if not found
            static Package GetFromFullName(String fullName);
            /// Returns packages in the given family, by name
            static Package[] FindByFamilyName(String familyName);
        }
    }
    ```
-->

## Appendix

<!-- TEMPLATE
    Anything else that you want to write down for posterity, but
    that isn't necessary to understand the purpose and usage of the API.
    For example, implementation details.
    
-->
