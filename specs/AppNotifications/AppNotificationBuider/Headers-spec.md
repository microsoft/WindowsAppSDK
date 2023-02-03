# Header

## Problem Definition

## Proposal

# FAQ

![AppNotification Header Example](toast-content-headers.png)

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

```c++
auto builder{ winrt::AppNotificationBuilder()
    .SetHeader(winrt::AppNotificationHeader(L"6289", L"Camping!!")
        .AddArgument(L"action", L"openConversation")
        .AddArgument(L"id", L"6289"))
    .AddText(L"Anyone have a sleeping bag I can borrow?")
};
```

```idl
[contract(AppNotificationBuilderContract, 2)]
runtimeclass AppNotificationHeader
{
    AppNotificationHeader();
    AppNotificationHeader(String id, String title);

    AppNotificationHeader AddArgument(String key, String value);
};
```



