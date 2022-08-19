# Notes

## Situation
PushNotificationManager is a singleton.
The first call to Default() will construct the object before return a reference to it. Subsequent calls will return a reference the already constructed obejct.
It's expected that the developer will call Register() early on. Usually the only action expected prior to calling Register() is setting the notification callback.
The recommanded sequece is:
1. Receive()
2. Register()
3. CreateChannelAsync()
It's expected that the developer will call Unregister() before exiting the application, although there  are contingencies in place in case that doesn'thappen. In the case the app crashes for example.
Instanciating an instance of the PushNotificationManager is a complex operation that will varies depending on the type of app (Packaged or not packaged) and the OS version (not all OS version supprt the full set of features or implementation details may vary))
A packaged application should providde a description for the COM Server in the appxmanifest, that will be used to setup callbacks and it will be used at construction.

## Problem
Some legit uses can differ from the recommanded usage pattern. For example a developer may only want to call CreateChannelAsyn() in order to obtain a channel but may not intent to receive notification during this activation.
In that case it would make sense to only call CreateChannelAsync() and not call register.
There is also no need to provide a COM Sever in the appmanifest since the app isn't expecting to be called back.
The problem is that PushNotificationManager expects the appmanifest to contain  a Com Server and construction will fail if it doesn't.
 
## Solution
Modify PushNotificationManager so that it won't fail at construction if there is no COM server specified.
Instead the PushNotificationManager should throw an exception if Register is called and a COM Sever wasn't present a construction time.
By delaying when the absence of a COM server is handle to the very moment it is actually needed (in Register()), we allow developers to use the manager only to obtain a channel, if they so desire.
