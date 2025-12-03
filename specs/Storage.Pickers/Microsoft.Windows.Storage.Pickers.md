Microsoft.Windows.Storage.Pickers Namespace
===

The `Microsoft.Windows.Storage.Pickers` API in the Windows App SDK provides a modernized file and 
folder picker experience for desktop applications. This API is based on the existing 
[Windows.Storage.Pickers](https://learn.microsoft.com/en-us/uwp/api/windows.storage.pickers) API 
design, but with key improvements for desktop scenarios.

# Background

The new `Microsoft.Windows.Storage.Pickers` API addresses two critical limitations of the UWP file 
and folder pickers on Apps developed with WinAppSDK/WinUI 3:

1. **Elevated Process Support**: The existing [Windows.Storage.Pickers](https://learn.microsoft.com/en-us/uwp/api/windows.storage.pickers) 
APIs do not work when the application is running as an administrator. The new API enables file and 
folder selection in elevated mode.

2. **Simplified Usage in WinUI 3**: Using the existing UWP pickers in WinUI 3 requires initializing 
a window handle for window association. The new pickers eliminate this requirement by accepting a 
`WindowId` directly in the constructor, making them easier to use.

# Key Differences
*Spec Note: Here are some key differences from the UWP `Windows.Storage.Pickers`:*
1. *Unlike the existing `Windows.Storage.Pickers` API which returns `StorageFile`/`StorageFolder` 
objects, this new API returns string-based paths through `PickFileResult` and `PickFolderResult` 
classes. This design choice simplifies the API and avoids complications with storage capabilities 
in elevated scenarios.*
1. *Similarly, the `FileSavePicker.SuggestedSaveFile` property (which returned a `StorageFile`) 
has been replaced. Its functionality is now covered by two string properties: `SuggestedFolder` and 
`SuggestedFileName`. These allow for suggesting the folder and file name for the save dialog.*
1. Also adding the `SuggestedFolder` property to `FileOpenPicker` and `FolderPicker`, to better 
support a commonly requested scenario - setting a persistent folder for all pickers.
1. *All new pickers are designed specifically for desktop apps and use a `WindowId` property to 
link the picker to its host window, replacing the `WinRT.Interop.InitializeWithWindow.Initialize` 
pattern.*
1. The new pickers allow developers to use them without requiring `FileTypeFilter` or 
`FileTypeChoices` to be specified. While UWP pickers throw exceptions when these properties are not 
set, the new pickers default to showing all files when developers do not explicitly configure these 
properties.
1. *The `HomeGroup` location has been excluded from the new `PickerLocationId` enum as it is 
no longer supported in Windows 10 and later.*
1. *`FolderPicker.FileTypeFilter` has been excluded as it was not functionally appropriate for folder 
selection.*
1. *Excluding methods and properties that are already marked as deprecated or "Do not use". 
e.g., `PickSingleFileAndContinue`, `ContinuationData`, `ResumePickSingleFileAsync`, etc.*
1. *Excluding methods and properties for [multi-user-mode](https://learn.microsoft.com/en-us/previous-versions/windows/uwp/xbox-apps/multi-user-applications), 
because the new APIs are currently designed for desktop scenarios where each user has their own 
interactive session, and each session is completely independent of the other sessions on the device.
This is in contrast to Xbox One or other multi-user devices.*

1. Adding `SuggestedStartFolder` for all 3 pickers. This allows setting the initial folder with 
an absolute folder path in string. When its specified folder exists, `SuggestedStartFolder` 
takes precedence over `SuggestedStartLocation`; when its folder not found, the picker falls back 
to `SuggestedStartLocation`, then to the system default.

1. Adding `FileTypeChoices` for `FileOpenPicker`. This allows the dialog of FileOpenPicker to have 
catagorized filter types. When both `FileTypeChoices` and `FileTypeFilter` are provided, 
`FileTypeChoices` is used and `FileTypeFilter` is ignored.

1. Adding `FileTypeIndex` for `FileOpenPicker` and `FileSavePicker`. This allows setting the default selected file type filter index. Note this index is 1-based. When it is 0 (the default value), the selected filter might be override by the API's default behavior.

1. The property `SettingsIdentifier` will be available in the new Storage.Pickers APIs from WindowsAppSDK2.0. `SettingsIdentifier` allows the picker to remember its state (e.g. size, location, etc) across sessions. When two different apps use the same string for SettingsIdentifier property, they will have their respective independent states.

1. Adding `Title` for all 3 pickers. `Title` allows setting the title of the picker dialog.

1. Adding `PickMultipleFoldersAsync` for `FolderPicker`. This allows selecting multiple folders in the folder picker dialog.


# Conceptual pages

# API

## Classes

Note: Developers should specify a window id to associate the picker with an owner window before 
showing the UI.

| **Class**        | **Description** |
|------------------|-----------------|
| [FileOpenPicker](./FileOpenPicker.md)| Displays a UI element that allows user to choose and open files. |
| [FileSavePicker](./FileSavePicker.md)| Displays a UI element that allows user to save a file.    |
| [FolderPicker](./FolderPicker.md)    | Displays a UI element that allows user to choose a folder.|
| [PickFileResult](./PickFileResult.md)| Represents the result of a file picking operation.        |
| [PickFolderResult](./PickFolderResult.md) | Represents the result of a folder picking operation. |

## Enums

| **Enum** | **Description** |
|----------|-----------------|
|[PickerLocationId](PickerLocationId.md)| Identifies the storage location that the file picker presents to the user. |
|[PickerViewMode](PickerViewMode.md)    | Indicates the view mode that the file picker uses to present items.    |

## Definition

```C#
namespace Microsoft.Windows.Storage.Pickers
{
    enum PickerViewMode
    {
        List = 0,
        Thumbnail = 1,
    }

    enum PickerLocationId
    {
        DocumentsLibrary = 0,
        ComputerFolder = 1,
        Desktop = 2,
        Downloads = 3,
        // [removed] HomeGroup = 4,  The HomeGroup LocationId is removed from Windows 10, therefore we will not support it..
        MusicLibrary = 5,
        PicturesLibrary = 6,
        VideosLibrary = 7,
        Objects3D = 8,
        Unspecified = 9,
    }

    runtimeclass PickFileResult {
        string Path { get; }
    }

    runtimeclass PickFolderResult {
        string Path { get; }
    }

    runtimeclass FileOpenPicker
    {
        FileOpenPicker(Microsoft.UI.WindowId windowId);

        string CommitButtonText;
        string Title;
        string SettingsIdentifier;

        IMap<string, IVector<string>> FileTypeChoices{ get; };
        IVector<string> FileTypeFilter{ get; };
        int FileTypeIndex;

        string SuggestedFolder;
        string SuggestedStartFolder;
        PickerLocationId SuggestedStartLocation;

        PickerViewMode ViewMode;

        Windows.Foundation.IAsyncOperation<PickFileResult> PickSingleFileAsync();
        Windows.Foundation.IAsyncOperation<IVectorView<PickFileResult>> PickMultipleFilesAsync();
    }

    runtimeclass FileSavePicker
    {
        FileSavePicker(Microsoft.UI.WindowId windowId);

        string CommitButtonText;
        string Title;
        string SettingsIdentifier;

        string DefaultFileExtension;
        string SuggestedFileName;

        IMap<string, IVector<string>> FileTypeChoices{ get; };
        int FileTypeIndex;

        string SuggestedFolder;
        string SuggestedStartFolder;
        PickerLocationId SuggestedStartLocation;

        Windows.Foundation.IAsyncOperation<PickFileResult> PickSaveFileAsync();
    }

    runtimeclass FolderPicker
    {
        FolderPicker(Microsoft.UI.WindowId windowId);

        string CommitButtonText;
        string Title;
        string SettingsIdentifier;

        string SuggestedFolder;
        string SuggestedStartFolder;
        PickerLocationId SuggestedStartLocation;

        PickerViewMode ViewMode;

        Windows.Foundation.IAsyncOperation<PickFolderResult> PickSingleFolderAsync();
        Windows.Foundation.IAsyncOperation<IVectorView<PickFolderResult>> PickMultipleFoldersAsync();
    }
}
```

Note: **Understanding SuggestedStartFolder/SuggestedStartLocation vs SuggestedFolder:**

These two kinds of properties have fundamentally different behaviors in terms of when and how they 
affect the picker:

- `SuggestedFolder` sets the path that will always be tried when opening the picker, regardless of 
    the user's previous operations. This uses the [SetFolder](https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nf-shobjidl_core-ifiledialog-setfolder) 
    method of the underlying COM APIs and takes precedence over any user navigation history.

- `SuggestedStartFolder` sets the path shown only the first time the user launches the picker 
    (typically when the app is newly installed). After the user has picked a file, subsequent 
    launches of the picker will open to the user's last selected folder, and `SuggestedStartFolder` 
    becomes silent. This corresponds to the [SetDefaultFolder](https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nf-shobjidl_core-ifiledialog-setdefaultfolder) 
    method in the COM API.

    The effective time span of `SuggestedStartFolder` is the same as that of `SuggestedStartLocation`, 
    both only influence the picker's initial behavior before user interaction establishes a 
    navigation history.

    `SuggestedStartFolder` takes precedence over `SuggestedStartLocation` when both specified.
