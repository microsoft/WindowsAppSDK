FolderPicker Class
===

# Background

Namespace: [Microsoft.Windows.Storage.Pickers](./Microsoft.Windows.Storage.Pickers.md)

Represents a UI element that lets the user choose a folder.

Supports specifying the initial location and text on commit button.

# API Pages

## Constructor

### Attributes

| **Attribute**           | **Type**           | **Description**   |
|-------------------------|--------------------|-------------------|
| `FileTypeFilter`        | `IList<string>`    | Avoid using this attribute! The folder picker only displays folders, so this attribute has no effect. It is retained for backward compatibility.  |
| `ViewMode`              | [Microsoft.Windows.Storage.Pickers.PickerViewMode](./PickerViewMode.md)    | Gets or sets the view mode that the file picker is using to present items.         |
| `SuggestedStartLocation`| [Microsoft.Windows.Storage.Pickers.PickerLocationId](./PickerLocationId.md)| Gets or sets the initial location where the file picker looks for files.           |
| `CommitButtonText`      | `string`                       | Gets or sets the text displayed on the commit button of the file picker.                                                   |

### Examples

C#

```C#
using Microsoft.Windows.Storage.Pickers;

var folderPicker = new FolderPicker(this.AppWindow.Id)
{
    // (Optional) specify the initial location.
    //     If not specified, using PickerLocationId.Unspecified by default.
    SuggestedStartLocation = PickerLocationId.DocumentsLibrary,

    // (Optional) specify the text displayed on commit button. If not specified, use system default.
    CommitButtonText = "Select Folder",
};
```

C++

```C++
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

FolderPicker folderPicker(AppWindow().Id());

// (Optional) specify the initial location.
//     If not specified, using PickerLocationId.Unspecified by default.
folderPicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);

// (Optional) specify the text displayed on commit button. If not specified, use system default.
folderPicker.CommitButtonText(L"Select Folder");
```

## FolderPicker.PickSingleFolderAsync

Displays a UI element that allows the user to choose a folder.

Returns the picked folder.

Returns null if the file dialog was cancelled or closed without selection.

### Examples

C#

```C#
using Microsoft.Windows.Storage.Pickers;

var folderPicker = new FolderPicker(this.AppWindow.Id);
var folder = await folderPicker.PickSingleFolderAsync();
if (folder is not null)
{
    var path = folder.Path;
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
auto& folder{ co_await folderPicker.PickSingleFolderAsync() };
if (folder)
{
    auto path{ folder.Path() };
}
else
{
    // error handling.
}
```
