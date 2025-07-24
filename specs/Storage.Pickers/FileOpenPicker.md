FileOpenPicker Class
===

# Background

Namespace: [Microsoft.Windows.Storage.Pickers](./Microsoft.Windows.Storage.Pickers.md)

Represents a UI element that lets the user choose and open files.

Supports specifying the initial location, extension filters, and text on commit button.

# API Pages

## Definition

```C#
runtimeclass FileOpenPicker
{
    FileOpenPicker(Microsoft.UI.WindowId windowId);

    string CommitButtonText;
    IVector<string> FileTypeFilter{ get; };
    PickerLocationId SuggestedStartLocation;
    PickerViewMode ViewMode;

    Windows.Foundation.IAsyncOperation<PickFileResult> PickSingleFileAsync();
    Windows.Foundation.IAsyncOperation<IVectorView<PickFileResult>> PickMultipleFilesAsync();
}
```

## Constructor

### Examples
C#

```C#
using Microsoft.Windows.Storage.Pickers;

var openPicker = new FileOpenPicker(this.AppWindow.Id)
{
    // (Optional) specify the initial location.
    //     If not specified, default to PickerLocationId.Unspecified.
    SuggestedStartLocation = PickerLocationId.DocumentsLibrary,
    
    // (Optional) specify the text displayed on commit button. 
    //     If not specified, the system uses a default label of "Open" (suitably translated).
    CommitButtonText = "Choose selected files",

    // (Optional) specify file extensions filters. If not specified, default to all (*.*)
    FileTypeFilter = { ".txt", ".pdf", ".doc", ".docx" },

    // (Optional) specify the view mode of the picker dialog. If not specified, default to List.
    ViewMode = PickerViewMode.List,
};
```

C++

```C++
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

FileOpenPicker openPicker(AppWindow().Id());

// (Optional) specify the initial location.
//     If not specified, default to PickerLocationId.Unspecified.
openPicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);

// (Optional) specify the text displayed on commit button. 
//     If not specified, the system uses a default label of "Open" (suitably translated).
openPicker.CommitButtonText(L"Choose selected files");

// (Optional) specify file extensions filters. If not specified, default to all (*.*)
openPicker.FileTypeFilter().ReplaceAll({ L".txt", L".pdf", L".doc", L".docx" });

// (Optional) specify the view mode of the picker dialog. If not specified, default to List.
picker.ViewMode(PickerViewMode::List);
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
auto result{ co_await openPicker.PickSingleFileAsync() };
if (result)
{
    std::ifstream fileReader(result.Path().c_str());
    std::string text(std::istreambuf_iterator(fileReader), {});
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
auto results{ co_await openPicker.PickMultipleFilesAsync() };
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
