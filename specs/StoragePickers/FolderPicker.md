FolderPicker Class
===

# Background

Namespace: [Microsoft.Windows.Storage.Pickers](./Microsoft.Windows.Storage.Pickers.md)

Represents a UI element that lets the user choose a folder.

Supports specifying the initial location and text on commit button.

# API Pages

## Constructor

### Attributes

| **Attribute**              | **Type**           | **Description**   |
|----------------------------|--------------------|-------------------|
| `ViewMode`                 | [Microsoft::Windows::Storage::Pickers::PickerViewMode](./PickerViewMode.md)    | Gets or sets the view mode that the file picker is using to present items.         |
| `SuggestedStartLocation`   | [Microsoft::Windows::Storage::Pickers::PickerLocationId](./PickerLocationId.md)| Gets or sets the initial location where the file picker looks for files.           |
| `CommitButtonText`         | `winrt::hstring`                       | Gets or sets the text displayed on the commit button of the file picker.                                                   |

### Examples

C#

```csharp
using Microsoft.Windows.Storage.Pickers;

var folderPicker = new FolderPicker(this.AppWindow.Id)
{
    // (Optional) specify the initial location. If not specified, use system default:
    SuggestedStartLocation = PickerLocationId.DocumentsLibrary,

    // (Optional) specify the text displayed on commit button. If not specified, use system default:
    CommitButtonText = "Select Folder",
};
```

C++

```cpp
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

FolderPicker folderPicker(AppWindow().Id());

// (Optional) specify the initial location. If not specified, use system default:
folderPicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);

// (Optional) specify the text displayed on commit button. If not specified, use system default:
folderPicker.CommitButtonText(L"Select Folder");
```

## FolderPicker.PickSingleFolderAsync

Displays a UI element that allows the user to choose a folder.

### Definition
```cpp
winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFolder> PickSingleFolderAsync();
```
Return null if the file dialog was cancelled or closed without selection.

### Examples

C#

```csharp
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
```cpp
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

FolderPicker folderPicker(AppWindow().Id());
auto& folder = co_await folderPicker.PickSingleFolderAsync();
if (folder != nullptr)
{
    auto path = folder.Path();
}
else
{
    // error handling.
}
```
