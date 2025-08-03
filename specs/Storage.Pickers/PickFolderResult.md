PickFolderResult Class
===

# Background

Namespace: [Microsoft.Windows.Storage.Pickers](./Microsoft.Windows.Storage.Pickers.md)

Represents the result of a folder picking operation. This is a lightweight class that contains a 
string property representing the folder path.

# API Pages

## Definition

```C#
runtimeclass PickFolderResult {
    string Path { get; }
}
```

# Backward Compatibility

A `PickFolderResult` object can be converted to a `Windows.Storage.StorageFolder` object via 
[Windows.Storage.StorageFolder.GetFolderFromPathAsync](https://learn.microsoft.com/en-us/uwp/api/windows.storage.storagefolder.getfolderfrompathasync)
by using the folder path.


## Examples

C#

```C#
using Microsoft.Windows.Storage.Pickers;

// In a method of a window class
var picker = new FolderPicker(this.AppWindow.Id);
var result = await picker.PickSingleFolderAsync();
if (result != null)
{
    // Perform this conversion if you have business logic that uses StorageFolder
    var storageFolder = await Windows.Storage.StorageFolder.GetFolderFromPathAsync(result.Path);
    // Continue your business logic with storageFolder
}
else
{
    // error handling.
}
```

C++

```C++
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

// In a coroutine method of a window class
FolderPicker picker{ AppWindow().Id() };
auto result{ co_await picker.PickSingleFolderAsync() };
if (result)
{
    // Perform this conversion if you have business logic that uses StorageFolder
    auto storageFolder{ co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(result.Path()) };
    // Continue your business logic with storageFolder
}
else
{
    // error handling.
}
```
