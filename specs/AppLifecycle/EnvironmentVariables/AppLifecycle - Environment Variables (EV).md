# AppLifecycle - Environment Variables

The AppLifecycle component provides a core set of functionality related to app
activation and lifecycle. The primary purpose is to provide a single consistent
set of APIs that any type of app can use. In some cases, this means combining
and rationalizing multiple existing APIs (from both classic Win32 and from WinRT)  
into a new Reunion class.

Environment variables is one example, where there are several existing APIs 
that provide partially overlapping functionality, and with some gaps. This spec
describes the Reunion support for environment variables.

Important Note: The EV tracking feature relies on other platform features which are only
available from Windows 21H1+ (i.e. version >=10.0.19043.0). An app can check the 
IsChangeTrackingSupported property to determine whether Environment manager will track EV changes.


Note that there are existing Win32 and .NET APIs that cover much of the same 
behaviors as the new APIs. The only _net_ _new_ behaviors are:

1. One single set of Environment-specific APIs that all app types can use.

2. The ability to track variables so that they can be cleaned up (reverted or
   removed) when apps are uninstalled (on a "best effort" basis).

3. The ability for a UWP app to read at Machine scope without having to p/invoke
   to a native API, and to read at User scope without using registry APIs.



## Background

The proposed new WinRT API gets and sets environment variables for the current
process, the current user, or the local machine, with tracking support for
restoring a previous value or deleting the variable when an app is uninstalled.
This API will be callable from packaged and unpackaged apps.

Many traditional applications rely on environment variables - including
variables that are created and updated by the app. In some cases the variable is
only used by the creating app; in other cases it needs to be visible to other
apps or to the platform itself. However, there’s no formal mechanism for the
platform to remove the variables when an application is removed – instead, we
rely on the app’s own uninstall behavior. For MSIX packaged apps, there is no
(generally available) custom uninstall mechanism. Both cases can result in
redundant variables left behind when an app is uninstalled.

The new API adds tracking of environment variables, which covers 2 cases:

- When an app creates a variable, and the app is later uninstalled, that
  variable can be deleted.

- When an app doesn't create a variable, but instead modifies an existing
  variable, and the app is later uninstalled, the previous value of the variable
  is restored.

## Description

### New types

This API will provide one new class with the following members. Note that the ability
for the caller to read/write environment variables (including PATH and PATHEXT)
depends on the type of app, and the scope of the variable (see Security and
permissions section below).

**class EnvironmentManager** - new class for reading and writing environment variables.

- **static EnvironmentManager GetForProcess** - returns an EnvironmentManager
  scoped to the current process.
- **static EnvironmentManager GetForUser** - returns an EnvironmentManager scoped
  to the current user.
- **static EnvironmentManager GetForMachine** - returns an EnvironmentManager at
  system-wide scope.
- **static bool IsSupported { get; }** - readonly property that indicates whether this
  API is supported on the current device/OS version.
- **bool IsChangeTrackingSupported { get;}** - readonly property that indicates whether the EV changes will be tracked.
- **IMapView<string, string> GetEnvironmentVariables** - gets a collection of
  environment variables at the scope of the current EnvironmentManager.
- **string GetEnvironmentVariable(string)** - gets the value of the specified
  environment variable at the scope of the current EnvironmentManager.

- **void SetEnvironmentVariable(string, string)** - sets the value of the
  specified environment variable at the scope of the current EnvironmentManager.
- **void AppendToPath(string)** - adds the specified path to the end of the PATH
  variable.
- **void RemoveFromPath(string)** - removes the specified path from the end of
  the PATH variable.
- **void AddExecutableFileExtension(string)** - adds the specified file
  extension to the end of the PATHEXT variable.
- **void RemoveExecutableFileExtension(string)** - removes the specified file
  extension from the end of the PATHEXT variable.

### Tracking

The API adds tracking of environment variables, which is used to cleanly
uninstall environment artifacts written by the app. Tracking also enables
restoration of previously written tracked variables when an app is uninstalled.

For packaged apps, a variable that is created or modified with the new API will
be tracked. Variables that are not created or modified with the new API continue
not to be tracked.

The platform can track uninstall for packaged apps, but not for unpackaged apps.
For unpackaged apps, we rely on the app's own uninstaller to clean up
environment variables, if it wants to. An unpackaged app can provide its own
cleanup on uninstall, by calling the SetEnvironmentVariable API with an empty
string for the value, or RemoveFromPath - but this would remove the variable, it
would not revert it to its previous state.

