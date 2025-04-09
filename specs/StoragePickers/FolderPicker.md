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
    IVector<string> FileTypeFilter{ get; };

    PickerLocationId SuggestedStartLocation;
    PickerViewMode ViewMode;
    string SettingsIdentifier;

    Windows.Foundation.IAsyncOperation<PickFolderResult> PickSingleFolderAsync();
}
```

## Constructor

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

Returns a light weight object that has the path of the picked folder.

Returns null if the file dialog was cancelled or closed without selection.

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
auto& result{ co_await folderPicker.PickSingleFolderAsync() };
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
