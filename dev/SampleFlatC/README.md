# Adding a new Flat C API Component

This directory is a sample of adding an API with a "flat C" style to Project Reunion.
Flat C APIs define an ABI using C-based headers exported from a DLL. Apps can use the
APIs from an import library or through a projection that applies a wrapper.

## Adding the shared project

1. In Visual Studio, right-click the `dev` node in the Solution and choose "New Solution Folder"
2. Pick a name for your new project (the rest of this example uses `Muffins`)
3. Right-click the `Muffins` solution folder and use "Add > New Project"
4. Use the "Shared Items Project", set the name (`Muffins`)
4. For path use the solution root plus `\\dev` - the final path will be in `\\dev\\Muffins`

## Reference the project

1. Right-click the **ProjectReunion** project, use "Add > Reference"
2. Choose `Muffins` from the list of "Shared" items

## Add public header

1. Right-click the shared project and use "Add > New Item"
2. From the "Installed > Visual C++ > Code" list, select "Header (.h)"
3. Pick a good name (for the rest of this example, we'll use `Muffins` again, so "muffins.h")
5. Define the ABI for the implementation

Follow the example of [SampleFlatC](./SampleFlatC.h):

* Use `STDAPI` and `STDAPI_(type)` to define entrypoints
* Use scoped enumerations (like `enum class`) instead of preprocessor definitions

## Add implementation

1. Add `.cpp` files that implement the APIs in the usual way
2. For code using C++-with-exceptions use an appropriate exception guard

## Publish header

1. In the `.vcxitems` for the new project, manually add something like this, per [SampleFlatC.vcxitems](./SampleFlatC.vcxitems)

```xml
<!-- Include this header in the set being published for use with the DLL -->
<ItemGroup>
  <PublicHeaders Include="$(MSBuildThisFileDirectory)SampleFlatC.h"/>
</ItemGroup>
```

## Adding exports

1. In [ProjectReunion.def](../ProjectReunion_DLL/ProjectReunion.def) add the list of exported methods

## Other notes

Be sure to add the copyright and license marker to all source files:

```c++
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
```
