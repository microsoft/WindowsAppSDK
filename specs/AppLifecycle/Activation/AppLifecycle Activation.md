# AppLifecycle - Rich Activation

Reunion introduces a new AppLifecycle component that provides a core set of
functionality related to app activation and lifecycle. Much of this
functionality is directly equivalent - or very similar - to existing
functionality within the platform. However, there is value in abstracting this
functionality so that all app types can use it, delivering it out-of-band from
the OS, and making it available as open-source. The totality of AppLifecycle
features in v1 is as follows (additional features may be added in later
releases):

- Rich activation objects
- Selective single/multi-instancing
- System state and power notifications.

This spec addresses the rich activation APIs in the component.

## Background

Traditional Win32 apps expect to get their arguments passed into WinMain in the
form of a string array. They can also call the Win32
[GetCommandLineW](https://docs.microsoft.com/en-us/windows/win32/api/processenv/nf-processenv-getcommandlinew)
API. Windows Forms apps expect to call
[Environment.GetCommandLineArgs](https://docs.microsoft.com/en-us/dotnet/api/system.environment.getcommandlineargs)
for the same purpose. This is true regardless of the "activation kind" - in
fact, for unpackaged apps, all activations are managed in the same way, only
varying by the arguments passed in to WinMain. Win32 apps are familiar with 3
activation kinds: regular launch (whether by command-line, tile/shortcut or
startup), file-type and protocol association.

Conversely, UWP supports
[44 different kinds of activation](https://docs.microsoft.com/en-us/uwp/api/Windows.ApplicationModel.Activation.ActivationKind),
each represented by a different IActivatedEventArgs class, where the arguments
are passed in to the app's Launched or Activated event handlers, as properties
on a specific XXXActivatedEventArgs object. In addition, multi-instanced UWP and
Desktop Bridge apps can call the
[AppInstance.GetActivatedEventArgs](https://docs.microsoft.com/en-us/uwp/api/windows.applicationmodel.appinstance.getactivatedeventargs)
API.

Of all the rich activation kinds, some require some form of prior information
registered with the system so that it knows how to activate the target app. In
the case of file-type, protocol and startup activation, Win32 apps can do this
registration by writing regkeys (either in their installer or at runtime).
Packaged (UWP and Desktop Bridge) apps do this via entries in their manifest
which the platform registers during install. Toast activation is unusual in that
the developer requirements are different between UWP and Desktop Bridge. For
UWP, it requires only very minimal "registration" - in that the system must be
told the ID of the app to use for activation. For Desktop Bridge, it does
require manifest declarations.

<br>

## Description

This part of Reunion AppLifecycle makes rich UWP activation functionality
available to non-MSIX-packaged Win32 app types. There are 2 main aspects to
consider:

- Which activation kinds will unpackaged apps be able to use?
- How does the app tell the system which activation kinds it wants to use?

### Supported activation kinds

The first release focuses on the most commonly-used rich activation kinds. The
AppLifecycle component will provide a converged GetActivatedEventArgs API which
will get all args, regardless of activation kind, effectively merging in the
functionality of GetCommandLineArgs/GetCommandLineW and the platform 
GetActivatedEventArgs. It will also be decoupled from multi-instancing.

Of the 44 UWP activation kinds, 4 of the most commonly-used kinds are also
supported for Desktop Bridge and Windows 
[reg-free WinRT](https://blogs.windows.com/windowsdeveloper/2019/04/30/enhancing-non-packaged-desktop-apps-using-windows-runtime-components/)
apps. The AppLifecycle implementation is based on this set. Some activation
kinds require prior registration, others do not. The target list for v1 is as
follows:

| Activation kind | Description                                                  |
| --------------- | ------------------------------------------------------------ |
| Launch          | Launch from a Start tile/shortcut, from a command window, or programmatically via ShellExecute/CreateProcess. |
| File            | The app is activated when the user double-clicks a registered file, or when a caller calls ShellExecute or LaunchFileAsync on a registered file. |
| Protocol        | Activated via ShellExecute or LaunchUriAsync, or by specifying a protocol string on a command-line. |
| StartupTask     | The app starts on user log-in - either registered in the registry, or via shortcuts in a well-known startup folder. |

<br/>

### Activation registration

Apps can start using supported modern activation phases by:

- Calling a method to register activation.
- Calling a method in their entrypoint to handle activation.

From a Win32 app perspective, the 2 activation kinds that do not require any
registration (Shortcut/Tile Launch and CommandLine) are effectively the same in
terms of activation payload. Indeed, it is not possible to distinguish a launch
activation of a Win32 app from a commandline activation. Therefore, the
AppLifecycle implementation will merge Launch and CommandLine into one (Launch)
activation kind.

UWP apps can only register for activation kinds via manifest declarations, and
therefore this happens during app install. Conversely, traditional app types can
write registry entries at any time.

A key benefit is to enable unpackaged Win32 apps to use the set of rich
activations using familiar designs, without any additional friction.
Specifically, AppLifecycle will provide APIs which the app can call to register
its interest in rich activations. The app is not required to have an MSIX
manifest, nor an MSIX package. Using the API approach rather than the manifest
approach has the added benefit that it also addresses a related customer request
for dynamic activation registrations even for UWP apps.

Currently all registered activation points are managed per-user. If your app is
installed for multiple users via an MSI or elevated installer your app will need
to re-register launch points for every user. For v1, the platform will support
only per-user registration.

 <br>

## Examples

### Register for rich activation

Providing APIs for activation registration means that an app can register at any
time. The most common case would be very early in the app's main function. The
app can register for any of the supported activation kinds. For most activation
kinds, the app can register multiple options (for example, multiple filetypes or
dataformats, or verbs) - and could therefore call the RegisterXXX function
multiple times, if required. For example, an app could register for ".jpg" and
".bmp" filetype activations at one point, and then later also register for
".png".

Each registered filetype must be unique for the app. To allow for the case where
the app determines the combination of options at runtime (and potentially
changes the combinations at a later time), where an app registers the same
filetype multiple times, the latest registration is honored and overwrites any
previous registrations.

In the existing platform, UWP apps can only register one startup activation
extension. However, for packaged desktop apps, multiple startup 
extensions are permitted, and each one can specify a different executable..

```c++
int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
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
    // Register one or more supported image filetypes, 
    // an icon (specified by binary file path plus resource index),
    // a display name to use in Shell and Settings,
    // zero or more verbs for the File Explorer context menu,
    // and the path to the EXE to register for activation.
    string imageFileTypes[3] = { ".jpg", ".png", ".bmp" };
    string verbs[2] = { "view", "edit" };
    ActivationRegistrationManager::RegisterForFileTypeActivation(
        imageFileTypes,
        "C:\\Program Files\\Contoso\\MyResources.dll, 123", 
        "Contoso File Types",
        verbs,
        "C:\\Program Files\\Contoso\\MyApp.exe"
    );

    // Register another set of filetypes, specifying a UWP-style
    // path to an image file for the icon, no explicit verbs,
    // and defaulting to the current executable for the EXE
    // to be activated.
    string videoFileTypes[3] = { ".mov", ".wmv", ".mp3" };
    ActivationRegistrationManager::RegisterForFileTypeActivation(
        videoFileTypes,
        "C:\\Program Files\\Fabrikam\\MyIcon.png",
        "Fabrikam Video Types",
        NULL,
        ""
    );

    // Register some URI schemes for protocol activation,
    // specifying the scheme name, icon, display name and EXE path.
    ActivationRegistrationManager::RegisterForProtocolActivation(
        "foo",
        "C:\\Program Files\\Contoso\\MyResources.dll, 45", 
        "Contoso Foo Protocol",
        "C:\\Program Files\\Contoso\\MyApp.exe"
    );

    // Register a protocol, specifying the scheme name,
    // UWP-style image file path, display name, and defaulting
    // the EXE to the current executable.
    ActivationRegistrationManager::RegisterForProtocolActivation(
        "com.fabrikam.list",
        "C:\\Program Files\\Fabrikam\\MyIcon.png",
        "Fabrikam Protocol",
        ""
    );

    // Register for startup activation.
    ActivationRegistrationManager::RegisterForStartupActivation(
        "MyTaskId",
        "C:\\Program Files\\Contoso\\MyApp.exe"
    );
    ActivationRegistrationManager::RegisterForStartupActivation(
        "AnotherTaskId",
        ""
    );
}
```

### Get rich activation objects

A Win32 app would typically get its command-line arguments very early in its
WinMain, and we therefore expect the app to call the new
AppLifecycle::GetActivatedEventArgs in the same place, instead of using the
supplied lpCmdLine parameter or using GetCommandLineW. From there, the app can
determine the specific ActivationKind, query the object for the specific
XXXActivatedEventArgs type, and then access the properties and methods of that
type.

```c++
void OnActivated(ActivationArguments const& args)
{
    ExtendedActivationKind kind = args.Kind;
    if (kind == ExtendedActivationKind::Launch)
    {
        LaunchActivatedEventArgs launchArgs = args.Data.as<LaunchActivatedEventArgs>();
        DoSomethingWithLaunchArgs(launchArgs.Arguments());
    }
    else if (kind == ExtendedActivationKind::File)
    {
        FileActivatedEventArgs fileArgs = args.Data.as<FileActivatedEventArgs>();
        DoSomethingWithFileArgs(fileArgs.Files());
    }
    else if (kind == ExtendedActivationKind::Protocol)
    {
        ProtocolActivatedEventArgs protocolArgs = args.Data.as<ProtocolActivatedEventArgs>();
        DoSomethingWithProtocolArgs(protocolArgs.Uri());
    }
    else if (kind == ExtendedActivationKind::StartupTask)
    {
        StartupTaskActivatedEventArgs startupArgs = args.Data.as<StartupTaskActivatedEventArgs>();
        DoSomethingWithStartupArgs(startupArgs.TaskId());
    }
}
```

### Unregister

The primary requirement is to be able to register for the supported activation
kinds dynamically. A secondary requirement is to be able to unregister for any
or all of these.

For filetype associations, the app can register for multiple filetypes. We will
provide the ability to unregister one or more filetypes. For protocol
registrations, the app can register for multiple protocols individually, so the
API will also enable the app to unregister for each of these individually. For
unregistering for startup behavior, the app must pass the taskId that it 
originally passed in when registering.

```c++
void UnregisterForActivation()
{
    // Unregister one or more registered filetypes.
    string imageFileTypes[3] = { ".jpg", ".png", ".bmp" };
    ActivationRegistrationManager::UnregisterForFileTypeActivation(
        imageFileTypes,
        "C:\\Program Files\\Contoso\\MyApp.exe"
    );

    // Unregister a protocol scheme.
    ActivationRegistrationManager::UnregisterForProtocolActivation(
        "foo",
        "");

    // Unregister for startup activation.
    ActivationRegistrationManager::UnregisterForStartupActivation(
        "AnotherTaskId",
        "");
}
```

<br>

## API Details

### Top-level types

This spec proposes one new enum and 6 new classes:

- An ExtendedActivationKind enum, based off
  Windows.ApplicationModel.Activation.ActivationKind.
- An ActivationArguments class that brings forward the core behavior of the platform's IActivatedEventArgs interface.
- An AppInstance class to encapsulate all API functionality for an instance of an app.
- An XXXActivatedEventArgs class for each activation kind, modeled directly on existing XXXActivatedEventArgs classes in the Windows.ApplicationModel.Activation namespace.

| API                                                          | Description                                                  |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| enum class ExtendedActivationKind<br/>{<br/>    /\* all existing platform ActivationKind values, \*/<br/>    ExtensionBase = 5000,<br/>    /\* new Reunion ExtendedActivationKind values\*/<br/>}; | This enum is based off the platform [ActivationKind](https://docs.microsoft.com/en-us/uwp/api/Windows.ApplicationModel.Activation.ActivationKind). All platform ActivationKind values are cloned to this class. Then, we set a high-value **ExtensionBase** value which is well above the existing highest ActivationKind value (1026), to allow for new values to be added to the platform. Going forward, any new platform values will also be added to the new enum, plus any new values that are only defined in the new enum. |
| class ActivationArguments<br/>{<br/>public:<br/>    ExtendedActivationKind Kind ;<br/>    IInspectable Data;<br/>}; | The platform defines [IActivatedEventArgs](https://docs.microsoft.com/en-us/uwp/api/Windows.ApplicationModel.Activation.IActivatedEventArgs), which exposes a Kind property. Apps can get an IActivatedEventArgs reference, examine the Kind and then cast the reference to the specific concrete class type that implements IActivatedEventArgs. This enables generic functions such as GetActivatedEventArgs and the Activated event handler, which provide the app with an IActivatedEventArgs that the app can then convert to a specific concrete type. However, IActivatedEventArgs also defines other properties that are only useful in a UWP context. In addition, we need a mechanism that supports both platform ActivationKinds and also Reunion-only ExtendedActivationKinds and their corresponding concrete class types. <br />The new ActivationArguments type serves this purpose: the app can examine the Kind, and then cast the Data property to the specific concrete type (which can be either a platform IActivatedEventArgs concrete class, or a Reunion class).<br />**Kind** is the enum value that indicates the kind of activation this object represents.<br />**Data** can be cast to a specific concrete class corresponding to Kind. |
| class AppInstance<br/>{<br/>public:<br/>    static AppInstance GetCurrent();<br/>    static IVector<AppInstance> GetInstances();<br/>    static AppInstance FindOrRegisterForKey(string key);<br/>    void UnregisterKey(string key);<br/>    void RedirectTo(ActivationArguments args);<br/>    static ActivationArguments GetActivatedEventArgs();<br/>    static void Activated(EventHandler<ActivationArguments> const& handler);<br/>    string Key;<br/>    bool IsCurrent;<br/>}; | New class. This is the major new class exposed in the AppLifecycle component in Reunion. <br />**GetCurrent** returns an AppInstance that represents the current app instance.<br />**GetInstances** returns a collection of all running instances of the app. Note: the existing platform [AppInstance.GetInstances](https://docs.microsoft.com/en-us/uwp/api/windows.applicationmodel.appinstance.getinstances) only returns instances that have explicitly registered for multi-instance redirection. However, the new AppInstance Reunion class will provide an API surface for all manner of app-instance-related behaviors, not restricted to instance redirection. For this reason, Reunion will maintain a list of all running instances and will not require explicit registration by the app.<br />**FindOrRegisterForKey** enables an app to register an app-defined key for the current instance, or if another instance has already registered that key, then return that other instance instead. This is similar to the platform [AppInstance.FindOrRegisterInstanceForKey](https://docs.microsoft.com/en-us/uwp/api/windows.applicationmodel.appinstance.findorregisterinstanceforkey) except that that implementation is specific to instance redirection, whereas the Reunion design allows for the app to register a key for any reason.<br />**UnregisterKey** unregisters a given key for this instance. The existing  platform behavior is specific to instance redirection, and unregistering the key unregisters that instance for redirection (and removes it from the platform's collection of registered instances). In the Reunion design, unregistering a key simply removes the key for this instance; it does not have any effect on instance redirection, nor does it remove this instance from the collection that Reunion is maintaining of all running instances. <br />**RedirectTo** enables an instance of the app to redirect the current activation request to another instance. This is very similar to the existing platform [AppInstance.RedirectActivationTo](https://docs.microsoft.com/en-us/uwp/api/windows.applicationmodel.appinstance.redirectactivationto) method, except that the Reunion implementation allows the app to pass an ActivationArguments payload, thus opening the scope to allow the app to modify or replace the activation arguments that the target instance will receive.<br />**GetActivatedEventArgs** provides similar behavior as the existing platform [AppInstance.GetActivatedEventArgs](https://docs.microsoft.com/en-us/uwp/api/windows.applicationmodel.appinstance.getactivatedeventargs), except that it returns a new ActivationArguments object for the current activation instead of an IActivatedEventArgs. <br/> |
| class LaunchActivatedEventArgs                               | Based on the existing [LaunchActivatedEventArgs](https://docs.microsoft.com/en-us/uwp/api/windows.applicationmodel.activation.launchactivatedeventargs). |
| class FileActivatedEventArgs                                 | Based on the existing [FileActivatedEventArgs](https://docs.microsoft.com/en-us/uwp/api/windows.applicationmodel.activation.fileactivatedeventargs). |
| class ProtocolActivatedEventArgs                             | Based on the existing [ProtocolActivatedEventArgs](https://docs.microsoft.com/en-us/uwp/api/windows.applicationmodel.activation.protocolactivatedeventargs). |
| class StartupTaskActivatedEventArgs                          | Based on the existing [StartupTaskActivatedEventArgs](https://docs.microsoft.com/en-us/uwp/api/windows.applicationmodel.activation.startuptaskactivatedeventargs). |

Also see the related API Spec AppLifecycle - Single/Multi-instancing, which
describes the new Activated event. An app can use GetActivatedEventArgs even if
it is not choosing to use multi-instance redirection. If it is using
multi-instance redirection, then it can use GetActivatedEventArgs and also
handle the Activated event.

### Properties, methods and sub-types

Most of the existing XXXActivatedEventArgs types include properties such as the
User, SplashScreen, PreviousExecutionState and ActivationViewSwitcher for
example. These are low-priority for v1, as they are less-commonly used.

In defining an API that is usable by both unpackged Win32 apps and UWP apps,
inevitably there will be some features that are not applicable to one or other
type of consumer. However, it is important to maximize consistency with the
existing platform APIs. The approach here is to implement only those UWP
interfaces in v1 that make sense for Win32 apps. For example, in UWP,
ProtocolActivatedEventArgs implements 5 interfaces, of which only 2 define
members that are interesting to Win32 apps - so for v1, the proposal is to
implement only those 2 interfaces; and defer consideration of the additional
interfaces to a later release.

The following table lists the existing APIs that will be implemented in
AppLifecycle in Reunion v1.

| API                                                          | Description                                                  |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| interface IActivatedEventArgs<br/> {<br/> ActivationKind Kind,<br/> ApplicationExecutionState  PreviousExecutionState,<br/> SplashScreen SplashScreen<br/> } | All XXXActivatedEventArgs types implement this interface.<br/>**Kind**: enum value indicating the type of this activation. <br/>**PreviousExecutionState**: in UWP, this gets the execution state of<br/>the app before this activation. The app can use this information to <br/>determine whether it should restore saved state. For Win32, the value <br/>will be ApplicationExecutionState.NotRunning. <br/>**SplashScreen**: in UWP, this gets the execution state of the app before <br/>this activation. The app can use this information to determine whether<br/> it should restore saved state. For Win32, the value will be ApplicationExecutionState. NotRunning. |
| class LaunchActivatedEventArgs                               | Implements IActivatedEventArgs, plus the following:          |
| interface ILaunchActivatedEventArgs<br/> {<br/> string Arguments;<br/> string TileId; <br/> }<br/> | **Arguments** is the minimum required property for this activation type. <br/>**TileId** is not applicable for Win32, and will return an empty string. |
| class FileActivatedEventArgs                                 | Implements IActivatedEventArgs, plus the following:          |
| interface IFileActivatedEventArgs<br/> {<br/> IVectorView<IStorageItem> Files;<br/> string Verb;<br/> } <br/> | **Files** is the minimum required property for this activation type. <br/>**Verb** is an arbitrary string that indicates the action associated <br/>with the activated file (open, delete, etc). |
| class ProtocolActivatedEventArgs                             | Implements IActivatedEventArgs, plus the following:          |
| interface IProtocolActivatedEventArgs<br/> {<br/> Uri Uri;<br/> }<br/> | **Uri** is the minimum required property for this activation type. |
| class StartupTaskActivatedEventArgs                          | Implements IActivatedEventArgs, plus the following:          |
| interface IStartupTaskActivatedEventArgs<br/> {<br/> string TaskId;<br/> }<br/> | **TaskId** is an app-defined value; the app can use this later in the <br/>StartupTask API to request enabling or disabling of the startup behavior. |

### Activation registration

For most activation kinds, the optional attributes that are available for the
traditional registry-based activation registrations are roughly equivalent to
those available for UWP manifest-based registration. The exception to this is
file-type association, where traditional registry activation offers 5 optional
attributes, whereas UWP offers 37 optional attributes. Most of the UWP optional
attributes are very rarely used, and in some cases there are no apps in the
Store that use a given parameter. For v1, the platform will support all the
registry-based optional attributes - further UWP attributes may be included in a
later release.

The new RegisterForXXXActivation methods will be exposed as static methods from
a new ActivationRegistrationManager class in the AppLifecycle component.

The aim is that the app would call any of these RegisterForXXXActivation methods
at any time dynamically from the app itself. For v1, this API does not support
calling from the app's installer. For filetype and protocol, the app can call
the RegisterForXXXActivation method multiple times, each time providing
different filetype names or different protocol names. These registrations would
be cumulative, so long as the parameters are different. If the app tries to
register for the same filetype name or the same protocol multiple times, this is
idempotent (there's only one registration per unique filetype name or protocol
name; no error for multiple identical registrations, any new values supplied for
the same registration overwrite any old values).

Similarly, if the app registers multiple times for startup, this is also
idempotent (a single registration, no error, any new values supplied overwrite
any old values).

| API                                                          | Description                                                  |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| class ActivationRegistrationManager                          | New class to encapsulate the activation RegisterForXXXActivation and UnregisterForXXXActivation methods. |
| static void RegisterForFileTypeActivation(<br/> string supportedFileTypes[],<br/> string logo,<br/> string displayName,<br/> string supportedVerbs[],<br/> string exePath<br/>); | **supportedFileTypes**: one or<br/>more supported filetypes, specified by the file extension including<br/>the leading ".", eg ".docx".<br/>**logo**: used by the Shell and Settings for this filetype.<br/>In UWP this is a package-relative path to an image file.<br/>In Win32 registry-based filetype registrations, it's a filepath<br/>to a binary file plus a resource index. The caller can pass either.<br/>**displayName**: used by the Shell and Settings for this filetype.<br/>**supportedVerbs**: zero or more app-defined verbs. Each verb is<br/>added to the File Explorer context menu when a registered file is<br/>right-clicked; and the selected verb is passed to the app as the<br/>FileActivatedEventArgs::Verb property.<br/>**exePath**: path to the executable to be activated.<br/>Typically this is specified if the caller is the app's installer<br/>rather than the app itself. |
| static void RegisterForProtocolActivation(<br/> string schemeName,<br/> string logo,<br/> string displayName,<br/> string exePath<br/>); | **schemeName**: the protocol identifier, eg "foo" or "https".<br/>**logo**: used by the Shell and Settings for this scheme.<br/>In UWP this is a package-relative path to an image file.<br/>In Win32 registry-based filetype registrations, it's a filepath<br/>to a binary file plus a resource index. The caller can pass either.<br/>**displayName**: used by the Shell and Settings for this scheme.<br/>**exePath**: path to the executable to be activated. |
| static void RegisterForStartupActivation(<br/> string taskId,<br/> string exePath<br/>); | **taskId**: a string identifier which the app can use in<br/>the StartupTask API to request enabling or disabling of the <br/>startup behavior.<br/>**exePath**: path to the executable to be activated. |



### Activation unregistration

The new ActivationRegistrationManager class will also include UnregisterForXXXActivation methods for each of the
supported activation kinds.

| API                                                          | Description                                                  |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| static void UnregisterForFileTypeActivation(<br/> string fileTypes[], <br/> string exePath<br/> ); | **fileTypes**: one or more filetypes that the caller wants to unregister. <br/>**exePath**: path to the executable that was registered for activation. |
| static void UnregisterForProtocolActivation(<br/> string schemeName,<br/> string exePath<br/> ); | **schemeName**: the previously-registered protocol identifier, <br/>eg "foo" or "https". <br/>**exePath**: path to the executable that was registered for activation. |
| static void UnregisterForStartupActivation(<br/> string taskId,<br/> string exePath<br/>); | **taskId**: a string identifier which the app specified when it<br/>registered for startup behavior initially.<br/>**exePath**: path to the executable that was registered for activation. |

<br/>
