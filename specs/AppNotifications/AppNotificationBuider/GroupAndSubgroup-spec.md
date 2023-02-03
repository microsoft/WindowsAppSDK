# Group and Subgroup

## Problem Definition


## Proposal





# FAQ

![AppNotification Group and Subgroup Example](toast-content-columns.png)

```xml
<toast>
    <visual>
        <binding template='ToastGeneric'>
            <text>Reminder: Windows Launch Party</text>
            <text>4:00 PM, 10/21/2021</text>
            <group>
                <subgroup>
                    <text hint-style='base'>52 attendees</text>
                    <text hint-style='captionSubtle'>23 minute drive</text>
                </subgroup>
                <subgroup>
                    <text hint-style='captionSubtle' hint-align='right'>1 Microsoft Way</text>
                    <text hint-style='captionSubtle' hint-align='right'>Bellevue, WA 98008</text>
                </subgroup>
            </group>
        </binding>
    </visual>
</toast>
```

```c++
auto builder{ winrt::AppNotificationBuilder()
    .AddText(L"Reminder: Windows Launch Party")
    .AddText(L"4:00 PM, 10/21/2021")
    .AddGroup(winrt::AppNotificationGroup()
        .AddSubgroup(winrt::AppNotificationSubgroup()
            .AddText(L"52 attendees", winrt::AppNotificationTextProperties()
                .SetStyle(winrt::AppNotificationTextStyle::Base))
            .AddText(L"23 minute drive", winrt::AppNotificationTextProperties()
                .SetStyle(winrt::AppNotificationTextStyle::CaptionSubtle)))
        .AddSubgroup(winrt::AppNotificationSubgroup()
            .AddText(L"1 Microsoft Way", winrt::AppNotificationTextProperties()
                .SetStyle(winrt::AppNotificationTextStyle::CaptionSubtle)
                    .SetAlign(winrt::AppNotificationTextAlign::Right))
            .AddText(L"Bellevue, WA 98008", winrt::AppNotificationTextProperties()
                .SetStyle(winrt::AppNotificationTextStyle::CaptionSubtle)
                    .SetAlign(winrt::AppNotificationTextAlign::Right))))
};
```c++