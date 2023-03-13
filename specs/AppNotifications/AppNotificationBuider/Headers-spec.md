
App Notification Headers
===

# Background

[App notifications](https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/notifications/app-notifications/app-notifications-quickstart?tabs=cs)
in the Windows App SDK are messages that your app can construct and deliver to
your user while they are not currently inside your app, for example:

![App notification example](AppNotificationExample.png)

App notifications are defined in XML, and the
[AppNotificationBuilder](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/Microsoft.Windows.AppNotifications.Builder.AppNotificationBuilder)
API provides a programattic way to build that XML.

The `AppNotificationBuilder` though does not support the 
[`header`](https://learn.microsoft.com/en-us/windows/apps/design/shell/tiles-and-notifications/toast-schema#toastheader)
feature of the XML.

Headers let developers identify related notifications so they can be grouped together in Notification Center, such as "Camping!!" in this example:

![AppNotification Header Example](HeaderExample.png)

The above notification is defined by:

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

The new API in this spec provides a way to build this with the `AppNotificationBuilder`.

# API Pages

## AppNotificationHeader class

Specifies a custom header that groups multiple notifications together within the notification.

In the following example, `AppNotificationBuilder` sets a header onto an
[AppNotification](https://docs.microsoft.com/windows/windows-app-sdk/api/winrt/Microsoft.Windows.AppNotifications.AppNotification).

```c++
auto builder{ winrt::AppNotificationBuilder()
    .SetHeader(winrt::AppNotificationHeader(L"6289", L"Camping!!")
        .AddArgument(L"action", L"openConversation")
        .AddArgument(L"id", L"6289"))
    .AddText(L"Anyone have a sleeping bag I can borrow?") };
```

This example uses the same header in multiple notifications:


```c++
auto header{ winrt::AppNotificationHeader(L"6289", L"Camping!!")
    .AddArgument(L"action", L"openConversation")
    .AddArgument(L"id", L"6289") };

auto builder1{ winrt::AppNotificationBuilder()
    .SetHeader(header)
    .AddText(L"Camping this weekend?")
};

auto builder2{ winrt::AppNotificationBuilder()
    .SetHeader(header)
    .AddText(L"Anyone have a sleeping bag I can borrow?")
};
```

The above usage produces the results bellow.

![AppNotification Header Example](HeaderExample.png)



# API Details

```idl
[contract(AppNotificationBuilderContract, 2)]
runtimeclass AppNotificationHeader
{
    AppNotificationHeader();
    AppNotificationHeader(String id, String title);

    String Id;
    String Title;
    Windows.Foundation.Collections.IMap<String, String> Arguments;

    AppNotificationHeader AddArgument(String key, String value);
};

[contract(AppNotificationBuilderContract, 1)]
runtimeclass AppNotificationBuilder
{
    ...

    [contract(AppNotificationBuilderContract, 2)]
    AppNotificationBuilder SetHeader(AppNotificationHeader value);

    ...
```

# Appendix

* The new AppNotificationHeader runtimeclass is needed because a Header can have a variable 
number of arguments.

* I thought about factoring out a runtimeclass specifically for holding arguments, similar to 
how AppNotificationTextProperties holds properties for text items, but this would require 
changes to a published API and the gain would be marginal at best as the xml required to 
define the arguments in a Header differs from the xml defining the arguments in the 
notification itself.

* The AppNotificationBuilder runtime classes typically offer both properties and fluent setters, 
although there may be some exceptions. This is an established pattern since the first iteration of 
the builder was released (in version 1.2), and the APIs in this spec adhere to it.

* The fluent setters work in any languages and let developers specify complex AppNotification 
using the dot notation. The property accessors are useful in langugages that support object 
initialization syntax (C# does but C++ does not, for example) and offer an alternate syntax 
to the dot notation afforded by the fluent setter by letting developers configure objects at 
construction time.