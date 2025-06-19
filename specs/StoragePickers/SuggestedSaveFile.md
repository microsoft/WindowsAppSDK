# One page design for `FileSavePicker.SuggestedSaveFile`


## 1. Overview

This document proposes a change to the `Microsoft.Windows.Storage.Pickers.FileSavePicker.SuggestedSaveFile` 
property. We aim to change its current type from the UWP `StorageFile` to a new class, 
`SuggestedSaveFile`. This new class will be created via a static factory method and will not expose 
the public `Path` property.

This change will allow for more light-weight objects.

## 2. Background: Behavior of `SuggestedSaveFile`

The `SuggestedSaveFile` property on the `FileSavePicker` dictates key aspects of the save file 
dialog's initial state:

*   **Initial Directory:** The dialog defaults to the directory of the `SuggestedSaveFile`. 

    This behavior overrides any picker-specific remembered folder settings and ensures the dialog 
    opens in the suggested file's parent folder.

*   **Pre-filled File Name:** The file name field in the dialog is pre-populated with the name of 
the `SuggestedSaveFile`. 

    This takes precedence over the `FileSavePicker.SuggestedFileName` property if both are set.

In essence, `SuggestedSaveFile` provides a comprehensive hint for both the target save location 
(directory) and the proposed file name. 

The file's full path, provided when creating the `SuggestedSaveFile` object via its static factory 
method, contains all the necessary information (directory and file name) for the picker to implement 
these behaviors internally.

## 3. Proposed Changes

We propose the following:

1.  **Introduce `SuggestedSaveFile` Class:** A new class to represent a suggested save file, 
    which is created using a static factory method that accepts a file path string. The path is 
    encapsulated and not exposed as a public property.

1.  **Update `FileSavePicker`:** Change the type of the `SuggestedSaveFile` property from 
    `Windows.Storage.StorageFile` to `Microsoft.Windows.Storage.Pickers.SuggestedSaveFile`.

## 4. Detailed Design

The `SuggestedSaveFile` class will provide the necessary information for a suggested save file.

```cs
namespace Microsoft.Windows.Storage.Pickers {
    // Constructor is not public
    runtimeclass SuggestedSaveFile {
        static SuggestedSaveFile CreateFromPath(String path);
    }

    runtimeclass FileSavePicker {
        // ... other members
        SuggestedSaveFile SuggestedSaveFile;
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
savePicker.SuggestedSaveFile = SuggestedSaveFile.CreateFromPath(file.Path);  // a light-weight object
```

### 5.2 If a legacy project is using StorageFile consturcted by other UWP methods

Before change:
```cs
var suggestedPath = @"C:\temp\Output.txt"

var suggestedFile = await StorageFile.GetFileFromPathAsync(of.Path);

var savePicker = Microsoft.Windows.Storage.Pickers.FileSavePicker(this.AppWindows.Id);
savePicker.SuggestedSaveFile = suggestedFile;
```

After Change:
```cs
var suggestedPath = @"C:\temp\Output.txt"

var suggestedFile = SuggestedSaveFile.CreateFromPath(suggestedPath);  // a light-weight object

var savePicker = Microsoft.Windows.Storage.Pickers.FileSavePicker(this.AppWindows.Id);
savePicker.SuggestedSaveFile = suggestedFile;
```


## 6. Benefits

*   **Simplicity:** Provides a straightforward way to suggest a save location and file name using 
a simple path string passed to a static factory method.
*   **Lightweight:** Using a path-based suggestion avoids the overhead of creating or passing 
full `StorageFile` objects where only the path is needed for the suggestion.
*   **Clear Semantics:** The static factory method clearly indicates the primary piece of information 
for the suggestion while keeping implementation details encapsulated.

## 7. Design Discussions

### 7.1 Rationale for the Path-Based SuggestedSaveFile and Decoupling from `PickFileResult`

