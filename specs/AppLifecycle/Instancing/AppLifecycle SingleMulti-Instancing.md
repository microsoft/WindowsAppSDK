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

The existing WinRT APIs are exposed through the
[Windows.ApplicationModel.AppInstance](https://docs.microsoft.com/en-us/uwp/api/windows.applicationmodel.appinstance)
class, with the following behaviors:

1. The system maintains a cache of app instances, including some app-defined key
   for each instance.
   - The system returns these keys to the app when requested.
   - For each instance, the key is maintained in the cache until that instance's
     process terminates.
   - The app is allowed to set its key as many times as it likes; and each time
     we will overwrite the data for that instance in the cache.
   - A given key can only be registered for one instance. If an app attempts to
     register a key that has already been registered for a different instance,
     the API will return the registered instance, and the app can check whether
     it is the current instance.
   - The system creates a cache entry for an instance when that instance first
     calls Register.
2. An app can register the current instance of itself as wanting to take part in
   "activation redirection".
   - This means that this instance of the process can handle multiple
     OnActivated calls, and so it could be a target for selective activation
     redirection.
   - When an activation is redirected to another instance, it arrives at that
     instance's regular OnActivated callback, thus hooking into the normal
     activation workflow that apps already expect
   - We allow for multiple instances to register themselves as redirection
     targets.
     - This meets the requirement where one instance might be handling one set
       of activation contracts or environments (eg holographic), and other
       instances might handle other sets of activation contracts or
       environments.
   - Registration can fail, for example if multiple instances of the app try to
     register with the same app-defined data key.
   - Registration returns an object that includes:
     - The registration status after the call (succeeded, failed).
     - An object that represents the instance that is registered for the given
       key (which might be the current instance, or it might be another
       instance).
3. The cache will not include all instances, because some instances are not
   suitable for redirection:
   - Scoped to those instances that have registered themselves.
   - Including instances that are running, suspending, or suspended.
   - Including instances that are being hosted in other apps (for example, file
     pickers or share targets).
     - Redirection is to process instances, not views. The hosted view remains
       where it is, but the process gets another activation. A clever app could
       choose to bring up a new window and view set to show the incoming
       activation.
   - Excluding instances that are Watsoning.
   - Excluding background-only instances (activated for in-proc background
     tasks).
   - Excluding the current instance.
4. The app can compose its key for registration based on arbitrary app-defined
   logic.
5. The app can ask the platform for a list of registered instances and their
   keys.
   - This allows the app to examine each key to see if it is suitable for
     redirecting this activation request.
6. Redirection is a terminal operation.
   - After calling the method to redirect, there is nothing the app can do -
     regardless of whether the redirect succeeded or failed. In calling
     redirect, the app is saying that it cannot/will not handle this activation
     request - so even if the redirection fails, there's nothing this instance
     can or will do anyway.
   - The platform will explicitly terminate an instance that has chosen to
     redirect.
   - If redirection fails, the activation request fails. The UX is the same as
     an activation failure today.
7. Unregister itself.
   - At any time, an instance of the app can unregister itself so that it is no
     longer available for activation redirection.
   - An app that has unregistered itself is not included in the list of instance
     that is made available to the app.
   - At any time, an app instance can re-register itself, even after it has
     unregistered itself.
8. In order to handle reactivation, the app can register for an Activated event.
   This will include the XXXActivatedEventArgs for the redirected activation.

 <br>

## Examples

### Redirection logic based on activation kind

In this example, the app gets its XXXActivatedEventArgs, and if it has been
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
    IActivatedEventArgs activatedArgs = AppLifecycle::GetActivatedEventArgs();
    if (activatedArgs != NULL)
    {
        // An app might want to set itself up for possible redirection in
        // the case where it opens files - for example, to prevent multiple
        // instances from working on the same file.
        ActivationKind kind = activatedArgs.Kind();
        if (kind == ActivationKind::File)
        {
            auto fileArgs = activatedArgs.as<FileActivatedEventArgs>();
            auto file = fileArgs.Files().GetAt(0);

            // Let's try to register this instance for this file.
            auto instance = AppLifecycle::FindOrRegisterInstanceForKey(file.Name());
            if (instance.IsCurrentInstance)
            {
                // If we successfully registered this instance, we can now just
                // go ahead and do normal initialization.
                RegisterClassAndStartMessagePump(hInstance, nCmdShow);
            }
            else
            {
                // Some other instance has already registered for this file,
                // so we'll redirect this activation to that instance instead.
                instance.RedirectActivationTo(activatedArgs);
            }
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
int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    IActivatedEventArgs activatedArgs = AppLifecycle::GetActivatedEventArgs();
    if (activatedArgs != NULL)
    {
        // As above, check for any specific activation kind we care about.
        ActivationKind kind = activatedArgs.Kind();
        if (kind == ActivationKind::File)
        {
            // ? as in previous scenario.
        }
        else
        {
            // For other activation kinds, we'll trawl all instances to see if
            // any are suitable for redirecting this request. First, get a list
            // of all running instances of this app.
            auto instances = AppLifecycle::GetRegisteredInstances();

            // In the simple case, we'll redirect to any other instance.
            AppLifecycle instance = instances[0];

            // If the app re-registers re-usable instances, we can filter for these instead.
            bool isFound = false;
            for (AppLifecycle instance : instances)
            {
                if (instance.Key == L"REUSABLE")
                {
                    isFound = true;
                    instance.RedirectActivationTo(activatedArgs);
                    break;
                }
            }
            if (!isFound)
            {
                // We'll register this as a reusable instance, and then
                // go ahead and do normal initialization.
                winrt::hstring szKey = L"REUSABLE";
                auto instance = AppLifecycle::FindOrRegisterInstanceForKey(szKey);
                if (instance.IsCurrentInstance)
                {
                    // If we successfully registered this instance, we can now just
                    // go ahead and do normal initialization.
                    RegisterClassAndStartMessagePump(hInstance, nCmdShow);
                }
                else
                {
                    // Some other instance has already registered for this key,
                    // so we'll redirect this activation to that instance instead.
                    instance.RedirectActivationTo(activatedArgs);
                }
            }
        }
    }
    return 1;
}
```

### Handling redirection

The first 2 scenarios illustrate how an app would redirect to another running
instance. This scenario shows how an app would handle the case where it is
already running, and then a fresh activation is redirected to this instance. The
AppLifecycle class will expose an Activated event, for which the app can
register. In its Activated event handler, the app would examine the type of
activation, retrieve the rich XXXActivatedEventArgs object, and then do whatever
app-specific work it wishes to do based on those arguments.

```c++
int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    // First, hook up the Activated event, to allow for this instance of the app
    // getting reactivated as a result of multi-instance redirection.
    AppLifecycle::Activated([](IInspectable sender, auto args)
        { OnActivated(sender, args); });

    //...etc - the rest of WinMain as normal.
}

void OnActivated(IInspectable const& sender, IActivatedEventArgs const& args)
{
    ActivationKind kind = args.Kind();
    if (kind == ActivationKind::Launch)
    {
        auto launchArgs = args.as<LaunchActivatedEventArgs>();
        DoSomethingWithLaunchArgs(launchArgs.Arguments());
    }
    else if (kind == ActivationKind::File)
    {
        auto fileArgs = args.as<FileActivatedEventArgs>();
        DoSomethingWithFileArgs(fileArgs.Files());
    }
    else if (kind == ActivationKind::Protocol)
    {
        auto protocolArgs = args.as<ProtocolActivatedEventArgs>();
        DoSomethingWithProtocolArgs(protocolArgs.Uri());
    }
    else if (kind == ActivationKind::StartupTask)
    {
        auto startupArgs = args.as<StartupTaskActivatedEventArgs>();
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
void OnActivated(IInspectable const& sender, IActivatedEventArgs const& args)
{
    ActivationKind kind = args.Kind();

    // For example, we might want to redirect protocol activations.
    if (kind == ActivationKind::Protocol)
    {
        auto protocolArgs = args.as<ProtocolActivatedEventArgs>();
        Uri uri = protocolArgs.Uri();

        // We'll try to find the instance that handles protocol activations.
        // If there isn't one, then this instance will take over that duty.
        auto instance = AppLifecycle::FindOrRegisterInstanceForKey(uri.AbsoluteUri());
        if (instance.IsCurrentInstance)
        {
            DoSomethingWithProtocolArgs(uri);
        }
        else
        {
            instance.RedirectActivationTo(args);
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
activation as tightly. Also, the XXXActivatedEventArgs object returned by
GetActivatedEventArgs is not the same object as the XXXActivatedEventArgs object
that is passed in to the Activated event callback. We will give the app the
opportunity to pass either one or the other to the target instance.

### Unregister for redirection

Just as an app can define its own logic for how and when it registers an
instance for redirection, so too will it be able to define its own logic for
when a given instance no longer wants to be a target for redirection.

Following the previous example of an app that suppors filetype activation, and
redirects to the instance that already has the selected file open - when that
file is closed, the app could unregister itself.

```c++
void CALLBACK OnFileClosed(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    AppLifecycle::UnregisterForRedirection();
}
```

<br>

## API Details

The proposal is to bring across almost all the methods and properties of the
existing Windows.ApplicationModel.Activation.AppInstance into the Reunion
AppLifecycle class, with one exception. The RecommendedInstance property on the
existing AppInstance implementation is not implemented, so this will not be
brought forward to AppLifecycle.

| API                                                                   | Description                                                                                                                                                                                                                                                                                                                                          |
| --------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| class AppLifecycle                                                    | This is the major new class exposed in the undocked AppLifecycle component. Members of this class are described below. This spec only covers multi-instance redirection aspects here. Additional AppLifecycle properties, methods and events are specified in other specs.                                                                           |
| string Key                                                            | An arbitrary app-defined string for each instance of the app.                                                                                                                                                                                                                                                                                        |
| bool IsCurrentInstance                                                | Whether the current instance of the app is the registered instance of the app for the specific key that this instance has defined.                                                                                                                                                                                                                   |
| void RedirectActivationTo(IActivatedEventArgs)                        | Redirects activation of the current app instance to the specified instance. The app must pass in either the ActivatedEventArgs object it received from GetActivatedEventArgs (in the case this is not a redirected activation) or the ActivatedEventArgs object it received in its Activated callback (in the case this is a redirected activation). |
| static AppLifecycle FindOrRegisterInstanceForKey(string)              | Registers an app instance with the platform, or finds an existing instance if another instance has already registered this key.                                                                                                                                                                                                                      |
| static void UnregisterInstanceForRedirection ()                       | Updates the system cache so that the current instance is no longer available for activation redirection. Based on the AppInstance class where Unregister implicitly meant "unregister this instance" - in the new API we need a more specific name.                                                                                                  |
| static vector<AppLifecycle> GetRegisteredInstances()                  | Gets the registered instances of the current app. Even in the existing API, this always meant registered instances - not necessarily all instances - so we should be explicit.                                                                                                                                                                       |
| static event TypedEventHandler<object, IActivatedEventArgs> Activated | Event raised when an existing instance of an app is re-activated, as a result of multi-instance redirection.                                                                                                                                                                                                                                         |

<br>
<br>
