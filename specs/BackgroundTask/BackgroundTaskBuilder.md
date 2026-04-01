BackgroundTaskBuilder API
===

This is the spec for BackgroundTaskBuilder API to support Background Task Registration for WinAppSDK apps.

[Related Bug Report]( https://github.com/microsoft/WindowsAppSDK/issues/3840)


# Background
Background tasks are app components that run in the background without a user interface. They can perform actions such as downloading files, syncing data, sending notifications, or updating tiles. They can be triggered by various events, such as time, system changes, user actions, or push notifications. These tasks can get executed when corresponding trigger occurs even when the app is not in running state.
Current [BackgroundTaskBuilder](https://learn.microsoft.com/en-us/uwp/api/windows.applicationmodel.background.backgroundtaskbuilder) is designed for UWP applications and many of the Background Task triggers are not supported for full trust COM Components and are supported only to be registered with Windows Runtime components that is to be launched with backgroundtaskhost process. Due to this, WinAppSDK desktop applications won’t be able to directly register the full trust COM components to be launched with background task triggers and have to do workaround of including the Windows Runtime components in the project.
This API takes care of avoiding this workaround so that WinAppSDK applications can directly register the full trust COM components with the background tasks.

# Conceptual pages (How To)

 ## Register Background Task (c++)

 Registering a Background Task for full trust COM component. Developers may also need to set the **WindowsAppSDKBackgroundTask** property as *true* in the project configuration. Also in the manifest file *EntryPoint* for BackgroundTask is to be set as **Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.Task**

 ```c++
       //Using WinAppSDK API for BackgroundTaskBuilder
        winrt::Microsoft::Windows::ApplicationModel::Background::BackgroundTaskBuilder builder;
        SystemTrigger trigger = SystemTrigger(SystemTriggerType::TimeZoneChange, false);
        auto backgroundTrigger = trigger.as<IBackgroundTrigger>();
        builder.SetTrigger(backgroundTrigger);
        builder.AddCondition(SystemCondition(SystemConditionType::InternetAvailable));
        builder.SetTaskEntryPointClsid(classGuid);
        builder.Register(); 
```

Package Manifest:
```
        <Extension Category="windows.backgroundTasks" EntryPoint="Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.Task">
            <BackgroundTasks>
                <Task Type="general"/>
            </BackgroundTasks>
        </Extension>
```

# API Pages

## BackgroundTaskBuilder class

Represents a background task to register with the system.

This class is not agile, which means that you need to consider its threading model and marshaling behavior. For more info, see [Agile Objects in C++/WinRT](https://learn.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/agile-objects), [Threading and Marshaling (C++/CX)]( https://learn.microsoft.com/en-us/cpp/cppcx/threading-and-marshaling-c-cx?view=msvc-170 ) and [Using Windows Runtime objects in a multithreaded environment (.NET)]( https://learn.microsoft.com/en-us/windows/uwp/threading-async/using-windows-runtime-objects-in-a-multithreaded-environment)


## BackgroundTaskBuilder constructor

| Name | Description |
|-|-|
| BackgroundTaskBuilder  | Create a new BackgroundTaskBuilder object.|


## BackgroundTaskBuilder Properties

| Name | Description | Value |
|-|-|-|
|Name| Gets or sets the name of a background task.| __String__ (A string representing name of the task) |
|TaskGroup| Gets and sets the group identifier so that background task registration can be maintained separately.| __BackgroundTaskRegistrationGroup__ (The group identifier for the task) |


## BackgroundTaskBuilder Methods

| Name | Description | Parameters | Returns |
|-|-|-|-|
| AddCondition(IBackgroundCondition) | Adds a condition to a background task.| __IBackgroundCondition__ Condition for Background Task | |
| Register() | Registers a background task with the system.| | __BackgroundTaskRegistration__|
| Register(String) | Registers a background task with the system.| __String__ Name for the task | __BackgroundTaskRegistration__|
| SetTaskEntryPointClsid(GUID) | Assigns a COM CLSID entry point using an existing BackgroundTaskBuilder object. | __GUID__ GUID of the Entry point class | |
| SetTrigger(IBackgroundTrigger) | Sets the event trigger for a background task. | __IBackgroundTrigger__ Trigger for Background Task | |



# API Details

> Note: all of this new WinAppSDK API is the same as the existing UWP API
 [BackgroundTaskBuilder](https://learn.microsoft.com/en-us/uwp/api/windows.applicationmodel.background.backgroundtaskbuilder), only changing the register operation internally to use WindowsRuntimeComponent for registration and then use the WindowsRuntimeComponent to activate the COM component of the application.
```c# (but really MIDL3)
// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

namespace Microsoft.Windows.ApplicationModel.Background
{
    [contractversion(1)]
    apicontract BackgroundTaskContract{};

    [contract(BackgroundTaskContract, 1)]
    runtimeclass BackgroundTaskBuilder
    {
        BackgroundTaskBuilder();

        void SetTrigger(
                Windows.ApplicationModel.Background.IBackgroundTrigger trigger
            );

        void AddCondition(
                winrt::Windows::ApplicationModel::Background::IBackgroundCondition trigger
            );

        void
            SetTaskEntryPointClsid(
                GUID clsId
            );

        String Name{ set; get; };
        Windows.ApplicationModel.Background.BackgroundTaskRegistrationGroup TaskGroup { set; get; };

        Windows.ApplicationModel.Background.BackgroundTaskRegistration Register(
            );
        Windows.ApplicationModel.Background.BackgroundTaskRegistration Register(
                String taskName
            );
    }
}

```