While the new `Microsoft.Windows.Storage.Pickers.FileOpenPicker` also returns a lightweight 
`PickFileResult` with `Path` property, we are **NOT** making `FileSavePicker.SuggestedSaveFile` 
directly consume this type. 
Instead, we introduce the `SuggestedSaveFile` class that can be constructed from a file path string. 
The reasons for this approach are:

*   **Broad Applicability:** Many legacy and existing applications construct or obtain file paths 
through various means, not solely from a `FileOpenPicker` interaction. This includes using UWP APIs 
like `StorageFile.GetFileFromPathAsync`, `StorageFolder.CreateFileAsync`, which are not yet 
implemented in the `Microsoft.Windows.Storage.Pickers` namespace. 

    A path-based mechanism - `SuggestedSaveFile.CreateFromPath(filePathString)` - offers maximum 
flexibility for developers to provide a suggestion regardless of how they obtained the path.

*   **Decoupling:** `PickFileResult` and `SuggestedSaveFile` serve distinct purposes. 
`PickFileResult` represents the outcome of a file *open* operation, which has different semantics 
and requirements than a *suggestion* for a file *save* operation. 

    By accepting a simple path via `SuggestedSaveFile`, we keep the `FileSavePicker`'s suggestion 
mechanism straightforward and decoupled from the specifics of how a file was previously opened or 
selected. 

*   **Future Divergence:** Forcing `PickFileResult` to conform to the structure of 
`SuggestedSaveFile` could become problematic if `SuggestedSaveFile` evolves with requirements not 
suitable for `PickFileResult` (e.g., specific metadata fields relevant only to saving). Keeping them 
separate ensures both can evolve independently. 


## 8. Open Discussions and Their History

This section consolidates questions and discussion points based on internal feedback, including ABI 
stability, versioning, and appropriate abstraction and design mechanisms in WinRT for the 
`SuggestedSaveFile` type.

### 8.1 ABI Stability: Adding Constructors and Members to Runtime Classes

The primary concern is understanding the Application Binary Interface (ABI) implications of evolving 
a runtime class.

