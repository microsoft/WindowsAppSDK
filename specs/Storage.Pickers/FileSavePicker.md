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
    string Title;
    string SettingsIdentifier;

    string DefaultFileExtension;
    string SuggestedFileName;

    IMap<string, IVector<string>> FileTypeChoices{ get; };
    Int32 DefaultFileTypeFilterIndex;

    Boolean ShowOverwritePrompt;
    Boolean CreateNewFileIfNotExists;

    string SuggestedFolder;
    String SuggestedStartFolder;
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
    // (Optional) Sets the folder that the file save dialog always tries to display when it opens.
    //     SuggestedFolder will not be overriden by the last picked folder.
    //     If not specified, or the specified path doesn't exist, defaults to the last folder the user picked.
    //     On first launch of the picker, SuggestedFolder takes precedence over the SuggestedStartFolder if both set.
    SuggestedFolder = @"C:\MyFiles",

    // (Optional) Sets an initial folder path shown when the picker is first launched.
    //     Once the user has picked from a directory, SuggestedStartFolder will be silently ignored.
    //     Takes precedence over SuggestedStartLocation when both defined.
    //     If this folder is not found, falls back to SuggestedStartLocation.
    SuggestedStartFolder = @"C:\MyFiles",

    // (Optional) Specify the initial location for the picker. 
    //     If the specified location doesn't exist on the user's machine, it falls back to the DocumentsLibrary.
    //     If not set, it defaults to PickerLocationId.Unspecified, and the system will use its default location.
    SuggestedStartLocation = PickerLocationId.DocumentsLibrary,
    
    // (Optional) specify the default file name. If not specified, use system default.
    SuggestedFileName = "My Document",

    // (Optional) specify the text displayed on the commit button. 
    //     If not specified, the system uses a default label of "Save" (suitably translated).
    CommitButtonText = "Save Document",

    // (Optional) specify the title of the picker.
    //     If not specified, the system uses a default title.
    Title = "Save File",

    // (Optional) specify the settings identifier of the picker.
    //     It allows the picker to remember its state (e.g. size, location, etc) across sessions.
    SettingsIdentifier = "MySettingsIdentifier",

    // (Optional) categorized extension types. If not specified, "All Files (*.*)" is allowed.
    //     Note that when "All Files (*.*)" is allowed, end users can save a file without an extension.
    FileTypeChoices = {
        { "Text", new List<string> {".txt"} },
        { "Documents", new List<string> { ".doc", ".docx" } }
    },

    // (Optional) specify the index of the file type filter to be selected by default.
    //     The index is 0-based. 
    //     When not specified, its value is -1.
    DefaultFileTypeFilterIndex = 1,  // this will auto-select Documents

    // (Optional) Show a warning prompt of file overwrite when user tries to pick an existing file.
    //      set to true by default.
    ShowOverwritePrompt = true,

    // (Optional) create an empty file when the picked file does not yet exist.
    //      set to true by default.
    CreateNewFileIfNotExists = true,

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

// (Optional) Sets the folder that the file save dialog always tries to display when it opens.
//     SuggestedFolder will not be overriden by the last picked folder.
//     If not specified, or the specified path doesn't exist, defaults to the last folder the user picked.
//     On first launch of the picker, SuggestedFolder takes precedence over the SuggestedStartFolder if both set.
savePicker.SuggestedFolder(L"C:\\MyFiles");

// (Optional) Sets an initial folder path shown when the picker is first launched.
//     Once the user has picked from a directory, SuggestedStartFolder will be silently ignored.
//     Takes precedence over SuggestedStartLocation when both defined.
//     If this folder is not found, falls back to SuggestedStartLocation.
savePicker.SuggestedStartFolder(L"C:\\MyFiles");

// (Optional) Specify the initial location for the picker. 
//     If the specified location doesn't exist on the user's machine, it falls back to the DocumentsLibrary.
//     If not set, it defaults to PickerLocationId.Unspecified, and the system will use its default location.
savePicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);

// (Optional) specify the default file name. If not specified, use system default.
savePicker.SuggestedFileName(L"NewDocument");

// (Optional) specify the text displayed on the commit button. 
//     If not specified, the system uses a default label of "Save" (suitably translated).
savePicker.CommitButtonText(L"Save Document");

// (Optional) specify the title of the picker.
//     If not specified, the system uses a default title.
savePicker.Title(L"Save File");

// (Optional) specify the settings identifier of the picker.
//     It allows the picker to remember its state (e.g. size, location, etc) across sessions.
savePicker.SettingsIdentifier(L"MySettingsIdentifier");

// (Optional) categorized extension types. If not specified, "All Files (*.*)" is allowed.
//     Note that when "All Files (*.*)" is allowed, end users can save a file without an extension.
savePicker.FileTypeChoices().Insert(L"Texts", winrt::single_threaded_vector<winrt::hstring>({ L".txt" }));
savePicker.FileTypeChoices().Insert(L"Documents", winrt::single_threaded_vector<winrt::hstring>({ L".doc", L".docx" }));

// (Optional) specify the index of the file type filter to be selected by default.
//     The index is 0-based. 
//     When not specified, its value is -1.
savePicker.DefaultFileTypeFilterIndex(1);    // this will auto-select Documents

// (Optional) Show a warning prompt of file overwrite when user tries to pick an existing file.
//      set to true by default.
savePicker.ShowOverwritePrompt(true);

// (Optional) create an empty file when the picked file does not yet exist.
//      set to true by default.
savePicker.CreateNewFileIfNotExists(true);

// (Optional) specify the default file extension (will be appended to SuggestedFileName).
//      If not specified, no extension will be appended.
savePicker.DefaultFileExtension(L".txt");
```

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
