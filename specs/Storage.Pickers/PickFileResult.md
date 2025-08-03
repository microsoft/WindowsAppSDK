PickFileResult Class
===

# Background

Namespace: [Microsoft.Windows.Storage.Pickers](./Microsoft.Windows.Storage.Pickers.md)

Represents the result of a file picking operation. This is a lightweight class that contains a 
string property representing the file path.

# API Pages

## Definition

```C#
runtimeclass PickFileResult {
    string Path { get; }
}
```

# Backward Compatibility

A `PickFileResult` object can be converted to a `Windows.Storage.StorageFile` object via 
[Windows.Storage.StorageFile.GetFileFromPathAsync](https://learn.microsoft.com/en-us/uwp/api/windows.storage.storagefile.getfilefrompathasync)
by using the file path.

## Examples

C#

```C#
using Microsoft.Windows.Storage.Pickers;

// In a coroutine method of a window class
var picker = new FileOpenPicker(this.AppWindow.Id);
var result = await picker.PickSingleFileAsync();
if (result != null)
{
    // Perform this conversion if you have business logic that uses StorageFile
    var storageFile = await Windows.Storage.StorageFile.GetFileFromPathAsync(result.Path);
    // Continue your business logic with storageFile
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
FileOpenPicker picker{ AppWindow().Id() };
auto result{ co_await picker.PickSingleFileAsync() };
if (result)
{
    // Perform this conversion if you have business logic that uses StorageFile
    auto storageFile{ co_await winrt::Windows::Storage::StorageFile::GetFileFromPathAsync(result.Path()) };
    // Continue your business logic with storageFile
}
else
{
    // error handling.
}
```
