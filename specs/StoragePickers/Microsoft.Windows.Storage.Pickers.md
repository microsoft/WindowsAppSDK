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

## Classes

Note: Developers should specify a window id to associate the picker with an owner window before 
showing UI.

| **Class**        | **Description** |
|------------------|-----------------|
| [FileOpenPicker](./FileOpenPicker.md)| Displays a UI element that allows user to choose and open files. |
| [FileSavePicker](./FileSavePicker.md)| Displays a UI element that allows user to save a file.    |
| [FolderPicker](./FolderPicker.md)    | Displays a UI element that allows user to choose a folder.|

## Enums

| **Enum** | **Description** |
|----------|-----------------|
|[PickerLocationId](PickerLocationId.md)| Identifies the storage location that the file picker presents to the user. |
|[PickerViewMode](PickerViewMode.md)    | Indicates the view mode that the file picker is using to present items.     |
