# Background

The current FilePicker API for UWP has several limitations. Some of the top limitations
are as described below:

**1. Unable to pick files and folders in a single instance of the Picker dialog**

The Picker dialog allows developers to specify picker mode to be single file or multiple
files. It does not however, allow developers to specify a mode to pick both files and folders.
There has been feedback indicating that this behaviour is limiting, requiring developers
to build their own picker experience.

**2. Unable to pick multiple folders.**

The Picker dialog (FolderPicker) does not allow users to pick multiple folders. The developer
experience currently is to select a single folder and repeat the dialog for more folders. This
is a less than ideal experience for application developers.

**3. Unable to specify an arbitrary start location for the picker.**

The existing File/Folder pickers do not allow the developer to specify an arbitrary start location 
(even if the app has access). Currently, the start location is limited to a set of predefined enum 
values.

The Reunion picker dialog addresses the above issues. This Reunion API will be based upon the below
APIs in the Windows SDK. The Reunion Picker API will supercede the existing APIs and add additional 
methods for the functionality: File and folder picker, Multiple folder picker.

-   [Windows.Storage.Pickers.FileOpenPicker](https://docs.microsoft.com/en-us/uwp/api/Windows.Storage.Pickers.FileOpenPicker)
-   [Windows.Storage.Pickers.FileSavePicker](https://docs.microsoft.com/en-us/uwp/api/windows.storage.pickers.filesavepicker)
-   [Windows.Storage.Pickers.FolderPicker](https://docs.microsoft.com/en-us/uwp/api/windows.storage.pickers.folderpicker)

# Description

The goal of this API is to address the gaps in the existing File/Folder picker APIs. The API 
surface is similar to the existing Picker APIs in Windows SDK with additional methods to support
File + Folder picker and multiple folder picker. The Project Reunion APIs will supercede the 
Windows APIs.

# Examples

## Show file and folder picker to pick images with specified extension

```c#
    var picker = new StorageItemPicker();
    picker.FiltersAndDescriptions.Insert("Images", "*.jpg, *.png");
    picker.StartLocation = @"%userprofile%\pictures";
    picker.PickerKinds = StorageItemPickerKinds.Folder | StorageItemPickerKinds.FileOpen;
    StorageItemPickerResult result = await picker.ShowPickerAsync();

    if(result.PickerResult == 0)
    {
        foreach(var storageItem in result.PickedItems)
        {
            if(storageItem is StorageFile)
            {
                IList<String> contents = await FileIO.ReadLinesAsync(storageItem);

                foreach(String content in contents)
                {
                    System.Diagnostics.Debug.WriteLine(content);
                }
            }
            else
            {
                System.Diagnostics.Debug.WriteLine(storageItem.Name);
            }
        }
    }
    else
    {
        StringBuilder stringBuilder = new StringBuilder("ShowPicker failed with hr:");
        stringBuilder.Append(result.PickerResult);
        System.Diagnostics.Debug.WriteLine(stringBuilder.ToString());
    }
```

## Pick folder

```c#
    var picker = new StorageItemPicker();
    picker.PickerKinds = StorageItemPickerKinds.Folder;
    StorageItemPickerResult result = await picker.ShowPickerAsync();

    if(result.PickerResult == 0)
    {
        var selectedFolder = result.PickedItems[0];
        System.Diagnostics.Debug.WriteLine(selectedFolder.Name);
        // Other folder operations
    }
    else
    {
        StringBuilder stringBuilder = new StringBuilder("ShowPicker failed with hr:");
        stringBuilder.Append(result.PickerResult);
        System.Diagnostics.Debug.WriteLine(stringBuilder.ToString());
    }
```

## Pick multiple folders for access

```c#
    var picker = new StorageItemPicker();
    picker.PickerKinds = StorageItemPickerKinds.Folder;
    picker.MultiSelect = true;
    StorageItemPickerResult result = await picker.ShowPickerAsync();

    if(result.PickerResult == 0)
    {
        foreach(var folder in result.PickedItems)
        {
            System.Diagnostics.Debug.WriteLine(folder.Name);
        }
    }
    else
    {
        StringBuilder stringBuilder = new StringBuilder("ShowPicker failed with hr:");
        stringBuilder.Append(result.PickerResult);
        System.Diagnostics.Debug.WriteLine(stringBuilder.ToString());
    }
```

## Pick multiple files and specify a start location

```c#
    var picker = new StorageItemPicker();
    picker.StartLocation = @"%userprofile%\foldername";
    picker.MultiSelect = true;
    picker.PickerKinds = StorageItemPickerKinds.FileOpen;
    StorageItemPickerResult result = await picker.ShowPickerAsync();

    if(result.PickerResult == 0)
    {
        foreach(var file in result.PickedItems)
        {
            System.Diagnostics.Debug.WriteLine(file.Name);
            System.Diagnostics.Debug.WriteLine(file.Path);
        }
    }
    else
    {
        StringBuilder stringBuilder = new StringBuilder("ShowPicker failed with hr:");
        stringBuilder.Append(result.PickerResult);
        System.Diagnostics.Debug.WriteLine(stringBuilder.ToString());
    }
```

## Show File Save picker starting at custom location

```c#
    var picker = new StorageItemPicker();
    picker.StartLocation = @"%userprofile%\folder";
    picker.PickerKinds = StorageItemPickerKinds.FileSave;
    StorageItemPickerResult result = await picker.ShowPickerAsync();

    if(result.PickerResult == 0)
    {
        var saveFile = result.PickedItems[0];
        if(saveFile != null)
        {
            await FileIO.WriteTextAsync(saveFile, "Picked from FilePicker");
        }
    }
    else
    {
        StringBuilder stringBuilder = new StringBuilder("ShowPicker failed with hr:");
        stringBuilder.Append(result.PickerResult);
        System.Diagnostics.Debug.WriteLine(stringBuilder.ToString());
    }
```

# Remarks

# API Notes
The ShowPickerAsync method must be invoked on the UI thread.

# API Details

```c#
    namespace Microsoft.Storage.Pickers
    {
        enum StorageItemPickerViewMode
        {
            List = 0,
            Details,
            Tiles,
            Content
        };

        [flags, v1_enum]
        enum StorageItemPickerKinds
        {
            FileOpen = 0x1,
            Folder = 0x2,
            FileSave = 0x4
        };

        runtimeclass StorageItemPickerResult
        {
            Windows.Foundation.Collections.IVectorView<Windows.Storage.IStorageItem> PickedItems{ get; };
            Int64 PickerResult{ get; };
        }

        runtimeclass StorageItemPicker
        {
            StorageItemPicker();

            /// Properties
            String StartLocationFolderPath;
            String CommitButtonText;
            String CancelButtonText;
            Windows.Foundation.Collections.IPropertySet FiltersAndDescriptions{ get; };
            StorageItemPickerViewMode DefaultViewMode;
            StorageItemPickerKinds PickerKinds;
            String SuggestedFileName;
            String DefaultFileExtension;
            Boolean MultiSelect;

            /// Methods
            Windows.Foundation.IAsyncOperation<StorageItemPickerResult> ShowPickerAsync();
        }
    }
```

# Appendix