Notes:

- We will not set up a registry listener, so the only way we know if something
  changed is if the caller uses the new API to create or modify the variable, or
  if an app that has done so is now uninstalled.
- We won’t track changes that are made outside the API; and we won’t track
  uninstall of unpackaged apps.
- When a packaged app is uninstalled, any variable it created will be deleted,
  regardless of any other changes made to that variable during its lifetime.
- If a variable was not created via the new API, then it will not be deleted
  when a packaged app is uninstalled – instead, the last change made by that app
  (via the new API) will be reverted.
- A-la-carte apps have identity but are not installed the way packaged apps are
  installed. We have no reliable way to detect when an a-la-carte app is
  uninstalled. Therefore, while a variable created/written by an a-la-carte app
  will be tracked, it will not be cleaned up when the app is uninstalled.
- As a special case, the PATH and PATHEXT variables will have additional API
  surface for adding and removing values.
- For a later release, we can consider adding a corresponding appxmanifest way
  of setting environment variables, which is more declarative, and provides a
  way of having the variables set at first launch for applications that expect
  them to exist (again, either for the current process, current user or local
  machine). The manifest approach is not part of the current proposal.
- For a later release, we can consider providing a way for changes made by
  unpackaged apps to be tracked and cleaned up fully. This is not part of the
  current proposal.

### Variable removal and restore

When uninstalling a package, environment cleanup and restoration is triggered.

1. Any variables created by the app are deleted.
2. Where a variable was not originally created by the app, but was last modified
   by the app, its value will be restored to the last value set by another app.
3. Variable changes made by mechanisms other than using these APIs (eg, 
   the user making manual changes via RegEdit) will be accounted for.

Note that an app setting a variable to an empty string is effectively “remove
this variable” and so no new value should be set.

Example sequences in the table below. 

