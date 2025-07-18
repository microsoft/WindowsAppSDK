# One page design for `FileSavePicker.SuggestedSaveFilePath`


## Overview

This document proposes a change to the `Microsoft.Windows.Storage.Pickers.FileSavePicker`. We aim to 
replace the `SuggestedSaveFile` property, which was of type `Windows.Storage.StorageFile`, with a 
new property `SuggestedSaveFilePath`, a string property that is capable of providing a comprehensive 
hint for both the target save location (directory) and the proposed file name using a single string.

This change will allow for a more straightforward way to suggest a default file path, and reduce the
boilerplate code.

We propose the following:

1.  Remove the existing `SuggestedSaveFile` property of type `Windows.Storage.StorageFile`.

1.  Introduce `SuggestedSaveFilePath` Property (readonly) and its set method 
    `Boolean TrySetSuggestedSaveFilePath(String filePath)`


## Detailed Design

The `FileSavePicker` class will be updated as follows:

```cs
namespace Microsoft.Windows.Storage.Pickers {
    runtimeclass FileSavePicker {
        // ... other members
        String SuggestedSaveFilePath { get; };
        Boolean TrySetSuggestedSaveFilePath(String filePath);
    }
}
```

## Changes in Developers' Experience.

### 1. When Developers using the result returned by FileOpenPicker

Before Change:
```cs
var openPicker = Microsoft.Windows.Storage.Pickers.FileOpenPicker(this.AppWindows.Id);
var savePicker = Microsoft.Windows.Storage.Pickers.FileSavePicker(this.AppWindows.Id);

var result = await openPicker.PickSingleFileAsync();
try {
    savePicker.SuggestedSaveFile = await StorageFile.GetFileFromPathAsync(result.Path);
} catch (Exception ex) {
    // Handling
}

```

After Change:
```cs
var openPicker = Microsoft.Windows.Storage.Pickers.FileOpenPicker(this.AppWindows.Id);
var savePicker = Microsoft.Windows.Storage.Pickers.FileSavePicker(this.AppWindows.Id);

var result = await openPicker.PickSingleFileAsync();
var isSuccess = savePicker.TrySetSuggestedSaveFilePath(result.Path);
if (!isSuccess)
{
    // Handling
}
```

### 2. If a legacy project is using a path from other sources

Before change:
```cs
var savePicker = Microsoft.Windows.Storage.Pickers.FileSavePicker(this.AppWindows.Id);
var suggestedPath = @"C:\temp\output.txt";

try {
    var suggestedFile = await StorageFile.GetFileFromPathAsync(suggestedPath);
    savePicker.SuggestedSaveFile = suggestedFile;
} catch (Exception ex) {
    // Handling 
}
```

After Change:
```cs
var savePicker = Microsoft.Windows.Storage.Pickers.FileSavePicker(this.AppWindows.Id);
var suggestedPath = @"C:\temp\output.txt";

var isSuccess = savePicker.TrySetSuggestedSaveFilePath(suggestedPath);
if (!isSuccess)
{
    // Handling
}
```

## Benefits

*   **Simplicity & Lightweight:** Provides a straightforward way to suggest a save location and file 
    name using a simple path string. Avoids the overhead of creating or passing a full `StorageFile` 
    objects where only the path is needed for the suggestion.

*   **Robustness:** Using a `TrySet` method allows the API to verify the existence of the provided 
    path and handle invalid inputs gracefully.

## History of Design Discussions

### 1. String Property vs Object Property

An alternative design involving a dedicated `SuggestedSaveFile` runtime class was considered and 
discussed at length. This approach would have involved creating an object to hold the path, with the 
primary motivation being future extensibility.

However, after discussion, the team decided against this in favor of the simpler `string` property 
for the following reasons:

*   **Broad Applicability:** Developers can provide a path from any source, not just from another 
    picker result. This makes the API flexible and easy to integrate into existing application logic.

*   **Decoupling:** It keeps the `FileSavePicker`'s suggestion mechanism decoupled from other types, 
    ensuring it remains a self-contained and straightforward feature.

*   **Improved Developer Experience:** Requiring developers to wrap a path string in an extra
    constructor or factory method adds boilerplate code. In contrast, a direct property assignment 
    (`savePicker.SuggestedSaveFilePath = filePath;`) is more intuitive and efficient for developers.

**Conclusion:** The `string SuggestedSaveFilePath` property was chosen as it provides a simpler, 
more direct API that meets the requirements without introducing the complexity of a new runtime 
class. 

This decision renders previous discussions about the `SuggestedSaveFile` class's ABI stability, 
constructors, factory patterns, and related interfaces obsolete.