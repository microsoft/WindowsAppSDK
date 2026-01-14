FileOpenPicker Class
===

# Background

Namespace: [Microsoft.Windows.Storage.Pickers](./Microsoft.Windows.Storage.Pickers.md)

Represents a UI element that lets the user choose and open files.

Supports specifying the initial location, extension filters, and text on commit button.

# API Pages

## Definition

```idl
runtimeclass FileOpenPicker
{
    FileOpenPicker(Microsoft.UI.WindowId windowId);

    string CommitButtonText;
    string Title;
    string SettingsIdentifier;

    IMap<String, IVector<String>> FileTypeChoices{ get; };
    IVector<string> FileTypeFilter{ get; };
    Int32 InitialFileTypeIndex;

    string SuggestedFolder;
    String SuggestedStartFolder;
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
    // (Optional) Sets the folder that the file dialog always tries to display when it opens.
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
    
    // (Optional) specify the text displayed on the commit button. 
    //     If not specified, the system uses a default label of "Open" (suitably translated).
    CommitButtonText = "Choose selected files",

    // (Optional) specify the title of the picker.
    //     If not specified, the system uses a default title.
    Title = "Open File",

    // (Optional) allows customization of the settings name, to distinguish picker instances.
    //     Without the SettingsIdentifier specified, pickers in one app share the state together.
    //     Only specify this when a picker needs to track its own state (e.g. size, location, etc).
    SettingsIdentifier = "BookContents",

    // (Optional) group file types into labeled choices
    //     FileTypeChoices takes precedence over FileTypeFilter when both defined.
    FileTypeChoices = {
        { "Documents", new List<string> { ".txt", ".doc", ".docx" } },
        { "Pictures", new List<string> { ".png", ".jpg", ".jpeg", ".bmp" } }
    },

    // (Optional) specify which file type to be automatically selected on dialog launch.
    //     The index is 0-based. 
    //     When not specified, its value is -1 and the dialog follows default behavior.
    InitialFileTypeIndex = 1,  // auto select Pictures

    // (Optional) specify the view mode of the picker dialog. If not specified, defaults to List.
    ViewMode = PickerViewMode.List,
};
```

C++

```C++
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

FileOpenPicker openPicker(AppWindow().Id());

// (Optional) Sets the folder that the file dialog always tries to display when it opens.
//     SuggestedFolder will not be overriden by the last picked folder.
//     If not specified, or the specified path doesn't exist, defaults to the last folder the user picked.
//     On first launch of the picker, SuggestedFolder takes precedence over the SuggestedStartFolder if both set.
openPicker.SuggestedFolder(L"C:\\MyFiles");

// (Optional) Sets an initial folder path shown when the picker is first launched.
//     Once the user has picked from a directory, SuggestedStartFolder will be silently ignored.
//     Takes precedence over SuggestedStartLocation when both defined.
//     If this folder is not found, falls back to SuggestedStartLocation.
openPicker.SuggestedStartFolder(L"C:\\MyFiles");

// (Optional) Specify the initial location for the picker. 
//     If the specified location doesn't exist on the user's machine, it falls back to the DocumentsLibrary.
//     If not set, it defaults to PickerLocationId.Unspecified, and the system will use its default location.
openPicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);

// (Optional) specify the text displayed on the commit button. 
//     If not specified, the system uses a default label of "Open" (suitably translated).
openPicker.CommitButtonText(L"Choose selected files");

// (Optional) specify the title of the picker.
//     If not specified, the system uses a default title.
openPicker.Title(L"Open File");

// (Optional) allows customization of the settings name, to distinguish picker instances.
//     Without the SettingsIdentifier specified, pickers in one app share the state together.
//     Only specify this when a picker needs to track its own state (e.g. size, location, etc).
openPicker.SettingsIdentifier(L"BookContents");

// (Optional) group file types into labeled choices
//     FileTypeChoices takes precedence over FileTypeFilter when both defined.
auto choices = openPicker.FileTypeChoices();
choices.Insert(L"Documents", winrt::single_threaded_vector<winrt::hstring>({ L".txt", L".doc", L".docx" }));
choices.Insert(L"Pictures", winrt::single_threaded_vector<winrt::hstring>({ L".png", L".jpg", L".jpeg", L".bmp" }));

// (Optional) specify which file type to be automatically selected on dialog launch.
//     The index is 0-based. 
//     When not specified, its value is -1 and the dialog follows default behavior.
openPicker.InitialFileTypeIndex(1);  // auto select Pictures

// (Optional) specify the view mode of the picker dialog. If not specified, defaults to List.
openPicker.ViewMode(PickerViewMode::List);
```

## New Properties

### FileOpenPicker.Title

Allow customizing the title of file dialog. It's based on the 
[IFileDialog::SetTitle method](https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nf-shobjidl_core-ifiledialog-settitle)

### FileOpenPicker.SettingsIdentifier

The SettingsIdentifier property allows the picker object to remember its own states.

See the examples in [Note 2: The use case and implementation of SettingsIdentifier (Microsoft.Windows.Storage.Pickers.md)](./Microsoft.Windows.Storage.Pickers.md#note-2-the-use-case-and-implementation-of-settingsidentifier)

### FileOpenPicker.InitialFileTypeIndex

The InitialFileTypeIndex is a 0-based value deciding the auto-selected file type on dialog launch. 

See the examples in [Note 3: Properties for File Types and The Initial Index (Microsoft.Windows.Storage.Pickers.md)](./Microsoft.Windows.Storage.Pickers.md#note-3-properties-for-file-types-and-its-auto-selection-on-launch)

## Methods

### FileOpenPicker.PickSingleFileAsync

Displays a UI element that allows the user to choose and open one file.

Returns a lightweight object that has the path of the picked file.

Returns `null` if the file dialog was cancelled or closed without a selection.

**Examples**

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

### FileOpenPicker.PickMultipleFilesAsync

Displays a UI element that allows the user to choose and open multiple files.

Returns a collection of lightweight objects that have the path of the picked files.

Returns an empty list (`Count` = 0) if the file dialog was cancelled or closed without a selection.

**Examples**

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