| Case | Packaged App A                   | Packaged App B       | Unpackaged App/User              | Var Value                |
| ---- | -------------------------------- | -------------------- | -------------------------------- | ------------------------ |
| 1    | Creates variable, sets it to "A" |                      |                                  | A                        |
|      | App A is uninstalled             |                      |                                  | [deleted]                |
|      |                                  |                      |                                  |                          |
| 2    | Creates variable, sets it to "A" |                      |                                  | A                        |
|      |                                  | Sets it to "B"       |                                  | B                        |
|      | App A is uninstalled             |                      |                                  | B                        |
|      |                                  | App B is uninstalled |                                  | [deleted]                |
|      |                                  |                      |                                  |                          |
| 3    | Creates variable, sets it to "A" |                      |                                  | A                        |
|      |                                  | Sets it to "B"       |                                  | B                        |
|      |                                  | App B is uninstalled |                                  | A                        |
|      | App A is uninstalled             |                      |                                  | [deleted]                |
|      |                                  |                      |                                  |                          |
| 4    | Creates variable, sets it to "A" |                      |                                  | A                        |
|      |                                  |                      | Sets it to "U"                   | U                        |
|      | App A is uninstalled             |                      |                                  | [deleted]                |
|      |                                  |                      |                                  |                          |
| 5    |                                  |                      | Creates variable, sets it to "U" | U                        |
|      | Sets it to "A"                   |                      |                                  | A                        |
|      | App A is uninstalled             |                      |                                  | U                        |
|      |                                  |                      |                                  |                          |
| 6    |                                  |                      | Creates variable, sets it to "U" | U                        |
|      | Sets it to "A"                   |                      |                                  | A                        |
|      |                                  | Sets it to "B"       |                                  | B                        |
|      |                                  | App B is uninstalled |                                  | A                        |
|      | App A is uninstalled             |                      |                                  | U                        |
|      |                                  |                      |                                  |                          |
| 7    |                                  |                      | Creates variable, sets it to "U" | U                        |
|      | Sets it to "A"                   |                      |                                  | A                        |
|      |                                  | Sets it to "B"       |                                  | B                        |
|      |                                  | App B is uninstalled |                                  | A                        |
|      |                                  |                      | Sets it to "V"                   | V                        |
|      | App A is uninstalled             |                      |                                  | V                        |
|      |                                  |                      |                                  |                          |
| 8    | Creates variable, sets it to "A" |                      |                                  | A                        |
|      |                                  | Sets it to "B"       |                                  | B                        |
|      | Sets it to "" (empty string)     |                      |                                  | [deleted]                |
|      | App A is uninstalled             |                      |                                  | B                        |
|      |                                  |                      |                                  |                          |
| 9    | Creates variable, sets it to "A" |                      |                                  | A                        |
|      |                                  |                      | Sets it to "U"                   | U                        |
|      |                                  |                      | Unpackaged app is uninstalled    | U                        |
|      |                                  |                      |                                  |                          |
| 10   |                                  |                      | PATH=A;B                         | A;B                      |
|      | Append("C")                      |                      |                                  | A;B;C                    |
|      |                                  |                      | User prepends "C"                | C;A;B;C                  |
|      | Remove("C")                      |                      |                                  | C;A;B                    |
|      |                                  |                      |                                  |                          |
| 11   |                                  |                      | PATH=A;B                         | A;B                      |
|      | Append("C")                      |                      |                                  | A;B;C                    |
|      |                                  |                      | User inserts "C"                 | A;C;B;C                  |
|      | Remove("C")                      |                      |                                  | A;C;B                    |
|      |                                  |                      |                                  |                          |
| 12   |                                  |                      | PATH=A;B                         | A;B                      |
|      | Append("C")                      |                      |                                  | A;B;C                    |
|      |                                  |                      | User removes "C"                 | A;B                      |
|      | Remove("C") (fails)              |                      |                                  | A;B                      |
|      | App A is uninstalled             |                      |                                  | A;B                      |
|      |                                  |                      |                                  |                          |
| 13   |                                  |                      | PATH=A;B;C                       | A;B;C                    |
|      | Remove("B")                      |                      |                                  | A;C                      |
|      | App A is uninstalled             |                      |                                  | A;B;C                    |
|      |                                  |                      |                                  |                          |
| 14   |                                  |                      | PATH=A;B;C                       | A;B;C                    |
|      | Remove("B")                      |                      |                                  | A;C                      |
|      |                                  |                      | User inserts "D"                 | A;D;C                    |
|      | App A is uninstalled             |                      |                                  | A;B;D;C                  |
|      |                                  |                      |                                  |                          |
| 14   |                                  |                      | PATH=A;B                         | A;B                      |
|      | Add("C")                         |                      |                                  | A;B;C                    |
|      |                                  | Remove("C")          |                                  | A;B                      |
|      | App A is uninstalled             |                      |                                  | A;B                      |
|      |                                  |                      |                                  |                          |
| 15   |                                  |                      | PATHEXT=.COM;.EXE;.BAT           | .COM;.EXE;.BAT           |
|      | Add(".FOO")                      |                      |                                  | .COM;.EXE;.BAT;.FOO      |
|      | App A is uninstalled             |                      |                                  | .COM;.EXE;.BAT           |
|      |                                  |                      |                                  |                          |
| 16   |                                  |                      | PATHEXT=.COM;.EXE;.BAT           | .COM;.EXE;.BAT           |
|      | Add(".FOO")                      |                      |                                  | .COM;.EXE;.BAT;.FOO      |
|      |                                  | Add(".FOO")          |                                  | .COM;.EXE;.BAT;.FOO;.FOO |
|      |                                  |                      | User removes ".FOO"              | .COM;.EXE;.BAT;.FOO      |
|      |                                  |                      | User inserts ".FOO"              | .COM;.FOO;.EXE;.BAT;.FOO |
|      |                                  | Remove(".FOO")       |                                  | .COM;.FOO;.EXE;.BAT      |
|      | App A is uninstalled             |                      |                                  | .COM;.EXE;.BAT           |
|      |                                  |                      |                                  |                          |
| 17   |                                  |                      | PATH=A;B;C                       | A;B;C                    |
|      | Add("D")                         |                      |                                  | A;B;C;D                  |
|      |                                  | Add("E")             |                                  | A;B;C;D;E                |
|      | Add("F")                         |                      |                                  | A;B;C;D;E;F              |
|      | App A is uninstalled             |                      |                                  | A;B;C;E                  |



### PATH and PATHEXT

The PATH and PATHEXT variables have special treatment to allow us to _append_
values, which are tracked like normal environment variables set through the API.
If an app adds a value to PATH, and the app is later uninstalled, then the value
will be removed from PATH. If an app removes a value from the PATH, and the
app is later uninstalled, then the value will be restored. Similar behavior applies 
to PATHEXT. PATH and PATHEXT are the only environment variables for which we 
track fragmentary values.

