# One page design for `FileSavePicker.SuggestedSaveFilePath`


## 1. Overview

This document proposes a change to the `Microsoft.Windows.Storage.Pickers.FileSavePicker`. We aim to 
replace the `SuggestedSaveFile` property, which was of type `Windows.Storage.StorageFile`, with a 
new property `SuggestedSaveFilePath` of type `String`.

This change will allow for a more straightforward way to suggest a default file path, and reduce the
boilerplate code.

## 2. Background: Behavior of the original property `SuggestedSaveFile`

The `SuggestedSaveFile` property on the `FileSavePicker` dictates key aspects of the save file 
dialog's initial state:

*   **Initial Directory:** The dialog defaults to the directory of the `SuggestedSaveFile`. 

    This behavior overrides any picker-specific remembered folder settings and ensures the dialog 
    opens in the suggested file's parent folder.

*   **Pre-filled File Name:** The file name field in the dialog is pre-populated with the name of 
the `SuggestedSaveFile`. 

    This takes precedence over the `FileSavePicker.SuggestedFileName` property if both are set.

In essence, a string property `SuggestedSaveFilePath` is capable of providing a comprehensive hint 
for both the target save location (directory) and the proposed file name using a single string.

## 3. Proposed Changes

We propose the following:

1.  **Introduce `SuggestedSaveFilePath` Property:** A new `String` property on `FileSavePicker` that 
accepts a full file path.

1.  **Remove `SuggestedSaveFile` Property:** The existing `SuggestedSaveFile` property of type 
`Windows.Storage.StorageFile` will be removed.

## 4. Detailed Design

The `FileSavePicker` class will be updated to include the new property.

```cs
namespace Microsoft.Windows.Storage.Pickers {
    runtimeclass FileSavePicker {
        // ... other members
        String SuggestedSaveFilePath;
    }
}
```

## 5. Changes in Developers' Experience.

### 5.1 When Developers using the result returned by FileOpenPicker

Before Change:
```cs
var openPicker = Microsoft.Windows.Storage.Pickers.FileOpenPicker(this.AppWindows.Id);
var savePicker = Microsoft.Windows.Storage.Pickers.FileSavePicker(this.AppWindows.Id);

var file = await openPicker.PickSingleFileAsync();
savePicker.SuggestedSaveFile = await StorageFile.GetFileFromPathAsync(file.Path);
```

After Change:
```cs
var openPicker = Microsoft.Windows.Storage.Pickers.FileOpenPicker(this.AppWindows.Id);
var savePicker = Microsoft.Windows.Storage.Pickers.FileSavePicker(this.AppWindows.Id);

var file = await openPicker.PickSingleFileAsync();
savePicker.SuggestedSaveFilePath = file.Path;
```

### 5.2 If a legacy project is using a path from other sources

Before change:
```cs
var suggestedPath = @"C:\temp\Output.txt"

var suggestedFile = await StorageFile.GetFileFromPathAsync(suggestedPath);

var savePicker = Microsoft.Windows.Storage.Pickers.FileSavePicker(this.AppWindows.Id);
savePicker.SuggestedSaveFile = suggestedFile;
```

After Change:
```cs
var suggestedPath = @"C:\temp\Output.txt"

var savePicker = Microsoft.Windows.Storage.Pickers.FileSavePicker(this.AppWindows.Id);
savePicker.SuggestedSaveFilePath = suggestedPath;
```


## 6. Benefits

*   **Simplicity:** Provides a straightforward way to suggest a save location and file name using a 
    simple path string.

*   **Lightweight:** Using a path string avoids the overhead of creating or passing a full 
    `StorageFile` objects where only the path is needed for the suggestion.

*   **Clear Semantics:** The property name `SuggestedSaveFilePath` clearly indicates its purpose 
    and type.


## 7. History of Design Discussions

### 7.1 String Property vs Object Property

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

### 7.2 [obsolete] ABI Stability: Adding Constructors and Members to Runtime Classes

The primary concern is understanding the Application Binary Interface (ABI) implications of evolving 
a runtime class.

*   **Adding Constructors/Members:**
    
    *   **Initial Question:** 
    Would adding new constructors or members to an existing class in the future lead to ABI 
    breaking changes?
    
    *   **Feedback (Jon):** 
    Adding new constructors or members is **not** an ABI breaking change **if done correctly using 
    contract versioning**. For example, update `[contractversion()]` for the type (e.g., to "2") 
    and mark the new member with 
    ```cs
    [contract(MyNewContract, 2)]
    MyNewClass(NewParameter name);
    ```

