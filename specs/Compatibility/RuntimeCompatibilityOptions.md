App-configurable compatibility options
===

# Background

_This spec adds a RuntimeCompatibilityOptions class to control behavior of servicing changes._

Apps using Windows App SDK have two choices today: use Windows App SDK as an
automatically-updating framework package or use Windows App SDK in self-contained mode with no
automatic updates. Apps which use the framework package automatically get fixes, which is great,
but they have a chance of being broken by a bug or subtle behavior change in a servicing update.
Some apps choose self-contained mode to avoid that risk of an automatic servicing update breaking
them. But even when apps choose self-contained mode, they may find that they can't update to a
newer servicing release due to a bug or behavior change. Also, self-contained apps can't use
features which require shared services, such as some Notification features delivered via the
Singleton package.

App-configurable compatibility is intended to prevent these problems, enabling apps to choose to
use the framework package with confidence they won't be broken. Also, apps which find a
compatibility problem in a servicing release will still be able to move forward by temporarily
disabling problematic changes. Even apps using self-contained can update to a new package with
confidence that app-configurable compatibility will ensure a successful update.

A new `RuntimeCompatibilityOptions` class has APIs to control the behavior of servicing changes.
There are also properties which can be set in the app's project file to automatically use the new
APIs with the specified values.

# API Pages

## RuntimeCompatibilityOptions class

Configures which changes in Windows App SDK servicing releases are enabled. By default, all
changes are enabled, but `RuntimeCompatibilityOptions` can be used to lock the runtime behavior to a
specified patch level or to disable specific changes:

1. **Choose the patch level:** You can specify which servicing release's behavior you want to use.
   For example, your app can specify that it wants the 1.7.2 patch level behavior, which will have
   Windows App SDK run in that patch level even if 1.7.3 or later is installed. This capability
   allows you to control when your app gets new fixes or behavior changes, even when not using
   self-contained mode.
2. **Temporarily disable specific changes:** If your app encounters a problem with a specific
   change in a servicing update, you can disable just that change while still benefiting from the
   other changes or features in that update. (All changes are enabled by default for the patch
   level in use.) Disabling a change is a temporary measure which gives time for a fix to be
   released in a future Windows App SDK update or for you to implement an update in your app.

Here's an example of using `RuntimeCompatibilityOptions` to specify a patch level and disable a
specific change:

```c#
void ApplyRuntimeCompatibilityOptions() 
{
    var compatibilityOptions = new RuntimeCompatibilityOptions();
    compatibilityOptions.PatchLevel1 = new WindowsAppRuntimeVersion(1,7,3);
    compatibilityOptions.PatchLevel2 = new WindowsAppRuntimeVersion(1,8,2);
    compatibilityOptions.DisabledChanges.Add(RuntimeCompatibilityChange.SampleApiCrashFix);
    compatibilityOptions.Apply();
}
```

RuntimeCompatibilityOptions must be applied early in the process before any other Windows App
SDK APIs are called, or right after initializing the Windows App Runtime.

`PatchLevel1` and `PatchLevel2` are simply two fields to set relevant patch levels. These needn't
match any specific version of the Windows App Runtime nor be in a specific order, so it is valid
to set `PatchLevel1` to 1.8.2 and `PatchLevel2` to 1.7.3, for example. And, in the above example,
when updating the app to 1.9, you may choose to simply update `PatchLevel1` to 1.9.3 and leave
`PatchLevel2` as 1.8.2.

### Specifying RuntimeCompatibilityOptions in the app's project file

You can also specify the patch level and disabled changes in the app's project file instead of
directly calling the RuntimeCompatibilityOptions APIs. This approach has the advantage of ensuring the
options are applied early at the proper timing. Here's an example of how to specify the patch
level and disabled changes in the project file (such as `.csproj` or `.vcxproj`):

```xml
  <PropertyGroup>
    <WindowsAppSDKRuntimePatchLevel1>1.7.3</WindowsAppSDKRuntimePatchLevel1>
    <WindowsAppSDKRuntimePatchLevel2>1.8.2</WindowsAppSDKRuntimePatchLevel2>
    <WindowsAppSDKDisabledChanges>SampleApiCrashFix, OtherSampleApiCrashFix</WindowsAppSDKDisabledChanges>
  </PropertyGroup>
```

The `WindowsAppSDKDisabledChanges` property is a comma-separated list of `RuntimeCompatibilityChange`
values to disable.

### Behavior with no PatchLevel specified

If no `PatchLevel1` or `PatchLevel2` is specified, or if neither value matches the major.minor
version of the runtime being used, then the runtime will use the latest patch level. In other
words, the runtime will run with all servicing changes enabled (just like how Windows App SDK
worked before this API existed).

## RuntimeCompatibilityOptions.PatchLevel1

Optional patch level to use if the runtime version matches the major.minor version. If the runtime
version does not match the specified major.minor version, this value is ignored.

