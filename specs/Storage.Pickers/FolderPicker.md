FolderPicker Class
===

# Background

Namespace: [Microsoft.Windows.Storage.Pickers](./Microsoft.Windows.Storage.Pickers.md)

Represents a UI element that lets the user choose a folder.

Supports specifying the initial location and text on commit button.

# API Pages

## Definition

```C#
runtimeclass FolderPicker
{
    FolderPicker(Microsoft.UI.WindowId windowId);

    string CommitButtonText;
    string Title;
    string SettingsIdentifier;

    string SuggestedFolder;
    String SuggestedStartFolder;
    PickerLocationId SuggestedStartLocation;

    PickerViewMode ViewMode;

    Windows.Foundation.IAsyncOperation<PickFolderResult> PickSingleFolderAsync();
    Windows.Foundation.IAsyncOperation<IVectorView<PickFolderResult>> PickMultipleFoldersAsync();
}
```

*Spec note:*
*`FolderPicker.FileTypeFilter` has been removed as it was not functionally appropriate for folder 
selection*

## Constructor

### Examples

C#

```C#
using Microsoft.Windows.Storage.Pickers;

var folderPicker = new FolderPicker(this.AppWindow.Id)
{
    // (Optional) Sets the folder that the folder dialog always tries to display when it opens.
    //     SuggestedFolder will not be overriden by the last picked folder.
    //     If not specified, or the specified path doesn't exist, defaults to the last folder the user picked.
    //     On first launch of the picker, SuggestedFolder takes precedence over the SuggestedStartFolder if both set.
    SuggestedFolder = @"C:\MyFiles",

    // (Optional) Sets an initial folder path shown when the picker is first launched.
    //     Once the user has picked from a directory, SuggestedStartFolder will be silently ignored.
    //     Takes precedence over SuggestedStartLocation when both defined.
    //     If this folder is not found, falls back to SuggestedStartLocation.
    SuggestedStartFolder = @"C:\MyFiles",

    // (Optional) Specify the initial location for the picker. 
    //     If the specified location doesn't exist on the user's machine, it falls back to the DocumentsLibrary.
    //     If not set, it defaults to PickerLocationId.Unspecified, and the system will use its default location.
    SuggestedStartLocation = PickerLocationId.DocumentsLibrary,

    // (Optional) specify the text displayed on the commit button. 
    //     If not specified, the system uses a default label of "Open" (suitably translated).
    CommitButtonText = "Select Folder",

    // (Optional) specify the title of the picker.
    //     If not specified, the system uses a default title.
    Title = "Select Folder",

    // (Optional) Allows customization of the settings name, to distinguish picker instances.
    //     Pickers in one app share state by default. Use this property only when you need
    //     multiple distinct picker states within the same app.
    //     See: https://learn.microsoft.com/en-us/uwp/api/windows.storage.pickers.folderpicker.settingsidentifier
    SettingsIdentifier = "BookContents",

    // (Optional) specify the view mode of the picker dialog. If not specified, default to List.
    ViewMode = PickerViewMode.List,
};
```

C++

```C++
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

FolderPicker folderPicker(AppWindow().Id());

// (Optional) Sets the folder that the folder dialog always tries to display when it opens.
//     SuggestedFolder will not be overriden by the last picked folder.
//     If not specified, or the specified path doesn't exist, defaults to the last folder the user picked.
//     On first launch of the picker, SuggestedFolder takes precedence over the SuggestedStartFolder if both set.
folderPicker.SuggestedFolder(L"C:\\MyFiles");

// (Optional) Sets an initial folder path shown when the picker is first launched.
//     Once the user has picked from a directory, SuggestedStartFolder will be silently ignored.
//     Takes precedence over SuggestedStartLocation when both defined.
//     If this folder is not found, falls back to SuggestedStartLocation.
folderPicker.SuggestedStartFolder(L"C:\\MyFiles");

// (Optional) Specify the initial location for the picker. 
//     If the specified location doesn't exist on the user's machine, it falls back to the DocumentsLibrary.
//     If not set, it defaults to PickerLocationId.Unspecified, and the system will use its default location.
folderPicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);

// (Optional) specify the text displayed on the commit button. 
//     If not specified, the system uses a default label of "Open" (suitably translated).
folderPicker.CommitButtonText(L"Select Folder");

// (Optional) specify the title of the picker.
//     If not specified, the system uses a default title.
folderPicker.Title(L"Select Folder");

// (Optional) Allows customization of the settings name, to distinguish picker instances.
//     Pickers in one app share state by default. Use this property only when you need
//     multiple distinct picker states within the same app.
//     See: https://learn.microsoft.com/en-us/uwp/api/windows.storage.pickers.folderpicker.settingsidentifier
folderPicker.SettingsIdentifier(L"BookContents");

// (Optional) specify the view mode of the picker dialog. If not specified, default to List.
folderPicker.ViewMode(PickerViewMode::List);
```

## New Properties

### FolderPicker.Title

Allow customizing the title of file dialog. It's based on the 
[IFileDialog::SetTitle method](https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nf-shobjidl_core-ifiledialog-settitle)

### FolderPicker.SettingsIdentifier

The SettingsIdentifier property allows the picker object to remember its own states.

See the examples in [Note 2: The use case and implementation of SettingsIdentifier (Microsoft.Windows.Storage.Pickers.md)](./Microsoft.Windows.Storage.Pickers.md#note-2-the-use-case-and-implementation-of-settingsidentifier)

## Methods

### FolderPicker.PickSingleFolderAsync

Displays a UI element that allows the user to choose a folder.

Returns a lightweight object that has the path of the picked folder.

Returns `null` if the file dialog was cancelled or closed without a selection.

**Examples**

C#

```C#
using Microsoft.Windows.Storage.Pickers;

var folderPicker = new FolderPicker(this.AppWindow.Id);
var result = await folderPicker.PickSingleFolderAsync();
if (result is not null)
{
    var path = result.Path;
}
else
{
    // error handling.
}
```

C++
```C++
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

FolderPicker folderPicker(AppWindow().Id());
auto result{ co_await folderPicker.PickSingleFolderAsync() };
if (result)
{
    auto path{ result.Path() };
}
else
{
    // error handling.
}
```

### FolderPicker.PickMultipleFoldersAsync

Displays a UI element that allows the user to choose multiple folders.

Returns a collection of lightweight objects that have the path of the picked folders.

Returns an empty list (`Count` = 0) if the folder dialog was cancelled or closed without a selection.

**Examples**

C#

```C#
using Microsoft.Windows.Storage.Pickers;

var folderPicker = new FolderPicker(this.AppWindow.Id);

var results = await folderPicker.PickMultipleFoldersAsync();
if (results.Count > 0)
{
    var pickedFolderPaths = results.Select(f => f.Path);
    foreach (var path in pickedFolderPaths)
    {
        // Do something with the folder path
    }
}
else
{
    // error handling.
}
```

C++
```C++
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

FolderPicker folderPicker(AppWindow().Id());
auto results{ co_await folderPicker.PickMultipleFoldersAsync() };
if (results.Size() > 0)
{
    for (auto const& result : results)
    {
        auto path{ result.Path() };
    }
}
else
{
    // error handling.
}
```

# See Also

[PickFolderResult](./PickFolderResult.md)

Notes:

- SuggestedStartFolder takes precedence over SuggestedStartLocation.
