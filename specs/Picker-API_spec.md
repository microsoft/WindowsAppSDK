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

The Reunion picker dialog is going to address the above issues. This Reunion API will be based upon the below
APIs in the Windows SDK. The Reunion Picker API will remove the deprecated APIs and add additional methods
for the functionality: File and folder picker, Multiple folder picker.

- Windows.Storage.Pickers.FileOpenPicker (https://docs.microsoft.com/en-us/uwp/api/Windows.Storage.Pickers.FileOpenPicker)
- Windows.Storage.Pickers.FileSavePicker (https://docs.microsoft.com/en-us/uwp/api/windows.storage.pickers.filesavepicker)
- Windows.Storage.Pickers.FolderPicker (https://docs.microsoft.com/en-us/uwp/api/windows.storage.pickers.folderpicker) 

# Description

The goal of this API is to address the gaps in the existing File/Folder picker APIs. The API surface is similar to the existing
Picker APIs in Windows SDK with additional methods to support File + Folder picker and multiple folder picker. The API removes the
deprecated methods from Windows SDK.

# Examples

## Show file and folder picker
    ```c#
    var picker = StorageItemPicker::CreateStorageItemPicker();
    picker.Filters.add("*.jpg");
    picker.Filters.add("*.png");
    picker.StartLocation = startLocation;
    picker.PickerMode = StorageItemPickerMode::Any;
    IReadOnlyList<StorageItem> storageItems = await picker.PickStorageItemAsync();

    if(0 < storageItems.Count)
    {
    }
    ```

## Show single folder picker
    ```c#
    var picker = StorageItemPicker::CreateStorageItemPicker();
    picker.PickerMode = StorageItemPickerMode::Folder;
    Windows.Storage.StorageFolder folder = await picker.PickSingleFolderAsync();
    ```


## Show multi folder picker
    ```c#
    var picker = StorageItemPicker::CreateStorageItemPicker();
    picker.PickerMode = StoargeItemPickerMode::Folder;
    IReadOnlyList<Windows.Storage.StorageFolder> folders = picker.PickMultipleFoldersAsync();
    ```

# Remarks

# API Notes


# API Details

    ```c#
    namespace Microsoft.Reunion.Storage.Pickers
    {
        typedef enum PickerViewMode
        {
            List = 0,
            Details,
            Tiles,
            Content
        } PickerViewMode;

        typedef enum StorageItemPickerMode
        {
            Any = 0,
            File,
            Folder
        } StorageItemPickerMode;

        runtimeclass StorageItemPicker
        {
            /// Static constructor
            static StorageItemPicker StorageItemPicker();

            /// Properties
            String StartLocation{ set; }
            String CommitButtonText { set; }
            String CancelButtonText { set; }
            Windows.Foundation.Collections.IMap<String, String> FilterAndDescription{ get; }
            PickerViewMode ViewMode{ get; set; }
            StorageItemPickerMode PickerMode { get; set; }
            String SuggestedSaveFile{ get; set; }
            String DefaultFileExtension{ get; set; }

            /// Methods
            Windows.Foundation.IAsyncOperation<Windows.Storage.StorageFile> PickSingleFileAsync();
            Windows.Foundation.IAsyncOperation<Windows.Foundation.Collections.IVectorView<Windows.Storage.StorageFile>> PickMutipleFilesAsync();
            Windows.Foundation.IAsyncOperation<Windows.Foundation.Collections.IVectorView<Windows.Storage.StorageItem>> PickStorageItemsAsync();
            Windows.Foundation.IAsyncOperation<Windows.Storage.StorageFile> PickSaveFileAsync();
            Windows.Foundation.IAsyncOperation<Windows.Storage.StorageFolder> PickFolderAsync();
            Windows.Foundation.IAsyncOperation<Windows.Foundation.Collections.IVectorView<Windows.Storage.StorageFolder>> PickMultipleFoldersAsync();
        }
    }
    ```

# Appendix