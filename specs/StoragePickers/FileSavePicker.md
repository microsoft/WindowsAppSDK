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
    Windows.Storage.StorageFile SuggestedSaveFile;
    IMap<string, IVector<string>> FileTypeChoices{ get; };

    PickerLocationId SuggestedStartLocation;

    Windows.Foundation.IAsyncOperation<PickFileResult> PickSaveFileAsync()
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

    // (Optional) categorized extensions types. If not specified, use system default: All Files (*.*)
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
//     If not specified, using PickerLocationId.Unspecified by defaultl
savePicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);

// (Optional) specify the default file name. If not specified, use system default.
savePicker.SuggestedFileName(L"NewDocument");

// (Optional) categorized extensions types. If not specified, use system default: All Files (*.*)
savePicker.FileTypeChoices().Insert(L"Text", winrt::single_threaded_vector<winrt::hstring>({ L".txt" }));

// (Optional) specify the default file extension (will be appended after the default file name).
//      If not specified, will not appended after the default extension.
savePicker.DefaultFileExtension(L".txt");
```

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

[PickFileResult](./PickFileResult.md)
