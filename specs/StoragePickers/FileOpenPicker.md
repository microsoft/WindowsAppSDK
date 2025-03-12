FileOpenPicker Class
===

# Background

Namespace: [Microsoft.Windows.Storage.Pickers](./Microsoft.Windows.Storage.Pickers.md)

Represents a UI element that lets the user choose and open files.

Supports specifying the initial location, extension filters, and text on commit button.

# API Pages

## Constructor

### Attributes

| **Attribute**            | **Type**           | **Description**                                                          |
|--------------------------|--------------------|--------------------------------------------------------------------------|
| `CommitButtonText`       | `string`           | Gets or sets the text displayed on the commit button of the file picker. |
| `FileTypeFilter`         | `IList<string>`    | Gets the collection of file types that the file picker displays.         |
| `SuggestedStartLocation` | [Microsoft.Windows.Storage.Pickers.PickerLocationId](./PickerLocationId.md)| Gets or sets the initial location where the file picker looks for files.  |
| `ViewMode`               | [Microsoft.Windows.Storage.Pickers.PickerViewMode](./PickerViewMode.md)    | Gets or sets the view mode that the file picker is using to present items.|

### Examples
C#

```C#
using Microsoft.Windows.Storage.Pickers;

var openPicker = new FileOpenPicker(this.AppWindow.Id)
{
    // (Optional) specify the initial location.
    //     If not specified, using PickerLocationId.Unspecified by default.
    SuggestedStartLocation = PickerLocationId.DocumentsLibrary,
    
    // (Optional) specify the text displayed on commit button. If not specified, use system default.
    CommitButtonText = "Choose selected files",

    // (Optional) specify file extensions filters. If not specified, default to all (*.*)
    FileTypeFilter = { ".txt", ".pdf", ".doc", ".docx" },
};
```

C++

```C++
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

FileOpenPicker openPicker(AppWindow().Id());

// (Optional) specify the initial location.
//     If not specified, using PickerLocationId.Unspecified by default.
openPicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);

// (Optional) specify the text displayed on commit button. If not specified, use system default.
openPicker.CommitButtonText(L"Choose selected files");

// (Optional) specify file extensions filters. If not specified, default to all (*.*)
openPicker.FileTypeFilter().Append(L".txt");
openPicker.FileTypeFilter().Append(L".pdf");
openPicker.FileTypeFilter().Append(L".doc");
openPicker.FileTypeFilter().Append(L".docx");
```

## FileOpenPicker.PickSingleFileAsync

Displays a UI element that allows user to choose and open one file.

Returns a light weight object that has the path of the picked file.

Return null if the file dialog was cancelled or closed without selection.

### Examples

C#

```C#
using Microsoft.Windows.Storage.Pickers;

var openPicker = new FileOpenPicker(this.AppWindow.Id);

var result = await openPicker.PickSingleFileAsync();
if (result is not null)
{
    var content = System.IO.File.ReadAllText(result.Path);
}
else
{
    // error handling.
}
```

C++
```C++
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
#include <fstream>
#include <string>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

FileOpenPicker openPicker(AppWindow().Id());
auto& result{ co_await openPicker.PickSingleFileAsync() };
if (result)
{
    std::ifstream fileReader(result.Path().c_str());
    std::string text((std::istreambuf_iterator<char>(fileReader)), std::istreambuf_iterator<char>());
    winrt::hstring hText = winrt::to_hstring(text);
}
else
{
    // error handling.
}
```

## FileOpenPicker.PickMultipleFilesAsync

Displays a UI element that allows user to choose and open multiple files.

Returns a collection of light weight objects that has the path of picked files.

Return an empty list (Count = 0) if the file dialog's cancelled or closed without selection.

### Examples

C#

```C#
using Microsoft.Windows.Storage.Pickers;

var openPicker = new FileOpenPicker(this.AppWindow.Id);

var results = await openPicker.PickMultipleFilesAsync();
if (results.Count > 0)
{
    var pickedFilePaths = results.Select(f => f.Path);
    foreach (var path in pickedFilePaths)
    {
        var content = System.IO.File.ReadAllText(path);
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
#include <fstream>
#include <string>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

FileOpenPicker openPicker(AppWindow().Id());
auto& results{ co_await openPicker.PickMultipleFilesAsync() };
if (results.Size() > 0)
{
    for (auto const& result : results)
    {
        std::ifstream fileReader(result.Path().c_str());
        std::string text((std::istreambuf_iterator<char>(fileReader)), std::istreambuf_iterator<char>());
        winrt::hstring hText = winrt::to_hstring(text);
    }
}
else
{
    // error handling.
}
```

# See Also

[PickFileResult](./PickFileResult.md)
