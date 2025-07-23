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

    string SettingsIdentifier;
    string DefaultFileExtension;
    string SuggestedFileName;
    string SuggestedSaveFilePath{ get; };   // read-only attribute
    boolean TrySetSuggestedSaveFilePath(String filePath);

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
    //     If not specified, using PickerLocationId.Unspecified by default.
    SuggestedStartLocation = PickerLocationId.DocumentsLibrary,
    
    // (Optional) specify the default file name. If not specified, use system default.
    SuggestedFileName = "My Document",

    // (Optional) specify the text displayed on commit button. If not specified, use system default.
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
//     If not specified, using PickerLocationId.Unspecified by default
savePicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);

// (Optional) specify the default file name. If not specified, use system default.
savePicker.SuggestedFileName(L"NewDocument");

// (Optional) categorized extensions types. If not specified, allow All Files (*.*)
//     Note that when allow All Files (*.*), end users can save a file without extension.
savePicker.FileTypeChoices().Insert(L"Text", winrt::single_threaded_vector<winrt::hstring>({ L".txt" }));

// (Optional) specify the default file extension (will be appended after the default file name).
//      If not specified, will not appended after the default extension.
savePicker.DefaultFileExtension(L".txt");
```

## FileSavePicker.TrySetSuggestedSaveFilePath and SuggestedSaveFilePath

### TrySetSuggestedSaveFilePath

This method sets the `SuggestedSaveFilePath` property on the `FileSavePicker`, that dictates key aspects 
of the save file dialog's initial state:

*   **Initial Directory:** The dialog defaults to the directory of the `SuggestedSaveFilePath`. 

    This behavior overrides any picker-specific remembered folder settings and ensures the dialog 
    opens in the suggested file's parent folder.

*   **Pre-filled File Name:** The file name field in the dialog is pre-populated with the name of 
the `SuggestedSaveFilePath`. 

    This file name overrides the `FileSavePicker.SuggestedFileName` property if both are set.

### Read-only SuggestedSaveFilePath

`FileSavePicker.SuggestedSaveFilePath` is a read-only attribute, meaning it can only be set via 
above method `FileSavePicker.TrySetSuggestedSaveFilePath`.

### Examples
C#
```C#
using Microsoft.Windows.Storage.Pickers;

var savePicker = new FileSavePicker(this.AppWindow.Id);
var isSuccess = savePicker.TrySetSuggestedSaveFilePath(@"C:\temp\MyProject\MyFile.txt");
if (!isSuccess)
{
    // Handling
}
```

C++
```C++
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

FileSavePicker savePicker(AppWindow().Id());
bool isSuccess = savePicker.TrySetSuggestedSaveFilePath(L"C:\\temp\\MyProject\\MyFile.txt");
if (!isSuccess)
{
    // Handling
}
```

### The Parsing Logic of TrySuggestedSaveFilePath

Method `TrySuggestedSaveFilePath` takes whatever after **the last slash** to fill in the file name 
box, as long as the part before the last slash is a valid and existing folder. 

And return `false` without writing any value if the input doesn't even contain a slash, 
or the folder doesn't exist on the end user's environment.

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
auto& result{ co_await savePicker.PickSaveFileAsync() };
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
