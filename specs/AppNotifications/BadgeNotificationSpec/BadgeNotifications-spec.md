# Badge notifications in Windows App SDK

<!-- Put an index here - see how dynamic dependencies doc do it -->

## Background

Badges are a notification type indicating a summary or status information specific to an app. It is represented either by a number or a glyph sitting over the taskbar app icon.

Here is an example of a numeric badge for the Microsoft To-Do List:

![Example of a numeric badge in Microsoft To-Do List](NumericBadge.PNG)

## Description

Badge notification Windows SDK APIs have three main limitations:

- It doesn't support Win32 apps, whether the app is packaged or not.
- The APIs expect a XML payload that contains the badge type to pin. There is no API where developers can directly send the number or glyph to pin.
- Ad of today, Badge APIs support a limited set of glyphs. If the app doesn't find any suitable glyph to convey their status, there is no option to pin a custom overlay.

More information about Windows SDK Badge API usage can be found [here](https://learn.microsoft.com/en-us/windows/apps/design/shell/tiles-and-notifications/badges#create-a-badge).

## API details

As part of bringing badges into Windows App SDK, we propose addressing the issues explained the previous section. Also, developers will be able to pin and clear badges writing less code than in the Windows SDK.

### 1. Posting a numeric badge

```cpp
BadgeNotificationManager::PostValue(4);
```

Note: Developers won't be able to post 0 or negative numbers for their badges.

### 2. Posting a glyph badge

We will provide an enum that contains all glpyhs already supported in the Windows SDK. This enum will be named `BadgeNotificationGlyph`.

```cpp
BadgeNotificationManager::PostGlyph(BadgeNotificationGlyph::Busy);
```

For a complete list of predefined glyphs, see the IDL details section.

### 3. Posting a custom overlay

```cpp
// using winrt::Windows::Foundation;

std::wstring iconFilepath{ std::filesystem::current_path() / "MyCustomBadge.png" };
BadgeNotificationManager::PostCustomBadge(Uri{iconFilepath});
```

### 4. Clear a badge

```cpp
BadgeNotificationManager::Clear();
```

## Remarks

- Badges will be tied to the lifetime of the app window. If the app is closed, the badge will be cleared.

## IDL details

``` idl
namespace Microsoft.Windows.AppNotifications.Badges
{
    [contractversion(1)]
    apicontract BadgeNotificationsContract {}

    // The following glyphs are based on what's currently available in the Windows SDK:
    // https://learn.microsoft.com/en-us/windows/apps/design/shell/tiles-and-notifications/badges
    [contract(BadgeNotificationsContract, 1)]
    enum BadgeNotificationGlyph
    {
        Activity,
        Alarm,
        Alert,
        Attention,
        Available,
        Away,
        Busy,
        Error,
        NewMessage,
        Paused,
        Playing,
        Unavailable
    };

    [contract(BadgeNotificationsContract, 1)]
    static runtimeclass BadgeNotificationManager
    {
        static void PostValue(UInt32 value);

        static void PostGlyph(BadgeNotificationGlyph glyph);

        static void PostCustomBadge(Windows.Foundation.Uri badgeUri);

        static void Clear();
    }
}
```