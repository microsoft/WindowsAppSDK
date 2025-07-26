FileSavePicker Class
===

# Background

Namespace: [Microsoft.Windows.Storage.Pickers](./Microsoft.Windows.Storage.Pickers.md)

Represents a UI element that lets the user choose a file to save.

# API Pages

## Definition

```C#
runtimeclass FileSavePicker
{
    FileSavePicker(Microsoft.UI.WindowId windowId);

    string CommitButtonText;
    string DefaultFileExtension;
    string SuggestedFileName;
    string SuggestedSaveFilePath;

    IMap<string, IVector<string>> FileTypeChoices{ get; };

    PickerLocationId SuggestedStartLocation;

    Windows.Foundation.IAsyncOperation<PickFileResult> PickSaveFileAsync();
}
```

## Constructor

### Examples
C#

```C#
using Microsoft.Windows.Storage.Pickers;

var savePicker = new FileSavePicker(this.AppWindow.Id)
{
    // (Optional) Specify the initial location for the picker. 
    //     If the specified location doesn't exist on the user's machine, it falls back to the DocumentsLibrary.
    //     If not set, it defaults to PickerLocationId.Unspecified, and the system will use its default location.
    SuggestedStartLocation = PickerLocationId.DocumentsLibrary,
    
    // (Optional) specify the default file name. If not specified, use system default.
    SuggestedFileName = "My Document",

    // (Optional) specify the text displayed on the commit button. 
    //     If not specified, the system uses a default label of "Save" (suitably translated).
    CommitButtonText = "Save Document",

    // (Optional) categorized extension types. If not specified, "All Files (*.*)" is allowed.
    //     Note that when "All Files (*.*)" is allowed, end users can save a file without an extension.
    FileTypeChoices = {
        { "Documents", new List<string> { ".txt", ".doc", ".docx" } }
    },

    // (Optional) specify the default file extension (will be appended to SuggestedFileName).
    //      If not specified, no extension will be appended.
    DefaultFileExtension = ".txt",
};
```

C++

```C++
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

FileSavePicker savePicker(AppWindow().Id());

// (Optional) Specify the initial location for the picker. 
//     If the specified location doesn't exist on the user's machine, it falls back to the DocumentsLibrary.
//     If not set, it defaults to PickerLocationId.Unspecified, and the system will use its default location.
savePicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);

// (Optional) specify the default file name. If not specified, use system default.
savePicker.SuggestedFileName(L"NewDocument");

// (Optional) specify the text displayed on the commit button. 
//     If not specified, the system uses a default label of "Save" (suitably translated).
savePicker.CommitButtonText(L"Save Document");

// (Optional) categorized extension types. If not specified, "All Files (*.*)" is allowed.
//     Note that when "All Files (*.*)" is allowed, end users can save a file without an extension.
savePicker.FileTypeChoices().Insert(L"Text", winrt::single_threaded_vector<winrt::hstring>({ L".txt" }));

// (Optional) specify the default file extension (will be appended to SuggestedFileName).
//      If not specified, no extension will be appended.
savePicker.DefaultFileExtension(L".txt");
```

## Setting the FileSavePicker.SuggestedSaveFilePath Property

The `SuggestedSaveFilePath` property of `FileSavePicker` dictates two key aspects of the save file 
dialog's initial state:

*   **Initial Directory:** The dialog defaults to the directory of the `SuggestedSaveFilePath`. 

    This behavior overrides any picker-specific remembered folder settings and ensures the dialog 
    opens in the suggested file's parent folder.

*   **Pre-filled File Name:** The file name field in the dialog is pre-populated with the name from 
the `SuggestedSaveFilePath`. 

    This file name overrides the `FileSavePicker.SuggestedFileName` property if both are set.

### Examples
C#
```C#
using Microsoft.Windows.Storage.Pickers;

var savePicker = new FileSavePicker(this.AppWindow.Id);
savePicker.SuggestedSaveFilePath = @"C:\temp\MyProject\MyFile.txt";
```

C++
```C++
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

FileSavePicker savePicker(AppWindow().Id());
savePicker.SuggestedSaveFilePath(L"C:\\temp\\MyProject\\MyFile.txt");
```

### The Parsing Logic

The `SuggestedSaveFilePath` property is parsed to set the directory and file name in the 
save dialog.

- The substring before the final path separator (`\`) is used as the initial directory. 
This part must be written in the format of a folder path.
- The substring after the final path separator is used as the suggested file name.
- If `SuggestedSaveFilePath` is set to an empty string, the property is cleared and will not take 
effect when launching the save dialog.
- If the provided path is a non-empty string but it does not have a folder path 
(e.g., `"MyFile.txt"`), an `InvalidArgumentException` will be thrown.

The following table illustrates the parsing behavior:

| `SuggestedSaveFilePath` Input | Resulting Initial Directory | Resulting File Name |
|-------------------------------|-----------------------------|---------------------|
| `'C:\temp\MyProject\MyFile.txt'` | `'C:\temp\MyProject'` | `'MyFile.txt'` |
| `'C:\temp\MyProject\.git\'` | `'C:\temp\MyProject\.git'` | `''` (empty) |
| `'C:\temp\MyProject\.git'` | `'C:\temp\MyProject'` | `'.git'` |
| `'C:\servers\www.bing.com\'` | `'C:\servers\www.bing.com'` | `''` (empty) |
| `'C:\servers\www.bing.com'` | `'C:\servers'` | `'www.bing.com'` |
| `''` (empty string) | null |
| `'MyFile.txt'` | Throws `InvalidArgumentException` | Throws `InvalidArgumentException` |


## FileSavePicker.PickSaveFileAsync

Displays a UI element that allows the user to configure the file path to save.

Returns a lightweight object that has the path of the saved file.

Returns `null` if the file dialog was cancelled or closed without saving a file.

### Examples

C#

```C#
using Microsoft.Windows.Storage.Pickers;

var savePicker = new FileSavePicker(this.AppWindow.Id);
var result = await savePicker.PickSaveFileAsync();
if (result is not null)
{
    System.IO.File.WriteAllText(result.Path, "Hello world.");
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

FileSavePicker savePicker(AppWindow().Id());
auto result{ co_await savePicker.PickSaveFileAsync() };
if (result)
{
    std::ofstream outFile(result.Path().c_str());
    outFile << "Hello world.";
    outFile.close();
}
else
{
    // error handling.
}
```

# See Also

* [PickFileResult](./PickFileResult.md)
