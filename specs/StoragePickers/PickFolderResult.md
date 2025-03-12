PickFolderResult Class
===

# Background

Namespace: [Microsoft.Windows.Storage.Pickers](./Microsoft.Windows.Storage.Pickers.md)

Represents the result of a folder picking operation. This is a lightweight class that contains a 
string attribute representing the folder path. Its class object can be converted to a 
`Windows.Storage.StorageFolder` object.

# API Pages

## Constructor

### Attributes

| **Attribute** | **Type** | **Description** |
|---------------|----------|-----------------|
| `Path`        | `string` | Gets the path of the picked folder. |

### Examples
C#

```C#
using Microsoft.Windows.Storage.Pickers;

var result = new PickFolderResult("C:\\example\\folder");
```

C++

```C++
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
#include <iostream>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

PickFolderResult result(L"C:\\example\\folder");
```

## PickFolderResult.ToStorageFolderAsync

Converts the picked folder to a `Windows.Storage.StorageFolder` object.

This conversion aims to facilitate a smooth transition for projects already using 
`Windows.Storage.StorageFolder` in their business logic.

Returns a lightweight object that has the path of the picked folder.

### Examples

C#

```C#
using Microsoft.Windows.Storage.Pickers;

var picker = new FolderPicker();
var result = await picker.PickSingleFolderAsync();
if (result != null)
{
    // Perform this conversion if you have business logic that uses StorageFolder
    var storageFolder = await result.ToStorageFolderAsync();
    // Your business logic
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

FolderPicker picker;
auto& result{ co_await picker.PickSingleFolderAsync() };
if (result)
{
    // Perform this conversion if you have business logic that uses StorageFolder
    auto storageFolder = co_await result.ToStorageFolderAsync();
    // Your business logic
}
else
{
    // error handling.
}
```