We will not check that the new value is a valid path. Even prior to this new
API, the PATH's value is never validated by any mechanism, although an invalid
value in the PATH can result in failure when the PATH is used.

In addition, the new API also includes the ability to remove items from the
PATH. An app can remove any element, regardless of whether the app originally
added that element.

For the initial release, we will provide an API that only enable apps to append
to the PATH. In this release, we will not enable any other modification of the PATH.

During removal, in the case of values that appear multiple times in the PATH,
only the last instance of the value will be removed. That is, the last instance
as it occurs in the string, not necessarily the "last" in the chronological
sense.

Note about casing: although variable names are treated as case-insensitive,
values are treated as case-sensitive, except for the values added to the PATH
and PATHEXT. Comparison of path values will be case-insensitive.

### Security and permissions

There are 3 scopes for writing environment variables, **Process**, **User**, and
**System**. Setting a **Process** variable only affects the current process.
Setting a **User** or **System** variable will persist that variable beyond the
life of the process in the user profile or system profile.

Unpackaged apps can use the existing native Win32 [GetEnvironmentVariable](https://docs.microsoft.com/windows/win32/api/winbase/nf-winbase-getenvironmentvariable)/
[SetEnvironmentVariable](https://docs.microsoft.com/windows/win32/api/winbase/nf-winbase-setenvironmentvariable) and
registry APIs. Unpackaged .NET apps can use [System.Environment](https://docs.microsoft.com/dotnet/api/system.environment?view=net-6.0) class, and
specifically the methods [GetEnvironmentVariable](https://docs.microsoft.com/dotnet/api/system.environment.getenvironmentvariable?view=net-6.0), 
[GetEnvironmentVariables](https://docs.microsoft.com/dotnet/api/system.environment.getenvironmentvariables?view=net-6.0)
and [SetEnvironmentVariable](https://docs.microsoft.com/dotnet/api/system.environment.setenvironmentvariable?view=net-6.0).

Environment variables are stored in the registry here:

- User: HKEY_CURRENT_USER\Environment

- Machine: HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session
  Manager\Environment

Note: to update the user-scoped list of variables we need to write to the
registry and cause Shell to refresh its cache. This will be done using an
existing public WNF notification.

### Errors

The methods in this API may throw exceptions in some cases, as follows:

- **ArgumentNullException**: the provided variable is null.

- **ArgumentException**: the provided variable contains a zero-length string, an
  initial hexadecimal zero character (0x00), or an equal sign ("="). Or the
  length of variable or value is greater than or equal to 32,767 characters. Or
  an error occurred during the execution of this operation.

- **SecurityException**: the caller does not have the required permission to
  perform this operation.

## Examples

### Get environment variables

To get an environment variable, use the GetEnvironmentVariable API. Specify the
scope (Process, User, or System) when getting an environment manager instance.
For at least the initial release, we only support getting user-scoped variables
for the current user, not for any other user.

```c++
// Get environment variables at the process-local level.
static void GetVariableInProcess()
{
    // Check first to see if this API is supported on this device/OS.
    if (EnvironmentManager.IsSupported)
    {
        var environment = EnvironmentManager.GetForProcess();
        var PROGRAM_MEMORY = environment.GetEnvironmentVariable("PROGRAM_MEMORY");
        Console.WriteLine($"PROGRAM_MEMORY is {PROGRAM_MEMORY}");
    }
}

// Get environment variables for the current user.
static void GetVariableInUserProfile()
{
    if (EnvironmentManager.IsSupported)
    {
        var environment = EnvironmentManager.GetForCurrentUser();
        var HOMEDIR = environment.GetEnvironmentVariable("HOMEDIR");
        Console.WriteLine($"HOMEDIR is {HOMEDIR}");
    }
}

// Get system-wide environment variables.
static void GetVariableInSystem()
{
    if (EnvironmentManager.IsSupported)
    {
        var environment = EnvironmentManager.GetForMachine();
        var windir = environment.GetEnvironmentVariable("windir");
        Console.WriteLine($"windir is {windir}");
    }
}

// Get all environment variables at a particular level.
static void GetAllVariablesInProcess()
{
    if (EnvironmentManager.IsSupported)
    {
        var environment = EnvironmentManager.GetForProcess();
        foreach (var envVar in environment.GetEnvironmentVariables())
        {
            Console.WriteLine($"Found variable '{envVar.Key}' with value '{envVar.Value}'");
        }
    }
}
```

### Set environment variables

To set an environment variable, use the SetEnvironmentVariables API. Specify the
scope (Process, User, or System) when getting an environment manager instance.
To remove a variable, pass **null** for the value.

```c++
// Environment variables set at the process level will persist
// only until the process terminates.
static void SetVariableInProcess()
{
    if (EnvironmentManager.IsSupported)
    {
        var environment = EnvironmentManager.GetForProcess();
        environment.SetEnvironmentVariable("PROGRAM_MEMORY", "1024");

        // Use the Get function to check the variable we just set.
        var PROGRAM_MEMORY = environment.GetEnvironmentVariable("PROGRAM_MEMORY");
        Console.WriteLine($"PROGRAM_MEMORY is {PROGRAM_MEMORY}");
    }
}

// Environment variables set at the user or machine level will
// persist until the app package is uninstalled.
static void SetVariableInUserProfile()
{
    if (EnvironmentManager.IsSupported)
    {
        var environment = EnvironmentManager.GetForCurrentUser();
        environment.SetEnvironmentVariable("HOMEDIR", "D:\\HomeTmp");
        var HOMEDIR = environment.GetEnvironmentVariable("HOMEDIR");
        Console.WriteLine($"HOMEDIR is {HOMEDIR}");
    }
}

static void SetVariableInSystem()
{
    if (EnvironmentManager.IsSupported)
    {
        var environment = EnvironmentManager.GetForMachine();
        environment.SetEnvironmentVariable("windir", "D:\\Windows.old");
        var windir = environment.GetEnvironmentVariable("windir");
        Console.WriteLine($"windir is {windir}");
    }
}
```

### Appending to PATH or PATHEXT

You can add to the end of the PATH or PATHEXT variables, at process, user or
machine scope.

```c++
// You can append paths to the end of the PATH variable, at
// process, user or machine scope.
static void AppendToUserPath()
{
    if (EnvironmentManager.IsSupported)
    {
        var environment = EnvironmentManager.GetForCurrentUser();
        environment.AppendToPath("%USERPROFILE%\\ContosoBin");
        var PATH = environment.GetEnvironmentVariable("PATH");
        Console.WriteLine($"PATH is {PATH}");
    }
}

// You can remove paths from the PATH variable that you
// previously appended.
static void RemoveFromUserPath()
{
    if (EnvironmentManager.IsSupported)
    {
        var environment = EnvironmentManager.GetForCurrentUser();

        // Removal is done with case-insensitive ordinal string comparison,
        // without expanding the %ProgramData% environment variable.
        environment.RemoveFromPath("%ProgramData%\\ContosoBin");
        var PATH = environment.GetEnvironmentVariable("PATH");
        Console.WriteLine($"PATH is {PATH}");
    }
}

// You can append extensions to the PATHEXT variable, and
// remove any you added previously.
private void AppendToUserPathExt()
{
    if (EnvironmentManager.IsSupported)
    {
        var environment = EnvironmentManager.GetForCurrentUser();
        environment.AddExecutableFileExtension(".XYZ");
        var PATHEXT = environment.GetEnvironmentVariable("PATHEXT");
        Console.WriteLine($"PATHEXT is {PATHEXT}");
    }
}
```

## Interface Definition

The new types are defined as follows:

```idl
namespace Microsoft.Windows.System
{
    [contractversion(2)]
    apicontract EnvironmentManagerContract{};

    [contract(EnvironmentManagerContract, 1)]
    runtimeclass EnvironmentManager
    {
        static EnvironmentManager GetForProcess();
        static EnvironmentManager GetForCurrentUser();
        static EnvironmentManager GetForMachine();
        static bool IsSupported { get; }

        [contract(EnvironmentManagerContract, 2]
        bool IsChangeTrackingSupported  {get; };

        IMapView<String, String> GetEnvironmentVariables();
        String GetEnvironmentVariable(String name);

        void SetEnvironmentVariable(String name, String value);
        void AppendToPath(String path);
        void RemoveFromPath(String path);
        void AddExecutableFileExtension(String pathExt);
        void RemoveExecutableFileExtension(String pathExt);
    }
}
```