*   **Future Constructor Overloading:**

    *   **Initial Question:** 
    If we create the runtimeclass with constructor `SuggestedSaveFile(String Path)`, what's the best
    practice to add more constructor (e.g. `SuggestedSaveFile(StorageFile storageFile)`) in future?
    
    *   **Feedback (Jon):** 
        WinRT APIs typically avoid overloading constructors or methods based on parameter *types* 
        due to compatibility issues with languages like JavaScript, which do not have strong typing 
        in the same way. 
        Overloading based on the *number* of parameters is preferred if overloading is necessary.
    
    *   **Consideration:** 
        In this context, the factory method pattern is superior to constructor overloading because 
        it produces a more explicit and language-agnostic API, circumventing the WinRT guideline 
        against overloading on parameter types.

        For `SuggestedSaveFile`, if future inputs are needed (e.g., to accept a `StorageFile`), 
        we can add new factory methods instead of another constructor also takes one parameter.

*   **Example Scenario Revisited:**

    *   **Version 1 (e.g., SDK 1.8.4, Contract v1):**
        ```cs
        [contractversion(MyNewContract, 1)]
        runtimeclass MyNewClass {

            // Internal/private constructor

            [contract(MyNewContract, 1)]
            static MyNewClass CreateFromString(String inputString);
        }
        ```

    *   **Potential Future Version (e.g., SDK 1.8.5, Contract v2):**
        ```cs
        [contractversion(MyNewContract, 2)] // Assuming contract version is incremented
        runtimeclass MyNewClass {
            
            // Internal/private constructor

            [contract(MyNewContract, 1)]
            static MyNewClass CreateFromString(String inputString);
            
            [contract(MyNewContract, 2)]   // New static method
            static MyNewClass CreateFromObj(Windows.Storage.StorageFile obj);

            [contract(MyNewContract, 2)] // Example new property to add in future
            String SomeNewProperty { get; };
        }
        ```
    Expect: With contract versioning, applications built against SDK 1.8.4 (Contract v1) should 
    continue to work with an updated SDK providing Contract v2, as they're only seeing v1 members. 
    Applications built against SDK 1.9 can use v2 members.

### 7.3 [obsolete] Discussion on the Potential of Using an Interface

*   **7.3.1 Abstraction Strategy: Interface vs. Runtime Class**

    *   **[deprecated] Initial Proposal:** 
        An interface (`ISuggestedSaveFile`) was considered for extensibility (e.g., supporting 
        `StorageFile`-based suggestions later) and potential ABI stability benefits.

        ```cs
        // Original interface idea (deprecated)
        interface ISuggestedSaveFile {
            String Path { get; };
        }
        
        runtimeclass MyNewClass : ISuggestedSaveFile {
            SuggestedSaveFile(String path);
        }
        
        runtimeclass FileSavePicker {
            // ... other members
            ISuggestedSaveFile SuggestedSaveFile;
        }
        ```

    *   **Feedback (Jon):** 
        In WinRT, interfaces are typically used for "polymorphic" types, especially as *input* 
        parameters to methods (e.g., `IInputStream`). Returning a new object as an interface can be 
        awkward if the object needs to add new properties/methods over time, as interfaces are 
        **generally immutable** once defined. It's more common to return a runtime class (which is 
        a collection of interfaces projected to look like a single type), as this allows for easier 
        evolution by adding new interfaces (and thus members) to the class in future versions.
    
    *   **Conclusion:** 
        It is simpler to use a direct runtime class the preferred WinRT design, and to rely on 
        contract versioning for future evolution. 
    
        However, using a simple string property is the most direct approach, avoiding the 
        complexities of both interfaces and dedicated runtime classes.

*   **7.3.2 Type Recovery (Relevant if an interface were used and multiple implementations existed)**

    *   **Original Question:** 
        If a new property returned an interface type, how could consumers safely recover the 
        underlying concrete type?

    *   **Feedback (Antonio):** 
        For C++/WinRT, use `.as<T>()` or `.try_as<T>()` for safe interface querying/casting, 
        not C-style casts or `dynamic_cast`. C# uses `as` or pattern matching.

    *   **Conclusion:** 
        This point is moot for this feature now, as the final design uses a simple string property 
        (`SuggestedSaveFilePath`) instead of an class or interface. 
        However, the information is useful for general WinRT interface programming.
