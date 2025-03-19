PickFileResult Class
===

# Background

Namespace: [Microsoft.Windows.Storage.Pickers](./Microsoft.Windows.Storage.Pickers.md)

Represents the result of a file picking operation. This is a lightweight class that contains a 
string attribute representing the file path.

# API Pages

## Definition

```C#
runtimeclass PickFileResult {
    string Path { get; }
}
```

# Backward compatability

A PickFileResult object can be converted to `Windows.Storage.StorageFile` object via 
[Windows.Storage.StorageFile.GetFileFromPathAsync](https://learn.microsoft.com/en-us/uwp/api/windows.storage.storagefile.getfilefrompathasync)
by the file path.

## Examples

C#

```C#
using Microsoft.Windows.Storage.Pickers;

var picker = new FileOpenPicker();
var result = await picker.PickSingleFileAsync();
if (result != null)
{
    // Perform this conversion if you have business logic that uses StorageFile
    var storageFile = await Windows.Storage.StorageFile.GetFileFromPathAsync(result.Path)
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

FileOpenPicker picker;
auto& result{ co_await openPicker.PickSingleFileAsync() };
if (result)
{
    // Perform this conversion if you have business logic that uses StorageFile
    auto& storageFile{ co_await winrt::Windows::Storage::StorageFile::GetFileFromPathAsync(result.Path) }
    // Continue your business logic with storageFile
}
else
{
    // error handling.
}
```