*   **Adding Constructors/Members:**
    
    *   **Initial Question:** 
    Would adding new constructors or members to `SuggestedSaveFile` in the future lead to ABI 
    breaking changes?
    
    *   **Feedback (Jon):** 
    Adding new constructors or members is **not** an ABI breaking change **if done correctly using 
    contract versioning**. For example, update `[contractversion()]` for the type (e.g., to "2") 
    and mark the new member with 
    `[contract(FileSavePickerContract, 2)] SuggestedSaveFile(NewParameter name);`.
    
    *   **Follow-up Question [TODO]:** 
    Does this contract versioning approach fully mitigate runtime issues for non-self-contained apps 
    if the SDK is updated with such non-breaking additions (e.g., in a **minor/patch** update), 
    or does it must be changed in a **new major version**?

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
        [contractversion(FileSavePickerContract, 1)]
        runtimeclass SuggestedSaveFile {

            // Internal/private constructor

            [contract(FileSavePickerContract, 1)]
            static SuggestedSaveFile CreateFromPath(String path);
        }
        ```

    *   **Potential Future Version (e.g., SDK 1.8.5, Contract v2):**
        ```cs
        [contractversion(FileSavePickerContract, 2)] // Assuming contract version is incremented
        runtimeclass SuggestedSaveFile {
            
            // Internal/private constructor

            [contract(FileSavePickerContract, 1)]
            static SuggestedSaveFile CreateFromPath(String path);
            
            [contract(FileSavePickerContract, 2)]   // New static method
            static SuggestedSaveFile CreateFromStorageFile(Windows.Storage.StorageFile storageFile);

            [contract(FileSavePickerContract, 2)] // Example new property to add in future
            String SomeNewProperty { get; };
        }
        ```
    Expect: With contract versioning, applications built against SDK 1.8.4 (Contract v1) should 
    continue to work with an updated SDK providing Contract v2, as they're only seeing v1 members. 
    Applications built against SDK 1.9 can use v2 members.

### 8.2 About the Design of runtimclass `SuggestedSaveFile` 

This section discusses the optimal design for `SuggestedSaveFile` itself.

*   **8.2.1 the Alternatives:** 
    What is the most appropriate way to instantiate and populate `SuggestedSaveFile`?

    Options:
    1.  ~~Constructor taking a path.~~ (not chosen)
    1.  ~~Default constructor with a read/write `Path` property.~~ (not chosen)
    1.  **Static factory methods on `SuggestedSaveFile` itself 
        (e.g., `SuggestedSaveFile.CreateFromPath(string)`). (This is the chosen approach)**

*   **8.2.2 `SuggestedSaveFile.CreateFromPath`**

    *   **Current Design:**
        In this design, we're adopting the 3rd option - static factory methods:
        ```cs
        runtimeclass SuggestedSaveFile {
            // Constructor is not public
            static SuggestedSaveFile CreateFromPath(String path);
        }
        ```

*   **8.2.3 Rationale for Encapsulating the Path Property**

    The Path property is encapsulated to ensure predictable behavior and maintains architectural 
    flexibility for future enhancements.

    1. Future Extensibility 
    
        Exposing Path could create conflicts when future file representation properties are added. 
        For instance, if in future a `StorageFile` property is added, and both the `Path` and the 
        `StorageFile` values coexist, developers would face ambiguity on which path is authoritative, 
        leading to inconsistent behavior.
        
        The encapsulation enables distinct creation pathways through static factory methods, 
        preventing mixed-mode initialization that could compromise object integrity.

    1. Simplified API Surface 
    
        Removing the Path property reduces cognitive overhead and potential misuse while 
        maintaining full functionality.

*   **8.2.4 Accessing Internal State from the Implementation**

    **[TODO] Problem:** 
    The `SuggestedSaveFile` object is created by the developer (e.g., in C#) and passed back to our 
    C++ SDK. Since the `Path` property is not exposed in the ABI, how can our C++ implementation 
    retrieve the path value from the `SuggestedSaveFile` object it receives? 
    In other words, how do we convert the `SuggestedSaveFile` object received from WinRT back to the 
    internal object that can access the private path value?

### 8.3 Overall API Usability

*   **Broad Applicability:** 
    The goal is to support developers who obtain paths from various sources (not just from results 
    of `FileOpenPicker`). A path-centric `SuggestedSaveFile` aims for this.

*   **Alignment with WinRT Best Practices:** 
    This design aims to ensure the final design aligns with established WinRT API design principles 
    for evolvability, usability, and ABI compatibility.


### 8.4 [Deprecated] Discussion on the Potential of Using an Interface

*   **8.4.1 Abstraction Strategy: Interface vs. Runtime Class**

    *   **[deprecated] Initial Proposal:** 
        An interface (`ISuggestedSaveFile`) was considered for extensibility (e.g., supporting 
        `StorageFile`-based suggestions later) and potential ABI stability benefits.

        ```cs
        // Original interface idea (deprecated)
        interface ISuggestedSaveFile {
            String Path { get; };
        }
        
        runtimeclass SuggestedSaveFile : ISuggestedSaveFile {
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
        It is simpler to use a direct runtime class `SuggestedSaveFile` (without a preceding 
        `ISuggestedSaveFile` for the property type) the preferred WinRT design, and to rely on 
        contract versioning for future evolution. 

*   **8.4.2 Type Recovery (Relevant if an interface were used and multiple implementations existed)**

    *   **Original Question:** 
        If `FileSavePicker.SuggestedSaveFile` returned an `ISuggestedSaveFile`, how could consumers 
        safely recover the underlying concrete type?

    *   **Feedback (Antonio):** 
        For C++/WinRT, use `.as<T>()` or `.try_as<T>()` for safe interface querying/casting, 
        not C-style casts or `dynamic_cast`. C# uses `as` or pattern matching.

    *   **Conclusion:** 
        This point is less critical if `SuggestedSaveFile` is returned directly as a runtime class, 
        but good to note for general WinRT interface usage.
