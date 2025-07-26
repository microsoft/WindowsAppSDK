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

    PickerLocationId SuggestedStartLocation;
    PickerViewMode ViewMode;

    Windows.Foundation.IAsyncOperation<PickFolderResult> PickSingleFolderAsync();
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
    // (Optional) Specify the initial location for the picker. 
    //     If the specified location doesn't exist on the user's machine, it falls back to the DocumentsLibrary.
    //     If not set, it defaults to PickerLocationId.Unspecified, and the system will use its default location.
    SuggestedStartLocation = PickerLocationId.DocumentsLibrary,

    // (Optional) specify the text displayed on the commit button. 
    //     If not specified, the system uses a default label of "Open" (suitably translated).
    CommitButtonText = "Select Folder",

    // (Optional) specify the view mode of the picker dialog. If not specified, default to List.
    ViewMode = PickerViewMode.List,
};
```

C++

```C++
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

FolderPicker folderPicker(AppWindow().Id());

// (Optional) Specify the initial location for the picker. 
//     If the specified location doesn't exist on the user's machine, it falls back to the DocumentsLibrary.
//     If not set, it defaults to PickerLocationId.Unspecified, and the system will use its default location.
folderPicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);

// (Optional) specify the text displayed on the commit button. 
//     If not specified, the system uses a default label of "Open" (suitably translated).
folderPicker.CommitButtonText(L"Select Folder");

// (Optional) specify the view mode of the picker dialog. If not specified, default to List.
folderPicker.ViewMode(PickerViewMode::List);
```

## FolderPicker.PickSingleFolderAsync

Displays a UI element that allows the user to choose a folder.

Returns a lightweight object that has the path of the picked folder.

Returns `null` if the file dialog was cancelled or closed without a selection.

### Examples

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

# See Also

[PickFolderResult](./PickFolderResult.md)
