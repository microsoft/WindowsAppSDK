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

   The existing File/Folder pickers do not allow the developer to specify an arbitrary start location (even if the app has access). Currently, the start location is limited to a set of predefined enum values.

The Reunion picker dialog addresses the above issues. This Reunion API will be based upon the below
APIs in the Windows SDK. The Reunion Picker API will remove the deprecated APIs and add additional methods
for the functionality: File and folder picker, Multiple folder picker.

- Windows.Storage.Pickers.FileOpenPicker (https://docs.microsoft.com/en-us/uwp/api/Windows.Storage.Pickers.FileOpenPicker)
- Windows.Storage.Pickers.FileSavePicker (https://docs.microsoft.com/en-us/uwp/api/windows.storage.pickers.filesavepicker)
- Windows.Storage.Pickers.FolderPicker (https://docs.microsoft.com/en-us/uwp/api/windows.storage.pickers.folderpicker) 

# Description

The goal of this API is to address the gaps in the existing File/Folder picker APIs. The API surface is similar to the existing
Picker APIs in Windows SDK with additional methods to support File + Folder picker and multiple folder picker. The Project Reunion APIs will supercede the Windows APIs.

# Examples
## Show file and folder picker
    ```c#
    var picker = new StorageItemPicker();
    picker.FilterAndDescription.Insert("Images", "*.jpg, *.png");
    picker.StartLocation = startLocation;
    picker.PickableKinds = StorageItemPickerKinds.Folder | StorageItemPickerKinds.File;
    IReadOnlyList<StorageItem> storageItems = await picker.PickMultipleItemsAsync();

    if(0 < storageItems.Count)
    {
    }
    ```
## Show single folder picker
    ```c#
    var picker = new StorageItemPicker();
    picker.PickerKinds = StorageItemPickerKinds.Folder;
    Windows.Storage.IStorageItem folder = await picker.PickSingleItemAsync();
    ```
## Show multi folder picker
    ```c#
    var picker = new StorageItemPicker();
    picker.PickerKinds = StorageItemPickerKinds.Folder;
    IReadOnlyList<Windows.Storage.IStorageItem> folders = await picker.PickMultipleItemsAsync();
    ```
# Remarks
# API Notes
# API Details
    ```c#
    namespace Microsoft.Reunion.Storage.Pickers
    {
        enum PickerViewMode
        {
            List = 0,
            Details,
            Tiles,
            Content
        };

        enum StorageItemPickerKinds
        {
            File = 0x1,
            Folder = 0x2
        };

        runtimeclass StorageItemPicker
        {
            StorageItemPicker();

            /// Properties
            String StartLocation;
            String CommitButtonText { set; }
            String CancelButtonText { set; }
            Windows.Foundation.Collections.IMap<String, String> FilterAndDescription{ get; }
            PickerViewMode ViewMode;
            StorageItemPickerKinds PickerKinds;
            String SuggestedSaveFile;
            String DefaultFileExtension;

            /// Methods
            Windows.Foundation.IAsyncOperation<Windows.Storage.IStorageItem> PickSingleItemAsync();
            Windows.Foundation.IAsyncOperation<Windows.Foundation.Collections.IVector<Windows.Storage.IStorageItem>> PickMutipleItemsAsync();
            Windows.Foundation.IAsyncOperation<Windows.Storage.StorageFile> PickSaveFileAsync();
        }
    }
    ```

# Appendix