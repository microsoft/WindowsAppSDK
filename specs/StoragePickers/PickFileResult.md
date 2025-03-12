PickFileResult Class
===

# Background

Namespace: [Microsoft.Windows.Storage.Pickers](./Microsoft.Windows.Storage.Pickers.md)

Represents the result of a file picking operation. This is a lightweight class that contains a 
string attribute representing the file path. Its class object can be converted to a 
`Windows.Storage.StorageFile` object.

# API Pages

## Constructor

### Attributes

| **Attribute** | **Type** | **Description** |
|---------------|----------|-----------------|
| `Path`        | `string` | Gets the path of the picked file. |

### Examples
C#

```csharp
using Microsoft.Windows.Storage.Pickers;

var result = new PickFileResult("C:\\example\\file.txt");
```

C++

```cpp
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
using namespace winrt::Microsoft::Windows::Storage::Pickers;

PickFileResult result(L"C:\\example\\file.txt");
```

## PickFileResult.ToStorageFileAsync

Converts the picked file to a `Windows.Storage.StorageFile` object.

This conversion aims to facilitate a smooth transition for developers already using 
`Windows.Storage.StorageFile` in their business logic.

Returns a lightweight object that has the path of the picked file.

### Examples

C#

```C#
using Microsoft.Windows.Storage.Pickers;

var picker = new FileOpenPicker();
var result = await picker.PickSingleFileAsync();
if (result != null)
{
    // Perform this conversion if you have business logic that uses StorageFile
    var storageFile = await result.ToStorageFileAsync();
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

FileOpenPicker picker;
auto& result{ co_await openPicker.PickSingleFileAsync() };
if (result)
{
    // Perform this conversion if you have business logic that uses StorageFile
    auto storageFile = co_await result.ToStorageFileAsync();
    // Your business logic
}
else
{
    // error handling.
}
```
