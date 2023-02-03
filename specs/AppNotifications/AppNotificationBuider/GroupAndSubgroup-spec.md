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
```

```idl
[contract(AppNotificationBuilderContract, 2)]
enum AppNotificationTextStyle
{
    Default,
    Caption,
    CaptionSubtle,
    Body,
    BodySubtle,
    Base,
    BaseSubtle,
    Subtitle,
    SubtitleSubtle,
    Title,
    TitleSubtle,
    TitleNumeral,
    Subheader,
    SubheaderSubtle,
    SubheaderNumeral,
    Header,
    HeaderSubtle,
    HeaderNumeral,
};
```

```idl
[contract(AppNotificationBuilderContract, 2)]
enum AppNotificationTextAlign
{
    Default,
    Auto,
    Left,
    Center,
    Right,
};
```

```idl
[contract(AppNotificationBuilderContract, 1)]
runtimeclass AppNotificationTextProperties
{
    // Contains the set of <text> attributes
    AppNotificationTextProperties();

    String Language;
    Boolean IncomingCallAlignment;
    Int32 MaxLines;

    [contract(AppNotificationBuilderContract, 2)]
    AppNotificationTextStyle Style;
    [contract(AppNotificationBuilderContract, 2)]
    Boolean Wrap;
    [contract(AppNotificationBuilderContract, 2)]
    Int32 MinLines;
    [contract(AppNotificationBuilderContract, 2)]
    AppNotificationTextAlign Align;

    AppNotificationTextProperties SetLanguage(String value);
    AppNotificationTextProperties SetIncomingCallAlignment();
    AppNotificationTextProperties SetMaxLines(Int32 value);

    [contract(AppNotificationBuilderContract, 2)]
    AppNotificationTextProperties SetStyle(AppNotificationTextStyle Style);
    [contract(AppNotificationBuilderContract, 2)]
    AppNotificationTextProperties SetWrap();
    [contract(AppNotificationBuilderContract, 2)]
    AppNotificationTextProperties SetMinLines(Int32 value);
    [contract(AppNotificationBuilderContract, 2)]
    AppNotificationTextProperties SetAlign(AppNotificationTextAlign Align);
};
```

```idl
[contract(AppNotificationBuilderContract, 2)]
runtimeclass AppNotificationSubgroup
{
    AppNotificationSubgroup();

    // Adds text to the AppNotificationSubgroup.
    AppNotificationSubgroup AddText(String text);
    AppNotificationSubgroup AddText(String text, AppNotificationTextProperties properties);

    // Sets the full-width inline-image that appears when you expand the AppNotification
    AppNotificationSubgroup SetInlineImage(Windows.Foundation.Uri imageUri);
    AppNotificationSubgroup SetInlineImage(Windows.Foundation.Uri imageUri, AppNotificationImageCrop imageCrop);
    AppNotificationSubgroup SetInlineImage(Windows.Foundation.Uri imageUri, AppNotificationImageCrop imagecrop, String alternateText);
};
```

```idl
[contract(AppNotificationBuilderContract, 2)]
runtimeclass AppNotificationGroup
{
    AppNotificationGroup();

    AppNotificationGroup AddSubgroup(AppNotificationSubgroup subgroup);
};
```

```idl
[contract(AppNotificationBuilderContract, 1)]
runtimeclass AppNotificationBuilder
{
    ...

    [contract(AppNotificationBuilderContract, 2)]
    AppNotificationBuilder AddGroup(AppNotificationGroup value);

    ...
};
```
