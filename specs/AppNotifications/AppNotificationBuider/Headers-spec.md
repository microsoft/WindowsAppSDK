# Headers

Headers let developers identify related notifications so they can be grouped together in Notification Center.
![AppNotification Header Example](toast-content-headers.png)

Developers can specify a Header when defining a notification in raw xml, but the AppNotificationBuilder doesn't support  it.

```xml
<toast>
    <header 
        id='6289' 
        title='Camping!!' 
        arguments='action=openConversation;id=6289'/>
    <visual>
        <binding template='ToastGeneric'>
            <text>Anyone have a sleeping bag I can borrow?</text>
        </binding>
    </visual>
</toast>
```

Adding support for Headers to the AppNotificationBuilder is straightforward. All is needed is a new Header runtime class to represent the Header.

```idl
[contract(AppNotificationBuilderContract, 2)]
runtimeclass AppNotificationHeader
{
    AppNotificationHeader();
    AppNotificationHeader(String id, String title);

    AppNotificationHeader AddArgument(String key, String value);
};
```

Along with a new SetHeader function in the AppNotificationBuilder itself to set the Header.

```idl
[contract(AppNotificationBuilderContract, 1)]
runtimeclass AppNotificationBuilder
{
    ...

    [contract(AppNotificationBuilderContract, 2)]
    AppNotificationBuilder SetHeader(AppNotificationHeader value);

    ...
```

Using the updated AppNotificationBuilder, developers can quickly set a header on any AppNotification. 

```c++
auto builder{ winrt::AppNotificationBuilder()
    .SetHeader(winrt::AppNotificationHeader(L"6289", L"Camping!!")
        .AddArgument(L"action", L"openConversation")
        .AddArgument(L"id", L"6289"))
    .AddText(L"Anyone have a sleeping bag I can borrow?") };
```

# Additional Notes
* The new AppNotificationHeader runtimeclass is needed because a Header can have a variable number of arguments.

* I thought about factoring out a runtimeclass specifically for holding arguments, similar to how AppNotificationTextProperties hold properties for text items but this would require changes to published API and the gain would be marginal at best as the xml required to define the arguments in a Header differs from the xml defining the arguments in the notification itself.  

