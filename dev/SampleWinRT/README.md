# Adding a new WinRT Component

This directory is a sample of adding a WinRT component to Project Reunion.
WinRT-based APIs are defined using [MIDL3](https://docs.microsoft.com/en-us/uwp/midl-3/)
and typically [implemented with C++/WinRT](https://github.com/Microsoft/cppwinrt). It's
straightforward to add a new component in this manner.

## Adding the shared project

1. In Visual Studio, right-click the `dev` node in the Solution and choose "New Solution Folder"
2. Pick a name for your new project (the rest of this example uses `Muffins`)
3. Right-click the `Muffins` solution folder and use "Add > New Project"
4. Use the "Shared Items Project", set the name (`Muffins`)
4. For path use the solution root plus `\\dev` - the final path will be in `\\dev\\Muffins`

## Reference the project

1. Right-click the **ProjectReunion** project, use "Add > Reference"
2. Choose `Muffins` from the list of "Shared" items

## Add IDL and implementation

1. Right-click the shared project and use "Add > New Item"
2. From the Installed > Visual C++ > Code list, select "Midl File (.idl)"
3. Pick a good name (for the rest of this example, we'll use `Muffins` again, so "muffins.idl")
4. Remove the default `import ...` statements that visual studio generates

Follow the example of [SampleWinRT](./SampleWinRT.idl):

* Use `Microsoft.Muffins` as the namespace
* Add types and classes as necessary

Add a header and `.cpp` file and an implementation.

Be sure to add the copyright and license marker to all source files:

```c++
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
```

Add any C++/WinRT projected headers used by the implementation to
the [pch.h](../ProjectReunion_DLL/pch.h) to reduce compilation times.

## Testing

1. Add a new file to the [CppShared](../../test/CppShared/CppShared.vcxitems)
2. Follow the existing pattern of adding a `TEST_CLASS` with `TEST_METHOD` for facets of your implementation
3. Build the project and use the Visual Studio Test Explorer to run all tests

For very large surfaces with lots of tests, add a new directory under `test`
with its own shared items project.
