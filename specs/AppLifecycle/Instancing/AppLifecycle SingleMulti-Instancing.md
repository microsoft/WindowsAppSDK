# AppLifecycle - Single/Multi-instancing

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

This spec addresses the Single/Multi-instancing APIs in the component.

<br>

## Background

Traditional Win32 apps are multi-instanced by default, and they have to do work
to achieve single-instancing if they need that behavior. For example, If you
open a docx file in Word, and then attempt to open the same file in another
instance of Word, the app detects that you're doing this, redirects you to the
existing instance, and terminates the new instance. There is no platform-defined
formal mechanism or pattern for achieving single-instancing: apps tend to use
named mutexes. If an app's instances need to communicate with each other - even
if only to gather information about each other to make a decision about
single-instancing, they often use named pipes.

Conversely, UWP apps are single-instanced by default. Windows 10 1803 introduced
support for UWP apps to opt in to be multi-instanced. This also allowed for the
possibility that even though an app has chosen to be multi-instanced, there
might be some scenario where it wants to redirect a fresh activation request to
an existing instance instead.

<br>

## Description

The Reunion behavior is based on the existing  [Windows.ApplicationModel.AppInstance](https://docs.microsoft.com/en-us/uwp/api/windows.applicationmodel.appinstance) class, but with some key differences:

| Feature                      | Common Behavior                                              | Platform Behavior                                            | Reunion Behavior                                             |
| ---------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| List of instances            | The system maintains a list of running instances of the app. The list includes instances that are running, suspending, or suspended, as well as instances that are being hosted in other apps (for example, file pickers or share targets). The list excludes instances that are Watsoning, and background-only instances (activated for in-proc background tasks). | GetInstances returns only the instances that the app explicitly registered for potential redirection. | GetInstances returns all running instances of the app.       |
| Registering  keys            | Each instance of the app can register a key, and this key is based on arbitrary app-defined logic. The app is allowed to set its key as many times as it likes; and each time we will overwrite the data for that instance in the cache. A given key can only be registered for one instance. If an app attempts to register a key that has already been registered for a different instance, the API will return the registered instance, and the app can check whether it is the current instance. | An instance must register a key in order to be included in the list returned from GetInstances. | Registering a key is decoupled from the list of instances.   |
| Instance redirection targets | An instance of an app can take part in "activation redirection". This means that this instance of the process can handle multiple Activated events, and so it could be a target for selective activation redirection. When an activation is redirected to another instance, it arrives at that instance's Activated callback, thus hooking into the normal activation workflow that apps already expect. An app can have multiple instances available as redirection targets. | Only instances that have registered a key can be a target for redirection. | Any instance can be a redirection target, whether or not it has a registered key. |
| Redirection                  | Redirection is a terminal operation. After calling the method to redirect, there is nothing the app can do - regardless of whether the redirect succeeded or failed. In calling redirect, the app is saying that it cannot/will not handle this activation request - so even if the redirection fails, there's nothing this instance can or will do anyway. The platform will explicitly terminate an instance that has chosen to redirect. If redirection fails, the activation request fails. The UX is the same as an activation failure today. |                                                              |                                                              |
| Unregistering                | At any time, an instance of the app can unregister its key. At any time, an app instance can re-register itself (again with any arbitrary key, not necessarily the same key each time), even after it has unregistered itself. | When an instance unregisters itself, it is no longer available for activation redirection. An app that has unregistered itself is not included in the list of instance that is made available to the app. | Unregistering a key does not prevent an instance from being a target for redirection. Nor does it exclude the instance from the list. |
| Receiving activation         | In order to handle reactivation, the app can register for an Activated event. | The event passes an IActivatedEventArgs to the app.          | The event passes an ActivationArguments  to the app.         |

<br>

## Examples

### Redirection logic based on activation kind

In this example, the app calls GetActivatedEventArgs, and if it has been
activated as a result of a file-type association, it checks first to see if
there is any other instance already running that has this file open. The app can
tell whether the instance has the file open because it includes the filename as
part of the key that it registers with the system.

If it finds another instance with the file open, the app redirects this
activation to that instance, and then does nothing. After redirecting the
activation to the other instance, the system will then terminate this instance.

If it doesn't find another instance with the file open, it registers itself as
the instance that has this file open, and continues with normal app
initialization (creating its main window, starting its message pump, and so on).

```c++
int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    // First, we'll get our rich activation event args.
    ActivationArguments activationArgs =
        AppInstance::GetCurrent().GetActivatedEventArgs();

    // An app might want to set itself up for possible redirection in 
    // the case where it opens files - for example, to prevent multiple
    // instances from working on the same file.
    ExtendedActivationKind kind = activationArgs.Kind;
    if (kind == ExtendedActivationKind::File)
    {
        auto fileArgs = activationArgs.Data.as<FileActivatedEventArgs>();
        auto file = fileArgs.Files().GetAt(0);

        // Let's try to register this instance for this file.
        AppInstance instance =
            AppInstance::FindOrRegisterForKey(file.Name());
        if (instance.IsCurrent)
        {
            // If we successfully registered this instance, we can now just
            // go ahead and do normal initialization.
            RegisterClassAndStartMessagePump(hInstance, nCmdShow);
        }
        else
        {
            // Some other instance has already registered for this file, 
            // so we'll redirect this activation to that instance instead.
            instance.RedirectTo(activationArgs);
        }
    }
    return 1;
}
```

### Arbitrary redirection

In the previous example, the app only redirects for file activations. In the
simplest case, it might just redirect on every activation if there is already an
instance running. The logic for deciding when to redirect is entirely up to the
app - it might be dependent on activation kind, or on some other logic.

In the following example, the app might have checked some specific activation
kind first, or it might not. Regardless, the app then checks all other running
instances to see if any of them has registered to be a "reusable" instance. What
constitutes "reusable" is also entirely up to the app to decide. It might be any
instance that doesn't have a file open, or doesn't have an editing session
active, or has some specific database connection, and so on. If it finds a
reusable instance, it redirects activation to that instance; if not, it goes
ahead with this activation and normal app initialization. In this example, the
app signals that an instance is reusable by specifying the "reusable" text as
the key it registers with the system. Of course, exactly what text to use for
this purpose is entirely up to the app to decide. For more complex scenarios, if
the app wanted to allow for multiple reusable instances, it could specify
"reusable" plus some unique identifier for each instance, and so on.

```c++
int APIENTRY B_wWinMain(
    _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    ActivationArguments activationArgs =
        AppInstance::GetCurrent().GetActivatedEventArgs();
    
    // As above, check for any specific activation kind we care about.
    ExtendedActivationKind kind = activationArgs.Kind;
    if (kind == ExtendedActivationKind::File)
    {
        // etc... as in previous scenario.
    }
    else
    {
        // For other activation kinds, we'll trawl all instances to see if
        // any are suitable for redirecting this request. First, get a list
        // of all running instances of this app.
        auto instances = AppInstance::GetInstances();

        // In the simple case, we'll redirect to any other instance.
        AppInstance instance = instances.GetAt(0);

        // If the app re-registers re-usable instances, we can filter for these instead.
        bool isFound = false;
        for (AppInstance instance : instances)
        {
            if (instance.Key.c_str() == "REUSABLE")
            {
                isFound = true;
                instance.RedirectTo(activationArgs);
                break;
            }
        }
        if (!isFound)
        {
            // We'll register this as a reusable instance, and then
            // go ahead and do normal initialization.
            winrt::hstring szKey = L"REUSABLE";
            AppInstance::FindOrRegisterForKey(szKey);
            RegisterClassAndStartMessagePump(hInstance, nCmdShow);
        }
    }
    return 1;
}
```

### Handling redirection

The first 2 scenarios illustrate how an app would redirect to another running
instance. This scenario shows how an app would handle the case where it is
already running, and then a fresh activation is redirected to this instance. The
AppInstance class will expose an Activated event, for which the app can
register. In its Activated event handler, the app would examine the type of
activation, retrieve the rich ActivationArguments object, and then do whatever
app-specific work it wishes to do based on those arguments.

```c++
int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    // First, hook up the Activated event, to allow for this instance of the app
    // getting reactivated as a result of multi-instance redirection.
    AppInstance::Activated([](ActivationArguments args)
        { OnActivated(args); });

    //...etc - the rest of WinMain as normal.
}

void OnActivated(ActivationArguments const& args)
{
    ExtendedActivationKind kind = args.Kind;
    if (kind == ExtendedActivationKind::Launch)
    {
        LaunchActivatedEventArgs launchArgs 
            = args.Data.as<LaunchActivatedEventArgs>();
        DoSomethingWithLaunchArgs(launchArgs.Arguments());
    }
    else if (kind == ExtendedActivationKind::File)
    {
        FileActivatedEventArgs fileArgs 
            = args.Data.as<FileActivatedEventArgs>();
        DoSomethingWithFileArgs(fileArgs.Files());
    }
    else if (kind == ExtendedActivationKind::Protocol)
    {
        ProtocolActivatedEventArgs protocolArgs 
            = args.Data.as<ProtocolActivatedEventArgs>();
        DoSomethingWithProtocolArgs(protocolArgs.Uri());
    }
    else if (kind == ExtendedActivationKind::StartupTask)
    {
        StartupTaskActivatedEventArgs startupArgs 
            = args.Data.as<StartupTaskActivatedEventArgs>();
        DoSomethingWithStartupArgs(startupArgs.TaskId());
    }
}
```

### Redirection orchestration

We can also imagine a more advanced scenario, where the app registers an
instance for redirection, but when it receives a redirected activation, it may
apply further app logic to decide whether to handle this new activation in the
current instance or redirect again, effectively chaining redirections.

```c++
void OnActivated(ActivationArguments const& args)
{
    ExtendedActivationKind kind = args.Kind;

    // For example, we might want to redirect protocol activations.
    if (kind == ExtendedActivationKind::Protocol)
    {
        ProtocolActivatedEventArgs protocolArgs 
            = args.Data.as<ProtocolActivatedEventArgs>();
        Uri uri = protocolArgs.Uri();

        // We'll try to find the instance that handles protocol activations.
        // If there isn't one, then this instance will take over that duty.
        auto instance 
            = AppInstance::FindOrRegisterForKey(
                uri.AbsoluteUri().c_str());
        if (!instance.IsCurrent)
        {
            instance.RedirectTo(args);
        }
        else
        {
            DoSomethingWithProtocolArgs(uri);
        }
    }
    else 
    {
        // In this example, this instance of the app handles all other 
        // activation kinds.
        DoSomethingWithNewActivationArgs(args);
    }
}
```

In the existing UWP API, RedirectActivationTo does not take any parameters.
However, in the UWP case, the activation contract is tightly controlled, and we
could ensure that the arguments passed on to the app were the arguments for the
redirected instance. In bringing this feature to Win32, we can't control
activation as tightly. Also, the ActivationArguments object returned by
GetActivatedEventArgs is not the same object as the IActivatedEventArgs object
that is passed in to the Activated event callback. The new API gives the app the
opportunity to modify or replace the payload to be passed to the target instance.

### Unregister for redirection

Just as an app can define its own logic for how and when it registers an
instance for redirection, so too will it be able to define its own logic for
when a given instance no longer wants to be a target for redirection.

Following the previous example of an app that supports filetype activation, and
redirects to the instance that already has the selected file open - when that
file is closed, the app could unregister itself.

```c++
void CALLBACK OnFileClosed(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    AppInstance::GetCurrent().UnregisterKey(g_fileName);
}
```

<br>

## API Details

The existing Windows.ApplicationModel.Activation.AppInstance is narrowly-scoped to instance redirection, whereas the Reunion AppInstance class aims to be the focus for any functionality related to an app instance, not just to instance redirection. 

| API                                                          | Description                                                  |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| enum class ExtendedActivationKind<br/>{<br/>    /\* all existing platform ActivationKind values, \*/<br/>    ExtensionBase = 5000,<br/>    /\* new Reunion ExtendedActivationKind values\*/<br/>}; | This enum is based off the platform [ActivationKind](https://docs.microsoft.com/en-us/uwp/api/Windows.ApplicationModel.Activation.ActivationKind). All platform ActivationKind values are cloned to this class. Then, we set a high-value **ExtensionBase** value which is well above the existing highest ActivationKind value (1026), to allow for new values to be added to the platform. Going forward, any new platform values will also be added to the new enum, plus any new values that are only defined in the new enum. |
| class ActivationArguments<br/>{<br/>public:<br/>    ExtendedActivationKind Kind ;<br/>    IInspectable Data;<br/>}; | The platform defines [IActivatedEventArgs](https://docs.microsoft.com/en-us/uwp/api/Windows.ApplicationModel.Activation.IActivatedEventArgs), which exposes a Kind property. Apps can get an IActivatedEventArgs reference, examine the Kind and then cast the reference to the specific concrete class type that implements IActivatedEventArgs. This enables generic functions such as GetActivatedEventArgs and the Activated event handler, which provide the app with an IActivatedEventArgs that the app can then convert to a specific concrete type. However, IActivatedEventArgs also defines other properties that are only useful in a UWP context. In addition, we need a mechanism that supports both platform ActivationKinds and also Reunion-only ExtendedActivationKinds and their corresponding concrete class types. <br />The new ActivationArguments type serves this purpose: the app can examine the Kind, and then cast the Data property to the specific concrete type (which can be either a platform IActivatedEventArgs concrete class, or a Reunion class).<br />**Kind** is the enum value that indicates the kind of activation this object represents.<br />**Data** can be cast to a specific concrete class corresponding to Kind. |
| class AppInstance<br/>{<br/>public:<br/>    static AppInstance GetCurrent();<br/>    static IVector<AppInstance> GetInstances();<br/>    static AppInstance FindOrRegisterForKey(string key);<br/>    void UnregisterKey(string key);<br/>    void RedirectTo(ActivationArguments args);<br/>    ActivationArguments GetActivatedEventArgs();<br/>    static void Activated(EventHandler<ActivationArguments> const& handler);<br/>    string Key;<br/>    bool IsCurrent;<br/>}; | New class. This is the major new class exposed in the AppLifecycle component in Reunion. <br />**GetCurrent** returns an AppInstance that represents the current app instance.<br />**GetInstances** returns a collection of all running instances of the app. Note: the existing platform [AppInstance.GetInstances](https://docs.microsoft.com/en-us/uwp/api/windows.applicationmodel.appinstance.getinstances) only returns instances that have explicitly registered for multi-instance redirection. However, the new AppInstance Reunion class will provide an API surface for all manner of app-instance-related behaviors, not restricted to instance redirection. For this reason, Reunion will maintain a list of all running instances and will not require explicit registration by the app.<br />**FindOrRegisterForKey** enables an app to register an app-defined key for the current instance, or if another instance has already registered that key, then return that other instance instead. This is similar to the platform [AppInstance.FindOrRegisterInstanceForKey](https://docs.microsoft.com/en-us/uwp/api/windows.applicationmodel.appinstance.findorregisterinstanceforkey) except that that implementation is specific to instance redirection, whereas the Reunion design allows for the app to register a key for any reason.<br />**UnregisterKey** unregisters a given key for this instance. The existing  platform behavior is specific to instance redirection, and unregistering the key unregisters that instance for redirection (and removes it from the platform's collection of registered instances). In the Reunion design, unregistering a key simply removes the key for this instance; it does not have any effect on instance redirection, nor does it remove this instance from the collection that Reunion is maintaining of all running instances. <br />**RedirectTo** enables an instance of the app to redirect the current activation request to another instance. This is very similar to the existing platform [AppInstance.RedirectActivationTo](https://docs.microsoft.com/en-us/uwp/api/windows.applicationmodel.appinstance.redirectactivationto) method, except that the Reunion implementation allows the app to pass an ActivationArguments payload, thus opening the scope to allow the app to modify or replace the activation arguments that the target instance will receive.<br />**GetActivatedEventArgs** provides similar behavior as the existing platform [AppInstance.GetActivatedEventArgs](https://docs.microsoft.com/en-us/uwp/api/windows.applicationmodel.appinstance.getactivatedeventargs), except that it returns a new ActivationArguments object for the current activation instead of an IActivatedEventArgs. <br/> |

<br>
<br>
