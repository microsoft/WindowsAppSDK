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
    // (Optional) specify the initial location.
    //     If not specified, default to PickerLocationId.Unspecified.
    SuggestedStartLocation = PickerLocationId.DocumentsLibrary,
    
    // (Optional) specify the default file name. If not specified, use system default.
    SuggestedFileName = "My Document",

    // (Optional) specify the text displayed on commit button. 
    //     If not specified, the system uses a default label of "Open" (suitably translated).
    CommitButtonText = "Save Document",

    // (Optional) categorized extensions types. If not specified, allow All Files (*.*)
    //     Note that when allow All Files (*.*), end users can save a file without extension.
    FileTypeChoices = {
        { "Documents", new List<string> { ".txt", ".doc", ".docx" } }
    },

    // (Optional) specify the default file extension (will be appended after the default file name).
    //      If not specified, will not appended after the default extension.
    DefaultFileExtension = ".txt",
};
```

C++

```C++
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

FileSavePicker savePicker(AppWindow().Id());

// (Optional) specify the initial location.
//     If not specified, default to PickerLocationId.Unspecified.
savePicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);

// (Optional) specify the default file name. If not specified, use system default.
savePicker.SuggestedFileName(L"NewDocument");

// (Optional) specify the text displayed on commit button. 
//     If not specified, the system uses a default label of "Open" (suitably translated).
savePicker.CommitButtonText(L"Save Document");

// (Optional) categorized extensions types. If not specified, allow All Files (*.*)
//     Note that when allow All Files (*.*), end users can save a file without extension.
savePicker.FileTypeChoices().Insert(L"Text", winrt::single_threaded_vector<winrt::hstring>({ L".txt" }));

// (Optional) specify the default file extension (will be appended after the default file name).
//      If not specified, will not appended after the default extension.
savePicker.DefaultFileExtension(L".txt");
```

## Setting the FileSavePicker.SuggestedSaveFilePath Property

The `SuggestedSaveFilePath` property of `FileSavePicker` dictates 2 key aspects of the save file 
dialog's initial state:

*   **Initial Directory:** The dialog defaults to the directory of the `SuggestedSaveFilePath`. 

    This behavior overrides any picker-specific remembered folder settings and ensures the dialog 
    opens in the suggested file's parent folder.

*   **Pre-filled File Name:** The file name field in the dialog is pre-populated with the name of 
the `SuggestedSaveFilePath`. 

    This file name overrides the `FileSavePicker.SuggestedFileName` property if both are set.

### Examples
C#
```C#
using Microsoft.Windows.Storage.Pickers;

var savePicker = new FileSavePicker(this.AppWindow.Id);
savePicker.SuggestedSaveFilePath(@"C:\temp\MyProject\MyFile.txt");
```

C++
```C++
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

FileSavePicker savePicker(AppWindow().Id());
bool isSuccess = savePicker.SuggestedSaveFilePath(L"C:\\temp\\MyProject\\MyFile.txt");
```

### The Parsing Logic of Setting SuggestedSaveFilePath

`SuggestedSaveFilePath` takes whatever after **the last slash** to fill in the file name box, 
as long as the part before the last slash is a valid and existing folder. 

It allows the value to be set to an empty string. However, it raises invalid argument exception 
if the non-empty input doesn't contain have a folder path.

Here're some examples about the parsing logic:

|Input path string | Set folder | Set file name |
|------------------|------------|---------------|
|`'C:\temp\MyProject\MyFile.txt'`|`'C:\temp\MyProject'`| `'MyFile.txt'`|
|`'C:\temp\MyProject\.git\'`|`'C:\temp\MyProject\.git'`| `''`|
|`'C:\temp\MyProject\.git'`|`'C:\temp\MyProject'`| `'.git'`|
|`'C:\servers\www.bing.com\'`|`'C:\servers\www.bing.com'`| `''`|
|`'C:\servers\www.bing.com'`|`'C:\servers`| `'www.bing.com'`|

## FileSavePicker.PickSaveFileAsync

Displays a UI element that allows the user to configure the file path to save.

Returns a light weight object that has the path of the saved file.

Returns null if the file dialog was cancelled or closed without saved file.

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
