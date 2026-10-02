# AppLifecycle - Rich Activation

Windows App SDK introduces a new AppLifecycle component that provides a core set of functionality related to
app activation and lifecycle. Much of this functionality is directly equivalent - or very similar -
to existing functionality within the platform. However, there is value in abstracting this
functionality so that all app types can use it, delivering it out-of-band from the OS, and making it
available as open-source. The totality of AppLifecycle features in v1 is as follows (additional
features may be added in later releases):

-   Rich activation objects
-   Selective single/multi-instancing
-   System state and power notifications.

This spec addresses the rich activation APIs in the component. The priority is to make modern
activation available to unpackaged apps. In the initial release, these will not be usable by
UWP or Desktop Bridge apps.

Terminology note. A "packaged" app is an app that is built into an MSIX package, including UWP
and Desktop Bridge apps, but not including Sparse packages where only the manifest is packaged.
An "unpackaged" app therefore is one that is not built into an MSIX package.

## Background

Traditional Win32 apps expect to get their arguments passed into WinMain in the form of a string. 
They can also call the Win32 [GetCommandLineW](https://docs.microsoft.com/windows/win32/api/processenv/nf-processenv-getcommandlinew) API. Windows Forms apps expect to call
[Environment.GetCommandLineArgs](https://docs.microsoft.com/dotnet/api/system.environment.getcommandlineargs) for the same purpose. This is true regardless of the 
"activation kind" - in fact, for unpackaged apps, all activations are managed in the same way, 
only varying by the arguments passed in to WinMain. Win32 apps are familiar with 3 activation 
kinds: regular launch (whether by command-line, tile/shortcut or startup), file-type and protocol
association.

Conversely, UWP supports [44 different kinds of activation](https://docs.microsoft.com/uwp/api/Windows.ApplicationModel.Activation.ActivationKind), each represented by a different 
IActivatedEventArgs class, where the arguments are passed in to the app's Launched or 
Activated event handlers, as properties on a specific XXXActivatedEventArgs object. In addition, 
multi-instanced UWP and Desktop Bridge apps can call the [AppInstance.GetActivatedEventArgs](https://docs.microsoft.com/uwp/api/windows.applicationmodel.appinstance.getactivatedeventargs)

API.

Of all the rich activation kinds, some require some form of prior information registered with the
system so that it knows how to activate the target app. In the case of file-type, protocol and
startup activation, Win32 apps can do this registration by writing regkeys (either in their
installer or at runtime). Packaged (UWP and Desktop Bridge) apps do this via entries in their
manifest which the platform registers during install. Toast activation is unusual in that the
developer requirements are different between UWP and Desktop Bridge. For UWP, it requires only very
minimal "registration" - in that the system must be told the ID of the app to use for activation.
For Desktop Bridge, it does require manifest declarations.

## Description

This part of Windows App SDK AppLifecycle makes rich UWP activation functionality available to
non-MSIX-packaged Win32 app types. There are 2 main aspects to consider:

-   Which activation kinds will unpackaged apps be able to use?
-   How does the app tell the system which activation kinds it wants to use?

### Supported activation kinds

The first release focuses on the most commonly-used rich activation kinds. The AppLifecycle
component will provide a converged GetActivatedEventArgs API which will get all args, regardless of
activation kind, effectively merging in the functionality of GetCommandLineArgs/GetCommandLineW and
the platform GetActivatedEventArgs. It will also be decoupled from multi-instancing.

Of the 44 UWP activation kinds, 4 of the most commonly-used kinds are also supported for Desktop
Bridge and Windows
[reg-free WinRT](https://blogs.windows.com/windowsdeveloper/2019/04/30/enhancing-non-packaged-desktop-apps-using-windows-runtime-components/)
apps. The AppLifecycle implementation is based on this set. Some activation kinds require prior
registration, others do not. The target list for v1 is as follows:

| Activation kind | Description                                                  |
| --------------- | ------------------------------------------------------------ |
| Launch          | Launch from a Start tile/shortcut, from a command window, or programmatically via ShellExecute/CreateProcess. |
| File            | The app is activated when the user double-clicks a registered file, or when a caller calls ShellExecute or LaunchFileAsync on a registered file. |
| Protocol        | Activated via ShellExecute or LaunchUriAsync, or by specifying a protocol string on a command-line. |
| StartupTask     | The app starts on user log-in - either registered in the registry, or via shortcuts in a well-known startup folder. |



### Activation registration

Apps can start using supported modern activation phases by:

-   Calling a method to register activation.
-   Calling a method in their entrypoint to handle activation.

From a Win32 app perspective, the 2 activation kinds that do not require any registration
(Shortcut/Tile Launch and CommandLine) are effectively the same in terms of activation payload.
Indeed, it is not possible to distinguish a launch activation of a Win32 app from a commandline
activation. Therefore, the AppLifecycle implementation will merge Launch and CommandLine into one
(Launch) activation kind.

UWP apps can only register for activation kinds via manifest declarations, and therefore this
happens during app install. Conversely, traditional app types can write registry entries at any
time.

A key benefit is to enable unpackaged Win32 apps to use the set of rich activations using familiar
designs, without any additional friction. Specifically, AppLifecycle will provide APIs which the app
can call to register its interest in rich activations. The app is not required to have an MSIX
manifest, nor an MSIX package. Using the API approach rather than the manifest approach has the
added benefit that it also addresses a related customer request for dynamic activation registrations
even for UWP apps.

Currently all registered activation points are managed per-user. If your app is installed for
multiple users via an MSI or elevated installer your app will need to re-register launch points for
every user. For v1, the platform will support only per-user registration.



## Examples

### Register for rich activation

Providing APIs for activation registration means that an app can register at any time. The most
common case would be very early in the app's main function. The app can register for any of the
supported activation kinds. For most activation kinds, the app can register multiple options (for
example, multiple filetypes or dataformats, or verbs) - and could therefore call the RegisterXXX
function multiple times, if required. For example, an app could register for ".jpg" and ".bmp"
filetype activations at one point, and then later also register for ".png".

An app can register a specific filetype only once. To allow for the case where the app determines
the combination of options at runtime (and potentially changes the combinations at a later time),
where an app registers the same filetype multiple times, the latest registration is honored and
overwrites any previous registrations.

In the existing platform, UWP apps can only register one startup activation extension. However, for
packaged desktop apps, multiple startup extensions are permitted, and each one can specify a
different executable.

The following example shows how an unpackaged Win32 Desktop app can use the new registration
APIs to register for one or more activation kinds.

```c++
int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE,
    _In_ LPWSTR,
    _In_ int nCmdShow)
{
    // Initialize COM.
    winrt::init_apartment();

    // Registering for rich activation kinds can be done in the
    // app's installer or in the app itself.
    RegisterForActivation();

    // When the app starts, it can get its activated eventargs, and perform
    // any required operations based on the activation kind and payload.
    RespondToActivation();

    ///////////////////////////////////////////////////////////////////////////
    // Standard Win32 window configuration/creation and message pump:
    // ie, whatever the app would normally do - nothing new here.
    RegisterClassAndStartMessagePump(hInstance, nCmdShow);
    return 1;
}

void RegisterForActivation()
{
    // Register one or more supported filetypes, specifying 
    // an icon (specified by binary file path plus resource index),
    // a display name to use in Shell and Settings,
    // zero or more verbs for the File Explorer context menu,
    // and the path to the EXE to register for activation.
    hstring myFileTypes[3] = { L".foo", L".foo2", L".foo3" };
    hstring verbs[2] = { L"view", L"edit" };
    ActivationRegistrationManager::RegisterForFileTypeActivation(
        myFileTypes,
        exePathAndIconIndex,
        L"Contoso File Types",
        verbs,
        exePath
    );

    // Register a URI scheme for protocol activation,
    // specifying the scheme name, icon, display name and EXE path.
    ActivationRegistrationManager::RegisterForProtocolActivation(
        L"foo",
        exePathAndIconIndex,
        L"Contoso Foo Protocol",
        exePath
    );

    // Register for startup activation.
    // As we're registering for startup activation multiple times,
    // and this is a multi-instance app, we'll get multiple instances
    // activated at startup.
    ActivationRegistrationManager::RegisterForStartupActivation(
        L"ContosoStartupId",
        exePath
    );

    // If we don't specify the EXE, it will default to this EXE.
    ActivationRegistrationManager::RegisterForStartupActivation(
        L"ContosoStartupId2",
        L""
    );
}
```

### Get rich activation objects

A Win32 app would typically get its command-line arguments very early in its WinMain, and we
therefore expect the app to call the new AppInstance::GetActivatedEventArgs in the same place,
instead of using the supplied lpCmdLine parameter or using GetCommandLineW. From there, the app can
determine the specific ExtendedActivationKind, query the object for the specific activation type,
and then access the properties and methods of that type. ExtendedActivationKind is a superset
of the UWP ActivationKind enum. The AppActivationArguments.Data property represents the
underlying activation event args type. Note that this provides an interface (ILaunchActivatedEventArgs,
IFileActivatedEventArgs, and so on) and not a class.

```c++
void RespondToActivation()
{
    AppActivationArguments args = 
        AppInstance::GetCurrent().GetActivatedEventArgs();
    ExtendedActivationKind kind = args.Kind();
    if (kind == ExtendedActivationKind::Launch)
    {
        ILaunchActivatedEventArgs launchArgs = 
            args.Data().as<ILaunchActivatedEventArgs>();
        if (launchArgs)
        {
            winrt::hstring argString = launchArgs.Arguments();
            std::vector<std::wstring> argStrings = SplitStrings(argString);
            OutputMessage(L"Launch activation");
            for (std::wstring const& s : argStrings)
            {
                OutputMessage(s.c_str());
            }
            // If the first argument is "Settings", we'll launch the Settings page.
            if (wcscmp(argStrings[1].c_str(), L"Settings") == 0)
            {
                LaunchSettingsPage();
            }
            else
            {
                LaunchMainPage();
            }
        }
    }
    else if (kind == ExtendedActivationKind::File)
    {
        IFileActivatedEventArgs fileArgs = 
            args.Data().as<IFileActivatedEventArgs>();
        if (fileArgs)
        {
            IStorageItem file = fileArgs.Files().GetAt(0);
            OutputFormattedMessage(
                L"File activation: %s", file.Name().c_str());
        }
    }
    else if (kind == ExtendedActivationKind::Protocol)
    {
        IProtocolActivatedEventArgs protocolArgs = 
            args.Data().as<IProtocolActivatedEventArgs>();
        if (protocolArgs)
        {
            Uri uri = protocolArgs.Uri();
            OutputFormattedMessage(
                L"Protocol activation: %s", uri.RawUri().c_str());
        }
    }
    else if (kind == ExtendedActivationKind::StartupTask)
    {
        IStartupTaskActivatedEventArgs startupArgs = 
            args.Data().as<IStartupTaskActivatedEventArgs>();
        if (startupArgs)
        {
            OutputFormattedMessage(
                L"Startup activation: %s", startupArgs.TaskId().c_str());
        }
    }
}
```

### Unregister

The primary requirement is to be able to register for the supported activation kinds dynamically. A
secondary requirement is to be able to unregister for any or all of these.

For filetype associations, the app can register for multiple filetypes. We will provide the ability
to unregister one or more filetypes. For the initial release, we do not include an API to
unregister all filetype registrations at once, although this could be added in a later release.
For protocol registrations, the app can register for multiple protocols individually, so the
API will also enable the app to unregister for each of these individually. For unregistering for
startup behavior, the app must pass the taskId that it originally passed in when registering.

```c++
void UnregisterForActivation()
{
    // Unregister one or more registered filetypes.
    try
    {
        hstring myFileTypes[3] = { L".foo", L".foo2", L".foo3" };
        ActivationRegistrationManager::UnregisterForFileTypeActivation(
            myFileTypes,
            exePath
        );
    }
    catch (...)
    {
        OutputMessage(L"Error unregistering file types");
    }

    // Unregister a protocol scheme.
    ActivationRegistrationManager::UnregisterForProtocolActivation(
        L"foo",
        L"");

    // Unregister for startup activation.
    ActivationRegistrationManager::UnregisterForStartupActivation(
        L"ContosoStartupId");
    ActivationRegistrationManager::UnregisterForStartupActivation(
        L"ContosoStartupId2");
}
```

## API Details

### AppInstance

This type represents an activation of an application in Windows App SDK, providing methods to find
other instances of itself, redirect activations across instances, and handle incoming non-launch
activations.

```idl
namespace Microsoft.Windows.AppLifecycle
{
    runtimeclass AppInstance
    {
        static AppInstance GetCurrent();

        AppActivationArguments GetActivatedEventArgs();
    }
}
```

**GetCurrent** returns an AppInstance that represents the current app instance.

**GetActivatedEventArgs** provides similar behavior as the existing platform
[AppInstance.GetActivatedEventArgs](https://docs.microsoft.com/uwp/api/windows.applicationmodel.appinstance.getactivatedeventargs),
except that it returns a new ActivationArguments object for the current activation instead of an
IActivatedEventArgs.


### ExtendedActivationKind

```idl

namespace Microsoft.Windows.AppLifecycle
{
    enum ExtendedActivationKind
    {
        ExtensionBase = 4096
    }
}
```


This enum is based on the platform

[ActivationKind](https://docs.microsoft.com/uwp/api/Windows.ApplicationModel.Activation.ActivationKind).
All platform ActivationKind values are cloned to this class. We determine an "extension base" value which
is well above the existing highest ActivationKind value (1026), to allow for new values to be added to the
platform. Going forward, any new platform values will also be added to the new enum, plus any new values
that are only defined in the new enum. That is, any values < the extension base value will exist in both the
Windows App SDK and platform implementations, but conversely any values > the extension base value only exist in the
Windows App SDK implementation and do not exist in the platform implementation.

### AppActivationArguments

```idl
namespace Microsoft.Windows.AppLifecycle
{
    [default_interface]
    runtimeclass AppActivationArguments
    {
        // The kind of activation these arguments represent
        ExtendedActivationKind Kind { get; };

        // An object with additional activation parameters, whose underlying type
        // matches the Kind property above.
        Object Data { get; };
    }
}
```

The platform defines
[IActivatedEventArgs](https://docs.microsoft.com/uwp/api/Windows.ApplicationModel.Activation.IActivatedEventArgs),
which exposes a Kind property. Apps can get an IActivatedEventArgs reference, examine the Kind and
then cast the reference to the interface for that specific activation.
This enables generic functions such as GetActivatedEventArgs and the Activated event handler, which
provide the app with an IActivatedEventArgs that the app can then convert to a specific 
type. However, IActivatedEventArgs also defines other properties that are only useful in a UWP
context. In addition, we need a mechanism that supports both platform ActivationKinds and also

Windows app SDK ExtendedActivationKinds and their corresponding interface types.

The new ActivationArguments type serves this purpose: the app can examine the Kind, and then cast
the Data property to the interface type that represents the specific activation.

**Kind** is the enum value that indicates the kind of activation this object represents.

**Data** can be cast to a specific interface corresponding to Kind.

### ActivatedEventArgs Clones

Windows App SDK initially defines four `-ActivatedEventArgs` types that replicate the Windows
equivalent `Windows.ApplicationModel.Activation.-ActivatedEventArgs`, but support adding new
functionality over time. These are:


| API                                      | Description                                                  |
| ---------------------------------------- | ------------------------------------------------------------ |
| interface ILaunchActivatedEventArgs      | Based on the existing [LaunchActivatedEventArgs](https://docs.microsoft.com/uwp/api/windows.applicationmodel.activation.launchactivatedeventargs). |
| interface IFileActivatedEventArgs        | Based on the existing [FileActivatedEventArgs](https://docs.microsoft.com/uwp/api/windows.applicationmodel.activation.fileactivatedeventargs). |
| interface IProtocolActivatedEventArgs    | Based on the existing [ProtocolActivatedEventArgs](https://docs.microsoft.com/uwp/api/windows.applicationmodel.activation.protocolactivatedeventargs). |
| interface IStartupTaskActivatedEventArgs | Based on the existing [StartupTaskActivatedEventArgs](https://docs.microsoft.com/uwp/api/windows.applicationmodel.activation.startuptaskactivatedeventargs). |

> In defining an API that is usable by both unpackged Win32 apps and UWP apps, inevitably there will
> be some features that are not applicable to one or other type of consumer. However, it is
> important to maximize consistency with the existing platform APIs. The approach here is to
> implement only those UWP interfaces in v1 that make sense for Win32 apps. For example, in UWP,
> ProtocolActivatedEventArgs implements 5 interfaces, of which only 2 define members that are
> interesting to Win32 apps - so for v1, the proposal is to implement only those 2 interfaces; and
> defer consideration of the additional interfaces to a later release.

### Activation registration

For most activation kinds, the optional attributes that are available for the traditional
registry-based activation registrations are roughly equivalent to those available for UWP
manifest-based registration. The exception to this is file-type association, where traditional
registry activation offers 5 optional attributes, whereas UWP offers 37 optional attributes. Most of
the UWP optional attributes are very rarely used, and in some cases there are no apps in the Store
that use a given parameter. For v1, the platform will support all the registry-based optional
attributes - further UWP attributes may be included in a later release.

The new `RegisterForXXXActivation` methods will be exposed as static methods from a new
ActivationRegistrationManager class in the AppLifecycle component.

The aim is that the app would call any of these RegisterForXXXActivation methods at any time
dynamically from the app itself. For v1, this API does not support calling from the app's installer.
For filetype and protocol, the app can call the RegisterForXXXActivation method multiple times, each
time providing different filetype names or different protocol names. These registrations would be
cumulative, so long as the parameters are different. If the app tries to register for the same
filetype name or the same protocol multiple times, this is idempotent (there's only one registration
per unique filetype name or protocol name; no error for multiple identical registrations, any new
values supplied for the same registration overwrite any old values).

Similarly, if the app registers multiple times for startup, this is also idempotent (a single
registration, no error, any new values supplied overwrite any old values).

```idl
namespace Microsoft.Windows.AppLifecycle
{
    static runtimeclass ActivationRegistrationManager
    {
        static void RegisterForFileTypeActivation(String[] supportedFileTypes, String logo,
            String displayName, String[] supportedVerbs, String exePath);

        static void RegisterForProtocolActivation(String scheme, String logo, String displayName,
            String exePath);

        static void RegisterForStartupActivation(String taskId, String exePath);

        static void UnregisterForFileTypeActivation(String[] fileTypes, String exePath);
        static void UnregisterForProtocolActivation(String scheme, String exePath);
        static void UnregisterForStartupActivation(String taskId);
    }
}
```

**RegisterForFileTypeActivation** registers the app for activation based on file types (extensions.)
See the existing documentation for [Win32 filetype association registry entries](https://docs.microsoft.com/windows/win32/shell/app-registration).

-   `supportedFileTypes` - one or more supported filetypes, specified by the file extension
    including the leading ".", eg ".docx"
-   `logo` - used by the Shell and Settings for this filetype. For packaged apps, a package-relative
    path to an image file. For unpackaged, a literal filepath to a binary file (DLL, EXE) plus a
    resource index. The caller can pass either.
-   `displayName` - used by the Shell and Settings for this filetype.
-   `supportedVerbs` - zero or more app-defined verbs. Each verb is added to the File Explorer
    context menu when a registered file is right-clicked; and the selected verb is passed to the app
    as the `FileActivatedEventArgs::Verb` property.
-   `exePath` - path to the executable to be activated. Typically this is specified if the caller is
    the app's installer rather than the app itself.

**RegisterForProtocolActivation** registers the app for activation based on a protocol scheme (like
`x-contoso-launch:`.)

-   `schemeName` - the protocol identifier, eg `foo` or `https`.
-   `logo` - used by the Shell and Settings for this scheme. For packaged apps, a package-relative
    path to an image file. For unpackaged, a literal filepath to a binary file (DLL, EXE) plus a
    resource index. The caller can pass either.
-   `displayName` - used by the Shell and Settings for this scheme.
-   `exePath` - path to the executable to be activated.

**RegisterForStartupActivation** registers the app for activation at user logon time, subject to
system and user policy.

-   `taskId` - a string identifier which the app can use in the StartupTask API to request enabling
    or disabling of the startup behavior.
-   `exePath` - path to the executable to be activated.

**UnregisterForFileTypeActivation** removes file type registration for this app from one or more
file types.

-   `fileTypes` - one or more filetypes that the caller wants to unregister.
-   `exePath` - path to the executable that was registered for activation.

**UnregisterForProtocolActivation** removes file type registration for this app from a protocol
scheme.

-   `schemeName` - the previously-registered protocol identifier, eg "foo" or "https".
-   `exePath` - path to the executable that was registered for activation.

**UnregisterForStartupActivation** removes registration for activation during user logon.

-   `taskId` - a string identifier which the app specified when it registered for startup behavior
    initially.
-   `exePath` - path to the executable that was registered for activation.