Instead of directly using this API, this patch level could be specified in the app's project file,
like this:

```xml
  <PropertyGroup>
    <WindowsAppSDKRuntimePatchLevel1>1.7.3</WindowsAppSDKRuntimePatchLevel1>
  </PropertyGroup>
```

If your app is not in the process of transitioning to a new version of the Windows App SDK, you
may only set this one patch level.

## RuntimeCompatibilityOptions.PatchLevel2

Optional patch level to use if the runtime version matches the major.minor version. If the runtime
version does not match the specified major.minor version, this value is ignored.

This property enables setting a second patch level to help apps transitioning to a new version of
the Windows App SDK. This is a convenience to allow the patch levels for both the old and new
version to be specified during the transition. Apps not in the process of transitioning should
only set the one patch level they want to use.

Setting both patch levels for the same major.minor version, such as 1.7.3 and 1.7.4, is not allowed
and will generate an error during `Apply()`.

Instead of directly using this API, this patch level could be specified in the app's project file,
like this:

```xml
  <PropertyGroup>
    <WindowsAppSDKRuntimePatchLevel2>1.8.2</WindowsAppSDKRuntimePatchLevel2>
  </PropertyGroup>
```

## RuntimeCompatibilityOptions.DisabledChanges

Optional list of specific servicing changes to disable.

If you encounter a problem with a specific change in a servicing update, you can disable just that
change by adding it to the `DisabledChanges` list before calling `Apply`, or by specifying it in
your app's project file:
```xml
  <PropertyGroup>
    <WindowsAppSDKDisabledChanges>SampleApiCrashFix, OtherSampleApiCrashFix</WindowsAppSDKDisabledChanges>
  </PropertyGroup>
```

The [release notes](https://learn.microsoft.com/windows/apps/windows-app-sdk/stable-channel) for
the Windows App SDK will list the name of each change that can be disabled.

Note that disabling a change is a temporary measure which gives time for a fix to be released in a
future Windows App SDK update or for you to implement an update in your app. You should report
changes you disable if you believe it to be a bug in the Windows App SDK. This will help the
Windows App SDK team to understand the impact of the change and prioritize a fix. You can report
issues on the [WindowsAppSDK GitHub repo](https://github.com/microsoft/WindowsAppSDK/issues/new?template=bug-report.yaml).

The capability to disable a change is **not** available across new Windows App SDK stable
releases (such as 1.7.x to 1.8.x), so this does not allow you to permanently disable an
intentional behavior change. Also, new stable releases, such as 1.8.0, start with no changes
available to disable -- this capability only applies to disabling targeted servicing changes
added in servicing releases.

## RuntimeCompatibilityOptions.Apply

Apply the set compatibility options to the runtime.

RuntimeCompatibilityOptions must be applied early in the process before any other Windows App
SDK APIs are called, or right after initializing the Windows App Runtime. The options must be set
early, before the Windows App Runtime automatically locks the configuration for the lifetime of the
process. Since the Windows App Runtime needs to run with a consistent configuration, it will lock
the configuration when it needs to ensure the configuration will no longer change. Calling `Apply`
will also lock the configuration.

If the configuration has already been locked, calling `Apply` will throw an `E_ILLEGAL_STATE_CHANGE`
exception if the options differ from the locked configuration. It is okay to call `Apply` multiple
times with the same configuration, such as if the process had initialized and used the Windows
App Runtime earlier and is reinitializing for additional use.

# API Details

```c# (but really MIDL3)
namespace Microsoft.Windows.ApplicationModel.WindowsAppRuntime
{
    /// The set of servicing changes that can be disabled.
    enum RuntimeCompatibilityChange
    {
        None = 0, /// do not use this value

        // Add real changes here:

        // 1.7.1
        // SampleApiCrashFix,
        // OtherSampleApiCrashFix,
        // ...
    };

    /// Represents a version of the Windows App Runtime.
    struct WindowsAppRuntimeVersion
    {
        UInt32 Major;
        UInt32 Minor;
        UInt32 Patch;
    };

    /// This object is used by the app to configure any desired compatibility options
    /// for Windows App Runtime behavior of changes added in servicing updates. This
    /// object is only used to set the runtime behavior and can't be used to query the
    /// applied options.
    runtimeclass RuntimeCompatibilityOptions
    {
        RuntimeCompatibilityOptions();

        /// An optional patch level to use if the runtime version matches the major.minor version.
        WindowsAppRuntimeVersion PatchLevel1 { get; set; };

        /// An optional patch level to use if the runtime version matches the major.minor version.
        WindowsAppRuntimeVersion PatchLevel2 { get; set; };

        /// An optional list of specific servicing changes to disable.
        IVector<RuntimeCompatibilityChange> DisabledChanges{ get; };

        /// Apply the compatibility options to the runtime.
        void Apply();
    }
}
```

