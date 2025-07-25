PickerLocationId Enum
===

Specifies the default folder or library that a picker starts from or displays to the user.

Namespace: [Microsoft.Windows.Storage.Pickers](./Microsoft.Windows.Storage.Pickers.md)

*Spec Note: This enum is based on [Windows.Storage.Pickers.PickerLocationId](https://learn.microsoft.com/en-us/uwp/api/windows.storage.pickers.pickerlocationid) but with the HomeGroup value removed, as HomeGroup is no longer supported in Windows 10 and later versions.*

# Fields

| **Name**           | **Value** | **Description**                                                 |
|--------------------|-----------|-----------------------------------------------------------------|
| DocumentsLibrary   | 0         | [The Documents library](#pickerlocationiddocumentslibrary)      |
| ComputerFolder     | 1         | [This PC](#pickerlocationidcomputerfolder)                      |
| Desktop            | 2         | [The Desktop](#pickerlocationiddesktop)                         |
| Downloads          | 3         | [The Downloads folder](#pickerlocationiddownloads)              |
| MusicLibrary       | 5         | [The Music library](#pickerlocationidmusiclibrary)              |
| PicturesLibrary    | 6         | [The Pictures library](#pickerlocationidpictureslibrary)        |
| VideosLibrary      | 7         | [The Videos library](#pickerlocationidvideoslibrary)            |
| Objects3D          | 8         | [The 3D Objects folder (avoid using this)](#pickerlocationidobjects3d)|
| Unspecified        | 9         | [An unspecified location](#pickerlocationidunspecified)         |

*Spec Note: The value 4 is intentionally skipped as it was previously assigned to HomeGroup in the original `Windows.Storage.Pickers` API.*

# Definition

```C#
enum PickerLocationId
{
    DocumentsLibrary = 0,
    ComputerFolder = 1,
    Desktop = 2,
    Downloads = 3,
    
    MusicLibrary = 5,
    PicturesLibrary = 6,
    VideosLibrary = 7,
    Objects3D = 8,
    Unspecified = 9,
}
```

## PickerLocationId.DocumentsLibrary
The `DocumentsLibrary` value represents the user's Documents library.

This is the default location where many applications save documents, and it is often mapped 
to the `%USERPROFILE%\Documents` folder on the user's system. 
If the user has configured OneDrive for documents, this location would be redirected to a OneDrive 
folder, such as `%USERPROFILE%\OneDrive\Documents`.

## PickerLocationId.ComputerFolder
The `ComputerFolder` value represents "This PC" directory.

This location provides access to all drives and devices connected to the user's computer, 
including internal and external storage devices.

## PickerLocationId.Desktop
The `Desktop` value represents the user's Desktop.

This is the location where users often save shortcuts, files, and folders for quick access. 
It is often mapped to `%USERPROFILE%\Desktop`.

## PickerLocationId.Downloads
The `Downloads` value represents the user's Downloads folder.

This is the default location where web browsers and other applications save downloaded files. 
It is often mapped to `%USERPROFILE%\Downloads`.

## PickerLocationId.MusicLibrary
The `MusicLibrary` value represents the user's Music library.

This is the default location where many applications save music files, and it is often mapped 
to `%USERPROFILE%\Music`. If the user has configured OneDrive for the music library, this location 
would be redirected to a OneDrive folder, such as `%USERPROFILE%\OneDrive\Music`.

## PickerLocationId.PicturesLibrary
The `PicturesLibrary` value represents the user's Pictures library.

This is the default location where many applications save image files, and it is often mapped 
to `%USERPROFILE%\Pictures`. If the user has configured OneDrive for the pictures library, this 
location would be redirected to a OneDrive folder, such as `%USERPROFILE%\OneDrive\Pictures`.

## PickerLocationId.VideosLibrary
The `VideosLibrary` value represents the user's Videos library.

This is the default location where many applications save video files, and it is often mapped 
to `%USERPROFILE%\Videos`. If the user has configured OneDrive for the videos library, this location 
would be redirected to a OneDrive folder, such as `%USERPROFILE%\OneDrive\Videos`.

## PickerLocationId.Objects3D
! Note: This location is being phased out, so it is recommended to avoid using this value.

The `Objects3D` value represents the 3D Objects folder. This is the default location where many 
applications save 3D object files, and it is often mapped to `%USERPROFILE%\3D Objects`.

This enum value is retained for backward compatibility with [Windows.Storage.Pickers.PickerLocationId](https://learn.microsoft.com/en-us/uwp/api/windows.storage.pickers.pickerlocationid).

## PickerLocationId.Unspecified
The `Unspecified` value represents an unspecified location.

When this value is used, the file picker will use the system default location, which may vary 
depending on the user's configuration and the context in which the picker is used.

When `SuggestedStartLocation` is not specified in [FileOpenPicker](./FileOpenPicker.md), 
[FileSavePicker](./FileSavePicker.md), or [FolderPicker](./FolderPicker.md), 
the default value is `PickerLocationId.Unspecified`.
