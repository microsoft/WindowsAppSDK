FileSavePicker Class
===

# Background

Namespace: [Microsoft.Windows.Storage.Pickers](./Microsoft.Windows.Storage.Pickers.md)

Represents a UI element that lets the user choose a file to save.

# API Pages

## Constructor

### Attributes

| **Attribute**              | **Type**           | **Description**   |
|----------------------------|--------------------|-------------------|
| `ViewMode`                 | [Microsoft::Windows::Storage::Pickers::PickerViewMode](./PickerViewMode.md)    | Gets or sets the view mode that the file picker is using to present items.         |
| `SuggestedStartLocation`   | [Microsoft::Windows::Storage::Pickers::PickerLocationId](./PickerLocationId.md)| Gets or sets the initial location where the file picker looks for files.           |
| `SuggestedFileName`        | `winrt::hstring`                       | Gets or sets the file name displayed in the file name input box on launching the dialog.                                   |
| `DefaultFileExtension`     | `winrt::hstring`                       | Gets or sets the file extension tailing the suggested file name in the file name input box on launching the dialog.        |
| `CommitButtonText`         | `winrt::hstring`                       | Gets or sets the text displayed on the commit button of the file picker.                                                   |
| `FileTypeChoices`          | `winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>>`    | The file extensions categorized by purpose.|


### Examples
C#

```csharp
using Microsoft.Windows.Storage.Pickers;

var savePicker = new FileSavePicker(this.AppWindow.Id)
{
    // (Optional) specify the initial location. If not specified, use system default:
    SuggestedStartLocation = PickerLocationId.DocumentsLibrary,
    
    // (Optional) specify the default file name. If not specified, use system default:
    SuggestedFileName = "My Document",

    // (Optional) specify the text displayed on commit button. If not specified, use system default:
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

```cpp
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

FileSavePicker savePicker(AppWindow().Id());

// (Optional) specify the initial location. If not specified, use system default:
savePicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);

// (Optional) specify the default file name. If not specified, use system default:
savePicker.SuggestedFileName(L"NewDocument");

// (Optional) categorized extensions types. If not specified, use system default: All Files (*.*)
savePicker.FileTypeChoices().Insert(L"Text", winrt::single_threaded_vector<winrt::hstring>({ L".txt" }));

// (Optional) specify the default file extension (will be appended after the default file name).
//      If not specified, will not appended after the default extension.
savePicker.DefaultFileExtension(L".txt");
```

## FileSavePicker.PickSaveFileAsync

Displays a UI element that allows the user to configure the file path to save.

### Definition
```cpp
winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> PickSaveFileAsync();
```
Return null if the file dialog was cancelled or closed without selection.

### Examples

C#

```csharp
using Microsoft.Windows.Storage.Pickers;

var savePicker = new FileSavePicker(this.AppWindow.Id);
var file = await savePicker.PickSaveFileAsync();
if (file is not null)
{
    System.IO.File.WriteAllText(file.Path, "Hello world.");
}
else
{
    // error handling.
}
```

C++

```cpp
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
#include <fstream>
#include <string>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

FileSavePicker savePicker(AppWindow().Id());
StorageFile file& = co_await savePicker.PickSaveFileAsync();
if (file != nullptr)
{
    std::ofstream outFile(file.Path().c_str());
    outFile << "Hello world.";
    outFile.close();
}
else
{
    // error handling.
}
```
