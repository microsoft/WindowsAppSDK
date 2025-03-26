Microsoft.Windows.Storage.Pickers Namespace
===

The `Microsoft.Windows.Storage.Pickers` API in the Windows App SDK lets desktop applications (like 
WinUI3) present a streamlined UI for selecting files or folders, modifying filenames and extensions, 
and accessing paths — all while integrating seamlessly across Windows desktops.

# Background

The standard OS file and folder picker APIs [Windows.Storage.Pickers](https://learn.microsoft.com/en-us/uwp/api/windows.storage.pickers) 
do not work when running as an administrator. To address this gap, here we're introducing the new
`Microsoft.Windows.Storage.Pickers` API by enabling file and folder selection in elevated mode. 
It is designed for desktop apps and uses a `WindowId` property to link the picker to its host window.

# Conceptual pages

# API

## Classes

Note: Developers should specify a window id to associate the picker with an owner window before 
showing UI.

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
|[PickerViewMode](PickerViewMode.md)    | Indicates the view mode that the file picker is using to present items.    |

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
        HomeGroup = 4,  // Will be removed in future.
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
        string SettingsIdentifier;
        IVector<string> FileTypeFilter{ get; };
        PickerLocationId SuggestedStartLocation;
        PickerViewMode ViewMode;

        Windows.Foundation.IAsyncOperation<PickFileResult> PickSingleFileAsync();
        Windows.Foundation.IAsyncOperation<IVectorView<PickFileResult>> PickMultipleFilesAsync();
    }

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

    runtimeclass FolderPicker
    {
        FolderPicker(Microsoft.UI.WindowId windowId);

        string CommitButtonText;
        IVector<string> FileTypeFilter{ get; };

        PickerLocationId SuggestedStartLocation;
        PickerViewMode ViewMode;
        string SettingsIdentifier;

        Windows.Foundation.IAsyncOperation<PickFolderResult> PickSingleFolderAsync();
    }
}
```
